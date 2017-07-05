#pragma hdrstop
#include "BedNomad1.h"

BedNomad1::BedNomad1()
{}

BedNomad1::~BedNomad1()
{}

extern NPCstructure::NPC BedNPC;

void BedNomad1::Create( ){
	npc = BedNPC;
	SET_NPC_NAME( "[12724]Bed" );
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}
void BedNomad1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void BedNomad1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void BedNomad1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckFlag(__FLAG_ADDON_BED1_SEARCHED) == 0)
		GiveFlag(__FLAG_ADDON_BED1_SEARCHED, 1)
		PRIVATE_SYSTEM_MESSAGE(INTL( 11890, "You search under the bed and discover a wooden box."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 11891, "You get 1200 gold from the box."))
		GiveGold(1200)
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 11890, "You search under the bed and discover a wooden box."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 11892, "The box is empty."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 11893, "You must step closer to the bed to search it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}