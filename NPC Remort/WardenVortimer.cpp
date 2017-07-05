#pragma hdrstop
#include "WardenVortimer.h"

WardenVortimer::WardenVortimer()
{}

WardenVortimer::~WardenVortimer()
{}

extern NPCstructure::NPC WardenVortimerNPC;

void WardenVortimer::Create( void )
{
   npc = WardenVortimerNPC;
   SET_NPC_NAME( "[10982]Warden Vortimer" );
   npc.InitialPos.X = 2455;
   npc.InitialPos.Y = 186;
   npc.InitialPos.world = 0;
}

void WardenVortimer::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT ReturnKey = 1; 
CONSTANT GiveKey = 2; 

InitTalk

Begin
INTL( 10658, "Greetings.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 10659, "I am Vortimer.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 10660, "I am the keeper of \"Madrigan\"'s house. If you ever need anything, feel free to ask.") 

Command2(INTL( 10661, "MADRIGAN"),INTL( 10662, "MADDEUS")) 
INTL( 10663, "Maddeus Madrigan was once a peaceful healer. He once left with a party of "
"adventurers, then lost his soul while battling with Makrsh P'Tangh. Sensing he "
"was gradually losing his mind, he tried building a house for mentally ill "
"people, but failed to heal himself before he became stark raving mad.")

Command3(INTL( 10664, "DOOR"),INTL( 8191, "KEY"),INTL( 7296, "ENTER")) 
""
IF (CheckFlag(__FLAG_NUMBER_OF_REMORTS) == 0) 
	Conversation
	INTL( 10665, "I'm afraid your mind is not prepared to enter in \"Madrigan\"'s house without risking "
	"permanent mental injuries.") 
ELSE 
	IF (CheckItem(__OBJ_MAD_HOUSE_KEY) == 0) 
		Conversation
		INTL( 10666, "To enter Madrigan's house, you need a key to unlock the door. I can lend you "		
		"a key if you promise to \"return\" it once you're finished with it. Do you agree?") 
		SetYesNo(GiveKey) 
	ELSE
		Conversation
		INTL( 10667, "You already have a mad house key. If you no longer need it, you can "
		"\"return\" it to me.")
	ENDIF 
ENDIF 

YES(GiveKey)
	Conversation
	INTL( 10668, "Here you go. Please \"return\" it to me once you're finished with it.") 
	PRIVATE_SYSTEM_MESSAGE(INTL( 10669, "Vortimer gives you a mad house key.")) 
	GiveItem(__OBJ_MAD_HOUSE_KEY) 

NO(GiveKey) 
	Conversation
	INTL( 6170, "Of course.")

YesNoELSE(GiveKey) 
	Conversation
	INTL( 10670, "Do you want the key or not?")
	SetYesNo(GiveKey) 

Command(INTL( 6167, "RETURN")) 
""
IF (CheckItem(__OBJ_MAD_HOUSE_KEY) == 0) 
	Conversation
	INTL( 10671, "You don't have a mad house key to return.") 
ELSE
	Conversation
	INTL( 10672, "You want to return your mad house key?") 
	SetYesNo(ReturnKey) 
ENDIF 

YES(ReturnKey) 
	;int nNumKeys = CheckItem(__OBJ_MAD_HOUSE_KEY); 
	FOR(0, nNumKeys) 
		TakeItem(__OBJ_MAD_HOUSE_KEY) 
	ENDFOR 
	Conversation
	INTL( 10673, "Thank you. I hope you haven't been disturbed by what you've seen "
	"in the house.") 
	PRIVATE_SYSTEM_MESSAGE(INTL( 10674, "You give the mad house key back to Vortimer.")) 

NO(ReturnKey) 
	Conversation
	INTL( 8109, "You know where to find me if you ever change your mind.")
	
YesNoELSE(ReturnKey) 
	Conversation
	INTL( 10675, "So, you want to give me back the mad house key?")
	SetYesNo(ReturnKey) 

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS ")) 
INTL( 10676, "I have no time for this nonsense.") 
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 1075, "Farewell.") 
BREAK

Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 2025, "I have no idea.")
ELSE
   Conversation
   INTL( 10677, "That is not a concern of mine at the moment.")
ENDIF

EndTalk
}
				 
