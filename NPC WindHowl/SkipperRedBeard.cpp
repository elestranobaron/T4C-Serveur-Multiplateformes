//////////////////////////////////////////////////////////////////////
// SkipperRedBeard.cpp: implementation of the SkipperRedBeard class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "SkipperRedBeard.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SkipperRedBeard::SkipperRedBeard()
{}

SkipperRedBeard::~SkipperRedBeard()
{}

extern NPCstructure::NPC SailorRedBeard;

//Nom: Skipper Red Beard.
//Statistique: Windhowl Sailor.
//Position: (2088, 618) at the docks
//World: 0
//Description: Sailor.
//Body: Sailor.
//OnAttacked: "ARGH! FFIGHHHTT!!!!!! AAAARRRRRRRRGGHHHH!!!! KHHIIIIILLLLLLLLL"

//////////////////////////////////////////////////////////////////////////////////////////
void SkipperRedBeard::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of SkipperRedBeard
//
{
	npc = SailorRedBeard;
	SET_NPC_NAME( "[3023]Skipper Red Beard" );
	npc.InitialPos.X = 1570;
	npc.InitialPos.Y = 1226;
	npc.InitialPos.world = 0;  
}

//////////////////////////////////////////////////////////////////////////////////////////
void SkipperRedBeard::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of SkipperRedBeard
//
{

InitTalk

Begin
INTL( 2700, "Hardy har! Step right up, hardy fella!")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2701, "Har! I am Red Beard, pleased to meet you.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2702, "I work for \"Harock\" Harr. I take care of the ship when he's gone drinking "
"or when he goes out at sea.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2703, "Balork's curse? Har!! That's horrible!")

Command(INTL( 523, "ANNABELLE"))
INTL( 2704, "Har! I've heard of this lady, but never saw her myself. Har! Har!")

Command(INTL( 2705, "HAROCK"))
INTL( 2706, "Hardy har! He's quite a strong fella! He's the greatest sailor of all "
"time, just ask him about stories, and he'll tell you quite a few about "
"his old days. Har! He taught me all I know about sailing!")

Command(INTL( 2707, "PIRATE"))
INTL( 2708, "There aren't many left these days. Must have all gone to the \"Lost\" \"Islands\".")

Command(INTL( 2709, "LOST ISLAND"))
INTL( 2710, "It is said that there is nothing on those islands. But I was just wondering "
"if it's a trick, har! Could make a good hiding place with all the fog "
"around them.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 973, "Goodbye.") BREAK

Default
INTL( 2711, "I'm telling ya, you don't wanna hear about it.")

EndTalk

}
