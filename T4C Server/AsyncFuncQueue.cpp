// AsyncFuncQueue.cpp: implementation of the AsyncFuncQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "AsyncFuncQueue.h"
#include "TFCServerGP.h"
#include "DeadlockDetector.h"
#include "ThreadMonitor.h"
#include <stdint.h>

//////////////////////////////////////////////////////////////////////////////////////////
AsyncFuncQueue::AsyncFuncQueue()
//////////////////////////////////////////////////////////////////////////////////////////
{
}

//////////////////////////////////////////////////////////////////////////////////////////
void AsyncFuncQueue::Initialize( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Initializes the async func queue thread.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{	
	// If thread is uninitialized
	if( hThreadID == NULL ){
        static CLock initialLock;
        CAutoLock autoLock( &initialLock );

		// Create the IO Completion port associated with the thread, before it starts.
		ctx = 0;
		//int ret;

		/*ret*/ io_setup(128, &ctx);
		////////////hIoCompletion = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 1);

		// Start the thread.
	/*	UINT threadId;
        hThreadID = (HANDLE)_beginthreadex( NULL, 0, AsyncFuncQueueThread, this, CREATE_SUSPENDED, &threadId );

        ResumeThread( hThreadID );*/
	pthread_t thread;
	pthread_create(&thread, NULL, AsyncFuncQueueThread, this);
	hThreadID = (HANDLE)pthread_self();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void AsyncFuncQueue::Call
//////////////////////////////////////////////////////////////////////////////////////////
// Adds a function to be called by the function queue thread.
// 
(
 ASYNC_FUNC lpFunc, // The function to call
 LPVOID lpData		// The data to pass as parameter
)
//////////////////////////////////////////////////////////////////////////////////////////
{
		struct iocb cb;
		struct iocb *cbs[1];
		int fd;

		fd = open("/tmp/testfile", O_RDWR | O_CREAT);
		memset(&cb, 0, sizeof(cb));
		cb.aio_fildes = fd;
		cb.aio_lio_opcode = IOCB_CMD_PWRITE;
	// Initialize thread
	Initialize();

	ASYNC_FUNC_DATA *lpFuncData = new ASYNC_FUNC_DATA;
	lpFuncData->lpFunc = lpFunc;
	lpFuncData->lpData = lpData;

	cb.aio_buf = (uint64_t)lpFuncData;
	cb.aio_offset = 0;
	cb.aio_nbytes = sizeof((uint64_t)lpFuncData);//4096;
	cbs[0] = &cb;

	/*hIoCompletion =*/ io_submit(ctx, 1, cbs);
	//PostQueuedCompletionStatus( hIoCompletion, 0, (DWORD)lpFuncData, NULL );
}

//////////////////////////////////////////////////////////////////////////////////////////
void* AsyncFuncQueue::AsyncFuncQueueThread
//////////////////////////////////////////////////////////////////////////////////////////
// The async func queue thread. Calls each queued function calls
// 
(
 LPVOID lpVoid // The AsyncFuncQueue instance.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	CAutoThreadMonitor tmMonitor("AsyncFuncQueue");
    AsyncFuncQueue *pThis = reinterpret_cast< AsyncFuncQueue * >( lpVoid );
    pThis->AsyncFuncQueueFunc();
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void AsyncFuncQueue::AsyncFuncQueueFunc()
//////////////////////////////////////////////////////////////////////////////////////////
{
    //////////CoInitialize( NULL );
    // Force thread to run on the first CPU.
    //SetThreadAffinityMask( hThreadID, 1 );
    _LOG_DEBUG
        LOG_DEBUG_LVL1,
        "AsyncFuncQueueThread Id=%u",
        pthread_self()//GetCurrentThreadId()
    LOG_

	DWORD dwStopMessage = 0;
	DWORD dwlpFuncData;
	ASYNC_FUNC_DATA *lpFuncData;
	LPOVERLAPPED s_oDummy;(void)s_oDummy;

    CDeadlockDetector cDeadlockDetector;
    cDeadlockDetector.RegisterThread( hThreadID, "AsyncFuncQueue Thread", 300000  );
		struct io_event events[1];

	// Read until its time to terminate the thread.
	while( dwStopMessage == 0 ){
		ENTER_TIMEOUT
        // Get the next queued function
		/*if( GetQueuedCompletionStatus( hIoCompletion, &dwStopMessage, &dwlpFuncData, &s_oDummy, INFINITE ))*/if (io_getevents(ctx, 1, 1, events, NULL)){
            LEAVE_TIMEOUT
			// If this isn't a thread termination message
			if( dwStopMessage == 0 ){
				lpFuncData = (ASYNC_FUNC_DATA *)( dwlpFuncData );
				
				// Call the function with its parameters
                _LOG_DEBUG
                    LOG_DEBUG_HIGH,
                    "\r\nEntering async function. func adress 0x%x",
                    lpFuncData->lpFunc
                LOG_

                lpFuncData->lpFunc( lpFuncData->lpData );

                _LOG_DEBUG
                    LOG_DEBUG_HIGH,
                    "\r\nLeaving async function"
                LOG_

				// Delete the async data object.
				delete lpFuncData;
			}
	    	io_destroy(ctx);
		}            
	}

    //////////////////CoUninitialize();
    STOP_DEADLOCK_DETECTION
}

//////////////////////////////////////////////////////////////////////////////////////////
AsyncFuncQueue *AsyncFuncQueue::GetAcctQueue()
//////////////////////////////////////////////////////////////////////////////////////////
{
    static AsyncFuncQueue instance;
    return &instance;
}

//////////////////////////////////////////////////////////////////////////////////////////
AsyncFuncQueue *AsyncFuncQueue::GetMainQueue()
//////////////////////////////////////////////////////////////////////////////////////////
{
    static AsyncFuncQueue instance;
    return &instance;
}
