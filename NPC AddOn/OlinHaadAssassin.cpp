#pragma hdrstop
#include "OlinHaadAssassin.H"

OlinHaadAssassin::OlinHaadAssassin()
{}

OlinHaadAssassin::~OlinHaadAssassin()
{}

extern NPCstructure::NPC OlinHaadAssassinNPC;

void OlinHaadAssassin::Create( void )
{
        npc = ( OlinHaadAssassinNPC );
        SET_NPC_NAME( "[76]Assassin" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void OlinHaadAssassin::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
	
	GiveGlobalFlag(__GLOBAL_FLAG_ADDON_NUMBER_OF_OLIN_HAAD_ASSASSINS_PRESENT, CheckGlobalFlag(__GLOBAL_FLAG_ADDON_NUMBER_OF_OLIN_HAAD_ASSASSINS_PRESENT) + 1);
NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}

void OlinHaadAssassin::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
		switch(rnd(0, 10))	 
			{		
			case 0: SHOUT(INTL( 12520, "Did you really think Olin Haad would let a rat like you live very long, Efnisien?")); break;		
			default: break;
			}
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void OlinHaadAssassin::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{
		CastSpellTarget(__SPELL_OLIN_HAAD_ASSASSIN_FLAG_SPELL)
	}

    CLOSE_HANDLER
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void OlinHaadAssassin::OnDestroy( UNIT_FUNC_PROTOTYPE )
{
	IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_NUMBER_OF_OLIN_HAAD_ASSASSINS_PRESENT) > 0)
		GiveGlobalFlag(__GLOBAL_FLAG_ADDON_NUMBER_OF_OLIN_HAAD_ASSASSINS_PRESENT, CheckGlobalFlag(__GLOBAL_FLAG_ADDON_NUMBER_OF_OLIN_HAAD_ASSASSINS_PRESENT) - 1)
	ENDIF

NPCstructure::OnDestroy( UNIT_FUNC_PARAM );
}
