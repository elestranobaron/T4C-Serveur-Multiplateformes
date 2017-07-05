//////////////////////////////////////////////////////////////////////
// Tobias.cpp: implementation of the Tobias class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Tobias.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Tobias::Tobias()
{}

Tobias::~Tobias()
{}

extern NPCstructure::NPC Scribe;

void Tobias::Create( ){
    npc = Scribe;
	SET_NPC_NAME( "[2990]Tobias" );
    npc.InitialPos.X = 1394;//2863;//1343; // NEED A POSITION FOR THIS NPC!!!!!
    npc.InitialPos.Y = 2339;//198;//2374; // NEED A POSITION FOR THIS NPC!!!!!
	npc.InitialPos.world = 0;//4;//0;
}

void Tobias::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT BOOK = 1;
CONSTANT BOOK_OF_WARFARE = 2;

InitTalk

Begin
INTL( 5889, "Welcome to my humble abode. How may I be of service?")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5890, "I am known as \"Tobias\" \"Ander\".")

Command(INTL( 5891, "TOBIAS"))
INTL( 5892, "That's right, Tobias is my name.")

Command(INTL( 5893, "ANDER"))
INTL( 5894, "You know it's quite rude to call someone by their last name!")

Command2(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"))
INTL( 5895, "I travel the world in search of \"books\" to add to my \"collection\".")

Command(INTL( 5896, "COLLECTION"))
INTL( 5897, "You are interested in seeing my collection? Well, feel free to look around. "
"Oh, and don't forget to have a look at the incredible \"Book\" \"of\" \"Warfare\" "
", a favorite of mine.")

Command(INTL( 1794, "ROYAL KEY"))
INTL( 5898, "Oh, yes, indeed, I had one such key a long time ago. Got it from a noble destitute "
"whose name I can't recall--was it Sir Gothar? I can never remember. Anyway, I kept "
"that lovely key for a few years, until Celestina Waterbreeze traded it for a Book "
"of Feylor. You should probably ask her.")
IF (CheckFlag(__QUEST_ROYAL_KEY6) == 0)
	GiveFlag(__QUEST_ROYAL_KEY6,1)
ENDIF

Command(INTL( 3908, "BOOK OF WARFARE"))
INTL( 5899, "I do indeed have such a book, in fact, I have several copies of it. I sometimes sell "
"them for 15,000 gold pieces. Would you care to purchase one?")
SetYesNo(BOOK_OF_WARFARE)

YES(BOOK_OF_WARFARE)
IF (Gold >= 15000)
	TakeGold(15000)
	GiveItem(__OBJ_BOOK_OF_WARFARE)
	Conversation
	INTL( 5900, "It's a pleasure doing business with you! Here's your book.")
ELSE
	Conversation
	INTL( 5901, "It's too bad you don't have that kind of money!")
ENDIF

NO(BOOK_OF_WARFARE)
Conversation
INTL( 5902, "That's fine by me.")

YesNoELSE(BOOK_OF_WARFARE)
Conversation
INTL( 5903, "I didn't get that. What did you say, yes or no?")
SetYesNo(BOOK_OF_WARFARE)

Command(INTL( 5279, "BOOKS"))
INTL( 5904, "You would be surprised at the amount of books that exist around the world.")

Command(INTL( 1427, "BOOK"))
INTL( 5905, "Is there a particular book that you are looking for?")
SetYesNo(BOOK)

YES(BOOK)
Conversation
INTL( 5906, "Hmm, what book would that be?")

NO(BOOK)
Conversation
INTL( 5907, "I see, well if there is nothing else, I will return to my reading if you please.")

YesNoELSE(BOOK)
Conversation
INTL( 5908, "Unfortunately, I have not yet learned to speak gibberish.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 5909, "Farewell then.") BREAK

Default
INTL( 5910, "What was that you said?")

EndTalk

}
