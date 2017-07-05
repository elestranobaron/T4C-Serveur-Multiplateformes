// PickLock.h: interface for the PickLock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICKLOCK_H__10840944_C384_11D1_AD9F_00E029058623__INCLUDED_)
#define AFX_PICKLOCK_H__10840944_C384_11D1_AD9F_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Skills.h"

class CPickLock  
{
public:
	CPickLock();
	void Destroy( void );

	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
					void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

	SKILL_ATTRIBUTES s_saAttrib;
};

#endif // !defined(AFX_PICKLOCK_H__10840944_C384_11D1_AD9F_00E029058623__INCLUDED_)
