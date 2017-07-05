// DrainLife.cpp: implementation of the DrainLife class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "DrainLife.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

REGISTER_SPELL_EFFECT( DRAIN_LIFE, DrainLife::NewFunc, DRAIN_LIFE_EFFECT, NULL );

//////////////////////////////////////////////////////////////////////////////////////////
BOOL DrainLife::InputParameter
//////////////////////////////////////////////////////////////////////////////////////////
//  Inputs parameters into DrainLife. This adds a third parameter to drain life.
// 
(
 CString csParam,   // Parameter
 WORD wParamID      // Parameter ID.
)
// Return: BOOL, TRUE if the parameter was OK
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( wParamID == 3 ){
        BOOL boParamOK = TRUE;

        // If the given formula isn't valid
        if( !cDamageModifier.SetFormula( csParam ) ){
            // Invalidate parameter.
            boParamOK = FALSE;
        }

        return boParamOK;
    }
    // If this wasn't a drain life specific parameter.
    else{
        switch( wParamID ){
        case 4:
            return HealthEffect::InputParameter( csParam, 3 );
        }

        // Then it must be a health effect parameter.
        return HealthEffect::InputParameter( csParam, wParamID );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void DrainLife::CallEffect
//////////////////////////////////////////////////////////////////////////////////////////
// When a drain life effect is called.
// 
(
 SPELL_EFFECT_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Deal health effect and collect the total damage done.
    int nTotalDamage = DealHealthEffect( SPELL_EFFECT_PARAMS );

    // Modify the received total damage by the damage modifier.
    nTotalDamage = (int)( ( (double)nTotalDamage * cDamageModifier.GetBoost( self ) ) / 100 );
    
    TRACE( "\r\nnTotalDamage=%u.", nTotalDamage );

    // If there was more damage than healing.
    if( nTotalDamage < 0 ){        
        // Heal caster with the damage done.
        DoUnitHealing( self, self, lpSpell, -nTotalDamage );
    }else{
        // Damage caster with the health given.
        DoUnitDamage ( self, self, lpSpell, -nTotalDamage );
    }

}

//////////////////////////////////////////////////////////////////////////////////////////
SpellEffect *DrainLife::NewFunc
//////////////////////////////////////////////////////////////////////////////////////////
// When an instance of a drain life effect is required.
// 
(
 LPSPELL_STRUCT lpSpell // The spell structure to register effect to.
)
// Return: SpellEffect, the spell effect instance.
//////////////////////////////////////////////////////////////////////////////////////////
{
    CREATE_EFFECT_HANDLE( DrainLife, 0 );
}