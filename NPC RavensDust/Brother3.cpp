#pragma hdrstop
#include "Brother3.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Brother3::Brother3()
{}

Brother3::~Brother3()
{}

extern NPCstructure::NPC DeadBrotherNPC;

void Brother3::Create(){
        npc = DeadBrotherNPC;
        SET_NPC_NAME( "[2926]A moaning shadow" );
        npc.InitialPos.X = 526;	    //Cave of Specters
        npc.InitialPos.Y = 2562;	//Cave of Specters
        npc.InitialPos.world = 1;
}

void Brother3::OnTalk( UNIT_FUNC_PROTOTYPE )

/*
__QUEST_DEAD_BROTHERS
	0: Has not begun talking to the dead brothers...
	1-12: Has successfully talked to Brother #X.
*/

{

InitTalk

Begin
INTL( 4323, "There is no rest for those such as we.")

Command(INTL( 4268, "TOURNAMENT OF PRINCE"))
""
IF ((CheckFlag(__QUEST_DEAD_BROTHERS) == 2) OR (CheckFlag(__QUEST_DEAD_BROTHERS) == 3))
	Conversation
	INTL( 4324, "So it was ordained by our father's testament, a battle to "
	"the death to choose the \"King of Goldmoon\".")
	GiveFlag(__QUEST_DEAD_BROTHERS,3)
ELSE
	Conversation
	INTL( 4282, "I cannot answer that. Speak to us in the right order.")
	GiveFlag(__QUEST_DEAD_BROTHERS,0)
ENDIF

Command5(INTL( 4266, "TORMENT"),INTL( 4269, "KING OF GOLDMOON"),INTL( 754, "THEODORE"),INTL( 1609, "DEATH"),INTL( 11417, "POISONED"))
INTL( 4270, "You are asking the wrong corpse. You must start all over again.")
GiveFlag(__QUEST_DEAD_BROTHERS,0)

Command5(INTL( 543, "CURSE"),INTL( 4271, "CUTHANA"),INTL( 569, "HEAL"),INTL( 4272, "ROYAL DOOR"),INTL( 4273, "LOWER DUNGEON"))
INTL( 4270, "You are asking the wrong corpse. You must start all over again.")
GiveFlag(__QUEST_DEAD_BROTHERS,0)

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 4325, "Why even ask? I am dead.")

Command2(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"))
INTL( 4326, "I do not work, I moan...")

Command2(INTL( 4275, "HINT"),INTL( 554, "HELP"))
INTL( 4327, "I do not speak after the fourth.")

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
