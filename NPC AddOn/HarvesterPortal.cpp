#pragma hdrstop
#include "HarvesterPortal.h"

HarvesterPortal::HarvesterPortal()
{}

HarvesterPortal::~HarvesterPortal()
{}

extern NPCstructure::NPC PortalNPC;

void HarvesterPortal::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 1129;
    npc.InitialPos.Y = 1190;
    npc.InitialPos.world = 0;
}

void HarvesterPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void HarvesterPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void HarvesterPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(IsInRange(4))
	IF((CheckItem(__OBJ_HEL_SOULSTONE) >= 1) && (CheckItem(__OBJ_JORMUNGAND_SOULSTONE) >= 1) && (CheckItem(__OBJ_FENRIR_SOULSTONE) >= 1))
		TakeItem(__OBJ_HEL_SOULSTONE)
		TakeItem(__OBJ_JORMUNGAND_SOULSTONE)
		TakeItem(__OBJ_FENRIR_SOULSTONE)
		PRIVATE_SYSTEM_MESSAGE(INTL( 12275, "As the three soulstones meld together, you are pulled inside the portal."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 12008, "You feel as though your body will not survive long on this plane of existence..."))
		CastSpellTarget(__SPELL_HARVESTER_RETURN_TELEPORT)
		TELEPORT(2710, 1040, 1)
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
