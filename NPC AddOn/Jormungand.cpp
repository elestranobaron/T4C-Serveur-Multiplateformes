#pragma hdrstop
#include "Jormungand.H"

Jormungand::Jormungand()
{}

Jormungand::~Jormungand()
{}

extern NPCstructure::NPC JormungandNPC;

void Jormungand::Create( void )
{
        npc = ( JormungandNPC );
        SET_NPC_NAME( "[12745]Jormungand" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void Jormungand::OnAttacked( UNIT_FUNC_PROTOTYPE )
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

void Jormungand::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{
		GiveItem(__OBJ_JORMUNGAND_SOULSTONE)
		PRIVATE_SYSTEM_MESSAGE(INTL( 12357, "You receive Jormungand's Soulstone."))
	}

    CLOSE_HANDLER
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}