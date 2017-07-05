// FirstAid.h: interface for the FirstAid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIRSTAID_H__95A91053_5FAF_11D1_BD8E_00E029058623__INCLUDED_)
#define AFX_FIRSTAID_H__95A91053_5FAF_11D1_BD8E_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Skills.h"

class FirstAid  
{
public:
	FirstAid();
	void Destroy( void );

	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
				void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

    static void ExhaustRemovallCallback( EFFECT_FUNC_PROTOTYPE );

	SKILL_ATTRIBUTES s_saAttrib;


};

#endif // !defined(AFX_FIRSTAID_H__95A91053_5FAF_11D1_BD8E_00E029058623__INCLUDED_)
