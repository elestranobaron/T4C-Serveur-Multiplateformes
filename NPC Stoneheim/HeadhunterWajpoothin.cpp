#pragma hdrstop
#include "HeadhunterWajpoothin.h"
		  
HeadhunterWajpoothin::HeadhunterWajpoothin()
{}

HeadhunterWajpoothin::~HeadhunterWajpoothin()
{}

extern NPCstructure::NPC HeadhunterWajpoothinNPC;

void HeadhunterWajpoothin::Create( ){
	npc = HeadhunterWajpoothinNPC;
	SET_NPC_NAME("[10858]Wajpoothin" );
	npc.InitialPos.X = 1170;
	npc.InitialPos.Y = 435;
	npc.InitialPos.world = 0; 
	npc.boPrivateTalk = TRUE;
}

void HeadhunterWajpoothin::OnTalk( UNIT_FUNC_PROTOTYPE )

{
 
CONSTANT TakeScalps = 1;

InitTalk

Begin
INTL( 8247, "Me liddle teym tew speek wit week hummie.")  
	
Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8248, "Me Wajpoothin.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8249, "Me gett odder tribe \"scalp\" an Weethgwotha pey me reel guud.")

Command(INTL( 8156, "SCALP"))
INTL( 8250, "Yu bring me, um... handful of scalps ov odder tribe, und I "
"give yew a \"Skraugbashor\" \"Mace\".")
 
CmdAND(INTL( 8251, "SKRAUGBASHOR"),INTL( 8252, "MACE"))
""
IF (CheckItem(__OBJ_MOON_TUG_SCALP)<5)
	Conversation
	INTL( 8253, "Me like dat mace, me gots myself a guud lots of dem. Me can give yew "
	"sum if yew bring me \"scalps\".")
ELSE
	Conversation
	INTL( 8254, "OOOGYAH! Dat is guud! Yew gots lots of scalps! Me takes dem und me gives "
	"yew a \"Skraugbashor\" \"Mace\". Yew agrees?")
	SetYesNo(TakeScalps)
ENDIF
 
YES(TakeScalps)
	IF (CheckItem(__OBJ_MOON_TUG_SCALP)<5) 
		Conversation
		INTL( 8255, "Scalps go poof?!? Wajpoothin angry!! Me BASH hummie!")
		FIGHT 
	ELSE
		Conversation
		INTL( 8256, "O-kay... Eer yew go.")
		FOR(0,5)
			TakeItem(__OBJ_MOON_TUG_SCALP)
		ENDFOR
		GiveItem(__OBJ_SKRAUGBASHOR_MACE)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8257, "You receive a Skraugbashor Mace.")) 
		;int nExpReward = USER_LEVEL*1000;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
		GiveXP(nExpReward)
	ENDIF 
	
NO(TakeScalps)
	Conversation
	INTL( 8258, "Dis tew badd...")

YesNoELSE(TakeScalps)
	Conversation
	INTL( 8259, "Uuuh... Me nut unnerstand.")
	SetYesNo(TakeScalps)

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8260, "Me gonna bash sum hummie skull wit dis bigg glubb!")
FIGHT

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8261, "Hummie go, me can gett back t' werk.")
BREAK

Default
""
IF (rnd.roll(dice(1,2)) ) 
	Conversation
	INTL( 8262, "Tel somwan elss abbud it.")
ELSE
	Conversation
	INTL( 8263, "Me nut untterstand hummie say.")
ENDIF


EndTalk
}
