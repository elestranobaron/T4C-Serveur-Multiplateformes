#pragma hdrstop
#include "MOBNightRetriever.h"

MOBNightRetriever::MOBNightRetriever()
{}

MOBNightRetriever::~MOBNightRetriever()
{}

extern NPCstructure::NPC MOBNightRetrieverNPC;

void MOBNightRetriever::Create(){
   npc = MOBNightRetrieverNPC;
   SET_NPC_NAME( "[10890]Night retriever" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void MOBNightRetriever::OnDeath( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
      SHOUT(INTL( 9169, "ARRRGHH! Master won't be pleased!!"))
   }
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}

void MOBNightRetriever::OnAttackHit( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
   if( target != NULL )
   {               
      IF(rnd.roll(dice(1,20)) == 1) 
         IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 6)
            TakeItem(__OBJ_FANG_OF_TRUE_RESOLVE)
            GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 5)
            PRIVATE_SYSTEM_MESSAGE(INTL( 9170, "The night retriever just stole a fang of true resolve from your backpack!")) 
         ENDIF  
      ENDIF
   }
   CLOSE_HANDLER
SimpleMonster::OnAttackHit( UNIT_FUNC_PARAM );
}





