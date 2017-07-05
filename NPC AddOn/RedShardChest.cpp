#pragma hdrstop
#include "RedShardChest.h"

RedShardChest::RedShardChest()
{}

RedShardChest::~RedShardChest()
{}

extern NPCstructure::NPC WoodenChestNPC;

void RedShardChest::Create( ){
	npc = WoodenChestNPC;
  SET_NPC_NAME( "[10840]wooden chest" );
  npc.InitialPos.X = 1572;
  npc.InitialPos.Y = 2052;
  npc.InitialPos.world = 1;
}
void RedShardChest::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void RedShardChest::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void RedShardChest::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(IsInRange(4))
  IF(CheckItem(__OBJ_RED_CRYSTAL_SHARD) >= 1)
    PRIVATE_SYSTEM_MESSAGE(INTL( 11894, "You open the chest but find nothing inside."))
  ELSE 
    GiveItem(__OBJ_RED_CRYSTAL_SHARD)
    PRIVATE_SYSTEM_MESSAGE(INTL( 12536, "You find a red crystal shard inside the chest."))
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
