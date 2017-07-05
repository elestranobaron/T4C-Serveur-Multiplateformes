/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "NPCGoblinWarrior.H"

NPCGoblinWarrior::NPCGoblinWarrior()
{}

NPCGoblinWarrior::~NPCGoblinWarrior()
{}

extern NPCstructure::NPC _NPCGoblinWarrior;

void NPCGoblinWarrior::Create( void )
{
      npc = ( _NPCGoblinWarrior );
      SET_NPC_NAME( "[7504]Goblin warrior" );  
      npc.InitialPos.X = 0; 
      npc.InitialPos.Y = 0;
      npc.InitialPos.world = 0;
}

