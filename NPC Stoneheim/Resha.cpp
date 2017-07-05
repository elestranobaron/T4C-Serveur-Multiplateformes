#pragma hdrstop
#include "Resha.h"

Resha::Resha()
{}

Resha::~Resha()
{}

extern NPCstructure::NPC ReshaNPC;

void Resha::Create( void )
{
   npc = ReshaNPC;
	SET_NPC_NAME( "[10913]Resha" );
   npc.InitialPos.X = 280;
   npc.InitialPos.Y = 695;
	npc.InitialPos.world = 0;
}

void Resha::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT TakeBows = 1;

InitTalk

Begin
INTL( 9990, "Do not bother me unless it's important.")

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 8866, "I have no time for chit-chats.")
BREAK

Command2(INTL( 9975, "RESHA"),INTL( 9976, "MARSACK"))
INTL( 2535, "Yes?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 9991, "You may call me Resha.")

Command2(INTL( 554, "HELP"),INTL( 896, "QUEST"))
""
IF(CheckItem(__OBJ_BOW_OF_CENTAUR_SLAYING) > 0)
	Conversation
	INTL( 9992, "Forget about quests! What are you doing with \"Bows\" \"of\" \"Centaur\" \"Slaying\"?!?")
ELSE
	Conversation
	INTL( 9993, "Well, I don't have any work for you, sorry. Perhaps you should check with Chryseida, "
	"the fortune-teller?")
ENDIF

CmdAND3(INTL( 7994, "BOW"),INTL( 7995, "CENTAUR"),INTL( 7996, "SLAY"))
""
IF(CheckItem(__OBJ_BOW_OF_CENTAUR_SLAYING) >= 5)
	Conversation
	INTL( 9994, "I see you've accumulated enough bows to earn your reward. I'll trade you a \"Cloak\" "
	"\"of\" \"the\" \"Archer\" against five of these bows. Agreed?")
	SetYesNo(TakeBows)
ELSEIF (CheckItem(__OBJ_BOW_OF_CENTAUR_SLAYING) > 0)
	Conversation
	INTL( 9995, "Come back when you have five of them, and I'll reward you. Stop wasting my time about "
	"this until then!")
ELSE
	Conversation
	INTL( 9996, "I happen to be friends with many centaurs! These bows are an outrage to the good will "
	"that has been developing between Centaurs and humans, and they must be destroyed. Bring "
	"them to me and I'll reward you.")
ENDIF

YES(TakeBows)
	IF(CheckItem(__OBJ_BOW_OF_CENTAUR_SLAYING) < 5)
		Conversation
		INTL( 9997, "I knew you couldn't be trusted!")
	ELSE
		Conversation
		INTL( 9998, "Here's your cloak. Thanks! I appreciate this.")
		FOR(0,5) 
			TakeItem(__OBJ_BOW_OF_CENTAUR_SLAYING)
		ENDFOR
		GiveItem(__OBJ_CLOAK_OF_THE_ARCHER)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9999, "You have just received a Cloak of the Archer."))
		;int nExpReward = USER_LEVEL*2500;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
		GiveXP(nExpReward)
	ENDIF

NO(TakeBows)
	Conversation
	INTL( 9997, "I knew you couldn't be trusted!")
	BREAK

YesNoELSE(TakeBows)
	Conversation
	INTL( 10000, "\"Yes\" or \"no\"?")
	SetYesNo(TakeBows)

Command(INTL( 5628, "ORACLE"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) >= 1)
	Conversation
	INTL( 10001, "*grumble* Yeah, I know of him. I went to him to ascend, a long time ago, but I did "
	"not succeed the challenges he put before me, so I returned here as a guard. Hope "
	"you'll have better luck!")
ELSE
	Conversation
	INTL( 10002, "None of your business! Leave me be.")
	BREAK
ENDIF

CmdAND(INTL( 10003, "CLOAK"),INTL( 10004, "ARCHER"))
INTL( 10005, "If you're an archer, this magically enhances your accuracy with a bow, and deflects some "
"of the attacks against you. Since I used to be a champion archer, I've accumulated a lot "
"of those, but I no longer need them since I use better gear, given to me by some of my "
"centaur friends.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 10006, "My duty is to enforce the law and protect the citizens of Stonecrest "
"from harm.")

Command2(INTL( 8284, "DARAN"),INTL( 8285, "LIGHTFOOT"))
INTL( 10007, "He should be hanged and his entrails should be given to the bears in "
"the forest.")

Command3(INTL( 738, "MAKRSH"),INTL( 739, "P'TANGH"),INTL( 737, "LICH"))
INTL( 10008, "Did you know that Makrsh P'Tangh the Lich used to be an elven prince? He "
"sure doesn't look like an elf anymore. They say that he is cursed "
"but I am not sure it is a curse to have such awesome powers.")

Command5(INTL( 697, "ASSHOLE"),INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 1919, "WHORE"),INTL( 698, " ASS "))
INTL( 10009, "I'll teach you some good manners.")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 1075, "Farewell.")
BREAK

Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 5910, "What was that you said?")
ELSE
   Conversation
   INTL( 5758, "I have no interest in that matter.")
ENDIF

EndTalk
}
				 