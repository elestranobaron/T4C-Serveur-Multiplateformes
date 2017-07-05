// Objects.h: interface for the Objects class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTS_H__ED5A8764_A9CC_11D0_9B9E_444553540000__INCLUDED_)
#define AFX_OBJECTS_H__ED5A8764_A9CC_11D0_9B9E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Unit.h"
#include "ObjectFlagsListing.h"
#include <string>

class EXPORT Objects : public Unit
{
public:
	Objects();	
	
	BOOL Create(UINT UnitType, UINT BaseReferenceID);
	
	int hit(LPATTACK_STRUCTURE strike, Unit *WhoHit);

	void SetUndead( WORD wUndead );
	WORD GetUndead( void );

	TemplateList <Unit> *GetBackpack();
	void SetBackpack(TemplateList <Unit> *newBackpack);

    int attacked(LPATTACK_STRUCTURE strike, Unit *Mechant){ return Unit::attacked( strike, Mechant ); };

    CString GetName( WORD wLang );
    void    SetName( CString csName );
    bool    IsNameOverriden();

    void VaporizeUnit( void );

    DWORD GetQty();
    void  SetQty( DWORD newQty );
    void  Add( DWORD qty = 1 );
    void  Remove( DWORD qty = 1 );
    bool  IsUnique( void );
    void  SetUnique( void );

    virtual long ViewFlag( unsigned long dwFlagID, long lDefaultValue = 0 );

private:	
    DWORD qty;
    bool  uniqueState;    
    
    virtual ~Objects();

	WORD wUndead;

	TemplateList <Unit> *backpack;

    string csOverridenName;
};

#endif // !defined(AFX_OBJECTS_H__ED5A8764_A9CC_11D0_9B9E_444553540000__INCLUDED_)
