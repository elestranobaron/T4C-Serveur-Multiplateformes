#pragma hdrstop
#include "OlinHaadCommander.H"

OlinHaadCommander::OlinHaadCommander()
{}

OlinHaadCommander::~OlinHaadCommander()
{}

extern NPCstructure::NPC OlinHaadCommanderNPC;

void OlinHaadCommander::Create( void )
{
        npc = ( OlinHaadCommanderNPC );
        SET_NPC_NAME( "[12759]Commander Owain" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void OlinHaadCommander::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{
		IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 14)
			GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 15)
			TakeItem(__OBJ_OWAIN_LETTER_TO_NOMAD)
			GiveItem(__OBJ_SOLINAE_STAFF)
			PRIVATE_SYSTEM_MESSAGE(INTL( 12521, "You take Solinae's staff from Commander Owain's lifeless hands."))
		ENDIF
	}

    CLOSE_HANDLER
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}