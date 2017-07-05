#pragma hdrstop
#include "OlinHaadEliteGuard.H"

OlinHaadEliteGuard::OlinHaadEliteGuard()
{}

OlinHaadEliteGuard::~OlinHaadEliteGuard()
{}

extern NPCstructure::NPC OlinHaadEliteGuardNPC;

void OlinHaadEliteGuard::Create( void )
{
        npc = ( OlinHaadEliteGuardNPC );
        SET_NPC_NAME( "[12760]Olin Haad elite guard" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void OlinHaadEliteGuard::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
		
		switch(rnd(0, 8))	 
			{		
			case 0: CastSpellTarget(__SPELL_FIRST_POWER_ACTIVATED); break;		
			default: break;
			}
		switch(rnd(0, 10))	 
			{		
			case 0: CastSpellSelf(__SPELL_MOB_MAX_REGEN); break;		
			default: break;
			}
	}
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}

void OlinHaadEliteGuard::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{
		IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 4)
			GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 4)
			CastSpellTarget(__SPELL_WRATH_OF_THE_ANCIENTS)
			PRIVATE_SYSTEM_MESSAGE(INTL( 12522, "You rock back as a surge of energy rips through your body and consumes the guard."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 12523, "As the guard's body hits the floor, you hear Olin Haad's voice from above, 'Enough!'."))
			CastSpellTarget(__SPELL_TELEPORT_TO_OLIN_HAAD_1)
			SHOUT(INTL( 12524, "Wh.. what are you? Nooooooo!"))
		ENDIF
	}

    CLOSE_HANDLER
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}