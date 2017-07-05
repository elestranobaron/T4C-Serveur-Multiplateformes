// BrotherNiuss.h: interface for the BrotherNiuss class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROTHERNIUSS_H__C944C5AA_86C5_11D1_BDE7_00E029058623__INCLUDED_)
#define AFX_BROTHERNIUSS_H__C944C5AA_86C5_11D1_BDE7_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class BrotherNiuss : public NPCstructure  
{
public:
	BrotherNiuss();
	virtual ~BrotherNiuss();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_BROTHERNIUSS_H__C944C5AA_86C5_11D1_BDE7_00E029058623__INCLUDED_)
