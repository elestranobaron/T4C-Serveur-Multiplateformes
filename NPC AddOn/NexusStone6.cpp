#pragma hdrstop
#include "NexusStone6.h"

NexusStone6::NexusStone6()
{}

NexusStone6::~NexusStone6()
{}

extern NPCstructure::NPC NexusStoneNPC;

void NexusStone6::Create( ){
	npc = NexusStoneNPC;
	SET_NPC_NAME( "[12756]Nexus Index" );
	npc.InitialPos.X = 1430; 
	npc.InitialPos.Y = 1747;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

void NexusStone6::OnAttacked( UNIT_FUNC_PROTOTYPE ){
     {}
	
}

void NexusStone6::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void NexusStone6::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) >= 28)
		IF(CheckFlag(__FLAG_ADDON_NEXUS_6_ACTIVATED) == 0)
			PRIVATE_SYSTEM_MESSAGE(INTL( 12442, "You place the Runed Stone Tablet on the Nexus Index."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 12443, "The Nexus Stone emits a beam of light that strikes the tablet."))
			GiveFlag(__FLAG_ADDON_NEXUS_6_ACTIVATED, 1)
			GiveFlag(__FLAG_ADDON_NEXUS_STONES_ACTIVATED, CheckFlag(__FLAG_ADDON_NEXUS_STONES_ACTIVATED) + 1)
			IF(CheckFlag(__FLAG_ADDON_NEXUS_STONES_ACTIVATED) == 15)
				PRIVATE_SYSTEM_MESSAGE(INTL( 12450, "As you grab the Runed Stone Tablet, the vibrations coming from within change subtly."))
			ELSE
				PRIVATE_SYSTEM_MESSAGE(INTL( 12445, "You take back the Runed Stone Tablet."))
			ENDIF
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 12446, "You place the Runed Stone Tablet on the Nexus Index, but nothing happens."))
		ENDIF
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 12447, "As far as you can tell, this is some kind of ancient device."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 12448, "There is a large square-shaped recess in the stone."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 12449, "You must step closer to the index to inspect it."))
ENDIF
BREAK

Default
""

EndTalk

}
	