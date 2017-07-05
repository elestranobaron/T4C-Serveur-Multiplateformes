//////////////////////////////////////////////////////////////////////
// ElmertMerkiss.cpp: implementation of the ElmertMerkiss class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "ElmertMerkiss.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ElmertMerkiss::ElmertMerkiss()
{}

ElmertMerkiss::~ElmertMerkiss()
{}

extern NPCstructure::NPC Guard_One;

void ElmertMerkiss::Create(){
    npc = Guard_One;
	SET_NPC_NAME( "[3035]Elmert Merkiss" );
    npc.InitialPos.X = 2868;
    npc.InitialPos.Y = 1135;
	npc.InitialPos.world = 0;
}

void ElmertMerkiss::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk

Begin
INTL( 1277, "Aye! Greetings! What \"news\" bring you here my friend?")

Command(INTL( 1278, "NEWS"))
INTL( 11748, "Well, since the \"brigands\" have been attacking travelers in the forest, "
"we haven't had many visitors. These guards roaming all over town aren't helping either, "
"let me tell you. I wish the war with \"Windhowl\" and the "
"goblins would end so we can have some guards to help with the \"brigands\" "
"in the forest. At least, sometimes \"Murmuntag\" takes it upon "
"himself to go scare them away.")

Command(INTL( 1037, "MURMUNTAG"))
INTL( 1280, "Aye, my friend, he isn't very smart, but he could take ten of my best "
"men single-handedly. When he makes his surprise attack on the \"brigands\" "
"in the forest, they usually calm down for a day or two. I wish I could "
"send him there more often, but we need him to guard the town.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 1281, "I am the town's chief guard. I have the responsibility to ensure the "
"town stays safe for our citizens.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1282, "Aye! I am Elmert Merkis, but please, do call me Elmert.")

Command(INTL( 514, "WINDHOWL"))
INTL( 1283, "Windhowl is our sister town on the island. It is currently battling against "
"the goblins in the northwestern mountains, trying to stop them from invading "
"all of the island. But since King \"Theodore\" rose to power, the goblins "
"have been gaining territory rather quickly. Reinforcements are always "
"coming late, or never coming at all. I'm sure they could use good fighters.")

Command(INTL( 1284, "RAVEN"))
INTL( 1285, "Raven's Dust is the island southwest of here. It is there that the castle of "
"King \"Theodore\" resides. Most of the guards and soldiers in \"Goldmoon\"'s "
"army are trained there.")

Command(INTL( 791, "GLOOMBLADE"))
""
IF (USER_LEVEL >= 10)
	Conversation
	INTL( 1286, "You're not going to believe this, but someone told me that a friend of his heard this "
	"as the dying words of a man who barely escaped Balork with his life... That Balork "
	"is building swords of darkness such as the Gloomblade to equip his evil armies when they "
	"try to take over our town. If you find some, give them to the priests. They can "
	"destroy them... I think.")
ELSE
	Conversation
	INTL( 1287, "These matters don't concern you, citizen. You are not of sufficient rank for me "
	"to share this kind of information with you.")
ENDIF

Command(INTL( 753, "GOLDMOON"))
INTL( 1288, "Goldmoon is the kingdom that encompasses the islands of \"Raven's\" \"Dust\" and "
"the island you are currently on, Arakas.")

Command(INTL( 754, "THEODORE"))
INTL( 1289, "That sorry excuse for a king sleeps half of the time, and awakens only to "
"go back to sleep! Meanwhile, \"Windhowl\"'s guards are decreasing at an "
"alarming rate.")

Command(INTL( 565, "BRIGAND"))
INTL( 1290, "I don't know what's been up with them lately, but they are constantly "
"attacking our \"merchants\" when they attempt to do business with \"Windhowl\". "
"This is nothing new, but lately they have been banding together and are in larger "
"groups. I wish I could solve this problem, but I don't have time to take care of it.")

Command(INTL( 1257, "MERCHANT"))
INTL( 2779, "These days, it is near impossible for the merchants of our fair city to do business with our "
"sister town, \"Windhowl\". If you would like to help one of our merchants, you must talk to "
"\"Lord\" \"Kirlor\" and \"register\" yourself. He will then give you a letter that you must "
"give to either \"Sigfried\" or \"Rolph\". They'll give you a report that must be delivered "
"to \"Lord\" \"Sunrock\" in Windhowl as fast as possible.")

Command(INTL( 1648, "REGISTER"))
INTL( 2780, "You must say this to \"Lord\" \"Kirlor\", not me!")

Command(INTL( 2518, "SIGFRIED"))
INTL( 2781, "Sigfried is the town's weaponsmith.")

Command(INTL( 2345, "ROLPH"))
INTL( 7163, "Rolph is the town's armorer.")

Command(INTL( 1436, "KIRLOR"))
INTL( 2783, "He is the town's Lord.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 1607, "Lighthaven is the name of our fair city.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 1292, "Ugh!") BREAK

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 1293, "Have a nice day.") BREAK

Default
INTL( 1294, "How would I know?")

EndTalk

}
