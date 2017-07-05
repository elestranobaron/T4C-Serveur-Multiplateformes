///////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "OracleChest14.h"

OracleChest14::OracleChest14()
{}

OracleChest14::~OracleChest14()
{}

extern NPCstructure::NPC OracleChestNPC;

void OracleChest14::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void OracleChest14::Create( void )
{
      npc = ( OracleChestNPC );
      SET_NPC_NAME( "[10840]wooden chest" );  
      npc.InitialPos.X = 2886; 
      npc.InitialPos.Y = 2266;
      npc.InitialPos.world = 2;
}

void OracleChest14::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OracleChest14::OnTalk( UNIT_FUNC_PROTOTYPE )
///////////////////////////////////////////////////////////////////////////

{

InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckItem(__OBJ_EXQUISITELY_WORKED_STONE_KEY) >= 1)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8700, "The chest is empty."))
	ELSEIF(CheckItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE) >= 6)
		;int nNumShardStones = CheckItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE); 
		FOR(0, nNumShardStones)
			TakeItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE)
		ENDFOR
		GiveItem(__OBJ_EXQUISITELY_WORKED_STONE_KEY)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9363, "Using all the oddly shaped shards of stone you possess, you unlock the chest."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 9364, "Inside the chest you find an exquisitely worked stone key."))
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 9355, "The chest is locked."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 9365, "You notice six oddly shaped holes where there should be a lock."))
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