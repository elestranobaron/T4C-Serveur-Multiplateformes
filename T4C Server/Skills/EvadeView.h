// EvadeView.h: interface for the EvadeView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVADEVIEW_H__8D5D4C14_C425_11D1_ADA2_00E029058623__INCLUDED_)
#define AFX_EVADEVIEW_H__8D5D4C14_C425_11D1_ADA2_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Skills.h"

class EvadeView  
{
public:
	EvadeView();
	void Destroy( void );

	static void OnAddPoints(Unit *lpuTrained, LPUSER_SKILL lpUserSkill, DWORD dwNbPoints);
	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
					void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

	SKILL_ATTRIBUTES s_saAttrib;
};

#endif // !defined(AFX_EVADEVIEW_H__8D5D4C14_C425_11D1_ADA2_00E029058623__INCLUDED_)
