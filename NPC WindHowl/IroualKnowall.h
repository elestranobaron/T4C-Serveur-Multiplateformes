// IroualKnowall.h: interface for the IroualKnowall class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IROUALKNOWALL_H__EE1E0195_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_IROUALKNOWALL_H__EE1E0195_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class IroualKnowall : public NPCstructure  
{
public:
	IroualKnowall();
	virtual ~IroualKnowall();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_IROUALKNOWALL_H__EE1E0195_878D_11D1_BDE9_00E029058623__INCLUDED_)
