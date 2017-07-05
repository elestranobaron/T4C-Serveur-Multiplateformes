#pragma hdrstop
#include "NexusStone5.h"

NexusStone5::NexusStone5()
{}

NexusStone5::~NexusStone5()
{}

extern NPCstructure::NPC NexusStoneNPC;

void NexusStone5::Create( ){
	npc = NexusStoneNPC;
	SET_NPC_NAME( "[12756]Nexus Index" );
	npc.InitialPos.X = 2150; 
	npc.InitialPos.Y = 1695;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

void NexusStone5::OnAttacked( UNIT_FUNC_PROTOTYPE ){
     {}
	
}

void NexusStone5::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void NexusStone5::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) >= 27)
		IF(CheckFlag(__FLAG_ADDON_NEXUS_5_ACTIVATED) == 0)
			PRIVATE_SYSTEM_MESSAGE(INTL( 12442, "You place the Runed Stone Tablet on the Nexus Index."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 12443, "The Nexus Stone emits a beam of light that strikes the tablet."))
			GiveFlag(__FLAG_ADDON_NEXUS_5_ACTIVATED, 1)
			GiveFlag(__FLAG_ADDON_NEXUS_STONES_ACTIVATED, CheckFlag(__FLAG_ADDON_NEXUS_STONES_ACTIVATED) + 1)
			IF(CheckFlag(__FLAG_ADDON_NEXUS_STONES_ACTIVATED) == 5)
				PRIVATE_SYSTEM_MESSAGE(INTL( 12444, "As you grab the Runed Stone Tablet, you feel some strong vibrations coming from within."))
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
	