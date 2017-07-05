// HumanDrunk.h: interface for the HumanDrunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HUMANDRUNK_H__EE1E0194_878D_11D1_BDE9_00E029058623__INCLUDED_)
#define AFX_HUMANDRUNK_H__EE1E0194_878D_11D1_BDE9_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class HumanDrunk : public NPCstructure  
{
public:
	HumanDrunk();
	virtual ~HumanDrunk();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_HUMANDRUNK_H__EE1E0194_878D_11D1_BDE9_00E029058623__INCLUDED_)
