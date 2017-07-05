// Jalus.h: interface for the Jalus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JALUS_H__53CB2374_AA4A_11D1_AD5F_00E029058623__INCLUDED_)
#define AFX_JALUS_H__53CB2374_AA4A_11D1_AD5F_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Jalus : public NPCstructure  
{
public:
	Jalus();
	virtual ~Jalus();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_JALUS_H__53CB2374_AA4A_11D1_AD5F_00E029058623__INCLUDED_)
