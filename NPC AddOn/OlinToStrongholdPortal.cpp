#pragma hdrstop
#include "OlinToStrongholdPortal.h"

OlinToStrongholdPortal::OlinToStrongholdPortal()
{}

OlinToStrongholdPortal::~OlinToStrongholdPortal()
{}

extern NPCstructure::NPC PortalNPC;

void OlinToStrongholdPortal::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 1676; 
    npc.InitialPos.Y = 2271;
    npc.InitialPos.world = 1;
}

void OlinToStrongholdPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void OlinToStrongholdPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OlinToStrongholdPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
  TELEPORT(1895,2153,1) 
ELSE
  PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF  
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk
}
