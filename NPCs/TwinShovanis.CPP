#pragma hdrstop
#include "TwinShovanis.H"

TwinShovanis::TwinShovanis()
{}

TwinShovanis::~TwinShovanis()
{}

extern NPCstructure::NPC Mage;

void TwinShovanis::Create( void )
{
        npc = Mage;
        SET_NPC_NAME( "[3059]Shovanis" );
        npc.InitialPos.X = 318;
        npc.InitialPos.Y = 295;
        npc.InitialPos.world = 1;
}

void TwinShovanis::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk
					   
Begin
INTL( 2129, "Are you in trouble, my friend?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2130, "I am called Shovanis, the Mage.")

Command4(INTL( 489, "WORK"),INTL( 2115, "PRIEST"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 2131, "I have the gift of \"magic\" and I will \"help\" you to the best of my knowledge.")

Command(INTL( 554, "HELP"))
INTL( 2132, "Well, there isn't much I can do, other than \"teach\" you a \"spell\" or two.")

Command3(INTL( 700, "SPELL"),INTL( 496, "TEACH"),INTL( 495, "LEARN"))
INTL( 7526, "This is what I can teach you.")
CreateSkillList
	AddTeachSkill (__SPELL_DUST_DEVIL, 7, 2388)
	AddTeachSkill (__SPELL_CURSE, 17, 17200)
	AddTeachSkill (__SPELL_WORD_OF_RECALL, 12, 18753)
SendTeachSkillList

Command(INTL( 569, "HEAL"))
INTL( 2163, "My brother takes care of healing.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2117, "Balork is lurking in the depth of this dungeon.")

Command(INTL( 2164, "NEVANIS"))
INTL( 2165, "Ahh, so you met my brother already? I hope he was able to help you.")

Command(INTL( 2166, "SHOVANIS"))
INTL( 2167, "I am the Mage in the family. My brother prefers to worship a god.")

Command(INTL( 1096, "MAGIC"))
INTL( 2168, "Magic can be very dangerous. Power in the hands of those who cannot control "
"it can be a danger to themselves and to those around them.")

Command(INTL( 2174, " THE ONE "))
INTL( 2175, "Who? Aah... You're a believer? I don't believe in any god. I believe in my "
"magic and myself. That is all I need. It is your choice to believe or not "
"in a god. That's what makes my brother and I different.")

Command(INTL( 2176, "COMINGS"))
INTL( 2177, "Ha! My brother's doing is it? I never cared about the comings. Don't believe "
"everything you hear, that's what I always say.")

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2127, "Take care.") BREAK

Default
INTL( 2128, "You should find out yourself.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void TwinShovanis::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_DUST_DEVIL, 7, 2388)
         TEACH_SKILL(__SPELL_CURSE, 17, 17200)
         TEACH_SKILL(__SPELL_WORD_OF_RECALL, 12, 18753)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE

