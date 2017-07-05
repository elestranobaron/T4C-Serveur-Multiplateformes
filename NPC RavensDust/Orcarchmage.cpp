#pragma hdrstop
#include "Orcarchmage.h"

Orcarchmage::Orcarchmage()
{}

Orcarchmage::~Orcarchmage()
{}

extern NPCstructure::NPC OrcArchMageNPC;

void Orcarchmage::Create(){
   npc = OrcArchMageNPC;
   SET_NPC_NAME( "[2974]Orcish arch mage" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void Orcarchmage::OnDeath( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
      SHOUT(INTL( 5601, "*snort* Tis cannot be! Argh... !"));
      GiveFlag( __QUEST_KILLED_ORC_MAGUS, 1);
      GiveGlobalFlag( __GLOBAL_FLAG_ORC_QUEST, 0);
   }
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void Orcarchmage::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk

Begin
""
BREAK

Default
""
BREAK

EndTalk
}

