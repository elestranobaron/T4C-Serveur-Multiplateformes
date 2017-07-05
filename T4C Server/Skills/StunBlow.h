// StunBlow.h: interface for the StunBlow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STUNBLOW_H__0753FE24_5546_11D1_BD7A_00E029058623__INCLUDED_)
#define AFX_STUNBLOW_H__0753FE24_5546_11D1_BD7A_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Skills.h"

class StunBlow  
{
public:	
	StunBlow();
	void Destroy( void );

	static void TimerStunRemovallCallback( EFFECT_FUNC_PROTOTYPE );

	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
					void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

	SKILL_ATTRIBUTES s_saAttrib;
};

#endif // !defined(AFX_STUNBLOW_H__0753FE24_5546_11D1_BD7A_00E029058623__INCLUDED_)
