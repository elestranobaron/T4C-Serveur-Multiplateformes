#pragma hdrstop
#include "DeepOneBoss.H"

DeepOneBoss::DeepOneBoss()
{}

DeepOneBoss::~DeepOneBoss()
{}

extern NPCstructure::NPC DeepOneBossNPC;

void DeepOneBoss::Create( void )
{
        npc = ( DeepOneBossNPC );
        SET_NPC_NAME( "[112]Deep One" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 2;
}

void DeepOneBoss::OnDeath( UNIT_FUNC_PROTOTYPE )
{
   INIT_HANDLER
   if( target != NULL )
	{		
	
      IF (CheckFlag(__QUEST_ROD_OF_MANA) == 1)
		IF (CheckFlag(__FLAG_USER_KNOWS_ABOUT_ALOYSIUS) == 0) 
			GiveFlag(__FLAG_USER_KNOWS_ABOUT_ALOYSIUS, 1)
			ENDIF
			GiveItem(__OBJ_NOTE_DEEPONE)
			SHOUT(INTL( 4654, "Gaak.. me no have rod...sold to old wizard.. take scroll..proof "))
		ENDIF
	}
   CLOSE_HANDLER
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}
