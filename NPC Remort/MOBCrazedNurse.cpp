#pragma hdrstop
#include "MOBCrazedNurse.h"

MOBCrazedNurse::MOBCrazedNurse()
{}

MOBCrazedNurse::~MOBCrazedNurse()
{}

extern NPCstructure::NPC CrazedNurseNPC;

void MOBCrazedNurse::Create(){
   npc = CrazedNurseNPC;
   SET_NPC_NAME( "[10975]Crazed nurse" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void MOBCrazedNurse::OnAttackHit( UNIT_FUNC_PROTOTYPE )
{
   IF (rnd.roll(dice(1,50)) == 1) 
      SWITCH(rnd.roll(dice(1,4)))
			CASE(1)
				SHOUT(INTL( 10652, "Get me another one! Get me another GUINEA PIG!")) 
				IF ( target != NULL )
					PRIVATE_SYSTEM_MESSAGE(INTL( 10653, "The nurse pulls out a wicked-looking syringe."))
				ENDIF
			ENDCASE
			CASE(2)
				SHOUT(INTL( 10654, "Damn! Still alive?!?")) 
				IF ( target != NULL )
					PRIVATE_SYSTEM_MESSAGE(INTL( 10655, "The nurse checks your pulse.")) 
				ENDIF
			ENDCASE
			CASE(3)
				SHOUT(INTL( 10656, "I'm afraid we'll have to amputate you!")) 
			ENDCASE	
			CASE(4) 
				SHOUT(INTL( 10657, "Oooh, that's going to get infected. Let me help you out...")) 
			ENDCASE
		ENDSWITCH
   ENDIF 
SimpleMonster::OnAttackHit( UNIT_FUNC_PARAM );
}

void MOBCrazedNurse::OnHit( UNIT_FUNC_PROTOTYPE )
{
   IF (rnd.roll(dice(1,50)) == 1) 
		SWITCH(rnd.roll(dice(1,4)))
			CASE(1)
				SHOUT(INTL( 10652, "Get me another one! Get me another GUINEA PIG!")) 
				IF ( target != NULL )
					PRIVATE_SYSTEM_MESSAGE(INTL( 10653, "The nurse pulls out a wicked-looking syringe."))
				ENDIF
			ENDCASE
			CASE(2) 
				SHOUT(INTL( 10654, "Damn! Still alive?!?")) 
				IF ( target != NULL )
					PRIVATE_SYSTEM_MESSAGE(INTL( 10655, "The nurse checks your pulse.")) 
				ENDIF
			ENDCASE
			CASE(3)
				SHOUT(INTL( 10656, "I'm afraid we'll have to amputate you!")) 
			ENDCASE	
			CASE(4) 
				SHOUT(INTL( 10657, "Oooh, that's going to get infected. Let me help you out...")) 
			ENDCASE
		ENDSWITCH
   ENDIF
SimpleMonster::OnHit( UNIT_FUNC_PARAM );
}



