#pragma hdrstop
#include "DemoPortal2.h"

DemoPortal2::DemoPortal2()
{}

DemoPortal2::~DemoPortal2()
{}

extern NPCstructure::NPC IslandPortalNPC;

void DemoPortal2::Create( ){
    npc = IslandPortalNPC;
    SET_NPC_NAME( "[7395]A shimmering portal beckons for you to enter." );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
//    npc.InitialPos.X = 2910;
//    npc.InitialPos.Y = 1066;
    npc.InitialPos.world = 0;
}
void DemoPortal2::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}




void DemoPortal2::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DemoPortal2::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(CheckFlag(__NEWBIE_QUEST) == 0)
	IF (IsInRange(4))
		TELEPORT( 2939, 1069, 0)
	   BREAK
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
		BREAK
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7360, "This portal has been drained of its energy."))
	BREAK
ENDIF

Default
""
BREAK

EndTalk

}