#pragma hdrstop
#include "MOBBlackProphet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MOBBlackProphet::MOBBlackProphet()
{}

MOBBlackProphet::~MOBBlackProphet()
{} 

extern NPCstructure::NPC MOBBlackProphetNPC;

void MOBBlackProphet::Create( ){
   npc = MOBBlackProphetNPC;
   SET_NPC_NAME( "[10878]Black prophet");
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0; 
}

void MOBBlackProphet::OnDeath( UNIT_FUNC_PROTOTYPE )
{	  
	if( target != NULL )
	{
		IF (rnd.roll(dice(1,10)) == 1) 
			SHOUT(INTL( 9328, "With my last dying breath, I summon a demon from Beyond to avenge my death!")) 			
			SUMMON("MOBMADBERSERKERDEMON", FROM_NPC(-1,X), FROM_NPC(-1,Y))							
		ENDIF 
	}

IF (CheckGlobalFlag(__FLAG_BLACK_PROPHET_INSTANCE) > 0 ) 
	GiveGlobalFlag(__FLAG_BLACK_PROPHET_INSTANCE, CheckGlobalFlag(__FLAG_BLACK_PROPHET_INSTANCE)-1) 	
ENDIF 

NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void MOBBlackProphet::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
   GiveGlobalFlag(__FLAG_BLACK_PROPHET_INSTANCE, CheckGlobalFlag(__FLAG_BLACK_PROPHET_INSTANCE)+1);
   NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}


void MOBBlackProphet::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {               
		IF (rnd.roll(dice(1,40)) == 1) 
			IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 			
				IF (rnd.roll(dice(1,2)) == 1) 
					SHOUT(INTL( 9329, "It was a mistake for you to come here, lightbringer! That mistake will be your last!")) 
				ELSE
					SHOUT(INTL( 9330, "The very sight of you sickens me -- and your death is just the cure I need!"))
				ENDIF 
			ELSEIF (CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
				IF (rnd.roll(dice(1,2)) == 1) 
					SHOUT(INTL( 9331, "How DARE you oppose the one true lord of Darkness?!? Your insolence will cost you!")) 
				ELSE
					SHOUT(INTL( 9332, "Follower of Ogrimar, repent thyself and join us or die by my hand!"))
				ENDIF 
			ELSE
				IF (rnd.roll(dice(1,2)) == 1) 
					SHOUT(INTL( 9333, "Foolish mortal! There is still time to join us! Stop this nonsense and be one of us!")) 
				ELSE
					SHOUT(INTL( 9334, "Such impudence! You are meddling with forces far beyond your comprehension, weakling!"))
				ENDIF 
			ENDIF 
		ENDIF 
   }
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void MOBBlackProphet::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {		
		IF (rnd.roll(dice(1,40)) == 1) 
			IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1) 			
				IF (rnd.roll(dice(1,2)) == 1) 
					SHOUT(INTL( 9329, "It was a mistake for you to come here, lightbringer! That mistake will be your last!")) 
				ELSE
					SHOUT(INTL( 9330, "The very sight of you sickens me -- and your death is just the cure I need!"))
				ENDIF 
			ELSEIF (CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
				IF (rnd.roll(dice(1,2)) == 1) 
					SHOUT(INTL( 9331, "How DARE you oppose the one true lord of Darkness?!? Your insolence will cost you!")) 
				ELSE
					SHOUT(INTL( 9332, "Follower of Ogrimar, repent thyself and join us or die by my hand!"))
				ENDIF 
			ELSE
				IF (rnd.roll(dice(1,2)) == 1) 
					SHOUT(INTL( 9333, "Foolish mortal! There is still time to join us! Stop this nonsense and be one of us!")) 
				ELSE
					SHOUT(INTL( 9334, "Such impudence! You are meddling with forces far beyond your comprehension, weakling!"))
				ENDIF 
			ENDIF 
		ENDIF 
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

