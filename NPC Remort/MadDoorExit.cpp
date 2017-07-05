#pragma hdrstop
#include "MadDoorExit.h"

MadDoorExit::MadDoorExit()
{}

MadDoorExit::~MadDoorExit()
{}

extern NPCstructure::NPC DoorNPC;

void MadDoorExit::Create( ){
	npc = DoorNPC;
	SET_NPC_NAME(  "[345]Wooden Door" );
	npc.InitialPos.X = 2702;
	npc.InitialPos.Y = 2227;
	npc.InitialPos.world = 0;
}
void MadDoorExit::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void MadDoorExit::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void MadDoorExit::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(3))
   PRIVATE_SYSTEM_MESSAGE(INTL( 10651, "You open the door and leave Madrigan's mad house."))
   TELEPORT(2450, 158, 0)
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 9367, "You cannot reach the door from that far away."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}
