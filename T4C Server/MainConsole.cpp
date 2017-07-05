// MainConsole.cpp: implementation of the MainConsole class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "MainConsole.h"
#include "TFC_MAIN.h"
#include "TFCTimers.h"
#include "Character.h"
#include "Clans.h"
#include "Skills.h"
#include "ODBCMage.h"
#include "DynObjManager.h"
#include "SpellEffectManager.h"
#include "SpellMessageHandler.h"
#include "IntlText.h"
#include "PacketManager.h"
#include "PlayerManager.h"
#include "DeadlockDetector.h"
#include "TFCMessagesHandler.h"
#include "Shutdown.h"
#include "NPC thread.h"
#include <stdio.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
//#include "ScriptFile.h"
#include "WeatherEffect.h"


using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern TFC_MAIN *TFCServer;
extern Clans *CreatureClans;
extern CTFCServerApp theApp;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

class AsyncNamedPipeServer{
public:
    AsyncNamedPipeServer( string bsThePipeName );
    ~AsyncNamedPipeServer();

    enum PipeStatus{
        StatusRead,
        StatusWrite,
        StatusConnect,
        StatusIoPending
    };

    bool Create( void );
    void Destroy( void );

    void Reset( void ){
        Disconnect();
        Destroy();
        Create();
    }

    PipeStatus GetPendingIo( void );

    bool Read      ( void );
    void Write     ( void );
    void Connect   ( void );
    void Disconnect( void );

    void   SetMessage( string bsMessage );
    string GetMessage( void );

private:

    string      bsPipeName;
    char        lpBuffer[ 4096 ];
    HANDLE      hPipe;
    OVERLAPPED  overLapped;
    PipeStatus  pendingPipeStatus;    
};

AsyncNamedPipeServer::AsyncNamedPipeServer( string bsThePipeName ) : 
    bsPipeName( bsThePipeName ),
    hPipe     ( INVALID_HANDLE_VALUE ),
    pendingPipeStatus( StatusIoPending )

{
    lpBuffer[ 0 ] = 0;
    memset( &overLapped, 0, sizeof( overLapped ) );    
}

AsyncNamedPipeServer::~AsyncNamedPipeServer( void ){    
    if( hPipe != INVALID_HANDLE_VALUE ){
        CloseHandle( hPipe );
    }
}

void AsyncNamedPipeServer::Destroy( void ){
    CloseHandle( hPipe );
    hPipe = INVALID_HANDLE_VALUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool AsyncNamedPipeServer::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Creates the named pipe server.
// 
// Return: bool, true if the named pipe server could be created.
//////////////////////////////////////////////////////////////////////////////////////////
{
    hPipe = CreateNamedPipe(
        bsPipeName.c_str(),
        PIPE_ACCESS_DUPLEX,// | FILE_FLAG_OVERLAPPED,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_NOWAIT,
        1,
        0,
        0,
        1000,
        NULL
    );

    if( hPipe == INVALID_HANDLE_VALUE ){
        printf( "\nCreate error=%u.", GetLastError() );
    }

    return( hPipe != INVALID_HANDLE_VALUE );
}

//////////////////////////////////////////////////////////////////////////////////////////
AsyncNamedPipeServer::PipeStatus AsyncNamedPipeServer::GetPendingIo( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the current state of the pending Io.
// 
// Return: PipeStatus, the pipe's current status.
//////////////////////////////////////////////////////////////////////////////////////////
{
    DWORD dwBytesTransfered = 0;
    if( hPipe != INVALID_HANDLE_VALUE && GetOverlappedResult( hPipe, &overLapped, &dwBytesTransfered, false ) ){
        return pendingPipeStatus;
    }else{
        return StatusIoPending;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
bool AsyncNamedPipeServer::Read ( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Issues an async reading. Return value fetched by GetMessage().
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( hPipe != INVALID_HANDLE_VALUE ){
        DWORD dwBytesRead = 0;

        pendingPipeStatus = StatusRead;
    
        if( ReadFile(
                hPipe,
                lpBuffer,
                4095,
                &dwBytesRead,
                NULL
            )
        ){
            return true;
        }
    }
    return false;
}
//////////////////////////////////////////////////////////////////////////////////////////
void AsyncNamedPipeServer::Write ( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Issues an async writing. It gets its data from SetMessage().
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( hPipe != INVALID_HANDLE_VALUE ){    
        pendingPipeStatus = StatusRead;
    
        DWORD dwBytesWritten = 0;

        WriteFile(
            hPipe,
            lpBuffer,
            strlen( lpBuffer ),
            &dwBytesWritten,
            &overLapped
        );
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void AsyncNamedPipeServer::Connect( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Waits for a pipe client to connect on the named pipe.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( hPipe != INVALID_HANDLE_VALUE ){
        pendingPipeStatus = StatusConnect;
    
        ConnectNamedPipe( 
            hPipe,
            &overLapped
        );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void AsyncNamedPipeServer::Disconnect( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Disconnects the current client from the pipe server.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( hPipe != INVALID_HANDLE_VALUE ){
        if( !DisconnectNamedPipe(
                hPipe
            )
            ){
            printf( "\nError %u disconnecting client pipe.", GetLastError() );

        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void AsyncNamedPipeServer::SetMessage
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets the current message to send on the next Write.
// 
(
 string bsMessage // The message.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    strcpy( lpBuffer, bsMessage.c_str() );
}
//////////////////////////////////////////////////////////////////////////////////////////
string AsyncNamedPipeServer::GetMessage( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Reads the message to get after the last Read.
// 
// Return: string, the message.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return lpBuffer;
}




MainConsole::MainConsole()
{

}

MainConsole::~MainConsole()
{

}

//////////////////////////////////////////////////////////////////////////////////////////
MainConsole &MainConsole::GetInstance( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the main console's sole instance.
//////////////////////////////////////////////////////////////////////////////////////////
{
    static MainConsole mInstance;

    return mInstance;
}

//////////////////////////////////////////////////////////////////////////////////////////
void MainConsole::TakeControl( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Takes control of the main console. Server is alive as long as the main console
//  is alive.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    const INT PipeBufferSize = 4096; // steph ajout de INT

    bool boControl = true;
	time_t tCalc=time(NULL);		
	tm *tmTime = localtime( &tCalc );

		printf( "\n-----                                                     " 
                "\nServer started on %s                                      "
			    "\nPress F5  to switch on rain.                              " // steph désactivation +fog
			    "\nPress F6  to switch off rain.                             " // steph désactivation +fog
                "\nPress F10 to shutdown server.                             "
                "\n-----                                                     "
                "\n                                                          ",asctime(tmTime)
    );

#ifdef _MONT4C
   BOOL fSuccess; 
   DWORD cbWritten, dwMode;
   LPTSTR lpszPipename = "\\\\.\\pipe\\T4CMain"; 

    printf( "\n" 
            "\n !!!Warning!!! This is a monitored server version!!!."
            "\n"
            "\n"
	);
      theApp.hPipeMain = CreateFile( 
         lpszPipename,   // pipe name 
         GENERIC_READ |  // read and write access 
         GENERIC_WRITE, 
         0,    // sharing 
         NULL,           // no security attributes
         OPEN_EXISTING,  // opens existing pipe 
         0,              // default attributes 
         NULL);          // no template file 
  
      if (theApp.hPipeMain == INVALID_HANDLE_VALUE) 
         printf( "\nFailed to open main pipe for monitor communication.\n" );


dwMode = PIPE_READMODE_MESSAGE; 
   fSuccess = SetNamedPipeHandleState( 
      theApp.hPipeMain,    // pipe handle 
      &dwMode,  // new pipe mode 
      NULL,     // don't set maximum bytes 
      NULL);    // don't set maximum time 
   if (!fSuccess) 
      printf("\nFailed to SetNamedPipeHandleState\n"); 


TCHAR lpvMessage[30];
//_stprintf(lpvMessage, _T("Message\r\n") );
wsprintf(lpvMessage, "Un message du serveur" );

	   fSuccess = WriteFile( 
		  theApp.hPipeMain,                  // pipe handle 
		  lpvMessage,             // message 
		  strlen(lpvMessage)+1, // message length 
		  &cbWritten,             // bytes written 
		  NULL);                  // not overlapped 
	   if (! fSuccess) 
		  printf("Write Pipe Failed! %u\n",cbWritten); 

		// print header
		SYSTEMTIME sysTime; 
		GetLocalTime(&sysTime);

		// Output: Date Time APP_TITLE EXCEPTION
		wsprintf(lpvMessage, _T("%d/%d/%d %02d:%02d:%02d Start\n"), 
			sysTime.wMonth,sysTime.wDay,sysTime.wYear, sysTime.wHour,
			sysTime.wMinute,sysTime.wSecond);
		WriteFile(theApp.hPipeMain, lpvMessage , strlen(lpvMessage)+1, &cbWritten, NULL);

#endif //_MONT4C

    AsyncNamedPipeServer pipeServer( "\\\\.\\pipe\\T4CServerMainConsole" );

    if( !pipeServer.Create() ){        
        _LOG_DEBUG
            LOG_CRIT_ERRORS,
            "Failed to open named pipe for inter-server communication. Error %u.",
            GetLastError()
        LOG_
        
        printf( "\nFailed to open named pipe for inter-server communication." );
    }

    // While we control the main console.
    while( boControl ){
        // If keyboard was hit.
        if( kbhit() ){
            // Get keyboard character.
            char ch = getch();

            TRACE( "\nKey %u (%c) got pressed.", ch, ch );
            
            // If the character is an extended keyboard character.
            if( ch <= 0 ){
                // Get extended code.
                ch = getch();

                TRACE( " - extended key %u (%c).", ch, ch );

                switch( ch ){
                // F10
                case 68:
                    printf( "Press F10 again twice to confirm server shutdown." );
                    if( getch() == 0 && getch() == 68 && getch() == 0 && getch() == 68 ){
#ifdef _MONT4C
	WriteFile(theApp.hPipeMain,"#Stop ",6,&cbWritten,NULL); 
#endif //_MONT4C    
                        boControl = false;
                    }else{
                        printf( " (canceled)\n" );
                    }
                    break;
                case 63:
                    printf( "\r\nPress F5 again twice to switch on Rain." ); // steph désactivation +Fog
                    if( getch() == 0 && getch() == 63 && getch() == 0 && getch() == 63 ){
                        printf( " Rain switched on.\n" ); // steph désactivation +Fog
						WorldPos wlPos = { 0, 0, 0 }; // BLBLBL
						Broadcast::BCWeatherMsg( wlPos, 0, WEATHER_RAIN, true ); // BLBLBL
						Broadcast::BCWeatherMsg( wlPos, 0, WEATHER_FOG, false ); // BLBLBL // steph false au lieu de true

                    }else{
                        printf( " (canceled)\n" );
                    }
                    break;
                case 64:
                    printf( "\r\nPress F6 again twice to switch off Rain." ); // steph désactivation +Fog
                    if( getch() == 0 && getch() == 64 && getch() == 0 && getch() == 64 ){
                        printf( " Rain switched off.\n" ); // steph désactivation +Fog
						WorldPos wlPos = { 0, 0, 0 }; // BLBLBL
						Broadcast::BCWeatherMsg( wlPos, 0, WEATHER_RAIN, false ); // BLBLBL
						Broadcast::BCWeatherMsg( wlPos, 0, WEATHER_FOG, false ); // BLBLBL

                    }else{
                        printf( " (canceled)\n" );
                    }
                    break;
/*				case 66:
					printf( "\r\nPress F8 again twice to run script." );
					if( getch() == 0 && getch() == 66 && getch() == 0 && getch() == 66 )
					{
						printf( " Running script..." );

						if( ScriptFile::GetInstance().RunScript( "Script\\script.txt" ) == 0 )
							printf( " Script correctly runned.\n" );
						else
							printf( " Script not found.\n" );
					}
					else
					{
						printf( " (canceled)\n" );
					}
					break;*/
/*#ifdef MEMORY_LOGGING
                case 64:
                    printf( "\r\nStarted memory logging." );
                    MemManager::GetInstance()->Start();
                    break;
                case 65:
                    printf( "\r\nStopping memory logging..." );
                    MemManager::GetInstance()->Stop();
                    printf( "\r\nDone!" );
                    break;
#endif*/

                };
            };
        }


        if( pipeServer.Read( ) ){
            // If a shutdown message was issued.
            const char ShutdownMsg[] = "Yo server dude, shutdown in ";            
            if( pipeServer.GetMessage().find( ShutdownMsg ) == 0 ){
                // Get the integer value residing after this string in the c_str.
                int nMin = atoi( &( pipeServer.GetMessage().c_str()[ sizeof( ShutdownMsg ) - 1 ] ) );                
                
                // If the minutes are greater than 30
                if( nMin > 30 || nMin < 0 ){
                    printf( "Shutdown canceled!\n" );
                    // This means cancel shutdown.
                    CShutdown::CancelShutdown( true );
                }else{
                    if( nMin > 0 ){
                        printf( "Shutdown issued by T4CShell, shutting down in %u minute", nMin );
                        
                        // Singular/plural twist ;-)
                        if( nMin > 1 ){
                            printf( "s.\n" );
                        }else{
                            printf( ".\n" );
                        }
                    }else{
                        printf( "Shutdown issued by T4CShell, shutting down NOW!\n" );
                    }
                    // Otherwise issue a shutdown equal to the requested minutes.
                    CShutdown::CreateShutdown( nMin );
                    CShutdown::StartShutdown();
                }
            }

            pipeServer.Disconnect();
            pipeServer.Destroy();
            pipeServer.Create();
        }

        Sleep( 25 );
    }

    printf( "\nShutting down NOW!\n" );

    // When main console closes, call shutdown
    CShutdown::CreateShutdown();
    CShutdown::StartShutdown();

    // Wait 3 minutes
	Sleep( 180000 );
}

//////////////////////////////////////////////////////////////////////////////////////////
void MainConsole::Terminate( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  This function shuts down the main console and therefore, the whole server.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	try{
        TFCMessagesHandler::Destroy();

        // Destroy the player and packet managers
        CPlayerManager::Destroy();
        
//        DebugLockManager::Instance().LogLockQueue();

        END_LOG;        

		// Tell each unit that the server is terminating
		Unit::SendGlobalUnitMessage( MSG_OnServerTermination, NULL, NULL, NULL );
		
		BYTE bTerminationData = '@';
				
		SYSTEM_INFO s_siSystem;
		GetSystemInfo(&s_siSystem);

		// Delete dynamically loaded items
		DynObjManager::Destroy();

		// Unregister the units
		Unit::UnRegisterUnits( );

        OleUninitialize();

		TFCTimerManager::DestroyTimers();
        

		// Remove ODBC
		Players::DestroyODBC( );
		Character::DestroyODBC( );

		delete TFCServer;
		delete [] CreatureClans;

		// Destroy all effects.
		UnitEffectManager::Destroy();
        SpellEffectManager::Destroy(); 
        SpellMessageHandler::Destroy();

		// Destroy the object timers.
		ObjectTimer::Destroy( );

		// Destroy the skills.
		Skills::Destroy();

        // Disable deadlock checking.
        CDeadlockDetector::Destroy();

	    // Catches anything and lets it go.
	}catch(...){
		_LOG_DEBUG LOG_CRIT_ERRORS, "Crashed in MainConsole::Terminate" LOG_
	}

	try{
        exit( NORMAL_SERVER_EXIT );
    }catch(...){
        TerminateProcess( GetCurrentProcess(), TERMINATE_FAIL_EXIT );
    }


}

