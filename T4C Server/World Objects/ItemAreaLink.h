// ItemAreaLink.h: interface for the ItemAreaLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMAREALINK_H__7EBA0DF2_3594_437B_B761_D027B97082C1__INCLUDED_)
#define AFX_ITEMAREALINK_H__7EBA0DF2_3594_437B_B761_D027B97082C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../ObjectStructure.h"

class ItemAreaLink : public ObjectStructure  
{
public:
	ItemAreaLink();
	virtual ~ItemAreaLink();

	static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_ITEMAREALINK_H__7EBA0DF2_3594_437B_B761_D027B97082C1__INCLUDED_)
