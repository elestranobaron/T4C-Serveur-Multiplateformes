#pragma hdrstop
#include "MirymwenFeatherfoot.h"

MirymwenFeatherfoot::MirymwenFeatherfoot()
{}

MirymwenFeatherfoot::~MirymwenFeatherfoot()
{}

extern NPCstructure::NPC MirymwenFeatherfootNPC;

void MirymwenFeatherfoot::Create( void )
{
    npc = MirymwenFeatherfootNPC;
    SET_NPC_NAME( "[10876]Mirymwen Featherfoot" );
    npc.InitialPos.X = 140;
    npc.InitialPos.Y = 1550;
    npc.InitialPos.world = 1;
}

void MirymwenFeatherfoot::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
INTL( 2388, "What do you want from me?")

Command2(INTL( 8856, "MIRYMWEN"),INTL( 8857, "FEATHERFOOT"))
INTL( 8858, "Yes, Mirymwen Featherfoot is the name.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8859, "I am Mirymwen Featherfoot.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8860, "I am a thief and I'm particularly skilled with a dagger. I'm also quite "
"adept at dodging, and I could probably \"train\" you in that field, seeing "
"as it is very useful for a thief.")

Command(INTL( 502, "TRAIN"))
INTL( 4867, "Hmph, let's begin.")
CreateSkillList
	AddTrainSkill( __SKILL_DODGE, 5000, 10 )
	AddTrainSkill( __SKILL_ARCHERY, 5000, 15 )
SendTrainSkillList

Command2(INTL( 8456, "DANTALIR"),INTL( 8457, "SONGWEAVER"))
INTL( 8861, "Dantalir Songweaver is a bard. Though, I must say that his thieving "
"skills are much better than his vocal cords.")

Command2(INTL( 8448, "RABLEK"),INTL( 8449, "SWIFTBLADE"))
INTL( 8862, "Rablek is the man with the gleaming sword who is standing over there.")

Command5(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "),INTL( 8863, " SEX "))
INTL( 8864, "In your dreams!")
BREAK

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 8497, "See you around.")
BREAK

Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 4675, "I don't have time for that nonsense.")
ELSE
   Conversation
   INTL( 5910, "What was that you said?")
ENDIF

EndTalk
}


//////////////////////////////////////////////////////////////////////////////////////////
void MirymwenFeatherfoot::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_DODGE, 5000, 10 )
		TRAIN_SKILL( __SKILL_ARCHERY, 5000, 15 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
