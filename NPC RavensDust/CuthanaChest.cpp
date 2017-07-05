///////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "CuthanaChest.h"

CuthanaChest::CuthanaChest()
{}

CuthanaChest::~CuthanaChest()
{}

extern NPCstructure::NPC CuthanaChestNPC;

void CuthanaChest::OnAttacked( UNIT_FUNC_PROTOTYPE ){
     {}
	
}

void CuthanaChest::Create( void )
{
      npc = ( CuthanaChestNPC );
      SET_NPC_NAME( "[2939]A mysterious chest" );  
      npc.InitialPos.X = 683; 
      npc.InitialPos.Y = 342;
      npc.InitialPos.world = 2;
}

void CuthanaChest::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void CuthanaChest::OnTalk( UNIT_FUNC_PROTOTYPE )
///////////////////////////////////////////////////////////////////////////

{
InitTalk

Begin
""
IF (CheckItem(__OBJ_CUTHANA_HERB) >= 1) 
	;int nNumCuthana = CheckItem(__OBJ_CUTHANA_HERB); 
   FOR(0, nNumCuthana)
      TakeItem(__OBJ_CUTHANA_HERB)
   ENDFOR
ENDIF
Conversation
INTL( 6399, "{You} {open} {the} {chest} {and} {find} {some} {cuthana} {herbs.}")
GiveItem(__OBJ_CUTHANA_HERB) 
TELEPORT (1016,1762,0)
BREAK

Default
""
BREAK

EndTalk
}
