#pragma hdrstop
#include "UrikThief.H"

UrikThief::UrikThief()
{}

UrikThief::~UrikThief()
{}

extern NPCstructure::NPC UrikThiefNPC;

void UrikThief::Create( void )
{
        npc = ( UrikThiefNPC );
        SET_NPC_NAME( "[12779]Thief" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void UrikThief::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
	
	GiveGlobalFlag(__GLOBAL_FLAG_ADDON_NUMBER_OF_URIK_THIEVES_PRESENT, CheckGlobalFlag(__GLOBAL_FLAG_ADDON_NUMBER_OF_URIK_THIEVES_PRESENT) + 1);
NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}

void UrikThief::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{
		CastSpellTarget(__SPELL_URIK_THIEF_FLAG_SPELL)
	}

    CLOSE_HANDLER
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}
 
void UrikThief::OnDestroy( UNIT_FUNC_PROTOTYPE )
{
	IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_NUMBER_OF_URIK_THIEVES_PRESENT) > 0)
		GiveGlobalFlag(__GLOBAL_FLAG_ADDON_NUMBER_OF_URIK_THIEVES_PRESENT, CheckGlobalFlag(__GLOBAL_FLAG_ADDON_NUMBER_OF_URIK_THIEVES_PRESENT) - 1)
	ENDIF

NPCstructure::OnDestroy( UNIT_FUNC_PARAM );
}
