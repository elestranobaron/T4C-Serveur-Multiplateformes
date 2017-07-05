// SysopCmd.cpp: implementation of the SysopCmd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "SysopCmd.h"
#include "TFC_MAIN.h"
#include "TFCInit.h"
#include "TFCPacket.h"
#include "TFC ServerDlg.h"
#include "RegKeyHandler.h"
#include "PlayerManager.h"
#include "AutoConfig.h"
#include "Shutdown.h"
#include "PacketManager.h"
#include "CommCenter.h"
#include "Format.h"
#include "AsyncFuncQueue.h"
#include "SpellMessageHandler.h"
#include "NPC Thread.h"
//#include "Rain.h"
//#include "Snow.h"
#include "WeatherEffect.h"
#include "Version.h"
#include <cmath>
#include "ThreadMonitor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define CREATE_MESSAGE		{\
			TFCPacket sending;\
			CString csText;\
			DWORD dwColor = RGB( 0, 100, 255 );\
			csText.Format

#define SEND_MESSAGE	;\
			sending << (RQ_SIZE)RQ_ServerMessage;\
			sending << (short)30;\
			sending << (short)3;\
			sending << (CString &)csText;\
			sending << (long) dwColor;\
			user->Lock();\
			user->self->SendPlayerMessage( sending );\
			user->Unlock();\
}

CLock SysopCmd::csSysLock;

static SysopCmd sysCmd;
extern CTFCServerApp theApp;

namespace{
    struct SetNameData{
        sockaddr_in sockGod;
        sockaddr_in sockTarget;
        string csNewName;
    };


    void AsyncSetName( LPVOID lpData );
	CString GetOPFlagNameByShortcut(CString csFlagShortCut);

    struct TeleportLocation{
        WorldPos wlPos;
        std::string Id;
    };
    list< TeleportLocation > locationList;


    //////////////////////////////////////////////////////////////////////////////////////////
    void SysopCfgUpdate( void )
    //////////////////////////////////////////////////////////////////////////////////////////
    //  A registry update occured.
    // 
    //////////////////////////////////////////////////////////////////////////////////////////
    {
        RegKeyHandler regKey;
        regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY CHARACTER_KEY );
        
        locationList.clear();
        TFormat format;

        int i = 1;
        std::string locationId = regKey.GetProfileString( "TeleportLocation1", "$NULL$" );
        while( locationId != "$NULL$" ){
            TeleportLocation location;
            location.Id = locationId;
            
            location.wlPos.X = regKey.GetProfileInt( 
                format( "TeleportLocation%uX", i ), 
                0 
            );

            location.wlPos.Y = regKey.GetProfileInt( 
                format( "TeleportLocation%uY", i ), 
                0 
            );
            
            location.wlPos.world = regKey.GetProfileInt( 
                format( "TeleportLocation%uW", i ), 
                0 
            );

            locationList.push_back( location );

            i++;
            locationId = regKey.GetProfileString( 
                format( "TeleportLocation%u", i ), 
                "$NULL$" 
            );
        }
    }
};

//////////////////////////////////////////////////////////////////////////////////////////
SysopCmd::SysopCmd( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Startup function
// 
// Return: 
//////////////////////////////////////////////////////////////////////////////////////////
{    
}

// Destructor ////////////////////////////////////////////////////////////////////////////
 SysopCmd::~SysopCmd( void )
//////////////////////////////////////////////////////////////////////////////////////////
// End func
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
//	DeleteCriticalSection( &csSysLock );
}

//////////////////////////////////////////////////////////////////////////////////////////
void SysopCmd::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Creates the sysop module
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoConfig::AddRegUpdateCallback( SysopCfgUpdate );
    SysopCfgUpdate();
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL SysopCmd::GetParameters
//////////////////////////////////////////////////////////////////////////////////////////
// Processes the command line and returns the parameters found
// 
(
 LPCTSTR lpszCommandTemplate,
 CString csCommandLine,
 CString *lpFoundParameters
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	struct TOKEN{
		int nTokenStart;
		int nTokenEnd;
	};
    	
	BOOL boError = FALSE;
	int nCurrentPos;
	int nLastPos = -1;
	int i;
	int nNbParams = 0;
	int nCommandTemplateSize = strlen( lpszCommandTemplate );
	TOKEN *lpTokens;

    // Replace spaces with ASC(27) in strings surrounded by "
    for( i = 0; i < csCommandLine.GetLength(); i++ ){
        if( csCommandLine[ i ] == '\"' ){
            csCommandLine.SetAt( i, ' ' );
            i++;
            while( i < csCommandLine.GetLength() && csCommandLine[ i ] != '\"' ){
                if( csCommandLine[ i ] == ' ' ){
                    csCommandLine.SetAt( i, 27 );
                }

                i++;
            }
            // If the last char is a "
            if( i < csCommandLine.GetLength() ){
                csCommandLine.SetAt( i, ' ' );
            }
        }
    }

	CString csSearchString( csCommandLine );

    csSearchString.MakeUpper();

	// Copy the command template into tokens for processing.
	char *lpszSavedToken;
	char *lpszToken = new char[ nCommandTemplateSize + 2 ];
	lpszSavedToken = lpszToken;	// Save address of token for deletion.
	memcpy( lpszToken, lpszCommandTemplate, nCommandTemplateSize );
	// Replace the trailing \0 with a Ø (char 216) to have a last token.
	lpszToken[ nCommandTemplateSize ] = 'Ø';
	lpszToken[ nCommandTemplateSize + 1 ] = 0;
			
	int nStrLen = csCommandLine.GetLength();
	
	// Finds the number of $ parameters in the string.
	for( i = 0; i < nCommandTemplateSize; i++ ){
		if( lpszToken[ i ] == '$' ){
			nNbParams++;
		}
	}

	lpTokens = new TOKEN[ nNbParams + 1 ];

	//COMMAND( "ADD FLAG $ VALUE $ TO $" )
	
	int j;
	i = 0;
    int findStart = 0;
	// Find each sentence parts	
	lpszToken = strtok( lpszToken, "$" );
	while( lpszToken != NULL && !boError ){
		nCurrentPos = csSearchString.Find( lpszToken, findStart );
		
		// If this newly found token is after the last one found.
		if( nCurrentPos > nLastPos ){
            int tokenLen = strlen( lpszToken );
						
			lpTokens[ i ].nTokenStart = nCurrentPos;
			lpTokens[ i ].nTokenEnd   = nCurrentPos + strlen( lpszToken );

			TRACE( "\r\nStart=%u, End=%u", lpTokens[ i ].nTokenStart, lpTokens[ i ].nTokenEnd );
			
            // If the token is a single character
            if( tokenLen == 1 ){
    			// Remove all of the successive tokens
	    		j = lpTokens[ i ].nTokenStart;
                while( j < lpTokens[ i ].nTokenEnd ||
                      ( j < nStrLen && csSearchString[ j ] == lpszToken[ 0 ] ) ){
			    	csSearchString.SetAt( j, '\r' );
                    j++;
			    }
                findStart = j;
            }else{
                // Otherwise only replace the token.
                for( j = lpTokens[ i ].nTokenStart; j < lpTokens[ i ].nTokenEnd; j++ ){
                    csSearchString.SetAt( j, '\r' );
                }
                findStart = j;
            }
						
			// Find next token
			lpszToken = strtok( NULL, "$" );
			i++;

			nLastPos = nCurrentPos;
		}else{
			boError = TRUE;
		}
	}

	if( lpTokens[ 0 ].nTokenStart != 0 ){
		boError = TRUE;
	}

	if( !boError ){
		

		// Scroll through the found parameters
		i = 0;
		for( i = 0; i < nNbParams; i++ ){
			lpTokens[ i ].nTokenEnd;
			
			// Add parameter to list.
			lpFoundParameters[ i ] = csCommandLine.Mid( lpTokens[ i ].nTokenEnd, lpTokens[ i+1 ].nTokenStart - lpTokens[ i ].nTokenEnd );			 

            int q;
            for( q = 0; q < lpFoundParameters[ i ].GetLength(); q++ ){
                if( lpFoundParameters[ i ].GetAt( q ) == 27 ){
                    lpFoundParameters[ i ].SetAt( q, ' ' );
                }
            }

			// Remove white spaces
			lpFoundParameters[ i ].TrimRight();
			lpFoundParameters[ i ].TrimLeft();
            
			if( lpFoundParameters[ i ].IsEmpty() ){
				boError = TRUE;
            }else{


            }
		}
	}

	delete lpTokens;
	delete lpszSavedToken;

	return !boError;
}


//////////////////////////////////////////////////////////////////////////////////////////
BOOL SysopCmd::GetParametersForNPC
//////////////////////////////////////////////////////////////////////////////////////////
// Processes the command line and returns the parameters found
// 
(
 LPCTSTR lpszCommandTemplate,
 CString csCommandLine,
 CString *lpFoundParameters
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	struct TOKEN{
		int nTokenStart;
		int nTokenEnd;
	};
    	
	BOOL boError = FALSE;
	int nCurrentPos;
	int nLastPos = -1;
	int i;
	int nNbParams = 0;
	int nCommandTemplateSize = strlen( lpszCommandTemplate );
	TOKEN *lpTokens;

    // Replace spaces with ASC(27) in strings surrounded by "
    for( i = 0; i < csCommandLine.GetLength(); i++ ){
        if( csCommandLine[ i ] == '\"' ){
            csCommandLine.SetAt( i, ' ' );
            i++;
            while( i < csCommandLine.GetLength() && csCommandLine[ i ] != '\"' ){
                if( csCommandLine[ i ] == ' ' ){
                    csCommandLine.SetAt( i, 27 );
                }

                i++;
            }
            // If the last char is a "
            if( i < csCommandLine.GetLength() ){
                csCommandLine.SetAt( i, ' ' );
            }
        }
    }

	CString csSearchString( csCommandLine );

    csSearchString.MakeUpper();

	// Copy the command template into tokens for processing.
	char *lpszSavedToken;
	char *lpszToken = new char[ nCommandTemplateSize + 2 ];
	lpszSavedToken = lpszToken;	// Save address of token for deletion.
	memcpy( lpszToken, lpszCommandTemplate, nCommandTemplateSize );
	// Replace the trailing \0 with a Ø (char 216) to have a last token.
	lpszToken[ nCommandTemplateSize ] = '.';
	lpszToken[ nCommandTemplateSize + 1 ] = 0;
			
	int nStrLen = csCommandLine.GetLength();
	
	// Finds the number of $ parameters in the string.
	for( i = 0; i < nCommandTemplateSize; i++ ){
		if( lpszToken[ i ] == '$' ){
			nNbParams++;
		}
	}

	lpTokens = new TOKEN[ nNbParams + 1 ];

	//COMMAND( "ADD FLAG $ VALUE $ TO $" )
	
	int j;
	i = 0;
    int findStart = 0;
	// Find each sentence parts	
	lpszToken = strtok( lpszToken, "$" );
	while( lpszToken != NULL && !boError ){
		nCurrentPos = csSearchString.Find( lpszToken, findStart );
		
		// If this newly found token is after the last one found.
		if( nCurrentPos > nLastPos ){
            int tokenLen = strlen( lpszToken );
						
			lpTokens[ i ].nTokenStart = nCurrentPos;
			lpTokens[ i ].nTokenEnd   = nCurrentPos + strlen( lpszToken );

			TRACE( "\r\nStart=%u, End=%u", lpTokens[ i ].nTokenStart, lpTokens[ i ].nTokenEnd );
			
            // If the token is a single character
            if( tokenLen == 1 ){
    			// Remove all of the successive tokens
	    		j = lpTokens[ i ].nTokenStart;
                while( j < lpTokens[ i ].nTokenEnd ||
                      ( j < nStrLen && csSearchString[ j ] == lpszToken[ 0 ] ) ){
			    	csSearchString.SetAt( j, '\r' );
                    j++;
			    }
                findStart = j;
            }else{
                // Otherwise only replace the token.
                for( j = lpTokens[ i ].nTokenStart; j < lpTokens[ i ].nTokenEnd; j++ ){
                    csSearchString.SetAt( j, '\r' );
                }
                findStart = j;
            }
						
			// Find next token
			lpszToken = strtok( NULL, "$" );
			i++;

			nLastPos = nCurrentPos;
		}else{
			boError = TRUE;
		}
	}

	if( lpTokens[ 0 ].nTokenStart != 0 ){
		boError = TRUE;
	}

	if( !boError ){
		

		// Scroll through the found parameters
		i = 0;
		for( i = 0; i < nNbParams; i++ ){
			lpTokens[ i ].nTokenEnd;
			
			// Add parameter to list.
			lpFoundParameters[ i ] = csCommandLine.Mid( lpTokens[ i ].nTokenEnd, lpTokens[ i+1 ].nTokenStart - lpTokens[ i ].nTokenEnd );			 

            int q;
            for( q = 0; q < lpFoundParameters[ i ].GetLength(); q++ ){
                if( lpFoundParameters[ i ].GetAt( q ) == 27 ){
                    lpFoundParameters[ i ].SetAt( q, ' ' );
                }
            }

			// Remove white spaces
			lpFoundParameters[ i ].TrimRight();
			lpFoundParameters[ i ].TrimLeft();
            
			if( lpFoundParameters[ i ].IsEmpty() ){
				boError = TRUE;
            }else{


            }
		}
	}

	delete lpTokens;
	delete lpszSavedToken;

	return !boError;
}

//////////////////////////////////////////////////////////////////////////////////////////
Players *SysopCmd::FindCharacter
//////////////////////////////////////////////////////////////////////////////////////////
// Finds the players structure corresponding to this name
// 
(
 CString csName // The name to search for.
)
// Return: Players, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    return CPlayerManager::GetCharacter( csName );
}

#define FIRST_COMMAND( __str, __god ) if( user->GetGodFlags() & __god && GetParameters( __str, csCommand, csParams ) != FALSE ){ boFound = TRUE;
#define COMMAND( __str, __god ) }else if( user->GetGodFlags() & __god && GetParameters( __str, csCommand, csParams ) != FALSE ){ boFound = TRUE;
#define END_COMMAND }
#define PARAM( __num ) ((LPCTSTR)csParams[ __num ])


#define SUPER_USER (stricmp( \
                (LPCTSTR)target->GetFullAccountName(), \
                CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str() \
            ) == 0)


//////////////////////////////////////////////////////////////////////////////////////////
DWORD SafeMinus
//////////////////////////////////////////////////////////////////////////////////////////
//  Substract the newvalue from the original value. Makes sure that if the variable
// underflows, that it stays at 0.
(
 DWORD original,
 DWORD newval 
)
// Return: DWORD, the result.
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( newval > original ){
        newval = 0;
    }else{
        newval = original - newval;
    }
    return newval;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL SysopCmd::VerifySysopCommand
//////////////////////////////////////////////////////////////////////////////////////////
// Checks the sysop command.
// 
(
 Players *user,		// The god
 CString csCommand	// The command-line
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	csSysLock.Lock();

    bool success = false;

	BOOL boFound = FALSE;
	// Max of 5 parameters.
	CString csParams[ 5 ];
	
	csCommand.TrimRight();
	csCommand.TrimLeft();
	//csCommand.MakeUpper();
	csCommand += 'Ø'; // Add command terminator (char 216)

	TRACE( "Command line--%s--", (LPCTSTR)csCommand );

	TemplateList< SQL_REQUEST > *lptlSQLRequests = new TemplateList< SQL_REQUEST >;//BLBLBL pour pouvoir logguer dans la base les commandes de moderation


    //////////////////////////////////////////////////////////////////////////////////////////
	// God teleportation. Teleport to the n'th found NPC 	
    FIRST_COMMAND( "TELEPORT TO NPC $,$", GOD_CAN_TELEPORT )
        NPCMain &npcs = NPCMain::GetInstance();
        DWORD order = atoi( PARAM( 1 ) );
        Creatures *npc = npcs.GetNPC( PARAM( 0 ), order, user->self->GetLang() );
        if( npc != NULL ){
            WorldPos wlPos = npc->GetWL();
			if( !user->self->Teleport( wlPos, 0 ) ){
				CREATE_MESSAGE( "The teleport destination is invalid." );
				SEND_MESSAGE;		
			}else{
                success = true;
			}
        }else{
            CREATE_MESSAGE( "NPC not found" );
            SEND_MESSAGE;
        }	
	//////////////////////////////////////////////////////////////////////////////////////////
	// Allow GM to use GM commands	
	COMMAND( "GM $", GOD_CAN_ZAP )//BLBLBL GOD_CAN_TELEPORT changed into GOD_CAN_ZAP // steph GM au lieu de AUTHENTIFICATION
		RegKeyHandler regKey; 

        if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY GEN_CFG_KEY ) )
		{
			// Get the key
			CString csKey;
			csKey = regKey.GetProfileString( "GM_KEY", "" );

			if( csKey.IsEmpty() )
			{
				user->self->boAuthGM = true;

				_LOG_GAMEOP
					LOG_CRIT_ERRORS,
					"God %s (%s) has been authentified by the system!",
					(LPCTSTR)user->self->GetTrueName(),
					(LPCTSTR)user->GetFullAccountName()						
				LOG_

				CREATE_MESSAGE( "Game Master commands enabled." );				
				dwColor = RGB( 0, 255, 0 );
				SEND_MESSAGE
			}
			else
			{
				if( strcmp( (LPCTSTR)csKey, PARAM( 0 ) ) == 0 )
				{
					user->self->boAuthGM = true;

					CREATE_MESSAGE( "Game Master commands enabled." );
					dwColor = RGB( 0, 255, 0 );
					SEND_MESSAGE
				}
				else
				{
					/* user->Lock();
					user->dwKickoutTime = 20 SECONDS TDELAY;
					user->Unlock(); */ // steph désactivation


					//////////////////////////////////////////////////////////////////////////////////////////
					// steph ajout
					//////////////////////////////////////////////////////////////////////////////////////////
					CREATE_MESSAGE( "Game Master commands not enabled." );
					dwColor = RGB( 255, 0, 0);
					SEND_MESSAGE



					_LOG_GAMEOP
						LOG_CRIT_ERRORS,
						"God %s (%s) entered wrong authentification key!",
						(LPCTSTR)user->self->GetTrueName(),
						(LPCTSTR)user->GetFullAccountName()						
					LOG_
				}
			}			
		}
		else
		{
			CREATE_MESSAGE( "Unable to authentificate you. Register do not respond.." );
			dwColor = RGB( 255, 0, 0 );
			SEND_MESSAGE
		}
	//////////////////////////////////////////////////////////////////////////////////////////
	// Show chest
	COMMAND( "SHOW CHEST", GOD_CAN_VIEW_USER_BACKPACK )
		user->self->ShowChest();

	COMMAND( "SAVEME", GOD_DEVELOPPER )
		user->self->SaveCharacter();
		success = true;

	COMMAND( "VIEW SERVER BUILD", GOD_DEVELOPPER )
		CREATE_MESSAGE( Version::sBuildStamp.c_str() );
		SEND_MESSAGE;
		success = true;
	
	COMMAND( "GET INFO UNITREF $", GOD_DEVELOPPER )
	{
		char name[1024];
		Unit::GetNameFromID(atoi(PARAM(0)),name);
		CREATE_MESSAGE("Name: %s", name);
		SEND_MESSAGE;
	}
	
	COMMAND( "LIST THREADS", GOD_DEVELOPPER )
		CThreadMonitor::ThreadList listOfThreads;
		CThreadMonitor::GetInstance().GetRunningThreadsList(listOfThreads);
		CThreadMonitor::ThreadListIterator i = listOfThreads.begin();
		CREATE_MESSAGE("Listing %u threads", listOfThreads.size()); SEND_MESSAGE;
		for (; i != listOfThreads.end(); ++i) {
			CREATE_MESSAGE("Thread ID: %u Name: %s", (*i).first, (*i).second.c_str());
			SEND_MESSAGE;
		}
		CREATE_MESSAGE("End."); SEND_MESSAGE;
	
	COMMAND( "RUNBF TARGET $, $", GOD_DEVELOPPER )
		{
			BoostFormula bf;
			if ( bf.SetFormula( PARAM( 1 ) ) ) {
				Players *target = FindCharacter( PARAM( 0 ) );
				if( target != NULL ){
					CREATE_MESSAGE( "BoostFormula Result: %f", bf.GetBoost(user->self, target->self) );
					SEND_MESSAGE;
				} else {
					CREATE_MESSAGE( "Ooops! Character %s is not around, dude!", PARAM(0) );
					SEND_MESSAGE;
				}
			} else {
				CREATE_MESSAGE( "Error evaluating the formula" );
				SEND_MESSAGE;
			}
		}
	
	COMMAND( "RUNBF $", GOD_DEVELOPPER )
		{
			BoostFormula bf;
			if ( bf.SetFormula( PARAM( 0 ) ) ) {
				CREATE_MESSAGE( "BoostFormula Result: %f", bf.GetBoost(user->self) );
				SEND_MESSAGE;
			} else {
				CREATE_MESSAGE( "Error evaluating the formula" );
				SEND_MESSAGE;
			}
		}
	COMMAND( "RUNSF TARGET $, $", GOD_DEVELOPPER )
		{
			Players *target = FindCharacter( PARAM( 0 ) );
			if( target != NULL ){
				CREATE_MESSAGE( "StringFormula Result: %s", (LPCTSTR)BoostFormula::TranslateStringFormula( PARAM( 1 ), user->self, target->self ) );
				SEND_MESSAGE;
			} else {
				CREATE_MESSAGE( "Ooops! Character %s is not around, dude!", PARAM(0) );
				SEND_MESSAGE;
			}

		}
	COMMAND( "RUNSF $", GOD_DEVELOPPER )
		{
			CREATE_MESSAGE( "StringFormula Result: %s", (LPCTSTR)BoostFormula::TranslateStringFormula( PARAM( 0 ), user->self ) );
			SEND_MESSAGE;
		}
	//////////////////////////////////////////////////////////////////////////////////////////
	// God teleportation. Teleport to a NPC
    COMMAND( "TELEPORT TO NPC $", GOD_CAN_TELEPORT )
        NPCMain &npcs = NPCMain::GetInstance();
        Creatures *npc = npcs.GetNPC( PARAM( 0 ), 0, user->self->GetLang() );
        if( npc != NULL ){
            WorldPos wlPos = npc->GetWL();
			if( !user->self->Teleport( wlPos, 0 ) ){
				CREATE_MESSAGE( "The teleport destination is invalid." );
				SEND_MESSAGE;		
			}else{
                success = true;
			}
        }else{
            CREATE_MESSAGE( "NPC not found" );
            SEND_MESSAGE;
        }
    //////////////////////////////////////////////////////////////////////////////////////////
    // Teleports to a known location
    COMMAND( "TELEPORT TO LOC $", GOD_CAN_TELEPORT )
        bool success = false;
        list< TeleportLocation >::iterator i;
        // Find the location in the list
        for( i = locationList.begin(); i != locationList.end(); i++ ){
            if( stricmp( (*i).Id.c_str(), PARAM( 0 ) ) == 0 ){
			    // Teleport to this location.
                if( !user->self->Teleport( (*i).wlPos, 0 ) ){
				    CREATE_MESSAGE( "The teleport destination is invalid." );
				    SEND_MESSAGE;		
			    }else{
                    success = true;
			    }
                break;
            }
        }
        
        if( !success ){
            CREATE_MESSAGE( "Location not found." );
            SEND_MESSAGE;
        }
    //////////////////////////////////////////////////////////////////////////////////////////
	// God teleportation
	COMMAND( "TELEPORT TO $,$,$", GOD_CAN_TELEPORT )
		BOOL boInvalid = FALSE;
		
		WorldPos wlPos = { 0, 0, 0 };

		wlPos.X		= atoi( PARAM( 0 ) );
		wlPos.Y		= atoi( PARAM( 1 ) );
		wlPos.world = atoi( PARAM( 2 ) );

		if( wlPos.X == 0 || wlPos.Y == 0 ){
			boInvalid = TRUE;
		}else{
			if( !user->self->Teleport( wlPos, 0 ) ){
				boInvalid = TRUE;
			}			
		}

		if( boInvalid ){
			CREATE_MESSAGE( "Your teleport destination is invalid." );
			SEND_MESSAGE;
        }else{
            success = true;
        }

    //////////////////////////////////////////////////////////////////////////////////////////
    // Teleports besides the given user.
    COMMAND( "TELEPORT TO $", GOD_CAN_TELEPORT )
		Players *target;
			
		target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){			
			WorldPos wlPos = target->self->GetWL();
            wlPos.X--;

			if( !user->self->Teleport( wlPos, 0 ) ){
				CREATE_MESSAGE( "The teleport destination is invalid." );
				SEND_MESSAGE;		
            }else{
                success = true;   
            }

		}else{
			CREATE_MESSAGE( "User %s is not online", PARAM( 0 ) );
			SEND_MESSAGE;
		}
	//////////////////////////////////////////////////////////////////////////////////////////
	// Teleport a user to a specified destination
	COMMAND( "TELEPORT USER $ TO $,$,$", GOD_CAN_TELEPORT_USER )		
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to teleport user %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_

			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;
		}
		else
		{	
			Players *target;			
			target = FindCharacter( PARAM( 0 ) );

			if( target != NULL ){
				WorldPos wlPos = { 0, 0, 0 };
				WorldPos wlFrom = target->self->GetWL();

				wlPos.X		= atoi( PARAM( 1 ) );
				wlPos.Y		= atoi( PARAM( 2 ) );
				wlPos.world = atoi( PARAM( 3 ) );


				target->Lock();
				if( !target->self->Teleport( wlPos, 0 ) ){
					CREATE_MESSAGE( "The teleport destination is invalid." );
					SEND_MESSAGE;		
				}else{
					success = true;
					
					//BLBL SENDBACK GM command, we store coming from position :
					target->self->prevTeleportPos=wlFrom;

					_LOG_GAMEOP
						LOG_SYSOP, 
						"God %s (%s) teleported character %s (%s) from ( %u, %u, %u ) to ( %u, %u, %u )",
						(LPCTSTR)user->self->GetTrueName(),
						(LPCTSTR)user->GetFullAccountName(),
						(LPCTSTR)target->self->GetTrueName(),
						(LPCTSTR)target->GetFullAccountName(),
						wlFrom.X,
						wlFrom.Y,
						wlFrom.world,
						wlPos.X,
						wlPos.Y,
						wlPos.world
					LOG_
				}
				target->Unlock();

			}else{
				CREATE_MESSAGE( "User %s is not online", PARAM( 0 ) );
				SEND_MESSAGE;
			}
		}
	//////////////////////////////////////////////////////////////////////////////////////////
	// Teleport a user to god's side
	COMMAND( "TELEPORT USER $ TO ME", GOD_CAN_TELEPORT_USER )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to teleport user %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_

			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;
		}
		else
		{
			Players *target;
			

			target = FindCharacter( PARAM( 0 ) );

			if( target != NULL ){
				WorldPos wlPos = user->self->GetWL(); wlPos.X--;
				WorldPos wlFrom = target->self->GetWL();


				target->Lock();
				if( !target->self->Teleport( wlPos, 0 ) ){
					CREATE_MESSAGE( "The teleport destination is invalid." );
					SEND_MESSAGE;		
				}else{
					
					//BLBL SENDBACK GM command, we store coming from position :
					target->self->prevTeleportPos=wlFrom;
					
					success = true;

					_LOG_GAMEOP
						LOG_SYSOP, 
						"God %s (%s) teleported character %s (%s) from ( %u, %u, %u ) to ( %u, %u, %u )",
						(LPCTSTR)user->self->GetTrueName(),
						(LPCTSTR)user->GetFullAccountName(),
						(LPCTSTR)target->self->GetTrueName(),
						(LPCTSTR)target->GetFullAccountName(),
						wlFrom.X,
						wlFrom.Y,
						wlFrom.world,
						wlPos.X,
						wlPos.Y,
						wlPos.world
					LOG_
				}
				target->Unlock();

			}else{
				CREATE_MESSAGE( "User %s is not online", PARAM( 0 ) );
				SEND_MESSAGE;
			}
		}
	//////////////////////////////////////////////////////////////////////////////////////////
	// Teleport a user to god's side
	COMMAND( "SENDBACK USER $", GOD_CAN_TELEPORT_USER )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to teleport user %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_

			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;
		}
		else
		{
			Players *target;
			

			target = FindCharacter( PARAM( 0 ) );

			if( target != NULL ){
				WorldPos wlPos = target->self->prevTeleportPos; wlPos.X--;
				WorldPos wlFrom = target->self->GetWL();


				target->Lock();
				if( !target->self->Teleport( wlPos, 0 ) ){
					CREATE_MESSAGE( "The teleport destination is invalid, maybe player was not teleported to you first ?" );
					SEND_MESSAGE;		
				}else{
					
					//BLBL SENDBACK GM command, we store coming from position :
					target->self->prevTeleportPos.X=0xFFFFFFFF;
					target->self->prevTeleportPos.Y=0xFFFFFFFF;
					target->self->prevTeleportPos.world=0xFFFFFFFF;
					
					success = true;

					_LOG_GAMEOP
						LOG_SYSOP, 
						"God %s (%s) sent back character %s (%s) from ( %u, %u, %u ) to ( %u, %u, %u )",
						(LPCTSTR)user->self->GetTrueName(),
						(LPCTSTR)user->GetFullAccountName(),
						(LPCTSTR)target->self->GetTrueName(),
						(LPCTSTR)target->GetFullAccountName(),
						wlFrom.X,
						wlFrom.Y,
						wlFrom.world,
						wlPos.X,
						wlPos.Y,
						wlPos.world
					LOG_
				}
				target->Unlock();

			}else{
				CREATE_MESSAGE( "User %s is not online", PARAM( 0 ) );
				SEND_MESSAGE;
			}
		}
    //////////////////////////////////////////////////////////////////////////////////////////
    // Counts how many NPCs of a given name exist in the world.
    COMMAND( "COUNT NPC $", GOD_CAN_SUMMON_MONSTERS )
        TFormat format;
        DWORD count = NPCMain::GetInstance().CountNPC( PARAM( 0 ), user->self->GetLang() );
        string msg;
        if( count == 0 ){
            msg = format( "There are no NPCs named %s.", PARAM( 0 ) );            
        }else if( count == 1 ){
            msg = format( "There is only 1 NPC named %s.", PARAM( 0 ) );
        }else{
            msg = format( "There are %u NPCs named %s.", count, PARAM( 0 ) );
        };
        CREATE_MESSAGE( msg.c_str() );
        SEND_MESSAGE;
	//////////////////////////////////////////////////////////////////////////////////////////	
	// Kicks a player out of game.
	COMMAND( "ZAP $", GOD_CAN_ZAP )
		Players *target = FindCharacter( PARAM( 0 ) );

		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to zap user %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_		

			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;
			
		}		

		if( target != NULL && user->self->boAuthGM == true )
		{
            if( SUPER_USER ){
                CREATE_MESSAGE( "Sorry but you cannot zap the super user!" );
                SEND_MESSAGE;
            }else{
			    CString csText = "You have been temporarly kicked out from the game.";
			    
			    TFCPacket sending;
			    sending << (RQ_SIZE)RQ_ServerMessage;
			    sending << (short)30;
			    sending << (short)3;
			    sending << (CString &)csText;
				sending << (long) RGB( 255, 0, 0 );
			    target->Lock(); 
			    target->self->SendPlayerMessage( sending );
			    target->dwKickoutTime = 5 SECONDS TDELAY;
			    target->Unlock();

			    _LOG_GAMEOP
				    LOG_SYSOP,
				    "God %s (%s) zapped player %s (%s) out of the game.",
				    (LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
				    (LPCTSTR)target->self->GetTrueName(),
				    (LPCTSTR)target->GetFullAccountName()
			    LOG_
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}

	//////////////////////////////////////////////////////////////////////////////////////////
	// Forbids a user from talking (quite harsh in this game)
	COMMAND( "UNSQUELCH $", GOD_CAN_SQUELCH )
		
		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
            
			if (target->boCanTalk == FALSE ){
			success = true;

			target->Lock();
			target->boCanTalk = TRUE;
			target->self->SendSystemMessage( "Your ability to speak has been restored.", RGB( 0, 255, 0 ) );
			target->Unlock();

			CREATE_MESSAGE( "Locals restored.", PARAM( 0 ) );
			SEND_MESSAGE;

			
            _LOG_GAMEOP
				LOG_SYSOP,
				"God %s (%s) restored %s's (%s) ability to speak.",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)target->self->GetTrueName(),
				(LPCTSTR)target->GetFullAccountName()
			LOG_
			}else{

				CREATE_MESSAGE( "User %s already can talk.", PARAM( 0 ) );
				SEND_MESSAGE;

			}

		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}

	//////////////////////////////////////////////////////////////////////////////////////////
	// Restore player's ability to speak in game.
	COMMAND( "SQUELCH $", GOD_CAN_SQUELCH )
		
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to squelch user %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_			

			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL && user->self->boAuthGM == true ){
            if( SUPER_USER ){
                CREATE_MESSAGE( "Sorry but you cannot squelch the super user!" );
                SEND_MESSAGE
            }else{
                
				if (target->boCanTalk == TRUE ){
				success = true;

    			time_t lTimeCalc;
				time(&lTimeCalc);

				//BLBLBL AccHistory, liste des punitions :
				CString csHistory;
				csHistory.Format( "Locals removed");
				target->AddToHistory(lTimeCalc,csHistory);

				
				target->Lock();
				target->boCanTalk = FALSE;
				target->self->SendSystemMessage( "You cannot speak anymore.", RGB( 255, 0, 0 ) );
				target->Unlock();

				CREATE_MESSAGE( "Locals removed.");
				SEND_MESSAGE;


	    		_LOG_GAMEOP
		    		LOG_SYSOP,
			    	"God %s (%s) suspended %s's (%s) ability to speak.",
				    (LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
				    (LPCTSTR)target->self->GetTrueName(),
				    (LPCTSTR)target->GetFullAccountName()
			    LOG_

				}else{

				CREATE_MESSAGE( "User %s already have his talking ability removed.", PARAM( 0 ) );
				SEND_MESSAGE;
				
				}
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}

    //////////////////////////////////////////////////////////////////////////////////////////
	// Restores the ability of a player to shout
	COMMAND( "RESTORE $'S SHOUTS", GOD_CAN_REMOVE_SHOUTS )
		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
            
			if (target->boCanShout == FALSE ){
			
			success = true;

			target->Lock();
			target->boCanShout= TRUE;
			target->lCutExpireDate= 0;//BLBLBL on vire la date d'expiration
			target->self->SendSystemMessage( "Your shouts have been restored.", RGB( 0, 255, 0 ) );
			target->Unlock();

			CREATE_MESSAGE( "Shouts restored." );
			SEND_MESSAGE;


			_LOG_GAMEOP
				LOG_SYSOP,
				"God %s (%s) restored %s's (%s) ability to shout.",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)target->self->GetTrueName(),
				(LPCTSTR)target->GetFullAccountName()
			LOG_

			}else{

				success = false;

				CREATE_MESSAGE( "User %s already have his shouts.", PARAM( 0 ) );
				SEND_MESSAGE;

			}

		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}

    //////////////////////////////////////////////////////////////////////////////////////////
    // Removes the ability of a player to shout
	COMMAND( "REMOVE $'S SHOUTS FOR $ DAYS", GOD_CAN_REMOVE_SHOUTS )
		Players *target = FindCharacter( PARAM( 0 ) );
		int nDaysCut = atoi( PARAM( 1 ) );
		if (nDaysCut <= 0) nDaysCut = 1;//BLBLBL 1j mini de cut si on choisi les jours

		if( target != NULL ){
            if( SUPER_USER ){
                CREATE_MESSAGE( "Sorry but you cannot remove the super user's shouts." );
                SEND_MESSAGE;
            }else{

				if (target->boCanShout == TRUE) {

                success = true;

    			time_t lTimeCalc;
				time(&lTimeCalc);

				//BLBLBL AccHistory, liste des punitions :
				CString csHistory;
				csHistory.Format( "Shouts removed for %d days", nDaysCut);
				target->AddToHistory(lTimeCalc,csHistory);

				lTimeCalc+=nDaysCut*3600*24;//on converti le parametre en secondes
      
				CString csTemp;
				csTemp.Format("Your shouts have been revoked for %d day(s)",nDaysCut);

				target->Lock();
				target->boCanShout = FALSE;
				target->lCutExpireDate = lTimeCalc;
				target->self->SendSystemMessage( csTemp, RGB( 255, 0, 0 ) );
				target->Unlock();

				CREATE_MESSAGE( "Shouts removed for %d day(s).", nDaysCut );
				SEND_MESSAGE;


	    		_LOG_GAMEOP
		    		LOG_SYSOP,
			    	"God %s (%s) suspended %s's (%s) ability to shout for %u days(s).",
    				(LPCTSTR)user->self->GetTrueName(),
	    			(LPCTSTR)user->GetFullAccountName(),
		    		(LPCTSTR)target->self->GetTrueName(),
			    	(LPCTSTR)target->GetFullAccountName(),
					nDaysCut
			    LOG_

				}else{
					success = false;
					CREATE_MESSAGE( "User %s already have his shouts removed.", PARAM( 0 ) );
					SEND_MESSAGE;
				}
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}

	/////////////////////////////////////////////////////////////////////////////////////////
    // Removes the ability of a player to shout
	COMMAND( "REMOVE $'S SHOUTS FOR $ HOURS", GOD_CAN_REMOVE_SHOUTS )
		Players *target = FindCharacter( PARAM( 0 ) );
		int nHoursCut = atoi( PARAM( 1 ) );
		if (nHoursCut <= 0) nHoursCut = 1;//BLBLBL 1h mini de cut si on choisi les heures

		if( target != NULL ){
            if( SUPER_USER ){
                CREATE_MESSAGE( "Sorry but you cannot remove the super user's shouts." );
                SEND_MESSAGE;
            }else{

				if (target->boCanShout == TRUE) {

                success = true;

    			time_t lTimeCalc;
				time(&lTimeCalc);

				//BLBLBL AccHistory, liste des punitions :
				CString csHistory;
				csHistory.Format( "Shouts removed for %d hours", nHoursCut);
				target->AddToHistory(lTimeCalc,csHistory);

				lTimeCalc+=nHoursCut*3600;//on converti le parametre en secondes
      
				CString csTemp;
				csTemp.Format("Your shouts have been revoked for %d hour(s)",nHoursCut);

				target->Lock();
				target->boCanShout = FALSE;
				target->lCutExpireDate = lTimeCalc;
				target->self->SendSystemMessage( csTemp, RGB( 255, 0, 0 ) );
				target->Unlock();

				CREATE_MESSAGE( "Shouts removed for %d hour(s).", nHoursCut );
				SEND_MESSAGE;


	    		_LOG_GAMEOP
		    		LOG_SYSOP,
			    	"God %s (%s) suspended %s's (%s) ability to shout for %u hour(s).",
    				(LPCTSTR)user->self->GetTrueName(),
	    			(LPCTSTR)user->GetFullAccountName(),
		    		(LPCTSTR)target->self->GetTrueName(),
			    	(LPCTSTR)target->GetFullAccountName(),
					nHoursCut
			    LOG_

				}else{
					success = false;
					CREATE_MESSAGE( "User %s already have his shouts removed.", PARAM( 0 ) );
					SEND_MESSAGE;
				}
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}

    //////////////////////////////////////////////////////////////////////////////////////////
    // Removes the ability of a player to shout
	COMMAND( "REMOVE $'S SHOUTS FOR $ MINUTES", GOD_CAN_REMOVE_SHOUTS )
		Players *target = FindCharacter( PARAM( 0 ) );
		int nMinutesCut = atoi( PARAM( 1 ) );
		if (nMinutesCut<=0) nMinutesCut = 1; //BLBLBL 1 minute mini pour le cut si on choisi les minutes.
		else if (nMinutesCut>240) nMinutesCut = 240; //BLBLBL max 4heures de cut par les minutes.

		if( target != NULL ){
            if( SUPER_USER ){
                CREATE_MESSAGE( "Sorry but you cannot remove the super user's shouts." );
                SEND_MESSAGE;
            }else{
                
				if (target->boCanShout == TRUE ){

				success = true;

    			time_t lTimeCalc;
				time(&lTimeCalc);

				//BLBLBL AccHistory, liste des punitions :
				CString csHistory;
				csHistory.Format( "Shouts removed for %d minutes", nMinutesCut);
				target->AddToHistory(lTimeCalc,csHistory);

				lTimeCalc+=nMinutesCut*60;//on converti le parametre en secondes
      
				CString csTemp;
				csTemp.Format("Your shouts have been revoked for %d minute(s).",nMinutesCut);

				target->Lock();
				target->boCanShout = FALSE;
				target->lCutExpireDate = lTimeCalc;
				target->self->SendSystemMessage( csTemp, RGB( 255, 0, 0 ) );
				target->Unlock();

				CREATE_MESSAGE( "Shouts removed for %d minute(s).", nMinutesCut );
				SEND_MESSAGE;


	    		_LOG_GAMEOP
		    		LOG_SYSOP,
			    	"God %s (%s) suspended %s's (%s) ability to shout for %u minutes(s).",
    				(LPCTSTR)user->self->GetTrueName(),
	    			(LPCTSTR)user->GetFullAccountName(),
		    		(LPCTSTR)target->self->GetTrueName(),
			    	(LPCTSTR)target->GetFullAccountName(),
					nMinutesCut
			    LOG_

				}else{

					CREATE_MESSAGE( "User %s already have his shouts removed.", PARAM( 0 ) );
					SEND_MESSAGE;

				}
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}

	//////////////////////////////////////////////////////////////////////////////////////////
    // Removes the ability of a player to shout
	COMMAND( "REMOVE $'S SHOUTS", GOD_CAN_REMOVE_SHOUTS )
		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
            if( SUPER_USER ){
                CREATE_MESSAGE( "Sorry but you cannot remove the super user's shouts." );
                SEND_MESSAGE;
            }else{
                
				if (target->boCanShout == TRUE){

				success = true;
      
    			time_t lTimeCalc;
				time(&lTimeCalc);

				//BLBLBL AccHistory, liste des punitions :
				CString csHistory;
				csHistory.Format( "Shouts removed");
				target->AddToHistory(lTimeCalc,csHistory);

				
				CString csTemp;
				csTemp.Format("Your shouts have been revoked.");

				target->Lock();
				target->boCanShout = FALSE;
				target->lCutExpireDate = 0;//BLBLB dans le cas d'un cut sans durée, c'est infini.
				target->self->SendSystemMessage( csTemp, RGB( 255, 0, 0 ) );
				target->Unlock();

				CREATE_MESSAGE( "Shouts removed." );
				SEND_MESSAGE;


	    		_LOG_GAMEOP
		    		LOG_SYSOP,
			    	"God %s (%s) suspended %s's (%s) ability to shout.",
    				(LPCTSTR)user->self->GetTrueName(),
	    			(LPCTSTR)user->GetFullAccountName(),
		    		(LPCTSTR)target->self->GetTrueName(),
			    	(LPCTSTR)target->GetFullAccountName()
			    LOG_

				}else{

					CREATE_MESSAGE( "User %s already have his shouts removed.", PARAM( 0 ) );
					SEND_MESSAGE;

				}
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}


	//////////////////////////////////////////////////////////////////////////////////////////
    // Blocks all shouts to the public channels by non-operators
    COMMAND( "UNBLOCK PUBLIC CHANNELS", GOD_CHAT_MASTER );
        CPlayerManager::GetChatter().SetOperatorPublicChannelControl( false );

		WorldPos wlPos = { 0, 0, 0 };
		Broadcast::BCServerMessage( wlPos, 0, "Public channels have been unblocked!", NULL, RGB( 0, 255, 0 ) );

        _LOG_GAMEOP
            LOG_SYSOP,
            "God %s (%s) unblocked the public channels.",
            (LPCTSTR)user->self->GetTrueName(),
            (LPCTSTR)user->GetFullAccountName()
        LOG_

		CREATE_MESSAGE( "Public channels are now accessible by everyone" );
		SEND_MESSAGE;
       
    COMMAND( "BLOCK PUBLIC CHANNELS", GOD_CHAT_MASTER )
        CPlayerManager::GetChatter().SetOperatorPublicChannelControl( true );

		WorldPos wlPos = { 0, 0, 0 };
		Broadcast::BCServerMessage( wlPos, 0, "Public channels are now blocked.", NULL, RGB( 255, 0, 0 ) );

        _LOG_GAMEOP
            LOG_SYSOP,
            "God %s (%s) blocked the public channels.",
            (LPCTSTR)user->self->GetTrueName(),
            (LPCTSTR)user->GetFullAccountName()
        LOG_

		CREATE_MESSAGE( "Public channels are now blocked." );
		SEND_MESSAGE;

    //////////////////////////////////////////////////////////////////////////////////////////
    // View the total list of channels
    COMMAND( "VIEW TOTAL CHANNEL LIST", GOD_CHAT_MASTER )
        ChatterChannels &chatter = CPlayerManager::GetChatter();

        typedef vector< ChatterChannels::Channel > ChannelList;
        
        ChannelList channels;
        chatter.GetTotalChannelList( channels );

        ChannelList::iterator i;
        for( i = channels.begin(); i != channels.end(); i++ ){
            CREATE_MESSAGE( "Chan: %s", (*i).GetID().c_str() );
            SEND_MESSAGE;
        }

        success = true;
        
    //////////////////////////////////////////////////////////////////////////////////////////
    // Restores the ability of a player to page.
    COMMAND( "RESTORE $'S PAGES", GOD_CAN_REMOVE_SHOUTS )
		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
            
			if (target->boCanPage == FALSE) {
			success = true;

			target->Lock();
			target->boCanPage = TRUE;
			target->self->SendSystemMessage( "Your pages have been restored.", RGB( 0, 255, 0 ) );
			target->Unlock();

			CREATE_MESSAGE( "Pages restored." );
			SEND_MESSAGE;



			_LOG_GAMEOP
				LOG_SYSOP,
				"God %s (%s) restored %s's (%s) ability to page.",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)target->self->GetTrueName(),
				(LPCTSTR)target->GetFullAccountName()
			LOG_

			}else{

				CREATE_MESSAGE( "User %s already have his pages.", PARAM( 0 ) );
				SEND_MESSAGE;

			}

		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}        
    //////////////////////////////////////////////////////////////////////////////////////////
    // Removes the ability of a player to page.
    COMMAND( "REMOVE $'S PAGES", GOD_CAN_REMOVE_SHOUTS )	    
        Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
            if( SUPER_USER ){
                CREATE_MESSAGE( "Sorry but you cannot remove the super user's pages." );
                SEND_MESSAGE;
            }else{
                
				if (target->boCanPage == TRUE ){

				success = true;

    			time_t lTimeCalc;
				time(&lTimeCalc);

				//BLBLBL AccHistory, liste des punitions :
				CString csHistory;
				csHistory.Format( "Pages removed");
				target->AddToHistory(lTimeCalc,csHistory);

				target->Lock();
				target->boCanPage = FALSE;
				target->self->SendSystemMessage( "Your pages have been revoked.", RGB( 255, 0, 0 ) );
				target->Unlock();

				CREATE_MESSAGE( "Pages removed ");
				SEND_MESSAGE;



	    		_LOG_GAMEOP
		    		LOG_SYSOP,
			    	"God %s (%s) suspended %s's (%s) ability to page.",
    				(LPCTSTR)user->self->GetTrueName(),
	    			(LPCTSTR)user->GetFullAccountName(),
		    		(LPCTSTR)target->self->GetTrueName(),
			    	(LPCTSTR)target->GetFullAccountName()
			    LOG_

				}else{

					CREATE_MESSAGE( "User %s already have his pages removed.", PARAM( 0 ) );
					SEND_MESSAGE;
				
				}
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}


    //////////////////////////////////////////////////////////////////////////////////////////    
    // Allows setting a shout delay to a specific user.
    COMMAND( "SET $'S SHOUT DELAY TO $", GOD_CAN_REMOVE_SHOUTS )
	    Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
            if( stricmp( PARAM( 1 ), "DEFAULT" ) == 0 ){
                success = true;
                target->self->RemoveFlag( __FLAG_SHOUT );
                _LOG_GAMEOP
				    LOG_SYSOP,
				    "God %s (%s) reset %s's (%s) shout delay to default.",
				    (LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
				    (LPCTSTR)target->self->GetTrueName(),
				    (LPCTSTR)target->GetFullAccountName()
			    LOG_
            }else{
                int nShoutDelay = atoi( PARAM( 1 ) );

                if( nShoutDelay > 0 ){
                    success = true;
                    target->self->SetFlag( __FLAG_SHOUT, nShoutDelay );

                    _LOG_GAMEOP
	    			    LOG_SYSOP,
		    		    "God %s (%s) set %s's (%s) shout delay to %u seconds.",
			    	    (LPCTSTR)user->self->GetTrueName(),
				        (LPCTSTR)user->GetFullAccountName(),
				        (LPCTSTR)target->self->GetTrueName(),
    				    (LPCTSTR)target->GetFullAccountName(),
                        nShoutDelay
	    		    LOG_
                }else{
                    CREATE_MESSAGE( "Specified shout delay is invalid. Value must be higher than 1." );
                    SEND_MESSAGE;
                }
            }
			            
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}


	//////////////////////////////////////////////////////////////////////////////////////////
	// Summons a monster
	COMMAND( "SUMMON MONSTER $ AT $,$,$", GOD_CAN_SUMMON_MONSTERS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to summon monsters without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName()				
			LOG_		
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		BOOL boInvalidPos = FALSE;
		BOOL boInvalidMonster = FALSE;
		
		WorldPos wlPos = { 0, 0, 0 };

		wlPos.X		= atoi( PARAM( 1 ) );
		wlPos.Y		= atoi( PARAM( 2 ) );
		wlPos.world = atoi( PARAM( 3 ) );		
		
		if( wlPos.X != 0 && wlPos.Y != 0 && user->self->boAuthGM == true ){
			DWORD dwID = Unit::GetIDFromName( PARAM(0), U_NPC, TRUE );
			
			if( dwID != 0 ){
				
				WorldMap *wlWorld = TFCMAIN::GetWorld( wlPos.world );			

				if( wlWorld != NULL ){
					if( wlWorld->IsValidPosition( wlPos ) ){//check if >=0 and <=MAXX / >=0 and <=MAXY
						Creatures *lpMonster = new Creatures;
						if( lpMonster->Create( U_NPC, dwID ) ){
                            success = true;

							lpMonster->SetDestination( wlPos );
							lpMonster->Do( wandering );
							lpMonster->SetWL( wlPos );
							if( !wlWorld->SummonMonster( lpMonster, TRUE ) ){
								lpMonster->DeleteUnit();
								boInvalidMonster = TRUE;
							}else{
								_LOG_GAMEOP
									LOG_SYSOP,
									"God %s (%s) summoned monster %s at ( %u, %u, %u ).",
									(LPCTSTR)user->self->GetTrueName(),
									(LPCTSTR)user->GetFullAccountName(),
									PARAM( 0 ),
									wlPos.X,
									wlPos.Y,
									wlPos.world
								LOG_
							}

						}else{
							boInvalidMonster = TRUE;
							lpMonster->DeleteUnit();
						}
					}else{
						boInvalidPos = TRUE;
					}
				}else{
					boInvalidPos = TRUE;
				}
			}else{
				boInvalidMonster = TRUE;	
			}
		}else{
			boInvalidPos = TRUE;
		}

		if( boInvalidMonster ){
			CREATE_MESSAGE( "Invalid monster ID %s.", PARAM( 0 ) );
			SEND_MESSAGE;
		}else if( boInvalidPos ){
			CREATE_MESSAGE( "( %u, %u, %u ) isn't a valid world position.", wlPos.X, wlPos.Y, wlPos.world );
			SEND_MESSAGE;
		}
		boFound = TRUE;
	//////////////////////////////////////////////////////////////////////////////////////////
	// Summons a monster on god's side 'n' times
	COMMAND( "SUMMON MONSTER $ *$", GOD_CAN_SUMMON_MONSTERS )

		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to summon monsters without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName()				
			LOG_		
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		if( atoi(PARAM(1)) > 200 && user->self->boAuthGM == false ){
			CREATE_MESSAGE( "Invalid quantity: %s. Max allowed: 200", PARAM( 1 ) );
			SEND_MESSAGE;
		} else {
			CString csRepeatCommand;
			WorldPos wlPos = user->self->GetWL();
			//WorldPos wlPosDest = user->self->GetWL();
			
			//
			//  MMM
			//  MMM
			//  MMM      M = Monsters
			//     C     C = caster

			int lineSize = floor(sqrt((double)atoi(PARAM(1))));//BLBLBL on arrondi, autrement on risque de génèrer des positions invalides.. // steph ajout de (double)
			//As the summoning area is a square, we pick the square root of quantity to know the number of monster per line.
			
			wlPos.X -= lineSize;
			wlPos.Y -= lineSize;
			
			for (int i=0; i< atoi(PARAM(1)); i++) {
				if (i % lineSize == 0) {
					wlPos.Y++;//on passe à la ligne suivante
					wlPos.X -= lineSize; //et on se remet en début de ligne
				} else wlPos.X++;
				csRepeatCommand.Format("SUMMON MONSTER %s AT %d,%d,%d", PARAM(0), wlPos.X, wlPos.Y,wlPos.world);
				VerifySysopCommand(user, csRepeatCommand);
			}
/*			for (int i=0; i>=0 && i< atoi(PARAM(1)); i++) {
				if (i % lineSize == 0) {
					wlPos.X++;
					wlPos.Y -= lineSize;
				} else wlPos.Y++;
				csRepeatCommand.Format("SUMMON MONSTER %s AT %d,%d,%d", PARAM(0), wlPos.X, wlPos.Y,wlPos.world);
				VerifySysopCommand(user, csRepeatCommand);
			}*/
			/*
			//invocation en forme de cercle autour de l'invocateur :
			int qtyToSummon = atoi(PARAM(1));
			int qtyCircles = ceil(qtyToSummon/8);
			int invocs = 0;
			int x,y=0;

			for (int c=0 ; c<qtyCircles ; c++){

				//  AAAAA		
				//  ACCCA
				//  ACXCA    X = caster, C = 1st circle, A = 2nd circle etc..
				//  ACCCA    Each circle brings +8 new spots
				//  AAAAA	 

				//haut du cercle
				x=0;y=0;
				wlPosDest.Y = wlPos.Y-1-c;
				for (x=wlPos.X-1-c; x<=wlPos.X-1-c+2+c*2,invocs<qtyToSummon; x++){					
					wlPosDest.X = x;
					csRepeatCommand.Format("SUMMON MONSTER %s AT %d,%d,%d", PARAM(0), wlPosDest.X, wlPosDest.Y,wlPosDest.world);
					VerifySysopCommand(user, csRepeatCommand);
					invocs++;
				}
				
				//bas du cercle
				x=0;y=0;
				wlPosDest.Y = wlPos.Y+1+c;
				for (x=wlPos.X-1-c; x<=wlPos.X-1-c+2+c*2,invocs<qtyToSummon; x++){
					wlPosDest.X = x;
					csRepeatCommand.Format("SUMMON MONSTER %s AT %d,%d,%d", PARAM(0), wlPosDest.X, wlPosDest.Y,wlPosDest.world);
					VerifySysopCommand(user, csRepeatCommand);
					invocs++;
				}
				
				//gauche du cercle
				x=0;y=0;
				wlPosDest.X = wlPos.X-1-c;
				for (y=wlPos.Y-c; y<=wlPos.Y+c*2,invocs<qtyToSummon; y++){
					wlPosDest.Y = y;
					csRepeatCommand.Format("SUMMON MONSTER %s AT %d,%d,%d", PARAM(0), wlPosDest.X, wlPosDest.Y,wlPosDest.world);
					VerifySysopCommand(user, csRepeatCommand);
					invocs++;
				}

				//droite du cercle
				x=0;y=0;
				wlPosDest.X = wlPos.X+1+c;
				for (y=wlPos.Y-c; y<=wlPos.Y+c*2,invocs<qtyToSummon; y++){
					wlPosDest.Y = y;
					csRepeatCommand.Format("SUMMON MONSTER %s AT %d,%d,%d", PARAM(0), wlPosDest.X, wlPosDest.Y,wlPosDest.world);
					VerifySysopCommand(user, csRepeatCommand);
					invocs++;
				}


			}*/

		}
	//////////////////////////////////////////////////////////////////////////////////////////
	// Summons a monster on god's side
	COMMAND( "SUMMON MONSTER $", GOD_CAN_SUMMON_MONSTERS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to summon monster without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName()			
			LOG_		
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		BOOL boInvalidPos = FALSE;
		BOOL boInvalidMonster = FALSE;
		
		WorldPos wlPos = user->self->GetWL();
        wlPos.X--;

		if( wlPos.X != 0 && wlPos.Y != 0 && user->self->boAuthGM == true ){
			DWORD dwID = Unit::GetIDFromName( PARAM(0), U_NPC, TRUE );
			
			if( dwID != 0 ){
				
				WorldMap *wlWorld = TFCMAIN::GetWorld( wlPos.world );			

				if( wlWorld != NULL ){
					if( wlWorld->IsValidPosition( wlPos ) ){
						Creatures *lpMonster = new Creatures;
						if( lpMonster->Create( U_NPC, dwID ) ){
                            success = true;

							lpMonster->SetDestination( wlPos );
							lpMonster->Do( wandering );
							lpMonster->SetWL( wlPos );
							if( !wlWorld->SummonMonster( lpMonster, TRUE ) ){
								lpMonster->DeleteUnit();
								boInvalidMonster = TRUE;
							}else{
								_LOG_GAMEOP
									LOG_SYSOP,
									"God %s (%s) summoned monster %s at ( %u, %u, %u ).",
									(LPCTSTR)user->self->GetTrueName(),
									(LPCTSTR)user->GetFullAccountName(),
									PARAM( 0 ),
									wlPos.X,
									wlPos.Y,
									wlPos.world
								LOG_
							}

						}else{
							boInvalidMonster = TRUE;
							lpMonster->DeleteUnit();
						}
					}else{
						boInvalidPos = TRUE;
					}
				}else{
					boInvalidPos = TRUE;
				}
			}else{
				boInvalidMonster = TRUE;	
			}
		}else{
			boInvalidPos = TRUE;
		}

		if( boInvalidMonster ){
			CREATE_MESSAGE( "Invalid monster ID %s.", PARAM( 0 ) );
			SEND_MESSAGE;
		}else if( boInvalidPos ){
			CREATE_MESSAGE( "( %u, %u, %u ) isn't a valid world position.", wlPos.X, wlPos.Y, wlPos.world );
			SEND_MESSAGE;
		}
		boFound = TRUE;
	//////////////////////////////////////////////////////////////////////////////////////////	
	// Summons an item in somebody's backpack
    COMMAND( "SUMMON ITEM $ ON $", GOD_CAN_SUMMON_ITEMS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to summon item on %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 1 )
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		BOOL boInvalidItem = FALSE;
		DWORD dwID = Unit::GetIDFromName( PARAM(0), U_OBJECT, TRUE );

		Players *target = FindCharacter( PARAM( 1 ) );

		if( target != NULL && user->self->boAuthGM == true){
		    if( dwID != 0 ){			
			    Objects *lpItem = new Objects;
			    if( lpItem->Create( U_OBJECT, dwID ) ){                
    			    _item *item = NULL;
	    		    // Get the item structure.
		    	    lpItem->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &item );

                    if( item->canSummon || user->GetGodFlags() & GOD_DEVELOPPER ){
                        success = true;

                        target->Lock();

                        target->self->AddToBackpack( lpItem );

                        TFCPacket sending;
                        sending << (RQ_SIZE)RQ_ViewBackpack;
	    			    sending << (char)0;	// Don't show backpack..!!
		    		    sending << (long)target->self->GetID();
			    	    target->self->PacketBackpack( sending );
                        target->self->SendPlayerMessage( sending );

                        sending.Destroy();
                        target->self->packet_equiped( sending );
                        target->self->SendPlayerMessage( sending );

                    
                        _LOG_GAMEOP
				            LOG_SYSOP,
						        "God %s (%s) summoned item %s in user %s (%s)'s backpack.",
						        (LPCTSTR)user->self->GetTrueName(),
						        (LPCTSTR)user->GetFullAccountName(),
						        PARAM( 0 ),
                                (LPCTSTR)target->self->GetTrueName(),
                                (LPCTSTR)target->GetFullAccountName()
			            LOG_

                        target->Unlock();
                    }else{
                        boInvalidItem = TRUE;
                        lpItem->DeleteUnit();
                    }
			    }else{
				    boInvalidItem = TRUE;
				    lpItem->DeleteUnit();
			    }                            
		    }else{
			    boInvalidItem = TRUE;	
		    }
        }else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 1 ) );
			SEND_MESSAGE;
        }

		if( boInvalidItem ){
			CREATE_MESSAGE( "Invalid object ID %s.", PARAM( 0 ) );
			SEND_MESSAGE;
		}


    //////////////////////////////////////////////////////////////////////////////////////////	
	// Summons an item on the ground        
    COMMAND( "SUMMON ITEM $ AT $,$,$", GOD_CAN_SUMMON_ITEMS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to summon item on the ground without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName()				
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		BOOL boInvalidItem = FALSE;
		DWORD dwID = Unit::GetIDFromName( PARAM(0), U_OBJECT, TRUE );
			
		if( dwID != 0 && user->self->boAuthGM == true ){
            WorldPos wlPos = { atoi(PARAM(1)),atoi(PARAM(2)),atoi(PARAM(3)) };
				
			Objects *lpItem = new Objects;
			if( lpItem->Create( U_OBJECT, dwID ) ){  
			    _item *item = NULL;
			    // Get the item structure.
			    lpItem->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &item );

                if( item->canSummon || user->GetGodFlags() & GOD_DEVELOPPER ){                
                    WorldMap *world = TFCMAIN::GetWorld( wlPos.world );
                    if( world != NULL && world->IsValidPosition( wlPos ) ){
                        world->deposit_unit( wlPos, lpItem );
                        success = true;

                        lpItem->BroadcastPopup( wlPos, true );

                        _LOG_GAMEOP
				            LOG_SYSOP,
						        "God %s (%s) summoned item %s at %u, %u, %u.",
						        (LPCTSTR)user->self->GetTrueName(),
						        (LPCTSTR)user->GetFullAccountName(),
						        PARAM( 0 ),
                                wlPos.X,
                                wlPos.Y,
                                wlPos.world
			            LOG_
                    }else{
                        CREATE_MESSAGE( 
                            "World position %u, %u, %u is not valid.",
                            wlPos.X,
                            wlPos.Y,
                            wlPos.world
                        );
                        SEND_MESSAGE;
                        lpItem->DeleteUnit();
                    }
                }else{
    				boInvalidItem = TRUE;
	    			lpItem->DeleteUnit();
                }
			}else{
				boInvalidItem = TRUE;
				lpItem->DeleteUnit();
			}
		}else{
			boInvalidItem = TRUE;	
		}

		if( boInvalidItem ){
			CREATE_MESSAGE( "Invalid object ID %s.", PARAM( 0 ) );
			SEND_MESSAGE;
		}
    //////////////////////////////////////////////////////////////////////////////////////////	
	// Summons an item on the ground        
    COMMAND( "SUMMON CIRCLE OF ITEM $ AT $,$,$", GOD_CAN_SUMMON_ITEMS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to summon item on the ground without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName()				
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		BOOL boInvalidItem = FALSE;
		DWORD dwID = Unit::GetIDFromName( PARAM(0), U_OBJECT, TRUE );
			
		if( dwID != 0 && user->self->boAuthGM == true ){
            
			WorldPos wlPos = { atoi(PARAM(1)),atoi(PARAM(2)),atoi(PARAM(3)) };
			WorldPos wlInitial = wlPos;
			
			for (int a=0;a<180;a+=10){//on parcours les angles de 0 à 180 par incrément de 10.


				//////////////////////////////////////////////////////////////////////////////////////////
				// steph ajout de (double)
				//////////////////////////////////////////////////////////////////////////////////////////
				wlPos.X = wlInitial.X + floor(cos((double)a)*10);
				wlPos.Y = wlInitial.Y + floor(sin((double)a)*10);
			


				Objects *lpItem = new Objects;
				if( lpItem->Create( U_OBJECT, dwID ) ){  
					_item *item = NULL;
					// Get the item structure.
					lpItem->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &item );

					if( item->canSummon || user->GetGodFlags() & GOD_DEVELOPPER ){                
						WorldMap *world = TFCMAIN::GetWorld( wlPos.world );
						if( world != NULL && world->IsValidPosition( wlPos ) ){
							world->deposit_unit( wlPos, lpItem );
							success = true;

							lpItem->BroadcastPopup( wlPos, true );

							_LOG_GAMEOP
								LOG_SYSOP,
									"God %s (%s) summoned item %s at %u, %u, %u.",
									(LPCTSTR)user->self->GetTrueName(),
									(LPCTSTR)user->GetFullAccountName(),
									PARAM( 0 ),
									wlPos.X,
									wlPos.Y,
									wlPos.world
							LOG_
						}else{
							CREATE_MESSAGE( 
								"World position %u, %u, %u is not valid.",
								wlPos.X,
								wlPos.Y,
								wlPos.world
							);
							SEND_MESSAGE;
							lpItem->DeleteUnit();
						}
					}else{
    					boInvalidItem = TRUE;
	    				lpItem->DeleteUnit();
					}
				}else{
					boInvalidItem = TRUE;
					lpItem->DeleteUnit();
				}

			}//BLBL fin for

		}else{
			boInvalidItem = TRUE;	
		}

		if( boInvalidItem ){
			CREATE_MESSAGE( "Invalid object ID %s.", PARAM( 0 ) );
			SEND_MESSAGE;
		}
    //////////////////////////////////////////////////////////////////////////////////////////	
	// Summons an item on the ground        
    COMMAND( "SUMMON CIRCLE OF ITEM $", GOD_CAN_SUMMON_ITEMS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to summon item on the ground without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName()				
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		BOOL boInvalidItem = FALSE;
		DWORD dwID = Unit::GetIDFromName( PARAM(0), U_OBJECT, TRUE );
			
		if( dwID != 0 && user->self->boAuthGM == true ){
            			
			WorldPos wlPos = user->self->GetWL();//on prend les coordonnées du lanceur de la commande
			WorldPos wlInitial = wlPos;
			
			for (int a=0;a<180;a+=10){//on parcours les angles de 0 à 180 par incrément de 10.


				//////////////////////////////////////////////////////////////////////////////////////////
				// steph ajout de (double)
				//////////////////////////////////////////////////////////////////////////////////////////
				wlPos.X = wlInitial.X + floor(cos((double)a)*10);
				wlPos.Y = wlInitial.Y + floor(sin((double)a)*10);
			


				Objects *lpItem = new Objects;
				if( lpItem->Create( U_OBJECT, dwID ) ){  
					_item *item = NULL;
					// Get the item structure.
					lpItem->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &item );

					if( item->canSummon || user->GetGodFlags() & GOD_DEVELOPPER ){                
						WorldMap *world = TFCMAIN::GetWorld( wlPos.world );
						if( world != NULL && world->IsValidPosition( wlPos ) ){
							world->deposit_unit( wlPos, lpItem );
							success = true;

							lpItem->BroadcastPopup( wlPos, true );

							_LOG_GAMEOP
								LOG_SYSOP,
									"God %s (%s) summoned item %s at %u, %u, %u.",
									(LPCTSTR)user->self->GetTrueName(),
									(LPCTSTR)user->GetFullAccountName(),
									PARAM( 0 ),
									wlPos.X,
									wlPos.Y,
									wlPos.world
							LOG_
						}else{
							CREATE_MESSAGE( 
								"World position %u, %u, %u is not valid.",
								wlPos.X,
								wlPos.Y,
								wlPos.world
							);
							SEND_MESSAGE;
							lpItem->DeleteUnit();
						}
					}else{
    					boInvalidItem = TRUE;
	    				lpItem->DeleteUnit();
					}
				}else{
					boInvalidItem = TRUE;
					lpItem->DeleteUnit();
				}

			}//BLBL fin for

		}else{
			boInvalidItem = TRUE;	
		}

		if( boInvalidItem ){
			CREATE_MESSAGE( "Invalid object ID %s.", PARAM( 0 ) );
			SEND_MESSAGE;
		}
	//////////////////////////////////////////////////////////////////////////////////////////	
	// Summons an item in the god's backpack (any qty for non unique items)
    COMMAND( "SUMMON ITEM $ *$", GOD_CAN_SUMMON_ITEMS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to summon items without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName()
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		BOOL boInvalidItem = FALSE;
		DWORD dwID = Unit::GetIDFromName( PARAM(0), U_OBJECT, TRUE );
			
		if( dwID != 0 && user->self->boAuthGM == true ){
				
			Objects *lpItem = new Objects;
			if( lpItem->Create( U_OBJECT, dwID ) ){
			    _item *item = NULL;
			    // Get the item structure.
			    lpItem->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &item );

                if( item->canSummon || user->GetGodFlags() & GOD_DEVELOPPER ){
					if ( ! lpItem->IsUnique() && atoi(PARAM(1))>0) lpItem->SetQty(atoi(PARAM(1)));
                   user->self->AddToBackpack( lpItem );

    	 		    TFCPacket sending;
                    sending << (RQ_SIZE)RQ_ViewBackpack;
	    		    sending << (char)0;	// Don't show backpack..!!
		    	    sending << (long)user->self->GetID();
			        user->self->PacketBackpack( sending );
                    user->self->SendPlayerMessage( sending );

                    sending.Destroy();
                    user->self->packet_equiped( sending );
                    user->self->SendPlayerMessage( sending );


                   success = true;
				    _LOG_GAMEOP
					    LOG_SYSOP,
					    "God %s (%s) summoned %ix item %s.",
					    (LPCTSTR)user->self->GetTrueName(),
					    (LPCTSTR)user->GetFullAccountName(),
						atoi( PARAM( 1 ) ),
					    PARAM( 0 )
				    LOG_
                }else{
                    boInvalidItem = TRUE;
                    lpItem->DeleteUnit();
                }
			}else{
				boInvalidItem = TRUE;
				lpItem->DeleteUnit();
			}
		}else{
			boInvalidItem = TRUE;	
		}

		if( boInvalidItem ){
			CREATE_MESSAGE( "Invalid object ID %s.", PARAM( 0 ) );
			SEND_MESSAGE;
		}
	//////////////////////////////////////////////////////////////////////////////////////////	
	// Summons an item in the god's backpack        
    COMMAND( "SUMMON ITEM $", GOD_CAN_SUMMON_ITEMS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to summon item without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName()
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}
		else
		{
			CString csRepeatCommand;
			csRepeatCommand.Format("SUMMON ITEM %s *1", PARAM(0));
			VerifySysopCommand(user,csRepeatCommand);
		}
	//////////////////////////////////////////////////////////////////////////////////////////
	// Sets a user flag on the given user.
	COMMAND( "SET $'S FLAG $ TO $", GOD_CAN_SET_USER_FLAG )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to set %s's flag without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_			
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
			SEND_MESSAGE;

		}

		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL && user->self->boAuthGM == true ){
			DWORD dwFlagID = atoi( PARAM( 1 ) );
			DWORD dwFlagValue = atoi( PARAM( 2 ) );
			if( dwFlagID != 0 ){
				target->Lock();
				target->self->SetFlag( dwFlagID, dwFlagValue );
				target->Unlock();
                
                success = true;

				_LOG_GAMEOP
					LOG_SYSOP,
					"God %s (%s) edited %s's (%s) flag#%u to %u.",
					(LPCTSTR)user->self->GetTrueName(),
					(LPCTSTR)user->GetFullAccountName(),
					(LPCTSTR)target->self->GetTrueName(),
					(LPCTSTR)target->GetFullAccountName(),
					dwFlagID,
					dwFlagValue
				LOG_

			}
			boFound = TRUE;
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}
	//////////////////////////////////////////////////////////////////////////////////////////
	// Removes a user flag on the given user.
	COMMAND( "REMOVE $'S FLAG $", GOD_CAN_SET_USER_FLAG )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to remove %s's flag without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_			

			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL && user->self->boAuthGM == true ){
			DWORD dwFlagID = atoi( PARAM( 1 ) );
			if( dwFlagID != 0 ){
                success = true;

				target->Lock();
				target->self->RemoveFlag( dwFlagID );
				target->Unlock();
				_LOG_GAMEOP
					LOG_SYSOP,
					"God %s (%s) removed %s's (%s) flag#%u.",
					(LPCTSTR)user->self->GetTrueName(),
					(LPCTSTR)user->GetFullAccountName(),
					(LPCTSTR)target->self->GetTrueName(),
					(LPCTSTR)target->GetFullAccountName(),
					dwFlagID
				LOG_

			}
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}
    //////////////////////////////////////////////////////////////////////////////////////////
    // View the specific value of a flag on a player,
    COMMAND( "VIEW $'S FLAG $", GOD_CAN_SET_USER_FLAG )
		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
			DWORD dwFlagID = atoi( PARAM( 1 ) );
			if( dwFlagID != 0 ){
				target->Lock();
				int flagValue = target->self->ViewFlag( dwFlagID );
				target->Unlock();

                CREATE_MESSAGE( "%s's flag %u = %d", PARAM( 0 ), dwFlagID, flagValue );
                SEND_MESSAGE;
			}
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}

	//////////////////////////////////////////////////////////////////////////////////////////
	// Set a skill or spell
	COMMAND( "SET $'S SKILL $ TO $", GOD_CAN_EDIT_USER_SKILLS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to set %s's skill without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		WORD wSpellID = atoi( PARAM( 1 ) );
		WORD wValue = atoi( PARAM( 2 ) );

        // If the spellID is 0, then perhaps a spell name was provided.
        if( wSpellID == 0 ){
            // Retreive the spell by its name.
            LPSKILL lpSkill = Skills::GetSkillByName( PARAM( 1 ), user->self->GetLang() );
            if( lpSkill != NULL ){
                wSpellID = lpSkill->nSkillID;
            }
        }	
				
		if( wSpellID != 0 ){
			Players *target = FindCharacter( PARAM( 0 ) );

			if( target != NULL && user->self->boAuthGM == true ){
				// Set 0 hp
				target->Lock();
				
				LPUSER_SKILL lpUserSkill = target->self->GetSkill( wSpellID );
				if( lpUserSkill != NULL ){
                    success = true;

					lpUserSkill->SetSkillPnts( wValue );
				    _LOG_GAMEOP
					    LOG_SYSOP,
					    "God %s (%s) set %s's (%s) skill %u to %u.",
					    (LPCTSTR)user->self->GetTrueName(),
					    (LPCTSTR)user->GetFullAccountName(),
					    (LPCTSTR)target->self->GetTrueName(),
					    (LPCTSTR)target->GetFullAccountName(),
					    wSpellID,
                        wValue
				    LOG_
				}else{
					CREATE_MESSAGE( "User doesn't have this skill." );
					SEND_MESSAGE;
				}

				target->Unlock();

			}else{
				CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
				SEND_MESSAGE;
			}
		}else{
			CREATE_MESSAGE( "Skill ID isn't valid" );
			SEND_MESSAGE;
		}

#define FIRST_COMPONENT( __cmp, __god,__pos ) if( user->GetGodFlags() & __god && stricmp( (LPCTSTR)PARAM( __pos ), __cmp ) == 0 ){
#define COMPONENT( __cmp, __god,__pos ) }else if( user->GetGodFlags() & __god && stricmp( (LPCTSTR)PARAM( __pos ), __cmp ) == 0  ){
	//////////////////////////////////////////////////////////////////////////////////////////	
	// Sets a specific playet stat to a given value
	COMMAND( "SET $'S $ TO $", GOD_CAN_EDIT_USER )	
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to set %s's %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 ),
				(LPCTSTR)PARAM( 1 )
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL && user->self->boAuthGM == true ){
			DWORD dwValue = atoi( PARAM( 2 ) );
			WORD bStat = (WORD)dwValue;
			
			CString csLogText;
			CString csAppend;
			csLogText.Format( "God %s (%s) edited %s's (%s) ",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)target->self->GetTrueName(),
				(LPCTSTR)target->GetFullAccountName()
			);

            bool plus = false;;
            bool minus = false;
            int paramLen = strlen( PARAM( 2 ) );
            // If the parameter is long enough to hold a + sign.
            if( paramLen > 1 ){
                // If the parameter has a plus sign.
                if( PARAM(2)[0] == '+' ){
                    plus = true;
                }else if( PARAM(2)[0] == '-' ){
                    dwValue = -atoi( PARAM( 2 ) );
                    bStat = (WORD)dwValue;
                    minus = true;
                }
            }
            
            target->Lock();

			TRACE( "\r\nParameters: %s, %s, %s", PARAM( 0 ), PARAM( 1 ), PARAM( 2 ) );

            success = true;

			FIRST_COMPONENT( "STR", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueSTR(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueSTR(), bStat ); };
                target->self->SetSTR( bStat );
				csAppend.Format( "strength to %u.", bStat );
			COMPONENT( "END", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueEND(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueEND(), bStat ); };
				target->self->SetEND( bStat );
				csAppend.Format( "endurance to %u.", bStat );
			COMPONENT(  "AGI", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueAGI(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueAGI(), bStat ); };
				target->self->SetAGI( bStat );
				csAppend.Format( "agility to %u.", bStat );
			COMPONENT( "INT", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueINT(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueINT(), bStat ); };
				target->self->SetINT( bStat );
				csAppend.Format( "intelligence to %u.", bStat );
			COMPONENT( "WIL", GOD_CAN_EDIT_USER_STAT, 1 )				
				csAppend.Format( "willpower is no longer implemented." );
			COMPONENT( "WIS", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueWIS(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueWIS(), bStat ); };
				target->self->SetWIS( bStat );
				csAppend.Format( "wisdom to %u.", bStat );
			COMPONENT( "LUCK", GOD_CAN_EDIT_USER_STAT, 1 )
				if( plus ) { bStat += target->self->GetTrueLCK(); }
				if( minus ) { bStat = SafeMinus( target->self->GetTrueLCK(), bStat ); };
				target->self->SetLCK( bStat );
				csAppend.Format( "luck to %u", bStat );
            COMPONENT( "KARMA", GOD_CAN_EDIT_USER_STAT, 1 )                
                target->self->SetKarma( atoi( PARAM( 2 ) ) );
                csAppend.Format( "karma to %d", bStat );
            COMPONENT( "FIRE RESIST", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueFireResist(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueFireResist(), bStat ); };
                target->self->SetFireResist( bStat );
                csAppend.Format( "fire resist to %u.", bStat );
            COMPONENT( "WATER RESIST", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueWaterResist(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueWaterResist(), bStat ); };
                target->self->SetWaterResist( bStat );
                csAppend.Format( "water resist to %u.", bStat );
            COMPONENT( "EARTH RESIST", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueEarthResist(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueEarthResist(), bStat ); };
                target->self->SetEarthResist( bStat );
                csAppend.Format( "earth resist to %u.", bStat );
            COMPONENT( "AIR RESIST", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueAirResist(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueAirResist(), bStat ); };
                target->self->SetAirResist( bStat );
                csAppend.Format( "air resist to %u.", bStat );
            COMPONENT( "LIGHT RESIST", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueLightResist(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueLightResist(), bStat ); };
                target->self->SetLightResist( bStat );
                csAppend.Format( "light resist to %u.", bStat );
            COMPONENT( "DARK RESIST", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueDarkResist(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueDarkResist(), bStat ); };
                target->self->SetDarkResist( bStat );
                csAppend.Format( "dark resist to %u.", bStat );
            COMPONENT( "FIRE", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueFirePower(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueFirePower(), bStat ); };
                target->self->SetFirePower( bStat );
                csAppend.Format( "fire power to %u.", bStat );
            COMPONENT( "WATER", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueWaterPower(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueWaterPower(), bStat ); };
                target->self->SetWaterPower( bStat );
                csAppend.Format( "water power to %u.", bStat );
            COMPONENT( "EARTH", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueEarthPower(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueEarthPower(), bStat ); };
                target->self->SetEarthPower( bStat );
                csAppend.Format( "earth power to %u.", bStat );
            COMPONENT( "AIR", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueAirPower(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueAirPower(), bStat ); };
                target->self->SetAirPower( bStat );
                csAppend.Format( "air power to %u.", bStat );
            COMPONENT( "LIGHT", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueLightPower(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueLightPower(), bStat ); };
                target->self->SetLightPower( bStat );
                csAppend.Format( "light power to %u.", bStat );
            COMPONENT( "DARK", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueDarkPower(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueDarkPower(), bStat ); };
                target->self->SetDarkPower( bStat );
                csAppend.Format( "dark power to %u.", bStat );
            COMPONENT( "DODGE", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueDODGE(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueDODGE(), bStat ); };
				target->self->SetDODGE( bStat );
				csAppend.Format( "dodge skill to %u.", bStat );
			COMPONENT( "ATTACK", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ bStat += target->self->GetTrueATTACK(); }
                if( minus ){ bStat = SafeMinus( target->self->GetTrueATTACK(), bStat ); };
				target->self->SetATTACK( bStat );
				csAppend.Format( "attack skill to %u.", bStat );
			COMPONENT( "GOLD", GOD_CAN_EDIT_USER_BACKPACK, 1 )
                if( plus ){ dwValue += target->self->GetGold(); }
                if( minus ){ dwValue = SafeMinus( target->self->GetGold(), dwValue ); };
				target->self->SetGold( dwValue );
				csAppend.Format( "gold to %u.", dwValue );
			
            COMPONENT( "XP", GOD_CAN_EDIT_USER_XP_LEVEL, 1 )
                __int64 xp;
                // If a + sign was put in front of the number.
                if( plus ){
                    __int64 oldxp = target->self->GetXP();
                    xp = _atoi64( PARAM(2) ) + target->self->GetXP();
                    target->self->SetXP( xp );

                    csAppend.Format( "experience from %I64u to %I64u.", oldxp, xp );
                }else if( minus ){
                    __int64 oldxp = target->self->GetXP();
                    xp = _atoi64( PARAM(2) ) + target->self->GetXP();
                    if( xp < 0 ){
                        xp = 0;
                    }
                    target->self->SetXP( xp );

                    csAppend.Format( "experience from %I64u to %I64u.", oldxp, xp );
                }else{
                    xp = _atoi64( PARAM(2) );
                    target->self->SetXP( xp );
                    csAppend.Format( "experience to %I64u.", xp );
                }                
			COMPONENT( "HP", GOD_CAN_EDIT_USER_HP, 1 )
                if( plus ){ dwValue += target->self->GetHP(); }
                if( minus ){ dwValue = SafeMinus( target->self->GetHP(), dwValue ); };
				target->self->SetHP( dwValue, true );
				csAppend.Format( "hit points to %u.", dwValue );
			COMPONENT( "MAX HP", GOD_CAN_EDIT_USER_HP, 1 )
                if( plus ){ dwValue += target->self->GetTrueMaxHP(); }
                if( minus ){ dwValue = SafeMinus( target->self->GetTrueMaxHP(), dwValue ); };
				target->self->SetMaxHP( dwValue );
				csAppend.Format( "maximum hit points to %u.", dwValue );
			COMPONENT( "MAX MANA", GOD_CAN_EDIT_USER_MANA_FAITH, 1 )
                if( plus ){ dwValue += target->self->GetTrueMaxMana(); }
                if( minus ){ dwValue = SafeMinus( target->self->GetTrueMaxMana(), dwValue ); };
				target->self->SetMaxMana( (WORD)dwValue );
				csAppend.Format( "maximum mana to %u.", dwValue );
			COMPONENT( "MANA", GOD_CAN_EDIT_USER_MANA_FAITH, 1 )
                if( plus ){ dwValue += target->self->GetMana(); }
                if( minus ){ dwValue = SafeMinus( target->self->GetMana(), dwValue ); };
				target->self->SetMana( (WORD)dwValue );
				csAppend.Format( "mana to %u.", dwValue );
			COMPONENT( "LEVEL", GOD_CAN_EDIT_USER_XP_LEVEL, 1 )
                if( plus ){ dwValue += target->self->GetLevel(); }
                if( minus ){ dwValue = SafeMinus( target->self->GetLevel(), dwValue ); };
                if( dwValue != 0 ){
                    target->self->SetLevel( (WORD)dwValue );
				    csAppend.Format( "level to %u.", dwValue );
                }else{
                    csAppend.Format( "level to 0, but change was forbidden." );                    
                }
            COMPONENT( "TITLE", GOD_CAN_EDIT_USER_NAME, 1 )
                target->self->SetTitle( PARAM( 2 ) );
                csAppend.Format( "title to %s.", PARAM( 2 ) );
			COMPONENT( "GUILD", GOD_CAN_EDIT_USER_NAME, 1 )//BLBLBL sysopcmd :: SET $'S GUILD TO
                target->self->SetGuildName( PARAM( 2 ) );
                csAppend.Format( "guild to %s.", PARAM( 2 ) );
            COMPONENT( "MISC DESC", GOD_CAN_EDIT_USER_NAME, 1 )
                target->self->SetListingMiscDesc( PARAM( 2 ) );
                csAppend.Format( "misc. listing description to %s.", PARAM( 2 ) );
            COMPONENT( "PSEUDONAME", GOD_CAN_EDIT_USER_NAME, 1 )
                target->self->SetPseudoName( PARAM( 2 ) );
                csAppend.Format( "pseudoname to %s.", PARAM( 2 ) );
			COMPONENT( "NAME", GOD_CAN_EDIT_USER_NAME, 1 )
                CString csName = PARAM( 2 );
                // Verify that the new name has correct specs.
                CString csCheckName = csName.SpanIncluding(_T("1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ -ïëöéèàùä"));
                if( csCheckName == csName ){
                    if( csName.GetLength() <= 19 && csName.GetLength() > 1 ){
                        // Otherwise, do an exhaustive player name search, asynchronously.
                        SetNameData *lpNameData = new SetNameData;
						
                        // Setup the SetNameData structure
                        lpNameData->sockGod = user->IPaddr;
                        lpNameData->sockTarget = target->IPaddr;
                        lpNameData->csNewName = PARAM( 2 );

                        // Call asynchronous name change function.
                        AsyncFuncQueue::GetMainQueue()->Call( AsyncSetName, lpNameData );
                    }else{
                        CString csMessage;
                        csMessage.Format( "Character names must be between 2 and 19 characters long.", csName.GetLength() );
                        user->self->SendSystemMessage( csMessage );
                    }
                }else{
                    user->self->SendSystemMessage( "Name unchanged, there were invalid characters in new name." );
                }				
			COMPONENT( "APPEARANCE", GOD_CAN_EDIT_USER_APPEARANCE_CORPSE, 1 )
				if( dwValue != 0 ){
					target->self->SetAppearance( dwValue );
					csAppend.Format( "appearance to %u.", dwValue );

                    Broadcast::BCObjectChanged( target->self->GetWL(), _DEFAULT_RANGE,
                        target->self->GetAppearance(),
                        target->self->GetID()
                    );
				}
			COMPONENT( "CORPSE", GOD_CAN_EDIT_USER_APPEARANCE_CORPSE, 1 )
				if( (WORD)dwValue != 0 ){
					csAppend.Format( "corpse to %u.", dwValue );
					target->self->SetCorpse( (WORD)dwValue );
				}
            COMPONENT( "SKILLPOINTS", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ dwValue += target->self->GetSkillPoints(); }
                if( minus ){ dwValue = SafeMinus( target->self->GetSkillPoints(), dwValue ); };
                // Flush all skill points.
                target->self->UseSkillPnts( target->self->GetSkillPoints() );
				// Give new skill points.
                target->self->GiveSkillPoints( dwValue );
				csAppend.Format( "skill points to %u.", dwValue );

            COMPONENT( "STATPOINTS", GOD_CAN_EDIT_USER_STAT, 1 )
                if( plus ){ dwValue += target->self->GetStatPoints(); }
                if( minus ){ dwValue = SafeMinus( target->self->GetStatPoints(), dwValue ); };
                target->self->SetStatPoints( dwValue );

			}else{
                success = false;
				CREATE_MESSAGE( "Invalid user component." );
				SEND_MESSAGE;
			}

			csLogText += csAppend;

			_LOG_GAMEOP
                LOG_SYSOP, 
                (char *)(LPCTSTR)csLogText 
            LOG_
			
			target->Unlock();

		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}
		boFound = TRUE;
	//////////////////////////////////////////////////////////////////////////////////////////	
	// Queries a player's component
	COMMAND( "VIEW $'S $", GOD_CAN_VIEW_USER )
		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
			CString csMessage;
			BOOL boOK = TRUE;
			
			target->Lock();

			TRACE( "\r\nParameters: %s, %s", PARAM( 0 ), PARAM( 1 ) );

			FIRST_COMPONENT( "STR", GOD_CAN_VIEW_USER_STAT, 1 )
				csMessage.Format( "%s's strength = (%u) %u", PARAM( 0 ), target->self->GetSTR(), target->self->GetTrueSTR() );
			COMPONENT( "END", GOD_CAN_VIEW_USER_STAT, 1 )
				csMessage.Format( "%s's endurance = (%u) %u", PARAM( 0 ), target->self->GetEND(), target->self->GetTrueEND() );
			COMPONENT(  "AGI", GOD_CAN_VIEW_USER_STAT, 1 )
				csMessage.Format( "%s's agility = (%u) %u", PARAM( 0 ), target->self->GetAGI(), target->self->GetTrueAGI() );
			COMPONENT( "INT", GOD_CAN_VIEW_USER_STAT, 1 )
				csMessage.Format( "%s's intelligence = (%u) %u", PARAM( 0 ), target->self->GetINT(), target->self->GetTrueINT() );
			COMPONENT( "WIL", GOD_CAN_VIEW_USER_STAT, 1 )
				csMessage.Format( "Willpower is no longer implemented." );
			COMPONENT( "WIS", GOD_CAN_VIEW_USER_STAT, 1 )
				csMessage.Format( "%s's wisdom = (%u) %u", PARAM( 0 ), target->self->GetWIS(), target->self->GetTrueWIS() );
			COMPONENT( "LUCK", GOD_CAN_VIEW_USER_STAT, 1 )
				csMessage.Format( "%s's luck = (%u) %u.", PARAM( 0 ), target->self->GetLCK(), target->self->GetTrueLCK() );
			COMPONENT( "DODGE", GOD_CAN_VIEW_USER_STAT, 1 )
				csMessage.Format( "%s's dodge skill = (%u) %u", PARAM( 0 ), target->self->GetDODGE(), target->self->GetTrueDODGE() );
			COMPONENT( "ATTACK", GOD_CAN_VIEW_USER_STAT, 1 )
				csMessage.Format( "%s's attack skill = (%u) %u", PARAM( 0 ), target->self->GetATTACK(), target->self->GetTrueATTACK() );
            COMPONENT( "KARMA", GOD_CAN_VIEW_USER_STAT, 1 )
                csMessage.Format( "%s's karma = %d", PARAM( 0 ), target->self->GetKarma() );
			COMPONENT( "GOLD", GOD_CAN_VIEW_USER_BACKPACK, 1 )
				csMessage.Format( "%s's gold = %u", PARAM( 0 ), target->self->GetGold() );
			COMPONENT( "XP", GOD_CAN_VIEW_USER_STAT, 1 )
				csMessage.Format( "%s's xp = %u", PARAM( 0 ), target->self->GetXP() );
			COMPONENT( "HP", GOD_CAN_VIEW_USER_STAT, 1 )
				csMessage.Format( "%s's hp = %u/%u(%u)", PARAM( 0 ), target->self->GetHP(), target->self->GetMaxHP(), target->self->GetTrueMaxHP() );
			COMPONENT( "MANA", GOD_CAN_VIEW_USER_STAT, 1 )
				csMessage.Format( "%s's mana = %u/%u(%u)", PARAM( 0 ), target->self->GetMana(), target->self->GetMaxMana(), target->self->GetTrueMaxMana() );
			/* BEGIN : Mestoph -> Removed skill pray for not used in the server
			COMPONENT( "FAITH", GOD_CAN_VIEW_USER_STAT, 1 )
				csMessage.Format( "%s's faith = %u/%u", PARAM( 0 ), target->self->GetFaith(), target->self->GetMaxFaith() );
			END : Mestoph -> Removed skill pray for not used in the server */
			COMPONENT( "LEVEL", GOD_CAN_VIEW_USER_STAT, 1 )
				csMessage.Format( "%s's level = %u", PARAM( 0 ), target->self->GetLevel() );
			COMPONENT( "APPEARANCE", GOD_CAN_VIEW_USER_APPEARANCE_CORPSE, 1 )
				csMessage.Format( "%s's appearance = %u", PARAM( 0 ), target->self->GetAppearance() );
            COMPONENT( "FIRE RESIST", GOD_CAN_VIEW_USER_STAT, 1 )                
                csMessage.Format( "%s's fire resist = %u", PARAM( 0 ), target->self->GetFireResist() );
            COMPONENT( "WATER RESIST", GOD_CAN_VIEW_USER_STAT, 1 )
                csMessage.Format( "%s's water resist = %u", PARAM( 0 ), target->self->GetWaterResist() );            
            COMPONENT( "EARTH RESIST", GOD_CAN_VIEW_USER_STAT, 1 )            
                csMessage.Format( "%s's earth resist = %u", PARAM( 0 ), target->self->GetEarthResist() );
            COMPONENT( "AIR RESIST", GOD_CAN_VIEW_USER_STAT, 1 )
                csMessage.Format( "%s's air resist = %u", PARAM( 0 ), target->self->GetAirResist() );
            COMPONENT( "LIGHT RESIST", GOD_CAN_VIEW_USER_STAT, 1 )
                csMessage.Format( "%s's light resist = %u", PARAM( 0 ), target->self->GetLightResist() );
            COMPONENT( "DARK RESIST", GOD_CAN_VIEW_USER_STAT, 1 )
                csMessage.Format( "%s's dark resist = %u", PARAM( 0 ), target->self->GetDarkResist() );
            COMPONENT( "FIRE", GOD_CAN_VIEW_USER_STAT, 1 )
                csMessage.Format( "%s's fire = %u", PARAM( 0 ), target->self->GetFirePower() );
            COMPONENT( "WATER", GOD_CAN_VIEW_USER_STAT, 1 )
                csMessage.Format( "%s's water = %u", PARAM( 0 ), target->self->GetWaterPower() );                
            COMPONENT( "EARTH", GOD_CAN_VIEW_USER_STAT, 1 )
                csMessage.Format( "%s's earth = %u", PARAM( 0 ), target->self->GetEarthPower() );
            COMPONENT( "AIR", GOD_CAN_VIEW_USER_STAT, 1 )
                csMessage.Format( "%s's air = %u", PARAM( 0 ), target->self->GetAirPower() );
            COMPONENT( "LIGHT", GOD_CAN_VIEW_USER_STAT, 1 )
                csMessage.Format( "%s's light = %u", PARAM( 0 ), target->self->GetLightPower() );
            COMPONENT( "DARK", GOD_CAN_VIEW_USER_STAT, 1 )
                csMessage.Format( "%s's dark = %u", PARAM( 0 ), target->self->GetDarkPower() );
            COMPONENT( "CORPSE", GOD_CAN_VIEW_USER_APPEARANCE_CORPSE, 1 )
				csMessage.Format( "%s's corpse = %u", PARAM( 0 ), target->self->GetCorpse() );            
            COMPONENT( "AC", GOD_CAN_VIEW_USER_STAT, 1 )
                csMessage.Format( "%s's AC = %f", PARAM(0), target->self->GetAC() );
            COMPONENT( "SKILLPOINTS", GOD_CAN_VIEW_USER_STAT, 1 )
                csMessage.Format( "%s's skill points = %u", PARAM(0), target->self->GetSkillPoints() );
            COMPONENT( "STATPOINTS", GOD_CAN_VIEW_USER_STAT, 1 )
                csMessage.Format( "%s's stat points = %u", PARAM(0), target->self->GetStatPoints() );


			// Show the player's backpack
			/*COMPONENT( "BACKPACK", GOD_CAN_VIEW_USER_BACKPACK, 1 )
				TFCPacket sending;

				sending << (RQ_SIZE)RQ_ViewBackpack;
				sending << (char)1;	// Of course player wants to view its backpack!
				sending << (long)target->self->GetID();
				target->self->PacketBackpack( sending );

				user->self->SendPlayerMessage( sending );
				
				boOK = FALSE; */
			// Display's the user's current status.
			/*COMPONENT( "STATUS", GOD_CAN_VIEW_USER_STAT, 1 )
				TFCPacket sending;
				
				target->self->packet_equiped( sending );
				user->self->SendPlayerMessage( sending );

				sending.Destroy();

				target->self->PacketStatus( sending );
				user->self->SendPlayerMessage( sending );				

				boOK = FALSE; */
			//////////////////////////////////////////////////////////////////////////////////////////			
			// Show the user's skills
			/*COMPONENT( "SKILLS", GOD_CAN_VIEW_USER_SKILLS, 1 )
				TFCPacket sending;
				target->self->PacketSkills( sending );
				user->self->SendPlayerMessage( sending );
				
				boOK = FALSE;
			// packet user's spells
			COMPONENT( "SPELLS", GOD_CAN_VIEW_USER_SPELLS, 1 )
				TFCPacket sending;
				target->self->PacketSpells( sending, 1 );
				user->self->SendPlayerMessage( sending );

				boOK = FALSE;  */
			}else{
				boOK = FALSE;
				CREATE_MESSAGE( "Invalid user component." );
				SEND_MESSAGE;
			}

			if( boOK ){
				CREATE_MESSAGE( (LPCTSTR)csMessage );
				SEND_MESSAGE;
			}
			
			target->Unlock();

		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}
		boFound = TRUE;
	
	//////////////////////////////////////////////////////////////////////////////////////////	
	// Ban temporarly user from the game.
	COMMAND( "LOCKOUT $ FOR $ DAYS", GOD_CAN_LOCKOUT_USER )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to lockout %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;
		}

		Players *target = FindCharacter( PARAM( 0 ) );
		int nDaysLocked = atoi( PARAM( 1 ) );

		if (nDaysLocked <= 0) nDaysLocked=1; //BLBLBL le délai de lock minimum en jours est de 1.
		
		if( target != NULL && user->self->boAuthGM == true ){

            if( SUPER_USER ){
                CREATE_MESSAGE( "Sorry but you cannot lock the super user out!" );
                SEND_MESSAGE;
            }else{
                success = true;


    			time_t lTimeCalc;
				time(&lTimeCalc);

				//BLBLBL AccHistory, liste des punitions :
				CString csHistory;
				csHistory.Format( "Locked out for %d days", nDaysLocked);
				target->AddToHistory(lTimeCalc,csHistory);

				lTimeCalc+=nDaysLocked*3600*24;//BLBLBL conversion en secondes du nombre de jours

                target->Lock();
				target->lLockExpireDate = lTimeCalc;
                target->boLockedOut = TRUE;
		        target->dwKickoutTime = 5 SECONDS TDELAY;
			    target->Unlock();

    			CREATE_MESSAGE( "You have been banned from the game for %d day(s).", nDaysLocked );
	    			sending << (RQ_SIZE)RQ_ServerMessage;
		    		sending << (short)30;
			    	sending << (short)3;
    				sending << (CString &)csText;
					sending << (long) RGB( 255, 0, 0 );
	    			target->self->SendPlayerMessage( sending );
                }
    			_LOG_GAMEOP
	    			LOG_SYSOP,
		    		"God %s (%s) locked out account %s from the game for %d day(s).",
			    	(LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
				    (LPCTSTR)target->GetFullAccountName(),
					nDaysLocked
			    LOG_	
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}

	//////////////////////////////////////////////////////////////////////////////////////////	
	// Ban temporarly user from the game.
	COMMAND( "LOCKOUT $ FOR $ HOURS", /*GOD_CAN_LOCKOUT_USER*/ GOD_CAN_ZAP )//BLBLBL : pour les lock temporaires inférieurs à 24H on peut donner cette fonction à ceux pouvant ZAPPER.
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to lockout %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;
		}

		Players *target = FindCharacter( PARAM( 0 ) );
		int nHoursLocked = atoi( PARAM( 1 ) );
		
		if (nHoursLocked > 48) nHoursLocked=48;//BLBLBL limitation en nombre d'heures à 48 heures, ce qui est déjà beaucoup !
		else if (nHoursLocked <= 0) nHoursLocked=1; //BLBLBL on ne peut pas mettre à 0 le nombre d'heures restantes, c'est 1 minimum.
		
		if( target != NULL && user->self->boAuthGM == true ){

            if( SUPER_USER ){
                CREATE_MESSAGE( "Sorry but you cannot lock the super user out!" );
                SEND_MESSAGE;
            }else{
                success = true;


    			time_t lTimeCalc;
				time(&lTimeCalc);

				//BLBLBL AccHistory, liste des punitions :
				CString csHistory;
				csHistory.Format( "Locked out for %d hours", nHoursLocked);
				target->AddToHistory(lTimeCalc,csHistory);

				lTimeCalc+=nHoursLocked*3600;//BLBLBL conversion en secondes du nombre de jours

                target->Lock();
				target->lLockExpireDate = lTimeCalc;
                target->boLockedOut = TRUE;
		        target->dwKickoutTime = 5 SECONDS TDELAY;
			    target->Unlock();

    			CREATE_MESSAGE( "You have been banned from the game for %d hour(s).", nHoursLocked );
	    			sending << (RQ_SIZE)RQ_ServerMessage;
		    		sending << (short)30;
			    	sending << (short)3;
    				sending << (CString &)csText;
					sending << (long) RGB( 255, 0, 0 );
	    			target->self->SendPlayerMessage( sending );
                }
    			_LOG_GAMEOP
	    			LOG_SYSOP,
		    		"God %s (%s) locked out account %s from the game for %d hour(s).",
			    	(LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
				    (LPCTSTR)target->GetFullAccountName(),
					nHoursLocked
			    LOG_	
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}



	//////////////////////////////////////////////////////////////////////////////////////////	
	// Ban user from the game.
	COMMAND( "LOCKOUT $", GOD_CAN_LOCKOUT_USER )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to lockout %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL && user->self->boAuthGM == true ){

            if( SUPER_USER ){
                CREATE_MESSAGE( "Sorry but you cannot lock the super user out!" );
                SEND_MESSAGE;
            }else{
                success = true;


    			time_t lTimeCalc;
				time(&lTimeCalc);

				//BLBLBL AccHistory, liste des punitions :
				CString csHistory;
				csHistory.Format( "Locked out");
				target->AddToHistory(lTimeCalc,csHistory);
                
				target->Lock();
                target->boLockedOut = TRUE;
		    	    target->dwKickoutTime = 5 SECONDS TDELAY;
			       target->Unlock();

    			CREATE_MESSAGE( "You have been permanently banned from the game.", PARAM( 0 ) );
	    			sending << (RQ_SIZE)RQ_ServerMessage;
		    		sending << (short)30;
			    	sending << (short)3;
    				sending << (CString &)csText;
					sending << (long) RGB( 255, 0, 0 );
	    			target->self->SendPlayerMessage( sending );
                }
    			_LOG_GAMEOP
	    			LOG_SYSOP,
		    		"God %s (%s) locked out account %s from the game.",
			    	(LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
				    (LPCTSTR)target->GetFullAccountName()
			    LOG_	
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}

		
	//////////////////////////////////////////////////////////////////////////////////////////	
	// Simply kill player normally
	COMMAND( "SLAY $", GOD_CAN_SLAY_USER )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to slay %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_		
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL && user->self->boAuthGM == true ){
            success = true;

			// Set 0 hp
			target->Lock();
			target->self->SetHP(0, false);
			ATTACK_STRUCTURE asBlow = {1,1,1,1,1};
			target->self->hit( &asBlow, user->self );
			target->Unlock();

			_LOG_GAMEOP
				LOG_SYSOP,
				"God %s (%s) slayed player %s (%s).",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)target->self->GetTrueName(),
				(LPCTSTR)target->GetFullAccountName()				
			LOG_	

		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}

	//////////////////////////////////////////////////////////////////////////////////////////
	// Devel command
	COMMAND( "QUERY BLOCK AT $,$,$", GOD_DEVELOPPER )
		BOOL boError = FALSE;
		WorldPos wlPos = { atoi( PARAM( 0 ) ), atoi( PARAM( 1 ) ), atoi( PARAM( 2 ) ) };
		WorldMap *wlWorld = TFCMAIN::GetWorld( wlPos.world );

		CString csTypeDescription[10];
		csTypeDescription[0]="__BLOCK_NONE";
		csTypeDescription[1]="__BLOCK_ABSOLUTE";
		csTypeDescription[2]="__BLOCK_CAN_FLY_OVER";
		csTypeDescription[3]="__BLOCK_DEEP_WATER";
		csTypeDescription[4]="__BLOCK_SHALLOW_WATER";
		csTypeDescription[5]="__AREA_BUILDING";
		csTypeDescription[6]="__SAFE_HAVEN";
		csTypeDescription[7]="__INDOOR_SAFE_HAVEN";
		csTypeDescription[8]="__AREA_FULL_PVP";
		csTypeDescription[9]="__BLOCK_FORCE_FIELD";

		if( wlWorld != NULL ){		
			if( wlWorld->IsValidPosition( wlPos ) ){
				CREATE_MESSAGE( "Blocking at ( %u, %u, %u ) is %u (%s).", 
					wlPos.X, 
					wlPos.Y, 
					wlPos.world, 
					wlWorld->QueryAreaType( wlPos ),
					csTypeDescription[wlWorld->QueryAreaType( wlPos )]
					
				);
				SEND_MESSAGE;
			}else{
				boError = TRUE;
			}
		}else{
			boError = TRUE;
		}

		if( boError ){
			CREATE_MESSAGE( "%u, %u, %u isn't a valid world position.",
				wlPos.X, wlPos.Y, wlPos.world );
			SEND_MESSAGE;
		}

	//////////////////////////////////////////////////////////////////////////////////////////
	// Devel command BLBLBL Allows to fix a hole if needed.
	COMMAND( "SET BLOCK AT $,$,$ TO $", GOD_DEVELOPPER )
		BOOL boError = FALSE;
		WorldPos wlPos = { atoi( PARAM( 0 ) ), atoi( PARAM( 1 ) ), atoi( PARAM( 2 ) ) };
		WorldMap *wlWorld = TFCMAIN::GetWorld( wlPos.world );
		
		CString csTypeDescription[10];
		csTypeDescription[0]="__BLOCK_NONE";
		csTypeDescription[1]="__BLOCK_ABSOLUTE";
		csTypeDescription[2]="__BLOCK_CAN_FLY_OVER";
		csTypeDescription[3]="__BLOCK_DEEP_WATER";
		csTypeDescription[4]="__BLOCK_SHALLOW_WATER";
		csTypeDescription[5]="__AREA_BUILDING";
		csTypeDescription[6]="__SAFE_HAVEN";
		csTypeDescription[7]="__INDOOR_SAFE_HAVEN";
		csTypeDescription[8]="__AREA_FULL_PVP";
		csTypeDescription[9]="__BLOCK_FORCE_FIELD";

		unsigned char newValue;
		newValue = atoi( PARAM ( 3 ) );

		if (newValue<0) newValue=0;
		else if (newValue>9) newValue=9;
		/*
		__BLOCK_NONE					0
		__BLOCK_ABSOLUTE				1
		__BLOCK_CAN_FLY_OVER			2
		__BLOCK_DEEP_WATER				3
		__BLOCK_SHALLOW_WATER			4
		__AREA_BUILDING					5
		__SAFE_HAVEN					6
		__INDOOR_SAFE_HAVEN				7
		__AREA_FULL_PVP                 8
		__BLOCK_FORCE_FIELD             9
		*/

		if( wlWorld != NULL ){		
			if( wlWorld->IsValidPosition( wlPos ) ){
				
				wlWorld->SetBlocking( wlPos, newValue);

				CREATE_MESSAGE( "Blocking at ( %u, %u, %u ) is now %u (%s).", 
					wlPos.X, 
					wlPos.Y, 
					wlPos.world, 
					wlWorld->QueryAreaType( wlPos ),
					csTypeDescription[wlWorld->QueryAreaType( wlPos )]
				);
				SEND_MESSAGE;
			}else{
				boError = TRUE;
			}
		}else{
			boError = TRUE;
		}

		if( boError ){
			CREATE_MESSAGE( "%u, %u, %u isn't a valid world position.",
				wlPos.X, wlPos.Y, wlPos.world );
			SEND_MESSAGE;
		}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
    // Dumps the packet log.
    COMMAND( "DUMP PACKET LOG", GOD_DEVELOPPER )
        success = true;
        CPacketManager::PrintPacketReport();        

    //////////////////////////////////////////////////////////////////////////////////////////    
    // Query's a player's position.
    COMMAND( "QUERY $'S POS", GOD_CAN_TELEPORT )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to query %s's pos without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL && user->self->boAuthGM == true ){
            CREATE_MESSAGE(
                "User's position is %u, %u, %u.",
                target->self->GetWL().X,
                target->self->GetWL().Y,
                target->self->GetWL().world
            );
            SEND_MESSAGE;
        }else{
		    CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
		    SEND_MESSAGE;
        }

    //////////////////////////////////////////////////////////////////////////////////////////    
    // Queries an item's description.
    COMMAND( "QUERY ITEM $ DESCRIPTION", GOD_CAN_SUMMON_ITEMS )
               
        // Get the item's ID.
        WORD wID = Unit::GetIDFromName( PARAM(0), U_OBJECT, TRUE );

        if( wID != 0 ){
            Objects *obj = new Objects;

            // Try to create the object's instance.
            if( obj->Create( U_OBJECT, wID ) ){
                // Get the object's underlying _item structure.
                _item *lpItem = NULL;

                obj->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItem );

                if( lpItem != NULL ){
                    
                    bool descOK = false;
                    CString csMessage;
                    
                    if( !lpItem->GmItemLocation.empty() ){
                        descOK = true;
                        csMessage.Format( "Item General Location: %s", lpItem->GmItemLocation.c_str() );
                        CREATE_MESSAGE( (LPCTSTR)csMessage );
                        SEND_MESSAGE;
                    }

                    // If no description was sent.
                    if( !descOK ){
                        CREATE_MESSAGE( "No description was found for this item." );
                        SEND_MESSAGE;
                    }
                }else{
                    CREATE_MESSAGE( "Failed to fetch this item's internal structure." );
                    SEND_MESSAGE;
                }
            }else{
                CREATE_MESSAGE( "Could not instantiate this item ID." );
                SEND_MESSAGE;
            }

            obj->DeleteUnit();
        }else{
            CREATE_MESSAGE( "This item ID does not exist" );
            SEND_MESSAGE;
        }
    //////////////////////////////////////////////////////////////////////////////////////////
    // Sets the gameop's viewing context.
    COMMAND( "SET CONTEXT TO $", GOD_CAN_VIEW_USER )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to set context to %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

	    Players *target = FindCharacter( PARAM( 0 ) );
        
        if( target != NULL && user->self->boAuthGM == true ){
            // Set the gameop's context.
            user->self->SetGameOpContext( target->self );

            user->self->SetGold( user->self->GetGold() );

			success = true;
        }else{
		    CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
		    SEND_MESSAGE;
        }

        
    COMMAND( "RESET CONTEXT", GOD_CAN_VIEW_USER )
        user->self->SetGameOpContext( NULL );

        user->self->SetGold( user->self->GetGold() );

		success = true;

	//////////////////////////////////////////////////////////////////////////////////////////
	// Give a skill or spell
	COMMAND( "GIVE SKILL $ TO $", GOD_CAN_EDIT_USER_SKILLS )	
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to give a skill to %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 1 )
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		WORD wSpellID = atoi( PARAM( 0 ) );

		// If the spellID is 0, then perhaps a spell name was provided.
        if( wSpellID == 0 ){
            // Retreive the spell by its name.
            LPSKILL lpSkill = Skills::GetSkillByName( PARAM( 0 ), user->self->GetLang() );
            if( lpSkill != NULL ){
                wSpellID = lpSkill->nSkillID;
            }
        }	
    
		if( wSpellID != 0 ){
			Players *target = FindCharacter( PARAM( 1 ) );

			if( target != NULL && user->self->boAuthGM == true ){
				// Set 0 hp
				target->Lock();
				
                CString errMsg;
				if( target->self->LearnSkill( wSpellID, 0, false, errMsg ) == NULL ){
					CREATE_MESSAGE( "Could not create skill on user. %s", (LPCTSTR)errMsg );
					SEND_MESSAGE;
                }else{
                    success = true;

			        _LOG_GAMEOP
				        LOG_SYSOP,
				        "God %s (%s) gave skill ID %u to %s (%s).",
				        (LPCTSTR)user->self->GetTrueName(),
				        (LPCTSTR)user->GetFullAccountName(),
                        wSpellID,
				        (LPCTSTR)target->self->GetTrueName(),
				        (LPCTSTR)target->GetFullAccountName()				
			        LOG_	
                }

				target->Unlock();

			}else{
				CREATE_MESSAGE( "User %s is not online.", PARAM( 1 ) );
				SEND_MESSAGE;
			}
		}else{
			CREATE_MESSAGE( "Skill/Spell ID isn't valid" );
			SEND_MESSAGE;
		}

	//////////////////////////////////////////////////////////////////////////////////////////
    // Give a spell to an user
	COMMAND( "GIVE SPELL $ TO $", GOD_CAN_EDIT_USER_SPELLS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to give a spell on %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 1 )
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		WORD wSpellID = atoi( PARAM( 0 ) );
				
		// If the spellID is 0, then perhaps a spell name was provided.
        if( wSpellID == 0 ){
            // Retreive the spell by its name.
            LPSPELL_STRUCT lpSpell = SpellMessageHandler::GetSpellByName( PARAM( 0 ), user->self->GetLang() );
            if( lpSpell != NULL ){
                wSpellID = lpSpell->wSpellID;
            }
        }
        if( wSpellID != 0 ){
			Players *target = FindCharacter( PARAM( 1 ) );

			if( target != NULL && user->self->boAuthGM == true ){

				// Set 0 hp
				target->Lock();
				
                CString errMsg;
				if( target->self->LearnSkill( wSpellID, 0, false, errMsg ) == NULL ){
					CREATE_MESSAGE( "Could not create spell on user. %s", (LPCTSTR)errMsg );
					SEND_MESSAGE;
                }else{
                    success = true;

			        _LOG_GAMEOP
				        LOG_SYSOP,
				        "God %s (%s) gave spell ID %u to %s (%s).",
				        (LPCTSTR)user->self->GetTrueName(),
				        (LPCTSTR)user->GetFullAccountName(),
                        wSpellID,
				        (LPCTSTR)target->self->GetTrueName(),
				        (LPCTSTR)target->GetFullAccountName()				
			        LOG_
                }

				target->Unlock();

			}else{
				CREATE_MESSAGE( "User %s is not online.", PARAM( 1 ) );
				SEND_MESSAGE;
			}
		}else{
			CREATE_MESSAGE( "Spell ID isn't valid" );
			SEND_MESSAGE;
		}
	//////////////////////////////////////////////////////////////////////////////////////////
    // Give a spell to self
	COMMAND( "GIVE SPELL $", GOD_CAN_EDIT_USER_SPELLS )	
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to give a spell to himself without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName()				
			LOG_			

			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		WORD wSpellID = atoi( PARAM( 0 ) );
				
		// If the spellID is 0, then perhaps a spell name was provided.
        if( wSpellID == 0 )
		{
            // Retreive the spell by its name.
            LPSPELL_STRUCT lpSpell = SpellMessageHandler::GetSpellByName( PARAM( 0 ), user->self->GetLang() );
            if( lpSpell != NULL ){
                wSpellID = lpSpell->wSpellID;
            }
        }
        if( wSpellID != 0 && user->self->boAuthGM == true )
		{
			user->self->Lock();

			CString errMsg;
			if( user->self->LearnSkill( wSpellID, 0, false, errMsg ) == NULL )
			{
				CREATE_MESSAGE( "Could not create spell on user. %s", (LPCTSTR)errMsg );
				SEND_MESSAGE;
			}
			else
			{
				success = true;

			    _LOG_GAMEOP
				    LOG_SYSOP,
				    "God %s (%s) gave spell ID %u to himself.",
				    (LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
                    wSpellID				    				
			    LOG_
            }

			user->self->Unlock();			
		}else{
			CREATE_MESSAGE( "Spell ID isn't valid" );
			SEND_MESSAGE;
		}
    //////////////////////////////////////////////////////////////////////////////////////////
    // Remove spell from a user
    COMMAND( "REMOVE SPELL $ FROM $", GOD_CAN_EDIT_USER_SPELLS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to remove spell from %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 1 )
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		WORD wSpellID = atoi( PARAM( 0 ) );

        // If the spellID is 0, then perhaps a spell name was provided.
        if( wSpellID == 0 ){
            // Retreive the spell by its name.
            LPSPELL_STRUCT lpSpell = SpellMessageHandler::GetSpellByName( PARAM( 0 ), user->self->GetLang() );
            if( lpSpell != NULL ){
                wSpellID = lpSpell->wSpellID;
            }
        }
				
		if( wSpellID != 0 && user->self->boAuthGM == true ){
			Players *target = FindCharacter( PARAM( 1 ) );

			if( target != NULL ){				
				target->Lock();
				
                // Fetch the user's spells
                TemplateList< USER_SKILL > *lpSpells = target->self->GetSpells();

                lpSpells->Lock();

                bool found = false;
                // Try to find the user's spell in the list of spells.
                lpSpells->ToHead();
                while( lpSpells->QueryNext() ){
                    if( lpSpells->Object()->GetSkillID() == wSpellID ){
                        // Remove spell
                        found = true;
                        lpSpells->DeleteAbsolute();                        
                    }
                }
                lpSpells->Unlock();

				target->Unlock();

                if( !found ){
                    CREATE_MESSAGE( "Spell was not found on user." );
                    SEND_MESSAGE;
                }else{
                    success = true;
                }
			}else{
				CREATE_MESSAGE( "User %s is not online.", PARAM( 1 ) );
				SEND_MESSAGE;
			}
		}else{
			CREATE_MESSAGE( "Spell ID isn't valid" );
			SEND_MESSAGE;
		}
    //////////////////////////////////////////////////////////////////////////////////////////
    // Removes the lighting effect from a torch
    COMMAND( "REMOVE LIGHT FROM $", GOD_DEVELOPPER )
        Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){				
		    target->Lock();

            target->self->RemoveBoostFromStat( STAT_RADIANCE );

            target->Unlock();
        }


    //////////////////////////////////////////////////////////////////////////////////////////    
    // Allows in game shutdown of server which will save their characters and warn them.
    COMMAND( "SHUTDOWN $", GOD_CAN_SHUTDOWN )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to shutdown server without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName()				
			LOG_	

			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

			
			return false;
		}		
    
        // Shutdown now stops right now :P
        if( stricmp( PARAM( 0 ), "NOW" ) == 0 || stricmp( PARAM( 0 ), "FAST" ) == 0 ){

			bool waitBeforeRelaunch = true;
			if (stricmp( PARAM( 0 ), "FAST" ) == 0 ) {
	            waitBeforeRelaunch = false;
			} 
            CShutdown::CreateShutdown( SHUTDOWN_NOW, true, /*waitBeforeRelaunch,*/ true );
            CShutdown::StartShutdown();

            _LOG_GAMEOP
			    LOG_SYSOP,
			    "God %s (%s) issued a shutdown ( NOW %s).",
			    (LPCTSTR)user->self->GetTrueName(),
			    (LPCTSTR)user->GetFullAccountName(),
				waitBeforeRelaunch == false ? "FAST " : ""
		    LOG_	
        }else 
        // If we should cancel a current shutdown    
        if( stricmp( PARAM( 0 ), "CANCEL" ) == 0 ){

            CShutdown::CancelShutdown( true );

			_LOG_GAMEOP
				LOG_SYSOP,
				"God %s (%s) cancelled shutdown.",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName()
			LOG_	
        }
        // Otherwise check if we need to shutdown in some time now.
        else{
            int nTime = atoi( PARAM( 0 ));

            // If time value is invalid
            if( nTime < 1 || nTime > 30 ){
				CREATE_MESSAGE( "You must supply a valid time value ranging from 1 to 30 minutes or NOW." );
				SEND_MESSAGE;
            }else{
        	    _LOG_GAMEOP
        		    LOG_SYSOP,
				    "God %s (%s) issued a server shutdown( %u ).",
				    (LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
                    nTime
			    LOG_	

                if( CShutdown::CreateShutdown( nTime, true, /*true,*/ true ) ){
                    CShutdown::StartShutdown();
                }else{
                    CREATE_MESSAGE( "Unable to reset shutdown timer. This shutdown cannot be overriden" );
                    SEND_MESSAGE;
                }
            }
        }

#define GIVE_GOD_FLAG( __flag, __msg ) target->SetGodMode( TRUE ); target->SetGodFlags( target->GetGodFlags() | __flag );\
    csMessage = __msg;\
    boGiven = TRUE;

#define GIVE_GOD_EDITFLAG( __flag, __msg ) target->SetGodMode( TRUE );\
    target->SetGodFlags( target->GetGodFlags() | GOD_CAN_EDIT_USER );\
    target->SetGodFlags( target->GetGodFlags() | __flag );\
    csMessage = __msg;\
    boGiven = TRUE;

#define GIVE_GOD_VIEWFLAG( __flag, __msg ) target->SetGodMode( TRUE );\
    target->SetGodFlags( target->GetGodFlags() | GOD_CAN_VIEW_USER );\
    target->SetGodFlags( target->GetGodFlags() | __flag );\
    csMessage = __msg;\
    boGiven = TRUE;


    //////////////////////////////////////////////////////////////////////////////////////////
    // Allow a super-god to give god flags.
    COMMAND( "GIVE GAMEOP FLAG $ TO $", GOD_CAN_GIVE_GOD_FLAGS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to give god flag to %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 1 )
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		Players *target = FindCharacter( PARAM( 1 ) );

		if( target != NULL && user->self->boAuthGM == true ){
            BOOL boGiven = FALSE;
            CString csMessage;            

			target->Lock();

            FIRST_COMPONENT( "GOD_NO_CLIP", GOD_CAN_GIVE_GOD_FLAGS, 0 )
                GIVE_GOD_FLAG( GOD_NO_CLIP, "God now walks through walls." );                
            
            COMPONENT( "GOD_NO_MONSTERS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_NO_MONSTERS, "God doesn't spawn monsters anymore." )
            
            COMPONENT( "GOD_CAN_TELEPORT", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_TELEPORT, "God can now teleport." );

            COMPONENT( "GOD_CAN_TELEPORT_USER", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_TELEPORT_USER, "God can now teleport other users." );

            COMPONENT( "GOD_CAN_ZAP", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_ZAP, "God can now kickout users." );

            COMPONENT( "GOD_CAN_SQUELCH", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_SQUELCH, "God can now remove a user's ability to talk." );

            COMPONENT( "GOD_CAN_REMOVE_SHOUTS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_REMOVE_SHOUTS, "God can now remove a user's ability to shout." );

            COMPONENT( "GOD_CAN_SUMMON_MONSTERS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_SUMMON_MONSTERS, "God can now summon monsters." );
                
            COMPONENT( "GOD_CAN_SUMMON_ITEMS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_SUMMON_ITEMS, "God can now summon items." );

            COMPONENT( "GOD_CAN_SET_USER_FLAG", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_SET_USER_FLAG, "God can now set a player's flag." );

            COMPONENT( "GOD_CAN_EDIT_USER_STAT", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_STAT, "God can now edit stats." );

            COMPONENT( "GOD_CAN_EDIT_USER_HP", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_HP, "God can now edit hit points." );

            COMPONENT( "GOD_CAN_EDIT_USER_MANA", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_MANA_FAITH, "God can now edit mana." );

            COMPONENT( "GOD_CAN_EDIT_USER_XP_LEVEL", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_XP_LEVEL, "God can now edit experience or level." );

            COMPONENT( "GOD_CAN_EDIT_USER_NAME", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_NAME, "God can now edit a user's name." );

            COMPONENT( "GOD_CAN_EDIT_USER_APPEARANCE_CORPSE", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_APPEARANCE_CORPSE, "God can now edit appearances." );

            COMPONENT( "GOD_CAN_EDIT_USER_SPELLS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_SPELLS, "God can now edit spells." );

            COMPONENT( "GOD_CAN_EDIT_USER_SKILLS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_SKILLS, "God can now edit skills." );

            COMPONENT( "GOD_CAN_EDIT_USER_BACKPACK", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_BACKPACK, "God can now edit backpacks." );

            COMPONENT( "GOD_CAN_VIEW_USER_STAT", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_VIEWFLAG( GOD_CAN_VIEW_USER_STAT, "God can now view stats." );

            COMPONENT( "GOD_CAN_VIEW_USER_BACKPACK", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_VIEWFLAG( GOD_CAN_VIEW_USER_BACKPACK, "God can now view backpack." );

            COMPONENT( "GOD_CAN_VIEW_USER_SPELLS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_VIEWFLAG( GOD_CAN_VIEW_USER_SPELLS, "God can now view spells." );

            COMPONENT( "GOD_CAN_VIEW_USER_SKILLS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_VIEWFLAG( GOD_CAN_VIEW_USER_SKILLS, "God can now view skills." );

            COMPONENT( "GOD_CAN_VIEW_USER_APPEARANCE_CORPSE", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_VIEWFLAG( GOD_CAN_VIEW_USER_APPEARANCE_CORPSE, "God can now view appearance IDs." );

            COMPONENT( "GOD_CAN_LOCKOUT_USER", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_LOCKOUT_USER, "God can lockout other users." );

            COMPONENT( "GOD_CAN_SLAY_USER", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_SLAY_USER, "God can now slay other players." );

                    TFCPacket sending;
                    sending << (RQ_SIZE)RQ_GodFlagUpdate;
                    sending << (char)UPDATE_GOD_CAN_SLAY_USER;
                    sending << (char)1;
                    
                    target->self->SendPlayerMessage( sending );

            COMPONENT( "GOD_CAN_COPY_USER", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_COPY_USER, "God can copy a player's stats." );

            COMPONENT( "GOD_CAN_EMULATE_MONSTER", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_EMULATE_MONSTER, "God can emulate a monster's stats and appearance." );

            COMPONENT( "GOD_INVINCIBLE", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_INVINCIBLE, "God is now immune to damage and death." );

            COMPONENT( "GOD_CANNOT_DIE", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CANNOT_DIE, "God is now immune to death (but not damage)." );

            COMPONENT( "GOD_CAN_RUN_CLIENT_SCRIPTS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_RUN_CLIENT_SCRIPTS, "God can now use the !RUN command." );

                TFCPacket sending;
                sending << (RQ_SIZE)RQ_GodFlagUpdate;
                sending << (char)UPDATE_GOD_CAN_RUN_CLIENT_SCRIPTS;
                sending << (char)1;
                
                target->self->SendPlayerMessage( sending );
                
            COMPONENT( "GOD_DEVELOPPER", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_DEVELOPPER, "God now has developper capabilities." );

            COMPONENT( "GOD_CAN_SHUTDOWN", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_SHUTDOWN, "God can now shutdown the T4C Server." );

            COMPONENT( "GOD_CAN_SEE_ACCOUNTS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_SEE_ACCOUNTS, "God can now see true accounts in the player listing." );

            COMPONENT( "GOD_UNLIMITED_SHOUTS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_UNLIMITED_SHOUTS, "God now has unlimited shouts." );
            
            COMPONENT( "GOD_TRUE_INVISIBILITY", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_TRUE_INVISIBILITY, "God now invisible to all players." );
            COMPONENT( "GOD_CAN_GIVE_GOD_FLAGS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_GIVE_GOD_FLAGS, "God can now give any gameop flag to other players." );
            COMPONENT( "GOD_CAN_EMULATE_SYSTEM", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CAN_EMULATE_SYSTEM, "God can now emulate system functions." );
            COMPONENT( "GOD_CHAT_MASTER", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_CHAT_MASTER, "God can now have access to all chatter channels." );
            COMPONENT( "GOD_BOOST_XP", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_BOOST_XP, "God will now receive a lot more XP from kills and attacks." );
            COMPONENT( "GOD_MODERATOR_GUARDIAN", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_MODERATOR_GUARDIAN, "God is now able to promote and demote moderators." );
            COMPONENT( "GOD_ROYAL_GUARD_CHIEF", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                GIVE_GOD_FLAG( GOD_ROYAL_GUARD_CHIEF, "User is now Royal Guard chief and can promote or demote royal guards." );
            }
            

			target->Unlock();

            if( boGiven ){
    			_LOG_GAMEOP
	    			LOG_SYSOP,
		    		"God %s (%s) gave gameop flag %s to %s (%s).",
			    	(LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
                    PARAM( 0 ),
    				(LPCTSTR)target->self->GetTrueName(),
	    			(LPCTSTR)target->GetFullAccountName()		    		
			    LOG_

                CREATE_MESSAGE( csMessage );
                SEND_MESSAGE;
            }else{
    			CREATE_MESSAGE( "%s is not a valid gameop flag.", PARAM( 0 ) );
	    		SEND_MESSAGE;
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 1 ) );
			SEND_MESSAGE;
		}

#define REMOVE_GOD_FLAG( __flag, __msg ) target->SetGodFlags( target->GetGodFlags() & (~static_cast< __int64 >( __flag ) ) );\
    csMessage = __msg;\
    if( target->GetGodFlags() == (__int64)(0) ){\
        target->SetGodMode( FALSE );\
    }\
    boGiven = TRUE;

    //////////////////////////////////////////////////////////////////////////////////////////
    // Allow a super-god to remove god flags.
    COMMAND( "REMOVE GAMEOP FLAG $ FROM $", GOD_CAN_GIVE_GOD_FLAGS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to remove gameop flag from %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 1 )
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		Players *target = FindCharacter( PARAM( 1 ) );

		if( target != NULL && user->self->boAuthGM == true ){
            BOOL boGiven = FALSE;
            CString csMessage;            

			target->Lock();

            if( stricmp( 
                    (LPCTSTR)target->GetFullAccountName(), 
                    CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str()
                ) != 0 || stricmp( 
                    (LPCTSTR)user->GetFullAccountName(), 
                    CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str()
                ) == 0 
           ){


                FIRST_COMPONENT( "GOD_NO_CLIP", GOD_CAN_GIVE_GOD_FLAGS, 0 )
                    REMOVE_GOD_FLAG( GOD_NO_CLIP, "God no long walks through walls." );                
            
                COMPONENT( "GOD_NO_MONSTERS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_NO_MONSTERS, "God now spawns monsters." )
            
                COMPONENT( "GOD_CAN_TELEPORT", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_TELEPORT, "God can no longer teleport." );

                COMPONENT( "GOD_CAN_TELEPORT_USER", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_TELEPORT_USER, "God can no longer teleport other users." );

                COMPONENT( "GOD_CAN_ZAP", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_ZAP, "God can no longer kickout users." );

                COMPONENT( "GOD_CAN_SQUELCH", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_SQUELCH, "God can no longer remove a user's ability to talk." );

                COMPONENT( "GOD_CAN_REMOVE_SHOUTS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_REMOVE_SHOUTS, "God can no longer remove a user's ability to shout." );

                COMPONENT( "GOD_CAN_SUMMON_MONSTERS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_SUMMON_MONSTERS, "God can no longer summon monsters." );
                
                COMPONENT( "GOD_CAN_SUMMON_ITEMS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_SUMMON_ITEMS, "God can no longer summon items." );

                COMPONENT( "GOD_CAN_SET_USER_FLAG", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_SET_USER_FLAG, "God can no longer set a player's flag." );

                COMPONENT( "GOD_CAN_EDIT_USER_STAT", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_EDIT_USER_STAT, "God can no longer edit stats." );

                COMPONENT( "GOD_CAN_EDIT_USER_HP", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_EDIT_USER_HP, "God can no longer edit hit points." );

                COMPONENT( "GOD_CAN_EDIT_USER_MANA", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_EDIT_USER_MANA_FAITH, "God can no longer edit mana." );

                COMPONENT( "GOD_CAN_EDIT_USER_XP_LEVEL", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_EDIT_USER_XP_LEVEL, "God can no longer edit experience or level." );

                COMPONENT( "GOD_CAN_EDIT_USER_NAME", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_EDIT_USER_NAME, "God can no longer edit a user's name." );

                COMPONENT( "GOD_CAN_EDIT_USER_APPEARANCE_CORPSE", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_EDIT_USER_APPEARANCE_CORPSE, "God can no longer edit appearances." );

                COMPONENT( "GOD_CAN_EDIT_USER_SPELLS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_EDIT_USER_SPELLS, "God can no longer edit spells." );

                COMPONENT( "GOD_CAN_EDIT_USER_SKILLS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_EDIT_USER_SKILLS, "God can no longer edit skills." );

                COMPONENT( "GOD_CAN_EDIT_USER_BACKPACK", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_EDIT_USER_BACKPACK, "God can no longer edit backpacks." );

                COMPONENT( "GOD_CAN_VIEW_USER_STAT", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_VIEW_USER_STAT, "God can no longer view stats." );

                COMPONENT( "GOD_CAN_VIEW_USER_BACKPACK", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_VIEW_USER_BACKPACK, "God can no longer view backpack." );

                COMPONENT( "GOD_CAN_VIEW_USER_SPELLS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_VIEW_USER_SPELLS, "God can no longer view spells." );

                COMPONENT( "GOD_CAN_VIEW_USER_SKILLS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_VIEW_USER_SKILLS, "God can no longer view skills." );

                COMPONENT( "GOD_CAN_VIEW_USER_APPEARANCE_CORPSE", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_VIEW_USER_APPEARANCE_CORPSE, "God can no longer view appearance IDs." );

                COMPONENT( "GOD_CAN_LOCKOUT_USER", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_LOCKOUT_USER, "God can no longer lockout other users." );

                COMPONENT( "GOD_CAN_SLAY_USER", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_SLAY_USER, "God can no longer slay other players." );

                    TFCPacket sending;
                    sending << (RQ_SIZE)RQ_GodFlagUpdate;
                    sending << (char)UPDATE_GOD_CAN_SLAY_USER;
                    sending << (char)0;
                    
                    target->self->SendPlayerMessage( sending );

                COMPONENT( "GOD_CAN_COPY_USER", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_COPY_USER, "God can no longer copy a player's stats." );

                COMPONENT( "GOD_CAN_EMULATE_MONSTER", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_EMULATE_MONSTER, "God can no longer emulate a monster's stats and appearance." );

                COMPONENT( "GOD_INVINCIBLE", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_INVINCIBLE, "God is now vulnerable to damage." );
                
                COMPONENT( "GOD_CANNOT_DIE", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CANNOT_DIE, "God is now vulnerable to death." );
                
                COMPONENT( "GOD_CAN_RUN_CLIENT_SCRIPTS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_RUN_CLIENT_SCRIPTS, "God can no longer use the !RUN command." );

                    TFCPacket sending;
                    sending << (RQ_SIZE)RQ_GodFlagUpdate;
                    sending << (char)UPDATE_GOD_CAN_RUN_CLIENT_SCRIPTS;
                    sending << (char)0;
                    
                    target->self->SendPlayerMessage( sending );

                COMPONENT( "GOD_DEVELOPPER", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_DEVELOPPER, "God no longer has developper capabilities." );

                COMPONENT( "GOD_CAN_SHUTDOWN", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_SHUTDOWN, "God can no longer shutdown the T4C Server." );

                COMPONENT( "GOD_CAN_SEE_ACCOUNTS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_SEE_ACCOUNTS, "God can no longer see true accounts in the player listing." );

                COMPONENT( "GOD_UNLIMITED_SHOUTS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_UNLIMITED_SHOUTS, "God now complies to default shouting policies." );

                COMPONENT( "GOD_TRUE_INVISIBILITY", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_TRUE_INVISIBILITY, "God now has normal visibility." );

                COMPONENT( "GOD_CAN_EMULATE_SYSTEM", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CAN_EMULATE_SYSTEM, "God can no longer emulate system functions." );                
                
                COMPONENT( "GOD_CHAT_MASTER", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_CHAT_MASTER, "God can no longer have access to all chatter channels." );

                COMPONENT( "GOD_BOOST_XP", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_BOOST_XP, "God now gains normal XP from kills and attacks." );
                
			    COMPONENT( "GOD_MODERATOR_GUARDIAN", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_MODERATOR_GUARDIAN, "God is no longer a moderator guardian." );
                COMPONENT( "GOD_ROYAL_GUARD_CHIEF", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    REMOVE_GOD_FLAG( GOD_ROYAL_GUARD_CHIEF, "God is no longer Royal guard chief." );
                    
                COMPONENT( "GOD_CAN_GIVE_GOD_FLAGS", GOD_CAN_GIVE_GOD_FLAGS, 0 );
                    if( stricmp( 
                        (LPCTSTR)target->GetFullAccountName(), 
                        CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str() 
                    ) != 0 ){                
                        REMOVE_GOD_FLAG( GOD_CAN_GIVE_GOD_FLAGS, "God can no longer give any gameop flag to other players." );
                    }else{
                        csMessage = "Sorry but you can't remove this flag from this god.";
                        boGiven = TRUE;
                    }			    			
                }
            }else{
    			CREATE_MESSAGE( "You cannot remove god flags from the super user." );
	    		SEND_MESSAGE;
            }

			target->Unlock();

            if( boGiven ){
    			_LOG_GAMEOP
	    			LOG_SYSOP,
		    		"God %s (%s) removed gameop flag %s from %s (%s).",
			    	(LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
                    PARAM( 0 ),
    				(LPCTSTR)target->self->GetTrueName(),
	    			(LPCTSTR)target->GetFullAccountName()		    		
			    LOG_

                CREATE_MESSAGE( csMessage );
                SEND_MESSAGE;
            }else{
    			CREATE_MESSAGE( "%s is not a valid gameop flag.", PARAM( 0 ) );
	    		SEND_MESSAGE;
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 1 ) );
			SEND_MESSAGE;
		}
    //////////////////////////////////////////////////////////////////////////////////////////
    // Make the user an HGM (gives all flags)
    COMMAND( "GIVE USER $ HGM POWERS", GOD_CAN_GIVE_GOD_FLAGS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to give HGM powers to %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		Players *target;
			
		target = FindCharacter( PARAM( 0 ) );

		if( target != NULL && user->self->boAuthGM == true ){			
			target->Lock();
            BOOL boGiven = FALSE;
            CString csMessage;            

            GIVE_GOD_FLAG( GOD_NO_CLIP, "God now walks through walls." );                
  //              GIVE_GOD_FLAG( GOD_NO_MONSTERS, "God doesn't spawn monsters anymore." )
            GIVE_GOD_FLAG( GOD_CAN_TELEPORT, "God can now teleport." );
            GIVE_GOD_FLAG( GOD_CAN_TELEPORT_USER, "God can now teleport other users." );
            GIVE_GOD_FLAG( GOD_CAN_ZAP, "God can now kickout users." );
            GIVE_GOD_FLAG( GOD_CAN_SQUELCH, "God can now remove a user's ability to talk." );
            GIVE_GOD_FLAG( GOD_CAN_REMOVE_SHOUTS, "God can now remove a user's ability to shout." );
            GIVE_GOD_FLAG( GOD_CAN_SUMMON_MONSTERS, "God can now summon monsters." );
            GIVE_GOD_FLAG( GOD_CAN_SUMMON_ITEMS, "God can now summon items." );
            GIVE_GOD_FLAG( GOD_CAN_SET_USER_FLAG, "God can now set a player's flag." );
            GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_STAT, "God can now edit stats." );
            GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_HP, "God can now edit hit points." );
            GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_MANA_FAITH, "God can now edit mana." );
            GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_XP_LEVEL, "God can now edit experience or level." );
            GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_NAME, "God can now edit a user's name." );
            GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_APPEARANCE_CORPSE, "God can now edit appearances." );
            GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_SPELLS, "God can now edit spells." );
            GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_SKILLS, "God can now edit skills." );
            GIVE_GOD_EDITFLAG( GOD_CAN_EDIT_USER_BACKPACK, "God can now edit backpacks." );
            GIVE_GOD_VIEWFLAG( GOD_CAN_VIEW_USER_STAT, "God can now view stats." );
            GIVE_GOD_VIEWFLAG( GOD_CAN_VIEW_USER_BACKPACK, "God can now view backpack." );
            GIVE_GOD_VIEWFLAG( GOD_CAN_VIEW_USER_SPELLS, "God can now view spells." );
            GIVE_GOD_VIEWFLAG( GOD_CAN_VIEW_USER_SKILLS, "God can now view skills." );
            GIVE_GOD_VIEWFLAG( GOD_CAN_VIEW_USER_APPEARANCE_CORPSE, "God can now view appearance IDs." );
            GIVE_GOD_FLAG( GOD_CAN_LOCKOUT_USER, "God can lockout other users." );
            GIVE_GOD_FLAG( GOD_CAN_SLAY_USER, "God can now slay other players." );
			{
                TFCPacket sending;
                sending << (RQ_SIZE)RQ_GodFlagUpdate;
                sending << (char)UPDATE_GOD_CAN_SLAY_USER;
                sending << (char)1;
                
                target->self->SendPlayerMessage( sending );
			}
            GIVE_GOD_FLAG( GOD_CAN_COPY_USER, "God can copy a player's stats." );
            GIVE_GOD_FLAG( GOD_CAN_EMULATE_MONSTER, "God can emulate a monster's stats and appearance." );
            GIVE_GOD_FLAG( GOD_INVINCIBLE, "God is now immune to damage and death." );
            GIVE_GOD_FLAG( GOD_CANNOT_DIE, "God is now immune to death (but not damage)." );
            GIVE_GOD_FLAG( GOD_CAN_RUN_CLIENT_SCRIPTS, "God can now use the !RUN command." );
			{
				TFCPacket sending;
				sending << (RQ_SIZE)RQ_GodFlagUpdate;
				sending << (char)UPDATE_GOD_CAN_RUN_CLIENT_SCRIPTS;
				sending << (char)1;
            
				target->self->SendPlayerMessage( sending );
            }
            GIVE_GOD_FLAG( GOD_DEVELOPPER, "God now has developper capabilities." );
            GIVE_GOD_FLAG( GOD_CAN_SHUTDOWN, "God can now shutdown the T4C Server." );
            GIVE_GOD_FLAG( GOD_CAN_SEE_ACCOUNTS, "God can now see true accounts in the player listing." );
            GIVE_GOD_FLAG( GOD_UNLIMITED_SHOUTS, "God now has unlimited shouts." );
//                GIVE_GOD_FLAG( GOD_TRUE_INVISIBILITY, "God now invisible to all players." );
            GIVE_GOD_FLAG( GOD_CAN_GIVE_GOD_FLAGS, "God can now give any gameop flag to other players." );
            GIVE_GOD_FLAG( GOD_CAN_EMULATE_SYSTEM, "God can now emulate system functions." );
            GIVE_GOD_FLAG( GOD_CHAT_MASTER, "God can now have access to all chatter channels." );
            GIVE_GOD_FLAG( GOD_BOOST_XP, "God will now receive a lot more XP from kills and attacks." );

           

			target->Unlock();

			CREATE_MESSAGE( "User %s has now HGM Powers!", PARAM( 0 ) );
			SEND_MESSAGE;

    		_LOG_GAMEOP
	    		LOG_SYSOP,
		    	"God %s (%s) gave HGM Powers to %s (%s).",
			    (LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
    			(LPCTSTR)target->self->GetTrueName(),
	    		(LPCTSTR)target->GetFullAccountName()		    		
			LOG_


		}else{
			CREATE_MESSAGE( "User %s is not online", PARAM( 0 ) );
			SEND_MESSAGE;
		}
    //////////////////////////////////////////////////////////////////////////////////////////
    // Allows a god to become invisible in the Online user listing.
    COMMAND( "REMOVE $ FROM USER LISTING", GOD_CAN_SEE_ACCOUNTS )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to remove %s from user listing without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL && user->self->boAuthGM == true ){
            success = true;

    		_LOG_GAMEOP
	    		LOG_SYSOP,
		    	"God %s (%s) removed %s (%s) from the online user listing.",
			    (LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
    			(LPCTSTR)target->self->GetTrueName(),
	    		(LPCTSTR)target->GetFullAccountName()		    		
			LOG_

            target->boWhoInvisible = true;
        }else{


        }

    //////////////////////////////////////////////////////////////////////////////////////////
    // Restore's the god in the user listing.
    COMMAND( "RESTORE $ TO USER LISTING", GOD_CAN_SEE_ACCOUNTS )
		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
            success = true;

    		_LOG_GAMEOP
	    		LOG_SYSOP,
		    	"God %s (%s) restored %s (%s) to the online listing.",
			    (LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
    			(LPCTSTR)target->self->GetTrueName(),
	    		(LPCTSTR)target->GetFullAccountName()		    		
			LOG_

            target->boWhoInvisible = false;
        }else{
            CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
            SEND_MESSAGE;
        }

	//////////////////////////////////////////////////////////////////////////////////////////
    // Turn pvp drops on/off
	COMMAND( "SWITCH PVP DROPS $", GOD_CAN_EDIT_USER )		

		if( stricmp( PARAM( 0 ), "on" ) == 0 )
		{
			theApp.dwPVPDropDisabled = 0;			
			success = true;

			WorldPos wlPos = { 0, 0, 0 };
			Broadcast::BCServerMessage( wlPos, 0, "PVP Drops have been turned on!", NULL, RGB( 255, 0, 0 ) );
		}
		else if( stricmp( PARAM( 0 ), "off" ) == 0 )
		{
			theApp.dwPVPDropDisabled = 1;
			success = true;

			WorldPos wlPos = { 0, 0, 0 };
			Broadcast::BCServerMessage( wlPos, 0, "PVP Drops have been turned off!", NULL, RGB( 0, 255, 0 ) );			
		}
		else
			success = false;

    //////////////////////////////////////////////////////////////////////////////////////////
    // Removes a player's access to PVP.
    COMMAND( "REMOVE $'S RIGHT TO PVP", GOD_CAN_SLAY_USER )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to remove %s's right to pvp authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

			
			return false;
		}

		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL && user->self->boAuthGM == true ){
            success = true;

    		_LOG_GAMEOP
	    		LOG_SYSOP,
		    	"God %s (%s) removed %s's (%s) right to PVP.",
			    (LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
    			(LPCTSTR)target->self->GetTrueName(),
	    		(LPCTSTR)target->GetFullAccountName()		    		
			LOG_

            target->SetPVP( false );
			target->self->SendSystemMessage( "Your pvp rights have been removed.", RGB( 255, 0, 0 ) );
        }else{
            CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
            SEND_MESSAGE;
        }
    //////////////////////////////////////////////////////////////////////////////////////////
    // Restores a player's access to PVP.
    COMMAND( "RESTORE $'S RIGHT TO PVP", GOD_CAN_SLAY_USER )
		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
            success = true;

    		_LOG_GAMEOP
	    		LOG_SYSOP,
		    	"God %s (%s) restored %s's (%s) right to PVP.",
			    (LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
    			(LPCTSTR)target->self->GetTrueName(),
	    		(LPCTSTR)target->GetFullAccountName()		    		
			LOG_

            target->SetPVP( true );
			target->self->SendSystemMessage( "Your pvp rights have been restored.", RGB( 50, 255, 50 ) );
        }else{
            CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
            SEND_MESSAGE;
        }

    //////////////////////////////////////////////////////////////////////////////////////////
    // Sets the target player to full PVP.
    COMMAND( "SET FULL PVP FOR $", GOD_CAN_SLAY_USER )
		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
            success = true;

    		_LOG_GAMEOP
	    		LOG_SYSOP,
		    	"God %s (%s) set full PVP for %s (%s).",
			    (LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
    			(LPCTSTR)target->self->GetTrueName(),
	    		(LPCTSTR)target->GetFullAccountName()		    		
			LOG_

            target->SetFullPVP( true );
        }else{
            CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
            SEND_MESSAGE;
        }
    //////////////////////////////////////////////////////////////////////////////////////////
    // Sets the target player to full PVP.
    COMMAND( "REMOVE FULL PVP FROM $", GOD_CAN_SLAY_USER )
		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
            success = true;

    		_LOG_GAMEOP
	    		LOG_SYSOP,
		    	"God %s (%s) set full PVP for %s (%s).",
			    (LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
    			(LPCTSTR)target->self->GetTrueName(),
	    		(LPCTSTR)target->GetFullAccountName()		    		
			LOG_

            target->SetFullPVP( false );
        }else{
            CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
            SEND_MESSAGE;
        }

    //NMNMNM
    
    //////////////////////////////////////////////////////////////////////////////////////////    
    // Allows dynamically boosting a CommCenter thread.
/*   
    COMMAND( "BOOST $ THREAD", GOD_DEVELOPPER )
        success = true;
        FIRST_COMPONENT( "LISTENING", GOD_DEVELOPPER, 0 )
            CCommCenter *lpComm = CPacketManager::GetCommCenter();
            lpComm->BoostListeningThread( THREAD_PRIORITY_ABOVE_NORMAL );
        COMPONENT( "SENDING", GOD_DEVELOPPER, 0 )
            CCommCenter *lpComm = CPacketManager::GetCommCenter();
            lpComm->BoostSendingThread( THREAD_PRIORITY_ABOVE_NORMAL );
        COMPONENT( "INTERPRETING", GOD_DEVELOPPER, 0 );
            CCommCenter *lpComm = CPacketManager::GetCommCenter();
            lpComm->BoostInterpretingThread( THREAD_PRIORITY_ABOVE_NORMAL );
        COMPONENT( "COMM", GOD_DEVELOPPER, 0 );
            CCommCenter *lpComm = CPacketManager::GetCommCenter();
            lpComm->BoostCommThread( THREAD_PRIORITY_ABOVE_NORMAL );
        }else{
            success = false;
            CREATE_MESSAGE( "No such thread not found." );
            SEND_MESSAGE;
        }
    //////////////////////////////////////////////////////////////////////////////////////////    
    // Allows dynamically boosting a CommCenter thread.
    COMMAND( "SUPERBOOST $ THREAD", GOD_DEVELOPPER )
        success = true;
        FIRST_COMPONENT( "LISTENING", GOD_DEVELOPPER, 0 )
            CCommCenter *lpComm = CPacketManager::GetCommCenter();
            lpComm->BoostListeningThread( THREAD_PRIORITY_HIGHEST );
        COMPONENT( "SENDING", GOD_DEVELOPPER, 0 )
            CCommCenter *lpComm = CPacketManager::GetCommCenter();
            lpComm->BoostSendingThread( THREAD_PRIORITY_HIGHEST );
        COMPONENT( "INTERPRETING", GOD_DEVELOPPER, 0 );
            CCommCenter *lpComm = CPacketManager::GetCommCenter();
            lpComm->BoostInterpretingThread( THREAD_PRIORITY_HIGHEST );
        COMPONENT( "COMM", GOD_DEVELOPPER, 0 );
            CCommCenter *lpComm = CPacketManager::GetCommCenter();
            lpComm->BoostCommThread( THREAD_PRIORITY_HIGHEST );
        }else{
            success = false;
            CREATE_MESSAGE( "No such thread not found." );
            SEND_MESSAGE;
        }

    //////////////////////////////////////////////////////////////////////////////////////////    
    // Allows dynamically regulating a CommCenter thread.
    COMMAND( "UNBOOST $ THREAD", GOD_DEVELOPPER )
        success = true;
        FIRST_COMPONENT( "LISTENING", GOD_DEVELOPPER, 0 )
            CCommCenter *lpComm = CPacketManager::GetCommCenter();
            lpComm->BoostListeningThread( THREAD_PRIORITY_NORMAL );
        COMPONENT( "SENDING", GOD_DEVELOPPER, 0 )
            CCommCenter *lpComm = CPacketManager::GetCommCenter();
            lpComm->BoostSendingThread( THREAD_PRIORITY_NORMAL );
        COMPONENT( "INTERPRETING", GOD_DEVELOPPER, 0 );
            CCommCenter *lpComm = CPacketManager::GetCommCenter();
            lpComm->BoostInterpretingThread( THREAD_PRIORITY_NORMAL );
       COMPONENT( "COMM", GOD_DEVELOPPER, 0 );
            CCommCenter *lpComm = CPacketManager::GetCommCenter();
            lpComm->BoostCommThread( THREAD_PRIORITY_NORMAL );
        }else{
            success = false;
            CREATE_MESSAGE( "No such thread not found." );
            SEND_MESSAGE;
        }

    //////////////////////////////////////////////////////////////////////////////////////////
    // Returns the CommThreads priorities
   /* COMMAND( "VIEW THREAD PRIORITIES", GOD_DEVELOPPER )
        CCommCenter *lpComm = CPacketManager::GetCommCenter();
        CREATE_MESSAGE( "Listening Thread=%d", lpComm->GetListeningThreadPriority() );
        SEND_MESSAGE;
        CREATE_MESSAGE( "Sending Thread=%d", lpComm->GetSendingThreadPriority() );
        SEND_MESSAGE;
        CREATE_MESSAGE( "Interpreting Thread=%d", lpComm->GetInterpretingThreadPriority() );
        SEND_MESSAGE;
        CREATE_MESSAGE( "Comm Thread=%d", lpComm->GetCommThreadPriority() );
        SEND_MESSAGE;
   */

	//////////////////////////////////////////////////////////////////////////////////////////       
    // Allows a god to broadcast system messages.
    COMMAND( "SYSMSG $", GOD_CAN_EMULATE_SYSTEM )
        WorldPos wlPos = { 0, 0, 0 };
        Broadcast::BCServerMessage( wlPos, 0, PARAM( 0 ));
	//////////////////////////////////////////////////////////////////////////////////////////       
    // Allows a god to send a system message to a player
	COMMAND( "USERMESSAGE $ SEND $", GOD_CAN_EMULATE_SYSTEM )
		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL )
		{
            success = true;

    		_LOG_GAMEOP
	    		LOG_SYSOP,
		    	"God %s (%s) sends an usermessage to %s (%s).",
			    (LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
    			(LPCTSTR)target->self->GetTrueName(),
	    		(LPCTSTR)target->GetFullAccountName()		    		
			LOG_

//			const RQ_ServerMessage = 63;
			TFCPacket msg_send;
			WorldPos wlPos = { -1, -1, -1 };
			CString csMessage;
			csMessage.Format( "God %s is talking to you: %s", (LPCTSTR)user->self->GetTrueName(), PARAM( 1 ) );
            
			msg_send << (RQ_SIZE)RQ_ServerMessage;
			msg_send << (short)30;
			msg_send << (short)3;
			msg_send << (CString &) csMessage;
			msg_send << (long) RGB( 200, 195, 125 );

			CPacketManager::SendPacket( msg_send, target->IPaddr, -1, wlPos, FALSE );
        }
		else
		{
            CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
            SEND_MESSAGE;
        }
    //////////////////////////////////////////////////////////////////////////////////////////       
    // Allows a god to broadcast a colored system messages.
    COMMAND( "CSYSMSG $,$", GOD_CAN_EMULATE_SYSTEM )

		DWORD Color;

		if(!stricmp(PARAM( 0 ), "red"))
			Color = RGB(255, 0, 0);
		else if(!stricmp(PARAM( 0 ), "orange"))
			Color = RGB(255, 100, 0);
		else if(!stricmp(PARAM( 0 ), "green"))
			Color = RGB(0, 255, 0);
		else if(!stricmp(PARAM( 0 ), "blue"))
			Color = RGB(0, 0, 255);
		else if(!stricmp(PARAM( 0 ), "white"))
			Color = RGB(255, 255, 255);
		else if(!stricmp(PARAM( 0 ), "black"))
			Color = RGB(0, 0, 0);
		else if(!stricmp(PARAM( 0 ), "yellow"))
			Color = RGB(251, 236, 55);
		else if(!stricmp(PARAM( 0 ), "purple"))
			Color = RGB(255, 72, 255);
		else
			Color = RGB(128, 128, 128);
			
        WorldPos wlPos = { 0, 0, 0 };
        Broadcast::BCServerMessage( wlPos, 0, PARAM( 1 ), NULL, Color );
    //////////////////////////////////////////////////////////////////////////////////////////
    // Allows a god to emulate a monster.
    COMMAND( "EMULATE MONSTER $", GOD_CAN_EMULATE_MONSTER )
        // If the monster exists.
        TRACE( "Param=%s.", PARAM(0));
        WORD wID = Unit::GetIDFromName( PARAM( 0 ), U_NPC, TRUE );
        if( wID != 0 ){
            
            // Create a new Creatures
            Creatures *lpCreature = new Creatures;
            // If this creature could be created.
            if( lpCreature->Create( U_NPC, wID ) ){
                success = true;
                
                user->self->Lock();

                // Copy the creature's stats.
	            user->self->SetINT( lpCreature->GetINT() );
	            user->self->SetEND( lpCreature->GetEND() );
	            user->self->SetSTR( lpCreature->GetSTR() );
	            user->self->SetAGI( lpCreature->GetAGI() );
	            user->self->SetWIS( lpCreature->GetWIS() );
	            user->self->SetATTACK( lpCreature->GetATTACK() );
	            user->self->SetDODGE( lpCreature->GetDODGE() );

                // Set the monster's level.                
                user->self->SetXP( 0 );

                TRACE( "\nbase referenceID=%u.", lpCreature->GetStaticReference() );
                // Copy the monster's spells.
                user->self->CopySpells( lpCreature );


                // Copy HP.
                user->self->SetMaxHP( lpCreature->GetMaxHP() );
                user->self->SetHP   ( user->self->GetMaxHP(), true );

                user->self->SetLevel( lpCreature->GetLevel() );

                // Set the god's pseudoname to the name of the create.
                TRACE( "\nbase referenceID=%u.", lpCreature->GetStaticReference() );
                user->self->SetPseudoName( lpCreature->GetName( user->self->GetLang() ) );

                // Set the appearance.
                user->self->SetAppearance( lpCreature->GetAppearance() );

                Broadcast::BCObjectChanged( user->self->GetWL(), _DEFAULT_RANGE,
                    user->self->GetAppearance(),
                    user->self->GetID()
                );

                user->self->Unlock();
            }else{
                CREATE_MESSAGE( "Could not create monster instance." );
                SEND_MESSAGE;
            }
            // Delete the creature.
            lpCreature->DeleteUnit();
        }else{
            CREATE_MESSAGE( "This is not a valid monster ID." );
            SEND_MESSAGE;
        }
    //////////////////////////////////////////////////////////////////////////////////////////    
    // Removes all god flags from a player.
    /*COMMAND( "CRASH THE T4C SERVER RIGHT NOW BY DOING A $", GOD_CAN_GIVE_GOD_FLAGS )
        if( stricmp( 
            (LPCTSTR)user->GetFullAccountName(), 
            CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str() 
        ) == 0 ){
    	    _LOG_GAMEOP
    	        LOG_SYSOP,
		        "SuperUser %s (%s) crashed the server!",
    		    (LPCTSTR)user->self->GetTrueName(),
	    	    (LPCTSTR)user->GetFullAccountName()
		    LOG_
            
            Sleep( 1000 );
            if( stricmp( PARAM( 0 ), "DEADLOCK" ) == 0 ){
                Sleep( INFINITE );                
            }else if( stricmp( PARAM( 0 ), "DIVIDE ERROR" ) == 0 ){
                int i = 0;
                int z = 10 / i;
            }else if( stricmp( PARAM( 0 ), "ACCESS VIOLATION" ) == 0 ){
                char *crash = 0;
                *crash = 1;
            }
        }else{
            _LOG_GAMEOP
                LOG_SYSOP,
		        "GameOp %s (%s) issued a server crash but was denied access (not the super user).",
    		    (LPCTSTR)user->self->GetTrueName(),
	    	    (LPCTSTR)user->GetFullAccountName()
            LOG_
        }*/
    //////////////////////////////////////////////////////////////////////////////////////////    
    // Shortcut to Set player's name to new name
    COMMAND( "RENAME $,$", GOD_CAN_EDIT_USER_NAME )
		CString csRepeatCommand;
		csRepeatCommand.Format("SET %s'S NAME TO %s", PARAM(0), PARAM(1));
		VerifySysopCommand(user, csRepeatCommand);
    //////////////////////////////////////////////////////////////////////////////////////////    
    // Shortcut to Set player's name to new name
    COMMAND( "OPFLAG $ + $,$", GOD_CAN_GIVE_GOD_FLAGS )
		CString csRepeatCommand;
		csRepeatCommand.Format("GIVE GAMEOP FLAG %s TO %s", GetOPFlagNameByShortcut(PARAM(1)), PARAM(0));
		VerifySysopCommand(user, csRepeatCommand);
		csRepeatCommand.Format("OPFLAG %s + %s", PARAM(0), PARAM(2));
		VerifySysopCommand(user, csRepeatCommand);
    //////////////////////////////////////////////////////////////////////////////////////////    
    // Shortcut to Set player's name to new name
    COMMAND( "OPFLAG $ + $", GOD_CAN_GIVE_GOD_FLAGS )
		CString csRepeatCommand;
		csRepeatCommand.Format("GIVE GAMEOP FLAG %s TO %s", GetOPFlagNameByShortcut(PARAM(1)), PARAM(0));
		VerifySysopCommand(user, csRepeatCommand);
    //////////////////////////////////////////////////////////////////////////////////////////    
    // Shortcut to Set player's name to new name
    COMMAND( "OPFLAG $ - $,$", GOD_CAN_GIVE_GOD_FLAGS )
		CString csRepeatCommand;
		csRepeatCommand.Format("REMOVE GAMEOP FLAG %s FROM %s", GetOPFlagNameByShortcut(PARAM(1)), PARAM(0));
		VerifySysopCommand(user, csRepeatCommand);
		csRepeatCommand.Format("OPFLAG %s - %s", PARAM(0), PARAM(2));
		VerifySysopCommand(user, csRepeatCommand);
    //////////////////////////////////////////////////////////////////////////////////////////    
    // Shortcut to Set player's name to new name
    COMMAND( "OPFLAG $ - $", GOD_CAN_GIVE_GOD_FLAGS )
		CString csRepeatCommand;
		csRepeatCommand.Format("REMOVE GAMEOP FLAG %s FROM %s", GetOPFlagNameByShortcut(PARAM(1)), PARAM(0));
		VerifySysopCommand(user, csRepeatCommand);
				
	//////////////////////////////////////////////////////////////////////////////////////////    
    // Shortcut to Set player's name to new name
    COMMAND( "SET $,$,$", GOD_CAN_EDIT_USER )
		CString csRepeatCommand;
		csRepeatCommand.Format("SET %s's %s TO %s", PARAM(0), PARAM(1), PARAM(2));
		VerifySysopCommand(user, csRepeatCommand);
    //////////////////////////////////////////////////////////////////////////////////////////    
    // Removes all god flags from a player.
    COMMAND( "DEMOTE GAMEOP $", GOD_CAN_GIVE_GOD_FLAGS )
		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
            target->Lock();

            if( stricmp( 
                (LPCTSTR)target->GetFullAccountName(), 
                CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str() 
            ) == 0 ){
    	    	_LOG_GAMEOP
    	    		LOG_SYSOP,
		        	"God %s (%s) tried to demote superuser %s (%s).",
    			    (LPCTSTR)user->self->GetTrueName(),
	    			(LPCTSTR)user->GetFullAccountName(),
    	    		(LPCTSTR)target->self->GetTrueName(),
	    	    	(LPCTSTR)target->GetFullAccountName()		    		
			    LOG_

                CREATE_MESSAGE( "You cannot demote this god." );
                SEND_MESSAGE;
            }else{
                target->SetGodFlags( 0 );
                target->SetGodMode( FALSE );

    	    	_LOG_GAMEOP
	    		LOG_SYSOP,
		        	"God %s (%s) removed all gameop flags from %s (%s).",
    			    (LPCTSTR)user->self->GetTrueName(),
	    			(LPCTSTR)user->GetFullAccountName(),
    	    		(LPCTSTR)target->self->GetTrueName(),
	    	    	(LPCTSTR)target->GetFullAccountName()		    		
			    LOG_

                CREATE_MESSAGE( "Demoted god" );
                SEND_MESSAGE;
            }

            target->Unlock();
        }else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
        }

	//////////////////////////////////////////////////////////////////////////////////////////    
    // Set the weather
	COMMAND( "SWITCHRAIN $", GOD_CAN_EMULATE_SYSTEM ) //GOD_CAN_SET_WEATHER
	{
		enum{ OFF, ON };
		short type;

		if((stricmp(PARAM(0), "off"))==0){
			type = OFF;
			success = true;
		}else if((stricmp(PARAM(0), "on"))==0){
			type = ON;
			success = true;
		}else{
			success = false;
		}

		if(success)
		{
//			if( WeatherEffect::GetInstance()->m_Rain.GetState() == true && type == ON )
			if( WeatherEffect::GetInstance()->GetEffectState( WEATHER_RAIN ) == true && type == ON )
			{
				CREATE_MESSAGE( "Rain already ON !" );
				SEND_MESSAGE;
			}
			//else if( WeatherEffect::GetInstance()->m_Rain.GetState() == false && type == OFF )
			else if( WeatherEffect::GetInstance()->GetEffectState( WEATHER_RAIN ) == false && type == OFF )
			{
				CREATE_MESSAGE( "Rain already OFF !" );
				SEND_MESSAGE;
			}

			//Rain::GetInstance()->SetState(type);
			WeatherEffect::GetInstance()->SetEffectState( type, WEATHER_RAIN );			

		} else {
			CREATE_MESSAGE( "You must choose between ON or OFF !" );
            SEND_MESSAGE;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////    
    // Set the weather
	COMMAND( "SWITCHFOG $", GOD_CAN_EMULATE_SYSTEM ) //GOD_CAN_SET_WEATHER
	{
		enum{ OFF, ON };
		short type;

		if((stricmp(PARAM(0), "off"))==0){
			type = OFF;
			success = true;
		}else if((stricmp(PARAM(0), "on"))==0){
			type = ON;
			success = true;
		}else{
			success = false;
		}

		if(success)
		{
			WeatherEffect::GetInstance()->SetEffectState( type, WEATHER_FOG );
		} else {
			CREATE_MESSAGE( "You must choose between ON or OFF !" );
            SEND_MESSAGE;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////    
    // Set the weather
	COMMAND( "SWITCHSNOW $", GOD_CAN_EMULATE_SYSTEM ) //GOD_CAN_SET_WEATHER
	{
		enum{ OFF, ON };
		short type;

		if((stricmp(PARAM(0), "off"))==0){
			type = OFF;
			success = true;
		}else if((stricmp(PARAM(0), "on"))==0){
			type = ON;
			success = true;
		}else{
			success = false;
		}

		if( success )					
			WeatherEffect::GetInstance()->SetEffectState( type, WEATHER_SNOW );		
		else
		{
			CREATE_MESSAGE( "You must choose between ON or OFF !" );
            SEND_MESSAGE;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////    
    // Remove a skill (in test)
	COMMAND( "REMOVE SKILL $ FROM $", GOD_CAN_GIVE_GOD_FLAGS ) //GOD_CAN_EDIT_USER_SKILLS
		WORD wSpellID = atoi( PARAM( 0 ) );

		// If the spellID is 0, then perhaps a spell name was provided.
        if( wSpellID == 0 )
		{
            // Retreive the spell by its name.
            LPSKILL lpSkill = Skills::GetSkillByName( PARAM( 0 ), user->self->GetLang() );
            if( lpSkill != NULL )
			{
                wSpellID = lpSkill->nSkillID;
            }
        }	
  
		if( wSpellID != 0 ){
			Players *target = FindCharacter( PARAM( 1 ) );

			if( target != NULL )
			{
				// Set 0 hp
				target->Lock();
				
				LPUSER_SKILL theSkill = target->self->GetSkill( wSpellID );

				if( theSkill )
				{
					theSkill->SetSkillPnts( 0 );
				}
				else
				{
					CREATE_MESSAGE( "Skill %s has been found.", PARAM( 0 ) );
					SEND_MESSAGE;
				}				

				target->Unlock();

			}else{
				CREATE_MESSAGE( "User %s is not online.", PARAM( 1 ) );
				SEND_MESSAGE;
			}
		}else{
			CREATE_MESSAGE( "Skill ID isn't valid" );
			SEND_MESSAGE;
		}	

	//////////////////////////////////////////////////////////////////////////////////////////    
    // Modify the Welcome Message
	COMMAND( "SET WELCOME MESSAGE TO $", GOD_CAN_EMULATE_SYSTEM ) 
		
		RegKeyHandler regKey; 

        if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY GEN_CFG_KEY ) )
		{
			regKey.WriteProfileString( "WelcomeMessage", PARAM( 0 ) );			

			CREATE_MESSAGE( "The welcome message has been correctly changed." );
			SEND_MESSAGE
		}
		else
		{
			CREATE_MESSAGE( "The welcome message cannot be changed." );
			SEND_MESSAGE
		}

	//////////////////////////////////////////////////////////////////////////////////////////    
    // Show the Welcome Message
	COMMAND( "GET WELCOME MESSAGE", GOD_CAN_EMULATE_SYSTEM ) 
		
		RegKeyHandler regKey; 

        if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY GEN_CFG_KEY ) )
		{
			// Get the text to send
			CString csWelcome;
			csWelcome = regKey.GetProfileString( "WelcomeMessage", "" );

			if( csWelcome.IsEmpty() )
			{
				CREATE_MESSAGE( "No welcome message at this time." );
				SEND_MESSAGE
			}
			else
			{
				CREATE_MESSAGE( "The current message is: %s", csWelcome );
				SEND_MESSAGE
			}			
		}
		else
		{
			CREATE_MESSAGE( "Unable to get the welcome message." );
			SEND_MESSAGE
		}

	//////////////////////////////////////////////////////////////////////////////////////////
    // Allows a god to emulate a monster.
    COMMAND( "EMULATE PLAYER $", GOD_CAN_EMULATE_MONSTER )
		Players *target = FindCharacter( PARAM( 0 ) );
        
        if( target != NULL )
		{
			user->self->Lock();

            // Copy the player's stats.
	        user->self->SetINT( target->self->GetINT() );
	        user->self->SetEND( target->self->GetEND() );
	        user->self->SetSTR( target->self->GetSTR() );
	        user->self->SetAGI( target->self->GetAGI() );
	        user->self->SetWIS( target->self->GetWIS() );
	        user->self->SetATTACK( target->self->GetATTACK() );
	        user->self->SetDODGE( target->self->GetDODGE() );

			user->self->SetGold( target->self->GetGold() );

            // Set the player's level.                
            user->self->SetXP( target->self->GetXP() );
			user->self->SetLevel( target->self->GetLevel() );
                
            // Copy the player's spells.
            user->self->CopySpells( target->self );

			// Copy the player's bp
			user->self->SetBackpack( target->self->GetBackpack() );

			// Copy the player's chest
			user->self->SetChest( target->self->GetChest() );

            // Copy HP.
            user->self->SetMaxHP( target->self->GetMaxHP() );
            user->self->SetHP   ( target->self->GetMaxHP(), true );

			// Copy Mana
            user->self->SetMaxMana( target->self->GetMaxMana() );
            user->self->SetMana   ( target->self->GetMaxMana(), true );
                            
            // Set the appearance.
            user->self->SetAppearance( target->self->GetAppearance() );

            Broadcast::BCObjectChanged( user->self->GetWL(), _DEFAULT_RANGE,
                    user->self->GetAppearance(),
                    user->self->GetID()
                );

			//user->self->SetPlayer( target );

			Broadcast::BCObjectChanged( user->self->GetWL(), _DEFAULT_RANGE,
                    user->self->GetAppearance(),
                    user->self->GetID()
                );

            user->self->Unlock();                        

			success = true;
        }
		else
		{
		    CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
		    SEND_MESSAGE;
        }              

		
	//////////////////////////////////////////////////////////////////////////////////////////	
	// Move out a player character ! (like move out from a door)
	COMMAND( "MOVEOUT $ TO $", GOD_CAN_TELEPORT )//BLBLBLBL
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to move out %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL && user->self->boAuthGM == true ){

            if( SUPER_USER ){
                CREATE_MESSAGE( "Sorry but you cannot move out the super user out!" );
                SEND_MESSAGE;
            }else{
                success = true;


		//ici la commande pour bouger un joueur
		if((stricmp(PARAM(1), "n"))==0){
				target->self->MoveUnit(DIR::north, false, true, true );
				target->self->MoveUnit(DIR::north, false, true, true );
		}else if((stricmp(PARAM(1), "s"))==0){
				target->self->MoveUnit(DIR::south, false, true, true );
				target->self->MoveUnit(DIR::south, false, true, true );
		}else if((stricmp(PARAM(1), "e"))==0){
				target->self->MoveUnit(DIR::east, false, true, true );
				target->self->MoveUnit(DIR::east, false, true, true );
		}else if((stricmp(PARAM(1), "w"))==0){
				target->self->MoveUnit(DIR::west, false, true, true );
				target->self->MoveUnit(DIR::west, false, true, true );
		}else{
			CREATE_MESSAGE( "You must specify a valid direction : N, S, E, W." );
			SEND_MESSAGE;
		}
				
    			_LOG_GAMEOP
	    			LOG_SYSOP,
		    		"God %s (%s) moved out account %s.",
			    	(LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
				    (LPCTSTR)target->GetFullAccountName()
			    LOG_	
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}

	//////////////////////////////////////////////////////////////////////////////////////////	
	// Unequip all items from a player ! usefull to delete an objet which is equiped !
	COMMAND( "UNEQUIP $", GOD_CAN_EDIT_USER )//BLBLBLBL
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"God %s (%s) tried to unequip a player %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL && user->self->boAuthGM == true ){

            if( SUPER_USER ){
                CREATE_MESSAGE( "Sorry but you cannot unequip the super user !" );
                SEND_MESSAGE;
            }else{
                success = true;

				int iPositions;
				for( iPositions = 0; iPositions < EQUIP_POSITIONS; iPositions++ ){
					target->self->unequip_object( iPositions );
				}
				
    			_LOG_GAMEOP
	    			LOG_SYSOP,
		    		"God %s (%s) unequiped items on the playing character from account %s.",
			    	(LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
				    (LPCTSTR)target->GetFullAccountName()
			    LOG_	
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}

    //////////////////////////////////////////////////////////////////////////////////////////    
    // Shortcut to give a player moderation flags. (this command is for MODERATOR GUARDIANS)
    COMMAND( "PROMOTE MODERATOR $", GOD_MODERATOR_GUARDIAN)
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"Moderator Guardian %s (%s) tried to give moderator gameopflag from %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 1 )
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL && user->self->boAuthGM == true ){
            BOOL boGiven = FALSE;
            CString csMessage;            

			target->Lock();

            if( stricmp( 
                    (LPCTSTR)target->GetFullAccountName(), 
                    CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str()
                ) != 0 || stricmp( 
                    (LPCTSTR)user->GetFullAccountName(), 
                    CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str()
                ) == 0 
           ){

             GIVE_GOD_FLAG( GOD_CAN_REMOVE_SHOUTS, "Target user is now able to remove users shouts." );         			
             CString csChangeValue = "Moderator";
			 target->self->SetGuildName( csChangeValue );
			 target->self->SetTitle( csChangeValue );

			 boGiven=TRUE;
			 
            }else{
    			CREATE_MESSAGE( "You cannot add god flags to the super user." );
	    		SEND_MESSAGE;
            }

			target->Unlock();

            if( boGiven ){
    			_LOG_GAMEOP
	    			LOG_SYSOP,
		    		"Moderator guardian %s (%s) promoted gave moderator gameop flag %s to %s (%s).",
			    	(LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
                    PARAM( 0 ),
    				(LPCTSTR)target->self->GetTrueName(),
	    			(LPCTSTR)target->GetFullAccountName()		    		
			    LOG_

                CREATE_MESSAGE( csMessage );
                SEND_MESSAGE;
            }else{
    			CREATE_MESSAGE( "%s is not a valid gameop flag.", PARAM( 0 ) );
	    		SEND_MESSAGE;
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 1 ) );
			SEND_MESSAGE;
		}		
    //////////////////////////////////////////////////////////////////////////////////////////    
    // Shortcut to remove from a player moderation flags (this command is for MODERATOR GUARDIANS)
    COMMAND( "DEMOTE MODERATOR $", GOD_MODERATOR_GUARDIAN )
		if( user->self->boAuthGM == false )
		{
			_LOG_GAMEOP
				LOG_CRIT_ERRORS,
				"Moderator Guardian %s (%s) tried to remove moderator gameop flag from %s without authentification!",
				(LPCTSTR)user->self->GetTrueName(),
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)PARAM( 0 )
			LOG_	
			
			CREATE_MESSAGE( "You need to authentificate as a GM first." );
            SEND_MESSAGE;

		}

		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL && user->self->boAuthGM == true ){
            BOOL boGiven = FALSE;
            CString csMessage;            

			target->Lock();

            if( stricmp( 
                    (LPCTSTR)target->GetFullAccountName(), 
                    CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str()
                ) != 0 || stricmp( 
                    (LPCTSTR)user->GetFullAccountName(), 
                    CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str()
                ) == 0 
           ){

             REMOVE_GOD_FLAG( GOD_CAN_REMOVE_SHOUTS, "Target user can no longer remove a user's ability to shout." );         			
             CString csChangeValue = "";
             target->self->SetGuildName( csChangeValue );
			 target->self->SetTitle( csChangeValue );

			 boGiven=TRUE;
			 
            }else{
    			CREATE_MESSAGE( "You cannot remove god flags from the super user." );
	    		SEND_MESSAGE;
            }

			target->Unlock();

            if( boGiven ){
    			_LOG_GAMEOP
	    			LOG_SYSOP,
		    		"Moderator guardian %s (%s) removed gameop flag from %s (%s).",
			    	(LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
    				(LPCTSTR)target->self->GetTrueName(),
	    			(LPCTSTR)target->GetFullAccountName()		    		
			    LOG_

                CREATE_MESSAGE( csMessage );
                SEND_MESSAGE;
            }
		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}
	
    //////////////////////////////////////////////////////////////////////////////////////////    
    // Shortcut to remove from a player moderation flags (this command is for MODERATOR GUARDIANS)
    COMMAND( "DEMOTE ROYAL GUARD $", GOD_ROYAL_GUARD_CHIEF )
	
		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
            BOOL boGiven = FALSE;
            CString csMessage;            

			target->Lock();

            if( stricmp( 
                    (LPCTSTR)target->GetFullAccountName(), 
                    CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str()
                ) != 0 || stricmp( 
                    (LPCTSTR)user->GetFullAccountName(), 
                    CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str()
                ) == 0 
           ){
                      			
             CString csChangeValue = "";
			 target->self->SetGuildName( csChangeValue );
			 target->self->SetTitle( csChangeValue );

			 boGiven=TRUE;
			 
            }else{
    			CREATE_MESSAGE( "You cannot remove title from the super user." );
	    		SEND_MESSAGE;
            }

			target->Unlock();

            if( boGiven ){
    			_LOG_GAMEOP
	    			LOG_SYSOP,
		    		"Royal guard chief %s (%s) removed royal guard Royal Guard title from %s (%s).",
			    	(LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
    				(LPCTSTR)target->self->GetTrueName(),
	    			(LPCTSTR)target->GetFullAccountName()		    		
			    LOG_

                CREATE_MESSAGE( csMessage );
                SEND_MESSAGE;
            }

		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}

   //////////////////////////////////////////////////////////////////////////////////////////    
    // Shortcut to remove from a player moderation flags (this command is for MODERATOR GUARDIANS)
    COMMAND( "PROMOTE ROYAL GUARD $", GOD_ROYAL_GUARD_CHIEF )
	
		Players *target = FindCharacter( PARAM( 0 ) );

		if( target != NULL ){
            BOOL boGiven = FALSE;
            CString csMessage;            

			target->Lock();

            if( stricmp( 
                    (LPCTSTR)target->GetFullAccountName(), 
                    CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str()
                ) != 0 || stricmp( 
                    (LPCTSTR)user->GetFullAccountName(), 
                    CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str()
                ) == 0 
           ){
                      			
             CString csChangeValue = "Royal Guard";
			 target->self->SetGuildName( csChangeValue );
			 target->self->SetTitle( csChangeValue );

			 boGiven=TRUE;
			 
            }else{
    			CREATE_MESSAGE( "You cannot set title on the super user." );
	    		SEND_MESSAGE;
            }

			target->Unlock();

            if( boGiven ){
    			_LOG_GAMEOP
	    			LOG_SYSOP,
		    		"Royal guard chief %s (%s) gave royal guard Royal Guard title to %s (%s).",
			    	(LPCTSTR)user->self->GetTrueName(),
				    (LPCTSTR)user->GetFullAccountName(),
    				(LPCTSTR)target->self->GetTrueName(),
	    			(LPCTSTR)target->GetFullAccountName()		    		
			    LOG_

                CREATE_MESSAGE( csMessage );
                SEND_MESSAGE;
            }

		}else{
			CREATE_MESSAGE( "User %s is not online.", PARAM( 0 ) );
			SEND_MESSAGE;
		}
	//////////////////////////////////////////////////////////////////////////////////////////    
    // Scans a player for cheats and such
	COMMAND( "WHOIS $", GOD_CAN_VIEW_USER_STAT)

		Players *target = FindCharacter( PARAM( 0 ) );

		bool bFoundSomething = false;
		int m_CountProb = 0;

		if(target != NULL){ 

			CREATE_MESSAGE("Scanning user %s", PARAM( 0 ));
			SEND_MESSAGE;

			// Get account and playername
			CString account		= target->GetAccount();

			// Get stats
			WORD level			= target->self->GetLevel();
			WORD strength		= target->self->GetTrueSTR();
			WORD agility		= target->self->GetTrueAGI();
			WORD endurance		= target->self->GetTrueEND();
			WORD intelligence	= target->self->GetTrueINT();
			WORD wisdom			= target->self->GetTrueWIS();
			WORD numremorts		= target->self->ViewFlag(30419);
			WORD statpts		= target->self->GetStatPoints();

			// Get island access and sanctuary flag
			WORD IslandAccess	= target->self->ViewFlag(30143);
			WORD SanctuaryFlag	= target->self->ViewFlag(20020);

			// Get bank gold
			WORD bankgold		= target->self->ViewFlag(30026);

			// Get IP
			CString ipaddr		= target->GetIP();

			// Calculate max stats and return a message if there is a problem
			WORD m_MaxStats		= ((level-1)*5)+(((numremorts*5)+20)*5);
			WORD m_Stats		= strength+agility+endurance+intelligence+wisdom+statpts;

			if(m_Stats > m_MaxStats)
			{
				CREATE_MESSAGE("User %s has too much stat points", PARAM( 0 ));
				SEND_MESSAGE;
				bFoundSomething = true;
				m_CountProb++;
			}

			// Check the sanctuary flag of the player and if he has access on the island it's set to
			if(SanctuaryFlag==215129856 && IslandAccess < 2){
				CREATE_MESSAGE("User %s has not access to Stoneheim but his sanctuary is set there.", PARAM( 0 ));
				SEND_MESSAGE;
				bFoundSomething = true;
				m_CountProb++;
			} else if(SanctuaryFlag==1634297088 && IslandAccess < 1){
				CREATE_MESSAGE("User %s has not access to Raven's dust but his sanctuary is set there.", PARAM( 0 ));
				SEND_MESSAGE;
				bFoundSomething = true;
				m_CountProb++;
			}

			//Check the user's gold
			if( bankgold > 50000000 )
			{
				CREATE_MESSAGE("User %s has more than 50mil in his bank account.", PARAM( 0 ));
				SEND_MESSAGE;
				bFoundSomething = true;
				m_CountProb++;
			}

			// If something maybe wrong is found, return a different message
			if(!bFoundSomething){
				CREATE_MESSAGE("Finished scanning user %s(%s). No problems found", PARAM( 0 ), account);
				SEND_MESSAGE;
				CREATE_MESSAGE("IP Address of %s: %s", PARAM( 0 ), ipaddr);
				SEND_MESSAGE;
			} else {
				CREATE_MESSAGE("Finished scanning user %s(%s) and found %i problems,", PARAM( 0 ), account, m_CountProb);
				SEND_MESSAGE;
				CREATE_MESSAGE("IP Address of %s: %s", PARAM( 0 ), ipaddr);
				SEND_MESSAGE;
			}


		} else {

			cODBCMage *ODBCCharRead = Character::GetODBC();

			CString csQuery;
#ifdef MSSQLSERVER
			csQuery.Format( "SELECT TOP 1 AccountName FROM PlayingCharacters WHERE PlayerName='%s'", PARAM( 0 ) ); //BLBLBL 05/01/2011
#else
			csQuery.Format( "SELECT AccountName FROM PlayingCharacters WHERE PlayerName='%s' LIMIT 1", PARAM( 0 ) ); //BLBLBL 05/01/2011
#endif
			ODBCCharRead->Lock();
			//Take the AccountName of this Player
			ODBCCharRead->SendRequest( (LPCTSTR)csQuery );

			char playerName[15];
			char accountName[20];
			DWORD playerLevel;

			ODBCCharRead->GetString( 1, accountName, 20);
				
			ODBCCharRead->Cancel();
			ODBCCharRead->Unlock();

			CREATE_MESSAGE( "Player %s", PARAM( 0 ) );
			SEND_MESSAGE;

			CString csQuery2;
			csQuery2.Format( "SELECT PlayerName, CurrentLevel FROM PlayingCharacters WHERE AccountName='%s'", accountName );
			
			ODBCCharRead->Lock();
			ODBCCharRead->SendRequest( (LPCTSTR)csQuery2 );

			// Take all characters on this AccountName
			while( ODBCCharRead->Fetch() ){	

				ODBCCharRead->GetString(1, playerName, 15);
				ODBCCharRead->GetDWORD(2, &playerLevel);

				CREATE_MESSAGE( "Has character %s (Level %u) in account : %s.", playerName, playerLevel, accountName );
				SEND_MESSAGE;

			}

			ODBCCharRead->Cancel();
			ODBCCharRead->Unlock();
		}


	END_COMMAND

    if( success ){

		CREATE_MESSAGE( "Done." );
        SEND_MESSAGE;
    }

	csSysLock.Unlock();
	return boFound;
};

namespace{
//////////////////////////////////////////////////////////////////////////////////////////
void AsyncSetName
//////////////////////////////////////////////////////////////////////////////////////////
//  This function is called to set name asynchronously.
// 
(
 LPVOID lpData // Contains the IP of the gameop and the IP of the target.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    auto_ptr< SetNameData > nameData( reinterpret_cast< SetNameData * >( lpData ) );

    // Fetch the target of the command.
    Players *lpTarget = NULL;
    
    // Try 10 times, 250ms to lock the player.
    int d;
    for( d = 0; d < 10; d++ ){
        lpTarget = CPlayerManager::GetPlayerResource( nameData->sockTarget );
        if( lpTarget != NULL ){
            break;
        }
        Sleep( 25 );
    }

    // If the target exists.
    if( lpTarget != NULL ){
        std::string originalName =  lpTarget->self->GetName( _DEFAULT_LNG );
        std::string newName = nameData->csNewName;
        bool printGameopLog = false;

        // Create a Format object.
        TFormat format;
        string csCompletionMessage;

        // Get an ODBC connection
        cODBCMage *lpDB = Character::GetODBC();

        // Lock connection
        lpDB->Lock();
        
        // Create the query statement       
        string csQuery = format( 
            "SELECT PlayerName FROM PlayingCharacters WHERE PlayerName='%s'", 
            nameData->csNewName.c_str()
        );
        
        // Send the request.
        lpDB->SendRequest( csQuery.c_str() );        

        // If the new name could NOT be fetched, then allow name change (no duplicates).
        if( !lpDB->Fetch() ){
            printGameopLog = true;

            // Set the player's name.
            lpTarget->self->SetName( nameData->csNewName.c_str() );

            // Tell the god.
            csCompletionMessage = format(
                "Name changed to %s.",
                nameData->csNewName.c_str()
            );


            // Update the OnlineUsers table.
            lpDB->Cancel();
            lpDB->SendRequest(
                format(
                    "UPDATE OnlineUsers SET PlayerName='%s' WHERE AccountName='%s'",//BLBLBL 05/01/2011 retrait de top
                    nameData->csNewName.c_str(),
                    (LPCTSTR)lpTarget->GetAccount()
                )
            );
            
            // Save player data (commit name change). Allows the name to be reverted on subsequent name changes.
            lpTarget->self->SaveCharacter();

        }
        // Otherwise warn the god.
        else{
            csCompletionMessage = format( 
                "The name %s already exists. Name change couldn't be completed.",
                nameData->csNewName.c_str()
            );
        }
        lpDB->Cancel();
        


        // Free the database.
        lpDB->Unlock();

        // Free the player resource.
        CPlayerManager::FreePlayerResource( lpTarget );

        // Get the god's player resource
        Players *lpGod = CPlayerManager::GetPlayerResource( nameData->sockGod );

        // If the god is still online.
        if( lpGod != NULL ){
            if( printGameopLog ){
                _LOG_GAMEOP
                    LOG_SYSOP,
                    "God %s (%s) changed player %s (%s)'s name to %s.",
                    (LPCTSTR)lpGod->self->GetName( _DEFAULT_LNG ),
                    (LPCTSTR)lpGod->GetFullAccountName(),
                    originalName.c_str(),
                    (LPCTSTR)lpTarget->GetFullAccountName(),
                    newName.c_str()
                LOG_
            }

            // Notify the god.
            lpGod->self->SendSystemMessage( csCompletionMessage.c_str() );

            // Free the player's resource.
            CPlayerManager::FreePlayerResource( lpGod );
        }else{
            if( printGameopLog ){
                _LOG_GAMEOP
                    LOG_SYSOP,
                    "Logged off god changed player %s (%s)'s name to %s.",
                    originalName.c_str(),
                    (LPCTSTR)lpTarget->GetFullAccountName(),
                    newName.c_str()
                LOG_
            }
        }
    }
}
CString GetOPFlagNameByShortcut(CString csFlagShortCut) {
	if (csFlagShortCut.CompareNoCase("noclip") == 0) return "GOD_NO_CLIP";
	else if (csFlagShortCut.CompareNoCase("nomonsters") == 0) return "GOD_NO_MONSTERS";
	else if (csFlagShortCut.CompareNoCase("teleport") == 0) return "GOD_CAN_TELEPORT";
	else if (csFlagShortCut.CompareNoCase("teleportuser") == 0) return "GOD_CAN_TELEPORT_USER";
	else if (csFlagShortCut.CompareNoCase("zap") == 0) return "GOD_CAN_ZAP";
	else if (csFlagShortCut.CompareNoCase("squelch") == 0) return "GOD_CAN_SQUELCH";
	else if (csFlagShortCut.CompareNoCase("removeshouts") == 0) return "GOD_CAN_REMOVE_SHOUTS";
	else if (csFlagShortCut.CompareNoCase("summonmonsters") == 0) return "GOD_CAN_SUMMON_MONSTERS";
	else if (csFlagShortCut.CompareNoCase("summonitems") == 0) return "GOD_CAN_SUMMON_ITEMS";
	else if (csFlagShortCut.CompareNoCase("setuserflag") == 0) return "GOD_CAN_SET_USER_FLAG";
	else if (csFlagShortCut.CompareNoCase("edituser") == 0) return "GOD_CAN_EDIT_USER";
	else if (csFlagShortCut.CompareNoCase("edituserstat") == 0) return "GOD_CAN_EDIT_USER_STAT";
	else if (csFlagShortCut.CompareNoCase("edituserhp") == 0) return "GOD_CAN_EDIT_USER_HP";
	else if (csFlagShortCut.CompareNoCase("editusermp") == 0) return "GOD_CAN_EDIT_USER_MANA";
	else if (csFlagShortCut.CompareNoCase("edituserxplevel") == 0) return "GOD_CAN_EDIT_USER_XP_LEVEL";
	else if (csFlagShortCut.CompareNoCase("editusername") == 0) return "GOD_CAN_EDIT_USER_NAME";
	else if (csFlagShortCut.CompareNoCase("edituserappearance") == 0) return "GOD_CAN_EDIT_USER_APPEARANCE_CORPSE";
	else if (csFlagShortCut.CompareNoCase("edituserspells") == 0) return "GOD_CAN_EDIT_USER_SPELLS";
	else if (csFlagShortCut.CompareNoCase("edituserskills") == 0) return "GOD_CAN_EDIT_USER_SKILLS";
	else if (csFlagShortCut.CompareNoCase("edituserbackpack") == 0) return "GOD_CAN_EDIT_USER_BACKPACK";
//	else if (csFlagShortCut.CompareNoCase("viewuser") == 0) return "GOD_CAN_VIEW_USER";
	else if (csFlagShortCut.CompareNoCase("viewuserstat") == 0) return "GOD_CAN_VIEW_USER_STAT";
	else if (csFlagShortCut.CompareNoCase("viewuserbackpack") == 0) return "GOD_CAN_VIEW_USER_BACKPACK";
	else if (csFlagShortCut.CompareNoCase("viewuserspells") == 0) return "GOD_CAN_VIEW_USER_SPELLS";
	else if (csFlagShortCut.CompareNoCase("viewuserskills") == 0) return "GOD_CAN_VIEW_USER_SKILLS";
	else if (csFlagShortCut.CompareNoCase("viewuserappearance") == 0) return "GOD_CAN_VIEW_USER_APPEARANCE_CORPSE";
	else if (csFlagShortCut.CompareNoCase("lockout") == 0) return "GOD_CAN_LOCKOUT_USER";
	else if (csFlagShortCut.CompareNoCase("slay") == 0) return "GOD_CAN_SLAY_USER";
	else if (csFlagShortCut.CompareNoCase("emulatemonster") == 0) return "GOD_CAN_EMULATE_MONSTER";
	else if (csFlagShortCut.CompareNoCase("invincible") == 0) return "GOD_INVINCIBLE";
	else if (csFlagShortCut.CompareNoCase("developper") == 0) return "GOD_DEVELOPPER";
	else if (csFlagShortCut.CompareNoCase("shutdown") == 0) return "GOD_CAN_SHUTDOWN";
	else if (csFlagShortCut.CompareNoCase("seeaccounts") == 0) return "GOD_CAN_SEE_ACCOUNTS";
	else if (csFlagShortCut.CompareNoCase("givegodflags") == 0) return "GOD_CAN_GIVE_GOD_FLAGS";
	else if (csFlagShortCut.CompareNoCase("unlimitedshouts") == 0) return "GOD_UNLIMITED_SHOUTS";
	else if (csFlagShortCut.CompareNoCase("trueinvisibility") == 0) return "GOD_TRUE_INVISIBILITY";
	else if (csFlagShortCut.CompareNoCase("emulatesystem") == 0) return "GOD_CAN_EMULATE_SYSTEM";
	else if (csFlagShortCut.CompareNoCase("chatmaster") == 0) return "GOD_CHAT_MASTER";
	else if (csFlagShortCut.CompareNoCase("cannotdie") == 0) return "GOD_CANNOT_DIE";
	else if (csFlagShortCut.CompareNoCase("runscripts") == 0) return "GOD_CAN_RUN_CLIENT_SCRIPTS";
	else if (csFlagShortCut.CompareNoCase("moderatorguardian") == 0) return  "GOD_MODERATOR_GUARDIAN";
	else if (csFlagShortCut.CompareNoCase("royalguardchief") == 0) return  "GOD_ROYAL_GUARD_CHIEF";
	else return csFlagShortCut;
}
};//namespace