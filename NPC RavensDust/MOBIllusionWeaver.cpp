#pragma hdrstop
#include "MOBIllusionWeaver.h"

MOBIllusionWeaver::MOBIllusionWeaver()
{}

MOBIllusionWeaver::~MOBIllusionWeaver()
{}

extern NPCstructure::NPC MOBIllusionWeaverNPC;

void MOBIllusionWeaver::Create(){
   npc = MOBIllusionWeaverNPC;
   SET_NPC_NAME( "[2969]Illusion weaver" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void MOBIllusionWeaver::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {               
      SWITCH (rnd.roll(dice(1,30)))
         CASE (1)
            SUMMON( "FakeIllusionWeaver", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
         ENDCASE
         CASE (2)
            SUMMON( "FakeGriroesh", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
         ENDCASE
         OTHERWISE
      ENDSWITCH
   }
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}

void MOBIllusionWeaver::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
      SWITCH (rnd.roll(dice(1,30))) 
         CASE (1)
            SUMMON( "FakeIllusionWeaver", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
         ENDCASE
         CASE (2)
            SUMMON( "FakeGriroesh", FROM_NPC(rnd.roll(dice(1, 8))-4,X), FROM_NPC(rnd.roll(dice(1, 8))-4,Y))
         ENDCASE
         OTHERWISE
      ENDSWITCH
	}
SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}



