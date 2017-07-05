#pragma hdrstop
#include "MOBMadBerserkerDemon.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MOBMadBerserkerDemon::MOBMadBerserkerDemon()
{}

MOBMadBerserkerDemon::~MOBMadBerserkerDemon()
{}
 
extern NPCstructure::NPC MOBMadBerserkerDemonNPC;

void MOBMadBerserkerDemon::Create( ){
   npc = MOBMadBerserkerDemonNPC;
   SET_NPC_NAME( "[10888]Mad berserker demon");
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0;
	npc.InitialPos.world = 0;
}

void MOBMadBerserkerDemon::OnPopup( UNIT_FUNC_PROTOTYPE )
{																	 
	
	CastSpellSelf(__SPELL_NPC_CANTRIP_PENTACLE) 	
	NPCstructure::OnPopup( UNIT_FUNC_PARAM );
}

void MOBMadBerserkerDemon::OnDeath( UNIT_FUNC_PROTOTYPE )
{	  
	if( target != NULL )
	{

	}
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}
 
void MOBMadBerserkerDemon::OnAttack( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
		switch(rnd(0, 20))	 
		{		
			case 0: SHOUT(INTL( 9326, "I love the taste of charred flesh!")); break;		
			case 1: SHOUT(INTL( 9327, "Not even your puny God can save you now!")); break;		
			default: break;
		}
   }
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}
