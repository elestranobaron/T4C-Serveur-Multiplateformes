#pragma hdrstop
#include "MakrshPortal5.h"

MakrshPortal5::MakrshPortal5()
{}

MakrshPortal5::~MakrshPortal5()
{}

extern NPCstructure::NPC PortalNPC;

void MakrshPortal5::Create( ){
	npc = PortalNPC;
	SET_NPC_NAME(  "[7396]A shimmering portal" );
	npc.InitialPos.X = 2265;
	npc.InitialPos.Y = 495;
	npc.InitialPos.world = 1;
}
void MakrshPortal5::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void MakrshPortal5::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void MakrshPortal5::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	IF(CheckGlobalFlag(__GLOBAL_FLAG_MAKRSH_PTANGH_IS_FIGHTING) == 1)
		TELEPORT(2724, 2192, 2)
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 9373, "You step into the portal but nothing seems to happen."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}