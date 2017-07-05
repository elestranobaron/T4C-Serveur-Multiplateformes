//////////////////////////////////////////////////////////////////////
// Guardman.cpp: implementation of the Guardman class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Guardman.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Guardman::Guardman()
{}

Guardman::~Guardman()
{}

extern NPCstructure::NPC Guard_One;


void Guardman::Create(){
    npc = Guard_One;
	SET_NPC_NAME( "[3038]A guardsman" );
    npc.InitialPos.X = 2865;
    npc.InitialPos.Y = 1076;
	npc.InitialPos.world = 0;
}

void Guardman::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
INTL( 11751, "You had best stay out of sight from Olin Haad's guards if you don't want any trouble, citizen.")

Command(INTL( 1329, "YES"))    
INTL( 1330, "I am sorry to hear that. We do our best to please everybody, "
"but it is not an easy task. Now, if you'll excuse me, I have to get back "
"to work.")  

Command(INTL( 1331, "NO"))    
INTL( 1332, "I am pleased to see that you're satisfied. Have a nice day.") BREAK

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1333, "I don't have time for endless chit-chat, I've got work to do.") BREAK

Command3(INTL( 510, "BRAND"),INTL( 509, "BALORK"),INTL( 582, "BALORK'S CURSE"))
INTL( 1334, "I don't know anything about that. Leave me alone, I have a job to do.") BREAK

Command(INTL( 523, "ANNABELLE"))
INTL( 1335, "I don't know her. Now if you'll excuse me...") BREAK

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1336, "I am a guard of Lighthaven's militia. Pardon my rudeness, but I must return "
"to my duties.") BREAK

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 1337, "Not while I'm on duty.")
BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 1338, "Have a good day.") BREAK

Default
INTL( 1339, "I'm only a guard.")

EndTalk

}
