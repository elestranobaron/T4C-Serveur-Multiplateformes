#pragma hdrstop
#include "MOBDarkNoble.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MOBDarkNoble::MOBDarkNoble()
{}

MOBDarkNoble::~MOBDarkNoble()
{}

extern NPCstructure::NPC MOBDarkNobleNPC;

void MOBDarkNoble::Create( ){
   npc = MOBDarkNobleNPC;
   SET_NPC_NAME( "[10881]Dark noble");
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}


void MOBDarkNoble::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
   GiveGlobalFlag(__FLAG_DARK_NOBLE_INSTANCE, CheckGlobalFlag(__FLAG_DARK_NOBLE_INSTANCE)+1);
   NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}


void MOBDarkNoble::OnDeath( UNIT_FUNC_PROTOTYPE )
{	  
	if( target != NULL )
	{		
	}

IF (CheckGlobalFlag(__FLAG_DARK_NOBLE_INSTANCE) > 0 ) 
	GiveGlobalFlag(__FLAG_DARK_NOBLE_INSTANCE, CheckGlobalFlag(__FLAG_DARK_NOBLE_INSTANCE)-1) 	
ENDIF 


NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void MOBDarkNoble::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {               
		IF (rnd.roll(dice(1,40)) == 1) 
			SWITCH(rnd.roll(dice(1,5))) 
				CASE(1)
					IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
						SHOUT(INTL( 9344, "Repent your ways, or darkness will consume you just as it did me."))	
					ELSE
						SHOUT(INTL( 9345, "It will be an honor to die by your hand."))				
					ENDIF 
				ENDCASE
				CASE(2)
					SHOUT(INTL( 9346, "You are a worthy opponent, but you must die, now."))
				ENDCASE
				CASE(3) 
					SHOUT(INTL( 9347, "Why waste your puny life, you know I cannot lose."))
				ENDCASE
				CASE(4)
					SHOUT(INTL( 9348, "Give up and flee before I *really* start hurting you.")) 
				ENDCASE
				CASE(5)
					SHOUT(INTL( 9349, "Your death shall be dealt swiftly.")) 
				ENDCASE
			ENDSWITCH 
		ENDIF 		
   }
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void MOBDarkNoble::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
		IF (rnd.roll(dice(1,40)) == 1) 
			SWITCH(rnd.roll(dice(1,5))) 
				CASE(1)
					IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
						SHOUT(INTL( 9344, "Repent your ways, or darkness will consume you just as it did me."))	
					ELSE
						SHOUT(INTL( 9345, "It will be an honor to die by your hand."))				
					ENDIF 
				ENDCASE
				CASE(2)
					SHOUT(INTL( 9346, "You are a worthy opponent, but you must die, now."))
				ENDCASE
				CASE(3) 
					SHOUT(INTL( 9347, "Why waste your puny life, you know I cannot lose."))
				ENDCASE
				CASE(4)
					SHOUT(INTL( 9348, "Give up and flee before I *really* start hurting you.")) 
				ENDCASE
				CASE(5)
					SHOUT(INTL( 9349, "Your death shall be dealt swiftly.")) 
				ENDCASE
			ENDSWITCH 
		ENDIF 		
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}
 



