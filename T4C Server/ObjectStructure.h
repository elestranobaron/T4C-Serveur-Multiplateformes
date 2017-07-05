// ObjectStructure.h: interface for the ObjectStructure class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTSTRUCTURE_H__85695826_0609_11D1_AD66_00E029058623__INCLUDED_)
#define AFX_OBJECTSTRUCTURE_H__85695826_0609_11D1_AD66_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "stdafx.h"
#include "StaticFlags.h"
#include "random.h"
#include "TFC_MAIN.h"
#include "Broadcast.h"
#include "Unit.h"
#include "Character.h"
#include "ObjectListing.h"
#include "ObjectFlagsListing.h"
#include "blockinglisting.h"
#include "_item.h"
#include "Lock.h"

extern Random rnd;
extern Broadcast BCast;

class __declspec(dllexport) ObjectStructure : public BaseReferenceMessages, public _item, /*public StaticFlags,*/ public CLock
{
public:
	ObjectStructure();
	virtual ~ObjectStructure();
	
	virtual void OnInitialise( UNIT_FUNC_PROTOTYPE );
	void OnGetUnitStructure( UNIT_FUNC_PROTOTYPE );
	
	virtual void OnAttack( UNIT_FUNC_PROTOTYPE );
	virtual void OnAttacked( UNIT_FUNC_PROTOTYPE );
	virtual void OnDisturbed( UNIT_FUNC_PROTOTYPE );
	virtual void OnUse( UNIT_FUNC_PROTOTYPE );
	virtual void OnNoMoreShots( UNIT_FUNC_PROTOTYPE );
    virtual void OnHit( UNIT_FUNC_PROTOTYPE );
    virtual void OnAttackHit( UNIT_FUNC_PROTOTYPE );
	
	virtual void OnEquip( UNIT_FUNC_PROTOTYPE );
	virtual void OnUnequip( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_OBJECTSTRUCTURE_H__85695826_0609_11D1_AD66_00E029058623__INCLUDED_)
