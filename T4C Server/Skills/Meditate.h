// Meditate.h: interface for the Meditate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDITATE_H__99A66227_6209_11D1_BD94_00E029058623__INCLUDED_)
#define AFX_MEDITATE_H__99A66227_6209_11D1_BD94_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Skills.h"

class Meditate  
{
public:
	Meditate();
	void Destroy( void );
	
	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
					void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

	SKILL_ATTRIBUTES s_saAttrib;
};

#endif // !defined(AFX_MEDITATE_H__99A66227_6209_11D1_BD94_00E029058623__INCLUDED_)
