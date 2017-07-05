// SamilAlgder.h: interface for the SamilAlgder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMILALGDER_H__C944C5A7_86C5_11D1_BDE7_00E029058623__INCLUDED_)
#define AFX_SAMILALGDER_H__C944C5A7_86C5_11D1_BDE7_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class SamilAlgder : public NPCstructure  
{
public:
	SamilAlgder();
	virtual ~SamilAlgder();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_SAMILALGDER_H__C944C5A7_86C5_11D1_BDE7_00E029058623__INCLUDED_)
