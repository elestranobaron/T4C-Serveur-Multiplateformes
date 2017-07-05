/*
Thread Monitor
Written by Carlos Lima <carlos@dialsoft.com>
2006-03-17

This should register all running threads IDs and Names
so we can track what crashed and what else was running 
by that time.
*/

#include "stdafx.h"
#include "ThreadMonitor.h"
#include "T4CLog.h"

CThreadMonitor::CThreadMonitor(){};
void CThreadMonitor::RegisterThread(std::string sThreadName){

	_LOG_DEBUG
		LOG_DEBUG_LVL4,
		"Starting thread %s ID %u", sThreadName.c_str(), GetCurrentThreadId()
	LOG_

	CAutoLock(this);
	runningThreadsMap[GetCurrentThreadId()] = sThreadName;
}
void CThreadMonitor::UnregisterThread(){

	_LOG_DEBUG
		LOG_DEBUG_LVL4,
		"Finishing thread %u", GetCurrentThreadId()
	LOG_

	CAutoLock(this);
	runningThreadsMap.erase(GetCurrentThreadId());
}

bool CThreadMonitor::GetThreadName(DWORD dwThreadID, std::string &sThreadName) {
	CAutoLock(this);
	ThreadListIterator i = runningThreadsMap.find(dwThreadID);
	if (i == runningThreadsMap.end()) return false;
	sThreadName = (*i).second;
	return true;
}
void CThreadMonitor::GetRunningThreadsList(ThreadList &containerForListOfThreads) {
	CAutoLock(this);
	containerForListOfThreads = runningThreadsMap;
}

CThreadMonitor& CThreadMonitor::GetInstance() {
	static CThreadMonitor threadMonitorInstance;
	return threadMonitorInstance;
}

CAutoThreadMonitor::CAutoThreadMonitor(std::string sThreadName) {
	CThreadMonitor::GetInstance().RegisterThread(sThreadName);
}

CAutoThreadMonitor::~CAutoThreadMonitor() {
	CThreadMonitor::GetInstance().UnregisterThread();
}
