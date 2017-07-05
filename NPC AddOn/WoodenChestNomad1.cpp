#pragma hdrstop
#include "WoodenChestNomad1.h"

WoodenChestNomad1::WoodenChestNomad1()
{}

WoodenChestNomad1::~WoodenChestNomad1()
{}

extern NPCstructure::NPC WoodenChestNPC;

void WoodenChestNomad1::Create( ){
	npc = WoodenChestNPC;
	SET_NPC_NAME( "[152]Chest" );
	npc.InitialPos.X = 2568;
	npc.InitialPos.Y = 1462;
	npc.InitialPos.world = 0;
}
void WoodenChestNomad1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void WoodenChestNomad1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void WoodenChestNomad1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(IsInRange(4))
	PRIVATE_SYSTEM_MESSAGE(INTL( 11894, "You open the chest but find nothing inside."))
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 8702, "You must step closer to the chest to open it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}