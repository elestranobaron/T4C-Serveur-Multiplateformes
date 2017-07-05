// HumanDrunk.cpp: implementation of the HumanDrunk class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "HumanDrunk.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HumanDrunk::HumanDrunk()
{}

HumanDrunk::~HumanDrunk()
{}

extern NPCstructure::NPC HumanDrunkNPC;

//////////////////////////////////////////////////////////////////////////////////////////
void HumanDrunk::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of HumanDrunk
//
{ 
    npc = HumanDrunkNPC;
	SET_NPC_NAME( "[3007]Drunk" );
    npc.InitialPos.X = 1786;
    npc.InitialPos.Y = 1245;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void HumanDrunk::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of HumanDrunk
//
{

InitTalk

Begin
INTL( 2353, "... zZZZzzzzZZZZzzzzzZZzzzZzzzZzzzz ...")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2354, "zZzz.. Heh? Ah... Er... zzzZzZZzz... Zzz...") BREAK

Command(INTL( 2355, "BEER"))
INTL( 2356, "*snort* *burp* Yep... 'nother one. ZzzZZ! Huh?") BREAK

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2357, "Uh? Ah... Yeah...") BREAK

Default
INTL( 2358, "...zzZz...")

EndTalk

}
