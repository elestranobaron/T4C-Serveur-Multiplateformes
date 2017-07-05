#pragma hdrstop
#include "Totak.H"

Totak::Totak()
{}

Totak::~Totak()
{}

extern NPCstructure::NPC Male_Brigand;

void Totak::Create( void )
{
	npc = ( Male_Brigand );
	SET_NPC_NAME( "[2908]Totak" );
	npc.InitialPos.X = 2151; // Brigand Camp
	npc.InitialPos.Y = 1224;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

void Totak::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin INTL( 1059, "Oh! You almost surprised me for an instant.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1060, "Uh? Call me Totak.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1061, "I am a brigand, what else? I enjoy making \"wagers\" with my friends. Heh! Heh!")

ParamCmd(INTL( 1062, "GAMBLE $ GOLD"))
""
UseC
int nGamble = NUM_PARAM( 0 );
IF (nGamble == 0 )
	Conversation
	INTL( 1063, "If you really want to gamble gold pieces with me, you will have to tell "
	"me how many you wish to risk. For example, if you would like to to put "
	"one hundred gold pieces on the table, simply say 'gamble 100 gold' and "
	"I'll throw a piece in the air. If it falls on heads, you will win double "
	"what you gambled, else you lose your bet. Quite simple, my friend, don't you think? "
	"If your wager seems too high, I simply will not accept it because I do not "
	"want you to be a wandering beggar. Heh! Heh!")
ELSE
	IF (nGamble < 0 )
		Conversation
		INTL( 1064, "Pah! You will not fool me that easily!")
		IF (Gold > 1)
			TakeGold( (Gold/4) )
		ENDIF
	ELSEIF (Gold < nGamble )
		Conversation
		INTL( 1065, "It is not wise gamble gold pieces you do not own!")
	ELSEIF (nGamble >= USER_LEVEL*100)
		Conversation
		INTL( 1066, "Sorry, you are gambling too many gold pieces.")
	ELSE
		TakeGold( nGamble ) // **** TAKE HIS GOLD ****
		IF (rnd.roll( dice( 1, 9 ) ) < 5 )
			Conversation
			INTL( 1067, "And the piece falls on... Heads! Congratulations, you have won your wager.")
			GiveGold( nGamble )
			GiveGold( nGamble )
		ELSE
			Conversation
			INTL( 1068, "And the piece falls on... Tails! You've lost! Perhaps you would like to try again.")
		ENDIF
	ENDIF
ENDIF

Command2(INTL( 1069, "GAMBLE"),INTL( 1070, "WAGER"))
INTL( 1071, "If you really want to gamble gold pieces with me, you will have to tell "
"me how many you wish to risk. For example, if you would like to to put "
"one hundred gold pieces on the table, simply say 'gamble 100 gold' and "
"I'll throw a piece in the air. If it falls on heads, you will win double "
"what you gambled, else you lose your bet. Quite simple my friend don't you think? "
"If your wager seems too high, I simply will not accept it because I do not "
"want you to be a wandering beggar. Heh! Heh!")

// Garbage
// Command(INTL( 1072, "KING"))
// INTL( 1073, "Nobody knows which king it is, he must have died centuries ago.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 1074, "Get bent!")
BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1075, "Farewell.") BREAK

Default
INTL( 1076, "I really have no clue.")

EndTalk

}
