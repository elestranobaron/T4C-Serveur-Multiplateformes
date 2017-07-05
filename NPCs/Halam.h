// Halam.h: interface for the Halam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HALAM_H__53CB2375_AA4A_11D1_AD5F_00E029058623__INCLUDED_)
#define AFX_HALAM_H__53CB2375_AA4A_11D1_AD5F_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Halam : public NPCstructure  
{
public:
	Halam();
	virtual ~Halam();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_HALAM_H__53CB2375_AA4A_11D1_AD5F_00E029058623__INCLUDED_)
