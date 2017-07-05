//////////////////////////////////////////////////////////////////////
// BoroarTheKnight.cpp: implementation of the BoroarTheKnight class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "BoroarTheKnight.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BoroarTheKnight::BoroarTheKnight()
{}

BoroarTheKnight::~BoroarTheKnight()
{}

extern NPCstructure::NPC Guard_Two;

//Nom: Boroar The Knight.
//Statistique: Windhowl wounded knight.
//Position: (2317, 644)
//World: 0
//Description: Wounded knight.
//Body: Knight.

//////////////////////////////////////////////////////////////////////////////////////////
void BoroarTheKnight::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of BoroarTheKnight
//
{
    npc = Guard_Two;
	SET_NPC_NAME( "[2996]Boroar the Knight" );
    npc.InitialPos.X = 1799;
    npc.InitialPos.Y = 1252;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void BoroarTheKnight::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of BoroarTheKnight
//
{

CONSTANT POTIONS = 1

InitTalk

Begin
INTL( 2197, "... Arrr... Hel... p... me! Skel... t... ons... A bright light... Arrrgh!")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2198, "he.....l..p!") BREAK

Default
INTL( 2199, "Aaa... AAAhh.... Hh...Ah... Hh... Hhh...") BREAK

EndTalk

}
