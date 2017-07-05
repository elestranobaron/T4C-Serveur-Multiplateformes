// GemOfLife.h: interface for the GemOfLife class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEMOFLIFE_H__849DA304_BE6D_11D1_AD91_00E029058623__INCLUDED_)
#define AFX_GEMOFLIFE_H__849DA304_BE6D_11D1_AD91_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\ObjectStructure.h"

class GemOfLife : public ObjectStructure  
{
public:
	GemOfLife();
	virtual ~GemOfLife();

	void OnDeath( UNIT_FUNC_PROTOTYPE );

	static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_GEMOFLIFE_H__849DA304_BE6D_11D1_AD91_00E029058623__INCLUDED_)
