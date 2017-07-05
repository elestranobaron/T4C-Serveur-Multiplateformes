#pragma hdrstop
#include "MOBRavingLunatic.h"

MOBRavingLunatic::MOBRavingLunatic()
{}

MOBRavingLunatic::~MOBRavingLunatic()
{} 

extern NPCstructure::NPC RavingLunaticNPC;

void MOBRavingLunatic::Create(){
   npc = RavingLunaticNPC;
   SET_NPC_NAME( "[10980]Raving lunatic" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void MOBRavingLunatic::OnAttack( UNIT_FUNC_PROTOTYPE )
{
	IF (rnd.roll(dice(1,50)) == 1) 
		SWITCH(rnd.roll(dice(1,3)))
			CASE(1)
				SHOUT(INTL( 10641, "You see them? Tell me you see them, too!!")) 
			ENDCASE
			CASE(2)
				SHOUT(INTL( 10642, "What's with the little stars?!")) 						
			ENDCASE
			CASE(3)
				SHOUT(INTL( 10643, "You're against me... they're ALL against me!")) 
			ENDCASE				
		ENDSWITCH
   ENDIF

SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}

void MOBRavingLunatic::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
	IF (rnd.roll(dice(1,50)) == 1) 
		SWITCH(rnd.roll(dice(1,3)))
			CASE(1)
				SHOUT(INTL( 10641, "You see them? Tell me you see them, too!!")) 
			ENDCASE
			CASE(2)
				SHOUT(INTL( 10642, "What's with the little stars?!")) 						
			ENDCASE
			CASE(3)
				SHOUT(INTL( 10643, "You're against me... they're ALL against me!")) 
			ENDCASE				
		ENDSWITCH
   ENDIF

SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}



