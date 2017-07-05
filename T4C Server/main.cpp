// TFC Server.cpp : Defines the class behaviors for the application.
//
  
#include "stdafx.h"
#include <conio.h>
//#include <smrtheap.h>
#include "TFC Server.h"
#include "TFCInit.h"
#include "TFC_MAIN.h"
#include "C_Servic.h"
#include "RegKeyHandler.h"
#include "TFCServerGP.h"
#include "expfltr.h"
#include "T4CLog.h"
#include "IntlText.h"
#include "AsyncFuncQueue.h"
//#include "TFC Messages\svrmsg.h"
#include "PacketManager.h"
#include "PlayerManager.h"
#include "TFCMessagesHandler.h"
#include "DeadlockDetector.h"
#include "AutoConfig.h"
#include "Game_Rules.h"
//#include "../T4C Monitor/T4C MonitorMap.h"
#include "Scheduler.h"
#include "Format.h"
#include "DynObjManager.h"
#include "Clans.h"
#include "SpellEffectManager.h"
#include "NPC Thread.h"
#include "MainConsole.h"
#include "SysopCmd.h"
#include <signal.h>
#include <process.h>
#include "ODBCTrace.h"
#include "version.h"
#include "ThreadMonitor.h"
#include "System.h"
#include "ExitCode.h"
//#include "ScriptFile.h"
#include "random.h"

#include "TextFilter.h" //16/06/2009 special censoring filter for bad words

typedef struct _ASYNC_PACKET_FUNC_PARAMS{
	TFCPacket	*msg;
	Players		*user;
	RQ_SIZE		rqRequestID;
} ASYNC_PACKET_FUNC_PARAMS, *LPASYNC_PACKET_FUNC_PARAMS;

typedef struct _RQSTRUCT_PUT_PLAYER_IN_GAME{
	ASYNC_PACKET_FUNC_PARAMS sParams;
	CString csName;
} RQSTRUCT_PUT_PLAYER_IN_GAME, *LPRQSTRUCT_PUT_PLAYER_IN_GAME;

typedef struct _GPEpTn{
	LPEXCEPTION_POINTERS lpEP;
	std::string threadName;
} GPEpTn, *LPGPEpTn;



#pragma data_seg ("SHARED_INSTANCE")
	BOOL boServerRunning = FALSE;
#pragma data_seg ()

#ifdef _DEBUG
	#define DEADLOCK	5000000
#else
	#define DEADLOCK	5000
#endif

//To choose between MYSQL and MSSQL for ODBC : (in order to optimize requests)
//#define MSSQLSERVER 0//BLBLBL 10/01/2011 (set to 1 if server is MSSQL, use TOP instead of LIMIT in SQL statments)
// ^^ défini dans les options de compilation ^^

#define VERSION_STRING  "v%u"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef __ENABLE_LOG
	DEBUG_LOG __LOG(200, 100); // Basic debug level of 100 entries and 25 entries
#endif

void ReportLastError(){
	TCHAR *lpMsgBuf;
	FormatMessage(     FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,    GetLastError(),
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
					(LPTSTR) &lpMsgBuf,    0,    NULL );// Display the string.
	MessageBox( NULL, lpMsgBuf, _T("GetLastError"), MB_OK|MB_ICONINFORMATION );
	// Free the buffer.
	LocalFree( lpMsgBuf );
}

void __cdecl EntryFunction(void *);
void __cdecl StopFunction(void *);

void TerminateServer( bool boExit );

void TFCInitMaps(void);

extern TFC_MAIN *TFCServer;
ODBCTrace *ODBCHarness;
extern Clans    *CreatureClans;
static CString   ServerPath;

void MainPumpExceptionFunction(unsigned int u, EXCEPTION_POINTERS* pExp ){
	TFCException *excp = new TFCException;
	excp->SetException(pExp);	
	throw excp;
}

LPTOP_LEVEL_EXCEPTION_FILTER lpDefaultExceptionFunc = NULL;

//unsigned MemDefaultPoolFlags = MEM_POOL_SERIALIZE;

//////////////////////////////////////////////////////////////////////////////////////////
void FindIPAddress
//////////////////////////////////////////////////////////////////////////////////////////
// Go get the machine's IP Address
// An Array of DWORD is given as parameter
// 
(
 DWORD *ipaddr,  // An array of DWORDs
 short nArrayLen // The length of the array.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	DWORD dwIPAddr=0;

	CHAR hostName[256];
	HOSTENT *pHostEnt;

	if (gethostname(hostName,sizeof(hostName)) == SOCKET_ERROR 
				|| (pHostEnt=gethostbyname(hostName)) == NULL) 
	{
		ipaddr[0] = 0;
		return;
	}
	short i = 0;
	for (i=0 ; pHostEnt->h_addr_list[i] != '\0'; i++)
	{
		struct in_addr *ptr = (struct in_addr *)pHostEnt->h_addr_list[i];
		SOCKADDR_IN sa;
		sa.sin_addr = *ptr;
		if (i < nArrayLen)	ipaddr[i] = sa.sin_addr.s_addr;
	}
	if (!i) 
	{
		ipaddr[0] = 0;
		return;
	}

	struct in_addr *ptr = (struct in_addr *)pHostEnt->h_addr;
	SOCKADDR_IN sa;
	sa.sin_addr = *ptr;
	// overwrite position 0 address.. in case its different.. 
	ipaddr[0] = sa.sin_addr.s_addr;// leave it in network order..
	return;
}


//////////////////////////////////////////////////////////////////////////////////////////
inline void AddTrailingBackslash
//////////////////////////////////////////////////////////////////////////////////////////
// This functions makes sure a trailing backlash exists at the end of a string.
// 
(
 CString &csText // The text.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	// Remove trailing white spaces
	csText.TrimLeft();
	// If string doesn't have a trailing backslash, add it.
	if( csText.GetAt( csText.GetLength() - 1 ) != '\\' ){
		csText += '\\';
	}
}
/////////////////////////////////////////////////////////////////////////////
// CTFCServerApp

/*BEGIN_MESSAGE_MAP(CTFCServerApp, CWinApp)
	//{{AFX_MSG_MAP(CTFCServerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()*/

#ifdef MEM_DEBUG
//    #include <smrtheap.hpp>
#endif

/////////////////////////////////////////////////////////////////////////////
// CTFCServerApp construction

CTFCServerApp::CTFCServerApp() : szServerAcctID( "T4CSVRID" )
{
	current_check = 1;
	last_PlayerMainDeadlockFlag = 0xFFFFFFFF;
	last_TFCMainDeadlockFlag = 0xFFFFFFFF;
	last_PlayerMainTime = 0;
	last_TFCMainTime = 0;
    hCrtReportFile = INVALID_HANDLE_VALUE;

    serverStarted = false;
}

CTFCServerApp::~CTFCServerApp(){
    if( hCrtReportFile != INVALID_HANDLE_VALUE ){
        CloseHandle( hCrtReportFile );
    }
}

#define _EXITLOG { CString fileName( theApp.sPaths.csLogPath ); fileName += "exit.txt";\
FILE *__f = fopen( fileName, "ab" ); if(__f){fprintf( __f, 
#define EXITLOG_ );fclose(__f);}};
#define EXITLOG_ );fclose(__f);}};

/////////////////////////////////////////////////////////////////////////////
// The one and only CTFCServerApp object

CTFCServerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTFCServerApp initialization

#define KEY2TXT( __str, __key, __default )  __str = regKey.GetProfileString( __key, __default );\
                                            __str.TrimRight();\
                                            __str.TrimLeft();

#include "BoostFormula.h"

//////////////////////////////////////////////////////////////////////////////////////////
typedef struct _CONTEXT_FETCH{
    HANDLE      hThread;    // Thread
    LPCONTEXT   lpContext;  // Context holder
    BOOL        boDone;
} CONTEXT_FETCH, *LPCONTEXT_FETCH;

//////////////////////////////////////////////////////////////////////////////////////////
UINT ContextFetch
//////////////////////////////////////////////////////////////////////////////////////////
// Async function which will fetch a suspended thread's context and then start it back.
// 
(
 LPVOID lpData // The LPCONTEXT_FETCH structure.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    LPCONTEXT_FETCH lpFetch = (LPCONTEXT_FETCH)lpData;

    TRACE( "\r\nHandle=%u", lpFetch->hThread );
    TRACE( "\r\nHandle=%u", GetCurrentThread() );
    // Sleep until asyn function fetched this thread's context.
    SuspendThread( lpFetch->hThread );
    
    // Fetch the thread's context.
    lpFetch->lpContext->ContextFlags = CONTEXT_FULL;        
	GetThreadContext( lpFetch->hThread, lpFetch->lpContext );

    lpFetch->boDone = TRUE;

    // Resume suspend count set by this function
    ResumeThread( lpFetch->hThread );    

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
unsigned int __stdcall ExceptionThread
//////////////////////////////////////////////////////////////////////////////////////////
//  This thread is created each time the default exception handler is called. This
// allows the error reporting mechanism to work in its own thread.
// 
(
 void *exceptpandname // EpTn struct (exceptionPointers + thread name).
)
// Return: unsigned int, 0
//////////////////////////////////////////////////////////////////////////////////////////
{
	CAutoThreadMonitor tmMonitor("Exception Thread");

	LPGPEpTn crashInfo = static_cast<LPGPEpTn>(exceptpandname);

//    LPEXCEPTION_POINTERS lp = static_cast< LPEXCEPTION_POINTERS >( exceptionPointers );
	LPEXCEPTION_POINTERS lp = crashInfo->lpEP;
    
    _EXITLOG "\r\nException thread started." EXITLOG_

    // Don't let any exception stop us from generating a GP.
    try{
        _LOG_DEBUG
            LOG_CRIT_ERRORS,
            "Exception in thread %s",
            crashInfo->threadName
        LOG_
    
        // Suspend deadlock detection for 3 minutes.
        SUSPEND_DEADLOCK_DETECTION( 60000 * 3 );

        // Flush the debug logger.
        DebugLogger::GetInstance().Flush();

//        DebugLockManager::Instance().LogLockQueue();
    
        END_LOG
    }catch(...){
    }

//    CString csId;
//    csId.Format( "Thread ( Id=%u )", GetCurrentThreadId() );

    TFCException *e = new TFCException;
    e->SetException( lp );

    _EXITLOG "\r\nWriting GP." EXITLOG_
    // Write the GP.
//    ReportGP( e, (LPCTSTR)csId );
    ReportGP( e, crashInfo->threadName.c_str() );

    _EXITLOG "\r\nClosing exception thread.." EXITLOG_

    return EXCEPTION_CONTINUE_SEARCH;
}


//////////////////////////////////////////////////////////////////////////////////////////
LONG __stdcall DefaultExcpFilter
//////////////////////////////////////////////////////////////////////////////////////////
// Function called when an Exception is raised outside any known thread.
// 
(
 LPEXCEPTION_POINTERS lp // The exception pointers.
)
// Return: LONG, EXCEPTION_EXECUTE_HANDLER
//////////////////////////////////////////////////////////////////////////////////////////
{        
    unsigned int threadId = 0;
    HANDLE       threadHandle;
    static int   exceptionCount = 0;

    SYSTEMTIME sysTime; 
    GetLocalTime(&sysTime);

	std::string threadName;
	if ( CThreadMonitor::GetInstance().GetThreadName(GetCurrentThreadId(), threadName) == FALSE ) {
		threadName = "ID ";
		threadName += GetCurrentThreadId();
		threadName += " [ Unnamed thread :( ]";
	}

    _EXITLOG "\r\n+++[EXCEPTION at 0x%x in thread %s] %u/%u/%u %02u:%02u:%02u +++",
        lp->ContextRecord->Eip,
        threadName.c_str(),
        sysTime.wMonth,
        sysTime.wDay,
        sysTime.wYear, 
        sysTime.wHour, 
        sysTime.wMinute,
        sysTime.wSecond
    EXITLOG_

    // If more than 20 exceptions were made
    exceptionCount++;
    if( exceptionCount > 20 ){
        _EXITLOG "\r\nException count too high, killing process." EXITLOG_        
        // Kill the process.
        TerminateProcess( GetCurrentProcess(), 134 );
    }

    if( !TRYLOCK_GP ){
        Sleep( 2000 );
        _EXITLOG "\r\nException already being analyzed." EXITLOG_
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    GPEpTn crashInfo;
    crashInfo.lpEP = lp;
    crashInfo.threadName = threadName;

    threadHandle = reinterpret_cast< HANDLE >(
                        _beginthreadex( NULL, 0, ExceptionThread, &crashInfo, 0, &threadId )
                   );
        
    DWORD exitCode = EXCEPTION_CONTINUE_SEARCH;
              
    if( threadHandle != reinterpret_cast< void * >( -1 ) ){
        _EXITLOG "\r\nWaiting for exception thread to finish." EXITLOG_
        // Wait 5 minutes for the GP thread to end.
        if( WaitForSingleObject( threadHandle, 300000 ) == WAIT_TIMEOUT ){
            _EXITLOG "\r\nTimeout waiting for thread to finish." EXITLOG_
        }

        // Use the exit code given by the thread.
        GetExitCodeThread( threadHandle, &exitCode );
    }else{
        _EXITLOG "\r\nCould not create exception thread." EXITLOG_;
    }

    _EXITLOG "\r\nException handler returning." EXITLOG_
    return exitCode;
}




void unexpectedfunc( void ){
    _EXITLOG "\r\nGame terminated abruptly (unexcepted exception was thrown)." EXITLOG_
}


/** @short The cleanup function called at server exit.
 */
void exitfunc( void )
{
#ifdef WIN32
    SYSTEMTIME sysTime; 
    GetLocalTime(&sysTime);

    _EXITLOG "\r\n+++[EXIT] %u/%u/%u %02u:%02u:%02u +++",
        sysTime.wMonth,
        sysTime.wDay,
        sysTime.wYear, 
        sysTime.wHour, 
        sysTime.wMinute,
        sysTime.wSecond
    EXITLOG_
	// Cleanly shutdown the Winsock2 library.
	WSACleanup();
#endif
}


/** @short This short helping function simply displays how to invoke the program.
 */
void display_usage(void)
{
	MessageBox(NULL, 
                 _T("You must start T4C as a service or specifically add\r\n"
                    "the -m command parameter if you wish to quickly test\r\n"
                    "the server's settings in a standard application window."), _T("Error"),MB_OK);
	exit(INVALID_PROGRAM_ARGUMENT);
}


/** @short The POSIX signals handler.
 * It catches the ABORT and TERM signals.
 * @param s The signal that were caught.
 * @remark It must remain lightweight: no IO, no system-calls.
 */
void sigfunc(int s){
/* Desboys: replacing the exception rising. To be removed.
    throw "abnormal program termination.";
*/
	_exit(SERVER_RECEIVED_SIGNAL);
}


/** @short The server main entry-point.
 */
// Desboys: doing a huge rework of the program, contact me if you wish
// to add something here.
int main(int argc,char **argv)
{	
	bool startAsService = false;
	// Setup the signal handler(s).
	 signal( SIGABRT, sigfunc );

#if defined(WIN32) && !defined(_DEBUG)
	 // In release mode, NEVER let the default exception handler display any information..!
    SetErrorMode( 
        SEM_FAILCRITICALERRORS |
        SEM_NOGPFAULTERRORBOX  |
        SEM_NOOPENFILEERRORBOX
    );
#endif    

// Desboys: Removed block [1], look at the end of the file to retrieve it.

#if defined(WIN32) && !defined(DISABLE_GP)
	// Sets the default top-most exception function.
    lpDefaultExceptionFunc = SetUnhandledExceptionFilter( DefaultExcpFilter );
#endif
    
// Desboys: Removed block [2], look at the end of the file to retrieve it.

#ifdef WIN32
	// Check wether another instance of the server is running.
	if( boServerRunning ){
		return ANOTHER_SERVER_ALREADY_RUNNING;
	}
	boServerRunning = TRUE;
#endif

// Desboys: Removed block [3], look at the end of the file to retrieve it.

	theApp.InService = FALSE;
	// Check the program parameters.
	if (argc == 2)
		if(0 == _stricmp(argv[1],"--spawn-service"))
		{
			startAsService = true;
			theApp.InService = true;
		}
		else if (0 == _stricmp(argv[1],"-m"))
		{
			theApp.InService = false;
		}
		else
			display_usage();
		
	else
	{
			theApp.InService = false;
		
	}

#ifdef WIN32
	// Setup the Winsock2 library.
    WSADATA wsaData;
/* Desboys: We need a clearer test on return value! */
    if( WSAStartup( MAKEWORD( 2, 0 ), &wsaData ) != 0 )
	{
        MessageBox( NULL, "T4C Server requires a WinSock 2.0 protocol to be installed.", "Error", MB_OK );
        return WINSOCK2_NOT_FOUND;
    }
#endif

	// Install the cleanup function.
	atexit( exitfunc );

// Desboys: Removed block [4], look at the end of the file to retrieve it.
    
	try{        
// Desboys: Removed block [5], look at the end of the file to retrieve it.

	#ifdef __ENABLE_LOG
		if(__LOG > 0) __LOG("Entering InitInstance");
	#endif

		// Getting the machine name.
		theApp.csMachineName = System::GetMachineName().c_str();
        

		//CUService	service;
		int			startAsService = FALSE;
		int 		loop  = 0;
		TCHAR 		param = 0;
		TCHAR		path[_MAX_PATH * 2];	
		char        stop_char = ' ';

#ifdef WIN32
		// Removing an unused key for the registry ... why setting it ?
        {
            RegKeyHandler regKey;
            regKey.Open( HKEY_LOCAL_MACHINE, "SOFTWARE\\Vircom\\The 4th Coming Server" );
            regKey.DeleteValue( "SHUTDOWN" );
            regKey.Close();            
        }
#endif
		
		loop = GetModuleFileName( GetModuleHandle( NULL ), path, _MAX_PATH * 2 );		
		// Find next backslash
		do{
			loop--;
		}while( path[ loop ] != '\\' && loop >= 0 );
		// End string after backslash.
		path[ loop + 1 ] = 0;


        
		//////////////////////////////////////////////////////////////////////////////////////////
		// Load the registry!
		RegKeyHandler regKey;
		// Paths.
		if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY PATHS_KEY ) ){
			theApp.sPaths.csLogPath =		regKey.GetProfileString( "LOG_PATH", path );
			theApp.sPaths.csBinaryPath =	regKey.GetProfileString( "BINARY_PATH", path );

			AddTrailingBackslash( theApp.sPaths.csLogPath );
			AddTrailingBackslash( theApp.sPaths.csBinaryPath );

            // Make certain that the log path exists.
            CreateDirectory( theApp.sPaths.csLogPath, NULL );

			regKey.Close();
		}else{
			theApp.sPaths.csLogPath = path;
			theApp.sPaths.csBinaryPath = path;

			AddTrailingBackslash( theApp.sPaths.csLogPath );
			AddTrailingBackslash( theApp.sPaths.csBinaryPath );
		}
        ServerPath = theApp.sPaths.csBinaryPath;

        {
            RegKeyHandler regKey;
            regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY CONTACT_KEY );

            theApp.sContact.csCompanyName = regKey.GetProfileString( "CompanyName", "<unspecified>" );
            theApp.sContact.csAdminEmail  = regKey.GetProfileString( "AdminEmail",  "unknown@unspecified.net" );
        }
        {
            RegKeyHandler regKey;
            if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY ORACLE_HEART_BEAT ) ){
				theApp.sOracleHB.csDelay = static_cast< DWORD >( regKey.GetProfileInt( "Delay_Minutes", 2 ) );
				theApp.sOracleHB.csState = static_cast< DWORD >( regKey.GetProfileInt( "State",  0 ) );
			}else{
				theApp.sOracleHB.csDelay = 0;
				theApp.sOracleHB.csState = 0;
			}
		}

        {
            RegKeyHandler regKey;
            if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY GEN_CFG_KEY ) )
			{
				theApp.sColosseum = static_cast< DWORD >( regKey.GetProfileInt( "ACK_COLOSSEUM", 0 ) );
			}
			else
			{
				theApp.sColosseum = 0;
			}

			if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY GEN_CFG_KEY ) )
			{
				theApp.sDoppelganger = static_cast< DWORD >( regKey.GetProfileInt( "ACK_DOPPELGANGER", 0 ) );
			}
			else
			{
				theApp.sDoppelganger = 0;
			}

			if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY GEN_CFG_KEY ) )
			{
				theApp.sMaxRemorts = static_cast< DWORD >( regKey.GetProfileInt( "ACK_MAXREMORTS", 3 ) );
			}
			else
			{
				theApp.sMaxRemorts = 3;
			}

			if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY GEN_CFG_KEY ) )
			{
				theApp.sMaxCharactersPerAccount = static_cast< DWORD >( regKey.GetProfileInt( "MAX_CHARACTERS_PER_ACCOUNT", 3 ) );
				theApp.dwDebugSkillParryDisabled = regKey.GetProfileInt( "DEBUG_SKILLPARRY_DISABLED", 0 );
				theApp.dwLogXPGains = regKey.GetProfileInt( "ENABLE_XP_GAIN_LOGGING", 0 );
				theApp.dwHideUncoverEffectDisabled = regKey.GetProfileInt( "DisableHideUncoverEffect", 0 );
				theApp.dwRobWhileWalkingEnabled = regKey.GetProfileInt( "EnableRobWhileWalking", 0 );
				theApp.dwRobWhileBeingAttackedEnabled = regKey.GetProfileInt( "EnableRobWhileBeingAttacked", 0 );
				theApp.dwDisableIndirectDelete = regKey.GetProfileInt( "DisableIndirectDelete", 0 );
				theApp.dwDisableItemInfo = regKey.GetProfileInt( "DisableItemInfo", 0 );
				theApp.dwScriptLoopLength = regKey.GetProfileInt( "SCRIPT_LOOP", 0 );
			}
			else
			{
				theApp.sMaxCharactersPerAccount = 3;
				theApp.dwDebugSkillParryDisabled = 0;
				theApp.dwLogXPGains = 0;
				theApp.dwHideUncoverEffectDisabled = 0;
				theApp.dwRobWhileWalkingEnabled = 0;
				theApp.dwRobWhileBeingAttackedEnabled = 0;
				theApp.dwDisableIndirectDelete = 0;
				theApp.dwDisableItemInfo = 0;
				theApp.dwScriptLoopLength = 0;
			}
			if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY GEN_CFG_KEY ) )
			{
				theApp.sBattleMode = static_cast< DWORD >( regKey.GetProfileInt( "BATTLE_MODE", 0 ) );
			}
			else
			{
				theApp.sBattleMode = 0;
			}



		}
		//BATTLE MODE KEY BEGIN//
		{ 
            RegKeyHandler regKey;
            if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY CFG_BATTLE_MODE ) )
			{
				theApp.sxptm1killtm2 = static_cast< DWORD >( regKey.GetProfileInt( "XP_TM1KILLTM2", 0 ) );
				theApp.sgoldtm1killtm2 = static_cast< DWORD >( regKey.GetProfileInt( "GOLD_TM1KILLTM2", 0 ) );
				theApp.skarmatm1killtm2 = static_cast< DWORD >( regKey.GetProfileInt( "KARMA_TM1KILLTM2", 0 ) );
				theApp.sxptm2killtm1 = static_cast< DWORD >( regKey.GetProfileInt( "XP_TM2KILLTM1", 0 ) );
				theApp.sgoldtm2killtm1 = static_cast< DWORD >( regKey.GetProfileInt( "GOLD_TM2KILLTM1", 0 ) );
				theApp.skarmatm2killtm1 = static_cast< DWORD >( regKey.GetProfileInt( "KARMA_TM2KILLTM1", 0 ) );
				theApp.sxplostsameteam = static_cast< DWORD >( regKey.GetProfileInt( "XP_LOST_SAMETEAM", 0 ) );
				theApp.sxplostsameteam = static_cast< DWORD >( regKey.GetProfileInt( "XP_LOST_SAMETEAM", 0 ) );
				theApp.sgoldlostsameteam = static_cast< DWORD >( regKey.GetProfileInt( "GOLD_LOST_SAMETEAM", 0 ) );
				theApp.skarmagaintk = static_cast< DWORD >( regKey.GetProfileInt( "KARMA_GAIN_SAMETEAM", 0 ) );
				theApp.skarmalosttk = static_cast< DWORD >( regKey.GetProfileInt( "KARMA_LOST_SAMETEAM", 0 ) );
				theApp.sbonuskill1 = static_cast< DWORD >( regKey.GetProfileInt( "BONUS_KILL_1", 0 ) );
				theApp.sbonuskill2 = static_cast< DWORD >( regKey.GetProfileInt( "BONUS_KILL_2", 0 ) );
				theApp.sbonuskill3 = static_cast< DWORD >( regKey.GetProfileInt( "BONUS_KILL_3", 0 ) );
				theApp.sxpbonus1 = static_cast< DWORD >( regKey.GetProfileInt( "XP_BONUS1", 0 ) );
				theApp.sxpbonus2 = static_cast< DWORD >( regKey.GetProfileInt( "XP_BONUS2", 0 ) );
				theApp.sxpbonus3 = static_cast< DWORD >( regKey.GetProfileInt( "XP_BONUS3", 0 ) );
				theApp.sgoldbonus1 = static_cast< DWORD >( regKey.GetProfileInt( "GOLD_BONUS1", 0 ) );
				theApp.sgoldbonus2 = static_cast< DWORD >( regKey.GetProfileInt( "GOLD_BONUS2", 0 ) );
				theApp.sgoldbonus3 = static_cast< DWORD >( regKey.GetProfileInt( "GOLD_BONUS3", 0 ) );
			}
			else
			{
				theApp.sxptm1killtm2 = 0;
				theApp.sgoldtm1killtm2 = 0;
				theApp.skarmatm1killtm2 = 0;
				theApp.sxptm2killtm1 = 0;
				theApp.sgoldtm2killtm1 = 0;
				theApp.skarmatm2killtm1 = 0;
				theApp.sxplostsameteam = 0;
				theApp.sxplostsameteam = 0;
				theApp.sgoldlostsameteam = 0;
				theApp.skarmagaintk = 0;
				theApp.skarmalosttk = 0;
				theApp.sbonuskill1 = 0;
				theApp.sbonuskill2 = 0;
				theApp.sbonuskill3 = 0;
				theApp.sxpbonus1 = 0;
				theApp.sxpbonus2 = 0;
				theApp.sxpbonus3 = 0;
				theApp.sgoldbonus1 = 0;
				theApp.sgoldbonus2 = 0;
				theApp.sgoldbonus3 = 0;
			}
		}

		{
         CString strFile;
         strFile.Format("%s\\KeyWorld.dat",ServerPath);
         
         FILE *pf = fopen(strFile.GetBuffer(0),"rt");
         if(pf)
         {
            char *pRet;
            char strLigne[2048];
            do 
            {
               pRet = fgets(strLigne,2048,pf);
               if(pRet)
               {
                  sMagicWorldSpell newWord;
                  char strTmp[2048];
                  int dwNbr = sscanf(strLigne,"%010d,%010d,%s",&newWord.uiFlagID,&newWord.uiSpellID,&strTmp);
                  if(dwNbr == 3)
                  {
                     newWord.strText.Format("%s",strTmp);
                     theApp.m_aSpellWorld.push_back(newWord);
                  }
               }
            }while(pRet);
            fclose(pf);
         }

         //sMagicWorldSpell nWorld;
         //nWorld.strText.Format("batard");
         //nWorld.uiSpellID = 10115;
         //nWorld.uiFlagID = 0;

         //theApp.m_aSpellWorld.Add(nWorld);
      }
	    //BATTLE MODE KEY END//
		regKey.Open(HKEY_LOCAL_MACHINE, T4C_KEY "Authentication\\");
		theApp.csDBDns = regKey.GetProfileString("ODBC_DSN", "");
		regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY CHARACTER_KEY );
		theApp.csDBUser      = regKey.GetProfileString( "DB_USER", "" );
		theApp.csDBPwd       = regKey.GetProfileString( "DB_PWD",  "" );
		theApp.dwDeadSpellID = regKey.GetProfileInt   ( "DeadSpellID",  0x00 ); //DEATH_EFFECT_ID
		if ( theApp.dwCustomStartupPositionOnOff = regKey.GetProfileInt( "StartupPosOnOff", FALSE ) ) {
			theApp.dwCustomStartupPositionX = regKey.GetProfileInt( "StartupPosX", NULL );
			theApp.dwCustomStartupPositionY = regKey.GetProfileInt( "StartupPosY", NULL );
			theApp.dwCustomStartupPositionW = regKey.GetProfileInt( "StartupPosW", NULL );
		} 
		if ( theApp.dwCustomStartupSanctuaryOnOff = regKey.GetProfileInt( "StartupSanctuaryOnOff", FALSE ) ) {
			theApp.dwCustomStartupSanctuaryX = regKey.GetProfileInt( "StartupSanctuaryX", NULL );
			theApp.dwCustomStartupSanctuaryY = regKey.GetProfileInt( "StartupSanctuaryY", NULL );
			theApp.dwCustomStartupSanctuaryW = regKey.GetProfileInt( "StartupSanctuaryW", NULL );
		}
		theApp.dwChestEncumbranceUpdatedLive = regKey.GetProfileInt( "ChestEncumbranceUpdatedLive", 0);
		theApp.csChestEncumbranceBoostFormula = regKey.GetProfileString( "ChestEncumbranceBoostFormula", 0 );

		 //NMNMNM Still Item ID
		  TFormat format;
		  int i = 1;
		  DWORD dwID = static_cast< DWORD >( regKey.GetProfileInt( "StillItem1", 0 ) );
		  while(dwID != 0 )
		  {
			 theApp.m_aStillItems.push_back(dwID);
			 i++;
			 dwID = static_cast< DWORD >( regKey.GetProfileInt( format( "StillItem%u", i ), 0 ) );
		  }

		regKey.Close();

		// ArenaLocations
		if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY "PVPDeath" ) )
		{
			theApp.arenaLocationList.clear();	
			
			TFormat format;

			int i = 1;
			std::string locationId = regKey.GetProfileString( "ArenaLocation1", "$NULL$" );
			while( locationId != "$NULL$" )
			{
				sArenaLocation loc;
				
				loc.wlTopLeft.X = regKey.GetProfileInt( format( "ArenaLocation%uX1", i ), 0 );
				loc.wlTopLeft.Y = regKey.GetProfileInt( format( "ArenaLocation%uY1", i ), 0 );
				
				loc.wlBottomRight.X = regKey.GetProfileInt( format( "ArenaLocation%uX2", i ), 0 );
				loc.wlBottomRight.Y = regKey.GetProfileInt( format( "ArenaLocation%uY2", i ), 0 );

				loc.wlBottomRight.world = loc.wlTopLeft.world = regKey.GetProfileInt( format( "ArenaLocation%uWorld", i ), 0 );

				loc.wlRecallAttacker.X = regKey.GetProfileInt( format( "ArenaLocation%uRecallKillX", i ), -1 );
				loc.wlRecallAttacker.Y = regKey.GetProfileInt( format( "ArenaLocation%uRecallKillY", i ), -1 );
				loc.wlRecallAttacker.world = regKey.GetProfileInt( format( "ArenaLocation%uRecallKillW", i ), 0 );

				loc.wlRecallTarget.X = regKey.GetProfileInt( format( "ArenaLocation%uRecallDieX", i ), 0 );
				loc.wlRecallTarget.Y = regKey.GetProfileInt( format( "ArenaLocation%uRecallDieY", i ), 0 );
				loc.wlRecallTarget.world = regKey.GetProfileInt( format( "ArenaLocation%uRecallDieW", i ), 0 );

				theApp.arenaLocationList.push_back( loc );

				++i;
				locationId = regKey.GetProfileString( format( "ArenaLocation%u", i ), "$NULL$" );
			}

			regKey.Close();
		}


		START_LOG;
	// Those lines got moved from below so that it starts the ODBCTrace
	// Before the first call to the logging functions.
	// This way we can make logging functions log to SQL as long as TXT files.
        try{
            ODBCHarness = new ODBCTrace;
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "Creating ODBCTrace object."
            LOG_
        }catch(...){
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "Crashed when creating ODBCTrace object."
            LOG_
            throw;
        }        
	// End of moved lines
		_LOG_DEBUG  LOG_ALWAYS, "-----" LOG_
		_LOG_DEBUG  LOG_ALWAYS, "Starting T4C server." LOG_
		_LOG_DEBUG  LOG_ALWAYS, Version::sBuildStamp.c_str() LOG_
		if ( theApp.sOracleHB.csState ){
			_LOG_DEBUG  LOG_DEBUG_LVL4, "Oracle Heart Beat Delay: %u",theApp.sOracleHB.csDelay LOG_
			_LOG_DEBUG  LOG_DEBUG_LVL4, "Oracle Heart Beat State: %u",theApp.sOracleHB.csState LOG_
		}
        _LOG_DEATH  LOG_ALWAYS, "-----" LOG_
        _LOG_DEATH  LOG_ALWAYS, "Starting T4C server." LOG_
        _LOG_GAMEOP LOG_ALWAYS, "-----" LOG_
        _LOG_GAMEOP LOG_ALWAYS, "Starting T4C server." LOG_
        _LOG_PC     LOG_ALWAYS, "-----" LOG_
        _LOG_PC     LOG_ALWAYS, "Starting T4C server." LOG_
        _LOG_ITEMS  LOG_ALWAYS, "-----" LOG_
        _LOG_ITEMS  LOG_ALWAYS, "Starting T4C server." LOG_
        _LOG_NPCS   LOG_ALWAYS, "-----" LOG_
        _LOG_NPCS   LOG_ALWAYS, "Starting T4C server." LOG_
        _LOG_WORLD  LOG_ALWAYS, "-----" LOG_
        _LOG_WORLD  LOG_ALWAYS, "Starting T4C server." LOG_
     

        CString csSource;
        

        // Network ///////////////////////////////////////////////////////////////////////////////        
		if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY NETWORK_KEY ) ){
            theApp.sNetwork.csRecvIP  = regKey.GetProfileString( "RECV_IP", "" );
            theApp.sNetwork.csSendIP  = regKey.GetProfileString( "SEND_IP", static_cast< LPCTSTR >( theApp.sNetwork.csRecvIP ) );
            theApp.sNetwork.csRecvIP.TrimRight();
            theApp.sNetwork.csRecvIP.TrimLeft();
            theApp.sNetwork.csSendIP.TrimRight();
            theApp.sNetwork.csSendIP.TrimLeft();
            
            theApp.sNetwork.wRecvPort = static_cast< WORD >( regKey.GetProfileInt( "RECV_PORT", 11677 ) );
            theApp.sNetwork.wSendPort = static_cast< WORD >( regKey.GetProfileInt( "SEND_PORT", 11677 ) );

			regKey.Close();
		}else{
			theApp.sNetwork.wRecvPort = 11677;
            theApp.sNetwork.wSendPort = 11678;

			_LOG_DEBUG
				LOG_CRIT_ERRORS,
				"\n     Could not open registry key " T4C_KEY NETWORK_KEY " required by T4C Server."
				"\n     Run T4C Server Setup from the control panel to setup the registry keys."
				"\n     Using default values."
			LOG_
		}
        // General Configuration /////////////////////////////////////////////////////////////////
		if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY GEN_CFG_KEY ) ){
			theApp.sGeneral.wNbWarnings = (WORD)regKey.GetProfileInt( "NB_WARNINGS", 5 );
			theApp.sGeneral.dwTimeBeforeWarning = regKey.GetProfileInt( "TIME_BEFORE_WARNING", 2500 );

/*
            HANDLE hProcess = GetCurrentProcess();
            DWORD processMask, systemMask;
            GetProcessAffinityMask( hProcess, &processMask, &systemMask );

            SetProcessAffinityMask( 
                hProcess, 
                regKey.GetProfileInt( "ProcessAffinity", 0xFFFFFFFF ) & processMask
            );
*/
            TFormat format;

            int nCount = 1;
            CString csLangDB = regKey.GetProfileString( "LangDB1", "$NULL$" );
            while( csLangDB != "$NULL$" ){            
                IntlText::LoadLngDB( (LPCTSTR)csLangDB );
                theApp.sGeneral.csLang = csLangDB;
                csLangDB = regKey.GetProfileString( format( "LangDB%u", ++nCount ), "$NULL$" );
            }


			// fill in the theApp.sGeneral.csLang field //DC
			// use: if ( theApp.sGeneral.csLang.Compare("t4c_kor.elng") == 0 ) for korean specific actions			

            // If the language configuration isn't valid.
            if( !IntlText::IsLngOK() ){
                _LOG_DEBUG
                    LOG_CRIT_ERRORS,
                    "Could not find any valid language database. Server cannot be started."
                LOG_
                END_LOG
                MessageBeep( -1 );
                return false;
            }

            // If the T4C_CRASH key was specified.
            /*if( regKey.GetProfileInt( "T4C_CRASH", 0 ) != 0 ){
                // Delete the key.
                regKey.DeleteValue( "T4C_CRASH" );

                // If the privacy key is set, do not send email.
                if( regKey.GetProfileInt( "PRIVACY", 0 ) == 0 ){
                    // Get the system time
                    SYSTEMTIME sysTime; 
	                GetLocalTime(&sysTime);

                    try{

                        CString csGPfile = theApp.sPaths.csLogPath;
                        csGPfile += "T4CServerGP.out";

                        CString domain;
                        CString mainText;

                        {
                            char hostName[ 256 ];                        
                                                        
                            gethostname( hostName, 256 );
                        
                            domain = hostName;
                            
                            in_addr mainIP;
                            DWORD dwVersion = SERVER_CONNECTION_HI_VERSION;
                            {
                                RegKeyHandler regKey;
                                regKey.Open( HKEY_LOCAL_MACHINE, "Software\\Vircom\\The 4th Coming Server\\GeneralConfig" );

                                // Fetch version from registry, otherwise default to the executable's version.
                                dwVersion = regKey.GetProfileInt( "Version", SERVER_CONNECTION_HI_VERSION );
                                regKey.Close();
                            }
                            
                            FindIPAddress( &mainIP.S_un.S_addr, 1 );
                            RegKeyHandler key;
                            key.Open( HKEY_LOCAL_MACHINE, "System\\CurrentControlSet\\Services\\Tcpip\\Parameters" );

                            domain += ".";
                            domain += key.GetProfileString( "domain", "" );

                            mainText =  "GP fault.";
                            mainText += "\r\n";
                            mainText += format( "\r\nServer version: v%u.",
                                            dwVersion
                                        );
                            mainText += format( "\r\nCompany name: %s",
                                            theApp.sContact.csCompanyName
                                        );
                            mainText += format( "\r\nAdministrator Email: %s",
                                            theApp.sContact.csAdminEmail
                                        );                                                
                            mainText += format( 
                                            "\r\nComing from address %s, host %s",
                                            inet_ntoa( mainIP ),
                                            (LPCTSTR)domain
                                        );
                            
                            key.Close();

                            CString license;

                            key.Open( HKEY_LOCAL_MACHINE, "Software\\Vircom\\The 4th Coming Server" );
                            LPCTSTR szLicense = key.GetProfileString( "License", "" );

                            if( strlen( szLicense ) >= 22 ){
                                license = &szLicense[ 22 ];
                            }else{
                                license = "<invalid>";
                            }
                            
                            mainText += format(
                                            "\r\nClient ID: %s",
                                            (LPCTSTR)license
                                        );

                        }

                        string deadlockFile( theApp.sPaths.csLogPath );
                        deadlockFile += "deadlock.txt";

                        string heavyDbg = theApp.sPaths.csLogPath;
                        heavyDbg += "heavydbg.txt";

                        string exitLog = theApp.sPaths.csLogPath;
                        exitLog += "exit.txt";


                        list< const char * > extraFileList;
                        extraFileList.push_back( deadlockFile.c_str() );
                        extraFileList.push_back( heavyDbg.c_str() );
                        extraFileList.push_back( exitLog.c_str() );

                        // Send email to Vircom.
                        EasyMail()(
                            "smtp.vircom.com", 
                            (LPCTSTR)theApp.sContact.csAdminEmail,
                            "t4ccrash@the4thcoming.com", 
                            format(
                                "T4C crash on %s (%s) at %02u/%02u/%04u %02u:%02u:%02u",
                                (LPCTSTR)theApp.sContact.csCompanyName,
                                (LPCTSTR)domain,
                                sysTime.wMonth,
                                sysTime.wDay,
                                sysTime.wYear, 
                                sysTime.wHour, 
                                sysTime.wMinute,
                                sysTime.wSecond
                            ),
                            (LPCTSTR)mainText,
                            (LPCTSTR)csGPfile,
                            "crashreports@the4thcoming.com",
                            "p0rt1cule",
                            &extraFileList
                        );

                        CString newGPfile( csGPfile );

                        // Append date/time to GP.
                        newGPfile += format(
                                ".%u%u%u.%02u%02u%04u.bck",
                                sysTime.wSecond,
                                sysTime.wMinute,
                                sysTime.wHour,
                                sysTime.wDay,
                                sysTime.wMonth,
                                sysTime.wYear
                         );

                        DeleteFile( deadlockFile.c_str() );
                        DeleteFile( heavyDbg.c_str() );
                        DeleteFile( exitLog.c_str() );

                        // Rename GP.
                        CFile::Rename( csGPfile, newGPfile );
                    }catch(...){
                        _LOG_DEBUG
                            LOG_DEBUG_HIGH,
                            "Crashed initializing emails."
                        LOG_
                    }
                }
            }


			regKey.Close();
			*/
		}else{
			theApp.sGeneral.wNbWarnings = 5;
			theApp.sGeneral.dwTimeBeforeWarning = 2500;

			_LOG_DEBUG
				LOG_CRIT_ERRORS,
				"\n     Could not open registry key " T4C_KEY GEN_CFG_KEY " required by T4C Server."
				"\n     Run T4C Server Setup from the control panel to setup the registry keys."
				"\n     Using default values."
			LOG_
		}

      { 
            SYSTEMTIME sysTime; 
            GetLocalTime(&sysTime);

            _EXITLOG "\r\n+++[STARTUP] %u/%u/%u %02u:%02u:%02u +++",
                sysTime.wMonth,
                sysTime.wDay,
                sysTime.wYear, 
                sysTime.wHour, 
                sysTime.wMinute,
                sysTime.wSecond
            EXITLOG_
        }

        // Authentification //////////////////////////////////////////////////////////////////////
        if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY AUTH_KEY ) )
		{
            theApp.sAuth.bAuthentificationMethod = (BYTE)regKey.GetProfileInt( "AuthenticationMethod", ODBC_AUTH );

/*            if( theApp.sAuth.bAuthentificationMethod == GOA_AUTH )
			{
                if( !InitGoaAuth() )
				{
                    _LOG_DEBUG
                        LOG_CRIT_ERRORS,
                        "GOA authentication specified but could not be initialized."
                    LOG_
                    exit( 127 );
                }
            }*/

            
            KEY2TXT( theApp.sAuth.csODBC_Credits,          "ODBC_CREDITS_FLD",     "" );
            KEY2TXT( theApp.sAuth.csODBC_DBPwd,            "ODBC_DB_PWD",          "" );
            KEY2TXT( theApp.sAuth.csODBC_DSN,              "ODBC_DSN",             "T4C Server Authentication" );
            KEY2TXT( theApp.sAuth.csODBC_Where,            "ODBC_WHERE",           "" );
            KEY2TXT( theApp.sAuth.csODBC_Pwd,              "ODBC_PWD_FLD",         "Password" );
            KEY2TXT( theApp.sAuth.csODBC_Table,            "ODBC_TABLE",           "T4CUsers" );
            KEY2TXT( theApp.sAuth.csODBC_Account,          "ODBC_NAME_FLD",        "Account" );
            KEY2TXT( theApp.sAuth.csODBC_DBUser,           "ODBC_DB_USER",         "" );
            
            WORD wDeduct = (WORD)regKey.GetProfileInt( "ODBC_DEDUCT_CREDITS", 1 );
            if( wDeduct != 0 )
			{
                theApp.sAuth.boODBC_DeductCredits = TRUE;
            }
			else
			{
                theApp.sAuth.boODBC_DeductCredits = FALSE;
            }

            theApp.sAuth.csODBC_Where.TrimRight();
            theApp.sAuth.csODBC_Where.TrimLeft();
	            
            
            /*CString csIP = regKey.GetProfileString( "VOP_SEC_IP", "0.0.0.0" );            
            csIP.TrimRight();
            csIP.TrimLeft();
            theApp.sAuth.csVOP_SECIP = csIP;
            TRACE( "\r\nIP: '%s')", (LPCTSTR)csIP );
            csIP = regKey.GetProfileString( "VOP_NAS_IP", "0.0.0.0" );
            csIP.TrimRight();
            csIP.TrimLeft();
            theApp.sAuth.csVOP_NASIP = csIP;

            theApp.sAuth.csWGKey = regKey.GetProfileString( "WG_T4C_KEY", "" );
            theApp.sAuth.csWGKey.TrimRight();
            theApp.sAuth.csWGKey.TrimLeft();

            theApp.sAuth.csRemoteWGKey = regKey.GetProfileString( "REMOTE_WG_T4C_KEY", "" );
            theApp.sAuth.csRemoteWGKey.TrimRight();
            theApp.sAuth.csRemoteWGKey.TrimLeft();

            theApp.sAuth.wVOP_SECPort = (WORD)regKey.GetProfileInt( "VOP_SEC_PORT", 0 );
            theApp.sAuth.csVOP_Secret = regKey.GetProfileString( "VOP_SECRET", "T4CSecret" );
            
            theApp.sAuth.m_StripRealmPartOfAccount = regKey.GetProfileInt( "VOP_STRIP_REALM", 0 ) != 0 ? true : false;

            theApp.sAuth.wAcctPort = (WORD)regKey.GetProfileInt( "VOP_ACCT_PORT", 0 );
            theApp.sAuth.csAcctIP  = regKey.GetProfileString( "VOP_ACCT_IP", "" );

            theApp.sAuth.w2ndAuthPort = (WORD)regKey.GetProfileInt( "VOP_2ND_AUTH_PORT", 0 );
            theApp.sAuth.cs2ndAuthIP  = regKey.GetProfileString( "VOP_2ND_AUTH_IP", "" );
            theApp.sAuth.w2ndAcctPort = (WORD)regKey.GetProfileInt( "VOP_2ND_ACCT_PORT", 0 );
            theApp.sAuth.cs2ndAcctIP  = regKey.GetProfileString( "VOP_2ND_ACCT_IP", "" );

            TRACE( "\r\nIP: '%s'", (LPCTSTR)csIP, theApp.sAuth.csVOP_NASIP );
            TRACE( "..%s..", (LPCTSTR)theApp.sAuth.csVOP_Secret );
			*/

            //theApp.sAuth.csRealm = regKey.GetProfileString( "AUTH_REALM", "" );
//DC
			/*theApp.sAuth.csWGFlag = static_cast< DWORD >( regKey.GetProfileInt( "WG_FLAG",  0 ) );
			if ( theApp.sAuth.csWGFlag ){
				_LOG_DEBUG  LOG_DEBUG_LVL4,
					"Worldgroup server is used for Radius authentification: %u",theApp.sAuth.csWGFlag
				LOG_
				theApp.sAuth.csVOP_NASPort = (WORD) 1;
			}else{
				theApp.sAuth.csVOP_NASPort = (WORD) 0;
			}*/
			

			theApp.dwEncryptedPassword		= regKey.GetProfileInt( "PASSWORD_ENCRYPTION", 0 );
			theApp.dwPasswordCaseSensitive  = regKey.GetProfileInt( "PASSWORD_CASE", 0 );			
//DC
            regKey.Close();
        }else{
            theApp.sAuth.csODBC_Credits = "";
            theApp.sAuth.csODBC_DBPwd = "";
            theApp.sAuth.csODBC_DSN = "T4C Server Authentication";
            theApp.sAuth.csODBC_Where = "";
            theApp.sAuth.csODBC_Pwd = "Password";
            theApp.sAuth.csODBC_Account = "Account";
            theApp.sAuth.boODBC_DeductCredits = FALSE;
            //theApp.sAuth.wVOP_SECPort = 0;
            //theApp.sAuth.csVOP_Secret = "T4CSecret";
			theApp.dwEncryptedPassword = 0;
			theApp.dwPasswordCaseSensitive = 0;

			_LOG_DEBUG
				LOG_CRIT_ERRORS,
				"\n     Could not open registry key " T4C_KEY AUTH_KEY " required by T4C Server."
				"\n     Run T4C Server Setup from the control panel to setup the registry keys."
				"\n     Using default values."
			LOG_
        }


        regKey.Close();

        regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY CHARACTER_KEY );
// Those 2 keys were load earlier to make it possible to initialize SQL logs
//        theApp.csDBUser = regKey.GetProfileString( "DB_USER", "" );
//        theApp.csDBPwd  = regKey.GetProfileString( "DB_PWD",  "" );

		theApp.InService = FALSE;		
		CString csExcpFile = ServerPath;
		csExcpFile += _T("T4CServerGP.out");

		CExpFltr::SetReportFile((LPTSTR)(LPCTSTR)csExcpFile);
		CExpFltr::SetAppTitle(_T("T4C Server"));

		TRACE(_T("**%s\r\n"), (LPCTSTR)ServerPath);
		
		CString messagepath = ServerPath + "T4C Messages.dll";
			
		// If the directory specified by "ServerPath" is invalid, inform the user and use normal path
		CFileFind check;
		if(!check.FindFile(ServerPath + ".")){
			LPCTSTR param[2] = {(LPCTSTR)ServerPath, path};
			
			TRACE(_T("%s--"), param[0]);
			TRACE(_T("%s"), param[1]);

//			ReportError Err(__WARNING_PATH_NOT_FOUND, 2, param);

			_LOG_DEBUG LOG_ALWAYS, "Server path %s not found", (LPCTSTR)ServerPath LOG_

			messagepath = path;
			messagepath += "T4C Messages.dll";
		}
		
		
		{		
			RegKeyHandler EventLog;
			if(!EventLog.Open(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\T4C Server"))
			{
				_LOG_DEBUG LOG_MISC_1, "Creating new NT EventViewer application entry: T4C Server" LOG_

				EventLog.Create(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\T4C Server");
				EventLog.WriteProfileString(_T("EventMessageFile"), (LPCTSTR)messagepath);
				EventLog.WriteProfileInt(_T("TypesSupported"),  EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | EVENTLOG_INFORMATION_TYPE);
			}
		}

		theApp.dwPVPDropDisabled = 0;

/*
		//get the program path
		lstrcpy( path, GetCommandLine() );
		
		int argc;

		// Path in wide char.
		WCHAR pathW[256];

		MultiByteToWideChar( CP_ACP, 0, path, -1, pathW, 256 );
		
		LPWSTR *argv = CommandLineToArgvW( pathW, &argc );
		
		startAsService = TRUE;

		if( argc == 2 ){		
			if( _wcsicmp( argv[1], L"-m" ) == 0 ){
				theApp.InService = FALSE;
//				SetInService( FALSE );	
				startAsService = FALSE;
			}else
			if( _wcsicmp( argv[1], L"--spawn_service" ) == 0 ){
				// Makes the server beleive its in service so it won't display
				// message boxes but rather output to the event logger.
				theApp.InService = TRUE;
//				SetInService( TRUE );
				startAsService = FALSE;
			}
		}

		GlobalFree( argv );		
*/
		//init the service with the SCM, if the program is to be started as
		//a service
		if(startAsService){	
			CUService service;
			//setup the service class callback functions
			service.SetStopTimeOut( 180000 );
            service.SetCallBacks(NULL,NULL, StopFunction);
			// Initialize the SCM.
			if(service.InitService(_T("T4C_Server"), EntryFunction) != TRUE)
                exit(COULDNT_START_AS_A_SERVICE);
		}
		//just call the programs main entry point, if it is not to start as
		//a service
		else{
				EntryFunction(NULL);
				return NORMAL_SERVER_EXIT;
		}

	}catch( ... ){
#ifdef _DEBUG
        throw;
#endif
		throw;

		FILE *fDbg = fopen( "T4CServerGP.out", "ab" );
		if( fDbg ){
			time_t current_time;
			time(&current_time);
			CString version;			
			version.LoadString(IDS_SERVER_VERSION);
			fprintf( fDbg, "\r\n-----");
			fprintf( fDbg, "\r\nT4C Server v%s - Build l - Main. General Protection fault report, %s\r\n\r\n", (LPCTSTR)version, ctime(&current_time) );
			fprintf( fDbg, "Server crashed during InitInstance initialisation.                              " );
			fclose( fDbg );
		}
		END_LOG
		// Terminates main pump.
		MessageBeep( -1 );
        return FALSE;
	}
return TRUE;
}

bool IsLicenseLegal( string licenseKey );
//////////////////////////////////////////////////////////////////////////////////////////


/** @short This is the service entry-point.
 */
void CDECL EntryFunction(void *cu)
{
	CAutoThreadMonitor tmMonitor("Console (EntryFunction)");

#ifdef __ENABLE_LOG
	if(__LOG > 0) __LOG("Entering the EntryFunction");
#endif
	try{
        CoInitialize( NULL );
/*
		if(ServerPath.IsEmpty())
		{
//			ReportError Err(__ERR_EMPTY_PATH);
			MessageBeep( -1 );
            exit( SERVERPATH_EMPTY );
		}			
*/		
/*
		SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
*/		
		//_set_se_translator(MainPumpExceptionFunction);
		
        
		/* On initialise d'abord avec une window d'init */
		
        {
			theApp.sLicense.loadDb = true;
      
        }

		// BEGIN : Mestoph -> Load SpeedHack configuration on registry
	/*	{
            RegKeyHandler regKey;
            if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY CHEAT_KEY ) ){
				theApp.iSpeedHackDelay = static_cast< int >( regKey.GetProfileInt( "SPEEDHACK_DELAY", SH_DEF_DELAY ) );
				if (theApp.iSpeedHackDelay < 5) theApp.iSpeedHackDelay = SH_DEF_DELAY;
			}else{
				theApp.iSpeedHackDelay = SH_DEF_DELAY;
			}


			if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY CHEAT_KEY ) ){
				theApp.iSpeedHackMaxMovments = static_cast< int >( regKey.GetProfileInt( "SPEEDHACK_MAX_MOVEMENTS", SH_DEF_MOVMENTS ) );
				if (theApp.iSpeedHackMaxMovments < 30) theApp.iSpeedHackMaxMovments = SH_DEF_MOVMENTS;
			}else{
				theApp.iSpeedHackMaxMovments = SH_DEF_MOVMENTS;
			}
		}*/
		// END : Mestoph -> Load SpeedHack configuration on registry
                
        DWORD dwVersion = SERVER_CONNECTION_HI_VERSION;
        {
            RegKeyHandler regKey;
            regKey.Open( HKEY_LOCAL_MACHINE, "Software\\Vircom\\The 4th Coming Server\\GeneralConfig" );

            // Fetch version from registry, otherwise default to the executable's version.
            dwVersion = regKey.GetProfileInt( "Version", SERVER_CONNECTION_HI_VERSION );
            regKey.Close();
        }

        
        CString csVersion;
        csVersion.Format( VERSION_STRING, dwVersion );
        
        printf( "-----                                                   "
                "\n%s.                                                   "
                "\nCopyright(c) Rebirth inc. 1998-2017.                  "
				"\nT4C: Rebirth special edition RC                       "
				"\nAll rights reserved.\n                                "
                "\n-----                                                 ",
				Version::sBuildStamp.c_str()
        );


#ifdef _MONT4C
	STARTUPINFO startInfo;
	startInfo.cb            = sizeof( STARTUPINFO );
	startInfo.lpReserved    = NULL; 
	startInfo.lpDesktop     = NULL;
	startInfo.lpTitle       = NULL;
	startInfo.dwFlags       = STARTF_USESHOWWINDOW | STARTF_USEFILLATTRIBUTE;
	startInfo.cbReserved2   = 0;
	startInfo.lpReserved2   = NULL; 

    PROCESS_INFORMATION procInfo;
        
    // Create the application's process.
    CreateProcess( 
        NULL, 
        "C:/ServerRelease/zzz.exe",//const_cast< char * >( appExec.c_str() ),
        NULL,
        NULL, 
        FALSE, 
        CREATE_NEW_CONSOLE, 
        NULL, 
        NULL,
        &startInfo, 
        &procInfo);
#endif //_MONT4C

		
		
		_LOG_DEBUG
            LOG_DEBUG_LVL1,
            "Loading version %s",
            (LPCTSTR)csVersion
        LOG_
        
        try{
            TFCServer = new TFC_MAIN;
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "Creating TFC_MAIN object."
            LOG_
        }catch(...){
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "Crashed when creating TFC_MAIN object."
            LOG_
            throw;
        }        

/*
	** Those lines got moved to the beggining so that it starts the ODBCTrace
	** Before the first call to the logging functions.
	** This way we can make logging functions log to SQL as long as TXT files.
        try{
            ODBCHarness = new ODBCTrace;
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "Creating ODBCTrace object."
            LOG_
        }catch(...){
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "Crashed when creating ODBCTrace object."
            LOG_
            throw;
        }        
*/
        try{
            TFCInitMaps();
        }catch(...){
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "Crashed when initializing worlds database."
            LOG_
            throw;
        }
		        

        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Installing performance counters."
        LOG_
        
        // Install performance counters.
/*        if( !CPrfData::Install( L"T4C Monitor.dll" ) ){
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "Failed to update performance counters, forcing installation. Counters are probably out-of-sync."
            LOG_

            // If installation fails, try to force it.
            if( !CPrfData::Install( L"T4C Monitor.dll", true ) ){
                _LOG_DEBUG
                    LOG_CRIT_ERRORS,
                    "Failed to force performance counter update."
                LOG_
                MessageBeep( -1 );
                exit( 127 );
            }else{
                _LOG_DEBUG
                    LOG_CRIT_ERRORS,
                    "Forced performance counter update succeeded!"
                LOG_
            }
        }

        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Activating performance counters."
        LOG_        
        
        CPrfData::Activate();*/

        
        _LOG_DEBUG
            LOG_DEBUG_LVL1,
            "InitThread Id=%u",
            GetCurrentThreadId()
        LOG_

        // Start the player and packet manager.
        CAutoConfig::Create( HKEY_LOCAL_MACHINE, "Software\\Vircom\\The 4th Coming Server", "RegUpdate" );

        SysopCmd::Create();
        printf( "\n- Initialised System operator/GM commands" ); //BLBLBL added verbose output


        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Post-Init phase A"
        LOG_  
		
        GAME_RULES::Create();
        printf( "\n- Initialised Game rules" );
        
		_LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Post-Init phase B"
        LOG_        
        
		CDeadlockDetector::Create();
        printf( "\n- Initialised Deadlock detector" );

        
		_LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Post-Init phase C"
        LOG_
        
		TFCMessagesHandler::Create();
		printf( "\n- Initialised Messages handler" );	
        
		_LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Post-Init phase D"
        LOG_        
        
		CPacketManager::Create();
		printf( "\n- Initialised Packet manager" );
        
		_LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Post-Init phase E"
        LOG_        
        
        // Get the sole instance, this also creates the NPC thread.
        NPCMain::GetInstance();
		printf( "\n- Initialised NPC and main instance" );

        _LOG_DEBUG
            LOG_DEBUG_LVL1,
            "NPC Thread Id=%u",
            NPCMain::GetInstance().GetThreadId()
        LOG_

		// Init Script thread
/*		ScriptFile::GetInstance();
		printf( "\n- Initialised Scripts support" );*/

        theApp.serverStarted = true;
        
//        GlobalStatistics::GetInstance()->Create();
//		printf( "\n- Initialised Global statistics" );

        TFCMAIN::StartBeat();
        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Post-Init phase F"
		LOG_

        CPlayerManager::Create(); 
		printf( "\n- Initialised Player manager" );

        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Post-Init phase G"
		LOG_

		TextFilter.Initialize("textfilter.ini");//16/06/2009 bad words filter, inititialization.
		printf( "\n- Initialised Text filter" );

        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Post-Init phase G2"
		LOG_
        
		///////////////////////////////////////
		// Sends the MSG_OnServerInitialisation
		Unit::SendGlobalUnitMessage( MSG_OnServerInitialisation, NULL, NULL, NULL );
		
        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Post-Init phase H"
		LOG_

		SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL);

        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Post-Init phase I"
		LOG_

        // Let the main console take control of this thread.
        MainConsole::GetInstance().TakeControl();

        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Post-Init phase J"
		LOG_

	}catch( ... ){
		
		_LOG_DEBUG LOG_CRIT_ERRORS, "Crashed during T4C Server initialization. EntryFunction section." LOG_
		
		END_LOG;
		
        throw;

	}

    exit( TERMINATE_FAIL_INIT );
}


void __cdecl StopFunction(void *cus)
{	
    // Terminate main console.
    MainConsole::GetInstance().Terminate();
}

#if 0
// Removed block listing, will get deleted soon.

/* Block [1] */
    // Query VOPSEC version
//VOPPORT VOPSEC_CODE VOPSEC_GetVersion(LPSTR szVersion, short nSizeVersion, 
//									  DWORD *dwAPIVersion);

   

#ifdef DETERMINATE_DB_PASSWORD    
    char szPwd[] = "Gh0s73y3";
    
    Random rnd;
    int i;
    TRACE( "\r\nPwd: " );
    rnd.SetSeed( 11677 );
    for( i =0; i < sizeof( szPwd ); i++ ){
        TRACE( "%u ", szPwd[ i ] ^ rnd( 0, 255 ) );
    }
    TRACE( "\r\n" );

    exit( 0 );
#endif    

/* End of Block [1] */

/* Block [2] */
	
    // Initialize SmartHeap
    //MemRegisterTask();
    //MemSetErrorHandler( SmartHeapErrorHandler );

    /*
    RegKeyHandler regKey;
       
    regKey.Open( HKEY_LOCAL_MACHINE, "Software\\Vircom\\The 4th Coming Server" );
    
    if(!LicenseKey::CheckLicense(regKey.GetProfileString( "License", "" ),true))
    {
       FILE *f = fopen( "_startup.log", "wb" );
       if( f )
       {
          fprintf( f, "Wrong license key." );
          fclose(f);
       }
       MessageBeep( -1 );
       exit( WRONG_LICENSE_KEY );
    }
    */

    
/* End of Block [2] */.

/* Block [3] */


//    CDebugLockManager::Create();

#ifdef MEM_DEBUG

//    dbgMemSetSafetyLevel( MEM_SAFETY_SOME );
#endif

#ifdef _DEBUG
    //_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );
#else
    //_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
#endif
    //_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    //_CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );

/* End of Block [3] */

/* Block [4] */

	    {
        char szMachineName[ 256 ];
        DWORD dwSize = 256;
        GetComputerName( szMachineName, &dwSize );
        theApp.csMachineName = szMachineName;
    }


/* End of Block [4] */

/* Block [5] */

		// Standard initialization
		// If you are not using these features and wish to reduce the size
		//  of your final executable, you should remove from the following
		//  the specific initialization routines you do not need.

	#ifdef _AFXDLL
//		Enable3dControls();			// Call this when using MFC in a shared DLL
	#else
//		Enable3dControlsStatic();	// Call this when linking to MFC statically
	#endif
		
/* End of Block [5] */

#endif
