#pragma hdrstop
#include "Brother9.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Brother9::Brother9()
{}

Brother9::~Brother9()
{}

extern NPCstructure::NPC DeadBrotherNPC;

void Brother9::Create(){
        npc = DeadBrotherNPC;
        SET_NPC_NAME( "[2932]A foul abomination" );
        npc.InitialPos.X = 561;	//Cave of Specters
        npc.InitialPos.Y = 2548;	//Cave of Specters
        npc.InitialPos.world = 1;
}

void Brother9::OnTalk( UNIT_FUNC_PROTOTYPE )

/*
__QUEST_DEAD_BROTHERS
	0: Has not begun talking to the dead brothers...
	1-12: Has successfully talked to Brother #X.
*/

{

InitTalk

Begin
INTL( 4351, "Begone, foul living thing!")

Command(INTL( 4271, "CUTHANA"))
""
IF ((CheckFlag(__QUEST_DEAD_BROTHERS) == 8) OR (CheckFlag(__QUEST_DEAD_BROTHERS) == 9))
	Conversation
	INTL( 4352, "Yes, this herb can \"heal\" even the grievest wound, but not pain from the soul.")
	GiveFlag(__QUEST_DEAD_BROTHERS,9)
ELSE
	Conversation
	INTL( 4282, "I cannot answer that. Speak to us in the right order.")
	GiveFlag(__QUEST_DEAD_BROTHERS,0)
ENDIF

Command5(INTL( 4266, "TORMENT"),INTL( 4268, "TOURNAMENT OF PRINCE"),INTL( 4283, "KINGDOM OF GOLDMOON"),INTL( 754, "THEODORE"),INTL( 1609, "DEATH"))
INTL( 4270, "You are asking the wrong corpse. You must start all over again.")
GiveFlag(__QUEST_DEAD_BROTHERS,0)

Command5(INTL( 11417, "POISONED"),INTL( 543, "CURSE"),INTL( 569, "HEAL"),INTL( 4272, "ROYAL DOOR"),INTL( 4273, "LOWER DUNGEON"))
INTL( 4270, "You are asking the wrong corpse. You must start all over again.")
GiveFlag(__QUEST_DEAD_BROTHERS,0)

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 4353, "I will not tell you!")

Command2(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"))
INTL( 4354, "Leave me be!")

Command2(INTL( 4275, "HINT"),INTL( 554, "HELP"))
INTL( 4355, "The fiend speaks after the one who speaks after me.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 4278, "Such foul language can only mean you have life force to spare.")
IF (USER_HP >= 2)
	target->SetHP(USER_HP / 2, true)
ENDIF
BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 4356, "Good riddance.")
BREAK

Default
INTL( 4279, "You cannot bore me to death, I am already dead.")

EndTalk
}
