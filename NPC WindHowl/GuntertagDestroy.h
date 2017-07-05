// GuntertagDestroy.h: interface for the GuntertagDestroy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUNTERTAGDESTROY_H__EE1E0186_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_GUNTERTAGDESTROY_H__EE1E0186_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class GuntertagDestroy : public NPCstructure  
{
public:
	GuntertagDestroy();
	virtual ~GuntertagDestroy();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_GUNTERTAGDESTROY_H__EE1E0186_878D_11D1_BDE9_00E029058623__INCLUDED_)
