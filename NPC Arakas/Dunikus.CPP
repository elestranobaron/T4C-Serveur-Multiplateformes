#pragma hdrstop
#include "Dunikus.H"

Dunikus::Dunikus()
{}

Dunikus::~Dunikus()
{}

extern NPCstructure::NPC DunikusNPC;

void Dunikus::Create( void )
{
        npc = ( DunikusNPC );
        SET_NPC_NAME( "[2896]Dunikus Hornwind" );
        npc.InitialPos.X = 2831; 
        npc.InitialPos.Y = 146;
        npc.InitialPos.world = 0;
}

void Dunikus::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT POTION_QUESTION = 1;

InitTalk

Begin
INTL( 661, "Welcome to the druidic camp of the \"Order\" \"of\" \"Nature\".")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 662, "The name is Dunikus Hornwind to you, good adventurer.") 

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 663, "Our work is to preserve nature. It may appear simple, but it is not, for "
"we have to fight foul creatures such as \"goblins\" when they threaten "
"our forest. I have acquired a special talent in brewing \"potions\", and I "
"can even \"teach\" you a new \"spell\" or two.")

Command2(INTL( 4442, "CELESTINA" ),INTL( 4443, "WATERBREEZE"))
INTL( 7298, "Celestina Waterbreeze is my sister. She is a druid also and resides in Raven's Dust.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 664, "Curse that Balork and his Brand! There are many like you who walk the land "
"and bear his mark. I tell you, friend, you have to seek Annabelle, blessed be "
"her eyes! She'll know what to do.")

Command(INTL( 523, "ANNABELLE"))
INTL( 665, "I heard a rumor that she is much older than what she appears to be.")

Command(INTL( 666, "POTION"))
""
IF (CheckNPCFlag (__DUNIKUS_FLASK_FLAG) > CurrentRound)
   Conversation
   INTL( 667, "I would be glad to brew a flask of bluish liquid for you but I lack a few  "
   "special ingredients that only I know where to find them. Come back later if "
   "you want.") 
ELSE
   IF         (CheckFlag(__QUEST_DRUIDIC_FLASK) < 1 )
       Conversation
       INTL( 668, "I have become skilled in the art of brewing potions. My speciality is a bluish "
       "liquid that could heal your wounds. I only need two ingredients: a leaf of a "
       "pink tree and an apple. Do you want me to brew you a small flask?")
       SetYesNo( POTION_QUESTION )

   ELSEIF     (CheckFlag(__QUEST_DRUIDIC_FLASK) == 1)

            IF (CheckItem (__OBJ_APPLE) >= 1 && CheckItem (__OBJ_LEAF_OF_A_PINK_TREE) >= 1 )
                RemFlag(__QUEST_DRUIDIC_FLASK) 
                TakeItem(__OBJ_LEAF_OF_A_PINK_TREE)
                TakeItem(__OBJ_APPLE) 
                GiveItem(__OBJ_FLASK_OF_BLUISH_LIQUID)
                GiveNPCFlag(__DUNIKUS_FLASK_FLAG, rnd.roll( dice( 2, 23 ) ) MINUTES TDELAY)
                Conversation
                INTL( 669, "Thank you my friend. As promised, I give you a flask of bluish liquid that "
                "might someday save your life.")
            ELSEIF (CheckItem (__OBJ_APPLE) >= 1)  // APPLE
                TakeItem(__OBJ_APPLE) 
                GiveFlag (__QUEST_DRUIDIC_FLASK, 2) 
                Conversation
                INTL( 670, "Thank you for the apple, but I still need a leaf of a pink tree if you "
                "want me to finish your potion.")
            ELSEIF (CheckItem (__OBJ_LEAF_OF_A_PINK_TREE) >= 1)  // PINK TREE
                TakeItem(__OBJ_LEAF_OF_A_PINK_TREE)
                GiveFlag (__QUEST_DRUIDIC_FLASK, 3)
                Conversation
                INTL( 671, "Thank you for the leaf, but I still need an apple if you want a flask of my "
                "speciality.")
            ELSE
                Conversation
                INTL( 672, "I still need a leaf from a pink tree and a fresh apple for "
                "the potion.") 
            ENDIF

   ELSEIF (CheckFlag(__QUEST_DRUIDIC_FLASK) == 2)   // ALREADY HAVE APPLE

            IF (CheckItem (__OBJ_LEAF_OF_A_PINK_TREE) >= 1)
                TakeItem(__OBJ_LEAF_OF_A_PINK_TREE)
                GiveItem(__OBJ_FLASK_OF_BLUISH_LIQUID)
                GiveNPCFlag(__DUNIKUS_FLASK_FLAG, rnd.roll( dice( 2, 23 ) ) MINUTES TDELAY)
                RemFlag (__QUEST_DRUIDIC_FLASK)
                Conversation
                INTL( 673, "Thank you my friend. As promised, I give you a flask of bluish liquid that "
                "might someday save your life.")
            ELSE
                Conversation
                INTL( 674, "I need a leaf of a pink tree if you want me to finish your potion.")
            ENDIF

   ELSEIF (CheckFlag(__QUEST_DRUIDIC_FLASK) == 3)   // ALREADY HAVE LEAF

            IF (CheckItem (__OBJ_APPLE) >= 1)
                TakeItem(__OBJ_APPLE)
                GiveItem(__OBJ_FLASK_OF_BLUISH_LIQUID)
                GiveNPCFlag(__DUNIKUS_FLASK_FLAG, rnd.roll( dice( 2, 23 ) ) MINUTES TDELAY)
                RemFlag (__QUEST_DRUIDIC_FLASK)               
                Conversation
                INTL( 675, "Thank you my friend. As promised, I give you a flask of bluish liquid that "
                "might someday save your life.")
            ELSE
                Conversation
                INTL( 676, "I still need an apple if you want a flask of my speciality.")
            ENDIF
   ENDIF
ENDIF

YES (POTION_QUESTION)
        Conversation
        INTL( 677, "Perfect! Gather the two ingredients I require and I shall brew you a potion "
        "and pour it into a small flask.")
        GiveFlag (__QUEST_DRUIDIC_FLASK,1)
 
NO (POTION_QUESTION)
        Conversation
        INTL( 678, "Ah! That is your choice my friend.")

YesNoELSE (POTION_QUESTION)
        Conversation
        INTL( 679, "Sorry, I am getting somewhat deaf these days, was that a yes or a no?")
        SetYesNo (POTION_QUESTION)

Command(INTL( 680, "ORDER OF NATURE"))
INTL( 681, "The Order of Nature is a small community of druids dedicated to the protection "
"of nature and was founded by \"Yrian\" \"Earthsong\".") 

Command2(INTL( 682, "YRIAN"),INTL( 683, "EARTHSONG"))
INTL( 684, "Yrian Earthsong is the Elder of our community. He is our spiritual leader "
"and a man with a great sense of responsibility. If you wish to meet him, "
"his house is located northeast of this camp.")

Command2(INTL( 685, "LANTALIR"),INTL( 686, "RAINMIST"))
INTL( 687, "Lantalir Rainmist is still an apprentice in the \"Order\" \"of\" \"Nature\", but his "
"work is appreciated nevertheless. He learns very fast and has proven to "
"be a great student. Already, he has learned the art of summoning the rain.")

Command2(INTL( 513, "LIGHTHAVEN"),INTL( 514, "WINDHOWL"))
INTL( 688, "We rarely get in contact with the inhabitants of Lighthaven, for they do not "
"share our concerns for nature. The same goes for the citizens of Windhowl.")

Command(INTL( 515, "ARAKAS"))
INTL( 689, "Arakas is the name of this island. The \"Lighthaven\" is located on the south "
"eastern part while \"Windhowl\" is located on the south western part of the "
"island.")

Command(INTL( 475, "STONE OF LIFE"))
INTL( 690, "The Stone of Life is an ordinary stone in which we have poured life energy. "
"The stone can be used as a catalyst for our spells of nature. The burden of "
"guarding it safely lies upon the shoulders of \"Yrian\" \"Earthsong\".")

Command2(INTL( 539, "GOBLIN"),INTL( 691, "UNDEAD"))
INTL( 692, "I do not like goblins and undeads, but the Forest Guardians keep "
"them away from the druidic camp.")

Command2(INTL( 541, "JARKO"),INTL( 693, "NECROMANCER"))
INTL( 694, "The dreaded Jarko sometimes sends \"goblin\" spies in our camp to "
"steal our \"Stone\" \"of\" \"Life\", but I have no fear since \"Yrian\" is guarding it.") 

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 699, "Begone!") BREAK

Command3(INTL( 700, "SPELL"),INTL( 496, "TEACH"),INTL( 495, "LEARN"))
INTL( 7564, "I shall begin instructing you right away.")
CreateSkillList
	AddTeachSkill (__SPELL_LIGHTNING_BOLT, 10, 10425)
	AddTeachSkill (__SPELL_CALL_LIGHTNING, 13, 27508)
SendTeachSkillList

Command3(INTL( 517, "FAREWELL"),INTL( 518, "BYE"),INTL( 519, "LEAVE"))
INTL( 727, "Farewell my friend, be watchful of \"goblins\".") BREAK

Default
INTL( 728, "Really? I did not know about this.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Dunikus::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_LIGHTNING_BOLT, 10, 10425)
         TEACH_SKILL(__SPELL_CALL_LIGHTNING, 13, 27508)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE
