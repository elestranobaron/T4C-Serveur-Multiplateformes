/******************************************

  Windows NT Service Class Library
	Copyright 1996-1997 Dundas Software Ltd.

*******************************************/

//MFC Users - include the following
#include "stdafx.h"
//OWL Users - include the following
//#include <owl\owlpch.h>
//SDK Users - include the following

#include <windows.h>

#include <process.h>
#include "c_servic.h"
#include "T4CLog.h"

extern CString ServerPath;
/******************************************
*******************************************/
CUService * CUServ;

/******************************************
*******************************************/
CUService::CUService(){

	//service variables
	m_ServiceName 				= NULL;
	m_ExitEvent		 			= NULL;
	m_PauseService				= FALSE;
	m_RunningService			= FALSE;
	m_ThreadHandle				= 0;
	m_EntryFunction				= NULL;
	m_PauseFunction				= NULL;
	m_ResumeFunction			= NULL;
	m_StopFunction				= NULL;

	//time-out variables
	m_StartTimeOut				= 10000;
	m_StopTimeOut				= 15000;
	m_PauseTimeOut				= 5000;
	m_ResumeTimeOut				= 5000;

	//install variables
	m_dwDesiredAccess			= SERVICE_ALL_ACCESS;
	m_dwServiceType		  		= SERVICE_WIN32_OWN_PROCESS;
	m_dwStartType			  	= SERVICE_AUTO_START;
	m_dwErrorControl		  	= SERVICE_ERROR_NORMAL;

	m_szLoadOrderGroup	  		= NULL;
	m_lpdwTagID					= NULL;
	m_szDependencies		  	= NULL;


}

/******************************************
*******************************************/
CUService::~CUService(){

	if(m_ServiceName != NULL)
		delete[] m_ServiceName;
}

/******************************************
InitService
	Purpose
		Registers the main service thread with
		the service manager
	Params
		name  - internal service name
		EntryFunction - pointer to the main programs entry
			function for when the service is started
*******************************************/
long CUService::InitService(LPCTSTR name, void * EntryFunction){

	CUServ = this;
	m_EntryFunction = (CUENTRY)EntryFunction;
	m_ServiceName = new TCHAR[lstrlen(name)+1];
	lstrcpy(m_ServiceName,name);


	SERVICE_TABLE_ENTRY ste[] ={
		{ (LPTSTR)name,(LPSERVICE_MAIN_FUNCTION) ServiceMain} ,{ NULL, NULL }};
		

	// Register with the SCM
	
	return StartServiceCtrlDispatcher(ste);
}

/******************************************
*******************************************/
void CUService::SetCallBacks(void *pause,void *resume,void *stop){
	m_PauseFunction		= (CUENTRY)pause;
	m_ResumeFunction	= (CUENTRY)resume;
	m_StopFunction		= (CUENTRY)stop;
}

/******************************************
ServiceMain
	Purpose
		This is the thread that is called from the
		service manager to start the service
*******************************************/
VOID CUService::ServiceMain(DWORD , LPTSTR *){
	BOOL success;


	// immediately call Registration function
	CUServ->m_ServiceStatusHandle = RegisterServiceCtrlHandler(
			CUServ->m_ServiceName,(LPHANDLER_FUNCTION )CUService::ServiceCtrlHandler);

	if (!CUServ->m_ServiceStatusHandle){
		CUServ->Exit(GetLastError());
		return;
	}

	// Notify SCM of progress
	success = CUServ->SCMStatus(SERVICE_START_PENDING,NO_ERROR, 0, 1, 8000);
	if (!success){
		CUServ->Exit(GetLastError());
		return;
	}

	// create the termination event
	CUServ->m_ExitEvent = CreateEvent (0, TRUE, FALSE,0);
	if (!CUServ->m_ExitEvent){
		CUServ->Exit(GetLastError());
		return;
	}

	// Notify SCM of progress
	success = CUServ->SCMStatus(	SERVICE_START_PENDING,NO_ERROR, 0, 3, CUServ->m_StartTimeOut);
	if (!success){
		CUServ->Exit(GetLastError());
		return;
	}

	// Start the service itself
	success = CUServ->OnStartService();
	if (!success){
		CUServ->Exit(GetLastError());
		return;
	}

	// The service is now running.
	// Notify SCM of progress
	success = CUServ->SCMStatus(SERVICE_RUNNING,NO_ERROR, 0, 0, 0);
	if (!success){
		CUServ->Exit(GetLastError());
		return;
	}
	// Wait for stop signal, and then exit
	WaitForSingleObject (CUServ->m_ExitEvent, INFINITE);

	CUServ->Exit(0);
}
/******************************************
OnStartService
	Purpose
		Called when the service is to be started
	Params
		none
	Return
		TRUE  - successful
		FALSE - fail
*******************************************/
long CUService::OnStartService(){

	// Start the service's thread
	m_ThreadHandle = (HANDLE) _beginthread((CUENTRY)m_EntryFunction,0, (VOID *)this);
	if (m_ThreadHandle==0)
		return FALSE;
	else
	{
		
		m_RunningService = TRUE;
		return TRUE;
	}
}
/******************************************
*******************************************/
void CUService::OnStopService(){
	
	m_RunningService=FALSE;

	if(m_StopFunction != NULL){
		DWORD thread;
		thread =  _beginthread((CUENTRY)m_StopFunction,0,(VOID *)this);
		if(thread != -1)
			WaitForSingleObject((HANDLE)thread,m_StopTimeOut);
	}
	
	WaitForSingleObject(m_ThreadHandle,m_StopTimeOut);

	// Set the event that is holding ServiceMain
	// so that ServiceMain can return
	SetEvent(m_ExitEvent);
}
/******************************************
*******************************************/
void CUService::OnPauseService(){

	if(m_PauseFunction != NULL){
		DWORD thread;
		thread =  _beginthread((CUENTRY)m_PauseFunction,0,(VOID *)this);
		if(thread != -1)
			WaitForSingleObject((HANDLE)thread,m_PauseTimeOut);
   }

	m_PauseService = TRUE;
	SuspendThread(m_ThreadHandle);
}
/******************************************
******************************************/
void CUService::OnResumeService(){

	if(m_ResumeFunction != NULL){
		DWORD thread;
		thread =  _beginthread((CUENTRY)m_ResumeFunction,0,(VOID *)this);
		if(thread != -1)
			WaitForSingleObject((HANDLE)thread,m_ResumeTimeOut);
   }

	m_PauseService = FALSE;
	ResumeThread(m_ThreadHandle);
}
/******************************************
*******************************************/
BOOL CUService::SCMStatus (DWORD dwCurrentState,DWORD dwWin32ExitCode,
			DWORD dwServiceSpecificExitCode,DWORD dwCheckPoint,DWORD dwWaitHint){

	BOOL success;
	SERVICE_STATUS serviceStatus;

	// Fill in all of the SERVICE_STATUS fields
	serviceStatus.dwServiceType =		SERVICE_WIN32_OWN_PROCESS;
	serviceStatus.dwCurrentState = 	dwCurrentState;

	// If in the process of something, then accept
	// no control events, else accept anything
	if (dwCurrentState == SERVICE_START_PENDING)
		serviceStatus.dwControlsAccepted = 0;
	else
		serviceStatus.dwControlsAccepted =	SERVICE_ACCEPT_STOP |
			SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_SHUTDOWN;

	// if a specific exit code is defines, set up
	// the win32 exit code properly
	if (dwServiceSpecificExitCode == 0)
		serviceStatus.dwWin32ExitCode = dwWin32ExitCode;
	else
		serviceStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;

	serviceStatus.dwServiceSpecificExitCode =	dwServiceSpecificExitCode;

	serviceStatus.dwCheckPoint = dwCheckPoint;
	serviceStatus.dwWaitHint = dwWaitHint;

	// Pass the status record to the SCM
	success = SetServiceStatus (m_ServiceStatusHandle, &serviceStatus);

	if (!success)
		OnStopService();

	return success;
}
/******************************************
*******************************************/
VOID CUService::ServiceCtrlHandler(DWORD controlCode){

 	DWORD  currentState = 0;

	switch(controlCode){
		// There is no START option because
		// ServiceMain gets called on a start

		// Stop the service
		case SERVICE_CONTROL_STOP:

			currentState = SERVICE_STOP_PENDING;
			
			// Tell the SCM what's happening
			CUServ->SCMStatus(currentState,NO_ERROR, 0, 1, CUServ->m_StopTimeOut);
			
			// Stop the service
			CUServ->OnStopService();
			return;

		// Pause the service
		case SERVICE_CONTROL_PAUSE:

			if (CUServ->m_RunningService && ! CUServ->m_PauseService){
			
				currentState = SERVICE_PAUSED;
				
				// Tell the SCM what's happening
				CUServ->SCMStatus(SERVICE_PAUSE_PENDING,NO_ERROR, 0, 1, CUServ->m_PauseTimeOut);
				CUServ->OnPauseService();
			}
			break;

		// Resume from a pause
		case SERVICE_CONTROL_CONTINUE:

			if (CUServ->m_RunningService && CUServ->m_PauseService){

				currentState = SERVICE_RUNNING;

				// Tell the SCM what's happening
				CUServ->SCMStatus(SERVICE_CONTINUE_PENDING,NO_ERROR, 0, 1, CUServ->m_ResumeTimeOut);
				CUServ->OnResumeService();
			}
			break;
	}

	//default
	CUServ->SCMStatus(currentState, NO_ERROR,0, 0, 0);
}
/******************************************
*******************************************/
VOID CUService::Exit(DWORD error){

    _LOG_DEBUG
        LOG_DEBUG_LVL1,
        "Exiting from service(%u).",
        error
    LOG_

	// if ExitEvent has been created, close it.
	if (m_ExitEvent)
		CloseHandle(m_ExitEvent);

	// Send a message to the scm to tell about
	// stopage
	if (m_ServiceStatusHandle)
		SCMStatus(SERVICE_STOPPED, error,0, 0, 0);

	// If the thread has started kill it off
	if (m_ThreadHandle)
		CloseHandle(m_ThreadHandle);

}

/******************************************
*******************************************/
int  CUService::SetStartTimeOut(int milisec){
	m_StartTimeOut = milisec;

	return m_StartTimeOut;
}
/******************************************
*******************************************/
int  CUService::SetStopTimeOut(int milisec){
	m_StopTimeOut = milisec;

	return m_StopTimeOut;
}
/******************************************
*******************************************/
int  CUService::SetPauseTimeOut(int milisec){
	m_PauseTimeOut = milisec;

	return m_PauseTimeOut;
}
/******************************************
*******************************************/
int  CUService::SetResumeTimeOut(int milisec){
	m_ResumeTimeOut = milisec;

	return m_ResumeTimeOut;
}
/********************************************
*********************************************/
int CUService::SetInstallOptions(DWORD dwDesiredAccess, DWORD dwServiceType,
					DWORD dwStartType,DWORD dwErrorControl){

	m_dwDesiredAccess	= dwDesiredAccess;
	m_dwServiceType 	= dwServiceType;
	m_dwStartType 		= dwStartType;
	m_dwErrorControl 	= dwErrorControl;

	return TRUE;
}
/********************************************
*********************************************/
int CUService::SetInstallOptions(LPTSTR szLoadOrderGroup,LPDWORD lpdwTagID,
					LPTSTR szDependencies){

	m_szLoadOrderGroup	= szLoadOrderGroup;
	m_lpdwTagID			= lpdwTagID;
	m_szDependencies	= szDependencies;

	return TRUE;
}
/********************************************
*********************************************/
int CUService::InstallService(LPCTSTR szInternName,LPCTSTR szDisplayName,LPCTSTR szFullPath){
	return InstallService(szInternName,szDisplayName,szFullPath,NULL,NULL);

}
/********************************************
	RETURN
		0	success
		1	Service manager failed to open
		2  Failed to create service
*********************************************/
int CUService::InstallService(LPCTSTR szInternName,LPCTSTR szDisplayName,LPCTSTR szFullPath,
		LPCTSTR szAccountName,LPCTSTR szPassword){

	SC_HANDLE newService, scm;
	int rt = 0;

	// open a connection to the SCM
	scm = OpenSCManager(0, 0,SC_MANAGER_CREATE_SERVICE);
	if (!scm){
		return 1;
	}

	// Install the new service
	newService = CreateService(
		scm,
		szInternName,				//intern name
		szDisplayName,				//display name
		m_dwDesiredAccess,        //desired access def: SERVICE_ALL_ACCESS
		m_dwServiceType,          //service type def: SERVICE_WIN32_OWN_PROCESS
		m_dwStartType,            //start type def: SERVICE_AUTOSTART
		m_dwErrorControl,         //error control def: SERVICE_ERROR_NORMAL
		szFullPath, 		     	// exec name and full path
		m_szLoadOrderGroup,       //load order group def: none
		m_lpdwTagID,              //group tag ID def: none
		m_szDependencies,         //dependencies def: none
		szAccountName,          // user account name def:Local System
		szPassword);            // user account password

	if (!newService){
		rt =2;
	}
	else{
		// clean up
		CloseServiceHandle(newService);
	}

	// clean up
	CloseServiceHandle(scm);

	return rt;
}
/********************************************
	Returns
		0			success
		1			failed to open service manager
		2			failed to locate the specified service
		3			failed to delete service
*********************************************/
int CUService::RemoveService(LPCTSTR szInternName){

	SC_HANDLE service, scm;
	int  rt;
   SERVICE_STATUS ss;

	// open a connection to the SCM
	scm = OpenSCManager(0, 0,SC_MANAGER_ALL_ACCESS);
	if (!scm){
		return 1;
	}

   //open the service
	service = OpenService(scm,szInternName,SERVICE_ALL_ACCESS|DELETE );
	if(service==NULL){
		MessageBox(NULL,_T("Failed to Locate Installed Service"),_T("Error"),MB_OK);
		// clean up
		CloseServiceHandle(scm);
		return 2;
	}

   ControlService(service,SERVICE_CONTROL_STOP,&ss);
	//delete the service
	if(DeleteService(service))
		rt = 0;
	else
		rt = 3;

	// clean up
	CloseServiceHandle(service);
	CloseServiceHandle(scm);

   return rt;
}

