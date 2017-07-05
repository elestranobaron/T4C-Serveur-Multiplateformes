// IcySaber.h: interface for the IcySaber class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICYSABER_H__1B9A5A59_C8A4_11D1_ADAB_00E029058623__INCLUDED_)
#define AFX_ICYSABER_H__1B9A5A59_C8A4_11D1_ADAB_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "..\ObjectStructure.h"

class IcySaber : public ObjectStructure  
{
public:
	IcySaber();
	virtual ~IcySaber();

	void OnAttack( UNIT_FUNC_PROTOTYPE );
	void OnDisturbed( UNIT_FUNC_PROTOTYPE );

	static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_ICYSABER_H__1B9A5A59_C8A4_11D1_ADAB_00E029058623__INCLUDED_)
