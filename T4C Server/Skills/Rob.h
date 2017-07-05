// Rob.h: interface for the Rob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROB_H__CB86BB9B_74D6_11D2_8447_00E02922FA40__INCLUDED_)
#define AFX_ROB_H__CB86BB9B_74D6_11D2_8447_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Skills.h"

class Rob  
{
public:
	Rob();	
    void Destroy( void );

	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
					void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

	SKILL_ATTRIBUTES s_saAttrib;

};

#endif // !defined(AFX_ROB_H__CB86BB9B_74D6_11D2_8447_00E02922FA40__INCLUDED_)
