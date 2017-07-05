//////////////////////////////////////////////////////////////////////
// IroualKnowall.cpp: implementation of the IroualKnowall class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "IroualKnowall.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IroualKnowall::IroualKnowall()
{}

IroualKnowall::~IroualKnowall()
{}

extern NPCstructure::NPC IroualKnowallNPC;

//Nom: Iroual Knowall.
//Statistique: Windhowl Paysan.
//Position: (2302, 625)
//World: 0
//Description: Innkeeper.
//Body: Innkeeper.

//////////////////////////////////////////////////////////////////////////////////////////
void IroualKnowall::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of IroualKnowall
//
{
	npc = IroualKnowallNPC;
	SET_NPC_NAME( "[3008]Iroual Knowall" );
	npc.InitialPos.X = 1784;
	npc.InitialPos.Y = 1233;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void IroualKnowall::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of IroualKnowall
//
{

CONSTANT KARMA = 1;

InitTalk

Begin
INTL( 2359, "Aye, what can I do for ya?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2360, "I am Iroual Knowall and I know just about everything there is to know about "
"\"drinks\", my friend!")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2361, "I am the barman and innkeeper of the Drunken Dragon's Inn. It's a very fine "
"tavern, to say the least. I've been its owner for more than twenty years "
"now! But where are my manners? Would you like a \"drink\"? We've got the "
"very best ale in the whole town!")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2362, "Balork cursed you, you say? I'm sorry to hear that. If \"Annabelle\" the "
"Blessed One was still here, she might be able to help you. But she's long "
"gone, now. I hear a troll took her away to feast upon her.") 

Command(INTL( 523, "ANNABELLE"))
INTL( 2363, "Oh, I don't know for sure if she's dead or alive, but she left us to find "
"her true love years ago... Some say she lives with a troll, now. Me? I "
"just think it's hogwash and she died.")

Command(INTL( 2364, "ALE"))
INTL( 2365, "It's the best I tell ya!")

Command(INTL( 1886, "KARMA"))
INTL( 7225, "For 100 GP, I'll tell you about your karma. That comes with a good meal, so it's "
"not a total waste. Will you pay?")
SetYesNo(KARMA)

YES(KARMA)
Conversation
INTL( 7226, "Glad to hear it... ")
IF (Gold >= 100)
	TakeGold(100)
	IF (USER_KARMA>=400)
		Conversation
		INTL( 7211, "As I understand it, you're a Pure. That's as good as you're likely to get, I'd say. Congrats!")
	ELSEIF (USER_KARMA>=300)
		Conversation
		INTL( 7212, "You're a Blessed, which isn't at the top, but pretty darn close. Good work! Next stop: becoming a Pure.")
	ELSEIF (USER_KARMA>=200)
		Conversation
		INTL( 7227, "I hear you're Redeemed, which means you've accomplished a great deal of good deeds, but "
		"there's still room for improvement. Keep this up and you'll become a Blessed.")
	ELSEIF (USER_KARMA>=100)
		Conversation
		INTL( 7228, "You're a Good person, which is more than I can say about half the population of this island. Don't give up, "
		"you're on the right path to become a Redeemed.")
	ELSEIF (USER_KARMA>-100)
		Conversation
		INTL( 7229, "You're essentially unaligned, right between Good and Evil. You'll have to work harder one way or the other "
		"to answer your true calling.")
	ELSEIF( USER_KARMA <= -400 )
		Conversation
		INTL( 7230, "Anyone can see you're a Bane. That's as evil as you're likely to get. I'm not sure congratulations are in "
		"order, so if you'll excuse me, I've got other customers to attend.")
	ELSEIF (USER_KARMA<=-300)
		Conversation
		INTL( 7231, "Well, what do you know, you're a Cursed! We don't like your kind much around here, but at least you haven't "
		"fallen to the level of Impure yet. There's still hope for you.")
	ELSEIF (USER_KARMA<=-200)
		Conversation
		INTL( 7232, "You're Malignant, and that's no way to go, if you ask me. Keep this up and you'll become a Cursed. You should "
		"consider the path of good, my friend. Evil begets evil, and nothing good can come of that.")
	ELSEIF (USER_KARMA<=-100)
		Conversation
		INTL( 7233, "You're Evil, plain and simple, but you haven't become Malignant yet. There's still time for you to turn to good. "
		"At least I think so.")
	ELSE
		Conversation
		INTL( 7220, "I'm... not sure *what* you are, sorry...")
	ENDIF
ELSE
	Conversation
	INTL( 7234, "I'm afraid you don't have enough gold on you. Please come again.")
ENDIF

NO(KARMA)
Conversation
INTL( 7235, "That's too bad, I've got all this food prepared and no patrons to eat it. I wish you would reconsider.")

YesNoELSE(KARMA)
Conversation
INTL( 7236, "I'd be happy with a simple \"yes\" or \"no\", you know?")
SetYesNo(KARMA)

Command(INTL( 1346, "DRINK"))
INTL( 2366, "Here at the Drunken Dragon's Inn, we have the best ale in all of \"Goldmoon\". "
"The king himself gets his supplies from here! ")

Command(INTL( 753, "GOLDMOON"))
INTL( 3632, "Are you some kind of traveler? if you want to know about Goldmoon, just ask "
"people about it. I don't have time to answer questions now.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 973, "Goodbye.") BREAK

Default
INTL( 2368, "Well, I'm sorry to say that I've never heard about that drink.")

EndTalk

}
