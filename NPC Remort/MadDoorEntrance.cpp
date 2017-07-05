#pragma hdrstop
#include "MadDoorEntrance.h"

MadDoorEntrance::MadDoorEntrance()
{}

MadDoorEntrance::~MadDoorEntrance()
{}

extern NPCstructure::NPC DoorNPC;

void MadDoorEntrance::Create( ){
	npc = DoorNPC;
	SET_NPC_NAME(  "[345]Wooden Door" );
	npc.InitialPos.X = 2453;
	npc.InitialPos.Y = 156;
	npc.InitialPos.world = 0;
}
void MadDoorEntrance::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void MadDoorEntrance::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void MadDoorEntrance::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(3)) 
	IF (CheckItem(__OBJ_MAD_HOUSE_KEY) == 0) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 10649, "The door appears to be locked."))	
	ELSE		
		PRIVATE_SYSTEM_MESSAGE(INTL( 10650, "Using the key given to you by Vortimer, you open the door and enter Madrigan's mad house."))
		TELEPORT(2704, 2226, 0) 
	ENDIF 
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 9367, "You cannot reach the door from that far away."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}
