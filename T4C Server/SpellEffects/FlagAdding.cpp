// FlagAdding.cpp: implementation of the FlagAdding class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "..\NPCmacroScriptLng.h"
#include "FlagAdding.h"
#include "../TFC_MAIN.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define REMOVE_FLAG_EFFECT      dwEffectID

// Saved Structure 
typedef struct _FLAG_ADDINGv1{
    DWORD dwFlagID;
} FLAG_ADDINGv1, *LPFLAG_ADDINGv1;

typedef struct _FLAG_ADDING{
    DWORD dwFlagID;
    DWORD effectID;
    DWORD spellID;
} FLAG_ADDING, *LPFLAG_ADDING;


FlagAdding::FlagAdding()
{
    dwFlagID = 0;
}

FlagAdding::~FlagAdding()
{

}

REGISTER_SPELL_EFFECT( FLAG_ADDING, FlagAdding::NewFunc, FLAG_ADDING_EFFECT, FlagAdding::Init );

//////////////////////////////////////////////////////////////////////////////////////////
void FlagAdding::Init( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Called by REGISTER_SPELL_EFFECT to complete spell initialisation
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL FlagAdding::InputParameter
//////////////////////////////////////////////////////////////////////////////////////////
// Enters the different effect parameters
// 
(
 CString csParam,           // String parameter
 WORD wParamID              // ID of parameter
)
// Return: BOOL, Should return TRUE if csParam is valid.
//////////////////////////////////////////////////////////////////////////////////////////
{       


	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
    const INT FlagID = 1;
    const INT FlagValue = 2;
    const INT Duration = 3;
	const INT Global = 4;



    BOOL boOK = TRUE;
    
    switch( wParamID ){
    /////////
    // FlagID
    case FlagID:
        dwFlagID = atoi( (LPCTSTR)csParam );

        // FlagID cannot be 0
        if( dwFlagID == 0 ){
            boOK = FALSE;
        }

        break;
    ////////////
    // FlagValue
    case FlagValue:
        if( !flagValue.SetFormula( csParam ) ){
            boOK = FALSE;
        }
        break;
    ///////////
    // Duration
    case Duration:
        dwDuration = atoi( (LPCTSTR)csParam );
        break;

	///////////
    // Global Flag //set at 1 if a global flag
    case Global:
        dwGlobal = atoi( (LPCTSTR)csParam );
        break;



    ///////////////////////////////////
    // Any other parameter is incorrect
    default:         
        boOK = FALSE; 
        break;
    }

    return boOK;
}

//////////////////////////////////////////////////////////////////////////////////////////
void FlagAdding::FlagRemoval
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
        LPFLAG_ADDING lpAddFlag = (LPFLAG_ADDING)lpEffectData;
        self->RemoveFlag( lpAddFlag->dwFlagID );        

        DispellEffectStatus( self, lpAddFlag->spellID );
    }else
    // If the spell got dispelled
    if( wMessageID == MSG_OnDispell ){
        // Remove the flag
        LPFLAG_ADDING lpAddFlag = (LPFLAG_ADDING)lpEffectData;
        self->RemoveFlag( lpAddFlag->dwFlagID );        
                             
        DispellEffectStatus( self, lpAddFlag->spellID );
        // Remove the effect.
        self->RemoveEffect( dwEffect );        
    }else
    // Player exited
    if( wMessageID == MSG_OnSavePlayer ){
        // Fetch the pointers
        LPFLAG_ADDING lpAddFlag = (LPFLAG_ADDING)lpEffectData;
		LPDATA_SAVE lpDataSave = (LPDATA_SAVE)lpUserData;
		// Prepare buffer to save on player
        lpDataSave->bBufferSize = sizeof( FLAG_ADDING );
        lpDataSave->lpbData = new BYTE[ sizeof( FLAG_ADDING ) ];        
        memcpy( lpDataSave->lpbData, lpAddFlag, sizeof( FLAG_ADDING ) );        
    }else
    // Player loads
    if( wMessageID == MSG_OnLoadPlayer ){
        LPUNIT_EFFECT lpUnitEffect = (LPUNIT_EFFECT)lpEffectData;
        LPDATA_SAVE lpDataSave = (LPDATA_SAVE)lpUserData;

        LPFLAG_ADDING lpAddFlag = new FLAG_ADDING;

        // Fetch the LPFLAG_ADDING;
        if( lpDataSave->bBufferSize == sizeof( FLAG_ADDING ) ){
            memcpy( lpAddFlag, lpDataSave->lpbData, sizeof( FLAG_ADDING ) );
            // Get the spell
            LPSPELL_STRUCT lpSpell = SpellMessageHandler::GetSpell( lpAddFlag->spellID );

            if( lpSpell != NULL ){
                // Create an effect status update for the client.
                CreateEffectStatus(
                    self,
                    lpAddFlag->spellID,
                    ( lpUnitEffect->dwTimer - TFCMAIN::GetRound() ) * 50,
                    lpUnitEffect->dwTotalDuration,
                    lpSpell
                );
            }
        }else if( lpDataSave->bBufferSize == sizeof( FLAG_ADDINGv1 ) ){
            FLAG_ADDINGv1 f;
            memcpy( &f, lpDataSave->lpbData, sizeof( FLAG_ADDING ) );
            lpAddFlag->dwFlagID = f.dwFlagID;
            lpAddFlag->effectID = 0;
            lpAddFlag->spellID = 0;
        }

        // Attach the flag adding structure to the effect.
        lpUnitEffect->lpData = lpAddFlag;
    }else
    // Effect is getting destroyed.
    if( wMessageID == MSG_OnDestroy ){
        // Delete the AddFlag structure associated to the effect.
        LPFLAG_ADDING lpAddFlag = (LPFLAG_ADDING)lpEffectData;
        delete lpAddFlag;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void FlagAdding::CallEffect
//////////////////////////////////////////////////////////////////////////////////////////
// Does the flag adding effect
// 
(
 SPELL_EFFECT_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	// If a target unit is specified
	if( target != NULL )
	{
    	// If user isn't already using this spell
		if( target->GetEffect( REMOVE_FLAG_EFFECT ) == NULL )
		{
			int thisFlagValue = static_cast< int >(flagValue.GetBoost(self, target ));

			// The effect is simple, add the flag to the target unit.
			if(dwGlobal)
			{
				GiveGlobalFlag( dwFlagID, thisFlagValue );
			}
			else
			{
				target->SetFlag( dwFlagID, thisFlagValue );
				// Get duration now.
				DWORD dwDuration = lpSpell->bfDuration.GetBoost( self, target );

				// If duration is non-null
				if( dwDuration != 0 ){
					// Setup the add flag
					LPFLAG_ADDING lpAddFlag = new FLAG_ADDING;
					lpAddFlag->dwFlagID = dwFlagID;

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
						REMOVE_FLAG_EFFECT,
						FlagRemoval,
						lpAddFlag,
						dwDuration MILLISECONDS TDELAY,
						dwDuration,
						lpSpell->wSpellID,
						0
					);
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
SpellEffect *FlagAdding::NewFunc
//////////////////////////////////////////////////////////////////////////////////////////
// Returns an instance of FlagAdding
// 
(
 LPSPELL_STRUCT lpSpell
)
// Return: SpellEffect, the FlagAdding instance
//////////////////////////////////////////////////////////////////////////////////////////
{
	// Register this spell's effect function.
	REGISTER_EFFECT( lpSpell->dwNextEffectID, FlagRemoval );

	CREATE_EFFECT_HANDLE( FlagAdding, 1 )
}