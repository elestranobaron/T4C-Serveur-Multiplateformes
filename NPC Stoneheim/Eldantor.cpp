#pragma hdrstop
#include "Eldantor.h"

Eldantor::Eldantor()
{}

Eldantor::~Eldantor()
{}

extern NPCstructure::NPC EldantorNPC;

void Eldantor::Create( void )
{
        npc = EldantorNPC;
        SET_NPC_NAME( "[10849]A wandering mage" );
        npc.InitialPos.X = 343;
        npc.InitialPos.Y = 766;
        npc.InitialPos.world = 0;
}

void Eldantor::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT MAGICSCRIPTINGKIT = 1; 

InitTalk

Begin
INTL( 1230, "Greetings, my friend.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8095, "The name is Eldantor to you.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 8096, "I wander around the world to quench my insatiable thirst for knowledge. I am an experienced mage and "
"could probably teach you the art of \"meditation\" if you wish to learn it. Furthermore, I am also a "
"great \"arcane\" \"scribe\" and may be of assistance if you are interested in magical lore.")

Command2(INTL( 554, "HELP"),INTL( 4275, "HINT"))
INTL( 8097, "I can't help you with whatever it is you need, but if it's advice you seek, perhaps you "
"should consult Chryseida Yolangda, the old gypsy. Careful, though. The more advice you "
"seek, the more she charges you for her services. Guess that's just the way the world is, eh?")

Command(INTL( 1383, "ARCANE SCRIBE"))
INTL( 8098, "Arcane scribes can use a \"magic\" \"scripting\" \"kit\" in order to inscribe powerful symbols of magic "
"into a blank magical tome.")

Command(INTL( 8099, "BLANK MAGIC TOME"))
INTL( 8100, "I have none left.")

Command(INTL( 8101, "TOME OF VALOR"))
INTL( 8102, "If you need a Tome of Valor, I heard of a mage who goes by the name of \"Liurn\" \"Clar\" "
	  "would be most suitable for the task.") 	  

CmdAND(INTL( 10212, "LIURN"),INTL( 10213, "CLAR")) 
INTL( 10214, "I think Liurn Clar resides in WindHowl.")

Command(INTL( 8103, "MAGIC SCRIPTING KIT"))
INTL( 8104, "I doubt you have enough talent in the Art to use it but if you insist on having one, I could probably sell "
"you one for a mere 20,000 gold pieces. So, do you wish to buy a magic scripting kit from me?") 
SetYesNo(MAGICSCRIPTINGKIT)

YES(MAGICSCRIPTINGKIT)
	IF	(Gold < 20000) 
		Conversation
		INTL( 8105, "I won't sell you a brand new magic scripting kit for less than 20,000 gold pieces.")
	ELSE	
		Conversation															  
		INTL( 8106, "You're the proud owner of a brand new magic scripting kit!") 
		TakeGold(20000)
		GiveItem(__OBJ_MAGIC_SCRIPTING_KIT) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 8107, "You give 20000 gold to Eldantor.")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 8108, "Eldantor gives you a magic scripting kit.")) 
	ENDIF
	
NO(MAGICSCRIPTINGKIT) 
	Conversation
	INTL( 8109, "You know where to find me if you ever change your mind.")

YesNoELSE(MAGICSCRIPTINGKIT)
	Conversation
	INTL( 8110, "Do you wish to buy a magic scripting kit?")
	SetYesNo(MAGICSCRIPTINGKIT)

Command(INTL( 5628, "ORACLE"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) >= 1)
	Conversation
	INTL( 8111, "If you need to seek your true destiny, he can definitely help you... if you find him.")
ELSE
	Conversation
	INTL( 8112, "The Oracle? I'm not sure...")
ENDIF

Command(INTL( 803, "MEDITATION"))
INTL( 8113, "To \"meditate\" is to heal the soul. The art of meditation is a discipline that takes time to master. "
"If you wish, I could \"teach\" you how to use it.")

Command2(INTL( 495, "LEARN"),INTL( 496, "TEACH"))
""
IF( UserSkill(__SKILL_MEDITATE) == 0 )
	IF( USER_LEVEL < 16 )
		IF( USER_TRUE_INT < 30 )
			IF( USER_TRUE_WIS < 30 )
				Conversation
				FORMAT(INTL( 805, "You need %u more levels, %u more intelligence and %u more wisdom to learn meditate."), 16 - USER_LEVEL, 30 - USER_TRUE_INT, 30 - USER_TRUE_WIS )
			ELSE
				Conversation
				FORMAT(INTL( 806, "You need %u more levels and %u more intelligence to learn meditate."), 16 - USER_LEVEL, 30 - USER_TRUE_INT )
			ENDIF
		ELSE
			IF( USER_TRUE_WIS < 30 )
				Conversation
				FORMAT(INTL( 807, "You need %u more levels and %u more wisdom to learn meditate."), 16 - USER_LEVEL, 30 - USER_TRUE_WIS )
			ELSE
				Conversation
				FORMAT(INTL( 808, "You need %u more levels to learn meditate."), 16 - USER_LEVEL )
			ENDIF
		ENDIF
	ELSE
		IF( USER_TRUE_INT < 30 )
			IF( USER_TRUE_WIS < 30 )
				Conversation
				FORMAT( INTL( 809, "You need %u more intelligence and %u more wisdom to learn meditate."), 30 - USER_TRUE_INT, 30 - USER_TRUE_WIS )
			ELSE
				Conversation
				FORMAT(INTL( 810, "You need %u more intelligence to learn meditate."), 30 - USER_TRUE_INT )
			ENDIF
		ELSE
			IF( USER_TRUE_WIS < 30 )
				Conversation
				FORMAT(INTL( 811, "You need %u more wisdom to learn meditate."), 30 - USER_TRUE_WIS )
			ELSE
				Conversation
				INTL( 812, "Very good, let us begin then.")
				CreateSkillList
					AddTeachSkill( __SKILL_MEDITATE, 1, 3000 )
				SendTeachSkillList
			ENDIF
		ENDIF
	ENDIF
ELSE
	Conversation
	INTL( 813, "You have already learned meditate.")
ENDIF

Command(INTL( 502, "TRAIN"))
""
IF( UserSkill(__SKILL_MEDITATE) == 0 )
	Conversation
	INTL( 814, "You must \"learn\" the skill before I can train you.")
ELSEIF( UserSkill(__SKILL_MEDITATE) < 100 )
	Conversation
	INTL( 815, "Very good, then let us begin your training.")
	CreateSkillList
		AddTrainSkill( __SKILL_MEDITATE, 100, 100 )
	SendTrainSkillList
ELSE
	Conversation
	INTL( 817, "You have learned well, I am pleased. A master of meditation, you are.")
ENDIF

Command(INTL( 818, "MEDITATE"))
INTL( 8114, "{The} {meditate} {technique} {increases} {a} {character's} {ability} {to} {regain} {lost} {mana.} "
"{Once} {initiated,} {the} {skill} {is} {effective} {until} {the} {character} {moves,} {attacks,} {casts} "
"{a} {spell} {or} {performs} {any} {other} {action.} {Level:} {16} {-} {Int:} {30} {-} {Wis:} {30}")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8115, "You must be so proud of yourself.")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8116, "Farewell. I shall return to my \"meditation\".")
BREAK

Command(INTL( 3771, "?"))
INTL( 8117, "Even I do not possess all the answers.")

Default
""
IF (rnd.roll(dice(1,2) ) == 1)
   Conversation
   INTL( 8118, "I do not think that this concerns me.")
ELSE
   Conversation
   INTL( 5758, "I have no interest in that matter.")
ENDIF
EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Eldantor::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL( __SKILL_MEDITATE, 1, 3000 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

	NPC_DATA_TRAIN		
		TRAIN_SKILL( __SKILL_MEDITATE, 100, 100 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
}
