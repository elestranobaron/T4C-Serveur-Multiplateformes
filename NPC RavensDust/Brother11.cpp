#pragma hdrstop
#include "Brother11.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Brother11::Brother11()
{}

Brother11::~Brother11()
{}

extern NPCstructure::NPC DeadBrotherNPC;

void Brother11::Create(){
        npc = DeadBrotherNPC;
        SET_NPC_NAME( "[2923]A creeping fiend" );
        npc.InitialPos.X = 610;	//Cave of Specters
        npc.InitialPos.Y = 2436;	//Cave of Specters
        npc.InitialPos.world = 1;
}

void Brother11::OnTalk( UNIT_FUNC_PROTOTYPE )

/*
__QUEST_DEAD_BROTHERS
	0: Has not begun talking to the dead brothers...
	1-12: Has successfully talked to Brother #X.
*/

{

InitTalk

Begin
INTL( 4287, "May your death come quickly, when it comes.")

Command(INTL( 4272, "ROYAL DOOR"))
""
IF ((CheckFlag(__QUEST_DEAD_BROTHERS) == 10) OR (CheckFlag(__QUEST_DEAD_BROTHERS) == 11))
	Conversation
	INTL( 4288, "They block the way to the \"Lower\" \"Dungeon\" where lies the herb...")
	GiveFlag(__QUEST_DEAD_BROTHERS,11)
ELSE
	Conversation
	INTL( 4282, "I cannot answer that. Speak to us in the right order.")
	GiveFlag(__QUEST_DEAD_BROTHERS,0)
ENDIF

Command5(INTL( 4266, "TORMENT"),INTL( 4268, "TOURNAMENT OF PRINCE"),INTL( 4283, "KINGDOM OF GOLDMOON"),INTL( 754, "THEODORE"),INTL( 1609, "DEATH"))
INTL( 4270, "You are asking the wrong corpse. You must start all over again.")
GiveFlag(__QUEST_DEAD_BROTHERS,0)

Command5(INTL( 11417, "POISONED"),INTL( 543, "CURSE"),INTL( 4271, "CUTHANA"),INTL( 569, "HEAL"),INTL( 4273, "LOWER DUNGEON"))
INTL( 4270, "You are asking the wrong corpse. You must start all over again.")
GiveFlag(__QUEST_DEAD_BROTHERS,0)

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 4289, "What does it matter?")

Command2(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"))
INTL( 4290, "You understand little about death, do you?")

Command2(INTL( 554, "HELP"),INTL( 4275, "HINT"))
INTL( 4291, "The last one speaks after me.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 4278, "Such foul language can only mean you have life force to spare.")
IF (USER_HP >= 2)
	target->SetHP(USER_HP / 2, true)
ENDIF
BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 4292, "Fare thee well.")
BREAK

Default
INTL( 4279, "You cannot bore me to death, I am already dead.")

EndTalk
}
