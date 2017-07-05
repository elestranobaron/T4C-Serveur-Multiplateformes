#pragma hdrstop
#include "DefilementPortal1.h"

DefilementPortal1::DefilementPortal1()
{}

DefilementPortal1::~DefilementPortal1()
{}

extern NPCstructure::NPC PortalNPC;

void DefilementPortal1::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 956;
    npc.InitialPos.Y = 1655;
    npc.InitialPos.world = 1;
}

void DefilementPortal1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void DefilementPortal1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DefilementPortal1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
  TELEPORT(1108,1511,1) 
ELSE
  PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF  
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk
}
