#pragma hdrstop
#include "MayorFairweather.h"

MayorFairweather::MayorFairweather()
{}

MayorFairweather::~MayorFairweather()
{}

extern NPCstructure::NPC MayorFairweatherNPC;

void MayorFairweather::Create( ){
	npc = MayorFairweatherNPC;
   SET_NPC_NAME(   "[10874]Mayor Fairweather" );
	npc.InitialPos.X = 305;
	npc.InitialPos.Y = 870;
	npc.InitialPos.world = 0;
}

void MayorFairweather::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT TakeNotes = 1;
CONSTANT TakeCertificate = 2;

InitTalk

Begin
INTL( 8703, "Please be brief, I have a lot of \"work\" that has to be done.")
	
Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8704, "I am Mayor Fairweather.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8705, "I am the mayor of Stonecrest. I see to the well-being of "
"the citizens of this town. In this, I have to say that I am fortunate "
"to have one such as \"Grant\" \"Hornkeep\" to uphold the law.") 

Command2(INTL( 8706, "GRANT"),INTL( 8305, "HORNKEEP"))
INTL( 8707, "He is the town's sheriff. It is his duty to enforce the law and stop "
"thieves and skraugs from wreaking havoc around here.")

Command(INTL( 1367, "DRAGON"))
INTL( 8708, "I used to be a dragonslayer in my young days. That's before I retired and took this job "
"as Stonecrest's mayor. It's a cushy job compared to fighting dragons, but the politics "
"can really get to you, sometimes. There are days when I miss the 'old life'...")

Command(INTL( 11335, "THANK-YOU NOTE")) 
""
IF (CheckItem(__OBJ_THANK_YOU_NOTE) < 6)
	Conversation
	INTL( 8712, "If you have half a dozen or more of those, I will reward you handsomely.")
ELSE
	Conversation
	INTL( 8713, "Oh! Happiness! A good, helpful citizen! If you wish, I will reward you for your good deeds. All right?")
	SetYesNo(TakeNotes)
ENDIF

CmdAND3(INTL( 8709, "THANK"),INTL( 8710, "YOU"),INTL( 8711, "NOTE"))
""
IF (CheckItem(__OBJ_THANK_YOU_NOTE) < 6)
	Conversation
	INTL( 8712, "If you have half a dozen or more of those, I will reward you handsomely.")
ELSE
	Conversation
	INTL( 8713, "Oh! Happiness! A good, helpful citizen! If you wish, I will reward you for your good deeds. All right?")
	SetYesNo(TakeNotes)
ENDIF

YES(TakeNotes)
	IF (CheckItem(__OBJ_THANK_YOU_NOTE) < 6)
		Conversation
		INTL( 8714, "I'm somewhat disappointed in you. What happened to your notes, all of a sudden? I'm sure you had "
		"at *least* six of them!")
	ELSE
		Conversation
		INTL( 8715, "My pleasure!")
		FOR(0,6) 
			TakeItem(__OBJ_THANK_YOU_NOTE)
		ENDFOR
		GiveItem(__OBJ_LOST_BLADE_OF_THE_DRAGON)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8716, "Mayor Fairweather gives you a Lost Blade of the Dragon."))
		;int nExpReward = USER_LEVEL*3000;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
		GiveXP(nExpReward)
	ENDIF

NO(TakeNotes)
	Conversation
	INTL( 8717, "Such a selfless fellow! Good for you.")

YesNoELSE(TakeNotes)
	Conversation
	INTL( 8718, "Pardon my feeble hearing, but was that a \"yes\" or a \"no\"?")
	SetYesNo(TakeNotes)

CmdAND(INTL( 8719, "CERTIFICATE"),INTL( 8720, "RECOGNITION"))
""
IF(CheckItem(__OBJ_CERTIFICATE_OF_RECOGNITION) >= 6)
	Conversation
	INTL( 8721, "I see you carry many Certificates of Recognition with you. Would you like to "
	"trade them in for a reward?")
	SetYesNo(TakeCertificate)
ELSEIF(CheckItem(__OBJ_CERTIFICATE_OF_RECOGNITION) >= 1)
	Conversation
	INTL( 8722, "I see you've got a few of those already. When you have half a dozen, come back "
	"and visit me, and I'll reward you accordingly.")
ELSE
	Conversation
	INTL( 8723, "Certificates of recognition are awarded by the sheriff of this town for great deeds "
	"done on behalf the the townsfolk.")
ENDIF

YES(TakeCertificate)
	IF (CheckItem( __OBJ_CERTIFICATE_OF_RECOGNITION) < 6 ) 
		Conversation
		INTL( 10222, "I'm somewhat disappointed in you. What happened to your certificates, all of a sudden? "
		"I'm sure you had at *least* six of them!")		
	ELSE
		Conversation
		INTL( 8724, "This is a good call, I think. ")
		FOR(0,6)
			TakeItem(__OBJ_CERTIFICATE_OF_RECOGNITION)
		ENDFOR
		GiveItem(__OBJ_LOST_HELM_OF_THE_DRAGON)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8725, "Mayor Fairweather gives you a Lost Helm of the Dragon."))
		;int nExpReward = USER_LEVEL*2000;
		;int nGoldReward = USER_LEVEL*1000;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) )
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 8726, "Mayor Fairweather gives you %u gold pieces."), nGoldReward) )
		GiveXP(nExpReward)
		GiveGold(nGoldReward)
	ENDIF 

NO(TakeCertificate)
	Conversation
	INTL( 8727, "It's your choice, I guess.")

YesNoELSE(TakeCertificate)
	Conversation
	INTL( 8728, "I... didn't quite get that. \"Yes\" or \"no\"?")
	SetYesNo(TakeCertificate)

CmdAND3(INTL( 3999, "LOST"),INTL( 7985, "BLADE"),INTL( 1367, "DRAGON"))
INTL( 8729, "I'm told it's a very potent item. I don't really know what it does, though.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8730, "I will not tolerate such language from anyone.")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 1075, "Farewell.")
BREAK

Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 8731, "I am sorry but you will have to seek your answers elsewhere.")
ELSE
   Conversation
   INTL( 5250, "I don't think that concerns me.")
ENDIF


EndTalk
}
