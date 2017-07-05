///////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "OracleTrappedChest5b.h"

OracleTrappedChest5b::OracleTrappedChest5b()
{}

OracleTrappedChest5b::~OracleTrappedChest5b()
{}

extern NPCstructure::NPC OracleChestNPC;

void OracleTrappedChest5b::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void OracleTrappedChest5b::Create( void )
{
      npc = ( OracleChestNPC );
      SET_NPC_NAME( "[10840]wooden chest" );  
      npc.InitialPos.X = 2808;
      npc.InitialPos.Y = 2316;
      npc.InitialPos.world = 2;
}

void OracleTrappedChest5b::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OracleTrappedChest5b::OnTalk( UNIT_FUNC_PROTOTYPE )
///////////////////////////////////////////////////////////////////////////

{

InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckItem(__OBJ_SCORCHED_METAL_KEY) >= 1)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8700, "The chest is empty."))
	ELSEIF(CheckGlobalFlag(__GLOBAL_FLAG_TRAPPED_CHEST_B) == 0)
		GiveGlobalFlag(__GLOBAL_FLAG_TRAPPED_CHEST_B, rnd.roll(dice(1, 7)))
		IF(CheckGlobalFlag(__GLOBAL_FLAG_TRAPPED_CHEST_B) == 5)
			GiveItem(__OBJ_SCORCHED_METAL_KEY)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9375, "You find a scorched metal key inside the chest."))
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 9353, "The chest is trapped!"))
			PRIVATE_SYSTEM_MESSAGE(INTL( 9354, "Unfortunately, it is also empty."))
			CastSpellTarget(__SPELL_MOB_ORACLE_TRAPPED_CHEST_FIREBALL_SPELL)
		ENDIF
	ELSEIF(CheckGlobalFlag(__GLOBAL_FLAG_TRAPPED_CHEST_B) == 5)
		GiveItem(__OBJ_SCORCHED_METAL_KEY)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9375, "You find a scorched metal key inside the chest."))
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 9353, "The chest is trapped!"))
		PRIVATE_SYSTEM_MESSAGE(INTL( 9354, "Unfortunately, it is also empty."))
		CastSpellTarget(__SPELL_MOB_ORACLE_TRAPPED_CHEST_FIREBALL_SPELL)
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
