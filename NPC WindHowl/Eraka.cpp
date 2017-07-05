//////////////////////////////////////////////////////////////////////
// Eraka.cpp: implementation of the Eraka class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Eraka.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Eraka::Eraka()
{}

Eraka::~Eraka()
{}

extern NPCstructure::NPC Guard_Two;

//////////////////////////////////////////////////////////////////////////////////////////
void Eraka::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Eraka
//
{
    npc = Guard_Two;
    SET_NPC_NAME( "[3001]Eraka" );
    npc.InitialPos.X = 1802;
    npc.InitialPos.Y = 1257;
    npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Eraka::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Eraka
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
	INTL( 2282, "Ugh... Ow!") 
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2283, "I am Eraka...")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2284, "I am a guard of this town, but I was injured in battle.")
	  
Command(INTL( 523, "ANNABELLE"))
INTL( 665, "I heard a rumor that she is much older than what she appears to be.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2670, "Balork's Brand? Huh?")

Command(INTL( 541, "JARKO"))
INTL( 2805, "He is the necromancer who lives somewhere in the northern mountains.")

Command(INTL( 599, "SUNROCK"))
INTL( 2810, "Sunrock is currently the Lord of \"Windhowl\".")

Command(INTL( 565, "BRIGAND"))
INTL( 2811, "Why should I know anything about them?")

Command2(INTL( 2812, " ORC "),INTL( 2813, " ORCS "))
INTL( 2814, "I do not like orcs.")

Command(INTL( 746, "DRUID"))
INTL( 2815, "The druidic camp is located to the northeast of the island.")

Command(INTL( 514, "WINDHOWL"))
INTL( 2816, "Windhowl is the name of this town.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 2817, "Lighthaven is our sister town. It's located on the eastern part of the "
"island.")

Command2(INTL( 755, "ISLAND"),INTL( 2818, "ARAKA"))
INTL( 2819, "Yes, the name of this island is Arakas.")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 2820, "That's the name of the island somewhere to the south. I don't know any "
"way to reach it. That island is also part of the kingdom of \"Goldmoon\".")

Command(INTL( 753, "GOLDMOON"))
INTL( 2821, "The kingdom of Goldmoon regroups both Raven's Dust and Arakas. It is "
"currently under the rulership of \"King\" \"Theodore\" \"XIII\".") 

Command2(INTL( 1072, "KING"),INTL( 754, "THEODORE"))
INTL( 2822, "Why hasn't he sent any reinforcements here yet?")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 973, "Goodbye.") BREAK

Default
INTL( 962, "Ask someone else.")

EndTalk
}
