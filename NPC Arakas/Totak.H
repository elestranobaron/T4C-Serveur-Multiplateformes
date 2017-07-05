// Totak.h: interface for the Totak class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOTAK_H__53CB2377_AA4A_11D1_AD5F_00E029058623__INCLUDED_)
#define AFX_TOTAK_H__53CB2377_AA4A_11D1_AD5F_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Totak : public NPCstructure  
{
public:
        Totak();
        virtual ~Totak();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_TOTAK_H__53CB2377_AA4A_11D1_AD5F_00E029058623__INCLUDED_)
