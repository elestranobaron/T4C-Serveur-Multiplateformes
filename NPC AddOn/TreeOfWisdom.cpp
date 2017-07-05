#pragma hdrstop
#include "TreeOfWisdom.h"

TreeOfWisdom::TreeOfWisdom()
{}

TreeOfWisdom::~TreeOfWisdom()
{}

extern NPCstructure::NPC TreeOfWisdomNPC;

void TreeOfWisdom::Create( ){
	npc = TreeOfWisdomNPC;
	SET_NPC_NAME( "[12776]Tree of Wisdom" );
	npc.InitialPos.X = 1791;
	npc.InitialPos.Y = 2617;
	npc.InitialPos.world = 1;
}
void TreeOfWisdom::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void TreeOfWisdom::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void TreeOfWisdom::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 30)
		PRIVATE_SYSTEM_MESSAGE(INTL( 12623, "You notice that a few branches have fallen from the Tree of Wisdom."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 12624, "You pick up a Branch of Wisdom."))
		GiveItem(__OBJ_BRANCH_OF_WISDOM)
		GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 31)
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 12625, "The Tree of Wisdom towers above you."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 12626, "You must step closer to the tree to search it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}