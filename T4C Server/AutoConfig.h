// *******************************************************************************************
// ***                                                                                     ***
//      File Name: AutoConfig.h
//      Project:   T4C Server
//      Plateform: Windows NT 4.0 Workstation/Server
//      Creation:  7/10/1998
//      Author:    Francois Leblanc (FL)
// ***                                                                                     ***
// *******************************************************************************************
// ***                                                                                     ***
//      Change History
//
//         Date            Ver.      Author         Purpose
//         7/10/1998       1.0       FL             Initial developpement
//
//      Description
//          This class handles run-time configuration changes. It checks changes made to
//      the server's configuration registry key and applies them to supplied variables.
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***           Copyright (c) 1997-1998 Virtual Dreams. All rights reserved.              ***


#if !defined(AFX_AUTOCONFIG_H__7EE5E236_5DF5_11D2_8425_00E02922FA40__INCLUDED_)
#define AFX_AUTOCONFIG_H__7EE5E236_5DF5_11D2_8425_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#pragma warning( disable : 4786 )

#include <string>
using namespace std;

typedef void (*REGCALLBACK)( void );

class CAutoConfig  
{
public:
    static void Create( HKEY hMainKey, LPCTSTR szSubKey, LPCTSTR szCheckValue );
    static void Destroy( void );
   
    static void AddRegString( LPCTSTR szSubKey, LPCTSTR szValue, LPCTSTR szDefault = NULL, HKEY hMainKey = hCheckMainKey );
    static void AddRegInt(    LPCTSTR szSubKey, LPCTSTR szValue, int nDefault = 0, HKEY hMainKey = hCheckMainKey );
    
    static string GetStringValue( LPCTSTR szSubKey, LPCTSTR szValue, HKEY hMainKey = hCheckMainKey );
    static int    GetIntValue(    LPCTSTR szSubKey, LPCTSTR szValue, HKEY hMainKey = hCheckMainKey ); 

    static void*   ChangeDetectionThread( LPVOID lpData );

    static void   AddRegUpdateCallback( REGCALLBACK lpRegCallback );

private:  
    static HKEY     hCheckMainKey;
    static string   sCheckSubKey;
    static string   sCheckValue;
    static HANDLE   hThread;
    static bool     boRunThread;
};


#endif // !defined(AFX_AUTOCONFIG_H__7EE5E236_5DF5_11D2_8425_00E02922FA40__INCLUDED_)
