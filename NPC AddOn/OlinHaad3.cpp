#pragma hdrstop
#include "OlinHaad3.h"

OlinHaad3::OlinHaad3()
{}

OlinHaad3::~OlinHaad3()
{}

extern NPCstructure::NPC OlinHaad3NPC;

void OlinHaad3::Create( ){
	npc = OlinHaad3NPC;
	SET_NPC_NAME( "[12758]Olin Haad");
	npc.InitialPos.X = 0; 
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}

void OlinHaad3::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
		switch(rnd(0, 20))
			{
			case 0: CastSpellSelf(__SPELL_MOB_FAST_REGEN); break;
			case 1: SHOUT(INTL( 12515, "You cannot defeat me... I am stronger than you!")); break;			
			default: break;
			}
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void OlinHaad3::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OlinHaad3::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
	
	IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_GLURIURL_PRESENT) == 1)
		SELF_DESTRUCT
	ENDIF

NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}

void OlinHaad3::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_GLURIURL_PRESENT) == 0)	
		SHOUT(INTL( 12516, "Death is nothing to me... NOTHING.. for I have already won!!")) 
		SHOUT(INTL( 12517, "Let's see how you'll fare against my master... Gluriurl, God of Corruption!")) 
		SUMMON("GLURIURL", 1772, 2379) 
	ENDIF
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void OlinHaad3::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 41)
	Conversation
	INTL( 1864, "...")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 41)
	Conversation
	INTL( 12518, "Ha ha ha! You're too late... The ritual is complete! The resurrection of Gluriurl is at hand!")
	FIGHT
ELSE
	Conversation
	INTL( 12519, "What is this?!? What am I doing here? ...You! You did this to me! DIE!")
	FIGHT
ENDIF
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk
}