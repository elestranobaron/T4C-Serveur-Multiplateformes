#pragma hdrstop
#include "MOBDelwobble.h"

MOBDelwobble::MOBDelwobble()
{}

MOBDelwobble::~MOBDelwobble()
{}

extern NPCstructure::NPC MOBDelwobbleNPC;

void MOBDelwobble::Create(){
   npc = MOBDelwobbleNPC;
   SET_NPC_NAME( "[2968]Delwobble the mad summoner" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
   npc.InitialPos.world = 0;
}

void MOBDelwobble::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {               
      SWITCH (rnd.roll(dice(1,30)))
         CASE (1){
				;int nRandomNumber = rnd.roll(dice(1,3)); 
            FOR(0, nRandomNumber) 				
                   SUMMON( "Acid Slime", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
            ENDFOR
         }ENDCASE
         CASE (2){
				;int nRandomNumber = rnd.roll(dice(1,4)); 
            FOR(0, nRandomNumber) 				                        
               SUMMON( "Death Stinger", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
            ENDFOR
         }ENDCASE
         OTHERWISE
      ENDSWITCH
   }
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void MOBDelwobble::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
      SWITCH (rnd.roll(dice(1,25))) 
         CASE (1){
				;int nRandomNumber = rnd.roll(dice(1,3)); 
            FOR(0, nRandomNumber) 				                        
	            SUMMON( "Acid Slime", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
            ENDFOR
         }ENDCASE
         CASE (2){
				;int nRandomNumber = rnd.roll(dice(1,4)); 
            FOR(0, nRandomNumber) 				                        
               SUMMON( "Death Stinger", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
            ENDFOR
         }ENDCASE
         OTHERWISE
      ENDSWITCH
   }
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void MOBDelwobble::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
/*
   __QUEST_DWARTHON_STONEFACE
   0: User isn't involved in the mini-quest. 
   1: User talked with Dwarthon and should be upgraded to 2. 
   2: User has already killed Delwobble but didn't talk to Dwarthon yet.
   5: User has killed Delwobble and talked to Dwarthon. 
*/
   IF (CheckFlag(__QUEST_DWARTHON_STONEFACE) == 1)
      GiveFlag(__QUEST_DWARTHON_STONEFACE, 2)
   ENDIF
	}

	NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}




