// FastHealing.h: interface for the FastHealing class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FASTHEALING_H__FBD80E7E_759F_11D2_8448_00E02922FA40__INCLUDED_)
#define AFX_FASTHEALING_H__FBD80E7E_759F_11D2_8448_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Skills.h"

class FastHealing  
{
public:
	FastHealing();
    void Destroy( void );

	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
					void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

	SKILL_ATTRIBUTES s_saAttrib;

};

#endif // !defined(AFX_FASTHEALING_H__FBD80E7E_759F_11D2_8448_00E02922FA40__INCLUDED_)
