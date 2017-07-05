#pragma hdrstop
#include "Brother10.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Brother10::Brother10()
{}

Brother10::~Brother10()
{}

extern NPCstructure::NPC DeadBrotherNPC;

void Brother10::Create(){
        npc = DeadBrotherNPC;
        SET_NPC_NAME( "[2922]A putrid beast" );
        npc.InitialPos.X = 571;	//Cave of Specters
        npc.InitialPos.Y = 2443;	//Cave of Specters
        npc.InitialPos.world = 1;
}

void Brother10::OnTalk( UNIT_FUNC_PROTOTYPE )

/*
__QUEST_DEAD_BROTHERS
	0: Has not begun talking to the dead brothers...
	1-12: Has successfully talked to Brother #X.
*/

{

InitTalk

Begin
INTL( 4280, "What could you possibly want?")

Command(INTL( 569, "HEAL"))
""
IF ((CheckFlag(__QUEST_DEAD_BROTHERS) == 9) OR (CheckFlag(__QUEST_DEAD_BROTHERS) == 10))
	Conversation
	INTL( 4281, "If you need that herb, all you need are the six Royal Keys to "
	"go through the \"Royal Doors\".")
	GiveFlag(__QUEST_DEAD_BROTHERS,10)
ELSE
	Conversation
	INTL( 4282, "I cannot answer that. Speak to us in the right order.")
	GiveFlag(__QUEST_DEAD_BROTHERS,0)
ENDIF

Command5(INTL( 4266, "TORMENT"),INTL( 4268, "TOURNAMENT OF PRINCE"),INTL( 4283, "KINGDOM OF GOLDMOON"),INTL( 754, "THEODORE"),INTL( 1609, "DEATH"))
INTL( 4270, "You are asking the wrong corpse. You must start all over again.")
GiveFlag(__QUEST_DEAD_BROTHERS,0)

Command5(INTL( 11417, "POISONED"),INTL( 543, "CURSE"),INTL( 4271, "CUTHANA"),INTL( 4272, "ROYAL DOOR"),INTL( 4273, "LOWER DUNGEON"))
INTL( 4270, "You are asking the wrong corpse. You must start all over again.")
GiveFlag(__QUEST_DEAD_BROTHERS,0)

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 4284, "I can tell you do not really care.")

Command2(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"))
INTL( 4285, "My work is beyond your understanding.")

Command2(INTL( 554, "HELP"),INTL( 4275, "HINT"))
INTL( 4286, "I speak after the foul one.")

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
