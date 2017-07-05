#pragma hdrstop
#include "OraclePortal8.h"

OraclePortal8::OraclePortal8()
{}

OraclePortal8::~OraclePortal8()
{}

extern NPCstructure::NPC PortalNPC;

void OraclePortal8::Create( ){
	npc = PortalNPC;
	SET_NPC_NAME(  "[7396]A shimmering portal" );
	npc.InitialPos.X = 2520;
	npc.InitialPos.Y = 2340;
	npc.InitialPos.world = 2;
}
void OraclePortal8::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void OraclePortal8::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void OraclePortal8::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF (IsInRange(4))
	IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1)
		IF(CheckItem(__OBJ_KEY_OF_ARTHERK) >= 1)
			SWITCH(rnd.roll(dice(1,4)))
				CASE(1)
					TELEPORT( 630, 630, 0)
				ENDCASE
				CASE(2)
					TELEPORT( 680, 580, 0)
				ENDCASE
				CASE(3)
					TELEPORT( 730, 630, 0)
				ENDCASE
				CASE(4)
					TELEPORT( 680, 680, 0)
				ENDCASE
			ENDSWITCH
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 9373, "You step into the portal but nothing seems to happen."))
		ENDIF
	ELSEIF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
		IF(CheckItem(__OBJ_KEY_OF_OGRIMAR) >= 1)
			SWITCH(rnd.roll(dice(1,4)))
				CASE(1)
					TELEPORT( 630, 630, 0)
				ENDCASE
				CASE(2)
					TELEPORT( 680, 580, 0)
				ENDCASE
				CASE(3)
					TELEPORT( 730, 630, 0)
				ENDCASE
				CASE(4)
					TELEPORT( 680, 680, 0)
				ENDCASE
			ENDSWITCH
		ELSE
			PRIVATE_SYSTEM_MESSAGE(INTL( 9373, "You step into the portal but nothing seems to happen."))
		ENDIF
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 9373, "You step into the portal but nothing seems to happen."))
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