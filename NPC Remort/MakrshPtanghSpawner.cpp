#pragma hdrstop
#include "MakrshPtanghSpawner.H"

MakrshPtanghSpawner::MakrshPtanghSpawner()
{}

MakrshPtanghSpawner::~MakrshPtanghSpawner()
{}

extern NPCstructure::NPC MakrshPtanghSpawnerNPC;

void MakrshPtanghSpawner::Create( void )
{
        npc = ( MakrshPtanghSpawnerNPC );
        SET_NPC_NAME( "[11522]An undead guardian" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void MakrshPtanghSpawner::OnPopup( UNIT_FUNC_PROTOTYPE ){
		
	IF(CheckGlobalFlag(__GLOBAL_FLAG_MAKRSH_PTANGH_IS_FIGHTING) == 1)
		IF(CurrentRound < CheckGlobalFlag(__GLOBAL_FLAG_MAKRSH_PTANGH_DEAD_TIMER))
			GiveGlobalFlag(__GLOBAL_FLAG_MAKRSH_PTANGH_IS_FIGHTING, 2)
			SUMMON("MAKRSHPTANGH", 2265, 295)
		ELSEIF(CurrentRound >= CheckGlobalFlag(__GLOBAL_FLAG_MAKRSH_PTANGH_DEAD_TIMER) + 24000)
			GiveGlobalFlag(__GLOBAL_FLAG_MAKRSH_PTANGH_IS_FIGHTING, 2)
			SUMMON("MAKRSHPTANGH", 2265, 295)
		ENDIF
	ENDIF

SimpleMonster::OnPopup( UNIT_FUNC_PARAM );
}
