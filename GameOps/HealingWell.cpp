#pragma hdrstop
#include "HealingWell.h"

HealingWell::HealingWell()
{}

HealingWell::~HealingWell()
{}

extern NPCstructure::NPC HealingWellNPC;

void HealingWell::OnAttacked( UNIT_FUNC_PROTOTYPE ){
     {}
	
}

void HealingWell::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}
void HealingWell::Create( void )
{
    npc = HealingWellNPC;
    SET_NPC_NAME( "[2991]A well" );
    npc.InitialPos.X = 129;
    npc.InitialPos.Y = 2909;
    npc.InitialPos.world = 1;
	 npc.boPrivateTalk = TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void HealingWell::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
{
InitTalk

Begin
""
IF (IsInRange(7))
	IF (CheckGlobalFlag(__GLOBAL_FLAG_HEALING_WELL_ENABLED) == 0)
	   IF (USER_MAXHP == USER_HP)
			PRIVATE_SYSTEM_MESSAGE(INTL( 7354, "Nothing happens."))      
		ELSE
	      PRIVATE_SYSTEM_MESSAGE(INTL( 7355, "You feel better."))
			HealPlayer(USER_MAXHP)
		ENDIF
	ELSE
	   Conversation
	   INTL( 6393, "{You} {hear} {some} {faint} {sounds} {of} {dripping} {water.}")
	ENDIF	
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7356, "You must step closer to the well."))	
ENDIF
BREAK

Default
"" BREAK

EndTalk
}

