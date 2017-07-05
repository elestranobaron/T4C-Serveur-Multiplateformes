// GeorgeTheIIIrd.h: interface for the GeorgeTheIIIrd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEORGETHEIIIRD_H__EE1E0185_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_GEORGETHEIIIRD_H__EE1E0185_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class GeorgeTheIIIrd : public NPCstructure  
{
public:
	GeorgeTheIIIrd();
	virtual ~GeorgeTheIIIrd();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_GEORGETHEIIIRD_H__EE1E0185_878D_11D1_BDE9_00E029058623__INCLUDED_)
