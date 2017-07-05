// WoundedGuard.h: interface for the WoundedGuard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WOUNDEDGUARD_H__EE1E0189_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_WOUNDEDGUARD_H__EE1E0189_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class WoundedGuard : public NPCstructure  
{
public:
	WoundedGuard();
	virtual ~WoundedGuard();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_WOUNDEDGUARD_H__EE1E0189_878D_11D1_BDE9_00E029058623__INCLUDED_)
