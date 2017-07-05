//	Filename: ODBCMage.c
//	Author	: Guy Carbonneau
//	Date	: 03.04.1998
//
//  Core of the class ODBC Mage.
////////////////////////////////
//  Secondary author : Francois Leblanc
//  Date : 21.04.1998
//
//  Modification to ODBC Mage class, 
//  Added functionnalities to fetch and set row data.
//  Added batch thread request functionnalities.


//  must include when working with MFC
#include "stdafx.h"
#include "TFC Server.h"
#include "ODBCMage.h"
#include "TFCServerGP.h"
#include <process.h>
#include "DeadlockDetector.h"
#include "RegKeyHandler.h"
#include "DebugLogger.h"
#include "format.h"
// BEGIN : Mestoph -> Remove Vircom Mail
//#include "EasyMail.h"
// END : Mestoph -> Remove Vircom Mail
#include "Shutdown.h"
#include <string>
#include "ODBCTrace.h"
#include "ThreadMonitor.h"



#define TRANSACT_SQL
#define CURSOR_SQL SQL_CUR_USE_ODBC
//#define CURSOR_SQL SQL_CUR_USE_IF_NEEDED
//#define CURSOR_SQL SQL_CUR_USE_DRIVER

extern CTFCServerApp theApp;
extern ODBCTrace *ODBCHarness;

void cODBCMage::CheckDisconnectError( void ){
    BYTE  lpbSQLState[ 6 ] = {0};
    BYTE lpbErrorMsg[ 200 ];
    long  dwNativeError;
    short wDummy = 0;

    SQLError( henv, hdbc, hstmt, lpbSQLState, &dwNativeError, lpbErrorMsg, 200, &wDummy );        
    
    if( stricmp( (const char *)lpbSQLState, "08S01" ) == 0 || 
        stricmp( (const char *)lpbSQLState, "08001" ) == 0 ||
        stricmp( (const char *)lpbSQLState, "08003" ) == 0 ||
        stricmp( (const char *)lpbSQLState, "08004" ) == 0 ){

        static bool shutdown = false;

        if( !shutdown ){
            shutdown = true;
            // Add the shutdown key to make sure the process won't start
            // until 5 minutes.
            RegKeyHandler regKey;
            regKey.Open( HKEY_LOCAL_MACHINE, "SOFTWARE\\Vircom\\The 4th Coming Server" );
            regKey.WriteProfileInt( "SHUTDOWN", 1 );
            regKey.Close();

            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "T4C was shutdown because the ODBC connection is down."
            LOG_

			/* BEGIN : Mestoph -> Remove Vircom Mail
	        CString sender( "tech@the4thcoming.com" );
            CString subject( "[T4C CRASH][SQL CONNECTION ERROR]" );
			END : Mestoph -> Remove Vircom Mail */
            CString body;

            body.Format(
				/* BEGIN : Mestoph -> Remove Vircom Mail
                "<This is an automated message from T4C Server of %s>"
                "\r\nYou can reply directly to this message if you need support about this item."
                "\r\n"
                "\r\nT4C was unable to establish a connection with the character database." */
                "T4C was unable to establish a connection with the character database."
				// END : Mestoph -> Remove Vircom Mail
                "\r\nThe server cannot run without a character database and has therefore"
                "\r\nbeen shutdown for a minimum period of 5 minutes."
                "\r\n"
                "\r\nPlease verify your setup and correct the situation as soon as possible."
                "\r\n"
                "\r\nSQL Error:"
                "\r\nSQL State     = %s"
                "\r\nNative error  = %u"
                "\r\nError Message = %s",
                theApp.sContact.csCompanyName,
                lpbSQLState,
                dwNativeError,
                lpbErrorMsg
            );

            /* BEGIN : Mestoph -> Remove Vircom Mail
			_LOG_DEBUG
                LOG_CRIT_ERRORS,
                "Copy of email sent to %s:",
                (LPCTSTR)theApp.sContact.csAdminEmail            
            LOG_
			END : Mestoph -> Remove Vircom Mail */
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                (LPCTSTR)body
            LOG_

            /*EasyMail()(
                "smtp.vircom.com",
                sender,
                theApp.sContact.csAdminEmail,
                subject,
                body,
                NULL,
                "crashreports@the4thcoming.com",
                "p0rt1cule"
            );*/

            MessageBeep( -1 );

            CShutdown::CreateShutdown( SHUTDOWN_NOW, true, /*true,*/ true );
            CShutdown::StartShutdown();
        }
    }
};


CLock cODBCMage::cStaticLock;
bool  cODBCMage::boSerialize = true;
cODBCMage::StaticInit cODBCMage::m_StaticInit;

cODBCMage::StaticInit::StaticInit( void ){       
    RegKeyHandler regKey;

    regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY GEN_CFG_KEY );

    if( regKey.GetProfileInt( "SerializeODBC", 1 ) != 0 ){
        boSerialize = true;
    }else{
        boSerialize = false;
    }
}

cODBCMage::cODBCMage()
{
	Create();
	ZeroMemory( lpszCurrentDSN, 20 );
	ZeroMemory( lpszCurrentUser, 20 );
	ZeroMemory( lpszCurrentPWD, 20 );

    boShutdown = FALSE;
    boStmtAlloc = false;

	hThreadID = NULL;
	hIoCompletionPort = NULL;
}


cODBCMage::~cODBCMage()
{
	Destroy();
}

//////////////////////////////////////////////////////////////////////////////////////////
void cODBCMage::Lock
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    /*TFormat format;
    DebugLogger::GetInstance().LogString(
        format(
            "Trying locking ODBC at %s(%u). (0x%x Thread %u)",
            lpszFileName,
            nLineNumber,
            &cStaticLock,
            GetCurrentThreadId()
        )
    );*/

    //if( boSerialize ){ cStaticLock.Lock();   }else{ cNonStaticLock.Lock();   }
    cStaticLock.Lock();

    /*DebugLogger::GetInstance().LogString(
        format(
            "Locked ODBC at %s(%u). (0x%x Thread %u)",
            lpszFileName,
            nLineNumber,
            &cStaticLock,
            GetCurrentThreadId()
        )
    );*/
}
//////////////////////////////////////////////////////////////////////////////////////////
void cODBCMage::Unlock
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    /*TFormat format;
    DebugLogger::GetInstance().LogString(
        format(
            "Unlocked ODBC at %s(%u). (0x%x Thread %u)",
            lpszFileName,
            nLineNumber,
            &cStaticLock,
            GetCurrentThreadId()
        )
    );
    
    //if( boSerialize ){ cStaticLock.Unlock(); }else{ cNonStaticLock.Unlock(); }*/
    cStaticLock.Unlock();
}

void cODBCMage::Create()
{
	SQLAllocEnv(&henv);
	SQLAllocConnect(henv, &hdbc);
	//InitializeCriticalSection( &csThreadLock );
}

void cODBCMage::Destroy()
{
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);
	//DeleteCriticalSection( &csThreadLock );
}

void cODBCMage::Connect(LPCSTR szDataSource, LPCSTR szUsername, LPCSTR szPassword)
{
	TRACE( "\r\nTrying to connect to DSN %s", szDataSource );
	TRACE( "\r\nTrying to connect to DSN %s", lpszCurrentDSN );

	Lock();	
	
    SQLSetConnectOption( hdbc, SQL_ODBC_CURSORS, SQL_CUR_USE_ODBC );
    
    // Updates the stored data source name and the current user names.
    if( szDataSource != NULL ){
        strcpy( lpszCurrentDSN, szDataSource );
    }else{
        strcpy( lpszCurrentDSN, "DEFAULT" );
    }
	
	TRACE( "\r\nTrying to connect to DSN %s", lpszCurrentDSN );
	TRACE( "\r\nTrying to connect to DSN %s", szDataSource );

	if( szUsername != NULL ){
		strcpy( lpszCurrentUser, szUsername );
	}else{
		lpszCurrentUser[ 0 ] = 0;
	}
	if( szPassword != NULL ){
		strcpy( lpszCurrentPWD, szPassword );
	}else{
		lpszCurrentPWD[ 0 ] = 0;
	}
	
	
    SQLRETURN nRet = SQLConnect(hdbc, (unsigned char *)szDataSource, SQL_NTS, (unsigned char *)szUsername, SQL_NTS, (unsigned char *)szPassword, SQL_NTS);
    if( nRet == SQL_SUCCESS_WITH_INFO || nRet == SQL_ERROR || nRet == SQL_INVALID_HANDLE ){

        // Verify that the connection could be accessed.
        CheckDisconnectError();

		BYTE lpbSQLState[ 200 ];		
		BYTE lpbErrorMsg[ 200 ];
		long  dwNativeError;
		short wDummy;

		SQLError( henv, hdbc, hstmt, lpbSQLState, &dwNativeError, lpbErrorMsg, 200, &wDummy );
		if( nRet ==  SQL_ERROR || nRet == SQL_INVALID_HANDLE ){
			_LOG_DEBUG
				LOG_DEBUG_LVL3,
				"SQL ERROR [SQLConnect]:"
			LOG_
			_LOG_DEBUG
				LOG_DEBUG_LVL3,
				"SQL State: %s", 
				lpbSQLState
			LOG_
			_LOG_DEBUG
				LOG_DEBUG_LVL3,
				"Native Error: %u", 
				dwNativeError
			LOG_
			_LOG_DEBUG
				LOG_DEBUG_LVL3,
				"Error message: %s", 
				lpbErrorMsg
			LOG_
		}
		if( nRet ==  SQL_SUCCESS_WITH_INFO ){
			_LOG_DEBUG
				LOG_DEBUG_LVL3,
				"SQL SUCCESS WITH INFO [SQLConnect]:"
			LOG_
			_LOG_DEBUG
				LOG_DEBUG_LVL3,
				"SQL State: %s", 
				lpbSQLState
			LOG_
			_LOG_DEBUG
				LOG_DEBUG_LVL3,
				"Native Info: %u", 
				dwNativeError
			LOG_
			_LOG_DEBUG
				LOG_DEBUG_LVL3,
				"Info message: %s", 
				lpbErrorMsg
			LOG_
		}

        //Disconnect();

        // Destroy and create.
        //Destroy();
        //Create();

        // Try to reconnect, not use checking returned error.
        //SQLSetConnectOption( hdbc, SQL_ODBC_CURSORS, SQL_CUR_USE_ODBC );
        //SQLConnect(hdbc, (unsigned char *)szDataSource, SQL_NTS, (unsigned char *)szUsername, SQL_NTS, (unsigned char *)szPassword, SQL_NTS);
	}
	
    // If statement hasn't already been allocated.
    if( !boStmtAlloc ){
        boStmtAlloc = true;
        // Allocate it.
        SQLAllocStmt(hdbc, &hstmt);
    }

	Unlock();
}
void cODBCMage::AllocStmt()
{
	Lock();
    if( !boStmtAlloc ){
        SQLAllocStmt(hdbc, &hstmt);
	    boStmtAlloc = true;
    }
	Unlock();
}
void cODBCMage::Disconnect()
{
	Lock();
    if( boStmtAlloc ){
        SQLFreeStmt(hstmt, SQL_DROP);
    }
    boStmtAlloc = false;
	SQLDisconnect(hdbc);
	Unlock();
}

BOOL cODBCMage::ExecuteRequest(LPCSTR szField, LPCSTR szTablename, LPCSTR szWhereStmt)
{
	CHAR szBuffer[1024];

	sprintf(szBuffer, "select %s from %s %s", szField, szTablename, szWhereStmt);

	SQLExecDirect(hstmt, (unsigned char *)szBuffer, SQL_NTS);

	rc = SQLFetch( hstmt );

	if(rc == SQL_SUCCESS){
		return TRUE;
	}
	
	return FALSE;	
}

//////////////////////////////////////////////////////////////////////////////////////////
void cODBCMage::ConnectOption
//////////////////////////////////////////////////////////////////////////////////////////
// Sets a connection option
// 
(
 WORD wConnectOption, // The connection option to change. See SQLSetConnectOption
 DWORD dwConnectValue // Its new value.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	SQLSetConnectOption( hdbc, wConnectOption, dwConnectValue );
}

//////////////////////////////////////////////////////////////////////////////////////////
int cODBCMage::Commit( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Commits pending connection data to database.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	if( SQLTransact( henv, hdbc, SQL_COMMIT ) == SQL_SUCCESS ){
		return TRUE;
	}
	return FALSE;
}


//////////////////////////////////////////////////////////////////////////////////////////
BOOL cODBCMage::Rollback( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Rollsback all pending operations on the current connection.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	if( SQLTransact( henv, hdbc, SQL_ROLLBACK ) == SQL_SUCCESS ){
		return TRUE;
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////////////
BOOL cODBCMage::Fetch( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Fetches the next row in the current recordset.
// 
// Return: BOOL, 
//////////////////////////////////////////////////////////////////////////////////////////
{
	if( SQLFetch( hstmt ) == SQL_SUCCESS ){
		return TRUE;
	}
#ifdef _DEBUG
	else{
		BYTE lpbSQLState[ 200 ];		
		BYTE lpbErrorMsg[ 200 ];
		long  dwNativeError;
		short wDummy;

		SQLError( henv, hdbc, hstmt, lpbSQLState, &dwNativeError, lpbErrorMsg, 200, &wDummy );
		TRACE( "\r\nSQL ERROR [SQLFetch]:" );		
		TRACE( "\r\n\tSQL State: %s", lpbSQLState );
		TRACE( "\r\n\tNative Error: %u", dwNativeError );
		TRACE( "\r\n\tError message: %s", lpbErrorMsg );
	}
#endif

	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////////////
BOOL cODBCMage::Cancel( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Cancels a transactions.
// 
// Return: BOOL, TRUE if it could cancel
//////////////////////////////////////////////////////////////////////////////////////////
{
    //if( SQLCloseCursor( hstmt ) == SQL_SUCCESS ){
    if( SQLCancel( hstmt ) == SQL_SUCCESS ){
		return TRUE;
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL cODBCMage::CloseCursor( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Closes a cursor opened on a statement . BLBL 11/12/2010
// 
// Return: BOOL, TRUE if it could cancel
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( SQLCloseCursor( hstmt ) == SQL_SUCCESS ){
		return TRUE;
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL cODBCMage::SendRequest
//////////////////////////////////////////////////////////////////////////////////////////
// Sends a complete request to the currently connected ODBC driver.
// 
(
 LPCTSTR lpszRequest, // The request to send.
 bool    boKnownError // True if the request can knowingly generate an error.
)
// Return: BOOL, TRUE if the function succeeded.
//////////////////////////////////////////////////////////////////////////////////////////
{

	rc = SQLExecDirect(hstmt, (LPBYTE)lpszRequest, SQL_NTS);

    if(rc == SQL_SUCCESS){
		return TRUE;
	}else if (rc == SQL_SUCCESS_WITH_INFO) {

		// Okay, it worked, no need to shutdown server...
		// but we should take some notes to logs, so that we know SQL Server is complaining at us.
		BYTE  lpbSQLState[ 6 ] = {0};
		BYTE lpbErrorMsg[ 200 ];
		long  dwNativeError;
		short wDummy = 0;

		SQLError( henv, hdbc, hstmt, lpbSQLState, &dwNativeError, lpbErrorMsg, 200, &wDummy );

		_LOG_DEBUG
			LOG_DEBUG_LVL1,
			"SQL SQL_SUCCESS_WITH_INFO [SQLExecDirect]:"
		LOG_
		_LOG_DEBUG
			LOG_DEBUG_LVL2,
			"Original SQL query statement: [ %s ]", 
			lpszRequest
		LOG_
		_LOG_DEBUG
			LOG_DEBUG_LVL2,
			"SQL State: %s", 
			lpbSQLState
		LOG_
		_LOG_DEBUG
			LOG_DEBUG_LVL2,
			"Native Error: %u", 
			dwNativeError
		LOG_
		_LOG_DEBUG
			LOG_DEBUG_LVL2,
			"Error message: %s", 
			lpbErrorMsg
		LOG_

		return TRUE;
	}else{


        // Verify that the connection was not closed.
        CheckDisconnectError();

        // If it is known that the function may return an error, return false immediatly.
        if( boKnownError ){
            return FALSE;
        }

		// else, log the problem and try sending again!
        _LOG_DEBUG
            LOG_WARNING,
            "SQLExecDirect failed, trying to re-send the request."
        LOG_

		rc = SQLExecDirect( hstmt, (LPBYTE)lpszRequest, SQL_NTS );

		if( rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO){
			_LOG_DEBUG
				LOG_WARNING,
				"SQLExecDirect failed, re-sending succeed."
			LOG_
			return TRUE;
        }else{
            BYTE  lpbSQLState[ 6 ] = {0};
            BYTE lpbErrorMsg[ 200 ];
            long  dwNativeError;
            short wDummy = 0;

            SQLError( henv, hdbc, hstmt, lpbSQLState, &dwNativeError, lpbErrorMsg, 200, &wDummy );

            _LOG_DEBUG
                LOG_CRIT_ERRORS, 
                "Unable to complete ODBC query, accounting will fail."                                                
            LOG_

            _LOG_DEBUG
                LOG_DEBUG_LVL2,
                "SQL ERROR [SQLExecDirect]:"
            LOG_
            _LOG_DEBUG
                LOG_DEBUG_LVL2,
                "Original SQL query statement: [ %s ]", 
                lpszRequest
            LOG_
            _LOG_DEBUG
                LOG_DEBUG_LVL2,
                "SQL State: %s", 
                lpbSQLState
            LOG_
            _LOG_DEBUG
                LOG_DEBUG_LVL2,
                "Native Error: %u", 
                dwNativeError
            LOG_
            _LOG_DEBUG
                LOG_DEBUG_LVL2,
			    "Error message: %s", 
                lpbErrorMsg
            LOG_
        }
	}
	
	return FALSE;	
}

//////////////////////////////////////////////////////////////////////////////////////////
RETCODE cODBCMage::GetDWORD
//////////////////////////////////////////////////////////////////////////////////////////
// This function fetches a DWORD from the current SQL row.
// 
(
 UWORD		uwCol,		// Column to fetch data from.
 LPDWORD	lpdwFetch	// DWORD pointer to put data in.
)
// Return: RETCODE, the SQL return code of the query
//////////////////////////////////////////////////////////////////////////////////////////
{	
    *lpdwFetch = 0;
    rc = SQLGetData(hstmt, uwCol, SQL_C_ULONG, lpdwFetch, 0, NULL );	

    if( rc != SQL_SUCCESS ){
			BYTE lpbSQLState[ 200 ];		
			BYTE lpbErrorMsg[ 200 ];
			long  dwNativeError;
			short wDummy;

			SQLError( henv, hdbc, hstmt, lpbSQLState, &dwNativeError, lpbErrorMsg, 200, &wDummy );
			TRACE( "\r\nSQL ERROR [SQLGetData]:" );
//			TRACE( "\r\n\tOriginal SQL query statement: [ %s ]", lpszRequest );
			TRACE( "\r\n\tSQL State: %s", lpbSQLState );
			TRACE( "\r\n\tNative Error: %u", dwNativeError );
			TRACE( "\r\n\tError message: %s", lpbErrorMsg );		
    }
 	return rc;
}

//////////////////////////////////////////////////////////////////////////////////////////
RETCODE cODBCMage::GetSDWORD
//////////////////////////////////////////////////////////////////////////////////////////
// This function fetches a DWORD from the current SQL row.
// 
(
 UWORD		uwCol,		// Column to fetch data from.
 long 	    *lpdwFetch	// DWORD pointer to put data in.
)
// Return: RETCODE, the SQL return code of the query
//////////////////////////////////////////////////////////////////////////////////////////
{	
    *lpdwFetch = 0;
    rc = SQLGetData(hstmt, uwCol, SQL_C_SLONG, lpdwFetch, 0, NULL );	

    if( rc != SQL_SUCCESS ){
			BYTE lpbSQLState[ 200 ];		
			BYTE lpbErrorMsg[ 200 ];
			long  dwNativeError;
			short wDummy;

			SQLError( henv, hdbc, hstmt, lpbSQLState, &dwNativeError, lpbErrorMsg, 200, &wDummy );
			TRACE( "\r\nSQL ERROR [SQLGetData]:" );
//			TRACE( "\r\n\tOriginal SQL query statement: [ %s ]", lpszRequest );
			TRACE( "\r\n\tSQL State: %s", lpbSQLState );
			TRACE( "\r\n\tNative Error: %u", dwNativeError );
			TRACE( "\r\n\tError message: %s", lpbErrorMsg );		
    }
 	return rc;
}

//////////////////////////////////////////////////////////////////////////////////////////
RETCODE cODBCMage::GetWORD
//////////////////////////////////////////////////////////////////////////////////////////
// This function fetches a WORD from the current SQL row.
// 
(
 UWORD		uwCol,		// Column to fetch data from.
 LPWORD		lpwFetch		// WORD pointer to put data in.
)
// Return: RETCODE, the SQL return code of the query
//////////////////////////////////////////////////////////////////////////////////////////
{
	rc = SQLGetData(hstmt, uwCol, SQL_C_USHORT, lpwFetch, 0, NULL ) ;

	return rc;
}
//////////////////////////////////////////////////////////////////////////////////////////
RETCODE cODBCMage::GetSWORD
//////////////////////////////////////////////////////////////////////////////////////////
// This function fetches a WORD from the current SQL row.
// 
(
 UWORD		uwCol,		// Column to fetch data from.
 short *    lpwFetch		// WORD pointer to put data in.
)
// Return: RETCODE, the SQL return code of the query
//////////////////////////////////////////////////////////////////////////////////////////
{
	rc = SQLGetData(hstmt, uwCol, SQL_C_SSHORT, lpwFetch, 0, NULL ) ;

	return rc;
}

//////////////////////////////////////////////////////////////////////////////////////////
RETCODE cODBCMage::GetBYTE
//////////////////////////////////////////////////////////////////////////////////////////
// This function fetches a DWORD from the current SQL row.
// 
(
 UWORD		uwCol,		// Column to fetch data from.
 LPBYTE		lpbFetch	// DWORD pointer to put data in.
)
// Return: RETCODE, the SQL return code if the query
//////////////////////////////////////////////////////////////////////////////////////////
{	
	SDWORD sdwMaxSize = 0;	
	WORD wWord = 0;
	
	rc = SQLGetData( hstmt, uwCol, SQL_C_USHORT, &wWord, 0, NULL );
	
	*lpbFetch = (BYTE)wWord;
	
	return rc; 
}


//////////////////////////////////////////////////////////////////////////////////////////
RETCODE cODBCMage::GetBLOB
//////////////////////////////////////////////////////////////////////////////////////////
// This function returns a byte buffer fetched from a row.
// NOTE: The caller is responsible for freeing the lpData created by this function.
//		 If the returned buffer is NULL, no data was fetched and dwSize will equal 0.
// 
(
 UWORD		uwCol,		// Column to fetch data from.
 LPVOID		*lppData,	// Pointer to a pointer which will contain the data in row:column.
 LPDWORD	lpdwSize	// Pointer to a DWORD which contains the size of the fetched buffer
)
// Return: RETCODE, the SQL return code if the query
//////////////////////////////////////////////////////////////////////////////////////////
{		
	LPBYTE lpResult = (LPBYTE)( *lppData );
	SDWORD sdwBufferSize = 0;
	SDWORD sdwNewSize = 0;
	int nDummy;	// dummy buffer, to avoid some possible problems with a null data buffer.
	
	// Make a first query asking for 0 bytes, this should return the complete buffer size.
	rc = SQLGetData( hstmt, uwCol, SQL_LONGVARBINARY, &nDummy, 0, &sdwBufferSize );

	if( sdwBufferSize != SQL_NO_TOTAL && sdwBufferSize != 0 ){
		// Create the buffer to accomodate the request.
		lpResult = new BYTE[ sdwBufferSize ];
		*lpdwSize = sdwBufferSize;
	
		// Fetch the complete amount of data, now that we have the complete buffer.
		rc = SQLGetData( hstmt, uwCol, SQL_LONGVARBINARY, lpResult, sdwBufferSize, &sdwNewSize );
	}else{
		lpResult = NULL;
		*lpdwSize = 0;
	}
	
	return rc; 
}

//////////////////////////////////////////////////////////////////////////////////////////
RETCODE cODBCMage::GetString
//////////////////////////////////////////////////////////////////////////////////////////
// This function fetches a string from the current SQL row.
// 
(
 UWORD		uwCol,		// Column to fetch data from.
 LPTSTR		lpszText,	// Pointer to a buffer which will contain the string.
 int		nMaxSize	// Max size of the given character buffer.
)
// Return: RETCODE, the SQL return code of the query
//////////////////////////////////////////////////////////////////////////////////////////
{
	SDWORD sdwNewMaxSize = 0;

	rc = SQLGetData( hstmt, uwCol, SQL_C_CHAR, lpszText, nMaxSize, &sdwNewMaxSize );

	return rc;
}

//////////////////////////////////////////////////////////////////////////////////////////
RETCODE cODBCMage::GetDouble
//////////////////////////////////////////////////////////////////////////////////////////
// This function fetches a DWORD from the current SQL row.
// 
(
 UWORD		uwCol,		// Column to fetch data from.
 double		*lpdblFetch	// double pointer to put data in.
)
// Return: RETCODE, the SQL return code of the query
//////////////////////////////////////////////////////////////////////////////////////////
{
	return SQLGetData( hstmt, uwCol, SQL_C_DOUBLE, lpdblFetch, 0, NULL );
}


//////////////////////////////////////////////////////////////////////////////////////////
RETCODE cODBCMage::GetDate
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the date from a field.
// 
(
 UWORD uwCol,               // The field's column
 SQL_DATE_STRUCT *lpSqlDate // The date structure to fill.
)
// Return: RETCODE, the SQL return code for the query.
//////////////////////////////////////////////////////////////////////////////////////////
{
    SDWORD nSize = 0;    
    return SQLGetData( hstmt, uwCol, SQL_C_TYPE_DATE, &lpSqlDate, sizeof( SQL_DATE_STRUCT ), &nSize );
}
//////////////////////////////////////////////////////////////////////////////////////////
void cODBCMage::InitializeWriteThread( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Initializes the write thread
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	if( hThreadID == NULL ){
		// Create the IO Completion port associated with the thread, before it starts.
		hIoCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 1);

		// Start the thread.
		hThreadID = (HANDLE)_beginthread( ODBCWriteThread, 0, this );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
void cODBCMage::SendBatchRequest
//////////////////////////////////////////////////////////////////////////////////////////
// Sends a batch of requests to the data source. Uses ODBCWrite thread to asynchronously
// send the requests and report to callback function.
//
(
 TemplateList<SQL_REQUEST> *lptlRequests,	// List of requests to send
 SQLTERMINATION lpTerminationCallback,		// Callback called upon batch request termination.
 LPVOID lpData,								// User data to send to callback function.
 LPTSTR lpszText							// Text that indicates the SendBatchRequest caller
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Do not accept requests if shutting down.
    //if( !boShutdown ){
        // Initialize thread
	    InitializeWriteThread();

	    BATCH_REQUEST *lpBatch = new BATCH_REQUEST;
	    lpBatch->lptlRequests = lptlRequests;
	    lpBatch->lpTerminationCallback = lpTerminationCallback;
	    lpBatch->lpData = lpData;
		lpBatch->lpszText = lpszText;

	    PostQueuedCompletionStatus( hIoCompletionPort, 0, (DWORD)lpBatch, NULL );
    //}
}

//////////////////////////////////////////////////////////////////////////////////////////
void cODBCMage::WaitForODBCShutdown( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Shuts downs ODBC and assures all requests have been sent before returning.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Now in shutdown mode.
    boShutdown = TRUE;

    // Send a STOP message to the io completion port.
    //PostQueuedCompletionStatus( hIoCompletionPort, 1, NULL, NULL );

    // Wait until ODBC thread terminates.
    WaitForSingleObject( hThreadID, INFINITE );
}

//////////////////////////////////////////////////////////////////////////////////////////
void cODBCMage::ODBCWriteThread
//////////////////////////////////////////////////////////////////////////////////////////
// This is the write thread. It only starts after the first call to SendBatchRequest.
// 
(
 LPVOID lpODBCObject // The object
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	CAutoThreadMonitor tmMonitor("ODBC Write Thread");
	_LOG_DEBUG
        LOG_DEBUG_LVL1,
        "ODBCWriteThread Id=%u",
        GetCurrentThreadId()
    LOG_
    
    cODBCMage *lpODBC = (cODBCMage *)lpODBCObject;
	DWORD dwStopMessage = 0;	
	LPOVERLAPPED s_oDummy;
	DWORD dwlpBatch;
	SQL_REQUEST *lpRequest;
	BATCH_REQUEST *lpBatch;
	TemplateList <SQL_REQUEST> *lptlRequests;
	BOOL boEndBatch;		

    // Force thread to run on the first CPU.
    //SetThreadAffinityMask( lpODBC->hThreadID, 1 );

    CDeadlockDetector cDeadlockDetector;
    cDeadlockDetector.RegisterThread( lpODBC->hThreadID, "ODBCWriteThread", 300000  );

	CString csRequest;
	char tmpbuf[9];

	// Read until its time to terminate the thread.
	while( dwStopMessage == 0 ){
        ENTER_TIMEOUT
		// Get the queued requests
		if( GetQueuedCompletionStatus( lpODBC->hIoCompletionPort, &dwStopMessage, &dwlpBatch, &s_oDummy, 2500 )){
            LEAVE_TIMEOUT
			// If this isn't a thread termination message
			if( dwStopMessage == 0 ){
				// Process the batch query
				lpBatch = (BATCH_REQUEST *)dwlpBatch;				
				lptlRequests = lpBatch->lptlRequests;
				
				boEndBatch = FALSE;
                // Lock ODBC
				lpODBC->Lock();

                DWORD dwBefore = GetRunTime();
				// Scroll the requests
				lptlRequests->ToHead();

				while( lptlRequests->QueryNext() && !boEndBatch ){
					lpRequest = lptlRequests->Object();

					//Tracing
					csRequest.Empty();
//					csRequest.Format( _strtime(tmpbuf) );
					csRequest += _strtime(tmpbuf);
					csRequest += " ; ";
					csRequest += lpRequest->csQuery;
					csRequest += " ; ";
					csRequest += lpBatch->lpszText;
					//csRequest += "\r\n";
					ODBCHarness->Lock();
					ODBCHarness->addRequest(csRequest);
					ODBCHarness->Unlock();
					//Tracing
					_LOG_DEBUG
						LOG_DEBUG_HIGH,
						"-->>> %s",
						csRequest
					LOG_

					if( !lpODBC->SendRequest( (LPCTSTR)lpRequest->csQuery ) ){
							boEndBatch = TRUE;
						}
						KEEP_ALIVE
					}
						
					DWORD dwAfter = GetRunTime();

					_LOG_DEBUG
						LOG_DEBUG_HIGH,
						"-->>> ODBC requests took %ums to send.",
						dwAfter - dwBefore
					LOG_

					//Tracing
					ODBCHarness->Lock();
					ODBCHarness->addDuration( dwAfter - dwBefore );
					ODBCHarness->Unlock();
					//Tracing
					
					if( boEndBatch ){
						if( CT4CLog::GetLog( LOG_DEBUG ) != NULL && 
							CT4CLog::GetLog( LOG_DEBUG )->GetLogLevels() & LOG_DEBUG_LVL2 ){

							CString csText;
							csText.Format( "Rollbacked %u database requests. Requests: ", lptlRequests->NbObjects() );

							_LOG_DEBUG
								LOG_DEBUG_LVL2,
								(char *)(LPCTSTR)csText
							LOG_

							csText.Empty();

							int i = 0;
							lptlRequests->ToHead();
							while( lptlRequests->QueryNext() ){
								csText += " [ ";
								csText += lptlRequests->Object()->csQuery;
								csText += " ]";

								_LOG_DEBUG
									LOG_DEBUG_LVL2,
									(char *)(LPCTSTR)csText
								LOG_
								csText.Empty();
							}
						}
						lpODBC->Rollback();					

						if( lpBatch->lpTerminationCallback != NULL ){
							// Call the callback function, batch request terminated.
							lpBatch->lpTerminationCallback( BATCH_FAILED, lpBatch->lpData );
						}
					}else{
						lpODBC->Commit();
						if( lpBatch->lpTerminationCallback != NULL ){
							// Call the callback function, batch request terminated.
							lpBatch->lpTerminationCallback( BATCH_SUCCEEDED, lpBatch->lpData );
						}
					}

					// Destroy each objects in list.
					lptlRequests->AnnihilateList();
					// Unlock ODBC
					lpODBC->Unlock();
					delete lptlRequests;
					delete lpBatch;
			}
        }else{
            if( lpODBC->boShutdown ){
                static int tryCount = 0;
                if( tryCount > 0 ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL1,
                        "ODBC was shutdown, writing thread empty."
                    LOG_

                    dwStopMessage = 1;
                }
                tryCount++;
            }
            LEAVE_TIMEOUT;
        }
	}

    STOP_DEADLOCK_DETECTION
}