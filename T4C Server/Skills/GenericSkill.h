// GenericSkill.h: interface for the GenericSkill class.
//
//////////////////////////////////////////////////////////////////////

// This is a template used for 'craft' skills, which are used by NPCs.

#if !defined(AFX_GENERICSKILL_H__D375A3A3_F9A1_11D2_84EC_00E02922FA40__INCLUDED_)
#define AFX_GENERICSKILL_H__D375A3A3_F9A1_11D2_84EC_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Skills.h"

class GenericSkill  
{
public:
	GenericSkill();

	void Destroy( void );
	
	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func( DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
					void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill );

	SKILL_ATTRIBUTES s_saAttrib;
};

#endif // !defined(AFX_GENERICSKILL_H__D375A3A3_F9A1_11D2_84EC_00E02922FA40__INCLUDED_)
