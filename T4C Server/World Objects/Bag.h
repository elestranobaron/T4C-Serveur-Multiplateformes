// Bag.h: interface for the Bag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BAG_H__F2F782C3_FFC1_11D0_88FF_00E029058623__INCLUDED_)
#define AFX_BAG_H__F2F782C3_FFC1_11D0_88FF_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\ObjectStructure.h"

class Bag : public ObjectStructure
{
public:
	Bag(WORD ObjectType, WORD BagSize);
	virtual ~Bag();

	void OnView( UNIT_FUNC_PROTOTYPE );

	static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_BAG_H__F2F782C3_FFC1_11D0_88FF_00E029058623__INCLUDED_)
