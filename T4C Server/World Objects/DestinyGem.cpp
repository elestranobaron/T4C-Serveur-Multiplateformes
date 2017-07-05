// DestinyGem.cpp: implementation of the DestinyGem class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "DestinyGem.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DestinyGem::DestinyGem()
{

}

DestinyGem::~DestinyGem()
{

}

//////////////////////////////////////////////////////////////////////////////////////////
void DestinyGem::OnInitialise
//////////////////////////////////////////////////////////////////////////////////////////
// Called when a gem of destiny is created.
// 
(
 UNIT_FUNC_PROTOTYPE // standard unit func prototype
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    ObjectStructure::OnInitialise( UNIT_FUNC_PARAM );
    // Gem cannot be dropped/robbed etc.	
}

//////////////////////////////////////////////////////////////////////////////////////////
void DestinyGem::OnDeath
//////////////////////////////////////////////////////////////////////////////////////////
// Called when unit holding the gem dies.
// 
(
 UNIT_FUNC_PROTOTYPE // standard unit func prototype.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
/*	LPDEATH_DATA lpDeathData = (LPDEATH_DATA)valueOUT;

	// Check to see where gem could teleport the player.
	WorldPos wlTeleportPos;

	DWORD dwPosValue = self->ViewFlag( __FLAG_DEATH_LOCATION );
	BOOL boDefaultPos = FALSE;
	
	if( dwPosValue == 0 ){
		// If flag doesn't exist use default death position.
		boDefaultPos = TRUE;
	}else{
		wlTeleportPos.X = ( (WORD)( dwPosValue >> 20 ) ) & 0x0FFF;	// Strip the first 4 bits of the word.
		wlTeleportPos.Y = ( (WORD)( dwPosValue >> 8 )  ) & 0x0FFF;
		wlTeleportPos.world = ( (BYTE)( dwPosValue ) & 0xFF );

		WorldMap *wlWorld = TFCMAIN::GetWorld( wlTeleportPos.world );

		// If world doesn't exist use default death position.
		if( wlWorld == NULL ){
			boDefaultPos = TRUE;
		}else{
			// If worldpos isn't a valid position use default death position.
			if( !wlWorld->IsValidPosition( wlTeleportPos ) ){
				boDefaultPos = TRUE;
			}
		}
	}
	
	if( boDefaultPos ){
		wlTeleportPos.X = 2973;
		wlTeleportPos.Y = 607;
		wlTeleportPos.world = 0;
	}
	
	// Now heal player.
	self->SetHP( self->GetHP() / 2 );

    __int64 nXP = self->GetXP();

    // Got killed by a player.
    if( target->GetType() == U_PC ){
        nXP = nXP / 100 * 95;
    }
    // Got killed by a npc
    else{
        nXP = nXP / 100 * 99;
    }

    self->SetXP( nXP );
	
    sending << (RQ_SIZE)RQ_ServerMessage;
    sending << (short)30;
    sending << (short)3;
    csMessage = _STR( 16 );
    sending << (CString &)csMessage;

	// Now teleport unit!
	self->Teleport( wlTeleportPos, 1 );

	// Cancels the player's death and destroy the gem.
	lpDeathData->bDeathType = CANCEL_DEATH;*/
}

//////////////////////////////////////////////////////////////////////////////////////////
ObjectStructure *DestinyGem::CreateObject( void ){
	return new DestinyGem;
}