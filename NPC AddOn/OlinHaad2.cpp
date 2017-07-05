#pragma hdrstop
#include "OlinHaad2.h"

OlinHaad2::OlinHaad2()
{}

OlinHaad2::~OlinHaad2()
{}

extern NPCstructure::NPC OlinHaad2NPC;

void OlinHaad2::Create( ){
	npc = OlinHaad2NPC;
	SET_NPC_NAME( "[12758]Olin Haad");
	npc.InitialPos.X = 1180;
	npc.InitialPos.Y = 2710;
	npc.InitialPos.world = 1;
}

void OlinHaad2::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
		IF(USER_HP<USER_MAXHP/5)
			CastSpellTarget(__SPELL_OLIN_HAAD_TELEPORT_4)
			SHOUT(INTL( 12514, "You see? You cannot kill me!"))
			GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 37)
		ENDIF
		switch(rnd(0, 10))
			{		
			case 0: CastSpellSelf(__SPELL_MOB_MAX_REGEN); break;		
			default: break;
			}
	}
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}