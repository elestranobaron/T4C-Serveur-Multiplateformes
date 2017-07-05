// JurnistakrKira.h: interface for the JurnistakrKira class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JURNISTAKRKIRA_H__C944C5A8_86C5_11D1_BDE7_00E029058623__INCLUDED_)
#define AFX_JURNISTAKRKIRA_H__C944C5A8_86C5_11D1_BDE7_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class JurnistakrKira : public NPCstructure  
{
public:
	JurnistakrKira();
	virtual ~JurnistakrKira();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_JURNISTAKRKIRA_H__C944C5A8_86C5_11D1_BDE7_00E029058623__INCLUDED_)
