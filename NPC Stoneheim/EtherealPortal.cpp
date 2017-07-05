#pragma hdrstop
#include "EtherealPortal.h"

EtherealPortal::EtherealPortal()
{}

EtherealPortal::~EtherealPortal()
{}

extern NPCstructure::NPC PortalNPC;

void EtherealPortal::Create( ){
    npc = PortalNPC;
    SET_NPC_NAME(  "[10851]An ethereal portal beckons for you to enter." );
    npc.InitialPos.X = 790;
    npc.InitialPos.Y = 495;
    npc.InitialPos.world = 0;
}
void EtherealPortal::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void EtherealPortal::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void EtherealPortal::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
   IF ((CheckItem(__OBJ_ETHEREAL_KEY) >= 1) || (CheckItem(__OBJ_FIXED_ETHEREAL_KEY) >= 1)) 
      SWITCH(rnd.roll(dice(1,10))) 
         CASE(1)
            SUMMON("ETHEREALPORTAL", 790, 495)
         ENDCASE
         CASE(2)
            SUMMON("ETHEREALPORTAL", 820, 620)
         ENDCASE
         CASE(3)
            SUMMON("ETHEREALPORTAL", 980, 610)
         ENDCASE
         CASE(4)
            SUMMON("ETHEREALPORTAL", 930, 520)
         ENDCASE
         CASE(5)
            SUMMON("ETHEREALPORTAL", 930, 520)
         ENDCASE
         CASE(6)
            SUMMON("ETHEREALPORTAL", 980, 610)
         ENDCASE
         CASE(7)
            SUMMON("ETHEREALPORTAL", 820, 620)
         ENDCASE
         CASE(8)
            SUMMON("ETHEREALPORTAL", 790, 495)
         ENDCASE
         CASE(9)
            SUMMON("ETHEREALPORTAL", 790, 495)
         ENDCASE
         CASE(10)
            SUMMON("ETHEREALPORTAL", 790, 495)
         ENDCASE     
      ENDSWITCH
		PRIVATE_SYSTEM_MESSAGE(INTL( 9172, "You feel somewhat dizzy after being translocated."))
      TELEPORT(2137,2798,0)  
      SELF_DESTRUCT 
      BREAK
   ELSE 
      PRIVATE_SYSTEM_MESSAGE(INTL( 7354, "Nothing happens."))      
   ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}
