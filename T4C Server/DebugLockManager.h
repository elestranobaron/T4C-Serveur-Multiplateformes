// DebugLockManager.h: interface for the CDebugLockManager class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DEBUGLOCKMANAGER_H_DEFINITION
#define DEBUGLOCKMANAGER_H_DEFINITION
    
class CLock;
class __declspec( dllexport ) DebugLockManager  
{
public:
    // CLock owns the DebugLockManager
    friend CLock;

    ~DebugLockManager();

    void Stop( void );
    
    void LogLockQueue( void );

    static DebugLockManager &Instance();    
private:       
    DebugLockManager();

    typedef void *DebugLockHandle;

    void NotifyLockWaiting( const char *lpszFileName, int nLineNumber, LPCRITICAL_SECTION lpThreadLock, DebugLockHandle &lpDebugHandle );
    void NotifyLockEntered( const char *lpszFileName, int nLineNumber, LPCRITICAL_SECTION lpThreadLock, DebugLockHandle &lpDebugHandle );
    void NotifyUnlock(      const char *lpszFileName, int nLineNumber, LPCRITICAL_SECTION lpThreadLock, DebugLockHandle &lpDebugHandle );
    void NotifyPicklock(    const char *lpszFileName, int nLineNumber, LPCRITICAL_SECTION lpThreadLock, DebugLockHandle &lpDebugHandle );    
};

#endif // DEBUGLOCKMANAGER_H_DEFINITION
