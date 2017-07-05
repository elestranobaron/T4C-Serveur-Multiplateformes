//////////////////////////////////////////////////////////////////////
// WoundedGuard.cpp: implementation of the WoundedGuard class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "WoundedGuard.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WoundedGuard::WoundedGuard()
{}

WoundedGuard::~WoundedGuard()
{}

extern NPCstructure::NPC Guard_One;

//Nom: Wounded Guard.
//Statistique: Windhowl Wounded Guard.
//Position: (2299, 687)
//World: 0
//Description: Wounded guard.
//Body: Guard.

//////////////////////////////////////////////////////////////////////////////////////////
void WoundedGuard::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of WoundedGuard
//
{
	npc = Guard_One;
	SET_NPC_NAME( "[3027]A wounded guard" );
	npc.InitialPos.X = 1787;
	npc.InitialPos.Y = 1293;
	npc.InitialPos.world = 0;  
}

//////////////////////////////////////////////////////////////////////////////////////////
void WoundedGuard::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of WoundedGuard
//
{

InitTalk

Begin
INTL( 2757, "Urrhh.. Arhhh... The... \"pain\" is... excruciating.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2758, "My name? Who cares about names when you are in such \"pain\" "
"as I am!")

Command(INTL( 523, "ANNABELLE"))
INTL( 2759, "I've seen her near the troll. She tried to stop him from hurting me... "
"and he obeyed!!")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2760, "Do not talk me about your... *urrrgh* problems... I have my own as you... aah... see!")

Command2(INTL( 535, "TROLL"),INTL( 484, "MHORGWLOTH"))
""
IF (CheckFlag (__TROLL_QUEST_DONE) == 3 )
	Conversation
	INTL( 2761, "I am... glad... you took care of him... arrrh!")
ELSE
	IF (CheckFlag(__TROLL_QUEST_DONE) == 2)
		Conversation
		INTL( 2762, "Arh... Huh? You have slain the troll? You... argh... are truly "
		"a friend. I... urgh... thank you for teaching him... a lesson. "
		"I give you... arrrgh... the pain! Take this shield... now... go"
		"... my friend.")
		GiveItem(__OBJ_WINDHOWL_SHIELD) 
		GiveFlag(__TROLL_QUEST_DONE, 3) 
	ELSE
		Conversation
		INTL( 2763, "Slay... the troll... then... return and argh... I... will give you "
		"a reward... for your... deed.")
		GiveFlag(__TROLL_QUEST_DONE, 1 )
	ENDIF
ENDIF

Command(INTL( 2764, "PAIN"))
INTL( 2765, "The... \"troll\" did this to me... argh!")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2766, "Do... I look like... urgh... somebody who can still... arrrh... work?")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2767, "Urgh...") BREAK

Default
INTL( 2768, "I... arhh... do not... argh... care.")

EndTalk

}
