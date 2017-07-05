#pragma hdrstop
#include "MakrshPtangh2.h"

MakrshPtangh2::MakrshPtangh2()
{}

MakrshPtangh2::~MakrshPtangh2()
{}

extern NPCstructure::NPC MakrshPtangh2NPC;

void MakrshPtangh2::Create(){
   npc = MakrshPtangh2NPC;
   SET_NPC_NAME( "[11524]Makrsh P'Tangh" );
   npc.InitialPos.X = 0;
   npc.InitialPos.Y = 0;
   npc.InitialPos.world = 0;
}

void MakrshPtangh2::OnAttack( UNIT_FUNC_PROTOTYPE )
{
	switch(rnd(0, 29)) //BLBLBL 05/01/2011 reduced number of sents
	{
		case 0: SHOUT(INTL( 11375, "You think you can stop me?")); break;
		case 1:
			SHOUT(INTL(  11642, "Servants of chaos, attack!"));
			SUMMON("Undead Guardian", FROM_NPC(rnd.roll(dice(1, 5))-3,X), FROM_NPC(rnd.roll(dice(1, 5))-3,Y));
			SUMMON("Undead Sentinel", FROM_NPC(rnd.roll(dice(1, 5))-2,X), FROM_NPC(rnd.roll(dice(1, 5))-2,Y));
            break;
		default: break;
	}

NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void MakrshPtangh2::OnAttacked( UNIT_FUNC_PROTOTYPE )
{ 
	switch(rnd(0, 39))//BLBLBL 05/01/2011 reduced number of sents
	{
		case 0: SHOUT(INTL( 9211, "Do you really think your weak attacks will hurt me?")); break;
		case 1:
			SHOUT(INTL(  11642, "Servants of chaos, attack!"));
			SUMMON("Undead Guardian", FROM_NPC(rnd.roll(dice(1, 5))-3,X), FROM_NPC(rnd.roll(dice(1, 5))-3,Y));
			SUMMON("Undead Sentinel", FROM_NPC(rnd.roll(dice(1, 5))-2,X), FROM_NPC(rnd.roll(dice(1, 5))-2,Y));
            break;
		default: break;
	}

NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void MakrshPtangh2::OnDeath( UNIT_FUNC_PROTOTYPE )
{
if( target != NULL )
	{
		IF(CheckFlag(__FLAG_USER_HAS_KILLED_MAKRSH_PTANGH) == 2)
			GiveFlag(__FLAG_USER_HAS_KILLED_MAKRSH_PTANGH, 3);
		ELSE
			GiveFlag(__FLAG_USER_HAS_KILLED_MAKRSH_PTANGH, 1);
		ENDIF
	}
	GiveGlobalFlag(__GLOBAL_FLAG_MAKRSH_PTANGH_IS_FIGHTING, 1);

	//GLOBAL_SYSTEM_MESSAGE( "The fog suddently disappeared, the sun is now shinning back." );

NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void MakrshPtangh2::OnDestroy( UNIT_FUNC_PROTOTYPE )
{

	GiveGlobalFlag(__GLOBAL_FLAG_MAKRSH_PTANGH_IS_FIGHTING, 1);
	GiveGlobalFlag(__GLOBAL_FLAG_MAKRSH_PTANGH_DEAD_TIMER, CurrentRound);

NPCstructure::OnDestroy( UNIT_FUNC_PARAM );
}