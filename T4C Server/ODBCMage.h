//	Filename: ODBCMage.h
//	Author	: Guy Carbonneau
//	Date	: 03.04.1998
//
//  This class is a homemade class it will be used for all kind of ODBC Access magic tricks
//  that will be required from me.  It will start up as a test to be elaborated to a level beyond
//  human capabilities... NOT. But it should have some neet functions hopefully.

#ifndef _ODBCMAGE_H
#define _ODBCMAGE_H

//#include <windows.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include "vdlist.h"
#include "Lock.h"

#define BATCH_FAILED		0
#define BATCH_SUCCEEDED		1

//////////////////////////////////////////////////////////////////////////////////////////
// This type defines single sql requests to send in batch writing.
typedef struct _SQL_REQUEST{
	BYTE		bFailBehavior;	// Behavior of batch request upon failure
	CString		csQuery;		// The query.
} SQL_REQUEST, *LPSQL_REQUEST;

typedef void ( *SQLTERMINATION )( DWORD dwResult, LPVOID lpData );

class cODBCMage
{
private:
	RETCODE				rc;				// Return code of ODBC functions.

	HENV				henv;			// Environment Handle.
	HDBC				hdbc;			// Connection Handle.
	HSTMT				hstmt;			// Statement Handle.
    bool                boStmtAlloc;    // TRUE if hstmt has been allocated.
		
	char	lpszCurrentDSN[250];			// The currently connected data source name.
	char	lpszCurrentUser[100];		    // The currently connected user.
	char	lpszCurrentPWD[100];			// The currently connected user's password.

    BOOL    boShutdown;

    static  bool  boSerialize;
    static  CLock cStaticLock;
    CLock cNonStaticLock;
    
    static struct StaticInit{
        StaticInit( void );
    } m_StaticInit;
    friend StaticInit;


public:

	cODBCMage();
	~cODBCMage();    

	void Create();
	void Destroy();

    //LOCK_FUNC  { if( boSerialize ){ cStaticLock.Lock();   }else{ cNonStaticLock.Lock();   } };               
    //UNLOCK_FUNC{ if( boSerialize ){ cStaticLock.Unlock(); }else{ cNonStaticLock.Unlock(); } };
    void Lock(  );
    void Unlock(  );
	
	void Connect(LPCSTR szDataSource, LPCSTR szUsername, LPCSTR szPassword);
	void AllocStmt( void ); //extra qualification cODBCMage::

    void CheckDisconnectError( void );
	void Disconnect();	
	BOOL ExecuteRequest(LPCSTR szField, LPCSTR szTablename, LPCSTR szWhereStmt);	

	// Sets specific connection options
	void ConnectOption( WORD wConnectOption, DWORD dwOptionValue );

	// Commits or rollbacks when connection is in manual commit mode.
	int Commit( void );
	int Rollback( void );


	// Send a SQL request to the connected ODBC driver
	BOOL SendRequest( LPCTSTR lpszRequest, bool boKnownError = false );

	// Moves to the first row in the current recordset.
	BOOL Fetch( void );

	// Cancels the current transaction.
	BOOL Cancel( void );

	// Closes the current transaction.
	BOOL CloseCursor( void );

	// Fetching functions.
	RETCODE GetDWORD	( UWORD uwCol, LPDWORD lpdwFetch );
	RETCODE GetWORD		( UWORD uwCol, LPWORD lpwFetch );
	RETCODE GetBYTE		( UWORD uwCol, LPBYTE lpbFetch );
	RETCODE GetDouble	( UWORD uwCol, double *lpdblFetch );
	RETCODE GetBLOB		( UWORD uwCol, LPVOID *lppData, LPDWORD lpdwBufferSize );
	RETCODE GetString	( UWORD uwCol, LPTSTR lpszText, int nMaxTextSize );
    RETCODE GetDate     ( UWORD uwCol, SQL_DATE_STRUCT *lpSqlDate );
    RETCODE GetSWORD    ( UWORD uwCol, short *lpsFetch );
    RETCODE GetSDWORD   ( UWORD uwCol, long *lpsFetch );

	// Initializes the write thread.
	void InitializeWriteThread( void ); //extra qualification
	// Sends a batch request to ODBC. Uses OBDCWriteThread to queue calls asynchronously.
	void SendBatchRequest( TemplateList <SQL_REQUEST> *lptlRequests,
						   SQLTERMINATION lpTerminationCallback, 
						   LPVOID lpData, 
						   LPTSTR lpszText );

    // Stops all new requests from being sent and waits until all batch requests have been sent before returning.
    void WaitForODBCShutdown( void );

	// This is the writting thread.
	static void ODBCWriteThread( LPVOID lpVoid );
    
private:    

	struct BATCH_REQUEST{
		TemplateList <SQL_REQUEST> *lptlRequests;
		SQLTERMINATION lpTerminationCallback;
		LPVOID lpData;
		LPTSTR lpszText;
	};

	HANDLE hThreadID;
	HANDLE hIoCompletionPort;
};

#endif
