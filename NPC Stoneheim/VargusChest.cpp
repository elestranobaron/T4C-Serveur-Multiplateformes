///////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "VargusChest.h"

VargusChest::VargusChest()
{}

VargusChest::~VargusChest()
{}

extern NPCstructure::NPC VargusChestNPC;

void VargusChest::OnAttacked( UNIT_FUNC_PROTOTYPE ){
     {}
	
}

void VargusChest::Create( void )
{
      npc = ( VargusChestNPC );
      SET_NPC_NAME( "[10934]A chest" );  
      npc.InitialPos.X = 610; 
      npc.InitialPos.Y = 224;
      npc.InitialPos.world = 0;
}

void VargusChest::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void VargusChest::OnTalk( UNIT_FUNC_PROTOTYPE )
///////////////////////////////////////////////////////////////////////////

{
InitTalk

Begin
""
IF(CheckFlag(__FLAG_USER_HAS_SKULL_OF_OGRIMAR) == 0 )
	IF(CheckFlag(__FLAG_USER_KNOWS_WHERE_SKULL_OF_OGRIMAR_IS_HIDDEN) == 1)
		GiveFlag(__FLAG_USER_HAS_SKULL_OF_OGRIMAR, 1)
		GiveFlag(__FLAG_USER_KNOWS_WHERE_SKULL_OF_OGRIMAR_IS_HIDDEN, 0)
		GiveItem(__OBJ_SKULL_OF_OGRIMAR)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9131, "The chest appears to be empty."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 9130, "Under the false bottom, you discover the Skull of Ogrimar!"))
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 9131, "The chest appears to be empty."))
	ENDIF
ELSE
	PRIVATE_SYSTEM_MESSAGE(INTL( 8700, "The chest is empty."))
ENDIF

Default
""
BREAK

EndTalk
}
