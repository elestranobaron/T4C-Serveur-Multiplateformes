#pragma hdrstop
#include "ChieftainYahgwuhl.h"

ChieftainYahgwuhl::ChieftainYahgwuhl()
{}

ChieftainYahgwuhl::~ChieftainYahgwuhl()
{}

extern NPCstructure::NPC ChieftainYahgwuhlNPC;

void ChieftainYahgwuhl::Create( ){
	npc = ChieftainYahgwuhlNPC;
	SET_NPC_NAME(   "[10837]Chieftain Yahgwuhl" );
	npc.InitialPos.X = 2185;
	npc.InitialPos.Y = 90;
	npc.InitialPos.world = 2;  
 	npc.boPrivateTalk = TRUE;
}

void ChieftainYahgwuhl::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 8160, "Lissen reel guud udderwise me barsh yew. If yew bash fellow "
"skraugs, me barsh yew so guud yew will screem fer mercy.")
	 
Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8161, "Eberywun call me Yahgwuhl.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8162, "Me werk is tew barsh meen skraugs frum odder tribe and smash hummie "
"skulls wen dey try tew hert us.")

CmdAND3(INTL( 8124, "BELT"),INTL( 8125, "SKRAUG"),INTL( 8126, "STRENGTH"))
INTL( 8163, "Me nut know, ask da Khan. He has dem, he does.")

CmdAND(INTL( 8128, "VILLAIN"), INTL( 8129, "SKULL"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8164, "Yaghwuhl had sum, but dey gone now. Yaghwuhl take dem tew \"hummie\".")
ELSE
	Conversation
	INTL( 8165, "Me nutt untterstand wut hummie sey.")
	FIGHT
ENDIF

Command2(INTL( 8166, "HUMMIE"), INTL( 6344, "HUMAN"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8167, "Yaghwuhl go far tru forest an giv da skullz tew da hummie inside gate.")
ELSE
	Conversation
	INTL( 8165, "Me nutt untterstand wut hummie sey.")
	FIGHT
ENDIF

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8168, "No wun ebber sey dat tew Yaghwuhl! Me gonna SMASH yer skull!")
FIGHT

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8169, "Abbut teym liddle hummie leeve.")
BREAK

Default
INTL( 8165, "Me nutt untterstand wut hummie sey.")

EndTalk
}
