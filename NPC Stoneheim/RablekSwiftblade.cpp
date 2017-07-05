#pragma hdrstop
#include "RablekSwiftblade.h"

RablekSwiftblade::RablekSwiftblade()
{}

RablekSwiftblade::~RablekSwiftblade()
{}

extern NPCstructure::NPC RablekSwiftbladeNPC;

void RablekSwiftblade::Create( void )
{
    npc = RablekSwiftbladeNPC;
    SET_NPC_NAME( "[10907]Rablek Swiftblade" );
    npc.InitialPos.X = 120;
    npc.InitialPos.Y = 1555;
    npc.InitialPos.world = 1;
}

void RablekSwiftblade::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
INTL( 8447, "What is your problem?")

Command2(INTL( 8448, "RABLEK"),INTL( 8449, "SWIFTBLADE"))
INTL( 8450, "Yes, Rablek is the name. I am the swiftest blade gold can buy around here. Using "
"a special \"technique\" I have learned a while ago, I am able to deliver "
"harmful blows even against an armored opponent.")

Command(INTL( 8451, "TECHNIQUE"))
INTL( 8452, "The technique is known as \"armor\" \"penetration\". I might \"teach\" this skill "
"to you if you're willing to pay the price.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8453, "You haven't heard of me before? I am Rablek Swiftblade, the renowned thief.")

Command3(INTL( 487, "OCCUPATION"),INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"))
INTL( 8454, "Curiosity is a bad habit. Around here, we do what we have to do and we "
"keep our mouth shut about it.")

Command2(INTL( 495, "LEARN"),INTL( 496, "TEACH"))
""
IF( UserSkill(__SKILL_ARMOR_PENETRATION) == 0 )
	IF( USER_LEVEL < 25 )
		IF( USER_TRUE_STR < 75 )
			IF( USER_TRUE_AGI < 40 )
				IF( USER_TRUE_INT < 30 )
					Conversation
					FORMAT( INTL( 3884, "You need %u more levels, %u more strength, %u more agility and %u more intelligence to learn armor penetration."), 25 - USER_LEVEL, 75 - USER_TRUE_STR, 40 - USER_TRUE_AGI, 30 - USER_TRUE_INT )
				ELSE
					Conversation
					FORMAT( INTL( 3885, "You need %u more levels, %u more strength and %u more agility to learn armor penetration."), 25 - USER_LEVEL, 75 - USER_TRUE_STR, 40 - USER_TRUE_AGI )
				ENDIF
			ELSE
				IF( USER_TRUE_INT < 30 )
					Conversation
					FORMAT( INTL( 3886, "You need %u more levels, %u more strength and %u more intelligence to learn armor penetration."), 25 - USER_LEVEL, 75 - USER_TRUE_STR, 30 - USER_TRUE_INT )
				ELSE
					Conversation
					FORMAT( INTL( 3887, "You need %u more levels and %u more strength to learn armor penetration."), 25 - USER_LEVEL, 75 - USER_TRUE_STR )
				ENDIF
			ENDIF
		ELSE
			IF( USER_TRUE_AGI < 40 )
				IF( USER_TRUE_INT < 30 )
					Conversation
					FORMAT( INTL( 3888, "You need %u more levels, %u more agility and %u more intelligence to learn armor penetration."), 25 - USER_LEVEL, 40 - USER_TRUE_AGI, 30 - USER_TRUE_INT )
				ELSE
					Conversation
					FORMAT( INTL( 3889, "You need %u more levels and %u more agility to learn armor penetration."), 25 - USER_LEVEL, 40 - USER_TRUE_AGI )
				ENDIF
			ELSE
				IF( USER_TRUE_INT < 30 )
					Conversation
					FORMAT( INTL( 3890, "You need %u more levels and %u more intelligence to learn armor penetration."), 25 - USER_LEVEL, 30 - USER_TRUE_INT )
				ELSE
					Conversation
					FORMAT( INTL( 3891, "You need %u more levels to learn armor penetration."), 25 - USER_LEVEL )
				ENDIF
			ENDIF
		ENDIF
	ELSE
		IF( USER_TRUE_STR < 75 )
			IF( USER_TRUE_AGI < 40 )
				IF( USER_TRUE_INT < 30 )
					Conversation
					FORMAT( INTL( 3892, "You need %u more strength, %u more agility and %u more intelligence to learn armor penetration."), 75 - USER_TRUE_STR, 40 - USER_TRUE_AGI, 30 - USER_TRUE_INT )
				ELSE
					Conversation
					FORMAT( INTL( 3893, "You need %u more strength and %u more agility to learn armor penetration."), 75 - USER_TRUE_STR, 40 - USER_TRUE_AGI )
				ENDIF
			ELSE
				IF( USER_TRUE_INT < 30 )
					Conversation
					FORMAT( INTL( 3894, "You need %u more strength and %u more intelligence to learn armor penetration."), 75 - USER_TRUE_STR, 30 - USER_TRUE_INT )
				ELSE
					Conversation
					FORMAT( INTL( 3895, "You need %u more strength to learn armor penetration."), 75 - USER_TRUE_STR )
				ENDIF
			ENDIF
		ELSE
			IF( USER_TRUE_AGI < 40 )
				IF( USER_TRUE_INT < 30 )
					Conversation
					FORMAT( INTL( 3896, "You need %u more agility and %u more intelligence to learn armor penetration."), 40 - USER_TRUE_AGI, 30 - USER_TRUE_INT )
				ELSE
					Conversation
					FORMAT( INTL( 3897, "You need %u more agility to learn armor penetration."), 40 - USER_TRUE_AGI )
				ENDIF
			ELSE
				IF( USER_TRUE_INT < 30 )
					Conversation
					FORMAT( INTL( 3898, "You need %u more intelligence to learn armor penetration."), 30 - USER_TRUE_INT )
				ELSE
					Conversation
					INTL( 1479, "Very good, this is what I can teach you.")
					CreateSkillList
						AddTeachSkill( __SKILL_ARMOR_PENETRATION, 1, 7500 )
					SendTeachSkillList
				ENDIF
			ENDIF
		ENDIF
	ENDIF
ELSE
   Conversation
	INTL( 3899, "You have already learned armor penetration.")
ENDIF

Command(INTL( 502, "TRAIN"))
""
IF( UserSkill(__SKILL_ARMOR_PENETRATION) == 0 )
	Conversation
	INTL( 814, "You must \"learn\" the skill before I can train you.")
ELSEIF( UserSkill(__SKILL_ARMOR_PENETRATION) < 100 )
	Conversation
	INTL( 1481, "Very good, then let's begin your training.")
	CreateSkillList
		AddTrainSkill( __SKILL_ARMOR_PENETRATION, 100, 300 )
	SendTrainSkillList
ELSE
   Conversation
	INTL( 3900, "I have taught you all I know. You are already a master of armor penetration!")
ENDIF

Command(INTL( 3901, "ARMOR PENETRATION"))
INTL( 8455, "{The} {armor} {penetration} {technique} {allows} {a} {character} {to} {pinpoint} {the} {weak} "
"{spot} {in} {his} {opponent's} {armor,} {thus} {reducing} {its} {effectiveness} {in} {absorbing} "
"{damage.} {The} {use} {of} {this} {skill} {is} {automatic.} {Level:} {25} {-} {Str:} {75} {-} "
"{Agi:} {40} {-} {Int:} {30}")

Command2(INTL( 8456, "DANTALIR"),INTL( 8457, "SONGWEAVER"))
INTL( 8458, "That's the guy over there who thinks he has some musical talent but "
"obviously does NOT.")

Command5(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "),INTL( 8459, " DICK "))
INTL( 8460, "Your tongue will get you killed someday.")
BREAK

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 8461, "About time!")
BREAK

Command(INTL( 3771, "?"))
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 8462, "Didn't I tell you that curiosity is a bad habit?")
ELSE
   Conversation
   INTL( 8463, "Do I look like someone who knows everything or what?")
ENDIF

Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 8464, "This is nonsense.")
ELSE
   Conversation
	INTL( 5910, "What was that you said?")   
ENDIF

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void RablekSwiftblade::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
{

	int nValue = 2 * ( USER_LEVEL - 24 );
	IF( nValue > 100 )
		nValue = 100;
	ENDIF

NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL( __SKILL_ARMOR_PENETRATION, 1, 7500 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH
	   
	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_ARMOR_PENETRATION, 100, 300 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
}


