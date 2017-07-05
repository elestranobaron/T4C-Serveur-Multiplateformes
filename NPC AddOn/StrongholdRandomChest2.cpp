///////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "StrongholdRandomChest2.h"

StrongholdRandomChest2::StrongholdRandomChest2()
{}

StrongholdRandomChest2::~StrongholdRandomChest2()
{}

extern NPCstructure::NPC WoodenChestNPC;

void StrongholdRandomChest2::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void StrongholdRandomChest2::Create( void )
{
      npc = ( WoodenChestNPC );
      SET_NPC_NAME( "[10840]wooden chest" );  
      npc.InitialPos.X = 1700; 
      npc.InitialPos.Y = 1952;
      npc.InitialPos.world = 1;
}

void StrongholdRandomChest2::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void StrongholdRandomChest2::OnTalk( UNIT_FUNC_PROTOTYPE )
///////////////////////////////////////////////////////////////////////////

{

InitTalk

Begin
"" 
IF(IsInRange(4))
  IF(CheckItem(__OBJ_VIOLET_CRYSTAL_SHARD) >= 1)
    PRIVATE_SYSTEM_MESSAGE(INTL( 8700, "The chest is empty."))
  ELSEIF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_RANDOM_CHEST) == 0)
    GiveGlobalFlag(__GLOBAL_FLAG_ADDON_RANDOM_CHEST, rnd.roll(dice(1, 7)))
    IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_RANDOM_CHEST) == 2)
      GiveItem(__OBJ_VIOLET_CRYSTAL_SHARD)
    PRIVATE_SYSTEM_MESSAGE(INTL( 12586, "You find a violet crystal shard inside the chest."))
    GiveGlobalFlag(__GLOBAL_FLAG_ADDON_RANDOM_CHEST, rnd.roll(dice(1, 7)))
		ELSE
      PRIVATE_SYSTEM_MESSAGE(INTL( 8700, "The chest is empty."))
		ENDIF
  ELSEIF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_RANDOM_CHEST) == 2)
    GiveItem(__OBJ_VIOLET_CRYSTAL_SHARD)
    PRIVATE_SYSTEM_MESSAGE(INTL( 12586, "You find a violet crystal shard inside the chest."))
    GiveGlobalFlag(__GLOBAL_FLAG_ADDON_RANDOM_CHEST, rnd.roll(dice(1, 7)))
	ELSE
    PRIVATE_SYSTEM_MESSAGE(INTL( 8700, "The chest is empty."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 8702, "You must step closer to the chest to open it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk
}
