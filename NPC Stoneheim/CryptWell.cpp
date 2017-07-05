#pragma hdrstop
#include "CryptWell.h"

CryptWell::CryptWell()
{}

CryptWell::~CryptWell()
{}

extern NPCstructure::NPC CryptWellNPC;

void CryptWell::OnAttacked( UNIT_FUNC_PROTOTYPE ){
     {}	
}

void CryptWell::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}
void CryptWell::Create( void )
{
    npc = CryptWellNPC;
    SET_NPC_NAME( "[10842]A well" );
    npc.InitialPos.X = 705;
    npc.InitialPos.Y = 1005;
    npc.InitialPos.world = 1;
	 npc.boPrivateTalk = TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void CryptWell::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
{
InitTalk

Begin
""
IF(IsInRange(5))  
		IF(CheckGlobalFlag(__GLOBAL_FLAG_CRYPT_CHEST_1_DESTROYED) == 1)
			GiveGlobalFlag(__GLOBAL_FLAG_CRYPT_CHEST_1_DESTROYED, 0)
			SUMMON("CRYPTCHEST1", 560, 1075)
		ENDIF
		IF(CheckGlobalFlag(__GLOBAL_FLAG_CRYPT_CHEST_2_DESTROYED) == 1)
			GiveGlobalFlag(__GLOBAL_FLAG_CRYPT_CHEST_2_DESTROYED, 0)
			SUMMON("CRYPTCHEST2", 558, 1068)
		ENDIF
		IF(CheckGlobalFlag(__GLOBAL_FLAG_CRYPT_CHEST_3_DESTROYED) == 1)
			GiveGlobalFlag(__GLOBAL_FLAG_CRYPT_CHEST_3_DESTROYED, 0)
			SUMMON("CRYPTCHEST3", 561, 1061)
		ENDIF
		IF(CheckGlobalFlag(__GLOBAL_FLAG_CRYPT_CHEST_4_DESTROYED) == 1)
			GiveGlobalFlag(__GLOBAL_FLAG_CRYPT_CHEST_4_DESTROYED, 0)
			SUMMON("CRYPTCHEST4", 568, 1058)
		ENDIF
		IF(CheckGlobalFlag(__GLOBAL_FLAG_CRYPT_CHEST_5_DESTROYED) == 1)
			GiveGlobalFlag(__GLOBAL_FLAG_CRYPT_CHEST_5_DESTROYED, 0)
			SUMMON("CRYPTCHEST5", 575, 1060)
		ENDIF
	IF(CheckItem(__OBJ_DEW_COVERED_METAL_KEY) >= 1)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9212, "As you approach the well to look inside, part of it crumbles and you fall in..."))		
	ELSE
		GiveItem(__OBJ_DEW_COVERED_METAL_KEY)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9213, "As you grab the dew-covered key, part of the well crumbles and you fall in...")) 		
	ENDIF
	TELEPORT(569, 1069, 1)
ELSE 
	IF(CheckItem(__OBJ_DEW_COVERED_METAL_KEY) == 0)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9214, "You catch a glimmer of something shiny resting on the side of the well."))
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 9215, "You must step closer to the well to look inside.")) 	
	ENDIF
ENDIF   
BREAK 

Default
""
BREAK

EndTalk
}

