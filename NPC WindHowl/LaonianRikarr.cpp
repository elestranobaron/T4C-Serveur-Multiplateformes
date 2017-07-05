//////////////////////////////////////////////////////////////////////
// LaonianRikarr.cpp: implementation of the LaonianRikarr class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "LaonianRikarr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LaonianRikarr::LaonianRikarr()
{}

LaonianRikarr::~LaonianRikarr()
{}
 
extern NPCstructure::NPC LaonianRikarrNPC;

//Nom: Laonian Rikarr.
//Statistique: Windhowl Priest.
//Position: (2223, 550)
//World: 0
//Description: High ranked priest.
//Body: Priest.

//////////////////////////////////////////////////////////////////////////////////////////
void LaonianRikarr::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of LaonianRikarr
//
{
	npc = LaonianRikarrNPC;
	SET_NPC_NAME( "[3011]Laonian Rikarr" );
	npc.InitialPos.X = 1705;
	npc.InitialPos.Y = 1158;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void LaonianRikarr::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of LaonianRikarr
//
{

InitTalk

Begin
INTL( 2402, "Greetings to you.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2403, "I am Laonian Rikarr. Pleased to make your acquaintance.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2404, "I am a Bishop of \"Artherk\".")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2405, "Curse that Balork and his Brand! There are many like you who walk the land "
"and bear his mark. I tell you, friend, you have to seek Annabelle, blessed be "
"her eyes! She'll know what to do.")

Command(INTL( 523, "ANNABELLE"))
INTL( 2406, "I wonder where she lives nowadays.")

Command(INTL( 1243, "ARTHERK"))
INTL( 2407, "Artherk is the god I worship, and the path he has set forth for me is "
"undoubtedly a great one. I hope your destiny will be as good as mine, "
"stranger. If you are in need of healing, you should ask Jurnis.")

Command(INTL( 569, "HEAL"))
INTL( 2408, "I am rather busy at the moment, but I am sure Jurnis would have time for you.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2409, "Come back when you are in need of help.") BREAK

Default
INTL( 2220, "Only Artherk could help you.")

EndTalk

}
