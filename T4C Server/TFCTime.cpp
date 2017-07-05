// TFCTime.cpp: implementation of the TFCTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "TFCTime.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

TFCTIME TFCTime::tMaxTime;
TFCTIME TFCTime::tCurTime;
UINT	TFCTime::nTotalTime = 0;

//////////////////////////////////////////////////////////////////////
// Init the time variables.
void TFCTime::Create(TFCTIME &tNewCurTime, TFCTIME &tNewMaxTime){
	tCurTime = tNewCurTime;
	tMaxTime = tNewMaxTime;
}

//////////////////////////////////////////////////////////////////////
// returns the current second
int TFCTime::Second(){
	return tCurTime.seconds;
}
//////////////////////////////////////////////////////////////////////
// returns the current minute
int TFCTime::Minute(){
	return tCurTime.minutes;
}
//////////////////////////////////////////////////////////////////////
// returns the current hour
int TFCTime::Hour(){
	return tCurTime.hours;
}
//////////////////////////////////////////////////////////////////////
// returns the current day
int TFCTime::Day(){
	return tCurTime.days;
}
//////////////////////////////////////////////////////////////////////
// returns the current week
int TFCTime::Week(){
	return tCurTime.weeks;
}
//////////////////////////////////////////////////////////////////////
// returns the current month
int TFCTime::Month(){
	return tCurTime.months;
}
//////////////////////////////////////////////////////////////////////
// returns the current year
int TFCTime::Year(){
	return tCurTime.years;
}


//////////////////////////////////////////////////////////////////////
// returns the current second
int TFCTime::MaxSeconds(){
	return tMaxTime.seconds;
}
//////////////////////////////////////////////////////////////////////
// returns the current minute
int TFCTime::MaxMinutes(){
	return tMaxTime.minutes;
}
//////////////////////////////////////////////////////////////////////
// returns the current hour
int TFCTime::MaxHours(){
	return tMaxTime.hours;
}
//////////////////////////////////////////////////////////////////////
// returns the current day
int TFCTime::MaxDays(){
	return tMaxTime.days;
}
//////////////////////////////////////////////////////////////////////
// returns the current week
int TFCTime::MaxWeeks(){
	return tMaxTime.weeks;
}
//////////////////////////////////////////////////////////////////////
// returns the current month
int TFCTime::MaxMonths(){
	return tMaxTime.months;
}
///////////////////////////////////////////////////////////////////////
// returns the total time, in seconds, elasped since the server started
UINT TFCTime::TotalTime(){
	return nTotalTime;
}


////////////////////////////////////////////////////////////////////////////////////////////
// returns TRUE if it's currently night
BOOL TFCTime::IsNight(){
	// If time is in it's first quarter, or last quarter of the day 
	// Classic: [0h00-6h00[ [18h00-0h00[
	if(tCurTime.hours < tMaxTime.hours / 4 || tCurTime.hours >= (tMaxTime.hours * 3 / 4))
		return TRUE;
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////
// returns TRUE if it's currently the day
BOOL TFCTime::IsDay(){
	// Classic: [6h00-18h00[
	return !IsNight();
}

////////////////////////////////////////////////////////////////////////////////////////////
// returns TRUE if it's currently the morning
BOOL TFCTime::IsMorning(){
	// [6h00-12h00[
	if(tCurTime.hours >= tMaxTime.hours / 4 && tCurTime.hours < tMaxTime.hours / 2)
		return TRUE;
	return FALSE;
}
////////////////////////////////////////////////////////////////////////////////////////////
// returns TRUE if it's currently the afternoon
BOOL TFCTime::IsAfterNoon(){
	// [12h00-18h00[
	if(tCurTime.hours >= tMaxTime.hours / 2 && tCurTime.hours <= tMaxTime.hours * 3 / 4)
		return TRUE;
	return FALSE;
}
////////////////////////////////////////////////////////////////////////////////////////////
// returns TRUE if it's currently the evening
BOOL TFCTime::IsEvening(){
	// [18h00-0h00[
	if(tCurTime.hours >= tMaxTime.hours * 3 / 4)
		return TRUE;
	return FALSE;
}

BOOL TFCTime::IsSleepTime(){
    // Asleep: [0h00-6h00[ [23h00-0h00[
    if ((tCurTime.hours < tMaxTime.hours / 4) || ( tCurTime.hours >= ( tMaxTime.hours * 23 ) / 24 ) )
        return TRUE;
	return FALSE;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// Increments the timer (for a second)
void TFCTime::IncTime(){
	tCurTime.seconds++;
	nTotalTime++;
	if(tCurTime.seconds == tMaxTime.seconds){
			tCurTime.seconds = 0;
			tCurTime.minutes++;
			if(tCurTime.minutes == tMaxTime.minutes){
			TRACE(_T("Year: %u, Month: %u, Week: %u, Day: %u, Hour: %u, Minute: %u, Second: %u.\r\n"),
			tCurTime.years, tCurTime.months, tCurTime.weeks, tCurTime.days, tCurTime.hours, 
			tCurTime.minutes, tCurTime.seconds);

				tCurTime.minutes = 0;
				tCurTime.hours++;
				if(tCurTime.hours == tMaxTime.hours){
					tCurTime.hours = 0;
					tCurTime.days++;
					if(tCurTime.days == tMaxTime.days){
						tCurTime.days = 0;
						tCurTime.weeks++;
						if(tCurTime.weeks == tMaxTime.weeks){
							tCurTime.weeks = 0;
							tCurTime.months++;
							if(tCurTime.months == tMaxTime.months){
								tCurTime.months = 0;
								tCurTime.years++;
							}
						}
					}
				}
			}
		}

}