#pragma hdrstop
#include "DantalirSongweaver.h"

DantalirSongweaver::DantalirSongweaver()
{}

DantalirSongweaver::~DantalirSongweaver()
{}

extern NPCstructure::NPC DantalirSongweaverNPC;

void DantalirSongweaver::Create( void )
{
    npc = DantalirSongweaverNPC;
    SET_NPC_NAME( "[10843]Dantalir the bard" );
    npc.InitialPos.X = 190;
    npc.InitialPos.Y = 1585;
    npc.InitialPos.world = 1;
}

void DantalirSongweaver::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk
						 
Begin
INTL( 9803, "I hope for your sake that no one has \"followed\" you into our hidden place.")
PRIVATE_SYSTEM_MESSAGE(INTL( 10199, "Dantalir eyes you suspiciously.")) 

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 9808, "I am Dantalir Songweaver, at your service.")

Command(INTL( 10200, "BARD")) 
INTL( 10201, "Guilty as charged. I am a bard and a talented one, I might add. I can play almost any "
"musical instruments you can find around.") 
PRIVATE_SYSTEM_MESSAGE(INTL( 10202, "Dantalir starts singing a boring tale about goblins.")) 

Command(INTL( 10203, "DRUM OF FATE")) 
INTL( 10204, "Unfortunately, I've never had the pleasure of having a drum of fate. I heard that there is "
"only one person on Raven's Dust that can craft them.")

Command(INTL( 4080, "DRUM")) 
INTL( 10205, "I got some finely crafted drums from a merchant a long time ago for a very fine price indeed. "
"However, I'm sorry to say that I have absolutely no clue where I've stored them. They should "
"be somewhere around here... ")
PRIVATE_SYSTEM_MESSAGE(INTL( 10206, "Dantalir grins.")) 

Command3(INTL( 487, "OCCUPATION"),INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"))
INTL( 9809, "That is not of your business, pal!")

Command2(INTL( 8456, "DANTALIR"),INTL( 8457, "SONGWEAVER"))
INTL( 10207, "Yeah?")

Command(INTL( 9804, "FOLLOW"))
INTL( 9805, "Once a person is hidden, they can \"sneak\" behind you and follow you without "
"you ever knowing they were there.")

Command(INTL( 9806, "SNEAK"))
INTL( 9807, "Heh heh, so you want to become a master of the art of silent footsteps, do you? "
"I suppose I could \"teach\" you since I am in a good mood.")

Command(INTL( 9810, "HIDEOUT"))
INTL( 9811, "The thieves' hideout is a secret. You must not reveal its location "
"to anyone lest you want us to cut off your tongue.")

Command2(INTL( 8448, "RABLEK"),INTL( 8449, "SWIFTBLADE"))
INTL( 9812, "You see the tall man with the sword over there? That's him.")

Command2(INTL( 8706, "GRANT"),INTL( 8305, "HORNKEEP"))
INTL( 9813, "Grant Hornkeep is an incompetent fool.")
							   
Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 9814, "You're starting to irritate me.")
BREAK

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
FORMAT(INTL( 9815, "I shall see you again later, %s."), USER_NAME) 
BREAK

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// SNEAK ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Command2(INTL( 495, "LEARN"), INTL( 496, "TEACH"))
""
;const int nLEVEL = 24;
const int nAGI = 75;
IF( USER_LEVEL < nLEVEL )
	IF( USER_TRUE_AGI < nAGI )
		Conversation
		FORMAT( INTL( 9816, "You need %u more levels and %u more agility to learn sneak."), nLEVEL - USER_LEVEL, nAGI - USER_TRUE_AGI )
	ELSE
		Conversation
		FORMAT( INTL( 9817, "You need %u more levels to learn sneak."), nLEVEL - USER_LEVEL )
	ENDIF
ELSE
	IF( USER_TRUE_AGI < nAGI )
		Conversation
		FORMAT( INTL( 9818, "You need %u more agility to learn sneak."), nAGI - USER_TRUE_AGI )
	ELSE
		Conversation
		INTL( 9463, "Splendid! Let us proceed then.")
		CreateSkillList
			AddTeachSkill( __SKILL_SNEAK, 1, 2500 )
		SendTeachSkillList
	ENDIF
ENDIF

Command(INTL( 502, "TRAIN"))
""
IF( UserSkill(__SKILL_SNEAK) == 0 )
	Conversation
	INTL( 814, "You must \"learn\" the skill before I can train you.")
ELSEIF( UserSkill(__SKILL_SNEAK) < 100 )
		Conversation
		INTL( 1481, "Very good, then let's begin your training.")
		CreateSkillList
			AddTrainSkill( __SKILL_SNEAK, 100, 100 )
		SendTrainSkillList	
ELSE
	Conversation
	INTL( 9819, "I have taught you all that I know. You are already a master of sneak!")
ENDIF

Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 9820, "It does not make sense.")
ELSE
   Conversation
   INTL( 5250, "I don't think that concerns me.")
ENDIF

EndTalk
}
//////////////////////////////////////////////////////////////////////////////////////////
void DantalirSongweaver::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Rolph data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL( __SKILL_SNEAK, 1, 2500 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

	NPC_DATA_TRAIN		
		TRAIN_SKILL( __SKILL_SNEAK, 100, 100 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
}