//////////////////////////////////////////////////////////////////////
// GeorgeTheIIIrd.cpp: implementation of the GeorgeTheIIIrd class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "GeorgeTheIIIrd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GeorgeTheIIIrd::GeorgeTheIIIrd()
{}

GeorgeTheIIIrd::~GeorgeTheIIIrd()
{}

extern NPCstructure::NPC Guard_One;

//////////////////////////////////////////////////////////////////////////////////////////
void GeorgeTheIIIrd::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of GeorgeTheIIIrd
//
{
	npc = Guard_One;
	SET_NPC_NAME( "[3003]George the third" );
	npc.InitialPos.X = 1811;
	npc.InitialPos.Y = 1263;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void GeorgeTheIIIrd::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of GeorgeTheIIIrd
//
{
InitTalk

Begin
""
IF (CheckFlag(__QUEST_USER_IS_A_TRAITOR) >= 3) 
	Conversation
	INTL( 7159, "We do not tolerate your kind here!")
	FIGHT 
ELSE
	Conversation
	INTL( 2306, "How do you do?")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2307, "Why, surely you must be an outsider to not be familiar with my name. I am "
"known as George the third, son of George the second.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2308, "I am the renowned captain of the guards. I protect the citizens of Goldmoon, "
"which, I would like to point out, has never fallen to an invasion. Not even "
"those damned \"goblins\" can breach the walls of this city.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2309, "Balork cursed you, you say? I'm sorry to hear that. If \"Annabelle\" the "
"Blessed One was still here, she might be able to help you. But she's long "
"gone, now. I hear a troll took her away to feast upon her.") 

Command(INTL( 523, "ANNABELLE"))
INTL( 2310, "I heard that she has elven blood running in her veins. Methinks it is untrue "
"because we all know that Elves have been wiped out a long time ago. Or "
"were they?") 

Command(INTL( 539, "GOBLIN"))
INTL( 2311, "Tough little brutes they've become lately, but still not even close to being "
"a match for me or my well-trained army. Rest assured, as long as I, George "
"the IIIrd, am captain of the guard, the goblins have no chance of invading "
"our proud town.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 973, "Goodbye.") BREAK

Default
INTL( 2312, "I knew you would ask.")

EndTalk

}
