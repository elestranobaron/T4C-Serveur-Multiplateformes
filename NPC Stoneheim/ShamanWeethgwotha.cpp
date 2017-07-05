#pragma hdrstop
#include "ShamanWeethgwotha.h"

ShamanWeethgwotha::ShamanWeethgwotha()
{}

ShamanWeethgwotha::~ShamanWeethgwotha()
{}

extern NPCstructure::NPC ShamanWeethgwothaNPC;

void ShamanWeethgwotha::Create( ){
	npc = ShamanWeethgwothaNPC;
	SET_NPC_NAME( "[10915]Shaman Weethgwotha" );
	npc.InitialPos.X = 1190;
	npc.InitialPos.Y = 500;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

void ShamanWeethgwotha::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT MAJICKS = 1;
CONSTANT ENTANGLE = 2;
CONSTANT BOULDERS = 3;
CONSTANT TRUESIGHT = 4;
CONSTANT AlchemyKit = 5;
CONSTANT BuyAlchemyKit = 6;
CONSTANT TRADE = 7;

InitTalk		   
						   								 
Begin
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1 && CheckItem(__OBJ_MANDRAKE) >= 5)
	Conversation
	INTL( 8381, "Hummie come tew treid mandreik fer scrolls?")
	SetYesNo(TRADE)
ELSE
	Conversation
	INTL( 8382, "Wut da leetle hummie want?")
ENDIF

YES(TRADE)
	IF(CheckItem(__OBJ_MANDRAKE) >= 5)
		Conversation
		INTL( 8383, "Dere yew go.")
		FOR(0, 5) 
			TakeItem(__OBJ_MANDRAKE)
		ENDFOR
		GiveItem(__OBJ_SCROLL_OF_HATE)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8384, "You give Weethgwotha 5 mandrake leaves."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 8385, "Weethgwotha gives you a scroll of hate."))
		IF(CheckItem(__OBJ_MANDRAKE) >= 5)
			Conversation
			INTL( 8386, " Yew have enuf fer anoder scroll, yew wanto treid aggen?")
			SetYesNo(TRADE)
		ENDIF
	ELSE
		Conversation
		INTL( 8387, "Weethgwotha dun like triks... hummie die now!")
		FIGHT
	ENDIF
NO(TRADE)
	Conversation
	INTL( 8388, "Den wut da leetle hummie want?")
YesNoELSE(TRADE)
	Conversation
	INTL( 8389, "Hummie wanto treid mandreik fer scrolls or no?")
	SetYesNo(TRADE)

Command2(INTL( 8390, "ALCHEMY KIT"), INTL( 8391, "ALKEMI KIT"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8392, "Da leetle hummie wanto buy alkemi kit?")
	SetYesNo(AlchemyKit)
ELSE
	Conversation
	INTL( 8393, "Weethgwotha cast guud majick on yew if yew dun leave now.")
	FIGHT
ENDIF

YES(AlchemyKit)
	Conversation
	INTL( 8394, "Fer leetle hummie, Weethgwotha do speshal price. Hummie pay 15000 shiny gold?")
	SetYesNo(BuyAlchemyKit)
NO(AlchemyKit)
	Conversation
	INTL( 8395, "Den why dumb hummie ax Weethgwotha fer kit if don wanto buy it?")
YesNoELSE(AlchemyKit)
	Conversation
	INTL( 8396, "Hummie wanto buy alkemi kit or not?")
	SetYesNo(AlchemyKit)

YES(BuyAlchemyKit)
	IF(Gold >= 15000)
		TakeGold(15000)
		GiveItem(__OBJ_ALCHEMY_KIT)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8397, "You give 15000 gold to Weethgwotha."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 8398, "Weethgwotha gives you a crude alchemy kit."))
		Conversation
		INTL( 8399, "Tankyuu leetle hummie.")
	ELSE
		Conversation
		INTL( 8400, "Hummie need 15000 shiny gold to pay fer alkemy kit. Dis not enuf.")
	ENDIF
NO(AlchemyKit)
	Conversation
	INTL( 8401, "Too much fer leetle hummie huh? Tew bad.")
YesNoELSE(BuyAlchemyKit)
	Conversation
	INTL( 8402, "Hummie pay 15000 gold or not?")
	SetYesNo(BuyAlchemyKit)

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8403, "Me name go like dis: Weethgwotha.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8404, "Oy is totemherbdoktor. Me teech guud \"majicks\" tew odder skraug.")

CmdAND(INTL( 1159, "SCROLL"), INTL( 8377, "HATE"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8405, "Did big dumb Oogla tell yew dat? Weethgwotha teech him guud lesson later. So yu want scroll of heit? "
	"Well Weethgwotha need sumting from hummietown. Weethgwotha give yu one scroll fer eech five mandreik.")
ELSE
	Conversation
	INTL( 8393, "Weethgwotha cast guud majick on yew if yew dun leave now.")
	FIGHT
ENDIF

Command5(INTL( 8406, "MAJICKS"), INTL( 1096, "MAGIC"), INTL( 496, "TEACH"), INTL( 495, "LEARN"), INTL( 8407, "LURN"))
INTL( 8408, "Wut? Yew wan me teech yu guud majicks?")
SetYesNo(MAJICKS)

YES(MAJICKS)
	Conversation
	INTL( 8409, "Hmmm, <sniff> <sniff>, mebby yu cuud lern, mebby nut. Me teech yu")
	CreateSkillList
		AddTeachSkill (__SPELL_ENTANGLE, 15, 37913)
		AddTeachSkill (__SPELL_BOULDERS, 27, 161537)
		AddTeachSkill (__SPELL_TRUE_SIGHT, 28, 170913)
	SendTeachSkillList
NO(MAJICKS)
	Conversation
	INTL( 8410, "Den wut yu want?")
YesNoELSE(MAJICKS)
	Conversation
	INTL( 8411, "Yew wan me teech yu guud majicks or nut?")
	SetYesNo(MAJICKS)

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8412, "Yew dew wut yew want, liddle hummie, Weethgwotha nut care.")
BREAK

Command2(INTL( 8413, "ENTANGLE"), INTL( 8414, "HENTENGLE"))
INTL( 8415, "Da hentengle spel hold yur enemy wit sticky stuf.")
	
Command2(INTL( 8416, "BOULDERS"), INTL( 8417, "BOULDURS"))
INTL( 8418, "Da bouldurs spel crush yur enemy wit big rocks. Yu kent lern if yu don have urthquake.")
	
Command2(INTL( 8419, "TRUE SIGHT"), INTL( 8420, "TRU SEIT"))
INTL( 8421, "Da tru seit spel make yu see evryting odder dumb hoomans don see. Yu see hiden an invisibull wit dis spel.")

Default
INTL( 8422, "If Hummie wood be more cleer, me wood unddersand.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void ShamanWeethgwotha::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL(__SPELL_ENTANGLE, 15, 37913)
			TEACH_SKILL(__SPELL_BOULDERS, 27, 161537)
			TEACH_SKILL(__SPELL_TRUE_SIGHT, 28, 170913)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE