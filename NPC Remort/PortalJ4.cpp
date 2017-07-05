#pragma hdrstop
#include "PortalJ4.h"

PortalJ4::PortalJ4()
{}

PortalJ4::~PortalJ4()
{}

extern NPCstructure::NPC PortalNPC;

void PortalJ4::Create( ){
	npc = PortalNPC;
	SET_NPC_NAME(  "[7396]A shimmering portal" );
	npc.InitialPos.X = 2753; 
	npc.InitialPos.Y = 2230;
	npc.InitialPos.world = 0;
}
void PortalJ4::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void PortalJ4::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void PortalJ4::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk 

Begin
""
IF (IsInRange(3))		 
	IF (CheckItem(__OBJ_J4_PERMIT) == 0) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 10632, "You need the J4 permit to gain access to this portal."))
	ELSE	
	   TELEPORT( 2793,2567,0)
	ENDIF 
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}

