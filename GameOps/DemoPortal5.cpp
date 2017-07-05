#pragma hdrstop
#include "DemoPortal5.h"

DemoPortal5::DemoPortal5()
{}

DemoPortal5::~DemoPortal5()
{}

extern NPCstructure::NPC IslandPortalNPC;

void DemoPortal5::Create( ){
    npc = IslandPortalNPC;
    SET_NPC_NAME(  "[7395]A shimmering portal beckons for you to enter." );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
//    npc.InitialPos.X = 2791;
//    npc.InitialPos.Y = 175;
    npc.InitialPos.world = 0;
}
void DemoPortal5::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}



void DemoPortal5::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DemoPortal5::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(CheckFlag(__GUARDIANS_KILLED) >= 1)
	IF (IsInRange(4))
		TELEPORT( 2600, 3000, 0)
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