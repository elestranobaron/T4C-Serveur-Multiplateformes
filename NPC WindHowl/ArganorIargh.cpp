//////////////////////////////////////////////////////////////////////
// ArganorIargh.cpp: implementation of the ArganorIargh class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "ArganorIargh.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ArganorIargh::ArganorIargh()
{}

ArganorIargh::~ArganorIargh()
{}

extern NPCstructure::NPC Nobleman;

//////////////////////////////////////////////////////////////////////////////////////////
void ArganorIargh::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of ArganorIargh
//
{
	npc = Nobleman;
	SET_NPC_NAME( "[2994]Arganor Iargh" );
	npc.InitialPos.X = 1689;//1689;
	npc.InitialPos.Y = 1232;//1232;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void ArganorIargh::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of ArganorIargh
//
{
InitTalk
                                 
Begin
INTL( 2190, "Greetings stranger!")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2191, "I am Sir Arganor Iargh. How are you faring, my friend?")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2192, "I am the chief trainer of this \"town\". I can \"teach\" you how to use your strength "
"to inflict great damage in combat.")

Command2(INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 1479, "Very good, this is what I can teach you.")
CreateSkillList
	AddTeachSkill( __SKILL_STUN_BLOW, 1, 150 )
	AddTeachSkill( __SKILL_PARRY, 1, 900 )
	AddTeachSkill( __SKILL_POWERFULL_BLOW, 1, 2500 )
SendTeachSkillList

Command(INTL( 502, "TRAIN"))
INTL( 7528, "I do not have time to train you. Talk to Garnir if you need some training.")

Command(INTL( 2398, "GARNIR"))
INTL( 7529, "He shouldn't be too far. I'm sure you will find him.")

Command(INTL( 523, "ANNABELLE"))
INTL( 2194, "Annabelle? I heard she is a lovely lady but somewhat odd, even though I've never " 
"seen her myself.") 

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 820, "Balork's curse? That's horrible!")

Command2(INTL( 1869, "TOWN"),INTL( 514, "WINDHOWL"))
INTL( 2195, "You are in Windhowl, the greatest town in the kingdom of Goldmoon.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 1338, "Have a good day.") BREAK

Default
INTL( 2196, "What for?")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void ArganorIargh::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL( __SKILL_STUN_BLOW, 1, 150 )
			TEACH_SKILL( __SKILL_PARRY, 1, 900 )
			TEACH_SKILL( __SKILL_POWERFULL_BLOW, 1, 2500 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE
}