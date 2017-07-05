#pragma hdrstop
#include "ArenaMob80.H"

ArenaMob80::ArenaMob80()
{}

ArenaMob80::~ArenaMob80()
{}

extern NPCstructure::NPC ArenaMob80NPC;

void ArenaMob80::Create( void )
{
        npc = ( ArenaMob80NPC );
        SET_NPC_NAME( "[10967]Warskeleton" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void ArenaMob80::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	if( target != NULL )
	{
		IF(rnd.roll(dice(1, 100)) <= (110 - (USER_LEVEL)))
			GiveItem(__OBJ_COLOSSEUM_TOKEN)
			PRIVATE_SYSTEM_MESSAGE(INTL( 10682, "You receive a battle token for your efforts."))
		ENDIF
	}
    CLOSE_HANDLER

	CastSpellSelf(__SPELL_MOB_ARENA_LEVEL_SPELL)

	SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}

void ArenaMob80::OnDestroy( UNIT_FUNC_PROTOTYPE )
{
	IF(CheckGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA) > 0)
		GiveGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA, CheckGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA) - 1)
	ENDIF

	SimpleMonster::OnDestroy( UNIT_FUNC_PARAM );
}