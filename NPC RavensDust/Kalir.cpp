//////////////////////////////////////////////////////////////////////
// Kalir.cpp: implementation of the Kalir class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Kalir.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Kalir::Kalir()
{}

Kalir::~Kalir()
{}

extern NPCstructure::NPC DesertNomad;

void Kalir::Create( ){
    npc = DesertNomad;
	SET_NPC_NAME( "[2960]Kalir" );
    npc.InitialPos.X = 276;
    npc.InitialPos.Y = 2518; 
	npc.InitialPos.world = 0;
}

MAKE_FUNC( GiveLetter )

IF (CheckItem(__OBJ_LETTER_TO_KALIR) >= 1) // If PC has a letter from Jamar...
	IF (CheckFlag(__QUEST_ROYAL_KEY5) >= 10) //...and was asked by Jamar to deliver it:
		Conversation
		INTL( 5308, " What?!? Jamar wrote back! Fantastic! *gasp* Now I know where we can meet again! "
		"Thank you for all the help! Hrmm. I think you wanted something from me "
		"before I've sent you on this errand... now... *gasp* What was it? Something "
		"about a key...? *pant*") 
		;int nNumLetters = CheckItem(__OBJ_LETTER_TO_KALIR); 
		FOR(0, nNumLetters )		
			TakeItem(__OBJ_LETTER_TO_KALIR)
		ENDFOR
		IF (CheckFlag(__QUEST_ROYAL_KEY5) == 10)
			GiveFlag(__QUEST_ROYAL_KEY5,11)
		ENDIF
	ELSE // If the letter was taken or stolen, but not given by Jamar:
		;int nNumLetters = CheckItem(__OBJ_LETTER_TO_KALIR); 
		FOR(0, nNumLetters )				
			TakeItem(__OBJ_LETTER_TO_KALIR)
		ENDFOR
		Conversation
		INTL( 5309, " Huh? A letter from Jamar? Thanks. You... didn't really get this from him, did you"
		"...? *gasp*")
	ENDIF
ELSE //  If the PC has no letter from Jamar, valid or not:
	Conversation
	INTL( 5310, " I wish he'd send me a letter to let me know he's fine.")
ENDIF

END_FUNC

void Kalir::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT LETTER_TO_JAMAR = 1;

InitTalk

Begin
INTL( 5311, "*pant*...Good day to you!")

Command(INTL( 3629, " NAME "))
INTL( 5312, "*huff* Forgive my... exhaustion. *puff* I am Kalir.")

Command(INTL( 1794, "ROYAL KEY"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY5) <= 10)
	Conversation
	INTL( 5313, "No, I'm sorry, I don't have such a key. I think you should ask my friend "
	"\"Jamar\".")
ELSE
	Conversation
	INTL( 5314, "I... *gasp* I'm really sorry for lying, really!! *pant* I... just didn't think "
	"you'd take my letter to him if I told you I had the key. But the truth is, I "
	"don't have the key anymore, I gave it to Morindin Arrowmist, as thanks for his "
	"help last time I got lost.")
	IF (CheckFlag(__QUEST_ROYAL_KEY5) == 11)
		GiveFlag(__QUEST_ROYAL_KEY5,12)
	ENDIF
ENDIF

Command(INTL( 554, "HELP"))
INTL( 5315, "If you would like to give me something, just type \"give\" \"<item name>\" and that should do it. "
"For instance, if you would like to give me, say, a letter, you should say \"give\" \"letter\".")

Command(INTL( 5262, "GIVE LETTER"))
""
CALL_FUNC( GiveLetter )

Command(INTL( 1999, "GIVE"))
INTL( 5316, "Give what?")

Command(INTL( 4142, "KALIR"))
INTL( 5317, "That is my name... yes.")

Command(INTL( 489, "WORK"))
INTL( 5318, "Well, \"Jamar\" has abandonned me *pant* as usual, so I am trying to catch up to "
"him. *gasp*")

Command(INTL( 5255, "JAMAR")) 
INTL( 5319, "He has... probably already made it *huff* into the \"town\".")
CALL_FUNC( GiveLetter )
IF ((CheckFlag(__QUEST_ROYAL_KEY5) == 8) OR (CheckFlag(__QUEST_ROYAL_KEY5) == 9))
	Conversation
	INTL( 5320, " If you see him, *gasp* could you give him a letter from me?")
	SetYesNo(LETTER_TO_JAMAR)
ENDIF

YES(LETTER_TO_JAMAR)
Conversation
INTL( 5321, "Ah!! Thank you *so* much!!! *gasp* I'm grateful beyond words! Just \"give\" \"letter\" "
"to him.")
IF (CheckFlag(__QUEST_ROYAL_KEY5) == 8)
	GiveFlag(__QUEST_ROYAL_KEY5, 9)
ENDIF
IF (CheckItem(__OBJ_LETTER_TO_JAMAR) >= 1)
	Conversation
	INTL( 5322, " But wait! *gasp* I see that you have one such letter already... *pant* Please "
	"give it to my friend Jamar as soon as possible. *gasp*")
ELSE
	GiveItem(__OBJ_LETTER_TO_JAMAR)
ENDIF

NO(LETTER_TO_JAMAR)
Conversation
INTL( 5323, "P...please reconsider...")
SetYesNo(LETTER_TO_JAMAR)

YesNoELSE(LETTER_TO_JAMAR)
Conversation
INTL( 5324, "It's the exhaustion... *huff* *puff* I must be going deaf... Say again?")
SetYesNo(LETTER_TO_JAMAR)

Command2(INTL( 1869, "TOWN"),INTL( 998, "SILVERSKY"))
INTL( 5325, "Why, yes *pant* the town of Silversky... *huff* *puff* you must have seen it already.")

Command(INTL( 1492, "DESERT"))
INTL( 5326, "The sun is very hot and bright here... *pant* *pant* It is dangerous just to sit around "
"if you are not adequately dressed. *puff*")

Command(INTL( 5266, "FRIEND"))
INTL( 5327, "Jamar would be a good friend... *gasp* if he didn't always leave me behind.")

Command(INTL( 3918, "VISITOR"))
INTL( 5328, "I doubt there are many people that wander into the desert *gasp* just for the pleasure "
"of it.")

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 1075, "Farewell.") BREAK

Default
INTL( 1755, "What?")

EndTalk

}
