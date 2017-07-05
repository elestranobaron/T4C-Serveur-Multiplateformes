#pragma hdrstop
#include "DoppelgangerPortal2b.h"

DoppelgangerPortal2b::DoppelgangerPortal2b()
{}

DoppelgangerPortal2b::~DoppelgangerPortal2b()
{}

extern NPCstructure::NPC PortalNPC;

void DoppelgangerPortal2b::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[12731]A radiating portal" );
    npc.InitialPos.X = 3006;
    npc.InitialPos.Y = 1350;
    npc.InitialPos.world = 1;
}
void DoppelgangerPortal2b::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void DoppelgangerPortal2b::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DoppelgangerPortal2b::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk

Begin
""
IF(IsInRange(4))
IF(USER_LEVEL >= 50 || CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= 2)//BLBLBL BL added limit on level 50
	PRIVATE_SYSTEM_MESSAGE(INTL( 12018, "You step through the portal and appear somewhere else."))
	CastSpellTarget(__SPELL_DOPPELGANGER_RETURN_TELEPORT_DISPEL)
	TELEPORT(1723, 1246, 0)
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
