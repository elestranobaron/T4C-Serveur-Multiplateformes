// DispellEffect.cpp: implementation of the DispellEffect class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "DispellEffect.h"
#include "../WorldMap.h"
#include "../tfc_main.h"
#include "../Broadcast.h"
#include "../Game_Rules.h"
#include "../format.h"
#include "../Character.h"
#include "../T4CLog.h"
#include <math.h>
#include <list>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

REGISTER_SPELL_EFFECT( DISPELLEFFECT, DispellEffect::NewFunc, DISPELL_EFFECT, NULL );

//////////////////////////////////////////////////////////////////////////////////////////
BOOL DispellEffect::InputParameter
//////////////////////////////////////////////////////////////////////////////////////////
//  Parameters are inputed to the dispell effect.
// 
(
 CString csParam,   // The parameter value.
 WORD wParamID      // The parameter ID.
)
// Return: BOOL, TRUE if the parameter is valid.
//////////////////////////////////////////////////////////////////////////////////////////
{


	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
    const INT TargetSpellID = 1;
    const INT SuccessPercentage = 2;
    


    switch( wParamID ){
    case TargetSpellID:
        targetSpellID = atoi( csParam );

        if( targetSpellID == 0 ){
            return FALSE;
        }
        break;
    case SuccessPercentage:
        if( !successPercentage.SetFormula( csParam ) ){
            return FALSE;
        }

        break;
    default:
        return FALSE;
    }
    return TRUE;
}
 

//////////////////////////////////////////////////////////////////////////////////////////
void DispellEffect::Dispell
//////////////////////////////////////////////////////////////////////////////////////////
//  Dispell's the given unit
// 
(
 Unit *caster,
 Unit *target // The dispell target.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Get the target's effects
    TemplateList<UNIT_EFFECT>*effectList = target->GetAllEffects();

    if( effectList == NULL ){
        return;
    }

    list< UNIT_EFFECT * > dispellList;
    
    effectList->Lock();

    effectList->ToHead();
    while( effectList->QueryNext() ){
        UNIT_EFFECT *effect = effectList->Object();

        // If the spell ID was found
        if( effect->bindedSpellID == targetSpellID ){
            // Send a dispell message to the effect
            dispellList.push_back( effect );
        }        
    }

    effectList->Unlock();

    list< UNIT_EFFECT * >::iterator i;
    for( i = dispellList.begin(); i != dispellList.end(); i++ ){
        // Send a dispell message to the effect.
        (*i)->lpFunc( MSG_OnDispell, (*i)->dwEffect, target, NULL, caster, (*i)->lpData, NULL );
    }

    
}

//////////////////////////////////////////////////////////////////////////////////////////
void DispellEffect::CallEffect
//////////////////////////////////////////////////////////////////////////////////////////
//  Called when the effect is triggered by the binded spell.
// 
(
 SPELL_EFFECT_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Target required.
    if( self == NULL ){
        return;
    }

    static Random rnd;
    
    // If there is a unit in center.
    if( target == NULL ){
        // Require a target.
        return;
    }

    // If the spell succesfully caught the target.
    if( rnd( 1, 100 ) < successPercentage.GetBoost( self, target, 0, 0, range ) ){
        Dispell( self, target );    
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
SpellEffect *DispellEffect::NewFunc
//////////////////////////////////////////////////////////////////////////////////////////
// Returns an instance of a spell effect.
// 
(
 LPSPELL_STRUCT lpSpell
)
// Return: static SpellEffect, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    CREATE_EFFECT_HANDLE( DispellEffect, 0 );
}
