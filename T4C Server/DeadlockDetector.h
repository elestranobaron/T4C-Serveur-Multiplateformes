// DeadlockDetector.h: interface for the CDeadlockDetector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEADLOCKDETECTOR_H__67CBC00E_52F9_11D2_83FE_00E02922FA40__INCLUDED_)
#define AFX_DEADLOCKDETECTOR_H__67CBC00E_52F9_11D2_83FE_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Lock.h"
#include <map>

#pragma warning( disable: 4786 )

#ifdef _DEBUG
#define DEADLOCK_TIME 120000
#else
#define DEADLOCK_TIME  30000
#endif

typedef struct _DEADLOCK_WATCH{
    HANDLE  hThreadHandle;
    int     nThreadId;
    CString csThreadName;
    DWORD   dwTimeout;
    DWORD   dwMaxTimeout;
    CLock   cLock;
    bool    boLogLock;
} DEADLOCK_WATCH, *LPDEADLOCK_WATCH;


class CDeadlockDetectorDebug;
class CDeadlockDetector  
{
public:
    friend CDeadlockDetectorDebug;

    CDeadlockDetector();
    ~CDeadlockDetector();

    static void Create( void );
    static void Destroy( void );

    void RegisterThread( HANDLE hThreadHandle, CString csThreadName, DWORD dwMaxTimeout = DEADLOCK_TIME, int nThreadId = pthread_self() /*GetCurrentThreadId()*/ );
    void UnregisterThread( void );

    void EnterTimeout( void );
    void LeaveTimeout( void );

    void KeepAlive( void );    

    void SetLockLog( bool boNewLogLock );

    static void SuspendDeadlockDetection( DWORD dwDelay = INFINITY /*INFINITE*/ );

private:
    static void DeadlockCheckThread( LPVOID lpData );
    DEADLOCK_WATCH deadLock;
};


#define START_DEADLOCK_DETECTION( __handle, __threadname )    CDeadlockDetector cDeadlockDetector;\
                                                              cDeadlockDetector.RegisterThread( __handle, __threadname )

#define DEADLOCK_LOG_LOCK        cDeadlockDetector.SetLockLog( true );
#define ENTER_TIMEOUT   cDeadlockDetector.EnterTimeout();
#define LEAVE_TIMEOUT   cDeadlockDetector.LeaveTimeout();
#define KEEP_ALIVE      cDeadlockDetector.KeepAlive();
#define SUSPEND_DEADLOCK_DETECTION  CDeadlockDetector::SuspendDeadlockDetection
                                                    
#define STOP_DEADLOCK_DETECTION cDeadlockDetector.UnregisterThread();

#endif // !defined(AFX_DEADLOCKDETECTOR_H__67CBC00E_52F9_11D2_83FE_00E02922FA40__INCLUDED_)
