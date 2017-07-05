// Pray.h: interface for the Pray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRAY_H__311E6BD4_62A0_11D1_BD96_00E029058623__INCLUDED_)
#define AFX_PRAY_H__311E6BD4_62A0_11D1_BD96_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Skills.h"

class Pray  
{
public:
	Pray();
	void Destroy( void );
	
	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
					void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

	SKILL_ATTRIBUTES s_saAttrib;
};

#endif // !defined(AFX_PRAY_H__311E6BD4_62A0_11D1_BD96_00E029058623__INCLUDED_)
