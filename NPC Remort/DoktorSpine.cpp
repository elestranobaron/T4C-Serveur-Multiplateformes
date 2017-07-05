#pragma hdrstop
#include "DoktorSpine.h"

DoktorSpine::DoktorSpine()
{}

DoktorSpine::~DoktorSpine()
{}

extern NPCstructure::NPC DoktorSpineNPC;

void DoktorSpine::Create( void )
{
   npc = DoktorSpineNPC;
   SET_NPC_NAME( "[10971]Doktor Spine" );
   npc.InitialPos.X = 0;
   npc.InitialPos.Y = 0;
   npc.InitialPos.world = 0;
}

void DoktorSpine::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   IF (rnd.roll(dice(1,40)) == 1) 
      SHOUT(INTL( 10636, "It's time for your spine transplant.")) 
   ENDIF
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}
