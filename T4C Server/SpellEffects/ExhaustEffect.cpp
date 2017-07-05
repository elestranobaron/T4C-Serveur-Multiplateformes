// ExhaustEffect.cpp: implementation of the ExhaustEffect class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop

#include "stdafx.h"
#include "ExhaustEffect.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExhaustEffect::ExhaustEffect()
{

}

ExhaustEffect::~ExhaustEffect()
{

}

REGISTER_SPELL_EFFECT( EXHAUST_EFFECT_INSTANCE, ExhaustEffect::NewFunc, EXHAUST_EFFECT, NULL );

//////////////////////////////////////////////////////////////////////////////////////////
BOOL ExhaustEffect::InputParameter
//////////////////////////////////////////////////////////////////////////////////////////
//  Adds parameters to the exhaust effect.
// 
(
 CString csParam,   // The parameter value.
 WORD wParamID
)
// Return: BOOL, TRUE if the parameter was valid.
//////////////////////////////////////////////////////////////////////////////////////////
{


	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
    const INT Attack = 1;
    const INT Mental = 2;
    const INT Move   = 3;
    const INT Success = 4;



    switch( wParamID ){
    case Attack:
        if( !attackExhaust.SetFormula( csParam ) ){
            return FALSE;
        }
        break;
    case Mental:
        if( !mentalExhaust.SetFormula( csParam ) ){
            return FALSE;
        }
        break;
    case Move:
        if( !moveExhaust.SetFormula( csParam ) ){
            return FALSE;
        }
        break;
    case Success:
        if( !successPercent.SetFormula( csParam ) ){
            return FALSE;
        }
        break;
    default:
        return FALSE;
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void ExhaustEffect::CallEffect
//////////////////////////////////////////////////////////////////////////////////////////
//  Deals the exhaust to the target unit.
// 
(
 SPELL_EFFECT_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( target == NULL ){
        return;
    }

    static Random rnd;
    if( rnd( 1, 100 ) > successPercent.GetBoost( self, target, 0, 0, range ) ){
        return;
    }

    DWORD theAttackExhaust = attackExhaust.GetBoost( self, target, 0, 0, range );
    DWORD theMentalExhaust = mentalExhaust.GetBoost( self, target, 0, 0, range );
    DWORD theMoveExhaust   = moveExhaust.GetBoost( self, target, 0, 0, range );
    
    target->DealExhaust(
        theAttackExhaust,
        theMentalExhaust,
        theMoveExhaust
    );
    
    DWORD maxExhaust = theAttackExhaust;
    if( theMentalExhaust > maxExhaust ){
        maxExhaust = theMentalExhaust;
    }
    if( theMoveExhaust > maxExhaust ){
        maxExhaust = theMoveExhaust;
    }

    // Create an effect status update for the client.
    CreateEffectStatus(
        target,
        lpSpell->wSpellID,
        maxExhaust,
        maxExhaust,
        lpSpell
    );
}

//////////////////////////////////////////////////////////////////////////////////////////
SpellEffect *ExhaustEffect::NewFunc
//////////////////////////////////////////////////////////////////////////////////////////
//  Creates an instance of the exhaust effect.
// 
(
 LPSPELL_STRUCT lpSpell
)
// Return: static SpellEffect, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    CREATE_EFFECT_HANDLE( ExhaustEffect, 0 );
}