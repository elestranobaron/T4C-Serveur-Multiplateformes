#pragma hdrstop
#include "FountainOfKnowledge.h"

FountainOfKnowledge::FountainOfKnowledge()
{}

FountainOfKnowledge::~FountainOfKnowledge()
{}

extern NPCstructure::NPC FountainOfKnowledgeNPC;

void FountainOfKnowledge::Create( ){
	npc = FountainOfKnowledgeNPC;
	SET_NPC_NAME( "[12738]Fountain of Knowledge" );
	npc.InitialPos.X = 1553;
	npc.InitialPos.Y = 2478;
	npc.InitialPos.world = 1;
}
void FountainOfKnowledge::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void FountainOfKnowledge::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void FountainOfKnowledge::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 31)
		PRIVATE_SYSTEM_MESSAGE(INTL( 12155, "The Fountain of Knowledge lies before you."))
	ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 31)
		PRIVATE_SYSTEM_MESSAGE(INTL( 12156, "You use the Branch of Knowledge to stir the Waters of Knowledge..."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 12157, "The waters swirl before your very eyes to form a single word: ETHEREAL"))
		PRIVATE_SYSTEM_MESSAGE(INTL( 12158, "You receive 300000 experience points."))
		GiveXP(300000)
		TakeItem(__OBJ_BRANCH_OF_WISDOM)
		GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 32)
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 12159, "The waters are somewhat clearer but you can still see something in the ripples: ETHEREAL"))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 12160, "You must step closer to the fountain to inspect it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}