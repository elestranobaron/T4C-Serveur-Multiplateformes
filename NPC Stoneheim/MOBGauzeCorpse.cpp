#pragma hdrstop
#include "MOBGauzeCorpse.h"

MOBGauzeCorpse::MOBGauzeCorpse()
{}

MOBGauzeCorpse::~MOBGauzeCorpse()
{}

extern NPCstructure::NPC MOBGauzeCorpseNPC;

void MOBGauzeCorpse::Create(){
   npc = MOBGauzeCorpseNPC;
   SET_NPC_NAME( "[10882]Gauze corpse" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
   npc.InitialPos.world = 0;
}						   

void MOBGauzeCorpse::OnAttack( UNIT_FUNC_PROTOTYPE )
{  
	
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}


void MOBGauzeCorpse::OnAttacked( UNIT_FUNC_PROTOTYPE )
{ 
	
SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}

void MOBGauzeCorpse::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );	 
}
