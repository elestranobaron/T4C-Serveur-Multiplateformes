// Parry.h: interface for the Parry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARRY_H__99A66226_6209_11D1_BD94_00E029058623__INCLUDED_)
#define AFX_PARRY_H__99A66226_6209_11D1_BD94_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Skills.h"

class Parry  
{
public:
	Parry();
	void Destroy( void );

	static void OnAddPoints(Unit *lpuTrained, LPUSER_SKILL lpUserSkill, DWORD dwNbPoints);
	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
					void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

	SKILL_ATTRIBUTES s_saAttrib;

};

#endif // !defined(AFX_PARRY_H__99A66226_6209_11D1_BD94_00E029058623__INCLUDED_)
