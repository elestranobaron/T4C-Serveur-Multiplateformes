//////////////////////////////////////////////////////////////////////
// Geena.cpp: implementation of the Geena class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Geena.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Geena::Geena()
{}

Geena::~Geena()
{}

extern NPCstructure::NPC GeenaNPC;

//////////////////////////////////////////////////////////////////////////////////////////
void Geena::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Geena
//
{
    npc = GeenaNPC;
	SET_NPC_NAME( "[3037]Geena" );
    npc.InitialPos.X = 2864;
    npc.InitialPos.Y = 1058;
	npc.InitialPos.world = 0;
	
}

//////////////////////////////////////////////////////////////////////////////////////////
void Geena::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Geena
//
{

InitTalk

Begin
""
IF( CheckGlobalFlag( __GLOBAL_QUEST_WHO_IS_INFECTED ) == 2 ) 
        GiveNPCFlag( __NPC_FLAG_GEENA_INFECTED, rnd.roll(dice(12, 4) ) MINUTES TDELAY )
	GiveGlobalFlag( __GLOBAL_QUEST_WHO_IS_INFECTED, 0 )
ENDIF
IF (CheckNPCFlag( __NPC_FLAG_GEENA_INFECTED) > CurrentRound)
   IF (CheckItem(__OBJ_HEALING_LEAF) > 0)
		TakeItem(__OBJ_HEALING_LEAF)
		Conversation
		INTL( 1314, "You have... brought back brown roots? Thank you... This will hopefully "
		"cure me and ease the pain... Ah... Thank you... Tell Halam I feel much better now.")
		GiveFlag(__QUEST_GOBLIN_GEENA_GO_SEE_HALAM, 1)
		GiveNPCFlag(__NPC_FLAG_GEENA_INFECTED, 0) 
	ELSE
      Conversation  // still infected.
      INTL( 1315, "...Think I have caught the terrible... Goblin fever. You... "
      "see Mushn and ask him... cure... pleas...")
      GiveFlag(__QUEST_CURE_GEENA, 1)
      BREAK
   ENDIF
ELSEIF ((CheckNPCFlag( __NPC_FLAG_GEENA_INFECTED ) < CurrentRound) && (CheckNPCFlag( __NPC_FLAG_MURMUNTAG_INFECTED ) != 0 ))
	Conversation
	INTL( 1316, "Hmmmm. I think the fever's gone... Finally! Thank you for your concern about my well-being.")
	GiveNPCFlag( __NPC_FLAG_GEENA_INFECTED, 0)
ELSE	
	Conversation
	INTL( 11750, "I hope I don't see to many guards tonight... oh I'm sorry, can I help you with something?")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1318, "Call me Geena.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1319, "I'm the waitress here.  I help \"Halam\" in his work.")

Command(INTL( 523, "ANNABELLE"))
INTL( 1158, "I do not know much about that woman.")

Command2(INTL( 2364, "ALE"),INTL( 1346, "DRINK" ))
INTL( 7297, "I'll be with you as soon as I have a minute.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2670, "Balork's Brand? Huh?")

Command(INTL( 1320, "HALAM")) // Testing
INTL( 1321, "He's very nice, and always joyful.  He speaks to all the \"travelers\".")

Command(INTL( 1322, "TRAVELER"))
INTL( 1323, "We haven't seen many lately. I'm waiting for the day that a nice adventurer "
"will ask to \"marry\" me.")

Command(INTL( 1324, "MARRY"))
INTL( 1325, "I'll wait until a rich adventurer comes to marry me.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1326, "Goodbye now.") BREAK

Default
INTL( 1327, "Pardon?")

EndTalk
}
