#pragma hdrstop
#include "ArenaMob275.H"

ArenaMob275::ArenaMob275()
{}

ArenaMob275::~ArenaMob275()
{}

extern NPCstructure::NPC ArenaMob275NPC;

void ArenaMob275::Create( void )
{
        npc = ( ArenaMob275NPC );
        SET_NPC_NAME( "[10953]Darkcrawler" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void ArenaMob275::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
  	CastSpellSelf(__SPELL_MOB_ARENA_MINOR_REGENERATION_SPELL) 	
	SimpleMonster::OnPopup( UNIT_FUNC_PARAM );
}

void ArenaMob275::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	if( target != NULL )
	{
		IF(rnd.roll(dice(1, 100)) <= (290 - (USER_LEVEL)))
			GiveItem(__OBJ_COLOSSEUM_TOKEN)
			PRIVATE_SYSTEM_MESSAGE(INTL( 10682, "You receive a battle token for your efforts."))
		ENDIF
	}
    CLOSE_HANDLER

	CastSpellSelf(__SPELL_MOB_ARENA_LEVEL_SPELL)

	SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}

void ArenaMob275::OnDestroy( UNIT_FUNC_PROTOTYPE )
{
	IF(CheckGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA) > 0)
		GiveGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA, CheckGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA) - 1)
	ENDIF

	SimpleMonster::OnDestroy( UNIT_FUNC_PARAM );
}