#pragma hdrstop
#include "MOBShriekerRodent.h"

MOBShriekerRodent::MOBShriekerRodent()
{
}

MOBShriekerRodent::~MOBShriekerRodent()
{}

extern NPCstructure::NPC MOBShriekerRodentNPC;

void MOBShriekerRodent::Create(){
   npc = MOBShriekerRodentNPC;
   SET_NPC_NAME( "[10895]Shrieker rodent" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
   npc.InitialPos.world = 0;
}						   

void MOBShriekerRodent::OnAttacked( UNIT_FUNC_PROTOTYPE )
{ 
	SWITCH (rnd.roll(dice(1,30))) 
		CASE (1)
			SUMMON( "MOBPURIFIER", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
		ENDCASE
		CASE (2)
			SUMMON( "MOBGAUZECORPSE", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
		ENDCASE
		CASE (3)
			SUMMON( "MOBCELESTIALCOBRA", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
		ENDCASE
		CASE (4)
			IF( rnd.roll( dice( 1, 100 ) ) > 90 )						
				SUMMON( "MOBSHRIEKERRODENT", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))					
			ELSE
				SUMMON( "MOBDARKFIEND", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))			
			ENDIF
		ENDCASE
      OTHERWISE
	ENDSWITCH

SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}





