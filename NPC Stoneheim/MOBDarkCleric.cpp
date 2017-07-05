#pragma hdrstop
#include "MOBDarkCleric.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MOBDarkCleric::MOBDarkCleric()
{}

MOBDarkCleric::~MOBDarkCleric()
{}

extern NPCstructure::NPC MOBDarkClericNPC;

void MOBDarkCleric::Create( ){
   npc = MOBDarkClericNPC;
   SET_NPC_NAME( "[10880]Dark cleric");
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}

void MOBDarkCleric::OnDeath( UNIT_FUNC_PROTOTYPE )
{	  
	if( target != NULL )
	{
		SHOUT(INTL( 9164, "Death means nothing to me... NOTHING!!! arg.."))
	}

IF (CheckGlobalFlag(__FLAG_DARK_CLERIC_INSTANCE) > 0 ) 
	GiveGlobalFlag(__FLAG_DARK_CLERIC_INSTANCE, CheckGlobalFlag(__FLAG_DARK_CLERIC_INSTANCE)-1) 	
ENDIF 

NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}


void MOBDarkCleric::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
	
	GiveGlobalFlag(__FLAG_DARK_CLERIC_INSTANCE, CheckGlobalFlag(__FLAG_DARK_CLERIC_INSTANCE)+1);
	NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}


void MOBDarkCleric::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {               
      // Possibility of adding spells/summons here. 				
   }
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
} 

void MOBDarkCleric::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
		switch(rnd(0, 40))	 
			{		
			case 0: SHOUT(INTL( 9165, "Try as you might, our dark powers shall triumph and we will dominate the world.")); break;		
			case 1: SHOUT(INTL( 9166, "You cannot stop the uprise of the Dark One!")); break; 
			case 2: SHOUT(INTL( 9167, "Your doom is at hand.")); break; 
			case 3: SHOUT(INTL( 9168, "I mock your feeble abilities.")); break; 
			default: break;
			}
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}




