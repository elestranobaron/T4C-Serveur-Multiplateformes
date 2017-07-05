// SkipperRedBeard.h: interface for the SkipperRedBeard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKIPPERREDBEARD_H__C944C5B5_86C5_11D1_BDE7_00E029058623__INCLUDED_)
#define AFX_SKIPPERREDBEARD_H__C944C5B5_86C5_11D1_BDE7_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class SkipperRedBeard : public NPCstructure  
{
public:
	SkipperRedBeard();
	virtual ~SkipperRedBeard();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_SKIPPERREDBEARD_H__C944C5B5_86C5_11D1_BDE7_00E029058623__INCLUDED_)
