#pragma hdrstop
#include "NamelessBard.h"

NamelessBard::NamelessBard()
{}

NamelessBard::~NamelessBard()
{}

extern NPCstructure::NPC NamelessBardNPC;

void NamelessBard::Create( ){
	npc = NamelessBardNPC;
	SET_NPC_NAME( "[12755]Nameless Bard");
	npc.InitialPos.X = 1656;
	npc.InitialPos.Y = 2574;
	npc.InitialPos.world = 1;
}

void NamelessBard::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 29)
	Conversation
	INTL( 12428, "I too was of the chosen...")
	PRIVATE_SYSTEM_MESSAGE(INTL( 12429, "The Nameless Bard mutters something too low for you to hear."))
	BREAK
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 29)
	Conversation
	INTL( 12430, "The world has come to \"punisssh\" its children.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 32)
	Conversation
	INTL( 12431, "In a tree you will find wisdom, in a fountain, knowledge. Where wisdom and knowledge converge, the "
	"answers you seek will emerge.")
ELSEIF((CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 32)||(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33))
	Conversation
	INTL( 12432, "What you have found is the word of power that opens the great gates of tremendous evil. They rest "
	"near the northernmost place in this land. To reach it, you will need to travel through darkness. Rest "
	"assured that if the Waters of Knowledge did not provide all the answers you seek, the one who dwells "
	"past those gates surely shall. This is your \"cursssse\".")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 33)
ELSE
	Conversation
	INTL( 12433, "I too was of the chosen... They came and offered us the forbidden... We refused and still we prayed to them... "
	"We dedicated our little life to their heaven... And they came and offered us the forsaken... Still we refused "
	"and we repented... Death came and cursed us of our lament... He slew all of us and in our amend... We swear that "
	"one day we will be avenged.")
ENDIF

Command(INTL( 12434, "PUNIS"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 29)
	Conversation
	INTL( 12435, "Into the \"abysssss\" I have looked and it said they were the next.")
ELSE
	Conversation
	INTL( 1864, "...")
ENDIF

Command(INTL( 12436, "ABYSS"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 29)
	Conversation
	INTL( 12437, "Look to the land and you will find the \"remnantsssss\" of my people.")
ELSE
	Conversation
	INTL( 1864, "...")
ENDIF

Command(INTL( 12438, "REMNANT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 29)
	Conversation
	INTL( 12439, "In a tree you will find wisdom, in a fountain, knowledge. Where wisdom and knowledge converge, the "
	"answers you seek will emerge.")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 30)
ELSE
	Conversation
	INTL( 1864, "...")
ENDIF

Command(INTL( 12440, "CURS"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 12441, "I too was of the chosen... They came and offered us the forbidden... We refused and still we prayed to them... "
	"We dedicated our little life to their heaven... And they came and offered us the forsaken... Still we refused "
	"and we repented... Death came and cursed us of our lament... He slew all of us and in our amend... We swear that "
	"one day we will be avenged.")
ELSE
	Conversation
	INTL( 1864, "...")
ENDIF

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 1864, "...")
BREAK

Default
INTL( 1864, "...")

EndTalk
}