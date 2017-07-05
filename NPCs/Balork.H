// Balork.h: interface for the Balork class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BALORK_H__53CB2377_AA4A_11D1_AD5F_00E029058623__INCLUDED_)
#define AFX_BALORK_H__53CB2377_AA4A_11D1_AD5F_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class _Balork : public NPCstructure  
{
public:
    _Balork();
    virtual ~_Balork();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_BALORK_H__53CB2377_AA4A_11D1_AD5F_00E029058623__INCLUDED_)
