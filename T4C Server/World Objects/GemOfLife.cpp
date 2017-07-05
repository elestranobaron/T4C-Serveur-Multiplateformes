// GemOfLife.cpp: implementation of the GemOfLife class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "GemOfLife.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GemOfLife::GemOfLife()
{

}

GemOfLife::~GemOfLife()
{

}


//////////////////////////////////////////////////////////////////////////////////////////
void GemOfLife::OnDeath
//////////////////////////////////////////////////////////////////////////////////////////
// Called on death.
// 
(
 UNIT_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPDEATH_DATA lpDeathData = (LPDEATH_DATA)valueOUT;

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
	self->SetHP( self->GetMaxHP(), true );
	
	// Now teleport unit!
	self->Teleport( wlTeleportPos, 1 );

	// Cancels the player's death and destroy the gem.
	lpDeathData->bDeathType = CANCEL_DEATH | DESTROY_UNIT_ON_DEATH | DESTROY_BACKPACK;	
}

//////////////////////////////////////////////////////////////////////////////////////////
ObjectStructure *GemOfLife::CreateObject( void ){
	return new GemOfLife;
}