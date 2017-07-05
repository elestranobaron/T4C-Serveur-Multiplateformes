#ifndef WINDOWS_LINUX_H
# define WINDOWS_LINUX_H

#if defined(_MSC_VER)
    //  Microsoft 
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
    #define CMP stricmp
#elif defined(__GNUC__)
	#include <stdbool.h>
	#include "Stdstrings/stdstring.h"
	#define CONFIG_FILE ".config.cfg"
	#define TRUE true
	#define FALSE false
	#define CMP strcasecmp
	//#define INVALID_HANDLE_VALUE -1 // pinvoke.net
	//# define CREATE_SUSPENDED 0x00000004
	//typedef int64_t __int64;
	typedef const char* LPCTSTR;
	typedef bool BOOL;
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
	typedef unsigned int UINT;
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
