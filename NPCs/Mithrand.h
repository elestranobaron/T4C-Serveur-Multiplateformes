// Mithrand.h: interface for the Mithrand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MITHRAND_H__DEE8E303_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_MITHRAND_H__DEE8E303_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Mithrand : public NPCstructure  
{
public:
	Mithrand();
	virtual ~Mithrand();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_MITHRAND_H__DEE8E303_35F6_11D1_BD3D_00E029058623__INCLUDED_)
