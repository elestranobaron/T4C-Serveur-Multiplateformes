#pragma hdrstop
#include "OraclePortal4.h"

OraclePortal4::OraclePortal4()
{}

OraclePortal4::~OraclePortal4()
{}

extern NPCstructure::NPC PortalNPC;

void OraclePortal4::Create( ){
	npc = PortalNPC;
	SET_NPC_NAME(  "[7396]A shimmering portal" );
	npc.InitialPos.X = 2544;
	npc.InitialPos.Y = 2948;
	npc.InitialPos.world = 2;
}
void OraclePortal4::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void OraclePortal4::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OraclePortal4::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(CheckItem(__OBJ_KEY_OF_OGRIMAR) >= 1)
	IF (IsInRange(3))
	   TELEPORT( 2840, 2312, 2)
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 9373, "You step into the portal but nothing seems to happen."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}