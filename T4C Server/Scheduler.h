// Scheduler.h: interface for the CScheduler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHEDULER_H__52875859_799D_11D2_844C_00E02922FA40__INCLUDED_)
#define AFX_SCHEDULER_H__52875859_799D_11D2_844C_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Shutdown.h"
#include "Lock.h"
#include <vector>
#include <string>
using namespace std;

#pragma warning(disable:4786)

typedef struct _SCHEDULED_EVENT{
    DWORD dwEventID;

    DWORD dwRelativeTime;
    DWORD dwTriggerTime;    

    vector< string > vCommands;
} SCHEDULED_EVENT, *LPSCHEDULED_EVENT;

#define EVENT_SHUTDOWN                      0x01
#define EVENT_ACCESS_MAINTENANCE            0x02
#define EVENT_ACCESS_MAINTENANCE_SHUTDOWN   0x03

class CScheduler  
{
// Public functions
public:
    ~CScheduler();

    // Start the scheduler.
    static void StartScheduler( void );
        
// Private functions
private:
    CScheduler();    

    void AddScheduledEvent( tm tmOffsetTime, tm tmRelativeTime, DWORD dwEventID );
    void AddEventCommand  ( string &csCommand );

    static void SchedulerThread( LPVOID lpVoid );
    void SchedulerMaintenance();

    static void LoadSchedule( void );
    void VerifySchedule( void );
    void TriggerEvent( SCHEDULED_EVENT &sEvent );
    static void AccessMaintenanceCallback( LPSHUTDOWN lpShutdown );
    void AccessMaintenance( void );

    
// Helper functions    
    DWORD TM2Round( tm tmOffset, tm tmTime );

// Variables
private:
    HANDLE                    hSchedulerThread;
    bool                      boSchedulerThreadRun;
    vector< SCHEDULED_EVENT > vEvents;
    string                    csAccessDB;
    string                    csAccessPwd;

    LPSCHEDULED_EVENT         lpLastEnteredEvent;

    CLock                     cLock;

// Single instance
private:
    static CScheduler m_Instance;
};

#endif // !defined(AFX_SCHEDULER_H__52875859_799D_11D2_844C_00E02922FA40__INCLUDED_)
