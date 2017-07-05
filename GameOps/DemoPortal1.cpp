#pragma hdrstop
#include "DemoPortal1.h"

DemoPortal1::DemoPortal1()
{}

DemoPortal1::~DemoPortal1()
{}

extern NPCstructure::NPC IslandPortalNPC;

void DemoPortal1::Create( ){
    npc = IslandPortalNPC;
    SET_NPC_NAME(  "[7395]A shimmering portal beckons for you to enter." );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
//    npc.InitialPos.X = 2944;
//    npc.InitialPos.Y = 1069;
    npc.InitialPos.world = 0;
}
void DemoPortal1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}




void DemoPortal1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DemoPortal1::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(CheckFlag(__NEWBIE_QUEST) == 0)
	IF (IsInRange(4))
		IF(target->GetHP() <= 500)
			target->SetMaxHP( 50000 );
			HealPlayer(50000)
			PRIVATE_SYSTEM_MESSAGE(INTL( 7358, "Your HP and Max HP have been set to 50000 for safety precautions."));
		ENDIF
		GiveGold(500000)
		TELEPORT( 2908, 1067, 0)
	   BREAK
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
		BREAK
	ENDIF
ELSEIF(CheckFlag(__NEWBIE_QUEST) == 1)
	IF (IsInRange(4))
		TELEPORT( 1928, 1630, 0)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7359, "You hear some commotion to the west... better go investigate."))
		GiveFlag(__RATS_KILLED, 0)
		SUMMON("NPCRAT", 1814, 1640)
		SUMMON("NPCRAT", 1811, 1643)
		SUMMON("NPCRAT", 1814, 1643)
		SUMMON("NPCRAT", 1817, 1643)
		SUMMON("NPCRAT", 1808, 1646)
		SUMMON("NPCRAT", 1811, 1646)
		SUMMON("NPCRAT", 1814, 1646)
		SUMMON("NPCRAT", 1817, 1646)
		SUMMON("NPCRAT", 1820, 1646)
		SUMMON("NPCRAT", 1811, 1649)
		SUMMON("NPCRAT", 1814, 1649)
		SUMMON("NPCRAT", 1817, 1649)
		SUMMON("NPCRAT", 1820, 1649)
		SUMMON("NPCRAT", 1823, 1649)
		SUMMON("NPCRAT", 1814, 1652)
		SUMMON("NPCRAT", 1817, 1652)
		SUMMON("NPCRAT", 1820, 1652)
		SUMMON("NPCRAT", 1823, 1652)
		SUMMON("NPCRAT", 1826, 1652)
		SUMMON("NPCRAT", 1817, 1655)
		SUMMON("NPCRAT", 1820, 1655)
		SUMMON("NPCRAT", 1823, 1655)
		SUMMON("NPCRAT", 1826, 1655)
		SUMMON("NPCRAT", 1829, 1655)
		SUMMON("NPCRAT", 1823, 1658)
		BREAK
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
		BREAK
	ENDIF
ELSEIF(CheckFlag(__NEWBIE_QUEST) == 2)
	IF (IsInRange(4))
		TELEPORT( 2850, 1102, 0)
		BREAK
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
		BREAK
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 7360, "This portal has been drained of its energy."))
	BREAK
ENDIF

Default
""
BREAK

EndTalk

}