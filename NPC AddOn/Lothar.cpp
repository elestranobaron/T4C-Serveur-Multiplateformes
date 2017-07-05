#pragma hdrstop
#include "Lothar.h"

Lothar::Lothar()
{}

Lothar::~Lothar()
{}

extern NPCstructure::NPC HighPriestGuntharNPC;

void Lothar::Create( ){
	npc = HighPriestGuntharNPC;
	SET_NPC_NAME( "[12747]Lothar");
	npc.InitialPos.X = 1631;
	npc.InitialPos.Y = 1644;
	npc.InitialPos.world = 1;
}

void Lothar::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void Lothar::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void Lothar::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 39)
	Conversation
	INTL( 1864, "...")
	BREAK
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 39)	
	Conversation
	INTL( 12404, "I have gone and my children have wept. Their cry still echoes in my essence... To them I leave "
	"the power of retribution. In them my seeds grow and will flourish into the last remnants of Justice.")
	PRIVATE_SYSTEM_MESSAGE(INTL( 12405, "Lothar hands you Caledbolg, the one true sword of Justice."))
	GiveItem(__OBJ_CALEDBOLG)
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 40) 	
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 40)
	Conversation
	INTL( 12406, "Return whence you came with Caledbolg in hand to face your destiny.") 
ELSE
	Conversation
	INTL( 1864, "...")
	BREAK
ENDIF

Default
INTL( 1864, "...")
BREAK

EndTalk
}