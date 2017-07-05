//////////////////////////////////////////////////////////////////////
// Uranos.cpp: implementation of the Uranos class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Uranos.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Uranos::Uranos()
{}

Uranos::~Uranos()
{}

extern NPCstructure::NPC UranosNPC;

void Uranos::Create(){
    npc = UranosNPC;
    SET_NPC_NAME( "[3060]Uranos" );
    npc.InitialPos.X = 2975;
    npc.InitialPos.Y = 950;
    npc.InitialPos.world = 0;
}

void Uranos::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	switch(rnd(0, 1)){
	case 0: SHOUT(INTL( 1378, "AHHHHHHHHHHHHHH!")); break;
	case 1: SHOUT(INTL( 1379, "HELP!")); break;
	}

	self->Do(flee);
	self->SetTarget(target);
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Uranos::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT BAT = 1;

InitTalk

Begin
INTL( 2073, "Yes? You seek knowledge?  Then maybe I can help you.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2074, "I am Uranos, guardian of all the knowledge stored inside the mage's \"tower\" "
"of Lighthaven.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2075, "I have the neverending task of collecting information and transcribing it "
"into \"books\", so that others in search of knowledge may come here to learn. "
"I am somewhat busy currently, I need the last component for my spell, but "
"I do not remember the final \"ingredient\". I think my friend Marsac Cred "
"in Windhowl knows which one though.")
IF (CheckFlag (__QUEST_URANOS) == 0 )
    GiveFlag (__QUEST_URANOS, 1 )
ENDIF

Command(INTL( 523, "ANNABELLE"))
INTL( 1158, "I do not know much about that woman.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2670, "Balork's Brand? Huh?")

Command(INTL( 2076, "INGREDIENT"))
INTL( 2077, "Yes... I wonder what it is...")

Command(INTL( 2078, "BAT WING"))
""
IF (CheckFlag (__QUEST_URANOS) == 2 )
    Conversation
    INTL( 2079, "Ah yes... Bat wings... Now I remember. But you've already helped me "
    "my friend!")
ELSEIF (CheckFlag (__QUEST_URANOS) == 1 )
	IF (CheckNPCFlag (__URANOS_DELAY_FLAG) > CurrentRound)
		Conversation
		INTL( 2080, "Ah, you found the ingredient I need, but I have plenty enough for now.")
	ELSE
		Conversation
		INTL( 2081, "Bat wings? Did Marsac Cred tell you or did you discover that all by yourself? "
		"Oh well, it doesn't matter. Would you like to give me a few bat wings?")
		SetYesNo(BAT)
	ENDIF
ELSE
	Conversation
	INTL( 2082, "Bat wings... I do not understand what you mean!") 
ENDIF

YES (BAT)
IF (CheckItem (__OBJ_DECAYING_BAT_WINGS) > 0)   
	;int nBats = CheckItem(__OBJ_DECAYING_BAT_WINGS); 
   FOR( 0, nBats )
      TakeItem(__OBJ_DECAYING_BAT_WINGS) 
   ENDFOR
   Conversation
   INTL( 2083, "Thank you for the bat wings, I really appreciate your help. Here, Let me give you "
   "a small skull dagger. {You} {have} {been} {awarded} {2500} {experience} {points.}")
   GiveXP(2500)
   GiveFlag(__QUEST_URANOS, 2)
   GiveItem (__OBJ_SKULL_DAGGER_2)
   GiveNPCFlag(__URANOS_DELAY_FLAG, (rnd.roll( dice( 2, 15, 5 ) ) ) MINUTES TDELAY)
ELSE
   Conversation
   INTL( 2084, "Fool! You do not even have bat wings!")
ENDIF

NO(BAT)
Conversation
INTL( 2085, "That's your decision, I understand. I think.")

YesNoELSE(BAT)
Conversation
INTL( 2086, "*sigh* Tell me when you make up your mind.")

Command(INTL( 1686, "TOWER"))
INTL( 2087, "The towers of magic are places where knowledge is stored. Whatever we find "
"in our travels is written in books that are kept in our library. We can "
"also teach \"magic\" to those who wish to learn it.")

Command(INTL( 1427, "BOOK"))
INTL( 2088, "Yes, we have quite a collection here I must say. A few hundred books, at least.")

Command(INTL( 1096, "MAGIC"))
INTL( 2089, "Ah? You are a scholar interested in the ways of magic? Perhaps I could \"teach\" "
"you a \"spell\" or two... If I can find the time.")

Command3(INTL( 700, "SPELL"),INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 7527, "You wish to increase your knowledge of spells? Very well, I shall help you.")
CreateSkillList
	AddTeachSkill (__SPELL_STONE_SHARD, 6, 1328)
	AddTeachSkill (__SPELL_SHATTER, 11, 14292)
SendTeachSkillList

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 1075, "Farewell.") BREAK

Default
INTL( 2112, "Magic could help you.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Uranos::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_STONE_SHARD, 6, 1328)
         TEACH_SKILL(__SPELL_SHATTER, 11, 14292)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE

