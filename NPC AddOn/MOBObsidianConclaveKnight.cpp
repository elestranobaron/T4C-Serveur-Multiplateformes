#pragma hdrstop
#include "MOBObsidianConclaveKnight.h"

MOBObsidianConclaveKnight::MOBObsidianConclaveKnight()
{}

MOBObsidianConclaveKnight::~MOBObsidianConclaveKnight()
{}

extern NPCstructure::NPC MOBObsidianConclaveKnightNPC;

void MOBObsidianConclaveKnight::Create(){
   npc = MOBObsidianConclaveKnightNPC;
   SET_NPC_NAME( "[12752]Obsidian Conclave Knight" );
   npc.InitialPos.X = 0;  
   npc.InitialPos.Y = 0; 
   npc.InitialPos.world = 0;
}

void MOBObsidianConclaveKnight::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {

	IF (rnd.roll(dice(1,30)) == 1) 
		IF (rnd.roll(dice(1,2)) == 1) 
			SHOUT(INTL( 12413, "You're no match for me!")) 
		ELSE 
			SHOUT(INTL( 12422, "Ow! You'll pay for that in blood!"))
		ENDIF 
	ENDIF    
   }
SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}

void MOBObsidianConclaveKnight::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL ){      
	IF(CheckFlag(__FLAG_ADDON_SERAPH_ARMOR_QUEST) == 1)
		GiveFlag(__FLAG_ADDON_OBSIDIAN_KNIGHT_COUNTER, (CheckFlag(__FLAG_ADDON_OBSIDIAN_KNIGHT_COUNTER)+1)) 
		IF (CheckFlag(__FLAG_ADDON_OBSIDIAN_KNIGHT_COUNTER) >= 10) 
			IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_MORDRED) == 0) 
				SUMMON2("MOBMORDRED", 571,764,0)
				GiveFlag(__FLAG_ADDON_OBSIDIAN_KNIGHT_COUNTER,0)
			ENDIF 
		ENDIF 		 
	ENDIF 
	}
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}


