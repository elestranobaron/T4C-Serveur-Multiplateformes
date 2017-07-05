// Doors.h: interface for the Doors class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOORS_H__7C32EC86_E8D3_11D0_A876_00E029058623__INCLUDED_)
#define AFX_DOORS_H__7C32EC86_E8D3_11D0_A876_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../ObjectStructure.h"
#include "../TFCTimers.h"

class Doors : public ObjectStructure 
{
public:
	Doors();
	virtual ~Doors();

    static void AutoClose( TIMERCALLBACK_PROTOTYPE );
	static void FinalClose( TIMERCALLBACK_PROTOTYPE );
	
	void OnUse( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );

	static ObjectStructure *CreateObject( void );    
};

#endif // !defined(AFX_DOORS_H__7C32EC86_E8D3_11D0_A876_00E029058623__INCLUDED_)
