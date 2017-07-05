// LordTravis.cpp: implementation of the LordTravis class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "LordTravis.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LordTravis::LordTravis()
{}

LordTravis::~LordTravis()
{}

extern NPCstructure::NPC Nobleman;

//////////////////////////////////////////////////////////////////////////////////////////
void LordTravis::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of LordTravis
//
{
	npc = Nobleman;
	SET_NPC_NAME( "[3014]Lord Travis" );
	npc.InitialPos.X = 1787;
	npc.InitialPos.Y = 1301;
	npc.InitialPos.world = 0;    
}

//////////////////////////////////////////////////////////////////////////////////////////
void LordTravis::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of LordTravis
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
	INTL( 2535, "Yes?")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2536, "I am Travis, Lieutenant of the guard and renowned knight of Windhowl!")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2537, "I am lieutenant of Windhowl's guard. I have the task, no, the obligation "
"of keeping the town peaceful for all of its citizens. And might I say "
"that it has become an \"overwhelming\" task lately.")

Command(INTL( 523, "ANNABELLE"))
INTL( 1158, "I do not know much about that woman.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2538, "Balork's Brand? What is that?")

Command(INTL( 2539, "OVERWHELMING"))
INTL( 2540, "Goblins must get reinforcements from somewhere or help from some outsider, "
"because they are better equipped than ever and come in ever-increasing numbers. "
"Luckily, they are still no match for the skill of our guards.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 973, "Goodbye.") BREAK

Default
INTL( 962, "Ask someone else.")

EndTalk

}
