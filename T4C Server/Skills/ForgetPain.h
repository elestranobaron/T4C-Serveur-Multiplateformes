// ForgetPain.h: interface for the ForgetPain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORGETPAIN_H__22D07A04_C4D8_11D1_ADA4_00E029058623__INCLUDED_)
#define AFX_FORGETPAIN_H__22D07A04_C4D8_11D1_ADA4_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Skills.h"

class ForgetPain  
{
public:
	ForgetPain();
	virtual ~ForgetPain();

	static void OnAddPoints(Unit *lpuTrained, LPUSER_SKILL lpUserSkill, DWORD dwNbPoints);
	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
					void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

	SKILL_ATTRIBUTES s_saAttrib;
};

#endif // !defined(AFX_FORGETPAIN_H__22D07A04_C4D8_11D1_ADA4_00E029058623__INCLUDED_)
