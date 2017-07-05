// Geena.h: interface for the Geena class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEENA_H__53CB2376_AA4A_11D1_AD5F_00E029058623__INCLUDED_)
#define AFX_GEENA_H__53CB2376_AA4A_11D1_AD5F_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Geena : public NPCstructure  
{
public:
	Geena();
	virtual ~Geena();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_GEENA_H__53CB2376_AA4A_11D1_AD5F_00E029058623__INCLUDED_)
