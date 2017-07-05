/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "NPCRat.H"

NPCRat::NPCRat()
{}

NPCRat::~NPCRat()
{}

extern NPCstructure::NPC _NPCRat;

void NPCRat::Create( void )
{
      npc = ( _NPCRat );
      SET_NPC_NAME( "[47]Brown rat" );  
      npc.InitialPos.X = 0; 
      npc.InitialPos.Y = 0;
      npc.InitialPos.world = 0;
}

void NPCRat::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
	TFormat FORMAT;
   GiveFlag( __RATS_KILLED, CheckFlag(__RATS_KILLED)+1 )
	IF (CheckFlag( __RATS_KILLED) == 1) 
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7364, "You have killed %u rat!"), CheckFlag(__RATS_KILLED)))
	ELSE
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7365, "You have killed %u rats!"), CheckFlag(__RATS_KILLED)))
	ENDIF
	}
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}


