#pragma hdrstop
#include "BookshelfNomad1.h"

BookshelfNomad1::BookshelfNomad1()
{}

BookshelfNomad1::~BookshelfNomad1()
{}

extern NPCstructure::NPC BookshelfNPC;

void BookshelfNomad1::Create( ){
	npc = BookshelfNPC;
	SET_NPC_NAME( "12725 Bookshelf" );
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}
void BookshelfNomad1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void BookshelfNomad1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void BookshelfNomad1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(IsInRange(4))
	PRIVATE_SYSTEM_MESSAGE(INTL( 11896, "You search the bookshelf but find nothing."))
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 11897, "You must step closer to the bookshelf to search it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}