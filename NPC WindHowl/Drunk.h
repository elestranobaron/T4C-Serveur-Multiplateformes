// Drunk.h: interface for the Drunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRUNK_H__EE1E0193_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_DRUNK_H__EE1E0193_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Drunk : public NPCstructure  
{
public:
	Drunk();
	virtual ~Drunk();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_DRUNK_H__EE1E0193_878D_11D1_BDE9_00E029058623__INCLUDED_)
