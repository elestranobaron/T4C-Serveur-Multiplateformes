#pragma hdrstop
#include "MetalChestNomad2.h"

MetalChestNomad2::MetalChestNomad2()
{}

MetalChestNomad2::~MetalChestNomad2()
{}

extern NPCstructure::NPC MetalChestNPC;

void MetalChestNomad2::Create( ){
	npc = MetalChestNPC;
	SET_NPC_NAME( "[152]Chest" );
	npc.InitialPos.X = 2582;
	npc.InitialPos.Y = 1456;
	npc.InitialPos.world = 0;
}
void MetalChestNomad2::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void MetalChestNomad2::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void MetalChestNomad2::OnTalk( UNIT_FUNC_PROTOTYPE )
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