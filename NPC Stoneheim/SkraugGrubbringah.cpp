#pragma hdrstop
#include "SkraugGrubbringah.h"

SkraugGrubbringah::SkraugGrubbringah()
{}

SkraugGrubbringah::~SkraugGrubbringah()
{}

extern NPCstructure::NPC SkraugGrubbringahNPC;

void SkraugGrubbringah::Create(){
   npc = SkraugGrubbringahNPC;
   SET_NPC_NAME( "[10920]Skraug grubbringah" );
   npc.InitialPos.X = 0; 
   npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}									 

void SkraugGrubbringah::OnAttack( UNIT_FUNC_PROTOTYPE )
{  
	switch(rnd(0, 40))	 
	{		
		case 0: SHOUT(INTL( 8499, "Yaaaaagh! Yew DIE!")); break;
		case 1: SHOUT(INTL( 8500, "Oy will skewer yew, weakling!")); break;
		case 2: SHOUT(INTL( 8501, "Yew die now!")); break;
		case 3: SHOUT(INTL( 8502, "Oy me SMASH yewr skull now, I eat yew later!")); break;
		case 4: SHOUT(INTL( 8503, "Yew not stand chance 'gainst moy strength! Oogh!")); break;
		case 5: SHOUT(INTL( 8504, "KILL! KILL! OY KILL YEW!")); break;
		case 6: SHOUT(INTL( 8505, "Oy feed moy kids wit yewr corpse!")); break;
		case 7: SHOUT(INTL( 8506, "Yew stop runnin'! Me want t'feenish yew quick!")); break;
		case 8: SHOUT(INTL( 8507, "Me gonna BARSH yew guuud!")); break;
		case 9: SHOUT(INTL( 8508, "Yur no match fer me!")); break;
		default: break;
	}
SimpleMonster::OnAttack( UNIT_FUNC_PARAM );
}


void SkraugGrubbringah::OnAttacked( UNIT_FUNC_PROTOTYPE )
{ 
	switch(rnd(0, 40))	 
	{
		case 0: SHOUT(INTL( 8509, "Dis not hurt me!")); break;
		case 1: SHOUT(INTL( 8510, "Oy not feel pain!")); break;
		case 2: SHOUT(INTL( 8511, "Hummies no match for Skraug.")); break;
		case 3: SHOUT(INTL( 8512, "Me like dis! Dis fun battle!")); break;
		case 4: SHOUT(INTL( 8513, "Yew not much hurt me! Try it 'gain.")); break;
		case 5: SHOUT(INTL( 8514, "Oy not impress'd! Do better! Hit harder!")); break;
		case 6: SHOUT(INTL( 8515, "Much swinging, little hurting.")); break;
		case 7: SHOUT(INTL( 8516, "Izzat all yew can dew?")); break;
		default: break;
	}

SimpleMonster::OnAttacked( UNIT_FUNC_PARAM );
}

void SkraugGrubbringah::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	switch(rnd(0, 40))	 
	{	
		case 0: SHOUT(INTL( 8517, "Og! Dat wuz fun! Oy dye guud death!")); break;
		case 1: SHOUT(INTL( 8518, "Oy is dead! Da Big Skraug in da Erth vait fo me.")); break;
		case 2: SHOUT(INTL( 8519, "Me see guud brite light... Arck...")); break;
		case 3: SHOUT(INTL( 8520, "Agh! Oy die merry and bloody!")); break;
		case 4: SHOUT(INTL( 8521, "Oy call fer revenge! My brudder will keel yu!")); break;
		case 5: SHOUT(INTL( 8522, "ARGH! Me go join me fodder in da ground.")); break;
		case 6: SHOUT(INTL( 8523, "Dis wuz guud battle. Yew get tew feed on moy entrails.")); break;
		case 7: SHOUT(INTL( 8524, "Oy die so young, und oy hod so much leff tew dew.")); break;
		case 8: SHOUT(INTL( 8525, "Argh! Me gut BARSH baadd....")); break;
		default: break; 
	 }	
SimpleMonster::OnDeath( UNIT_FUNC_PARAM );	 
}




