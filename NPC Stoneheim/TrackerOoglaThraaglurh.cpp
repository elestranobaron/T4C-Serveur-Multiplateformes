#pragma hdrstop
#include "TrackerOoglaThraaglurh.h"

TrackerOoglaThraaglurh::TrackerOoglaThraaglurh()
{}

TrackerOoglaThraaglurh::~TrackerOoglaThraaglurh()
{}

extern NPCstructure::NPC TrackerOoglaThraaglurhNPC;

void TrackerOoglaThraaglurh::Create( ){
	npc = TrackerOoglaThraaglurhNPC;
   SET_NPC_NAME(   "[10932]Oogla Thraaglurh" );
	npc.InitialPos.X = 2235;
	npc.InitialPos.Y = 95;
	npc.InitialPos.world = 2; 
	npc.boPrivateTalk = TRUE;
}

void TrackerOoglaThraaglurh::OnTalk( UNIT_FUNC_PROTOTYPE )

{							   

CONSTANT TRADE = 1;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1 && CheckItem(__OBJ_VILLAIN_SKULL) >= 2 && CheckItem(__OBJ_SCROLL_OF_HATE) >= 2)
	Conversation
	INTL( 8358, "Haar! Oogla not tink hummie wuud bring enuf tings tew treid fer skull. Very guud leetle hummie. Yew wanto treid fer skull den?")
	SetYesNo(TRADE)
ELSE
	Conversation
	INTL( 8359, "Dis Oogla say tew yu...  yew come tew dew trubbles an Oogla "
	"give yu sum guud boom-boom wit dis bigg club.")
ENDIF

YES(TRADE)
	IF(Gold >= 15000)
		IF(CheckItem(__OBJ_VILLAIN_SKULL) >= 2 && CheckItem(__OBJ_SCROLL_OF_HATE) >= 2)
			Conversation
			INTL( 8360, "Har haaar! Hummie teik dis. Oogla teik 15000 gold tew. Yew dun like dat, yew can ask big club fer reefund.")
			PRIVATE_SYSTEM_MESSAGE(INTL( 10230, "You give two villain skulls and two scrolls of hate to Oogla Thraaglurh."))
			TakeItem(__OBJ_VILLAIN_SKULL)
			TakeItem(__OBJ_VILLAIN_SKULL)
			TakeItem(__OBJ_SCROLL_OF_HATE)
			TakeItem(__OBJ_SCROLL_OF_HATE)
			GiveItem(__OBJ_SKULL_OF_EVIL)
			GiveFlag(__FLAG_USER_HAS_SKULL_OF_EVIL, 1)
			TakeGold(15000)
			PRIVATE_SYSTEM_MESSAGE(INTL( 8361, "Oogla Thraaglurh takes 15000 gold from you."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 8362, "You receive the Skull of Evil."))
		ELSE
			Conversation
			INTL( 8363, "Oogla no fool, bash ur skull in fer dat!")
			FIGHT
		ENDIF
	ELSE
		Conversation
		INTL( 8364, "Hummie giv Oogla 15000 gold wit skulls an scrolls or Oogla no dew treid.")
	ENDIF
NO(TRADE)
	Conversation
	INTL( 8365, "Den Oogla say dis tew yu...  yew come tew dew trubbles an Oogla "
	"give yu sum guud boom-boom wit dis bigg club.")
YesNoELSE(TRADE)
	Conversation
	INTL( 8366, "Yew wanto treid fer skull or no?")
	SetYesNo(TRADE)

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8367, "Me Oogla.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8368, "Oogla smash skraugs frum odder tribe reel guud.")
 
Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8369, "Time tew dew sum boom-boom on hummie metinks!")
FIGHT

Command(INTL( 8370, "SKULL OF EVIL"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8371, "Wut? Hummie wan to have my skull? Har har har! Very funny. Oogla tinks hummie will never have \"enuf\" treasur to "
	"buy skull from Oogla!")
ELSE
	Conversation
	INTL( 8372, "Grr! Oogla bash ur skull in fer dat!")
	FIGHT
ENDIF

Command2(INTL( 8373, "ENUF"), INTL( 8374, "ENOUGH"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8375, "Har har! If hummie bring Oogla tew \"villain\" \"skulls\" an tew \"scrolls\" \"of\" \"hate\", mebbe Oogla give hummie Skull of Evil.")
ELSE
	Conversation
	INTL( 8372, "Grr! Oogla bash ur skull in fer dat!")
	FIGHT
ENDIF
 
CmdAND(INTL( 8128, "VILLAIN"), INTL( 8129, "SKULL"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8376, "Hummie ask skraug brudders fer skull, dey know about dem.")
ELSE
	Conversation
	INTL( 8372, "Grr! Oogla bash ur skull in fer dat!")
	FIGHT
ENDIF


CmdAND(INTL( 1159, "SCROLL"), INTL( 8377, "HATE"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8378, "Hummie ax Weethgwotha, mebbe shaman know where dey are.")
ELSE
	Conversation
	INTL( 8372, "Grr! Oogla bash ur skull in fer dat!")
	FIGHT
ENDIF

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8379, "Oogla happy yew go. Hummie smell nut guud.")
BREAK

Default
INTL( 8380, "Me not untterstand wadda hummie say.")		

EndTalk
}
