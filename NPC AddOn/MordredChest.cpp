#pragma hdrstop
#include "MordredChest.h"

MordredChest::MordredChest()
{}

MordredChest::~MordredChest()
{}

extern NPCstructure::NPC MetalChestNPC;

void MordredChest::Create( ){
	npc = MetalChestNPC;
  SET_NPC_NAME( "[12754]metallic chest" );
  npc.InitialPos.X = 576;
  npc.InitialPos.Y = 760;
  npc.InitialPos.world = 0;
}
void MordredChest::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void MordredChest::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void MordredChest::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(IsInRange(4))
	IF(CheckItem(__OBJ_MORDRED_KEY)>=1)
		FOR(0, CheckItem(__OBJ_MORDRED_KEY) )
			TakeItem(__OBJ_MORDRED_KEY) 
		ENDFOR 
		PRIVATE_SYSTEM_MESSAGE(INTL( 12426, "The key found on Mordred's corpse fits the lock perfectly and you open the chest.")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 12427, "Inside the chest you find a beautifully crafted armor, probably stolen from the seraph's corpse.")) 					
		GiveItem(__OBJ_SERAPH_PLATE) 	
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 9355, "The chest is locked.")) 
	ENDIF 
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 8702, "You must step closer to the chest to open it."))
ENDIF
BREAK

Default
""
BREAK

EndTalk

}
