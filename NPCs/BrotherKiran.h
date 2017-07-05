// BrotherKiran.h: interface for the BrotherKiran class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROTHERKIRAN_H__DEE8E309_35F6_11D1_BD3D_00E029058623__INCLUDED_)
#define AFX_BROTHERKIRAN_H__DEE8E309_35F6_11D1_BD3D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class BrotherKiran : public NPCstructure  
{
public:
	BrotherKiran();
	virtual ~BrotherKiran();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );

};

#endif // !defined(AFX_BROTHERKIRAN_H__DEE8E309_35F6_11D1_BD3D_00E029058623__INCLUDED_)
