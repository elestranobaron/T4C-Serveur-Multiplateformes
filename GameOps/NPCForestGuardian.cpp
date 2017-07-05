/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "NPCForestGuardian.H"

NPCForestGuardian::NPCForestGuardian()
{}

NPCForestGuardian::~NPCForestGuardian()
{}

extern NPCstructure::NPC _NPCForestGuardian;

void NPCForestGuardian::Create( void )
{
      npc = ( _NPCForestGuardian );
      SET_NPC_NAME( "[87]Forest Guardian" );  
      npc.InitialPos.X = 0; 
      npc.InitialPos.Y = 0;
      npc.InitialPos.world = 0;
}

void NPCForestGuardian::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
	TFormat FORMAT;
	GiveFlag( __GUARDIANS_KILLED, CheckFlag(__GUARDIANS_KILLED) + 1) 	
	IF (CheckFlag( __GUARDIANS_KILLED) == 1) 
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7362, "You have killed %u forest guardian!"), CheckFlag(__GUARDIANS_KILLED)))
	ELSE
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7363, "You have killed %u forest guardians!"), CheckFlag(__GUARDIANS_KILLED)))
	ENDIF
	}
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}


