// DetectDetectInvisibility.cpp: implementation of the DetectDetectInvisibility class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "DetectInvisibility.h"
#include "../TFC_MAIN.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

REGISTER_SPELL_EFFECT( DEINVIS, DetectInvisibility::NewFunc, DETECT_INVISIBILITY_EFFECT, NULL );

DetectInvisibility::DetectInvisibility()
{

}

DetectInvisibility::~DetectInvisibility()
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
BOOL DetectInvisibility::InputParameter
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
    const INT PopoffVisual = 2;



    switch( wParamID ){
    case Success:
        if( !successPercentage.SetFormula( csParam ) ){
            return FALSE;
        }
        break;
    case PopoffVisual:
        popoffVisualEffect = atoi( csParam );
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void DetectInvisibility::SendInvisibleList
//////////////////////////////////////////////////////////////////////////////////////////
//  Sends a remove unit for all invisible units on the screen
// 
(
 DWORD flagId,
 Unit *self,
 DWORD popup
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    WorldMap *wl = TFCMAIN::GetWorld( self->GetWL().world );

    if( wl == NULL ){
        return;
    }

    // Get all units within the default range.
    TemplateList< Unit > *unitList = wl->GetLocalUnits( self->GetWL(), _DEFAULT_RANGE, FALSE );//BLBL 30=>_DEFAULT_RANGE

    if( unitList == NULL ){
        return;
    }
    
    unitList->ToHead();
    while( unitList->QueryNext() ){
        Unit *un = unitList->Object();

        // If the unit is invisible.
        if( un->ViewFlag( flagId ) != 0 ){
            if( popup != 0 ){
                WorldPos wlPos = self->GetWL();

                TFCPacket sending;
                // Display the dissappearing effect.
                sending << (RQ_SIZE)__EVENT_SPELL_EFFECT;
                sending << (short)popup;
                sending << (long) un->GetID();
                sending << (long) un->GetID();
                sending << (short)wlPos.X;
                sending << (short)wlPos.Y;
                sending << (short)wlPos.X;
                sending << (short)wlPos.Y;
                sending << (long)GetNextGlobalEffectID();
                sending << (long)0;

                self->SendPlayerMessage( sending );
            }

            // Make it dissappear.
            TFCPacket sending;
            sending << (RQ_SIZE)__EVENT_OBJECT_REMOVED;
		    sending << (char)0;
		    sending << (long)un->GetID();
            
            self->SendPlayerMessage( sending );


        }
    }

    delete unitList;

}

//////////////////////////////////////////////////////////////////////////////////////////
void DetectInvisibility::SendNewlyVisibleList
//////////////////////////////////////////////////////////////////////////////////////////
//  Sends the list of all invisible players, now visible
// 
(
 DWORD flagId,
 Unit *self,
 DWORD popup
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

        // If the unit is invisible.
        if( un->ViewFlag( flagId ) != 0 ){
            // Make it dissappear.
            TFCPacket sending;

            un->PacketPopup( un->GetWL(), sending );

            self->SendPlayerMessage( sending );

            if( popup != 0 ){
                WorldPos wlPos = self->GetWL();

                // Display the dissappearing effect.
                sending << (RQ_SIZE)__EVENT_SPELL_EFFECT;
                sending << (short)popup;
                sending << (long) un->GetID();
                sending << (long) un->GetID();
                sending << (short)wlPos.X;
                sending << (short)wlPos.Y;
                sending << (short)wlPos.X;
                sending << (short)wlPos.Y;
                sending << (long)GetNextGlobalEffectID();
                sending << (long)0;

                self->SendPlayerMessage( sending );
            }
        }
    }

    delete unitList;
}

//////////////////////////////////////////////////////////////////////////////////////////
void DetectInvisibility::DetectInvisibilityRemoval
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

        // Remove DetectInvisibility
        self->RemoveFlag( __FLAG_DETECT_INVISIBILITY );

        DispellEffectStatus( self, invisEffect->spellID );

        // Make all invisible units dissappear.
        SendInvisibleList( __FLAG_INVISIBILITY, self, invisEffect->popupEffect );
    }else
    // If the spell got dispelled
    if( wMessageID == MSG_OnDispell ){
        InvisEFFECT *invisEffect = (InvisEFFECT *)lpEffectData;

        // Remove DetectInvisibility
        self->RemoveFlag( __FLAG_DETECT_INVISIBILITY );

        DispellEffectStatus( self, invisEffect->spellID );

        // Remove the effect.
        self->RemoveEffect( dwEffect );

        // Make all invisible units dissappear.
        SendInvisibleList( __FLAG_INVISIBILITY, self, invisEffect->popupEffect );        
    }else
    // Player saves.
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
void DetectInvisibility::CallEffect
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
    
    // Add the DetectInvisibility flag
    target->SetFlag( __FLAG_DETECT_INVISIBILITY, 1 );

    SendNewlyVisibleList( __FLAG_INVISIBILITY, self, popoffVisualEffect );

    // Setup the add flag
    InvisEFFECT *invisEffect = new InvisEFFECT;
    invisEffect->popupEffect = popoffVisualEffect;
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
        DetectInvisibilityRemoval,
        invisEffect,
        dwDuration MILLISECONDS TDELAY,
        dwDuration,
        lpSpell->wSpellID,
        __FLAG_DETECT_INVISIBILITY
    );
}

//////////////////////////////////////////////////////////////////////////////////////////
SpellEffect *DetectInvisibility::NewFunc
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
 LPSPELL_STRUCT lpSpell // 
)
// Return: static SpellEffect, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    REGISTER_EFFECT( lpSpell->dwNextEffectID, DetectInvisibilityRemoval );
    
    CREATE_EFFECT_HANDLE( DetectInvisibility, 1 )
}
