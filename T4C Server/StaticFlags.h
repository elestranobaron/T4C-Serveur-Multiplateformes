// StaticFlags.h: interface for the StaticFlags class.
//
//////////////////////////////////////////////////////////////////////
 /*
#if !defined(AFX_STATICFLAGS_H__85695825_0609_11D1_AD66_00E029058623__INCLUDED_)
#define AFX_STATICFLAGS_H__85695825_0609_11D1_AD66_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Lock.h"

class __declspec(dllexport) StaticFlags  
{
public:
	StaticFlags();
	virtual ~StaticFlags();

	int  ViewStaticFlag(UINT which);
	void SetStaticFlag(UINT which, int value);

	UINT GetStaticFlags(LPINT *FlagValues, UINT **FlagIDs);

	void DestroyStaticFlags();

private:
	void AddStaticFlag (UINT which, int value);
	
	int	 *Flags;
	UINT *FlagRef;
	UINT flag_length;

	CLock csFlagLock;
};

#endif // !defined(AFX_STATICFLAGS_H__85695825_0609_11D1_AD66_00E029058623__INCLUDED_)
  */