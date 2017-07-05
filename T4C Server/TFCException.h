// TFCException.h: interface for the TFCException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TFCEXCEPTION_H__E5BFC953_31DF_11D1_BD35_00E029058623__INCLUDED_)
#define AFX_TFCEXCEPTION_H__E5BFC953_31DF_11D1_BD35_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "TFCServerContext.h"

#define _TFC_THREAD_DEADLOCK 0xA0000001
#define _TFC_MEMORY_ERROR    0xA0000002

#define EXCEPTION_FUNCTION static void ThreadLocalExceptionFunction(unsigned int u, EXCEPTION_POINTERS* pExp){\
	TFCException *excp = new TFCException;\
	excp->SetException(pExp);\
	throw excp;\
}

#define SET_EXCEPTION_HANDLER _set_se_translator( ThreadLocalExceptionFunction );

class TFCException  
{
public:
	TFCException();
	virtual ~TFCException();

	void SetException(LPEXCEPTION_POINTERS new_excp);	
	void SetTFCException(DWORD ExceptionID, LPVOID address);

	LPEXCEPTION_POINTERS GetException();

private:
	LPEXCEPTION_POINTERS excp;

};

#endif // !defined(AFX_TFCEXCEPTION_H__E5BFC953_31DF_11D1_BD35_00E029058623__INCLUDED_)
