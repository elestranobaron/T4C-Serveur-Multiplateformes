#ifndef WINDOWS_LINUX_H
# define WINDOWS_LINUX_H

#if defined(_MSC_VER)
    //  Microsoft 
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
    #define CMP stricmp
#elif defined(__GNUC__)
	#include <stdbool.h>
#include <sqltypes.h>
	#include "Stdstrings/stdstring.h"
	#define CONFIG_FILE ".config.cfg"
	#define TRUE true
	#define FALSE false
	#define CMP strcasecmp
	//#define INVALID_HANDLE_VALUE -1 // pinvoke.net
	//# define CREATE_SUSPENDED 0x00000004
	//typedef int64_t __int64;
	typedef const char* LPCTSTR;
	// typedef bool BOOL; // Already declared in sqltype which comes because UINT was wrongly designed by ME
	typedef void* PVOID;
	typedef PVOID HANDLE;
	typedef HANDLE HKEY;
	typedef unsigned short WORD;
	typedef WORD* LPWORD;
	typedef unsigned int DWORD; // si ca est defini dans timer.h il ne pleure pas dans shared structure
	typedef unsigned char BYTE;
	typedef BYTE* LPBYTE;
	typedef void VOID;
	typedef VOID* LPVOID;
	//typedef unsigned int UINT;
	typedef int INT;
	typedef INT* LPINT;
	typedef long LONG;
	typedef unsigned long ULONG;
	typedef unsigned long ULONG_PTR;
	typedef struct _OVERLAPPED {
	  ULONG_PTR Internal;
	  ULONG_PTR InternalHigh;
	  union {
		    struct {
		      DWORD Offset;
		      DWORD OffsetHigh;
		    };
		    PVOID  Pointer;
		  };
		  HANDLE    hEvent;
	} OVERLAPPED, *LPOVERLAPPED;
	typedef DWORD COLORREF;
	COLORREF RGB(
		BYTE byRed,
		BYTE byGreen,
		BYTE byBlue
	);
	typedef struct _EXCEPTION_RECORD {
		DWORD                    ExceptionCode;
		DWORD                    ExceptionFlags;
		struct _EXCEPTION_RECORD  *ExceptionRecord;
		PVOID                    ExceptionAddress;
		DWORD                    NumberParameters;
		ULONG_PTR                ExceptionInformation[15];//EXCEPTION_MAXIMUM_PARAMETERS;
	} EXCEPTION_RECORD, *PEXCEPTION_RECORD;
	typedef struct _EXCEPTION_POINTERS {
		PEXCEPTION_RECORD ExceptionRecord;
		//PCONTEXT          ContextRecord; // du pur concetré
	} EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;
	typedef PEXCEPTION_POINTERS LPEXCEPTION_POINTERS;

	struct mrevent {
		pthread_mutex_t mutex;
		pthread_cond_t cond;
		bool triggered;
	};

	void mrevent_init(struct mrevent *ev) {
		pthread_mutex_init(&ev->mutex, 0);
		pthread_cond_init(&ev->cond, 0);
		ev->triggered = false;
}

	void mrevent_trigger(struct mrevent *ev) {
		pthread_mutex_lock(&ev->mutex);
		ev->triggered = true;
		pthread_cond_signal(&ev->cond);
		pthread_mutex_unlock(&ev->mutex);
}

	void mrevent_reset(struct mrevent *ev) {
		pthread_mutex_lock(&ev->mutex);
		ev->triggered = false;
		pthread_mutex_unlock(&ev->mutex);
}

	void mrevent_wait(struct mrevent *ev) {
		pthread_mutex_lock(&ev->mutex);
		while (!ev->triggered)
			pthread_cond_wait(&ev->cond, &ev->mutex);
		pthread_mutex_unlock(&ev->mutex);
	}
/* https://codereview.stackexchange.com/questions/223492/c-simulating-windows-io-completion-ports-in-linux */
#include <queue>
#include <condition_variable>
#include <unistd.h>
#include <sys/epoll.h>
#include <thread>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <cstdio>
#include <cstring>
#include <cerrno>
using namespace std;

template <class T>
class SafeQueue
{
public:

    SafeQueue()
    {}
    void Push(const T& val);
    void Push(T&& val);
    void Pop(T& val);
    T Pop();
    void Clear();
    bool IsEmpty();
    size_t Size();
private :
    std::queue<T> q;
    std::mutex mtx;
    std::condition_variable cv;
};

template<class T>
inline void SafeQueue<T>::Push(const T& val)
{
    std::unique_lock<std::mutex> lock(mtx);
    q.emplace(val);
    cv.notify_one();
}

template<class T>
inline void SafeQueue<T>::Push(T&& val)
{
    std::unique_lock<std::mutex> lock(mtx);
    q.emplace(std::move(val));
    cv.notify_one();
}

template<class T>
inline void SafeQueue<T>::Pop(T& val)
{
    std::unique_lock<std::mutex> lock(mtx);
    while (q.empty())
    {
        cv.wait(lock);
    }
    val = q.front();
    q.pop();
}

template <class T>
inline T SafeQueue<T>::Pop()
{
    T val;
    std::unique_lock<std::mutex> lock(mtx);
    while (q.empty())
    {
        cv.wait(lock);
    }
    val = q.front();
    q.pop();
    return val;
}

template <class T>
inline void SafeQueue<T>::Clear()
{
    std::unique_lock<std::mutex> lock(mtx);
    while(!q.empty())
        q.pop();
}

template <class T>
inline bool SafeQueue<T>::IsEmpty()
{
    std::unique_lock<std::mutex> lock(mtx);
    return q.empty();
}

template <class T>
inline size_t SafeQueue<T>::Size()
{
    std::unique_lock<std::mutex> lock(mtx);
    return q.size();
}

#define Io_Chunk_Size size_t(1024)

enum IoOpCode
{
    IoWriteCode,
    IoReadCode,
    IoSpecialCode,
};

enum class IoStatusCode
{
    IoStatusOk,
    IoStatusPending,
    IoStatusFailed,
};

struct IoContext
{
    IoStatusCode code;
    unsigned int bytes;
    void *buffer;
    unsigned int key;
};

struct IoOperationStruct
{
    IoOperationStruct()
    {}
    IoOperationStruct(const epoll_event& ev);
    std::shared_ptr<SafeQueue<IoContext*>> rport;
    int fd;
    char *buffer;
    IoOpCode code;
    IoContext *context;
    size_t rest;
    size_t offset;
};

static int io_epoll_instance;

static SafeQueue<IoOperationStruct*> io_requests;

static bool IoStopFlag;

void IoMainThread()
{
    epoll_event evs[50];
    while(!IoStopFlag)
    {
        int num = epoll_wait(io_epoll_instance, evs, 50, 10000);
        if (num < 0)
            return;
        for (int i = 0; i < num; ++i)
        {
            io_requests.Push((IoOperationStruct*)evs[i].data.ptr);
        }
    }
}

bool AddIoToQueue(IoOperationStruct *IoStruct, bool modify = false)
{
    epoll_event ev;
    ev.events = EPOLLONESHOT;
    switch(IoStruct->code)
    {
        case IoWriteCode :
            ev.events |= EPOLLOUT;
            break;
        case IoReadCode :
            ev.events |= EPOLLIN;
            break;
        default:
            break;
    }
    ev.data.ptr = IoStruct;
    bool res = epoll_ctl(io_epoll_instance, modify ? EPOLL_CTL_MOD : EPOLL_CTL_ADD,IoStruct->fd,  &ev) != -1;
    if (!res)
    {
        if (errno == EPERM)
        {
            res = true;
            io_requests.Push(IoStruct);
        }
    }
    if (!res)
        cout << "failed with error : " << strerror(errno) << endl;
    return res;
}

struct HANDLEQUEUE
{
    shared_ptr<SafeQueue<IoContext*>> q;
    int fd;
    unsigned int key;
};

HANDLEQUEUE CreateIoCompletionPort()
{
    HANDLEQUEUE port;
    port.q = make_shared<SafeQueue<IoContext*>>();
    port.fd = 0;
    return port;
}

void CloseHandle(HANDLEQUEUE Handle)
{
    Handle.q.reset();
    if (Handle.fd)
        close(Handle.fd);
    Handle.fd = 0;
}

HANDLEQUEUE BindToPort(HANDLEQUEUE port, int fd, unsigned int key)
{
    HANDLEQUEUE handle;
    handle.fd = fd;
    handle.q = port.q;
    handle.key = key;
    return handle;
}

bool GetQueuedCompletionStatus(HANDLEQUEUE port, unsigned int *num_of_bytes, IoContext **ctx, unsigned int *key, unsigned int wait_time)
{
    port.q->Pop(*ctx);
    *num_of_bytes = (*ctx)->bytes;
    *key = (*ctx)->key;
    if (*num_of_bytes)
        (*ctx)->code = IoStatusCode::IoStatusOk;
    else
        (*ctx)->code = IoStatusCode::IoStatusFailed;
    return true;
}

bool WriteFile(HANDLEQUEUE Handle, const void *data, size_t size, IoContext * Ctx)
{
    if (!data || !size || !Ctx)
        return false;
    IoOperationStruct *IoStruct = new IoOperationStruct();
    IoStruct->fd = Handle.fd;
    IoStruct->rport = Handle.q;
    IoStruct->buffer = (char*)data;
    IoStruct->context = Ctx;
    IoStruct->offset = 0;
    IoStruct->rest = size;
    IoStruct->code = IoOpCode::IoWriteCode;
    IoStruct->context->bytes = 0;
    IoStruct->context->code = IoStatusCode::IoStatusPending;
    return AddIoToQueue(IoStruct);
}

bool ReadFile(HANDLEQUEUE Handle, void *data, size_t size, IoContext *Ctx)
{
    if (!data || !size || !Ctx)
        return false;
    IoOperationStruct *IoStruct = new IoOperationStruct();
    IoStruct->fd = Handle.fd;
    IoStruct->rport = Handle.q;
    IoStruct->buffer = (char*)data;
    IoStruct->context = Ctx;
    IoStruct->offset = 0;
    IoStruct->rest = size;
    IoStruct->code = IoOpCode::IoReadCode;
    IoStruct->context->bytes = 0;
    IoStruct->context->code = IoStatusCode::IoStatusPending;
    return AddIoToQueue(IoStruct);
}

bool IoHandleWrite(IoOperationStruct & IoStruct)
{
    if (!IoStruct.rest)
        return false;
    size_t to_write = std::min(IoStruct.rest, Io_Chunk_Size);
    int written = write(IoStruct.fd, IoStruct.buffer + IoStruct.offset, to_write);
    if (written < 0)
    {
        if (errno == EWOULDBLOCK || errno == EAGAIN)
            return true;
        return false;
    }
    IoStruct.offset += written;
    IoStruct.rest -= written;
    IoStruct.context->bytes += written;
    if (!IoStruct.rest)
        return false;
    return true;
}

bool IoHandleRead(IoOperationStruct& IoStruct)
{
    if (!IoStruct.rest)
        return false;
    size_t to_read = std::min(IoStruct.rest, Io_Chunk_Size);
    int was_read = read(IoStruct.fd, IoStruct.buffer + IoStruct.offset, to_read);
    if (was_read < 0)
    {
        if (errno == EWOULDBLOCK || errno == EAGAIN)
            return true;
        return false;
    }
    IoStruct.offset += was_read;
    IoStruct.context->bytes += was_read;
    IoStruct.rest -= was_read;
    if (!IoStruct.rest)
        return false;
    return true;
}

void IoHandleResult(bool result, IoOperationStruct *IoStruct)
{
    if (!result)
    {
        shared_ptr<SafeQueue<IoContext*>> rport = IoStruct->rport;
        IoContext *Ctx = IoStruct->context;
        delete IoStruct;
        rport->Push(Ctx);
    }
    else
    {
        if (!AddIoToQueue(IoStruct, true))
            return IoHandleResult(false, IoStruct);
    }
}

void IoHandlerThread()
{
    IoOperationStruct *IoStruct;
    while(!IoStopFlag)
    {
        io_requests.Pop(IoStruct);

        if (IoStruct->code == IoOpCode::IoWriteCode)
        {
            bool result = IoHandleWrite(*IoStruct);
            IoHandleResult(result, IoStruct);
        }
        else if (IoStruct->code == IoOpCode::IoReadCode)
        {
            bool result = IoHandleRead(*IoStruct);
            IoHandleResult(result, IoStruct);
        }
        else if (IoStruct->code == IoOpCode::IoSpecialCode)
        {
            IoHandleResult(false, IoStruct);
        }
    }
}

void start_io_ports()
{
    io_epoll_instance = epoll_create(10);
    if (io_epoll_instance < 0)
        cout << "failed to open epoll with error : " << strerror(errno) << endl;
    IoStopFlag = false;
    std::thread(IoMainThread).detach();
    for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
    {
        std::thread(IoHandlerThread).detach();
    }
}

HANDLEQUEUE port;

std::condition_variable cv;
std::mutex mtx;

void worker_thread()
{
    cout << "id : " << this_thread::get_id() << endl;
    while (1)
    {
        unsigned int bytes;
        unsigned int key;
        IoContext *ctx;
        GetQueuedCompletionStatus(port, &bytes, &ctx, &key, 1000);
        cout << " ======== " << endl;
        cout << "io was performed " << endl;
        cout << "bytes transferred : " << bytes << endl;
        cout << " ========= " << endl;
        delete (char*)ctx->buffer;
        delete ctx;
    }
}
/*
int main()
{
    start_io_ports();
    port = CreateIoCompletionPort();
    int fd = open("/sdcard/Ayat/test.txt", O_WRONLY | O_CREAT);
    if (fd < 0)
    {
        cout << "error : " << strerror(errno) << endl;
        return 0;
    }
    HANDLE file = BindToPort(port, fd, 5);
    std::thread(worker_thread).detach();
    sleep(1);
    while (1)
    {
        cout << "submitting a job" << endl;
        char *buff = new char[10010];
        IoContext *ctx = new IoContext();
        ctx->buffer = buff;
        size_t to_write = 0;
        for (size_t i = 0; i < 10000; i += 9)
        {
            memcpy(buff + i, "ttttttttt", 9);
            to_write += 9;
        }
        if(!WriteFile(file, buff,to_write,  ctx))
            cout << "failed !" << endl;
        sleep(2);
    }
    CloseHandle(file);
    sleep(10000000000000000);
}*/
/* https://codereview.stackexchange.com/questions/223492/c-simulating-windows-io-completion-ports-in-linux */

    //  GCC
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#else
    //  do nothing and hope for the best?
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#endif
