#pragma hdrstop
#include "MOBRunawayPatient.h"

MOBRunawayPatient::MOBRunawayPatient()
{}

MOBRunawayPatient::~MOBRunawayPatient()
{}

extern NPCstructure::NPC MOBRunawayPatientNPC;

void MOBRunawayPatient::Create(){
   npc = MOBRunawayPatientNPC;
   SET_NPC_NAME( "[10981]Runaway patient" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void MOBRunawayPatient::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   IF (rnd.roll(dice(1,30)) == 1) 
      SWITCH(rnd.roll(dice(1,3))) 
			CASE(1) 
            SHOUT(INTL( 11339, "They're after me!"))   
			ENDCASE
			CASE(2)
            SHOUT(INTL( 11340, "NOOOOOOO!"))    
			ENDCASE
			CASE(3) 
            SHOUT(INTL( 11341, "Hey, that hurts damnit!")) 
			ENDCASE
		ENDSWITCH
   ENDIF
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void MOBRunawayPatient::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   IF (rnd.roll(dice(1,30)) == 1) 
      SWITCH(rnd.roll(dice(1,3))) 
			CASE(1) 
            SHOUT(INTL( 11339, "They're after me!"))
         ENDCASE
			CASE(2)
            SHOUT(INTL( 11340, "NOOOOOOO!"))      
			ENDCASE
			CASE(3) 
            SHOUT(INTL( 11341, "Hey, that hurts damnit!")) 
			ENDCASE
		ENDSWITCH
   ENDIF
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}




