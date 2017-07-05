// TFCException.cpp: implementation of the TFCException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "TFCException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


TFCException::TFCException()
{
	excp = NULL;
}

TFCException::~TFCException()
{
	if(excp) delete excp;
}

void TFCException::SetException(LPEXCEPTION_POINTERS new_excp){
	excp = new EXCEPTION_POINTERS;
	memcpy(excp, new_excp, sizeof(_EXCEPTION_POINTERS));
}

LPEXCEPTION_POINTERS TFCException::GetException(){
	return excp;
}

void TFCException::SetTFCException(DWORD ExceptionID, LPVOID address){
	excp = new EXCEPTION_POINTERS;

	ZeroMemory(excp, sizeof(EXCEPTION_POINTERS));

	excp->ExceptionRecord = new EXCEPTION_RECORD;
	
	excp->ExceptionRecord->ExceptionCode = ExceptionID;
	excp->ExceptionRecord->ExceptionFlags = 0;
	excp->ExceptionRecord->ExceptionRecord = NULL;
	excp->ExceptionRecord->ExceptionAddress = address;
	excp->ExceptionRecord->NumberParameters = 0;	
}