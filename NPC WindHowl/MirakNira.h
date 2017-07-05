// MirakNira.h: interface for the MirakNira class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIRAKNIRA_H__C944C5B0_86C5_11D1_BDE7_00E029058623__INCLUDED_)
#define AFX_MIRAKNIRA_H__C944C5B0_86C5_11D1_BDE7_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class MirakNira : public NPCstructure  
{
public:
	MirakNira();
	virtual ~MirakNira();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_MIRAKNIRA_H__C944C5B0_86C5_11D1_BDE7_00E029058623__INCLUDED_)
