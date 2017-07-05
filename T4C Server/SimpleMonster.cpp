// SimpleMonster.cpp: implementation of the SimpleMonster class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SimpleMonster.h"
#include "StatModifierFlagsListing.h"
#include "Objects.h"
#include "BlockingListing.h"
#include "T4CLog.h"
#include "IntlText.h"
#include "format.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const int _PHYSICAL = 0;
const int _SPELL	= 1;

SimpleMonster::SimpleMonster(){	
	npc.block = 1;
	npc.wUndead = 0;
}

void SimpleMonster::Create(){	
}

SimpleMonster::~SimpleMonster(){
	TRACE("here\r\n");
}

//////////////////////////////////////////////////////////////////////////////////////////
void SimpleMonster::OnInitialise
//////////////////////////////////////////////////////////////////////////////////////////
// Initialises a simple monster
// 
(
 UNIT_FUNC_PROTOTYPE // self/medium etc
)
//////////////////////////////////////////////////////////////////////////////////////////
{
//	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
//	self->AddFlag(__FLAG_HP, npc.HP);
//	self->SetStaticFlagsReference(this);
	self->SetMaxHP(npc.HP);
	self->SetHP( npc.HP, false );
	self->SetDODGE( npc.DodgeSkill );
	self->SetATTACK( 0 );
	self->SetFlag(__FLAG_BLOCKING, npc.block );
	self->SetTarget(NULL);
	self->SetSpeed(npc.speed);
	self->SetAgressivness(npc.agressive);
	self->SetClan(npc.clan);
	self->SetCorpse(npc.Corpse);
	self->SetAppearance(npc.appearance);
//	self->SetName(npc.name);
    self->SetAttack( npc.boCanAttack );

	self->SetINT( npc.INT );
	self->SetEND( npc.END );
	self->SetSTR( npc.STR );
	self->SetWIS( npc.WIS );
	self->SetAGI( npc.AGI );

    self->SetBlock( __BLOCK_CAN_FLY_OVER );

	WorldPos wlDest = { -1, -1, -1 };
	self->SetDestination( wlDest );
	self->SetUpperLimit( wlDest );
	self->SetLowerLimit( wlDest );

	self->SetSystemDestroy( TRUE );	// Monsters should be cleaned if not used.
	self->SetUndead( npc.wUndead );

    self->SetLevel( npc.level );

	self->Do( wandering );

    if( npc.FireResist  != 0 ){ self->SetFireResist ( npc.FireResist ); }
    if( npc.WaterResist != 0 ){ self->SetWaterResist( npc.WaterResist ); }
    if( npc.AirResist   != 0 ){ self->SetAirResist  ( npc.AirResist ); }
    if( npc.EarthResist != 0 ){ self->SetEarthResist( npc.EarthResist ); }
    if( npc.LightResist != 0 ){ self->SetLightResist( npc.LightResist ); }
    if( npc.DarkResist  != 0 ){ self->SetDarkResist ( npc.DarkResist  ); }

    if( npc.FirePower  != 0 ){ self->SetFirePower ( npc.FirePower ); }
    if( npc.WaterPower != 0 ){ self->SetWaterPower( npc.WaterPower ); }
    if( npc.AirPower   != 0 ){ self->SetAirPower  ( npc.AirPower ); }
    if( npc.EarthPower != 0 ){ self->SetEarthPower( npc.EarthPower ); }
    if( npc.LightPower != 0 ){ self->SetLightPower( npc.LightPower ); }    
    if( npc.DarkPower  != 0 ){ self->SetDarkPower( npc.DarkPower ); }
}

//////////////////////////////////////////////////////////////////////////////////////////
void SimpleMonster::OnPopup
//////////////////////////////////////////////////////////////////////////////////////////
// Called when monster is summoned
// 
(
 UNIT_FUNC_PROTOTYPE // prototype
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	//BOOL *boValidate = (BOOL *)valueOUT;
	
	//*boValidate = TRUE;

	EXHAUST newExhaust = {0,0,0};
	self->SetExhaust(newExhaust);

	// Default behavior
	self->Do(wandering);								
	WorldPos pos = {-1, -1, -1};	
	self->SetDestination( pos );
	
	// Night only creatures do not appear at daytime ;)
	//if( npc.creature & _NIGHT_ONLY && TFCTime::IsDay() )
	//	*boValidate = FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////
MonsterStructure *SimpleMonster::GetMonsterStructure( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the monster structure of a monster
// 
// Return: MonsterStructure, The monster structure
//////////////////////////////////////////////////////////////////////////////////////////
{
	return &npc;
}

//////////////////////////////////////////////////////////////////////////////////////////
void SimpleMonster::OnServerInitialisation
//////////////////////////////////////////////////////////////////////////////////////////
// Override server initialisation.
// 
(
 UNIT_FUNC_PROTOTYPE,
 WORD wBaseReferenceID
)
//////////////////////////////////////////////////////////////////////////////////////////
{
}