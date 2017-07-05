#pragma hdrstop
#include "MonsterSpawner.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MonsterSpawner::MonsterSpawner()
{}

MonsterSpawner::~MonsterSpawner()
{}
 
extern NPCstructure::NPC MonsterSpawnerNPC;

void MonsterSpawner::Create( ){
   npc = MonsterSpawnerNPC;
   SET_NPC_NAME( "[10905]A phantasm");
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}

void MonsterSpawner::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
 
// MOBBlackProphet      x 2
// MOBDarkCleric        x 2 
// MOBHereticWarrior    x 2 
// MOBDarkNoble         x 2 
// MOBMadBerserkerDemon x 0 (summoned by the Black Prophet) 


CastSpellSelf(__SPELL_NPC_DELAYED_DEATH) 
SimpleMonster::OnPopup( UNIT_FUNC_PARAM );
}


