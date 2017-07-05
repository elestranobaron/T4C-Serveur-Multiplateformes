// Gwen.h: interface for the Gwen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GWEN_H__EE1E018E_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_GWEN_H__EE1E018E_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Gwen : public NPCstructure  
{
public:
	Gwen();
	virtual ~Gwen();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_GWEN_H__EE1E018E_878D_11D1_BDE9_00E029058623__INCLUDED_)
