///////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "OracleRandomChest3.h"

OracleRandomChest3::OracleRandomChest3()
{}

OracleRandomChest3::~OracleRandomChest3()
{}

extern NPCstructure::NPC OracleChestNPC;

void OracleRandomChest3::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void OracleRandomChest3::Create( void )
{
      npc = ( OracleChestNPC );
      SET_NPC_NAME( "[10840]wooden chest" );  
      npc.InitialPos.X = 2792; 
      npc.InitialPos.Y = 2462;
      npc.InitialPos.world = 2;
}

void OracleRandomChest3::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OracleRandomChest3::OnTalk( UNIT_FUNC_PROTOTYPE )
///////////////////////////////////////////////////////////////////////////

{

InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckItem(__OBJ_DULL_COPPER_KEY) >= 1)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8700, "The chest is empty."))
	ELSEIF(CheckGlobalFlag(__GLOBAL_FLAG_ORACLE_RANDOM_CHEST) == 0)
		GiveGlobalFlag(__GLOBAL_FLAG_ORACLE_RANDOM_CHEST, rnd.roll(dice(1, 11)))
		IF(CheckGlobalFlag(__GLOBAL_FLAG_ORACLE_RANDOM_CHEST) == 3)
			GiveItem(__OBJ_DULL_COPPER_KEY)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9374, "You find a dull copper key inside the chest."))
			GiveGlobalFlag(__GLOBAL_FLAG_ORACLE_RANDOM_CHEST, rnd.roll(dice(1, 11)))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 8700, "The chest is empty."))
		ENDIF
	ELSEIF(CheckGlobalFlag(__GLOBAL_FLAG_ORACLE_RANDOM_CHEST) == 3)
		GiveItem(__OBJ_DULL_COPPER_KEY)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9374, "You find a dull copper key inside the chest."))
		GiveGlobalFlag(__GLOBAL_FLAG_ORACLE_RANDOM_CHEST, rnd.roll(dice(1, 11)))
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 8700, "The chest is empty."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 8702, "You must step closer to the chest to open it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk
}
