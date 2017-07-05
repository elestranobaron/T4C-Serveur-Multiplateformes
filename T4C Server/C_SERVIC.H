#include <winsvc.h>

#ifndef __C_SERVICE_H
#define __C_SERVICE_H

typedef void (* CUENTRY)(void *);

class CUService{

	private:
		LPTSTR 					m_ServiceName;
		HANDLE 					m_ExitEvent;
		SERVICE_STATUS_HANDLE	m_ServiceStatusHandle;
		BOOL 					m_PauseService;
		BOOL 					m_RunningService;
		HANDLE					m_ThreadHandle;
		CUENTRY					m_EntryFunction;
		CUENTRY					m_PauseFunction;
		CUENTRY					m_ResumeFunction;
		CUENTRY					m_StopFunction;

		int	m_StartTimeOut;
		int	m_StopTimeOut;
		int	m_PauseTimeOut;
		int	m_ResumeTimeOut;

		void OnPauseService();
		void OnResumeService();
		void OnStopService();
		long OnStartService();

		static VOID ServiceMain(DWORD argc, LPTSTR *argv);

		BOOL SCMStatus (DWORD dwCurrentState,DWORD dwWin32ExitCode,
			DWORD dwServiceSpecificExitCode,DWORD dwCheckPoint,DWORD dwWaitHint);

		static VOID ServiceCtrlHandler (DWORD controlCode);

		VOID Exit(DWORD error);


		//install variables
		DWORD m_dwDesiredAccess;
		DWORD m_dwServiceType;
		DWORD m_dwStartType;
		DWORD m_dwErrorControl;

		LPTSTR 	m_szLoadOrderGroup;
		LPDWORD m_lpdwTagID;
		LPTSTR 	m_szDependencies;


	public:
		CUService();
		~CUService();

		//service entry point
		long InitService(LPCTSTR name,void * EntryFunction);
		void SetCallBacks(void *pause,void *resume,void *stop);
      
		//service timeout settings
		int  SetStartTimeOut(int milisec);
		int  SetStopTimeOut(int milisec);
		int  SetPauseTimeOut(int milisec);
		int  SetResumeTimeOut(int milisec);

		//service install / un-install
		int SetInstallOptions(DWORD dwDesiredAccess, DWORD dwServiceType,
					DWORD dwStartType,DWORD dwErrorControl);
		int SetInstallOptions(LPTSTR szLoadOrderGroup,LPDWORD lpdwTagID,
					LPTSTR szDependencies);
		int InstallService(LPCTSTR szInternName,LPCTSTR szDisplayName,LPCTSTR szFullPath);
		int InstallService(LPCTSTR szInternName,LPCTSTR szDisplayName,LPCTSTR szFullPath,
					LPCTSTR szAccountName,LPCTSTR szPassword);
      int RemoveService(LPCTSTR szInternName);

};

#endif