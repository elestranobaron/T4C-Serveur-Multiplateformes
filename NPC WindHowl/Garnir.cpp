//////////////////////////////////////////////////////////////////////
// Garnir.cpp: implementation of the Garnir class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Garnir.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Garnir::Garnir()
{}

Garnir::~Garnir()
{}

extern NPCstructure::NPC Nobleman;

//Nom: Garnir.
//Statistique: Windhowl Assistant.
//Position: (2210, 616)
//World: 0
//Description: Trainer.
//Body: Trainer.

//////////////////////////////////////////////////////////////////////////////////////////
void Garnir::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Garnir
//
{
	npc = Nobleman;
	SET_NPC_NAME( "[3002]Garnir" );
	npc.InitialPos.X = 1692;
	npc.InitialPos.Y = 1224;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Garnir::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Garnir
//
{
InitTalk

Begin
INTL( 2286, "*grumble* YES?! WHAT DO YOU WANT?!")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2287, "Do not waste my time with petty questions! I have \"work\" to do.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2288, "I am an assistant to Lord Arganor. Tiring work it is, I tell you. I have done "
"that for so many years, I just can't wait to finally \"leave\". Anyway, do "
"you need \"help\" or not? I don't have all day! *grumble*")

Command(INTL( 523, "ANNABELLE"))
INTL( 2289, "Annabelle? I heard she is a lovely lady, but somewhat odd, even though I never " 
"met her myself.") 

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 7206, "Devilish monster? Cursed from beyond? Marked for eternity? Yeah, right!")

Command(INTL( 519, "LEAVE"))
INTL( 2290, "I do not have all day to chat, you know! Go bother someone else!") BREAK

Command(INTL( 554, "HELP"))
INTL( 2291, "I can help you train your skills to help better yourself, but you'd better be quick about it!")

Command(INTL( 502, "TRAIN"))
INTL( 1481, "Very good, then let's begin your training.")
CreateSkillList
	AddTrainSkill( __SKILL_ATTACK, 5000, 10 )
	AddTrainSkill( __SKILL_STUN_BLOW, 100, 20 )
	AddTrainSkill( __SKILL_PARRY, 100, 75 )
	AddTrainSkill( __SKILL_POWERFULL_BLOW, 100, 50 )
SendTrainSkillList

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2304, "Good riddance!") BREAK

Default
INTL( 2305, "I don't have time to help you with this.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Garnir::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_ATTACK, 5000, 10 )
		TRAIN_SKILL( __SKILL_STUN_BLOW, 100, 20 )
		TRAIN_SKILL( __SKILL_PARRY, 100, 75 )
		TRAIN_SKILL( __SKILL_POWERFULL_BLOW, 100, 50 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
}