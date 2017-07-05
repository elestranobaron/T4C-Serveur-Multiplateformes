// AreaSensitiveEffect.h: interface for the AreaSensitiveEffect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AREASENSITIVEEFFECT_H__E7C519C3_DE6D_11D0_A876_00E029058623__INCLUDED_)
#define AFX_AREASENSITIVEEFFECT_H__E7C519C3_DE6D_11D0_A876_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Character.h"

#define __AREA_TELEPORT		0xA001


class EXPORT AreaSensitiveEffect  
{
public:
	AreaSensitiveEffect();
	virtual ~AreaSensitiveEffect();

	BOOL QueryEffect(WorldPos where, Unit *who_stepped_in);
	void Create(UINT minx, UINT maxx, WORD effect, LPVOID params = NULL, int paramsize = 0);

private:	
	void Execute(Unit *); // Executes the effect
	
	// Box coordinates of the affecting effect
	unsigned int minx, maxx;
	unsigned short effect;
	LPVOID params;	
};

#endif // !defined(AFX_AREASENSITIVEEFFECT_H__E7C519C3_DE6D_11D0_A876_00E029058623__INCLUDED_)
