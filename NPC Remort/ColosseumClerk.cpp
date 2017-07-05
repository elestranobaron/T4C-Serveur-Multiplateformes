// Colosseum clerk
///////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "ColosseumClerk.h"

ColosseumClerk::ColosseumClerk()
{}

ColosseumClerk::~ColosseumClerk()
{}

extern NPCstructure::NPC ColosseumClerkNPC;

void ColosseumClerk::Create( void )
{
      npc = ( ColosseumClerkNPC );
      SET_NPC_NAME( "[10969]A busy-looking clerk" );  
      npc.InitialPos.X = 1730; 
      npc.InitialPos.Y = 1830;
      npc.InitialPos.world = 0;
}

void ColosseumClerk::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
} 

void ColosseumClerk::OnTalk( UNIT_FUNC_PROTOTYPE )
///////////////////////////////////////////////////////////////////////////

{

InitTalk

CONSTANT Arena = 1;
CONSTANT SpendTokensOrFight = 2;
CONSTANT PurchaseGoods = 3;
CONSTANT NumberOfOpponents = 4;
CONSTANT LevelSelection = 5;
CONSTANT BuySomethingElse = 6;
CONSTANT PurchaseExpensiveGoods = 7;
CONSTANT LeaveArenaOrFight = 8;


Begin
""
IF (IsInRange(8)) 
	IF(CheckFlag(__FLAG_USER_LEVEL_SLICE) == 0)
	IF(USER_LEVEL <= 40)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 40)
		GiveFlag(__FLAG_ARENA_LEVEL, 40)
	ELSEIF(USER_LEVEL <= 50)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 50)
		GiveFlag(__FLAG_ARENA_LEVEL, 50)
	ELSEIF(USER_LEVEL <= 60)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 60)
		GiveFlag(__FLAG_ARENA_LEVEL, 60)
	ELSEIF(USER_LEVEL <= 70)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 70)
		GiveFlag(__FLAG_ARENA_LEVEL, 70)
	ELSEIF(USER_LEVEL <= 80)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 80)
		GiveFlag(__FLAG_ARENA_LEVEL, 80)
	ELSEIF(USER_LEVEL <= 90)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 90)
		GiveFlag(__FLAG_ARENA_LEVEL, 90)
	ELSEIF(USER_LEVEL <= 100)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 100)
		GiveFlag(__FLAG_ARENA_LEVEL, 100)
	ELSEIF(USER_LEVEL <= 110)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 110)
		GiveFlag(__FLAG_ARENA_LEVEL, 110)
	ELSEIF(USER_LEVEL <= 120)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 120)
		GiveFlag(__FLAG_ARENA_LEVEL, 120)
	ELSEIF(USER_LEVEL <= 130)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 130)
		GiveFlag(__FLAG_ARENA_LEVEL, 130)
	ELSEIF(USER_LEVEL <= 140)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 140)
		GiveFlag(__FLAG_ARENA_LEVEL, 140)
	ELSEIF(USER_LEVEL <= 150)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 150)
		GiveFlag(__FLAG_ARENA_LEVEL, 150)
	ELSEIF(USER_LEVEL <= 160)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 160)
		GiveFlag(__FLAG_ARENA_LEVEL, 160)
	ELSEIF(USER_LEVEL <= 170)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 170)
		GiveFlag(__FLAG_ARENA_LEVEL, 170)
	ELSEIF(USER_LEVEL <= 180)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 180)
		GiveFlag(__FLAG_ARENA_LEVEL, 180)
	ELSEIF(USER_LEVEL <= 190)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 190)
		GiveFlag(__FLAG_ARENA_LEVEL, 190)
	ELSEIF(USER_LEVEL <= 200)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 200)
		GiveFlag(__FLAG_ARENA_LEVEL, 200)
	ELSEIF(USER_LEVEL <= 225)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 225)
		GiveFlag(__FLAG_ARENA_LEVEL, 225)
	ELSEIF(USER_LEVEL <= 250)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 250)
		GiveFlag(__FLAG_ARENA_LEVEL, 250)
	ELSEIF(USER_LEVEL <= 275)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 275)
		GiveFlag(__FLAG_ARENA_LEVEL, 275)
	ELSEIF(USER_LEVEL <= 300)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 300)
		GiveFlag(__FLAG_ARENA_LEVEL, 300)
	ELSEIF(USER_LEVEL <= 325)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 325)
		GiveFlag(__FLAG_ARENA_LEVEL, 325)
	ELSEIF(USER_LEVEL <= 350)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 350)
		GiveFlag(__FLAG_ARENA_LEVEL, 350)
	ELSEIF(USER_LEVEL <= 375)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 375)
		GiveFlag(__FLAG_ARENA_LEVEL, 375)
	ELSEIF(USER_LEVEL <= 400)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 400)
		GiveFlag(__FLAG_ARENA_LEVEL, 400)
	ELSEIF(USER_LEVEL <= 425)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 425)
		GiveFlag(__FLAG_ARENA_LEVEL, 425)
	ELSEIF(USER_LEVEL <= 450)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 450)
		GiveFlag(__FLAG_ARENA_LEVEL, 450)
	ELSEIF(USER_LEVEL <= 475)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 475)
		GiveFlag(__FLAG_ARENA_LEVEL, 475)
	ELSEIF(USER_LEVEL <= 500)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 500)
		GiveFlag(__FLAG_ARENA_LEVEL, 500)
	ENDIF
ENDIF
IF(CheckGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA) > 0)
	Conversation
	INTL( 10683, "I cannot help you until all the monsters have been defeated.")
	BREAK
ELSEIF(CheckFlag(__FLAG_USER_HAS_SPOKEN_TO_COLOSSEUM_CLERK) >= 1)
	IF(CheckFlag(__FLAG_USER_HAS_READ_COLOSSEUM_INSTRUCTIONS) == 0)
	Conversation
		FORMAT(INTL( 10684, "Welcome back %s. If you are here to fight, I must explain the \"procedures\" before we can begin."), USER_NAME)
	ELSE
		IF(CheckItem(__OBJ_COLOSSEUM_TOKEN) >= 5)
			Conversation
			INTL( 10685, "I see you have acquired at least 5 tokens. You may \"spend\" these right now, \"continue\" fighting or \"leave\" the "
			"arena.")
			;YesNo = SpendTokensOrFight;
		ELSE
			IF(CheckFlag(__FLAG_USER_LEVEL_SLICE) == 0)
				Conversation
				FORMAT(INTL( 10686, "Welcome back %s. I trust you are well? Good, good. Will you be fighting in the arena today?"), USER_NAME)
				SetYesNo(Arena)
			ELSE
				Conversation
				FORMAT(INTL( 10687, "Your current level of difficulty is %u. Would you like to \"increase\", \"decrease\" or \"leave\" it as is?"), CheckFlag(__FLAG_USER_LEVEL_SLICE))
				;YesNo = LevelSelection;
			ENDIF
		ENDIF
	ENDIF
ELSE
	Conversation
	INTL( 10688, "Ah! A new contestant! Welcome to the \"colosseum\", my friend.")
ENDIF
ELSE
	Conversation
	INTL( 11665, "You must come closer if you want to talk to me.")
	BREAK
ENDIF 


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// SpendTokensOrFight /////////////////////////////////////////////////

;} else if( ( msg.Find( INTL( 10690, "SPEND") ) != -1 ) && YesNo == SpendTokensOrFight) {;
Conversation
INTL( 10691, "I offer a small variety of upgrades to your abilities. For a mere 5 tokens, you can purchase a \"complete\" \"restoration\". "
"For 10 tokens, you can purchase either a \"physical\" \"defense\" or a \"magical\" \"defense\" upgrade. For 15 tokens, you "
"can purchase either a \"physical\" \"offense\" or a \"magical\" \"offense\" upgrade. You may also purchase \"everything\" in "
"one \"package\", which will only cost you 40 tokens. What would you like to purchase?")
;YesNo = PurchaseGoods;

;} else if( ( msg.Find( INTL( 10692, "CONTIN") ) != -1 ) && YesNo == SpendTokensOrFight) {;
Conversation
FORMAT(INTL( 10693, "Your current level of difficulty is %u. Would you like to \"increase\", \"decrease\" or \"leave\" it as is?"), CheckFlag(__FLAG_USER_LEVEL_SLICE))
;YesNo = LevelSelection;

;} else if( ( msg.Find( INTL( 519, "LEAVE") ) != -1 ) && YesNo == SpendTokensOrFight) {;
Conversation
FORMAT(INTL( 10694, "As always it was a pleasure having you here, %s. You are welcome to come again!"), USER_NAME)
CastSpellTarget(__SPELL_NPC_CANTRIP_FLAK)
TELEPORT(343, 492, 0)
;YesNo = 0;
BREAK

;} else if(YesNo == SpendTokensOrFight) {;
Conversation
INTL( 10695, "You may \"spend\" your tokens right now, \"continue\" to fight or \"leave\" the arena. What will you do?")

//////////////////////////////////////////////// SpendTokensOrFight /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////// LevelSelection ///////////////////////////////////////////////////

;} else if( ( msg.Find( INTL( 9873, "INCREAS") ) != -1 ) && YesNo == LevelSelection) {;
IF(CheckFlag(__FLAG_ARENA_LEVEL) < CheckFlag(__FLAG_USER_LEVEL_SLICE))
	Conversation
	INTL( 11641, "It seems you did not actively participate in the last battle. Because of this, I must leave your difficulty level as is. "
	"How many opponents will you be fighting?")
	;YesNo = NumberOfOpponents;
ELSEIF(CheckFlag(__FLAG_USER_HAS_CHANGED_DIFFICULTY_LEVEL) == 1)
	Conversation
	INTL( 10696, "You have already changed the level of difficulty. You may not do so again until you have fought with your current "
	"settings. Now, how many opponents will you be fighting?")
	;YesNo = NumberOfOpponents;
ELSEIF(CheckFlag(__FLAG_USER_LEVEL_SLICE) <= 190)
	GiveFlag(__FLAG_USER_LEVEL_SLICE, CheckFlag(__FLAG_USER_LEVEL_SLICE) + 10)
	GiveFlag(__FLAG_USER_HAS_CHANGED_DIFFICULTY_LEVEL, 1)
	Conversation
	FORMAT(INTL( 10697, "Very well, your current level of difficulty is now %u. How many opponents will you be fighting?"), CheckFlag(__FLAG_USER_LEVEL_SLICE))
	;YesNo = NumberOfOpponents;
ELSEIF(CheckFlag(__FLAG_USER_LEVEL_SLICE) <= 450)
	GiveFlag(__FLAG_USER_LEVEL_SLICE, CheckFlag(__FLAG_USER_LEVEL_SLICE) + 25)
	GiveFlag(__FLAG_USER_HAS_CHANGED_DIFFICULTY_LEVEL, 1)
	Conversation
	FORMAT(INTL( 10697, "Very well, your current level of difficulty is now %u. How many opponents will you be fighting?"), CheckFlag(__FLAG_USER_LEVEL_SLICE))
	;YesNo = NumberOfOpponents;
ELSEIF(CheckFlag(__FLAG_USER_LEVEL_SLICE) == 475)
	GiveFlag(__FLAG_USER_LEVEL_SLICE, 500)
	GiveFlag(__FLAG_USER_HAS_CHANGED_DIFFICULTY_LEVEL, 1)
	Conversation
	INTL( 10698, "Very well, your current level of difficulty is now 500. Please note that you will not be able to increase the difficulty "
	"level beyond 500. How many opponents will you be fighting?")
	;YesNo = NumberOfOpponents;
ELSEIF(CheckFlag(__FLAG_USER_LEVEL_SLICE) == 500)
	Conversation
	INTL( 10699, "You may not raise the difficulty level beyond 500. Would you like to \"decrease\" your current level of difficulty "
	"or \"leave\" it as is?")
	;YesNo = LevelSelection;
ENDIF
	
;} else if( ( msg.Find( INTL( 10700, "DECREAS") ) != -1 ) && YesNo == LevelSelection) {;
IF(CheckFlag(__FLAG_USER_HAS_CHANGED_DIFFICULTY_LEVEL) == 1)
	Conversation
	INTL( 10701, "You have already changed the level of difficulty. You may not do so again until you have fought with your current "
	"settings. Now, how many opponents will you be fighting?")
	;YesNo = NumberOfOpponents;
ELSEIF(CheckFlag(__FLAG_USER_LEVEL_SLICE) >= 225)
	GiveFlag(__FLAG_USER_LEVEL_SLICE, CheckFlag(__FLAG_USER_LEVEL_SLICE) - 25)
	GiveFlag(__FLAG_USER_HAS_CHANGED_DIFFICULTY_LEVEL, 1)
	Conversation
	FORMAT(INTL( 10697, "Very well, your current level of difficulty is now %u. How many opponents will you be fighting?"), CheckFlag(__FLAG_USER_LEVEL_SLICE))
	;YesNo = NumberOfOpponents;
ELSEIF(CheckFlag(__FLAG_USER_LEVEL_SLICE) >= 60)
	GiveFlag(__FLAG_USER_LEVEL_SLICE, CheckFlag(__FLAG_USER_LEVEL_SLICE) - 10)
	GiveFlag(__FLAG_USER_HAS_CHANGED_DIFFICULTY_LEVEL, 1)
	Conversation
	FORMAT(INTL( 10697, "Very well, your current level of difficulty is now %u. How many opponents will you be fighting?"), CheckFlag(__FLAG_USER_LEVEL_SLICE))
	;YesNo = NumberOfOpponents;
ELSEIF(CheckFlag(__FLAG_USER_LEVEL_SLICE) == 50)
	GiveFlag(__FLAG_USER_LEVEL_SLICE, 40)
	GiveFlag(__FLAG_USER_HAS_CHANGED_DIFFICULTY_LEVEL, 1)
	Conversation
	INTL( 10702, "Very well, your current level of difficulty is now 40. Please note that you will not be able to decrease the difficulty "
	"level under 40. This is an arena and not a playground after all. How many opponents will you be fighting?")
	;YesNo = NumberOfOpponents;
ELSEIF(CheckFlag(__FLAG_USER_LEVEL_SLICE) == 40)
	Conversation
	INTL( 10703, "You may not lower the difficulty level under 40. Would you like to \"increase\" your current level of difficulty "
	"or \"leave\" it as is?")
	;YesNo = LevelSelection;
ENDIF

;} else if( ( msg.Find( INTL( 519, "LEAVE") ) != -1 ) && YesNo == LevelSelection) {;
Conversation
INTL( 10704, "Very well, your current level of difficulty will remain as is. How many opponents will you be fighting?")
;YesNo = NumberOfOpponents;

;} else if(YesNo == LevelSelection) {;
Conversation
INTL( 10705, "Would you like to \"increase\", \"decrease\" or \"leave\" it as is?")
;YesNo = LevelSelection;

////////////////////////////////////////////////// LevelSelection ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// NumberOfOpponents /////////////////////////////////////////////////

;} else if( ( ( msg.Find( INTL( 7311, " 1 ") ) != -1 ) || ( msg.Find( INTL( 10507, " ONE ") ) != -1 ) ) && YesNo == NumberOfOpponents) {;

IF (CheckGlobalFlag(__COLOSSEUM_MONSTER_DISABLE) == 1) 
	Conversation
	INTL( 11666, "Alas, I cannot summon monsters for the time being. Come back later.")
ELSE
	GiveGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA, 1)
	Conversation
	INTL( 10706, "The battle is set... good luck!")
	SWITCH(CheckFlag(__FLAG_USER_LEVEL_SLICE))
	CASE(40)
		SUMMON("ARENAMOB40", 1707, 1853)
	ENDCASE
	CASE(50)
		SUMMON("ARENAMOB50", 1707, 1853)
	ENDCASE
	CASE(60)
		SUMMON("ARENAMOB60", 1707, 1853)
	ENDCASE
		CASE(70)
	SUMMON("ARENAMOB70", 1707, 1853)
	ENDCASE
	CASE(80)
		SUMMON("ARENAMOB80", 1707, 1853)
	ENDCASE
	CASE(90)
		SUMMON("ARENAMOB90", 1707, 1853)
	ENDCASE
	CASE(100)
		SUMMON("ARENAMOB100", 1707, 1853)
	ENDCASE
	CASE(110)
		SUMMON("ARENAMOB110", 1707, 1853)
	ENDCASE
	CASE(120)
		SUMMON("ARENAMOB120", 1707, 1853)
	ENDCASE
	CASE(130)
		SUMMON("ARENAMOB130", 1707, 1853)
	ENDCASE
	CASE(140)
		SUMMON("ARENAMOB140", 1707, 1853)
	ENDCASE
	CASE(150)
		SUMMON("ARENAMOB150", 1707, 1853)
	ENDCASE
	CASE(160)
		SUMMON("ARENAMOB160", 1707, 1853)
	ENDCASE
	CASE(170)
		SUMMON("ARENAMOB170", 1707, 1853)
	ENDCASE
	CASE(180)
		SUMMON("ARENAMOB180", 1707, 1853)
	ENDCASE
	CASE(190)
		SUMMON("ARENAMOB190", 1707, 1853)
	ENDCASE
	CASE(200)
		SUMMON("ARENAMOB200", 1707, 1853)
	ENDCASE
	CASE(225)
		SUMMON("ARENAMOB225", 1707, 1853)
	ENDCASE
	CASE(250)
		SUMMON("ARENAMOB250", 1707, 1853)
	ENDCASE
	CASE(275)
		SUMMON("ARENAMOB275", 1707, 1853)
	ENDCASE
	CASE(300)
		SUMMON("ARENAMOB300", 1707, 1853)
	ENDCASE
	CASE(325)
		SUMMON("ARENAMOB325", 1707, 1853)
	ENDCASE
	CASE(350)
		SUMMON("ARENAMOB350", 1707, 1853)
	ENDCASE
	CASE(375)
		SUMMON("ARENAMOB375", 1707, 1853)
	ENDCASE
	CASE(400)
		SUMMON("ARENAMOB400", 1707, 1853)
	ENDCASE
	CASE(425)
		SUMMON("ARENAMOB425", 1707, 1853)
	ENDCASE
	CASE(450)
		SUMMON("ARENAMOB450", 1707, 1853)
	ENDCASE
	CASE(475)
		SUMMON("ARENAMOB475", 1707, 1853)
	ENDCASE
	CASE(500)
		SUMMON("ARENAMOB500", 1707, 1853)
	ENDCASE
ENDSWITCH
CastSpellTarget(__SPELL_MOB_COLOSSEUM_UPGRADE_SPELL)
GiveFlag(__FLAG_USER_HAS_CHANGED_DIFFICULTY_LEVEL, 0)
ENDIF 
BREAK

;} else if( ( ( msg.Find( INTL( 10509, " 2 ") ) != -1 ) || ( msg.Find( INTL( 10510, " TWO ") ) != -1 ) ) && YesNo == NumberOfOpponents) {;
IF (CheckGlobalFlag(__COLOSSEUM_MONSTER_DISABLE) == 1) 
	Conversation
	INTL( 11667, "Unfortunately, I've just been informed that I am no longer allowed "
	"to summon monsters inside the Colosseum for the time being. Please come "
	"back later.") 
ELSE

GiveGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA, 2)
Conversation
INTL( 10706, "The battle is set... good luck!")
SWITCH(CheckFlag(__FLAG_USER_LEVEL_SLICE))
	CASE(40)
		SUMMON("ARENAMOB40", 1710, 1825)
		SUMMON("ARENAMOB40", 1735, 1850)
	ENDCASE
	CASE(50)
		SUMMON("ARENAMOB50", 1710, 1825)
		SUMMON("ARENAMOB50", 1735, 1850)
	ENDCASE
	CASE(60)
		SUMMON("ARENAMOB60", 1710, 1825)
		SUMMON("ARENAMOB60", 1735, 1850)
	ENDCASE
	CASE(70)
		SUMMON("ARENAMOB70", 1710, 1825)
		SUMMON("ARENAMOB70", 1735, 1850)
	ENDCASE
	CASE(80)
		SUMMON("ARENAMOB80", 1710, 1825)
		SUMMON("ARENAMOB80", 1735, 1850)
	ENDCASE
	CASE(90)
		SUMMON("ARENAMOB90", 1710, 1825)
		SUMMON("ARENAMOB90", 1735, 1850)
	ENDCASE
	CASE(100)
		SUMMON("ARENAMOB100", 1710, 1825)
		SUMMON("ARENAMOB100", 1735, 1850)
	ENDCASE
	CASE(110)
		SUMMON("ARENAMOB110", 1710, 1825)
		SUMMON("ARENAMOB110", 1735, 1850)
	ENDCASE
	CASE(120)
		SUMMON("ARENAMOB120", 1710, 1825)
		SUMMON("ARENAMOB120", 1735, 1850)
	ENDCASE
	CASE(130)
		SUMMON("ARENAMOB130", 1710, 1825)
		SUMMON("ARENAMOB130", 1735, 1850)
	ENDCASE
	CASE(140)
		SUMMON("ARENAMOB140", 1710, 1825)
		SUMMON("ARENAMOB140", 1735, 1850)
	ENDCASE
	CASE(150)
		SUMMON("ARENAMOB150", 1710, 1825)
		SUMMON("ARENAMOB150", 1735, 1850)
	ENDCASE
	CASE(160)
		SUMMON("ARENAMOB160", 1710, 1825)
		SUMMON("ARENAMOB160", 1735, 1850)
	ENDCASE
	CASE(170)
		SUMMON("ARENAMOB170", 1710, 1825)
		SUMMON("ARENAMOB170", 1735, 1850)
	ENDCASE
	CASE(180)
		SUMMON("ARENAMOB180", 1710, 1825)
		SUMMON("ARENAMOB180", 1735, 1850)
	ENDCASE
	CASE(190)
		SUMMON("ARENAMOB190", 1710, 1825)
		SUMMON("ARENAMOB190", 1735, 1850)
	ENDCASE
	CASE(200)
		SUMMON("ARENAMOB200", 1710, 1825)
		SUMMON("ARENAMOB200", 1735, 1850)
	ENDCASE
	CASE(225)
		SUMMON("ARENAMOB225", 1710, 1825)
		SUMMON("ARENAMOB225", 1735, 1850)
	ENDCASE
	CASE(250)
		SUMMON("ARENAMOB250", 1710, 1825)
		SUMMON("ARENAMOB250", 1735, 1850)
	ENDCASE
	CASE(275)
		SUMMON("ARENAMOB275", 1710, 1825)
		SUMMON("ARENAMOB275", 1735, 1850)
	ENDCASE
	CASE(300)
		SUMMON("ARENAMOB300", 1710, 1825)
		SUMMON("ARENAMOB300", 1735, 1850)
	ENDCASE
	CASE(325)
		SUMMON("ARENAMOB325", 1710, 1825)
		SUMMON("ARENAMOB325", 1735, 1850)
	ENDCASE
	CASE(350)
		SUMMON("ARENAMOB350", 1710, 1825)
		SUMMON("ARENAMOB350", 1735, 1850)
	ENDCASE
	CASE(375)
		SUMMON("ARENAMOB375", 1710, 1825)
		SUMMON("ARENAMOB375", 1735, 1850)
	ENDCASE
	CASE(400)
		SUMMON("ARENAMOB400", 1710, 1825)
		SUMMON("ARENAMOB400", 1735, 1850)
	ENDCASE
	CASE(425)
		SUMMON("ARENAMOB425", 1710, 1825)
		SUMMON("ARENAMOB425", 1735, 1850)
	ENDCASE
	CASE(450)
		SUMMON("ARENAMOB450", 1710, 1825)
		SUMMON("ARENAMOB450", 1735, 1850)
	ENDCASE
	CASE(475)
		SUMMON("ARENAMOB475", 1710, 1825)
		SUMMON("ARENAMOB475", 1735, 1850)
	ENDCASE
	CASE(500)
		SUMMON("ARENAMOB500", 1710, 1825)
		SUMMON("ARENAMOB500", 1735, 1850)
	ENDCASE
ENDSWITCH
CastSpellTarget(__SPELL_MOB_COLOSSEUM_UPGRADE_SPELL)
GiveFlag(__FLAG_USER_HAS_CHANGED_DIFFICULTY_LEVEL, 0)
ENDIF
BREAK

;} else if( ( ( msg.Find( INTL( 10511, " 3 ") ) != -1 ) || ( msg.Find( INTL( 10512, " THREE ") ) != -1 ) ) && YesNo == NumberOfOpponents) {;
IF (CheckGlobalFlag(__COLOSSEUM_MONSTER_DISABLE) == 1) 
	Conversation
	INTL( 11668, "Unfortunately, I've just been informed that I am no longer allowed "
	"to summon monsters inside the Colosseum for the time being. Please come "
	"back later.") 
ELSE

GiveGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA, 3)
Conversation
INTL( 10706, "The battle is set... good luck!")
SWITCH(CheckFlag(__FLAG_USER_LEVEL_SLICE))
	CASE(40)
		SUMMON("ARENAMOB40", 1707, 1853)
		SUMMON("ARENAMOB40", 1710, 1825)
		SUMMON("ARENAMOB40", 1735, 1850)
	ENDCASE
	CASE(50)
		SUMMON("ARENAMOB50", 1707, 1853)
		SUMMON("ARENAMOB50", 1710, 1825)
		SUMMON("ARENAMOB50", 1735, 1850)
	ENDCASE
	CASE(60)
		SUMMON("ARENAMOB60", 1707, 1853)
		SUMMON("ARENAMOB60", 1710, 1825)
		SUMMON("ARENAMOB60", 1735, 1850)
	ENDCASE
	CASE(70)
		SUMMON("ARENAMOB70", 1707, 1853)
		SUMMON("ARENAMOB70", 1710, 1825)
		SUMMON("ARENAMOB70", 1735, 1850)
	ENDCASE
	CASE(80)
		SUMMON("ARENAMOB80", 1707, 1853)
		SUMMON("ARENAMOB80", 1710, 1825)
		SUMMON("ARENAMOB80", 1735, 1850)
	ENDCASE
	CASE(90)
		SUMMON("ARENAMOB90", 1707, 1853)
		SUMMON("ARENAMOB90", 1710, 1825)
		SUMMON("ARENAMOB90", 1735, 1850)
	ENDCASE
	CASE(100)
		SUMMON("ARENAMOB100", 1707, 1853)
		SUMMON("ARENAMOB100", 1710, 1825)
		SUMMON("ARENAMOB100", 1735, 1850)
	ENDCASE
	CASE(110)
		SUMMON("ARENAMOB110", 1707, 1853)
		SUMMON("ARENAMOB110", 1710, 1825)
		SUMMON("ARENAMOB110", 1735, 1850)
	ENDCASE
	CASE(120)
		SUMMON("ARENAMOB120", 1707, 1853)
		SUMMON("ARENAMOB120", 1710, 1825)
		SUMMON("ARENAMOB120", 1735, 1850)
	ENDCASE
	CASE(130)
		SUMMON("ARENAMOB130", 1707, 1853)
		SUMMON("ARENAMOB130", 1710, 1825)
		SUMMON("ARENAMOB130", 1735, 1850)
	ENDCASE
	CASE(140)
		SUMMON("ARENAMOB140", 1707, 1853)
		SUMMON("ARENAMOB140", 1710, 1825)
		SUMMON("ARENAMOB140", 1735, 1850)
	ENDCASE
	CASE(150)
		SUMMON("ARENAMOB150", 1707, 1853)
		SUMMON("ARENAMOB150", 1710, 1825)
		SUMMON("ARENAMOB150", 1735, 1850)
	ENDCASE
	CASE(160)
		SUMMON("ARENAMOB160", 1707, 1853)
		SUMMON("ARENAMOB160", 1710, 1825)
		SUMMON("ARENAMOB160", 1735, 1850)
	ENDCASE
	CASE(170)
		SUMMON("ARENAMOB170", 1707, 1853)
		SUMMON("ARENAMOB170", 1710, 1825)
		SUMMON("ARENAMOB170", 1735, 1850)
	ENDCASE
	CASE(180)
		SUMMON("ARENAMOB180", 1707, 1853)
		SUMMON("ARENAMOB180", 1710, 1825)
		SUMMON("ARENAMOB180", 1735, 1850)
	ENDCASE
	CASE(190)
		SUMMON("ARENAMOB190", 1707, 1853)
		SUMMON("ARENAMOB190", 1710, 1825)
		SUMMON("ARENAMOB190", 1735, 1850)
	ENDCASE
	CASE(200)
		SUMMON("ARENAMOB200", 1707, 1853)
		SUMMON("ARENAMOB200", 1710, 1825)
		SUMMON("ARENAMOB200", 1735, 1850)
	ENDCASE
	CASE(225)
		SUMMON("ARENAMOB225", 1707, 1853)
		SUMMON("ARENAMOB225", 1710, 1825)
		SUMMON("ARENAMOB225", 1735, 1850)
	ENDCASE
	CASE(250)
		SUMMON("ARENAMOB250", 1707, 1853)
		SUMMON("ARENAMOB250", 1710, 1825)
		SUMMON("ARENAMOB250", 1735, 1850)
	ENDCASE
	CASE(275)
		SUMMON("ARENAMOB275", 1707, 1853)
		SUMMON("ARENAMOB275", 1710, 1825)
		SUMMON("ARENAMOB275", 1735, 1850)
	ENDCASE
	CASE(300)
		SUMMON("ARENAMOB300", 1707, 1853)
		SUMMON("ARENAMOB300", 1710, 1825)
		SUMMON("ARENAMOB300", 1735, 1850)
	ENDCASE
	CASE(325)
		SUMMON("ARENAMOB325", 1707, 1853)
		SUMMON("ARENAMOB325", 1710, 1825)
		SUMMON("ARENAMOB325", 1735, 1850)
	ENDCASE
	CASE(350)
		SUMMON("ARENAMOB350", 1707, 1853)
		SUMMON("ARENAMOB350", 1710, 1825)
		SUMMON("ARENAMOB350", 1735, 1850)
	ENDCASE
	CASE(375)
		SUMMON("ARENAMOB375", 1707, 1853)
		SUMMON("ARENAMOB375", 1710, 1825)
		SUMMON("ARENAMOB375", 1735, 1850)
	ENDCASE
	CASE(400)
		SUMMON("ARENAMOB400", 1707, 1853)
		SUMMON("ARENAMOB400", 1710, 1825)
		SUMMON("ARENAMOB400", 1735, 1850)
	ENDCASE
	CASE(425)
		SUMMON("ARENAMOB425", 1707, 1853)
		SUMMON("ARENAMOB425", 1710, 1825)
		SUMMON("ARENAMOB425", 1735, 1850)
	ENDCASE
	CASE(450)
		SUMMON("ARENAMOB450", 1707, 1853)
		SUMMON("ARENAMOB450", 1710, 1825)
		SUMMON("ARENAMOB450", 1735, 1850)
	ENDCASE
	CASE(475)
		SUMMON("ARENAMOB475", 1707, 1853)
		SUMMON("ARENAMOB475", 1710, 1825)
		SUMMON("ARENAMOB475", 1735, 1850)
	ENDCASE
	CASE(500)
		SUMMON("ARENAMOB500", 1707, 1853)
		SUMMON("ARENAMOB500", 1710, 1825)
		SUMMON("ARENAMOB500", 1735, 1850)
	ENDCASE
ENDSWITCH
CastSpellTarget(__SPELL_MOB_COLOSSEUM_UPGRADE_SPELL)
GiveFlag(__FLAG_USER_HAS_CHANGED_DIFFICULTY_LEVEL, 0)
ENDIF
BREAK

;} else if(YesNo == NumberOfOpponents) {;
Conversation
INTL( 10707, "How many opponents will you be fighting? \"One\", \"two\" or \"three\"?")
;YesNo = NumberOfOpponents;

///////////////////////////////////////////////// NumberOfOpponents /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////// PurchaseGoods ///////////////////////////////////////////////////

;} else if( ( ( msg.Find( INTL( 10708, "COMPLET") ) != -1 ) && ( msg.Find( INTL( 9253, "RESTOR") ) != -1 ) ) && YesNo == PurchaseGoods) {;
IF(CheckFlag(__FLAG_USER_BOUGHT_COMPLETE_RESTORATION) == 0)
	IF(CheckItem(__OBJ_COLOSSEUM_TOKEN) >= 5)
		FOR(0, 5)
			TakeItem(__OBJ_COLOSSEUM_TOKEN)
		ENDFOR
		GiveFlag(__FLAG_USER_BOUGHT_COMPLETE_RESTORATION, 1)
		Conversation
		INTL( 10709, "Done! Your health and mana will be completely restored upon the start of the fight. Is there anything else you wish "
		"to purchase?")
		SetYesNo(BuySomethingElse)
	ELSE
		Conversation
		INTL( 10710, "You do not have enough tokens to buy this upgrade. Is there anything else you wish to purchase?")
		SetYesNo(BuySomethingElse)
	ENDIF
ELSE
	Conversation
	INTL( 10711, "You have already bought this upgrade. Is there anything else you wish to purchase?")
	SetYesNo(BuySomethingElse)
ENDIF

;} else if( ( ( msg.Find( INTL( 10712, "PHYSICAL") ) != -1 ) && ( msg.Find( INTL( 10713, "OFFENSE") ) != -1 ) ) && YesNo == PurchaseGoods) {;
IF(CheckFlag(__FLAG_USER_BOUGHT_PHYSICAL_OFFENSE_UPGRADE) == 0)
	IF(CheckItem(__OBJ_COLOSSEUM_TOKEN) >= 15)
		FOR(0, 15)
			TakeItem(__OBJ_COLOSSEUM_TOKEN)
		ENDFOR
		GiveFlag(__FLAG_USER_BOUGHT_PHYSICAL_OFFENSE_UPGRADE, 1)
		Conversation
		INTL( 10714, "Done! Your physical offensive capabilities will be increased for a short duration upon the start of the fight. Is "
		"there anything else you wish to purchase?")
		SetYesNo(BuySomethingElse)
	ELSE
		Conversation
		INTL( 10710, "You do not have enough tokens to buy this upgrade. Is there anything else you wish to purchase?")
		SetYesNo(BuySomethingElse)
	ENDIF
ELSE
	Conversation
	INTL( 10711, "You have already bought this upgrade. Is there anything else you wish to purchase?")
	SetYesNo(BuySomethingElse)
ENDIF

;} else if( ( ( msg.Find( INTL( 10715, "MAGICAL") ) != -1 ) && ( msg.Find( INTL( 10713, "OFFENSE") ) != -1 ) ) && YesNo == PurchaseGoods) {;
IF(CheckFlag(__FLAG_USER_BOUGHT_MAGICAL_OFFENSE_UPGRADE) == 0)
	IF(CheckItem(__OBJ_COLOSSEUM_TOKEN) >= 15)
		FOR(0, 15)
			TakeItem(__OBJ_COLOSSEUM_TOKEN)
		ENDFOR
		GiveFlag(__FLAG_USER_BOUGHT_MAGICAL_OFFENSE_UPGRADE, 1)
		Conversation
		INTL( 10716, "Done! Your magical offensive capabilities will be increased for a short duration upon the start of the fight. Is "
		"there anything else you wish to purchase?")
		SetYesNo(BuySomethingElse)
	ELSE
		Conversation
		INTL( 10710, "You do not have enough tokens to buy this upgrade. Is there anything else you wish to purchase?")
		SetYesNo(BuySomethingElse)
	ENDIF
ELSE
	Conversation
	INTL( 10711, "You have already bought this upgrade. Is there anything else you wish to purchase?")
	SetYesNo(BuySomethingElse)
ENDIF

;} else if( ( ( msg.Find( INTL( 10712, "PHYSICAL") ) != -1 ) && ( msg.Find( INTL( 10717, "DEFENSE") ) != -1 ) ) && YesNo == PurchaseGoods) {;
IF(CheckFlag(__FLAG_USER_BOUGHT_PHYSICAL_DEFENSE_UPGRADE) == 0)
	IF(CheckItem(__OBJ_COLOSSEUM_TOKEN) >= 10)
		FOR(0, 10)
			TakeItem(__OBJ_COLOSSEUM_TOKEN)
		ENDFOR
		GiveFlag(__FLAG_USER_BOUGHT_PHYSICAL_DEFENSE_UPGRADE, 1)
		Conversation
		INTL( 10718, "Done! Your physical defensive capabilities will be increased for a short duration upon the start of the fight. Is "
		"there anything else you wish to purchase?")
		SetYesNo(BuySomethingElse)
	ELSE
		Conversation
		INTL( 10710, "You do not have enough tokens to buy this upgrade. Is there anything else you wish to purchase?")
		SetYesNo(BuySomethingElse)
	ENDIF
ELSE
	Conversation
	INTL( 10711, "You have already bought this upgrade. Is there anything else you wish to purchase?")
	SetYesNo(BuySomethingElse)
ENDIF

;} else if( ( ( msg.Find( INTL( 10715, "MAGICAL") ) != -1 ) && ( msg.Find( INTL( 10717, "DEFENSE") ) != -1 ) ) && YesNo == PurchaseGoods) {;
IF(CheckFlag(__FLAG_USER_BOUGHT_MAGICAL_DEFENSE_UPGRADE) == 0)
	IF(CheckItem(__OBJ_COLOSSEUM_TOKEN) >= 10)
		FOR(0, 10)
			TakeItem(__OBJ_COLOSSEUM_TOKEN)
		ENDFOR
		GiveFlag(__FLAG_USER_BOUGHT_MAGICAL_DEFENSE_UPGRADE, 1)
		Conversation
		INTL( 10719, "Done! Your magical defensive capabilities will be increased for a short duration upon the start of the fight. Is "
		"there anything else you wish to purchase?")
		SetYesNo(BuySomethingElse)
	ELSE
		Conversation
		INTL( 10710, "You do not have enough tokens to buy this upgrade. Is there anything else you wish to purchase?")
		SetYesNo(BuySomethingElse)
	ENDIF
ELSE
	Conversation
	INTL( 10711, "You have already bought this upgrade. Is there anything else you wish to purchase?")
	SetYesNo(BuySomethingElse)
ENDIF

;} else if( ( ( msg.Find( INTL( 10720, "EVERYTHING") ) != -1 ) || ( msg.Find( INTL( 10721, "PACKAGE") ) != -1 ) ) && YesNo == PurchaseGoods) {;
IF((CheckFlag(__FLAG_USER_BOUGHT_MAGICAL_DEFENSE_UPGRADE) == 0 && CheckFlag(__FLAG_USER_BOUGHT_MAGICAL_OFFENSE_UPGRADE) == 0) && CheckFlag(__FLAG_USER_BOUGHT_PHYSICAL_DEFENSE_UPGRADE) == 0 && CheckFlag(__FLAG_USER_BOUGHT_PHYSICAL_OFFENSE_UPGRADE) == 0 && CheckFlag(__FLAG_USER_BOUGHT_COMPLETE_RESTORATION) == 0)
	IF(CheckItem(__OBJ_COLOSSEUM_TOKEN) >= 40)
		FOR(0, 40)
			TakeItem(__OBJ_COLOSSEUM_TOKEN)
		ENDFOR
		GiveFlag(__FLAG_USER_BOUGHT_MAGICAL_DEFENSE_UPGRADE, 1)
		GiveFlag(__FLAG_USER_BOUGHT_MAGICAL_OFFENSE_UPGRADE, 1)
		GiveFlag(__FLAG_USER_BOUGHT_PHYSICAL_DEFENSE_UPGRADE, 1)
		GiveFlag(__FLAG_USER_BOUGHT_PHYSICAL_OFFENSE_UPGRADE, 1)
		GiveFlag(__FLAG_USER_BOUGHT_COMPLETE_RESTORATION, 1)
		Conversation
		FORMAT(INTL( 10722, "Done! You will be fully restored and all your magical and physical capabilities will be increased for a short duration "
		"at the start of the fight. Your current level of difficulty is %u. Would you like to \"increase\", \"decrease\" or \"leave\" it as is?"), CheckFlag(__FLAG_USER_LEVEL_SLICE))
		;YesNo = LevelSelection;
	ELSE
		Conversation
		INTL( 10723, "You do not have enough tokens to buy the complete package. Is there anything else you wish to purchase?")
		SetYesNo(BuySomethingElse)
	ENDIF
ELSE
	Conversation
	INTL( 10724, "You cannot purchase the complete package if you have already purchased a separate upgrade. Is there anything else you wish to purchase?")
	SetYesNo(BuySomethingElse)
ENDIF

;} else if( ( msg.Find( INTL( 5210, "NOTHING") ) != -1 ) && YesNo == PurchaseGoods) {;
Conversation
FORMAT(INTL( 10725, "Very well. Your current level of difficulty is %u. Would you like to \"increase\", \"decrease\" or \"leave\" it as is?"), CheckFlag(__FLAG_USER_LEVEL_SLICE))
;YesNo = LevelSelection;

;} else if(YesNo == PurchaseGoods) {;
Conversation
INTL( 10726, "What would you like to purchase?")
;YesNo = PurchaseGoods;

/////////////////////////////////////////////////// PurchaseGoods ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

YES(BuySomethingElse)
	Conversation
	INTL( 10727, "Remember, aside from a \"complete\" \"restoration\", the upgrades available are \"physical\" "
	"\"offense\", \"physical\" \"defense\", \"magical\" \"offense\", \"magical\" \"defense\" and \"everything\" in "
	"one \"package\". What would you like to purchase then?")
	;YesNo = PurchaseGoods;
NO(BuySomethingElse)
	Conversation
	FORMAT(INTL( 10728, "Very well. Your current level of difficulty is %u. Would you like to \"increase\", \"decrease\" or \"leave\" it as is?"), CheckFlag(__FLAG_USER_LEVEL_SLICE))
	;YesNo = LevelSelection;
YesNoELSE(BuySomethingElse)
	Conversation
	INTL( 10729, "Is there anything more you wish to purchase?")
	SetYesNo(BuySomethingElse)

YES(Arena)
	Conversation
	FORMAT(INTL( 10730, "Splendid! Your current level of difficulty is %u. Would you like to \"increase\", \"decrease\" or \"leave\" it as is?"), CheckFlag(__FLAG_USER_LEVEL_SLICE))
	;YesNo = LevelSelection;
NO(Arena)
	Conversation
	INTL( 10731, "I see. Then what can I do for you?")
YesNoELSE(Arena)
	Conversation
	INTL( 10732, "Will you be fighting in the arena today or not?")
	SetYesNo(Arena)

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 10733, "My name is Darvis.")

Command(INTL( 10734, "DARVIS"))
INTL( 10735, "Yes that's what I said, Darvis.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 10736, "I am the caretaker as well as the chief operator of this \"arena\". I will gladly answer any questions you may have about the "
"\"colosseum\". All complaints will promptly be ignored.")

Command2(INTL( 7383, "ARENA"), INTL( 10737, "COLOSSEUM"))
INTL( 10738, "The arena is used by adventurers of all levels to better hone their skills in \"battle\", as well "
"as the occasional \"battle\" \"token\".")

CmdAND(INTL( 10739, "BATTLE"), INTL( 3723, "TOKEN"))
INTL( 10740, "Whenever an opponent is slain, there is a chance it will drop a battle token. The harder your opponent is relatively "
"to you, the more chances you have of receiving a token. These tokens can then be traded in for temporary ability "
"enhancements before each fight.")

Command(INTL( 10739, "BATTLE"))
INTL( 10741, "The goal of the arena is simple: \"fight\" monsters, kill monsters, then fight more monsters and so on.")

Command(INTL( 10742, "PROCEDURE"))
INTL( 10743, "Each time you enter the arena, a level of difficulty is attributed to you based on your level of experience. Every fight's "
"difficulty is based on this level. Before each fight, you will have the opportunity to either raise, lower or "
"leave the level of difficulty as is. Once you have set the level for the fight, you will be asked how many opponents you wish "
"to fight at the same time. This can be either one, two or three opponents. Once you have chosen, all purchased ability "
"enhancements will be activated and the battle will begin. After each fight, you will be given the opportunity to spend your "
"battle tokens, provided you have accumulated enough, to purchase additional ability enhancements. With that said, I believe "
"you are ready to \"fight\".")
GiveFlag(__FLAG_USER_HAS_READ_COLOSSEUM_INSTRUCTIONS, 1)

Command(INTL( 4045, "FIGHT"))
""
GiveFlag(__FLAG_USER_HAS_SPOKEN_TO_COLOSSEUM_CLERK, 1)
IF(CheckFlag(__FLAG_USER_HAS_READ_COLOSSEUM_INSTRUCTIONS) == 0)
	Conversation
	INTL( 10744, "Whoa! Not so fast! There are certain \"procedures\" you will have to learn about before I will let you fight.")
ELSE
	Conversation
	FORMAT(INTL( 10745, "Your current level of difficulty is %u. Would you like to \"increase\", \"decrease\" or \"leave\" it as is?"), CheckFlag(__FLAG_USER_LEVEL_SLICE))
	;YesNo = LevelSelection;
ENDIF

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 10746, "Will you be \"leaving\" the arena or are you ready to \"fight\"?")
GiveFlag(__FLAG_USER_HAS_SPOKEN_TO_COLOSSEUM_CLERK, 1)
;YesNo = LeaveArenaOrFight;

;} else if( ( msg.Find( INTL( 4045, "FIGHT") ) != -1 ) && YesNo == LeaveArenaOrFight) {;
Conversation
FORMAT(INTL( 10747, "Your current level of difficulty is %u. Would you like to \"increase\", \"decrease\" or \"leave\" it as is?"), CheckFlag(__FLAG_USER_LEVEL_SLICE))
GiveFlag(__FLAG_USER_HAS_SPOKEN_TO_COLOSSEUM_CLERK, 1)
;YesNo = LevelSelection;

;} else if( ( msg.Find( INTL( 10748, "LEAV") ) != -1 ) && YesNo == LeaveArenaOrFight) {;
Conversation
FORMAT(INTL( 10749, "It was a pleasure having you here, %s. You are welcome to come again!"), USER_NAME)
CastSpellTarget(__SPELL_NPC_CANTRIP_FLAK)
TELEPORT(343, 492, 0)
;YesNo = 0;
BREAK

Default
INTL( 10750, "I do not quite understand what you mean. Could you be more specific?")

EndTalk
}