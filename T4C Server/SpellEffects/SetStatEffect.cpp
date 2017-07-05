// SetStatEffect.cpp: implementation of the SetStatEffect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SetStatEffect.h"
#include "..\Broadcast.h"

#define ISEQUAL( a ) csParam.CompareNoCase( a ) == 0
#define GETSETVAL cSetVal.GetBoost( self, target, 0, 0, range )
#define _DEFAULT_RANGE				40 //BLBL ne sert que pour le ChangeAppearance (mettre même valeur que dans le _DEFAULT_RANGE normal)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SetStatEffect::SetStatEffect()
{

}

SetStatEffect::~SetStatEffect()
{

}

REGISTER_SPELL_EFFECT( SETSTAT, SetStatEffect::NewFunc, SETSTAT_EFFECT, NULL );

//////////////////////////////////////////////////////////////////////////////////////////
BOOL SetStatEffect::InputParameter
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
 CString csParam,   // Parameter value.
 WORD wParamID      // Parameter ID.
)
// Return: BOOL, TRUE if parameter was accepted.
//////////////////////////////////////////////////////////////////////////////////////////
{

	BOOL boReturn = TRUE;

	//


	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de BOOL
	//////////////////////////////////////////////////////////////////////////////////////////
	const BOOL StatToSet = 1;
	const BOOL SetValue = 2;
	const BOOL Success = 3;



	switch( wParamID )
	{
	case StatToSet:
		if( ISEQUAL( "strength" ) )
			wSetType = STR;
		else if( ISEQUAL( "endurance" ) )
			wSetType = END;
		else if( ISEQUAL( "agility" ) )
			wSetType = AGI;
		else if( ISEQUAL( "wisdom" ) )
			wSetType = WIS;
		else if( ISEQUAL( "intelligence" ) )
			wSetType = INT;
		else if( ISEQUAL( "appearance" ) )
			wSetType = APPEARANCE;
		else if( ISEQUAL( "air" ) )
			wSetType = AIR_POWER;
		else if( ISEQUAL( "dark" ) )
			wSetType = DARK_POWER;
		else if( ISEQUAL( "earth" ) )
			wSetType = EARTH_POWER;
		else if( ISEQUAL( "fire" ) )
			wSetType = FIRE_POWER;
		else if( ISEQUAL( "light" ) )
			wSetType = LIGHT_POWER;
		else if( ISEQUAL( "water" ) )
			wSetType = WATER_POWER;
		else if( ISEQUAL( "air resist" ) )
			wSetType = AIR_RESIST;
		else if( ISEQUAL( "dark resist" ) )
			wSetType = DARK_RESIST;
		else if( ISEQUAL( "earth resist" ) )
			wSetType = EARTH_RESIST;
		else if( ISEQUAL( "fire resist" ) )
			wSetType = FIRE_RESIST;
		else if( ISEQUAL( "light resist" ) )
			wSetType = LIGHT_RESIST;
		else if( ISEQUAL( "water resist" ) )
			wSetType = WATER_RESIST;
		else
			wSetType = 0;//BLBLBLBL 0 au lieu de -1
		break;
	case SetValue:
		if(!cSetVal.SetFormula(csParam))
			boReturn = FALSE;
		break;
	case Success:
		if( !successPercent.SetFormula(csParam) )
			boReturn = FALSE;
		break;
	}
	
	return boReturn;
}

//////////////////////////////////////////////////////////////////////////////////////////
void SetStatEffect::CallEffect
//////////////////////////////////////////////////////////////////////////////////////////
// Take or give an item
// 
(
 SPELL_EFFECT_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	static Random rnd;

	if ( rnd(1, 100) >= successPercent.GetBoost( self, target, 0, 0, range ) ) {
		return;
	} else {
		CString csLogTxt;
		csLogTxt = "SetStat Effect called. ";
		csLogTxt += self->GetName( _DEFAULT_LNG );
		csLogTxt += " setted ";
		csLogTxt += target->GetName( _DEFAULT_LNG );
		csLogTxt += "'s ";

		switch( wSetType )
		{
		case STR:
			target->SetSTR( GETSETVAL );
			csLogTxt += "strength";
			break;
		case END:
			target->SetEND( GETSETVAL );
			csLogTxt += "endurance";
			break;
		case AGI:
			target->SetAGI( GETSETVAL );
			csLogTxt += "agility";
			break;
		case WIS:
			target->SetWIS( GETSETVAL );
			csLogTxt += "wisdom";
			break;
		case INT:
			target->SetINT( GETSETVAL );
			csLogTxt += "intelligence";
			break;
		case APPEARANCE:
			target->SetAppearance( GETSETVAL );
			Broadcast::BCObjectChanged( target->GetWL(), _DEFAULT_RANGE,
				target->GetAppearance(),
				target->GetID()
				);
			csLogTxt += "appearance";
			break;
		case AIR_POWER:
			target->SetAirPower( GETSETVAL );
			csLogTxt += "air";
			break;
		case DARK_POWER:
			target->SetDarkPower( GETSETVAL );
			csLogTxt += "dark";
			break;
		case EARTH_POWER:
			target->SetEarthPower( GETSETVAL );
			csLogTxt += "earth";
			break;
		case FIRE_POWER:
			target->SetFirePower( GETSETVAL );
			csLogTxt += "fire";
			break;
		case LIGHT_POWER:
			target->SetLightPower( GETSETVAL );
			csLogTxt += "air";
			break;
		case WATER_POWER:
			target->SetWaterPower( GETSETVAL );
			csLogTxt += "water";
			break;
		case AIR_RESIST:
			target->SetAirResist( GETSETVAL );
			csLogTxt += "air resist";
			break;
		case DARK_RESIST:
			target->SetDarkResist( GETSETVAL );
			csLogTxt += "dark resist";
			break;
		case EARTH_RESIST:
			target->SetEarthResist( GETSETVAL );
			csLogTxt += "earth resist";
			break;
		case FIRE_RESIST:
			target->SetFireResist( GETSETVAL );
			csLogTxt += "fire resist";
			break;
		case LIGHT_RESIST:
			target->SetLightResist( GETSETVAL );
			csLogTxt += "air resist";
			break;
		case WATER_RESIST:
			target->SetWaterResist( GETSETVAL );
			csLogTxt += "water resist";
			break;
		}

		csLogTxt += " to ";
		char buffer [33];
		ltoa(GETSETVAL,buffer,10);
		csLogTxt.Append(buffer);

		_LOG_GAMEOP
            LOG_SYSOP, 
            (char *)(LPCTSTR)csLogTxt 
        LOG_
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
SpellEffect *SetStatEffect::NewFunc
//////////////////////////////////////////////////////////////////////////////////////////
// Create a SpellEffect object.
// 
(
 LPSPELL_STRUCT lpSpell // The spell structure for any spell effect registration.
)
// Return: SpellEffect, the spell effect. 
//////////////////////////////////////////////////////////////////////////////////////////
{
  CREATE_EFFECT_HANDLE( SetStatEffect, 0 )
}