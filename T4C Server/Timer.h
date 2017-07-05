#ifndef TIMER_H_18092000
#define TIMER_H_18092000
#if defined(_MSC_VER)
//  Microsoft
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
//  GCC
	//typedef unsigned long DWORD;
	#define EXPORT __attribute__((visibility("default")))
    //#define IMPORT
#else
//  do nothing and hope for the best?
#define EXPORT
#define IMPORT
#pragma warning Unknown dynamic link import/export semantics.

DWORD EXPORT GetRunTime();
#endif
#endif // TIMER_H_18092000
