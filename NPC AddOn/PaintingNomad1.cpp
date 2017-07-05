#pragma hdrstop
#include "PaintingNomad1.h"

PaintingNomad1::PaintingNomad1()
{}

PaintingNomad1::~PaintingNomad1()
{}

extern NPCstructure::NPC PaintingNPC;

void PaintingNomad1::Create( ){
	npc = PaintingNPC;
	SET_NPC_NAME( "[12761]Painting" );
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}
void PaintingNomad1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void PaintingNomad1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void PaintingNomad1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckFlag(__FLAG_ADDON_CACHE_SEARCHED) == 0)
		PRIVATE_SYSTEM_MESSAGE(INTL( 12525, "You search behind the painting and discover a small hidden cache."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 12526, "You get 1500 gold from the cache."))
		GiveGold(1500)
		GiveFlag(__FLAG_ADDON_CACHE_SEARCHED, 1)
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 12525, "You search behind the painting and discover a small hidden cache."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 12527, "The cache is empty."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 12528, "You must step closer to the painting to search it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}