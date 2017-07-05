	// MarnecSunim.h: interface for the MarnecSunim class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MARNECSUNIM_H__DEE8E312_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_MARNECSUNIM_H__DEE8E312_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class MarnecSunim : public NPCstructure  
{
public:
	MarnecSunim();
	virtual ~MarnecSunim();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_MARNECSUNIM_H__DEE8E312_35F6_11D1_BD3D_00E029058623__INCLUDED_)
