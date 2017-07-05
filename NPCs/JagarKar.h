// JagarKar.h: interface for the JagarKar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JAGARKAR_H__DEE8E313_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_JAGARKAR_H__DEE8E313_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class JagarKar : public NPCstructure  
{
public:
	JagarKar();
	virtual ~JagarKar();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_JAGARKAR_H__DEE8E313_35F6_11D1_BD3D_00E029058623__INCLUDED_)
