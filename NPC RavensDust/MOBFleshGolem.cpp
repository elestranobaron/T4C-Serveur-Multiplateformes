#pragma hdrstop
#include "MOBFleshGolem.h"

MOBFleshGolem::MOBFleshGolem()
{}

MOBFleshGolem::~MOBFleshGolem()
{}

void MOBFleshGolem::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
	CastSpellSelf(__SPELL_NPC_CANTRIP_RED_WIPE)
   NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}

extern NPCstructure::NPC FleshGolemNPC;

void MOBFleshGolem::Create(){
   npc = FleshGolemNPC;
   SET_NPC_NAME( "[10506]Flesh golem" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void MOBFleshGolem::OnAttacked( UNIT_FUNC_PROTOTYPE ){ 
IF ( (NPC_HP < 181) && (rnd.roll(dice(1,4)) == 1 )) 
      SHOUT(INTL( 7686, "With my last dying breath, I shall kill you!"));
      CastSpellSelf(__SPELL_MOB_AI_SPELL_BLAZE_OF_GLORY);
ENDIF
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

