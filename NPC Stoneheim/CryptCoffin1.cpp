///////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "CryptCoffin1.h"

CryptCoffin1::CryptCoffin1()
{}

CryptCoffin1::~CryptCoffin1()
{}

extern NPCstructure::NPC CoffinNPC;

void CryptCoffin1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void CryptCoffin1::Create( void )
{
      npc = ( CoffinNPC );
      SET_NPC_NAME( "[10841]A massive coffin" );
      npc.InitialPos.X = 675;
      npc.InitialPos.Y = 1175;
      npc.InitialPos.world = 1;
}

void CryptCoffin1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void CryptCoffin1::OnTalk( UNIT_FUNC_PROTOTYPE )
///////////////////////////////////////////////////////////////////////////

{

InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckItem(__OBJ_CRUMBLING_BONE_KEY) >= 1)
		IF((CheckNPCFlag(__FLAG_LORD_STONECREST_REPOP_DELAY) == 0) || CurrentRound >= CheckNPCFlag(__FLAG_LORD_STONECREST_REPOP_DELAY))
			GiveNPCFlag(__FLAG_LORD_STONECREST_REPOP_DELAY, CurrentRound + 36000) 
			;int nNumKeys = CheckItem(__OBJ_CRUMBLING_BONE_KEY);
			FOR(0, nNumKeys)
				TakeItem(__OBJ_CRUMBLING_BONE_KEY)
			ENDFOR
			PRIVATE_SYSTEM_MESSAGE(INTL( 9356, "You place the crumbling bone key in its place on the coffin."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 10487, "Your key crumbles to dust and the coffin begins to open..."))
			SUMMON("LORDSTONECREST", 672, 1172)
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 9356, "You place the crumbling bone key in its place on the coffin."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 9357, "The coffin begins to open..."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 9358, "Unfortunately, there is nothing inside."))
		ENDIF
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 9359, "The coffin seems to be locked somehow."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 9360, "You must step closer to the coffin to open it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk
}