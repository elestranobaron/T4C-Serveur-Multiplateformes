// LiurnClar.h: interface for the LiurnClar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIURNCLAR_H__C944C5B6_86C5_11D1_BDE7_00E029058623__INCLUDED_)
#define AFX_LIURNCLAR_H__C944C5B6_86C5_11D1_BDE7_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class LiurnClar : public NPCstructure  
{
public:
	LiurnClar();
	virtual ~LiurnClar();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_LIURNCLAR_H__C944C5B6_86C5_11D1_BDE7_00E029058623__INCLUDED_)
