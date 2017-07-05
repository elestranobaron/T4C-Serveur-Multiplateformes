// Markam.h: interface for the Markam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MARKAM_H__DEE8E305_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_MARKAM_H__DEE8E305_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Markam : public NPCstructure  
{
public:
	Markam();
	virtual ~Markam();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );

};

#endif // !defined(AFX_MARKAM_H__DEE8E305_35F6_11D1_BD3D_00E029058623__INCLUDED_)
