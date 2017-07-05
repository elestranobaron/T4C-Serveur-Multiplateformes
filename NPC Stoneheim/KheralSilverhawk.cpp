#pragma hdrstop
#include "KheralSilverhawk.h"

KheralSilverhawk::KheralSilverhawk()
{}

KheralSilverhawk::~KheralSilverhawk()
{}

extern NPCstructure::NPC KheralSilverhawkNPC;

void KheralSilverhawk::Create(){
   npc = KheralSilverhawkNPC;
   SET_NPC_NAME( "[10867]Kheral Silverhawk" );
   npc.InitialPos.X = 290; 
   npc.InitialPos.Y = 685; 
	npc.InitialPos.world = 0;
}									 

void KheralSilverhawk::OnAttack( UNIT_FUNC_PROTOTYPE )
{  
   switch(rnd(0, 20))    
	{		
   case 0: SHOUT(INTL( 8544, "Stonecrest is under my protection! Leave or DIE!")); break;
   case 1: SHOUT(INTL( 2030, "You're bleeding? Come to me and bleed some more!")); break; 
   case 2: SHOUT(INTL( 8545, "Isn't it a nice day to die?")); break;
   default: break;
	}
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}


void KheralSilverhawk::OnAttacked( UNIT_FUNC_PROTOTYPE )
{ 
   switch(rnd(0, 20))    
	{
      case 0: SHOUT(INTL( 2032, "Ow!")); break;
      case 1: SHOUT(INTL( 8546, "You got lucky on that one!")); break;
      case 2: SHOUT(INTL( 8547, "You're starting to make me mad!")); break;
		default: break;
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void KheralSilverhawk::OnDeath( UNIT_FUNC_PROTOTYPE )
{
   switch(rnd(0, 2)) 
	{	
      case 0: SHOUT(INTL( 1860, "Urgh!")); break;
		default: break; 
	 }	
NPCstructure::OnDeath( UNIT_FUNC_PARAM );    
}

void KheralSilverhawk::OnTalk( UNIT_FUNC_PROTOTYPE )

{
InitTalk

Begin
INTL( 8975, "I have no time to spare. I have to defend Stonecrest.")
BREAK

Default
""
BREAK
EndTalk
}