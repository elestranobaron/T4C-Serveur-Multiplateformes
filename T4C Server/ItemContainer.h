/*
ItemContainer.h
Header file for the Item Container object.
Its designed to be used on the chest (online mule) and trade system and also any other thing it may apply latter

Originally Written by Carlos Lima (carlos@dialsoft.com)
for Dialsoft (http://www.dialsoft.com)
*/

#ifndef DIALSOFT_ITEMCONTAINER_H_2005_06_29_MNABVNDKJH987SH7_9H5VA1L4M2V0__INCLUDED_
#define DIALSOFT_ITEMCONTAINER_H_2005_06_29_MNABVNDKJH987SH7_9H5VA1L4M2V0__INCLUDED_

#include "Objects.h"

class EXPORT ItemContainer
{
public:
	ItemContainer();
	~ItemContainer();
	BOOL					Put						(Objects* oObjectToAdd, BOOL boIgnoreMaxWeight = false); //Add/insert an object into the container. Returns TRUE for success, FALSE if container is full
	Objects*				Take					(DWORD dwObjectID, DWORD qty); //Remove an object from the container. Returns: a pointer to the object removed or NULL if no object got removed
	Objects*				TakeTop					(void); // Takes the top object from the container. NULL if empty
	BOOL					Destroy					(DWORD dwObjectID, DWORD qty); //Destroy an object (junk it). Returns: TRUE if the object got destroyed or FALSE if nothing destroyed
	BOOL					GetItemWeight			(DWORD dwObjectID, int &iObjectWeight); // Searches for the item and if found, sets uiItemWeight to the found's item weight and returns TRUE. Else, returns false.
	BOOL					GetItemName				(DWORD dwObjectID, CString &pObjectName, WORD pLanguageID); // Searches for the item and if found, sets pObjectName to the found's item name and returns TRUE. Else, returns false;
	unsigned int			GetWeight				(void); //Get how many weight the chest is carrying (encumbrance)
	unsigned int			GetFreeWeight			(void); //Get how many weight the chest can still carry (emcumbrance left)
	unsigned int			GetMaxWeight			(void); //Returns the maximum allowed weight for this container
	void					SetMaxWeight			(unsigned int iMaxWeight);//Sets the maximum allowed weight for this container
	void					ResetContainer			(void);//Resets the container: Clear all entries in it
	void					GetPacket				(TFCPacket &packet); //adds container info to the given packet
	TemplateList<Objects>*	LockAndGetList			(void); //Lock the list and returns a pointer to it. No other method can be called until release
	void					UnlockAndReleaseList	(void); //Unlocks the list. Must be called before any other method if LockAndGetList was called.
private:
	TemplateList <Objects> *container;	
	unsigned int m_iMaxWeight;
};

#endif //DIALSOFT_ITEMCONTAINER_H_2005_06_29_MNABVNDKJH987SH7_9H5VA1L4M2V0__INCLUDED_
