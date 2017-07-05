// T4CLog.h: interface for the CT4CLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_T4CLOG_H__91929B24_3B5C_11D2_83D5_00E02922FA40__INCLUDED_)
#define AFX_T4CLOG_H__91929B24_3B5C_11D2_83D5_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OldLogger.h"

#define LOG_DEATH       0
#define LOG_GAMEOP      1
#define LOG_PC          2
#define LOG_ITEMS       3
#define LOG_NPCS        4
#define LOG_WORLD       5
#define LOG_DEBUG       6
#define LOG_PAGE        7
#define LOG_SHOUTS      8
#define LOG_TEXT        9
// BEGIN : Mestoph -> Add Cheat Log
#define LOG_CHEAT       10
// END : Mestoph -> Add Cheat Log


class EXPORT CT4CLog  
{
public:
    static void InitLogs();
    static void StopLogs();
         
    static CLogger *GetLog( DWORD dwType );
    static void     DebugLog();
    static DWORD    GetLogID( DWORD dwType );
    static void     DebugLog( WORD wLogLevels, const char *szText, ... );

    static BOOL IsInit( void );
	static void SaveToLog( DWORD dwType, WORD wLogLevels, const char *szText, ...);
	 static void SaveDeathLog(CString &strVictime,CString &strAssassin, int dwType);
	static const char* GetLogTableName( DWORD dwType );
private:
    CT4CLog( void );
    void Destroy( void );

    void Create( LPBYTE lpszFileName, WORD wLogLevels );
	static void CheckForODBCErrorsCallBack( DWORD dwSaveStatus, LPVOID lpData);

    static  CT4CLog  *cT4CLogs;
	static DWORD dwODBCErrorTimer; // Checks when the last error ocurred
	static int ODBCErrorCounter; // Counts the number of errors
	static WORD wSQLLogTypes; // The log types that will be logged to SQL
	static WORD wSQLLogLevel; // The log level for the SQL log

    BOOL    boLog;
    DWORD   dwLogID;
    LPBYTE  lpbBuffer;
    CLogger logLog;
};

#define START_LOG       			CT4CLog::InitLogs();
#define END_LOG						//CT4CLog::StopLogs();

#define IS_LOG_INIT                     CT4CLog::IsInit()

/*
#define _LOG_DEATH  if( CT4CLog::GetLog( LOG_DEATH ) != NULL ){ \
                                    CT4CLog::GetLog( LOG_DEATH )->AsyncLog(
#define _LOG_GAMEOP if( CT4CLog::GetLog( LOG_GAMEOP ) != NULL ){ \
                                   CT4CLog::GetLog( LOG_GAMEOP )->AsyncLog(
#define _LOG_PC     if( CT4CLog::GetLog( LOG_PC ) != NULL ){ \
                                   CT4CLog::GetLog( LOG_PC )->AsyncLog(
//#define _LOG_ITEMS  if( CT4CLog::GetLog( LOG_ITEMS ) != NULL ){ \
//                                   CT4CLog::GetLog( LOG_ITEMS )->AsyncLog(
#define _LOG_ITEMS { CT4CLog::SaveToLog(LOG_ITEMS,

#define _LOG_NPCS   if( CT4CLog::GetLog( LOG_NPCS ) != NULL ){ \
                                   CT4CLog::GetLog( LOG_NPCS )->AsyncLog(
#define _LOG_WORLD  if( CT4CLog::GetLog( LOG_WORLD ) != NULL ){ \
                                   CT4CLog::GetLog( LOG_WORLD )->AsyncLog(
#define _LOG_DEBUG  { \
                                   CT4CLog::DebugLog(

#define _LOG_SHOUTS  if( CT4CLog::GetLog( LOG_SHOUTS ) != NULL ){ \
                                   CT4CLog::GetLog( LOG_SHOUTS )->AsyncLog(
#define _LOG_PAGE  if( CT4CLog::GetLog( LOG_PAGE ) != NULL ){ \
                                   CT4CLog::GetLog( LOG_PAGE )->AsyncLog(
#define _LOG_TEXT  if( CT4CLog::GetLog( LOG_TEXT ) != NULL ){ \
                                   CT4CLog::GetLog( LOG_TEXT )->AsyncLog(

#define _SYNC_LOG_DEBUG if( CT4CLog::GetLog( LOG_DEBUG ) != NULL ){ \
                                   CT4CLog::GetLog( LOG_DEBUG )->SyncLog(
*/

#define _LOG_DEATH { CT4CLog::SaveToLog(LOG_DEATH,
#define _LOG_GAMEOP { CT4CLog::SaveToLog(LOG_GAMEOP,
#define _LOG_PC { CT4CLog::SaveToLog(LOG_PC,
#define _LOG_ITEMS { CT4CLog::SaveToLog(LOG_ITEMS,
#define _LOG_NPCS { CT4CLog::SaveToLog(LOG_NPCS,
#define _LOG_WORLD { CT4CLog::SaveToLog(LOG_WORLD,
#define _LOG_SHOUTS { CT4CLog::SaveToLog(LOG_SHOUTS,
#define _LOG_PAGE { CT4CLog::SaveToLog(LOG_PAGE,
#define _LOG_TEXT { CT4CLog::SaveToLog(LOG_TEXT,
// BEGIN : Mestoph -> Add Cheat Log
#define _LOG_CHEAT { CT4CLog::SaveToLog(LOG_CHEAT,
// END : Mestoph -> Add Cheat Log
#define _LOG_DEBUG  { CT4CLog::DebugLog(
#define _SYNC_LOG_DEBUG if( CT4CLog::GetLog( LOG_DEBUG ) != NULL ){ \
                                   CT4CLog::GetLog( LOG_DEBUG )->SyncLog(
#define LOG_    ); };

#endif // !defined(AFX_T4CLOG_H__91929B24_3B5C_11D2_83D5_00E02922FA40__INCLUDED_)
