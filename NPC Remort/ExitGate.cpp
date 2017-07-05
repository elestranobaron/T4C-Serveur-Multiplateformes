#pragma hdrstop
#include "ExitGate.h"

ExitGate::ExitGate()
{}

ExitGate::~ExitGate()
{}

extern NPCstructure::NPC PortalNPC;

void ExitGate::Create( ){
	npc = PortalNPC;
  SET_NPC_NAME(  "[11715]An exit gate" );
  npc.InitialPos.X = 0;  
  npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}

void ExitGate::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void ExitGate::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}


void ExitGate::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk 

Begin
""

IF (IsInRange(3))		 
	;BYTE bPositionWorld = (target->ViewFlag(__ARENA_RETURN_LOC) & 0xFF);
	WORD wPositionY = (target->ViewFlag(__ARENA_RETURN_LOC) & 0xFFF00) >> 8;
	WORD wPositionX = (target->ViewFlag(__ARENA_RETURN_LOC) & 0xFFF00000) >> 20;
	IF(target->ViewFlag(__ARENA_RETURN_LOC) != 0)
		TELEPORT( wPositionX, wPositionY, bPositionWorld)
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 11663, "ERROR!!!")) 
		TELEPORT(2941, 1062, 0)
	ENDIF 
ELSE
  PRIVATE_SYSTEM_MESSAGE(INTL( 11664, "You must step closer to the gate to activate it."))
ENDIF

BREAK

Default
""
BREAK

EndTalk
}