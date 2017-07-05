#pragma hdrstop
#include "OracleVulnerableGuardian.h"

OracleVulnerableGuardian::OracleVulnerableGuardian()
{}

OracleVulnerableGuardian::~OracleVulnerableGuardian()
{}

extern NPCstructure::NPC OracleVulnerableGuardianNPC;

void OracleVulnerableGuardian::Create(){
   npc = OracleVulnerableGuardianNPC;
   SET_NPC_NAME( "[10906]Oracle gatekeeper" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void OracleVulnerableGuardian::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	TFormat FORMAT;
	if( target != NULL )
	{
		IF(CheckItem(__OBJ_GLEAMING_ORICHALCUM_KEY) == 0)
			GiveItem(__OBJ_GLEAMING_ORICHALCUM_KEY)
			PRIVATE_SYSTEM_MESSAGE(INTL( 9821, "A gleaming orichalcum key falls to the floor and you quickly pick it up."))
		ENDIF
	}
    CLOSE_HANDLER

SimpleMonster::OnDeath( UNIT_FUNC_PARAM );	 
}



