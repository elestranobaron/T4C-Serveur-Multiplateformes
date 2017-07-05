#pragma hdrstop
#include "DaranLightfoot.h"

DaranLightfoot::DaranLightfoot()
{}

DaranLightfoot::~DaranLightfoot()
{}

extern NPCstructure::NPC DaranLightfootNPC;

void DaranLightfoot::Create( void )
{
        npc = ( DaranLightfootNPC ) ;
        SET_NPC_NAME( "[10846]Daran Lightfoot" );
        npc.InitialPos.X = 365;
        npc.InitialPos.Y = 820;
        npc.InitialPos.world = 0;
}

/*

WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING

  If you modify this character, please notify Jean and/or reproduce
  these modifications yourselves in the DaranAnnithae and DaranAtrocity
  CPP files. Normally, these characters are all identical except for
  a section at the end of the "alternate" CPP files (where Jean adds
  any quest-related code for Daran's Romance quest.

WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING

*/

void DaranLightfoot::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT TakeBlades = 1;
CONSTANT SeduceAnnithae = 2;

InitTalk

Begin
INTL( 8280, "Well, well.") 

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
INTL( 10529, "The name is Daran Lightfoot, at your service. Hey, you wouldn't know someone "
"who has some \"assassin's\" \"blades\", would you? Uhh, guess not. I tell you what... if "
"you ever get your hands on some of these blades, I'd be interested in making a little trade "
"with ya.") 	  	 

Command2(INTL( 8288, "MAYOR"),INTL( 8289, "FAIRWEATHER")) 
INTL( 8290, "Mayor Fairweather is the rich bas... man living down the street in a large house he "
"built using the Stonecrest taxes.")

CmdAND(INTL( 7984, "ASSASSIN"),INTL( 7985, "BLADE"))
""
IF(CheckItem(__OBJ_ASSASSIN_BLADE) >= 2)
	Conversation
	INTL( 8291, "If you want, I can trade you two of them against a little trinket I have. "
	"Interested?")
	SetYesNo(TakeBlades)
ELSE
	Conversation
	INTL( 8292, "Those items are hard to find and pretty useful for someone in my line of work. *heh* "
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
		PRIVATE_SYSTEM_MESSAGE(INTL( 10530, "You give Daran two Assassin's Blades."))
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
	INTL( 8298, "I won't take \"no\" for an answer, friend.")
	PRIVATE_SYSTEM_MESSAGE(INTL( 8299, "Daran's friendly grin broadens some more."))

YesNoELSE(TakeBlades)
	Conversation
	INTL( 8300, "That's a \"yes\", right?")
	SetYesNo(TakeBlades)

CmdAND3(INTL( 8301, "BROKEN"),INTL( 5010, "ETHER"),INTL( 8191, "KEY"))
INTL( 8302, "I have no idea what door it opens, but perhaps you should ask Chryseida? She's a "
"fortune teller, if anyone can point you in the right direction, she might be it, hm?")
PRIVATE_SYSTEM_MESSAGE(INTL( 8303, "Daran laughs mischievously."))

Command3(INTL( 8304, "SHERIFF"),INTL( 8305, "HORNKEEP"),INTL( 8306, " GRANT ")) 
INTL( 8307, "The Stonecrest sheriff, Grant Hornkeep, can usually be found patrolling the town's entrance.")

Command(INTL( 586, "GUILD")) 
INTL( 8308, "Guild? What guild are you talking about?")

CmdAND(INTL( 970, "THIEF"), INTL( 586, "GUILD")) 
INTL( 8309, "You want to learn the location of the Thieves' Guild? I'm afraid I cannot help you with that. "
"You'll have to find it yourself, I guess.")

CmdAND(INTL( 8310, "THIEVE"), INTL( 586, "GUILD")) 
INTL( 8311, "You want to learn the location of the Thieves' Guild? I'm afraid I cannot help you with that. "
"You'll have to find it yourself, I guess.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
""
IF ((CheckFlag(__BLACK_MARKET) >= 1) || ( UserSkill(__SKILL_PEEK) >= 1 ))
	Conversation
   INTL( 8312, "You seem like a reasonable person. I think I can tell a little \"secret\", just between "
	"you and me.") 	
ELSE
	Conversation
	INTL( 8313, "You wouldn't be interested in what I do, trust me.")
ENDIF 

Command(INTL( 1533, "SECRET"))  
INTL( 8314, "You civilized people usually refer to this as \"robbing\" but I personally prefer long-term "
"borrowing. If they don't notice that you've borrowed something, it probably means they don't "
"need it in the first place. Heh! Heh!") 

Command(INTL( 1573, "ROBBING")) 
INTL( 8315, "Shhh! Keep it down, damnit! You don't want that fool \"Hornkeep\" to catch m.. us. If you "
"want to \"learn\" from the master himself, you need only to ask and I'll help you... for "
"a fee, of course.") 

Command2(INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 712, "Very well.")
CreateSkillList
	AddTeachSkill( __SKILL_ROB, 1, 5000 )
SendTeachSkillList

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
INTL( 8317, "{The} {rob} {technique} {allows} {a} {character} {to} {steal} {an} {object} {out} {of} {another} "
"{character's} {inventory.} {The} {peek} {skill} {must} {have} {a} {rating} {of} {25} {before} {rob} "
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

Command2(INTL( 8323, "ANNITHAE"),INTL( 8326, "TEARDROP"))
INTL( 8327, "Annithae is the nicest woman I've ever met. She lives alone in a small house near the "
"fountain. Someday, I swear I'll steal her heart with my charm and my good looks")
IF( USER_GENDER == GENDER_FEMALE )
	Conversation
   INTL( 8328, ", if I don't steal yours first!")
ELSE
   Conversation
   INTL( 8329, ".")
ENDIF

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
/* NOTICE: DARAN'S QUEST HAS BEEN DISABLED ON October 31th 2000. 
CmdAND(INTL( 8322, "SEDUC"),INTL( 8323, "ANNITHAE"))
INTL( 8324, "Aaah, to hold her in my arms... It doesn't really matter to me if it's the real one "
"or a magical copy who loves me, as long as I can have her... Y'know what I mean?")
PRIVATE_SYSTEM_MESSAGE(INTL( 8325, "Daran winks at you meaningfully."))

Command2(INTL( 8323, "ANNITHAE"),INTL( 8326, "TEARDROP"))
INTL( 8327, "Annithae is the nicest woman I've ever met. She lives alone in a small house near the "
"fountain. Someday, I swear I'll steal her heart with my charm and my good looks")
IF( USER_GENDER == GENDER_FEMALE )
	Conversation
   INTL( 8328, ", if I don't steal yours first!")
ELSE
   Conversation
   INTL( 8329, ".")
ENDIF

Command2(INTL( 554, "HELP"),INTL( 896, "QUEST"))
""
IF(CheckGlobalFlag(__QUEST_DARAN_CERTIFICATE) == 0) //Daran's ready to start the quest (server crash/shutdown or no):
	IF(CheckFlag(__QUEST_DARAN_CERTIFICATE) != 0) //Server crash interrupted the quest; must restart.
		RemFlag(__QUEST_DARAN_CERTIFICATE)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8330, "A server crash or shutdown has occurred and you must restart this quest."))
		BREAK
	ENDIF
	Conversation
	INTL( 8331, "If you really want to help, I might need your assistance in \"seducing\" \"Annithae\". "
	"Whaddya say?")
	SetYesNo(SeduceAnnithae)
ELSEIF(CheckGlobalFlag(__QUEST_DARAN_CERTIFICATE) == CheckFlag(__QUEST_DARAN_CERTIFICATE)) // The quest is already in progress:
	SWITCH(CheckGlobalFlag(__QUEST_DARAN_ROMANCE))
		CASE(1)
			Conversation
			INTL( 8332, "Like I said... Get me the book, then we'll see.")
		ENDCASE
		CASE(2)
			Conversation
			INTL( 8333, "All I need now are the components I mentioned: three Tear-Shaped "
			"Pearls and four Vials of Fey Blood.")
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

YES(SeduceAnnithae)
	Conversation
	INTL( 8335, "Hey, thanks, pal! Here's the trick... I've heard of this really old tome called "
	"the \"Book\" \"of\" \"Duplication\", which describes a spell that could create the "
	"Annithae of my dreams, one who would love me. I don't know where this book is hiding, "
	"but that's your first mission: bring it to me. Then we'll see.")
	GiveGlobalFlag(__QUEST_DARAN_ROMANCE, 1)
	GiveGlobalFlag(__QUEST_DARAN_CERTIFICATE, CurrentRound)
	GiveFlag(__QUEST_DARAN_CERTIFICATE, CheckGlobalFlag(__QUEST_DARAN_CERTIFICATE))

NO(SeduceAnnithae)
	Conversation
	INTL( 8336, "Oh well. I'll find someone else.")

YesNoELSE(SeduceAnnithae)
	Conversation
	INTL( 8337, "I'm not sure what that meant. Was it a \"yes\" or a \"no\"?")
	SetYesNo(SeduceAnnithae)

CmdAND(INTL( 1427, "BOOK"),INTL( 8338, "DUPLICATION"))
""
IF(CheckGlobalFlag(__QUEST_DARAN_CERTIFICATE) == 0) //Daran's ready to start the quest (server crash/shutdown or no):
	IF(CheckFlag(__QUEST_DARAN_CERTIFICATE) != 0) //Server crash interrupted the quest; must restart.
		RemFlag(__QUEST_DARAN_CERTIFICATE)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8330, "A server crash or shutdown has occurred and you must restart this quest."))
		BREAK
	ENDIF
	SWITCH(CheckGlobalFlag(__QUEST_DARAN_ROMANCE))
		CASE(0)
			Conversation
			INTL( 8339, "You know about it? Well, good fer ya!")
		ENDCASE
		CASE(1)
			IF(CheckItem(__OBJ_BOOK_OF_DUPLICATION) > 0)
				Conversation
				INTL( 8340, "Oh, great! ")
				PRIVATE_SYSTEM_MESSAGE(INTL( 8341, "You give Daran the Book of Duplication."))
				TakeItem(__OBJ_BOOK_OF_DUPLICATION)
				Conversation
				INTL( 8342, "Let's see, now... Hmm... It says here that I need three items that "
				"represent the one I love... I guess Tear-Shaped Pearls should "
				"do fine. Oh, and we'll need four Vials of Fey Blood, too. "
				"Come back and tell me when you've got the \"components\".")
				GiveGlobalFlag(__QUEST_DARAN_ROMANCE,2)
			ELSE
				Conversation
				INTL( 8343, "Like I said, bring it to me, and I'll tell you then what I need... Ah, "
				"Annithae... She will be mine... Oh yes, she WILL be mine... Heh heh heh.")
			ENDIF
		ENDCASE
		CASE(2)
			Conversation
			INTL( 8344, "Thanks for the book. Now all I need are the components I mentioned: THREE "
			"Tear-Shaped Pearls and FOUR Vials of Fey Blood. "
			"Let me know when you've got all the \"components\".")
		ENDCASE
		OTHERWISE //Debug code.
			Conversation
			INTL( 8345, "Huh? Something's wrong, here...")
			PRIVATE_SYSTEM_MESSAGE(INTL( 8346, "[ERROR DL1.1] This text should not appear. If you see it, please report it to Vircom."))
	ENDSWITCH
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
IF(CheckGlobalFlag(__QUEST_DARAN_CERTIFICATE) == 0) //Daran's ready to start the quest (server crash/shutdown or no):
	IF(CheckFlag(__QUEST_DARAN_CERTIFICATE) != 0) //Server crash interrupted the quest; must restart.
		RemFlag(__QUEST_DARAN_CERTIFICATE)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8330, "A server crash or shutdown has occurred and you must restart this quest."))
		BREAK
	ENDIF
	SWITCH(CheckGlobalFlag(__QUEST_DARAN_ROMANCE))
		CASE(0)
			Conversation
			INTL( 8348, "Components? I don't know what you're talking about.")
		ENDCASE
		CASE(1)
			Conversation
			INTL( 8348, "Components? I don't know what you're talking about.")
		ENDCASE
		CASE(2)
			IF(CheckItem(__OBJ_VIAL_OF_FEY_BLOOD) >= 4 && CheckItem(__OBJ_TEAR_SHAPED_PEARL) >= 3)
				Conversation
				INTL( 8349, "Hey, you've got it all, thanks! ")
				FOR(0,3) 
					TakeItem(__OBJ_VIAL_OF_FEY_BLOOD)
					TakeItem(__OBJ_TEAR_SHAPED_PEARL)
				ENDFOR
				TakeItem(__OBJ_VIAL_OF_FEY_BLOOD)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8350, "You give Daran four Vials of Fey Blood and three Tear-Shaped Pearls."))
				Conversation
				INTL( 8351, "Okay, I've rehearsed this spell often enough, let's see what happens now.")
				GiveGlobalFlag(__QUEST_DARAN_ROMANCE,3)
				//Insert Daran's Transformation into Annithae here, using a pentagram spell effect.
			ELSE
				Conversation
				INTL( 8352, "Thanks for the book. Now all I need are the components I mentioned: THREE "
				"Tear-Shaped Pearls and FOUR Vials of Fey Blood. "
				"Let me know when you've got all the \"components\".")
			ENDIF
		ENDCASE
		OTHERWISE //Debug code.
			Conversation
			INTL( 8345, "Huh? Something's wrong, here...")
			PRIVATE_SYSTEM_MESSAGE(INTL( 8353, "[ERROR DL1.2] This text should not appear. If you see it, please report it to Vircom."))
	ENDSWITCH
ELSEIF(CheckFlag(__QUEST_DARAN_CERTIFICATE) != 0)
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
	PRIVATE_SYSTEM_MESSAGE(INTL( 8330, "A server crash or shutdown has occurred and you must restart this quest."))
ELSE
	Conversation
	INTL( 8334, "Someone else's already on the job, thanks.")
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
ENDIF

Command(INTL( 8354, "ATROCITY"))
INTL( 8355, "Huh?? You sayin' I look like an Atrocity? You kiddin' me?")
*/

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
void DaranLightfoot::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
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


