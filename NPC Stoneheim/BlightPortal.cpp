#pragma hdrstop
#include "BlightPortal.h"

BlightPortal::BlightPortal()
{}

BlightPortal::~BlightPortal()
{}

extern NPCstructure::NPC PortalNPC;

void BlightPortal::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[10828]A portal beckons for you to enter." );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0; 
    npc.InitialPos.world = 0;
}
void BlightPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void BlightPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void BlightPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
      //TELEPORT(x,y) // To user 
      BREAK
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}
