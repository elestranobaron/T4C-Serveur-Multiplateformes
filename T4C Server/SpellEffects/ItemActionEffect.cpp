// ItemActionEffect.cpp: implementation of the ItemActionEffect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ItemActionEffect.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ItemActionEffect::ItemActionEffect()
{
	bError = NOT_LOADED;
	dwItemID = 0;
	bResType = 0;
}

ItemActionEffect::~ItemActionEffect()
{

}

REGISTER_SPELL_EFFECT( ITEMACTION, ItemActionEffect::NewFunc, ITEMACTION_EFFECT, NULL );

//////////////////////////////////////////////////////////////////////////////////////////
BOOL ItemActionEffect::InputParameter
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
    const INT ResType = 1;
	const INT ItemID = 2;




	BOOL boReturn = TRUE;

	switch(wParamID)
	{
	case ResType:
		if(csParam.CompareNoCase("take") == 0){
			bResType = TAKE;
		}else if (csParam.CompareNoCase("give")==0){
			bResType = GIVE;
		}else{
			boReturn = FALSE;
		}
	break;
	case ItemID:
		csItemName = csParam;
	break;
	}
	
	return boReturn;
}

//////////////////////////////////////////////////////////////////////////////////////////
void ItemActionEffect::HandleError
//////////////////////////////////////////////////////////////////////////////////////////
// Log errors
// 
(
 DWORD dwDaItemID,
 BYTE bDaResType,
 CString csDaItemName,
 Unit *self,
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	_LOG_DEBUG
		LOG_DEBUG_HIGH,
		"\r\nError while casting ItemActionEffect. \
		 \r\nItemID: %d, ActionType: %d, ItemBuffer: %s \
		 \r\nCurrent target: %08X self: %08X",
		 dwDaItemID,
		 bDaResType,
		 csDaItemName,
		 target,
		 self
	LOG_
}

//////////////////////////////////////////////////////////////////////////////////////////
void ItemActionEffect::CallEffect
//////////////////////////////////////////////////////////////////////////////////////////
// Take or give an item
// 
(
 SPELL_EFFECT_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	if(bError == NOT_LOADED){
		dwItemID = Unit::GetIDFromName( csItemName, U_OBJECT, TRUE );
		bError = LOADED;
		if(dwItemID == 0){
			bError = FAILED;
		}
	}

	if(bError == FAILED){
		HandleError(dwItemID, bResType, csItemName, self, target);
	}

	if(bError == LOADED){
		switch(bResType)
		{
		case TAKE:{
			if( target != NULL ) {
				try {
					TakeItemFunc(dwItemID, target);
				} catch (...) {
					HandleError(dwItemID, bResType, csItemName, self, target);
				}
			} else {
				HandleError(dwItemID, bResType, csItemName, self, target);
			}
		}break;
		case GIVE:{
			if( (target != NULL) && (self != NULL) ) {
				try {
					__GiveItem( self, target, dwItemID, false, true, true );
				} catch (...) {
					HandleError(dwItemID, bResType, csItemName, self, target);
				}

			} else {
				HandleError(dwItemID, bResType, csItemName, self, target);
			}
		}break;
		default:
		break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
SpellEffect *ItemActionEffect::NewFunc
//////////////////////////////////////////////////////////////////////////////////////////
// Create a SpellEffect object.
// 
(
 LPSPELL_STRUCT lpSpell // The spell structure for any spell effect registration.
)
// Return: SpellEffect, the spell effect. 
//////////////////////////////////////////////////////////////////////////////////////////
{
  CREATE_EFFECT_HANDLE( ItemActionEffect, 0 )
}