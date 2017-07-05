//////////////////////////////////////////////////////////////////////
// Belagan.cpp: implementation of the Belagan class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Belagan.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Belagan::Belagan()
{}

Belagan::~Belagan()
{}
 
extern NPCstructure::NPC BelaganNPC;

void Belagan::Create( ){
    npc = BelaganNPC;
	SET_NPC_NAME( "[2918]Belagan" );
    npc.InitialPos.X = 1598;
    npc.InitialPos.Y = 2539;
	npc.InitialPos.world = 0;
}

void Belagan::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT FAVOR = 1;

InitTalk

Begin
INTL( 4209, "Welcome!")
	
Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 4210, "I am Belagan, \"Adriana\"'s assistant.")

Command(INTL( 3903, "BELAGAN"))
INTL( 4211, "That is correct.")

Command2(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"))
INTL( 4212, "I help Adriana with the chores around the house. In exchange, she lets me stay for free. ")

Command(INTL( 3880, "ADRIANA"))
INTL( 4213, "Adriana is the mistress here. She is often too busy \"training\" adventurers in the art of war, "
"so I take care of the everyday tasks, such as \"cleaning\" and \"cooking\".")

Command(INTL( 4214, "TRAINING"))
INTL( 4215, "Just like I said, Adriana takes care of that. If you seek to improve your skills or learn "
"new ones, go seek her out.")

Command2(INTL( 3905, "REYNEN"),INTL( 3906, "ASPICDART"))
""
SWITCH(CheckFlag(__QUEST_ROYAL_KEY1))
	CASE(0) // Hasn't talked to Celydia yet...
		Conversation
		INTL( 4216, "I'm sorry, I'm a little busy right now...")
	ENDCASE
	CASE(1) // Has talked to Celydia...
		Conversation
		INTL( 4217, "I... can't really talk much about it, in case Mistress Adriana finds out. She gets "
		"very upset when someone mentions his name. Perhaps if you'll do me a favor, it'll be "
		"worth my while to talk to you. Would you do that?")
		SetYesNo(FAVOR)
	ENDCASE
	CASE(2) // Has received but not completed Book of Warfare Quest.
		Conversation
		INTL( 4218, "Please bring me the book I asked for first, and I'll tell you everything.")
	ENDCASE
	CASE(3) // Brought the Book back.
		Conversation
		INTL( 4219, "Ah, yes, about Aspicdart... Well, there was an affair between him and my mistress, "
		"a few years ago, and it ended pretty sourly. I know she considered going after him "
		"when she learned he had gone to the \"Cave\" \"of\" \"Illusions\", but her work here was enough "
		"to keep her from going... barely.")
		GiveFlag(__QUEST_ROYAL_KEY1,4)
	ENDCASE
	CASE(4) // Already knows about Aspicdart.
		Conversation
		INTL( 4220, "I've told you all I know about him. Now seek him in the Cave of Illusions, wherever "
		"that may be.")
	ENDCASE
	OTHERWISE // Has already gone way past this point in the quest.
		Conversation
		INTL( 4221, "I think I've talked about him enough.")
	ENDCASE
ENDSWITCH

YES(FAVOR)
Conversation
INTL( 4222, "Very well... I would like to some day impress my mistress with my knowledge of tactics, "
"so she notices me as more than just a cook, but I can't find any books to help me. If "
"you could seek a copy of \"Kerthew's\" \"Book\" \"of\" \"Warfare\", I would be eternally grateful.")
IF (CheckFlag(__QUEST_ROYAL_KEY1) == 1)
	GiveFlag(__QUEST_ROYAL_KEY1,2)
ENDIF

NO(FAVOR)
Conversation
INTL( 4223, "So be it.")

YesNoELSE(FAVOR)
Conversation
INTL( 2422, "Huh?")

Command(INTL( 4224, "CAVE OF ILLUSION"))
INTL( 4225, "I guess it's a cave where there are many illusions. I don't know where that would be, sorry.")

Command2(INTL( 4002, "ELYSANA"),INTL( 4003, "BLACKROSE"))
INTL( 4226, "I have nothing to say about that poison-brewing witch.")

Command(INTL( 3908, "BOOK OF WARFARE"))
INTL( 4227, "It is a book that teaches the finer points of the art of war. It is extremely rare and valuable.")
IF ((CheckItem(__OBJ_BOOK_OF_WARFARE) >= 1) && (CheckFlag(__QUEST_ROYAL_KEY1) == 2))
	Conversation
	INTL( 4228, " Oh, you've brought me a copy? Thank you so much!")
	TakeItem(__OBJ_BOOK_OF_WARFARE)
	GiveFlag(__QUEST_ROYAL_KEY1,3)
ELSE
	Conversation
	INTL( 4229, " I would LOVE to get a copy of it, but there are so few available... A collector's "
	"item! I'm sure Adriana wouldn't mind a copy either.")
ENDIF

Command(INTL( 4230, "CLEAN"))
INTL( 4231, "I don't mind the work, since I do get to spend some time with Adriana, and I don't have to "
"pay for my room.")

Command(INTL( 3916, "COOK"))
INTL( 4232, "Ahhh, now that I enjoy doing. I can practice my cooking skills and eventually maybe open my "
"own tavern or something like it.")

Command(INTL( 4233, "TAVERN"))
INTL( 4234, "Alas, right now it is but a dream.")

Command(INTL( 3918, "VISITOR"))
""
IF (CheckFlag(__QUEST_VISITOR_SPOTTED) == 0)
	IF (CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 2)
		Conversation
		INTL( 4235, "I do not recall seeing anyone out of the ordinary, but I could be wrong.")
		GiveFlag(__QUEST_VISITOR_SPOTTED, 1)
	ELSE
		Conversation
		INTL( 4236, "I do not recall seeing anyone out of the ordinary.")
	ENDIF
ELSEIF (CheckFlag(__QUEST_VISITOR_SPOTTED) == 1)
	Conversation
	INTL( 4237, "Hmm, come to think of it, I have seen a rather strange person recently. I believe he was walking "
	"in the direction of Nafuhr's shop.")
	GiveFlag(__QUEST_VISITOR_SPOTTED, 2)
ELSEIF (CheckFlag(__QUEST_VISITOR_SPOTTED) >= 2)
	Conversation
	INTL( 4238, "I told you before, the man you look for was headed towards Nafuhr's shop.")
ENDIF

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 973, "Goodbye.")
BREAK

Default
INTL( 4239, "Please, be brief. I must get back to my chores.")

EndTalk

}
