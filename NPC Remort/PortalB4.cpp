#pragma hdrstop
#include "PortalB4.h"

PortalB4::PortalB4()
{}

PortalB4::~PortalB4()
{}

extern NPCstructure::NPC PortalNPC;

void PortalB4::Create( ){
	npc = PortalNPC;
	SET_NPC_NAME(  "[7396]A shimmering portal" );
	npc.InitialPos.X = 2809; 
	npc.InitialPos.Y = 2550;
	npc.InitialPos.world = 0;
}
void PortalB4::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void PortalB4::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void PortalB4::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
"" 
IF (IsInRange(3)) 
	IF (CheckItem(__OBJ_J1_PERMIT) == 0) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 10634, "You need the J1 permit to gain access to this portal."))
	ELSE					
		TELEPORT( 2709, 2305, 0)
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

