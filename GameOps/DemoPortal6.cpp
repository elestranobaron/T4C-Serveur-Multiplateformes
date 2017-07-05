#pragma hdrstop
#include "DemoPortal6.h"

DemoPortal6::DemoPortal6()
{}

DemoPortal6::~DemoPortal6()
{}

extern NPCstructure::NPC IslandPortalNPC;

void DemoPortal6::Create( ){
    npc = IslandPortalNPC;
    SET_NPC_NAME(  "[7395]A shimmering portal beckons for you to enter." );
    npc.InitialPos.X = 0;
    npc.InitialPos.Y = 0;
//    npc.InitialPos.X = 2848;
//    npc.InitialPos.Y = 1122;
    npc.InitialPos.world = 0;
}
void DemoPortal6::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}


void DemoPortal6::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void DemoPortal6::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(CheckFlag(__NEWBIE_QUEST) == 2)
	IF (IsInRange(4))
		SUMMON("NPCFORESTGUARDIAN", 2784, 176)
		SUMMON("NPCFORESTGUARDIAN", 2795, 168)
		SUMMON("NPCFORESTGUARDIAN", 2795, 184)
		SUMMON("NPCFORESTGUARDIAN", 2775, 176)
		SUMMON("NPCFORESTGUARDIAN", 2800, 160)
		SUMMON("NPCFORESTGUARDIAN", 2800, 192)
		TELEPORT( 2793, 177, 0)
		BREAK
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 7349, "You must step closer to the portal to activate it."))
		BREAK
	ENDIF
ELSE
	Conversation
	INTL( 7361, "This portal is not yet activated.")
ENDIF

/*IF (IsInRange(4))
	TELEPORT( 2600, 3000, 0)
   BREAK
ELSE
	PRIVATE_SYSTEM_MESSAGE("You must step closer to the portal to activate it.")
	BREAK
ENDIF
*/

Default
""
BREAK

EndTalk

}