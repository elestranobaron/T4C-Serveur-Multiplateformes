#pragma hdrstop
#include "BookshelfNomad3.h"

BookshelfNomad3::BookshelfNomad3()
{}

BookshelfNomad3::~BookshelfNomad3()
{}

extern NPCstructure::NPC BookshelfNPC;

void BookshelfNomad3::Create( ){
	npc = BookshelfNPC;
	SET_NPC_NAME( "[12725]Bookshelf" );
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}
void BookshelfNomad3::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void BookshelfNomad3::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void BookshelfNomad3::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckFlag(__FLAG_ADDON_BOOKSHELF3_SEARCHED) == 0)
		GiveFlag(__FLAG_ADDON_BOOKSHELF3_SEARCHED, 1)
		PRIVATE_SYSTEM_MESSAGE(INTL( 11898, "You search the bookshelf and find some jewelry inside a hollow book."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 11899, "You get an exquisitely crafted gold ring from the book."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 11900, "You get a sparkling ruby from the book."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 11901, "You get a gem-encrusted silver pendant from the book."))
		GiveItem(__OBJ_EXQUISITELY_CRAFTED_GOLD_RING)
		GiveItem(__OBJ_SPARKLING_RUBY)
		GiveItem(__OBJ_GEM_ENCRUSTED_SILVER_PENDANT)
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 11898, "You search the bookshelf and find some jewelry inside a hollow book."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 11902, "The book is empty."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 11897, "You must step closer to the bookshelf to search it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}