#pragma hdrstop
#include "HarvesterOfLife.H"

HarvesterOfLife::HarvesterOfLife()
{}

HarvesterOfLife::~HarvesterOfLife()
{}

extern NPCstructure::NPC HarvesterOfLifeNPC;

void HarvesterOfLife::Create( void )
{
        npc = ( HarvesterOfLifeNPC );
        SET_NPC_NAME( "[12743]Harvester Of Life" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void HarvesterOfLife::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{
		IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 4)
			GiveItem(__OBJ_CRYSTAL_OF_PROVIDENCE)
			GiveFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS, 5)
			PRIVATE_SYSTEM_MESSAGE(INTL( 12274, "You get the Crystal of Providence."))
		ENDIF
	}

    CLOSE_HANDLER
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}