// KirlorDhul.h: interface for the KirlorDhul class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KIRLORDHUL_H__82A36E43_3120_11D1_BD34_00E029058623__INCLUDED_)
#define AFX_KIRLORDHUL_H__82A36E43_3120_11D1_BD34_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class KirlorDhul : public NPCstructure  
{
public:
	KirlorDhul();
	virtual ~KirlorDhul();

	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_KIRLORDHUL_H__82A36E43_3120_11D1_BD34_00E029058623__INCLUDED_)
