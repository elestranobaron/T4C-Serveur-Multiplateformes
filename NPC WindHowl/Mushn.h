// Mushn.h: interface for the Mushn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSHN_H__EE1E018C_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_MUSHN_H__EE1E018C_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Mushn : public NPCstructure  
{
public:
	Mushn();
	virtual ~Mushn();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_MUSHN_H__EE1E018C_878D_11D1_BDE9_00E029058623__INCLUDED_)
