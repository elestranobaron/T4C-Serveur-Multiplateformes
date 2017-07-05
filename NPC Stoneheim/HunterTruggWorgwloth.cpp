#pragma hdrstop
#include "HunterTruggWorgwloth.h"

HunterTruggWorgwloth::HunterTruggWorgwloth()
{}

HunterTruggWorgwloth::~HunterTruggWorgwloth()
{}

extern NPCstructure::NPC HunterTruggWorgwlothNPC;

void HunterTruggWorgwloth::Create( ){
	npc = HunterTruggWorgwlothNPC;
   SET_NPC_NAME(   "[10861]Trugg" );
	npc.InitialPos.X = 1085;
	npc.InitialPos.Y = 405; 
	npc.InitialPos.world = 0; 
   	npc.boPrivateTalk = TRUE;
}

void HunterTruggWorgwloth::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 8526, "Wadda ya want?! Speek or yew gonna lurn pain!")
	
Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8527, "Dey call me Trugg Worgwloth. Me no feer anyone. Trugg strung and can heel "
"wounds guud if harm. Me \"teech\" if yew want.")

Command(INTL( 8528, "GRUTT"))
INTL( 8529, "Grutt is me yung brodder.")

Command(INTL( 8438, "BROGG"))
INTL( 8530, "Brogg waz strung warrior. Brogg teech Grutt how tew fight. ")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8531, "Me try tew sdop Moon Tug from steelin our liddle shiny metal.")
 
Command3(INTL( 495, "LEARN"),INTL( 496, "TEACH"),INTL( 8532, "TEECH"))
""
IF( UserSkill(__SKILL_RAPID_HEALING) == 0 )
	IF( USER_LEVEL < 30 )
		IF( USER_TRUE_END < 80 )
			Conversation
			FORMAT(INTL( 8533, "You week! Trugg teech if yew %u more levels and %u more endurance!"), 30 - USER_LEVEL, 80 - USER_TRUE_END )
		ELSE
			Conversation
			FORMAT(INTL( 8534, "You week! Trugg teech if yew %u more levels!"), 30 - USER_LEVEL )
		ENDIF
	ELSE
		IF( USER_TRUE_END < 80 )
			Conversation
			FORMAT(INTL( 8535, "You week! Trugg teech if yew %u more endurance!"), 80 - USER_TRUE_END )
		ELSE
			Conversation
			INTL( 8536, "Me teech now.")
			CreateSkillList
				AddTeachSkill( __SKILL_RAPID_HEALING, 1, 5000 )
			SendTeachSkillList
		ENDIF
	ENDIF
ELSE
	Conversation
	INTL( 8537, "Yew learn already! Me no teech again!")
ENDIF

Command(INTL( 502, "TRAIN"))
""
IF( UserSkill(__SKILL_RAPID_HEALING) == 0 )
	Conversation
	INTL( 8538, "\"Learn\" skill first! Den me train yew.")
ELSEIF( UserSkill(__SKILL_RAPID_HEALING) < 100 )
	Conversation
	INTL( 504, "Me train now.")
	CreateSkillList
		AddTrainSkill( __SKILL_RAPID_HEALING, 100, 200 )
	SendTrainSkillList
ELSE
	Conversation
	INTL( 8540, "Yew guud fast healing. Guud like Trugg!")
ENDIF

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8541, "Trugg gonna teech yu a liddle bashin' lesson!")
FIGHT 

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8542, "Guud, Trugg have sum werk tew dew.")
BREAK

Default
INTL( 8543, "Hummie dry tew mess wit Trugg brain?")


EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void HunterTruggWorgwloth::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL( __SKILL_RAPID_HEALING, 1, 5000 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_RAPID_HEALING, 100, 200 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
}
