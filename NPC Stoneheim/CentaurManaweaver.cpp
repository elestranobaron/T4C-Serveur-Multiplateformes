#pragma hdrstop
#include "CentaurManaweaver.h"

CentaurManaweaver::CentaurManaweaver()
{}

CentaurManaweaver::~CentaurManaweaver()
{}

extern NPCstructure::NPC CentaurManaweaverNPC;

void CentaurManaweaver::Create(){
   npc = CentaurManaweaverNPC;
   SET_NPC_NAME( "[10833]Centaur manaweaver" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
   npc.InitialPos.world = 0;
}

void CentaurManaweaver::OnAttack( UNIT_FUNC_PROTOTYPE )
{  
	switch(rnd(0, 30))	 
	{		
		case 0: SHOUT(INTL( 8878, "Fight me, coward!")); break;
		case 1: SHOUT(INTL( 8879, "Stop parrying and start fighting!")); break;		
		default: break;
	}
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}


void CentaurManaweaver::OnAttacked( UNIT_FUNC_PROTOTYPE )
{ 
		switch(rnd(0, 30))	 
	{
		case 0: SHOUT(INTL( 8880, "You dare strike a Centaur?! You'll pay for this!")); break;
		case 1: SHOUT(INTL( 8881, "You really think you can hurt me?")); break;
		case 2: SHOUT(INTL( 8882, "Your blows are too feeble!")); break;		
		default: break;
	}
SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}

void CentaurManaweaver::OnDeath( UNIT_FUNC_PROTOTYPE )
{
		switch(rnd(0, 30))	 
	{	
		case 0: SHOUT(INTL( 8854, "At least, I die fighting!")); break;
		case 1: SHOUT(INTL( 8883, "Centaurs will avenge me!")); break;
		case 2: SHOUT(INTL( 8884, "ARRRRGH!")); break;
		default: break;  
	 }	

SimpleMonster::OnDeath( UNIT_FUNC_PARAM );	 
}
