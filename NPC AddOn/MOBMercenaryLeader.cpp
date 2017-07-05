#pragma hdrstop
#include "MOBMercenaryLeader.h"

MOBMercenaryLeader::MOBMercenaryLeader()
{}

MOBMercenaryLeader::~MOBMercenaryLeader()
{}

extern NPCstructure::NPC MOBMercenaryLeaderNPC;

void MOBMercenaryLeader::Create(){
   npc = MOBMercenaryLeaderNPC;
   SET_NPC_NAME( "[12749]Mercenary Leader" );
   npc.InitialPos.X = 0; // Monster is spawned through quest at 2680,895,0
   npc.InitialPos.Y = 0; 
   npc.InitialPos.world = 0;
}

void MOBMercenaryLeader::OnPopup( UNIT_FUNC_PROTOTYPE )
{											 	
	GiveGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LEADER_SPAWNED, 1);
NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}

void MOBMercenaryLeader::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
	IF (rnd.roll(dice(1,30)) == 1) 
		IF (rnd.roll(dice(1,2)) == 1) 
			SHOUT(INTL( 12413, "You're no match for me!")) 
		ELSE 
      SHOUT(INTL( 12414, "Ow! You'll pay in blood!"))
		ENDIF 
	ENDIF    
   }
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void MOBMercenaryLeader::OnDeath( UNIT_FUNC_PROTOTYPE )
{
  INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{

		SHOUT(INTL( 12415, "AAARGH! Olin Haad will hear of this...urgh!")) 
		CastSpellTarget(__SPELL_MERCENARY_LEADER_DEFEAT_FLAG_SPELL)
	}

    CLOSE_HANDLER
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}


void MOBMercenaryLeader::OnDestroy( UNIT_FUNC_PROTOTYPE )
{
	GiveGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LEADER_SPAWNED, 0);
NPCstructure::OnDestroy( UNIT_FUNC_PARAM );
}



