#pragma hdrstop
#include "MOBDerangedOrderly.h"

MOBDerangedOrderly::MOBDerangedOrderly()
{}

MOBDerangedOrderly::~MOBDerangedOrderly()
{}

extern NPCstructure::NPC DerangedOrderlyNPC;

void MOBDerangedOrderly::Create(){
   npc = DerangedOrderlyNPC;
   SET_NPC_NAME( "[10976]Deranged orderly" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void MOBDerangedOrderly::OnAttack( UNIT_FUNC_PROTOTYPE )
{ 
	IF (rnd.roll(dice(1,50)) == 1) 
		SWITCH(rnd.roll(dice(1,2)))
			CASE(1)
				SHOUT(INTL( 10644, "You're making a mess here! Stop this!")) 
			ENDCASE
			CASE(2)
				SHOUT(INTL( 10645, "Aww, all this blood, I'm going to have to change the sheets again.")) 						
			ENDCASE			
		ENDSWITCH
   ENDIF
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}

void MOBDerangedOrderly::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
	IF (rnd.roll(dice(1,50)) == 1) 
		SWITCH(rnd.roll(dice(1,2)))
			CASE(1)
				SHOUT(INTL( 10644, "You're making a mess here! Stop this!")) 
			ENDCASE
			CASE(2)
				SHOUT(INTL( 10645, "Aww, all this blood, I'm going to have to change the sheets again.")) 						
			ENDCASE			
		ENDSWITCH
   ENDIF
SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}



