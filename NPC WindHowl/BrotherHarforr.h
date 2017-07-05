// BrotherHarforr.h: interface for the BrotherHarforr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROTHERHARFORR_H__C944C5AB_86C5_11D1_BDE7_00E029058623__INCLUDED_)
#define AFX_BROTHERHARFORR_H__C944C5AB_86C5_11D1_BDE7_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class BrotherHarforr : public NPCstructure  
{
public:
	BrotherHarforr();
	virtual ~BrotherHarforr();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_BROTHERHARFORR_H__C944C5AB_86C5_11D1_BDE7_00E029058623__INCLUDED_)
