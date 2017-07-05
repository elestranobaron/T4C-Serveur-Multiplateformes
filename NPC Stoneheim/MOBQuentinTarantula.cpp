#pragma hdrstop
#include "MOBQuentinTarantula.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MOBQuentinTarantula::MOBQuentinTarantula()
{}

MOBQuentinTarantula::~MOBQuentinTarantula()
{}

extern NPCstructure::NPC MOBQuentinTarantulaNPC;

void MOBQuentinTarantula::Create( ){
   npc = MOBQuentinTarantulaNPC;
   SET_NPC_NAME( "[10892]Quentin Tarantula");
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}

void MOBQuentinTarantula::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {               
      
		IF (rnd.roll(dice(1,40)) == 1)
         SUMMON( "MOBGIANTBLACKWIDOW", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
		ENDIF      
				
   }
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}

void MOBQuentinTarantula::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
		IF (rnd.roll(dice(1,40)) == 1)
         SUMMON( "MOBGIANTBLACKWIDOW", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
		ENDIF      		
	}
SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}

void MOBQuentinTarantula::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
  	CastSpellSelf(__SPELL_MOB_REGENERATION_SPELL) 	
	
	SimpleMonster::OnPopup( UNIT_FUNC_PARAM );
}



