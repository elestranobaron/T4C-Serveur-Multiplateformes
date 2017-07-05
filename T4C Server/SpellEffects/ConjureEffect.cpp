// ConjureEffect.cpp: implementation of the ConjureEffect class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ConjureEffect.h"
#include "../Objects.h"
#include "../Creatures.h"
#include "../WorldMap.h"
#include "../TFC_main.h"
#include "../T4CLog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ConjureEffect::ConjureEffect()
{
    wConjureID = 0;
    bConjureType = 0;
	wlDestinationPos.X = 0;
	wlDestinationPos.Y = 0;
	wlDestinationPos.world = 0;
	bmUserDefinedPosition = 0;
	bError = NOT_LOADED;
}

ConjureEffect::~ConjureEffect()
{

}

REGISTER_SPELL_EFFECT( CONJURE, ConjureEffect::NewFunc, CONJURE_EFFECT, NULL );

//////////////////////////////////////////////////////////////////////////////////////////
BOOL ConjureEffect::InputParameter
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


	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
    const INT ConjureType = 1;
    const INT ConjureID = 2;
	const INT ConjurePosX = 3;
	const INT ConjurePosY = 4;
	const INT ConjurePosW = 5;



    BOOL boReturn = TRUE;

    switch( wParamID ){
    case ConjureType:
        if( csParam.CompareNoCase( "object" ) == 0 ){
            bConjureType = U_OBJECT;
        }else if( csParam.CompareNoCase( "npc" ) == 0 || csParam.CompareNoCase( "monster" ) == 0 ){
            bConjureType = U_NPC;
        }else if( csParam.CompareNoCase( "equip" ) == 0 ){//BLBLBL dans le cas ou le type demandé est equip, on va équiper l'item en question sur le joueur
            bConjureType = U_EQUIP;
        }else{
            // If this isn't a valid type.
            boReturn = FALSE;
        }
        break;
    case ConjureID:
		csConjureID = csParam;
        break;
	case ConjurePosX:
		if (bfPosX.SetFormula(csParam) == FALSE) {
			boReturn = FALSE;
		} else {
			bmUserDefinedPosition |= 0x01;
		}
		break;
	case ConjurePosY:
		if (bfPosY.SetFormula(csParam) == FALSE) {
			boReturn = FALSE;
		} else {
			bmUserDefinedPosition |= 0x02;
		}
		break;
	case ConjurePosW:
		if (bfPosW.SetFormula(csParam) == FALSE) {
			boReturn = FALSE;
		} else {
			bmUserDefinedPosition |= 0x04;
		}
		break;
	default:
		boReturn = FALSE;
    }
    
    return boReturn;
}

//////////////////////////////////////////////////////////////////////////////////////////
void ConjureEffect::HandleError()
//////////////////////////////////////////////////////////////////////////////////////////
// Log errors
//////////////////////////////////////////////////////////////////////////////////////////
{
	_LOG_DEBUG
		LOG_DEBUG_LVL1,
		"Error while casting ConjureEffect. SummonType: %d, EntityID: %s, Destination Parameteters: %s, Entity: %s",
		bConjureType,
		csConjureID,
		bmUserDefinedPosition != 0x00 && bmUserDefinedPosition != 0x07 ? "Incomplete" : "(X,Y,W) Ok",
		wConjureID == 0 ? "Inexistent" : "Ok"
	LOG_
}

//////////////////////////////////////////////////////////////////////////////////////////
void ConjureEffect::CallEffect
//////////////////////////////////////////////////////////////////////////////////////////
// Conjures a monster or an object.
// 
(
 SPELL_EFFECT_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	if(bError == NOT_LOADED){
		if (bConjureType==U_EQUIP) wConjureID = Unit::GetIDFromName( csConjureID, U_OBJECT, TRUE);//dans le cas d'un conjure de type equip on recherche un objet dans la liste existente.
		else wConjureID = Unit::GetIDFromName( csConjureID, bConjureType, TRUE);

		bError = LOADED;
		if(wConjureID == 0 || (bmUserDefinedPosition != 0x00 && bmUserDefinedPosition != 0x07) ){ //bmUserDefinedPosition must be 0 (no specific position formula defined) or 7 (X, Y and W formulas defined)
			bError = FAILED;
		}
	}

	if(bError == FAILED){
		HandleError();
	}

	if(bError == LOADED){
		
		switch( bConjureType ){
		case U_OBJECT:{
			if( target->GetType() != U_PC ){
				return;
			}

			Character *lpChar = static_cast< Character * >( target );

			// Conjure the object in the target unit's backpack.
			if( target != NULL ){
				if( target->GetType() == U_PC ){
					// Create an object item.
					Objects *lpuUnit = new Objects;

					if( lpuUnit->Create( U_OBJECT, wConjureID ) ){
						lpChar->AddToBackpack( lpuUnit );
					}else{
						lpuUnit->DeleteUnit();
					}
				}
			}
		} break;
		case U_NPC:{
			WorldPos wlDestination;
			if (bmUserDefinedPosition == 0x07) { // user specified formulas for X, Y and W.
				wlDestination.X = bfPosX.GetBoost(self, target);
				wlDestination.Y = bfPosY.GetBoost(self, target);
				wlDestination.world = bfPosW.GetBoost(self, target);
			} else { // no user defined formulas, lets use the spell casting position.
				wlDestination = wlPos;
			}
			// If a position was provided
			if( wlDestination.X > 0 || wlDestination.Y > 0 ){
				WorldMap *wlWorld = TFCMAIN::GetWorld( wlDestination.world );

				// If world is valid.
				if( wlWorld != NULL ){
					// Create a new NPC
					Creatures *lpCreature = new Creatures;
					if( lpCreature->Create( U_NPC, wConjureID ) ){                    
						lpCreature->SetBond( self );
						lpCreature->SetWL( wlDestination );
						if( !wlWorld->SummonMonster( lpCreature, TRUE ) ){
							lpCreature->DeleteUnit();
						}
					}else{
						lpCreature->DeleteUnit();
					}
				}
			}
		} break;
		case U_EQUIP:{//BLBLBL dans le cas ou on demande d'equiper un objet
			if( target->GetType() != U_PC ){
				return;
			}

			Character *lpChar = static_cast< Character * >( target );

			// Conjure the object in the target unit's backpack, then equip it.
			if( target != NULL ){
				if( target->GetType() == U_PC ){
					// Create an object item.
					Objects *lpuUnit = new Objects;

					if( lpuUnit->Create( U_OBJECT, wConjureID ) ){
						DWORD itemGlobalId = lpuUnit->GetID();
						lpChar->AddToBackpack( lpuUnit );
						if (lpuUnit->IsUnique()){
							_item *lpItemStructure = NULL;
            				// Get the item structure.
							lpuUnit->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItemStructure );
        					if( lpItemStructure != NULL) {
								lpChar->unequip_object(lpItemStructure->equip_position);//on déséquipe l'objet précédemment porté
								lpChar->equip_object( itemGlobalId );//et on équipe le nouvel objet
							}else{
							_LOG_DEBUG
								LOG_DEBUG_LVL1,
								"Could not find the structure (equipement position) for instance of item %d, item was summoned but not equiped.",
								wConjureID
							LOG_
							}
						}else{
							_LOG_DEBUG
								LOG_DEBUG_LVL1,
								"Only unique items can be equiped via this spell effect, item %d was summoned but not equiped.",
								wConjureID
							LOG_
						}
						
					}else{
						lpuUnit->DeleteUnit();
					}
				}
			}
		} break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
SpellEffect *ConjureEffect::NewFunc
//////////////////////////////////////////////////////////////////////////////////////////
// Create a SpellEffect object.
// 
(
 LPSPELL_STRUCT lpSpell // The spell structure for any spell effect registration.
)
// Return: SpellEffect, the spell effect. 
//////////////////////////////////////////////////////////////////////////////////////////
{
  CREATE_EFFECT_HANDLE( ConjureEffect, 0 )
}