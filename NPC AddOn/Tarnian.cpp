#pragma hdrstop
#include "Tarnian.h"

Tarnian::Tarnian()
{}

Tarnian::~Tarnian()
{}

extern NPCstructure::NPC TarnianNPC;

void Tarnian::Create( ){
	npc = TarnianNPC;
	SET_NPC_NAME( "[12775]Tarnian");
	npc.InitialPos.X = 2780;
	npc.InitialPos.Y = 1205;
	npc.InitialPos.world = 0;
}

void Tarnian::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT GuntharSent = 1;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 25)
	Conversation
	INTL( 12594, "Well met, friend.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 25)
	Conversation
	INTL( 12595, "Well met, friend! Are you the one that Gunthar sent to me?")
	SetYesNo(GuntharSent)
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 26)
	Conversation
	INTL( 12596, "Have you found Antonian yet? Just take the road to Windhowl. After the road goes north for awhile, it "
	"will turn west again and you will come to an intersection going northeast and south. From that point, "
	"just keep going northwest and pass between some mountains to find his cottage.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 42)
	Conversation
	INTL( 12597, "I know you will fight this thing through to the end. I can only pray that you will prove stronger than "
	"your foes in the end.")
ELSE
	Conversation
	INTL( 12598, "Gunthar told me what you did for us, for my son. Even though we must continue our battle against his "
	"men, you have given us renewed hope. Without their leader they will fall more easily. Thank you.")
ENDIF

YES(GuntharSent)
	Conversation
	INTL( 12599, "I'm pleased to make your acquaintance then. I see that you have found the \"Darkstone\".")
NO(GuntharSent)
	Conversation
	INTL( 12600, "I must be mistaken then. Good day to you.")
	BREAK
YesNoELSE(GuntharSent)
	Conversation
	INTL( 12601, "Are you the one that Gunthar sent to me or not?")
	SetYesNo(GuntharSent)

Command(INTL( 12493, "DARKSTONE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 25)
	Conversation
	INTL( 12602, "Gunthar told me he sold the stone to some merchant by mistake. That was before he knew of the "
	"stone's \"worth\".")
ELSE
	Conversation
	INTL( 12603, "Perhaps we can talk about this when I am not so busy...")
ENDIF

Command(INTL( 1024, "WORTH"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 25)
	Conversation
	INTL( 12604, "I'm not talking about it's worth in gold. The stone is a representation of the heart of \"Gluriurl\". "
	"It is the key to entering another temple, where you will find the \"skull\" of the dead god.")
ELSE
	Conversation
	INTL( 12603, "Perhaps we can talk about this when I am not so busy...")
ENDIF

Command(INTL( 12397, "GLURIURL"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 25)
	Conversation
	INTL( 12605, "All I know on the subject is what Gunthar told me, which I am sure is what he told you.")
ELSE
	Conversation
	INTL( 12603, "Perhaps we can talk about this when I am not so busy...")
ENDIF

Command(INTL( 8129, "SKULL"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 25)
	Conversation
	INTL( 12606, "We need the skull in order to discover the one who's hiding behind the curtain of blood. I'm not interested "
	"in legends and the rising of an ancient god, but rather in the \"one\" responsible for the recent killings.")
ELSE
	Conversation
	INTL( 12603, "Perhaps we can talk about this when I am not so busy...")
ENDIF

Command(INTL( 11871, "ONE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 25)
	Conversation
	INTL( 12607, "The one I'm after killed my only \"son\"... Gunthar believes that the one responsible for the \"murders\" is connected "
	"to Olin Haad.")
ELSE
	Conversation
	INTL( 12603, "Perhaps we can talk about this when I am not so busy...")
ENDIF

Command(INTL( 12608, "SON"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 25)
	Conversation
	INTL( 12609, "The bastard took my son and sacrificed him in a ritual! I swear, when I find him, he will pay with his life! I will "
	"scatter his entrails to the four corners of the world!")
ELSE
	Conversation
	INTL( 12603, "Perhaps we can talk about this when I am not so busy...")
ENDIF

Command(INTL( 12610, "MURDER"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 25)
	Conversation
	INTL( 12611, "People have started disappearing recently only to be found days later, dismembered and lying in a pentagram of some "
	"sort. Gunthar believes that the one responsible for these gruesome murders is the same insane \"fanatic\" that wants "
	"to revive Gluriurl.")
ELSE
	Conversation
	INTL( 12603, "Perhaps we can talk about this when I am not so busy...")
ENDIF

Command(INTL( 12612, "FANATIC"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 25)
	Conversation
	INTL( 12613, "That's why we need your help. I must remain here to defend the town so you must get the skull yourself. If Gunthar "
	"\"believes\" in you, then I will do the same.")
ELSE
	Conversation
	INTL( 12603, "Perhaps we can talk about this when I am not so busy...")
ENDIF

Command(INTL( 12614, "BELIEV"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 25)
	Conversation
	INTL( 12615, "Here, take this. To reach the Nameless Bard, you will need to travel to Raven's Dust. This stone tablet is "
	"the key to reaching \"Raven's\" \"Dust\" without Olin Haad knowing about it.")
	PRIVATE_SYSTEM_MESSAGE(INTL( 12616, "Tarnian gives you a Runed Stone Tablet."))
	GiveItem(__OBJ_RUNED_STONE_TABLET)
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 26)
ELSE
	Conversation
	INTL( 12603, "Perhaps we can talk about this when I am not so busy...")
ENDIF

CmdAND(INTL( 1284, "RAVEN"), INTL( 9158, "DUST"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 26)
	Conversation
	INTL( 12617, "Antonian the hermit can teach you how to use it. To get to his house, take the northwest bridge out "
	"of town and get on the road to Windhowl. At the first intersection, go southwest. Shortly after, you "
	"will cross a bridge. After the bridge, the road will turn north. Once you get to the intersection where "
	"it branches off northeast and south, just keep going northwest and pass between some mountains to find "
	"his cottage.")
ELSE
	Conversation
	INTL( 12603, "Perhaps we can talk about this when I am not so busy...")
ENDIF

Command(INTL( 483, "NAME"))
INTL( 12618, "Tarnian Wolfmane, at your service.")

Command(INTL( 489, "WORK"))
INTL( 12619, "Olin Haad thinks he can just take this town by force. I'm here to see that doesn't happen.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 12620, "Farewell and good luck.")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 12621, "Do you hear that my friend? The battle calls...")
ELSE
	Conversation
	INTL( 12622, "Perhaps another time, friend.")
ENDIF

EndTalk
}