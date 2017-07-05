#pragma hdrstop
#include "HunterGruttWorgwloth.h"

HunterGruttWorgwloth::HunterGruttWorgwloth()
{}

HunterGruttWorgwloth::~HunterGruttWorgwloth()
{}

extern NPCstructure::NPC HunterGruttWorgwlothNPC;

void HunterGruttWorgwloth::Create( ){
	npc = HunterGruttWorgwlothNPC;
   SET_NPC_NAME( "[10860]Grutt");
	npc.InitialPos.X = 1140;
	npc.InitialPos.Y = 450;
	npc.InitialPos.world = 0; 
	npc.boPrivateTalk = TRUE;
}		   

void HunterGruttWorgwloth::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin		 
INTL( 8433, "URGH?! Say wut liddle hummie is tewingg here or \"Grutt\" gonna BASH sum "
"hummie butt guud!")
	
Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8434, "Me am Grutt Worgwloth, son ub \"Brogg\" an brodder of \"Trugg\".")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8435, "Me go in forest an bash badd hummies an evil Moon Tug skraugs. Dey "
"reelly badd. Wen dey see us, dey try tew bash an smash us guud.")

Command(INTL( 8436, "TRUGG"))
INTL( 8437, "Trugg is dum brodder.")

Command(INTL( 8438, "BROGG"))
INTL( 8439, "Brogg was me fodder but bad hummies like yu bash him. Me no like yur "
"kind! Hummies har so ugly an stinky.")

Command(INTL( 8440, "WAJPOOTHIN"))
INTL( 8441, "Him huntor of hedds of Skraugs of Moon Tug. We is impresst by eem, we ore. "
"If yew gots \"scalps\" of Moon Tug, yew otta give dem to eem.")

Command(INTL( 8156, "SCALP"))
INTL( 8442, "Yuk yuk yuk... Moon Tug scalps make guud soup. \"Wajpoothin\" mayks guud soup.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8443, "No wun say dat tew Grutt an gett away wit it!")
FIGHT

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8444, "About time hummie go. Me start tew gett hungry.")
BREAK
						  
Default
""							  
IF (rnd.roll(dice(1,2)) ) 	 
	Conversation
	INTL( 8445, "Hummie dry tew mess wit Grutt brain?")
ELSE
	Conversation
	INTL( 8446, "Me not untterstand wut dum hummie say.")
ENDIF

EndTalk
}
