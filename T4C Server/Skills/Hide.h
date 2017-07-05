// Hide.h: interface for the Hide class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HIDE_H__D287BE5D_B3D5_11D3_85DF_00E02922FA40__INCLUDED_)
#define AFX_HIDE_H__D287BE5D_B3D5_11D3_85DF_00E02922FA40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Skills.h"

class Hide  
{
public:
	Hide();
	void Destroy( void );

	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
					void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

	SKILL_ATTRIBUTES s_saAttrib;

};

#endif // !defined(AFX_HIDE_H__D287BE5D_B3D5_11D3_85DF_00E02922FA40__INCLUDED_)
