#pragma hdrstop
#include "DoorEfnisien2.h"

DoorEfnisien2::DoorEfnisien2()
{}

DoorEfnisien2::~DoorEfnisien2()
{}

extern NPCstructure::NPC DoorNPC;

void DoorEfnisien2::Create( ){
	npc = DoorNPC;
	SET_NPC_NAME( "[345]Wooden Door" );
	npc.InitialPos.X = 2996;
	npc.InitialPos.Y = 1090;
	npc.InitialPos.world = 0;
}
void DoorEfnisien2::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void DoorEfnisien2::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DoorEfnisien2::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	IF((target->GetWL().X + (self->GetWL().Y-3072-self->GetWL().X)) < target->GetWL().Y-3072)
		IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) >= 40)
			TELEPORT(2998,1088,0) // Goes inside.
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 4, "The door is locked.")) 
		ENDIF
	ELSE
		TELEPORT(2994,1092,0) // Goes outside.    
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