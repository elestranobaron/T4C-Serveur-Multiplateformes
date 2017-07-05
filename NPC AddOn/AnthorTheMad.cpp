#pragma hdrstop
#include "AnthorTheMad.H"

AnthorTheMad::AnthorTheMad()
{}

AnthorTheMad::~AnthorTheMad()
{}

extern NPCstructure::NPC AnthorTheMadNPC;

void AnthorTheMad::Create( void )
{
        npc = ( AnthorTheMadNPC );
        SET_NPC_NAME( "[12721]Anthor The Mad" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void AnthorTheMad::OnAttacked( UNIT_FUNC_PROTOTYPE )
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

void AnthorTheMad::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{
		IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 1)
			GiveItem(__OBJ_TOME_OF_ARCANE_KNOWLEDGE)
			GiveFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS, 2)
			PRIVATE_SYSTEM_MESSAGE(INTL( 11826, "You get the Tome of Arcane Knowledge."))
		ENDIF
	}

    CLOSE_HANDLER
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}