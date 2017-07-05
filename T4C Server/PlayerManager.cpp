// PlayerManager.cpp: implementation of the CPlayerManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "PlayerManager.h"
#include "TFC_MAIN.h"
#include "CommCenter.h"
#include "PacketManager.h"
//#include "TFCServerGP.h"
#include "DeadlockDetector.h"
//#include "../T4C Monitor/T4C MonitorMap.h"
//#include "GlobalStatistics.h"
#include <process.h>
//#include "ODBCMage.h"
#include "RegKeyHandler.h"
#include "ThreadMonitor.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define INITIAL_SIZE        100
#define GROW_BY             10

// Utility macro.
#define SAME_IP( sock1, sock2 ) (sock1).sin_addr.S_un.S_addr == (sock2).sin_addr.S_un.S_addr &&\
                                (sock1).sin_port             == (sock2).sin_port

// externs
extern TFC_MAIN *TFCServer;
extern TemplateList< DEATHROW > tluDeathRow;

// static variables
Players **CPlayerManager::lpRegisteredUsers =       NULL;
int       CPlayerManager::nUserCount =              0;
int       CPlayerManager::nBufferSize =             0;
CLock     CPlayerManager::cUserLock;
CLock     CPlayerManager::cMaintenanceLock;
CLock     CPlayerManager::cFetchLock;

//static CLock     cGetResourceLock;

HANDLE    CPlayerManager::hMaintenanceThread =      NULL;
HANDLE    CPlayerManager::hDeletionIo =             NULL;
ChatterChannels *CPlayerManager::lpChatter = NULL;

static HANDLE hDeleteThread = NULL;

static BOOL        boMaintenance;

DWORD  Round = 0;

static BOOL   boStop = FALSE;

extern CTFCServerApp theApp;

//////////////////////////////////////////////////////////////////////////////////////////
void CPlayerManager::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Initializes the player manager.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{   
    // Begin with 100 users.
    lpRegisteredUsers = new Players *[ INITIAL_SIZE ];

    int i;
    for( i = 0; i < INITIAL_SIZE; i++ ){
        lpRegisteredUsers[ i ] = NULL;
    }

    nUserCount = 0;
    nBufferSize = INITIAL_SIZE;

    // Begin maintenance thread.
    boMaintenance = TRUE;
    hMaintenanceThread = (HANDLE)_beginthread( PlayerMaintenance, 0, NULL );
    boStop = FALSE;
    
    hDeletionIo = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 1 );    

    // Start async deletion thread.
    hDeleteThread = (HANDLE)_beginthread( AsyncDeletePlayer, 0, NULL );
}

//////////////////////////////////////////////////////////////////////////////////////////
void CPlayerManager::Destroy( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Destroys the player manager.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Kill maintenance thread.
    boStop = TRUE;
    boMaintenance = FALSE;
    if( WaitForSingleObject( hMaintenanceThread, 5000 ) == WAIT_TIMEOUT ){
        TerminateThread( hMaintenanceThread, 1 );
    }

    int i;
    for( i = 0; i < nBufferSize; i++ ){
        if( lpRegisteredUsers[ i ] != NULL ){
            delete lpRegisteredUsers[ i ];
        }
    }
    
    CancelIo( hDeletionIo );
    CloseHandle( hDeletionIo );

    delete [] lpRegisteredUsers;
}

//////////////////////////////////////////////////////////////////////////////////////////
void CPlayerManager::GrowBufferSpace( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Grows the user buffer space.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    MultiLock3( &cMaintenanceLock, &cUserLock, &cFetchLock );

    Players **lpNew = new Players *[ nBufferSize + GROW_BY ];
    
    // Copy all users from previous buffer to new one.
    int i;
    for( i = 0; i < nBufferSize; i++ ){
        lpNew[ i ] = lpRegisteredUsers[ i ];
    }
    // Fill the rest of the users to NULL.
    nBufferSize += GROW_BY;
    for(; i < nBufferSize; i++ ){
        lpNew[ i ] = NULL;
    }

    // Replace previous user buffer with new one.
    delete lpRegisteredUsers;
    lpRegisteredUsers = lpNew;    

    cFetchLock.Unlock();
    cUserLock.Unlock();
    cMaintenanceLock.Unlock();
    
}

//////////////////////////////////////////////////////////////////////////////////////////
Players *CPlayerManager::CreatePlayer
//////////////////////////////////////////////////////////////////////////////////////////
// Creates a new player entry.
// 
(
 sockaddr_in sockAddr, // Address of remote player.
 CString csAccountName // Account name of remote player.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( boStop ) return NULL;

    // Create a new Players object.
    Players *lpPlayer = new Players;
    BOOL boFound;
    int i;

    lpPlayer->ResetIdle();
    lpPlayer->IdleTime = 30 SECONDS TDELAY;
	 lpPlayer->IPaddr   = sockAddr;

    //cGetResourceLock.Lock();

    // Lock player list.
    MultiLock3( &cMaintenanceLock, &cUserLock, &cFetchLock );

    // Try to find a duplicate entry for this address.
    boFound = FALSE;
    i = 0;
    while( i < nBufferSize && !boFound ){
        // If an non-empty spot was found.
        if( lpRegisteredUsers[ i ] != NULL ){
            if( SAME_IP( lpRegisteredUsers[ i ]->IPaddr, sockAddr ) ){
                boFound = TRUE;
            }
        }
        i++;
    }

    // If a duplicate entry wasn't found.
    if( !boFound ){
        // Try to find an empty user spot.
        i = 0;
        boFound = FALSE;    
        while( i < nBufferSize && !boFound ){
            // If an empty spot was found.
            if( lpRegisteredUsers[ i ] == NULL ){
                TRACE( "\r\nFound player slot %u.", i );
                // Reserve this space.
                boFound = TRUE;
                lpRegisteredUsers[ i ] = lpPlayer;
                
                // Set the port ID to the assigned player slot.
                lpPlayer->SetRadiusPortID( i );
            }
            i++;
        }
        // If no spot could be found
        if( !boFound ){
            // Grow the user buffer space.
            GrowBufferSpace();

            // And get the first grown entry.
            lpRegisteredUsers[ i ] = lpPlayer;

            // Set the port ID to the assigned player slot.
            lpPlayer->SetRadiusPortID( i );
        }    

        _LOG_DEBUG
            LOG_DEBUG_HIGH,
            "Created new player slot!"
        LOG_
        
        // One more user!
        nUserCount++;
        TRACE( "\r\nNew user count=%u.", nUserCount );        
    
//        PERF_CNT( PRFUSERS_ONLINE_USERS ) = nUserCount;//BLBLBL 17/12/2010 je vire t4c monitor
    
      //  TRACE( "-->%d", PERF_CNT( PRFUSERS_ONLINE_USERS ) );//BLBLBL 17/12/2010 je vire t4c monitor

        // Lock the player resource.
        lpPlayer->Lock();

    }else{
        delete lpPlayer;
        lpPlayer = NULL;       
    }

    // Unlock player list.
    cFetchLock.Unlock();
    cUserLock.Unlock();
    cMaintenanceLock.Unlock();
    

    if( lpPlayer == NULL ){
        //cGetResourceLock.Unlock();
    }

    return lpPlayer;
}

//////////////////////////////////////////////////////////////////////////////////////////
void CPlayerManager::DeletePlayer
//////////////////////////////////////////////////////////////////////////////////////////
// Remove a player from the player list.
// 
(
 Players *lpPlayer, // The player entry to destroy.
 BOOL boIdle        // TRUE if we delete the player because he's idle.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( boStop ) return;
    // Lock player list.
    MultiLock3( &cMaintenanceLock, &cUserLock, &cFetchLock );

    // Find the player entry.
    BOOL boFound = FALSE;
    int i = 0;
    while( i < nBufferSize && !boFound ){
        // If the entry was found.
        if( lpRegisteredUsers[ i ] == lpPlayer ){
            TRACE( "\r\nFreed player slot %u.", i );
            // Free the entry.
            lpRegisteredUsers[ i ] = NULL;
            boFound = TRUE;
        }
        i++;
    }

    // Tell the chatter channels to delete this player.
    GetChatter().Remove( lpPlayer );

    // If unit hasn't been found, there's nothing to remove.
    if( !boFound ){
        return;
    }

    // One less user!
    nUserCount--;
//    TRACE( "\r\nNew user count=%u.", nUserCount );
//    PERF_CNT( PRFUSERS_ONLINE_USERS ) = nUserCount;

    _LOG_DEBUG
        LOG_DEBUG_LVL1,
        "Logging off player %s memaddr( 0x%x ).",
        (LPCTSTR)lpPlayer->GetFullAccountName(),
        lpPlayer->self
    LOG_

    // Unlock player list.
    cFetchLock.Unlock();
    cUserLock.Unlock();
    cMaintenanceLock.Unlock();
    

    // If logoffs have not been stopped.
    PostQueuedCompletionStatus( hDeletionIo, 0, reinterpret_cast< DWORD >( lpPlayer ), NULL );    
}

//////////////////////////////////////////////////////////////////////////////////////////
void CPlayerManager::AsyncDeletePlayer
//////////////////////////////////////////////////////////////////////////////////////////
//  Asynchronously deletes players.
// 
(
 LPVOID lpNull // NULL
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	CAutoThreadMonitor tmMonitor("Async Delete Player");
    _LOG_DEBUG
        LOG_DEBUG_LVL1,
        "PlayerDeletion Thread Id=%u",
        GetCurrentThreadId()
    LOG_
        
    CDeadlockDetector cDeadlockDetector;
    cDeadlockDetector.RegisterThread( hDeleteThread, "Player Deletion Thread", 300000  );
    
    // While player manager is running
    while( boMaintenance )
	{
        DWORD dwBytes = 0;
        DWORD dwPlayerAddress = 0;
        LPOVERLAPPED lpOverlapped = NULL;
    
        ENTER_TIMEOUT;
        // Get next player to delete.
        if( GetQueuedCompletionStatus( hDeletionIo, &dwBytes, &dwPlayerAddress, &lpOverlapped, 60000 ) )
		{
            LEAVE_TIMEOUT;

            // Get player's object.
            Players *lpPlayer = reinterpret_cast< Players * >( dwPlayerAddress );

            // Wait pending saves.
            lpPlayer->self->WaitForSaving();

	        // Lock player usage ( any async functions performing on player must complete ).
	        lpPlayer->UseDeathLock();
            lpPlayer->UseUnlock( __FILE__, __LINE__ );

            lpPlayer->Logoff();
    
            if( lpPlayer->IsIdle() ){ //BLBLBL cet appel est effectué plusieurs dizaines de fois par seconde, ce qui incrémente trop vite le nombre de IdleChances !
                _LOG_WORLD
                    LOG_MISC_1,
                    "User %s got kicked-out due to timeout.",
                    (LPCTSTR)lpPlayer->GetFullAccountName()
                LOG_        
            }

	        // Log player exit
            if( lpPlayer->registred ){
                CString csText;
                CString csOther;
                csText.Format( "User %s logged off. memaddr( 0x%x )", lpPlayer->GetFullAccountName(), lpPlayer->self );
                if( lpPlayer->in_game ){
                    csOther.Format( "  Character %s was in game and exited from position ( %u, %u, %u ).",
                        lpPlayer->self->GetTrueName(),
                        lpPlayer->self->GetWL().X,
                        lpPlayer->self->GetWL().Y,
                        lpPlayer->self->GetWL().world
                    );
                    csText += csOther;
                }else{//BLBL on affiche les détails même si le personnage était pas en ligne.
                    csOther.Format( "  Character %s was NOT in_game ?? and exited from position ( %u, %u, %u ).",
                        lpPlayer->self->GetTrueName(),
                        lpPlayer->self->GetWL().X,
                        lpPlayer->self->GetWL().Y,
                        lpPlayer->self->GetWL().world
                    );
                    csText += csOther;
				}

                _LOG_WORLD
                    LOG_MISC_1,
                    (char *)(LPCTSTR)csText
                LOG_
            }else{



            }
            // Write credit deductions if any.
            lpPlayer->WriteCreditDeduction();

	        // Lock User and perform Unit/World related removes.
            lpPlayer->self->Lock();

            // Try to remove player from world wether it is in game of not.
	        WorldMap *wlWorld = TFCMAIN::GetWorld( lpPlayer->self->GetWL().world );
	        if( wlWorld ){
		        wlWorld->remove_world_unit( lpPlayer->self->GetWL(), lpPlayer->self->GetID());
	        }

	        if( lpPlayer->in_game ){
                Broadcast::BCObjectRemoved( lpPlayer->self->GetWL(), _DEFAULT_RANGE,
                    lpPlayer->self->GetID()
                );
	        }
	        if( lpPlayer->in_game || lpPlayer->boRerolling || lpPlayer->boPreInGame ){
		        lpPlayer->self->SaveCharacter( FALSE );
	        }

            //lpPlayer->self->WaitForSaving();

            // Player is now deleted, dereference it from the Unit.
            lpPlayer->self->SetPlayer( NULL );

            if( lpPlayer->in_game ){
	            lpPlayer->ModifyPlayer( 
                    lpPlayer->self->GetTrueName(), 
                    (WORD)lpPlayer->self->GetAppearance(), 
                    (WORD)lpPlayer->self->GetLevel() 
                 );
	            // Save player.
	            lpPlayer->SaveAccount();
            }
            // Free Unit resource
            lpPlayer->self->Unlock();

            // Last of ALL, send unit to deathrow for destruction.
	        LPDEATHROW lpMandate = new DEATHROW;
	        lpMandate->lpuCondemned = lpPlayer->self;
	        lpMandate->boDelete = TRUE;
									        
	        // Add player for deletion!
	        tluDeathRow.Lock();
	        tluDeathRow.AddToTail( lpMandate );
	        tluDeathRow.Unlock();                            

	        // Delete the player structure
            delete lpPlayer;
        }
    }

    STOP_DEADLOCK_DETECTION
}

//////////////////////////////////////////////////////////////////////////////////////////
Players *CPlayerManager::GetPlayerResource
//////////////////////////////////////////////////////////////////////////////////////////
// Fetches a player resource.
// 
(
 sockaddr_in sockAddr // The address of the player to fetch.
)
// Return: Players, the locked player resource.
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( boStop ) return NULL;

    //cGetResourceLock.Lock();   

    Players *lpPlayer;

    // Find the player structure.
    int i;
    BOOL   boFound = FALSE;
    bool   playerLockedOrAbsent = false;
    
    // These two variables make sure that the player is dropped when it is locked
    // for too much time.
    const  int maxLoopCount = 100; // steph ajout de int
    int    loopCount = 0;

    // Loop until we either find a player and successfully lock it,
    // or until the player isn't found in the list.    
    // NOTE: This is done to ensure thread safety when fetching player resources.
    while( !playerLockedOrAbsent && loopCount < maxLoopCount ){
        // Lock the registered user array.
  
        CAutoLock fetchLock( &cFetchLock );

        i = 0;
        // Scroll through the array of registered users.
        while( i < nBufferSize && !boFound ){
            lpPlayer = lpRegisteredUsers[ i ];
            // If there is a player in this slot.
            if( lpPlayer != NULL ){
                // If the player was found (same IP address).
                if( SAME_IP( lpPlayer->IPaddr, sockAddr ) ){
                    // Break search, player was found.
                    boFound = TRUE;
                }
            }
            i++;
        }
  

        // If the player wasn't found.
        if( !boFound ){
            // Player is NULL
            lpPlayer = NULL;
            // And break from main loop (player is absent).
            playerLockedOrAbsent = true;
        }else{
            // Otherwise try to lock the player.
            if( lpPlayer->PickLock() ){
                // If the player was successfully locked, 
                // break from main loop (player is locked)
                playerLockedOrAbsent = true;
            }
            // Otherwise, reloop and try to fetch the player again, until the player
            // is unlocked or its entry gets deleted from the list.
        }

        // Increase loop count, to make sure the function doesn't stall if the player
        // is locked for too much time.
        loopCount++;
    }

    // If the loop broke because the loopCount exceeded
    if( !playerLockedOrAbsent ){
        // Set player to NULL, player was denied packet interpretation.
        lpPlayer = NULL;        
    }

    if( lpPlayer == NULL ){
        //cGetResourceLock.Unlock();
    }

    return lpPlayer;
}
//////////////////////////////////////////////////////////////////////////////////////////
void CPlayerManager::FreePlayerResource
//////////////////////////////////////////////////////////////////////////////////////////
// Frees a player object.
// 
(
 Players *lpPlayer // The player to free
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( boStop ) return;

    //cGetResourceLock.Unlock();

    lpPlayer->Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL CPlayerManager::SearchForConnection
//////////////////////////////////////////////////////////////////////////////////////////
// Search for this address among the registered users
// 
(
 const sockaddr_in &sockAddr // the address to search for
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( boStop ) return FALSE;

	Players *lpPlayer;

    for (int i=0; i < nBufferSize; i++) {
		lpPlayer = lpRegisteredUsers[i];
		if ( lpPlayer != NULL && SAME_IP(lpPlayer->IPaddr, sockAddr) ) return TRUE;
	}
	return FALSE;

}
//////////////////////////////////////////////////////////////////////////////////////////
void CPlayerManager::GetGlobalBroadcastAddress
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the addresses of all in game players.
// 
(
 vector< sockaddr_in > &vAddresses,
 SendPacketVisitor *packetVisitor,
 bool inGame
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( boStop ) return;

    Players *lpPlayer;
    int i;    
    
    cFetchLock.Lock();
    
    // Scroll the list of users.
    for( i = 0; i < nBufferSize; i++ ){
        lpPlayer = lpRegisteredUsers[ i ];
        if( lpPlayer != NULL ){
            // User must be ingame
            if( lpPlayer->in_game || !inGame ){
                bool addIP = true;
                if( packetVisitor != NULL ){
                    addIP = packetVisitor->SendPacketTo( lpPlayer->self );
                }
                if( addIP ){
                    // Create a new IP object.
                    vAddresses.push_back( lpPlayer->IPaddr );
                }
            }
        }
    }

    cFetchLock.Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
void CPlayerManager::GetLocalBroadcastAddress 
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the addresses of all players local to a certain spot in a world.
// 
(
 vector< sockaddr_in > &vAddresses,
 WorldPos wlPos, // 
 int nRange, // 
 SendPacketVisitor *packetVisitor
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( boStop ) return;

    Players *lpPlayer;
    int i;    
    WorldPos wlPlayerPos;
    
    cFetchLock.Lock();
    
    // Scroll the list of users.
    for( i = 0; i < nBufferSize; i++ ){
        lpPlayer = lpRegisteredUsers[ i ];
        if( lpPlayer != NULL ){
            // User must be ingame
            if( lpPlayer->in_game != NULL && lpPlayer->in_game==TRUE ){//BLBL ajout d'un test NuLL & in_game==true
                // Fetch player position.
                wlPlayerPos = lpPlayer->self->GetWL();

                // If in same world.
                if( wlPlayerPos.world == wlPos.world ){

                    // If within range.
                    if( abs( wlPlayerPos.X - wlPos.X ) <= nRange && 
                        abs( wlPlayerPos.Y - wlPos.Y ) <= nRange*2 ){ //BLBL : le range Y multiplé par 2 car il y a 1.5 fois plus de cases en Y qu'en X au format 1024x768. _DEFAULT_RANGE
                        
                        bool addIP = true;
                        if( packetVisitor != NULL ){
                            addIP = packetVisitor->SendPacketTo( lpPlayer->self );
                        }
                        if( addIP ){                        
                            // Create a new IP object.
                            vAddresses.push_back( lpPlayer->IPaddr );
                        }
                    }
                }
            }
        }
    }

    cFetchLock.Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
void CPlayerManager::PlayerMaintenance
//////////////////////////////////////////////////////////////////////////////////////////
// Player maintenance thread.
// 
(
 LPVOID lpData
)
//////////////////////////////////////////////////////////////////////////////////////////
{    
	CAutoThreadMonitor tmMonitor("Player Maintenance");
    _LOG_DEBUG
        LOG_DEBUG_LVL1,
        "PlayerMaintenance Thread Id=%u",
        GetCurrentThreadId()
    LOG_
//DC
	DWORD delay = theApp.sOracleHB.csDelay*60;
	time_t ttCurTime;	
	time_t ttHitTime;
	BOOL OracleHit=false;
//DC
    
    CDeadlockDetector cDeadlockDetector;
    cDeadlockDetector.RegisterThread( hMaintenanceThread, "Player Maintenance Thread", 120000  );            
   
    int i;
    Players *lpPlayer;
    DWORD dwInitialTime = 0;

    TemplateList <Players> tlPlayersToDelete;

	if (theApp.sOracleHB.csState){///////////////////////////////////DC
		time( &ttHitTime );
	}////////////////////////////////////////////////////////////////DC


    while( boMaintenance ){
        KEEP_ALIVE

        cMaintenanceLock.Lock();

        CCommCenter *lpComm = CPacketManager::GetCommCenter();
        
        // If CommCenter is still alive.
        if( lpComm != NULL ){
            std::vector< sockaddr_in > *vLostConnections = lpComm->GetLostConnections();
            // If there are lost connections.
            if( !vLostConnections->empty() ){
                _LOG_DEBUG
                    LOG_DEBUG_LVL4,
                    "PM:Found %u lost connections.",
                    vLostConnections->size()
                LOG_

                // Find any player who has this IP address
                for( i = 0; i < nBufferSize; i++ ){
                    lpPlayer = lpRegisteredUsers[ i ];

                    if( lpPlayer != NULL ){
                        std::vector< sockaddr_in >::iterator f;
                        for( f = vLostConnections->begin(); f != vLostConnections->end(); f++ ){
                            // If the IP matches that of a lost connection, delete player.
                            if( SAME_IP( (*f), lpPlayer->IPaddr ) ){
                                _LOG_DEBUG
                                    LOG_DEBUG_LVL4,
                                    "PM:Found lost connection player."
                                LOG_
                                _LOG_WORLD
                                    LOG_MISC_1,
                                    "Player %s will be disconnected because T4C received a destination unreachable packet.",
                                    (LPCTSTR)lpPlayer->GetFullAccountName()
                                LOG_
                                lpPlayer->DeletePlayer();
                            }
                        }                                        
                    }
                }
            }
            lpComm->FreeLostConnections( TRUE );
        }


        // Scroll through all players currently in game for maintenance.
        for( i = 0; i < nBufferSize; i++ ){
            KEEP_ALIVE;
            lpPlayer = lpRegisteredUsers[ i ];

            // If player 
            if( lpPlayer != NULL ){
                // If the player ressource could be fetched.
                if( lpPlayer->PickLock() ){

                    // If the maintenance thread should delete this player. ( Idle or to delete ).
                    if( ( lpPlayer->Delete() || lpPlayer->IsIdle() ) && !lpPlayer->IsLoading() ){
                        if( lpPlayer->Delete() ){
                            _LOG_DEBUG
                                LOG_DEBUG_HIGH,
                                "Flushing player %s because delete flag was true.",
                                (LPCTSTR)lpPlayer->GetFullAccountName()
                            LOG_
                        }
                        
                        // Delete player.
                        tlPlayersToDelete.AddToTail( lpPlayer );
                    }else{

#define HVYLOG(Z)  if( f ){ fprintf( f,  Z ); fflush(f);}
                   
						// Require lock on Unit structure to do unit specific maintenance
                        if( lpPlayer->self->PickLock() ){

                            //CString fileName( theApp.sPaths.csLogPath );
                            //fileName += "heavydbg.txt";
                            //FILE *f = fopen( fileName, "wb" );

                            //HVYLOG( "A" );
                            
                            // Must user auto-save?
                            lpPlayer->QueryNextSave();

                           //HVYLOG( "B" );

                            ENTER_TIMEOUT;

                            //HVYLOG( "C" );
                            // Check if we must send watch dog packets to radius server.                                
                            //lpPlayer->QueryAuthWatchDog();
                            //HVYLOG( "D" );
                            
                            LEAVE_TIMEOUT;
                            //HVYLOG( "E" );

                            // Can player regen?
                            if( lpPlayer->in_game && lpPlayer->dwRegenTime <= TFCMAIN::GetRound() ){
                                //HVYLOG( "F" );
                                // Regen hp and mana.
                                //GAME_RULES::HPregen( lpPlayer->self );
                                //GAME_RULES::ManaRegen( lpPlayer->self );
                                lpPlayer->self->Regenerate();
                                //HVYLOG( "G" );
                                lpPlayer->dwRegenTime = 2 SECONDS TDELAY;
                            }
                            //HVYLOG( "H" );

			    		    // Verify the unit's messages
		    			    lpPlayer->self->VerifyTimers();

							//BLBL 08/09/2009 : antispeedhack system, on vérifie si il y a encore des packets de mouvements stockés à envoyer :
														
							if (lpPlayer->MoveList.size()>0){

								const INT MoveExhaust = 0;//BLBLBL 200=>400=>200 pour cette boucle là, à 100 on peut encore speedhacker !! // steph ajout de INT // steph 0 au lieu de 200 MILLISECONDS
								TFCPacket sending;
								WorldPos tmp;
								char searchway;
								WorldPos saved_pos = lpPlayer->self->GetWL();
								EXHAUST newExhaust = lpPlayer->self->GetExhaust();

								if( newExhaust.move <= TFCMAIN::GetRound() ) {
								

									//BL Ce système implémente une "liste de mouvements à faire"
									//Cela permet d'éviter le speedhack.
									//Ces appels à MoveUnit doivent être les mêmes que ceux dans TFCMessageHandler.cpp
									//puisque cette liste de mouvements à effectuer utilise les mêmes appels à MoveUnit.
									switch( lpPlayer->MoveList.front() )
									{
										case RQ_MoveNorth:               // NORTH
												tmp = lpPlayer->self->MoveUnit(DIR::north, false, true, true );
												searchway = DIR::north;
												break;
										case RQ_MoveNorthEast:               // NORTHEAST
												tmp = lpPlayer->self->MoveUnit(DIR::northeast, false, true, true );
												searchway = DIR::northeast; 
												break;
										case RQ_MoveEast:                // EAST
												tmp = lpPlayer->self->MoveUnit(DIR::east, false, true, true );
												searchway = DIR::east;
												break;
										case RQ_MoveSouthEast:				   // SOUTHEAST
												tmp = lpPlayer->self->MoveUnit(DIR::southeast, false, true, true );
												searchway = DIR::southeast;
												break;
										case RQ_MoveSouth:                // SOUTH
												tmp = lpPlayer->self->MoveUnit(DIR::south, false, true, true );
												searchway = DIR::south;
												break;
										case RQ_MoveSouthWest:                // SOUTHWEST
												tmp = lpPlayer->self->MoveUnit(DIR::southwest, false, true, true );
												searchway = DIR::southwest;
												break;
										case RQ_MoveWest:		           // WEST
												tmp = lpPlayer->self->MoveUnit(DIR::west, false, true, true ); 
												searchway = DIR::west;
												break;
										case RQ_MoveNorthWest:                // NORTHWEST						
												tmp = lpPlayer->self->MoveUnit(DIR::northwest, false, true, true );
												searchway = DIR::northwest;
												break;
										case RQ_GetPlayerPos:
												tmp = lpPlayer->self->GetWL();
												searchway = -1;
												break;
									}

									newExhaust.move = TFCMAIN::GetRound() + MoveExhaust;
						
									//lpPlayer->Lock();//BLBL test de lock apparement cause un pb de RST (flag qui s'attribue plus bien)
								    lpPlayer->self->SetExhaust(newExhaust);
									//lpPlayer->Unlock();//BLBL test de delock apparement cause un pb de RST (flag qui s'attribue plus bien)
									
						/*			lpPlayer->lMoveCounter++;
						_LOG_CHEAT LOG_MISC_1, 
							"Moved %s from fifo, exaust is %i",
							lpPlayer->self->GetTrueName(),
							lpPlayer->self->GetExhaust()							
						LOG_;*/
									lpPlayer->MoveList.pop_front();


								}else{//fin if !exhaust

									tmp = lpPlayer->self->GetWL();

								}								

								WorldMap *world = TFCMAIN::GetWorld(tmp.world);
								
								// Then send the peripheric object to the person who moved					
								if( ( tmp.X != saved_pos.X || tmp.Y != saved_pos.Y || tmp.world != saved_pos.world ) && world != NULL )
								{				
									// If there are peripheral objects to packet.
									if( world->packet_peripheral_units(tmp, 0, (DIR::MOVE)searchway, sending, lpPlayer->self ) ){
										
										lpPlayer->self->SendPlayerMessage( sending );
									}
                
									/*if( !user->self->LastMoveWasBroadcasted()// || 
										//user->self->GetPlayer()->GetGodFlags() & GOD_TRUE_INVISIBILITY ||
										//user->self->ViewFlag( __FLAG_INVISIBILITY ) != 0 
									 ){*///BLBLBL test de on broadcast tout le temps le mouvement 
										TFCPacket sending;
										sending << (RQ_SIZE)__EVENT_OBJECT_MOVED;
										sending << (short)lpPlayer->self->GetWL().X;
										sending << (short)lpPlayer->self->GetWL().Y;     // where the player has moved (is now)
										
										lpPlayer->self->PacketUnitInformation( sending );                
		    							lpPlayer->self->SendPlayerMessage( sending );
								   // }
								}		


							}
							//BLBL///////////////


                            //HVYLOG( "I" );
                            // Free unit structure.
                            lpPlayer->self->Unlock();

                            //HVYLOG( "J" );
                            //if( f) {fclose(f);};
                        }


                        // If we should perform credit deduction.
                        if( lpPlayer->CreditDeduction() ){
                            // If user has been online for more time then he has credits
                            if( lpPlayer->GetOnlineTime() >= lpPlayer->GetCredits() && lpPlayer->dwKickoutTime == 0xFFFFFFFF ){
                                CString csText = _STR( 11660, IntlText::GetDefaultLng() );
                        
                                TFCPacket sending;
			                    sending << (RQ_SIZE)RQ_ServerMessage;
			                    sending << (short)30;
    			                sending << (short)3;
	    		                sending << (CString &)csText;	
								sending << (long)RGB( 255, 0, 0 );
			                    lpPlayer->self->SendPlayerMessage( sending );

								RegKeyHandler RegistryKey;
								RegistryKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY AUTH_KEY );

			                    // Display a custom message (sysop defined) to the player
								csText = RegistryKey.GetProfileString("OutOfCreditsMessage", "");
								if ( !csText.IsEmpty() ) {
									sending.Destroy();
									sending << (RQ_SIZE)RQ_ServerMessage;
									sending << (short)30;
    								sending << (short)3;
	    							sending << (CString &)csText;
									sending << (long) RGB( 255, 0, 5 );
									lpPlayer->self->SendPlayerMessage( sending );
								}

								// Redirect player to a Server Web Page (sysop defined) where he can buy credits
								CString csURL;
								csURL = RegistryKey.GetProfileString("OutOfCreditsURL", "");
								if ( !csURL.IsEmpty() ) {
									sending.Destroy();
									sending << (RQ_SIZE)RQ_OpenURL;
									sending << (CString&)csURL;
									lpPlayer->self->SendPlayerMessage( sending );
								}
                    
                                // flush player.
                                lpPlayer->dwKickoutTime = 5 SECONDS TDELAY;
                            }
                            if( ( lpPlayer->GetCredits() - lpPlayer->GetOnlineTime() ) / 60 < 
                                lpPlayer->cMinutesLeft && lpPlayer->dwKickoutTime == 0xFFFFFFFF ){
                        
                                lpPlayer->cMinutesLeft = (char)( ( lpPlayer->GetCredits() - lpPlayer->GetOnlineTime() ) / 60 );
                                // If quantity of minutes must be adjusted.                                                        
                                CString csText;
                                csText.Format( _STR( 11661, IntlText::GetDefaultLng() ), lpPlayer->cMinutesLeft + 1 );

                                TFCPacket sending;
			                    sending << (RQ_SIZE)RQ_ServerMessage;
			                    sending << (short)30;
    			                sending << (short)3;
	    		                sending << (CString &)csText;
								sending << (long)RGB( 235, 235, 0 );
			                    lpPlayer->self->SendPlayerMessage( sending );                            
                            }
                        }
                    }
                    lpPlayer->Unlock();
                }
            }
        }

        // Lock the player resources (not resources allowed to be checked out)
        // while we verify in-game issues.        
        {
            //cGetResourceLock.Lock();
        
            // Scroll through all players currently in game for maintenance.
            for( i = 0; i < nBufferSize; i++ ){
                KEEP_ALIVE;
                lpPlayer = lpRegisteredUsers[ i ];

                // If player 
                if( lpPlayer == NULL ){
                    continue;
                }
                // Should always succeed since no ressources are checked out.
                if( lpPlayer->PickLock() ){
                    if( lpPlayer->self->GetTarget() != NULL ){
                        // If the character structure could be locked.
                        if( lpPlayer->self->PickLock() ){
                            // Get the target.
                            Unit *target = lpPlayer->self->GetTarget();
                            // Get a lock on the target right now.
                            if( target->PickLock() ){                    
                                // Verify auto-combat.
                                lpPlayer->self->ExecAutoCombat();
                    
                                target->Unlock();
                            }
                            lpPlayer->self->Unlock();
                        }
                    }
                    lpPlayer->Unlock();
                }
            }
        
            //cGetResourceLock.Unlock();
        }

        

        // Delete all players that were added for deletion
        tlPlayersToDelete.ToHead();
        while( tlPlayersToDelete.QueryNext() ){
            RemoveTargetReferences( tlPlayersToDelete.Object()->self );

            // Delete player.
            DeletePlayer( tlPlayersToDelete.Object() );
            tlPlayersToDelete.Remove();
        }

		if (theApp.sOracleHB.csState){//DC
			time( &ttCurTime );
			if ( (ttCurTime-ttHitTime) > delay ){
				_LOG_DEBUG  LOG_DEBUG_LVL4, "Oracle Heart Beat sent to the data base" LOG_
				ttHitTime = ttCurTime;

				OracleHit = lpPlayer->AccountHeartBeat();
				if ( OracleHit ){
//					_LOG_DEBUG  LOG_DEBUG_LVL4, "Oracle have been hit by the Player Manager 3 " LOG_
				}
				else{
					_LOG_DEBUG  LOG_DEBUG_LVL4, "Oracle Heart Beat have failed! " LOG_
				}
			}
		}//DC


		cMaintenanceLock.Unlock();

        Sleep( 25 );//BLBLBL Faudrait 20 pour s'harmoniser en nombre de "tours" sur la boule main

    }

    STOP_DEADLOCK_DETECTION
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL CPlayerManager::PageUser
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the address of the player named 'name'
// 
(
 Players *sender,
 CString &csPlayer,
 CString csSender,
 CString csMessage,
 bool    boCanPageInvisible
)
// Return: BOOL, TRUE if the user was found.
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( boStop ) return FALSE;

    int i;

    BOOL boReturn = TRUE;

    Players *lpFoundPlayer = NULL;
    
    cFetchLock.Lock();

    i = 0;
    // Scroll through all users.
    while( i < nBufferSize  ){
        Players *lpPlayer = lpRegisteredUsers[ i ];

        if( lpPlayer != NULL ){
            if( !lpPlayer->boWhoInvisible || boCanPageInvisible ){
                CString csFoundName = lpPlayer->self->GetTrueName();
                csFoundName.MakeUpper();

                // If this player corresponds to the player
                csPlayer.MakeUpper();            
                if( csFoundName.Find( csPlayer ) == 0 ){
                    // If no name was previously found or if the name exactly matches the specified name.
                    if( lpFoundPlayer == NULL || csFoundName == csPlayer ){
                        lpFoundPlayer = lpPlayer;
                    }
                }
            }
        }
        i++;
    }
    // If a player was found.
    if( lpFoundPlayer != NULL ){

        // If the player's pages are off.
        if( !lpFoundPlayer->PageState() ){
            csPlayer = lpFoundPlayer->self->GetTrueName();

            CString errMsg;
            errMsg.Format(
                _STR( 7125, sender->self->GetLang() ),
                csPlayer
            );

            sender->self->SendSystemMessage( errMsg );

            boReturn = FALSE;            
        }else{
            bool doPage = true;
            CString msgAppend;

            // If the player is not allowed to page and if the target
            // player is not a gameop with re
            if( !sender->boCanPage ){
                // If the target player is a gameop
                if( lpFoundPlayer->GetGodFlags() & GOD_CAN_REMOVE_SHOUTS ){
                    // Append a small header to the user's message
                    msgAppend = "<pages revoked>: ";
                }else{
                    doPage = false; // Do not allow paging.
                }
            }
            
            if( doPage ){
                csMessage = msgAppend + csMessage;

                // Update player name
                csPlayer = lpFoundPlayer->self->GetTrueName();

                _LOG_PAGE
                    LOG_MISC_1,
                    "Player %s pages player %s, saying '%s'.",
                    (LPCTSTR)csSender,
                    (LPCTSTR)lpFoundPlayer->self->GetTrueName(),
                    (LPCTSTR)csMessage
                LOG_                

		        TFCPacket sending;
		        sending << (RQ_SIZE)RQ_Page;			
		        sending << (CString &)csSender;
		        sending << (CString &)csMessage;

                WorldPos wlDummy = { -1, -1, -1 };
                CPacketManager::SendPacket( sending, lpFoundPlayer->IPaddr, -1, wlDummy, FALSE );
            }else{
                // Send a message to the sender stating that his shouts were revoked.
                sender->self->SendSystemMessage( _STR( 7172, sender->self->GetLang() ) );
            }
        }
    }else{
		// Player not found! Send null ack.
		csMessage = "";
		TFCPacket sending;
		sending << (RQ_SIZE)RQ_Page;
		sending << (CString &)csMessage;
		sending << (CString &)csMessage;
		
		sender->self->SendPlayerMessage( sending );
        
        boReturn = FALSE;
    }

    cFetchLock.Unlock();

    return boReturn;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool CPlayerManager::MSComGetUserList
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the list of users on the system.
// 
(
 BYTE bCode,
 LPBYTE &lpBuffer,
 int &nSize
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( boStop ) return false;

    if( bCode != 0xf0 ){
        return false;
    }
    
    Players *lpPlayer;
    int i, j;
    CString csName;
    
    TFCPacket sending;
    sending << (char)0x70;
    sending << (char)'T';
    sending << (char)'h';
    sending << (char)'e';
    sending << (char)' ';
    sending << (char)'4';
    sending << (char)'t';
    sending << (char)'h';
    sending << (char)' ';
    sending << (char)'C';
    sending << (char)'o';
    sending << (char)'m';
    sending << (char)'i';
    sending << (char)'n';
    sending << (char)'g';
    sending << (char)0;

    cFetchLock.Lock();
    for( i = 0; i < nBufferSize; i++ ){
        lpPlayer = lpRegisteredUsers[ i ];

        if( lpPlayer != NULL ){
            csName = lpPlayer->GetAccount();

            for( j = 0; j < csName.GetLength(); j++ ){
                sending << (char)csName[ j ];
            }
            
            sending << (char)0;
            sending << (char)0;
        }    	
    }
    cFetchLock.Unlock();
    
    sending << (char)0;
    sending << (char)0;
    sending << (char)0;

    const INT PacketHeader = KEY_SIZE + CHECKSUM_SIZE; // steph ajout de INT

    // Get the packet's buffer and copy it into the provided buffer.
    LPBYTE lpTempBuf = NULL;
    sending.GetBuffer( lpTempBuf, nSize );
    nSize -= PacketHeader;

    lpBuffer = new BYTE[ nSize ];
    memcpy( lpBuffer, lpTempBuf + PacketHeader, nSize );

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////
void CPlayerManager::PacketUserList
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the player listing.
// 
(
 Players *lpUser
)
//////////////////////////////////////////////////////////////////////////////////////////
{   
    if( boStop ) return;
  
    int i;    
    Players *lpPlayer;
    TFCPacket sending;
	CString csVoid = "";

    sending << (RQ_SIZE)RQ_GetOnlinePlayerList;

    TemplateList <Players> tlFoundUsers;

    cFetchLock.Lock();
    
    for( i = 0; i < nBufferSize; i++ ){
        lpPlayer = lpRegisteredUsers[ i ];

        if( lpPlayer != NULL ){
            // If player isn't invisible to player listing, or if player is a god.
            if( lpPlayer->in_game && !lpPlayer->boWhoInvisible || ( lpUser->GetGodFlags() & GOD_CAN_SEE_ACCOUNTS ) ){
                tlFoundUsers.AddToTail( lpPlayer );
		    }
        }    	
    }

    sending << (short)tlFoundUsers.NbObjects();
    tlFoundUsers.ToHead();
	while( tlFoundUsers.QueryNext() ){
		lpPlayer = tlFoundUsers.Object();
		// Player invisible?
		if( lpPlayer->boWhoInvisible ){
			CString csName;
			csName = lpPlayer->GetFullAccountName();
			csName += "(invisible)";	// append

			sending << (CString &)csName;
			if( lpPlayer->in_game ){
				sending << (CString &)lpPlayer->self->GetTrueName();
			}else{
				sending << (CString &)csVoid;
			}
		}
		// otherwise display normally
		else{

            if( lpUser->GetGodFlags() & GOD_CAN_SEE_ACCOUNTS ){
                sending << (CString &)lpPlayer->GetFullAccountName();
            }else{
                sending << (CString &)csVoid;
            }
			if( lpPlayer->in_game ){
				sending << (CString &)lpPlayer->self->GetTrueName();
			}else{
				sending << (CString &)csVoid;
			}
		}
	}
    cFetchLock.Unlock();

    lpUser->self->SendPlayerMessage( sending );
}


//////////////////////////////////////////////////////////////////////////////////////////
BOOL CPlayerManager::VerifyPlayerUnique
//////////////////////////////////////////////////////////////////////////////////////////
// Makes sure player is unique (not twice). Will bump any same-player found.
//
(
 Players *lpPlayer
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( boStop ) return FALSE;

    BOOL boUnique = TRUE;

    Players *lpOtherPlayer;
    // Try to find another player.
    cFetchLock.Lock();
    
    TRACE( "\r\nCurrentPlayer=0x%x.", lpPlayer );

    int i;
    for( i = 0; i < nBufferSize; i++ ){
        lpOtherPlayer = lpRegisteredUsers[ i ];

        if( lpOtherPlayer != NULL ){
            TRACE( "\r\nFound player ( 0x%x ) in slot %u.", lpOtherPlayer, i );
            
            bool sameAccount = false;
            if( theApp.sAuth.m_StripRealmPartOfAccount ){
                sameAccount = stricmp( (LPCTSTR)lpOtherPlayer->GetAccount(), (LPCTSTR)lpPlayer->GetAccount() ) == 0;
            }else{
                sameAccount = stricmp( (LPCTSTR)lpOtherPlayer->GetFullAccountName(), (LPCTSTR)lpPlayer->GetFullAccountName() ) == 0;
            }

            // If player is already online but isn't on the same player resource.
            if( lpOtherPlayer != lpPlayer && sameAccount ){
                _LOG_DEBUG
                    LOG_DEBUG_HIGH,
                    "Flagging delete for %s because character is already online.",
                    (LPCTSTR)lpOtherPlayer->GetFullAccountName()
                LOG_
                
                // Send other player for deletion.
                lpOtherPlayer->DeletePlayer();

                // Send this current player for deletion also.
                lpPlayer->DeletePlayer();

                boUnique = FALSE;
		    }
        }    	
    }

    cFetchLock.Unlock();

    return boUnique;
}

//////////////////////////////////////////////////////////////////////////////////////////
Players *CPlayerManager::GetCharacter
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the player which has an in game character of a certain name.
// 
(
 CString csName // The name of the character to search.
)
// Return: Players, the found player structure.
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( boStop ) return NULL;

    cFetchLock.Lock();

    Players *lpPlayer;
    Players *lpFoundPlayer = NULL;
	// BEGIN : Mestoph -> Fix for get character
	CString csNameCpy = csName;
	// END : Mestoph -> Fix for get character
	
    int i = 0;

	// BEGIN : Mestoph -> Fix for get character
	while( i < nBufferSize && lpFoundPlayer == NULL )
	{
        lpPlayer = lpRegisteredUsers[ i ];

        if( lpPlayer != NULL )
		{
            if( lpPlayer->in_game )
			{
                CString csFoundName = lpPlayer->self->GetTrueName();
                csFoundName.MakeUpper();

                // If this player corresponds to the player
                csNameCpy.MakeUpper();            
                if( csFoundName.Find( csNameCpy ) == 0 )
				{
                    // If no name was previously found or if the name exactly matches the specified name.
                    if( lpFoundPlayer == NULL || csFoundName == csNameCpy )
                        lpFoundPlayer = lpPlayer;
                }
            }
        }
        i++;
    }
    /* Before : while( i < nBufferSize && lpFoundPlayer == NULL ){    
        lpPlayer = lpRegisteredUsers[ i ];

        if( lpPlayer != NULL ){            
            
            if( lpPlayer->in_game ){
                // If player names match.
                if( stricmp( (LPCTSTR)lpPlayer->self->GetTrueName(), (LPCTSTR)csName ) == 0 ){
                    // Player was found.
                    lpFoundPlayer = lpPlayer;
                }
            }
        }
        i++;
    }*/
	// END : Mestoph -> Fix for get character

    cFetchLock.Unlock();

    return lpFoundPlayer;
}

//////////////////////////////////////////////////////////////////////////////////////////
void CPlayerManager::SaveAll( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Saves all players currently in game.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    Players *lpPlayer;
    
    cFetchLock.Lock();    
    int i;
    for( i = 0; i < nBufferSize; i++ ){
        lpPlayer = lpRegisteredUsers[ i ];

        if( lpPlayer != NULL ){
            // Logoff all users.
            lpPlayer->DeletePlayer();

        }
   }

   cFetchLock.Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
ChatterChannels &CPlayerManager::GetChatter( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the chatter channels instance.
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( lpChatter == NULL ){
        // Create the chatter channels.        
        lpChatter = new ChatterChannels();
    }

    return *lpChatter;
}

//////////////////////////////////////////////////////////////////////////////////////////
void CPlayerManager::RemoveTargetReferences
//////////////////////////////////////////////////////////////////////////////////////////
// Removes all references to a target unit from all players.
// 
(
 Unit *targetUnit // The unit to dereference.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    MultiLock( &cMaintenanceLock, &cFetchLock );

    int i;
    for( i = 0; i < nBufferSize; i++ ){
        Players *lpPlayer = lpRegisteredUsers[ i ];

        if( lpPlayer != NULL ){           
            if( lpPlayer->self->GetTarget() == targetUnit ){
                lpPlayer->self->SetTarget( NULL );

                // If the player was robbing this player.
                if( lpPlayer->self->ViewFlag( __FLAG_ROBBING ) != 0 ){
                    lpPlayer->self->RemoveFlag( __FLAG_ROBBING );
        
                    TFCPacket sending;
                    sending << (RQ_SIZE)RQ_DispellRob;
                    lpPlayer->self->SendPlayerMessage( sending );
                }

            }
            if( lpPlayer->self->GetGameOpContext() == targetUnit ){
                lpPlayer->self->SetGameOpContext( NULL );
                lpPlayer->self->SetGold( lpPlayer->self->GetGold() );
            }
            lpPlayer->self->RemoveReferenceTo( targetUnit );
        }
   }   
   cFetchLock.Unlock();
   cMaintenanceLock.Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
void CPlayerManager::RefreshSystemChannels( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Refreshes the player list of all system channels.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock autoLock( &cFetchLock );
    
    int i;
    for( i = 0; i < nBufferSize; i++ ){
        Players *lpPlayer = lpRegisteredUsers[ i ];

        if( lpPlayer != NULL ){
           CPlayerManager::GetChatter().AddToSystemChannels( lpPlayer );
        }
    }
}