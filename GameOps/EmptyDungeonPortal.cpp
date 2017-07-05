#pragma hdrstop
#include "EmptyDungeonPortal.h"

EmptyDungeonPortal::EmptyDungeonPortal()
{}

EmptyDungeonPortal::~EmptyDungeonPortal()
{}

extern NPCstructure::NPC IslandPortalNPC;

void EmptyDungeonPortal::Create( ){
    npc = IslandPortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
    npc.InitialPos.world = 0;
}
void EmptyDungeonPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void EmptyDungeonPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void EmptyDungeonPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
   TELEPORT( 140, 2900, 1)
ELSE
   PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}
