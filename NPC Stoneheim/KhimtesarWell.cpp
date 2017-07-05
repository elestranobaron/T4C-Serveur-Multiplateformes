#pragma hdrstop
#include "KhimtesarWell.h"

KhimtesarWell::KhimtesarWell()
{}

KhimtesarWell::~KhimtesarWell()
{}

extern NPCstructure::NPC KhimtesarWellNPC;

void KhimtesarWell::OnAttacked( UNIT_FUNC_PROTOTYPE ){
     {}

}

void KhimtesarWell::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}
void KhimtesarWell::Create( void )
{
	npc = KhimtesarWellNPC;
	SET_NPC_NAME( "[10869]An ordinary well" );
	npc.InitialPos.X = 1099;
	npc.InitialPos.Y = 277;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = FALSE;
}

void KhimtesarWell::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF(CheckFlag(__FLAG_USER_HAS_CHECKED_THE_WELL) == 0)
	PRIVATE_SYSTEM_MESSAGE(INTL( 10215, "There doesn't seem to be anything special about this particular well."))
	GiveFlag(__FLAG_USER_HAS_CHECKED_THE_WELL, 1)
ELSEIF(CheckFlag(__FLAG_USER_HAS_CHECKED_THE_WELL) == 1)
	PRIVATE_SYSTEM_MESSAGE(INTL( 10216, "Upon further inspection, you discover some muddled text on the back of the well."))
	GiveFlag(__FLAG_USER_HAS_CHECKED_THE_WELL, 2)
ELSEIF(CheckFlag(__FLAG_USER_HAS_CHECKED_THE_WELL) == 2) 
	PRIVATE_SYSTEM_MESSAGE(INTL( 10533, "You attempt to decipher the text and fail miserably."))
	GiveFlag(__FLAG_USER_HAS_CHECKED_THE_WELL, 3)
ELSEIF(CheckFlag(__FLAG_USER_HAS_CHECKED_THE_WELL) == 3)
	PRIVATE_SYSTEM_MESSAGE(INTL( 10217, "You attempt to decipher the text and fail miserably."))
	GiveFlag(__FLAG_USER_HAS_CHECKED_THE_WELL, 4)
ELSEIF(CheckFlag(__FLAG_USER_HAS_CHECKED_THE_WELL) == 4)
	PRIVATE_SYSTEM_MESSAGE(INTL( 10218, "After understanding that the text was engraved by a much larger and clumsy hand, you are able to read the following:"))
	PRIVATE_SYSTEM_MESSAGE(INTL( 10769, "GIANT CAVE AT ROCK - 7 STEPS WEST - 20 STEPS NORTH"))
	GiveFlag(__FLAG_USER_HAS_CHECKED_THE_WELL, 5)
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 10220, "The text engraved on the back of the well reads the following:"))
	PRIVATE_SYSTEM_MESSAGE(INTL( 10219, "GIANT CAVE AT ROCK - 7 STEPS WEST - 20 STEPS NORTH"))
ENDIF
BREAK

Default
""
PRIVATE_SYSTEM_MESSAGE(INTL( 10215, "There doesn't seem to be anything special about this particular well."))
BREAK

EndTalk
}