#pragma hdrstop
#include "Brother12.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Brother12::Brother12()
{}

Brother12::~Brother12()
{}

extern NPCstructure::NPC DeadBrotherNPC;

void Brother12::Create(){
        npc = DeadBrotherNPC;
        SET_NPC_NAME( "[2924]A loathsome horror" );
        npc.InitialPos.X = 680;  // Dungeon of Specters
        npc.InitialPos.Y = 2390; // Dungeon of Specters
        npc.InitialPos.world = 1;
}

void Brother12::OnTalk( UNIT_FUNC_PROTOTYPE )

/*
__QUEST_DEAD_BROTHERS
	0: Has not begun talking to the dead brothers...
	1-12: Has successfully talked to Brother #X.
*/

{

CONSTANT GOTO_DUNGEON = 1;

InitTalk

Begin
INTL( 4293, "At last, someone to talk to.")

Command(INTL( 4273, "LOWER DUNGEON"))
""
IF ((CheckFlag(__QUEST_DEAD_BROTHERS) == 11) OR (CheckFlag(__QUEST_DEAD_BROTHERS) == 12))
	Conversation
	INTL( 4294, "Only worthy adventurers may solve this puzzle. When you have the six Royal "
	"Keys, come and tell me \"I\" \"have\" \"the\" \"six\" \"keys\".")
	GiveFlag(__QUEST_DEAD_BROTHERS,12)
ELSE
	Conversation
	INTL( 4282, "I cannot answer that. Speak to us in the right order.")
	GiveFlag(__QUEST_DEAD_BROTHERS,0)
ENDIF

Command(INTL( 4295, "I HAVE THE SIX KEY"))
""					 	
IF ((CheckItem(__OBJ_ROYAL_KEY_1) >= 1) && (CheckItem(__OBJ_ROYAL_KEY_2) >= 1) && (CheckItem(__OBJ_ROYAL_KEY_3) >= 1) && (CheckItem(__OBJ_ROYAL_KEY_4) >= 1) && (CheckItem(__OBJ_ROYAL_KEY_5) >= 1) && (CheckItem(__OBJ_ROYAL_KEY_6) >= 1) && (CheckFlag(__QUEST_DEAD_BROTHERS) >= 12))	
	Conversation
	INTL( 4296, "Well, then, since you've got all six keys, I can send you to the Cave of Fear, "
	"which lies deep within the earth, and you can look for the cuthana herb there. "
	"Are you ready?")
	SetYesNo(GOTO_DUNGEON)
ELSE // PC doesn't have all keys and/or hasn't talked to all the brothers
	IF (CheckFlag(__QUEST_DEAD_BROTHERS) < 12) // Hasn't talked to 12 brothers:
		Conversation
		INTL( 4297, "I ask that you speak with all my brothers first, *then* I will tell you what "
		"you need to know.")
	ELSE // Hasn't retrieved all the keys:
		Conversation
		INTL( 4298, "You can't go to the Cave of Fear unless you've retrieved all six Royal Keys.")
	ENDIF
ENDIF

YES(GOTO_DUNGEON)
IF ((CheckItem(__OBJ_ROYAL_KEY_1) >= 1) && (CheckItem(__OBJ_ROYAL_KEY_2) >= 1) && (CheckItem(__OBJ_ROYAL_KEY_3) >= 1) && (CheckItem(__OBJ_ROYAL_KEY_4) >= 1) && (CheckItem(__OBJ_ROYAL_KEY_5) >= 1) && (CheckItem(__OBJ_ROYAL_KEY_6) >= 1))
	Conversation
	INTL( 4299, "Here we go... Good luck, and keep your wits with you.")
	TELEPORT(595,300,2)
	BREAK 
ELSE
	Conversation
	INTL( 4300, "You do not seem to have all the keys with you anymore. I cannot send you there "
	"without the keys. Perhaps someone stole some from you? Come again when you have "
	"all your keys.")
ENDIF

NO(GOTO_DUNGEON)
Conversation
INTL( 4301, "Come back... Come back...")

YesNoELSE(GOTO_DUNGEON)
Conversation
INTL( 4302, "Do not attempt to confuse me, yes or no?")
SetYesNo(GOTO_DUNGEON)

Command5(INTL( 4266, "TORMENT"),INTL( 4268, "TOURNAMENT OF PRINCE"),INTL( 4283, "KINGDOM OF GOLDMOON"),INTL( 754, "THEODORE"),INTL( 1609, "DEATH"))
INTL( 4270, "You are asking the wrong corpse. You must start all over again.")
GiveFlag(__QUEST_DEAD_BROTHERS,0)

Command5(INTL( 11417, "POISONED"),INTL( 543, "CURSE"),INTL( 4271, "CUTHANA"),INTL( 569, "HEAL"),INTL( 4272, "ROYAL DOOR"))
INTL( 4270, "You are asking the wrong corpse. You must start all over again.")
GiveFlag(__QUEST_DEAD_BROTHERS,0)

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 4303, "I was named Gran Theo, eldest and mightiest of Theopold's sons.")

Command2(INTL( 554, "HELP"),INTL( 4275, "HINT"))
INTL( 4304, "Loathsome I may be, but you go nowhere before me.")

Command2(INTL( 4305, "FAT"),INTL( 4306, "WEIGHT"))
INTL( 4307, "Mock me not! My mass was a great asset as a fighter! Few could "
"resist my unrelenting onslaughts!")

Command(INTL( 1794, "ROYAL KEY"))
""
IF (CheckFlag(__QUEST_DEAD_BROTHERS) >= 12)
	Conversation
	INTL( 4308, "These keys can be found all over Raven's Dust, and will help you unlock the "
	"dungeon where you will find the cuthana herb. Return to me when you have them "
	"all.")
ELSE
	Conversation
	INTL( 4309, "You must first ask the right one among us...")
ENDIF

Command(INTL( 554, "HELP"))
""
IF ((USER_KARMA >= 100) && (CheckFlag(__QUEST_DEAD_BROTHERS) == 12))
	Conversation
	INTL( 4310, "I will help you, for you are a good person at heart, and even in death I have "
	"some life force to give.")
	IF (USER_HP <= (USER_MAXHP/2))
		target->SetHP(USER_HP * 1.5, true)
	ENDIF
	IF ((CheckItem(__OBJ_LIGHT_HEALING_POTION) <= 5) && (Gold >= 100))
		GiveItem(__OBJ_LIGHT_HEALING_POTION)
		TakeGold(100)
	ENDIF
ELSE
	Conversation
	INTL( 4311, "I may be dead, but I do not help just anyone.")
ENDIF

Command2(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"))
INTL( 4312, "I am the guardian of my brothers, no less, even in death and after "
"they tried to kill me, back then.")

Command(INTL( 4313, "GUARDIAN"))
INTL( 4314, "Indeed, we fought each other, but even after our passing, I cannot hold "
"a grudge against them. It was our father's crime that caused our death, "
"not anyone else's. Still, I should have become king, not Theodore...")

Command(INTL( 1072, "KING"))
INTL( 4315, "A shame that our weakest and laziest brother now rules this kingdom. Had I "
"acceeded to the throne, Goldmoon would now rule over Stoneheim as well as Goldmoon. But "
"one must accept's one fate, I guess.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 4278, "Such foul language can only mean you have life force to spare.")
IF (USER_HP >= 2)
	target->SetHP(USER_HP / 2, true)
ENDIF
BREAK

CmdAND(INTL( 6126, "RIDDLE"),INTL( 4275, "HINT"))
INTL( 7134, "I don't give hints to riddles, but old man Menark might be able to help you.")

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 4316, "Safe travels.")
BREAK

Default
INTL( 4317, "This means little to me.")

EndTalk
}
