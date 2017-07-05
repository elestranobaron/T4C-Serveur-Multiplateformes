// Armor.h: interface for the Armor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARMOR_H__40CA51B3_D762_11D0_B566_00E029058623__INCLUDED_)
#define AFX_ARMOR_H__40CA51B3_D762_11D0_B566_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\ObjectStructure.h"

class Armor : public ObjectStructure  
{
public:
	Armor();
	virtual ~Armor();
	
	void OnAttacked( UNIT_FUNC_PROTOTYPE );

	static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_ARMOR_H__40CA51B3_D762_11D0_B566_00E029058623__INCLUDED_)
