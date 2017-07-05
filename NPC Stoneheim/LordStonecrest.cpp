#pragma hdrstop
#include "LordStonecrest.h"

LordStonecrest::LordStonecrest()
{}

LordStonecrest::~LordStonecrest()
{}

extern NPCstructure::NPC LordStonecrestNPC;

void LordStonecrest::Create(){
   npc = LordStonecrestNPC;
   SET_NPC_NAME( "[10872]Lord Stonecrest" );
   npc.InitialPos.X = 0;
   npc.InitialPos.Y = 0;
   npc.InitialPos.world = 0;
}

void LordStonecrest::OnAttack( UNIT_FUNC_PROTOTYPE )
{  
	switch(rnd(0, 15))	 
	{		
		case 0:
			SHOUT(INTL( 9361, "Guards! Dispose of this wretch!"));
			SUMMON("Skeleton Warder", FROM_NPC(rnd.roll(dice(1, 5))-3,X), FROM_NPC(rnd.roll(dice(1, 5))-3,Y)); break;
			SUMMON("Skeleton Warder", FROM_NPC(rnd.roll(dice(1, 5))-2,X), FROM_NPC(rnd.roll(dice(1, 5))-2,Y)); break;
		default: break;
	}
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}

void LordStonecrest::OnDeath( UNIT_FUNC_PROTOTYPE )
{ 
    INIT_HANDLER
	if( target != NULL )
	{
		GiveFlag(__FLAG_USER_HAS_KILLED_LORD_STONECREST, CheckFlag(__FLAG_USER_HAS_KILLED_LORD_STONECREST) + 1)
		IF(CheckItem(__OBJ_BLUESTONE_TALISMAN) == 0)
			GiveItem(__OBJ_BLUESTONE_TALISMAN)
		ENDIF
	}
    CLOSE_HANDLER
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );
}

void LordStonecrest::OnPopup( UNIT_FUNC_PROTOTYPE )
{
	SHOUT(INTL( 9362, "Who dares disturb my sleep? I shall squash you like the fly that you are!"));
 
SimpleMonster::OnPopup( UNIT_FUNC_PARAM );
}