#pragma hdrstop
#include "KhanWulgworth.h"

KhanWulgworth::KhanWulgworth()
{}

KhanWulgworth::~KhanWulgworth()
{}

extern NPCstructure::NPC KhanWulgworthNPC;

void KhanWulgworth::Create( ){
	npc = KhanWulgworthNPC;
	SET_NPC_NAME( "[10866]Khan Wulgworth" );
	npc.InitialPos.X = 2165;
	npc.InitialPos.Y = 140;
	npc.InitialPos.world = 2; 
	npc.boPrivateTalk = TRUE;
}

void KhanWulgworth::OnTalk( UNIT_FUNC_PROTOTYPE )

{
 
CONSTANT TakeMace = 1;

InitTalk

Begin
INTL( 8836, "Why, hello there, good day to you.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8837, "My name is Khan Wulgworth. You may call me 'Your Honor' since I "
"graduated in Law from the Corinthian Academy of Jurists.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8838, "I trained to be a judge, but seeing all the corruption of human "
"society convinced me to return to my folks and improve their lives.")

Command2(INTL( 554, "HELP"),INTL( 896, "QUEST"))
INTL( 8839, "If you will help me, I might have a task for you. Have you ever heard of \"Skraugbashor\" \"Maces\"? If so,"
"please kindly bring me as many as you can.")

CmdAND(INTL( 8128, "VILLAIN"), INTL( 8129, "SKULL"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8840, "Yes, I have heard something to that effect. It seems there is a human in the town of Stonecrest that trades valuables and "
	"other paraphernalia in exchange for a certain type of skull. I believe his name was Delnar... yes that was it.")
ELSE
	Conversation
	INTL( 8841, "You might wish to rephrase that.")
	FIGHT
ENDIF

CmdAND(INTL( 8251, "SKRAUGBASHOR"),INTL( 8252, "MACE"))
""
IF (CheckItem(__OBJ_SKRAUGBASHOR_MACE) < 5)
	Conversation
	INTL( 8842, "This is quite an excellent item, even though it's Kahp Leth manufacture. This said, should you bring me five such "
	"maces, I will gladly reward you with a \"belt\" \"of\" \"skraug\" \"strength\".")
ELSE
	Conversation
	INTL( 8843, "I see that you are the proud owner of many \"Skraugbashor\" \"Maces\". Would you part with five of them in exchange "
	"for a \"belt\" \"of\" \"skraug\" \"strength\"?")
	SetYesNo(TakeMace)
ENDIF

YES(TakeMace)
	IF (CheckItem(__OBJ_SKRAUGBASHOR_MACE) < 5)
		Conversation
		INTL( 8844, "Your attempt at deceiving me has failed. You must have at least five Maces in your backpack "
		"for this transaction to occur.")
	ELSE
		Conversation
		INTL( 8845, "Excellent news!")
		FOR(0,5) 
			TakeItem(__OBJ_SKRAUGBASHOR_MACE)
		ENDFOR
		GiveItem(__OBJ_BELT_OF_SKRAUG_STRENGTH)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8846, "You receive a Belt of Skraug Strength.")) 
		;int nExpReward = USER_LEVEL*1000;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
		GiveXP(nExpReward)
	ENDIF

NO(TakeMace)
	Conversation
	INTL( 8847, "Ah, you disappoint me, but I will not hold this against you.")

YesNoELSE(TakeMace)
	Conversation
	INTL( 8848, "A \"yes\" or \"no\" shall suffice.")
	SetYesNo(TakeMace)

CmdAND3(INTL( 8124, "BELT"),INTL( 8125, "SKRAUG"),INTL( 8126, "STRENGTH"))
INTL( 8849, "I'll reward you with a \"Belt\" \"of\" \"Skraug\" \"Strength\" if you bring me five \"Skraugbashor\" \"Maces\".")

Command(INTL( 8850, "DELNAR"))
""

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8851, "Fare well, and be sure to stay away from my people.")
BREAK

Default
INTL( 8841, "You might wish to rephrase that.")

EndTalk
}
