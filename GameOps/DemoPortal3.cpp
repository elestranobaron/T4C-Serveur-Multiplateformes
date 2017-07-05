#pragma hdrstop
#include "DemoPortal3.h"

DemoPortal3::DemoPortal3()
{}

DemoPortal3::~DemoPortal3()
{}

extern NPCstructure::NPC IslandPortalNPC;

void DemoPortal3::Create( ){
    npc = IslandPortalNPC;
    SET_NPC_NAME(  "[7395]A shimmering portal beckons for you to enter." );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
//    npc.InitialPos.X = 1805;
//    npc.InitialPos.Y = 1667;
    npc.InitialPos.world = 0;
}
void DemoPortal3::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}




void DemoPortal3::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DemoPortal3::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(CheckFlag(__RATS_KILLED) >= 15)
	IF (IsInRange(4))
		TELEPORT( 2939, 1069, 0)
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