// StandardObject.h: interface for the StandardObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STANDARDOBJECT_H__DEC4A374_4EDB_11D1_BD70_00E029058623__INCLUDED_)
#define AFX_STANDARDOBJECT_H__DEC4A374_4EDB_11D1_BD70_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\ObjectStructure.h"

class StandardObject : public ObjectStructure  
{
public:
	StandardObject();
	virtual ~StandardObject();
	
	static ObjectStructure *StandardObject::CreateObject( void );
};

#endif // !defined(AFX_STANDARDOBJECT_H__DEC4A374_4EDB_11D1_BD70_00E029058623__INCLUDED_)
