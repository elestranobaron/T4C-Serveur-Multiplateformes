// DOESN'T leave any file handle open.. so files are always accessible by outside viewers..

#include "stdafx.h"
#include <windows.h>
#include <time.h>
#include "OldLogger.h"
#include "format.h"
#include "Lock.h"
#include <process.h>
#include <stack>
#include <queue>

#pragma warning( disable : 4786 )

using namespace std;

// Internal LogItem class. Asynchronously passes data though async queues.
class LogItemQueue;
class LogItem{
public:
    void    SetLogger( CLogger *lpNewLogger ){ lpLogger = lpNewLogger; };
    void    SetText(   string bsNewText  )   { bsText = bsNewText; };

    CLogger *GetLogger( void ){ return lpLogger; };
    string  &GetText( void ){ return bsText; };

    // Construction and destruction of LogItems
    static LogItem  *GetLogItem( void );
    inline void      FreeLogItem( void );

    inline void     Push( void );
    static LogItem *Pop ( void );

private:
    typedef stack< LogItem * > ItemPool;
    typedef LogItemQueue       ItemQueue;
    
    LogItem( )
        :   lpLogger( NULL ), 
            bsText( "" )
    {};  
    
    // LogItem pool.
    static ItemPool  cItemPool;
    static CLock     cPoolLock;
    static ItemQueue cItemQueue;


    CLogger *lpLogger;
    string  bsText;    
};

class LogItemQueue : public CLock{
public:
    LogItemQueue(){
        hQueueEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
    }

    ~LogItemQueue(){
        CloseHandle( hQueueEvent );
    }
    
    // Delegate queue functions to the queue object.
    LogItem * pop( void ){ 
        // If the queue is currently empty.
        if( qQueue.empty() ){
            // Wait for a queue event to happen.
            if( WaitForSingleObject( hQueueEvent, 10000 ) == WAIT_OBJECT_0 ){
                ResetEvent( hQueueEvent );
            
                // If the queue isn't still empty.
                if( !qQueue.empty() ){
                    // Lock the queue.
                    CAutoLock cAutoLock( this );
            
                    // Returns the queue's top if the queue was signaled.                
                    LogItem *lpLogItem = qQueue.front();
                    qQueue.pop();
                    return lpLogItem;
                }
            }
        }else{
            // Lock the queue.
            CAutoLock cAutoLock( this );

            // Automaticaly return the queue's top.
            LogItem *lpLogItem = qQueue.front();
            qQueue.pop();            
            return lpLogItem;
        }
        // Return NULL otherwise.
        return NULL;
    }
    // Pushes an item into the asyn queue.
    void push( LogItem *lpItem ){ 
        // Lock the queue.
        CAutoLock cAutoLock( this );
        
        // Push the item to the queue.
        qQueue.push( lpItem ); 
        // Signal event.
        SetEvent( hQueueEvent );
    };

private:
    HANDLE hQueueEvent;
    queue< LogItem * > qQueue;
};


CLogger::CLogger(void) 
    :   bsLogFile ( "default.log" ),
        wSetLogLevels( LOG_DEBUG_LIGHT )
{
    InitializeCriticalSection( &critSection );
}

CLogger::~CLogger(void)
{
    DeleteCriticalSection( &critSection );
}


LogItem::ItemPool  LogItem::cItemPool;
LogItem::ItemQueue LogItem::cItemQueue;
CLock              LogItem::cPoolLock;


//////////////////////////////////////////////////////////////////////////////////////////
CLogger::AutoAsyncLogThreadStart::AutoAsyncLogThreadStart( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  This constructor initializes the logger's IO completion port and AsyncLogThread.
//  See CLogger::AsyncLog().
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Starts the AsyncLogThread
    _beginthread( AsyncLogThread,  0, NULL );
}


//////////////////////////////////////////////////////////////////////////////////////////
void CLogger::SetLogLevels
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets the log's levels.
// 
(
 WORD wNewLogLevels // The new log levels.
)                      
//////////////////////////////////////////////////////////////////////////////////////////
{
	Lock();
    
    wSetLogLevels = wNewLogLevels;

    Unlock();
}


//////////////////////////////////////////////////////////////////////////////////////////
void CLogger::SetLogFile
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets the current log file.
// 
(
 string bsNewFile // The new file name.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    Lock();
    
    // If the new file name is smaller than the maximum allowed path name,
    if( bsNewFile.size() < _MAX_PATH){
        bsLogFile = bsNewFile;
    }

    Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
WORD CLogger::GetLogLevels( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the log levels
// 
// Return:
//////////////////////////////////////////////////////////////////////////////////////////
{
	return wSetLogLevels;
}

namespace{
// Helper functions //////////////////////////////////////////////////////////////////////
inline const char *LogLvl2Str
//////////////////////////////////////////////////////////////////////////////////////////
//  Specifies the string equivalent of a debug log level.
// 
(
 WORD wLogLvl // The log level.
)
// Return: inline const, the corresponding string.
//////////////////////////////////////////////////////////////////////////////////////////
{
	switch ( wLogLvl )
	{
	case LOG_CRIT_ERRORS: return "CRITICAL";
	case LOG_GEN_ERRORS: return "Error";
	case LOG_DEBUG_LVL1: 
	case LOG_DEBUG_LVL2: return "Debug";
    case LOG_DEBUG_LVL3: return "Debug3";
    case LOG_DEBUG_LVL4: return "Debug4";
	case LOG_MEMORY: return "Memory";
	case LOG_WARNING: return "Warning";
	case LOG_ALWAYS: return "Info";
	case LOG_MISC_1: return "Misc1";
	case LOG_SYSOP: return "Admin";
    case LOG_DEBUG_HIGH: return "HeavyDbg";
    default: return "Log";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
inline string FormatLogString
//////////////////////////////////////////////////////////////////////////////////////////
//  Formats a string
// 
(
 WORD wLogLevels,       // The log levels.
 const char *szText     // The text.
)
// Return: inline string, the returns STL string.
//////////////////////////////////////////////////////////////////////////////////////////
{
    vir::TFormat format;

    string bsString;

    // If log levels isn't DEBUG_LVL2
    if ( wLogLevels != LOG_DEBUG_LVL2){            
        // Get the system time
        SYSTEMTIME sysTime; 
	    GetLocalTime(&sysTime);

        // Start with the date and time 
        bsString = format( 
            "\r\n(%s),%d/%d/%d,%d:%02d:%02d,",
			LogLvl2Str( wLogLevels ), 
            sysTime.wMonth,
            sysTime.wDay,
            sysTime.wYear, 
            sysTime.wHour, 
            sysTime.wMinute,
            sysTime.wSecond
        );
	}else{ 
        // Otherwise use a tab.
        bsString = "\r\n\t";
    }

    // Append the text to the string.
    bsString += szText;

    return bsString;
}

} // namespace

//////////////////////////////////////////////////////////////////////////////////////////
void CLogger::AsyncLog
//////////////////////////////////////////////////////////////////////////////////////////
//  Asynchronously logs the given string
// 
(
 WORD        wLogLevels, // The log levels.
 const char *szText,     // The text to log.
 ...                     // The format specifiers.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // This function doesn't need to lock the lpLogger since it uses
    // none of its internal functionnalities.
    
    // If the passed log levels are contained within the set log levels.
    if( wLogLevels & wSetLogLevels || wLogLevels == LOG_ALWAYS ){    
        char lpBuffer[ 4096 ];
        va_list argp;		
        va_start( argp, szText );
        vsprintf( lpBuffer, szText, argp );
        string bsLoggedString = FormatLogString( wLogLevels, lpBuffer );
        va_end( argp );
        
        // Create a new LogItem
        LogItem *lpLogItem = LogItem::GetLogItem();

        lpLogItem->SetLogger( this );
        lpLogItem->SetText  ( bsLoggedString );

        // Start the async. logger the first time this function is called.
        static AutoAsyncLogThreadStart cAutoStart;

        // Push the log item into its async queue.
        lpLogItem->Push();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void CLogger::SyncLog
//////////////////////////////////////////////////////////////////////////////////////////
//  Synchronously logs the given string
// 
(
 WORD        wLogLevels, // The log levels.
 const char *szText,     // The text to log.
 ...                     // The format specifiers.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // This function doesn't need to lock the lpLogger since it uses
    // none of its internal functionnalities.
    
    // If the passed log levels are contained within the set log levels.
    if( wLogLevels & wSetLogLevels ){    
        char lpBuffer[ 4096 ];

        va_list argp;		
        va_start( argp, szText );
        vsprintf( lpBuffer, szText, argp );
        string bsLoggedString = FormatLogString( wLogLevels, lpBuffer );
        va_end( argp );

        // Directly write the string.
        WriteLog( bsLoggedString.c_str() );        
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void CLogger::AsyncLogThread
//////////////////////////////////////////////////////////////////////////////////////////
// This thread asynchronously logs the queued data each time interval.
// 
(
 void *lpData // NULL
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    DWORD dwNbBytes = 0;
    LPOVERLAPPED lpOverlapped = NULL;
    while(1){
        DWORD dwLogAddr = 0;
        // Get next log item.
        LogItem *lpLogItem = LogItem::Pop();
        
        if( lpLogItem != NULL ){
            // Write the text to the specified logger item.
            lpLogItem->GetLogger()->WriteLog( lpLogItem->GetText().c_str() );

            // Free this log item.
            lpLogItem->FreeLogItem();
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void CLogger::WriteLog
//////////////////////////////////////////////////////////////////////////////////////////
//  Writes to a log file
// 
(
 const char *szString // The string to write to the log file.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    string bsFile;
    
    {
        // Lock this logger while we fetch its internal data.
        Lock();

        bsFile = bsLogFile;

        Unlock();
    }
    
    FILE *fFile = fopen( bsFile.c_str(), "ab" );

    // If the file is NULL
    if( fFile == NULL ){
        return;   
    }

    // Write the data.
    fputs( szString, fFile );

    // Close the file.
    fclose( fFile );
}

void CLogger::Lock(){
    EnterCriticalSection( &critSection );
}

void CLogger::Unlock(){
    LeaveCriticalSection( &critSection );
}


//////////////////////////////////////////////////////////////////////////////////////////
LogItem *LogItem::GetLogItem( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns a valid LogItem address. This function acts as a memory pool provider,
//  avoids having to 'new/delete' a LogItem each time we push it on the queue.
// 
// Return: LogItem, a valid LogItem (this function cannot fail).
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cAutoLock( &cPoolLock );
    
    // If the item pool is empty.
    if( cItemPool.empty() ){
        // Push 10 items into the pool.
        int i;
        for( i = 0; i < 10; i++ ){
            cItemPool.push( new LogItem() );
        }
    }
    
    // Set the log item as being the top of the pool
    LogItem *lpLogItem = cItemPool.top();

    // Pop the top item.
    cItemPool.pop();

    // Return the valid log item.
    return lpLogItem;
}

//////////////////////////////////////////////////////////////////////////////////////////
void LogItem::FreeLogItem( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Frees the given log item.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cAutoLock( &cPoolLock );
    
    // Simply push the freed item on top of the free stack.
    cItemPool.push( this );
}

//////////////////////////////////////////////////////////////////////////////////////////
void LogItem::Push( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Pushes a LogItem into the ItemQueue
// 
//////////////////////////////////////////////////////////////////////////////////////////
{    
    cItemQueue.push( this );
}
//////////////////////////////////////////////////////////////////////////////////////////
LogItem *LogItem::Pop( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Pops a LogItem from the queue.
// 
// Return: LogItem *, a valid LogItem or NULL if queue is empty.
//////////////////////////////////////////////////////////////////////////////////////////
{  
    // Fetch the top queue item.
    LogItem *lpLogItem = cItemQueue.pop();

    return lpLogItem;
}
