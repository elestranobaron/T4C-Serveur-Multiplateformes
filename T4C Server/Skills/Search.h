// Search.h: interface for the Search class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCH_H__58ED3D01_B49F_11D3_85E0_00E02922FA40__INCLUDED_)
#define AFX_SEARCH_H__58ED3D01_B49F_11D3_85E0_00E02922FA40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Skills.h"

class Search  
{
public:
	Search();
	void Destroy( void );

	static LPSKILLPNTFUNC lpOnAddPnts;

	static int Func(DWORD dwReason, Unit *self, Unit *medium, Unit *target, 
					void *valueIN, void *valueOUT, LPUSER_SKILL lpusUserSkill);

	SKILL_ATTRIBUTES s_saAttrib;
};

#endif // !defined(AFX_SEARCH_H__58ED3D01_B49F_11D3_85E0_00E02922FA40__INCLUDED_)
