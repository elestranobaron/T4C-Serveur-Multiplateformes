//////////////////////////////////////////////////////////////////////
// Kederic.cpp: implementation of the Kederic class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Kederic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Kederic::Kederic()
{}

Kederic::~Kederic()
{}

extern NPCstructure::NPC Elder_Druid;

void Kederic::Create( ){
    npc = Elder_Druid;
	SET_NPC_NAME( "[2961]Kederic Riverbane" );
    npc.InitialPos.X = 1405; 
    npc.InitialPos.Y = 2854;
	npc.InitialPos.world = 0;
}

void Kederic::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 5329, "Hello, and welcome.")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5330, "I am known as Kederic Riverbane, \"harvester\" of the rains.")

Command2(INTL( 5331, "RIVERBANE"),INTL( 5332, "KEDERIC"))
INTL( 5256, "Yes, that is my name.")

Command(INTL( 5333, "HARVESTER"))
INTL( 5334, "I harvest the powers and forces that flow in waters all around us.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 5335, "I am here to protect the forest and all who inhabit it. I can also \"teach\" you a spell or two.")

Command2(INTL( 496, "TEACH"), INTL( 495, "LEARN"))
INTL( 7557, "You're interested? In that case, this is what I can teach you.")
CreateSkillList
	AddTeachSkill (__SPELL_BARRIER, 12, 18753)
	AddTeachSkill (__SPELL_CLEAR_THOUGHT, 14, 31472)
SendTeachSkillList

Command(INTL( 5357, "MALEAK"))
INTL( 5358, "So you seek the maleak plant? I believe there might be some in the nearby woods.")

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 1075, "Farewell.") BREAK

Default
INTL( 5359, "That is beyond my knowledge.")

EndTalk

}
//////////////////////////////////////////////////////////////////////////////////////////
void Kederic::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_BARRIER, 12, 18753)
         TEACH_SKILL(__SPELL_CLEAR_THOUGHT, 14, 31472)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE