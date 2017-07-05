// DeadlockDetector.cpp: implementation of the CDeadlockDetector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "DeadlockDetector.h"
#include "TFCServerGP.h"
#include <process.h>
#include "format.h"
#include <list>
#include "ThreadMonitor.h"


//#define DEADLOCK_CHECK_OFF //DC To be place in comment for release, then after testing

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;

typedef list< CDeadlockDetector * >     WatchList;
static HANDLE                           hDeadlockThread;
static WatchList                        watchList;
static CLock                            watchLock;
static BOOL                             boCheck;
static DWORD                            dwWaitTime = 0;


#define DBG_LOG( watch, text ) if( watch->boLogLock ){\
                                    TFormat format;\
                                    DebugLogger::GetInstance().LogString(\
                                        format( \
                                            text"(thread %u) at %s (%u)",\
                                            watch->nThreadId,\
                                            __FILE__,\
                                            __LINE__\
                                        ), true\
                                    );\
                                }

extern CTFCServerApp theApp;


//////////////////////////////////////////////////////////////////////////////////////////
void CDeadlockDetector::SuspendDeadlockDetection
//////////////////////////////////////////////////////////////////////////////////////////
//  Stops the global deadlock checking mechanism for a given time.
// 
(
 DWORD dwDelay // The time to wait, INFINITE is the default.
)
//////////////////////////////////////////////////////////////////////////////////////////
{        
    dwWaitTime = dwDelay;  
}

//////////////////////////////////////////////////////////////////////////////////////////
void CDeadlockDetector::DeadlockCheckThread
//////////////////////////////////////////////////////////////////////////////////////////
// This is the thread which checks for deadlocks. This thread cannot deadlock.. ;)
// 
(
 LPVOID lpData // Nothing.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	CAutoThreadMonitor tmMonitor("Deadlock Detector");
    while( boCheck ){
        // Wait 2 seconds, this thread doesn't have to be fast.
        Sleep( 2000 );

#if defined( _DEBUG ) || defined( DEADLOCK_CHECK_OFF )
        Sleep( 50000000 );
#endif
        
               
        Sleep( dwWaitTime );
        dwWaitTime = 0;

        DWORD dwCurrentTime = GetRunTime();

        TFormat format;

        CAutoLock autoWatchListLock( &watchLock );
        
        WatchList::iterator z;
        for( z = watchList.begin(); z != watchList.end(); z++ ){
            DEADLOCK_WATCH &watch = (*z)->deadLock;
            
            CAutoLock autoWatchLock( &watch.cLock );            

            // If watch timed out.
            if( watch.dwTimeout <= dwCurrentTime ){
                LOCK_GP
                _LOG_DEBUG
                    LOG_CRIT_ERRORS,
                    "Found thread deadlock in %s",
                    watch.csThreadName
                LOG_

                string deadlockFile( theApp.sPaths.csLogPath );
                deadlockFile += "deadlock.txt";

                // Dump the lock data.
                if( CDebugLockManager::GetInstance()->DumpLockData( deadlockFile ) ){ 
                    _LOG_DEBUG
                        LOG_CRIT_ERRORS,
                        "A deadlock.dat file was created."
                    LOG_
                };

                
                // Flush the debug logger.
                DebugLogger::GetInstance().Flush();

                // Suspend the timeouted thread (in case..)
                SuspendThread( watch.hThreadHandle );

                EXCEPTION_POINTERS sException;
	            EXCEPTION_RECORD   sRecord;
	            
                // Fill-in the exception record structure to throw.
                ZeroMemory( &sRecord, sizeof( EXCEPTION_RECORD ) );
	            sRecord.ExceptionCode = _TFC_THREAD_DEADLOCK;
	            sRecord.ExceptionFlags = 0;
	            sRecord.ExceptionRecord = NULL;
	            sRecord.ExceptionAddress = NULL;
	            sRecord.NumberParameters = 0;	
	            sException.ExceptionRecord = &sRecord;

                // Get its context
				CONTEXT sContext;
				ZeroMemory( &sContext, sizeof( CONTEXT ) );

				sContext.ContextFlags = CONTEXT_FULL;
				GetThreadContext( watch.hThreadHandle, &sContext );
				
                sException.ContextRecord = &sContext;
                sException.ExceptionRecord->ExceptionAddress = (void *)sContext.Eip;			

                // Manually create a thread exception.
                TFCException *excp = new TFCException;
				excp->SetException( &sException );

                try{
                    _LOG_DEBUG
                        LOG_CRIT_ERRORS,
						"T4C Server was terminated due to thread deadlock in %s.",
                        //"T4C Server NOT was terminated due to thread deadlock in %s. Be WARNED !",
						//BLBLBL 6 avril 2009 ajustement du message d'erreur.
                        watch.csThreadName
                    LOG_
                }catch(...){
                    _LOG_DEBUG
                        LOG_CRIT_ERRORS,
                        "T4C Server was terminated due to thread deadlock. Crashed while querying information about thread name."
                    LOG_
                }

                END_LOG

                try{
                    // Report false exception.
                    ReportGP( excp, watch.csThreadName );
					//BLBLBL 6 avril 2009 on ne ferme plus le serveur en cas de deadlock
					//BLBLBL 13 avril 2009 : on oublie cette solution.
                }catch( ... ){
                }
               
                exit( DEADLOCK_CRASH );
				//BLBLBL 6 avril 2009 on ne ferme plus le serveur en cas de deadlock
				//BLBLBL 13 avril 2009 : ne pas fermer le serveur empeche les nouveaux joueurs de se co
				//et laisse certains jouer, mais au prochain reboot, un géant TW apparait.
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void CDeadlockDetector::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creates the deadlock detector
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    boCheck = TRUE;
    hDeadlockThread = (HANDLE)_beginthread( CDeadlockDetector::DeadlockCheckThread, 0, NULL );
}
//////////////////////////////////////////////////////////////////////////////////////////
void CDeadlockDetector::Destroy( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Destroys the deadlock detector
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    boCheck = FALSE;
    if( WaitForSingleObject( hDeadlockThread, 5000 ) == WAIT_TIMEOUT ){
        TerminateThread( hDeadlockThread, -1 );
    }    
}

// Construction //////////////////////////////////////////////////////////////////////////
CDeadlockDetector::CDeadlockDetector( void )
//////////////////////////////////////////////////////////////////////////////////////////
{
}

// Destructor ////////////////////////////////////////////////////////////////////////////
CDeadlockDetector::~CDeadlockDetector( void )
//////////////////////////////////////////////////////////////////////////////////////////
{
    _LOG_DEBUG
        LOG_DEBUG_LVL1,
        "Destroyed deadlock detector for thread %u.",
        GetCurrentThreadId()
    LOG_
}

//////////////////////////////////////////////////////////////////////////////////////////
void CDeadlockDetector::RegisterThread
//////////////////////////////////////////////////////////////////////////////////////////
// Registers a thread to be monitored by the deadlock detector.
// 
(
 HANDLE hThreadHandle,  // The thread's handle.
 CString csThreadName,  // The name of the thread (for easy identification).
 DWORD dwMaxTimeout,    // Timeout before thread is declared dead.
 int nThreadId          // Thread's ID.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Create an entry for the newly registered thread.
    deadLock.hThreadHandle = hThreadHandle;
    deadLock.nThreadId     = nThreadId;
    deadLock.csThreadName  = csThreadName;
    deadLock.dwTimeout     = GetRunTime() + dwMaxTimeout;
    deadLock.dwMaxTimeout  = dwMaxTimeout;
    deadLock.boLogLock     = false;

    CAutoLock autoWatchListLock( &watchLock );

    watchList.push_back( this );
}
//////////////////////////////////////////////////////////////////////////////////////////
void CDeadlockDetector::UnregisterThread( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Removes a thread from the monitoring list. Must be called before a thread ends..!
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    BOOL boFound = FALSE;
    
    CAutoLock autoWatchListLock( &watchLock );
    
    WatchList::iterator i;
    
    for( i = watchList.begin(); i != watchList.end(); i++ ){
        if( (*i) == this ){
            i = watchList.erase( i );
            boFound = TRUE;
        }
    }

    if( boFound ){
        _LOG_DEBUG
            LOG_DEBUG_LVL1,
            "Successfully unregistered thread %u.",
            GetCurrentThreadId()
        LOG_
    }else{
        _LOG_DEBUG
            LOG_DEBUG_LVL1,
            "Failed to unregistered thread %u.",
            GetCurrentThreadId()
        LOG_
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void CDeadlockDetector::EnterTimeout( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Tells the detector that the thread enters a state where it can timeout for an unknown
// amount of time. The detector will stop checking on this thread.
//
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock autoWatchLock( &deadLock.cLock );

    // Set timeout to an unreachable value.
    deadLock.dwTimeout = 0xFFFFFFFF;
}
//////////////////////////////////////////////////////////////////////////////////////////
void CDeadlockDetector::LeaveTimeout( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Tells the detector that the thread has finished waiting and that it should continue
// checking for deadlocks with this thread.
//
//////////////////////////////////////////////////////////////////////////////////////////
{
    KeepAlive();
}

//////////////////////////////////////////////////////////////////////////////////////////
void CDeadlockDetector::KeepAlive( void )
//////////////////////////////////////////////////////////////////////////////////////////
// This tells the detector that the thread is still alive. You *MUST* call this function 
// regularly to avoid having the detector detect a deadlock.
//
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock autoWatchLock( &deadLock.cLock );
    
    // Reset timeout value.
    deadLock.dwTimeout = GetRunTime() + deadLock.dwMaxTimeout;
}

//////////////////////////////////////////////////////////////////////////////////////////
void CDeadlockDetector::SetLockLog
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets the 'logging' value.
// 
(
 bool boValue // True for heavy logging of this deadlock item.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock autoWatchLock( &deadLock.cLock );

    deadLock.boLogLock = boValue;
}