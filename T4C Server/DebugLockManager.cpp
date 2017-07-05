// DebugLockManager.cpp: implementation of the DebugLockManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lock.h"
#include "RegKeyHandler.h"

#pragma warning(disable:4786 )

namespace{
    enum LockState{
        TryLocked = 1, Locked = 2, Unlocked = 3, PickLocked = 4
    };

    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////    
    class CDebugLockManagerTracer : public CDebugLockManager{
    public:
        CDebugLockManagerTracer(){
            RegKeyHandler regKey;
            regKey.Open( HKEY_LOCAL_MACHINE, "Software\\Vircom\\The 4th Coming Server\\Logging" );

            LOCK_TABLE_SIZE = regKey.GetProfileInt( "DeadlockJournalSize", 10000 );


            InitializeCriticalSection( &critSection );
            curPos = 0;
            totalLockCount = 0;
            lockTable = new LockData[ LOCK_TABLE_SIZE ];

            concurrentLocks = 0;
            maxConcurrentLocks = 0;            
        }
        ~CDebugLockManagerTracer(){
            DeleteCriticalSection( &critSection );
            delete lockTable;
        }
        void Lock(){
            EnterCriticalSection( &critSection );
        }
        void Unlock(){
            LeaveCriticalSection( &critSection );
        }

        class LockData{
        public:
            LockData() : lockState( Unlocked ){};

            DWORD callerAddr;
            DWORD manAddr;
            DWORD threadId;
            DWORD previousEntry;
            CLock *lockPtr;
            DWORD lockEntry;
            DWORD timeStamp;
            DWORD waitTime;
            LockState lockState;
        };

        // Simply logs a lock call into the journal.
        DWORD AddEntry( DWORD callerAddr, DWORD manAddr, LockState state, CLock *lockPtr ){
            Lock();
            totalLockCount++;
            
            // Find the 1st entry which is unused.
            do{
                curPos++;
                if( curPos >= LOCK_TABLE_SIZE ){
                    curPos = 0;
                }
            }while( lockTable[ curPos ].lockState != Unlocked );

            // Fill-in the entry data.
            lockTable[ curPos ].callerAddr = callerAddr;
            lockTable[ curPos ].manAddr = manAddr;
            lockTable[ curPos ].threadId = GetCurrentThreadId();
            lockTable[ curPos ].lockState = state;
            lockTable[ curPos ].lockPtr = lockPtr;
            lockTable[ curPos ].timeStamp = GetRunTime();            
            DWORD ret = curPos;

            Unlock();
            return ret;
        }

        ////////////////////////////////////////////////////////////////////
        virtual void Locking( DWORD callerAddr, CLock *lockPtr, DWORD &newLockEntry ){
            // When Locking, CLockData must be kept being the lock's Id
            // in order for other threads to add entries.
            DWORD manAddr;
            GET_CALLER_ADDR( manAddr );
            newLockEntry = AddEntry( callerAddr, manAddr, TryLocked, lockPtr );

            // Stat info to check the maximum number of entries ever used at one time.
            InterlockedIncrement( reinterpret_cast< long * >( &concurrentLocks ) );
            if( concurrentLocks > maxConcurrentLocks ){
                maxConcurrentLocks = concurrentLocks;
            }
        };
        ////////////////////////////////////////////////////////////////////
        virtual void GotLock( DWORD &newLockEntry, DWORD &previousLockEntry ){
            // When the lock is fetched, the lockEntry can be safely set
            // to the entry's value until the next unlock.
            
            // Save the previous lockEntry.
            lockTable[ newLockEntry ].previousEntry = previousLockEntry;
            // Modify the lock's state. 
            lockTable[ newLockEntry ].lockState = Locked;

            DWORD currentTime = GetRunTime();
            lockTable[ curPos ].waitTime = lockTable[ newLockEntry ].timeStamp - currentTime;
            lockTable[ newLockEntry ].timeStamp = currentTime;           
            
            // Set the previous lock to the lock's entry.
            previousLockEntry = newLockEntry;
        };
        ////////////////////////////////////////////////////////////////////
        virtual void Unlocking( DWORD &lockEntry ){

            if( lockEntry == EmptyEntry ){
                throw "Double Unlock!";
            }
            // Restore the lock entry.
            DWORD oldLockEntry = lockEntry;
            lockEntry = lockTable[ oldLockEntry ].previousEntry;
            // Set state last to avoid adding an entry over this one before
            // the previousEntry was fetched.
            lockTable[ oldLockEntry ].lockState = Unlocked;

            InterlockedDecrement( reinterpret_cast< long * >( &concurrentLocks ) );
        };
        ////////////////////////////////////////////////////////////////////
        virtual void Picklock( DWORD callerAddr, CLock *lockPtr, DWORD &lockEntry ){
            // Directly modify the lockEntry since lock is already acquired.
            DWORD manAddr;
            GET_CALLER_ADDR( manAddr );
            DWORD newLockEntry = AddEntry( callerAddr, manAddr, PickLocked, lockPtr );
            lockTable[ newLockEntry ].previousEntry = lockEntry;
            lockEntry = newLockEntry;
        };

        ////////////////////////////////////////////////////////////////////
        // This function checks the buffer and plays back all the lock data
        // into a CDebugLockManagerImpl implementation. It then delegates
        // the file data dumping to it.
        virtual bool DumpLockData( std::string fileName ){
            Lock();

            // Get the ending pos.
            DWORD startPos;
            if( curPos >= LOCK_TABLE_SIZE ){
                startPos = 0;
            }else{
                startPos = curPos + 1;
            }

            FILE *f = fopen( fileName.c_str(), "wb" );
            if( f == NULL ){
                return false;
            }

            SYSTEMTIME sysTime; 
	        GetLocalTime(&sysTime);
            
            fprintf( f, "-----" );
            fprintf( f, "\r\nDeadlock report %02u/%02u/%04u %02u:%02u:%02u",
                sysTime.wMonth,
                sysTime.wDay,
                sysTime.wYear, 
                sysTime.wHour, 
                sysTime.wMinute,
                sysTime.wSecond
            );
            fprintf( f, "\r\n" );

            // Read the lock table for unresolved entries.
            for(;;){
                LockData &lockData = lockTable[ startPos ];
                
                // Check the event.
                switch( lockData.lockState ){
                case TryLocked:
                    fprintf( f, "\r\nFound unresolved TryLock:" );
                    fprintf( f, "\r\n At %08ums: lockPtr=0x%08x, callerAddr=0x%08x, manAddr=0x%08x, threadId=%03u",
                        lockData.timeStamp, lockData.lockPtr, lockData.callerAddr, lockData.manAddr, lockData.threadId 
                    );

                    break;
                case Locked:
                    fprintf( f, "\r\nFound unresolved Lock:" );
                    fprintf( f, "\r\n At %08ums: lockPtr=0x%08x, callerAddr=0x%08x, manAddr=0x%08x, threadId=%03u, waited %ums.",
                        lockData.timeStamp, lockData.lockPtr, lockData.callerAddr, lockData.manAddr, lockData.threadId, lockData.waitTime 
                    );
                    break;
                case PickLocked:
                    fprintf( f, "\r\nFound unresolved PickLock:" );
                    fprintf( f, "\r\n At %08ums: lockPtr=0x%08x, callerAddr=0x%08x, manAddr=0x%08x, threadId=%03u",
                        lockData.timeStamp, lockData.lockPtr, lockData.callerAddr, lockData.manAddr, lockData.threadId 
                    );
                    break;
                }

                // If buffer was totally checked.
                if( startPos == curPos ){
                    break;                    
                }

                // Move pointer.
                startPos++;
                if( startPos >= LOCK_TABLE_SIZE ){
                    startPos = 0;
                }
            }
            fprintf( f, "\r\n\r\n" );

            fclose( f );
            
            LeaveCriticalSection( &critSection );

            // File logging never fails.
            return true;
        }
    private:
        // Internal lock.
        CRITICAL_SECTION critSection;
        
        // Buffer variables.
        DWORD curPos;
        DWORD LOCK_TABLE_SIZE;
        LockData *lockTable;
        
        // Stat variables.
        DWORD totalLockCount;
        long  concurrentLocks;
        long  maxConcurrentLocks;

    };
};

// Does absolutly nothing (disabled lock manager).
class CEmptyDebugLockManager : public CDebugLockManager{
    virtual void Locking( DWORD callerAddr, CLock *lockPtr, DWORD &newLockEntry ){};
    virtual void GotLock( DWORD &newLockEntry, DWORD &previousLockEntry ){};
    virtual void Picklock( DWORD callerAddr, CLock *lockPtr, DWORD &lockEntry ){};
    virtual void Unlocking( DWORD &lockEntry ){};
    virtual bool DumpLockData( std::string fileName ){ return false; };
};


// Returns the implementation to use.
CDebugLockManager *GetCurrentImplementation(){
     // Query wether or not deadlock logging is enabled.
    RegKeyHandler regKey;

    regKey.Open( HKEY_LOCAL_MACHINE, "Software\\Vircom\\The 4th Coming Server\\Logging" );

    DWORD imp = regKey.GetProfileInt( "DeadlockLogging", 1 );

    if( imp != 0 ){
        static CDebugLockManagerTracer instance;
        return &instance;
    }else{
        static CEmptyDebugLockManager instance;
        return &instance;
    }
}

// Returns the debug lock manager instance.
CDebugLockManager *CDebugLockManager::GetInstance(){
    static CDebugLockManager *instance = GetCurrentImplementation();
    return instance;
}