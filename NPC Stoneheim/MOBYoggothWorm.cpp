#pragma hdrstop
#include "MOBYoggothWorm.h"

MOBYoggothWorm::MOBYoggothWorm()
{}

MOBYoggothWorm::~MOBYoggothWorm()
{}

extern NPCstructure::NPC MOBYoggothWormNPC;

void MOBYoggothWorm::Create(){
   npc = MOBYoggothWormNPC;
   SET_NPC_NAME( "[10896]Yoggoth worm" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
   npc.InitialPos.world = 0;
}						   

void MOBYoggothWorm::OnAttackHit( UNIT_FUNC_PROTOTYPE )
{  	
	if( target != NULL )
   {                     
		IF (rnd.roll(dice(1,100)) == 1)
			CastSpellTarget(__SPELL_NPC_CANTRIP_RED_WIPE)
			CastSpellSelf(__SPELL_MOB_REGENERATION_SPELL)						
			SWITCH(rnd.roll(dice(1,14))) 
				CASE(1) 
					TELEPORT(2265,835,2)
				ENDCASE
				CASE(2) 
					TELEPORT(2176,854,2)
				ENDCASE
				CASE(3) 
					TELEPORT(2266,875,2)
				ENDCASE
				CASE(4)
					TELEPORT(2313,901,2)
				ENDCASE
				CASE(5) 
					TELEPORT(2068,919,2)
				ENDCASE
				CASE(6) 
					TELEPORT(2138,925,2)
				ENDCASE
				CASE(7)
					TELEPORT(2227,952,2)
				ENDCASE
				CASE(8) 
					TELEPORT(2082,971,2)
				ENDCASE
				CASE(9) 
					TELEPORT(2025,974,2)
				ENDCASE
				CASE(10)
					TELEPORT(2249,1007,2)
				ENDCASE
				CASE(11) 
					TELEPORT(2212,1054,2)
				ENDCASE
				CASE(12) 
					TELEPORT(2250,1072,2)
				ENDCASE
				CASE(13) 
					TELEPORT(2114,1092,2)
				ENDCASE
				CASE(14) 
					TELEPORT(2353,1143,2)
				ENDCASE
         ENDSWITCH 
			PRIVATE_SYSTEM_MESSAGE(INTL( 9210, "The ground suddenly opens beneath you and swallows you. You reappear elsewhere...")) 
		ENDIF      				
   }
SimpleMonster::OnAttackHit( UNIT_FUNC_PARAM );
}



