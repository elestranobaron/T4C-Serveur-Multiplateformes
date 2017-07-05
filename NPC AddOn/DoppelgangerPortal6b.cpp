#pragma hdrstop
#include "DoppelgangerPortal6b.h"

DoppelgangerPortal6b::DoppelgangerPortal6b()
{}

DoppelgangerPortal6b::~DoppelgangerPortal6b()
{}

extern NPCstructure::NPC PortalNPC;

void DoppelgangerPortal6b::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[12731]A radiating portal" );
    npc.InitialPos.X = 2959;
    npc.InitialPos.Y = 1392;
    npc.InitialPos.world = 1;
}
void DoppelgangerPortal6b::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void DoppelgangerPortal6b::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DoppelgangerPortal6b::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk

Begin
""
IF(IsInRange(4))
IF(USER_LEVEL >= 50 || CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= 2)//BLBLBL BL added limit on level 50
	PRIVATE_SYSTEM_MESSAGE(INTL( 12018, "You step through the portal and appear somewhere else."))
	CastSpellTarget(__SPELL_DOPPELGANGER_RETURN_TELEPORT_DISPEL)
	TELEPORT(280, 2512, 0)
ELSE//BLBLBL BL added limit on level 50
	PRIVATE_SYSTEM_MESSAGE(INTL( 13034, "You must be level 50 or X2 at least to inspect this portal."))
	BREAK
ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 12014, "You must step closer to the portal to inspect it."))
ENDIF
BREAK


Default
INTL( 7353, "This is a bug, please report it.")

EndTalk

}
