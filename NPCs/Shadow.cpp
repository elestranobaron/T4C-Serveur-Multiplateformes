// Shadow.cpp: implementation of the Shadow class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Shadow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Shadow::Shadow()
{}

Shadow::~Shadow()
{}

extern NPCstructure::NPC ShadowNPC;

void Shadow::Create(){
	npc = ShadowNPC;
	SET_NPC_NAME( "[3056]A dark figure..." );
	npc.InitialPos.X = 2888;
	npc.InitialPos.Y = 1123;
	npc.InitialPos.world = 0;
	 npc.boPrivateTalk = TRUE;
}

void Shadow::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	switch(rnd(0, 1)){
	case 0: SHOUT(INTL( 1969, "ARGH!")); break;
	case 1: SHOUT(INTL( 1379, "HELP!")); break;
	}

	self->Do(flee);
	self->SetTarget(target);
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Shadow::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT TRAINING = 1

InitTalk

Begin
INTL( 11779, "Ahh, a wealthy traveler! Don't see too many like you since the guards came")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1971, "I don't think my name matters to you!")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1972, "That does not concern you...")

Command(INTL( 523, "ANNABELLE"))
INTL( 1973, "I don't care.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 1974, "I'm not cursed, therefore it does not concern me.")

Command(INTL( 585, "SHADOW"))
INTL( 1975, "Who told you my name? No matter. I suppose you want me to \"teach\" you a skill now. Serves "
"me right for not keeping my identity a secret.")

Command(INTL( 970, "THIEF"))
INTL( 1976, "A thief? Where? I don't see any thieves around here!")

Command(INTL( 894, "SKILL"))
INTL( 1977, "I guess I could teach you how to \"peek\" into other people's belongings.")

Command2(INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 712, "Very well.")
CreateSkillList
	AddTeachSkill( __SKILL_PEEK, 1, 500 )
SendTeachSkillList

Command(INTL( 502, "TRAIN"))
INTL( 7525, "You must look elsewhere for your training...")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1989, "Very well, enjoy your purse, while you still carry it...") BREAK

Default
INTL( 1990, "Let's talk about something else.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Shadow::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Rolph data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL( __SKILL_PEEK, 1, 500 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE
}