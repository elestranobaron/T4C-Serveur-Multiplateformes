/*
Thread Monitor
Written by Carlos Lima <carlos@dialsoft.com>
2006-03-17

This should register all running threads IDs and Names
so we can track what crashed and what else was running 
by that time.
*/
#include "Lock.h"
#include <map>

class CThreadMonitor : public CLock{
public:
	typedef std::map<DWORD, std::string> ThreadList;
	typedef std::map<DWORD, std::string>::iterator ThreadListIterator;

	static CThreadMonitor& GetInstance();
	void RegisterThread(std::string sThreadName);
	void UnregisterThread();
	bool GetThreadName(DWORD dwThreadID, std::string &sThreadName);
	void GetRunningThreadsList(ThreadList &containerForListOfThreads);
private:
	ThreadList runningThreadsMap;
	CThreadMonitor();
};

class CAutoThreadMonitor {
public:
	CAutoThreadMonitor(std::string sThreadName);
	~CAutoThreadMonitor();
};