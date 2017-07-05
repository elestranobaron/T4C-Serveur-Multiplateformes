#pragma hdrstop
#include "GrantHornkeep.h"

GrantHornkeep::GrantHornkeep()
{}

GrantHornkeep::~GrantHornkeep()
{}

extern NPCstructure::NPC GrantHornkeepNPC;

void GrantHornkeep::Create( void )
{
    npc = GrantHornkeepNPC;
    SET_NPC_NAME( "[10856]Sheriff Grant Hornkeep" );
    npc.InitialPos.X = 315;
    npc.InitialPos.Y = 740;
    npc.InitialPos.world = 0;
}


void GrantHornkeep::OnTalk( UNIT_FUNC_PROTOTYPE )
{							  
InitTalk 

CONSTANT TakeBelts = 1;
CONSTANT GiveDocument = 2;

Begin
INTL( 9926, "Please, be brief. I have work to do.")

Command2(INTL( 8706, "GRANT"),INTL( 8305, "HORNKEEP"))
INTL( 9927, "Yes, that's the name. I am the town's sheriff.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 9928, "I am Grant Hornkeep, but you may call me Grant.")

Command2(INTL( 554, "HELP"),INTL( 896, "QUEST"))
INTL( 9929, "I could use some \"Belt\" \"of\" \"Skraug\" \"Strength\", if you know where to find some. Also, "
"I could use some assitance in killing the \"nightcreepers\" and \"pilferers\" that hang around Stonecrest. "
"Also, if you could bring me some of the thieves' \"Secret\" \"Documents\", I could learn of their plans "
"and thwart them more efficiently.")

Command(INTL( 5628, "ORACLE"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) >= 1)
	Conversation
	INTL( 9930, "You will require the Key of Artherk before you can find him. Ask around, I'm sure "
	"you'll figure it out.")
ELSE
	Conversation
	INTL( 9931, "A lot of *good* folks have been asking about him, lately. I believe he exists, "
	"but I don't know if he's as powerful as they say.")
ENDIF

CmdAND(INTL( 1533, "SECRET"),INTL( 9932, "DOCUMENT"))
""
IF(CheckItem(__OBJ_SECRET_DOCUMENT) >= 5)
	Conversation
	INTL( 9933, "Well well, what do we have here? Are you saying you are giving me these secret documents?")
	SetYesNo(GiveDocument)
ELSEIF(CheckItem(__OBJ_SECRET_DOCUMENT) >= 1)
	Conversation
	INTL( 9934, "I see you have a few of those secret documents on you, but I really require five "
	"before I give you a reward for them.")
ELSE
	Conversation
	INTL( 9935, "The thieves' guild that operates in these parts keeps its plans on secret documents. "
	"Those are hidden in a steel safe in their hideout. The trick is to find the key "
	"to that safe, which I haven't been able to do. Bring me at least five such documents, "
	"and I'll give you a honest reward.")
ENDIF

YES(GiveDocument)
	Conversation
	INTL( 9936, "You're a righteous fellow! My thanks! ")
	IF(CheckItem(__OBJ_SECRET_DOCUMENT) >= 5)
		Conversation
		INTL( 9937, "Here! I give you a bit of gold and this Certificate of Recognition.")
		FOR(0,5)
			TakeItem(__OBJ_SECRET_DOCUMENT)
		ENDFOR
		GiveItem(__OBJ_CERTIFICATE_OF_RECOGNITION)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9938, "Grant gives you a Certificate of Recognition."))
		;int nExpReward = USER_LEVEL*2500;
		;int nGoldReward = USER_LEVEL*3500;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
		GiveXP(nExpReward)
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 9939, "Grant gives you %u gold pieces."), nGoldReward ))
		GiveGold(nGoldReward)
	ELSE
		Conversation
		INTL( 9940, "Wait! Where are they, suddenly? Ah, I knew this was too good to be true.")
	ENDIF

NO(GiveDocument)
	Conversation
	INTL( 9941, "Pity, that. Let me know if you change your mind.")

YesNoELSE(GiveDocument)
	Conversation
	INTL( 9942, "\"Yes\" or \"no\"?")
	SetYesNo(GiveDocument)

CmdAND(INTL( 8719, "CERTIFICATE"),INTL( 8720, "RECOGNITION"))
INTL( 9943, "You may not think it's worth a lot, but the mayor rewards handsomely individuals who have "
"accumulated many such certificates.")

Command(INTL( 8763, "NIGHTCREEPER"))
""
IF (CheckFlag(__FLAG_NIGHTCREEPERS_KILLED) < 9)
	Conversation
	INTL( 9944, "Please kill as many as you can. For every nine you kill, I'll give you a reward.")
ELSE
	Conversation
	INTL( 9945, "Bravo! You did good work. Here's your reward!")
	RemFlag(__FLAG_NIGHTCREEPERS_KILLED)
	GiveItem(__OBJ_THANK_YOU_NOTE)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9946, "Grant gives you a \"thank\" \"you\" \"note\"."))
    ;int nExpReward = 0;
	IF(USER_LEVEL*1500 < 50000)
		;nExpReward = USER_LEVEL*1500;
	ELSE
		;nExpReward = 50000;
	ENDIF
	PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
	GiveXP(nExpReward)
ENDIF

Command(INTL( 8766, "PILFERER"))
""
IF (CheckFlag(__FLAG_PILFERERS_KILLED) < 8)
	Conversation
	INTL( 9947, "They are a real pain in the neck! Kill eight of them and I'll give you a reward.")
ELSE
	Conversation
	INTL( 9948, "I knew I could count on you! Here's your reward.")
	RemFlag(__FLAG_PILFERERS_KILLED)
	GiveItem(__OBJ_THANK_YOU_NOTE)
	PRIVATE_SYSTEM_MESSAGE(INTL( 9949, "Grant gives you a \"Thank\" \"you\" \"note\"."))
    int nExpReward = 0;
	IF(USER_LEVEL*1000 < 50000)
		;nExpReward = USER_LEVEL*1000;
	ELSE
		;nExpReward = 50000
	ENDIF
	PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
	GiveXP(nExpReward)
ENDIF

CmdAND3(INTL( 8709, "THANK"),INTL( 8710, "YOU"),INTL( 8711, "NOTE"))
INTL( 9950, "You may not think those are very useful, but once you've got enough of them, the Mayor himself "
"will reward you.")

Command(INTL( 11335, "THANK-YOU NOTE")) 
INTL( 9950, "You may not think those are very useful, but once you've got enough of them, the Mayor himself "
"will reward you.")

CmdAND(INTL( 8030, "COLLECTOR"),INTL( 1427, "BOOK"))
INTL( 9951, "I have an extensive collection, second only to that of King Gravesoul, ruler of the Centaurs.")

CmdAND3(INTL( 8124, "BELT"),INTL( 8125, "SKRAUG"),INTL( 8126, "STRENGTH"))
""
IF (CheckItem(__OBJ_BELT_OF_SKRAUG_STRENGTH)<3)
	Conversation
	INTL( 9952, "Those belts could come in handy, actually. I could equip our militia with them and better "
	"protect Stonecrest, if you know what I mean. If you happen to have three of those, I'll "
	"trade them in for a very special \"Collector's\" \"Book\".")
ELSE
	Conversation
	INTL( 9953, "Would you like to trade three Belts against one \"Collector's\" \"Book\"?")
	SetYesNo(TakeBelts)
ENDIF

YES(TakeBelts)
	IF (CheckItem(__OBJ_BELT_OF_SKRAUG_STRENGTH) < 3)
		Conversation
		INTL( 9954, "You trying to cheat with *me*?!? What were you *thinking*???")
		BREAK
	ELSE
		Conversation
		INTL( 9955, "Wonderful! Let's proceed!")
		FOR(0,3)
			TakeItem(__OBJ_BELT_OF_SKRAUG_STRENGTH)
		ENDFOR
		GiveItem(__OBJ_COLLECTOR_BOOK)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9956, "Grant gives you a Collector's Book.")) 
		;int nExpReward = USER_LEVEL*3000;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
		GiveXP(nExpReward)
	ENDIF

NO(TakeBelts)
	Conversation
	INTL( 9957, "Then be on your way, I've got a town to protect.")

YesNoELSE(TakeBelts)
	Conversation
	INTL( 9958, "That was an odd answer. Did you say \"yes\" or \"no\"?")
	SetYesNo(TakeBelts)

Command3(INTL( 487, "OCCUPATION"),INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"))
INTL( 9959, "I am the town's sheriff. Now, if you'll excuse me, I still have some "
"unresolved cases that require my full attention. Unless you want to " 
"\"help\", I'll have to ask you to leave.") 

Command2(INTL( 8284, "DARAN"),INTL( 8285, "LIGHTFOOT"))
INTL( 9960, "If I get my hands on this thief, he will spend the remaining "
"days of his sorry life in a jail cell.")

Command(INTL( 8424, "TORGAS"))
INTL( 9961, "Torgas is the bartender of the local tavern, where all the miscreants "
"usually are.")

Command2(INTL( 9962, "NISSUS"),INTL( 9963, "HALOSEEKER"))
INTL( 9964, "Nissus Haloseeker is the only priest we have in our small temple. "
"Seek his aid if you need healing or guidance.")
 
Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 9965, "If you'll excuse me, there is work to be done.")
BREAK

Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 5396, "I honestly don't know.")
ELSE
   Conversation
   INTL( 9966, "I beg you pardon?")
ENDIF

EndTalk
}

