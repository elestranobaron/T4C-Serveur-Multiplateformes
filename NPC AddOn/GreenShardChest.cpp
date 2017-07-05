#pragma hdrstop
#include "GreenShardChest.h"

GreenShardChest::GreenShardChest()
{}

GreenShardChest::~GreenShardChest()
{}

extern NPCstructure::NPC WoodenChestNPC;

void GreenShardChest::Create( ){
	npc = WoodenChestNPC;
  SET_NPC_NAME( "[10840]wooden chest" );
  npc.InitialPos.X = 2076;
  npc.InitialPos.Y = 2435;
  npc.InitialPos.world = 1;
}
void GreenShardChest::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void GreenShardChest::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void GreenShardChest::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(IsInRange(4))
  IF(CheckItem(__OBJ_GREEN_CRYSTAL_SHARD) >= 1)
    PRIVATE_SYSTEM_MESSAGE(INTL( 11894, "You open the chest but find nothing inside."))
  ELSEIF(CheckFlag(__FLAG_ADDON_CHEST_INSPECT_COUNT) == 0) 
      PRIVATE_SYSTEM_MESSAGE(INTL( 11894, "You open the chest but find nothing inside."))
      GiveFlag(__FLAG_ADDON_CHEST_INSPECT_COUNT, 1) 
  ELSE
      PRIVATE_SYSTEM_MESSAGE(INTL( 12167, "Upon closer inspection of the chest, you discover a false bottom!")) 
      PRIVATE_SYSTEM_MESSAGE(INTL( 12168, "You lift the false bottom and find a green crystal shard."))
      GiveItem(__OBJ_GREEN_CRYSTAL_SHARD)    
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
