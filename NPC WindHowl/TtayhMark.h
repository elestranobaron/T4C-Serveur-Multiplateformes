// TtayhMark.h: interface for the TtayhMark class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TTAYHMARK_H__EE1E0190_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_TTAYHMARK_H__EE1E0190_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class TtayhMark : public NPCstructure  
{
public:
	TtayhMark();
	virtual ~TtayhMark();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_TTAYHMARK_H__EE1E0190_878D_11D1_BDE9_00E029058623__INCLUDED_)
