#pragma hdrstop
#include "Efnisien.h"

Efnisien::Efnisien()
{}

Efnisien::~Efnisien()
{}

extern NPCstructure::NPC EfnisienNPC;

void Efnisien::Create( ){
	npc = EfnisienNPC;
	SET_NPC_NAME( "[12734]Efnisien");
	npc.InitialPos.X = 2628;
	npc.InitialPos.Y = 1450;
	npc.InitialPos.world = 0;
}

void Efnisien::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT Visit = 1;

InitTalk

Begin
""
IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_NUMBER_OF_OLIN_HAAD_ASSASSINS_PRESENT) > 0)
	Conversation
	INTL( 12073, "Well? Don't just stand there! Help me out here!")
	BREAK
ELSE
	IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 0)
		Conversation
		INTL( 12074, "Hush... did you hear that?")
		SUMMON("OLINHAADASSASSIN", 2628, 1450)
		SUMMON("OLINHAADASSASSIN", 2628, 1450)
		SUMMON("OLINHAADASSASSIN", 2628, 1450)
		BREAK
	ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 1)
		Conversation
		INTL( 12075, "Those damned \"guards\"! They think they can rough everybody around!")
	ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 2)
		Conversation
		INTL( 12076, "Hello again! Have you talked to \"Olin\" \"Haad\" yet? You can find him inside the "
		"cavern across town.")
	ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 5)
		Conversation
		INTL( 12077, "By the look on your face, I can tell that you went to see Olin Haad and that he refused "
		"to speak to you. I told you before, if you wish to get his attention, you need to beat up "
		"some of his guards. Not the ones around here, mind you. He doesn't care about those. No, "
		"you need to get the guards in the cave or around his hideout.")
	ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 5)
		Conversation
		INTL( 12078, "By Artherk! He really said he wouldn't stop until we were all turned into his undead slaves? "
		"You really should go see the high priest and tell him about all this.")
	ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 6)
		Conversation
		INTL( 12079, "So the high priest told you to head to Windhowl? What are you doing standing around here then?")
	ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 39)
		Conversation
		INTL( 12080, "I really should be more careful with those guards...")
	ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 39)
		Conversation
		INTL( 12081, "Hail, my good friend! Tell me, how may I be of \"service\" to you?")
	ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 40)
		Conversation
		INTL( 12082, "It's about time you get here! You must hurry friend, Olin Haad has found an alternate way inside "
		"the temple. You can use the stairs in the room behind the locked door over there. I will unlock the "
		"door for you.")
		GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 41)
	ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 41)
		Conversation
		INTL( 12083, "You must stop Olin Haad! Hurry, he's already inside the temple. You can use the stairs in that room "
		"over there...")
	ELSE
		IF(CheckItem(__OBJ_DARKSTONE) >= 1)
			Conversation
			INTL( 12084, "It looks like I've no choice but to thank you friend. I heard about your heroic feat down there and "
			"I must admit, I'm rather proud to have met you. Now, I will take this Darkstone and hide it somewhere "
			"safe.")
			TakeItem(__OBJ_DARKSTONE)
			PRIVATE_SYSTEM_MESSAGE(INTL( 12085, "You give the Darkstone to Efnisien."))
		ELSE
			Conversation
			INTL( 12086, "It looks like I've no choice but to thank you friend. I heard about your heroic feat down there and "
			"I must admit, I'm rather proud to have met you.")
		ENDIF
	ENDIF
ENDIF

Command(INTL( 483, "NAME"))
INTL( 12087, "Efnisien, at your service.")

Command(INTL( 12088, "EFNISIEN"))
INTL( 1755, "What?")

Command(INTL( 489, "WORK"))
INTL( 12089, "Oh, this and that. I would tell you more about myself, but I don't really know you.")

Command(INTL( 2505, "GUARD"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 1)
	Conversation
	INTL( 12090, "Look at me now... I'm covered in blood! Damn my jaw hurts too... Oh, but where are my manners? "
	"My name is Efnisien, and these gentlemen were \"assassins\" sent here by \"Olin\" \"Haad\", "
	"'necromancer extraordinaire'.")
ELSE
	Conversation
	INTL( 12091, "I don't have time to talk about that now.")
ENDIF

Command(INTL( 7984, "ASSASSIN"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 1)
	Conversation
	INTL( 12092, "Ahem!, Aye... but nevermind them, it's just an old quarrel... Now, I presume you're here to talk "
	"about \"Olin\" \"Haad\", right? Let's get to it then.")
ELSE
	Conversation
	INTL( 12091, "I don't have time to talk about that now.")
ENDIF

Command2(INTL( 11925, "OLIN"), INTL( 11926, "HAAD"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 1)
	Conversation
	INTL( 12093, "That bastard took the town \"under\" \"siege\", and for what? I heard it was for a worthless "
	"piece of stone!")
ELSE
	Conversation
	INTL( 12091, "I don't have time to talk about that now.")
ENDIF

CmdAND(INTL( 12094, "UNDER"), INTL( 4006, "SIEGE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 1)
	Conversation
	INTL( 12095, "Yeah, and under our bum of a king's nose, too! He took the city with as much ease as a hot "
	"knife cuts through butter. He said he was looking for \"something\", but I'm not sure what.")
ELSE
	Conversation
	INTL( 12091, "I don't have time to talk about that now.")
ENDIF

Command(INTL( 4082, "SOMETHING"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 1)
	Conversation
	INTL( 12096, "From what I hear, it's a stone or something of the sort that the king promised him in exchange "
	"for his \"services\".")
ELSE
	Conversation
	INTL( 12091, "I don't have time to talk about that now.")
ENDIF

Command(INTL( 12097, "SERVICE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 1)
	Conversation
	INTL( 12098, "Our king Theodore XIII hired this guy to clean some rather powerful creatures that were roaming "
	"the land in these parts. Believe it or not, once the deed was done, the king actually \"refused\" "
	"to pay up.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 39)
	Conversation
	INTL( 12099, "Gunthar told you about my duty? I believe it doesn't matter anymore anyway. I can tell you where "
	"the \"entrance\" to Lothar's burial grounds if you wish but...")
ELSE
	Conversation
	INTL( 12091, "I don't have time to talk about that now.")
ENDIF

Command(INTL( 12100, "REFUSED"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 1)
	Conversation
	INTL( 12101, "I don't know why, but seeing as you seem more interested in the matter than I, perhaps you should "
	"take it up with Olin Haad directly. You can find him in a cavern across town. After all, I believe "
	"he is the reason you came to \"visit\" me, is it not?")
	SetYesNo(Visit)
ELSE
	Conversation
	INTL( 12091, "I don't have time to talk about that now.")
ENDIF

YES(Visit)
	Conversation
	INTL( 12102, "I thought so. You see, I received a \"letter\" telling me to expect your arrival.")
NO(Visit)
	Conversation
	INTL( 12103, "It's not? That's strange, I received a \"letter\" telling me to expect your arrival.")
YesNoELSE(Visit)
	Conversation
	INTL( 12104, "Are you sure you didn't come here to speak to me about Olin Haad? I received a \"letter\" "
	"telling me to expect your arrival.")

Command(INTL( 11882, "VISIT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 1)
	Conversation
	INTL( 12105, "The \"letter\" I received mentioned that you would come visit me to talk about Olin Haad.")
ELSE
	Conversation
	INTL( 12091, "I don't have time to talk about that now.")
ENDIF

Command(INTL( 1301, "LETTER"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 1)
	Conversation
	INTL( 12106, "I'm sorry, as much as I would like to chat with you all day, I have other things to do. And since "
	"my jaw hurts like hell, I must attend to it. Oh yes, one last thing... if you want to make yourself "
	"known to Olin Haad, try giving his guards a beating or two. If you need a reason, do it for me, heh "
	"heh. Now, if you'll excuse me...")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 2)
ELSE
	Conversation
	INTL( 12091, "I don't have time to talk about that now.")
ENDIF

Command(INTL( 8946, "ENTRANCE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 39)
	Conversation
	INTL( 12107, "It's too late anyway. Olin Haad has found an alternate way to enter and he's inside the temple right "
	"now. You can enter through the stairs in the room behind the locked door, but it will serve you no "
	"good, as you won't be able to defeat him without a special weapon of some sort.")
ELSE
	Conversation
	INTL( 12091, "I don't have time to talk about that now.")
ENDIF

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 1075, "Farewell.")
BREAK

Default
""
IF(rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 12108, "I wouldn't know anything about that.")
ELSE
	Conversation
	INTL( 5283, "I don't know what you are talking about.")
ENDIF

EndTalk
}