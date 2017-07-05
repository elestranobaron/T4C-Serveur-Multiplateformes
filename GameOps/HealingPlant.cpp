#pragma hdrstop
#include "HealingPlant.h"

HealingPlant::HealingPlant()
{}

HealingPlant::~HealingPlant()
{}

extern NPCstructure::NPC HealingPlantNPC;

void HealingPlant::Create( ){
    npc = HealingPlantNPC;
    SET_NPC_NAME(  "[7398]A mysterious plant" );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
    npc.InitialPos.world = 0;
}

void HealingPlant::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

// The healing plant does not require any coding so sue me. :)
                                                              
