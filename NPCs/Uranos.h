// Uranos.h: interface for the Uranos class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_URANOS_H__DEE8E30E_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_URANOS_H__DEE8E30E_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Uranos : public NPCstructure  
{
public:
	Uranos();
	virtual ~Uranos();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_URANOS_H__DEE8E30E_35F6_11D1_BD3D_00E029058623__INCLUDED_)
