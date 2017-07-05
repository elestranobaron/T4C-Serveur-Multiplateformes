#pragma hdrstop
#include "PortalC1.h"

PortalC1::PortalC1()
{}

PortalC1::~PortalC1()
{}

extern NPCstructure::NPC PortalNPC;

void PortalC1::Create( ){
	npc = PortalNPC;
	SET_NPC_NAME(  "[7396]A shimmering portal" );
	npc.InitialPos.X = 2824; 
	npc.InitialPos.Y = 2591;
	npc.InitialPos.world = 0;
}
void PortalC1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void PortalC1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void PortalC1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
"" 
IF (IsInRange(3)) 
	IF (CheckItem(__OBJ_C1_PERMIT) == 0) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 10633, "You need the C1 permit to gain access to this portal."))
	ELSE					
		TELEPORT( 2722, 2378, 0)
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

