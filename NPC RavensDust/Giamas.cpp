//////////////////////////////////////////////////////////////////////
// Giamas.cpp: implementation of the Giamas class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Giamas.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Giamas::Giamas()
{}

Giamas::~Giamas()
{}
 
extern NPCstructure::NPC GiamasNPC;

void Giamas::Create( ){
    npc = GiamasNPC;
 	SET_NPC_NAME( "[2951]Brother Giamas" );
    npc.InitialPos.X = 1548; 
    npc.InitialPos.Y = 2399;
	npc.InitialPos.world = 0;
}

void Giamas::OnTalk( UNIT_FUNC_PROTOTYPE )

{
 
InitTalk

Begin
INTL( 1230, "Greetings, my friend.")

Command(INTL( 3629, " NAME "))
INTL( 5117, "I am Brother Giamas.")

Command(INTL( 5118, "GIAMAS"))
INTL( 5119, "That is the name my god has chosen for me.")

Command2(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"))
INTL( 5120, "Ahh yes, I would gladly tell you about my work. Like many others, I am a priest and choose to worship "
"Artherk. I also make it a hobby of mine to \"teach\" some of what I know to strangers like yourself.")

Command(INTL( 4271, "CUTHANA"))
INTL( 5121, "'Tis a potent herb, when used by someone of pure spirit... I doubt that you could be such a person, "
"but the world is full of surprises.")

Command3(INTL( 700, "SPELL"),INTL( 496, "TEACH"),INTL( 495, "LEARN"))
INTL( 7556, "Here are the spells that I can teach you.")
CreateSkillList
	AddTeachSkill (__SPELL_EARTHEN_STRENGTH, 12, 22057)
	AddTeachSkill (__SPELL_STONE_SKIN, 17, 52577)
	AddTeachSkill (__SPELL_EARTHQUAKE, 20, 82297)
SendTeachSkillList

Command2(INTL( 5171, "GOD"),INTL( 1243, "ARTHERK"))
INTL( 5172, "I worship Artherk, and he looks after his people. He is a kind and just god and deserves all "
"the followers he can get.")

Command2(INTL( 1869, "TOWN"),INTL( 998, "SILVERSKY"))
INTL( 5173, "This is a beautiful town with alot of good people.")

Command(INTL( 3918, "VISITOR"))
INTL( 5174, "I have not seen anyone that fits that description, I'm afraid.")

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 5175, "May Artherk guide you, my friend.") BREAK

Default
INTL( 5176, "Can you elaborate a bit more?")

EndTalk

}
//////////////////////////////////////////////////////////////////////////////////////////
void Giamas::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_EARTHEN_STRENGTH, 12, 22057)
         TEACH_SKILL(__SPELL_STONE_SKIN, 17, 52577)
         TEACH_SKILL(__SPELL_EARTHQUAKE, 20, 82297)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE