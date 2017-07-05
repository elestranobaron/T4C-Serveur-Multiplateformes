// LordTravis.h: interface for the LordTravis class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LORDTRAVIS_H__EE1E0187_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_LORDTRAVIS_H__EE1E0187_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class LordTravis : public NPCstructure  
{
public:
	LordTravis();
	virtual ~LordTravis();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_LORDTRAVIS_H__EE1E0187_878D_11D1_BDE9_00E029058623__INCLUDED_)
