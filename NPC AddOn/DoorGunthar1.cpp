#pragma hdrstop
#include "DoorGunthar1.h"

DoorGunthar1::DoorGunthar1()
{}

DoorGunthar1::~DoorGunthar1()
{}

extern NPCstructure::NPC DoorNPC;

void DoorGunthar1::Create( ){
	npc = DoorNPC;
	SET_NPC_NAME( "[345]Wooden Door" );
	npc.InitialPos.X = 2962;
	npc.InitialPos.Y = 1041;
	npc.InitialPos.world = 0;
}
void DoorGunthar1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void DoorGunthar1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DoorGunthar1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	IF((target->GetWL().X + (self->GetWL().Y-3072-self->GetWL().X)) > target->GetWL().Y-3072)
		TELEPORT(2960,1043,0) // Goes outside.
	ELSEIF((CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 19)||(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 20)||(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 21)||(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 22))	
		PRIVATE_SYSTEM_MESSAGE(INTL( 11996, "The door is locked but there is a note on it. The note reads:"))
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 11997, "%s,"), USER_NAME))
		PRIVATE_SYSTEM_MESSAGE(INTL( 11998, "     I apologize for not being there to meet you, but I had urgent matters to attend to."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 11999, "If you wish to know where to find me, talk to the priests in the temple."))	
	ELSE
		TELEPORT(2964,1039,0) // Goes inside.
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 11995, "You must step closer to the door to open it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}