#pragma hdrstop
#include "MOBNeoflare.h"

MOBNeoflare::MOBNeoflare()
{}

MOBNeoflare::~MOBNeoflare()
{}


void MOBNeoflare::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 

	CastSpellSelf(__SPELL_NPC_CANTRIP_RED_WIPE)
	SimpleMonster::OnPopup( UNIT_FUNC_PARAM );
}

extern NPCstructure::NPC MOBNeoflareNPC;

void MOBNeoflare::Create(){
   npc = MOBNeoflareNPC;
   SET_NPC_NAME( "[10889]Neoflare" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void MOBNeoflare::OnDeath( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {	
     GiveFlag(__FLAG_COUNTER_NEOFLARE_KILLED, (CheckFlag(__FLAG_COUNTER_NEOFLARE_KILLED)+1));     	
   }
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}


