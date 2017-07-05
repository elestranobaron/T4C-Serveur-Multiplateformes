// Food.h: interface for the Food class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOOD_H__DEC4A375_4EDB_11D1_BD70_00E029058623__INCLUDED_)
#define AFX_FOOD_H__DEC4A375_4EDB_11D1_BD70_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\ObjectStructure.h"

class Food : public ObjectStructure  
{
public:
	Food();
	virtual ~Food();

	void OnUse( UNIT_FUNC_PROTOTYPE );

	static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_FOOD_H__DEC4A375_4EDB_11D1_BD70_00E029058623__INCLUDED_)
