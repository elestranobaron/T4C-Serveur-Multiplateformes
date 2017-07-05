#pragma hdrstop
#include "CentaurAvenger.h"

CentaurAvenger::CentaurAvenger()
{}

CentaurAvenger::~CentaurAvenger()
{}

extern NPCstructure::NPC CentaurAvengerNPC;

void CentaurAvenger::Create(){
   npc = CentaurAvengerNPC;
   SET_NPC_NAME( "[10831]Centaur avenger" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
   npc.InitialPos.world = 0;
}						   

void CentaurAvenger::OnAttack( UNIT_FUNC_PROTOTYPE )
{  
	switch(rnd(0, 10))	 
	{		
		case 0: SHOUT(INTL( 8852, "You're too feeble to even scratch me!")); break;		
		default: break;
	}
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}


void CentaurAvenger::OnAttacked( UNIT_FUNC_PROTOTYPE )
{ 
	switch(rnd(0, 10))	 
	{
		case 0: SHOUT(INTL( 8853, "You'll pay in blood for this.")); break;		
		default: break;
	}

SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}

void CentaurAvenger::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	switch(rnd(0, 3))	 
	{	
		case 0: SHOUT(INTL( 8854, "At least, I die fighting!")); break;
		case 1: SHOUT(INTL( 8855, "Other centaurs will avenge me!")); break;	
		default: break; 
	 }	
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );	 
}
