#pragma hdrstop
#include "IslandPortal11.h"

IslandPortal11::IslandPortal11()
{}

IslandPortal11::~IslandPortal11()
{}

extern NPCstructure::NPC IslandPortalNPC;

void IslandPortal11::Create( ){
    npc = IslandPortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 2956;
    npc.InitialPos.Y = 2807;
    npc.InitialPos.world = 0;
}
void IslandPortal11::OnAttacked( UNIT_FUNC_PROTOTYPE ){
{}
}

void IslandPortal11::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void IslandPortal11::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(CheckGlobalFlag(__GLOBAL_FLAG_ISLAND_MAZE_PRESET) == 1)
	IF (IsInRange(4))
	   TELEPORT( 2949, 2847, 0)
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
	ENDIF
ELSE
	IF (IsInRange(4))
		UseC
		BYTE bPositionWorld = (target->ViewFlag(__FLAG_DEATH_LOCATION) & 0xFF);
		WORD wPositionY = (target->ViewFlag(__FLAG_DEATH_LOCATION) & 0xFFF00) >> 8;
		WORD wPositionX = (target->ViewFlag(__FLAG_DEATH_LOCATION) & 0xFFF00000) >> 20;
		IF(target->ViewFlag(__FLAG_DEATH_LOCATION) != 0)
			TELEPORT( wPositionX, wPositionY, bPositionWorld)
		ELSE
			TELEPORT(2941, 1062, 0)
		ENDIF
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
	ENDIF
ENDIF
BREAK

Default
""
BREAK

EndTalk

}