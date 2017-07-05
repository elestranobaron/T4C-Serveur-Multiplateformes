// Invisibility.cpp: implementation of the Invisibility class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Invisibility.h"
#include "../TFC_MAIN.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

REGISTER_SPELL_EFFECT( INVIS, Invisibility::NewFunc, INVISIBILITY_EFFECT, NULL );


Invisibility::Invisibility()
{

}

Invisibility::~Invisibility()
{

}

namespace{
struct InvisEFFECT{
    DWORD popupEffect;
    DWORD effectID;
    DWORD spellID;
};
};


//////////////////////////////////////////////////////////////////////////////////////////
BOOL Invisibility::InputParameter
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
 CString csParam, // 
 WORD wParamID // 
)
// Return: BOOL, 
//////////////////////////////////////////////////////////////////////////////////////////
{


	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
    const INT Success = 1;
    const INT PopupEffect = 2;



    switch( wParamID ){
    case Success:
        if( !successPercentage.SetFormula( csParam ) ){
            return FALSE;
        }
        break;
    case PopupEffect:
        popupVisualEffect = atoi( csParam );
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Invisibility::BroadcastInvisibility
//////////////////////////////////////////////////////////////////////////////////////////
//  Broadcasts invisibility to all players without detect invisible
// 
(
 Unit *self // The invisibility caster.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    WorldMap *wl = TFCMAIN::GetWorld( self->GetWL().world );

    if( wl == NULL ){
        return;
    }

    // Get all units within the default range.
    TemplateList< Unit > *unitList = wl->GetLocalUnits( self->GetWL(), _DEFAULT_RANGE, FALSE );//BLBLBL 30=>_DEFAULT_RANGE

    if( unitList == NULL ){
        return;
    }
    
    unitList->ToHead();
    while( unitList->QueryNext() ){
        Unit *un = unitList->Object();

        // If the unit does not have detect invisible.
        if( un->ViewFlag( __FLAG_DETECT_INVISIBILITY ) == 0 ){
            // Make it dissappear.
            TFCPacket sending;
            // Make the player dissappear
		    sending << (RQ_SIZE)__EVENT_OBJECT_REMOVED;
            sending << (char)0;
		    sending << (long)self->GetID();

            un->SendPlayerMessage( sending );
        }
    }

    delete unitList;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Invisibility::InvisibilityRemoval
//////////////////////////////////////////////////////////////////////////////////////////
// Called when timer expires and flag must be removed.
// 
(
 EFFECT_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	// Timer make the call to the function.
	if( wMessageID == MSG_OnTimer ){
        InvisEFFECT *invisEffect = (InvisEFFECT *)lpEffectData;

        // Remove invisibility
        self->RemoveFlag( __FLAG_INVISIBILITY );
        
        WorldPos wlPos = self->GetWL();

        DispellEffectStatus( self, invisEffect->spellID );

        // Display the popup        
        self->BroadcastPopup( wlPos );

        if( invisEffect->popupEffect != 0 ){
            Broadcast::BCSpellEffect( wlPos, _DEFAULT_RANGE,//BLBLBL 30=>_DEFAULT_RANGE
                invisEffect->popupEffect,
                self->GetID(),
                self->GetID(),
                wlPos,
                wlPos,
                GetNextGlobalEffectID(),
                0
            );
        }
    }else
    // If the spell got dispelled
    if( wMessageID == MSG_OnDispell ){
        InvisEFFECT *invisEffect = (InvisEFFECT *)lpEffectData;

        // Remove invisibility
        self->RemoveFlag( __FLAG_INVISIBILITY );

        DispellEffectStatus( self, invisEffect->spellID );

        WorldPos wlPos = self->GetWL();

        // Display the popup
        self->BroadcastPopup( wlPos );

        if( invisEffect->popupEffect != 0 ){
            Broadcast::BCSpellEffect( wlPos, _DEFAULT_RANGE,//BLBLBL 30=>_DEFAULT_RANGE
                invisEffect->popupEffect,
                self->GetID(),
                self->GetID(),
                wlPos,
                wlPos,
                GetNextGlobalEffectID(),
                0
            );
        }

        // Remove the effect.
        self->RemoveEffect( dwEffect );        
    }else
    // Player exited
    if( wMessageID == MSG_OnSavePlayer ){
        // Fetch the pointers
        InvisEFFECT *invisEffect = (InvisEFFECT *)lpEffectData;
		LPDATA_SAVE lpDataSave = (LPDATA_SAVE)lpUserData;
		// Prepare buffer to save on player
        lpDataSave->bBufferSize = sizeof( InvisEFFECT );
        lpDataSave->lpbData = new BYTE[ sizeof( InvisEFFECT ) ];        
        memcpy( lpDataSave->lpbData, invisEffect, sizeof( InvisEFFECT ) );        
    }else
    // Player loads
    if( wMessageID == MSG_OnLoadPlayer ){
        LPUNIT_EFFECT lpUnitEffect = (LPUNIT_EFFECT)lpEffectData;
        LPDATA_SAVE lpDataSave = (LPDATA_SAVE)lpUserData;

        InvisEFFECT *invisEFFECT = new InvisEFFECT;

        // Fetch the LPFLAG_ADDING;
        if( lpDataSave->bBufferSize == sizeof( InvisEFFECT ) ){
            memcpy( invisEFFECT, lpDataSave->lpbData, sizeof( InvisEFFECT ) );
            // Get the spell
            LPSPELL_STRUCT lpSpell = SpellMessageHandler::GetSpell( invisEFFECT->spellID );

            if( lpSpell != NULL ){
                // Create an effect status update for the client.
                CreateEffectStatus(
                    self,
                    invisEFFECT->spellID,
                    lpUnitEffect->dwTotalDuration == 0xFFFFFFFF ? 0xFFFFFFFF : ( lpUnitEffect->dwTimer - TFCMAIN::GetRound() ) * 50,
                    lpUnitEffect->dwTotalDuration,
                    lpSpell
                );
            }
        }

        // Attach the flag adding structure to the effect.
        lpUnitEffect->lpData = invisEFFECT;
    }else
    // Effect is getting destroyed.
    if( wMessageID == MSG_OnDestroy ){
        // Delete the AddFlag structure associated to the effect.
        InvisEFFECT *invisEffect = (InvisEFFECT *)lpEffectData;
        delete invisEffect;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void Invisibility::CallEffect
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
 SPELL_EFFECT_PROTOTYPE // 
)
//////////////////////////////////////////////////////////////////////////////////////////
{

    if( target == NULL ){
        return;
    }

    // If the spell fails.
    static Random rnd;
    if( rnd( 1, 100 ) >= successPercentage.GetBoost( self, target, 0, 0, range ) ){
        return;
    }
    // Get duration now.
    DWORD dwDuration = lpSpell->bfDuration.GetBoost( self, target );
    if( dwDuration == 0 ){
        return;
    }
        
    // Remove the previous effect
    target->RemoveEffect( dwEffectID );
    
    // Add the invisibility flag
    target->SetFlag( __FLAG_INVISIBILITY, 1 );


    BroadcastInvisibility( target );

    // Setup the add flag
    InvisEFFECT *invisEffect = new InvisEFFECT;
    invisEffect->popupEffect = popupVisualEffect;
    invisEffect->spellID = lpSpell->wSpellID;
    invisEffect->effectID = dwEffectID;

    // Create an effect status update for the client.
    CreateEffectStatus(
        target,
        lpSpell->wSpellID,
        dwDuration,
        dwDuration,
        lpSpell
    );


    CREATE_EFFECT(
        target,
        MSG_OnTimer,
        dwEffectID,
        InvisibilityRemoval,
        invisEffect,
        dwDuration MILLISECONDS TDELAY,
        dwDuration,
        lpSpell->wSpellID,
        __FLAG_INVISIBILITY
    );
}

//////////////////////////////////////////////////////////////////////////////////////////
SpellEffect *Invisibility::NewFunc
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
 LPSPELL_STRUCT lpSpell // 
)
// Return: static SpellEffect, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    REGISTER_EFFECT( lpSpell->dwNextEffectID, InvisibilityRemoval );

    CREATE_EFFECT_HANDLE( Invisibility, 1 )
}
