// Shadow.h: interface for the Shadow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHADOW_H__DEE8E315_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_SHADOW_H__DEE8E315_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Shadow : public NPCstructure  
{
public:
	Shadow();
	virtual ~Shadow();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif // !defined(AFX_SHADOW_H__DEE8E315_35F6_11D1_BD3D_00E029058623__INCLUDED_)
