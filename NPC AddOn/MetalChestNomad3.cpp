#pragma hdrstop
#include "MetalChestNomad3.h"

MetalChestNomad3::MetalChestNomad3()
{}

MetalChestNomad3::~MetalChestNomad3()
{}

extern NPCstructure::NPC MetalChestNPC;

void MetalChestNomad3::Create( ){
	npc = MetalChestNPC;
	SET_NPC_NAME( "[152]Chest" );
	npc.InitialPos.X = 2565;
	npc.InitialPos.Y = 1499;
	npc.InitialPos.world = 0;
}
void MetalChestNomad3::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void MetalChestNomad3::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void MetalChestNomad3::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckItem(__OBJ_SMALL_KEY) >= 1)
		IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 12)
			IF(CheckFlag(__FLAG_ADDON_METALCHEST3_SEARCHED) == 0)
				GiveFlag(__FLAG_ADDON_METALCHEST3_SEARCHED, 1)
				GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 13)
				PRIVATE_SYSTEM_MESSAGE(INTL( 12410, "Your small key unlocks the chest."))
				PRIVATE_SYSTEM_MESSAGE(INTL( 12411, "You open the chest and find a letter inside."))
				PRIVATE_SYSTEM_MESSAGE(INTL( 12412, "You get the letter from the chest."))
				TakeItem(__OBJ_SMALL_KEY) 
				GiveItem(__OBJ_OWAIN_LETTER_TO_NOMAD)
			// The false bottom code is never executed because the storyline progress 
			// is incremented by one in the first search. 
			// ELSEIF(CheckFlag(__FLAG_ADDON_METALCHEST3_SEARCHED) == 1)
			//	GiveFlag(__FLAG_ADDON_METALCHEST3_SEARCHED, 2)
			//	PRIVATE_SYSTEM_MESSAGE("Your small key unlocks the chest.")
			//	PRIVATE_SYSTEM_MESSAGE("You open the chest and discover that it has a false bottom.")
			//	PRIVATE_SYSTEM_MESSAGE("You get 10000 gold from the bottom of the chest.")
			//	GiveGold(10000)
			// ELSE
			//	PRIVATE_SYSTEM_MESSAGE("Your small key unlocks the chest.")
			//	PRIVATE_SYSTEM_MESSAGE("You open the chest but find nothing inside.")
			ENDIF
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 12410, "Your small key unlocks the chest."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 11894, "You open the chest but find nothing inside."))
		ENDIF
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 9355, "The chest is locked."))
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