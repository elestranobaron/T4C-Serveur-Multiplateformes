// CSetup.h: interface for the CSetup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSETUP_H__0F8B168F_E5A0_43FB_BE1A_5550358F0137__INCLUDED_)
#define AFX_CSETUP_H__0F8B168F_E5A0_43FB_BE1A_5550358F0137__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include "Lock.h"
/*
 * The CSetup class handles and maintains the configuration of the serveur.
*/
class CSetup  
{
public:
	struct Paths:CLock
	{
		std::string binay_path;
		std::string motd_path;
		std::string log_path;
	};
	static Paths paths;
public:
	CSetup();
	~CSetup();
	// Initialises the data, and launches the maintenance thread
	void Init();
private:
	HANDLE maintenance_thread;
	DWORD maintenance_thread_id;
	static DWORD MaintenanceThreadHelper(LPVOID );
	void MaintenanceThread();
};

#endif // !defined(AFX_CSETUP_H__0F8B168F_E5A0_43FB_BE1A_5550358F0137__INCLUDED_)
