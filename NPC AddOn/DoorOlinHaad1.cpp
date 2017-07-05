#pragma hdrstop
#include "DoorOlinHaad1.h"

DoorOlinHaad1::DoorOlinHaad1()
{}

DoorOlinHaad1::~DoorOlinHaad1()
{}

extern NPCstructure::NPC DoorNPC;

void DoorOlinHaad1::Create( ){
	npc = DoorNPC;
	SET_NPC_NAME( "[345]Wooden Door" );
	npc.InitialPos.X = 2955;
	npc.InitialPos.Y = 1364; 
	npc.InitialPos.world = 0;
}
void DoorOlinHaad1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void DoorOlinHaad1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DoorOlinHaad1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 39)
		IF((target->GetWL().X + (self->GetWL().Y-3072-self->GetWL().X)) > target->GetWL().Y-3072)
			TELEPORT(2953,1366,0) // Goes outside.
		ELSE
			TELEPORT(2957,1362,0) // Goes inside.
		ENDIF
	ELSE
		IF((target->GetWL().X + (self->GetWL().Y-3072-self->GetWL().X)) > target->GetWL().Y-3072)
			TELEPORT(2953,1366,0) // Goes outside.
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 4, "The door is locked."))
		ENDIF
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