#pragma hdrstop
#include "DaranAtrocity.h"

DaranAtrocity::DaranAtrocity()
{}

DaranAtrocity::~DaranAtrocity()
{}

extern NPCstructure::NPC DaranAtrocityNPC;

void DaranAtrocity::Create( void )
{
        npc = ( DaranAtrocityNPC ) ;
        SET_NPC_NAME( "[10845]An Atrocity (with Daran's voice)" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void DaranAtrocity::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT TakeBlades = 1;
CONSTANT HelpDaran = 2; 
CONSTANT GiveScroll = 3;

InitTalk

Begin //WARNING: Code modified from "original" Daran to accomodate the "transformation".
""
IF(CheckGlobalFlag(__QUEST_DARAN_ROMANCE) > 5)
	Conversation
	INTL( 9216, "I'm an Atrocity, I know, but I have someone helping me already. I can't wait "
	"to be myself again. Just don't mind my \"looks\", it's business as usual.")
ELSE
	Conversation
	INTL( 9217, "Oh my god, I've become an *ATROCITY*!!! Someone better \"help\" me...")
	PRIVATE_SYSTEM_MESSAGE(INTL( 9218, "The Atrocity (whose voice sounds like Daran's) shakes his head in disbelief."))
ENDIF

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 8281, "I don't say hello for free nowadays.")
IF (rnd.roll(dice(1,5)) == 1)
	Conversation
	INTL( 8282, " Hey, you're quite fast. I'm really impressed.") 
	PRIVATE_SYSTEM_MESSAGE(INTL( 8283, "You caught Daran Lightfoot in the act of robbing you!")) 
ELSE	
	IF (Gold > 10000 )
	   TakeGold(1000)
	ENDIF
ENDIF 

Command2(INTL( 8284, "DARAN"),INTL( 8285, "LIGHTFOOT"))
INTL( 8286, "Yes, that is my name. Lightfoot refers to my fleeing talents.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8287, "The name is Daran Lightfoot, at your service. Hey, you wouldn't know someone "
"who has some \"assassin's\" \"blades\", would you? Uhh, guess not. I tell you what... if "
"you ever get your hands on some of these blades, I'd be interested in making a little trade "
"with ya.")

Command2(INTL( 8288, "MAYOR"),INTL( 8289, "FAIRWEATHER")) 
INTL( 9219, "Mayor Fairweather is the rich bas... man living down the street in a large house he "
"built using the Stonecrest taxes.")

CmdAND(INTL( 7984, "ASSASSIN"),INTL( 7985, "BLADE"))
""
IF(CheckItem(__OBJ_ASSASSIN_BLADE) >= 2)
	Conversation
	INTL( 9220, "If you want, I can trade you two of them against a little trinket I have. "
	"Interested?")
	SetYesNo(TakeBlades)
ELSE
	Conversation
	INTL( 9221, "Those items are hard to find and pretty useful for someone in my line of work. *heh* "
	"Look, if you bring me two \"Assassin's\" \"Blades\", I'll give you something in "
	"exchange.")
ENDIF

YES(TakeBlades)
	Conversation
	INTL( 8293, "That's the spirit! ")
	IF(CheckItem(__OBJ_ASSASSIN_BLADE) >= 2)
		Conversation
		INTL( 8294, "Here we go!")
		FOR(0,2) 
			TakeItem(__OBJ_ASSASSIN_BLADE)
		ENDFOR
		GiveItem(__OBJ_BROKEN_ETHEREAL_KEY)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8295, "You give Daran two Assassin's Blades."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 8296, "You receive a Broken Ethereal Key."))
		;int nExpReward = USER_LEVEL*1500;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
		GiveXP(nExpReward)
	ELSE
		Conversation
		INTL( 8297, "Hey, what happened? Did you drop them or what?!?")
	ENDIF

NO(TakeBlades)
	Conversation
	INTL( 9222, "I won't take \"no\" for an answer, friend.")
	PRIVATE_SYSTEM_MESSAGE(INTL( 8299, "Daran's friendly grin broadens some more."))

YesNoELSE(TakeBlades)
	Conversation
	INTL( 9223, "That's a \"yes\", right?")
	SetYesNo(TakeBlades)

CmdAND3(INTL( 8301, "BROKEN"),INTL( 5010, "ETHER"),INTL( 8191, "KEY"))
INTL( 9224, "I have no idea what door it opens, but perhaps you should ask Chryseida? She's a "
"fortune teller, if anyone can point you in the right direction, she might be it, hm? "
"But I hear her services are very, very expensive, so good luck!")
PRIVATE_SYSTEM_MESSAGE(INTL( 8303, "Daran laughs mischievously."))

Command3(INTL( 8304, "SHERIFF"),INTL( 8305, "HORNKEEP"),INTL( 8306, " GRANT ")) 
INTL( 8307, "The Stonecrest sheriff, Grant Hornkeep, can usually be found patrolling the town's entrance.")

Command(INTL( 586, "GUILD")) 
INTL( 8308, "Guild? What guild are you talking about?")

CmdAND(INTL( 970, "THIEF"), INTL( 586, "GUILD")) 
INTL( 9225, "You want to learn the location of the Thieves' Guild? I'm afraid I cannot help you with that. "
"You'll have to find it yourself, I guess.")

CmdAND(INTL( 8310, "THIEVE"), INTL( 586, "GUILD")) 
INTL( 9226, "You want to learn the location of the Thieves' Guild? I'm afraid I cannot help you with that. "
"You'll have to find it yourself, I guess.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
""
IF ((CheckFlag(__BLACK_MARKET) >= 1) || ( UserSkill(__SKILL_PEEK) >= 1 ))
	Conversation
	INTL( 9227, "You seem like a reasonable person. I think I can tell a little \"secret\", just between "
	"you and me.") 
ELSE
	Conversation
	INTL( 8313, "You wouldn't be interested in what I do, trust me.")
ENDIF 

Command(INTL( 1533, "SECRET"))  
INTL( 9228, "You civilized people usually refer to this as \"robbing\" but I personally prefer long-term "
"borrowing. If they don't notice that you've borrowed something, it probably means they don't "
"need it in the first place. Heh! Heh!") 

Command(INTL( 1573, "ROBBING")) 
INTL( 9229, "Shhh! Keep it down, damnit! You don't want that fool \"Hornkeep\" to catch m.. us. If you "
"want to \"learn\" from the master himself, you need only to ask and I'll help you... for "
"a fee, of course.") 

Command2(INTL( 495, "LEARN"),INTL( 496, "TEACH"))
""
IF( UserSkill(__SKILL_PEEK) < 33 )
	Conversation
	INTL( 9230, "You're not good enough at peeking! If you don't know how to \"peek\", how can you expect to rob "
	"people? Never mind, you're obviously not worth the effort.")
ELSE
	IF( UserSkill(__SKILL_ROB) == 0 )
		IF( USER_LEVEL < 17 )
			IF( USER_TRUE_AGI < 50 )
				Conversation
				FORMAT(INTL( 4099, "You need %u more levels and %u more agility to learn rob."), 17 - USER_LEVEL, 50 - USER_TRUE_AGI )
			ELSE
				Conversation
				FORMAT(INTL( 4101, "You need %u more levels to learn rob."), 17 - USER_LEVEL )
			ENDIF
		ELSE
			IF( USER_TRUE_AGI < 50 )
				Conversation
				FORMAT(INTL( 4103, "You need %u more agility to learn rob."), 50 - USER_TRUE_AGI )
			ELSE
				Conversation
				INTL( 712, "Very well.")
				CreateSkillList
					AddTeachSkill( __SKILL_ROB, 1, 5000 )
				SendTeachSkillList
			ENDIF
		ENDIF
	ELSE
		Conversation
		INTL( 4105, "You have already learned rob.")
	ENDIF
ENDIF

Command(INTL( 502, "TRAIN"))
""
IF( UserSkill(__SKILL_ROB) == 0 )
	Conversation
	INTL( 814, "You must \"learn\" the skill before I can train you.")
ELSEIF( UserSkill(__SKILL_ROB) < 100 )
	Conversation
	INTL( 4106, "Very well then.")
	CreateSkillList
		AddTrainSkill( __SKILL_ROB, 100, 250 )
	SendTrainSkillList
ELSE
	Conversation
	INTL( 4107, "I have taught you all I know. You rob as well as I do!")
ENDIF
  
Command(INTL( 4108, "ROB"))
INTL( 9231, "{The} {rob} {technique} {allows} {a} {character} {to} {steal} {an} {object} {out} {of} {another} "
"{character's} {inventory.} {The} {peek} {skill} {must} {have} {a} {rating} {of} {33} {before} {rob} "
"{can} {be} {learned}. {Level:} {17} {-} {Agi:} {50}")

Command(INTL( 6251, "STONEHEIM"))
INTL( 4945, "That's the name of this island.") 

Command2(INTL( 7700, "STONECREST"),INTL( 1869, "TOWN"))
INTL( 8318, "Stonecrest is the name of the town you're in.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 698, " ASS "),INTL( 697, "ASSHOLE"))
INTL( 8319, "You bore me.")
IF (rnd.roll(dice(1,5)) == 1)
	PRIVATE_SYSTEM_MESSAGE(INTL( 8283, "You caught Daran Lightfoot in the act of robbing you!")) 
ELSE
	IF (Gold > 10000)
	   TakeGold(5000)
	ENDIF
ENDIF 
BREAK

Command4(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"))
""
IF( USER_GENDER == GENDER_FEMALE )
	Conversation
	INTL( 8320, "Awww. You're breaking my heart.")
ELSE
	Conversation
	INTL( 8321, "See ya around.")
ENDIF	
BREAK

/* ADDITIONAL COMMANDS FOR DARAN'S ROMANCE QUEST */

CmdAND(INTL( 8322, "SEDUC"),INTL( 8323, "ANNITHAE"))
INTL( 9232, "HEY! You think that's funny, eh? Who are you laughing at! Erm... Well, yeah, I guess "
"it's a little ironic, when you think about it. Well, it's quite a predicament I'm in, "
"as you can see...")

Command2(INTL( 8323, "ANNITHAE"),INTL( 8326, "TEARDROP"))
INTL( 9233, "Yeah, it's kind of because of her this all started. Oh, don't blame her, she's got "
"nothing to do with this, it's my own fault. But it should be all right soon... I "
"hope. Meanwhile, let's pretend this isn't happening, 'kay?")

Command2(INTL( 554, "HELP"),INTL( 896, "QUEST"))
""
IF(CheckGlobalFlag(__QUEST_DARAN_CERTIFICATE) == CheckFlag(__QUEST_DARAN_CERTIFICATE)) // The quest is already in progress:
	SWITCH(CheckGlobalFlag(__QUEST_DARAN_ROMANCE))
		CASE(5)
			Conversation
			INTL( 9234, "THIS IS A CATASTROPHE! It keeps going downhill! First I was in Annithae's "
			"body, now I'm a friggin' ATROCITY! Look, will you help me one more time?")
			SetYesNo(HelpDaran)
		ENDCASE
		CASE(6)
			Conversation
			INTL( 9235, "Please just go see Mithanna Snowraven and see if she's got something to "
			"\"help\" \"poor\" \"Daran\", anything will do! Maybe she's got a Scroll "
			"of Appearance Restoration or something, y'know?")
		ENDCASE
		CASE(7)
			Conversation
			INTL( 9236, "Please just go see Mithanna Snowraven and see if she's got something to "
			"\"help\" \"poor\" \"Daran\", anything will do! Maybe she's got a Scroll "
			"of Appearance Restoration or something, y'know?")
		ENDCASE
		CASE(8)
			IF(CheckItem(__OBJ_SCROLL_OF_APPEARANCE_RESTORATION) >= 1)
				Conversation
				INTL( 9237, "HEY, good deal, pal! I don't know how I can ever repay you! Can I have "
				"the scroll now?")
				SetYesNo(GiveScroll)
			ELSE //Defensive code.
				Conversation
				INTL( 9238, "What happened to the scroll? You should go see Mithanna and get another "
				"one.")
				GiveGlobalFlag(__QUEST_DARAN_ROMANCE, 6)
            ENDIF
		ENDCASE
		OTHERWISE
			PRIVATE_SYSTEM_MESSAGE(INTL( 9239, "[ERROR DL1.5] This text should not appear. If you see it, please report it to Vircom."))
        ENDCASE
	ENDSWITCH
ELSEIF(CheckFlag(__QUEST_DARAN_CERTIFICATE) != 0)
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
	PRIVATE_SYSTEM_MESSAGE(INTL( 8330, "A server crash or shutdown has occurred and you must restart this quest."))
ELSE
	Conversation
	INTL( 8334, "Someone else's already on the job, thanks.")
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
ENDIF

YES(HelpDaran)
	Conversation
	INTL( 9240, "THANKS! Look, I've learned my lesson! Enough with that sorcerer's apprentice stuff! I just "
	"want to be myself again. Okay, here's what you're gonna do. Go see Mithanna Snowraven "
	"and ask her if she can \"help\" \"poor\" \"Daran\". I'm sure she's got a Scroll of "
	"Appearance Restoration or something...")
	GiveGlobalFlag(__QUEST_DARAN_ROMANCE, 6)

NO(HelpDaran)
	Conversation
	INTL( 9241, "Say \"YES\", please!")
	SetYesNo(HelpDaran)

YesNoELSE(HelpDaran)
	Conversation
	INTL( 9242, "Say \"YES\", please!")
	SetYesNo(HelpDaran)

YES(GiveScroll)
	Conversation
	INTL( 9243, "I knew I could count on you! ")
	IF(CheckItem(__OBJ_SCROLL_OF_APPEARANCE_RESTORATION) >= 1)
		TakeItem(__OBJ_SCROLL_OF_APPEARANCE_RESTORATION)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9244, "You give Daran the Scroll of Appearance Restoration."))
		Conversation
		INTL( 9245, "Let me reward you for your great help! ")
		;int nExpReward = USER_LEVEL*7500;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) )
		GiveXP(nExpReward)
		;int nGoldReward = USER_LEVEL*10000;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 9246, "You receive %u gold pieces!"), nGoldReward) )
		GiveGold(nGoldReward)
		IF(rnd.roll(dice(1,100)) >= 95) // 5% of receiving a unique item.
			//GiveItem(???)
		ENDIF
		Conversation
		INTL( 9247, "Let's see what this does... Here goes nuthin'!")
		PRIVATE_SYSTEM_MESSAGE(INTL( 9248, "Daran reads the Scroll of Appearance Restoration."))
		RemFlag(__QUEST_DARAN_CERTIFICATE)
		GiveGlobalFlag(__QUEST_DARAN_CERTIFICATE,0)
		GiveGlobalFlag(__QUEST_DARAN_ROMANCE,0)
		//Insert Daran's Transformation into himself here, using a pentagram spell effect.
	ELSE
		Conversation
		INTL( 9249, "Hey, you jipped me! WHERE IS IT???")
	ENDIF

NO(GiveScroll)
	Conversation
	INTL( 9250, "No way! You're not backing out on me now, are you? Say \"YES\"!")
	SetYesNo(GiveScroll)

YesNoELSE(GiveScroll)
	Conversation
	INTL( 9251, "Aw, c'mon, pal! Make a little sense, here. \"Yes\" or \"no\"?")
	SetYesNo(GiveScroll)

CmdAND3(INTL( 1159, "SCROLL"),INTL( 9252, "APPEARANCE"),INTL( 9253, "RESTOR"))
""
IF(CheckGlobalFlag(__QUEST_DARAN_CERTIFICATE) == CheckFlag(__QUEST_DARAN_CERTIFICATE)) // The quest is already in progress:
	IF(CheckItem(__OBJ_SCROLL_OF_APPEARANCE_RESTORATION) >= 1)
		Conversation
		INTL( 9254, "HEY, good deal, pal! I don't know how I can ever repay you! Can I have "
		"the scroll now?")
		SetYesNo(GiveScroll)
	ELSE
		Conversation
		INTL( 9255, "Please just go see Mithanna Snowraven and see if she's got something to "
		"\"help\" \"poor\" \"Daran\", anything will do! Maybe she's got a Scroll "
		"of Appearance Restoration or something, y'know?")
	ENDIF
ELSEIF(CheckFlag(__QUEST_DARAN_CERTIFICATE) != 0)
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
	PRIVATE_SYSTEM_MESSAGE(INTL( 8330, "A server crash or shutdown has occurred and you must restart this quest."))
ELSE
	Conversation
	INTL( 8334, "Someone else's already on the job, thanks.")
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
ENDIF


CmdAND(INTL( 1427, "BOOK"),INTL( 8338, "DUPLICATION"))
""
IF(CheckGlobalFlag(__QUEST_DARAN_CERTIFICATE) == CheckFlag(__QUEST_DARAN_CERTIFICATE)) // The quest is already in progress:
	Conversation
	INTL( 9256, "Look, it's not the right time to talk about the book. Just \"help\" me, willya!")
ELSEIF(CheckFlag(__QUEST_DARAN_CERTIFICATE) != 0)
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
	PRIVATE_SYSTEM_MESSAGE(INTL( 8330, "A server crash or shutdown has occurred and you must restart this quest."))
ELSE
	Conversation
	INTL( 8334, "Someone else's already on the job, thanks.")
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
ENDIF

Command(INTL( 8347, "COMPONENT"))
""
IF(CheckGlobalFlag(__QUEST_DARAN_CERTIFICATE) == CheckFlag(__QUEST_DARAN_CERTIFICATE)) // The quest is already in progress:
	Conversation
	INTL( 9257, "Look, it's not the right time to talk about the components. Just \"help\" me, willya!")
ELSEIF(CheckFlag(__QUEST_DARAN_CERTIFICATE) != 0)
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
	PRIVATE_SYSTEM_MESSAGE(INTL( 8330, "A server crash or shutdown has occurred and you must restart this quest."))
ELSE
	Conversation
	INTL( 8334, "Someone else's already on the job, thanks.")
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
ENDIF

Command3(INTL( 9252, "APPEARANCE"),INTL( 1303, "LOOK"),INTL( 8354, "ATROCITY"))
INTL( 9258, "Yeah, I look like an Atrocity, let's not dwell on this, 'kay?")

Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 8356, "I don't really care about that.")
ELSE
   Conversation
   INTL( 8357, "I have little interest in that matter.")
ENDIF

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void DaranAtrocity::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL( __SKILL_ROB, 1, 5000 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_ROB, 100, 250 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
}


