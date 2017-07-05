#pragma hdrstop
#include "WindHowlPortal.h"

WindHowlPortal::WindHowlPortal()
{}

WindHowlPortal::~WindHowlPortal()
{}

extern NPCstructure::NPC IslandPortalNPC;


void WindHowlPortal::Create( ){
    npc = IslandPortalNPC;
    SET_NPC_NAME(  "[7400]A flickering portal" );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
    npc.InitialPos.world = 0;
}
void WindHowlPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
{}
}

void WindHowlPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void WindHowlPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
   TELEPORT( 1685, 1171, 0)
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF
BREAK

Default
""
IF (IsInRange(4))
   TELEPORT( 1685, 1171, 0)
ENDIF
BREAK

EndTalk

}