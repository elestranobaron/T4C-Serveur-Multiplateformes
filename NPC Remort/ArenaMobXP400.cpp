#pragma hdrstop
#include "ArenaMobXP400.H"

ArenaMobXP400::ArenaMobXP400()
{}

ArenaMobXP400::~ArenaMobXP400()
{}

extern NPCstructure::NPC ArenaMobXP400NPC;

void ArenaMobXP400::Create( void )
{
        npc = ( ArenaMobXP400NPC );
        SET_NPC_NAME( "[10959]Shadowterror" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void ArenaMobXP400::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
  	CastSpellSelf(__SPELL_MOB_ARENA_MAJOR_REGENERATION_SPELL) 	
	SimpleMonster::OnPopup( UNIT_FUNC_PARAM );
}

void ArenaMobXP400::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	if( target != NULL )
	{
		IF(rnd.roll(dice(1, 100)) <= (390 - (USER_LEVEL)))
			GiveItem(__OBJ_COLOSSEUM_TOKEN)
			PRIVATE_SYSTEM_MESSAGE(INTL( 10682, "You receive a battle token for your efforts."))
		ENDIF
	}
    CLOSE_HANDLER

	CastSpellSelf(__SPELL_MOB_ARENA_LEVEL_SPELL)

	SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}

void ArenaMobXP400::OnDestroy( UNIT_FUNC_PROTOTYPE )
{
	IF(CheckGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA) > 0)
		GiveGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA, CheckGlobalFlag(__GLOBAL_FLAG_NUMBER_MONSTERS_IN_ARENA) - 1)
	ENDIF

	SimpleMonster::OnDestroy( UNIT_FUNC_PARAM );
}