// SpellEffectManager.cpp: implementation of the SpellEffectManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "SpellEffectManager.h"
#include "IntlText.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

TemplateList < SpellEffectManager::REGISTERED_SUPERSTRUCTURE > SpellEffectManager::tlRegisteredEffects;

//////////////////////////////////////////////////////////////////////////////////////////
void SpellEffectManager::Destroy( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Destroys the spell effect manager.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    tlRegisteredEffects.AnnihilateList();
}
//////////////////////////////////////////////////////////////////////////////////////////
void SpellEffectManager::RegisterSuperstructure
//////////////////////////////////////////////////////////////////////////////////////////
// Registers a superstructure
// 
(
 LPNEW_FUNC lpFunc, // Functions which will return the handle to the specific object.
 WORD wID           // The ID of the effect superstructure to fetch
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    REGISTERED_SUPERSTRUCTURE *lpReg = new REGISTERED_SUPERSTRUCTURE;

    TRACE( "\r\nRegistering spell structure %u.", wID );

    lpReg->lpFunc = lpFunc;
    lpReg->wID    = wID;

    tlRegisteredEffects.AddToHead( lpReg );
}

//////////////////////////////////////////////////////////////////////////////////////////
SpellEffect *SpellEffectManager::GetEffectObject
//////////////////////////////////////////////////////////////////////////////////////////
// Returns an instance of the derived effect class.
// 
(
 WORD wID,                  // ID of the effect superstructure to fetch an object from.
 LPSPELL_STRUCT lpSpell     // Parent spell structure.
)
// Return: SpellEffect, The object of the wanted type. NULL if none registered.
//////////////////////////////////////////////////////////////////////////////////////////
{
    SpellEffect *lpEffect = NULL;

    tlRegisteredEffects.ToHead();

    while( tlRegisteredEffects.QueryNext() && lpEffect == NULL ){
        if( tlRegisteredEffects.Object()->wID == wID ){
            lpEffect = tlRegisteredEffects.Object()->lpFunc( lpSpell );
        }
    }

    return lpEffect;
}