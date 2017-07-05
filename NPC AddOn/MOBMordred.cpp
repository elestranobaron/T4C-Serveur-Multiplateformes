#pragma hdrstop
#include "MOBMordred.h"

MOBMordred::MOBMordred()
{}

MOBMordred::~MOBMordred()
{}

extern NPCstructure::NPC MordredNPC;

void MOBMordred::Create(){
   npc = MordredNPC;
   SET_NPC_NAME( "[12751]Commander Mordred" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
   npc.InitialPos.world = 0;
}

void MOBMordred::OnDestroy( UNIT_FUNC_PROTOTYPE )
{
	GiveGlobalFlag(__GLOBAL_FLAG_ADDON_MORDRED, 0);
    SimpleMonster::OnDestroy( UNIT_FUNC_PARAM );
}

void MOBMordred::OnPopup( UNIT_FUNC_PROTOTYPE )
{
	SHOUT(INTL( 12418, "Enough!! Let's see how you'll fare against me and my blade!")); 	
	GiveGlobalFlag(__GLOBAL_FLAG_ADDON_MORDRED, 1);
	SimpleMonster::OnPopup( UNIT_FUNC_PARAM );
}

void MOBMordred::OnAttack( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL ){
		switch(rnd(0, 15)){		
		case 0:
			SHOUT(INTL( 12419, "Knights! Dispose of this wretch!"));
			SUMMON("MOBOBSIDIANCONCLAVEKNIGHT", FROM_NPC(rnd.roll(dice(1, 5))-3,X), FROM_NPC(rnd.roll(dice(1, 5))-3,Y)); break;
			SUMMON("MOBOBSIDIANCONCLAVEKNIGHT", FROM_NPC(rnd.roll(dice(1, 5))-2,X), FROM_NPC(rnd.roll(dice(1, 5))-2,Y)); break;
		default: break;
		}
	}
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}

void MOBMordred::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	if( target != NULL )
	{
	IF(CheckFlag(__FLAG_ADDON_SERAPH_ARMOR_QUEST) == 1)
		SHOUT(INTL( 12420, "AAAAAARRRH... I hate all you winged freaks! Urrh..."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 12421, "You find a small iron key on Mordred's corpse."))
		GiveItem(__OBJ_MORDRED_KEY)
		GiveFlag(__FLAG_ADDON_SERAPH_ARMOR_QUEST, 2)
	ENDIF

	}
	CLOSE_HANDLER
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}