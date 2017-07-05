// Isulgur.h: interface for the Isulgur class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISULGUR_H__DEE8E304_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_ISULGUR_H__DEE8E304_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Isulgur : public NPCstructure  
{
public:
	Isulgur();
	virtual ~Isulgur();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_ISULGUR_H__DEE8E304_35F6_11D1_BD3D_00E029058623__INCLUDED_)
