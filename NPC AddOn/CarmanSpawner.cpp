#pragma hdrstop
#include "CarmanSpawner.h"

CarmanSpawner::CarmanSpawner()
{}

CarmanSpawner::~CarmanSpawner()
{}

extern NPCstructure::NPC CarmanSpawnerNPC;

void CarmanSpawner::Create( ){
	npc = CarmanSpawnerNPC;
	SET_NPC_NAME( "[12726]Hel");
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}

void CarmanSpawner::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void CarmanSpawner::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void CarmanSpawner::OnDestroy( UNIT_FUNC_PROTOTYPE )
{
	SUMMON("CARMAN", 1663, 1040)

NPCstructure::OnDestroy( UNIT_FUNC_PARAM );
}

void CarmanSpawner::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_USER_SPAWNED_CARMAN) == 1)
	Conversation
	INTL( 11904, "So, you figured out my little ruse. Well, that's too bad... for you!")
	CastSpellSelf(__SPELL_SELF_DESTRUCT_5_SECONDS)
	BREAK
ELSE
	Conversation
	INTL( 11905, "I don't have time to speak with you.")
	BREAK
ENDIF

EndTalk
}