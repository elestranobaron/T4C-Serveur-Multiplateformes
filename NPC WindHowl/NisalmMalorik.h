// NisalmMalorik.h: interface for the NisalmMalorik class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NISALMMALORIK_H__C944C5B1_86C5_11D1_BDE7_00E029058623__INCLUDED_)
#define AFX_NISALMMALORIK_H__C944C5B1_86C5_11D1_BDE7_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class NisalmMalorik : public NPCstructure  
{
public:
	NisalmMalorik();
	virtual ~NisalmMalorik();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_NISALMMALORIK_H__C944C5B1_86C5_11D1_BDE7_00E029058623__INCLUDED_)
