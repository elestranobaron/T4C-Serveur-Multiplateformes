#pragma hdrstop
#include "StrongholdToOlinPortal.h"

StrongholdToOlinPortal::StrongholdToOlinPortal()
{}

StrongholdToOlinPortal::~StrongholdToOlinPortal()
{}

extern NPCstructure::NPC PortalNPC;

void StrongholdToOlinPortal::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[7396]A shimmering portal" );
    npc.InitialPos.X = 1897;
    npc.InitialPos.Y = 2151;
    npc.InitialPos.world = 1;
}

void StrongholdToOlinPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void StrongholdToOlinPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void StrongholdToOlinPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))  
	IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) >= 42)
		PRIVATE_SYSTEM_MESSAGE(INTL( 12587, "The portal is sealed.")) 
	ELSEIF((CheckItem(__OBJ_RED_CRYSTAL_SHARD)>=1)&&(CheckItem(__OBJ_GREEN_CRYSTAL_SHARD)>=1)&&(CheckItem(__OBJ_YELLOW_CRYSTAL_SHARD)>=1)&&(CheckItem(__OBJ_BLUE_CRYSTAL_SHARD)>=1)&&(CheckItem(__OBJ_VIOLET_CRYSTAL_SHARD)>=1))
		PRIVATE_SYSTEM_MESSAGE(INTL( 12588, "You step inside the portal and your vision begins to blur..."))   
		TELEPORT(1674,2273,1) 
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 12589, "You step inside the portal but nothing happens.")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 12590, "You notice five triangular recesses at the base of the portal.")) 
	ENDIF 	  
ELSE
  PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF  
BREAK

Default
INTL( 7353, "This is a bug, please report it.")

EndTalk
}
