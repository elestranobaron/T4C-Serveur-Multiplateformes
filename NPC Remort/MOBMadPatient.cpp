#pragma hdrstop
#include "MOBMadPatient.h"

MOBMadPatient::MOBMadPatient()
{}

MOBMadPatient::~MOBMadPatient()
{}

extern NPCstructure::NPC MadPatientNPC;

void MOBMadPatient::Create(){
   npc = MadPatientNPC;
   SET_NPC_NAME( "[10979]Mad patient" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void MOBMadPatient::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   IF (rnd.roll(dice(1,50)) == 1) 
      SWITCH(rnd.roll(dice(1,3))) 
			CASE(1) 
				SHOUT(INTL( 10638, "Pain! Gimme more pain!"))
			ENDCASE
			CASE(2)
				SHOUT(INTL( 10639, "Oooh, hurts so gooood..."))		
			ENDCASE
			CASE(3) 
				SHOUT(INTL( 10640, "I'm feeling at odds with myself. Is it time for my medication yet?")) 
			ENDCASE
		ENDSWITCH
   ENDIF
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}

void MOBMadPatient::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   IF (rnd.roll(dice(1,50)) == 1) 
      SWITCH(rnd.roll(dice(1,3))) 
			CASE(1) 
				SHOUT(INTL( 10638, "Pain! Gimme more pain!"))
			ENDCASE
			CASE(2)
				SHOUT(INTL( 10639, "Oooh, hurts so gooood..."))		
			ENDCASE
			CASE(3) 
				SHOUT(INTL( 10640, "I'm feeling at odds with myself. Is it time for my medication yet?")) 
			ENDCASE
		ENDSWITCH
   ENDIF
SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}



