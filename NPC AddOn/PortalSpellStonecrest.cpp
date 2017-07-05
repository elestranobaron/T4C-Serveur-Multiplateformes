#pragma hdrstop
#include "PortalSpellStonecrest.h"

PortalSpellStonecrest::PortalSpellStonecrest()
{}

PortalSpellStonecrest::~PortalSpellStonecrest()
{}

extern NPCstructure::NPC SpellPortalNPC;

void PortalSpellStonecrest::Create( ){
    npc = SpellPortalNPC;
    SET_NPC_NAME(  "[12765]Stonecrest Portal" );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
    npc.InitialPos.world = 0;
}
void PortalSpellStonecrest::OnAttacked( UNIT_FUNC_PROTOTYPE ){

	TFormat FORMAT;
	IF(NPC_HP<10000)
		CastSpellSelf(__SPELL_NPC_CANTRIP_FLAK)
		SELF_DESTRUCT
	ENDIF

}

void PortalSpellStonecrest::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void PortalSpellStonecrest::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 

	CastSpellSelf(__SPELL_SELF_DESTRUCT_20_SECONDS);
NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}

void PortalSpellStonecrest::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk

Begin
""
IF(IsInRange(5))
	IF(CheckFlag(__QUEST_ISLAND_ACCESS) >= 2)
		TELEPORT(144, 737, 0)
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 11906, "You step through the portal but nothing happens."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 12014, "You must step closer to the portal to inspect it."))
ENDIF
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk

}