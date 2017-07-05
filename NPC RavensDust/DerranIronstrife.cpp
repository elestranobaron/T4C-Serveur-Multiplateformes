/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "DerranIronstrife.H"

DerranIronstrife::DerranIronstrife()
{}

DerranIronstrife::~DerranIronstrife()
{}

extern NPCstructure::NPC Normal_Guard;

void DerranIronstrife::Create( void )
{
      npc = ( Normal_Guard );
      SET_NPC_NAME( "[2942]Derran Ironstrife" );
      npc.InitialPos.X = 1346;//2902;//1368; 
      npc.InitialPos.Y = 2384;//255;//2413;
      npc.InitialPos.world = 0;//4;//0;
}

void DerranIronstrife::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{
CONSTANT KNOWLEDGE = 1;

InitTalk

Begin
""
IF (CheckNPCFlag (__FLAG_DELAY_DERRAN) > CurrentRound) // This means the delay is not over yet
ELSEIF (CheckGlobalFlag(__GLOBAL_FLAG_ORC_QUEST) == 1) // This means the Quest is running
// Do nothing since the Quest is already running. 
ELSE   
	IF (rnd.roll(dice(1, 25) ) == 1)
		SUMMON( "ORCARCHMAGE", 1395, 1830) // Summons the orcish great mage in Raven's Dust orc camp
		GiveGlobalFlag(__GLOBAL_FLAG_ORC_QUEST, 1) // Orc great mage is now running
	ELSE
		GiveNPCFlag (__FLAG_DELAY_DERRAN, rnd.roll(dice(3, 4 ) ) MINUTES TDELAY)
	ENDIF
ENDIF	
IF (CheckFlag(__DERRAN_KNOWS_YOU) >= 1)
	Conversation
   FORMAT(INTL( 4655, "Greetings %s. It is nice to see you again."), USER_NAME)
ELSE
	Conversation
	INTL( 4656, "I have never seen you around stranger. I guess you're new because I don't remember you. Would you care to tell me who you are?")
	SetYesNo( KNOWLEDGE )
ENDIF

YES ( KNOWLEDGE )
	Conversation
   FORMAT(INTL( 4657, "You truly are %s? I have heard a few stories about you. It is nice to make your acquaintance."), USER_NAME)
   GiveFlag( __DERRAN_KNOWS_YOU, 1 )

NO ( KNOWLEDGE )
	Conversation
	INTL( 4658, "You do not want to tell me who you are? So be it stranger!") 

YesNoELSE ( KNOWLEDGE )
	Conversation
	INTL( 4659, "Is it that difficult to answer a simple question? Do you want to tell me who you are?")
	SetYesNo( KNOWLEDGE ) 
	
Command2(INTL( 485, "WHO ARE YOU"),INTL( 3694, " NAME"))
INTL( 4660, "I am Derran Ironstrife, warrior dedicated to the protection of our \"Majesty\".")

Command2(INTL( 4661, "DERRAN"),INTL( 4662, "IRONSTRIFE"))
INTL( 4663, "Yes, I am Derran Ironstrife. I already told you that didn't I? You could have asked me simply "
"by asking me my \"name\".")

Command(INTL( 1460, "THEOPOLD"))
INTL( 4664, "King Theopold was King Theodore XIIIth's honorable father.")

Command3(INTL( 3990, "MAJESTY"),INTL( 1072, "KING"),INTL( 754, "THEODORE"))
INTL( 4665, "Our King is truly admirable!")

Command3(INTL( 3696, "WHAT DO YOU DO"),INTL( 489, "WORK"),INTL( 487, "OCCUPATION"))
INTL( 4666, "I am a warrior fighting for the good cause of our King. I also help \"train\" "
"those who are willing to fight the orc menace. Sometimes, we attack the orcs to prevent "
"their siege weapons from approaching within range of the castle's walls. Sadly, we aren't "
"able to eradicate them once and for all. I heard they often hide in the surrounding \"caverns\".")

Command(INTL( 502, "TRAIN"))
INTL( 2392, "Let's begin.")
CreateSkillList
	AddTrainSkill( __SKILL_ATTACK, 5000, 10 )
	AddTrainSkill( __SKILL_STUN_BLOW, 100, 20 )
	AddTrainSkill( __SKILL_POWERFULL_BLOW, 100, 50 )
SendTrainSkillList

Command(INTL( 744, "ORC"))
INTL( 4667, "I hate those orcs. Their leader, Ghundarg, almost killed me the other day. He cowardly attacked me "
"from behind. Someday, I'll get my revenge...")

Command(INTL( 881, "CAVE"))
INTL( 4668, "There are many caverns on the island of Raven's Dust. You should always bring a few torches if you wish "
"to explore them. Oh, and bring a sword, that will prove useful too. Trust me.") 

Command2(INTL( 1492, "DESERT"),INTL( 3865, "VULTURE'S DEN"))
INTL( 4669, "I wouldn't dare to go there if I were you.")

Command(INTL( 3854, "RAVENWOOD"))
INTL( 4670, "The Ravenwood forest is not a nice place to wander around. I heard that a woodcutter lives there though.")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 4671, "It's the island you are currently standing on. We're locating south of Arakas if you did not know already.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 698, " ASS "),INTL( 697, "ASSHOLE"))
INTL( 4672, "How dare you to speak to me like that? I could slice you in two in a swift movement of my arm.")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
""
IF (CheckFlag(__DERRAN_KNOWS_YOU) >= 1) 
	Conversation
	INTL( 4673, "Until we meet again my friend.")
	BREAK
ELSE
	Conversation
	INTL( 4674, "Farewell stranger.")
	BREAK
ENDIF
	
Default 
INTL( 4675, "I don't have time for that nonsense.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void DerranIronstrife::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_ATTACK, 5000, 10 )
		TRAIN_SKILL( __SKILL_STUN_BLOW, 100, 20 )
		TRAIN_SKILL( __SKILL_POWERFULL_BLOW, 100, 50 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE

