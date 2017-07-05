#pragma hdrstop
#include "Fenrir.H"

Fenrir::Fenrir()
{}

Fenrir::~Fenrir()
{}

extern NPCstructure::NPC JormungandNPC;

void Fenrir::Create( void )
{
        npc = ( JormungandNPC );
        SET_NPC_NAME( "[12736]Fenrir" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void Fenrir::OnAttacked( UNIT_FUNC_PROTOTYPE )
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

void Fenrir::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{
		GiveItem(__OBJ_FENRIR_SOULSTONE)
		PRIVATE_SYSTEM_MESSAGE(INTL( 12109, "You receive Fenrir's Soulstone."))
	}

    CLOSE_HANDLER
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}