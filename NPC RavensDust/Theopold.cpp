#pragma hdrstop
#include "Theopold.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Theopold::Theopold()
{}

Theopold::~Theopold()
{}

extern NPCstructure::NPC DeadBrotherNPC;

void Theopold::Create(){
        npc = DeadBrotherNPC;
        SET_NPC_NAME( "[2988]Theopold's Specter" );
        npc.InitialPos.X = 625;  //Cave of Fear
        npc.InitialPos.Y = 290;  //Cave of Fear
        npc.InitialPos.world = 2;
}

void Theopold::OnTalk( UNIT_FUNC_PROTOTYPE )

/*

FLAG __QUEST_THEOPOLD_RIDDLES

	0: Haven't begun yet
	1: Answered Riddle #1
	2: Answered Riddle #2
	3: Answered Riddle #3
	4: Answered Riddle #4
	5: Answered Riddle #5
	6+: Answered Riddle #6

*/

{

CONSTANT ASK_RIDDLES = 1;
CONSTANT GOTO_CUTHANA = 2;

InitTalk

Begin
INTL( 6119, "A visitor... at last. What news bring thou from the world above?")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 6120, "We are the \"tormented\" spirit of King Theopold.")

Command(INTL( 4266, "TORMENT"))
INTL( 6121, "We cannot rest knowing that our cowardly and unworthy son sits on our throne, "
"and that our kingdom stands on the brink of chaos and destruction. There are "
"\"terrible\" \"events\" set in motion, and we are restless just thinking about it.")

CmdAND(INTL( 6126, "RIDDLE"),INTL( 4275, "HINT"))
INTL( 7157, "I will give you no such hint. Go back to your world and someone may help you there.")

Command(INTL( 4275, "HINT"))
INTL( 6122, "I give no hints. Find the answers to these riddles or return to your world. Perhaps "
"someone there will be able to give you \"riddle\" \"hints\".")

CmdAND(INTL( 6123, "TERRIBLE"),INTL( 4361, "EVENT"))
INTL( 6124, "These are none of thy concern. Thou shalt certainly learn of them soon enough, "
"should thy prove worthy.")

Command2(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"))
INTL( 6125, "We do no work since we are made of ether. We do have \"riddles\", however, and "
"you must answer those if you wish to proceed further.")

Command(INTL( 6126, "RIDDLE"))
""
IF (CheckFlag(__QUEST_THEOPOLD_RIDDLES) >= 6)
	Conversation
	INTL( 6127, "Thou know our riddles already, we might as well let thee pass. Are thou ready?")
	SetYesNo(GOTO_CUTHANA)
ELSE
	IF (CheckFlag(__QUEST_THEOPOLD_RIDDLES) == 2)
		IF (CheckItem(__OBJ_ROYAL_KEY_3) >= 1)
			Conversation
			INTL( 6128, "Excellent, although we wonder if thou did not guess this by mistake. No "
			"matter, let us proceed to the next \"riddle\". {You} {receive} {10,000} "
			"{XPs} {as} {a} {reward}.")
			GiveFlag(__QUEST_THEOPOLD_RIDDLES,3)
			TakeItem(__OBJ_ROYAL_KEY_3)
			GiveXP(10000)
		ELSE
			Conversation
			INTL( 6129, "Thou have the correct answer, but not the key we require, although thou were "
			"warned. Return to thine world, seek the key, then return to us.")
			TELEPORT(420,2500,0)
			BREAK
		ENDIF
	ELSE
		Conversation
		INTL( 6130, "We have many riddles to ask. For each riddle, we require a Royal Key. If thou "
		"do not have the required key, we shall send thee away. Are thou ready?")
		SetYesNo(ASK_RIDDLES)
	ENDIF
ENDIF

YES(ASK_RIDDLES)
SWITCH(CheckFlag(__QUEST_THEOPOLD_RIDDLES))
	CASE(0)
		IF (CheckItem(__OBJ_ROYAL_KEY_1) >= 1)
			Conversation
			INTL( 6131, "Let us start with a simple one. What is the center of balance?")
		ELSE
			Conversation
			INTL( 6132, "Thou do not have the first of the six keys. Return to thine world, "
			"seek that key and return here, if thou can.")
			TELEPORT(420,2500,0)
			BREAK
		ENDIF
	ENDCASE
	CASE(1)
		IF (CheckItem(__OBJ_ROYAL_KEY_2) >= 1)
			Conversation
			INTL( 6133, "What happens once in a minute, twice in a moment, once during weekdays "
			"but never during weekends, and never, ever during a hundred thousand "
			"years?")
		ELSE
			Conversation
			INTL( 6134, "Thou do not have the second of the six keys. Return to thine world, "
			"seek that key and return here, if thou can.")
			TELEPORT(420,2500,0)
			BREAK
		ENDIF
	ENDCASE
	CASE(2)
		IF (CheckItem(__OBJ_ROYAL_KEY_3) >= 1)
			Conversation
			INTL( 6135, "What sphynxes employ, the players enjoy.")
		ELSE
			Conversation
			INTL( 6136, "Thou do not have the third of the six keys. Return to thine world, "
			"seek that key and return here, if thou can.")
			TELEPORT(420,2500,0)
			BREAK
		ENDIF
	ENDCASE
	CASE(3)
		IF (CheckItem(__OBJ_ROYAL_KEY_4) >= 1)
			Conversation
			INTL( 6137, "AYAMS TOKEER ANNEED SOMELP.")
		ELSE
			Conversation
			INTL( 6138, "Thou do not have the fourth of the six keys. Return to thine world, "
			"seek that key and return here, if thou can.")
			TELEPORT(420,2500,0)
			BREAK
		ENDIF
	ENDCASE
	CASE(4)
		IF (CheckItem(__OBJ_ROYAL_KEY_5) >= 1)
			Conversation
			INTL( 6139, "One where none or two should be, seeking out purity in the king's tree. "
			"What am I?")
		ELSE
			Conversation
			INTL( 6140, "Thou do not have the fifth of the six keys. Return to thine world, "
			"seek that key and return here, if thou can.")
			TELEPORT(420,2500,0)
			BREAK
		ENDIF
	ENDCASE
	CASE(5)
		IF (CheckItem(__OBJ_ROYAL_KEY_6) >= 1)
			Conversation
			INTL( 6141, "Final riddle! I am better than eternal life, I am worse than death, "
			"dead men eat me, if you eat me you'll die.")
		ELSE
			Conversation
			INTL( 6142, "Thou do not have the last of the six keys. Return to thine world, "
			"seek that key and return here, if thou can.")
			TELEPORT(420,2500,0)
			BREAK
		ENDIF
	ENDCASE
	OTHERWISE
		Conversation
		INTL( 6143, "You have already answered all our riddles. Do you wish to move on?")
		SetYesNo(GOTO_CUTHANA)
	ENDCASE
ENDSWITCH

NO(ASK_RIDDLES)
Conversation
INTL( 6144, "We do not care either way.")

YesNoELSE(ASK_RIDDLES)
Conversation
INTL( 6145, "We do not understand thee. Speak up.")

Command(INTL( 5210, "NOTHING"))
""
IF (CheckFlag(__QUEST_THEOPOLD_RIDDLES) == 5)
	IF (CheckItem(__OBJ_ROYAL_KEY_6) >= 1)
		Conversation
		INTL( 6146, "AH! We are shocked! Very well, if thou know all the answers, we must keep our "
		"word and send you further along. Art thou ready?")
		GiveFlag(__QUEST_THEOPOLD_RIDDLES,6)
		SetYesNo(GOTO_CUTHANA)
	ELSE
		Conversation
		INTL( 6147, "Thou have the correct answer, but not the key we require, although thou were "
		"warned. Return to thine world, seek the key, then return to us.")
		TELEPORT(420,2500,0)
		BREAK
	ENDIF
ELSE
	Conversation
	INTL( 6148, "This is not the correct answer.")
ENDIF

YES(GOTO_CUTHANA)
IF (CheckItem(__OBJ_ROYAL_KEY_6) >= 1)
	Conversation
	INTL( 6149, "Hold on to thine horse, my friend. {You} {receive} {10,000} {XPs} {as} {a} {reward}.")
	TakeItem(__OBJ_ROYAL_KEY_6)
	GiveXP(10000)
	TELEPORT(655,350,2)
ELSE
	Conversation
	INTL( 6150, "But thou have not the key that we require! This will not do, we fear.")
ENDIF

NO(GOTO_CUTHANA)
Conversation
INTL( 6151, "Then stay with us a while longer, we do not mind.")

YesNoELSE(GOTO_CUTHANA)
Conversation
INTL( 6152, "Hm?")

Command(INTL( 6153, "UNICORN"))
""
IF (CheckFlag(__QUEST_THEOPOLD_RIDDLES) == 4)
	IF (CheckItem(__OBJ_ROYAL_KEY_5) >= 1)
		Conversation
		INTL( 6154, "You are truly very intelligent, or someone has fed you those answers! "
		"Let us proceed with the next \"riddle\", shall we? {You} {receive} {10,000} "
		"{XPs} {as} {a} {reward}.")
		GiveFlag(__QUEST_THEOPOLD_RIDDLES,5)
		GiveXP(10000)
		TakeItem(__OBJ_ROYAL_KEY_5)
	ELSE
		Conversation
		INTL( 6155, "Thou have the correct answer, but not the key we require, although thou were "
		"warned. Return to thine world, seek the key, then return to us.")
		TELEPORT(420,2500,0)
		BREAK
	ENDIF
ELSE
	Conversation
	INTL( 6148, "This is not the correct answer.")
ENDIF

Command(INTL( 6156, "I AM STUCK HERE AND NEED SOME HELP"))
""
IF (CheckFlag(__QUEST_THEOPOLD_RIDDLES) == 3)
	IF (CheckItem(__OBJ_ROYAL_KEY_4) >= 1)
		Conversation
		INTL( 6157, "Wonderful! Ha ha! We have not enjoyed ourselves this much since we passed away. "
		"Let us proceed with the next \"riddle\", if thou art ready. {You} {receive} "
		"{10,000} {XPs} {as} {a} {reward}.")
		GiveFlag(__QUEST_THEOPOLD_RIDDLES,4)
		GiveXP(10000)
		TakeItem(__OBJ_ROYAL_KEY_4)
	ELSE
		Conversation
		INTL( 6158, "Thou have the correct answer, but not the key we require, although thou were "
		"warned. Return to thine world, seek the key, then return to us.")
		TELEPORT(420,2500,0)
		BREAK
	ENDIF
ELSE
	Conversation
	INTL( 6148, "This is not the correct answer.")
ENDIF

Command(INTL( 11525, "LETTER M"))
""
IF (CheckFlag(__QUEST_THEOPOLD_RIDDLES) == 1)
	IF (CheckItem(__OBJ_ROYAL_KEY_2) >= 1)
		Conversation
		INTL( 6160, "Yes, that the correct answer. Let us proceed with the next \"riddle\", if "
		"thou art ready. {You} {receive} {10,000} {XPs} {as} {a} {reward}.")
		GiveFlag(__QUEST_THEOPOLD_RIDDLES,2)
		GiveXP(10000)
		TakeItem(__OBJ_ROYAL_KEY_2)
	ELSE
		Conversation
		INTL( 6161, "Thou have the correct answer, but not the key we require, although thou were "
		"warned. Return to thine world, seek the key, then return to us.")
		TELEPORT(420,2500,0)
	ENDIF
ELSE
	Conversation
	INTL( 6148, "This is not the correct answer.")
ENDIF

CmdAND(INTL( 1301, "LETTER"),INTL( 6162, " A"))
""
IF (CheckFlag(__QUEST_THEOPOLD_RIDDLES) == 0)
	IF (CheckItem(__OBJ_ROYAL_KEY_1) >= 1)
		Conversation
		INTL( 6163, "Yes, that is a good start. Let us proceed with the next \"riddle\", if "
		"thou art ready. {You} {receive} {10,000} {XPs} {as} {a} {reward}.")
		GiveFlag(__QUEST_THEOPOLD_RIDDLES,1)
		GiveXP(10000)
		TakeItem(__OBJ_ROYAL_KEY_1)
	ELSE
		Conversation
		INTL( 6164, "Thou have the correct answer, but not the key we require, although thou were "
		"warned. Return to thine world, seek the key, then return to us.")
		TELEPORT(420,2500,0)
		BREAK
	ENDIF
ELSE
	Conversation
	INTL( 6148, "This is not the correct answer.")
ENDIF

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 6165, "We have no tolerance for people such as thou.")
IF (USER_HP >= 2)
	target->SetHP(1, true)
ENDIF
BREAK

Command(INTL( 554, "HELP"))
INTL( 6166, "If you wish to return whence you came, just say the word.")

Command(INTL( 6167, "RETURN"))
INTL( 6168, "As thou wish.")
TELEPORT(680,2385,1)
BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 6169, "Begone.")
BREAK

Default
INTL( 6170, "Of course.")

EndTalk
}
