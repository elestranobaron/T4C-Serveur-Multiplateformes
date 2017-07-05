// Murmuntag.h: interface for the Murmuntag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MURMUNTAG_H__DEE8E30B_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_MURMUNTAG_H__DEE8E30B_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Murmuntag : public NPCstructure  
{
public:
	Murmuntag();
	virtual ~Murmuntag();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_MURMUNTAG_H__DEE8E30B_35F6_11D1_BD3D_00E029058623__INCLUDED_)
