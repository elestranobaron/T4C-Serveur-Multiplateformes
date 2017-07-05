//////////////////////////////////////////////////////////////////////
// JagarKar.cpp: implementation of the JagarKar class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "JagarKar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

JagarKar::JagarKar()
{}

JagarKar::~JagarKar()
{}

extern NPCstructure::NPC Nobleman;

void JagarKar::Create( ){
	npc = Nobleman;
	SET_NPC_NAME( "[3042]Jagar Kar" );
	npc.InitialPos.X = 2920;
	npc.InitialPos.Y = 1082;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

void JagarKar::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT SWORDFURY = 1;

InitTalk

Begin
INTL( 11755, "Welcome! Guards pushing you around? Why not \"learn\" some new skills to even up the odds?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1452, "I am Jagar Kar. I help people to \"learn\" new skills. My assistant "
"and I have trained each and every one of the town's guards. I was even "
"a personal guard of \"Theopold\" in my younger days. I have come here "
"to \"teach\" people how to fight the \"goblins\".")

Command(INTL( 523, "ANNABELLE"))
INTL( 1453, "Oh, I don't know if she's dead or alive for sure, but she left us to find "
"her true love years ago... Some say she lives with a troll, now. Me? I "
"just think it's hogwash and she died.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 7176, "Devilish monster? Cursed from beyond? Marked from eternity? Yeah, right!")

Command2(INTL( 1454, "ASSISTANT"),INTL( 1455, "ORTANALAS"))
INTL( 1456, "Oy! He's one of the finest warriors around. A tough fellow, that Ortanalas. "
"He can work for hours without getting bored! Sometimes, I even give him the "
"pleasure and honor of doing my laundry, shining my armor and weapons collection, "
"and he still has a bright smile on his face after that. Never heard a word "
"of complaint out of his mouth. I tell ya, good ones like him are hard to "
"find, nowadays.")

Command(INTL( 539, "GOBLIN"))
INTL( 1457, "If I wasn't so busy training guardsmen, I would be out there crushing "
"as many as I could! One day I'm going to charge right into \"Righul\"'s "
"mountain, and show them my way of thinking.")

Command(INTL( 1458, "RIGHUL"))
INTL( 1459, "Righul's mountain is where the goblins hide.  It's a very dangerous place "
"for a normal fellow.  Swarms of goblins live there. Oy! But it's like a child's "
"playground for me! Goblins are hardly a match for my superior battle skills!")

Command(INTL( 1460, "THEOPOLD"))
INTL( 1461, "Ahh, a great king he was. The greatest, no doubt. He didn't wimp out from "
"a fight like his coward of a son, Theodore. He once went alone against a troll "
"warband and came out victorious. He personally led the assault against the "
"goblins, and he even fought in the front lines. His son must have inherited "
"some goblin blood or something, because he is nothing like his father!")

Command(INTL( 1356, "NIGHTSWORD"))
""
IF (CheckFlag(__QUEST_KALASTOR_MISSION) == 1)
	Conversation
	INTL( 1462, "I indeed have a few Nightswords, but they're not for sale. I'll trade you for "
	"a \"Sword\" \"of\" \"Fury\", if you can find one. Some elite goblin warlords own one, so with "
	"some luck, who knows...")
ELSE
	Conversation
	INTL( 1463, "Beautiful swords, they are. I've got a pretty nifty collection, and I'm rather "
	"attached to it.")
ENDIF

Command(INTL( 1464, "SWORD OF FURY"))
""
IF (CheckFlag(__QUEST_KALASTOR_MISSION) == 1)
	Conversation
	INTL( 1465, "I'd gladly give you a Nightsword in exchange for a Sword of Fury. Do you have one "
	"to trade?")
	SetYesNo(SWORDFURY)
ELSE
	Conversation
	INTL( 1466, "Swords of Fury are often used by warriors who value offense over defense. I'd never "
	"use one myself, but they're rather hard to come by and I wouldn't mind owning a few.")
ENDIF

YES(SWORDFURY)
IF (CheckItem(__OBJ_SWORD_OF_FURY) >= 1)
	Conversation
	INTL( 1467, "Excellent. Let us trade, then... Thank you.")
	TakeItem(__OBJ_SWORD_OF_FURY)
	GiveItem(__OBJ_NIGHTSWORD)
ELSE
	Conversation
	INTL( 1468, "This isn't a honest answer. I will not do business with you.")
	BREAK
ENDIF

NO(SWORDFURY)
Conversation
INTL( 1469, "Ah well. Another time, perhaps.")

YesNoELSE(SWORDFURY)
Conversation
INTL( 1470, "You're not making sense! Don't you realize what an honor it is to speak with me? So "
"what are you saying, yes or no?")
SetYesNo(SWORDFURY)

Command3(INTL( 495, "LEARN"),INTL( 496, "TEACH"),INTL( 894, "SKILL"))
INTL( 7515, "Let's begin the lesson.")
CreateSkillList
	AddTeachSkill( __SKILL_STUN_BLOW, 1, 150 )
	AddTeachSkill( __SKILL_POWERFULL_BLOW, 1, 2500 )
SendTeachSkillList

Command(INTL( 502, "TRAIN"))
INTL( 7516, "I don't seem to have as much time as I used to so I won't be able to train you in the use of your new "
"skills. You can talk to my assistant though, I'm sure he'll be glad to help you.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1485, "I am here to \"teach\" people how to become fierce fighters. I must say, "
"humbly, that I am great at it! Better yet, I am amazing, no uh, incredible! "
"Err no that's not it, oh well... Anyway, you get the picture. There simply "
"is no better teacher around here.")

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1486, "Go make use of those new skills and kill some damned goblins!") BREAK

Default
INTL( 624, "What are you talking about?")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void JagarKar::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Rolph data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL( __SKILL_STUN_BLOW, 1, 150 )
			TEACH_SKILL( __SKILL_POWERFULL_BLOW, 1, 2500 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE
}
