#pragma hdrstop
#include "TwinNevanis.H"

TwinNevanis::TwinNevanis()
{}

TwinNevanis::~TwinNevanis()
{}

extern NPCstructure::NPC Priest;

void TwinNevanis::Create( void )
{
	npc = Priest;
	SET_NPC_NAME( "[3058]Nevanis" );
	npc.InitialPos.X = 302;
	npc.InitialPos.Y = 288;
	npc.InitialPos.world = 1;
	npc.boPrivateTalk = TRUE;
}

void TwinNevanis::OnTalk( UNIT_FUNC_PROTOTYPE )
 
{
InitTalk

Begin
INTL( 2113, "I may \"help\" you, my friend, if you are in trouble.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2114, "I am called Brother Nevanis.")

Command4(INTL( 489, "WORK"),INTL( 2115, "PRIEST"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 2116, "I am here to \"help\" you.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2117, "Balork is lurking in the depth of this dungeon.")

Command(INTL( 554, "HELP"))
INTL( 2118, "I could \"heal\" your wounds, if it is what you want.")

Command(INTL( 569, "HEAL")) 
""
IF (USER_MAXHP == USER_HP)
	Conversation
	INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
	Conversation
	INTL( 2119, "I will \"help\" you until you can take care of yourself alone.")
	CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
	HealPlayer(USER_MAXHP)
	PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
ENDIF

Command(INTL( 2120, "MOONROCK"))
INTL( 2121, "She is a priestess in the \"temple\" above.")

Command(INTL( 2122, "KILHIAM"))
INTL( 2123, "She is a priestess of Artherk in the \"temple\" above. She is recruiting "
"adventurers to rescue the poor fools who dared to challenge \"Balork\".")

Command(INTL( 1365, "TEMPLE"))
INTL( 2124, "This was once part of the temple too. But since \"Balork\" has taken "
"control of the temple, few travel here.")

Command(INTL( 509, "BALORK"))
INTL( 2125, "He was once a war-priest of \"Artherk\" but went insane when he lost "
"his faith.")

Command(INTL( 1243, "ARTHERK"))
INTL( 2126, "Artherk does not forgive easily. That is one reason why \"Balork\" left the "
"brotherhood. During a battle, he had to choose between helping his fallen "
"comrade or inflict revenge on the enemy who had killed him. His anger took "
"control and he went berserk. The battle was won but at a high cost. In his "
"rage, Balork had accidentally killed one of his priests. Shortly after, he "
"was demoted to a normal priest.")

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2127, "Take care.") BREAK

Default
INTL( 2128, "You should find out yourself.")

EndTalk

}
