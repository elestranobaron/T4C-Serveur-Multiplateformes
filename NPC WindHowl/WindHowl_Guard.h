// WindHowl_Guard.h: interface for the WindHowl_Guard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDHOWL_GUARD_H__EE1E0188_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_WINDHOWL_GUARD_H__EE1E0188_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class WindHowl_Guard : public NPCstructure  
{
public:
	WindHowl_Guard();
	virtual ~WindHowl_Guard();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_WINDHOWL_GUARD_H__EE1E0188_878D_11D1_BDE9_00E029058623__INCLUDED_)
