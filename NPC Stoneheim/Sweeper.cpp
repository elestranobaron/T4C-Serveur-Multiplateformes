#pragma hdrstop
#include "Sweeper.H"

Sweeper::Sweeper()
{}

Sweeper::~Sweeper()
{}

extern NPCstructure::NPC SweeperNPC;

void Sweeper::Create( void )
{
        npc = ( SweeperNPC );
        SET_NPC_NAME( "[10928]A Sweeper" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void Sweeper::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
	GiveGlobalFlag(__GLOBAL_FLAG_TOTAL_SWEEPERS_PRESENT, (CheckGlobalFlag(__GLOBAL_FLAG_TOTAL_SWEEPERS_PRESENT) + 1));
	NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}

void Sweeper::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	TFormat FORMAT;
	IF(CheckGlobalFlag(__GLOBAL_FLAG_TOTAL_SWEEPERS_PRESENT) > 0)
		GiveGlobalFlag(__GLOBAL_FLAG_TOTAL_SWEEPERS_PRESENT, CheckGlobalFlag(__GLOBAL_FLAG_TOTAL_SWEEPERS_PRESENT) - 1)
	ENDIF
	IF( target != NULL )
		GiveFlag(__FLAG_SWEEPERS_KILLED_BY_USER, CheckFlag(__FLAG_SWEEPERS_KILLED_BY_USER) + 1)
		GiveItem(__OBJ_ARCANE_SCROLL)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9089, "As you kill the Sweeper, an arcane scroll mysteriously appears in your hands."))
    ENDIF

    CLOSE_HANDLER
	NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void Sweeper::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
BREAK

Default
""
BREAK

EndTalk
}
