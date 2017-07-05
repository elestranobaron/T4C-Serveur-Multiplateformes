// Kilhiam.h: interface for the Kilhiam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KILHIAM_H__DEE8E30E_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_KILHIAM_H__DEE8E30E_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Kilhiam : public NPCstructure  
{
public:
        Kilhiam();
        virtual ~Kilhiam();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );

};

#endif // !defined(AFX_KILHIAM_H__DEE8E30E_35F6_11D1_BD3D_00E029058623__INCLUDED_)
