// Lock.h: interface for the CLock class.
//
//////////////////////////////////////////////////////////////////////

#ifndef LOCK_H_CLASS_DEFINITION
#define LOCK_H_CLASS_DEFINITION

#define LOCK_FUNC()     void Lock( void )
#define UNLOCK_FUNC()   void Unlock( void )
#define PICKLOCK_FUNC() BOOL PickLock( void )
#include <unistd.h> //sleep
#include "stackhlp.h"
#include <string>

#include "windows_linux.h"


class CLock;
class CDebugLockManager{
public:
    virtual void Locking( DWORD callerAddr, CLock *lockPtr, DWORD &newLockEntry ) = 0;
    virtual void GotLock( DWORD &newLockEntry, DWORD &previousLockEntry ) = 0;
    virtual void Picklock( DWORD callerAddr, CLock *lockPtr, DWORD &lockEntry ) = 0;
    virtual void Unlocking( DWORD &lockEntry ) = 0;
    virtual bool DumpLockData( std::string fileName ) = 0;

    enum{ EmptyEntry = 0xFFFFFFFF };

    static EXPORT CDebugLockManager *GetInstance();
};
//////////////////////////////////////////////////////////////////////////////////////////
// CLock class definition.
class CLock  
{
public:
    CLock(){ 
        lockEntry = CDebugLockManager::EmptyEntry;
        //create mutex attribute variable
	pthread_mutexattr_t mAttr;

	// setup recursive mutex for mutex attribute
	pthread_mutexattr_settype(&mAttr, PTHREAD_MUTEX_RECURSIVE_NP);

	// Use the mutex attribute to create the mutex
	pthread_mutex_init(&m, &mAttr);

	// Mutex attribute can be destroy after initializing the mutex variable
	pthread_mutexattr_destroy(&mAttr);
    };
    virtual ~CLock(){
        pthread_mutex_destroy (&m);
    };

    //////////////////////////////////////////////////////////////////////////////////////////
    virtual void Lock( ){
        DWORD callerAddr;
        GET_CALLER_ADDR( callerAddr );

        // Holds the new lock entry table. This information is thread specific
        // until the lock is aquired.
        DWORD newLockEntry;

        // Register that we are waiting for the lock to be released.
        CDebugLockManager::GetInstance()->Locking( callerAddr, this, newLockEntry );

        pthread_mutex_lock (&m);

        // Register that we are inside the lock.
        CDebugLockManager::GetInstance()->GotLock( newLockEntry, lockEntry );
    };
    //////////////////////////////////////////////////////////////////////////////////////////    
    virtual void Unlock( ){
        // Log that this lock was released.
        CDebugLockManager::GetInstance()->Unlocking( lockEntry );

        pthread_mutex_unlock (&m);
    }
    
// Picklock only works on WinNT 4.0 or more.
#if( _WIN32_WINNT >= 0x400 )    
    //////////////////////////////////////////////////////////////////////////////////////////    
    virtual int PickLock( ){
        // If lock is successfull
        if( pthread_mutex_trylock (&m) ){
            DWORD callerAddr;
            GET_CALLER_ADDR( callerAddr );

            // Log picklog
            CDebugLockManager::GetInstance()->Picklock( callerAddr, this, lockEntry );
            return true;
        }
        return false;
    }
#endif

private:
    // Entry of lock in the lock table.
    DWORD lockEntry;

    // The underlying critical section.
    pthread_mutex_t m;

};

//////////////////////////////////////////////////////////////////////////////////////////
// Auto lock structure. Locks lock on creation, and unlocks it on destruction.
// Client is responsible for preserving the lock's integrity.
class CAutoLock{
public:
    CAutoLock( CLock *lpNewLock ) : lpLock( lpNewLock ){
        lpLock->Lock();
    }
    ~CAutoLock(){
        lpLock->Unlock();
    }
private:
    CLock *lpLock;
};



#if( _WIN32_WINNT >= 0x400 )
//////////////////////////////////////////////////////////////////////////////////////////
// Helper functions, allows safely locking multiple locks.
inline void MultiLock( CLock *cLockL, CLock *cLockR ){
    cLockL->Lock();
    while( !cLockR->PickLock() ){
        cLockL->Unlock();
        sleep( 0 );
        cLockL->Lock();
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
// Allows lockuing 3 locks.
inline void MultiLock3( CLock *cLock1, CLock *cLock2, CLock *cLock3 ){
    bool boFailed = true;
    while( boFailed ){
        cLock1->Lock();
        if( cLock2->PickLock() ){
            if( cLock3->PickLock() ){
                boFailed = false;
            }else{
                cLock1->Unlock();
                cLock2->Unlock();
                boFailed = true;
            }
        }else{
            cLock1->Unlock();
            boFailed = true;
        }
    }
}
#endif

#endif//#define LOCK_H_CLASS_DEFINITION
