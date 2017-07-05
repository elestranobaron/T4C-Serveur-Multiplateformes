//////////////////////////////////////////////////////////////////////
// Karl.cpp: implementation of the Karl class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Karl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Karl::Karl()
{}

Karl::~Karl()
{}

extern NPCstructure::NPC Nobleman;

//Nom: Karl.
//Statistique: Trainer.
//Position: (2219, 630)
//World: 0
//Description: Trainer.
//Body: Trainer.

//////////////////////////////////////////////////////////////////////////////////////////
void Karl::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Karl
//
{
	npc = Nobleman;
	SET_NPC_NAME( "[3010]Karl" );
	npc.InitialPos.X = 1701;
	npc.InitialPos.Y = 1238;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Karl::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Karl
//
{

InitTalk

Begin
INTL( 2388, "What do you want from me?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2389, "My name is Karl and I am rather \"busy\" now.")

Command4(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"),INTL( 2390, "BUSY"))
INTL( 2391, "I am the assistant trainer. I help Sir \"Arganor\" with his work. It is a "
"tiring job, but I manage. If you're here to \"train\" your attack skills, you've "
"come to the right place.")

Command(INTL( 502, "TRAIN"))
INTL( 2392, "Let's begin.")
CreateSkillList
	AddTrainSkill( __SKILL_ATTACK, 5000, 10 )
	AddTrainSkill( __SKILL_ARCHERY, 5000, 15 )
SendTrainSkillList

Command(INTL( 523, "ANNABELLE"))
INTL( 1158, "I do not know much about that woman.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 1791, "I don't know.")

Command(INTL( 2394, "ARGANOR"))
INTL( 2395, "What a great man! His swordsmanship is unmatched in the realm. He has already "
"won many tournaments across the \"land\".")

Command(INTL( 2396, "LAND"))
INTL( 2397, "The world is a large place indeed, my friend. I haven't traveled much of it "
"myself, but I hope to change that someday.")

Command(INTL( 2398, "GARNIR"))
INTL( 2399, "He is the other assistant. A good lad with a big heart, his only flaw is "
"his bad temper. I have known him for years now, and although we both like "
"to work here, we are getting very tired of it.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2400, "I wish you good luck!") BREAK

Default
INTL( 2401, "I do not know.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Karl::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_ATTACK, 5000, 10 )
		TRAIN_SKILL( __SKILL_ARCHERY, 5000, 15 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
