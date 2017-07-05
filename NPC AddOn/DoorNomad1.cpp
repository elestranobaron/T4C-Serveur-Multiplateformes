#pragma hdrstop
#include "DoorNomad1.h"

DoorNomad1::DoorNomad1()
{}

DoorNomad1::~DoorNomad1()
{}

extern NPCstructure::NPC DoorNPC;

void DoorNomad1::Create( ){
	npc = DoorNPC;
	SET_NPC_NAME( "[345]Wooden Door" );
	npc.InitialPos.X = 1672;
	npc.InitialPos.Y = 1330;
	npc.InitialPos.world = 0;
}
void DoorNomad1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void DoorNomad1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DoorNomad1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	IF((target->GetWL().X + (self->GetWL().Y-3072-self->GetWL().X)) < target->GetWL().Y-3072)
		TELEPORT(1674,1328,0)
	ELSEIF(CheckItem(__OBJ_NOMAD_HOUSE_KEY) >= 1)	
		PRIVATE_SYSTEM_MESSAGE(INTL( 12000, "You use Nomad's house key to unlock the door."))
		TakeItem(__OBJ_NOMAD_HOUSE_KEY)
		GiveFlag(__FLAG_ADDON_NOMAD_DOOR_UNLOCKED, 1) 
		TELEPORT(1670, 1332, 0)
	ELSEIF(CheckFlag(__FLAG_ADDON_NOMAD_DOOR_UNLOCKED)==1)
		TELEPORT(1670, 1332, 0)
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 4, "The door is locked."))
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