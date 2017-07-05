// Hive.cpp: implementation of the Hive class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "Hive.h"
#include "TFC_MAIN.h"
#include "WorldMap.h"
#include "Creatures.h"
#include "Random.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern Random rnd;

// Constructor ///////////////////////////////////////////////////////////////////////////
Hive::Hive( void )
//////////////////////////////////////////////////////////////////////////////////////////
{
	dwCurrentEmergeTime = 0;
	wCurrentChildrenCount = 0;
}

// Destructor ////////////////////////////////////////////////////////////////////////////
Hive::~Hive( void )
//////////////////////////////////////////////////////////////////////////////////////////
{
	tlLarvae.AnnihilateList();
}

//////////////////////////////////////////////////////////////////////////////////////////
void Hive::Create
//////////////////////////////////////////////////////////////////////////////////////////
// Creates a monster larva and adds it this this larvae group.
// 
(
 WORD wNewMinEmergeTime,	// Minimum time before a larva can re-emerge.
 WORD wNewMaxEmergeTime,	// Maximum time before a larva can re-emerge.
 WORD wNewMaxChildren,		// Maximum quantity of living children larva can sustend.
 WORD wNewEmergenceRange	// Range from which larva can differ from its original position.
)
//////////////////////////////////////////////////////////////////////////////////////////
{	
	UnitType        = U_HIVE;
	Appearance      = BaseReferenceID = 0;

	wMinEmergeTime	= wNewMinEmergeTime;
	wMaxEmergeTime	= wNewMaxEmergeTime;
	wMaxChildren	= wNewMaxChildren;
	wEmergenceRange	= wNewEmergenceRange;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Hive::AddLarva
//////////////////////////////////////////////////////////////////////////////////////////
// Adds a larva to the hive.
// 
(
 LPLARVA lpLarva	// The larva to add to the hive.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	tlLarvae.AddToTail( lpLarva );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Hive::DecreaseMonsterCount( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Decreases the monster count.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	wCurrentChildrenCount--;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Hive::QueryPopup( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Queries if hive should make one of its larva emerge.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	// If its time to spawn a monster.
	if( dwCurrentEmergeTime <= TFCMAIN::GetRound() ){
		// If hive can still create monsters.
		if( wCurrentChildrenCount < wMaxChildren ){
			
			LARVA *lpLarva = NULL;
			
			// Choose a random larva from the larva group.
			tlLarvae.Lock();
			
			WORD wLarva = rnd( 0, tlLarvae.NbObjects() - 1 );
			WORD wI = 0;

            // Goto the choosen larva.
			tlLarvae.ToHead();            
            while( wI <= wLarva && tlLarvae.QueryNext() ){
    		    lpLarva = tlLarvae.Object();
                wI++;
            }

	    	// If larva was found
		    if( lpLarva != NULL ){
			    // Popup its monster
    			PopupMonster( lpLarva->wMonsterID );
	    	}


			tlLarvae.Unlock();
        }else{
            _LOG_DEBUG
                LOG_DEBUG_HIGH,
                "Hive did not popup because its children count is full (%u/%u)",
                wCurrentChildrenCount,
                wMaxChildren
            LOG_
        }
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void Hive::PopupMonster
//////////////////////////////////////////////////////////////////////////////////////////
// Pop's up a monster
// 
(
 WORD wMonsterID // ID of the monster to popup.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	// TRUE if popup is forced, FALSE if it shouldn't appear in front of a player.
	const BOOL ForcePopup = TRUE;

	WorldPos wlHivePos = GetWL();
	WorldMap *wlWorld = TFCMAIN::GetWorld( wlHivePos.world );
	
	if( wlWorld == NULL ){	
		return;
	}
	// Create a new creature
	Creatures *lpCreature = new Creatures;

	// If monster could be created.
	if( !lpCreature->Create(U_NPC, wMonsterID ) ){        	
		lpCreature->DeleteUnit();
		return;
	}

	WorldPos wlDest = { -1, -1, -1 };
    lpCreature->SetDestination( wlDest );

    if( lpCreature->SystemDestroy() ){
	    lpCreature->SetUpperLimit( wlDest );
	    lpCreature->SetLowerLimit( wlDest );
    }else{
	    WorldPos wlUpperLimit = wlHivePos;
	    wlUpperLimit.X += 25;
	    wlUpperLimit.Y += 25;
	    WorldPos wlLowerLimit = wlHivePos;
	    wlLowerLimit.X -= 25;
	    wlLowerLimit.Y -= 25;


	    lpCreature->SetUpperLimit(wlUpperLimit);
	    lpCreature->SetLowerLimit(wlLowerLimit);
    }
//            lpCreature->Do( nothing );
//        	lpCreature->SetSystemDestroy( TRUE );	// Hive spawned NPCs should be cleaned when not used.


	TRACE( "\r\nPopped up a monster!" );

	int i = 0;
    BOOL boBlock = FALSE;
    WorldPos wlPos = { 0,0, wlHivePos.world };

    do{
        // Assign it a random place.
		wlPos.X = rnd( wlHivePos.X - ( wEmergenceRange >> 1 ), wlHivePos.X + ( wEmergenceRange >> 1 ) ),
		wlPos.Y = rnd( wlHivePos.Y - wEmergenceRange, wlHivePos.Y + wEmergenceRange ),

        // Check if this pos is blocking.
        boBlock = wlWorld->IsBlocking( wlPos, NULL );
        i++;
    }while( i < 10 && boBlock );//BLBLBL n'essaye de trouver des positions qui bloquent pas

    // If monster didn't appear on a block
    if( !boBlock ){//if !FALSE

		_LOG_DEBUG
        LOG_DEBUG_LVL2,
		"Spawning monster at %u %u %u. ", wlPos.X, wlPos.Y, wlPos.world
   	    LOG_;

		TRACE( "\r\nSpawning monster at %u %u %u. ", wlPos.X, wlPos.Y, wlPos.world );
        // Set its binded hive.
		lpCreature->SetBindedHive( this );
		
		// Sets its position
		lpCreature->SetWL( wlPos );

		// Reinit the respawn time.
		wCurrentChildrenCount++;			
		dwCurrentEmergeTime = rnd( wMinEmergeTime, wMaxEmergeTime ) SECONDS;
		dwCurrentEmergeTime += TFCMAIN::GetRound();

		// Then summon it.			
		if( !wlWorld->SummonMonster( lpCreature, ForcePopup ) ){
			lpCreature->DeleteUnit();
		}
    }else{
        lpCreature->DeleteUnit();
    }
}