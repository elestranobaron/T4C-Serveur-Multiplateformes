/////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TFC Server.h"
#include "TFC_MAIN.h"
//#include "TFCServerContext.h"
//#include "TFC Messages\ReportError.h"
#include "ExpFltr.h"
#include <process.h>
//#include <smrtheap.hpp>
#include "TFCServerGP.h"
#include "RegKeyHandler.h"
#include "ODBCTrace.h"
#include "ThreadMonitor.h"

extern TFC_MAIN *TFCServer;
//extern LPPLAYERMSG_CONTEXT lpMsgContext;
//extern CWinThread **PlayerMessageThreadPool;
extern CTFCServerApp theApp;
extern LPTOP_LEVEL_EXCEPTION_FILTER lpDefaultExceptionFunc;
extern ODBCTrace *ODBCHarness;

#define MAX_QUEUE 5

#define GP_MSG		GPmsg.Format
#define WRITE_GP	GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());

#define _EXITLOG { CString fileName( theApp.sPaths.csLogPath ); fileName += "exit.txt";\
FILE *__f = fopen( fileName, "ab" ); if(__f){fprintf( __f, 
#define EXITLOG_ );fclose(__f);}};

typedef struct _GP{
    TFCException  *e;
    CString        csThreadNameID;
} GP, *LPGP;

void AsyncReportGP( LPVOID lpData );

#define TIMEOUT 300000

void AutoDestroy( LPVOID lpData ){
	CAutoThreadMonitor tmMonitor("AutoDestroy");
    _EXITLOG "\r\nEntering AutoDestroy thread." EXITLOG_
    try{
        // Wait for a maximum of 5 minutes.
        Sleep( TIMEOUT );
                    MessageBeep( -1 );
        _EXITLOG "\r\nExiting from AutoDestroy" EXITLOG_
        exit( SERVER_GP_TIMEOUT_KILL );
    }catch(...){
        _EXITLOG "\r\nException, TerminateProcess from AutoDestroy" EXITLOG_
        TerminateProcess( GetCurrentProcess(), TERMINATE_AUTODESTROY );
    }
}

BOOL LockGP( BOOL boTry ){
    try{
        static CLock cGPlock;
        if( boTry ){
            //DebugLockManager::Instance().Stop();
            return cGPlock.PickLock();                    
        }else{            
            cGPlock.Lock();
        }
    }catch(...){
        //MessageBox( NULL, "oups error in cGPlock.Lock()!", "...", MB_OK );
        try{
        //    exit( -1 );
        }catch(...){
        //    TerminateProcess( GetCurrentProcess(), -1 );
        }
    }
    return FALSE;
}


//////////////////////////////////////////////////////////////////////////////////////////
void ExceptionFunction
//////////////////////////////////////////////////////////////////////////////////////////
// Exception creation function.
// 
(
 unsigned int u, // dunno
 EXCEPTION_POINTERS* pExp // the exception pointers.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	TFCException *excp = new TFCException;
	excp->SetException(pExp);
	throw excp;
}
//////////////////////////////////////////////////////////////////////////////////////////
void ReportGP
//////////////////////////////////////////////////////////////////////////////////////////
// Reports a GP. This function spawns a thread which will write the GP. If the GP
// crashes or its thread deadlocks, the thread will terminate the server.
// 
(
 TFCException *e,       // The exception pointer for the exception to report.
 CString csThreadNameID // The name of the thread to show.
)
//////////////////////////////////////////////////////////////////////////////////////////
{  
    try{
    GP gp;
    gp.e = e;
    gp.csThreadNameID = csThreadNameID;


#ifdef _MONT4C
	DWORD cbWritten;
	WriteFile(theApp.hPipeMain,"#Stop ",6,&cbWritten,NULL); 
#endif //_MONT4C    

    
    _EXITLOG "\r\nStarting GP thread." EXITLOG_
    
    // Starts the GP logging function
    HANDLE hThread = (HANDLE)_beginthread( AsyncReportGP, 0, &gp );

    _EXITLOG "\r\nStarting AutoDestroy thread." EXITLOG_

    // Starts an auto-destruction function which will kill the server after 2 minutes.
    HANDLE hAutoDestroy = (HANDLE)_beginthread( AutoDestroy, 0, 0 );

    _EXITLOG "\r\nWaiting for GP thread to stop." EXITLOG_
    // Wait 2 minutes for completion of GP.
    WaitForSingleObject( hThread, TIMEOUT );

    _EXITLOG "\r\nTerminating AutoDestroyThread." EXITLOG_
    // Terminate the auto-destruction thread now that the GP is complete.
    TerminateThread( hAutoDestroy, 0 );
    }catch(...){
        try{
            _EXITLOG "\r\nExiting from ReportGP." EXITLOG_
            exit( REPORTGP_SPAWNING_THREAD_END );
        }catch(...){
            _EXITLOG "\r\nException, TerminateProcess from ReportGP." EXITLOG_
            TerminateProcess( GetCurrentProcess(), TERMINATE_SPAWNING_THREAD );
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void AsyncReportGP
//////////////////////////////////////////////////////////////////////////////////////////
// Thread which reports an error.
// 
(
 LPVOID lpData // The exception pointer.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	CAutoThreadMonitor tmMonitor("Async Report GP");

    // Reset default exception filter to avoid conflicting with current GP report.
    //SetUnhandledExceptionFilter( lpDefaultExceptionFunc );
    
    //SETUP_GP

#ifdef _MONT4C
	DWORD cbWritten;
	WriteFile(theApp.hPipeMain,"#Stop ",6,&cbWritten,NULL); 
#endif //_MONT4C    


    _EXITLOG "\r\nEntering GP Report Thread." EXITLOG_

    try{
    static BOOL boInGP = FALSE;
    if( boInGP ){
        _EXITLOG "\r\nAlready writing a GP file, blocking." EXITLOG_
        Sleep( TIMEOUT );
        return;
    }
    boInGP = TRUE;

    LPGP lpGP = (LPGP)lpData;    
    
    TFCException *e = lpGP->e;
    CString csThreadNameID = lpGP->csThreadNameID;
    EXCEPTION_POINTERS *Excp = e->GetException();

//	int i, j;
	
    // Stop smartheap background checking.
#ifdef MEM_DEBUG    
    TRACE( "\r\nDisabling smartheap background checking." );
    MemSetErrorHandler( NULL );
    dbgMemScheduleChecking( FALSE, 0, 0 );
    TRACE( "-Disabling smartheap background checking." );
#endif

    CString GPpath;
	SYSTEM_INFO s_siSystem;
	GetSystemInfo(&s_siSystem);

	try{
	

    CFile GPFile;	
    GPpath = theApp.sPaths.csLogPath;
	GPpath += _T("T4CServerGP.out");
	if(!GPFile.Open((LPCTSTR)(GPpath), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate)){
		if(!GPFile.Open(_T("\\T4CServerGP.out"), CFile::modeCreate | CFile::modeWrite)){
//			LPCTSTR param[1] = {_T("and could not create a GP file! Please check for disk access priorities or disk space!!")};
//			ReportError Err(__FATAL_UNCAUGHT_EXCEPTION, 1, param);
//			exit(0);				
		}else{
//			LPCTSTR param[1] = {_T("and created a GP file in \\T4CServerGP.out")};
//			ReportError Err(__FATAL_UNCAUGHT_EXCEPTION, 1, param);
		}
	}else{
		CString msg;
		msg = _T("and created a GP file in ");
        msg += TFCMAIN::GetHomeDir();
		msg += _T("T4CServerGP.out");
//		LPCTSTR param[1] = {(LPCTSTR)msg};
//		ReportError Err(__FATAL_UNCAUGHT_EXCEPTION, 1, param);
	}

	GPFile.Seek(0, CFile::end);
	CString GPmsg;
	
	GPmsg = _T("\r\n================================================================================\r\n");
	GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
	
	
	{		
		time_t current_time;
		time(&current_time);
		CString version;			
		version.Format( "0.%ub", TFCServer->dwVersion );
		GPmsg.Format(_T("T4C Server v%s - Build l - ServerGP. General Protection fault report, %s \r\n\r\n"), (LPCTSTR)version, ctime(&current_time));
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
	}
	
	
	TRACE(_T("[Uncaught exception in %s]\r\n\r\n"), csThreadNameID );
	GPmsg.Format(_T("[Uncaught exception in %s]\r\n\r\n"), csThreadNameID );
	GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());

	
	
	switch(Excp->ExceptionRecord->ExceptionCode){
	case EXCEPTION_ACCESS_VIOLATION: 
		TRACE(_T("The thread tried to read from or write to a virtual address for which it does not have the appropriate access."));		
		GPmsg = _T("EXCEPTION_ACCESS_VIOLATION: The thread tried to read from or write to a virtual address for which it does not have the appropriate access.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// The thread tried to read from or write to a virtual address for which it does not have the appropriate access. 
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: 
		TRACE(_T("The thread tried to access an array element that is out of bounds and the underlying hardware supports bounds checking."));
		GPmsg = _T("EXCEPTION_ARRAY_BOUNDS_EXCEEDED: The thread tried to access an array element that is out of bounds and the underlying hardware supports bounds checking.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// The thread tried to access an array element that is out of bounds and the underlying hardware supports bounds checking. 
	case EXCEPTION_BREAKPOINT: 
		TRACE(_T("A breakpoint was encountered."));
		GPmsg = _T("EXCEPTION_BREAKPOINT: A breakpoint was encountered.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// A breakpoint was encountered. 
	case EXCEPTION_DATATYPE_MISALIGNMENT: 
		TRACE(_T("The thread tried to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries; 32-bit values on 4-byte boundaries, and so on."));
		GPmsg = _T("EXCEPTION_DATATYPE_MISALIGNMENT: The thread tried to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries; 32-bit values on 4-byte boundaries, and so on.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// The thread tried to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries; 32-bit values on 4-byte boundaries, and so on. 
	case EXCEPTION_FLT_DENORMAL_OPERAND: 
		TRACE(_T("One of the operands in a floating-point operation is denormal. A denormal value is one that is too small to represent as a standard floating-point value."));
		GPmsg = _T("EXCEPTION_FLT_DENORMAL_OPERAND: One of the operands in a floating-point operation is denormal. A denormal value is one that is too small to represent as a standard floating-point value.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// One of the operands in a floating-point operation is denormal. A denormal value is one that is too small to represent as a standard floating-point value. 
	case EXCEPTION_FLT_DIVIDE_BY_ZERO: 
		TRACE(_T("The thread tried to divide a floating-point value by a floating-point divisor of zero."));
		GPmsg = _T("EXCEPTION_FLT_DIVIDE_BY_ZERO: The thread tried to divide a floating-point value by a floating-point divisor of zero.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;		
		// The thread tried to divide a floating-point value by a floating-point divisor of zero. 
	case EXCEPTION_FLT_INEXACT_RESULT: 
		TRACE(_T("The result of a floating-point operation cannot be represented exactly as a decimal fraction."));
		GPmsg = _T("EXCEPTION_FLT_INEXACT_RESULT: The result of a floating-point operation cannot be represented exactly as a decimal fraction.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// The result of a floating-point operation cannot be represented exactly as a decimal fraction. 
	case EXCEPTION_FLT_INVALID_OPERATION: 
		TRACE(_T("This exception represents any floating-point exception not included in this list."));
		GPmsg = _T("EXCEPTION_FLT_INVALID_OPERATION: This exception represents any floating-point exception not included in this list.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// This exception represents any floating-point exception not included in this list. 
	case EXCEPTION_FLT_OVERFLOW: 
		TRACE(_T("The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type."));
		GPmsg = _T("EXCEPTION_FLT_OVERFLOW: The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type. 
	case EXCEPTION_FLT_STACK_CHECK: 
		TRACE(_T("The stack overflowed or underflowed as the result of a floating-point operation."));
		GPmsg = _T("EXCEPTION_FLT_STACK_CHECK: The stack overflowed or underflowed as the result of a floating-point operation."); 
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// The stack overflowed or underflowed as the result of a floating-point operation. 
	case EXCEPTION_FLT_UNDERFLOW: 
		TRACE(_T("The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type."));
		GPmsg = _T("EXCEPTION_FLT_UNDERFLOW: The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type. 
	case EXCEPTION_ILLEGAL_INSTRUCTION: 
		TRACE(_T("The thread tried to execute an invalid instruction."));
		GPmsg = _T("EXCEPTION_ILLEGAL_INSTRUCTION: The thread tried to execute an invalid instruction.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// The thread tried to execute an invalid instruction. 
	case EXCEPTION_IN_PAGE_ERROR: 
		TRACE(_T("The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network."));
		GPmsg = _T("EXCEPTION_IN_PAGE_ERROR: The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network. 
	case EXCEPTION_INT_DIVIDE_BY_ZERO: 
		TRACE(_T("The thread tried to divide an integer value by an integer divisor of zero."));
		GPmsg = _T("EXCEPTION_INT_DIVIDE_BY_ZERO: The thread tried to divide an integer value by an integer divisor of zero.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// The thread tried to divide an integer value by an integer divisor of zero. 
	case EXCEPTION_INT_OVERFLOW: 
		TRACE(_T("The result of an integer operation caused a carry out of the most significant bit of the result."));
		GPmsg = _T("EXCEPTION_INT_OVERFLOW: The result of an integer operation caused a carry out of the most significant bit of the result.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// The result of an integer operation caused a carry out of the most significant bit of the result. 
	case EXCEPTION_INVALID_DISPOSITION: 
		TRACE(_T("An exception handler returned an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception."));
		GPmsg = _T("EXCEPTION_INVALID_DISPOSITION: An exception handler returned an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// An exception handler returned an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception. 
	case EXCEPTION_NONCONTINUABLE_EXCEPTION: 
		TRACE(_T("The thread tried to continue execution after a noncontinuable exception occurred."));
		GPmsg = _T("EXCEPTION_NONCONTINUABLE_EXCEPTION: The thread tried to continue execution after a noncontinuable exception occurred.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// The thread tried to continue execution after a noncontinuable exception occurred. 
	case EXCEPTION_PRIV_INSTRUCTION: 
		TRACE(_T("The thread tried to execute an instruction whose operation is not allowed in the current machine mode."));
		GPmsg = _T("EXCEPTION_PRIV_INSTRUCTION: The thread tried to execute an instruction whose operation is not allowed in the current machine mode.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// The thread tried to execute an instruction whose operation is not allowed in the current machine mode. 
	case EXCEPTION_SINGLE_STEP: 
		TRACE(_T("A trace trap or other single-instruction mechanism signaled that one instruction has been executed."));
		GPmsg = _T("EXCEPTION_SINGLE_STEP: A trace trap or other single-instruction mechanism signaled that one instruction has been executed.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
		// A trace trap or other single-instruction mechanism signaled that one instruction has been executed. 
	case EXCEPTION_STACK_OVERFLOW: 
		TRACE(_T("The thread used up its stack."));
		GPmsg = _T("EXCEPTION_STACK_OVERFLOW: The thread used up its stack.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;

	case _TFC_THREAD_DEADLOCK:
		TRACE(_T("DEADLOCK: The thread has gone into a deadlock."));
		GPmsg = _T("_T4C_THREAD_DEADLOCK: T4C Server has detected that the thread has deadlocked.");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		break;
    case _TFC_MEMORY_ERROR:
        GPmsg = _T("_T4C_MEMORY_ERROR: T4C Server has detected a memory error." );
        GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
        break;
	default:
		GPmsg.Format( _T("UNKOWN EXCEPTION: An unknown exception 0x%x was thrown."), Excp->ExceptionRecord->ExceptionCode );
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
	}
	
	TRACE(_T("\r\n\r\nOccured at address 0x%x\r\n\r\n"), Excp->ExceptionRecord->ExceptionAddress);		

	GPmsg.Format(_T("\r\n\r\nOccured at address 0x%x\r\n\r\n"), Excp->ExceptionRecord->ExceptionAddress);
	GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());


    // Call the registered functions so they can append their information to the GP.
    
    /*	
	try{

		switch(c->WhichThread()){
		//////////////////////////////////////////////////////////////////////////////////////////		
		case __PLAYER_MESSAGES_THREAD:
			GP_MSG( "Happened in player messages handling." );
			WRITE_GP;
		break;
		//////////////////////////////////////////////////////////////////////////////////////////
		case __FETCH_THREAD:
			GP_MSG( "Fetch thread error: " );
			WRITE_GP;
            break;
		case __PLAYER_MAINTENANCE_THREAD: {
			if(cplayer) {
				if(cplayer->registred){
					GPmsg.Format(_T("Happened while handling player %s "), cplayer->GetAccount());
					GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
					try{
						if(cunit){
							GPmsg.Format(_T("logged on character %s.\r\n"), cunit->GetName());
							GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());					
							GPmsg.Format(_T("%s's character:\r\n"), cunit->GetName());
							GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
							GPmsg.Format(_T("  position: (%u, %u world %u)\r\n"), cunit->GetWL().X, cunit->GetWL().Y, cunit->GetWL().world);
							GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());							
	// ADD Player dump						
					
						
						}else{
							GPmsg.Format(_T("outside of game.\r\n"));
							GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
						}
					}catch(TFCException *e){ delete e; }
				}else{
					GPmsg.Format(_T("Happened while handling unregistred player coming from %s port %u\r\n"), 
						cplayer->GetIP(), cplayer->GetPort());
					GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
				}

				GPmsg.Format(_T("\r\nContent of last message(s):\r\n"));
				GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());

			}else{
				GPmsg.Format(_T("Happened outside player handling\r\n"));
				GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
			}
		}break;
		//////////////////////////////////////////////////////////////////////////////////////////
		case __TFC_MAIN_THREAD: {
			int queue = 0;
			CString indent = _T("  ");
			CString tmpstr;

			if(cunit){
				GPmsg.Format(_T("Happened while handling unit ID#%u (%s)\r\n"), cunit->GetID(), cunit->GetName());
				GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());

				while(cunit){
					tmpstr.Format(_T("\"%s\":\r\n"), cunit->GetName());
					GPmsg = indent;
					GPmsg += tmpstr;
					GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
			
					indent += _T("  ");
					tmpstr.Format(_T("position: (%u, %u world %u)\r\n"), cunit->GetWL().X, cunit->GetWL().Y, cunit->GetWL().world);
					GPmsg = indent;
					GPmsg += tmpstr;
					GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
					
					switch(cunit->IsDoing()){
					case wandering:	{
									tmpstr.Format(_T("Unit was wandering.\r\n")); 
									GPmsg = indent;
									GPmsg += tmpstr;
									GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
									cunit = NULL;
						}break;
					case fighting:	{
									cunit = cunit->GetTarget();
									if(cunit){
										tmpstr.Format(_T("Unit was fighting unit ID#%u (%s)\r\n"), cunit->GetID(), cunit->GetName());
										GPmsg = indent;
										GPmsg += tmpstr;
										GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
										indent += "  ";										
										if(queue > MAX_QUEUE) 
											cunit = NULL;
																		
										queue++;
									}else{
										tmpstr.Format(_T("Unit was fighting nothing!\r\n"), cunit->GetID(), cunit->GetName());
										GPmsg = indent;
										GPmsg += tmpstr;
										GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
									}
							}break;
					case talking:  {
									cunit = cunit->GetTarget();
									if(cunit){
										tmpstr.Format(_T("Unit was talking to unit ID#%u (%s)\r\n"), cunit->GetID(), cunit->GetName());
										GPmsg = indent;
										GPmsg += tmpstr;
										GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
										indent += _T("  ");
										if(queue > MAX_QUEUE) 
											cunit = NULL;
									}else{
										tmpstr.Format(_T("Unit was talking to nothing!\r\n"), cunit->GetID(), cunit->GetName());
										GPmsg = indent;
										GPmsg += tmpstr;
										GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
									}
							}break;
					default: {
							tmpstr.Format(_T("Unit had an unknown behavior '%u' "), cunit->IsDoing());
							GPmsg = indent;
							GPmsg += tmpstr;
							GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
							cunit = cunit->GetTarget();
							if(cunit){
								tmpstr.Format(_T("and was targetting unit ID#%u (%s)\r\n"), cunit->GetID(), cunit->GetName());
								GPmsg = indent;
								GPmsg += tmpstr;
								GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
							}else{
								tmpstr.Format(_T("and wasn't targetting anything.\r\n"));
								GPmsg = indent;
								GPmsg += tmpstr;
								GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
							}
							queue++;
						}
					}
				}
			}else{
				GPmsg.Format(_T("Happened outside unit handling.\r\n"));
				GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
			}
		} break;
		}
		
	}catch(...){
		GPmsg.Format(_T("[Error while querying information of about current context]\r\n"));
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		delete e;
	}
*/
	try{
		//////////////////////////////////////////////////////////////////////////////////////////
		// Content of messages threads.
	/*	GP_MSG( "\r\n[Current content of messages threads]\r\n\r\n" );
		WRITE_GP;
		
		for( i = 0; i < (int)MESSAGES_THREADS; i++ ){
			GP_MSG( "Message thread #%u", i );
			WRITE_GP;

			if( lpMsgContext[ i ].lpPlayer != NULL ){
				Players *lpPl = lpMsgContext[ i ].lpPlayer;
				GP_MSG( "\r\n   Handling user %s IP %s port %u.", (LPCTSTR)lpPl->GetAccount(),
					(LPCTSTR)lpPl->GetIP(), lpPl->GetPort() );
				WRITE_GP
				if( lpMsgContext[ i ].lpPlayer->in_game ){
					GP_MSG( "\r\n      User was currently playing character %s.", lpPl->self->GetName() );
					WRITE_GP
				}
			}else{
				GP_MSG( "\r\n   Outside player message handling (waiting for message)" );
				WRITE_GP
			}
			if( lpMsgContext[ i ].dwMessageID != 0 ){
				GP_MSG( "\r\n   Server was interpreting message ID %u", lpMsgContext[ i ].dwMessageID );
				WRITE_GP;
			}else{
				GP_MSG( "\r\n   Server wasn't yet interpreting message from player." );
				WRITE_GP;
				if( lpMsgContext[ i ].lpRawPacket != NULL ){
					GP_MSG( "\r\n   Content of raw packet received by server: " );
					WRITE_GP;
										
					try{						
						CString csTempStr;
						GPmsg = "   [ ";
						for( j = 0; j < (int)lpMsgContext[ i ].dwRawPacketSize; j++ ){
							csTempStr.Format( "%u ", lpMsgContext[ i ].lpRawPacket[ j ] );
							GPmsg += csTempStr;
						}

						GPmsg += "]";
						WRITE_GP;
					}catch(...){
						GP_MSG( "* CAUGHT ERROR IN PACKET *" );
						WRITE_GP;
					}
				}
			}
			TemplateList<TFCPacket> *lptlList = lpMsgContext[ i ].lptlPacketList;
			TFCPacket *lpPacket;

			if( lptlList != NULL ){
				GP_MSG( "\r\n   List of packets received by the server." );
				WRITE_GP

				j = 0;
				lptlList->ToHead();
				while( lptlList->QueryNext() ){
					lpPacket = lptlList->Object();

					GP_MSG( "\r\n      Packet %u: [ ", j );
					WRITE_GP

					lpPacket->Seek( 0, 0 );

					try{
                        CString csPacket = lpPacket->GetDebugPacketString();
    					GP_MSG( "%s ", (LPCTSTR)csPacket );
						WRITE_GP
					}catch( TFCPacketException *e ){
						delete e;
						GP_MSG( " *CAUGHT ERROR IN PACKET* " );
						WRITE_GP
					}

					GP_MSG( "]" );
					WRITE_GP
					j++;
				}					
			}

			GP_MSG( "\r\n\r\n" );
			WRITE_GP
		}*/


	}catch( ... ){
		GP_MSG( "[Error while querying information about currently handled player messages]" );
		WRITE_GP;
	}
	
	TRACE(_T("[End exception trace]\r\n"));

	{
		CThreadMonitor::ThreadList listOfThreads;
		CThreadMonitor::GetInstance().GetRunningThreadsList(listOfThreads);
		CThreadMonitor::ThreadListIterator i = listOfThreads.begin();
		GP_MSG("\r\nListing %u active Threads:\r\n", listOfThreads.size());
		WRITE_GP;
		for (; i != listOfThreads.end(); ++i) {
			GP_MSG("Thread ID: %u Name: %s\r\n", (*i).first, (*i).second.c_str());
			WRITE_GP;
		}
		GP_MSG("\r\n"); WRITE_GP;
	}



	// End of specific information
    GPmsg = _T("\r\n[End of T4C Server specific debug information]\r\n-----\r\n");
	GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
    GPmsg = _T("\r\n[Start writing ODBCTrace specific information]\r\n-----\r\n");
	GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());

	//Trace
	{
		//Get vectors
		csVectorRequest csVector;
		loVectorDuration loVector;
		ODBCHarness->Lock();
		csVector = ODBCHarness->getVectorRequest();
		loVector = ODBCHarness->getVectorDuration();
		ODBCHarness->Unlock();
		//Write csVector
		csVectorRequest::iterator i;
		for( i = csVector.begin(); i != csVector.end(); i++ ){
			GPFile.Write( (*i), (*i).GetLength() );        
		}
		csVector.clear();
		//Compute the mean values and get the two last values
		unsigned long bigMean=0, smallMean=0, lastValue=0, lastLastValue=0;
		loVectorDuration::iterator j;
		for( j = loVector.begin(); j != loVector.end(); j++ ){
			bigMean += (*j);
		}
		bigMean = bigMean / VECTOR_SIZE;
		//bigMean = bigMean/VECTOR_SIZE > 100000 ? 0 : bigMean/VECTOR_SIZE;//If pb with little values
		for( j = (loVector.end())-10; j != loVector.end(); j++ ){
			smallMean += (*j);
		}
		smallMean = smallMean/10;
		lastValue = *(loVector.end()-1);
		lastLastValue = *((loVector.end()) - 2);
		loVector.clear();
		//Write the values in the GPFile
		GPmsg = _T("\r\n[average of the ODBC request duration]\r\n-----\r\n");
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		GPmsg.Format(_T("\r\n[average of the %u last values = %u ms]"),VECTOR_SIZE,bigMean);
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		GPmsg.Format(_T("\r\n[average of the %u last values = %u ms]"),10,smallMean);
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());

		GPmsg.Format(_T("\r\n[the last duration takes %u ms]"),lastValue);
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
		GPmsg.Format(_T("\r\n[lastlast duration takes %u ms]"),lastLastValue);
		GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
	}
	//Trace

	// Close the GP file
    GPmsg = _T("\r\n[End of ODBCTrace specific debug information]\r\n-----\r\n");
	GPFile.Write((LPCTSTR)GPmsg, GPmsg.GetLength());
	GPFile.Close();

	// Catches anything and lets it go.
	}catch(...){		
	}

    _EXITLOG "\r\nWriting GP data." EXITLOG_

    try{            
        // Report extensive debug information.
        CExpFltr::SetReportFile( (char *)(LPCTSTR)GPpath );
        CExpFltr::Filter(Excp);
        
    }catch(...){        
    }   
    }catch(...){        
    }    

    _EXITLOG "\r\nWriting crash info in registry." EXITLOG_

    try{        
        RegKeyHandler regKey;

        regKey.Open( HKEY_LOCAL_MACHINE, "Software\\Vircom\\The 4th Coming Server\\GeneralConfig" );
        regKey.WriteProfileInt( "T4C_CRASH", 1 );

        regKey.Close();

        _EXITLOG "\r\nExiting from AsyncReportGP." EXITLOG_

        exit( SERVERGP_EXIT );
    }catch(...){

        _EXITLOG "\r\nException, TerminateProcess from AsyncReportGP." EXITLOG_

        TerminateProcess( GetCurrentProcess(), TERMINATE_SERVERGP );
    }
}