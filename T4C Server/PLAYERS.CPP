// Players.cpp: implementation of the Players class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "Players.h"
#include "TFC_MAIN.H"
#include "ODBCMage.h"
#include "TFCMessagesHandler.h"
#include "AutoConfig.h"
#include "random.h"
#include "PlayerManager.h"
#include "AsyncFuncQueue.h"
#include "format.h"

//#include "VopCom.h"
//raw_interfaces_only, raw_native_types, no_namespace, named_guids

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern Random rnd;
extern CTFCServerApp theApp;
extern TFC_MAIN *TFCServer;

#define AUTH_WATCH_DOG_DELAY    10 MINUTES

static cODBCMage ODBCUsers;
//static cODBCMage ODBCAsyncUsers;

// Defines the table rows associated with the different fields.
#define DB_UserPC					1
#define DB_UserAppearance			2
#define DB_UserLevel				3


//#define VOP_KEY  "VSEC941145"

namespace{
    class CAutoLoad{
    public:
        CAutoLoad(){
            CAutoConfig::AddRegInt( T4C_KEY CHARACTER_KEY, "ShoutDelay", 10, HKEY_LOCAL_MACHINE );
        };        
    } cAutoLoad;
};

DWORD Players::dwAutoSaveFrequency = 240; //Dialsoft modified delay, was 600 initially//BLBLBL mis à 240 au lieu de 120, pour limiter usage SQL

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Players::Players()
{	
//	InitializeCriticalSection( &csPacketLock );
//	InitializeCriticalSection( &csUsageLock );
	
    loadingCount = 0;
	//	IP_addr = "";
//	port_addr = 0;

	IdleChances = 0;

	in_game = FALSE;    // Player always starts out of the game
	registred = FALSE;//FALSE;  // Player is, by default, not registred to play!
	god_mode = FALSE;//FALSE; // By default, no one is a GOD! :)
	boPreInGame = FALSE;
	
	// BEGIN : Mestoph : Anti SpeedHack
	/*iCountMovement = 0;
	iSpeedHackTime = time(NULL);
	bSpeedHackWarned = FALSE;*/
	// END : Mestoph : Anti SpeedHack
    
	// BEGIN : BL -> Anti Speedhack (2nd try)
	lLastRoundMove=0;
//	lMoveCounter=0;
	// END : BL -> Anti Speedhack (2nd try)
	
	self = new Character;
    self->SetPlayer( this );

	i64GodFlags = 0;	// No god flags by default
	boRerolling = FALSE;
	boWhoInvisible = FALSE;
	boCanTalk = TRUE;
	boCanShout = TRUE;
	lCutExpireDate = 0;//BLBLBL on initialise l'expiration date à 0
	boLockedOut = FALSE;
	lLockExpireDate = 0;//BLBLBL on initialise l'expiration date à 0
    boCanPage = TRUE;
    cCreditDeduction = 0;

    dwCredits = 0xFFFFFFFF;     // Inifinite credits by default.	
	dwKickoutTime = 0xFFFFFFFF;
    dwRegenTime = 0;
    cMinutesLeft = 6;    
    dwNextSave = 0;

    boDeletionFlag = FALSE;

    dwNextShout = 0;

    boIdle = false;

	boSanctuPlug = false;//BLBBL par defaut, un joueur n'est pas en train de sanctu plug.

    //dwAuthWatchDogTime = 0xFFFFFFFF;

    time( &ttLogTime );

    static DWORD dwNewPlayerAcctID = 0;
    dwPlayerAcctID = dwNewPlayerAcctID++;

    dwNextPageTime = 0;
    dwNextPageCount = 0;

    boCanPVP = true;
    boFullPVP = false;

    pages = true;

	pPCs = new TemplateList <CStringAndRace>;
	m_timeout = GetTickCount() + 15000;
}

Players::~Players()
{	
	pPCs->ToHead();
	while(pPCs->QueryNext()){
		pPCs->DeleteAbsolute();
	}

	delete pPCs;
}

inline char *Players::QuotedAccount( char szBuffer[], CString &csAccount ){
    
    int nLength = csAccount.GetLength();
    int i, j = 0;
    
    for( i = 0; i < nLength; i++ ){
        szBuffer[ j ] = csAccount[ i ];
        if( szBuffer[ j ] == '\'' ){
            j++;
            szBuffer[ j ] = '\'';
        }

        j++;
    }
    szBuffer[ j ] = 0;

    return szBuffer;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::InitializeODBC( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Connects the Users database for the first time, specifying the DSN
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	ODBCUsers.Connect( USERS_DSN, USERS_USER, USERS_PWD );

    TFormat format;



	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout
	//////////////////////////////////////////////////////////////////////////////////////////
	ODBCUsers.SendRequest(
		format(
			"DELETE FROM Flags WHERE FlagID='14'", 
			(LPCTSTR)theApp.csMachineName
		)
	);



    // Flush all online user records.
    ODBCUsers.SendRequest( 
        format( 
            "DELETE FROM OnlineUsers WHERE MachineName='%s'",//BLBLBL 05/01/2011 
            (LPCTSTR)theApp.csMachineName 
        ) 
    );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::DestroyODBC( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Deconnects from the ODBC server.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    TFormat format;

    // Flush all online user records.
    ODBCUsers.SendRequest( 
        format( 
            "DELETE FROM OnlineUsers WHERE MachineName='%s'",//BLBLBL 05/01/2011 
            (LPCTSTR)theApp.csMachineName 
        )
    );

	ODBCUsers.Disconnect( );
}

CString Players::GetIP(){
	return inet_ntoa(IPaddr.sin_addr);
}

int Players::GetPort(){
	return ntohs( IPaddr.sin_port );
}

BOOL Players::IsGod(){
	return god_mode;}

void Players::SetGodMode(BOOL asd){
	god_mode = asd;}
void Players::SetInGame(BOOL status){
	in_game = status;
}


void Players::SetGodFlags( unsigned __int64 i64Flags ){
	i64GodFlags = i64Flags;
}

unsigned __int64 Players::GetGodFlags( void ){
return i64GodFlags;
}

UINT Players::NbPlayers(){
	return pPCs->NbObjects();
}

//////////////////////////////////////////////////////////////////////////////////////////
#define ADD_INSERT_PC_NAME	if( pPCs->QueryNext() ){\
			csTemp.Format( "'%s',", (LPCTSTR)pPCs->Object()->name );\
		}else{\
			csTemp.Format( "NULL," );\
		}	csQuery += csTemp;
//////////////////////////////////////////////////////////////////////////////////////////
#define ADD_UPDATE_PC_NAME( PC_NAME ) if( pPCs->QueryNext() ){\
			csTemp.Format( PC_NAME"='%s',", (LPCTSTR)pPCs->Object()->name );\
		}else{\
			csTemp.Format( PC_NAME"=NULL," );\
		}	csQuery += csTemp;

#define ADD_QUERY	{ \
	LPSQL_REQUEST lpSql = new SQL_REQUEST;\
	lpSql->csQuery = csQuery;\
	lptlSQLRequests->AddToTail( lpSql );\
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Players::SaveAccount
//////////////////////////////////////////////////////////////////////////////////////////
// This functions saves the information of a player in the database
// 
(
 BOOL boCreate // TRUE if we create a new player
)
// Return: BOOL, TRUE if the player has been saved.
//////////////////////////////////////////////////////////////////////////////////////////
{	
	const INT BitFieldSize = 64; // steph ajout de INT

	CString csQuery;
	CString csTemp;
	
	BOOL boInsert = FALSE;
	unsigned __int64 i;

	TemplateList< SQL_REQUEST > *lptlSQLRequests = new TemplateList< SQL_REQUEST >;

    char szAccount[ 1024 ];

    QuotedAccount( szAccount, GetAccount() );    

	// Delete the currently set user flags
	csQuery.Format( "DELETE FROM UserFlags WHERE AccountName='%s'", szAccount );
	
	ADD_QUERY;

	// If player is god
	if( IsGod() )
	{
		// Check each god flag
		for( i = 0; i < BitFieldSize; i++ )
		{
			TRACE( "%u,", i );
			// If player has bit
			if( GetGodFlags() & (unsigned __int64)( (unsigned __int64)(1) << i ) )
			{
				// Add it
				csQuery.Format( "INSERT INTO UserFlags(AccountName, FlagBitPosition) VALUES ('%s', %u)", 
								szAccount,
								i );
				ADD_QUERY;
			}
		}
	}	

	if( !boCanTalk ){
		csQuery.Format( "INSERT INTO UserFlags(AccountName, FlagBitPosition) VALUES('%s', 10001)", szAccount );
		ADD_QUERY;
	}
	if( !boCanShout ){
		csQuery.Format( "INSERT INTO UserFlags(AccountName, FlagBitPosition, ExpireDate) VALUES('%s', 10002, %d)", szAccount, lCutExpireDate );//BLBLBL ajouté expire date
		ADD_QUERY;
	}
	if( boLockedOut ){
		csQuery.Format( "INSERT INTO UserFlags(AccountName, FlagBitPosition, ExpireDate) VALUES('%s', 10000, %d)", szAccount, lLockExpireDate );//BLBLBL ajouté expire date
		ADD_QUERY;
	}
    if( boWhoInvisible ){
		csQuery.Format( "INSERT INTO UserFlags(AccountName, FlagBitPosition) VALUES('%s', 10003)", szAccount );
		ADD_QUERY;
    }
    if( !boCanPVP ){
        csQuery.Format( "INSERT INTO UserFlags(AccountName, FlagBitPosition) VALUES('%s', 10004)", szAccount );
        ADD_QUERY;
    }
    if( !boCanPage ){
        csQuery.Format( "INSERT INTO UserFlags(AccountName, FlagBitPosition) VALUES('%s', 10005)", szAccount );
        ADD_QUERY;
    }
    if( boFullPVP ){
        csQuery.Format( "INSERT INTO UserFlags(AccountName, FlagBitPosition) VALUES('%s', 10006)", szAccount );
        ADD_QUERY;
    }

	// Save the flags
	//ODBCUsers.Lock();
	ODBCUsers.SendBatchRequest( lptlSQLRequests, NULL, NULL, "ODBCUsers" );
	//ODBCUsers.Unlock();
    
 

	return TRUE;
}

struct AsyncWriteCreditDeductionData{
    CString theAccount;
    DWORD   dwPlayerAcctID;
    DWORD   onlineTime;
    sockaddr_in sockAddr;
};

//////////////////////////////////////////////////////////////////////////////////////////
void AsyncWriteCreditDeduction( LPVOID lpData )
//////////////////////////////////////////////////////////////////////////////////////////
{
    /*AsyncWriteCreditDeductionData *pData = reinterpret_cast< AsyncWriteCreditDeductionData * >( lpData );

    CString &theAccount = pData->theAccount;
    
    // If a realm was specified.
    if( !theApp.sAuth.csRealm.IsEmpty() ){
        // Try to find if the user has inputed an @ sign.
        int realmPos = theAccount.FindOneOf( "@" );                
        // If the user inputed an @ sign.    
        if( realmPos != -1 ){
            // Flush the realm specified by the user.
            theAccount = theAccount.Left( realmPos );
        }
        theAccount += '@';
        theAccount += theApp.sAuth.csRealm;
    }
    
    CString step = "Instantiating COM object";
    try{            
        IRadClntPtr iVop( "VOPCOM.RadClnt" );
        
        step = "Setting license key";
        iVop->LicenseKey = VOP_LICENSE_KEY;
        
        step = "Setting up logging";
        iVop->LogFile = (LPCTSTR)theApp.sAuth.vopLogFile;
        iVop->LogLevels = theApp.sAuth.vopLogLevels;
        
        step = "Opening request";
        long requestID = iVop->OpenRequest(
            (LPCTSTR)theAccount,
            "",
            (LPCTSTR)theApp.sAuth.csVOP_NASIP,
            theApp.sAuth.csVOP_NASPort,
            (LPCTSTR)theApp.sAuth.csVOP_Secret,
            theApp.sAuth.csWGFlag,
            "T4C Server",
            VOPCOM_ACCT_REQUEST
        );

        CString csAcctID;
        csAcctID.Format(
            "%s%u",
            theApp.szServerAcctID,
            pData->dwPlayerAcctID
            );
        
        step = "Setting accounting options";
        const ACCT_STOP = 2;
//        TRACE( "\nRadiusPortID=%u.", dwRadiusPortID );
        // Set accounting options.
        long bSuccess = iVop->SetAcctOptions(
            requestID,
            ACCT_STOP,
            (DWORD)pData->onlineTime,
            (LPCTSTR)csAcctID
        );
        
        {
            const VOP_SERVICE = 7;
            const VOP_ID  = 0x221516L;
        
            _variant_t varAttr;
        
            varAttr = _bstr_t( (LPCTSTR)_T("T4C Server") );
            // Add VOP Service so that VOP Acct works
            iVop->AddAttributeEx( requestID, VOP_SERVICE, VOP_ID, &varAttr );
        }
        
//DC Adding IP for Credit Deduction
		VARIANT  varIPAddr;
		VariantInit( &varIPAddr );
		DWORD hsIP = htonl( pData->sockAddr.sin_addr.S_un.S_addr );
		varIPAddr.lVal = long( hsIP ); 
		varIPAddr.vt   = VT_I4;
		iVop->AddAttributeEx( requestID, 8, 0, &varIPAddr );
		VariantClear( &varIPAddr );
//DC
        if( bSuccess ){
            step = "Sending request";
            iVop->SendRequest(
                requestID,
                (LPCTSTR)theApp.sAuth.csAcctIP,  //VOP_RADIP,
                theApp.sAuth.wAcctPort, //VOP_RADPORT,
                0
                );
        }
        
        step = "Closing request";
        iVop->CloseRequest( requestID );
    }catch( _com_error e ){
        _LOG_DEBUG
            LOG_CRIT_ERRORS,
            "There was a COM error sending radius accounting request (ACCT_STOP-%s): %s",
            (LPCTSTR)step,
            e.ErrorMessage()
            LOG_                    
    }

    delete pData;*/
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::WriteCreditDeduction( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Writes the credit deduction, either through Radius or ODBC.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // If credit deduction was enabled
    if( cCreditDeduction != 0 ){    
        // If authentication method is Radius.
        /*if( theApp.sAuth.bAuthentificationMethod == VOP_AUTH ){
#ifndef NO_VOP_ACCT
            // Send the request asynchronously
            AsyncWriteCreditDeductionData *pData = new AsyncWriteCreditDeductionData;
            pData->theAccount = GetFullAccountName();
            pData->dwPlayerAcctID = dwPlayerAcctID;
            pData->onlineTime = GetOnlineTime();
            pData->sockAddr = this->IPaddr;

            AsyncFuncQueue::GetAcctQueue()->Call( AsyncWriteCreditDeduction, pData );
#endif
        }else*/
        // Check if credits must be deducted through ODBC
        if( theApp.sAuth.boODBC_DeductCredits ){
            // If its an ODBC authentification
            if( theApp.sAuth.bAuthentificationMethod == ODBC_AUTH ){
                // If a credit field was specified.
                if( !theApp.sAuth.csODBC_Credits.IsEmpty() ){
                    // Get the ODBC authentification connection.
                    cODBCMage *lpODBCAuth = TFCMessagesHandler::GetODBCAuth();

                    time_t ttCurTime;
                    time( &ttCurTime );                

                    // Check online time.
                    double dOnlineTime = difftime( ttCurTime, ttLogTime );
                
                    int nCredits = dwCredits - (DWORD)dOnlineTime; // Substract seconds.
                    nCredits = nCredits < 0 ? 0 : nCredits;

                    TemplateList< SQL_REQUEST > *lptlSQLRequests = new TemplateList< SQL_REQUEST >;

                    char szAccount[ 1024 ];
                    QuotedAccount( szAccount, GetAccount() );
                    
                    CString csQuery;
                    // Update credits in the database.
                    csQuery.Format( "UPDATE %s SET %s=%u WHERE %s='%s'",
                        (LPCTSTR)theApp.sAuth.csODBC_Table,
                        (LPCTSTR)theApp.sAuth.csODBC_Credits,
                        nCredits,
                        (LPCTSTR)theApp.sAuth.csODBC_Account,
                        szAccount
                    );

                    ADD_QUERY;

                    // Send batch request to ODBC authentification database.
//                    lpODBCAuth->Lock();
                    lpODBCAuth->SendBatchRequest( lptlSQLRequests, NULL, NULL, "ODBCAuth" );
//                    lpODBCAuth->Unlock();

                }
            }
        }
    }
}

#define SUPERUSER( FLAG ) SetGodFlags( GetGodFlags() | FLAG )

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Players::LoadAccount
//////////////////////////////////////////////////////////////////////////////////////////
// Loads information from a database about a specific user.
// 
(
 CString name // Name of the player to load.
)
// Return: BOOL, TRUE if the player was successfully loaded.
//////////////////////////////////////////////////////////////////////////////////////////
{



	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
	const INT LockedOut     = 10000;
	const INT Squelched     = 10001;
	const INT NoShouts	    = 10002;
    const INT WhoInvisible  = 10003;
    const INT DisallowedPVP = 10004;
    const INT CannotPage    = 10005;
    const INT FullPVP       = 10006;
	



	// Desboys: Here is the 3 characters per account Limit.
	const int nMaxUsers = 3;
	int nCount = 0;
	
	CString csQuery;
	CStringAndRace *plNewPlayer;

	pPCs->ToHead();
	while( pPCs->QueryNext() ){
		pPCs->DeleteAbsolute();
	}    

	delete pPCs;
    pPCs = new TemplateList <CStringAndRace>;

    SetGodFlags( 0 );
    if( stricmp( (LPCTSTR)name, CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str() ) == 0 ){
        // SuperUser has the ability of giving god flags.
        SetGodFlags( GOD_CAN_GIVE_GOD_FLAGS );
        SetGodMode( TRUE );
    }

	ODBCUsers.Lock();

    struct AutoFindoutBug{
        AutoFindoutBug(){
            _LOG_DEBUG
                LOG_DEBUG_HIGH,
                "Entered Players::LoadAccount"
            LOG_
        }
        ~AutoFindoutBug(){
            _LOG_DEBUG
                LOG_DEBUG_HIGH,
                "Left Players::LoadAccount"
            LOG_
        }

    } cAutoFindoutBug;

    char szAccount[ 1024 ];

    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Players::LoadAccount QuotedAccount( %s )",
        (LPCTSTR)GetAccount()
    LOG_

    QuotedAccount( szAccount, GetAccount() );

    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Players::LoadAccount csQuery.Format()"
    LOG_

	// Send a query to fetch the spcified user.
#ifdef MSSQLSERVER
    csQuery.Format( "SELECT TOP 20 PlayerName, Appearance, CurrentLevel FROM PlayingCharacters WHERE AccountName='%s'", szAccount ); //BLBLBL 05/01/2011 20 max characters should be enough
#else
    csQuery.Format( "SELECT PlayerName, Appearance, CurrentLevel FROM PlayingCharacters WHERE AccountName='%s' LIMIT 20", szAccount ); //BLBLBL 05/01/2011 20 max characters should be enough
#endif
    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Players::LoadAccount SendRequest()"
    LOG_

    ODBCUsers.SendRequest( (LPCTSTR)csQuery );

    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Players::LoadAccount 1"
    LOG_
    
    // If user could be fetched.
	while( ODBCUsers.Fetch() && nCount < nMaxUsers ){
		char lpszText[ 20 ];
		ODBCUsers.GetString( DB_UserPC, lpszText, 20 );
		
		plNewPlayer = new CStringAndRace;
		plNewPlayer->name = lpszText;

		ODBCUsers.GetWORD( DB_UserAppearance,	&plNewPlayer->race );
		ODBCUsers.GetWORD( DB_UserLevel,		&plNewPlayer->level );
		pPCs->AddToTail( plNewPlayer );
	}

	WORD wWord;
	unsigned long lSavedExpireDate;//BLBLBL systeme expiration des flags

	__int64 n64Flag;
	ODBCUsers.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

	csQuery.Format( "SELECT FlagBitPosition, ExpireDate FROM UserFlags WHERE AccountName='%s'", szAccount );//BLBL ajout ExpireDate
	TRACE( "SELECT FlagBitPosition, ExpireDate FROM UserFlags WHERE AccountName='%s'", szAccount );
	
    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Players::LoadAccount 2"
    LOG_
	
	ODBCUsers.SendRequest( (LPCTSTR)csQuery );
	// If user could be fetched.
	while( ODBCUsers.Fetch() ){
		n64Flag = 0;
		wWord = 0;
		// Get the flag.
		ODBCUsers.GetWORD( 1, &wWord );		
		ODBCUsers.GetDWORD( 2, &lSavedExpireDate );//au chargement on reprend la valeur expire stockée dans les flags

		// If its a god flag
		if( wWord < 64 ){			
			TRACE( "\r\nUser has flag bit %u", wWord );
			n64Flag = wWord;
			// Add it.
			SetGodFlags( GetGodFlags() | ( 1 << n64Flag ) );
			god_mode = TRUE;

			if( wWord > 10 && wWord < 20 ){
				SetGodFlags( GetGodFlags() | GOD_CAN_EDIT_USER );
			}else if( wWord > 20 && wWord < 26 ){
				SetGodFlags( GetGodFlags() | GOD_CAN_VIEW_USER );
			}
		}else{
   			time_t lTimeNow;//BLBL on récupère la date/heure courante pour vérifier les punitions expirées
			time(&lTimeNow);
			
			// Otherwise check for special case
			switch( wWord ){
			case LockedOut:
				
				lLockExpireDate = lSavedExpireDate;//BLBLBL on garde la valeur stockée dans les flags
				if (lLockExpireDate>0 && lLockExpireDate<lTimeNow) {//BLBL on ne vérifie que si une date d'expiration est définie.
					boLockedOut= FALSE;
					lLockExpireDate=0;
				}else{
					boLockedOut = TRUE;
				}
				
				//boLockedOut = TRUE;
			break;
			case Squelched:
				boCanTalk = FALSE;
			break;
			case NoShouts:
				lCutExpireDate = lSavedExpireDate;//BLBLBL on garde la valeur stockée dans les flags
				if (lCutExpireDate>0 && lCutExpireDate<lTimeNow) {//BLBL on ne vérifie que si une date d'expiration est définie.
					boCanShout= TRUE;
					lCutExpireDate=0;
				}else{
					boCanShout = FALSE;
				}
			break;
            case WhoInvisible:
                boWhoInvisible = true;
            break;
            case DisallowedPVP:
                boCanPVP = false;
            break;
            case CannotPage:
                boCanPage = FALSE;
            break;
            case FullPVP:
                boFullPVP = true;
            break;
			}
		}

	}

	_LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Players::LoadAccount 3"
    LOG_

    // If this is the super user!
    if( stricmp( 
        (LPCTSTR)GetFullAccountName(), 
        CAutoConfig::GetStringValue( "Software\\Vircom\\The 4th Coming Server\\GeneralConfig", "SuperUser", HKEY_LOCAL_MACHINE ).c_str() 
    ) == 0 ){
        // Give him some god flags.
        SUPERUSER( GOD_CAN_EDIT_USER );
        SUPERUSER( GOD_CAN_VIEW_USER );
        SUPERUSER( GOD_CAN_COPY_USER );
        SUPERUSER( GOD_CAN_EDIT_USER_APPEARANCE_CORPSE );
        SUPERUSER( GOD_CAN_EDIT_USER_BACKPACK );
        SUPERUSER( GOD_CAN_EDIT_USER_HP );
        SUPERUSER( GOD_CAN_EDIT_USER_MANA_FAITH );
        SUPERUSER( GOD_CAN_EDIT_USER_NAME );
        SUPERUSER( GOD_CAN_EDIT_USER_SKILLS );
        SUPERUSER( GOD_CAN_EDIT_USER_SPELLS );
        SUPERUSER( GOD_CAN_EDIT_USER_STAT );
        SUPERUSER( GOD_CAN_EDIT_USER_XP_LEVEL );
        SUPERUSER( GOD_CAN_EMULATE_MONSTER );
        SUPERUSER( GOD_CAN_GIVE_GOD_FLAGS );
        SUPERUSER( GOD_CAN_LOCKOUT_USER );
        SUPERUSER( GOD_CAN_REMOVE_SHOUTS );
        SUPERUSER( GOD_CAN_SEE_ACCOUNTS );
        SUPERUSER( GOD_CAN_SET_USER_FLAG );
        SUPERUSER( GOD_CAN_SHUTDOWN );
        SUPERUSER( GOD_CAN_SLAY_USER );
        SUPERUSER( GOD_CAN_SQUELCH );
        SUPERUSER( GOD_CAN_SUMMON_ITEMS );
        SUPERUSER( GOD_CAN_SUMMON_MONSTERS );
        SUPERUSER( GOD_CAN_TELEPORT );
        SUPERUSER( GOD_CAN_TELEPORT_USER );
        SUPERUSER( GOD_CAN_VIEW_USER_APPEARANCE_CORPSE );
        SUPERUSER( GOD_CAN_VIEW_USER_BACKPACK );
        SUPERUSER( GOD_CAN_VIEW_USER_SKILLS );
        SUPERUSER( GOD_CAN_VIEW_USER_SPELLS );
        SUPERUSER( GOD_CAN_VIEW_USER_STAT );
        SUPERUSER( GOD_CAN_ZAP );
        SUPERUSER( GOD_INVINCIBLE );
        SUPERUSER( GOD_UNLIMITED_SHOUTS );
        SUPERUSER( GOD_CAN_EMULATE_SYSTEM );
    }

	_LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Players::LoadAccount 4"
    LOG_


	// Cancel fetch
	ODBCUsers.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close
	ODBCUsers.Unlock();
	return TRUE;
}

void Players::AddPlayer(CString name, WORD race, WORD level){
	// checks to see if player isn't already there	
	pPCs->Lock();
	CStringAndRace *newPC = new CStringAndRace;
	newPC->name = name;
	newPC->race = race;
	newPC->level = level;
	pPCs->ToHead();
	pPCs->AddToTail(newPC);
	pPCs->Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::ModifyPlayer
//////////////////////////////////////////////////////////////////////////////////////////
// Modifies the player information of the player named 'name'.
// 
(
 CString name, // Name of the player to modify
 WORD race,    // New race to set.
 WORD level    // New level to set.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	BOOL boDone = FALSE;
	CStringAndRace *pl;
	pPCs->Lock();
	pPCs->ToHead();
	while( !boDone ){
		pl = pPCs->Object();

		if( pl->name == name ){
			pl->race = race;
			pl->level = level;
		}

		if(!pPCs->QueryNext())
			boDone = TRUE;
	}
	pPCs->Unlock();
}

void Players::RemovePlayer(CString name){
	
	CStringAndRace *PC;
	pPCs->Lock();
	pPCs->ToHead();
	while( pPCs->QueryNext() ){
		PC = pPCs->Object();
		if( stricmp( (LPCTSTR)PC->name, (LPCTSTR)name ) == 0 ){
			pPCs->DeleteAbsolute();
		}
	}
	pPCs->Unlock();

	SaveAccount( FALSE );
}

void Players::AddToHistory(unsigned long historyDate, CString historyText){

	CString csQuery;
	csQuery.Format( "INSERT INTO AccHistory(AccountName, HistoryDate, HistoryText) VALUES ('%s', %d,'%s')", 
                GetFullAccountName(),
                historyDate,
                historyText);
    ODBCUsers.SendRequest( csQuery, false );

}

CString Players::GetPwd() const{
	return m_Password;
}

void Players::SetPwd(CString name){
	m_Password = name;
}

CString Players::GetAccount() const{
	return m_Account;
}

void Players::SetAccount(CString name){
    // Parse the realm part of the account.
    int pos = name.ReverseFind( '@' );

    if( pos != -1 ){
        if( theApp.sAuth.m_StripRealmPartOfAccount ){
            m_Account = name.Left( pos );
        }else{
            m_Account = name;
        }
        
        m_Realm   = name.Right( name.GetLength() - pos - 1 );
    }else{
        m_Account = name;
    }
}

TemplateList <CStringAndRace> *Players::GetPCs(){
	return pPCs;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::UseDeathLock( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Locks player usage. Should never be called except by Death.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Trying usagelock(%s).",
        (LPCTSTR)GetAccount()
    LOG_	
    
    loadingCount++;
    csUsageLock.Lock();
    
    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Got usagelock(%s). loadingCount=%u.",
        (LPCTSTR)GetAccount(),
        loadingCount
    LOG_	
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::UseUnlock( const char *lpszFileName, int nLineNumber )
//////////////////////////////////////////////////////////////////////////////////////////
// Unlocks player usage.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    loadingCount--;
    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "UsageUnlock(%s) at %s(%u). loadingCount=%u",
        (LPCTSTR)GetAccount(),
        lpszFileName,
        nLineNumber,
        loadingCount
    LOG_
	
    csUsageLock.Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Players::UsePicklock( const char *lpszFileName, int nLineNumber )
//////////////////////////////////////////////////////////////////////////////////////////
// Picklocks player usage.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{   
    if( csUsageLock.PickLock() ){
        loadingCount++;
        _LOG_DEBUG
            LOG_DEBUG_HIGH,
            "UsagePicklock(%s) at %s(%u). loadingCount=%u",
            (LPCTSTR)GetAccount(),
            lpszFileName,
            nLineNumber,
            loadingCount
        LOG_
        

        return TRUE;
    }
    return FALSE;
}

bool Players::IsLoading(){
    return( loadingCount > 0 );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::SetCredits
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the credits remaining on a player.
// 
(
 DWORD dwNewCredits // Quantity of credits on player account.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    dwCredits = dwNewCredits;
}

//////////////////////////////////////////////////////////////////////////////////////////
DWORD Players::GetCredits( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the quantity of credits on player
// 
// Return: DWORD, Quantity of credits on user.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return dwCredits;
}

struct AsyncBeginSessionData{
    CString theAccount;
    DWORD   dwPlayerAcctID;
	sockaddr_in sockAddr;
};

//////////////////////////////////////////////////////////////////////////////////////////
void AsyncBeginSession( LPVOID lpData )
//////////////////////////////////////////////////////////////////////////////////////////
{
    /*AsyncBeginSessionData *pData = reinterpret_cast< AsyncBeginSessionData * >( lpData );

    CString &theAccount = pData->theAccount;
    // If a realm was specified.
    if( !theApp.sAuth.csRealm.IsEmpty() ){
        // Try to find if the user has inputed an @ sign.
        int realmPos = theAccount.FindOneOf( "@" );                
        // If the user inputed an @ sign.    
        if( realmPos != -1 ){
            // Flush the realm specified by the user.
            theAccount = theAccount.Left( realmPos );
        }
        theAccount += '@';
        theAccount += theApp.sAuth.csRealm;
    }
    
    
    CString step = "Instantiating COM object";
    try{            
        IRadClntPtr iVop( "VOPCOM.RadClnt" );
        
        step = "Setting license key";
        iVop->LicenseKey = VOP_LICENSE_KEY;

        step = "Setting up logging";
        iVop->LogFile = (LPCTSTR)theApp.sAuth.vopLogFile;
        iVop->LogLevels = theApp.sAuth.vopLogLevels;
        
        step = "Opening request";
        
        // Recreate a new request to send an accounting start message.
        long requestID = iVop->OpenRequest(
            (LPCTSTR)theAccount,
            "",
            (LPCTSTR)theApp.sAuth.csVOP_NASIP,
            theApp.sAuth.csVOP_NASPort,
            (LPCTSTR)theApp.sAuth.csVOP_Secret,
            theApp.sAuth.csWGFlag,
            "T4C Server",
            VOPCOM_ACCT_REQUEST
            );
        
        CString csAcctID;
        csAcctID.Format(
            "%s%u",
            theApp.szServerAcctID,
            pData->dwPlayerAcctID
            );
        
        //TRACE( "\nRadiusPortID=%u.", dwRadiusPortID );
        
        step = "Setting accounting options";
        const ACCT_START = 1;
        iVop->SetAcctOptions(
            requestID,
            ACCT_START,
            0,
            (LPCTSTR)csAcctID
            );
        
        {
            const VOP_SERVICE = 7;
            const VOP_ID  = 0x221516L;
            
            _variant_t varAttr;
            
            varAttr = _bstr_t( (LPCTSTR)_T("T4C Server") );
            // Add VOP Service so that VOP Acct works
            iVop->AddAttributeEx( requestID, VOP_SERVICE, VOP_ID, &varAttr );            
        }
        
//DC Adding IP for Begin session
		VARIANT  varIPAddr;
		VariantInit( &varIPAddr );
		DWORD hsIP = htonl( pData->sockAddr.sin_addr.S_un.S_addr );
		varIPAddr.lVal = long( hsIP );
		varIPAddr.vt   = VT_I4;
		iVop->AddAttributeEx( requestID, 8, 0, &varIPAddr );
		VariantClear( &varIPAddr );
//DC

        step = "Sending request";
        iVop->SendRequest(
            requestID,
            (LPCTSTR)theApp.sAuth.csAcctIP,
            theApp.sAuth.wAcctPort,
            0
            );
        
        step = "Closing request";
        iVop->CloseRequest( requestID );
        
    }catch( _com_error e ){
        _LOG_DEBUG
            LOG_CRIT_ERRORS,
            "There was a COM error sending radius accounting request (ACCT_START-%s): %s",
            (LPCTSTR)step,
            e.ErrorMessage()
            LOG_
    }

    delete pData;*/
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::BeginSession( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the round at which user first entered game.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    //dwAuthWatchDogTime = AUTH_WATCH_DOG_DELAY;    
    time( &ttLogTime );

    // If ODBC credit deduction or Radius authentication.
    if( theApp.sAuth.boODBC_DeductCredits ){
        cCreditDeduction = 1; // Enable credit deduction on player
        // If this is VOP authentication method.
        /*if( theApp.sAuth.bAuthentificationMethod == VOP_AUTH ){
#ifndef NO_VOP_ACCT
            AsyncBeginSessionData *pData = new AsyncBeginSessionData;

            pData->theAccount = GetFullAccountName();
            pData->dwPlayerAcctID = dwPlayerAcctID;
            pData->sockAddr = this->IPaddr;

            AsyncFuncQueue::GetAcctQueue()->Call( AsyncBeginSession, pData );
#endif
        }*/
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
double Players::GetOnlineTime( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the elapsed seconds since player got online.
// 
// Return: double, the elapsed time.
//////////////////////////////////////////////////////////////////////////////////////////
{
    time_t ttCurTime;
    time( &ttCurTime );
    
    return difftime( ttCurTime, ttLogTime );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::QueryNextSave( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Queries if player should auto-save.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( dwNextSave != 0 ){
        // If auto-save triggers.
        if( dwNextSave <= TFCMAIN::GetRound() ){
            // Save character
            self->SaveCharacter();
			_LOG_DEBUG
				LOG_DEBUG_LVL3,
				"Auto-save of %s requested after approx 4 minutes delay.", // steph 4 au lieu de 5
				(LPCTSTR)GetFullAccountName()
			LOG_

            // Set next auto-save time.
            dwNextSave = rnd( dwAutoSaveFrequency - 30, dwAutoSaveFrequency + 30 ) SECONDS TDELAY;
		    //Dialsoft modification : - 30 instead of -60 ^^  
			// dwAutoSaveFrequency = 300, which is 5 minutes.
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::SetNextSave( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the next auto save.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    dwNextSave = 4 MINUTES + ( rnd( 0, 2 ) MINUTES ) TDELAY;//BLBLBL modifié de 7 minutes +0,3 à 5+0,2 // steph 4 au lieu de 5
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::ResetIdle( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Resets the idle time on the player structure.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	
	/*_LOG_DEBUG
							LOG_CRIT_ERRORS,
							"RESETIDLE.%s",this->GetAccount()
					LOG_
*/
    //BLBL antiplug : in case of the player being under sanctuary spell effect the flush time must be 120 seconds
	if (this->self!=NULL && this->self->GetAC()>=5000) {
		IdleTime    = TFCMAIN::GetRound() + ( 75000 * 20 ) / 1000;//BL Note : 1 round dure 50ms, 20 rounds = 1 seconde, donc 75 secondes doit être converti en nombre de rounds
//		boSanctuPlug = true;
	}else{
		IdleTime    = TFCMAIN::GetRound() + TFCServer->flush_time;
//		boSanctuPlug = false;
	}
    IdleChances = 0;
	boIdle=false;//BLBLBL 11/12/2010 si on reset son statut, autant reset le booléan qui l'indique.
	m_timeout = GetTickCount() + 15000;


}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Players::IsIdle( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Determines if player is idle or not.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	
    if( boIdle ){
        return true;
    }
    

	/*if(this->m_timeout < GetTickCount()){
	
		//boIdle = true;
		//return true;
	}
	else if(GetTickCount() -  (this->m_timeout - 15000) > 2000){
		TFCPacket sending;
		sending << (RQ_SIZE)RQ_Ack;
		TRACE( "\r\nSending Keep-Alive" );
		self->SendPlayerMessage( sending );
	}
	
	return false;*/









    // If player is time-idle
	// BL Note : we check if the Client is not answering anymore (crashed or killed processus)
	//           each time the idle is reached we increment the "number of chances" the player had to come back
	//           if after max_chances if flush_time seconds the player still do not answer we kick him off
	//           to avoid his toon stay ingame.
	// Antiplug : BLBL In case of Sanctuary spell running on the character (AC>=5000) then the total 
	//           idle delay check must be 120 seconds (to let time to the sanctuary spell to wear off)

/*		    	_LOG_WORLD
                    LOG_MISC_1,
					"Idle time %u, round time : %u",IdleTime,TFCMAIN::GetRound()
				LOG_
*/
	/*if( IdleTime <= TFCMAIN::GetRound() ){//BLBLBL 12/12/2010 on check directement l'idle time
		
		if (this->self!=NULL && this->self->GetAC()>=5000) {
			boSanctuPlug = true;
		}else{
			boSanctuPlug = false;
		}
        if (boSanctuPlug) {
			_LOG_WORLD
                LOG_MISC_1,
				"Flushed player %s because chances (%u out of %u allowed) ran out during sanctuary spell.",
				(LPCTSTR)GetFullAccountName(),IdleChances,TFCServer->max_chances
			LOG_
		}else{
			_LOG_WORLD
                LOG_MISC_1,
				"Flushed player %s because chances (%u out of %u allowed) ran out.",
				(LPCTSTR)GetFullAccountName(),IdleChances,TFCServer->max_chances
			LOG_
		}
        
        // Faith is scealed, player is IDLE! 
        boIdle = true;
        return TRUE;
	
	}*/

    if( IdleTime <= TFCMAIN::GetRound()){
        
		//12/12/2010 BLBLB .. en fait.. c'est débile de changer l'idle time dans le isIdle(), il faut changer cela
		//quand on recoit un RQ_Ack..

		if (this->self!=NULL && this->self->GetAC()>=5000) {
			//BLBLBL 11/12/2010 : hmm, pourquoi changer cette valeur ici.. ça me parait bidon :
			IdleTime    = TFCMAIN::GetRound() + (75000 * 20) / 1000;//BL Note : 1 round dure 50ms, 20 rounds = 1 seconde, donc 75 secondes doit être converti en nombre de rounds
			boSanctuPlug = true;
		}else{
			//11/12/2010 :: apparement en commentat cette ligne, on a des prises rouges toutes les 10 sec : à VOIR !!!!!
			IdleTime = TFCMAIN::GetRound() + TFCServer->flush_time;
			boSanctuPlug = false;
		}
        
        IdleChances++; //BLBLBLL 12/12/2010 je vire carrément cette histoire de chances, ça chie les 3/4 du temps.
		    	/*_LOG_WORLD
                    LOG_MISC_1,
					"IdleChances increased %u.",
					IdleChances
				LOG_*/

        // If max chances exceeded.
       if( IdleChances > TFCServer->max_chances ){            
            if (boSanctuPlug) {
				_LOG_WORLD
                    LOG_MISC_1,
					"Flushed player %s because chances (%u out of %u allowed) ran out during sanctuary spell.",
					(LPCTSTR)GetFullAccountName(),IdleChances,TFCServer->max_chances
				LOG_
			}else{
				_LOG_WORLD
                    LOG_MISC_1,
					"Flushed player %s because chances (%u out of %u allowed) ran out.",
					(LPCTSTR)GetFullAccountName(),IdleChances,TFCServer->max_chances
				LOG_
			}
            
            // Faith is scealed, player is IDLE! 
            boIdle = true;
            return TRUE;
        }
       
        TFCPacket sending;
		sending << (RQ_SIZE)RQ_Ack;
		TRACE( "\r\nSending Keep-Alive" );
		self->SendPlayerMessage( sending );
		
    }

	if( dwKickoutTime < TFCMAIN::GetRound() ){
            if (boSanctuPlug) {
				_LOG_WORLD
                    LOG_MISC_1,
					"Flushed player %s because kickout time expired during sanctuary spell.",
					(LPCTSTR)GetFullAccountName()
				LOG_			
			}else{
				_LOG_WORLD
                    LOG_MISC_1,
					"Flushed player %s because kickout time expired.",
					(LPCTSTR)GetFullAccountName()
				LOG_
			}

            boIdle = true;
            return TRUE;
        }
		
	//If client was not timed out : send ack to client.
	
								
										  
										   
	   

    return FALSE;
}

/*struct WatchDogInfo{
    sockaddr_in sockAddr;
    CString theAccount;
    DWORD onlineTime;
    DWORD dwPlayerAcctID;
};*/

//////////////////////////////////////////////////////////////////////////////////////////
//void AsyncWatchDog
//////////////////////////////////////////////////////////////////////////////////////////
// Called asynchronously to check watch dog accounting information
// 
//(
 //LPVOID lpVoid // 
//)
//////////////////////////////////////////////////////////////////////////////////////////
//{
    /*WatchDogInfo *wdi = reinterpret_cast< WatchDogInfo * >( lpVoid );
 
    CString step = "Instantiating COM object";
    try{
        IRadClntPtr iVop( "VOPCOM.RadClnt" );

        step = "Setting license key";
        iVop->LicenseKey = VOP_LICENSE_KEY;

        step = "Setting up logging";
        iVop->LogFile = (LPCTSTR)theApp.sAuth.vopLogFile;
        iVop->LogLevels = theApp.sAuth.vopLogLevels;        

        step = "Opening request";
        // Create a new request to send a watch dog to.
        long requestID = iVop->OpenRequest(
            (LPCTSTR)wdi->theAccount,
            "",
            (LPCTSTR)theApp.sAuth.csVOP_NASIP,
            theApp.sAuth.csVOP_NASPort,
            (LPCTSTR)theApp.sAuth.csVOP_Secret,
            theApp.sAuth.csWGFlag,
            "T4C Server",
            VOPCOM_ACCT_REQUEST
        );

        CString csAcctID;
        csAcctID.Format(
            "%s%u",
            theApp.szServerAcctID,
            wdi->dwPlayerAcctID
        );
    
//        TRACE( "\r\nRadiusPortID=%u AcctID=%s. OnlineTime=%u", dwRadiusPortID, (LPCTSTR)csAcctID, (DWORD)GetOnlineTime() );
        
        step = "Setting account options";
        const ACCT_WATCHDOG = 3;
        // Set accounting options.
        iVop->SetAcctOptions(
            requestID,
            ACCT_WATCHDOG,
            (DWORD)wdi->onlineTime,
            (LPCTSTR)csAcctID
        );

        {
            const VOP_SERVICE = 7;
            const VOP_ID  = 0x221516L;
            
            _variant_t varAttr;
            
            varAttr = _bstr_t( (LPCTSTR)_T("T4C Server") );
            // Add VOP Service so that VOP Acct works
            iVop->AddAttributeEx( requestID, VOP_SERVICE, VOP_ID, &varAttr );            
        }
//DC Adding IP for WatchDog
    	VARIANT  varIPAddr;
		VariantInit( &varIPAddr );
		DWORD hsIP = htonl( wdi->sockAddr.sin_addr.S_un.S_addr );
		varIPAddr.lVal = long( hsIP ); 
		varIPAddr.vt   = VT_I4;
		iVop->AddAttributeEx( requestID, 8, 0, &varIPAddr );
		VariantClear( &varIPAddr );
//DC
        step = "Sending request";
        long ret = iVop->SendRequest(
		    requestID,
            (LPCTSTR)theApp.sAuth.csAcctIP,
		    theApp.sAuth.wAcctPort,
		    0
        );

        if( ret == VOPCOM_ACCT_CREDIT_FAIL || 
            ret == VOPCOM_ACCT_FAIL_TIME ||
            ret == VOPCOM_ACCT_FAIL ){

            Players *pl = CPlayerManager::GetPlayerResource( wdi->sockAddr );
            if( pl != NULL ){
                CString csText = _STR( 10492, pl->self->GetLang() );

                TFCPacket sending;
		        sending << (RQ_SIZE)RQ_ServerMessage;
		        sending << (short)30;
    	        sending << (short)3;
	            sending << (CString &)csText;
				sending << (long) 0x000A64E0 ;// RGB( 255, 0, 0 );
		        pl->self->SendPlayerMessage( sending );

                // flush player.
                pl->dwKickoutTime = 15 SECONDS TDELAY;

                CPlayerManager::FreePlayerResource( pl );
            }   
        }

        step = "Closing request";
        iVop->CloseRequest( requestID );
    }catch( _com_error e ){
        _LOG_DEBUG
            LOG_CRIT_ERRORS,
            "There was a COM error sending radius accounting request (ACCT_WATCHDOG): %s",
            e.ErrorMessage()
        LOG_            
    }

    delete wdi;*/
//}

//////////////////////////////////////////////////////////////////////////////////////////
//void Players::QueryAuthWatchDog( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Determines if we should send an authentication watch dog packet.
// 
//////////////////////////////////////////////////////////////////////////////////////////
//{
    // Only send watch dog packets for Radius authentication.
    /*if( cCreditDeduction != 0 && theApp.sAuth.bAuthentificationMethod == VOP_AUTH ){
        if( TFCMAIN::GetRound() >= dwAuthWatchDogTime ){
#ifndef NO_VOP_ACCT
            // Reset next ack.
            dwAuthWatchDogTime = AUTH_WATCH_DOG_DELAY TDELAY;

            CString theAccount = GetFullAccountName();
            // If a realm was specified.
            if( !theApp.sAuth.csRealm.IsEmpty() ){
                // Try to find if the user has inputed an @ sign.
                int realmPos = theAccount.FindOneOf( "@" );                
                // If the user inputed an @ sign.    
                if( realmPos != -1 ){
                    // Flush the realm specified by the user.
                    theAccount = theAccount.Left( realmPos );
                }
                theAccount += '@';
                theAccount += theApp.sAuth.csRealm;
            }


            WatchDogInfo *wdi = new WatchDogInfo;
            wdi->dwPlayerAcctID = dwPlayerAcctID;
            wdi->onlineTime = GetOnlineTime();
            wdi->sockAddr = this->IPaddr;
            wdi->theAccount = theAccount;

            AsyncFuncQueue::GetAcctQueue()->Call( AsyncWatchDog, wdi );
#endif
        }
    }*/
//}

//////////////////////////////////////////////////////////////////////////////////////////
bool Players::CanShout( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Queries if a player can shout.
// 
// Return: bool, true if player can shout.
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( dwNextShout <= TFCMAIN::GetRound() ){
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::ToggleShout( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Called to flag the user's shout.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{           
    // If player has unlimited shouts
    if( GetGodFlags() & GOD_UNLIMITED_SHOUTS ){
        dwNextShout = 0;
    }else{
        // If player has a shout-delay specific flag.
        DWORD dwShoutDelay = self->ViewFlag( __FLAG_SHOUT );
        if( dwShoutDelay != 0 ){
            dwNextShout = dwShoutDelay SECONDS TDELAY;
        }else{
            TRACE( "\r\nShoutDelay=%u.", CAutoConfig::GetIntValue( T4C_KEY CHARACTER_KEY, "ShoutDelay", HKEY_LOCAL_MACHINE ) );
            dwNextShout = CAutoConfig::GetIntValue( T4C_KEY CHARACTER_KEY, "ShoutDelay", HKEY_LOCAL_MACHINE ) SECONDS TDELAY;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::Logon( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  When a character logs on.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
     // Add player entry to OnlineUser table.
    char szAccount[ 1024 ];
    QuotedAccount( szAccount, GetAccount() );
    
    CString csQuery;
    TemplateList< SQL_REQUEST > *lptlSQLRequests = new TemplateList< SQL_REQUEST >;

    csQuery.Format( "UPDATE OnlineUsers SET PlayerName='%s' WHERE AccountName='%s'", //BLBLBL 05/01/2011 retrait de top
        (LPCTSTR)self->GetTrueName(),
        szAccount
    );
    ADD_QUERY;

    ODBCUsers.SendBatchRequest( lptlSQLRequests, NULL, NULL, "ODBCUsers" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::Logoff( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Callback called when player is logged off.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{    
    // Remove character from its current group.
    if( self->GetGroup() != NULL ){
        self->GetGroup()->Dismiss( self );
    }

	// Cancel any running trade
	self->GetTradeMgr2()->Cancel();

    // Remove player entry from OnlineUser table.
    char szAccount[ 1024 ];
    QuotedAccount( szAccount, GetAccount() );

    CString csQuery;
    TemplateList< SQL_REQUEST > *lptlSQLRequests = new TemplateList< SQL_REQUEST >;
 	

    csQuery.Format( "DELETE FROM OnlineUsers WHERE AccountName='%s'", szAccount );//BLBLBL 05/01/2011
    ADD_QUERY;

    ODBCUsers.SendBatchRequest( lptlSQLRequests, NULL, NULL, "ODBCUsers" );
}

namespace{


	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
    const INT MaxPageTime = 3 SECONDS;
    const INT MaxPageCountPerMaxPageTime = 2;



};

//////////////////////////////////////////////////////////////////////////////////////////
bool Players::CanPage( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Determines if the player can page right now.
// 
// Return: bool, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // If no-paging time has expired.
    if( dwNextPageTime <= TFCMAIN::GetRound() ){
        // Decrease the page count.
        // Remove the quantity of 'MaxPageTime' found between the current time and the set NextPageTime.
        // +1 insures that even if the page time just expired, the page count will decrease.        
        DWORD dwCountDecrease = ( ( TFCMAIN::GetRound() - dwNextPageTime ) / MaxPageTime ) + 1;
                
        // If the next page count is bigger then the desired decrease.
        if( dwNextPageCount > dwCountDecrease ){
            // Decrease 
            dwNextPageCount -= dwCountDecrease;
        }else{
            // Otherwise the new page count is 0.
            dwNextPageCount = 0;
        }
    }
    
    // If the page count is smaller than the maximum allowed pages in a given time.
    if( dwNextPageCount < MaxPageCountPerMaxPageTime || GetGodFlags() & GOD_UNLIMITED_SHOUTS ){       
        // Player can page.
        return true;
    }

    // Player cannot page.
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::PageNotification( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Notifies the player structure that the player just paged.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Reset the next page time.
    dwNextPageTime = MaxPageTime TDELAY;

    // Augment the page count.
    dwNextPageCount++;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool Players::AccountLogged
//////////////////////////////////////////////////////////////////////////////////////////
//  Determines if a player is already logged on, on another server perhaps.
// 
(
 const CString &csAccountName, // The name to verify
 LPCSTR szIP                    // Textual IP adress of player.
)
// Return: bool, true if the player is already logged on.
//////////////////////////////////////////////////////////////////////////////////////////
{
	ODBCUsers.Lock();
	TFormat format;  
    bool boLogged = false;
    if( !ODBCUsers.SendRequest( format(
                "INSERT INTO OnlineUsers(MachineName,AccountName,PlayerName,IPaddr) VALUES ('%s','%s','<%s>','%s')",
                (LPCTSTR)theApp.csMachineName,
                (LPCTSTR)csAccountName,
                _STR( 2846, _DEFAULT_LNG ),
                szIP
            ), false ) )
	{
        // He is logged somewhere (this or another server).
        boLogged = true;
    }
	ODBCUsers.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

    ODBCUsers.Unlock();

    return boLogged;
	//on accept les multi connexion

	
    ODBCUsers.Lock();
	//BLBL : check si le joueur est déjà connecté pour pas générer d'erreur SQL :
	CString csQuery;
#ifdef MSSQLSERVER
	csQuery.Format( "SELECT TOP 1 AccountName FROM OnlineUsers WHERE AccountName='%s'", (LPCTSTR)csAccountName ); //BLBBL 05/01/2011
#else
	csQuery.Format( "SELECT AccountName FROM OnlineUsers WHERE AccountName='%s' LIMIT 1", (LPCTSTR)csAccountName ); //BLBBL 05/01/2011
#endif
	ODBCUsers.SendRequest( csQuery );	

	if ( ODBCUsers.Fetch() ) {
	
		boLogged=true;
	
	}else // Send a request to fetch the user from the OnlineUsers table
		  
		  ODBCUsers.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close;//on "repositionne le curseur" (truc bizarre de MSSQL si on fait 2 requetes qui se suivent)          
		  if( !ODBCUsers.SendRequest( format(
                "INSERT INTO OnlineUsers(MachineName,AccountName,PlayerName,IPaddr) VALUES ('%s','%s','<%s>','%s')",
                (LPCTSTR)theApp.csMachineName,
                (LPCTSTR)csAccountName,
                _STR( 2846, _DEFAULT_LNG ),
                szIP
            ), false ) )
	{
        // He is logged somewhere (this or another server).
        boLogged = true;
    }

    // Otherwise the player isn't there.
    ODBCUsers.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

    ODBCUsers.Unlock();

    return boLogged;
}

/////////////////////////////////////////
// How many connections from this IP?
int Players::IPLogged( LPCSTR szIP )
{
	CString csQuery;
	int nConnection = 0;

	csQuery.Format( "SELECT AccountName FROM OnlineUsers WHERE IPaddr='%s'", szIP );

	ODBCUsers.Lock();

	ODBCUsers.SendRequest( csQuery );
	
	// Count the connections
	while( ODBCUsers.Fetch() )
	{
		nConnection++;				
	}

	ODBCUsers.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

	ODBCUsers.Unlock();

	return nConnection;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool Players::NameExists
//////////////////////////////////////////////////////////////////////////////////////////
//  Determines if a player name exists in the player database.
// 
(
 const string &name // The name of the player.
)
// Return: bool, true if the name exists, false otherwise.
//////////////////////////////////////////////////////////////////////////////////////////
{
    TFormat format;
    bool exists = true;
    
    ODBCUsers.Lock();
    
    // Send a request to fetch the user name from PlayingCharacters.
    if( ODBCUsers.SendRequest(
        format(
            "SELECT PlayerName FROM PlayingCharacters WHERE PlayerName='%s'",
            name.c_str()
        )
     ) ){
        // If no field containing this name could be fetched.
        if( !ODBCUsers.Fetch() ){        
            exists = false;            
        }
        ODBCUsers.CloseCursor();
    }

    ODBCUsers.Unlock();

    return exists;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Players::AccountLoggonFailed
//////////////////////////////////////////////////////////////////////////////////////////
//  Called to notify the database that the account failed to authenticate.
// 
(
 const CString &csAccountName // The account name.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CString csQuery;
    TemplateList< SQL_REQUEST > *lptlSQLRequests = new TemplateList< SQL_REQUEST >;
 	

    csQuery.Format( "DELETE FROM OnlineUsers WHERE AccountName='%s'", csAccountName ); //BLBLBL 05/01/2011
    ADD_QUERY;

    ODBCUsers.SendBatchRequest( lptlSQLRequests, NULL, NULL, "ODBCUsers" );
}

//////////////////////////////////////////////////////////////////////////////////////////
bool Players::AccountHeartBeat()
//////////////////////////////////////////////////////////////////////////////////////////
//  If any no player are logged on, send a SQL dummy messages as heart beat on this connection.
//  Return bool: True if the SQL dummy messages succed.
//////////////////////////////////////////////////////////////////////////////////////////
{
	// If its an ODBC authentification
	if( theApp.sAuth.bAuthentificationMethod == ODBC_AUTH ){
		// Get the ODBC authentification connection.
		cODBCMage *lpODBCAuth = TFCMessagesHandler::GetODBCAuth();

		TemplateList< SQL_REQUEST > *lptlSQLRequests = new TemplateList< SQL_REQUEST >;
		CString csQuery;
		// Send a dummy messages on auth table in the database.
        csQuery.Format( "UPDATE %s SET %s='%s' WHERE %s='%s'",
            (LPCTSTR)theApp.sAuth.csODBC_Table,
            (LPCTSTR)theApp.sAuth.csODBC_Account,
            "DBHeartBeat",
            (LPCTSTR)theApp.sAuth.csODBC_Account,
            "DBHeartBeat"
        );

		ADD_QUERY;

		// Send batch request to ODBC authentification database.
		lpODBCAuth->SendBatchRequest( lptlSQLRequests, NULL, NULL, "ODBCAuth" );

		return true;
	}else{
		return false;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////
CString Players::GetRealm() const
{
    return m_Realm;
}

//////////////////////////////////////////////////////////////////////////////////////////
CString Players::GetFullAccountName() const
{
    if( theApp.sAuth.m_StripRealmPartOfAccount && !m_Realm.IsEmpty() ){
        CString fullName( m_Account );
        fullName += "@";
        fullName += m_Realm;
        return fullName;
    }
    return m_Account;
}