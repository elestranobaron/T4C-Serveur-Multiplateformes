// Yolak.h: interface for the Yolak class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YOLAK_H__6E349274_AFA2_11D1_AD6E_00E029058623__INCLUDED_)
#define AFX_YOLAK_H__6E349274_AFA2_11D1_AD6E_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Yolak : public NPCstructure  
{
public:
	Yolak();
	virtual ~Yolak();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_YOLAK_H__6E349274_AFA2_11D1_AD6E_00E029058623__INCLUDED_)
