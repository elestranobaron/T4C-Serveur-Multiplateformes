#pragma hdrstop
#include "ChiefWuuthgoran.h"

ChiefWuuthgoran::ChiefWuuthgoran()
{}

ChiefWuuthgoran::~ChiefWuuthgoran()
{}

extern NPCstructure::NPC ChiefWuuthgoranNPC;

void ChiefWuuthgoran::Create( ){
	npc = ChiefWuuthgoranNPC;
	SET_NPC_NAME( "[10838]Chief Wuuthgoran");
	npc.InitialPos.X = 1230;
	npc.InitialPos.Y = 420;
	npc.InitialPos.world = 0;  
		npc.boPrivateTalk = TRUE;
}

void ChiefWuuthgoran::OnTalk( UNIT_FUNC_PROTOTYPE )

{
			
InitTalk			 


Begin		   
INTL( 8153, "Me no have fat bellie. Me call eet moy weenter paddeeng.")
	
Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8154, "Oy's calld Wuuthgoran, da king of us KAHP LETH!!!")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8155, "Wuuthgoran da biggess, da strongess, da smathess  skraugz of dem oll!")

Command(INTL( 8156, "SCALP"))
INTL( 8157, "Gets us deir SCALPS!")

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8158, "Me nutt gonna miss yew. Hummie week.")
BREAK

Default
INTL( 8159, "Methinks dat hummie make no sense.")

EndTalk
}
