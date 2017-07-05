#pragma hdrstop
#include "Brother1.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Brother1::Brother1()
{}

Brother1::~Brother1()
{}

extern NPCstructure::NPC DeadBrotherNPC;

void Brother1::Create(){
        npc = DeadBrotherNPC;
        SET_NPC_NAME( "[2921]A decrepit figure" );
        npc.InitialPos.X = 633;	    //Cave of Specters
        npc.InitialPos.Y = 2353;	//Cave of Specters
        npc.InitialPos.world = 1;
}

void Brother1::OnTalk( UNIT_FUNC_PROTOTYPE )

/*
__QUEST_DEAD_BROTHERS
	0: Has not begun talking to the dead brothers...
	1-12: Has successfully talked to Brother #X.
*/

{

InitTalk

Begin
INTL( 4265, "Nothing can spare us our \"torment\".")
IF ((CheckFlag(__QUEST_DEAD_BROTHERS) == 0) OR (CheckFlag(__QUEST_DEAD_BROTHERS) == 1))
	GiveFlag(__QUEST_DEAD_BROTHERS,1)
ENDIF

Command(INTL( 4266, "TORMENT"))
INTL( 4267, "Ask my brother.")

Command5(INTL( 4268, "TOURNAMENT OF PRINCE"),INTL( 4269, "KING OF GOLDMOON"),INTL( 754, "THEODORE"),INTL( 1609, "DEATH"),INTL( 11417, "POISONED"))
INTL( 4270, "You are asking the wrong corpse. You must start all over again.")
GiveFlag(__QUEST_DEAD_BROTHERS,0)

Command5(INTL( 543, "CURSE"),INTL( 4271, "CUTHANA"),INTL( 569, "HEAL"),INTL( 4272, "ROYAL DOOR"),INTL( 4273, "LOWER DUNGEON"))
INTL( 4270, "You are asking the wrong corpse. You must start all over again.")
GiveFlag(__QUEST_DEAD_BROTHERS,0)

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 4274, "My brothers and I have a tale to tell... But you must know who to ask, "
"and when. Let me know if you need \"help\".")

Command2(INTL( 554, "HELP"),INTL( 4275, "HINT"))
INTL( 4276, "The sixth told you who was first.")

Command2(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"))
INTL( 4277, "The dead do not work.")

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
