// TFCTimers.cpp: implementation of the TFCTimers class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "TFCTimers.h"
#include "TFC_MAIN.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

TFCTimers TFCTimerManager::tGlobalTimer;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Constructor ///////////////////////////////////////////////////////////////////////////
TFCTimers::TFCTimers( void )
//////////////////////////////////////////////////////////////////////////////////////////
{
	lptlteTimerList = NULL;
}

// Destructor ////////////////////////////////////////////////////////////////////////////
 TFCTimers::~TFCTimers( void )
//////////////////////////////////////////////////////////////////////////////////////////
{
	if( lptlteTimerList != NULL ){
		delete lptlteTimerList;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
// This function adds a timer.
//	dwTriggerTime:		Round at which the timer should trigger.
//	tcbFunc:			Timer callback function which is triggered upon timer release.
//	lpParams:			Parameters to pass to the callback function.
//	boRelative:			TRUE if dwTriggerTime is relative to the current server time.
void TFCTimers::AddTimer( WORD wTimerID, DWORD dwTriggerTime, TIMERCALLBACK tcbFunc, 
						 LPVOID lpParams, BOOL boRelativeTime){
	
	csThreadLock.Lock();
	
	if( lptlteTimerList == NULL ){
		lptlteTimerList = new TemplateList< TIMER_EVENT >;
	}

	// creates and inits a new timerevent structure
	LPTIMER_EVENT newTimer	= new TIMER_EVENT;
	if(boRelativeTime){
		newTimer->dwTriggerTime = dwTriggerTime + TFCMAIN::GetRound();
	}else{
		newTimer->dwTriggerTime	= dwTriggerTime;
	}
	newTimer->wTimerID		= wTimerID;
	newTimer->lpParams		= lpParams;
	newTimer->tcbFunc		= tcbFunc;
	lptlteTimerList->AddToTail(newTimer);

	csThreadLock.Unlock();
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// This function removes all timers that have lpParam as parameter
//	lpParam:	Address parameter to seek and destroy
// return:		TRUE if any timer has been removed
BOOL TFCTimers::RemoveTimersByParameter(LPVOID lpSearchParam){
	
	LPTIMER_EVENT lpteThisTimer;
	BOOL boDestroyed = FALSE;
	
	if( lptlteTimerList != NULL ){	
		csThreadLock.Lock();
		
		lptlteTimerList->ToHead();
		while( lptlteTimerList->QueryNext() ){
			lpteThisTimer = lptlteTimerList->Object();
		
			// If timer has this parameter, destroy it
			if(lpteThisTimer->lpParams == lpSearchParam){
				lptlteTimerList->DeleteAbsolute();
				boDestroyed = TRUE;
			}
		}

		csThreadLock.Unlock();
	}

	return boDestroyed;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// This function removes all timers that have tcbSearchFunc as callback function
//	tcbSearchFunc:	Destroy timers associated with this callback function
// return:			TRUE if any timer has been removed.
BOOL TFCTimers::RemoveTimersByCallback(TIMERCALLBACK tcbSearchCallback){

	LPTIMER_EVENT lpteThisTimer;
	BOOL boDestroyed = FALSE;
	
	if( lptlteTimerList != NULL ){
		csThreadLock.Lock();
		
		lptlteTimerList->ToHead();
		while( lptlteTimerList->QueryNext() ){
			lpteThisTimer = lptlteTimerList->Object();
		
			// If timer has this parameter, destroy it
			if(lpteThisTimer->tcbFunc == tcbSearchCallback){
				lptlteTimerList->DeleteAbsolute();
				boDestroyed = TRUE;
			}
		}

		csThreadLock.Unlock();
	}

	return boDestroyed;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// This function removes all timers that have both the callback function, and the parameter
//	tcbSearchFunc:	Destroy timers associated with this callback function
//	lpParam:		Address parameter to seek and destroy
// return:			TRUE if any timer has been removed./
BOOL TFCTimers::RemoveTimersByCallbackAndParameter(TIMERCALLBACK tcbSearchCallback,
												   LPVOID lpSearchParams){
	LPTIMER_EVENT lpteThisTimer;
	BOOL boDestroyed = FALSE;
	
	if( lptlteTimerList != NULL ){
		csThreadLock.Lock();
		
		lptlteTimerList->ToHead();
		while( lptlteTimerList->QueryNext() ){
			lpteThisTimer = lptlteTimerList->Object();
		
			// If timer has this parameter, destroy it
			if( lpteThisTimer->tcbFunc == tcbSearchCallback && 
			   lpteThisTimer->lpParams == lpSearchParams ){
				
				lptlteTimerList->DeleteAbsolute();
				boDestroyed = TRUE;
			}
		}

		csThreadLock.Unlock();
	}

	return boDestroyed;
}


BOOL TFCTimers::RemoveTimersByID( WORD wID ){
    LPTIMER_EVENT lpteThisTimer;
    
    BOOL boDestroyed = FALSE;

	if( lptlteTimerList != NULL ){
		csThreadLock.Lock();
		
		lptlteTimerList->ToHead();
		while( lptlteTimerList->QueryNext() ){
			lpteThisTimer = lptlteTimerList->Object();
		
			// If timer has this parameter, destroy it
			if( lpteThisTimer->wTimerID == wID ){				
				lptlteTimerList->DeleteAbsolute();
				boDestroyed = TRUE;
			}
		}

		csThreadLock.Unlock();
	}
    
    return boDestroyed;
}

/////////////////////////////////////////////////////////////////////////////////////////
// This function checks all the timers to see if any have popped. (internal)
void TFCTimers::VerifyTimers(){
	if( lptlteTimerList != NULL ){
	
		csThreadLock.Lock();
		LPTIMER_EVENT lpteThisTimer;

		// Makes a copy of the timers to call on the stack (to avoid thread problems)
		TemplateList <TIMER_EVENT> tlteCallTimer;

		lptlteTimerList->ToHead();
		while( lptlteTimerList->QueryNext()){
			lpteThisTimer = lptlteTimerList->Object();

			if(lpteThisTimer->dwTriggerTime <= TFCMAIN::GetRound()){
				tlteCallTimer.AddToTail(lpteThisTimer);
				lptlteTimerList->Remove();
			}
		}
		csThreadLock.Unlock();
		// Unlocks the object before calling the timers callback function to enable
		// them to create a timer themselves (without deadlocking everything up).
		tlteCallTimer.ToHead();
		while(tlteCallTimer.QueryNext()){
			lpteThisTimer = tlteCallTimer.Object();
			// Call the callback function
			lpteThisTimer->tcbFunc( lpteThisTimer->wTimerID, MSG_OnTimer, lpteThisTimer->lpParams, NULL );

            tlteCallTimer.DeleteAbsolute();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
// This functions destroys all the timers.
void TFCTimers::DestroyTimers(){
	if( lptlteTimerList != NULL ){
		csThreadLock.Lock();

		lptlteTimerList->ToHead();
		while( lptlteTimerList->QueryNext() )
			lptlteTimerList->DeleteAbsolute();
		
		csThreadLock.Unlock();
	}
}
/*
//////////////////////////////////////////////////////////////////////////////////////////
void TFCTimers::SaveTimers
//////////////////////////////////////////////////////////////////////////////////////////
// Saves the timers into a CVDByteArray used by the player database.
// 
(
 CVDByteArray &vdbBuffer // The buffer
)
//////////////////////////////////////////////////////////////////////////////////////////
{	
	if( lptlteTimerList != NULL ){
		csThreadLock.Lock();

		TIMER_EVENT *lpTimerEvent;
		int i;
		
		vdbBuffer << (WORD)lptlteTimerList->NbObjects();
		
		DATA_SAVE sDataSave;

		lptlteTimerList->ToHead();
		while( lptlteTimerList->QueryNext() ){
			lpTimerEvent = lptlteTimerList->Object();

			vdbBuffer << (WORD)lpTimerEvent->wTimerID;
			vdbBuffer << (DWORD)( lpTimerEvent->dwTriggerTime - TFCMAIN::GetRound() );

			if( lpTimerEvent->tcbFunc ){
				ZeroMemory( &sDataSave, sizeof( DATA_SAVE ) );
				lpTimerEvent->tcbFunc( lpTimerEvent->wTimerID, MSG_OnSavePlayer, lpTimerEvent->lpParams, &sDataSave );
			}

			vdbBuffer << (BYTE)sDataSave.bBufferSize;

			if( sDataSave.bBufferSize > 0 ){
				for( i = 0; i < sDataSave.bBufferSize; i++ ){
					vdbBuffer << (BYTE)( sDataSave.lpbData[ i ] );
				}

				delete sDataSave.lpbData;
			}			
		}

		csThreadLock.Unlock();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCTimers::LoadTimers
//////////////////////////////////////////////////////////////////////////////////////////
// Loads the timer from a VDByteArry supplied by the character database.
// 
(
 CVDByteArray &vdbBuffer // The buffer.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	csThreadLock.Lock();
	if( lptlteTimerList == NULL ){
		lptlteTimerList = new TemplateList <TIMER_EVENT>;
	}

	TIMER_EVENT *lpTimerEvent;
	int i, j;
	WORD wNbTimers;
	DATA_SAVE sDataSave;

	vdbBuffer >> (WORD &)wNbTimers;

	for( i = 0; i < wNbTimers; i++ ){
		lpTimerEvent = new TIMER_EVENT;

		vdbBuffer >> (WORD &)lpTimerEvent->wTimerID;
		vdbBuffer >> (DWORD &)( lpTimerEvent->dwTriggerTime );
		lpTimerEvent->dwTriggerTime += TFCMAIN::GetRound();
		
		lpTimerEvent->tcbFunc = TFCTimersManager::GetTimerProc( lpTimerEvent->wTimerID );
		lpTimerEvent->lpParams = NULL;

		vdbBuffer >> (BYTE &)( sDataSave.bBufferSize );

		if( sDataSave.bBufferSize > 0 ){
			sDataSave.lpbData = new BYTE[ sDataSave.bBufferSize ];
			
			for( j = 0; j < sDataSave.bBufferSize; j++ ){
				vdbBuffer >> (BYTE &)( sDataSave.lpbData[ j ] );
			}	
		
			if( lpTimerEvent->tcbFunc != NULL ){
				// Ask the timer function if it needs to rebuild the timer event.
				lpTimerEvent->tcbFunc( lpTimerEvent->wTimerID, MSG_OnLoadPlayer, lpTimerEvent, &sDataSave );
			}
		}
	}

	if( lptlteTimerList->NbObjects == 0 ){
		delete lptlteTimerList;
		lptlteTimerList = NULL;
	}

	csThreadLock.Unlock();
}*/
//////////////////////////////////////////////////////////////////////////////////////////
void TFCTimerManager::AddTimer
//////////////////////////////////////////////////////////////////////////////////////////
// Adds a global timer
// 
(
 WORD wTimerID,
 DWORD dwTriggerTime,		// Elapse time after which timer should be triggered
 TIMERCALLBACK tcbFunc,		// Timer callback function
 LPVOID lpParams,			// User parameters
 BOOL boRelativeTime		// TRUE if dwTriggerTime is an absolute 'round' time.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	tGlobalTimer.AddTimer( wTimerID, dwTriggerTime, tcbFunc, lpParams, boRelativeTime );
}
	
//////////////////////////////////////////////////////////////////////////////////////////
BOOL TFCTimerManager::RemoveTimersByParameter
//////////////////////////////////////////////////////////////////////////////////////////
// Remove all timers using a certain parameter
// 
(
 LPVOID lpSearchParams // The parameter to seek and destroy
)
// Return: BOOL, TRUE if timer was found and destroyed.
//////////////////////////////////////////////////////////////////////////////////////////
{
	return tGlobalTimer.RemoveTimersByParameter( lpSearchParams );
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL TFCTimerManager::RemoveTimersByCallback
//////////////////////////////////////////////////////////////////////////////////////////
// Remove all timers using a certain parameter
// 
(
 TIMERCALLBACK tcbSearchFunc	// Callback function to seek and destroy.
)
// Return: BOOL, TRUE if timer was found and destroyed.
//////////////////////////////////////////////////////////////////////////////////////////
{
	return tGlobalTimer.RemoveTimersByParameter( tcbSearchFunc );
}

BOOL TFCTimerManager::RemoveTimersByID( WORD wID ){
    return tGlobalTimer.RemoveTimersByID( wID );
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL TFCTimerManager::RemoveTimersByCallbackAndParameter
//////////////////////////////////////////////////////////////////////////////////////////
// Both above functions combined
// 
(
 TIMERCALLBACK tcbSearchFunc,	// "
 LPVOID lpSearchParams			// "
)
// Return: BOOL, "
//////////////////////////////////////////////////////////////////////////////////////////
{
	return tGlobalTimer.RemoveTimersByCallbackAndParameter( tcbSearchFunc, lpSearchParams );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCTimerManager::VerifyTimers( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Verifies the global timers.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	tGlobalTimer.VerifyTimers();
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCTimerManager::DestroyTimers( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Destroy all the global timers
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	tGlobalTimer.DestroyTimers();
}