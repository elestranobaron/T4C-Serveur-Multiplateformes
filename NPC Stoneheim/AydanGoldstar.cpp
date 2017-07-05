#pragma hdrstop
#include "AydanGoldstar.h"

AydanGoldstar::AydanGoldstar()
{}

AydanGoldstar::~AydanGoldstar()
{}

extern NPCstructure::NPC AydanGoldstarNPC;

void AydanGoldstar::Create( void )
{
        npc = AydanGoldstarNPC;
        SET_NPC_NAME( "[10830]Aydan Goldstar" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void AydanGoldstar::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk

Begin
""

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
""

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
""

Command4(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"))
""
BREAK

Default
""

EndTalk
}
