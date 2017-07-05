// Malaar.h: interface for the Malaar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MALAAR_H__C944C5A6_86C5_11D1_BDE7_00E029058623__INCLUDED_)
#define AFX_MALAAR_H__C944C5A6_86C5_11D1_BDE7_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Malaar : public NPCstructure  
{
public:
	Malaar();
	virtual ~Malaar();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_MALAAR_H__C944C5A6_86C5_11D1_BDE7_00E029058623__INCLUDED_)
