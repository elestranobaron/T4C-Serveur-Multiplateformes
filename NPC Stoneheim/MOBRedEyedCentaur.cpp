#pragma hdrstop
#include "MOBRedEyedCentaur.h"

MOBRedEyedCentaur::MOBRedEyedCentaur()
{}

MOBRedEyedCentaur::~MOBRedEyedCentaur()
{}

extern NPCstructure::NPC MOBRedEyedCentaurNPC;

void MOBRedEyedCentaur::Create(){
   npc = MOBRedEyedCentaurNPC;
   SET_NPC_NAME( "[10893]Red-Eyed centaur" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}


void MOBRedEyedCentaur::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
	    switch(rnd(0, 4)){
        case 0: SHOUT(INTL( 8695, "You'll pay for this!")); break;
        case 1: SHOUT(INTL( 5178, "Argh!")); break;
        case 2:break;
        case 3:break;
        case 4:break;

        }
   
        SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
   }
}

void MOBRedEyedCentaur::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
   TFormat FORMAT;
   if( target != NULL )
   {		
		// Check to ensure that the user is indeed after the mind-control talismans. 
		IF( CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 8) // Sent on behalf of Aedenas 
			GiveItem(__OBJ_MIND_CONTROL_TALISMAN) // NoDrop, NoJunk, NoGive
			PRIVATE_SYSTEM_MESSAGE(INTL( 8696, "Upon inspection of the unconscious centaur's body, you notice a "
			"mind-control talisman tied around his neck.")) 
			PRIVATE_SYSTEM_MESSAGE(INTL( 8697, "You remove the talisman from the centaur's neck, freeing him "
			"of Zion Thunderheart's hypnotic influence!"))			
			IF (CheckFlag( __MIND_CONTROL_TALISMAN_COUNTER) < 12) 
				IF (CheckItem(__OBJ_MIND_CONTROL_TALISMAN) < 12) // If the user has less than twelve talismans.
		 			;int nExpReward = 25000; 	
		 			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 8698, "You have been awarded %u additional experience points!"),nExpReward) )
		 			GiveXP(nExpReward)
					GiveFlag(__MIND_CONTROL_TALISMAN_COUNTER, CheckFlag(__MIND_CONTROL_TALISMAN_COUNTER) + 1) 
				ENDIF
			ENDIF 
		ENDIF
   }
   CLOSE_HANDLER
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}
