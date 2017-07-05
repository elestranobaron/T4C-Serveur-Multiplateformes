// SysopCmd.h: interface for the SysopCmd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSOPCMD_H__A4383683_F3D4_11D1_8316_00104B2CA38F__INCLUDED_)
#define AFX_SYSOPCMD_H__A4383683_F3D4_11D1_8316_00104B2CA38F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Players.h"

class EXPORT SysopCmd  
{
public:	
	SysopCmd();
	~SysopCmd();

	static BOOL VerifySysopCommand( Players *self, CString csCommand );
	static BOOL GetParameters( LPCTSTR lpszCommandTemplate, CString csCommandLine, CString *lpcsFoundParameters );    
   static BOOL GetParametersForNPC( LPCTSTR lpszCommandTemplate, CString csCommandLine, CString *lpcsFoundParameters );    

    static void Create();

private:
    static void ShutdownTimer( WORD, BYTE, LPVOID, LPVOID );

	static CLock csSysLock;

	static Players *FindCharacter( CString csName );
	

};

#endif // !defined(AFX_SYSOPCMD_H__A4383683_F3D4_11D1_8316_00104B2CA38F__INCLUDED_)
