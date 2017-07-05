//////////////////////////////////////////////////////////////////////
// MarsacCred.cpp: implementation of the MarsacCred class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "MarsacCred.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MarsacCred::MarsacCred()
{}

MarsacCred::~MarsacCred()
{}

extern NPCstructure::NPC Mage;

//Nom: Marsac Cred.
//Statistique: Windhowl Mage.
//Position: (2134, 653)
//World: 0
//Description: Mage.
//Body: Mage.

//////////////////////////////////////////////////////////////////////////////////////////
void MarsacCred::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of MarsacCred
//
{
	npc = Mage;
	SET_NPC_NAME( "[3016]Marsac Cred" );
	npc.InitialPos.X = 1608;
	npc.InitialPos.Y = 1253;
	npc.InitialPos.world = 0;  
}

//////////////////////////////////////////////////////////////////////////////////////////
void MarsacCred::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of MarsacCred
//
{

CONSTANT MAKESCROLL = 1;
CONSTANT MAKESCROLL2 = 2;

InitTalk

Begin
INTL( 2568, "Hiya! What can I do for you?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2569, "I am Marsac Cred. Pleased to make your acquaintance.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2570, "I am an \"elemental\" mage, and I help \"R'yleth\" here in this tower "
"of magic.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2670, "Balork's Brand? Huh?")

Command(INTL( 523, "ANNABELLE"))
INTL( 665, "I heard a rumor that she is much older than what she appears to be.")

Command(INTL( 1424, "URANOS"))
""
IF (CheckFlag (__QUEST_URANOS) == 1)
 GiveFlag (__QUEST_URANOS_INGREDIENTS, 1)
 Conversation
 INTL( 2571, "So, Uranos needs a special component, eh? Well, he can thank his lucky star that "
 "I know exactly what he's looking for. You will have to find some decaying bat \"wings\" and bring "
 "them to him before they crumble to dust. He'll probably need more than one though, so get "
 "as many as you can.") 
ELSE
	Conversation
	INTL( 2572, "He's a friend of mine who lives in Lighthaven.")
ENDIF

Command(INTL( 2573, "WINGS"))
INTL( 2574, "They're just ordinary bat wings... Well, that's not entirely true. Actually, "
"the kind of wing he is looking for only comes from the undead bats that roam "
"in the dungeon under Lighthaven.")

Command(INTL( 2575, "R'YLETH"))
INTL( 2576, "R'yleth is the current mage \"Guildmaster\" here in Windhowl. His great "
"power is only matched by his enormous ego. *snicker* But other than that, "
"he truly is a master of magic. He has travelled much and has learned from "
"the greatest magicians that live.")

Command(INTL( 1181, "SCROLL OF ENCHANTMENT"))
INTL( 2577, "These are powerful scrolls indeed. They can help you make a magical item, or to "
"improve an item that is already magical. Would you like me to make one for you?")
SetYesNo(MAKESCROLL)

YES(MAKESCROLL)
Conversation
INTL( 2578, "Great. All you need is a \"blank\" \"magic\" \"scroll\", a \"human\" \"bone\", a \"runic\" "
"\"scripting\" \"box\" and, of course a donation of 4,000 GPs. So shall we proceed?")
SetYesNo(MAKESCROLL2)

NO(MAKESCROLL)
Conversation
INTL( 2579, "It's not that expensive... Only a few thousand gold pieces, really...")

YesNoELSE(MAKESCROLL)
Conversation
INTL( 2580, "Is that so?")

YES(MAKESCROLL2)
Conversation
INTL( 2581, "Let's get to work, then...")
 IF ((CheckItem(__OBJ_BLANK_MAGIC_SCROLL) >= 1) AND (CheckItem(__OBJ_HUMAN_BONE) >= 1) AND (CheckItem(__OBJ_RUNIC_SCRIPTING_KIT) >= 1) AND (Gold >= 4000))
		Conversation
		INTL( 2582, "Very good, very good. A little bit of this, a little bit of that... Let it rest "
		"for a few moments... And here we are!")
		TakeItem(__OBJ_BLANK_MAGIC_SCROLL)
		TakeItem(__OBJ_HUMAN_BONE)
		TakeGold(4000)
		GiveItem(__OBJ_SCROLL_OF_ENCHANTMENT)
	ELSE
		Conversation
		INTL( 2583, "Hey! May I remind you what I said earlier? Blank magic scroll, human bone, "
		"a runic scripting kit, 4,000 gold pieces. Come back when you've got everything.")
	ENDIF

NO(MAKESCROLL2)
Conversation
INTL( 712, "Very well.")

YesNoELSE(MAKESCROLL2)
Conversation
INTL( 2584, "Hm. I see.")

Command(INTL( 1175, "BLANK MAGIC SCROLL"))
INTL( 2585, "This type of scroll is required to create \"scroll\" \"of\" \"enchantment\". You should definitely "
"try to acquire a few. All true mages have them and trade them.")

Command(INTL( 1673, "HUMAN BONE"))
INTL( 2586, "Orcs sometimes collect those, so you know where to look. Go figure. *shrug*")

Command(INTL( 1385, "RUNIC SCRIPTING KIT"))
INTL( 2587, "You can't make that on your own, you have to check with someone who's specialized in "
"making such kits. I know of a certain Iraltok who could perhaps help you with that.")

Command(INTL( 2588, "ELEMENTAL"))
INTL( 2589, "Elemental magic is the base of all things pure. A mage can gather the mana "
"that flows around him and channel it into one of four elements and release the "
"energies in the form of a spell. I control the forces of \"water\".")

Command(INTL( 2590, "WATER"))
INTL( 2591, "Althought most of the time, water is peaceful in nature, it can sometimes "
"be devastating. I can show you how to harness the forces of water and \"teach\" "
"you how to cast water spells, so that you may use these forces to your advantage.")

Command3(INTL( 700, "SPELL"),INTL( 496, "TEACH"),INTL( 495, "LEARN"))
INTL( 7544, "I will teach you what I can.")
CreateSkillList
	AddTeachSkill (__SPELL_FREEZE, 11, 17200)
	AddTeachSkill (__SPELL_ICE_BOLT, 13, 25625)
SendTeachSkillList

Command(INTL( 2615, "GUILDMASTER"))
INTL( 2616, "The guildmaster's work consists of controlling the research of new spells "
"and the teaching of magic to apprentices. The guildmaster is also often asked "
"to help the city in various matters, mostly political.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 973, "Goodbye.") BREAK

Default
INTL( 2617, "Magic is all I need to know.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void MarsacCred::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
   TEACH_SKILL(__SPELL_FREEZE, 11, 17200)
   TEACH_SKILL(__SPELL_ICE_BOLT, 13, 25625)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE

