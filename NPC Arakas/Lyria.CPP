#pragma hdrstop
#include "Lyria.H"

Lyria::Lyria()
{}

Lyria::~Lyria()
{}

extern NPCstructure::NPC LyriaNPC;

void Lyria::Create( void )
{
	npc = ( LyriaNPC );
	SET_NPC_NAME( "[2902]Lyria" );  
	npc.InitialPos.X = 2181; // Brigand Camp
	npc.InitialPos.Y = 1276;
	npc.InitialPos.world = 0;
}

void Lyria::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 935, "Hi, stranger.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 936, "They call me Lyria. You don't look as suspicious as they say.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 937, "Oh, I am just doing things. Not very \"interesting\". But you seem to be a great "
"\"adventurer\".")

Command(INTL( 938, "INTERESTING"))
INTL( 939, "I was just practicing my \"skills\".")

Command(INTL( 894, "SKILL"))
INTL( 940, "I am a master at picking locks. I could \"teach\" it to you, if it will help "
"you in your journey.")

Command2(INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 948, "Let's stop wasting time then.")
CreateSkillList
	AddTeachSkill( __SKILL_PICKLOCK, 1, 800 )
SendTeachSkillList

Command(INTL( 502, "TRAIN"))
INTL( 951, "Let's begin your training.") 
CreateSkillList
	AddTrainSkill( __SKILL_PEEK, 100, 25 )
	AddTrainSkill( __SKILL_PICKLOCK, 100, 100 )
SendTrainSkillList

Command(INTL( 523, "ANNABELLE"))
INTL( 955, "I heard that she has Elven blood running in her veins. Methinks it is untrue "
"because we all know that Elves have been wiped out a long time ago. Or "
"were they?") 

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 820, "Balork's curse? That's horrible!")

Command(INTL( 956, "ADVENTURER"))
INTL( 957, "If you are a good robber, you should ask \"Asarr\" for a job. But you have to be "
"very good, because if you get caught, he will not do a thing for you.")

Command(INTL( 958, "ASARR"))
INTL( 959, "Asarr is our leader and a greater master thief too.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 960, "Up yours!")
BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 961, "Farewell, friend.") BREAK

Default
INTL( 962, "Ask someone else.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Lyria::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Lyria data function
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL( __SKILL_PICKLOCK, 1, 800 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_PEEK, 100, 25 )
		TRAIN_SKILL( __SKILL_PICKLOCK, 100, 100 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
}