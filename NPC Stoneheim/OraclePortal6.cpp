#pragma hdrstop
#include "OraclePortal6.h"

OraclePortal6::OraclePortal6()
{}

OraclePortal6::~OraclePortal6()
{}

extern NPCstructure::NPC PortalNPC;

void OraclePortal6::Create( ){
	npc = PortalNPC;
	SET_NPC_NAME(  "[7396]A shimmering portal" );
	npc.InitialPos.X = 2744;
	npc.InitialPos.Y = 2236;
	npc.InitialPos.world = 2;
}
void OraclePortal6::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void OraclePortal6::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OraclePortal6::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(3))
   TELEPORT( 2744, 2248, 2)
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}

