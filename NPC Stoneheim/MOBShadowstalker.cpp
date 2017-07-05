#pragma hdrstop
#include "MOBShadowstalker.h"

MOBShadowstalker::MOBShadowstalker()
{}

MOBShadowstalker::~MOBShadowstalker()
{}

extern NPCstructure::NPC MOBShadowstalkerNPC;


void MOBShadowstalker::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	SimpleMonster::OnInitialise( UNIT_FUNC_PARAM );
	CastSpellSelf(__SPELL_MOB_INVISIBILITY_SPELL);
}
void MOBShadowstalker::Create(){
   npc = MOBShadowstalkerNPC;
   SET_NPC_NAME( "[10894]Shadowstalker" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void MOBShadowstalker::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {               
   }
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}

void MOBShadowstalker::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
	}
SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}

void MOBShadowstalker::OnDeath( UNIT_FUNC_PROTOTYPE )
{

	if( target != NULL )
   {
      SHOUT(INTL( 9171, "NooOOoo! Mordenthal will burn my entrails for this!"))
   }


SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}

void MOBShadowstalker::OnAttackHit( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {               
   }
SimpleMonster::OnAttackHit( UNIT_FUNC_PARAM );
}


