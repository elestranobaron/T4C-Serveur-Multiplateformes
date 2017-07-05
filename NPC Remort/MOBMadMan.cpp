#pragma hdrstop
#include "MOBMadMan.h"

MOBMadMan::MOBMadMan()
{}

MOBMadMan::~MOBMadMan()
{}

extern NPCstructure::NPC MadManNPC;

void MOBMadMan::Create(){
   npc = MadManNPC;
   SET_NPC_NAME( "[10978]Madman" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void MOBMadMan::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   IF (rnd.roll(dice(1,50)) == 1) 
		SWITCH(rnd.roll(dice(1,3)))
			CASE(1)
				SHOUT(INTL( 10646, "I'm the last thing you'll ever see... 'till we meet again.")) 
			ENDCASE
			CASE(2)
				SHOUT(INTL( 10647, "Do you have the time?")) 						
			ENDCASE
			CASE(3)
				SHOUT(INTL( 10648, "HEY! It's not because you're paranoid that they're NOT out to get you!")) 
			ENDCASE				
		ENDSWITCH
   ENDIF

SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}

void MOBMadMan::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
IF (rnd.roll(dice(1,50)) == 1) 
		SWITCH(rnd.roll(dice(1,3)))
			CASE(1)
				SHOUT(INTL( 10646, "I'm the last thing you'll ever see... 'till we meet again.")) 
			ENDCASE
			CASE(2)
				SHOUT(INTL( 10647, "Do you have the time?")) 						
			ENDCASE
			CASE(3)
				SHOUT(INTL( 10648, "HEY! It's not because you're paranoid that they're NOT out to get you!")) 
			ENDCASE				
		ENDSWITCH
   ENDIF
SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}



