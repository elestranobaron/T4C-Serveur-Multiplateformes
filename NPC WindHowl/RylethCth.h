// RylethCth.h: interface for the RylethCth class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RYLETHCTH_H__EE1E0183_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_RYLETHCTH_H__EE1E0183_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class RylethCth : public NPCstructure  
{
public:
	RylethCth();
	virtual ~RylethCth();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_RYLETHCTH_H__EE1E0183_878D_11D1_BDE9_00E029058623__INCLUDED_)
