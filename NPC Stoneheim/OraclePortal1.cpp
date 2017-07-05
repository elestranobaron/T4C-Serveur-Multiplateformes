#pragma hdrstop
#include "OraclePortal1.h"

OraclePortal1::OraclePortal1()
{}

OraclePortal1::~OraclePortal1()
{}

extern NPCstructure::NPC PortalNPC;

void OraclePortal1::Create( ){
	npc = PortalNPC;
	SET_NPC_NAME(  "[7396]A shimmering portal" );
	npc.InitialPos.X = 2856;
	npc.InitialPos.Y = 2432;
	npc.InitialPos.world = 2;
}
void OraclePortal1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void OraclePortal1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OraclePortal1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(3))
   TELEPORT( 2874, 2450, 2)
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}