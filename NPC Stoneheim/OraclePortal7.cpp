#pragma hdrstop
#include "OraclePortal7.h"

OraclePortal7::OraclePortal7()
{}

OraclePortal7::~OraclePortal7()
{}

extern NPCstructure::NPC PortalNPC;

void OraclePortal7::Create( ){
	npc = PortalNPC;
	SET_NPC_NAME(  "[7396]A shimmering portal" );
	npc.InitialPos.X = 2692;
	npc.InitialPos.Y = 2392;
	npc.InitialPos.world = 2;
}
void OraclePortal7::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void OraclePortal7::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OraclePortal7::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) >= 1)
	IF (IsInRange(3))
	   TELEPORT( 2632, 2452, 2)
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
	ENDIF
ELSEIF(CheckFlag(__QUEST_FIXED_ALIGNMENT) <= -1)
	IF (IsInRange(3))
	   TELEPORT( 2664, 2420, 2)
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
	ENDIF
ENDIF
BREAK

Default
""
BREAK

EndTalk

}