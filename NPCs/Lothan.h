// Lothan.h: interface for the Lothan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOTHAN_H__DEE8E311_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_LOTHAN_H__DEE8E311_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Lothan : public NPCstructure  
{
public:
	Lothan();
	virtual ~Lothan();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
    void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif // !defined(AFX_LOTHAN_H__DEE8E311_35F6_11D1_BD3D_00E029058623__INCLUDED_)
