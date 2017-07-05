#pragma hdrstop
#include "PortalJ3.h"

PortalJ3::PortalJ3()
{}

PortalJ3::~PortalJ3()
{}

extern NPCstructure::NPC PortalNPC;

void PortalJ3::Create( ){
	npc = PortalNPC;
	SET_NPC_NAME(  "[7396]A shimmering portal" );
	npc.InitialPos.X = 2724; 
	npc.InitialPos.Y = 2376;
	npc.InitialPos.world = 0;
}
void PortalJ3::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void PortalJ3::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void PortalJ3::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk
 
Begin
""
IF (IsInRange(3)) 
	IF (CheckItem(__OBJ_C1_PERMIT) == 0) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 10633, "You need the C1 permit to gain access to this portal."))
	ELSE
		TELEPORT( 2822,2593,0)
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

