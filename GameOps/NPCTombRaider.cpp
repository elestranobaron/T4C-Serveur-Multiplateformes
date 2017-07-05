/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "NPCTombRaider.H"

NPCTombRaider::NPCTombRaider()
{}

NPCTombRaider::~NPCTombRaider()
{}

extern NPCstructure::NPC _NPCTombRaider;

void NPCTombRaider::Create( void )
{
      npc = ( _NPCTombRaider );
      SET_NPC_NAME( "[88]Tomb raider" );  
      // npc.InitialPos.X = 85; 
      // npc.InitialPos.Y = 620;
		npc.InitialPos.X = 0; 
      npc.InitialPos.Y = 0;
      npc.InitialPos.world = 1;
}

void NPCTombRaider::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{  
	TFormat FORMAT;
	GiveFlag( __FLAG_KILLED_TOMB_RAIDER, 1)
	SHOUT(FORMAT(INTL( 7366, "Damn you %s! You'll never get away with this!"), USER_NAME) )
	PRIVATE_SYSTEM_MESSAGE(INTL( 7367, "You have slain the tomb raider!")) 
	}
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void NPCTombRaider::OnAttack( UNIT_FUNC_PROTOTYPE ){
    switch(rnd(0, 5)){
    case 0: SHOUT(INTL( 7368, "Die like the pig you are!")); break;
    case 1: SHOUT(INTL( 2030, "You're bleeding? Come to me and bleed some more!")); break;
    case 2:break;
    case 3:break;
    case 4:break;
    case 5:break;
	}
	NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void NPCTombRaider::OnAttacked( UNIT_FUNC_PROTOTYPE ){
    switch(rnd(0, 9)){
    case 0: SHOUT(INTL( 7369, "Damnit! That hurts!")); break;
    case 1: SHOUT(INTL( 7370, "Argh! You'll pay for this!")); break;
    case 2:break;
    case 3:break;
    case 4:break;
    case 5:break;
	 case 6:break;
	 case 7:break;
    case 8:break;
    case 9:break;
	}
	NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}



