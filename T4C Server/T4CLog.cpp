// T4CLog.cpp: implementation of the CT4CLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ODBCMage.h"
#include "TFC Server.h"
#include "T4CLog.h"
#include "RegKeyHandler.h"
#include "TFC Server.h"
#include "AutoConfig.h"
#include "OldLogger.h"
#include "TFC_MAIN.h"

#include "DebugLoggerAPI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define NB_LOG_TYPES        11 // MOD : Mestoph : incremented by 1 before : 10
#define LOG_BUFFER_SIZE     4048


extern CTFCServerApp theApp;

//////////////////////////////////////////////////////////////////////////////////////////
#define CREATE_LOG( __type, __key, __enablelog,  __default ) {\
    csFileName = csLogPath;\
    csFileName += regKey.GetProfileString( __key, __default );\
    if( regKey.GetProfileInt( __enablelog, 1 ) != 0 ){\
        TRACE( "\r\nLogging to file %s.", (LPCTSTR)csFileName );\
        cT4CLogs[ __type ].Create( (LPBYTE)(LPCTSTR)csFileName, wLevel );\
    }else{\
        TRACE( "\r\nNOT logging to file %s.", (LPCTSTR)csFileName );\
        cT4CLogs[ __type ].Create( NULL, 0 );\
    }\
}

#define IFLOG( __key, __level ) if( regKey.GetProfileInt( __key, 0 ) != 0 ){ wLevel |= __level; };

CT4CLog *CT4CLog::cT4CLogs;
DWORD CT4CLog::dwODBCErrorTimer; // Checks when the last error ocurred
int CT4CLog::ODBCErrorCounter; // Counts the number of errors
static bool logToMonitor = false;

static cODBCMage ODBCLogs;
WORD CT4CLog::wSQLLogTypes, CT4CLog::wSQLLogLevel;

//////////////////////////////////////////////////////////////////////////////////////////
void LogUpdate( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Called when the registry is udpated.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    RegKeyHandler regKey;

    if( !regKey.Open( HKEY_LOCAL_MACHINE, "SOFTWARE\\Vircom\\The 4th Coming Server\\Logging" ) ){ 
        return;
    }

    if( regKey.GetProfileInt( "LogToMonitor", 0 ) != 0 ){
        logToMonitor = true;
    }else{
        logToMonitor = false;
    }
}


static BOOL boIsInit = FALSE;
//////////////////////////////////////////////////////////////////////////////////////////
void CT4CLog::InitLogs( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Inits all logs
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    RegKeyHandler regKey;
    CString csLogPath;
    CString csFileName;
    WORD wLevel = 0;//BLBLBL Il faut ajouter une commande SYSOP permettant de mettre ce level au max debug ON/OFF pour les besoins
	                //de debuggage sans redémarrer le serveur, ou alors réintorroger de temps en temps le reglage du serveur dans le
	                //panneau de configuration windows.

    cT4CLogs = new CT4CLog[ NB_LOG_TYPES ];

    if( !regKey.Open( HKEY_LOCAL_MACHINE, "SOFTWARE\\Vircom\\The 4th Coming Server\\Logging" ) )
	{        
        wLevel = LOG_DEBUG_LIGHT;
    }

    CAutoConfig::AddRegUpdateCallback( LogUpdate );
    LogUpdate();

    csLogPath = theApp.sPaths.csLogPath;
    
    IFLOG( "LOG_CRITICAL_ERRORS",   LOG_CRIT_ERRORS );
    IFLOG( "LOG_GEN_ERRORS",        LOG_GEN_ERRORS );
    IFLOG( "LOG_WARNINGS",          LOG_WARNING );
    IFLOG( "LOG_MISC",              LOG_MISC_1 );
    IFLOG( "LOG_DEBUG_LVL1",        LOG_DEBUG_LVL1 | LOG_DEBUG_LVL2 );
    IFLOG( "LOG_DEBUG_LVL3",        LOG_DEBUG_LVL3 | LOG_DEBUG_LVL2 );
    IFLOG( "LOG_DEBUG_LVL4",        LOG_DEBUG_LVL4 | LOG_DEBUG_LVL2 );
    IFLOG( "LOG_DEBUG_HIGH",        LOG_DEBUG_HIGH | LOG_DEBUG_LVL2 );
    

    wLevel |= LOG_SYSOP;
    
    TRACE( "\r\nLog path=%s.", (LPCTSTR)csLogPath );

    CREATE_LOG( LOG_DEATH,  "DEATH_LOG",  "LOG_DEATH_LOG",  "Death.log" );
    CREATE_LOG( LOG_GAMEOP, "GAMEOP_LOG", "LOG_GAMEOP_LOG", "GameOp.log" );
    CREATE_LOG( LOG_PC,     "PC_LOG",     "LOG_PC_LOG",     "PCEdit.log" );
    
    CREATE_LOG( LOG_PAGE,   "PAGE_LOG",   "LOG_PAGE_LOG",   "Pages.log" );
    CREATE_LOG( LOG_SHOUTS, "SHOUTS_LOG", "LOG_SHOUTS_LOG", "Shouts.log" );
    CREATE_LOG( LOG_TEXT,   "TEXT_LOG",   "LOG_TEXT_LOG",   "OnlineText.log" );

    CREATE_LOG( LOG_ITEMS,  "ITEMS_LOG",  "LOG_ITEMS_LOG",  "Items.log" );
    CREATE_LOG( LOG_NPCS,   "NPCS_LOG",   "LOG_NPCS_LOG",   "NPCs.log" );
    CREATE_LOG( LOG_WORLD,  "WORLD_LOG",  "LOG_WORLD_LOG",  "World.log" );
    CREATE_LOG( LOG_DEBUG,  "DEBUG_LOG",  "LOG_DEBUG_LOG",  "Debug.log" );

	// BEGIN : Mestoph -> Add Cheat Log
    CREATE_LOG( LOG_CHEAT,  "LOG_CHEAT",  "LOG_CHEAT_LOG",  "Cheat.log" );
	// END : Mestoph -> Add Cheat Log

	if (boIsInit == FALSE) {

		// Starting SQL log levels and connections
		wSQLLogLevel = wSQLLogTypes = 0; // Initialize SQL log levels and types to all disabled

		// Determine which types will be logged to SQL
		if( regKey.GetProfileInt( "LOGSQL_DEATH_LOG", 0 ) != 0 ) { wSQLLogTypes |= 1 << LOG_DEATH; }
		if( regKey.GetProfileInt( "LOGSQL_GAMEOP_LOG", 0 ) != 0 ) { wSQLLogTypes |= 1 << LOG_GAMEOP; }
		if( regKey.GetProfileInt( "LOGSQL_PC_LOG", 0 ) != 0 ) { wSQLLogTypes |= 1 << LOG_PC; }
		if( regKey.GetProfileInt( "LOGSQL_PAGE_LOG", 0 ) != 0 ) { wSQLLogTypes |= 1 << LOG_PAGE; }
		if( regKey.GetProfileInt( "LOGSQL_SHOUTS_LOG", 0 ) != 0 ) { wSQLLogTypes |= 1 << LOG_SHOUTS; }
		if( regKey.GetProfileInt( "LOGSQL_TEXT_LOG", 0 ) != 0 ) { wSQLLogTypes |= 1 << LOG_TEXT; }
		if( regKey.GetProfileInt( "LOGSQL_ITEMS_LOG", 0 ) != 0 ) { wSQLLogTypes |= 1 << LOG_ITEMS; }
		if( regKey.GetProfileInt( "LOGSQL_NPCS_LOG", 0 ) != 0 ) { wSQLLogTypes |= 1 << LOG_NPCS; }
		if( regKey.GetProfileInt( "LOGSQL_WORLD_LOG", 0 ) != 0 ) { wSQLLogTypes |= 1 << LOG_WORLD; }

		// Determine which levels will be logged to SQL
		wSQLLogLevel |= LOG_SYSOP; // Sysop messages should always get logged!
		if( regKey.GetProfileInt( "LOGSQL_CRITICAL_ERRORS", 0 ) != 0 ) { wSQLLogLevel |= LOG_CRIT_ERRORS; }
		if( regKey.GetProfileInt( "LOGSQL_GEN_ERRORS",		 0 ) != 0 ) { wSQLLogLevel |= LOG_GEN_ERRORS; }
		if( regKey.GetProfileInt( "LOGSQL_WARNINGS",		 0 ) != 0 ) { wSQLLogLevel |= LOG_WARNING; }
		if( regKey.GetProfileInt( "LOGSQL_MISC",			 0 ) != 0 ) { wSQLLogLevel |= LOG_MISC_1; }
		if( regKey.GetProfileInt( "LOGSQL_DEBUG_LVL1",		 0 ) != 0 ) { wSQLLogLevel |= LOG_DEBUG_LVL1 | LOG_DEBUG_LVL2; }
		if( regKey.GetProfileInt( "LOGSQL_DEBUG_LVL3",		 0 ) != 0 ) { wSQLLogLevel |= LOG_DEBUG_LVL3 | LOG_DEBUG_LVL2; }
		if( regKey.GetProfileInt( "LOGSQL_DEBUG_LVL4",		 0 ) != 0 ) { wSQLLogLevel |= LOG_DEBUG_LVL4 | LOG_DEBUG_LVL2; }
		if( regKey.GetProfileInt( "LOGSQL_DEBUG_HIGH",		 0 ) != 0 ) { wSQLLogLevel |= LOG_DEBUG_HIGH | LOG_DEBUG_LVL2; }

		ODBCLogs.Connect ( USERS_DSN, USERS_USER, USERS_PWD );
		ODBCLogs.ConnectOption( SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF );
	}

    boIsInit = TRUE;
}

BOOL CT4CLog::IsInit( void ){
    return boIsInit;
}

//////////////////////////////////////////////////////////////////////////////////////////
void CT4CLog::StopLogs( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Stops all logs.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{       
    if( boIsInit ){
        int i;
        for( i = 0; i < NB_LOG_TYPES; i++ ){
            cT4CLogs[ i ].Destroy();
        }
    }
    
    // Destroy all log objects.
    //delete cT4CLogs;
}

//////////////////////////////////////////////////////////////////////////////////////////
CT4CLog::CT4CLog( void )
//////////////////////////////////////////////////////////////////////////////////////////
{   
    lpbBuffer = new BYTE[ LOG_BUFFER_SIZE + 1 ];
    boLog = FALSE;
}

// Destructor ////////////////////////////////////////////////////////////////////////////
void  CT4CLog::Destroy( void )
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( boLog ){        
        //logLog.EndLog( dwLogID );
    }
    //delete lpbBuffer; 
}
//////////////////////////////////////////////////////////////////////////////////////////
void CT4CLog::Create
//////////////////////////////////////////////////////////////////////////////////////////
// Initializes a specific logger object.
// 
(
 LPBYTE lpszFileName, // The log file name
 WORD   wLogLevels    // The log levels.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( lpszFileName != NULL ){
        logLog.SetLogFile( (char *)lpszFileName );
        logLog.SetLogLevels( wLogLevels );

        boLog = TRUE;

        //dwLogID = logLog.StartLog( ( char *)lpbBuffer, LOG_BUFFER_SIZE );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
CLogger *CT4CLog::GetLog
//////////////////////////////////////////////////////////////////////////////////////////
// Returns a logger object.
// 
(
 DWORD dwType // ID of logger object
)
// Return: CLogger, the logger object
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( cT4CLogs[ dwType ].boLog ){    
        return &cT4CLogs[ dwType ].logLog;
    }

    return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////
void CT4CLog::DebugLog
//////////////////////////////////////////////////////////////////////////////////////////
// This outputs strictly debug strings.
//
(
 WORD wLogLevels, // The log levels.
 const char *szText,     // The text to log.
 ...                     // The format specifiers.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Get the debug logger object.
    CLogger *logger = GetLog( LOG_DEBUG );
    if( logger == NULL ){
        return;
    }

    // If the logging level is not accepted.
    if( !( wLogLevels & logger->GetLogLevels() || wLogLevels == LOG_ALWAYS ) ){
        return;
    }

    static bool error = false;

    char lpBuffer[ 4096 ];

    va_list argp;		
    va_start( argp, szText );
    vsprintf( lpBuffer, szText, argp );
    va_end( argp );

    // If the application is set to output debug logs to a debug monitor
    // instead of a file.
    if( logToMonitor && !error ){
        DebugLoggerAPI::GetInstance()->Log( lpBuffer );
    }else{
        // Send string directly to the logger.
        logger->AsyncLog( wLogLevels, lpBuffer );
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
DWORD CT4CLog::GetLogID
//////////////////////////////////////////////////////////////////////////////////////////
// returns the log ID of a particular log.
// 
(
 DWORD dwType // The log type
)
// Return: DWORD, The log ID
//////////////////////////////////////////////////////////////////////////////////////////
{
    return cT4CLogs[ dwType ].dwLogID;
}

//////////////////////////////////////////////////////////////////////////////////////////
void CT4CLog::SaveToLog
//////////////////////////////////////////////////////////////////////////////////////////
// call both functions: TXT and SQL
// 
(
 DWORD       dwType,      // The log type
 WORD        wLogLevels, // The log levels.
 const char *szText,     // The text to log.
 ...                     // The format specifiers.
)
//////////////////////////////////////////////////////////////////////////////////////////
{

	char lpBuffer[4096];
    va_list argp;
    va_start( argp, szText );
    vsprintf( lpBuffer, szText, argp );
    va_end( argp );

	CString tempBuffer(lpBuffer);
	tempBuffer.Replace("%", "%%");
	strcpy(lpBuffer, tempBuffer.GetBuffer(0));
	

	
	// If it should be logged to text file..
	if (GetLog(dwType) != NULL) {
		GetLog(dwType)->AsyncLog( wLogLevels, lpBuffer );
	}
	
	// Then go for SQL..

	if ( ((1<<dwType) & wSQLLogTypes) == 0 ) return; // This log type is not being logged to SQL
	if ( wLogLevels != LOG_ALWAYS && (wLogLevels & wSQLLogLevel) == 0 ) return; // This log level is not being logged to SQL

    // Get the TimeStamp
    SYSTEMTIME sysTime; 
	GetLocalTime(&sysTime);
    CString csTimeStamp;
	csTimeStamp.Format("%04d%02d%02d%02d%02d%02d",
        sysTime.wYear, 
        sysTime.wMonth,
        sysTime.wDay,
        sysTime.wHour, 
        sysTime.wMinute,
        sysTime.wSecond
    );

	CString tmp(lpBuffer);
	tmp.Replace("'", "''");
	const char *csTableName = GetLogTableName(dwType);

	TemplateList< SQL_REQUEST > *lptlSQLRequests = new TemplateList< SQL_REQUEST >;
	LPSQL_REQUEST lpSql = new SQL_REQUEST;

	lpSql->csQuery.Format( "INSERT INTO %s (%s.Level,%s.TimeStamp,%s.LogInfo) VALUES ('%s','%s','%s')", csTableName, csTableName, csTableName, csTableName, "", csTimeStamp, tmp );

	lptlSQLRequests->AddToTail( lpSql );\
	ODBCLogs.SendBatchRequest( lptlSQLRequests, CheckForODBCErrorsCallBack, &lpSql->csQuery, "ODBCLogs" );

}

void CT4CLog::SaveDeathLog(CString &strVictime,CString &strAssassin, int dwType)
{

   // Get the TimeStamp
   SYSTEMTIME sysTime; 
   GetLocalTime(&sysTime);
   CString csTimeStamp;
   csTimeStamp.Format("%04d%02d%02d%02d%02d%02d",sysTime.wYear, sysTime.wMonth,sysTime.wDay,sysTime.wHour, sysTime.wMinute,sysTime.wSecond);

   CString strTableName;
   strTableName = "LogDeath2";

	
	TemplateList< SQL_REQUEST > *lptlSQLRequests = new TemplateList< SQL_REQUEST >;
	LPSQL_REQUEST lpSql = new SQL_REQUEST;

	lpSql->csQuery.Format( "INSERT INTO LogDeath2 (LogDeath2.TimeStamp,LogDeath2.Victime,LogDeath2.Assassin,LogDeath2.Type) VALUES ('%s','%s','%s','%d')", csTimeStamp, strVictime,strAssassin,dwType );

	lptlSQLRequests->AddToTail( lpSql );\
	ODBCLogs.SendBatchRequest( lptlSQLRequests, CheckForODBCErrorsCallBack, &lpSql->csQuery, "ODBCLogs" );
}

//////////////////////////////////////////////////////////////////////////////////////////
const char* CT4CLog::GetLogTableName
//////////////////////////////////////////////////////////////////////////////////////////
// Return the name of the table where logs are saved into SQL
// 
( 
 DWORD dwType	//The log type
)
//////////////////////////////////////////////////////////////////////////////////////////
// Return CString, the name of the table where the log will be saved to
{
	switch(dwType) {
	case LOG_DEATH: return "LogDeath";
	case LOG_GAMEOP: return "LogGameop";
	case LOG_PC: return "LogPC";
	case LOG_ITEMS: return "LogItems";
	case LOG_NPCS: return "LogNPCS";
	case LOG_WORLD: return "LogWorld";
	case LOG_DEBUG: return "LogDebug";
	case LOG_PAGE: return "LogPage";
	case LOG_SHOUTS: return "LogShouts";
	case LOG_TEXT: return "LogText";

	default: return "LogDefault";
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void CT4CLog::CheckForODBCErrorsCallBack
//////////////////////////////////////////////////////////////////////////////////////////
// Get the result of the ODBC Log requests and decide what to do on fails
// 
( 
 DWORD dwSaveStatus,	// Status of ODBC request
 LPVOID lpData			// The query string. (CString)
)
//////////////////////////////////////////////////////////////////////////////////////////
// 
{
	if (dwSaveStatus == BATCH_SUCCEEDED) return;
	CString *csQuery = reinterpret_cast< CString * >(lpData);
	_LOG_DEBUG
		LOG_CRIT_ERRORS,
			"SQL Error (%d) while trying: %s",
			dwSaveStatus,
			*csQuery
	LOG_
	DWORD curRound = TFCMAIN::GetRound();
	if (dwODBCErrorTimer < curRound) ODBCErrorCounter = 0;
	ODBCErrorCounter++;
	if (ODBCErrorCounter >= 10) {
		ODBCLogs.CheckDisconnectError();
		_LOG_DEBUG
			LOG_CRIT_ERRORS,
				"Getting too many (%d) SQL ERROR responses, checking for disconnection.",
				ODBCErrorCounter
		LOG_
	}
	dwODBCErrorTimer = curRound + 12000;	
}