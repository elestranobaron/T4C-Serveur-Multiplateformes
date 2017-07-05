// Container.h: interface for the Container class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTAINER_H__9D4BF104_770C_11D1_BDC7_00E029058623__INCLUDED_)
#define AFX_CONTAINER_H__9D4BF104_770C_11D1_BDC7_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\ObjectStructure.h"

class Container : public ObjectStructure  
{
public:
	Container();
	virtual ~Container();

	void OnInitialise( UNIT_FUNC_PROTOTYPE );
	void OnUse( UNIT_FUNC_PROTOTYPE );

	static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_CONTAINER_H__9D4BF104_770C_11D1_BDC7_00E029058623__INCLUDED_)
