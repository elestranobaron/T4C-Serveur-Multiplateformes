#pragma hdrstop
#include "OracleGuardian1a.H"

OracleGuardian1a::OracleGuardian1a()
{}

OracleGuardian1a::~OracleGuardian1a()
{}

extern NPCstructure::NPC OracleGuardian1NPC;

void OracleGuardian1a::Create( void )
{
        npc = ( OracleGuardian1NPC );
        SET_NPC_NAME( "[10904]A timeless guardian" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}


void OracleGuardian1a::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	TFormat FORMAT;
	if( target != NULL )
	{
		IF(CheckItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE) == 0)
			GiveItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9368, "An oddly shaped shard of stone falls to the floor and you quickly pick it up."))
		ELSEIF(CheckItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE) == 1)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9369, "An oddly shaped shard of stone falls to the floor and crumbles to dust."))
		ELSEIF(CheckItem(__OBJ_ODDLY_SHAPED_SHARD_OF_STONE) >= 2)
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