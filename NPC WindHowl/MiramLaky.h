// MiramLaky.h: interface for the MiramLaky class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIRAMLAKY_H__EE1E018D_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_MIRAMLAKY_H__EE1E018D_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class MiramLaky : public NPCstructure  
{
public:
	MiramLaky();
	virtual ~MiramLaky();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_MIRAMLAKY_H__EE1E018D_878D_11D1_BDE9_00E029058623__INCLUDED_)
