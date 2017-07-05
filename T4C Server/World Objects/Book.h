// Book.h: interface for the Book class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOOK_H__EF6AD953_57A3_11D1_BD7E_00E029058623__INCLUDED_)
#define AFX_BOOK_H__EF6AD953_57A3_11D1_BD7E_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\ObjectStructure.h"

class Book : public ObjectStructure  
{
public:
	Book();
	virtual ~Book();

	void OnUse( UNIT_FUNC_PROTOTYPE );

	static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_BOOK_H__EF6AD953_57A3_11D1_BD7E_00E029058623__INCLUDED_)
