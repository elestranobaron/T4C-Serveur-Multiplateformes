#pragma hdrstop
#include "Brother7.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Brother7::Brother7()
{}

Brother7::~Brother7()
{}

extern NPCstructure::NPC DeadBrotherNPC;

void Brother7::Create(){
        npc = DeadBrotherNPC;
        SET_NPC_NAME( "[2930]A wailing entity" );
        npc.InitialPos.X = 568;	//Cave of Specters
        npc.InitialPos.Y = 2441;	//Cave of Specters
        npc.InitialPos.world = 1;
}

void Brother7::OnTalk( UNIT_FUNC_PROTOTYPE )

/*
__QUEST_DEAD_BROTHERS
	0: Has not begun talking to the dead brothers...
	1-12: Has successfully talked to Brother #X.
*/

{

InitTalk

Begin
INTL( 4341, "Have you come to mourn our passing?")

Command(INTL( 11417, "POISONED"))
""
IF ((CheckFlag(__QUEST_DEAD_BROTHERS) == 6) OR (CheckFlag(__QUEST_DEAD_BROTHERS) == 7))
	Conversation
	INTL( 4342, "We remain here, \"cursed\" and tormented, till the day he comes to join us.")
	GiveFlag(__QUEST_DEAD_BROTHERS,7)
ELSE
	Conversation
	INTL( 4282, "I cannot answer that. Speak to us in the right order.")
	GiveFlag(__QUEST_DEAD_BROTHERS,0)
ENDIF

Command5(INTL( 4266, "TORMENT"),INTL( 4268, "TOURNAMENT OF PRINCE"),INTL( 4283, "KINGDOM OF GOLDMOON"),INTL( 754, "THEODORE"),INTL( 1609, "DEATH"))
INTL( 4270, "You are asking the wrong corpse. You must start all over again.")
GiveFlag(__QUEST_DEAD_BROTHERS,0)

Command5(INTL( 543, "CURSE"),INTL( 4271, "CUTHANA"),INTL( 569, "HEAL"),INTL( 4272, "ROYAL DOOR"),INTL( 4273, "LOWER DUNGEON"))
INTL( 4270, "You are asking the wrong corpse. You must start all over again.")
GiveFlag(__QUEST_DEAD_BROTHERS,0)

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 4343, "You could not possibly care.")

Command2(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"))
INTL( 4344, "The dead but wail their sorrows...")

Command2(INTL( 554, "HELP"),INTL( 4275, "HINT"))
INTL( 4345, "I talk after the pitiful one.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 4278, "Such foul language can only mean you have life force to spare.")
IF (USER_HP >= 2)
	target->SetHP(USER_HP / 2, true)
ENDIF
BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 1075, "Farewell.")
BREAK

Default
INTL( 4279, "You cannot bore me to death, I am already dead.")

EndTalk
}
