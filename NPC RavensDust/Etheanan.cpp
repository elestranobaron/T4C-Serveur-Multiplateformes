//////////////////////////////////////////////////////////////////////
// Etheanan.cpp: implementation of the Etheanan class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Etheanan.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Etheanan::Etheanan()
{}

Etheanan::~Etheanan()
{}

extern NPCstructure::NPC Mage;

void Etheanan::Create( ){
	npc = Mage ; 
	SET_NPC_NAME( "[2948]Etheanan" );
	npc.InitialPos.X = 617; 
	npc.InitialPos.Y = 1900;
	npc.InitialPos.world = 0;
}

void Etheanan::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT FISHING = 1;
CONSTANT BreakConversation = 100;

InitTalk

Begin
INTL( 1923, "Greetings, what can I do for you?")

Command(INTL( 3629, " NAME "))
INTL( 6448, "There are a very few people who know me. My name is Etheanan. What can I do for you?")

Command(INTL( 6450, "ETHEANAN"))
INTL( 6451, "Yes? Do I know you? Hmm, somehow I doubt that.")

Command(INTL( 489, "WORK"))
INTL( 6453, "I am a \"wizard\", though a very \"special\" one at that.")

Command(INTL( 6455, "WIZARD"))
INTL( 6456, "Yes, I create my own \"spells\" to help with my everyday \"chores\".")

Command(INTL( 6457, "CHORES"))
INTL( 6458, "These include \"fishing\", \"hunting\", \"cleaning\", oh and \"cooking\", of course. Heh heh heh.")

Command(INTL( 6459, "FISHING"))
INTL( 6460, "Ahh, one of the better things in life, if you ask me. Do you like to fish by any chance?")
SetYesNo(FISHING)

YES(FISHING)
	Conversation
	INTL( 6461, "Why that's splendid! Perhaps we could go together one day. If the opportunity ever arises, I'll be "
	"certain to let you know of it.")
NO(FISHING)
	Conversation
	INTL( 6462, "A pity, I must say.")
YesNoELSE(FISHING)
	Conversation
	INTL( 6463, "I really wish you would just answer my question. Do you like to fish or not?")
	SetYesNo(FISHING)

Command(INTL( 6464, "HUNTING"))
INTL( 6465, "Hmm, my food stores are getting quite a bit low, if I do say so myself. I'll not survive the next season if "
"I don't get around to start hunting again. I don't really enjoy it, but it is a must for someone who lives "
"around here.")
	
Command(INTL( 6466, "CLEANING"))
INTL( 6467, "Bah! That is the one thing I truly dislike. I live so far away from the general populace that I cannot get a "
"decent maid. If it wasn't for my magic, I would have gone back to \"civilization\" a long time ago.")

Command(INTL( 6468, "CIVILIZATION"))
INTL( 6469, "I am referring, of course, to the city of \"Silversky\".")

Command(INTL( 998, "SILVERSKY"))
INTL( 6470, "It is a fine city, but one I try to avoid nonetheless.")

Command(INTL( 6471, "COOKING"))
INTL( 6472, "\"Nothing\" \"like\" \"a\" \"home-cooked\" \"meal\", that's what I always say!")

Command(INTL( 6473, "NOTHING LIKE A HOME-COOKED MEAL"))
INTL( 6474, "Hah! you think so too eh?")

Command(INTL( 6475, "SPECIAL"))
INTL( 6476, "Well, I am what you might call an \"elementalist\".")

Command(INTL( 6477, "ELEMENTALIST"))
INTL( 6478, "Yes, I have devoted my life to the study of all things arcane, but especially to the \"elements\".")

Command(INTL( 6479, "ELEMENT"))
INTL( 6480, "There are six elements in this plane of existence. Nearly all spells are connected with at least one of these "
"elements. They are fire, water, air, earth, light and dark. There are many \"theories\" "
"and \"beliefs\" out there about what happens when you cast a spell, but very few are actually accurate.")

Command(INTL( 6481, "BELIEFS"))
INTL( 6482, "Many people think that \"mana\" flows all around us, and that they can just bend and shape it to their will. "
"This is at the most only partly true. \"Mana\" does flow around us, but not how you would think.")

Command(INTL( 6483, "THEORIES"))
INTL( 6484, "Well for instance, many people, wizards included, believe that casting a spell involves channeling raw mana "
"and altering it through force of will into one of the six elements for easier manipulation and containment. "
"This is in fact a misconception, as the mana is not so much channeled and then altered, as it is drawn from "
"one of the \"metaplanes\".")

Command(INTL( 6485, "METAPLANE"))
INTL( 6486, "The elemental metaplanes are where the true magic comes from. Whenever a wizard casts a spell, he is in fact "
"tapping into one of the metaplanes. Each metaplane can be tapped for mana of the appropriate element. For "
"example, to cast a firestorm, I would create a link between the elemental metaplane of fire and myself, allowing "
"myself to draw sufficient mana to cast my spell. This is all done instinctively, of course, so no one would ever "
"believe you if you tried to explain it to them.")

Command(INTL( 6487, "RAW SPELLS"))
INTL( 6488, "These often consist of utility spells and are most subject to having special, if not strange effects. "
"The mana burst spell, for instance, is one such raw spell, and is quite useful in certain circumstances. At "
"first sight, this spell appears to be rather weak, but careful examination will reveal a great potential on "
"magic-resistant creatures. Because of the nature of this spell, the damage it inflicts may not be resisted "
"by a creature's natural magic defenses.")

Command3(INTL( 7074, "SPELLS"),INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 6489, "Ahhh, so you would like to learn some of my spells, is that it? Very well then.")
CreateSkillList
	AddTeachSkill (__SPELL_FIRE_SHIELD, 21, 85632)
	AddTeachSkill (__SPELL_RAIN_OF_FIRE, 22, 103297)
	AddTeachSkill (__SPELL_MANA_SURGE, 23, 107028)
	AddTeachSkill (__SPELL_MANA_SHIELD, 14, 33553)
	AddTeachSkill (__SPELL_GLACIER, 23, 110825)
	AddTeachSkill (__SPELL_ELECTRIC_SHIELD, 21, 89033)
SendTeachSkillList

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 6987, "Very well, go in peace.") BREAK

Command(INTL( 902, "MANA"))
INTL( 7076, "To understand mana is to control it. Each spell requires a special kind of mana, whether it be a simple fire dart "
"spell or a devastating avalanche spell. There are, of course, exceptions to this rule, which we will call \"raw\" "
"\"spells\".")

;} else if(YesNo == BreakConversation) {;YesNo = 0;
BREAK

Default
INTL( 624, "What are you talking about?")

EndTalk

}
//////////////////////////////////////////////////////////////////////////////////////////
void Etheanan::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_FIRE_SHIELD, 21, 85632)
         TEACH_SKILL(__SPELL_RAIN_OF_FIRE, 22, 103297)
         TEACH_SKILL(__SPELL_MANA_SURGE, 23, 107028)
         TEACH_SKILL(__SPELL_MANA_SHIELD, 14, 33553)
         TEACH_SKILL(__SPELL_GLACIER, 23, 110825)
         TEACH_SKILL(__SPELL_ELECTRIC_SHIELD, 21, 89033)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE