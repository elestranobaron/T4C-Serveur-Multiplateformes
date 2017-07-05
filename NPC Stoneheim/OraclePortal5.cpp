#pragma hdrstop
#include "OraclePortal5.h"

OraclePortal5::OraclePortal5()
{}

OraclePortal5::~OraclePortal5()
{}

extern NPCstructure::NPC PortalNPC;

void OraclePortal5::Create( ){
	npc = PortalNPC;
	SET_NPC_NAME(  "[7396]A shimmering portal" );
	npc.InitialPos.X = 2768;
	npc.InitialPos.Y = 2212;
	npc.InitialPos.world = 2;
}
void OraclePortal5::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void OraclePortal5::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OraclePortal5::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(3))
   TELEPORT( 2780, 2212, 2)
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}
