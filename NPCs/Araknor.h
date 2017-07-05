// Araknor.h: interface for the Araknor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARAKNOR_H__DEE8E310_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_ARAKNOR_H__DEE8E310_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Araknor : public NPCstructure  
{
public:
	Araknor();
	virtual ~Araknor();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	//void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif // !defined(AFX_ARAKNOR_H__DEE8E310_35F6_11D1_BD3D_00E029058623__INCLUDED_)
