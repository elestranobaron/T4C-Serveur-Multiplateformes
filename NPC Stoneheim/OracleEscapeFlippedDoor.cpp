#pragma hdrstop
#include "OracleEscapeFlippedDoor.h"

OracleEscapeFlippedDoor::OracleEscapeFlippedDoor()
{}

OracleEscapeFlippedDoor::~OracleEscapeFlippedDoor()
{}

extern NPCstructure::NPC FlippedDoorNPC;

void OracleEscapeFlippedDoor::Create( ){
	npc = FlippedDoorNPC;
	SET_NPC_NAME(  "[345]Wooden Door" );
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}
void OracleEscapeFlippedDoor::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void OracleEscapeFlippedDoor::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OracleEscapeFlippedDoor::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(3))
	;BYTE bPositionWorld = (target->ViewFlag(__FLAG_DEATH_LOCATION) & 0xFF);
	WORD wPositionY = (target->ViewFlag(__FLAG_DEATH_LOCATION) & 0xFFF00) >> 8;
	WORD wPositionX = (target->ViewFlag(__FLAG_DEATH_LOCATION) & 0xFFF00000) >> 20;
	IF(target->ViewFlag(__FLAG_DEATH_LOCATION) != 0)
		TELEPORT( wPositionX, wPositionY, bPositionWorld)
	ELSE
		TELEPORT(2941, 1062, 0)
	ENDIF
	PRIVATE_SYSTEM_MESSAGE(INTL( 9366, "As your hand touches the door handle, you are magically transported to a safe place."))
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 9367, "You cannot reach the door from that far away."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}