// ElmertMerkiss.h: interface for the ElmertMerkiss class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELMERTMERKISS_H__DEE8E30C_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_ELMERTMERKISS_H__DEE8E30C_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class ElmertMerkiss : public NPCstructure  
{
public:
	ElmertMerkiss();
	virtual ~ElmertMerkiss();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif // !defined(AFX_ELMERTMERKISS_H__DEE8E30C_35F6_11D1_BD3D_00E029058623__INCLUDED_)
