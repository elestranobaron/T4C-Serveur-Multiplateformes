// Bow.h: interface for the Bow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOW_H__40CA51B4_D762_11D0_B566_00E029058623__INCLUDED_)
#define AFX_BOW_H__40CA51B4_D762_11D0_B566_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../ObjectStructure.h"

class Bow : public ObjectStructure  
{
public:
	Bow();
	virtual ~Bow();
	
	void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );

    static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_BOW_H__40CA51B4_D762_11D0_B566_00E029058623__INCLUDED_)
