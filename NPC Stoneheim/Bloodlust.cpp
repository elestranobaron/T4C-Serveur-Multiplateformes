#pragma hdrstop
#include "Bloodlust.H"

Bloodlust::Bloodlust()
{}

Bloodlust::~Bloodlust()
{}

extern NPCstructure::NPC BloodlustNPC;

void Bloodlust::Create( void )
{
        npc = ( BloodlustNPC );
        SET_NPC_NAME( "[10829]Bloodlust" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void Bloodlust::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{
		GiveFlag(__FLAG_USER_HAS_SLAIN_BLOODLUST, 1)
		IF(rnd.roll(dice(1, 4)) <= 3)
			GiveItem(__OBJ_BLOODSTONE_RING)
			PRIVATE_SYSTEM_MESSAGE(INTL( 8833, "You search the corpse and discover a curious ring inset with a polished bloodstone."))
			IF(rnd.roll(dice(1, 4)) == 1)
				GiveItem(__OBJ_ESSENCE_OF_BLOODLUST)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8834, "Upon further investigation of the corpse, you discover a small glowing bloodstone."))
			ENDIF
		ELSE
			IF(rnd.roll(dice(1, 4)) == 1)
				GiveItem(__OBJ_ESSENCE_OF_BLOODLUST)
				PRIVATE_SYSTEM_MESSAGE(INTL( 8835, "You search the corpse and discover a small glowing bloodstone."))
			ENDIF
		ENDIF
	}

    CLOSE_HANDLER
	NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void Bloodlust::OnDestroy( UNIT_FUNC_PROTOTYPE )
{
	GiveGlobalFlag(__GLOBAL_FLAG_BLOODLUST_IS_ON_THE_MAP, 0);
    NPCstructure::OnDestroy( UNIT_FUNC_PARAM );
}
