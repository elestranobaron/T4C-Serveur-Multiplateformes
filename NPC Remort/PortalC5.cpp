#pragma hdrstop
#include "PortalC5.h"

PortalC5::PortalC5()
{}

PortalC5::~PortalC5()
{}

extern NPCstructure::NPC PortalNPC;

void PortalC5::Create( ){
	npc = PortalNPC;
	SET_NPC_NAME(  "[7396]A shimmering portal" );
	npc.InitialPos.X = 2810; 
	npc.InitialPos.Y = 2412;
	npc.InitialPos.world = 0;
}
void PortalC5::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void PortalC5::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void PortalC5::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
"" 
IF (IsInRange(3)) 
	IF (CheckItem(__OBJ_C5_PERMIT) == 0) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 10635, "You need the C5 permit to gain access to this portal."))
	ELSE					
		TELEPORT( 2723,2395,0)
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

