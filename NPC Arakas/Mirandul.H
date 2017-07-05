// Mirandul.h: interface for the Mirandul class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIRANDUL_H__53CB2377_AA4A_11D1_AD5F_00E029058623__INCLUDED_)
#define AFX_MIRANDUL_H__53CB2377_AA4A_11D1_AD5F_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class Mirandul : public NPCstructure  
{
public:
        Mirandul();
        virtual ~Mirandul();

	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
};

#endif // !defined(AFX_MIRANDUL_H__53CB2377_AA4A_11D1_AD5F_00E029058623__INCLUDED_)
