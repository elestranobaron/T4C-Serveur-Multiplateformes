#pragma hdrstop
#include "StaticDungeonPortal1.h"

StaticDungeonPortal1::StaticDungeonPortal1()
{}

StaticDungeonPortal1::~StaticDungeonPortal1()
{}

extern NPCstructure::NPC IslandPortalNPC;

void StaticDungeonPortal1::Create( ){
    npc = IslandPortalNPC;
    SET_NPC_NAME(  "[7400]A flickering portal" );
    npc.InitialPos.X = 391;
    npc.InitialPos.Y = 2846;
    npc.InitialPos.world = 1;
}
void StaticDungeonPortal1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
{}
}

void StaticDungeonPortal1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void StaticDungeonPortal1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	IF(CheckGlobalFlag(__GLOBAL_FLAG_SCATTERED_BONES_PRESET) == 1)
		TELEPORT( 647, 2790, 1)
	ELSE
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
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF
BREAK

Default 
"" BREAK

EndTalk
}
