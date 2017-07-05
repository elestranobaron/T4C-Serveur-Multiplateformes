/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "DorkenRotsmell.H"

DorkenRotsmell::DorkenRotsmell()
{}

DorkenRotsmell::~DorkenRotsmell()
{}

extern NPCstructure::NPC _DorkenRotsmell;

void DorkenRotsmell::Create( void )
{
	npc = ( _DorkenRotsmell );
	SET_NPC_NAME( "[2895]Dorken Rotsmell" ); 
	npc.InitialPos.X = 0; 
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}

void DorkenRotsmell::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
		GiveGlobalFlag( __GLOBAL_FLAG_GOBLIN_QUEST, 0)
		GiveGlobalFlag( __GLOBAL_QUEST_WHO_IS_INFECTED, rnd.roll( dice(1, 3)) )
		SHOUT(INTL( 472, "AARGH!")) 
		// Dorken is somewhat of a bad guy...
		IF (USER_KARMA <= (100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1))) // People who are sufficiently bad...
			GiveKarma(1*(500-USER_KARMA)/500)
		ENDIF
	}
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void DorkenRotsmell::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{
InitTalk

Begin
INTL( 473, "You die!") FIGHT

Default
INTL( 473, "You die!") FIGHT

EndTalk
}

