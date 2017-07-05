//////////////////////////////////////////////////////////////////////
// Drunk.cpp: implementation of the Drunk class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Drunk.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Drunk::Drunk()
{}

Drunk::~Drunk()
{}

extern NPCstructure::NPC DrunkNPC;

//Nom: Drunk.
//Statistique: Drunk.
//Position: (2286, 625)
//World: 0
//Description: Smiling man.
//Body: Drunk.

//////////////////////////////////////////////////////////////////////////////////////////
void Drunk::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Drunk
//
{
    npc = DrunkNPC;
	SET_NPC_NAME( "[3000]A happy fellow" );
    npc.InitialPos.X = 1768;
    npc.InitialPos.Y = 1233;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Drunk::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Drunk
//
{
CONSTANT DONATION = 1

InitTalk

Begin
INTL( 2257, "... *Hic* *Hic*... *buuurrp* *snort* Yeah? Whaddaya want?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2258, "*hic* I am R*snort* g*Buuurrp*!")

Command(INTL( 523, "ANNABELLE"))
INTL( 2259, "She wants to *hic* give me a beer, I hope? *snort*")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2260, "*hic* Another beeerr... *snort*")

Command(INTL( 2261, "MONEY"))
""
IF(CheckFlag(__GAVE_MONEY_TO_DRUNK) < 10 AND Gold>=100)
	Conversation
	INTL( 2262, "Eeh? *hic* Wanna make a *gurgle* donation? A hundred gold pieces *hic* "
	"would be fine... Can you shpare that much?")
	SetYesNo(DONATION)
ELSE
	INTL( 2263, "Lemme sleep, I had too much to drink... *burp*") BREAK	
ENDIF

YES(DONATION)
	Conversation
	INTL( 2264, "Sh'great! Thanks, friend... *hic*")
	TakeGold(100)
	IF (USER_KARMA <= (100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
		GiveKarma(5*(500-USER_KARMA)/500)
	ENDIF
	GiveFlag(__GAVE_MONEY_TO_DRUNK,CheckFlag(__GAVE_MONEY_TO_DRUNK)+1)
NO(DONATION)
	Conversation
	INTL( 2265, "Ah... *hic* Sh'too bad... *hic*")
YesNoELSE(DONATION)
	Conversation
	INTL( 2266, "Eh? *belch* What was dat?")
	SetYesNo(DONATION)

Command(INTL( 1350, "RUMOR"))
INTL( 2267, "*Hic* I know some things... Just give me gold and the more you give me... "
"the more I talk... *snort*")

ParamCmd(INTL( 2268, "GIVE $ GOLD"))
""
;int nGiveGold = NUM_PARAM( 0 );
IF (nGiveGold < 1 )
	Conversation
	INTL( 2269, "Ah... *hic* T-that's not right...")
ELSEIF (nGiveGold != 0 )
	IF (Gold >= nGiveGold )
		TakeGold( nGiveGold ) 
		Conversation
		INTL( 2270, "Thank you! You're... *burp* much too kind...")
		IF (nGiveGold <= 100)
			Conversation
			INTL( 2271, "Hmph... *hic* For that kind of money... I'll tell you "
			"that it's gonna rain tomorrow... *hiccup*.")
		ELSEIF (nGiveGold <= 250)
			Conversation
			INTL( 2272, "That isn't much... but... *burp* I guess it's worth a little tip... "
			"Careful what quests you undertake, they may prevent you from doing "
			"some other quests later on.")
		ELSEIF (nGiveGold <= 1000)
			Conversation
			INTL( 2273, "Many thanks... If you're high enough level, perhapsh Darkfang will "
			"be able to tell you a little shomething... *hiccup* about your karma.")
		ELSEIF (nGiveGold <= 2000)
			Conversation
			INTL( 2274, "People like you are rare... You should know that if you ever sheek... "
			"a weapon, a glum sword, that it doesn't exist... It'sh probably... *burp* "
			"a Gloomblade... Hard to find...")
		ELSE
			Conversation
			INTL( 2275, "Perhapsh you'll want to look into the story of the Seraphs... *hiccup* "
			"A shobering shtory if I ever heard one...")		
		ENDIF
	ELSE
		Conversation
		INTL( 2277, "Heh! *hiccup* You're just like me... stranger... trying to spend"
		"gold you don't have... *hic*")
	ENDIF
ELSE
	Conversation
	INTL( 2278, "To gimme gold, type \"give\" \"<x>\" \"gold\", where x ish the amount of "
	"gold pieces you wanna give. *hic*")
ENDIF

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2279, "Work? *Hic* My job is to empty the tavern's beer mugs! Now get out of my "
"way, I need another *hic* *snort* beer! I alsho know shome \"rumors\", if "
"you can shpare shome gold pieces...")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2280, "*hic*") BREAK

Default
INTL( 2281, "Go away!")

EndTalk

}
