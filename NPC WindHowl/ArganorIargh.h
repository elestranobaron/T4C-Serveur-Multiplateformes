// ArganorIargh.h: interface for the ArganorIargh class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARGANORIARGH_H__C944C5AC_86C5_11D1_BDE7_00E029058623__INCLUDED_)
#define AFX_ARGANORIARGH_H__C944C5AC_86C5_11D1_BDE7_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class ArganorIargh : public NPCstructure  
{
public:
	ArganorIargh();
	virtual ~ArganorIargh();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_ARGANORIARGH_H__C944C5AC_86C5_11D1_BDE7_00E029058623__INCLUDED_)
