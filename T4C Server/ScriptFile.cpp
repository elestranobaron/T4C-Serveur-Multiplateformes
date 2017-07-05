// ScriptFile.cpp: implementation of the ScriptFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ScriptFile.h"
#include <process.h>
#include "ThreadMonitor.h"
#include "DeadlockDetector.h"
#include "TFC Server.h"
#include "PlayerManager.h"
#include "Players.h"
#include "SysopCmd.h"
#include <stdarg.h>

extern CTFCServerApp theApp;

#define COMMENT				   if( strCmd[0] == '#' )
#define CHECK_COMMAND( __cmd ) else if( strCmd.find( __cmd ) != -1 )
#define BASIC_COMMAND		   else

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ScriptFile::ScriptFile()
{
	boStopScriptExecution = false;
	boSafeMode        = false;
	boScriptIsRunning = false;
	boTraceExecution  = false;
	boKeepScript	  = false;

	strGodCharacter   = "";
	strScriptFilename = "";

	if( theApp.dwScriptLoopLength > 0 )
	{
		boScriptThreadDone	 = false;
		hScriptThread = (HANDLE)_beginthreadex( NULL, 0, ScriptThread, 0, 0, &nScriptThreadId );

		_LOG_DEBUG
			LOG_DEBUG_LVL1,
			"Script Thread ID=%u",
			GetThreadId()
		LOG_
	}
	else
		boScriptThreadDone	 = true;
}

////////////////////////////////////////////
// Return only instance of the class
ScriptFile& ScriptFile::GetInstance( void )
{
	static ScriptFile inst;
	return inst;
}

////////////////////////////////////////////
// Main Script thread
unsigned int CALLBACK ScriptFile::ScriptThread( void* pParam )
{
	CAutoThreadMonitor tmMonitor( "Script Thread" );
	GetInstance().ThreadFunc();
	return 0;
}

////////////////////////////////////////////
// Called by ScriptThread
void ScriptFile::ThreadFunc( void )
{
	START_DEADLOCK_DETECTION( hScriptThread, "Script Thread" );

	// Waiting the right time to start the thread
	int PriorityChange = 1;
	int lastsecond = 0;

	while( !boScriptThreadDone )
	{
		KEEP_ALIVE

		// Run script if possible
		if( theApp.dwScriptLoopLength > 0 )
			RunScript( "Script\\script.txt" );

		KEEP_ALIVE

		// Verify global timers
		TFCTimerManager::VerifyTimers();

		Sleep( theApp.dwScriptLoopLength*1000 );
	}

	STOP_DEADLOCK_DETECTION
}

////////////////////////////////////////////
// Executes script content
int ScriptFile::RunScript( char* szScriptPath )
{	
	if( boScriptIsRunning )
		return -1;

	boScriptIsRunning = true;

	int nResult = 0;

	try
	{
		// Open script
		std::string strScript =	OpenScript( szScriptPath );

		// Default value is false
		boTraceExecution = false;
		boSafeMode = false;
		boKeepScript = false;
		boStopScriptExecution = false;
		strGodCharacter  = "";
		strScriptFilename = szScriptPath;

		// Parse line after line
		while( !strScript.empty() && !boStopScriptExecution )
		{
			// Get end of line
			std::string::size_type pos_endl = strScript.find_first_of( "\n" )+1;

			// If no \n, this is the end of file
			if( pos_endl == 0 )
			{
				// Only line left is the last command
				pos_endl = strScript.size();
				TranslateScript( strScript );
			}
			else
			{
				// Translate command
				std::string strCmd = strScript.substr( 0, pos_endl-1 );
				TranslateScript( strCmd );
			}

			// Remove treated line
			strScript.erase( 0, pos_endl );
		}
	}
	catch( int err )
	{
		nResult = err;
	}

	if( !boKeepScript )
	{
		// Rename file to avoid to be executed another time
		char newFilename[128];
		sprintf( newFilename, "%d_%s", time( NULL ), strScriptFilename.c_str() );
		
		MoveFile( strScriptFilename.c_str(), newFilename );
	}

	strScriptFilename = "";
	boScriptIsRunning = false;

	return nResult;
}

////////////////////////////////////////////
// Open script (if any errors, thows an exception )
std::string ScriptFile::OpenScript( char* szFile )
{
	// Try to open the file
	FILE* fp = fopen( szFile, "r+" );

	if( fp == NULL )
		throw 1;

	// Get file size
	fseek( fp, 0, SEEK_END );
	int file_size = ftell( fp );
	fseek( fp, 0, SEEK_SET );

	if( file_size <= 0 )
		throw 2;

	// Create buffer
	char* buf = new char[file_size+1];

	// Read file
	fread( buf, file_size, 1, fp );
	buf[file_size] = 0;

	// Keep script
	std::string strScript;
	strScript = const_cast< const char* >( buf );

	// Free buffer
	delete buf;

	// Close file
	fclose( fp );

	return strScript;
}

////////////////////////////////////////////
// Translate a command
void ScriptFile::TranslateScript( std::string strCmd )
{
	// Comments
	COMMENT
	{
		if( boTraceExecution )
			TraceExecution( "Commented line." );
	}
	// Enable report
	CHECK_COMMAND( "REPORT ON" )
	{
		InitTrace();
	}
	// Disable report
	CHECK_COMMAND( "REPORT OFF" )
	{
		if( boTraceExecution )
			TraceExecution( "Report disabled." );

		boTraceExecution = false;
	}
	// Does it stop as soon as an error occurs?
	CHECK_COMMAND( "SAFE MODE" )
	{
		boSafeMode = true;

		if( boTraceExecution )
			TraceExecution( "Safe mode activated." );
	}
	// Normal execution
	CHECK_COMMAND( "NORMAL MODE" )
	{
		boSafeMode = false;

		if( boTraceExecution )
			TraceExecution( "Normal mode activated." );
	}
	// Defines which char must be used
	CHECK_COMMAND( "USE CHAR" )
	{
		// Get character name
		strGodCharacter = strCmd.erase( 0, strlen( "USE CHAR " ) );

		// Check if this character is online
		if( CPlayerManager::GetCharacter( strGodCharacter.c_str() ) != NULL )
		{
			if( boTraceExecution )
				TraceExecution( "Character %s will be considered as god.", strGodCharacter.c_str() );
		}
		else
		{
			if( boTraceExecution )
				TraceExecution( "Character %s isn't online.", strGodCharacter.c_str() );
			if( boSafeMode )
				boStopScriptExecution = true;

			strGodCharacter = "";
		}
	}
	// Wait X seconds before continue execution
	CHECK_COMMAND( "SLEEP" )
	{
		// Get the delay
		std::string strLength = strCmd.erase( 0, strlen( "SLEEP " ) );
		int delay = atoi( strLength.c_str() );

		// Only if the delay is valid...
		if( delay > 0 )
		{
			if( boTraceExecution )
				TraceExecution( "Waiting %d seconds...", delay );

			Sleep( delay*1000 );
		}
		else
		{
			if( boTraceExecution )
				TraceExecution( "Weird delay! (%d seconds)", delay );
			if( boSafeMode )
				boStopScriptExecution = true;
		}
	}
	// Change loop delay
	CHECK_COMMAND( "SET LOOP" )
	{
		// Get new time
		std::string strLength = strCmd.erase( 0, strlen( "SET LOOP " ) );
		int delay = atoi( strLength.c_str() );

		// if new time is valid
		if( delay > 0 )
		{
			if( boTraceExecution )
				TraceExecution( "Loop delay has been set to %d seconds.", delay );

			theApp.dwScriptLoopLength = delay;
		}
		else
		{
			if( boTraceExecution )
				TraceExecution( "Invalid loop delay (%d seconds).", delay );
			if( boSafeMode )
				boStopScriptExecution = true;
		}

	}
	// Rename script to avoid to be executed another time
	CHECK_COMMAND( "DO NOT RENAME ME" )
	{
		boKeepScript = true;

		if( boTraceExecution )
			TraceExecution( "Script will be kept in the script directory." );
	}
	// Include a sub script
	CHECK_COMMAND( "INCLUDE" )
	{
		// Get script filename
		std::string strFileName = strCmd.erase( 0, strlen( "INCLUDE " ) );
		
		if( boTraceExecution )
			TraceExecution( "Include script %s.\r\n*****************************************************", strFileName.c_str() );

		// Create a new instance of a ScriptFile class to execute the sub script
		ScriptFile includedScript;
		int res = includedScript.RunScript( (char*) strFileName.c_str() );

		if( boTraceExecution )
			TraceExecution( "Script returned code %d.\r\n******************************************************", res );

		if( boSafeMode && res != 0 )
			boStopScriptExecution = true;
	}
	BASIC_COMMAND
	{
		bool boTemporaryUser = false;
		Players* user;

		// If a character has been assigned, get it
		if( strGodCharacter.size() > 0 )
		{
			user = CPlayerManager::GetCharacter( strGodCharacter.c_str() );

			// If user cannot be fetched
			if( user == NULL )
			{
				if( boTraceExecution )
					TraceExecution( "Character %s cannot be found. Sysop command cannot be translated.", strGodCharacter.c_str() );

				if( boSafeMode )
					boStopScriptExecution = true;

				return;
			}
		}
		else
		{
			// Else build a temporary character flagged
			user = new Players;
			boTemporaryUser = true;
			
			user->self->SetName( "OfflineScript" );
			user->SetAccount( "OfflineScript" );
			user->SetGodMode( TRUE );
			user->SetGodFlags( GOD_CAN_ZAP | GOD_CAN_LOCKOUT_USER |
						   GOD_CAN_SQUELCH | GOD_CAN_REMOVE_SHOUTS |
						   GOD_CAN_SUMMON_MONSTERS | GOD_CAN_SUMMON_ITEMS |
						   GOD_CAN_SET_USER_FLAG | GOD_CAN_EDIT_USER_STAT | GOD_CAN_EDIT_USER_HP | GOD_CAN_EDIT_USER_MANA_FAITH | GOD_CAN_EDIT_USER_XP_LEVEL | GOD_CAN_EDIT_USER_NAME | GOD_CAN_EDIT_USER_APPEARANCE_CORPSE | GOD_CAN_EDIT_USER_SPELLS | GOD_CAN_EDIT_USER_SKILLS | GOD_CAN_EDIT_USER_BACKPACK |
						   GOD_CAN_VIEW_USER_STAT | GOD_CAN_VIEW_USER_BACKPACK | GOD_CAN_VIEW_USER_SPELLS | GOD_CAN_VIEW_USER_SKILLS | GOD_CAN_VIEW_USER_APPEARANCE_CORPSE |
						   GOD_CAN_SLAY_USER | GOD_CAN_TELEPORT_USER | GOD_CAN_TELEPORT |
						   GOD_CAN_COPY_USER | GOD_CAN_EMULATE_MONSTER | GOD_CAN_SHUTDOWN |
						   GOD_CAN_SEE_ACCOUNTS | GOD_CAN_GIVE_GOD_FLAGS | GOD_CAN_EMULATE_SYSTEM | GOD_CHAT_MASTER );
		}

		// Parse sysop command
		int boSuccess = SysopCmd::VerifySysopCommand( user, strCmd.c_str() );

		// If Sysop command failed
		if( !boSuccess )
		{
			if( boTraceExecution )
				TraceExecution( "Sysop command \"%s\" failed.", strCmd.c_str() );

			if( boSafeMode )
				boStopScriptExecution = true;
		}
		else
		{
			if( boTraceExecution )
				TraceExecution( "Sysop command \"%s\" succeed.", strCmd.c_str() );
		}

		// If this is a temporary user, free it
		if( boTemporaryUser )
			delete user;
	}
}

////////////////////////////////////////////
// Write a debug file
void ScriptFile::TraceExecution( const char* msg, ... )
{	
	va_list	args;
	va_start( args, msg );

	char buf[512];
	char date[64];

	_vsnprintf( buf, sizeof( buf ), msg, args );
	strcat( buf, "\r\n" );

	SYSTEMTIME sysTime;
	GetLocalTime( &sysTime );

	// Format date/time
	sprintf( date, "%04d/%02d/%02d %02d:%02d:%02d,", 
		sysTime.wYear, 
        sysTime.wMonth,
        sysTime.wDay,
        sysTime.wHour, 
        sysTime.wMinute,
        sysTime.wSecond  );

	// Open report file
	FILE* fp = fopen( "Script\\report.txt", "a" );
	if( fp != NULL )
	{
		// Write trace
		fwrite( date, strlen( date ), 1, fp );
		fwrite( buf, strlen( buf ), 1, fp );
		fclose( fp );
	}
	else
	{
		// Stop tracing if there's no way to write report
		boTraceExecution = false;
	}

	va_end( args );
}

////////////////////////////////////////////
// Init debug file
void ScriptFile::InitTrace( void )
{
	boTraceExecution = true;

	TraceExecution( "----- Script-Running -----" );
	TraceExecution( "Report enabled." );
}
