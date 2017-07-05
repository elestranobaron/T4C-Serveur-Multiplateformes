//////////////////////////////////////////////////////////////////////////////////////////
//ODBCTrace.h
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_ODBCTrace_H__A7D17DE3_1349_11D1_BCE6_00E__INCLUDED_)
#define AFX_ODBCTrace_H__A7D17DE3_1349_11D1_BCE6_00E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
//////////////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include "Lock.h"

#define VECTOR_SIZE  99
typedef std::vector <CString> csVectorRequest;
typedef std::vector <unsigned long> loVectorDuration;

class ODBCTrace 
{

private:
    static  CLock cTraceLock;  

public:
	ODBCTrace();
	virtual ~ODBCTrace();	

	void addRequest( CString request);
	void addDuration( unsigned long duration );

    void Lock();
    void Unlock();

	csVectorRequest getVectorRequest();
	loVectorDuration getVectorDuration();

private:
    bool bTraceLock;
	csVectorRequest vecRequest;
	loVectorDuration vecDuration;
};
#endif // !defined(AFX_ODBCTrace_H__A7D17DE3_1349_11D1_BCE6_00E__INCLUDED_)
