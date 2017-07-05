#pragma hdrstop
#include "MetalChestNomad1.h"

MetalChestNomad1::MetalChestNomad1()
{}

MetalChestNomad1::~MetalChestNomad1()
{}

extern NPCstructure::NPC MetalChestNPC;

void MetalChestNomad1::Create( ){
	npc = MetalChestNPC;
	SET_NPC_NAME( "[152]Chest" );
	npc.InitialPos.X = 2576;
	npc.InitialPos.Y = 1472;
	npc.InitialPos.world = 0;
}
void MetalChestNomad1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void MetalChestNomad1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void MetalChestNomad1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 12)
		IF(CheckFlag(__FLAG_ADDON_TABLE1_SEARCHED) == 0)
			GiveFlag(__FLAG_ADDON_TABLE1_SEARCHED, 1)
			PRIVATE_SYSTEM_MESSAGE(INTL( 12407, "You open the chest and find a small key inside."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 12408, "You get the small key."))
			GiveItem(__OBJ_SMALL_KEY)
		ELSEIF(CheckFlag(__FLAG_ADDON_TABLE1_SEARCHED) == 1)
			GiveFlag(__FLAG_ADDON_TABLE1_SEARCHED, 2)
			PRIVATE_SYSTEM_MESSAGE(INTL( 12409, "You lift up the chest and discover 1000 gold hidden under it."))
	 		GiveGold(1000)
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 11894, "You open the chest but find nothing inside."))
		ENDIF
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 11894, "You open the chest but find nothing inside."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 8702, "You must step closer to the chest to open it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}