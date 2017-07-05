#pragma hdrstop
#include "OraclePortal2.h"

OraclePortal2::OraclePortal2()
{}

OraclePortal2::~OraclePortal2()
{}

extern NPCstructure::NPC PortalNPC;

void OraclePortal2::Create( ){
	npc = PortalNPC;
	SET_NPC_NAME(  "[7396]A shimmering portal" );
	npc.InitialPos.X = 2872;
	npc.InitialPos.Y = 2448;
	npc.InitialPos.world = 2;
}
void OraclePortal2::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void OraclePortal2::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OraclePortal2::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(3))
   TELEPORT( 2854, 2430, 2)
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}