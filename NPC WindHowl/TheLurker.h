// TheLurker.h: interface for the TheLurker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THELURKER_H__EE1E0191_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_THELURKER_H__EE1E0191_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class TheLurker : public NPCstructure  
{
public:
	TheLurker();
	virtual ~TheLurker();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

    void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_THELURKER_H__EE1E0191_878D_11D1_BDE9_00E029058623__INCLUDED_)
