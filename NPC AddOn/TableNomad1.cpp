#pragma hdrstop
#include "TableNomad1.h"

TableNomad1::TableNomad1()
{}

TableNomad1::~TableNomad1()
{}

extern NPCstructure::NPC TableNPC;

void TableNomad1::Create( ){
	npc = TableNPC;
	SET_NPC_NAME( "[12774]Table" );
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}
void TableNomad1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void TableNomad1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void TableNomad1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 12)
		IF(CheckFlag(__FLAG_ADDON_TABLE1_SEARCHED) == 0)
			GiveFlag(__FLAG_ADDON_TABLE1_SEARCHED, 1)
			PRIVATE_SYSTEM_MESSAGE(INTL( 12591, "You search the table and discover a small key attached under it."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 12408, "You get the small key."))
			GiveItem(__OBJ_SMALL_KEY)
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 12592, "You search the table but find nothing."))
		ENDIF
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 12592, "You search the table but find nothing."))
	ENDIF
ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 12593, "You must step closer to the table to search it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}