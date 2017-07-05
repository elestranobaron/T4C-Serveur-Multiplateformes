// Lothan.cpp: implementation of the Lothan class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Lothan.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Lothan::Lothan()
{}

Lothan::~Lothan()
{}

extern NPCstructure::NPC Mage;

void Lothan::Create(){
	npc = Mage;
	SET_NPC_NAME( "[3047]Lothan" );
	npc.InitialPos.X = 2979;
	npc.InitialPos.Y = 968;
	npc.InitialPos.world = 0;
}

void Lothan::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk

Begin
INTL( 1657, "Welcome to the \"tower\", stranger.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1658, "My name is Lothan, pleased to meet you.")

Command4(INTL( 489, "WORK"),INTL( 1659, "MAGE"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 1660, "I am a mage who studies the element of \"water\". I have been assigned the "
"task of watching over \"Araknor\". I have yet another concern, however. The "
"orc shaman named \"Araf\" \"Kul\" is dangerously growing in power. I highly "
"doubt he will ever be a match for my magic. However, I wonder what special component "
"he uses for his spell casting.") 

Command(INTL( 523, "ANNABELLE"))
INTL( 1661, "I don't know where she is. Sorry I couldn't help you.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 1662, "Curse that Balork and his Brand! There are many like you who walk the land "
"and bear his mark. I tell you, friend, you have to seek Annabelle, blessed be "
"her eyes! She'll know what to do.")

CmdAND(INTL( 1663, "YELLOW"),INTL( 1664, "POWDER"))
""
IF (CheckItem(__OBJ_POUCH_OF_YELLOW_POWDER) >= 1)
	TakeItem(__OBJ_POUCH_OF_YELLOW_POWDER)	
	Conversation
	INTL( 1665, "You took this pouch of yellow powder from the corpse of Araf'Kul? "
	"I will exchange it for...")
	SWITCH( rnd.roll( dice( 1, 3 ) ))
		CASE (1)
			Conversation
			INTL( 1666, " this magnificient Ring of the Initiate!")
			GiveItem(__OBJ_RING_OF_THE_INITIATE)
		ENDCASE
		CASE (2)
			Conversation
			INTL( 1667, " 850 gold pieces. I think it will be enough since Araf'Kul was not "
			"a very challenging opponent.")
			GiveGold(850)
		ENDCASE
		CASE (3)
			Conversation
			INTL( 1668, " this pair of Gloves of the Duelist. They are of no use to me since I never "
			"have to physically fight anyone. My spells alone are more than enough "
			"to handle the \"goblins\".")
			GiveItem(__OBJ_GLOVES_OF_THE_DUELIST)
		ENDCASE
	ENDSWITCH
ELSE
	Conversation
	INTL( 1670, "Yellow powder? Now that might be an interesting component for magical "
	"spells.")
ENDIF

Command(INTL( 1671, "POUCH"))
INTL( 1672, "Pouch? A pouch of what?")

Command(INTL( 1673, "HUMAN BONE"))
INTL( 1674, "Human bone? I could simply ask \"Araknor\" for one, he has a collection "
"of them, you know.")

Command2(INTL( 1675, "PINK LEAF"),INTL( 1676, "PINK TREE"))
INTL( 1677, "The leaf of a pink tree? What would I do with that? Pfah! I'll tell you..."
"NOTHING! Well, perhaps a druid could find a use for it of course.")

Command2(INTL( 744, "ORC"),INTL( 1678, "ARAF"))
INTL( 1679, "He is a shaman orc and surprisingly skilled in the art of magic for one "
"of his race.")

Command(INTL( 734, "ARAKNOR"))
INTL( 1680, "He is someone who just can't be trusted. He is a follower of the ways of "
"necromancy, and therefore is a very dark and disturbed individual. He is "
"currently a resident of the \"tower\" and benefits from the massive \"library\" "
"stored here. This is the only reason why he would accept to pay the "
"ridiculous sums of money we charge him to stay here. If it was up to me, I would "
"kick him out of the \"kingdom\" myself, but our town is in dire need of "
"resources due to the \"brigands\" roaming around town.")

Command(INTL( 514, "WINDHOWL"))
INTL( 1681, "Our sister town on this isle, Windhowl is located on the western part of "
"the island. Because of its proximity to the goblin hideout, it is always "
"assaulted by the \"goblin\" army. Fortunately, the guardsmen have done a good "
"job repelling them. Let's hope they will hold on until reinforcements arrive.")

Command(INTL( 1429, "LIBRARY"))
INTL( 1682, "The tower's library is a place where knowledge from all over the world is "
"stored. You can find information on just about any subject in there.")

Command(INTL( 565, "BRIGAND"))
INTL( 2788, "Brigands are attacking all the \"merchants\" crossing the forest to the west. "
"If you wish to help, go see Lord Kirlor's office.")

Command(INTL( 1686, "TOWER"))
INTL( 1687, "The tower of magic contains a great \"library\", where thousands of books "
"containing all sorts of information can be found.")

Command2(INTL( 753, "GOLDMOON"),INTL( 994, "KINGDOM"))
INTL( 1688, "Goldmoon is the kingdom regrouping the islands of Raven's Dust and Arakas, "
"which is the one you are currently on. As for Raven's Dust, it is the island "
"southwest of here, where the castle of King \"Theodore\" XIII is located.")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 1689, "Raven's Dust is a small island located southwest of this island.")

Command(INTL( 754, "THEODORE"))
INTL( 1690, "I must say, he is the worst king the kingdom has ever had! He always sleeps "
"and never gets anything done, even now as the \"goblin\" hordes are gaining "
"ground. These are indeed dark times we live in...")

Command(INTL( 539, "GOBLIN"))
INTL( 1691, "I don't know precisely what is happening with them, only that we are slowly "
"losing the battle. Some say they even witnessed certain goblins carrying "
"magical weapons! I fail to see how that is possible, goblins being rather "
"stupid and wanting nothing to do with magic.")
		 
Command(INTL( 1257, "MERCHANT"))
INTL( 2789, "These days, it is near impossible for the merchants of our fair city to do business with our "
"sister town, \"Windhowl\". If you would like to help one of our merchants, you must talk to "
"\"Lord\" \"Kirlor\" and \"register\" yourself. He will then give you a letter that you must "
"give to either \"Sigfried\" or \"Rolph\". They'll give you a report that must be delivered "
"to Lord Sunrock in Windhowl as fast as possible.")

Command(INTL( 1648, "REGISTER"))
INTL( 2790, "You must say this to \"Lord\" \"Kirlor\", not me!")

Command(INTL( 2518, "SIGFRIED"))
INTL( 2781, "Sigfried is the town's weaponsmith.")

Command(INTL( 2345, "ROLPH"))
INTL( 7163, "Rolph is the town's armorer.")

Command(INTL( 1436, "KIRLOR"))
INTL( 2783, "He is the town's Lord.")

Command(INTL( 514, "WINDHOWL"))
INTL( 7179, "Windhowl is a town located to the southwestern part of the island.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 1607, "Lighthaven is the name of our fair city.")

Command(INTL( 2590, "WATER"))
INTL( 1693, "I have studied long and hard to master the use of these \"spells\"... Perhaps one day, "
"when you are strong enough, I will \"teach\" you some of them.")

Command3(INTL( 700, "SPELL"),INTL( 496, "TEACH"),INTL( 495, "LEARN"))
INTL( 7520, "Let's see if you are ready for what I can teach you.")
CreateSkillList
	AddTeachSkill (__SPELL_POISON_ARROW, 10, 12937)
	AddTeachSkill (__SPELL_POISON, 7, 3017)
	AddTeachSkill (__SPELL_ICE_SHARD, 8, 4473)
SendTeachSkillList

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"),INTL( 521, "EXIT"),INTL( 519, "LEAVE"))
INTL( 973, "Goodbye.") BREAK

Default
INTL( 1726, "Please forgive me, I cannot help you.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Lothan::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
     TEACH_SKILL(__SPELL_POISON, 7, 3017)
     TEACH_SKILL(__SPELL_ICE_SHARD, 8, 4473)
     TEACH_SKILL(__SPELL_POISON_ARROW, 10, 12937)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE

