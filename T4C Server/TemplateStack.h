// ************************************************************************
// ***                                                                  ***
//      File Name: TemplateStack.h
//      Project:   Virtual Dreams Library
//      Creation:  August 2nd 1997
//      Author:    Francois Leblanc (FL)
//				   based on TemplateList by Benoit Thomas
// ***                                                                  ***
// ************************************************************************
// ***                                                                  ***
//      Change History
//
//         Date            Ver.	   Author	   Purpose
//         08-02-1997      1.0     FL          Initial development
//
//      Description
//				Provide Template stacks.
// ***                                                                  ***
//	************************************************************************
// *** Copyright (c) 1997-1998 Vritual Dreams (r). All rights reserved. ***

#if !defined(AFX_TEMPLATESTACK_H__B5F32863_E0F7_11D0_A876_00E029058623__INCLUDED_)
#define AFX_TEMPLATESTACK_H__B5F32863_E0F7_11D0_A876_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

template <class ObjectType> class TemplateStack;

template <class ObjectType>
class TemplateStackObject {
	friend TemplateStack <ObjectType>;

	protected:
		TemplateStackObject *Lesser;

	public:
		TemplateStackObject(void);		
		ObjectType     *Pointer;
};

template <class ObjectType>
class TemplateStack {

	private:
		TemplateStackObject<ObjectType> *Current;
		BOOL AddObject(ObjectType *obj);
		BOOL RetreiveObject(ObjectType **obj);  // pointer of pointer
	
	public:
	
		TemplateStack(void);
		~TemplateStack(void);
		
		BOOL push(ObjectType *obj);			// puts an object on the stack
		BOOL push(ObjectType &obj);
		BOOL pop(ObjectType **obj);			// gets an object from the stack
		BOOL pop(ObjectType *&obj);

        BOOL IsEmpty( void );

		ObjectType *Object();				// returns the currently pointed object without popping it
		
		void DestroyStack();
};

template <class ObjectType>
TemplateStackObject<ObjectType>::TemplateStackObject(void) : Lesser(0) {
// TemplateStackObject Defautl Constructor.
// Initialize Greater and Lesser pointer to null.
}


template <class ObjectType>
TemplateStack<ObjectType>::TemplateStack(void) : Current(0){
}
template <class ObjectType>
TemplateStack<ObjectType>::~TemplateStack(void){
}

template <class ObjectType>
BOOL TemplateStack<ObjectType>::AddObject(ObjectType *obj) {

	TemplateStackObject <ObjectType> *TempObject = new TemplateStackObject<ObjectType>;
	TempObject->Lesser = Current;
	Current = TempObject;
	Current->Pointer = obj;			// stacks are always "floating"	
	return TRUE;
}

template <class ObjectType>
ObjectType *TemplateStack<ObjectType>::Object(){
	if(Current) return Current->Pointer;
return NULL;
}

template <class ObjectType>
BOOL TemplateStack<ObjectType>::RetreiveObject(ObjectType **obj) {			
	if(!Current){
		*obj = NULL;		
		return FALSE;
	}	
	*obj = Current->Pointer;
	TemplateStackObject <ObjectType> *TempObject = Current;
	Current = Current->Lesser;
	delete TempObject;			// remove it from the stack	
return TRUE;
}	

template <class ObjectType>
BOOL TemplateStack<ObjectType>::push(ObjectType *obj){
	return AddObject(obj);
}
template <class ObjectType>
BOOL TemplateStack<ObjectType>::push(ObjectType &obj){
	return AddObject(&obj);
}
template <class ObjectType>
BOOL TemplateStack<ObjectType>::pop(ObjectType **obj){
	return RetreiveObject(obj);
}
template <class ObjectType>
BOOL TemplateStack<ObjectType>::pop(ObjectType *&obj){
	return RetreiveObject(&obj);
}
template <class ObjectType>
void TemplateStack<ObjectType>::DestroyStack(){
	while(Current){
		ObjectType *obj;
		pop(&obj);
		delete obj;
	}
}

template< class ObjectType >
BOOL TemplateStack<ObjectType>::IsEmpty( void ){
    if( !Current ){
        return TRUE;
    }
    return FALSE;
}

#endif AFX_TEMPLATESTACK_H__B5F32863_E0F7_11D0_A876_00E029058623__INCLUDED_