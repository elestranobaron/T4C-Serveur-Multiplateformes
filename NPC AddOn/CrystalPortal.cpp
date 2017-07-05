#pragma hdrstop
#include "CrystalPortal.h"

CrystalPortal::CrystalPortal()
{}

CrystalPortal::~CrystalPortal()
{}

extern NPCstructure::NPC PortalNPC;

void CrystalPortal::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 948;
    npc.InitialPos.Y = 2328;
    npc.InitialPos.world = 1;
}
void CrystalPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}



void CrystalPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void CrystalPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	IF (CheckFlag(__FLAG_ADDON_CRYSTAL_KEY) == 1) 
		TELEPORT(937,2318,1) 
	ELSEIF ((CheckItem(__OBJ_CRYSTAL_KERVIAN) >=1)&&(CheckItem(__OBJ_CRYSTAL_VHARMES) >=1)&&(CheckItem(__OBJ_CRYSTAL_ASGOTH) >=1)&&(CheckItem(__OBJ_CRYSTAL_RAMIEL) >=1))				
		PRIVATE_SYSTEM_MESSAGE(INTL( 11946, "You carefully place the four crystals at the base of the portal.")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 11947, "The portal begins to glow and you step inside...")) 
		TakeItem(__OBJ_CRYSTAL_KERVIAN) 
		TakeItem(__OBJ_CRYSTAL_VHARMES) 
		TakeItem(__OBJ_CRYSTAL_ASGOTH) 
		TakeItem(__OBJ_CRYSTAL_RAMIEL) 
		GiveFlag(__FLAG_ADDON_CRYSTAL_KEY, 1) 
		TELEPORT(937,2318,1) 
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 11948, "The portal's magical energy appears to be depleted.")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 11949, "You notice four diamond-shaped holes at the base of the portal."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk

}
