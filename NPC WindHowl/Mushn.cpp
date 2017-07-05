// Mushn.cpp: implementation of the Mushn class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Mushn.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Mushn::Mushn()
{}

Mushn::~Mushn()
{}

extern NPCstructure::NPC MushnNPC;

//////////////////////////////////////////////////////////////////////////////////////////
void Mushn::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Mushn
//
{
	npc = MushnNPC;
	SET_NPC_NAME( "[3019]Mushn" );
	npc.InitialPos.X = 1755;
	npc.InitialPos.Y = 1319;
	npc.InitialPos.world = 0;  
}

//////////////////////////////////////////////////////////////////////////////////////////
void Mushn::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Mushn
//
{

InitTalk
					 
Begin
""
IF (CheckFlag(__QUEST_CURE_GEENA) == 1)
	Conversation
	INTL( 2652, "Sweet n lovin' Geena is currently ill with the goblin fever? 'Tis quite a sad bit o'news "
 "you're bringin' t'me, m'friend. Fortunately, I've jus' the thing she be needin'. Give her "
 "this leaf. It comes from a rare enchanted tree an' can cure her disease.") 
	GiveItem(__OBJ_HEALING_LEAF) // Leaf of a healing tree
	RemFlag(__QUEST_CURE_GEENA) 
ELSE
	Conversation
	INTL( 2653, "Hello, how may I be of service?")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2654, "I'm Mushn. Greetings to you too.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2655, "I own a farm, and I can tell you, it's a job that \"occupies\" me every minute "
"of the day.")

Command(INTL( 523, "ANNABELLE"))
INTL( 2656, "I've never heard of that woman.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2657, "Balork's curse? As long as it does not tamper with my crops...")

Command(INTL( 2658, "OCCUP"))
INTL( 2659, "Yes, there are so many things to do on a farm like this. Feed the animals, "
"cultivate the wheat and plant new grains. I sure could use some help around "
"here, but unfortunately, I'm not making much money, and those darn \"goblins\" "
"are making the trading business very difficult.")

Command(INTL( 539, "GOBLIN"))
INTL( 3634, "Darn little red demons. Several days ago, one got through here, and I had "
"to kill it myself with my shovel. I wish somebody would go to the northern "
"mountains and wipe them out!")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 1293, "Have a nice day.") BREAK

Default
INTL( 624, "What are you talking about?")

EndTalk

}
