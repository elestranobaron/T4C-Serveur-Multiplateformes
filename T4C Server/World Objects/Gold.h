// Gold.h: interface for the Gold class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GOLD_H__89D152A6_7E3C_11D2_8454_00E02922FA40__INCLUDED_)
#define AFX_GOLD_H__89D152A6_7E3C_11D2_8454_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "../ObjectStructure.h"

class Gold  : public ObjectStructure
{
public:
	Gold();
	virtual ~Gold();

  	void OnInitialise( UNIT_FUNC_PROTOTYPE );
    void OnUse( UNIT_FUNC_PROTOTYPE );

    static ObjectStructure *CreateObject( void );
};

#endif // !defined(AFX_GOLD_H__89D152A6_7E3C_11D2_8454_00E02922FA40__INCLUDED_)
