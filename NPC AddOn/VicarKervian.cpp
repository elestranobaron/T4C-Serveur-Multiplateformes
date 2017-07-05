#pragma hdrstop
#include "VicarKervian.h"

VicarKervian::VicarKervian()
{}

VicarKervian::~VicarKervian()
{}

extern NPCstructure::NPC VicarKervianNPC;

void VicarKervian::Create(){
  npc = VicarKervianNPC;
  SET_NPC_NAME( "[12781]Vicar Kervian" );
  npc.InitialPos.X = 0;
  npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void VicarKervian::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	if( target != NULL )
	{

		
		IF ((CheckFlag(__FLAG_ADDON_CRYSTAL_KEY) == 0) && (CheckItem(__OBJ_CRYSTAL_KERVIAN)==0))
			SHOUT(INTL( 12677, "What? how is it possible? AAAAAARRRRRGH!"))
			PRIVATE_SYSTEM_MESSAGE(INTL( 12673, "As the vicar's body hits the floor, a small key-shaped crystal falls out of its hand."))
			PRIVATE_SYSTEM_MESSAGE(INTL( 12674, "You pick up the crystal key."))
			GiveItem(__OBJ_CRYSTAL_KERVIAN) 
		ENDIF	


	}
    CLOSE_HANDLER
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}
 
void VicarKervian::OnAttack( UNIT_FUNC_PROTOTYPE )
{
	switch(rnd(0, 20))
	{
		case 0: SHOUT(INTL( 12675, "You cannot kill what is already dead!")); break;
		case 1:
			SHOUT(INTL( 12676, "Servants of corruption, attack!"));
			SUMMON("Roaming Corpse", FROM_NPC(rnd.roll(dice(1, 5))-3,X), FROM_NPC(rnd.roll(dice(1, 5))-3,Y));
			SUMMON("Roaming Cadaver", FROM_NPC(rnd.roll(dice(1, 5))-2,X), FROM_NPC(rnd.roll(dice(1, 5))-2,Y));
            break;
		default: break;
	}

NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}