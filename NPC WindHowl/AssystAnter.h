// AssystAnter.h: interface for the AssystAnter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSYSTANTER_H__C944C5B2_86C5_11D1_BDE7_00E029058623__INCLUDED_)
#define AFX_ASSYSTANTER_H__C944C5B2_86C5_11D1_BDE7_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class AssystAnter : public NPCstructure  
{
public:
	AssystAnter();
	virtual ~AssystAnter();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_ASSYSTANTER_H__C944C5B2_86C5_11D1_BDE7_00E029058623__INCLUDED_)
