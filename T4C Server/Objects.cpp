// Objects.cpp: implementation of the Objects class.
//
//  This file will handle objects, at least dynamic objects!
//  Francois Leblanc 1997
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Objects.h"
#include "TFC_MAIN.h"
#include "T4CLog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Objects::Objects() : uniqueState( false ), qty( 1 )
{
	backpack = NULL;
	wUndead = 0;
}

Objects::~Objects()
{
	if(backpack){
		backpack->ToHead();
		while(backpack->QueryNext()){
            backpack->Object()->DeleteUnit();
            backpack->Remove();
			//backpack->DeleteAbsolute();
		}

		delete backpack;
	}
}

BOOL Objects::Create(UINT UnitType, UINT BaseReferenceID){
	// first load the object the normal way
	if(Unit::Create(UnitType, BaseReferenceID)){
		return TRUE;
	}
return FALSE;
}

/************************************************************************/
/*void Objects::Action(B::behave which, SharedCStats *ThisPlayer, Objects *Target, signed long &Strike)
// If an event happens to the object, this function is called
// and the cmd_data[which] script is executed.
{
	int thebehavior = -1;
	
	switch(which){
	case B::OnAttack:		thebehavior = 0;		
	case B::OnAttacked:		thebehavior = 1;
	case B::OnDisturbed:	thebehavior = 2;
	case B::OnUse:			thebehavior = 3;
	case B::OnTimer:		thebehavior = 4;
	case B::OnNoMoreShots:	thebehavior = 5;
	}

	if(thebehavior > 0){
		if(script_length[thebehavior] > 0){
			int i;
			for(i = 0; i < script_length[thebehavior]; i++){
				SpellInterface.SetupParticipants(this, ThisPlayer, Target);
				SpellInterface.Activate((WORD)script_ref[i]);
			}
		   }
	}

	ObjectInterface.SetupParticipants(this, ThisPlayer, Target);
	ObjectInterface.Action(which, static_object_ref, Strike);
}
/************************************************************************/
/*void Objects::Action(B::behave which, SharedCStats *ThisPlayer, SharedCStats *Target, signed long &Strike)
{
	int thebehavior = -1;
	
	switch(which){
	case B::OnAttack:		thebehavior = 0;		
	case B::OnAttacked:		thebehavior = 1;
	case B::OnDisturbed:	thebehavior = 2;
	case B::OnUse:			thebehavior = 3;
	case B::OnTimer:		thebehavior = 4;
	case B::OnNoMoreShots:	thebehavior = 5;
	}

	if(thebehavior > 0){
		if(script_length[thebehavior] > 0){
			int i;
			for(i = 0; i < script_length[thebehavior]; i++){
				SpellInterface.SetupParticipants(this, ThisPlayer, Target);
				SpellInterface.Activate((WORD)script_ref[i]);
			}
		   }
	}

	ObjectInterface.SetupParticipants(this, ThisPlayer, Target);
	ObjectInterface.Action(which, static_object_ref, Strike);
}

/***********************************************************************************************/	
int Objects::hit(LPATTACK_STRUCTURE blow, Unit *WhoHit){

	SendUnitMessage( MSG_OnAttacked, this, NULL, WhoHit );
		
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
TemplateList <Unit> *Objects::GetBackpack(){
	return backpack;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void Objects::SetBackpack(TemplateList <Unit> *newBackpack){
	backpack = newBackpack;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Objects::SetUndead
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the undead to assign to this object upon resurrection.
// 
(
 WORD wNewUndead // the new undead.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	wUndead = wNewUndead;
}

//////////////////////////////////////////////////////////////////////////////////////////
WORD Objects::GetUndead( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the undead which should be created when resurrecting this object
// 
// Return: WORD, the undead to create. 0 if none.
//////////////////////////////////////////////////////////////////////////////////////////
{
	return wUndead;
}

//////////////////////////////////////////////////////////////////////////////////////////
CString Objects::GetName( WORD wLang )
//////////////////////////////////////////////////////////////////////////////////////////
//  returns the name of the object.
// 
// Return: CString, the name of the object.
//////////////////////////////////////////////////////////////////////////////////////////
{
    // If an overriden name was specified
    if( IsNameOverriden() ){
        // return that name
        return csOverridenName.c_str();
    }
    // Otherwise return the default name.
    return Unit::GetName( wLang );
}

bool Objects::IsNameOverriden(){
    return( !csOverridenName.empty() );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Objects::SetName
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets the overriden name of an object.
// 
(
 CString csName // The new name.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    csOverridenName = (LPCTSTR)csName;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Objects::VaporizeUnit( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Called to terminate the object's existence.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Get the object's host world.
    WorldMap *wlWorld = TFCMAIN::GetWorld( GetWL().world );

    _LOG_GAMEOP
        LOG_SYSOP,
        "Item named %s (ID %u) was vaporized.",
        (LPCTSTR)GetName( _DEFAULT_LNG ),
        GetID()
    LOG_

    // If a world was found.
    if( wlWorld != NULL ){
        // Remove it from the world.
        wlWorld->remove_world_unit( GetWL(), GetID() );

		// Broadcast object dissappearance.
        Broadcast::BCObjectRemoved( GetWL(), _DEFAULT_RANGE,
            GetID()
        );
    }

    TFCTimerManager::RemoveTimersByParameter( this );

    // Annihilate self.
    DeleteUnit();
}

//////////////////////////////////////////////////////////////////////////////////////////
DWORD Objects::GetQty( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the quantity of objects
//////////////////////////////////////////////////////////////////////////////////////////
{
    return qty;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Objects::SetQty
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets the quantity of items
// 
(
 DWORD newQty // The quantity
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Non-unique items always have as much charges as there are items in the stack.
    if( !IsUnique() ){
        // If the charges are not unlimited.
        if( ViewFlag( __FLAG_CHARGES ) >= 0 ){
            SetFlag( __FLAG_CHARGES, 1 );
        }
    }
    qty = newQty;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Objects::Add
//////////////////////////////////////////////////////////////////////////////////////////
//  Adds items.
// 
(
 DWORD addQty // Quantity to add
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( !IsUnique() ){
        qty += addQty;

        // If the charges are not unlimited.
        if( ViewFlag( __FLAG_CHARGES ) >= 0 ){
            // Non-unique items always have as much charges as there are items in the stack.
            SetFlag( __FLAG_CHARGES, 1 );
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void Objects::Remove
//////////////////////////////////////////////////////////////////////////////////////////
//  Removes items.
// 
(
 DWORD remQty // Quantity to remove
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Removed unique items get a 0 qty.
    if( qty < remQty || IsUnique() ){
        qty = 0;
    }else{
        qty -= remQty;
    }

    // Non-unique items always have as much charges as there are items in the stack.
    if( !IsUnique() ){
        // If the charges are not unlimited.
        if( ViewFlag( __FLAG_CHARGES ) >= 0 ){
            SetFlag( __FLAG_CHARGES, 1 );
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
bool Objects::IsUnique( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Determines wheter the object is unique (non-stackable).
//////////////////////////////////////////////////////////////////////////////////////////
{
    return uniqueState;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Objects::SetUnique( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets an object as being unique
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    uniqueState = true;
}

//////////////////////////////////////////////////////////////////////////////////////////
long Objects::ViewFlag
//////////////////////////////////////////////////////////////////////////////////////////
// Override ViewFlag to catch __FLAG_CHARGES and set it to -1 if the Unlimited
// charges value is set on the item reference.
// 
(
 unsigned long dwFlagID, // The flag ID
 long lDefaultValue      // The default value to return.
)
// Return: virtual long, The flag's value, or the default value if the flag
//                       wasn't found.
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( dwFlagID == __FLAG_CHARGES ){
        // Get the unit structure
        _item *lpItem = NULL;

        SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItem );

        // If it has unlimited charges return -1.
        if( lpItem != NULL && lpItem->magic.charges < 0 ){
            return -1;
        }
    }
    return DynamicFlags::ViewFlag( dwFlagID, lDefaultValue );
}