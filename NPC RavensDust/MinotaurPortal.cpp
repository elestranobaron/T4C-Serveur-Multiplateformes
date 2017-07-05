#pragma hdrstop
#include "MinotaurPortal.h"

MinotaurPortal::MinotaurPortal()
{}

MinotaurPortal::~MinotaurPortal()
{}

extern NPCstructure::NPC MinotaurPortalNPC;

void MinotaurPortal::Create( ){
    npc = MinotaurPortalNPC;
    SET_NPC_NAME( "[7500]A shimmering portal" );
    npc.InitialPos.X = 510;
    npc.InitialPos.Y = 807;
    npc.InitialPos.world = 1;
}
void MinotaurPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	{} 
}

void MinotaurPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void MinotaurPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
   TELEPORT( 873, 2078, 0)   
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7501, "You must step closer to the portal to activate it.") )
ENDIF
BREAK

Default
INTL( 3642, "{This} {is} {a} {bug.}")

EndTalk

}



