#pragma hdrstop
#include "ChaosEastExitPortal.h"

ChaosEastExitPortal::ChaosEastExitPortal()
{}

ChaosEastExitPortal::~ChaosEastExitPortal()
{}

extern NPCstructure::NPC PortalNPC;

void ChaosEastExitPortal::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 1625;
    npc.InitialPos.Y = 1661;
    npc.InitialPos.world = 1; 
} 

void ChaosEastExitPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void ChaosEastExitPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void ChaosEastExitPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
  TELEPORT(1660,1699,1) 
ELSE
  PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF  
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk
}
