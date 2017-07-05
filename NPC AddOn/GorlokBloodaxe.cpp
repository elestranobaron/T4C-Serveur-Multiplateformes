#pragma hdrstop
#include "GorlokBloodaxe.H"

GorlokBloodaxe::GorlokBloodaxe()
{}

GorlokBloodaxe::~GorlokBloodaxe()
{}

extern NPCstructure::NPC GorlokBloodaxeNPC;

void GorlokBloodaxe::Create( void )
{
	npc = ( GorlokBloodaxeNPC );
	SET_NPC_NAME( "[12740]Gorlok Bloodaxe" );
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}

void GorlokBloodaxe::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	INIT_HANDLER

	TFormat FORMAT;
	if( target != NULL )
	{
		IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 22);
			SUMMON("HIGHPRIESTGUNTHAR2", target->GetWL().X, target->GetWL().Y)
			PRIVATE_SYSTEM_MESSAGE(INTL( 12166, "By killing Gorlok Bloodaxe, you have freed the High Priest from his captors."))
		ENDIF;
	}

	CLOSE_HANDLER
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}