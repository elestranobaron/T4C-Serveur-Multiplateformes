#pragma hdrstop
#include "MadMadrigan.h"
 
MadMadrigan::MadMadrigan()
{}

MadMadrigan::~MadMadrigan()
{}

extern NPCstructure::NPC MadMadriganNPC;

void MadMadrigan::Create( void )
{
   npc = MadMadriganNPC;
   SET_NPC_NAME( "[10974]Mad Madrigan" );
   npc.InitialPos.X = 0;
   npc.InitialPos.Y = 0;
   npc.InitialPos.world = 0;
}

void MadMadrigan::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   IF (rnd.roll(dice(1,30)) == 1) 
		SWITCH(rnd.roll(dice(1,2) ) ) 
			CASE(1)
				SHOUT(INTL( 10681, "Hee hee hee, bet you think you're tough, right?")) 	
			ENDCASE
			CASE(2)
				SHOUT(INTL( 1375, "Oink! Oink!")) 
			ENDCASE			
		ENDSWITCH
   ENDIF
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void MadMadrigan::OnPopup( UNIT_FUNC_PROTOTYPE ){																	 
  	CastSpellSelf(__SPELL_MOB_INVISIBILITY_SPELL) 	
	
	NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}
