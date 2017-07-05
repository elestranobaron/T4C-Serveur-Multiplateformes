#pragma hdrstop
#include "ArenaMobXP425.H"

ArenaMobXP425::ArenaMobXP425()
{}

ArenaMobXP425::~ArenaMobXP425()
{}

extern NPCstructure::NPC ArenaMobXP425NPC;

void ArenaMobXP425::Create( void )
{
        npc = ( ArenaMobXP425NPC );
        SET_NPC_NAME( "[10960]Holydefender" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void ArenaMobXP425::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
  	CastSpellSelf(__SPELL_MOB_ARENA_MAJOR_REGENERATION_SPELL) 	
	SimpleMonster::OnPopup( UNIT_FUNC_PARAM );
}

void ArenaMobXP425::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	if( target != NULL )
	{
		GiveItem(__OBJ_COLOSSEUM_TOKEN)
		PRIVATE_SYSTEM_MESSAGE(INTL( 10682, "You receive a battle token for your efforts."))
	}
    CLOSE_HANDLER

	CastSpellSelf(__SPELL_MOB_ARENA_LEVEL_SPELL)

	SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}

void ArenaMobXP425::OnDestroy( UNIT_FUNC_PROTOTYPE )
{
	IF(CheckGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA) > 0)
		GiveGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA, CheckGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA) - 1)
	ENDIF

	SimpleMonster::OnDestroy( UNIT_FUNC_PARAM );
}