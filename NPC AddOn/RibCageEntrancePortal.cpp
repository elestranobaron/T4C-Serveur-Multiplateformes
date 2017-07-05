#pragma hdrstop
#include "RibCageEntrancePortal.h"

RibCageEntrancePortal::RibCageEntrancePortal()
{}

RibCageEntrancePortal::~RibCageEntrancePortal()
{}

extern NPCstructure::NPC PortalNPC;

void RibCageEntrancePortal::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 1095;
    npc.InitialPos.Y = 1494;
    npc.InitialPos.world = 1;
}

void RibCageEntrancePortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void RibCageEntrancePortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void RibCageEntrancePortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	IF(CheckItem(__OBJ_HEART_OF_GLURIURL) == 0) 			
		PRIVATE_SYSTEM_MESSAGE(INTL( 9373, "You step into the portal but nothing seems to happen.")) 		
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 12543, "The heart of Gluriurl begins to pulsate, causing the portal to shimmer in answer."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 12544, "You step inside the portal and your vision blurs briefly...")) 
		TELEPORT(930,1815,1)      
	ENDIF 
ELSE
  PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF  
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk
}
