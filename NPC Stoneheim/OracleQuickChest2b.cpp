///////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "OracleQuickChest2b.h"

OracleQuickChest2b::OracleQuickChest2b()
{}

OracleQuickChest2b::~OracleQuickChest2b()
{}

extern NPCstructure::NPC OracleChestNPC;

void OracleQuickChest2b::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	self->Do( nothing );
}

void OracleQuickChest2b::OnHit( UNIT_FUNC_PROTOTYPE ){
	self->Do( nothing );
}

void OracleQuickChest2b::Create( void )
{
      npc = ( OracleChestNPC );
      SET_NPC_NAME( "[10840]wooden chest" );  
      npc.InitialPos.X = 2760; 
      npc.InitialPos.Y = 2264;
      npc.InitialPos.world = 2;
}

void OracleQuickChest2b::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OracleQuickChest2b::OnTalk( UNIT_FUNC_PROTOTYPE )
///////////////////////////////////////////////////////////////////////////

{

InitTalk

Begin
""
IF(IsInRange(4))
	IF(IsBlocked)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8702, "You must step closer to the chest to open it."))
		BREAK
	ELSE
		IF(CheckFlag(__FLAG_CHAMBER_OF_QUICKNESS_ACTIVATED) == 0)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9355, "The chest is locked."))
		ELSEIF(CheckFlag(__FLAG_CHAMBER_OF_QUICKNESS_ACTIVATED) == 1)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9822, "Your enchanted glass key unlocks the chest."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 9823, "Inside you find a pulsating key."))
			TakeItem(__OBJ_ENCHANTED_GLASS_KEY)
			GiveItem(__OBJ_PULSATING_KEY)
			GiveFlag(__FLAG_CHAMBER_OF_QUICKNESS_ACTIVATED, 0)
			CastSpellTarget(__SPELL_MOB_ORACLE_QUICK_CHEST_DISPEL_SPELL_2)
		ELSEIF(CheckFlag(__FLAG_CHAMBER_OF_QUICKNESS_ACTIVATED) == 2)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9824, "Your enchanted glass key fits perfectly inside the lock..."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 9825, "A strange force prevents you from turning it."))
		ENDIF
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
