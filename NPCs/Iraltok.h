// Iraltok.h: interface for the Iraltok class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IRALTOK_H__DEE8E30F_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_IRALTOK_H__DEE8E30F_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Iraltok : public NPCstructure  
{
public:
	Iraltok();
	virtual ~Iraltok();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
    void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif // !defined(AFX_IRALTOK_H__DEE8E30F_35F6_11D1_BD3D_00E029058623__INCLUDED_)
