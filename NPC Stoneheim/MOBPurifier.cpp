#pragma hdrstop
#include "MOBPurifier.h"

MOBPurifier::MOBPurifier()
{}

MOBPurifier::~MOBPurifier()
{}

extern NPCstructure::NPC MOBPurifierNPC;

void MOBPurifier::Create(){
   npc = MOBPurifierNPC;
   SET_NPC_NAME( "[10891]Purifier" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
   npc.InitialPos.world = 0;
}						   

void MOBPurifier::OnAttack( UNIT_FUNC_PROTOTYPE )
{  
	switch(rnd(0, 10))	 
	{		
		case 0: SHOUT(INTL( 9211, "Your soul shall be purified!")); break;		
		default: break;
	}
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}

void MOBPurifier::OnAttacked( UNIT_FUNC_PROTOTYPE )
{ 
	switch(rnd(0, 10))	 
	{
		case 0: SHOUT(INTL( 9211, "Your soul shall be purified!")); break;		
		default: break;
	}
SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}

void MOBPurifier::OnDeath( UNIT_FUNC_PROTOTYPE )
{ 
if( target != NULL )
   {	
     GiveFlag(__FLAG_COUNTER_PURIFIER_KILLED, (CheckFlag(__FLAG_COUNTER_PURIFIER_KILLED)+1));     	
   }
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );	 
}

