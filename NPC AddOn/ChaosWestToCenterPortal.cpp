#pragma hdrstop
#include "ChaosWestToCenterPortal.h"

ChaosWestToCenterPortal::ChaosWestToCenterPortal()
{}

ChaosWestToCenterPortal::~ChaosWestToCenterPortal()
{}

extern NPCstructure::NPC PortalNPC;

void ChaosWestToCenterPortal::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 1567;
    npc.InitialPos.Y = 1607;
    npc.InitialPos.world = 1;
}
 
void ChaosWestToCenterPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void ChaosWestToCenterPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void ChaosWestToCenterPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	IF((CheckFlag(__FLAG_ADDON_TERROR_DEMON_KILLED)==1)&&(CheckFlag(__FLAG_ADDON_CHAOS_DEMON_KILLED)==1)&&(CheckFlag(__FLAG_ADDON_DARKNESS_DEMON_KILLED)==1))
		TELEPORT(1605,1645,1) 
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 11906, "You step through the portal but nothing happens."))
	ENDIF
ELSE
  PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF  
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk
}
