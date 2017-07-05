//////////////////////////////////////////////////////////////////////
// WindHowl_Guard.cpp: implementation of the WindHowl_Guard class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "WindHowl_Guard.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WindHowl_Guard::WindHowl_Guard()
{}

WindHowl_Guard::~WindHowl_Guard()
{}

extern NPCstructure::NPC Guard_Three;


//Nom: GUARDS.
//Statistique: Windhowl Guard.
//Position: (Anywhere)
//World: 0
//Description: Fully armored guard.
//Body: Guard.

//////////////////////////////////////////////////////////////////////////////////////////
void WindHowl_Guard::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of WindHowl_Guard
//
{
	npc = Guard_Three;
	SET_NPC_NAME( "[3026]A guard" );
	npc.InitialPos.X = 1752;
	npc.InitialPos.Y = 1238;
	npc.InitialPos.world = 0;  
}

//////////////////////////////////////////////////////////////////////////////////////////
void WindHowl_Guard::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of WindHowl_Guard
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
	INTL( 2751, "I'm sorry but I don't have much time for talking.")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2752, "I do not have time to talk with you.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2753, "I patrol this town to prevent fights among the citizens.")

Command(INTL( 523, "ANNABELLE"))
INTL( 2754, "I do not have time to talk about women.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2755, "It does not concern me.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 973, "Goodbye.") BREAK

Default
INTL( 2756, "I'm going to have to ask you to leave.") BREAK

EndTalk

}
