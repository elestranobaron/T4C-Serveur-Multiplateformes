// BishopCrowbanner.cpp: implementation of the BishopCrowbanner class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "BishopCrowbanner.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BishopCrowbanner::BishopCrowbanner()
{}

BishopCrowbanner::~BishopCrowbanner()
{}

extern NPCstructure::NPC ChamberlainThomarNPC;

//////////////////////////////////////////////////////////////////////////////////////////
void BishopCrowbanner::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Bishop Crowbanner
//
{
    npc = ChamberlainThomarNPC;
    SET_NPC_NAME( "[2919]Bishop Crowbanner");
    npc.InitialPos.X = 1415;//2844;//1415; // Somewhere in Silversky castle
    npc.InitialPos.Y = 2334;//691;//2334; // Somewhere in Silversky castle
	npc.InitialPos.world = 0;//4;//0;

    GiveGlobalFlag(__QUEST_BISHOP_ILLNESS, rnd.roll(dice(1,2))-1);
	GiveGlobalFlag(__GLOBAL_QUEST_CROWBANNER_TIMER, rnd.roll(dice(1,6))*4 HOURS TDELAY);
}


//////////////////////////////////////////////////////////////////////////////////////////
void BishopCrowbanner::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Bishop Crowbanner
//////////////////////////////////////////////////////////////////////////////////////////

{

InitTalk

Begin
""
// If quest has been running for too long.
IF (CheckGlobalFlag(__GLOBAL_QUEST_CROWBANNER_TIMER) <= CurrentRound)
    // Invert illness status and reset timer.
	GiveGlobalFlag(__QUEST_BISHOP_ILLNESS, abs(CheckGlobalFlag(__QUEST_BISHOP_ILLNESS)-1))
	GiveGlobalFlag(__GLOBAL_QUEST_CROWBANNER_TIMER, rnd.roll(dice(1,6))*4 HOURS TDELAY)
ENDIF
IF (CheckGlobalFlag(__QUEST_BISHOP_ILLNESS) == 1)
	Conversation
	INTL( 6171, "I'm in remission, but I need my rest. Please leave me be.")
ELSE
	Conversation
	INTL( 6172, "Oooh... Ow! The pain! P-please... I need help... Ask... Princess Delilah...")
	BREAK
ENDIF

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 3777, "I have no time for this.")
BREAK

CmdAND(INTL( 6126, "RIDDLE"),INTL( 4275, "HINT"))
INTL( 7133, "I'm afraid I have no time for this. If you're interested in riddles, why don't you ask "
"Menark? He's quite fond of riddles. I think he knows the answer to six thousand riddles, "
"so he's got to have the answer to the one that bothers you.")

Command(INTL( 4545, "BISHOP"))
INTL( 6173, "Yes, I am the Bishop Crowbanner.")

Command(INTL( 4547, "CROWBANNER"))
INTL( 6174, "I am the Bishop Crowbanner! If you truly have to say something to me, "
"do it properly by using my holy title.")

CmdAND(INTL( 1999, "GIVE"),INTL( 4648, "APPLE"))
""
IF (CheckItem(__OBJ_POISON_APPLE) >= 1) // Got a poison apple?
	Conversation
	INTL( 6175, "An apple, for me? Thank you, I'm sure it will be very good.")
	GiveGlobalFlag(__QUEST_BISHOP_ILLNESS,0)
	GiveGlobalFlag(__GLOBAL_QUEST_CROWBANNER_TIMER, rnd.roll(dice(1,6))*4 HOURS TDELAY)
	IF (CheckFlag(__QUEST_SEEK_SHADEEN) <= 1) // If PC never gave poison to bishop before:
		GiveFlag(__QUEST_SEEK_SHADEEN, 2)
		IF (USER_KARMA > (-100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
			GiveKarma(-25 * ( 500 + USER_KARMA ) / 500)
		ENDIF
	ENDIF
	TakeItem(__OBJ_POISON_APPLE)
ELSE // Don't got no poison apple to give...
	IF (CheckItem(__OBJ_APPLE) >= 1) //...but got a real one:
		Conversation
		INTL( 6176, "Why, thank you!")
		TakeItem(__OBJ_APPLE)
	ELSE //...and don't got no apple to give either:
		Conversation
		INTL( 6177, "Are you offering me something, or are you asking? I don't understand.")
	ENDIF
ENDIF

Command4(INTL( 509, "BALORK"),INTL( 543, "CURSE"),INTL( 510, "BRAND"),INTL( 1001, "MARK"))
""
IF (CheckFlag(__BALORK_BRAND) == 0)
	Conversation
	INTL( 6178, "It is said that a demon on Arakas has been cursing a great number of heroes.")
ELSE
	Conversation
	INTL( 6179, "I see that you too bear the brand of Balork. Perhaps my pupil, Princess Delilah, "
	"could be of some assistance. Perhaps you should ask her about \"Balork\".")
ENDIF

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 6180, "My name is Crowbanner. My first name is of no concern to you.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 6181, "I am the kingdom's bishop, the highest ranking religious man here.")

Command3(INTL( 700, "SPELL"),INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 7547, "Hmm, I would rather be resting, but I suppose I could teach you some spells.")
CreateSkillList
	//AddTeachSkill (__SPELL_SANCTUARY, 33, 99632) // steph désactivation
	AddTeachSkill (__SPELL_HEALING, 35, 110825)
SendTeachSkillList

Command2(INTL( 4541, "PRINCESS"),INTL( 1005, "DELILAH"))
INTL( 6183, "If only all would be as sweet as her.") 

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 6184, "You make me sick!")
BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 6185, "I need my rest. Goodbye.")
BREAK

Default
INTL( 2492, "I do not understand.")

EndTalk

}
//////////////////////////////////////////////////////////////////////////////////////////
void BishopCrowbanner::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         //TEACH_SKILL(__SPELL_SANCTUARY, 33, 99632) // steph désactivation
         TEACH_SKILL(__SPELL_HEALING, 35, 110825)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE