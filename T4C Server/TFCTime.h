// TFCTime.h: interface for the TFCTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TFCTIME_H__B1BEE9F4_4580_11D1_BD5F_00E029058623__INCLUDED_)
#define AFX_TFCTIME_H__B1BEE9F4_4580_11D1_BD5F_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// These are real life values
#define MILLISECONDS * 2 / 100
#define TENTHS	* 2
#define SECONDS * 20
#define MINUTES SECONDS * 60
#define HOURS   SECONDS * 3600
#define DAYS    SECONDS * 86400
#define MILLISECOND * 2 / 100
#define TENTH	* 2
#define SECOND  * 20
#define MINUTE  SECOND * 60
#define HOUR    SECOND * 3600
#define DAY     SECOND * 86400


#define TDELAY	+ TFCMAIN::GetRound()

typedef struct _TFCTIME {
	int seconds;
	int minutes;
	int hours;
	int days;
	int weeks;
	int months;
	int years;
} TFCTIME, *LPTFCTIME;


class EXPORT TFCTime  
{
public:
	static void Create(TFCTIME &tCurrTime, TFCTIME &tMaxTime);
	static void IncTime();

	static int Second();
	static int Minute();
	static int Hour();
	static int Day();
	static int Week();
	static int Month();
	static int Year();
		
	static UINT TotalTime();

	static int MaxSeconds();
	static int MaxMinutes();
	static int MaxHours();
	static int MaxDays();
	static int MaxWeeks();
	static int MaxMonths();
	
	static BOOL IsNight();
	static BOOL IsDay();
	
	static BOOL IsMorning();
	static BOOL IsAfterNoon();
	static BOOL IsEvening();
    static BOOL IsSleepTime();

private:
	static TFCTIME tCurTime;
	static TFCTIME tMaxTime;
	static UINT nTotalTime;
};

#endif // !defined(AFX_TFCTIME_H__B1BEE9F4_4580_11D1_BD5F_00E029058623__INCLUDED_)
