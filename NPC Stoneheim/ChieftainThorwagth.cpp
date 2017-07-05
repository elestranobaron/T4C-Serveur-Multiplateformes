#pragma hdrstop
#include "ChieftainThorwagth.h"

ChieftainThorwagth::ChieftainThorwagth()
{}

ChieftainThorwagth::~ChieftainThorwagth()
{}

extern NPCstructure::NPC ChieftainThorwagthNPC;

void ChieftainThorwagth::Create( ){
	npc = ChieftainThorwagthNPC;
	SET_NPC_NAME( "[10836]Chieftain Thorwagth" );
	npc.InitialPos.X = 2240;
	npc.InitialPos.Y = 90;
	npc.InitialPos.world = 2;	   
	npc.boPrivateTalk = TRUE;
}

void ChieftainThorwagth::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 8119, "Eidder yew kum in peece or me gutt hummie tew pieces.")

Command3(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"),INTL( 8120, "THORWAGTH"))
INTL( 8121, "Me preddy name is Thorgwagth!")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8122, "Werk? Me no werk like liddle hummie, me barsh skulls guud.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8123, "Me gonna do guud hummie stew wit yew flesh!")
FIGHT
 
CmdAND3(INTL( 8124, "BELT"),INTL( 8125, "SKRAUG"),INTL( 8126, "STRENGTH"))
INTL( 8127, "Me nut have one, but da Khan, he knowz.")

CmdAND(INTL( 8128, "VILLAIN"), INTL( 8129, "SKULL"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8130, "Thorwagth giv all me skulls to hummie in hummietown. He giv guud reword.")
ELSE
	Conversation
	INTL( 8131, "Hummie try tew mess wit me skull?")
	FIGHT
ENDIF

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8132, "Guud. Me bash skull if hummie stey longger.")
BREAK

Default
""
IF (rnd.roll(dice(1,2)) ) 
	Conversation
	INTL( 8133, "Stewp boddering me.")
ELSE
	Conversation
	INTL( 8131, "Hummie try tew mess wit me skull?")
ENDIF


EndTalk
}
