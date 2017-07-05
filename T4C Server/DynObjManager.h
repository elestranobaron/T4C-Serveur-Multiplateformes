// DynObjManager.h: interface for the DynObjManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYNOBJMANAGER_H__10CA361D_EFE8_11D1_830E_00104B2CA38F__INCLUDED_)
#define AFX_DYNOBJMANAGER_H__10CA361D_EFE8_11D1_830E_00104B2CA38F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "_item.h"
#include "ObjectStructure.h"

typedef ObjectStructure *( *DYNOBJCALLBACK)( void );

class _declspec( dllexport ) DynObjManager  
{
public:
	static void RegisterObjectStructureCallback( WORD wStructureID, DYNOBJCALLBACK lpCallback );

	static ObjectStructure *GetRegisteredUnit( WORD wStructureID, WORD wReferenceID, LPCTSTR lpszUnitName );

	static void PostInitDestroy( void );
	static void Destroy( void );
private:
	struct DYNLIST{
		DYNOBJCALLBACK lpCallback;
		WORD wStructureID;		
	};

	static TemplateList< DYNLIST >			tlDynObjects;
	static TemplateList< ObjectStructure >	tlRegisteredUnits;

};

#endif // !defined(AFX_DYNOBJMANAGER_H__10CA361D_EFE8_11D1_830E_00104B2CA38F__INCLUDED_)
