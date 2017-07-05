#pragma hdrstop
#include "IslandMadnessPortal.h"

IslandMadnessPortal::IslandMadnessPortal()
{}

IslandMadnessPortal::~IslandMadnessPortal()
{}

extern NPCstructure::NPC IslandPortalNPC;

void IslandMadnessPortal::Create( ){
    npc = IslandPortalNPC;
    SET_NPC_NAME(  "[7395]A shimmering portal beckons for you to enter." );
    npc.InitialPos.X = 2750;
    npc.InitialPos.Y = 3000;
    npc.InitialPos.world = 0;
}
void IslandMadnessPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}



void IslandMadnessPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void IslandMadnessPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(CheckGlobalFlag(__GLOBAL_FLAG_ISLAND_MAZE_PRESET) == 1)
	IF (IsInRange(4))
	   TELEPORT( 2825, 2780, 0)
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
	ENDIF
ELSE
	IF (IsInRange(4))
		PRIVATE_SYSTEM_MESSAGE(INTL( 7357, "This portal is currently inactive."))
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
	ENDIF
ENDIF
BREAK

Default
""
BREAK

EndTalk

}