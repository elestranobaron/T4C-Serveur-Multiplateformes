// Eraka.h: interface for the Eraka class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERAKA_H__EE1E018A_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_ERAKA_H__EE1E018A_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Eraka : public NPCstructure  
{
public:
	Eraka();
	virtual ~Eraka();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_ERAKA_H__EE1E018A_878D_11D1_BDE9_00E029058623__INCLUDED_)
