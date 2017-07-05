///////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "OracleQuickChest1b.h"

OracleQuickChest1b::OracleQuickChest1b()
{}

OracleQuickChest1b::~OracleQuickChest1b()
{}

extern NPCstructure::NPC OracleChestNPC;

void OracleQuickChest1b::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	self->Do( nothing );
}

void OracleQuickChest1b::OnHit( UNIT_FUNC_PROTOTYPE ){
	self->Do( nothing );
}

void OracleQuickChest1b::Create( void )
{
      npc = ( OracleChestNPC );
      SET_NPC_NAME( "[10840]wooden chest" );  
      npc.InitialPos.X = 2755; 
      npc.InitialPos.Y = 2291;
      npc.InitialPos.world = 2;
}														  

void OracleQuickChest1b::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OracleQuickChest1b::OnTalk( UNIT_FUNC_PROTOTYPE )
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
			PRIVATE_SYSTEM_MESSAGE(INTL( 8699, "Upon opening the chest you discover an enchanted glass key."))
			GiveItem(__OBJ_ENCHANTED_GLASS_KEY)
			GiveFlag(__FLAG_CHAMBER_OF_QUICKNESS_ACTIVATED, 1)
			CastSpellTarget(__SPELL_MOB_ORACLE_QUICK_CHEST_TELEPORT_SPELL_2)
		ELSEIF(CheckFlag(__FLAG_CHAMBER_OF_QUICKNESS_ACTIVATED) == 1)
			PRIVATE_SYSTEM_MESSAGE(INTL( 8700, "The chest is empty."))
		ELSEIF(CheckFlag(__FLAG_CHAMBER_OF_QUICKNESS_ACTIVATED) == 2)
			PRIVATE_SYSTEM_MESSAGE(INTL( 8699, "Upon opening the chest you discover an enchanted glass key."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 8701, "As you take hold of the key, the one in your inventory mysteriously disappears."))
			GiveFlag(__FLAG_CHAMBER_OF_QUICKNESS_ACTIVATED, 1)
			CastSpellTarget(__SPELL_MOB_ORACLE_QUICK_CHEST_TELEPORT_SPELL_2)
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
