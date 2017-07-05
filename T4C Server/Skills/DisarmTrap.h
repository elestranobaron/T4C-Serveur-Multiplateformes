// DisarmTrap.h: interface for the DisarmTrap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISARMTRAP_H__AEF4A704_C403_11D1_ADA1_00E029058623__INCLUDED_)
#define AFX_DISARMTRAP_H__AEF4A704_C403_11D1_ADA1_00E029058623__INCLUDED_

#include "Skills.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class DisarmTrap  
{
public:
	DisarmTrap();
	void Destroy( void );
	
	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
				void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

	SKILL_ATTRIBUTES s_saAttrib;
};

#endif // !defined(AFX_DISARMTRAP_H__AEF4A704_C403_11D1_ADA1_00E029058623__INCLUDED_)
