// LanceSilversmith.h: interface for the Lance Silversmith class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANCESILVERSMITH_H__DEE8E30C_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_LANCESILVERSMITH_H__DEE8E30C_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class LanceSilversmith : public NPCstructure  
{
public:
	LanceSilversmith();
	virtual ~LanceSilversmith();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif // !defined(AFX_LANCESILVERSMITH_H__DEE8E30C_35F6_11D1_BD3D_00E029058623__INCLUDED_)
