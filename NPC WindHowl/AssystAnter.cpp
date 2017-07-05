//////////////////////////////////////////////////////////////////////
// AssystAnter.cpp: implementation of the AssystAnter class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "AssystAnter.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AssystAnter::AssystAnter()
{}

AssystAnter::~AssystAnter()
{}

extern NPCstructure::NPC Nobleman;

//Nom: Assyst Anter.
//Statistique: Windhowl noble.
//Position: (2151, 583)
//World: 0
//Description: Busy man.
//Body: Paysan.

//////////////////////////////////////////////////////////////////////////////////////////
void AssystAnter::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of AssystAnter
//
{
	npc = Nobleman;
	SET_NPC_NAME( "[2995]Assyst Anter" );
	npc.InitialPos.X = 1639;
	npc.InitialPos.Y = 1191;
	npc.InitialPos.world = 0;	
}

//////////////////////////////////////////////////////////////////////////////////////////
void AssystAnter::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of AssystAnter
//
{
InitTalk

Begin
INTL( 2178, "Yes? Can I help you?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2179, "I am Assyst Anter, greetings to you from our great town.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2180, "I am in charge of keeping \"count\" of our soldiers. I also tend to the needs "
"of our army by ordering weapons, armor and anything else our guards might "
"need to accomplish their work.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 583, "Balork's Brand? Uh?")

Command(INTL( 523, "ANNABELLE"))
INTL( 7204, "I heard she is much older than what she appears to be.")

Command(INTL( 2181, "COUNT"))
INTL( 2182, "I must say, it has decreased drastically. Moreover, some pirates have "
"tried to rob our port. *sigh* I fear we will have more enemies to deal with "
"in the near future. Fortunately, we still have some great warriors like "
"\"Guntertag\" or \"George\" the IIIrd to repel invasions.")

Command(INTL( 2183, "GUNTERTAG"))
INTL( 2184, "I doubt even a goblin army would be able to defeat such a powerful man. "
"I tell you, he's very dumb and his brain is probably as thick as his "
"biceps, but what a great warrior he is! He once vanquished thirty goblins "
"all by himself and he was still shouting for more. If only his brother, "
"Murmuntag, would come live here instead of Lighthaven.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 2185, "It's the other town on the island, probably the one where you come from, I'll "
"wager.")

Command(INTL( 2186, "GEORGE"))
INTL( 2187, "George the IIIrd is one intelligent guy. After all, he isn't "
"captain of the guards for nothing, you know. He doesn't fight with the "
"brutality that is Guntertag's pride and joy, but he is so skilled that he "
"can defeat just about anyone in a fair duel.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2188, "May luck be with you in your travels.") BREAK

Default
INTL( 2189, "I do not know what you're talking about.")

EndTalk

}
