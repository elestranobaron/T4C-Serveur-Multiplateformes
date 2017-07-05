// SpellBook.h: interface for the SpellBook class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPELLBOOK_H__11208CD3_DB50_11D0_B56F_00E029058623__INCLUDED_)
#define AFX_SPELLBOOK_H__11208CD3_DB50_11D0_B56F_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\ObjectStructure.h"

class SpellBook : public ObjectStructure  
{
public:
	SpellBook(unsigned short object_type);
	virtual ~SpellBook();

	void OnInitialise( UNIT_FUNC_PROTOTYPE ); // put spell in here

	static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_SPELLBOOK_H__11208CD3_DB50_11D0_B56F_00E029058623__INCLUDED_)
