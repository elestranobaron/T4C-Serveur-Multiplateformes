// Sigfried.h: interface for the Sigfried class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGFRIED_H__DEE8E306_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_SIGFRIED_H__DEE8E306_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Sigfried : public NPCstructure  
{
public:
	Sigfried();
	virtual ~Sigfried();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );

};

#endif // !defined(AFX_SIGFRIED_H__DEE8E306_35F6_11D1_BD3D_00E029058623__INCLUDED_)
