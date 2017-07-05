// Karl.h: interface for the Karl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KARL_H__C944C5AD_86C5_11D1_BDE7_00E029058623__INCLUDED_)
#define AFX_KARL_H__C944C5AD_86C5_11D1_BDE7_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Karl : public NPCstructure  
{
public:
	Karl();
	virtual ~Karl();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_KARL_H__C944C5AD_86C5_11D1_BDE7_00E029058623__INCLUDED_)
