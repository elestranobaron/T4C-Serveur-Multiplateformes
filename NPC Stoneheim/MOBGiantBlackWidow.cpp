#pragma hdrstop
#include "MOBGiantBlackWidow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MOBGiantBlackWidow::MOBGiantBlackWidow()
{}

MOBGiantBlackWidow::~MOBGiantBlackWidow()
{}

extern NPCstructure::NPC MOBGiantBlackWidowNPC;

void MOBGiantBlackWidow::Create( ){
	npc = MOBGiantBlackWidowNPC;
	SET_NPC_NAME( "[10884]Giant black widow");
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}

void MOBGiantBlackWidow::OnDeath( UNIT_FUNC_PROTOTYPE )
{	  
	if( target != NULL )
	{
	SUMMON("Widow hatchling", FROM_NPC(-1,X), FROM_NPC(-1,Y))	
	SUMMON("Widow hatchling", FROM_NPC(-0,X), FROM_NPC(-1,Y))	
	SUMMON("Widow hatchling", FROM_NPC(-1,X), FROM_NPC(-0,Y))	
	SUMMON("Widow hatchling", FROM_NPC(1,X), FROM_NPC(0,Y))	
	SUMMON("Widow hatchling", FROM_NPC(0,X), FROM_NPC(1,Y))	
	}

SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}

void MOBGiantBlackWidow::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {               
      
		IF (rnd.roll(dice(1,40)))
			SUMMON( "Widow hatchling", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
		ENDIF      
				
   }
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}

void MOBGiantBlackWidow::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
		IF (rnd.roll(dice(1,40)))
			SUMMON( "Widow hatchling", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
		ENDIF      		
	}
SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}

