// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__BC8F306A_A74F_11D0_9B9E_444553540000__INCLUDED_)
#define AFX_STDAFX_H__BC8F306A_A74F_11D0_9B9E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#ifndef _WIN32_WINNT
	#define _WIN32_WINNT 0x0600
#endif 
#define DEBUG			#ifdef _DEBUG

//#define _AFX_NO_OLE_SUPPORT
//#define _AFX_NO_DB_SUPPORT
//#define _AFX_NO_DAO_SUPPORT
#pragma warning( disable : 4786 )   // Debug string too long.
#pragma warning( disable : 4284 )   // Return type of operator ->

// To disable when debugging app.
#pragma warning( disable : 4244 )   // Conversion from 'type1' to 'type2'
#pragma warning( disable : 4018 )   // Signed/unsigned mismatched.


//#define __ENABLE_LOG
//#include <afxdao.h>

//#include <afxwin.h>         // MFC core and standard components
//#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
//#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//#include <afxmt.h>

//#include <afxsock.h>		// MFC socket extensions

//#include <imagehlp.h>

#ifdef MEM_DEBUG
    #include <smrtheap.hpp>
#endif

#include "ExitCode.h"
#include "Timer.h"

#ifdef __ENABLE_LOG
	extern DEBUG_LOG __LOG;
#endif

#ifndef ATLASSERT
#define ATLASSERT ASSERT
#endif
namespace vir{};
using namespace vir;
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BC8F306A_A74F_11D0_9B9E_444553540000__INCLUDED_)
