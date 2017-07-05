#pragma hdrstop
#include "MOBLoon.h"

MOBLoon::MOBLoon()
{}

MOBLoon::~MOBLoon()
{}

extern NPCstructure::NPC LoonNPC;

void MOBLoon::Create(){
   npc = LoonNPC;
   SET_NPC_NAME( "[10977]Loon" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void MOBLoon::OnAttack( UNIT_FUNC_PROTOTYPE )
{
 IF (rnd.roll(dice(1,50)) == 1) 
		SWITCH(rnd.roll(dice(1,3)))
			CASE(1)
				SHOUT(INTL( 10678, "This is going to hurt me more than it hurts you.")) 
			ENDCASE
			CASE(2)
				SHOUT(INTL( 10679, "Have you seen a rabbit carrying a watch?")) 						
			ENDCASE
			CASE(3)
				SHOUT(INTL( 10680, "I'm late, I'm so late...")) 
			ENDCASE				
		ENDSWITCH
   ENDIF
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}

void MOBLoon::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
	IF (rnd.roll(dice(1,50)) == 1) 
		SWITCH(rnd.roll(dice(1,3)))
			CASE(1)
				SHOUT(INTL( 10678, "This is going to hurt me more than it hurts you.")) 
			ENDCASE
			CASE(2)
				SHOUT(INTL( 10679, "Have you seen a rabbit carrying a watch?")) 						
			ENDCASE
			CASE(3)
				SHOUT(INTL( 10680, "I'm late, I'm so late...")) 
			ENDCASE				
		ENDSWITCH
   ENDIF
SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}

void MOBLoon::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
  	CastSpellSelf(__SPELL_MOB_INVISIBILITY_SPELL) 	
	
	SimpleMonster::OnPopup( UNIT_FUNC_PARAM );
}




