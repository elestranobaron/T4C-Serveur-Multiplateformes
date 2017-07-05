#pragma hdrstop
#include "RoenGreenleaf.h"

RoenGreenleaf::RoenGreenleaf()
{}

RoenGreenleaf::~RoenGreenleaf()
{}

extern NPCstructure::NPC RoenGreenleafNPC;

void RoenGreenleaf::Create( void )
{
        npc = RoenGreenleafNPC;
        SET_NPC_NAME( "[10914]Roen Greenleaf" );
        npc.InitialPos.X = 800;
        npc.InitialPos.Y = 1110;
        npc.InitialPos.world = 0;
}

void RoenGreenleaf::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk

Begin
""
IF ((CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) >= 14) /*|| (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 15)*/)
        IF (CheckFlag(__FLAG_USER_GOT_ROEN_RING) == 0)
                Conversation
                FORMAT(INTL( 8486, "%s, I dreamt of your visit. You have embarked upon a difficult journey and the trials ahead will be both "
                "glorious and painful. I saw the ghostly image of a winged woman standing at the end of the "
                "room. She said that you might come and that I must give you a ring that will help you during "
                "your journey. When I woke up in the morning, this \"ring\" was there, lying on the table. Heh, I guess "
                "it's yours now."), USER_NAME)
                GiveFlag(__FLAG_USER_GOT_ROEN_RING, 1 )
                GiveItem(__OBJ_RING_OF_THE_SERAPH)
                PRIVATE_SYSTEM_MESSAGE(INTL( 8487, "Roen gives you a ring of the Seraph."))
                ;int nExpReward = 50000;
                PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) )
                GiveXP(nExpReward)
        ELSE
                Conversation
                INTL( 8488, "Greetings! What brings you into these woods?")
        ENDIF
ELSE
        Conversation
        INTL( 8488, "Greetings! What brings you into these woods?")
ENDIF

Command(INTL( 8039, "RING"))
""
IF (CheckFlag(__FLAG_USER_GOT_ROEN_RING) == 1)
        Conversation
        INTL( 8489, "I'm not sure about the magical properties of the Ring of the Seraph but I'll make a wild "
        "guess and say that it protects its wearer against harm.")
        PRIVATE_SYSTEM_MESSAGE(INTL( 8490, "Roen smiles."))
ELSE
        Conversation
        INTL( 8491, "What are you babbling about?")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8492, "The name is Roen Greenleaf but Roen will do just fine.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 8493, "I hunt the wild animals in the forest when I have need of sustenance. I've also "
"learned how to use the forest's vast resources to my advantage. For instance, I "
"know how to mend my wounds using plants and roots found in the forest. If you want, "
"I could \"show\" you how it's done.")

Command3(INTL( 495, "LEARN"),INTL( 496, "TEACH"),INTL( 8494, "SHOW"))
""
IF( UserSkill(__SKILL_FIRST_AID) == 0 )
        IF( USER_LEVEL < 12 )
                IF( USER_TRUE_INT < 20 )
                        IF( USER_TRUE_WIS < 20 )
                                Conversation
                                FORMAT( INTL( 5543, "You need %u more levels, %u more intelligence and %u more wisdom to learn first aid."), 12 - USER_LEVEL, 20 - USER_TRUE_INT, 20 - USER_TRUE_WIS )
                        ELSE
                                Conversation
                                FORMAT( INTL( 5544, "You need %u more levels and %u more intelligence to learn first aid."), 12 - USER_LEVEL, 20 - USER_TRUE_INT )
                        ENDIF
                ELSE
                        IF( USER_TRUE_WIS < 20 )
                                Conversation
                                FORMAT( INTL( 5545, "You need %u more levels and %u more wisdom to learn first aid."), 12 - USER_LEVEL, 20 - USER_TRUE_WIS )
                        ELSE
                                Conversation
                                FORMAT( INTL( 5546, "You need %u more levels to learn first aid."), 12 - USER_LEVEL )
                        ENDIF
                ENDIF
        ELSE
                IF( USER_TRUE_INT < 20 )
                        IF( USER_TRUE_WIS < 20 )
                                Conversation
                                FORMAT( INTL( 5547, "You need %u more intelligence and %u more wisdom to learn first aid."), 20 - USER_TRUE_INT, 20 - USER_TRUE_WIS )
                        ELSE
                                Conversation
                                FORMAT( INTL( 5548, "You need %u more intelligence to learn first aid."), 20 - USER_TRUE_INT )
                        ENDIF
                ELSE
                        IF( USER_TRUE_WIS < 20 )
                                Conversation
                                FORMAT( INTL( 5549, "You need %u more wisdom to learn first aid."), 20 - USER_TRUE_WIS )
                        ELSE
                                Conversation
                                INTL( 2392, "Let's begin.")
                                CreateSkillList
                                        AddTeachSkill( __SKILL_FIRST_AID, 1, 1000 )
                                SendTeachSkillList
                        ENDIF
                ENDIF
        ENDIF
ELSE
        Conversation
        INTL( 5550, "You have already learned first aid.")
ENDIF

Command(INTL( 502, "TRAIN"))
""
IF( UserSkill(__SKILL_FIRST_AID) == 0 )
        Conversation
        INTL( 814, "You must \"learn\" the skill before I can train you.")
ELSEIF( UserSkill(__SKILL_FIRST_AID) < 100 )
        Conversation
        INTL( 1481, "Very good, then let's begin your training.")
        CreateSkillList
                AddTrainSkill( __SKILL_FIRST_AID, 100, 30 )
        SendTrainSkillList
ELSE
        Conversation
        INTL( 5551, "You have learned all I can teach you. You have mastered first aid!")
ENDIF

Command(INTL( 5541, "FIRST AID"))
INTL( 8495, "{The} {first} {aid} {technique} {allows} {a} {character} {to} {mend} {the} {physical} {injuries} "
"{suffered} {during} {combat.} {Note} {that} {the} {skill} {can} {fail,} {worsening} {the} {wounds} "
"{instead} {of} {healing} {them} {and} {that} {first} {aid} {cannot} {be} {performed} {on} {others.} "
"{Level:} {12} {-} {Wis:} {20} {-} {Int:} {20}")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8496, "The young pup bares its fangs, eh? The old wolf will teach you some manners!")
FIGHT

Command4(INTL( 517, "FAREWELL"),INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 519, "LEAVE"))
INTL( 8497, "See you around.")
BREAK

Default
""
IF (rnd.roll(dice(1,2)) == 1)
        Conversation
        INTL( 1623, "I cannot help you with this.")
ELSE
        Conversation
        INTL( 8498, "I care not about this.")
ENDIF

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void RoenGreenleaf::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

        NPC_DATA_TRAIN
                TRAIN_SKILL( __SKILL_FIRST_AID, 100, 30 )
        CLOSE_NPC_DATA_TRAIN

        NPC_DATA_TEACH
                NPC_TEACH_SKILL_LIST
                        TEACH_SKILL (__SKILL_FIRST_AID, 1, 1000)
                CLOSE_NPC_TEACH_SKILL_LIST
        CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE
}
