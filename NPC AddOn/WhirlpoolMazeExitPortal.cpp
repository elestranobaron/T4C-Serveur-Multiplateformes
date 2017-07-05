#pragma hdrstop
#include "WhirlpoolMazeExitPortal.h"

WhirlpoolMazeExitPortal::WhirlpoolMazeExitPortal()
{}

WhirlpoolMazeExitPortal::~WhirlpoolMazeExitPortal()
{}

extern NPCstructure::NPC PortalNPC;

void WhirlpoolMazeExitPortal::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 1554;
    npc.InitialPos.Y = 2068;
    npc.InitialPos.world = 1;
}

void WhirlpoolMazeExitPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void WhirlpoolMazeExitPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void WhirlpoolMazeExitPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4)) 
  TELEPORT(1748,2228,1) 
ELSE
  PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF  
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk
}
