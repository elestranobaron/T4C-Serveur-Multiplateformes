// Guardman.h: interface for the Guardman class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUARDMAN_H__DEE8E30D_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_GUARDMAN_H__DEE8E30D_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Guardman : public NPCstructure  
{
public:
	Guardman();
	virtual ~Guardman();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif // !defined(AFX_GUARDMAN_H__DEE8E30D_35F6_11D1_BD3D_00E029058623__INCLUDED_)
