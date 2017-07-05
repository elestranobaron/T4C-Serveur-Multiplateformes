// Sign.h: interface for the Sign class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGN_H__61D373F1_06A0_11D4_8664_00E02922FA40__INCLUDED_)
#define AFX_SIGN_H__61D373F1_06A0_11D4_8664_00E02922FA40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../ObjectStructure.h"

class Sign : public ObjectStructure  
{
public:
	Sign();
	virtual ~Sign();

	void OnUse( UNIT_FUNC_PROTOTYPE );
    void OnInitialise( UNIT_FUNC_PROTOTYPE );

	static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_SIGN_H__61D373F1_06A0_11D4_8664_00E02922FA40__INCLUDED_)
