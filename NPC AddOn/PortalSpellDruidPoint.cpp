#pragma hdrstop
#include "PortalSpellDruidPoint.h"

PortalSpellDruidPoint::PortalSpellDruidPoint()
{}

PortalSpellDruidPoint::~PortalSpellDruidPoint()
{}

extern NPCstructure::NPC SpellPortalNPC;

void PortalSpellDruidPoint::Create( ){
    npc = SpellPortalNPC;
    SET_NPC_NAME(  "[12762]Druid's Point Portal" );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
    npc.InitialPos.world = 0;
}
void PortalSpellDruidPoint::OnAttacked( UNIT_FUNC_PROTOTYPE ){

	TFormat FORMAT;
	IF(NPC_HP<10000)
		CastSpellSelf(__SPELL_NPC_CANTRIP_FLAK)
		SELF_DESTRUCT
	ENDIF

}

void PortalSpellDruidPoint::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void PortalSpellDruidPoint::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 

	CastSpellSelf(__SPELL_SELF_DESTRUCT_20_SECONDS);
NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}

void PortalSpellDruidPoint::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk

Begin
""
IF(IsInRange(5))
	TELEPORT(2790, 175, 0)
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 12014, "You must step closer to the portal to inspect it."))
ENDIF
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk

}