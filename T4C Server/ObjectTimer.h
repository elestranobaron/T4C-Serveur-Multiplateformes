// ObjectTimer.h: interface for the ObjectTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTTIMER_H__14F0EB34_C327_11D1_AD9D_00E029058623__INCLUDED_)
#define AFX_OBJECTTIMER_H__14F0EB34_C327_11D1_AD9D_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Lock.h"
#include "Unit.h"

class EXPORT ObjectTimer
{
public:
	static void Create( void );
	static void Destroy( void );

	static void AddObject( Unit *lpuUnit );
	static void RemoveObject( Unit *lpuUnit );
	static void RemoveObject( DWORD dwID );

	static BOOL ObjectInList( Unit *lpuUnit );
	static BOOL ObjectInList( DWORD dwID );
	
	static void VerifyTimers( void );
private:
	static TemplateList <Unit> tluObjectTimers;
	static CLock csThreadLock;

};

#endif // !defined(AFX_OBJECTTIMER_H__14F0EB34_C327_11D1_AD9D_00E029058623__INCLUDED_)
