#pragma hdrstop
#include "OracleGuardian1e.H"

OracleGuardian1e::OracleGuardian1e()
{}

OracleGuardian1e::~OracleGuardian1e()
{}

extern NPCstructure::NPC OracleGuardian1NPC;

void OracleGuardian1e::Create( void )
{
        npc = ( OracleGuardian1NPC );
        SET_NPC_NAME( "[10904]A timeless guardian" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}


void OracleGuardian1e::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	TFormat FORMAT;
	if( target != NULL )
	{
		IF(CheckItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE) == 0)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9369, "An oddly shaped shard of stone falls to the floor and crumbles to dust."))
		ELSEIF(CheckItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE) == 1)
			TakeItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9370, "As the guardian dies, it unleashes an ear-piercing scream."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 9372, "When you search your inventory for the other shard, all you find is dust."))
		ELSEIF(CheckItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE) == 2)
			TakeItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE)
			TakeItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9370, "As the guardian dies, it unleashes an ear-piercing scream."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 9371, "When you search your inventory for the other shards, all you find is dust."))
		ELSEIF(CheckItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE) == 3)
			TakeItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE)
			TakeItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE)
			TakeItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9370, "As the guardian dies, it unleashes an ear-piercing scream."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 9371, "When you search your inventory for the other shards, all you find is dust."))
		ELSEIF(CheckItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE) == 4)
			GiveItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9368, "An oddly shaped shard of stone falls to the floor and you quickly pick it up."))
		ELSEIF(CheckItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE) == 5)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9369, "An oddly shaped shard of stone falls to the floor and crumbles to dust."))
		ELSEIF(CheckItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE) == 6) 
			;int nNumShardStones = CheckItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE); 
			FOR(0, nNumShardStones)			
				TakeItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE)
			ENDFOR
			PRIVATE_SYSTEM_MESSAGE(INTL( 9370, "As the guardian dies, it unleashes an ear-piercing scream."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 9371, "When you search your inventory for the other shards, all you find is dust."))
		ENDIF
	}
    CLOSE_HANDLER

	NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}