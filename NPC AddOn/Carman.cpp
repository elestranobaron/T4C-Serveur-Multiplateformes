#pragma hdrstop
#include "Carman.H"

Carman::Carman()
{}

Carman::~Carman()
{} 

extern NPCstructure::NPC CarmanNPC;

void Carman::Create( void )
{
        npc = ( CarmanNPC );
        SET_NPC_NAME( "[12726]Hel" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void Carman::OnPopup( UNIT_FUNC_PROTOTYPE )
{
	GiveGlobalFlag(__GLOBAL_FLAG_ADDON_CARMAN_PRESENT, 2)
	CastSpellSelf(__SPELL_MOB_FAST_REGEN)
NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}

void Carman::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
		switch(rnd(0, 10))
			{
			case 0: CastSpellSelf(__SPELL_MOB_FAST_REGEN); break;
			default: break;
			}
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Carman::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{
		GiveItem(__OBJ_HEL_SOULSTONE)
		PRIVATE_SYSTEM_MESSAGE(INTL( 11903, "You receive Hel's Soulstone."))
		CastSpellTarget(__SPELL_CARMAN_FLAG_SPELL)
	}
	GiveGlobalFlag(__GLOBAL_FLAG_ADDON_CARMAN_PRESENT, 0);

    CLOSE_HANDLER
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void Carman::OnDestroy( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
	}
NPCstructure::OnDestroy( UNIT_FUNC_PARAM );
}