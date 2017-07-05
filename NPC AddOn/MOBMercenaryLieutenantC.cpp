#pragma hdrstop
#include "MOBMercenaryLieutenantC.h"

MOBMercenaryLieutenantC::MOBMercenaryLieutenantC()
{}

MOBMercenaryLieutenantC::~MOBMercenaryLieutenantC()
{}

extern NPCstructure::NPC MOBMercenaryLieutenantNPC;

void MOBMercenaryLieutenantC::Create(){
   npc = MOBMercenaryLieutenantNPC;
   SET_NPC_NAME( "[12750]Mercenary Lieutenant" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
   npc.InitialPos.world = 0;
}

void MOBMercenaryLieutenantC::OnPopup( UNIT_FUNC_PROTOTYPE )
{											 	
  GiveGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LIEUTENANT_C_SPAWNED, 1);
NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}

void MOBMercenaryLieutenantC::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
	IF (rnd.roll(dice(1,30)) == 1) 
		IF (rnd.roll(dice(1,2)) == 1) 
			SHOUT(INTL( 12413, "You're no match for me!")) 
		ELSE 
      SHOUT(INTL( 12414, "Ow! You'll pay in blood!"))
		ENDIF 
	ENDIF    
   }
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void MOBMercenaryLieutenantC::OnDeath( UNIT_FUNC_PROTOTYPE )
{
  INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{
            SHOUT(INTL( 12416, "AAARGH! My men will avenge me!"))     
            GiveGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LIEUTENANT_C_KILLED_TIMER, CurrentRound)
            IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LIEUTENANT_A_KILLED_TIMER)>=(CurrentRound-3600)) 
              IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LIEUTENANT_B_KILLED_TIMER)>=(CurrentRound-3600))
                IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LIEUTENANT_C_KILLED_TIMER)>=(CurrentRound-3600))
				IF((CheckGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LEADER_SPAWNED)==0)&&(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LIEUTENANT_A_KILLED_TIMER)!=0)&&(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LIEUTENANT_B_KILLED_TIMER)!=0)&&(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LIEUTENANT_C_KILLED_TIMER)!=0))
					SUMMON("MOBMERCENARYLEADER", 2680,895 )
					PRIVATE_SYSTEM_MESSAGE(INTL( 12417, "As the mercenary lieutenant falls lifeless, you hear a loud war call from the northern camp.")) 
					GiveGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LIEUTENANT_A_KILLED_TIMER, 0)
					GiveGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LIEUTENANT_B_KILLED_TIMER, 0)
					GiveGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LIEUTENANT_C_KILLED_TIMER, 0)
				ENDIF
                ENDIF
              ENDIF
            ENDIF           
	}

    CLOSE_HANDLER
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void MOBMercenaryLieutenantC::OnDestroy( UNIT_FUNC_PROTOTYPE )
{
    GiveGlobalFlag(__GLOBAL_FLAG_ADDON_MERCENARY_LIEUTENANT_C_SPAWNED, 0);
NPCstructure::OnDestroy( UNIT_FUNC_PARAM );
}

