// Markam.cpp: implementation of the Markam class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Markam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Markam::Markam()
{}

Markam::~Markam()
{}

extern NPCstructure::NPC MarkamNPC;

void Markam::Create(){ 
	npc = MarkamNPC;
	SET_NPC_NAME( "[3048]Markam" );
  npc.InitialPos.X = 2954;
  npc.InitialPos.Y = 1102;
	npc.InitialPos.world = 0;
}

void Markam::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	switch(rnd(0, 1)){
	case 0: SHOUT(INTL( 1378, "AHHHHHHHHHHHHHH!")); break;
	case 1: SHOUT(INTL( 1379, "HELP!")); break;
	}

	self->Do(flee);
	self->SetTarget(target);
	NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}


void Markam::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 21)
	Conversation
	INTL( 11768, "There was some commotion outside just before you arrived. I wonder if anyone got hurt...")
ELSE
	Conversation
	INTL( 11769, "I wish these damned guards would go away. Lord Kirlor doesn't show it, but he's really disturbed "
	"by their presence.")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1728, "The name is Markam Korwald to you, stranger.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1729, "My duties are numerous in this town. You might say that I am "
"\"Lord\" \"Kirlor\"'s assistant.")

Command(INTL( 523, "ANNABELLE"))
INTL( 1730, "Annabelle? I heard she is a lovely lady, but somewhat odd, even though I've never "
"met her.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2670, "Balork's Brand? Huh?")

Command2(INTL( 1435, "LORD"),INTL( 1436, "KIRLOR"))
INTL( 1731, "Lord Kirlor has been looking for adventurers lately to help in the protection "
"of the local \"merchants\".")

Command(INTL( 753, "GOLDMOON"))
INTL( 1732, "It is the kingdom regrouping all the villages on the islands of \"Arakas\" "
"and \"Raven's\" \"Dust\".")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 1733, "That is the island you can see just southwest of here.")

Command(INTL( 515, "ARAKAS"))
INTL( 1734, "Arakas is the island you are currently standing on.")

Command(INTL( 1257, "MERCHANT"))
INTL( 1735, "The merchants are constantly being robbed by \"brigands\" while trying to "
"cross the forest to \"Windhowl\". They are having a hard time. Their shops are "
"losing money and all. ")

Command(INTL( 617, "REWARD"))
INTL( 1736, "Reward? For what?")

Command(INTL( 554, "HELP"))
INTL( 1737, "All you have to do is \"register\" at the Lord's office, and find a merchant.")

Command(INTL( 514, "WINDHOWL"))
INTL( 1738, "The western town on the island, Windhowl is the biggest town in the "
"kingdom of \"Goldmoon\". But be careful if you go there because \"brigands\" "
"and strange creatures have been ambushing careless wanderers lately.")

Command(INTL( 565, "BRIGAND"))
INTL( 2792, "Brigands have been banding together in large groups to attack our \"merchant\" "
"carriers. If one could \"help\" them by bringing a simple report to "
"Lord Sunrock in \"Windhowl\", it would allow both towns to send "
"guarded merchant caravans at a secret planned time and do business without "
"fearing the interference of the brigands. If you are an adventurer, then "
"by all means, talk to Lord Kirlor in his office and \"register\" yourself!")
		 
Command(INTL( 1257, "MERCHANT"))
INTL( 2793, "These days, it is near impossible for the merchants of our fair city to do business with our "
"sister town, \"Windhowl\". If you would like to help one of our merchants, you must talk to "
"\"Lord\" \"Kirlor\" and \"register\" yourself. He will then give you a letter that you must "
"give to either \"Sigfried\" or \"Rolph\". They'll give you a report that must be delivered "
"to \"Lord\" \"Sunrock\" in Windhowl as fast as possible.")

Command(INTL( 1648, "REGISTER"))
INTL( 2794, "You must say this to \"Lord\" \"Kirlor\", not me!")

Command(INTL( 2518, "SIGFRIED"))
INTL( 2781, "Sigfried is the town's weaponsmith.")

Command(INTL( 2345, "ROLPH"))
INTL( 7163, "Rolph is the town's armorer.")

Command(INTL( 1436, "KIRLOR"))
INTL( 2783, "He is the town's Lord.")

Command(INTL( 514, "WINDHOWL"))
INTL( 2791, "Windhowl is a town located to the western part of the island.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 1607, "Lighthaven is the name of our fair city.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1740, "Until we meet again.") BREAK

Default
INTL( 1741, "Ask around, my friend.")

EndTalk

}
