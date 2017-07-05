#pragma hdrstop
#include "SufferingPortal1.h"

SufferingPortal1::SufferingPortal1()
{}

SufferingPortal1::~SufferingPortal1()
{}

extern NPCstructure::NPC PortalNPC;

void SufferingPortal1::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 1254;
    npc.InitialPos.Y = 1868;
    npc.InitialPos.world = 1;
}

void SufferingPortal1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void SufferingPortal1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void SufferingPortal1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
  TELEPORT(1082,1511,1)      
ELSE
  PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF  
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk
}
