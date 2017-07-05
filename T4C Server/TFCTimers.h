// TFCTimers.h: interface for the TFCTimers class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TFCTIMERS_H__3E772E33_3D1A_11D1_BD4E_00E029058623__INCLUDED_)
#define AFX_TFCTIMERS_H__3E772E33_3D1A_11D1_BD4E_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "stdafx.h"
#include "TFCTime.h"
#include "vdlist.h"
#include "Lock.h"

#define TIMERCALLBACK_PROTOTYPE	WORD wTimerID, BYTE bCallReason, LPVOID lpData, LPVOID lpUserData
typedef void (*TIMERCALLBACK)( TIMERCALLBACK_PROTOTYPE );


class EXPORT TFCTimers
{
public:
	TFCTimers( void );
	~TFCTimers( void );

	virtual void AddTimer( WORD wTimerID, DWORD dwTriggerTime, TIMERCALLBACK tcbFunc, 
						   LPVOID lpParams, BOOL boRelativeTime);

    virtual BOOL RemoveTimersByID( WORD wID );
	virtual BOOL RemoveTimersByParameter(LPVOID lpSearchParams);
	virtual BOOL RemoveTimersByCallback(TIMERCALLBACK tcbSearchFunc);
	virtual BOOL RemoveTimersByCallbackAndParameter(TIMERCALLBACK tcbSearchFunc, 
													LPVOID lpSearchParams);
	
	virtual void VerifyTimers();
	virtual void DestroyTimers();	

	typedef struct _TIMER_EVENT{
		WORD	wTimerID;		// ID of the timer.
		DWORD	dwTriggerTime;	// Round at which the timer triggers
		LPVOID	lpParams;		// Parameters associated to the timer.
		TIMERCALLBACK tcbFunc;	// The timer callback function.
	} TIMER_EVENT, *LPTIMER_EVENT;

private:
	
	TemplateList <TIMER_EVENT> *lptlteTimerList;
	
    CLock csThreadLock;
};

class EXPORT TFCTimerManager
{
public:
	static void AddTimer( WORD wTimerID, DWORD dwTriggerTime, TIMERCALLBACK tcbFunc, 
						 LPVOID lpParams, BOOL boRelativeTime);

	static BOOL RemoveTimersByID( WORD wTimerID );
    static BOOL RemoveTimersByParameter(LPVOID lpSearchParams);
	static BOOL RemoveTimersByCallback(TIMERCALLBACK tcbSearchFunc);
	static BOOL RemoveTimersByCallbackAndParameter(TIMERCALLBACK tcbSearchFunc, 
												  LPVOID lpSearchParams);

	static void VerifyTimers();
	static void DestroyTimers();

private:
	static TFCTimers tGlobalTimer;
};

#endif // !defined(AFX_TFCTIMERS_H__3E772E33_3D1A_11D1_BD4E_00E029058623__INCLUDED_)
