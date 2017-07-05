#pragma hdrstop
#include "InvisibleMazeExitPortal.h"

InvisibleMazeExitPortal::InvisibleMazeExitPortal()
{}

InvisibleMazeExitPortal::~InvisibleMazeExitPortal()
{}

extern NPCstructure::NPC PortalNPC;

void InvisibleMazeExitPortal::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 2003;
    npc.InitialPos.Y = 1931;
    npc.InitialPos.world = 1;
}

void InvisibleMazeExitPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void InvisibleMazeExitPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void InvisibleMazeExitPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
  TELEPORT(1944,1996,1) 
ELSE
  PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF  
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk
}
