// DestinyGem.h: interface for the DestinyGem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DESTINYGEM_H__1CAB2F44_BDC8_11D1_AD90_00E029058623__INCLUDED_)
#define AFX_DESTINYGEM_H__1CAB2F44_BDC8_11D1_AD90_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\ObjectStructure.h"

class DestinyGem : public ObjectStructure  
{
public:
	DestinyGem();
	virtual ~DestinyGem();

	void OnInitialise( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );

	static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_DESTINYGEM_H__1CAB2F44_BDC8_11D1_AD90_00E029058623__INCLUDED_)
