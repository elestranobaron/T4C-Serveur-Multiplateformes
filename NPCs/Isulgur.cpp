//////////////////////////////////////////////////////////////////////
// Isulgur.cpp: implementation of the Isulgur class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Isulgur.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Isulgur::Isulgur()
{}

Isulgur::~Isulgur()
{}

extern NPCstructure::NPC IsulgurNPC;

void Isulgur::Create(){
	npc = IsulgurNPC;
	SET_NPC_NAME( "[3041]Isulgur" );
    npc.InitialPos.X = 2970;
    npc.InitialPos.Y = 1096;
	npc.InitialPos.world = 0;
}

void Isulgur::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	switch(rnd(0, 1)){
	case 0: SHOUT(INTL( 1378, "AHHHHHHHHHHHHHH!")); break;
	case 1: SHOUT(INTL( 1379, "HELP!")); break;
	}

	self->Do(flee);
	self->SetTarget(target);
	NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Isulgur::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 21)
	Conversation
	INTL( 11753, "I heard some disturbance outside just a few moments ago.")
ELSE
	Conversation
	INTL( 11754, "Greetings, my \"name\" is Isulgur. Please be brief, I am rather busy what with the guards "
	"roaming around and the brigands.")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1433, "My name is Isulgur. I \"work\" for the town's \"Lord\".")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1434, "I work for Kirlor, the \"lord\" of Lighthaven. Since the \"brigands\" started "
"attacking the \"merchants\", we have been very busy here at the "
"\"lord\"'s office.")

Command(INTL( 523, "ANNABELLE"))
INTL( 665, "I heard a rumor that she is much older than what she appears to be.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 820, "Balork's curse? That's horrible!")

Command2(INTL( 1435, "LORD"),INTL( 1436, "KIRLOR"))
INTL( 1437, "Kirlor is the first and only lord this town has ever had. I'd have to say he has "
"done a fine job up until now. The problem is that ever since \"Theodore\" XIII "
"won the title of king of \"Goldmoon\", things have been going pretty bad "
"around here, especially for the \"merchants\".")

Command(INTL( 753, "GOLDMOON"))
INTL( 1438, "Goldmoon is the kingdom regrouping all the villages on the islands of \"Arakas\" "
"and \"Raven's\" \"Dust\".")

Command(INTL( 1284, "RAVEN"))
INTL( 1439, "Raven's Dust is the island on which the castle of \"Theodore\" XIII is located.  "
"Travel southward from \"Arakas\" to find it.")

Command(INTL( 515, "ARAKAS"))
INTL( 1440, "That is the name of the island you are currently on.")

Command(INTL( 754, "THEODORE"))
INTL( 1441, "Yes, Theodore XIII.  If you ask me, he isn't half the king his \"father\" "
"used to be. He's so lazy, nothing ever gets done right around here. I heard "
"things are getting pretty bad with the \"goblin\" invasion of \"Windhowl\", "
"and having a sleepy king is no help, let me tell you!")

Command(INTL( 539, "GOBLIN"))
INTL( 1442, "Goblin legions are massed in the mountains at the northwest corner of "
"the island. \"Windhowl\" is the only defense standing between us and them.")

Command(INTL( 1443, "FATHER"))
INTL( 1444, "Theodore's father was King Theopold. A great king indeed, he united all "
"the villages of the land of \"Goldmoon\" to fight against the ever growing "
"hordes of goblins. His leadership led to a legendary victory and brought "
"peace throughout the land. Ever since Theodore gained the throne two years "
"ago, things have been taking a turn for the worse. The goblins have begun "
"making slow progress and the King is doing nothing about it.")

Command(INTL( 1257, "MERCHANT"))
INTL( 2784, "These days, it is near impossible for the merchants of our fair city to do business with our "
"sister town, \"Windhowl\". If you would like to help one of our merchants, you must talk to "
"\"Lord\" \"Kirlor\" and \"register\" yourself. He will then give you a letter that you must "
"give to either \"Sigfried\" or \"Rolph\". They'll give you a report that must be delivered "
"to \"Lord\" \"Sunrock\" in Windhowl as fast as possible.")

Command(INTL( 1648, "REGISTER"))
INTL( 2785, "You must say this to \"Lord\" \"Kirlor\", not me!")

Command(INTL( 2518, "SIGFRIED"))
INTL( 2781, "Sigfried is the town's weaponsmith.")

Command(INTL( 2345, "ROLPH"))
INTL( 7163, "Rolph is the town's armorer.")

Command(INTL( 1436, "KIRLOR"))
INTL( 2783, "He is the town's Lord.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 1607, "Lighthaven is the name of our fair city.")
Command(INTL( 554, "HELP"))
INTL( 1446, "To help a merchant travel across the forest, all you have to do is register "
"at the \"Lord\"'s office.")

Command(INTL( 514, "WINDHOWL"))
INTL( 1447, "The westernmost town on the island, Windhowl is the greatest in the kingdom. "
"Still, be careful if you go there, \"brigands\" and strange creatures roam around "
"the outskirts, ambushing wanderers.")

Command(INTL( 565, "BRIGAND"))
INTL( 1448, "They have been regrouping lately and they are attacking our merchants "
"every time they try to pass through the forest. I wish someone would "
"stop them. They are ruining us!")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1449, "Goodbye brave adventurer.") BREAK

Default
INTL( 1450, "I can't help you with this.")

EndTalk

}
