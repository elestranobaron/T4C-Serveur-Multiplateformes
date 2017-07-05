//////////////////////////////////////////////////////////////////////
// TheLurker.cpp: implementation of the TheLurker class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "TheLurker.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TheLurker::TheLurker()
{}

TheLurker::~TheLurker()
{}

extern NPCstructure::NPC Thief_TheLurker;

//Nom: The Lurker.
//Statistique: Windhowl Thief.
//Position: (2233, 564)
//World: 0
//Description: Hard looking man.
//Body: Thief.

//////////////////////////////////////////////////////////////////////////////////////////
void TheLurker::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of TheLurker
//
{
	npc = Thief_TheLurker;
	SET_NPC_NAME( "[3024]The Lurker" );
	npc.InitialPos.X = 1714;
	npc.InitialPos.Y = 1174;
	npc.InitialPos.world = 0;  
}

//////////////////////////////////////////////////////////////////////////////////////////
void TheLurker::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of TheLurker
//
{

CONSTANT BAL = 1;
CONSTANT KALASTOR = 2;

InitTalk

Begin
""
IF (CheckFlag(__QUEST_CURE_KALASTOR) == 1)
	Conversation
	INTL( 2712, "Kalastor, that numbskull! You say he got the dreaded goblin fever? I need him "
	"at the best of his capacities, lest we lose contact with Lighthaven. "
	"I can sell you a cure for 800 gold pieces, just because it's for a friend. "
	"Do you want to buy the cure?")
	SetYesNo(KALASTOR)
ELSE
	Conversation
	INTL( 2713, "What?! Oh, it's you again.")
ENDIF

YES(KALASTOR)
RemFlag(__QUEST_CURE_KALASTOR) 
IF (Gold >= 800)
 Conversation
 INTL( 2714, "Give him this elixir of purity and be careful--this stuff ain't cheap.")
 GiveItem(__OBJ_ELIXIR_OF_PURITY)
 TakeGold(800)
ELSE
 Conversation
 INTL( 2715, "You do not have enough gold pieces!")
ENDIF

NO(KALASTOR)
INTL( 2716, "Poor Kalastor...")
RemFlag(__QUEST_CURE_KALASTOR)

YesNoELSE(KALASTOR)
INTL( 2717, "Hmpf.")
RemFlag(__QUEST_CURE_KALASTOR) 

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2718, "I go by the name 'The Lurker'. It is the only name you need to know.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2719, "If you think you are skilled enough, I could try to \"teach\" you some new "
"tricks. Of course, everything comes at a price.")

Command(INTL( 523, "ANNABELLE"))
INTL( 1158, "I do not know much about that woman.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2720, "Have you been cursed too by that Balork?")
SetYesNo(BAL)

YES(BAL)
Conversation
INTL( 2721, "Poor soul. At least, I heard there's no winter in hell.")

NO(BAL)
Conversation
INTL( 2722, "Good for you my friend.")

YesNoELSE(BAL)
Conversation
INTL( 2723, "*shrug* Not that I actually care.") 

Command2(INTL( 496, "TEACH"),INTL( 495, "LEARN"))
INTL( 2724, "Looks like I can't teach you anything new, but I can help you \"train\" your dodging skills instead.")

Command(INTL( 502, "TRAIN"))
INTL( 1579, "Very good, let's begin.")
CreateSkillList
	AddTrainSkill( __SKILL_DODGE, 5000, 10 )
	AddTrainSkill( __SKILL_PEEK, 100, 25 )
	AddTrainSkill( __SKILL_PICKLOCK, 100, 100 )
SendTrainSkillList

Command(INTL( 2726, "MARKET OF SHADOW"))
""
IF (CheckFlag(__BLACK_MARKET) == 1)
	Conversation
	INTL( 2727, "Asarr really sent you to me? You do not look like a thief to me, but "
	"who am I to argue with the leader of the brigands. The market of shadows "
	"is, in reality, a black market where we sell the goods we have stolen. "
	"Ttayh Mark controls the black market in WindHowl. Meet him at his shop "
	"and he will grant you access.")
	GiveFlag(__BLACK_MARKET, 2) 
ELSEIF (CheckFlag(__BLACK_MARKET) == 2)
	Conversation
	INTL( 2728, "I already told you about the black market. Weren't you listening or what? "
	"If you want to see what our black market has to offer, go see Ttayh Mark, "
	"the weaponsmith, and ask him about the black market.")
ELSE
	Conversation
	INTL( 2729, "Who knows?")
ENDIF

Command(INTL( 2730, "BLACK MARKET"))
INTL( 2731, "But why should I know something like that?")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2732, "Remember your task.") BREAK

Default
INTL( 2729, "Who knows?")

EndTalk

}

void TheLurker::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_DODGE, 5000, 10 )
		TRAIN_SKILL( __SKILL_PEEK, 100, 25 )
		TRAIN_SKILL( __SKILL_PICKLOCK, 100, 100 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
