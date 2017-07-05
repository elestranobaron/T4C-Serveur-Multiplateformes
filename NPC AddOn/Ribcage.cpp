#pragma hdrstop
#include "Ribcage.h"

Ribcage::Ribcage()
{}

Ribcage::~Ribcage()
{}

extern NPCstructure::NPC RibcageNPC;

void Ribcage::Create( ){
	npc = RibcageNPC;
	SET_NPC_NAME( "[12770]A ribcage" );
	npc.InitialPos.X = 852;
	npc.InitialPos.Y = 1737;
	npc.InitialPos.world = 1;
}
void Ribcage::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void Ribcage::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void Ribcage::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 17)
		PRIVATE_SYSTEM_MESSAGE(INTL( 12537, "A dark stone floats in the air where the heart should be."))
	ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 17)
		IF(CheckItem(__OBJ_HEART_OF_GLURIURL) >= 1)
			PRIVATE_SYSTEM_MESSAGE(INTL( 12537, "A dark stone floats in the air where the heart should be."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 12538, "With great care, you take the dark stone and replace it with the Heart of Gluriurl."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 12539, "You receive 125000 experience points."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 12162, "The Gypsy's voice enters your head:"))
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 12540, "%s! You must come see me, I have something important to show you!"), USER_NAME))
			GiveXP(125000)
			TakeItem(__OBJ_HEART_OF_GLURIURL)
			GiveItem(__OBJ_DARKSTONE)
			GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 18)
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 12537, "A dark stone floats in the air where the heart should be."))
		ENDIF
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 12541, "The Heart of Gluriurl floats in the air in the middle of the ribcage."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 12542, "You must step closer to the ribcage to inspect it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}
