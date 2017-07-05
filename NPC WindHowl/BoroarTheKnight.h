// BoroarTheKnight.h: interface for the BoroarTheKnight class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOROARTHEKNIGHT_H__EE1E018B_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_BOROARTHEKNIGHT_H__EE1E018B_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class BoroarTheKnight : public NPCstructure  
{
public:
	BoroarTheKnight();
	virtual ~BoroarTheKnight();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_BOROARTHEKNIGHT_H__EE1E018B_878D_11D1_BDE9_00E029058623__INCLUDED_)
