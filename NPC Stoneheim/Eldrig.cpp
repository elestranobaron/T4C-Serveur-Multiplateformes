#pragma hdrstop
#include "Eldrig.h"

Eldrig::Eldrig()
{}

Eldrig::~Eldrig()
{}

extern NPCstructure::NPC EldrigNPC;

void Eldrig::Create( void )
{
    npc = EldrigNPC;
    SET_NPC_NAME( "[10850]Eldrig" );
    npc.InitialPos.X = 340;
    npc.InitialPos.Y = 840;
    npc.InitialPos.world = 0;
}

void Eldrig::OnTalk( UNIT_FUNC_PROTOTYPE )
{

	
InitTalk

Begin
INTL( 8865, "Can't you see I'm busy training my sword skills?!")

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 8866, "I have no time for chit-chats.")

Command(INTL( 8867, "ELDRIG"))
INTL( 8868, "Yeah, that's the name.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8869, "I am Eldrig. Hey, while you're around, why don't you \"train\" your skills "
"with me and see how good you are?") 

Command3(INTL( 487, "OCCUPATION"),INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"))
INTL( 8870, "I am being handsomely paid by \"Grant\" \"Hornkeep\" to enforce the laws in "
"this town and to ensure protection of our citizens.")

Command2(INTL( 554, "HELP"),INTL( 4275, "HINT"))
INTL( 8871, "You're asking the wrong person, I'm not the one to give you help or hints on your "
"quests. You should ask the old gypsy, she can foretell your future. Be sure to have "
"a lot of gold with you, though. She's not cheap.")

Command(INTL( 502, "TRAIN"))
INTL( 2392, "Let's begin.")
CreateSkillList
	AddTrainSkill( __SKILL_ATTACK, 5000, 10 )
SendTrainSkillList

Command3(INTL( 8706, "GRANT"),INTL( 8305, "HORNKEEP"),INTL( 8304, "SHERIFF"))
INTL( 8872, "Grant Hornkeep is the town's sheriff.")

Command2(INTL( 8284, "DARAN"),INTL( 8285, "LIGHTFOOT"))
INTL( 8873, "If you know where that thief is hiding, you'd better tell me or I'll assume "
"that you are one of his accomplices!")
															 
Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8278, "Say your prayers.")
FIGHT

Command(INTL( 5628, "ORACLE"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) >= 1)
	Conversation
	INTL( 8874, "I'm sure he'll talk to someone like you. I hear he dwells at the very center of Stoneheim, "
	"although I don't know what you'll find there.")
ELSE
	Conversation
	INTL( 8875, "Can't help you there, sorry.")
ENDIF

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 1790, "About time.")
BREAK
 
Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 8876, "What now?")
ELSE
   Conversation
   INTL( 8877, "Quit pestering me, I have work that has to be done.")
ENDIF

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Eldrig::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
{
NPC_DATA_EXCHANGE
 
	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_ATTACK, 5000 , 10 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE

}