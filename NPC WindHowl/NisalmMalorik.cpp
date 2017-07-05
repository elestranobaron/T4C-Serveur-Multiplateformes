//////////////////////////////////////////////////////////////////////
// NisalmMalorik.cpp: implementation of the NisalmMalorik class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "NisalmMalorik.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NisalmMalorik::NisalmMalorik()
{}

NisalmMalorik::~NisalmMalorik()
{}

extern NPCstructure::NPC Nobleman;

//Nom: Nisalm Malorik.
//Statistique: Windhowl noble.
//Position: (2139, 567)
//World: 0
//Description: Working man.
//Body: Paysan.

//////////////////////////////////////////////////////////////////////////////////////////
void NisalmMalorik::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of NisalmMalorik
//
{
	npc = Nobleman;
	SET_NPC_NAME( "[3020]Nisalm Malorik" );
	npc.InitialPos.X = 1621;
	npc.InitialPos.Y = 1175;
	npc.InitialPos.world = 0;  
}

//////////////////////////////////////////////////////////////////////////////////////////
void NisalmMalorik::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of NisalmMalorik
//
{

InitTalk

Begin
INTL( 2661, "Hi! Our great town welcomes you, traveller!")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2662, "I am Nisalm Malorik. Please, do call me Niss, it's what all my friends "
"call me.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2663, "I am an assistant here, at Lord Sunrock's office. I am in charge of "
"the citizens' demands. I also keep track of everything that's happening "
"in town. Unfortunately, that is \"confidential\" information, as per Lord Sunrock's "
"orders.")

Command(INTL( 523, "ANNABELLE"))
INTL( 2664, "I heard that she has elven blood running in her veins. Methinks it is untrue "
"because we all know that Elves have been wiped out a long time ago. Or "
"were they?") 

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2670, "Balork's Brand? Huh?")

Command(INTL( 2665, "CONFIDENTIAL"))
INTL( 2666, "Do not forget that our town is waging a fierce war against the goblins. Many "
"unscrupulous fools would sell information about our town for a goodly "
"price. So we have to keep some information under a seal of secrecy.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 1338, "Have a good day.") BREAK

Default
INTL( 1755, "What?")

EndTalk

}
