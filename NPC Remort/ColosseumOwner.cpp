#pragma hdrstop
#include "ColosseumOwner.h"

ColosseumOwner::ColosseumOwner()
{}

ColosseumOwner::~ColosseumOwner()
{}

extern NPCstructure::NPC ColosseumClerkNPC;

void ColosseumOwner::Create( void )
{
      npc = ( ColosseumClerkNPC );
      SET_NPC_NAME( "[10970]A wealthy-looking man" );  
      npc.InitialPos.X = 345; 
      npc.InitialPos.Y = 490;
      npc.InitialPos.world = 0;
}

void ColosseumOwner::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void ColosseumOwner::OnTalk( UNIT_FUNC_PROTOTYPE ){


InitTalk

CONSTANT WantToFight = 1;
CONSTANT UserWantsToBeASpectator = 2;
CONSTANT Gladiator = 3;
CONSTANT Spectate = 4; 
CONSTANT GoToBattleGround = 5; 

Begin
""
// This line supposedly stores a set of coordinates x,y,world into a single flag.  
// Note: The flag is either ARENA_RETURN_LOC or __ARENA_RETURN_LOC
;target->SetFlag( __ARENA_RETURN_LOC,(((DWORD)((WORD)345)<<20)+((DWORD)((WORD)490)<<8)+(DWORD)((BYTE)0)));
IF(CheckFlag(__FLAG_USER_HAS_ENTERED_COLOSSEUM) == 0)
	Conversation
	INTL( 10751, "Greetings brave adventurer and welcome!")
ELSE
	Conversation
	FORMAT(INTL( 10752, "Welcome back, %s."), USER_NAME)	
ENDIF

Command2(INTL( 483, "NAME"), INTL( 485, "WHO ARE YOU"))
INTL( 10753, "My name is Polainas.")

Command(INTL( 10754, "POLAINAS"))
INTL( 2221, "What can I do for you?")

Command3(INTL( 489, "WORK"), INTL( 3696, "WHAT DO YOU DO"), INTL( 487, "OCCUPATION"))
INTL( 10755, "I am the owner of two magnificent establishments. One is called "
"the famed \"colosseum\" while the other one is called the \"battleground\".") 
	 	 	 	 
Command(INTL( 10737, "COLOSSEUM"))
INTL( 10756, "In the colosseum, fighters of all rank and caliber come to "
"\"test\" their abilities against powerful creatures. However, if you don't "
"feel like fighting, it is possible to become a \"spectator\".") 

Command(INTL( 11669, "BATTLEGROUND")) 
INTL( 11670, "Unlike the \"colosseum\", the battleground does not allow creatures. It is a "
"dreadful place where there are *NO* rules. No matter what rank you are, if "
"you \"fight\" in the battleground, you can be slain by *ANY* other gladiators. "
"However, if you don't feel like fighting, it is possible to become a "
"\"spectator\".") 

Command2(INTL( 11671, "SPECTATOR"),INTL( 11672, "SPECTATE")) 
INTL( 11673, "So, you want to become a spectator?")
SetYesNo( UserWantsToBeASpectator ) 

YES( UserWantsToBeASpectator ) 
Conversation
INTL( 11674, "You won't regret this. I can assure you that you'll see only the "
"very best fighters around. Now, I need to know whether you want to "
"be a spectator in the \"Battleground\" or in the \"Colosseum\"?") 
;YesNo = Spectate;

NO( UserWantsToBeASpectator ) 
Conversation
INTL( 11675, "Fair enough, but I'm telling you that you're missing a great fight.") 

YesNoELSE ( UserWantsToBeASpectator ) 
Conversation
INTL( 11676, "Do you want to become a spectator or not?")
SetYesNo( UserWantsToBeASpectator ) 

;} else if( ( msg.Find( INTL( 11669, "BATTLEGROUND") ) != -1 ) && YesNo == Spectate) {;YesNo = 0;
Conversation
INTL( 11677, "Enjoy the show!")
CastSpellTarget(__SPELL_NPC_CANTRIP_FLAK)
TELEPORT(2045,1815,0) 
BREAK

;} else if( ( msg.Find( INTL( 10737, "COLOSSEUM") ) != -1 ) && YesNo == Spectate) {;YesNo = 0;

IF (ACK_COLOSSEUM == 0) // If Colosseum XP is disallowed. 
	CastSpellTarget(__SPELL_NPC_CANTRIP_FLAK)
	Conversation
	INTL( 11677, "Enjoy the show!")
	TELEPORT(1745,1815,0) // The No-XP colosseum
ELSE
	Conversation
	INTL( 11726, "I'm sorry, but you can be a spectator in the Colosseum only when it is in non-XP mode.") 	
//	TELEPORT(1655,2010,0) // The XP colosseum
ENDIF
BREAK

;} else if(YesNo == Spectate) {;
Conversation
INTL( 11678, "You have to tell me whether you want to be a spectator in the \"colosseum\" "
"or in the \"battleground\". Make your choice with haste, I am a busy man "
"and have other things to do.") 

Command2(INTL( 4045, "FIGHT"), INTL( 4138, "TEST"))
INTL( 10757, "Well, you do look like you can handle yourself. Would you like to enter one of my arenas and try your fighting skills?")
SetYesNo(WantToFight)
	
YES(WantToFight)
IF ((ACK_COLOSSEUM == 0) || (CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= 1))
	Conversation
	INTL( 11679, "So you think you're strong enough to fight, eh? Very well. All I need to "
	"know is where you want to fight. Will it be the \"battleground\" or the "
	"\"colosseum\"?") 
	;YesNo = Gladiator;
ELSE
	Conversation
	INTL( 11713, "Alas, you can only enter the Battleground because the Colosseum is not "
	"accessible to non-Seraphs. So, do you want to enter the Battleground?")  
	SetYesNo(GoToBattleGround) 
ENDIF 
	
YES(GoToBattleGround)
	Conversation
	INTL( 10759, "Splendid! Off you go then, and best of luck to you!")
	CastSpellTarget(__SPELL_NPC_CANTRIP_FLAK)
	TELEPORT(1990, 1870, 0)
	BREAK

NO(GoToBattleGround) 
	Conversation
	INTL( 10760, "Oh, then what can I do for you?")

YesNoELSE(GoToBattleGround) 
	Conversation
	INTL( 11680, "So, do you want to fight or not?")
	SetYesNo(GoToBattleGround)

NO(WantToFight)
	Conversation
	INTL( 10760, "Oh, then what can I do for you?")

YesNoELSE(WantToFight)
	Conversation
	INTL( 11680, "So, do you want to fight or not?")
	SetYesNo(WantToFight)

;} else if( ( msg.Find( INTL( 11669, "BATTLEGROUND") ) != -1 ) && YesNo == Gladiator) {;YesNo = 0;
	Conversation
	INTL( 10759, "Splendid! Off you go then, and best of luck to you!")
	CastSpellTarget(__SPELL_NPC_CANTRIP_FLAK)
	TELEPORT(1990, 1870, 0)
	BREAK

;} else if( ( msg.Find( INTL( 10737, "COLOSSEUM") ) != -1 ) && YesNo == Gladiator) {;YesNo = 0;
	IF (ACK_COLOSSEUM == 0) 		
		GiveFlag(__FLAG_USER_HAS_ENTERED_COLOSSEUM, 1)
		GiveFlag(__FLAG_ARENA_LEVEL, 0)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 0)
		Conversation
		INTL( 10759, "Splendid! Off you go then, and best of luck to you!")
		CastSpellTarget(__SPELL_NPC_CANTRIP_FLAK)
		TELEPORT(1725, 1835, 0)
		BREAK 
	ELSEIF (CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= 1) // XP Colosseum
		GiveFlag(__FLAG_USER_HAS_ENTERED_COLOSSEUM, 1)
		GiveFlag(__FLAG_ARENA_LEVEL, 0)
		GiveFlag(__FLAG_USER_LEVEL_SLICE, 0)
		Conversation
		INTL( 10759, "Splendid! Off you go then, and best of luck to you!")
		CastSpellTarget(__SPELL_NPC_CANTRIP_FLAK)
		TELEPORT(1595, 2070, 0)
		BREAK 
	ELSE
		Conversation
		INTL( 11714, "You cannot enter the Colosseum currently because you are not a Seraph.") 		
		BREAK
	ENDIF 

;} else if(YesNo == Gladiator) {;
Conversation
INTL( 11681, "So, do you want to fight in the \"battleground\" or in the \"colosseum\"?")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 1293, "Have a nice day.")
BREAK

Default
INTL( 5283, "I don't know what you are talking about.")

EndTalk
}