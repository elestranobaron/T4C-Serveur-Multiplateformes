#pragma hdrstop
#include "RibCageExitPortal.h"

RibCageExitPortal::RibCageExitPortal()
{}

RibCageExitPortal::~RibCageExitPortal()
{}

extern NPCstructure::NPC PortalNPC;

void RibCageExitPortal::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 836;
    npc.InitialPos.Y = 1721;
    npc.InitialPos.world = 1;
}

void RibCageExitPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void RibCageExitPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void RibCageExitPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
  TELEPORT(1095,1500,1)      
ELSE
  PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF  
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk
}
