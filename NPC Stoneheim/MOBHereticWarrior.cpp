#pragma hdrstop
#include "MOBHereticWarrior.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MOBHereticWarrior::MOBHereticWarrior()
{}

MOBHereticWarrior::~MOBHereticWarrior()
{}
 
extern NPCstructure::NPC MOBHereticWarriorNPC;

void MOBHereticWarrior::Create( ){
   npc = MOBHereticWarriorNPC;
   SET_NPC_NAME( "[10885]Heretic warrior");
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}


void MOBHereticWarrior::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
	GiveGlobalFlag(__FLAG_HERETIC_WARRIOR_INSTANCE, CheckGlobalFlag(__FLAG_HERETIC_WARRIOR_INSTANCE)+1);
	NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}


void MOBHereticWarrior::OnDeath( UNIT_FUNC_PROTOTYPE )
{	  
	if( target != NULL ) 
	{
	SHOUT(INTL( 9319, "I'm bleeding to death! How can this be!?! Dark One, you LIED to me!!")) 
	}

IF (CheckGlobalFlag(__FLAG_HERETIC_WARRIOR_INSTANCE) > 0 ) 
	GiveGlobalFlag(__FLAG_HERETIC_WARRIOR_INSTANCE, CheckGlobalFlag(__FLAG_HERETIC_WARRIOR_INSTANCE)-1) 	
ENDIF 

NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void MOBHereticWarrior::OnAttack( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
   {
		IF (rnd.roll(dice(1,40)) == 1) 
			IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 			
				IF (rnd.roll(dice(1,2)) == 1) 
					SHOUT(INTL( 9320, "You do not stand a chance! Even if you defeat me, more will come to take my place!")) 
				ELSE
					SHOUT(INTL( 9321, "Yield now, and I shall grant you a merciful death. Fight on and I'll burn your soul!"))
				ENDIF 
			ELSEIF (CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
				IF (rnd.roll(dice(1,2)) == 1) 
					SHOUT(INTL( 9322, "Makrsh P'Tangh won't forgive your interference! There will be retribution for this!")) 
				ELSE
					SHOUT(INTL( 9323, "Have you no loyalty? You turn upon us, your kin? It almost makes me weep with pride!"))
				ENDIF 
			ELSE			
			IF (rnd.roll(dice(1,2)) == 1) 
					SHOUT(INTL( 9324, "You insignificant gnat! I will be done with you shortly and return to my business.")) 
				ELSE
					SHOUT(INTL( 9325, "Stand aside, weakling. You have no strength, no convictions! Prepare to die!"))
				ENDIF 
			ENDIF 
		ENDIF 	
   }
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void MOBHereticWarrior::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
		IF (rnd.roll(dice(1,40)) == 1) 
			IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 			
				IF (rnd.roll(dice(1,2)) == 1) 
					SHOUT(INTL( 9320, "You do not stand a chance! Even if you defeat me, more will come to take my place!")) 
				ELSE
					SHOUT(INTL( 9321, "Yield now, and I shall grant you a merciful death. Fight on and I'll burn your soul!"))
				ENDIF 
			ELSEIF (CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
				IF (rnd.roll(dice(1,2)) == 1) 
					SHOUT(INTL( 9322, "Makrsh P'Tangh won't forgive your interference! There will be retribution for this!")) 
				ELSE
					SHOUT(INTL( 9323, "Have you no loyalty? You turn upon us, your kin? It almost makes me weep with pride!"))
				ENDIF 
			ELSE			
			IF (rnd.roll(dice(1,2)) == 1) 
					SHOUT(INTL( 9324, "You insignificant gnat! I will be done with you shortly and return to my business.")) 
				ELSE
					SHOUT(INTL( 9325, "Stand aside, weakling. You have no strength, no convictions! Prepare to die!"))
				ENDIF 
			ENDIF 
		ENDIF 	
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

