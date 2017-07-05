#pragma hdrstop
#include "MOBGehennaReaver.h"

MOBGehennaReaver::MOBGehennaReaver()
{}

MOBGehennaReaver::~MOBGehennaReaver()
{}

extern NPCstructure::NPC MOBGehennaReaverNPC;

void MOBGehennaReaver::Create(){
   npc = MOBGehennaReaverNPC;
   SET_NPC_NAME( "[10883]Gehenna Reaver" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void MOBGehennaReaver::OnDeath( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   { 
		SHOUT(INTL( 9317, "ARGHHH! Others will avenge me for this!!!"))
   }
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}

void MOBGehennaReaver::OnAttackHit( UNIT_FUNC_PROTOTYPE )
{   
  if( target != NULL )
   {
		switch(rnd(0, 30))	 
			{		
			case 0: SHOUT(INTL( 9318, "I will cut you to pieces!")); break;					
			case 1: SHOUT(INTL( 9168, "I mock your feeble abilities.")); break; 
			default: break;
			}
	}   
SimpleMonster::OnAttackHit( UNIT_FUNC_PARAM );
}


