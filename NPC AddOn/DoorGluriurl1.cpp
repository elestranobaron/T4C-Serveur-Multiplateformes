#pragma hdrstop
#include "DoorGluriurl1.h"

DoorGluriurl1::DoorGluriurl1()
{}

DoorGluriurl1::~DoorGluriurl1()
{}

extern NPCstructure::NPC DoorNPC;

void DoorGluriurl1::Create( ){
	npc = DoorNPC;
	SET_NPC_NAME( "[345]Wooden Door" );
	npc.InitialPos.X = 2527;
	npc.InitialPos.Y = 1656;
	npc.InitialPos.world = 0;
}
void DoorGluriurl1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void DoorGluriurl1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DoorGluriurl1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	IF((target->GetWL().X + (self->GetWL().Y-3072-self->GetWL().X)) < target->GetWL().Y-3072)
		TELEPORT(2529, 1654, 0)
	ELSE
		TELEPORT(2525, 1658, 0)
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