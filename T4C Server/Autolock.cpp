// ************************************************************************
// ***                                                                  ***
//      File Name: Autolock.cpp
//      Project:   The 4th Coming
//      Creation:  Friday, September 24, 1999
//      Author:    Ben Thomas (TH)
// ***                                                                  ***
// ************************************************************************
// *** Copyright (c) 1997-1999 Vircom. All rights reserved.             ***

#include "stdafx.h"
#include "Autolock.h"

//*********************************************************************************
Autolock::Autolock
/**********************************************************************************
 * Constructor, Enter the critical section
 */
(
 #if defined(_MSC_VER)
 CRITICAL_SECTION *cs           // The Critical Section to lock (unlock).
 #elif defined(__GNUC__)
 pthread_mutex_t m
 #else
 #endif
)
//*********************************************************************************
{
	#if defined(_MSC_VER)
	m_cs = cs; // Remember the Critical section, needed for the destructor.
	EnterCriticalSection(m_cs);
	#elif defined(__GNUC__)
	m_cp = m;
	pthread_mutex_lock (&m_cp);
	#else
	#endif
}

//*********************************************************************************
Autolock::~Autolock( void )
/**********************************************************************************
 * Destructor, Leave the Critical Section when the the instance goes out of scope.
 */
{
	#if defined(_MSC_VER)
	LeaveCriticalSection(m_cs);
	#elif defined(__GNUC__)
	pthread_mutex_unlock (&m_cp);
	#else
	#endif
}
