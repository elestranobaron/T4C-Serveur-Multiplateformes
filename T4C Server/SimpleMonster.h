// SimpleMonster.h: interface for the SimpleMonster class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLEMONSTER_H__8745E2D3_0F4C_11D1_BCDB_00E029058623__INCLUDED_)
#define AFX_SIMPLEMONSTER_H__8745E2D3_0F4C_11D1_BCDB_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NPCstructure.h"

class __declspec( dllexport ) SimpleMonster : public NPCstructure
{
public:
	SimpleMonster();
	virtual ~SimpleMonster();

	void Create( );
	
	virtual void OnInitialise( UNIT_FUNC_PROTOTYPE );
	virtual void OnPopup( UNIT_FUNC_PROTOTYPE );
	virtual void OnServerInitialisation( UNIT_FUNC_PROTOTYPE, WORD wBaseReferenceID );

	MonsterStructure *GetMonsterStructure( void );
};

#endif // !defined(AFX_SIMPLEMONSTER_H__8745E2D3_0F4C_11D1_BCDB_00E029058623__INCLUDED_)
