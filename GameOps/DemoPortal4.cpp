#pragma hdrstop
#include "DemoPortal4.h"

DemoPortal4::DemoPortal4()
{}

DemoPortal4::~DemoPortal4()
{}

extern NPCstructure::NPC IslandPortalNPC;

void DemoPortal4::Create( ){
    npc = IslandPortalNPC;
    SET_NPC_NAME(  "[7395]A shimmering portal beckons for you to enter." );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
//    npc.InitialPos.X = 93;
//    npc.InitialPos.Y = 637;
    npc.InitialPos.world = 1;
}
void DemoPortal4::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

						
void DemoPortal4::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DemoPortal4::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(CheckFlag(__FLAG_KILLED_TOMB_RAIDER) >= 1)
	IF (IsInRange(4))
		TELEPORT( 2850, 1102, 0)
	   BREAK
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
		BREAK
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7361, "This portal is not yet activated."))
	BREAK
ENDIF

Default
""
BREAK

EndTalk

}