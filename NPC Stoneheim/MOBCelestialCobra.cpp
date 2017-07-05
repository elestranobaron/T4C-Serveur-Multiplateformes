#pragma hdrstop
#include "MOBCelestialCobra.h"

MOBCelestialCobra::MOBCelestialCobra()
{}

MOBCelestialCobra::~MOBCelestialCobra()
{}

extern NPCstructure::NPC MOBCelestialCobraNPC;

void MOBCelestialCobra::Create(){
   npc = MOBCelestialCobraNPC;
   SET_NPC_NAME( "[10879]Celestial cobra" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
   npc.InitialPos.world = 0;
}						   

void MOBCelestialCobra::OnAttack( UNIT_FUNC_PROTOTYPE )
{  
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}


void MOBCelestialCobra::OnAttacked( UNIT_FUNC_PROTOTYPE )
{ 

SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}

void MOBCelestialCobra::OnDeath( UNIT_FUNC_PROTOTYPE )
{
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );	 
}
