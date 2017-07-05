/*
ItemContainer.cpp
Implementation file for the Item Container object.
Its designed to be used on the chest (online mule) and trade system and also any other thing it may apply latter

Originally Written by Carlos Lima (carlos@dialsoft.com)
for Dialsoft (http://www.dialsoft.com)
*/
/*
	Modification:
	Desboys (SD) : 11/08/2005 : Improved a bit GetFreeWeight(), removing one call to GetWeight()
*/
#include "stdafx.h"
#include "ItemContainer.h"
#include "_item.h"

/* Constructor */
ItemContainer::ItemContainer() : m_iMaxWeight(0)
{
	container = new TemplateList <Objects>;
}



/* Destructor */
ItemContainer::~ItemContainer() {
	if( container != NULL ){
        container->ToHead();
		while(container->QueryNext()){
            container->Object()->DeleteUnit();
            container->Remove();
		}        
	
		delete container;
	}
}



/*******************************************************************************************************
BOOL Put (Objects*, BOOL) : used to insert/add an object to the container
Returns TRUE for success, FALSE if container is full
*******************************************************************************************************/
BOOL ItemContainer::Put(Objects *oObjectToAdd, BOOL boIgnoreMaxWeight)
{
	if ( boIgnoreMaxWeight == false && GetFreeWeight() < oObjectToAdd->GetWeight() * oObjectToAdd->GetQty() ) return FALSE;

    container->Lock();

    // If the object is unique add it directly.
    bool boCreateItemOnContainer = true;
    if( !oObjectToAdd->IsUnique() ){

        //Search for the item inside the container
		container->ToHead();
        while( container->QueryNext() ){
            Objects *containerItem = container->Object();

            // If an item of the same type was found.
            if( containerItem->GetStaticReference() == oObjectToAdd->GetStaticReference() ){
                // Simply add the item's quantity to this item.
                containerItem->Add( oObjectToAdd->GetQty() );

                // Delete this item's instance (replaced by the item in the container).
                oObjectToAdd->DeleteUnit();

                // Do not add the object to the container
                boCreateItemOnContainer = false;

                break;
            }
        }

    }

    // If the object should be added to the container (not found or unique).
    if( boCreateItemOnContainer ){
        container->AddToTail( oObjectToAdd );
    }

    container->Unlock();
	return TRUE;
}


/*******************************************************************************************************
Objects* Take (DWORD, DWORD) : used to remove an object from the container
Returns a pointer to the object or NULL if failed
*******************************************************************************************************/
Objects* ItemContainer::Take(DWORD dwObjectID, DWORD dwQty)
{

	container->Lock();
    container->ToHead();
	while( container->QueryNext() ){

		Objects *obj = container->Object();

		if (obj->GetID() == dwObjectID) {

			// If the quantity is bigger than the total quantity.
			if( obj->GetQty() < dwQty ){
				// Adjust it.
				dwQty = obj->GetQty();
			}

			_item *lpItem = NULL;
			obj->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItem );
			if( lpItem == NULL ){
				continue;
			}

			bool forceQtyToOne = false;
			Objects *droppedObj;
			// If there are more than 1 item in the container
			if( obj->GetQty() > 1 ){
				// Create a copy of the container item
				droppedObj = new Objects();
				if( !droppedObj->Create( U_OBJECT, obj->GetStaticReference() ) ){
					droppedObj->DeleteUnit();
					continue;
				}
				// Set the quantity of items to the quantity of dropped items.
				droppedObj->SetQty( dwQty );
			}else{
				// Used the container item as the dropped item.
				droppedObj = obj;
				// Add 1 qty count to avoid deleting the unit.
				forceQtyToOne = true;

				container->Remove();
			}

			// Remove the quantity of objects dropped from the container item.
        
			if( forceQtyToOne ){
				obj->SetQty( 1 );
			}else{
				obj->Remove( dwQty );
			}
			if( obj->GetQty() == 0 ){
				container->Remove();
				obj->DeleteUnit();
			}

			container->Unlock();

			return droppedObj;

		}
					
    }
    container->Unlock();
	return NULL;
}

/*******************************************************************************************************
Objects* TakeTop () : used to remove an object from the top of the container
Returns a pointer to the object or NULL if empty
*******************************************************************************************************/
Objects* ItemContainer::TakeTop(void)
{
	container->Lock();
    container->ToHead();
	if ( container->QueryNext() ) {

		Objects *obj = container->Object();

		Objects *droppedObj;
		// Used the container item as the dropped item.
		droppedObj = obj;
		// Add 1 qty count to avoid deleting the unit.

		container->Remove();

		container->Unlock();

		return droppedObj;

    }
    container->Unlock();
	return NULL;

}

/*******************************************************************************************************
BOOL Destroy (DWORD, DWORD) : used to destroy/junk an object from the container
Returns TRUE on success, else FALSE
*******************************************************************************************************/
BOOL ItemContainer::Destroy(DWORD dwObjectID, DWORD dwQty)
{

	BOOL boReturnValue = FALSE;

    container->Lock();
	container->ToHead();
    while( container->QueryNext() ){
        Objects *obj = container->Object();
        if( obj->GetID() == dwObjectID ){
			_item *item = NULL;

			// Get the item structure.
			obj->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &item );

            if( item != NULL ){

                obj->Remove( dwQty );
                if( obj->GetQty() == 0 ){                
                    obj->DeleteUnit();
                    container->Remove();
                }
				boReturnValue = TRUE;

            }
            break;
        }
    }
	container->Unlock();
	return boReturnValue;
}


/*******************************************************************************************************
unsigned int GetWeight (void) : used to get the total weight of the container
*******************************************************************************************************/
unsigned int ItemContainer::GetWeight(void)
{
    unsigned int iWeight = 0;
    container->Lock();
    container->ToHead();
    while( container->QueryNext() ){
        Objects *obj = container->Object();
        iWeight += obj->GetWeight() * obj->GetQty();
    }
    container->Unlock();
	return iWeight;
}


/*******************************************************************************************************
unsigned int GetFreeWeight (void) : used to get the remaining weight of the container
*******************************************************************************************************/
unsigned int ItemContainer::GetFreeWeight(void)
{
	// (SD: 11/08/05) prevent two calls to GetWeight()
	int weight = m_iMaxWeight - GetWeight();
	return (weight<0?0:weight);
	/*
	// If the container is overweighted, tell there is no room left
	if ( GetWeight() >= m_iMaxWeight ) return 0;
	return m_iMaxWeight - GetWeight();
	*/
}


/*******************************************************************************************************
unsigned int GetMaxWeight (void) : used to get the maximum allowed weight for this container
Returns the maximum weight
*******************************************************************************************************/
unsigned int ItemContainer::GetMaxWeight(void)
{
	return m_iMaxWeight;
}


/*******************************************************************************************************
void SetMaxWeight (int) : used to set the maximum allowed weight for this container
*******************************************************************************************************/
void ItemContainer::SetMaxWeight(unsigned int iMaxWeight)
{
	m_iMaxWeight = iMaxWeight;
}


/*******************************************************************************************************
void ResetContainer (void) : used to reset (delete) the container's items
*******************************************************************************************************/
void ItemContainer::ResetContainer(void)
{
	if( container != NULL ){
        container->ToHead();
		while(container->QueryNext()){
            container->Object()->DeleteUnit();
            container->Remove();
		}        
	}
}


/*******************************************************************************************************
void GetPacket (TFCPacket) : add container info to the packet
*******************************************************************************************************/
void ItemContainer::GetPacket(TFCPacket &packet)
{
	if (container->NbObjects() > 0) {
		container->Lock();
		container->ToHead();
		
		packet << (short)container->NbObjects();
		while (container->QueryNext()) {
			Objects *obj = container->Object();
			
			long lObjCharges = 0;
			if (obj->IsUnique()) lObjCharges = obj->ViewFlag( __FLAG_CHARGES );

			packet << (short)obj->GetAppearance();
			packet << (long)obj->GetID();
			packet << (short)obj->GetStaticReference();
			packet << (long)obj->GetQty();
			packet << (long)lObjCharges;
		}
		container->Unlock();
	} else {
		packet << (short)0;
	}
}


/*******************************************************************************************************
TemplateList<Objects>*	LockAndGetList (void) : Lock the list and returns a pointer to it. 
												No other method can be called until UnlockAndReleaseList
Returns: A pointer to the list
*******************************************************************************************************/
TemplateList<Objects>*	ItemContainer::LockAndGetList(void)
{
	container->Lock();
	return container;
}

	
/*******************************************************************************************************
void UnlockAndReleaseList (void) : Unlocks the list. 
								   Must be called before any other method if LockAndGetList was called.
*******************************************************************************************************/
void ItemContainer::UnlockAndReleaseList(void)
{
	container->Unlock();
}

/*******************************************************************************************************
BOOL GetItemWeight (DWORD, unsigned int&) : Searches for the item and if found, sets uiItemWeight to 
											the found's item weight and returns TRUE. Else, returns FALSE.
*******************************************************************************************************/
BOOL ItemContainer::GetItemWeight(DWORD dwObjectID, int &iObjectWeight)
{
	container->Lock();
    container->ToHead();
	while( container->QueryNext() ){

		Objects *obj = container->Object();
		if (obj->GetID() == dwObjectID) {
			iObjectWeight = obj->GetWeight();
			container->Unlock();
			return TRUE;
		}
    }
    container->Unlock();
	return FALSE;
}

/*******************************************************************************************************
BOOL GetItemName (DWORD, char*) : Searches for the item and if found, sets pObjectName to 
											the found's item name and returns TRUE. Else, returns FALSE.
*******************************************************************************************************/
BOOL ItemContainer::GetItemName(DWORD dwObjectID, CString &pObjectName, WORD pLanguageID)
{
	container->Lock();
    container->ToHead();
	while( container->QueryNext() ){

		Objects *obj = container->Object();
		if (obj->GetID() == dwObjectID) {
			pObjectName = obj->GetName( pLanguageID );
			container->Unlock();
			return TRUE;
		}
    }
    container->Unlock();
	return FALSE;
}
