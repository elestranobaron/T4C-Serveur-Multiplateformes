#pragma hdrstop
#include "Kavarian.h"

Kavarian::Kavarian()
{}

Kavarian::~Kavarian()
{}

extern NPCstructure::NPC KavarianNPC;

void Kavarian::Create( ){
	npc = KavarianNPC;
	SET_NPC_NAME( "[10865]An intelligent-looking man" );
	npc.InitialPos.X = 531;
	npc.InitialPos.Y = 374;
	npc.InitialPos.world = 0;
}

void Kavarian::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	CastSpellSelf(__SPELL_MOB_INVISIBILITY_SPELL);
}

void Kavarian::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 8952, "?!? You can see me? Well, I must say that is quite a feat, considering I am \"invisible\".")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8953, "My name is Kavarian the Unseen.")

Command2(INTL( 8954, "KAVARIAN"), INTL( 8955, "UNSEEN"))
INTL( 8956, "Yes, I am Kavarian the Unseen. My knowledge of the \"arts\" has allowed me to become invisible to "
"the naked eye.")

Command(INTL( 8957, "ARTS"))
INTL( 8958, "I have been studying the art of spellcraft for a very long time now. Ever since I was but a small boy, "
"my path in life has always been that of the \"wizard\".")

Command(INTL( 6455, "WIZARD"))
INTL( 8959, "The path of the wizard is a hard one to follow, but in the end all the hard work pays off.")

Command(INTL( 8960, "INVISIB"))
INTL( 8961, "Well, my long \"research\" has taught me the ability to alter my physical appearance in such a way that I blend "
"into my surroundings, rendering me nearly invisible. Only those with a certain enchantment can see me.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8962, "I have long ago stopped working to pursue my own goals. As it happens, the \"research\" I have done has "
"allowed me to make a great deal of profit. Consequently, there is little I cannot provide for myself in the "
"way of material things.")

Command(INTL( 8963, "RESEARCH"))
INTL( 8964, "I have been conducting research in several fields of the mystic arts. Seeing as I am discovered, I see no harm in "
"\"teaching\" you a few of my best spells.")

Command2(INTL( 496, "TEACH"), INTL( 495, "LEARN"))
INTL( 8965, "Hmm, this is a strange variety of spells, you will probably think, but they are all very potent spells nonetheless.")
CreateSkillList
	AddTeachSkill (__SPELL_DISPEL, 28, 170913)
	AddTeachSkill (__SPELL_FLARE, 25, 130800)
	AddTeachSkill (__SPELL_MAJOR_COMBAT_SENSE, 27, 156948)
	AddTeachSkill (__SPELL_INVISIBILITY, 24, 122612)
SendTeachSkillList
	
Command(INTL( 8966, "DISPEL"))
INTL( 8967, "The dispel spell will remove all negative spells that are anchored on the target, and will have a chance of remove some "
"of the other spells also.")
	
Command(INTL( 8968, "FLARE"))
INTL( 8969, "The flare spell can inflict tremendous amounts of fire damage on a living target and may even set it on fire for "
"a short period of time. You are required to have the rain of fire spell before you can learn it.")

Command(INTL( 8970, "MAJOR COMBAT SENSE"))
INTL( 8971, "The major combat sense spell greatly augments the recipient's fighting abilities. You are required to have knowledge "
"of the minor combat sense spell to learn it.")
	
Command(INTL( 8972, "INVISIBILITY"))
INTL( 8973, "The invisibility spell renders the caster completely invisible to the naked eye. The caster will still be visible "
"to someone with the detect invisible spell cast upon them, however. To learn this spell, you must have knowledge "
"of the detect invisible spell.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 1075, "Farewell.")
BREAK

Default
INTL( 8974, "I have no time for such trivial things.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Kavarian::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_DISPEL, 28, 170913)
         TEACH_SKILL(__SPELL_FLARE, 25, 130800)
         TEACH_SKILL(__SPELL_MAJOR_COMBAT_SENSE, 27, 156948)
         TEACH_SKILL(__SPELL_INVISIBILITY, 24, 122612)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE