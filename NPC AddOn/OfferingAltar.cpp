#pragma hdrstop
#include "OfferingAltar.h"

OfferingAltar::OfferingAltar()
{}

OfferingAltar::~OfferingAltar()
{}

extern NPCstructure::NPC WellNPC;

void OfferingAltar::Create( ){
  npc = WellNPC;
	SET_NPC_NAME( "[12757]An altar" );
  npc.InitialPos.X = 1095;
  npc.InitialPos.Y = 1504;
  npc.InitialPos.world = 1;
}
void OfferingAltar::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void OfferingAltar::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OfferingAltar::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 17)
		IF(CheckItem(__OBJ_FLASK_OF_GLURIURL_BLOOD) >= 1)
			IF(CheckItem(__OBJ_CORRUPT_HEART) >= 1)
				PRIVATE_SYSTEM_MESSAGE(INTL( 12451, "You place the corrupt heart on the altar and desecrate it with the blood of Gluriurl."))
				PRIVATE_SYSTEM_MESSAGE(INTL( 12452, "As you watch, the corrupt heart slowly starts to beat."))
				PRIVATE_SYSTEM_MESSAGE(INTL( 12453, "You take the Heart of Gluriurl from the altar."))
				TakeItem(__OBJ_FLASK_OF_GLURIURL_BLOOD)
				TakeItem(__OBJ_CORRUPT_HEART)
				GiveItem(__OBJ_HEART_OF_GLURIURL)
			ELSE
				PRIVATE_SYSTEM_MESSAGE(INTL( 12454, "The altar has a large heart-shaped recess on it."))
			ENDIF
		ELSE
			IF(CheckItem(__OBJ_CORRUPT_HEART) >= 1)
				PRIVATE_SYSTEM_MESSAGE(INTL( 12455, "You place the corrupt heart on the altar..."))
				PRIVATE_SYSTEM_MESSAGE(INTL( 7354, "Nothing happens."))
				PRIVATE_SYSTEM_MESSAGE(INTL( 12456, "You take back the corrupt heart from the altar."))
			ELSE
				PRIVATE_SYSTEM_MESSAGE(INTL( 12454, "The altar has a large heart-shaped recess on it."))
			ENDIF
		ENDIF
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 12454, "The altar has a large heart-shaped recess on it."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 12457, "You must step closer to the altar to inspect it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}
