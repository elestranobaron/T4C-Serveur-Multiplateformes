// LaonianRikarr.h: interface for the LaonianRikarr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAONIANRIKARR_H__C944C5A9_86C5_11D1_BDE7_00E029058623__INCLUDED_)
#define AFX_LAONIANRIKARR_H__C944C5A9_86C5_11D1_BDE7_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class LaonianRikarr : public NPCstructure  
{
public:
	LaonianRikarr();
	virtual ~LaonianRikarr();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_LAONIANRIKARR_H__C944C5A9_86C5_11D1_BDE7_00E029058623__INCLUDED_)
