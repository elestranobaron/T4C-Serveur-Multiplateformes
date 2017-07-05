// AsyncFuncQueue.h: interface for the AsyncFuncQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASYNCFUNCQUEUE_H__EFFD7FAE_F0BA_11D1_830E_00104B2CA38F__INCLUDED_)
#define AFX_ASYNCFUNCQUEUE_H__EFFD7FAE_F0BA_11D1_830E_00104B2CA38F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <fcntl.h>
#include <linux/aio_abi.h>
#include <sys/syscall.h>
int io_setup(unsigned nr, aio_context_t *ctxp) {
    return syscall(__NR_io_setup, nr, ctxp);
}
int io_destroy(aio_context_t ctx) {
    return syscall(__NR_io_destroy, ctx);
}
int io_submit(aio_context_t ctx, long nr,  struct iocb **iocbpp) {
    return syscall(__NR_io_submit, ctx, nr, iocbpp);
}
int io_getevents(aio_context_t ctx, long min_nr, long max_nr, struct io_event *events, struct timespec *timeout) {
    return syscall(__NR_io_getevents, ctx, min_nr, max_nr, events, timeout);
}
///////////#include <libaio.h>
#include "vdlist.h"

typedef void ( *ASYNC_FUNC )( LPVOID lpData );

//////////////////////////////////////////////////////////////////////////////////////////
// This class handles queued function calls. Allows asynchronous calls to functions 
// without having to start a new thread each time.
class EXPORT AsyncFuncQueue
{
public:	
	void Destroy( void );

	void Call( ASYNC_FUNC lpFunc, LPVOID lpData );

    static AsyncFuncQueue *GetMainQueue();
    static AsyncFuncQueue *GetAcctQueue();

private:
    AsyncFuncQueue();

	void Initialize( void );

	struct ASYNC_FUNC_DATA{
		ASYNC_FUNC lpFunc;
		LPVOID lpData;
	};

	HANDLE hIoCompletion;
	HANDLE hThreadID;
	aio_context_t ctx;

	static void* CALLBACK AsyncFuncQueueThread( LPVOID lpVoid ); // uint sous window
    void AsyncFuncQueueFunc();
};

#endif // !defined(AFX_ASYNCFUNCQUEUE_H__EFFD7FAE_F0BA_11D1_830E_00104B2CA38F__INCLUDED_)
