// Kalastor.h: interface for the Kalastor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KALASTOR_H__DEE8E316_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_KALASTOR_H__DEE8E316_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Kalastor : public NPCstructure  
{
public:
	Kalastor();
	virtual ~Kalastor();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif // !defined(AFX_KALASTOR_H__DEE8E316_35F6_11D1_BD3D_00E029058623__INCLUDED_)
