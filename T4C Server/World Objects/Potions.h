// Potions.h: interface for the Potions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POTIONS_H__DEC4A376_4EDB_11D1_BD70_00E029058623__INCLUDED_)
#define AFX_POTIONS_H__DEC4A376_4EDB_11D1_BD70_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\ObjectStructure.h"

class Potions : public ObjectStructure  
{
public:
	Potions();
	virtual ~Potions();

	void OnInitialise( UNIT_FUNC_PROTOTYPE );
	void OnUse( UNIT_FUNC_PROTOTYPE );

	static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_POTIONS_H__DEC4A376_4EDB_11D1_BD70_00E029058623__INCLUDED_)
