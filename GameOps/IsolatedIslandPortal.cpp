#pragma hdrstop
#include "IsolatedIslandPortal.h"

IsolatedIslandPortal::IsolatedIslandPortal()
{}

IsolatedIslandPortal::~IsolatedIslandPortal()
{}

extern NPCstructure::NPC IslandPortalNPC;

void IsolatedIslandPortal::Create( ){
    npc = IslandPortalNPC;
    SET_NPC_NAME(  "[7395]A shimmering portal beckons for you to enter." );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
    npc.InitialPos.world = 0;
}
void IsolatedIslandPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
{}
}

void IsolatedIslandPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void IsolatedIslandPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	IF(CheckGlobalFlag(__GLOBAL_FLAG_ISOLATED_PRESET) == 1)
		   TELEPORT( 2640,2785, 0)
	ELSE	
		PRIVATE_SYSTEM_MESSAGE(INTL( 7357, "This portal is currently inactive."))
	ENDIF
ELSE	
	PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF
BREAK

Default
""
IF (IsInRange(4))
	IF(CheckGlobalFlag(__GLOBAL_FLAG_ISOLATED_PRESET) == 1)
		   TELEPORT( 2640,2785, 0)
	ELSE	
		PRIVATE_SYSTEM_MESSAGE(INTL( 7357, "This portal is currently inactive."))
	ENDIF
ELSE	
	PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF
BREAK

EndTalk

}
