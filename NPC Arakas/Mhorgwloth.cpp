//////////////////////////////////////////////////////////////////////
// Mhorgwloth.cpp: implementation of Jarko
//
//////////////////////////////////////////////////////////////////////

#pragma hdrstop
#include "Mhorgwloth.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mhorgwloth::Mhorgwloth()
{}

Mhorgwloth::~Mhorgwloth()
{}

extern NPCstructure::NPC _Mhorgwloth;

//////////////////////////////////////////////////////////////////////////////////////////
void Mhorgwloth::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Mhorgwloth
//
{
	npc = _Mhorgwloth;
	SET_NPC_NAME( "[2903]Mhorgwloth the troll" );
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}

void Mhorgwloth::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
        IF( CheckFlag(__TROLL_QUEST_DONE) == 1 )
            GiveFlag(__TROLL_QUEST_DONE, 2)
        ENDIF
		// Mhorgwloth is a good guy...
		IF (USER_KARMA >= (-100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
			GiveKarma(-3*(500+USER_KARMA)/500)
		ENDIF
    }
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Mhorgwloth::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Mhorgwloth
//  
//
{
CONSTANT DIAMOND = 1;

InitTalk

Begin
INTL( 474, "Mhorgwloth! You ugly.")

Command(INTL( 475, "STONE OF LIFE")) 
""
IF ((CheckGlobalFlag (__QUEST_STONE_OF_LIFE) > 1) && (CheckGlobalFlag (__WHO_HAS_THE_STONE_FLAG) == 2))
	IF (CheckGlobalFlag (__TROLL_STONE_OF_LIFE) == 5 )
		Conversation
		INTL( 476, "Mhorgwloth not have shiny rock. Mhorgwloth gave rock. ")
	ELSE
		Conversation
		INTL( 477, "Mhorgwloth give life of stone for shiny diamond. Mhorgwloth say. Yessh or Nowhlop?")
		SetYesNo(DIAMOND)
	ENDIF
ELSE
	Conversation
	INTL( 478, "Awhlop! Mhorgwloth! Me like shiny rocks! Mhorgwloth!")
ENDIF

YES (DIAMOND)
        IF (CheckItem (__OBJ_DIAMOND) > 0)  // DIAMOND
            GiveGlobalFlag(__TROLL_STONE_OF_LIFE, 5 )
            TakeItem(__OBJ_DIAMOND) 
            Conversation
            INTL( 479, "Mhorgwloth happy! Mhorgwloth give rock.")
            GiveItem(__OBJ_STONE_OF_LIFE)
            GetItemHandle(__OBJ_STONE_OF_LIFE, StoneOfLife)
            GiveUnitFlag (StoneOfLife, __ITEM_QUEST_STONE_OF_LIFE, CheckGlobalFlag( __QUEST_STONE_OF_LIFE ))
        ELSE
            Conversation
            INTL( 480, "You not have diamond. Awshlop! You die.")
            FIGHT
        ENDIF

NO (DIAMOND)
            Conversation
            INTL( 481, "Shiny rock good taste! Mhorgwloth want shiny rock. Mhorgwloth kill!")
            FIGHT

YesNoELSE(DIAMOND)
            Conversation
            INTL( 482, "Mhorgwloth want shiny rock. Mhorgwloth kill!")
            FIGHT

Command3(INTL( 483, "NAME"),INTL( 484, "MHORGWLOTH"),INTL( 485, "WHO ARE YOU"))
INTL( 486, "Mhorgwloth! Mhorgwloth! Mhorgwloth!")

Command3(INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"),INTL( 489, "WORK"))
INTL( 490, "Whorc? Mhorwgloth don't know. Mhorgwloth dumb. Only thing Mhorgwloth do is \"grow\"!")

Command(INTL( 491, "GROW"))
INTL( 492, "GRRR! Evil king chop Mhorgwloth arm! But arm grow back! Mhorgwloth \"special\".")

Command(INTL( 493, " SPECIAL "))
INTL( 494, "You want special too? Mhorgwloth \"teach\" you.")

Command2(INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 500, "Me teach now.")
CreateSkillList
	AddTeachSkill( __SKILL_RAPID_HEALING, 1, 5000 )
SendTeachSkillList

Command(INTL( 502, "TRAIN"))
INTL( 504, "Me train now.") 
CreateSkillList
	AddTrainSkill( __SKILL_RAPID_HEALING, 100, 200 )
SendTrainSkillList

Command(INTL( 507, "ORKANIS"))
INTL( 508, "Mhorgwloth too strong for small humans. Mhorgwloth killed king.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 512, "Balork's Brand? Me not understand! Awhlop!")

Command3(INTL( 513, "LIGHTHAVEN"),INTL( 514, "WINDHOWL"),INTL( 515, "ARAKAS"))
INTL( 516, "Isshhhh! Awhlop! Town.. human town. Me don't like human!")

Command5(INTL( 517, "FAREWELL"),INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 522, "Mhorgwloth! Awhlop!")
BREAK

Command(INTL( 523, "ANNABELLE"))
INTL( 524, "Mhorgwloth not know her. Only know \"pretty\" \"lady\".")

Command2(INTL( 525, "PRETTY"),INTL( 526, "LADY"))
INTL( 527, "Huh huh huh... Awhlop! Pretty lady! Huh huh...")

Default
INTL( 528, "Awhlop! Swloph!")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Mhorgwloth::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Rolph data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL( __SKILL_RAPID_HEALING, 1, 5000 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_RAPID_HEALING, 100, 200 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
}
