#pragma hdrstop
#include "DrVonPyre.h"

DrVonPyre::DrVonPyre()
{}

DrVonPyre::~DrVonPyre()
{}

extern NPCstructure::NPC DrVonPyreNPC;

void DrVonPyre::Create( void )
{
   npc = DrVonPyreNPC;
   SET_NPC_NAME( "[10972]Dr. Von Pyre" );
   npc.InitialPos.X = 0;
   npc.InitialPos.Y = 0;
   npc.InitialPos.world = 0;
}

void DrVonPyre::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   IF (rnd.roll(dice(1,40)) == 1) 
      SHOUT(INTL( 10637, "How is your blood pressure today?")) 
   ENDIF
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}
 