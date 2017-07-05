// TwoWeapons.h: interface for the TwoWeapons class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TWOWEAPONS_H__06136B84_C7DF_11D1_ADA9_00E029058623__INCLUDED_)
#define AFX_TWOWEAPONS_H__06136B84_C7DF_11D1_ADA9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Skills.h"

class TwoWeapons  
{
public:
	TwoWeapons();
	virtual ~TwoWeapons();
	
	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
					void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

	SKILL_ATTRIBUTES s_saAttrib;
};

#endif // !defined(AFX_TWOWEAPONS_H__06136B84_C7DF_11D1_ADA9_00E029058623__INCLUDED_)
