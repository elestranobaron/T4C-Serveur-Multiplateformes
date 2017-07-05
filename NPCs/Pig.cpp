#pragma hdrstop
#include "Pig.h"

Pig::Pig()
{}

Pig::~Pig()
{}

extern NPCstructure::NPC _Pig;

void Pig::Create( void )
{
        npc = ( _Pig );
        SET_NPC_NAME( "[3054]A pig" );
        npc.InitialPos.X = 0; 
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}      

void Pig::OnAttacked( UNIT_FUNC_PROTOTYPE ){
    switch(rnd(0, 4)){
    case 0: SHOUT(INTL( 1374, "Oink?!!")); break;
    case 1:break; 
    case 2:break;
    case 3:break;
    case 4:break;
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Pig::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
     GiveFlag(__FLAG_COUNTER_PIG_KILLED, (CheckFlag(__FLAG_COUNTER_PIG_KILLED)+1));
     
	}
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}
