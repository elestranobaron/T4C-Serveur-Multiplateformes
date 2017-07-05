// ArmorPenetration.h: interface for the ArmorPenetration class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARMORPENETRATION_H__1E9CCE82_15AF_11D2_8374_00E02922FA40__INCLUDED_)
#define AFX_ARMORPENETRATION_H__1E9CCE82_15AF_11D2_8374_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Skills.h"

class ArmorPenetration  
{
public:
	ArmorPenetration();
	
    static LPSKILLPNTFUNC lpOnAddPnts;

    static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
					void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

	SKILL_ATTRIBUTES s_saAttrib;

};

#endif // !defined(AFX_ARMORPENETRATION_H__1E9CCE82_15AF_11D2_8374_00E02922FA40__INCLUDED_)
