#pragma hdrstop
#include "DeskNomad1.h"

DeskNomad1::DeskNomad1()
{}

DeskNomad1::~DeskNomad1()
{}

extern NPCstructure::NPC DeskNPC;

void DeskNomad1::Create( ){
	npc = DeskNPC;
	SET_NPC_NAME( "[12729]Wooden Desk" );
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}
void DeskNomad1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void DeskNomad1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DeskNomad1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	PRIVATE_SYSTEM_MESSAGE(INTL( 11993, "You search the desk but find nothing."))
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 11994, "You must step closer to the desk to search it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}