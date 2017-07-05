/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "NPCGoblinScout.H"

NPCGoblinScout::NPCGoblinScout()
{}

NPCGoblinScout::~NPCGoblinScout()
{}

extern NPCstructure::NPC _NPCGoblinScout;

void NPCGoblinScout::Create( void )
{
      npc = ( _NPCGoblinScout );
      SET_NPC_NAME( "[7503]Goblin scout" );  
      npc.InitialPos.X = 0; 
      npc.InitialPos.Y = 0;
      npc.InitialPos.world = 0;
}

