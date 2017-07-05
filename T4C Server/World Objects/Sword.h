// Sword.h: interface for the Sword class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWORD_H__AA87D2A4_D6BD_11D0_B565_00E029058623__INCLUDED_)
#define AFX_SWORD_H__AA87D2A4_D6BD_11D0_B565_00E029058623__INCLUDED_

#include "..\ObjectStructure.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class Sword : public ObjectStructure
{
public:
	Sword();
	virtual ~Sword();

	//Create(WORD object_type, WORD equip_where, WORD exhaust, WORD Att, WORD Str, WORD Dex, 
	//	WORD dice_roll, WORD plus_to_hit);

	void OnAttack( UNIT_FUNC_PROTOTYPE );
    void OnAttacked( UNIT_FUNC_PROTOTYPE );

	static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_SWORD_H__AA87D2A4_D6BD_11D0_B565_00E029058623__INCLUDED_)
