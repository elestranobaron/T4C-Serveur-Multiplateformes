#pragma hdrstop
#include "SanctuaryPortal.h"

SanctuaryPortal::SanctuaryPortal()
{}

SanctuaryPortal::~SanctuaryPortal()
{}

extern NPCstructure::NPC IslandPortalNPC;

void SanctuaryPortal::Create( ){
    npc = IslandPortalNPC;
    SET_NPC_NAME(  "[7400]A flickering portal" );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
    npc.InitialPos.world = 0;
}
void SanctuaryPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
{}
}

void SanctuaryPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void SanctuaryPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
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
BREAK

Default
""
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
ENDIF
BREAK

EndTalk

}