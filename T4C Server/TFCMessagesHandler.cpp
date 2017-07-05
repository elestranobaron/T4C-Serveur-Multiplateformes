// TFCMessagesHandler.cpp: implementation of the TFCMessagesHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "TFC ServerDlg.h"
#include "TFCMessagesHandler.h"
#include "TFC_MAIN.h"
//#include "Player Messages Threads.h"
#include "Broadcast.h"
#include "TFCServerGP.h"
#include <eh.h>
#include "Random.h"
#include "TFCMessagesHandler.h"
#include "SkillListing.h"
#include "AsyncFuncQueue.h"
#include "SysopCmd.h"
#include "IntlText.h"
#include "RegKeyHandler.h"
#include "PacketManager.h"
#include "PlayerManager.h"
#include "AutoConfig.h"
#include "Format.h"
#include "PacketManager.h"
#include "QuestFlagsListing.h"
#include "FormatPlayerName.h"
#include "WeatherEffect.h"
#include "TextFilter.h"
#include "BlockingListing.h"//BLBLBL for antiplug use with type of blocks (no antiplug in safe haven)

#define MAX_PLAYERS     75

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAX_USER_KEY    "UserMax"

// Uncomment to use VOP capabilities
//#define NO_AUTHENTIFICATION
//#define ENCRYPTED_PASSWORD

#ifndef NO_AUTHENTIFICATION
//#include "VopCom.h"
#endif

////////////////////////////////////////////////////////////////////////////////////////////
// Externs..
extern TFC_MAIN *TFCServer;
extern CTFCServerDlg *MainDlg;
extern CTFCServerApp theApp;
//extern TemplateList <Players> UsersList;
extern Random rnd;

extern TFC_MAIN *TFCServer;
extern CTFCServerDlg *MainDlg;
//////////////////////////////////////////////////////////////////////////////////////////

//LPPACKET_FUNC   TFCMessagesHandler::FuncTable[ RQ_QUANTITY ];
//cODBCMage       TFCMessagesHandler::ODBCAuth;

TemplateList <LOCAL_USER> TFCMessagesHandler::tlLocalUsers;
DWORD                     TFCMessagesHandler::dwMaxLocalUsers;
DWORD                     TFCMessagesHandler::dwMaxRemoteUsers;


namespace{
    CString csMotD;
    CString csAccessRightDenialMsg;
};

#define RQ_HEADER           try{
#define RQ_FOOTER( __rq )   }catch( ... ){\
                                _LOG_DEBUG\
                                    LOG_CRIT_ERRORS,\
                                    "Detected crash in RQ_"__rq\
                                LOG_\
                                _LOG_DEBUG\
                                    LOG_CRIT_ERRORS,\
                                    "Packet: [ %s ]",\
                                    (LPCTSTR)msg->GetDebugPacketString()\
                                LOG_\
                                throw;\
                            }

#define RQ_FOOTER_EX_START( __rq ) }catch( ... ){\
                                _LOG_DEBUG\
                                    LOG_CRIT_ERRORS,\
                                    "Detected crash in RQ_"__rq\
                                LOG_\
                                _LOG_DEBUG\
                                    LOG_CRIT_ERRORS,\
                                    "Packet: [ %s ]",\
                                    (LPCTSTR)msg->GetDebugPacketString()\
                                LOG_
#define RQ_FOOTER_EX_END        throw; }

typedef struct _ASYNC_PACKET_FUNC_PARAMS{
	TFCPacket	*msg;
	Players		*user;
	RQ_SIZE		rqRequestID;
} ASYNC_PACKET_FUNC_PARAMS, *LPASYNC_PACKET_FUNC_PARAMS;

#define FILL_ASYNC_PARAMS( __structure ) (__structure).msg = NULL;\
										 (__structure).user = user;\
										 (__structure).rqRequestID = rqRequestID;


struct PATCH_SERVER{
    CString csIP;
    WORD    wPort;
};
static struct WEBPATCH_SERVER : public CLock{
    CString csIP;
    CString csImagePath;
    CString csUserName;
    CString csPassword;
} webPatchServer;

static struct vvector : public vector< PATCH_SERVER >, CLock{} vPatchServers;

//////////////////////////////////////////////////////////////////////////////////////////
#define LOG_PACKET_ERROR( __packetErrText )	_LOG_DEBUG \
	LOG_DEBUG_LVL1,\
	"Error in "#__packetErrText\
	", packet was incomplete. Packet:[ %s]",\
	(LPCTSTR)msg->GetDebugPacketString()\
LOG_

// TFCMessagesHandler specific variables.
namespace{
    class PacketFunc{
    public:
        PacketFunc(){
            lpFunc = NULL;
        };

        void Setup( LPPACKET_FUNC lpPacketFunc ){
            lpFunc = lpPacketFunc;
            //iPacketPerfInstance = iPacketPerf;
        };

        LPPACKET_FUNC GetFunc(){ return lpFunc; };
        //CPrfData::INSTID GetInstID(){ return iPacketPerfInstance; };
    private:
        LPPACKET_FUNC lpFunc;
        //CPrfData::INSTID iPacketPerfInstance;
    };

    PacketFunc FuncTable[ RQ_QUANTITY ];    
    cODBCMage ODBCAuth;    


// Goa authentication functions
//typedef int  (*GoaCheckStringPtr)(char* lpszString,BOOL boTimestampIsThere);

//GoaCheckStringPtr   GoaCheckString = NULL;

};
//////////////////////////////////////////////////////////////////////////////////////////
//bool InitGoaAuth( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Initializes GOA authentication
// 
// Return: bool, true if initialization was correct
//////////////////////////////////////////////////////////////////////////////////////////
//{
/*    HINSTANCE hDLL = LoadLibrary( "GoaCrypt.dll" );

    if( hDLL == NULL ){
        DWORD err = GetLastError();
        _LOG_DEBUG
            LOG_CRIT_ERRORS,
            "Could not load GoaCrypt.dll (err %u)",
            err
        LOG_
        return false;
    }

    GoaCheckString = (GoaCheckStringPtr)GetProcAddress( hDLL, "CheckString" );
    if( GoaCheckString == NULL ){
        DWORD err = GetLastError();
        _LOG_DEBUG
            LOG_CRIT_ERRORS,
            "Could not get address of CheckString function in GoaCrypt.dll (err %u)",
            err
        LOG_
        return false;
    }
    return true;
	*/
//}


//////////////////////////////////////////////////////////////////////////////////////////
cODBCMage *TFCMessagesHandler::GetODBCAuth( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Return the ODBC connection.
// 
// Return: cODBCMage, the ODBC connection
//////////////////////////////////////////////////////////////////////////////////////////
{
    return &ODBCAuth;
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creates the TFC Message handler
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
//	RQ_SIZE i;

	//for( i = 0; i < RQ_QUANTITY; i++ ){
	//	FuncTable[ i ] = NULL;
	//}

    _LOG_DEBUG
        LOG_DEBUG_LVL4,
        "Registring messages handlers."
    LOG_
	
	RegisterFunction( RQFUNC_PlayerMove, RQ_MoveNorth );
	RegisterFunction( RQFUNC_PlayerMove, RQ_MoveNorthEast );
	RegisterFunction( RQFUNC_PlayerMove, RQ_MoveEast );
	RegisterFunction( RQFUNC_PlayerMove, RQ_MoveSouthEast );
	RegisterFunction( RQFUNC_PlayerMove, RQ_MoveSouth );
	RegisterFunction( RQFUNC_PlayerMove, RQ_MoveSouthWest );
	RegisterFunction( RQFUNC_PlayerMove, RQ_MoveWest );
	RegisterFunction( RQFUNC_PlayerMove, RQ_MoveNorthWest );
	RegisterFunction( RQFUNC_PlayerMove, RQ_GetPlayerPos );
	RegisterFunction( RQFUNC_Ack, RQ_Ack );
	RegisterFunction( RQFUNC_GetObject, RQ_GetObject );
	RegisterFunction( RQFUNC_DepositObject, RQ_DepositObject );
	RegisterFunction( RQFUNC_PutPlayerInGame, RQ_PutPlayerInGame );
	RegisterFunction( RQFUNC_RegisterAccount, RQ_RegisterAccount );
	RegisterFunction( RQFUNC_DeletePlayer, RQ_DeletePlayer );
	RegisterFunction( RQFUNC_SendPeriphericObjects, RQ_SendPeriphericObjects );
	RegisterFunction( RQFUNC_GodCreateObject, RQ_GodCreateObject );
	RegisterFunction( RQFUNC_ViewBackpack, RQ_ViewBackpack );
	RegisterFunction( RQFUNC_ViewEquipped, RQ_ViewEquiped );
	RegisterFunction( RQFUNC_ExitGame, RQ_ExitGame );
	RegisterFunction( RQFUNC_EquipObject, RQ_EquipObject );
	RegisterFunction( RQFUNC_UnequipObject, RQ_UnequipObject );
	RegisterFunction( RQFUNC_UseObject, RQ_UseObject );
	RegisterFunction( RQFUNC_Attack, RQ_Attack );
	RegisterFunction( RQFUNC_CreatePlayer, RQ_CreatePlayer );
	RegisterFunction( RQFUNC_GetPersonnalPClist, RQ_GetPersonnalPClist );
	RegisterFunction( RQFUNC_IndirectTalk, RQ_IndirectTalk );
	RegisterFunction( RQFUNC_Shout, RQ_Shout );
	RegisterFunction( RQFUNC_Page, RQ_Page );
	RegisterFunction( RQFUNC_DirectedTalk, RQ_DirectedTalk );
	RegisterFunction( RQFUNC_Reroll, RQ_Reroll );
	RegisterFunction( RQFUNC_CastSpell, RQ_CastSpell );
	RegisterFunction( RQFUNC_HPchanged, RQ_HPchanged );
	RegisterFunction( RQFUNC_BroadcastTextChange, RQ_BroadcastTextChange );
	RegisterFunction( RQFUNC_GetUnitName, RQ_GetUnitName );
	RegisterFunction( RQFUNC_BreakConversation, RQ_BreakConversation );
	RegisterFunction( RQFUNC_ReturnToMenu, RQ_ReturnToMenu );
	RegisterFunction( RQFUNC_GetSkillList, RQ_GetSkillList );
	RegisterFunction( RQFUNC_SendTrainSkillList, RQ_SendTrainSkillList );
	RegisterFunction( RQFUNC_UseSkill, RQ_UseSkill );
	RegisterFunction( RQFUNC_GetStatus, RQ_GetStatus );
	RegisterFunction( RQFUNC_XPchanged, RQ_XPchanged );
	RegisterFunction( RQFUNC_GetTime, RQ_GetTime );
	RegisterFunction( RQFUNC_FromPreInGameToInGame, RQ_FromPreInGameToInGame );
	RegisterFunction( RQFUNC_EnterChatterChannel, RQ_EnterChatterChannel );
	RegisterFunction( RQFUNC_SendChatterMessage, RQ_SendChatterMessage );
	RegisterFunction( RQFUNC_GetChatterUserList, RQ_GetChatterUserList );
	RegisterFunction( RQFUNC_GetOnlinePlayerList, RQ_GetOnlinePlayerList );
	RegisterFunction( RQFUNC_GetSkillStatPoints, RQ_GetSkillStatPoints );
	RegisterFunction( RQFUNC_GoldChange, RQ_GoldChange );
	RegisterFunction( RQFUNC_ViewGroundItemIndentContent, RQ_ViewGroundItemIndentContent );
	RegisterFunction( RQFUNC_SendTeachSkillList, RQ_SendTeachSkillList );
	RegisterFunction( RQFUNC_SendBuyItemList, RQ_SendBuyItemList );
	RegisterFunction( RQFUNC_SendSellItemList, RQ_SendSellItemList );
	RegisterFunction( RQFUNC_SendStatTrain, RQ_SendStatTrain );
	RegisterFunction( RQFUNC_QueryItemName, RQ_QueryItemName );
	RegisterFunction( RQFUNC_GetNearItems, RQ_GetNearItems );
	RegisterFunction( RQFUNC_SendSpellList, RQ_SendSpellList );
    RegisterFunction( RQFUNC_QueryServerVersion, RQ_QueryServerVersion );
    RegisterFunction( RQFUNC_MessageOfDay, RQ_MessageOfDay );
    RegisterFunction( RQFUNC_PuppetInformation, RQ_PuppetInformation );    
    RegisterFunction( RQFUNC_QueryUnitExistence, RQ_QueryUnitExistence );
    RegisterFunction( RQFUNC_UseItemByAppearance, RQ_UseItemByAppearance );
    RegisterFunction( RQFUNC_RemoveFromChatterChannel, RQ_RemoveFromChatterChannel );
    RegisterFunction( RQFUNC_GetChatterChannelList, RQ_GetChatterChannelList );
    RegisterFunction( RQFUNC_UpdateGroupMembers, RQ_UpdateGroupMembers );
    RegisterFunction( RQFUNC_UpdateGroupInviteList, RQ_UpdateGroupInviteList );
    RegisterFunction( RQFUNC_GroupInvite, RQ_GroupInvite );
    RegisterFunction( RQFUNC_GroupJoin, RQ_GroupJoin );
    RegisterFunction( RQFUNC_GroupLeave, RQ_GroupLeave );
    RegisterFunction( RQFUNC_GroupKick, RQ_GroupKick );
    RegisterFunction( RQFUNC_JunkItems, RQ_JunkItems );
    RegisterFunction( RQFUNC_ToggleChatterListening, RQ_ToggleChatterListening );
    RegisterFunction( RQFUNC_GroupToggleAutoSplit, RQ_GroupToggleAutoSplit );
    RegisterFunction( RQFUNC_TogglePage, RQ_TogglePage );
    RegisterFunction( RQFUNC_QueryNameExistence, RQ_QueryNameExistence );
    RegisterFunction( RQFUNC_QueryPatchServerInfo, RQ_QueryPatchServerInfo );
    RegisterFunction( RQFUNC_Rob, RQ_Rob );
    RegisterFunction( RQFUNC_AuthenticateServerVersion, RQ_AuthenticateServerVersion );
	RegisterFunction( RQFUNC_ChestAddItemFromBackpack, RQ_ChestAddItemFromBackpack );
	RegisterFunction( RQFUNC_ChestRemoveItemToBackpack, RQ_ChestRemoveItemToBackpack );
	RegisterFunction( RQFUNC_TradeInvite, RQ_TradeInvite );
	RegisterFunction( RQFUNC_TradeCancel, RQ_TradeCancel );
	RegisterFunction( RQFUNC_TradeSetStatus, RQ_TradeSetStatus );
	RegisterFunction( RQFUNC_TradeAddItemFromBackpack, RQ_TradeAddItemFromBackpack );
	RegisterFunction( RQFUNC_TradeRemoveItemToBackpack, RQ_TradeRemoveItemToBackpack );
	RegisterFunction( RQFUNC_TradeClear, RQ_TradeClear );
	RegisterFunction( RQFUNC_QueryItemInfo, RQ_QueryItemInfo );
	RegisterFunction( RQFUNC_SafePlug, RQ_SafePlug );//BLBLBL new function for antiplug system
	// by Asteryh for pvp ranking
	RegisterFunction( RQFUNC_GetPvpRanking, RQ_GetPvpRanking );
    
    // Does the user use ODBC authentification?
    if( theApp.sAuth.bAuthentificationMethod == ODBC_AUTH ){
        _LOG_DEBUG
            LOG_DEBUG_LVL4,
            "Connecting to ODBC authentication database."
        LOG_

        // Create the ODBC interface.
        ODBCAuth.Connect( theApp.sAuth.csODBC_DSN, theApp.sAuth.csODBC_DBUser, theApp.sAuth.csODBC_DBPwd );
    }
    ODBCAuth.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close
    //ODBCAuth.ConnectOption( SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF );	

    _LOG_DEBUG
        LOG_DEBUG_LVL4,
        "Setting up auto-registry callback"
    LOG_

    CAutoConfig::AddRegUpdateCallback( MaxUserUpdate );

    // Get the 'max users' variables
    MaxUserUpdate();

#ifndef NO_VOP_ACCT

    /*if( theApp.sAuth.bAuthentificationMethod == VOP_AUTH ){
        
        CString step = "Instantiating COM object";
        try{        
            IRadClntPtr iVop( "VOPCOM.RadClnt" );

            step = "Setting license key";
            iVop->LicenseKey = VOP_LICENSE_KEY;

            step = "Setting up logging";
            iVop->LogFile = (LPCTSTR)theApp.sAuth.vopLogFile;
            iVop->LogLevels = theApp.sAuth.vopLogLevels;            
    
            step = "Opening request";
            // Initialize VOP accounting service.
            long requestID = iVop->OpenRequest(
                "system",
                "",
                (LPCTSTR)theApp.sAuth.csVOP_NASIP,
                theApp.sAuth.csVOP_NASPort,
                (LPCTSTR)theApp.sAuth.csVOP_Secret,
                theApp.sAuth.csWGFlag,
                "T4C Server",
                VOPCOM_ACCT_REQUEST
                );
            
            step = "Setting account options";
            const ACCT_ON = 7;
            // Set accounting options.
            iVop->SetAcctOptions(
                requestID,
                ACCT_ON,
                0,
                theApp.szServerAcctID
                );
            
            {
                const VOP_SERVICE = 7;
                const VOP_ID  = 0x221516L;
                
                _variant_t varAttr;
                
                varAttr = _bstr_t( (LPCTSTR)_T("T4C Server") );
                // Add VOP Service so that VOP Acct works
                iVop->AddAttributeEx( requestID, VOP_SERVICE, VOP_ID, &varAttr );                
            }

            _LOG_DEBUG
                LOG_DEBUG_LVL4,
                "Sending radius ACCT_ON packet."
            LOG_
    
            step = "Sending request";
            iVop->SendRequest(
		        requestID,
		        (LPCTSTR)theApp.sAuth.csAcctIP,
		        theApp.sAuth.wAcctPort,
		        0
	        );

            _LOG_DEBUG
                LOG_DEBUG_LVL4,
                "Close radius request."
            LOG_

            step = "Closing request";
            iVop->CloseRequest( requestID );
        }catch( _com_error e ){
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "There was a COM error sending radius accounting request (ACCT_ON-%s): %s",
                (LPCTSTR)step,
                e.ErrorMessage()
            LOG_
        }
    }*/
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::Destroy( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Destroys the TFCMessageHandler
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
#ifndef NO_VOP_ACCT
    /*if( theApp.sAuth.bAuthentificationMethod == VOP_AUTH ){
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
                "system",
                "",
                (LPCTSTR)theApp.sAuth.csVOP_NASIP,
                theApp.sAuth.csVOP_NASPort,
                (LPCTSTR)theApp.sAuth.csVOP_Secret,
                theApp.sAuth.csWGFlag,
                "T4C Server",
                VOPCOM_ACCT_REQUEST
                );
            
            step = "Setting accounting options";
            const ACCT_OFF = 8;
            // Set accounting options.
            iVop->SetAcctOptions(
                requestID,
                ACCT_OFF,
                0,
                theApp.szServerAcctID
                );
            
            {
                const VOP_SERVICE = 7;
                const VOP_ID  = 0x221516L;
                
                _variant_t varAttr;
                
                varAttr = _bstr_t( (LPCTSTR)_T("T4C Server") );
                // Add VOP Service so that VOP Acct works
                iVop->AddAttributeEx( requestID, VOP_SERVICE, VOP_ID, &varAttr );                
            }

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
                "There was a COM error sending radius accounting request (ACCT_OFF-%s): %s",
                (LPCTSTR)step,
                e.ErrorMessage()
            LOG_                
        }
    }*/
#endif
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::MaxUserUpdate( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Called when the there is a registry update and we must update the max users.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    LPLOCAL_USER lpLocalUser;
    RegKeyHandler regKey;
    regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY MAX_USER_KEY );
    
    tlLocalUsers.Lock();

    // Destroy the current local user list.
    tlLocalUsers.AnnihilateList();

    dwMaxLocalUsers  = regKey.GetProfileInt( "LocalUserMax",  65536 );
    dwMaxRemoteUsers = regKey.GetProfileInt( "RemoteUserMax", 65536 );

    int i = 1;
    // Fetch all local ip definitions.
    CString csIP = regKey.GetProfileString( "LocalUserIP1", "$NULL$" );
    while( csIP != "$NULL$" ){
        lpLocalUser = new LOCAL_USER;

        lpLocalUser->dwIP      = inet_addr( (LPCTSTR)csIP );
        TRACE( "\r\nFoundIP=%u", lpLocalUser->dwIP );
        if( lpLocalUser->dwIP != 0xFFFFFFFF ){        
            csIP.Format( "LocalUserNetmask%u", i );
                
            lpLocalUser->dwNetmask = inet_addr( regKey.GetProfileString( (LPCTSTR)csIP, "255.255.255.0" ) );
            if( lpLocalUser->dwNetmask != 0xFFFFFFFF ){
                TRACE( "\r\nFoundNetmask=%d", lpLocalUser->dwNetmask );

                // Add the local user definition.
                tlLocalUsers.AddToTail( lpLocalUser );
            }else{
                delete lpLocalUser;
            }
        }else{
            delete lpLocalUser;
        }
        csIP.Format( "LocalUserIP%u", ++i );
        csIP = regKey.GetProfileString( (LPCTSTR)csIP, "$NULL$" );
    }

    regKey.Close();
    regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY PATCH_KEY );

    tlLocalUsers.Unlock();

    //////////////////////////////////////////////////////////////////////////////////////////    
    vPatchServers.Lock();

    // Flush old patch server listing
    vPatchServers.erase( vPatchServers.begin(), vPatchServers.end() );

    i = 1;
    // Fetch all local ip definitions.
    csIP = regKey.GetProfileString( "OtherServer1_IP", "$NULL$" );
    while( csIP != "$NULL$" ){
        PATCH_SERVER pPatch;

        pPatch.csIP = (LPCTSTR)csIP;               
        
        csIP.Format( "OtherServer%u_Port", i );                
        pPatch.wPort = static_cast< WORD >( regKey.GetProfileInt( (LPCTSTR)csIP, 11679 ) );

        TRACE( "\r\nFound patch server at %sp%u", (LPCTSTR)pPatch.csIP, pPatch.wPort );

        vPatchServers.push_back( pPatch );
        
        csIP.Format( "OtherServer%u_IP", ++i );      
        csIP = regKey.GetProfileString( (LPCTSTR)csIP, "$NULL$" );
    }

    vPatchServers.Unlock();

    //////////////////////////////////////////////////////////////////////////////////////////
    // New web patch.
    webPatchServer.Lock();

    // Fetch all local ip definitions.    
    webPatchServer.csIP = regKey.GetProfileString( "WebPatch_URL", "" );                
    webPatchServer.csImagePath = regKey.GetProfileString( "WebPatch_ImageFile", "" );
    webPatchServer.csUserName = regKey.GetProfileString( "WebPatch_User", "" );
    webPatchServer.csPassword = regKey.GetProfileString( "WebPatch_Pwd", "" );
        
    webPatchServer.Unlock();

    {
        RegKeyHandler regKey;
        regKey.Open( HKEY_LOCAL_MACHINE, "SOFTWARE\\Vircom\\The 4th Coming Server\\Paths" );

        csMotD = regKey.GetProfileString( "MOTD", "\\INVALID\\" );
    }

    {
        RegKeyHandler regKey;
        regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY AUTH_KEY );
        
        csAccessRightDenialMsg = regKey.GetProfileString( "ACCESS_RIGHT_DENIAL_MSG", "You do not have access rights to play The 4th Coming." );
    }

    regKey.Close();
    regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY CHARACTER_KEY );

    ChatterChannels &chatter =  CPlayerManager::GetChatter();
    chatter.Lock();
    
    chatter.ClearSystemChannels();
    
    CString key;
    i = 2;
    string channelId = regKey.GetProfileString( "PublicChannel1", "$NULL$" );
    while( channelId != "$NULL$" ){
        chatter.AddSystemChannel( channelId );

        key.Format( "PublicChannel%u", i );
        i++;
        channelId = regKey.GetProfileString( key, "$NULL$" );
    }

    CPlayerManager::RefreshSystemChannels();

    chatter.Unlock();
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RegisterFunction
//////////////////////////////////////////////////////////////////////////////////////////
// Registers a function in the jump table
// 
(
 LPPACKET_FUNC lpFunc,	// Function associated with request
 RQ_SIZE rqRequestID	// Request type
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( rqRequestID < RQ_QUANTITY ){
        try{
            FuncTable[ rqRequestID ].Setup( lpFunc/*CPrfData::GetInstance()->AddInstance( PRFOBJ_PACKETS, wFormat( L"%u", rqRequestID ) )*/ );
        }catch(...){
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "Crashed setting up packet function table. Probable cause: performance counters initialization."
            LOG_
            throw;
        }
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::DispatchPacket
//////////////////////////////////////////////////////////////////////////////////////////
// Dispatches a message to a specific packet handler
// 
(
	PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{		
	TFormat format;
    
    // send the packet
	BOOL boInvalid = FALSE;
	TRACE( "\r\n** Received packet ID %u, packet is ", rqRequestID );
	if( rqRequestID > 0 && rqRequestID < RQ_QUANTITY){
		if( FuncTable[ rqRequestID ].GetFunc() != NULL ){
			TRACE( "valid." );
            try{

/*				try{ //BLBLBL 6 avril 2009 mise en commentaire de ces trucs qui font crasher.
					// Call the appropriate function
					DWORD dwTimeBefore = GetRunTime();
                
                
					DebugLogger::GetInstance().LogString( format( "Start-analyzing packet %u.", rqRequestID ), true );


					//CPrfData::GetInstance()->GetCtr32( PRFPCK_RECV_PACKET_TYPE_SEC, FuncTable[ rqRequestID ].GetInstID() )++;
					// Increment the packet specific received counter.
					CPacketManager::IncRecvPacketType( rqRequestID );

				}catch(...){
					_LOG_DEBUG
						LOG_CRIT_ERRORS,
						"Detected crash in TFCMessagesHandler::DispatchPacket, requestID %u, before calling request's function!.", 
						rqRequestID
					LOG_
					throw;
				}*/
				
				try{

					( FuncTable[ rqRequestID ].GetFunc() )( PACKET_FUNC_PARAM );
				}catch(...){
					_LOG_DEBUG
						LOG_CRIT_ERRORS,
						"Detected crash in TFCMessagesHandler::DispatchPacket, requestID %u, while calling request's function!.", 
						rqRequestID
					LOG_
					throw;
				}

			/*	try{
					DebugLogger::GetInstance().LogString( format( "Stopped-analyzing packet %u.", rqRequestID ), true );

					DWORD dwTimeAfter = GetRunTime();
				}catch(...){
					_LOG_DEBUG
						LOG_CRIT_ERRORS,
						"Detected crash in TFCMessagesHandler::DispatchPacket, requestID %u, after calling request's function!.", 
						rqRequestID
					LOG_
					throw;
				}*/

            }catch(...){
                _LOG_DEBUG
                    LOG_CRIT_ERRORS,
                    "Detected crash in TFCMessagesHandler, request %u.", 
                    rqRequestID
                LOG_
                if( user != NULL ){
                    _LOG_DEBUG
                        LOG_CRIT_ERRORS,
                        "Happened while handling account %s.",
                        (LPCTSTR)user->GetFullAccountName()
                    LOG_
                    if( user->in_game ){
                        _LOG_DEBUG
                            LOG_CRIT_ERRORS,
                            "User was in game under character %s (ID %u).",
                            (LPCTSTR)user->self->GetTrueName()
                        LOG_
                    }
                }

                throw;
            }
		}else{
			boInvalid = TRUE;
		}
	}else{
		boInvalid = TRUE;
	}

	if( boInvalid ){
        if( user != NULL ){
		    if( user->registred ){
			    if( user->in_game ){
				    _LOG_DEBUG LOG_DEBUG_LVL1, 
					    "Received an unregistered packet ID %u from user %s "
					    "playing character %s, IP %s.", 
					    rqRequestID,
					    (LPCTSTR)user->GetFullAccountName(),
					    (LPCTSTR)user->self->GetTrueName(),
					    (LPCTSTR)user->GetIP()
				    LOG_
			    }else{
				    _LOG_DEBUG LOG_DEBUG_LVL1, 
					    "Received an unregistered packet ID %u from user %s"
					    ", IP %s.", 
					    rqRequestID,
					    (LPCTSTR)user->GetFullAccountName(),
					    (LPCTSTR)user->GetIP()
				    LOG_
			    }            
		    }else{
			    _LOG_DEBUG LOG_DEBUG_LVL1, 
				    "Received an unregistered packet ID %u"
				    ", from IP %s.", 
				    rqRequestID,
				    (LPCTSTR)user->GetIP()
			    LOG_						
		    }
        }
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_Ack
//////////////////////////////////////////////////////////////////////////////////////////
// Ack function
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{//BLBLBL elle ne fait rien cette fonction de traitement des acks ?


}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_PlayerMove
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQ_PlayerMove
//
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    const INT MoveExhaust = 0;//BLBLBL 200=>400=>200 remis à 200 sinon on a un accoup au démarrage d'une séquence de marche // steph ajout de INT // steph 0 au lieu de 200 MILLISECONDS

    TFCPacket sending;

	
	if( rqRequestID == RQ_GetPlayerPos){

		WorldPos wlPos = user->self->GetWL();
		sending << (RQ_SIZE)RQ_GetPlayerPos; // GetPlayerPos request
		sending << (short)wlPos.X;
		sending << (short)wlPos.Y;
		sending << (short)wlPos.world;					

		// we send the packet in the player's box	
		user->self->SendPlayerMessage( sending );

    }else if(user->in_game ){
		
		user->Lock();//BLBLBL tentative d'ajouter un lock
        user->self->StopAutoCombat();

//		if( user->self->ViewFlag( __FLAG_BERSERK ) == 0 ){
            
			char searchway;
			WorldPos tmp;
			WorldPos saved_pos = user->self->GetWL();

					EXHAUST newExhaust = user->self->GetExhaust();

					// If user isn't move exhaust
					// Or if user sends an advanced move exhaust.
					//if( newExhaust.move <= TFCMAIN::GetRound() || ( newExhaust.boWalking && newExhaust.move - TFCMAIN::GetRound() <= MoveExhaust ) ){
					if( newExhaust.move <= TFCMAIN::GetRound() /*|| ( newExhaust.boWalking && newExhaust.move - TFCMAIN::GetRound() <= MoveExhaust )*/ ){//BLBL à mon avis c'est ptet cette condition qui laisse passer trop de paquets de mouvements.
                
						switch( rqRequestID )
						{
							case RQ_MoveNorth:               // NORTH
									tmp = user->self->MoveUnit(DIR::north, false, true, true );
									searchway = DIR::north;
									break;
							case RQ_MoveNorthEast:               // NORTHEAST
									tmp = user->self->MoveUnit(DIR::northeast, false, true, true );
									searchway = DIR::northeast; 
									break;
							case RQ_MoveEast:                // EAST
									tmp = user->self->MoveUnit(DIR::east, false, true, true );
									searchway = DIR::east;
									break;
							case RQ_MoveSouthEast:				   // SOUTHEAST
									tmp = user->self->MoveUnit(DIR::southeast, false, true, true );
									searchway = DIR::southeast;
									break;
							case RQ_MoveSouth:                // SOUTH
									tmp = user->self->MoveUnit(DIR::south, false, true, true );
									searchway = DIR::south;
									break;
							case RQ_MoveSouthWest:                // SOUTHWEST
									tmp = user->self->MoveUnit(DIR::southwest, false, true, true );
									searchway = DIR::southwest;
									break;
							case RQ_MoveWest:		           // WEST
									tmp = user->self->MoveUnit(DIR::west, false, true, true ); 
									searchway = DIR::west;
									break;
							case RQ_MoveNorthWest:                // NORTHWEST						
									tmp = user->self->MoveUnit(DIR::northwest, false, true, true );
									searchway = DIR::northwest;
									break;
							case RQ_GetPlayerPos:
									tmp = user->self->GetWL();
									searchway = -1;
									break;
						}
             			
						newExhaust.move = TFCMAIN::GetRound() + MoveExhaust;
						user->self->SetExhaust(newExhaust);

					}else{ 			                
						// If user is exhausted, send its current position.
						tmp = user->self->GetWL();
                
						
						// If player is more than 2 seconds exhaust.
						if( newExhaust.move >= TFCMAIN::GetRound() + 2 SECONDS ){
							// Send a system message telling the player that he's exhaust.
							// This might flood a player with these messages if he keeps his finger on the move button.
							user->self->SendSystemMessage( _STR( 2776, user->self->GetLang() ) );
							user->MoveList.clear();//si le joueur est exhausté on vide sa liste de mouvements

						}   
						
						//on ne mémorise les déplacements qui arrivent que si le joueur n'est pas exhausté :
						if (user->MoveList.size()<3 &&  newExhaust.move < TFCMAIN::GetRound() /* + 200 MILLISECONDS // steph désactivation */) {
							//user->Lock();apparement cause un pb de RST (flag qui s'attribue plus bien)
							user->MoveList.push_back(rqRequestID);//BLBL on stocke la direction qui a foiré
							//user->Unlock();apparement cause un pb de RST (flag qui s'attribue plus bien)
						}							
						
					}

							
					WorldMap *world = TFCMAIN::GetWorld(tmp.world);

					// Then send the peripheric object to the person who moved					
					if( ( tmp.X != saved_pos.X || tmp.Y != saved_pos.Y || tmp.world != saved_pos.world ) && world != NULL )
					{				
						// If there are peripheral objects to packet.
						if( world->packet_peripheral_units(tmp, 0, (DIR::MOVE)searchway, sending, user->self ) ){
							user->self->SendPlayerMessage( sending );
						}
                
						/*if( !user->self->LastMoveWasBroadcasted()// || 
							//user->self->GetPlayer()->GetGodFlags() & GOD_TRUE_INVISIBILITY ||
							//user->self->ViewFlag( __FLAG_INVISIBILITY ) != 0 
						 ){*///BLBLBL test de on broadcast tout le temps le mouvement 
							TFCPacket sending;
							sending << (RQ_SIZE)__EVENT_OBJECT_MOVED;
							sending << (short)user->self->GetWL().X;
							sending << (short)user->self->GetWL().Y;     // where the player has moved (is now)
							
							user->self->PacketUnitInformation( sending );                
	    					
							user->self->SendPlayerMessage( sending );
					   // }
					}		

		//	}//end if lastroundmove was not this round.
		//}//end if not berserk.

		user->Unlock();//BLBL tentative d'ajouter un lock ?
	}

    RQ_FOOTER_EX_START( "RQ_PlayerMove" )        
        _LOG_DEBUG
            LOG_CRIT_ERRORS,
            "Player was at ( %u, %u, %u ).",
            user->self->GetWL().X,
            user->self->GetWL().Y,
            user->self->GetWL().world
        LOG_
    RQ_FOOTER_EX_END
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GetObject
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQ_GetObject
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    TFCPacket sending;
	
    user->self->Lock();

	if(user->in_game) // If we can process this message..
	{
		try
		{				
			WorldMap *world = TFCMAIN::GetWorld( user->self->GetWL().world );
			
			if(world)
			{
				DWORD dwID = 0;
				WorldPos wlPos = { 0, 0, 0 };
				Unit *lpuGet;
				
				GET_WORD( wlPos.X );				
				GET_WORD( wlPos.Y );
				GET_LONG( dwID );

				TRACE( "\r\nGot unit %u at (%u, %u)", dwID, wlPos.X, wlPos.Y );
				
				lpuGet = world->FindNearUnit( wlPos, dwID );
                      
				if( lpuGet && lpuGet->GetType() == U_OBJECT )
				{
					wlPos = lpuGet->GetWL();
                    // If the user is able to hold this item.
					if( user->self->can_get( wlPos, static_cast< Objects *>( lpuGet ) ) )
					{
						// Remove the object from the world.						
                        world->remove_world_unit( wlPos, dwID );
					
                        char lpszID[ 256 ];
                        strcpy( lpszID, "UNDEFINED ID" );
                        Unit::GetNameFromID( lpuGet->GetStaticReference(), lpszID, U_OBJECT );                         
                        
						_LOG_ITEMS
                            LOG_MISC_1,
                            "Player %s got %u item %s ID( %s ) from ( %u, %u, %u ).",
                            (LPCTSTR)user->self->GetTrueName(),
							static_cast<Objects*>(lpuGet)->GetQty(),
                            (LPCTSTR)lpuGet->GetName( _DEFAULT_LNG ),
                            lpszID,
                            wlPos.X,
                            wlPos.Y,
                            user->self->GetWL().world
                        LOG_
						
						_LOG_DEBUG
                            LOG_MISC_1,
                            "Player %s got %u item %s ID( %s ) from ( %u, %u, %u ).",
                            (LPCTSTR)user->self->GetTrueName(),
							static_cast<Objects*>(lpuGet)->GetQty(),
                            (LPCTSTR)lpuGet->GetName( _DEFAULT_LNG ),
                            lpszID,
                            wlPos.X,
                            wlPos.Y,
                            user->self->GetWL().world
                        LOG_

                        
                        TRACE( "Reference=%u, type %u.", lpuGet->GetStaticReference(), lpuGet->GetType() );
						
                        Broadcast::BCObjectRemoved( wlPos, _DEFAULT_RANGE,
                            lpuGet->GetID()
                        );

                        // Give item to character.
                        user->self->GetUnit( wlPos, lpuGet );
					}
                }
				else
				{
                    TFCPacket sending;
                    sending << (RQ_SIZE)RQ_MissingUnit;
                    sending << (long)dwID;
                    sending << (RQ_SIZE)RQ_GetObject;
                    
                    user->self->SendPlayerMessage( sending );
					_LOG_DEBUG
                            LOG_MISC_1,
                            "Player %s COULD NOT get an item from ( %u, %u, %u ), item does not exist or is not U_OBJECT",
                            (LPCTSTR)user->self->GetTrueName(),                    
                            wlPos.X,
                            wlPos.Y,
                            user->self->GetWL().world
                    LOG_


                }
			}else{
						_LOG_DEBUG
                            LOG_MISC_1,
                            "Player %s COULD NOT GET item invalid world coordinate",
                            (LPCTSTR)user->self->GetTrueName()
                        LOG_
			
			}
		}catch(TFCPacketException *e)
		{
			LOG_PACKET_ERROR( "RQ_GetObject" )
			delete e;
		}
	}

    user->self->Unlock();

    RQ_FOOTER( "RQ_GetObject" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_DepositObject
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQ_FUNC
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    if( !user->in_game ){
        return;
    }
		
    WorldMap *wl = TFCMAIN::GetWorld( user->self->GetWL().world );
	if( wl == NULL ){
        return;
    }

    try{
		WorldPos where = {0,0,0};		
		
        DWORD itemId;
        DWORD qty;
		
        GET_WORD( where.X );
        GET_WORD( where.Y );
        GET_LONG( itemId );
        GET_LONG( qty );

		where.world = user->self->GetWL().world;

        Unit *obj = user->self->DropUnit( where, itemId, qty );
		
		if( obj != NULL ){
            obj->BroadcastPopup( where );
		}
    }catch(TFCPacketException *e){
	    LOG_PACKET_ERROR( "RQ_DepositObject" )
	    delete e;
    }

    RQ_FOOTER( "RQ_DepositObject" );
}

//////////////////////////////////////////////////////////////////////////////////////////
typedef struct _RQSTRUCT_PUT_PLAYER_IN_GAME{
	ASYNC_PACKET_FUNC_PARAMS sParams;
	CString csName;
} RQSTRUCT_PUT_PLAYER_IN_GAME, *LPRQSTRUCT_PUT_PLAYER_IN_GAME;


//////////////////////////////////////////////////////////////////////////////////////////
void AsyncRQFUNC_PutPlayerInGame
//////////////////////////////////////////////////////////////////////////////////////////
// Asynchronious function which will load the player.
// 
(
 LPVOID lpData // RQSTRUCT_PUT_PLAYER_IN_GAME
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	TFCPacket sending;
	LPRQSTRUCT_PUT_PLAYER_IN_GAME lpParams = (LPRQSTRUCT_PUT_PLAYER_IN_GAME)lpData;
	Players *user = lpParams->sParams.user;

    // Makes sure the user always unlocks its UseLock wherever this function exits.
    struct AutoExit{
        AutoExit( Players *theUser, LPRQSTRUCT_PUT_PLAYER_IN_GAME theParams ) 
            : user( theUser ), lpParams( theParams ){
        }
        // Auto cleans.
        ~AutoExit(){
            // Unlock user's UseLock
            user->UseUnlock(__FILE__, __LINE__);
            // Delete the parameters.
            delete lpParams;
        }
    private:
        Players *user;
        LPRQSTRUCT_PUT_PLAYER_IN_GAME lpParams;
    }// Auto object. 
     cAutoExit( user, lpParams );


    // If user is already in_game, then its CERTAIN that the user has knowledge of being in_game.
    if( user->in_game ){
        return;
    }
    
    //user->Lock();	
    _LOG_DEBUG
        LOG_DEBUG_LVL1,
        "Waiting for character %s memaddr( 0x%x ) to save.",
        lpParams->csName
    LOG_
	
	user->self->WaitForSaving();

	//	user->god_mode = TRUE; // TO BE REMOVED!!!!!!!!!!!
	sending << (RQ_SIZE)RQ_PutPlayerInGame; // request 13;

	char receive = 1;
    if( user->registred ){
        // If this packet wasn't already sent before.
        if( !user->boPreInGame ){
            _LOG_DEBUG
                LOG_DEBUG_LVL1,
                "Loading character %s data.",
                lpParams->csName
            LOG_
            // Load player.
            receive = user->self->load_character( lpParams->csName, user->GetAccount(), 0);
            _LOG_DEBUG
                LOG_DEBUG_LVL1,
                "Finished loading."
            LOG_
        }else{
            receive = 0;// Otherwise do as if we were loading the player.
        }
    }
	sending << (char)receive;
	WorldPos player_pos;
	player_pos = user->self->GetWL();

	if(player_pos.world < TFCMAIN::GetMaxWorlds())
	{
		WorldMap *world = TFCMAIN::GetWorld(player_pos.world);
		if( world != NULL && world->IsValidPosition(player_pos) ){
			if(receive == 0)
            {	
				TRACE(_T("Opened %s for %s\r\n"), (LPCTSTR)lpParams->csName, (LPCTSTR)user->GetAccount());
				//user->playerID = CurrentGlobalID++;
				//sending << (long)user->playerID;			
			
                _LOG_WORLD
                    LOG_MISC_1,
                    "Character %s ( user %s ) just entered the realm at %u, %u, %u!",
                    lpParams->csName,
                    user->GetFullAccountName(),
                    user->self->GetWL().X,
                    user->self->GetWL().Y,
                    user->self->GetWL().world
                LOG_
			
				// shoot the player's stats
				sending << (long)user->self->GetID();							
				sending << (short)player_pos.X;
				sending << (short)player_pos.Y;
				sending << (short)player_pos.world;
				sending << (long)user->self->GetHP();
				sending << (long)user->self->GetMaxHP();
				sending << (short)user->self->GetMana();
				sending << (short)user->self->GetMaxMana();
				sending << (long)(user->self->GetXP() >> 32);
				sending << (long)user->self->GetXP();
				DWORD dwLevel = user->self->GetLevel();
                if( dwLevel >= MAX_LEVEL )
				{
		            dwLevel = MAX_LEVEL - 1;
                }
				else if( dwLevel == 0 )
				{
                    dwLevel = 1;
                }
                sending << (long)(Character::sm_n64XPchart[dwLevel] >> 32);
				sending << (long)Character::sm_n64XPchart[dwLevel];
				sending << (short)user->self->GetSTR();
				sending << (short)user->self->GetEND();
				sending << (short)user->self->GetAGI();
				sending << (short)0; // wil
				sending << (short)user->self->GetWIS();
				sending << (short)user->self->GetINT();
				sending << (short)0; // lck
				sending << (char )TFCTime::Second();
				sending << (char )TFCTime::Minute();
				sending << (char )TFCTime::Hour();
				sending << (char )TFCTime::Week();
				sending << (char )TFCTime::Day();
				sending << (char )TFCTime::Month();
				sending << (short)TFCTime::Year();
				sending << (long)user->self->GetGold( );
				sending << (short)dwLevel;
				// last level xp
				sending << (long)(Character::sm_n64XPchart[dwLevel - 1] >> 32);
				sending << (long)Character::sm_n64XPchart[dwLevel - 1];
				

				user->self->SendPlayerMessage( sending );

                sending.Destroy();                

				sending << (RQ_SIZE)RQ_ViewBackpack;
				sending << (char)0;	// Don't show backpack..!!
				sending << (long)user->self->GetID();
				user->self->PacketBackpack( sending );
                user->self->SendPlayerMessage( sending );	
			
				
				TRACE(_T("\r\nPlayer is located at (%u, %u) in world #%u\r\n"), player_pos.X, player_pos.Y, player_pos.world);

				TemplateList <TFCPacket> theList;
									
			    user->boPreInGame = TRUE;
                user->in_game = FALSE;

                user->BeginSession();

				int read;
				sending.Destroy();
                read = world->packet_inview_units( player_pos, sending, 40, user->self );//BLBLBL _DEFAULT_RANGE est trop petit pour certains endroits à l'oracle où les portes disparaissent sinon., j'essaye 40
                if( read != 0 )
				{
                    user->self->SendPlayerMessage( sending );
                }

                user->SetNextSave(); //BLBLB d'après la fonction, la première sauvegarde du joueur interviens vers 7 à 10 minutes, puis ce sera toutes les 30 secondes apparement ?

				// Sends list of objects			   
				//TRACE("\r\n-- %u --\r\n", user->self->get_appearance());						
					
				//user->binded_object = world->create_world_object(user->self->GetAppearance(), player_pos, nothing);
				//user->binded_object->SetID(user->playerID);
				//user->binded_object->SetMaster((void *)user->self);
			}
		}else sending << (char)1;	
	}else{
		TRACE(_T("Player file corrupted"));
		sending << (char)9; 
		user->in_game = FALSE;
		user->self->reset_character();

		//user->self->SendPlayerMessage( sending );
	}

    {
        if( user->GetGodFlags() & GOD_CAN_RUN_CLIENT_SCRIPTS ){
            TFCPacket sending;
            sending << (RQ_SIZE)RQ_GodFlagUpdate;
            sending << (char)UPDATE_GOD_CAN_RUN_CLIENT_SCRIPTS;
            sending << (char)1;
        
            user->self->SendPlayerMessage( sending );
        }
        if( user->GetGodFlags() & GOD_CAN_SLAY_USER ){
            TFCPacket sending;
            sending << (RQ_SIZE)RQ_GodFlagUpdate;
            sending << (char)UPDATE_GOD_CAN_SLAY_USER;
            sending << (char)1;
        
            user->self->SendPlayerMessage( sending );
        }

		WeatherEffect::GetInstance()->CheckWeatherState( user->self, user->self->GetWL() );

    }

	/////////////////////////////////////////
	// Send a welcome message to the player
    RegKeyHandler regKey;     
		
	if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY GEN_CFG_KEY ) )
	{
		// Get the text to send
		CString csWelcome;
		csWelcome = regKey.GetProfileString( "WelcomeMessage", "" );		

		// If there is a text, send it
		if( !csWelcome.IsEmpty() )
		{
			TFCPacket sending;
			
			sending << (RQ_SIZE)RQ_ServerMessage;
			sending << (short)30;
			sending << (short)3;
			sending << (CString &)csWelcome;
			sending << (long)0x000A64E0/*RGB( 0, 100, 255 )*/;
			
			user->Lock();
			user->self->SendPlayerMessage( sending );
			user->Unlock();		
		}

		regKey.Close();
	}
	
	/////////////////////////////////////////
	// Cast a spell when a player connect to the game (test)
	/*user->Lock();

	if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY CHARACTER_KEY ) )
	{
		// Get the spell ID to cast
		int spellID = 0;
		spellID = regKey.GetProfileInt( "ConnectionSpell", 0 );

		// If a spell has been caught, cast it
		if( spellID != 0 )
		{
			user->self->CastSpellDirect( spellID, user->self );
		}

		regKey.Close();
	}
	
	user->Unlock();*/
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_PutPlayerInGame
//////////////////////////////////////////////////////////////////////////////////////////
// From out of game to PreInGame.
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;

    if( user->boLockedOut ){
        return;
    }

    
    // if player isn't in game (for a change..!!! :))
	if(!user->in_game && !user->boPreInGame && user->registred)
	{
		if( user->UsePicklock(__FILE__, __LINE__) ){
			try{
				unsigned char temp_length;
				unsigned char temp_byte;
				unsigned char dummy;
				BOOL go = TRUE;		
		//		SharedCStats *current_character;

				CString name;
				name.Empty();

	//			CFile player_file;
	//			CString full_directory;

	//			sending.packet_ID = TFCMAIN::GetRound();	

				msg->Get((char *)(&temp_length));		
				// Retrieves the name

				for(dummy = 0; dummy < temp_length; dummy++){
					msg->Get((char *)(&temp_byte));
					name += (TCHAR)temp_byte;
				}
				
				// Create new player message structure
				LPRQSTRUCT_PUT_PLAYER_IN_GAME lpParams = new RQSTRUCT_PUT_PLAYER_IN_GAME;
				lpParams->sParams.user = user;
				lpParams->sParams.rqRequestID = rqRequestID;
				lpParams->sParams.msg = NULL;
				lpParams->csName = name;
							
				// Call asynchronous loading function
				//AsyncRQFUNC_PutPlayerInGame(lpParams);
				AsyncFuncQueue::GetMainQueue()->Call( AsyncRQFUNC_PutPlayerInGame, lpParams );
				//user->UseUnlock(__FILE__, __LINE__);

			}catch(TFCPacketException *e){
				LOG_PACKET_ERROR( "RQ_PutPlayerInGame" );
				user->UseUnlock(__FILE__, __LINE__);
				delete e;
			}

		}
	}else
	// If user is between states, then and then only send the stats.
	if( user->boPreInGame ){
		TFCPacket sending;
		
		sending << (short)RQ_PutPlayerInGame; // request 13;	
		sending << (char)0;
		sending << (long)user->self->GetID();							
		WorldPos player_pos = user->self->GetWL();
		sending << (short)player_pos.X;
		sending << (short)player_pos.Y;
		sending << (short)player_pos.world;
		sending << (long)user->self->GetHP();
		sending << (long)user->self->GetMaxHP();
		sending << (short)user->self->GetMana();
		sending << (short)user->self->GetMaxMana();
		sending << (long)(user->self->GetXP() >> 32);
		sending << (long)user->self->GetXP();
		DWORD dwLevel = user->self->GetLevel();
        if( dwLevel >= MAX_LEVEL ){
		    dwLevel = MAX_LEVEL - 1;
        }else if( dwLevel == 0 ){
            dwLevel = 1;
        }
        sending << (long)(Character::sm_n64XPchart[dwLevel] >> 32);
		sending << (long)Character::sm_n64XPchart[dwLevel];

        sending << (short)user->self->GetSTR();
		sending << (short)user->self->GetEND();
		sending << (short)user->self->GetAGI();
		sending << (short)0; // wil
		sending << (short)user->self->GetWIS();
		sending << (short)user->self->GetINT();
		sending << (short)user->self->GetLCK(); // lck
		sending << (char )TFCTime::Second();
		sending << (char )TFCTime::Minute();
		sending << (char )TFCTime::Hour();
		sending << (char )TFCTime::Week();
		sending << (char )TFCTime::Day();
		sending << (char )TFCTime::Month();
		sending << (short)TFCTime::Year();
		sending << (long)user->self->GetGold( );
		sending << (short)dwLevel;
		// last level xp
		sending << (long)(Character::sm_n64XPchart[dwLevel - 1] >> 32);
		sending << (long)Character::sm_n64XPchart[dwLevel - 1];
		user->self->SendPlayerMessage( sending );
	}

    RQ_FOOTER( "RQ_PutPlayerInGame" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_FromPreInGameToInGame
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQ_FUNC
// When client knows he have been teleported with RQ_TeleportPlayer (Pak 57)
// He sends the get near unit, and the FromPreInGameToInGame :
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( user->boLockedOut ){
        return;
    }

	RQ_HEADER;
    
    TFCPacket sending;

	if( user->boPreInGame && !user->in_game ){
			 		
	  char result = user->self->PutPlayerInGame( );//return 0 if okay

	  //CPlayerManager::GetChatter().AddToSystemChannels( user );//BLBLBL Déplacé dans le bloc conditionnel

	  if( !result ){ //if no problem (0 = OK, 1 = Error happened)

			CPlayerManager::GetChatter().AddToSystemChannels( user );

	  	    user->in_game = TRUE;
			user->boPreInGame = FALSE;
            user->self->ResetDeath();// If unit teleported, it cannot be dead.
//			user->lFirstRound=TFCMAIN::GetRound();//BLBLBL quand le joueur entre en jeu on enregistre son round d'entrée, pour pouvoir calculer son ratio temps de jeu, nombre de paquets de mouvements lMoveCount;

            TRACE( "\r\nPlayer's radiance = %u.", user->self->GetRadiance() );

           // if( user->GetGodFlags() & GOD_TRUE_INVISIBILITY || 
           //     user->self->ViewFlag( __FLAG_INVISIBILITY ) != 0 ){
            //    user->self->BroadcastPopup( user->self->GetWL(), false );
            //}else{
            user->self->DeferredLoadEffects();

            if( user->self->ViewFlag( __FLAG_NUMBER_OF_REMORTS ) > 0 ){
                user->self->BroadcastSeraphArrival();
            }else{
                user->self->BroadcastPopup( user->self->GetWL(), true );
            }
            //}

            // Send the stats after the deferred load effects.
            {
                TFCPacket stats;
                user->self->PacketStatus( stats );	
                user->self->SendPlayerMessage( stats );
				// asteryth pvp ranking
				stats.Destroy();
                user->self->PacketPvpRanking( stats );
                user->self->SendPlayerMessage( stats );
            }

            if( user->self->IsPuppet() ){                
                user->self->PacketPuppetInfo( sending );
                // If the player is godly invisible
                //if( user->GetGodFlags() & GOD_TRUE_INVISIBILITY ||
                //    user->self->ViewFlag( __FLAG_INVISIBILITY ) != 0 ){
                    // Send puppet info only to him
                //    user->self->SendPlayerMessage( sending );
                //}else{
                    // Otherwise broadcast it.
                //NMNMNM 20
                Broadcast::BCast( user->self->GetWL(), _DEFAULT_RANGE, sending, user->self->GetInvisibleQuery() );//BLBLBL 30=>_DEFAULT_RANGE
                //}
            }            
	  }else{//BLBL : sinon, si on a pas réussi à remettre en jeu le joueur on logue :
		  if (user->self->boLoaded){
			_LOG_DEBUG
				LOG_DEBUG_LVL1,
				"User %s could not be put from PreGame to InGame problem creating bound unit ?",
				(LPCTSTR)user->GetFullAccountName()
			LOG_
		}else{
			_LOG_DEBUG
				LOG_DEBUG_LVL1,
				"User %s could not be put from PreGame to InGame user was not Loaded ?",
				(LPCTSTR)user->GetFullAccountName()
			LOG_
		  }
	  }
	
	  WorldMap *wlWorld = TFCMAIN::GetWorld( user->self->GetWL().world );
		if( wlWorld ){
            if( !( user->GetGodFlags() & GOD_NO_MONSTERS ) ){
		        wlWorld->VerifyInviewHives( user->self->GetWL() );
            }
		}

		sending.Destroy();
        sending << (RQ_SIZE)RQ_FromPreInGameToInGame;
		sending << (char)result;

        if( wlWorld != NULL ){
		// This is already sent when connecting. Before asking to go in-game, client asks for GetNearUnits, which send this packets.
		// wlWorld->packet_inview_units( user->self->GetWL(), sending, _DEFAULT_RANGE, user->self );
            user->self->SendPlayerMessage( sending );
        }

	}else{//else de la condition : if( user->boPreInGame && !user->in_game ){

		sending << (RQ_SIZE)RQ_FromPreInGameToInGame;
		sending << (char)1; // user already in game
		user->self->SendPlayerMessage( sending );		
        WorldMap *wlWorld = TFCMAIN::GetWorld( user->self->GetWL().world );
		int read;//BLBLBL 03/12/2010 : ajout d'une variable pour stocker resultat d'appel
        if( wlWorld != NULL ){
            read = wlWorld->packet_inview_units( user->self->GetWL(), sending, _DEFAULT_RANGE, user->self );
            if (read > 0 ) user->self->SendPlayerMessage( sending ); //BLBLBL ajout d'une condition d'envoi si non nul
        }
	}

    RQ_FOOTER( "RQ_FromPreInGameToInGame" );
}

//////////////////////////////////////////////////////////////////////////////////////////
typedef struct _RQSTRUCT_CREATE_PLAYER{
	ASYNC_PACKET_FUNC_PARAMS sParams;
	CString csName;
	BYTE lpbAnswers[ 6 ];
} RQSTRUCT_CREATE_PLAYER, *LPRQSTRUCT_CREATE_PLAYER;


//////////////////////////////////////////////////////////////////////////////////////////
void AsyncRQFUNC_CreatePlayer
//////////////////////////////////////////////////////////////////////////////////////////
// Asynchronously create player.
// 
(
 LPVOID lpData // A RQSTRUCT_CREATE_PLAYER
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPRQSTRUCT_CREATE_PLAYER lpStruct = (LPRQSTRUCT_CREATE_PLAYER)lpData;
	
	TFCPacket sending;
	Players *user = lpStruct->sParams.user;	
    char receive;

	// Wait for saving.
    user->self->WaitForSaving();
	
	//user->Lock();
	receive = user->self->load_character( lpStruct->csName, user->GetAccount(), lpStruct->lpbAnswers );
	//user->SaveAccount();
	TRACE(_T("\r\nReceive=%u\r\n"), receive);
	sending << (RQ_SIZE)RQ_CreatePlayer;
	sending << (char)receive;		

	user->self->packet_stats(sending);			
	user->self->SendPlayerMessage( sending );

	//user->Unlock();

	user->UseUnlock(__FILE__, __LINE__);
	delete lpStruct;
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_CreatePlayer
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_CreatePlayer
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;

    TFCPacket sending;

	if( user->UsePicklock(__FILE__, __LINE__) ){
		if(user->registred && !user->in_game){

			// If user was previously in the reroll menu.
			if( user->boRerolling ){
				// Not rerolling anymore.
				user->boRerolling = FALSE;
				// Save rerolled data.
				user->self->SaveCharacter();
			}
			
			unsigned int dummy;
			unsigned char temp_length;
	//		unsigned char temp_byte;
			LPBYTE lpbName = NULL;
			CString name;
			name.Empty();


			try{
				// Create a structure to pass to the asynchronous function
				LPRQSTRUCT_CREATE_PLAYER lpStruct = new RQSTRUCT_CREATE_PLAYER;

                // Get the packet
				//msg->Get((short *)(&race));	//  10001
                GET_BYTE( lpStruct->lpbAnswers[ 0 ] );
                GET_BYTE( lpStruct->lpbAnswers[ 1 ] );
                GET_BYTE( lpStruct->lpbAnswers[ 2 ] );
                GET_BYTE( lpStruct->lpbAnswers[ 3 ] );
                GET_BYTE( lpStruct->lpbAnswers[ 4 ] );
                GET_BYTE( lpStruct->lpbAnswers[ 5 ] );
				msg->Get((char *)(&temp_length));	// 4	
				
				lpbName = new BYTE[ temp_length + 1 ];
				for(dummy = 0; dummy < temp_length; dummy++){
					GET_BYTE( lpbName[ dummy ] );
				}
				
				lpbName[ dummy ] = 0;
				
				// Setup the structure
				lpStruct->csName = lpbName;

                // Format the player name to make it legal.
                FormatPlayerName::Format( &lpStruct->csName );

				delete lpbName;
				// Fill default parameters
				FILL_ASYNC_PARAMS( lpStruct->sParams );

                lpStruct->csName.TrimLeft();
                lpStruct->csName.TrimRight();

				// Call loading function asynchronously to avoid loading jams.
				AsyncFuncQueue::GetMainQueue()->Call( AsyncRQFUNC_CreatePlayer, lpStruct );
						
			}catch(TFCPacketException *e){
				user->UseUnlock(__FILE__, __LINE__);
				if( lpbName != NULL ){
					delete lpbName;
				}

				LOG_PACKET_ERROR( "RQ_CreatePlayer" );
				delete e;
			}
		}else{
			user->UseUnlock(__FILE__, __LINE__);
		}
	}

    RQ_FOOTER( "RQ_CreatePlayer" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_Reroll
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_Reroll
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;

    TFCPacket sending;

	//////////////////////////////////////////////////////////////////////////////////////////////
	// Rerolls a PC (function reroll should hold a "level" checker
	if(!user->in_game && user->registred){
		if(user->self->roll_stats()){
			user->boRerolling = TRUE;

			sending << (RQ_SIZE)RQ_Reroll;
			user->self->packet_stats( sending );
			user->self->SendPlayerMessage( sending );
		}
	}

    RQ_FOOTER( "RQ_Reroll" );
}

//////////////////////////////////////////////////////////////////////////////////////////
typedef struct _RQSTRUCT_REGISTER_ACCOUNT{
	ASYNC_PACKET_FUNC_PARAMS sParams;	
	CString csPassword;
	CString csAccount;
    sockaddr_in sockAddr;
	unsigned int packetSeedID;
} RQSTRUCT_REGISTER_ACCOUNT, *LPRQSTRUCT_REGISTER_ACCOUNT;


//////////////////////////////////////////////////////////////////////////////////////////
DWORD TFCMessagesHandler::GetUserMax
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the max users according to an IP address.
// 
(
 sockaddr_in sockAddr // The IP address.
)
// Return: DWORD, the max number of users for this IP.
//////////////////////////////////////////////////////////////////////////////////////////
{
    BOOL boLocal = FALSE;
    DWORD dwMax = 65536;
    
    tlLocalUsers.Lock();
    // Determine if this address is part of the local addresses.        

    tlLocalUsers.ToHead();
    while( tlLocalUsers.QueryNext() && !boLocal ){
        LPLOCAL_USER lpLocal = tlLocalUsers.Object();

        // If the IP & netmask match
        TRACE( "\r\nIP %u vs %u, netmasked %u vs %u.", 
            sockAddr.sin_addr.S_un.S_addr,
            lpLocal->dwIP,
            sockAddr.sin_addr.S_un.S_addr & lpLocal->dwNetmask,
            lpLocal->dwIP & lpLocal->dwNetmask
        );
        if( ( sockAddr.sin_addr.S_un.S_addr & lpLocal->dwNetmask ) == ( lpLocal->dwIP & lpLocal->dwNetmask ) ){
            boLocal = TRUE;
        }
    }
    
    if( boLocal ){
        dwMax = dwMaxLocalUsers;
    }else{
        dwMax = dwMaxRemoteUsers;
    }

    // If license doesn't allow for more players then setup.
    if( theApp.sLicense.wMaxUsers < dwMax ){
        dwMax = theApp.sLicense.wMaxUsers;
    }

    tlLocalUsers.Unlock();

    return dwMax;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool TFCMessagesHandler::IsLocalIP
//////////////////////////////////////////////////////////////////////////////////////////
//  Determines of an IP is local or remote.
// 
(
 sockaddr_in sockAddr // The IP.
)
// Return: bool, true if the IP is local.
//////////////////////////////////////////////////////////////////////////////////////////
{
    bool boLocal = false;
    tlLocalUsers.Lock();
    
    // Determine if this address is part of the local addresses.
    tlLocalUsers.ToHead();
    while( tlLocalUsers.QueryNext() && !boLocal ){
        LPLOCAL_USER lpLocal = tlLocalUsers.Object();

        if( ( sockAddr.sin_addr.S_un.S_addr & lpLocal->dwNetmask ) == ( lpLocal->dwIP & lpLocal->dwNetmask ) ){
            boLocal = true;
        }
    }
    tlLocalUsers.Unlock();

    return boLocal;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool LoadPlayer
//////////////////////////////////////////////////////////////////////////////////////////
// Called once the player has been successfully authenticated.
// 
(
 LPRQSTRUCT_REGISTER_ACCOUNT lpStruct, // The player data.
 CString &csErrorMsg,
 TFCPacket &sending,
 DWORD setCredits
)
// Return: CString, the error message.
//////////////////////////////////////////////////////////////////////////////////////////
{
    bool boAccountSuccessfullyLoggedOn = false;
    
    _LOG_DEBUG
        LOG_DEBUG_LVL3,
        "Creating player %s.",
        (LPCTSTR)lpStruct->csAccount
    LOG_

    
    Players *lpPlayer = CPlayerManager::CreatePlayer( lpStruct->sockAddr, lpStruct->csAccount );

    
    if( lpPlayer != NULL ){
        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Successfully created player %s",
            (LPCTSTR)lpStruct->csAccount
        LOG_

        lpPlayer->SetPwd("");
	    lpPlayer->SetAccount( lpStruct->csAccount );

		if( lpPlayer->LoadAccount( lpStruct->csAccount )){
			// Was user locked out?
			if( lpPlayer->boLockedOut ){
				lpPlayer->registred = FALSE;
				sending << (char)1;
                csErrorMsg = _DEFAULT_STR( 452 );
				_LOG_WORLD
					LOG_WARNING, 
					"User %s at IP %s tried to log on server. This account is currently locked-out.",
					(LPCTSTR)lpStruct->csAccount,
					lpPlayer->GetIP()
				LOG_
			}else{
                _LOG_WORLD
                    LOG_MISC_1,
                    "User %s just logged in from IP( %s p%u ). %u users online!",
                    (LPCTSTR)lpStruct->csAccount,
                    (LPCTSTR)lpPlayer->GetIP(),
                    (LPCTSTR)lpPlayer->GetPort(),
                    CPlayerManager::GetUserCount()
                LOG_

                lpPlayer->SetCredits( setCredits );

                if( CPlayerManager::VerifyPlayerUnique( lpPlayer ) ){                    
                    TRACE( "\r\nUser registred\r\n" );
                    csErrorMsg = _DEFAULT_STR( 453 );
					sending << (char)0;

                    boAccountSuccessfullyLoggedOn = true;

                }else{
                    csErrorMsg = _DEFAULT_STR( 454 );
					sending << (char)2;
                }
			}
        }else{
            _LOG_WORLD
                LOG_WARNING,
                "Could not load user information for %s at IP %s. Access denied.",
                (LPCTSTR)lpStruct->csAccount,
                inet_ntoa( lpStruct->sockAddr.sin_addr )
            LOG_
			csErrorMsg = _DEFAULT_STR( 455 );
            sending << (char)1;
        }

        CPlayerManager::FreePlayerResource( lpPlayer );
	}else{ 	// not loaded?
        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Could NOT created player %s",
            (LPCTSTR)lpStruct->csAccount
        LOG_

        // User was probably already online. Accept it.
        csErrorMsg = _DEFAULT_STR( 453 );
        sending << (char)0;

        boAccountSuccessfullyLoggedOn = true;
    }



    return boAccountSuccessfullyLoggedOn;
}

//const VOP_KEY = 1;
//const VOP_ID  = 0x221516L;

//////////////////////////////////////////////////////////////////////////////////////////
//void InitVOP( CString csAccount, CString csPassword, sockaddr_in &sockAddr, long &requestID, IRadClnt *iVop, CString &authKey, CString &step )
//////////////////////////////////////////////////////////////////////////////////////////
//{
    /*step = "Opening request";
    requestID =  iVop->OpenRequest(
        (LPCTSTR)csAccount,
        (LPCTSTR)csPassword,
        (LPCTSTR)theApp.sAuth.csVOP_NASIP,
        theApp.sAuth.csVOP_NASPort,
        (LPCTSTR)theApp.sAuth.csVOP_Secret,
        theApp.sAuth.csWGFlag,
        "T4C Server",
        VOPCOM_ACCESS_REQUEST
        );
    
    step = "Adding Session-Timeout attribute";
    // Get the session timeout value
    iVop->AddAttribute( requestID, 27, "", 0 );
    
    
    VARIANT  varIPAddr;
    
    VariantInit( &varIPAddr );
    
    DWORD hsIP = htonl( sockAddr.sin_addr.S_un.S_addr );
    
    varIPAddr.lVal = long( hsIP ); // Your IP address in host order here 
    varIPAddr.vt   = VT_I4;
    iVop->AddAttributeEx( requestID, 8, 0, &varIPAddr );
    
    VariantClear( &varIPAddr );
    
    // Add Framed-Address value.
    //DWORD hsIP = htons( sockAddr.sin_addr.S_un.S_addr );
    //iVop->AddAttribute( requestID, 8, inet_ntoa( sockAddr.sin_addr ), hsIP );

    // If the IP is local
    if( TFCMessagesHandler::IsLocalIP( sockAddr ) ){
        // If the local WG key isn't empty.
        if( !theApp.sAuth.csWGKey.IsEmpty() ){                    
            // Ask the the TFC key access
            TRACE( "\r\nLocal: Adding option key %s.", theApp.sAuth.csWGKey );
        
            step = "Adding local-WG attribute";
            _variant_t varAttr;
            
            varAttr = _bstr_t( (LPCTSTR)theApp.sAuth.csWGKey );
            iVop->AddAttributeEx( requestID, VOP_KEY, VOP_ID, &varAttr );            
        
            authKey = theApp.sAuth.csWGKey;
        }
    }
    // If the IP is remote.
    else{
        // If the remote WG key isn't empty.
        if( !theApp.sAuth.csRemoteWGKey.IsEmpty() ){
            TRACE( "\r\nRemote: Adding option key %s.", theApp.sAuth.csRemoteWGKey );
        
            step = "Adding remote-WG attribute";
            
            _variant_t varAttr;
            varAttr = _bstr_t( (LPCTSTR)theApp.sAuth.csRemoteWGKey );
            iVop->AddAttributeEx( requestID, VOP_KEY, VOP_ID, &varAttr );
        
            authKey = theApp.sAuth.csRemoteWGKey;
        }
    }*/
//}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::AsyncRQFUNC_RegisterAccountVOP
//////////////////////////////////////////////////////////////////////////////////////////
// Asynchronously registers the account using VOP.
// 
(
 LPVOID lpData
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	/*LPRQSTRUCT_REGISTER_ACCOUNT lpStruct = (LPRQSTRUCT_REGISTER_ACCOUNT)lpData;
    
    CString csErrorMsg = "";

    _LOG_DEBUG
        LOG_DEBUG_LVL3,
        "Authenticating account %s.",
        lpStruct->csAccount
    LOG_

	TFCPacket sending;

	sending.SetPacketSeedID( lpStruct->packetSeedID );
	
	sending << (RQ_SIZE)RQ_RegisterAccount;
    // Check if another isn't already online.
    
    BOOL found = FALSE;
    BOOL boSendPacket = TRUE;

        // If the user cap has been reached.
        if( CPlayerManager::GetUserCount() >= (int)GetUserMax( lpStruct->sockAddr ) ){
		    csErrorMsg = _DEFAULT_STR( 451 );
            sending << (char)1;            
        }else 
        // Otherwise if the user is already logged on this, or another server.    
        if( Players::AccountLogged( lpStruct->csAccount, inet_ntoa( lpStruct->sockAddr.sin_addr ) ) ){            
            // If player is logged on a server.
            csErrorMsg = _DEFAULT_STR( 2845 );
            sending << (char)1;
        }else{
            bool boAccountSuccessfullyLoggedOn = false;

    	    BOOL boValidKey = TRUE;
            
            // Is user isn't already registred
            CString csIP = inet_ntoa( lpStruct->sockAddr.sin_addr );
            if( lpStruct->csAccount.GetLength() > 1){
                // Create a VOP authentification request for the user.		        
                CString csAccount = lpStruct->csAccount;

                // If a realm was specified.
                if( !theApp.sAuth.csRealm.IsEmpty() ){
                    // Try to find if the user has inputed an @ sign.
                    int realmPos = csAccount.FindOneOf( "@" );                
                    // If the user inputed an @ sign.    
                    if( realmPos != -1 ){
                        // Flush the realm specified by the user.
                        csAccount = csAccount.Left( realmPos );
                    }
                    csAccount += '@';
                    csAccount += theApp.sAuth.csRealm;
                }

                
                CString step = "Instantiating COM object";
                try{
                    IRadClntPtr iVop( "VOPCOM.RadClnt" );

                    step = "Setting license key";
                    iVop->LicenseKey = VOP_LICENSE_KEY;

                    step = "Setting up logging";
                    iVop->LogFile = (LPCTSTR)theApp.sAuth.vopLogFile;
                    iVop->LogLevels = theApp.sAuth.vopLogLevels;                    
    
                    CString authKey;               
                    long requestID;

                    InitVOP( csAccount, lpStruct->csPassword, lpStruct->sockAddr, requestID, iVop, authKey, step );
                    TRACE( "\r\nSecIP: %s SecPort: %u", (LPCTSTR)theApp.sAuth.csVOP_SECIP, theApp.sAuth.wVOP_SECPort );

                    step = "Sending request";
                    long ret = iVop->SendRequest(
				        requestID,
				        (LPCTSTR)theApp.sAuth.csVOP_SECIP,
				        theApp.sAuth.wVOP_SECPort,
				        0
			        );

                    // If request timedout.
                    if( ret == VOPCOM_TIMEDOUT ){
                        _LOG_DEBUG
                            LOG_CRIT_ERRORS,
                            "The main radius server timed-out, trying the 2nd radius server."
                        LOG_

                        step = "Closing request1";
                        // Close the VOP request.
                        iVop->CloseRequest( requestID );

                        // Re-init the whole thing.
                        InitVOP( csAccount, lpStruct->csPassword, lpStruct->sockAddr, requestID, iVop, authKey, step );
                        
                        step = "Sending request2";
                        // Send on secondary IP.
                        ret = iVop->SendRequest(
                            requestID,
                            (LPCTSTR)theApp.sAuth.cs2ndAuthIP,
                            theApp.sAuth.w2ndAuthPort,
                            0
                            );
                    }
                    
                    if( !authKey.IsEmpty() ){                        
                        // Check all attributes for the WG key.
                        int cnt = iVop->GetAttributeCount( requestID );
                        
                        int i;
                        for( i = 1; i <= cnt; i++ ){
                            long code;
                            long vendorId;
                            _variant_t varAttr;
                            varAttr = iVop->GetAttributeValueByIndex( requestID, i,
                                &code, &vendorId );

                            // If this is a WG key.
                            if( code == VOP_KEY && vendorId == VOP_ID ){
                                SafeArrayLock( varAttr.parray );
                                LPBYTE buf = 
                                    reinterpret_cast< LPBYTE >( varAttr.parray->pvData );

                                // Fetch the key from the safe array.
                                CString key;
                                DWORD e;
                                
                                for( e = varAttr.parray->rgsabound->lLbound; e <
                                    varAttr.parray->rgsabound->cElements; e++ ){
                                    
                                    if( buf[ e ] == '\0' ){
                                        e++;
                                        break;
                                    }
                                    key += buf[ e ];
                                }
                                // If this is the requested WG key.
                                if( stricmp( key, authKey ) == 0 ){
                                    // If the next value in the safe array is 1
                                    if( buf[ e ] != '1' ){
                                        boValidKey = FALSE;
                                    }

                                }

                                SafeArrayUnlock( varAttr.parray );
                            }
                        }
                    }                    
		        
		            // See what VOP had to say
		            switch( ret ){
			            case VOPCOM_CACHE_ACCEPTED:
			            case VOPCOM_ACCEPTED:
			            // user was accepted.. you can now verify values 
			            // for keys in privlist_val
			            // If player has access to TFC
			            if( boValidKey ){

                            step = "Getting the session-timeout value.";
                            long timeout;
                            // Get the session time value.
                            long found = iVop->GetAttributeValue( requestID, 27, NULL, &timeout );
                            DWORD credits = 0xFFFFFFFF;

                            if( found && timeout != 0 ){
                                credits = timeout;
                            }

                            // Load the player.
                            boAccountSuccessfullyLoggedOn = LoadPlayer( lpStruct, csErrorMsg, sending, credits );
                        }else{
                            _LOG_WORLD
                                LOG_MISC_1,
                                "User %s at IP %s was denied access because he doesn't have key access to T4C.",
                                (LPCTSTR)lpStruct->csAccount,
                                inet_ntoa( lpStruct->sockAddr.sin_addr )
                            LOG_
                    
                            csErrorMsg = csAccessRightDenialMsg;
                        }
			            break;
			            case VOPCOM_CACHE_REJECTED:
			            case VOPCOM_REJECTED:
			            // either user doesn't exist or password invalid..
				            _LOG_WORLD
                                LOG_MISC_1,
                                "User %s at IP %s was denied access by the Radius server.",
                                (LPCTSTR)lpStruct->csAccount,
                                inet_ntoa( lpStruct->sockAddr.sin_addr )
                            LOG_

				            TRACE( "\r\nUser rejected\r\n" );

                            csErrorMsg = _DEFAULT_STR( 458 );				            
			            break;
			            case VOPCOM_TIMEDOUT:
			            case VOPCOM_ERROR:
			            // The Radius Server did not answer at any of the requests...					
				            
                            _LOG_WORLD
					            LOG_CRIT_ERRORS, 
					            "User %s was denied access because authentification server "
					            "did not answer.",
                                (LPCTSTR)csAccount
				            LOG_
									              
                            _LOG_DEBUG
                                LOG_CRIT_ERRORS, 
                                "User %s was denied access because authentification server "
                                "did not answer.",
                                (LPCTSTR)csAccount
                            LOG_

                            TRACE( "\r\nRadius server does not answer\r\n" );
				            csErrorMsg = _DEFAULT_STR( 459 );
			            break;
			            default:
				            _LOG_WORLD
					            LOG_CRIT_ERRORS,
					            "VOP Registration returned an invalid value %u.", ret
				            LOG_
                            csErrorMsg = _DEFAULT_STR( 460 );
			            break;
		            }

                    if( !csErrorMsg.IsEmpty() ){
                        BSTR msg;
                        long foo;
                        // If an error message was defined by the radius server,
                        // use it instead.
                        if( iVop->GetAttributeValue( requestID, 18, &msg, &foo ) ){
                            if( SysStringLen( msg ) != 0 ){
                                csErrorMsg = msg;
                            }

                            SysFreeString( msg );
                        }

                        sending << (char)1;
                    }

                    step = "Closing request2";
                    iVop->CloseRequest( requestID );
                }catch( _com_error e ){
                    _LOG_DEBUG
                        LOG_CRIT_ERRORS,
                        "There was a COM error sending radius auth. request (%s): %s",
                        (LPCTSTR)step,
                        e.ErrorMessage()
                    LOG_                       
                    sending << (char)1;
                    csErrorMsg = _DEFAULT_STR( 459 );
                }
            }// account length ok.
            else{                
                sending << (char)1; // if ! found		
                csErrorMsg = _DEFAULT_STR( 461 );
            }

            // If the account did not successfully logged on.
            if( !boAccountSuccessfullyLoggedOn ){
                // Notify the players that the loggon failed.
                Players::AccountLoggonFailed( lpStruct->csAccount );
            }
        }//if not user cap.

    if( boSendPacket ){
        sending << (CString &)csErrorMsg;
        WorldPos wlPos = { -1, -1, -1 };
        CPacketManager::SendPacket( sending, lpStruct->sockAddr, -1, wlPos, FALSE );
    }
    
    delete lpStruct;
	*/
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::AsyncRQFUNC_RegisterAccountODBC
//////////////////////////////////////////////////////////////////////////////////////////
// Asynchronously registers a player using ODBC.
//
(
 LPVOID lpData
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPRQSTRUCT_REGISTER_ACCOUNT lpStruct = (LPRQSTRUCT_REGISTER_ACCOUNT)lpData;

	TFCPacket sending;
    CString csErrorMsg;
    DWORD dwUserCredits = 0xFFFFFFFF;

	sending.SetPacketSeedID( lpStruct->packetSeedID );

	sending << (RQ_SIZE)RQ_RegisterAccount;

	// Allow multi account per IP?
	RegKeyHandler regKey;   
	int nMaxAccountPerIP = 0;
		
	if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY AUTH_KEY ) )
	{
		// Get the value		
		nMaxAccountPerIP = regKey.GetProfileInt( "NO_MULTI_ACC_PER_IP", 0 );
		regKey.Close();
	}


   // If the user cap has been reached.
   if( CPlayerManager::GetUserCount() >= (int)GetUserMax( lpStruct->sockAddr ) ){
        csErrorMsg = _DEFAULT_STR( 451 );
        sending << (char)1;            
   }else
   if( lpStruct->csAccount.GetLength() <= 1 ){
        csErrorMsg = _DEFAULT_STR( 461 );
        sending << (char)1;
   
   }
   // If multi account per IP isn't allowed
   else if( (nMaxAccountPerIP != 0) && (Players::IPLogged( inet_ntoa( lpStruct->sockAddr.sin_addr ) ) >= nMaxAccountPerIP) )
   {
	   csErrorMsg = "An account is already logged in with your IP.";
       sending << (char)1;
   }
   // Otherwise if the user is already logged on this, or another server.    
   else if( Players::AccountLogged( lpStruct->csAccount, inet_ntoa( lpStruct->sockAddr.sin_addr ) ) ){            
        // If player is logged on a server.
        csErrorMsg = _DEFAULT_STR( 2845 );
        sending << (char)1;
   }
   else
   {
        bool boAccountSuccessfullyLoggedOn = false;

        // Do authentification
        CString csQuery;
        BOOL boAuth = TRUE;
        BOOL boDBError = FALSE;

        char szPassword[ 250 ];
        szPassword[ 0 ] = 0;

        char cSendingCode = 0;
        
        char szAccount[ 1024 ];

		lpStruct->csAccount.MakeLower();
        Players::QuotedAccount( szAccount, lpStruct->csAccount );


        ODBCAuth.Lock(); //BLBLBLBL commented

        TRACE( "\r\nAccountName=%s.", szAccount );

        // If user wants credits checking.
        if( !theApp.sAuth.csODBC_Credits.IsEmpty() ){                    
            csQuery.Format(
                "SELECT %s, %s FROM %s WHERE %s='%s'",
                theApp.sAuth.csODBC_Pwd,
                theApp.sAuth.csODBC_Credits,
                theApp.sAuth.csODBC_Table,
                theApp.sAuth.csODBC_Account,
                szAccount
            );
        }
        // Otherwise user doesn't want credits checking.
        else{
            csQuery.Format(
                "SELECT %s FROM %s WHERE %s='%s'",
                theApp.sAuth.csODBC_Pwd,
                theApp.sAuth.csODBC_Table,
                theApp.sAuth.csODBC_Account,
                szAccount
            );
        }

        // Append the supplied where statement if it exists.
        if( !theApp.sAuth.csODBC_Where.IsEmpty() ){
            csQuery += " AND (";
            csQuery += theApp.sAuth.csODBC_Where;
            csQuery += ")";
        }

        // Send the request
        if( ODBCAuth.SendRequest( (LPCTSTR)csQuery ) )
		{                        
            if( ODBCAuth.Fetch() )
			{
                // Fetch password.
                ODBCAuth.GetString( 1, szPassword, 250 );

                // Fetch credits fields if it exists.
                if( !theApp.sAuth.csODBC_Credits.IsEmpty() )
				{
                    ODBCAuth.GetDWORD( 2, &dwUserCredits );
                }
            }
			else
			{
                csErrorMsg = _DEFAULT_STR( 462 );
                boAuth = FALSE;
            }
        }else
		{
            boDBError = TRUE;
            boAuth = FALSE;
            csErrorMsg = _DEFAULT_STR( 459 );
        }                    

        // If no DB error occured
        //if( boDBError ){
            // Cancel data fetch operation.
            ODBCAuth.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close//BLBLBL commented
        //}
    
        ODBCAuth.Unlock();//BLBLBBL commented

		// If password encryption has been requested
		if( theApp.dwEncryptedPassword )
		{
			// TODO
		}

        // Check password (case sensitive).
		if( theApp.dwPasswordCaseSensitive && boAuth &&
					strcmp( szPassword, (LPCTSTR)lpStruct->csPassword ) != 0 )
		{
			csErrorMsg = _DEFAULT_STR( 458 );
			boAuth = FALSE;
		}
		// Check password
        else if( boAuth && stricmp( szPassword, (LPCTSTR)lpStruct->csPassword ) != 0 )
		{
            csErrorMsg = _DEFAULT_STR( 458 );
            boAuth = FALSE;
        }
        
        // User registered ///////////////////////////////////////////////////////////////////////            
        if( boAuth ){
            boAccountSuccessfullyLoggedOn = LoadPlayer( lpStruct, csErrorMsg, sending, dwUserCredits );
        }else
        // Database out //////////////////////////////////////////////////////////////////////////            
        if( boDBError ){
			_LOG_PC
				LOG_CRIT_ERRORS, 
				"User %s was denied access because ODBC authentication server "
				"did not answer.",
                (LPCTSTR)lpStruct->csAccount
			LOG_
            sending << (char)1;
        }else{
            sending << (char)1;
        }

        // If the account did not successfully log on.
        if( !boAccountSuccessfullyLoggedOn ){
            // Notify the players that the loggon failed.
            Players::AccountLoggonFailed( lpStruct->csAccount );
        }
    }


    sending << (CString &)csErrorMsg;
    WorldPos wlPos = { -1, -1, -1 };
    CPacketManager::SendPacket( sending, lpStruct->sockAddr, -1, wlPos, FALSE );

    delete lpStruct;
}

//////////////////////////////////////////////////////////////////////////////////////////
/*void TFCMessagesHandler::AsyncRQFUNC_RegisterAccountGOA
//////////////////////////////////////////////////////////////////////////////////////////
//  Register an account via GOA authentication.
// 
(
 LPVOID lpData
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	const ERR_CHECKSTRING_NOERROR = 0;
    const ERR_CHECKSTRING_INVALIDSTRING = 1;
    
    LPRQSTRUCT_REGISTER_ACCOUNT lpStruct = (LPRQSTRUCT_REGISTER_ACCOUNT)lpData;

	TFCPacket sending;
    CString csErrorMsg;

	sending.SetPacketSeedID( lpStruct->packetSeedID );

	sending << (RQ_SIZE)RQ_RegisterAccount;

    int ticketPaddingSize = strlen( "TTTTTTTTTSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS" );

    bool wrongAccount = true;
    // Check to see if the ticket has the good user ID.
    if( lpStruct->csPassword.GetLength() > ticketPaddingSize ){
        CString ticketAccount = lpStruct->csPassword.Left( 
            lpStruct->csPassword.GetLength() - ticketPaddingSize
        );

        ticketAccount.TrimRight();
        ticketAccount.TrimLeft();
        // If the accounts correspond
        if( stricmp( ticketAccount, lpStruct->csAccount ) == 0 ){
            wrongAccount = false;
        }
    }

   // If the user cap has been reached.
   if( CPlayerManager::GetUserCount() >= (int)GetUserMax( lpStruct->sockAddr ) ){
        csErrorMsg = _DEFAULT_STR( 451 );
        sending << (char)1;            
   }else
   if( lpStruct->csAccount.GetLength() <= 1 || wrongAccount ){
        csErrorMsg = _DEFAULT_STR( 461 );
        sending << (char)1;
   
   }else 
   // Otherwise if the user is already logged on this, or another server.    
   if( Players::AccountLogged( lpStruct->csAccount, inet_ntoa( lpStruct->sockAddr.sin_addr ) ) ){            
        // If player is logged on a server.
        csErrorMsg = _DEFAULT_STR( 2845 );
        sending << (char)1;
   }else{
        bool boAccountSuccessfullyLoggedOn = false;

        int iOk = ERR_CHECKSTRING_INVALIDSTRING;
        
        if( lpStruct->csPassword.GetLength() < 255 ){
            // Copy the password into a modifiable char buffer.
            char pwd[ 256 ];
            strcpy( pwd, lpStruct->csPassword );
            
            // Verify the string.
            iOk = GoaCheckString( pwd, TRUE );
        }
                
        // User registered ///////////////////////////////////////////////////////////////////////            
        if( iOk == ERR_CHECKSTRING_NOERROR ){
            boAccountSuccessfullyLoggedOn = LoadPlayer( lpStruct, csErrorMsg, sending, 0xFFFFFFFF );
        }else{
            csErrorMsg = _DEFAULT_STR( 458 );
            sending << (char)1;
        }

        // If the account did not successfully log on.
        if( !boAccountSuccessfullyLoggedOn ){
            // Notify the players that the loggon failed.
            Players::AccountLoggonFailed( lpStruct->csAccount );
        }
    }

    sending << (CString &)csErrorMsg;
    WorldPos wlPos = { -1, -1, -1 };
    CPacketManager::SendPacket( sending, lpStruct->sockAddr, -1, wlPos, FALSE );

    delete lpStruct;
}*/

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_RegisterAccount
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_RegisterAccount
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
 )
 //////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;
    
    TFCPacket sending;

	sending.SetPacketSeedID( msg->GetPacketSeedID() );

    char *lpcStr = NULL;
        
    Players *user = CPlayerManager::GetPlayerResource( sockAddr );
    if( user != NULL ){
        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Player was already authenticated. Resending authentication agreement."
        LOG_
            
        TFCPacket sending;
        
		sending.SetPacketSeedID( msg->GetPacketSeedID() );

        sending << (RQ_SIZE)RQ_RegisterAccount;        
        sending << (char)0;
        sending << (CString)_DEFAULT_STR( 453 );               
        
        user->self->SendPlayerMessage( sending );
        
        CPlayerManager::FreePlayerResource( user );
        
        return;
    }

	/**********************************************************************************************/
	// Register account
	// If we're not already registred and if we can read the message
	try{
		unsigned char temp_length1;
		unsigned char temp_length2;
		unsigned short hi_version;
		unsigned short lo_version;
		int dummy;		

		CString account;
		CString password;
		
		CString full_directory;

		sending << (RQ_SIZE)RQ_RegisterAccount;

		msg->Get((char *)(&temp_length1));		
        TRACE( "\r\nLen %u: ", temp_length1 );
		if( temp_length1 ){
			lpcStr = new char[ temp_length1 + 1 ];
			// Retrieves the name
			for(dummy = 0; dummy < temp_length1; dummy++){				
				msg->Get( (char *)( &lpcStr[ dummy ] ) );
                TRACE( "%c", lpcStr[ dummy ] );
			}
			lpcStr[ dummy ] = 0;	// NULL term string.

			account = lpcStr;
			delete lpcStr;
            lpcStr = NULL;
		}
		else
		{
			account = "";
		}
        // Remove beginning and trailing white spaces.
        account.TrimRight();
        account.TrimLeft();

		msg->Get((char *)(&temp_length2));	
        TRACE( "\r\nLen %u: ", temp_length2 ); // Thomas: J'ai changer temp_length1 to temp_length2.
		
        if( temp_length2 ){
			lpcStr = new char[ temp_length2 + 1 ];
			for(dummy = 0; dummy < temp_length2; dummy++){				
				msg->Get((char *)( &lpcStr[ dummy ] ));	
                TRACE( "%c", lpcStr[ dummy ] );
			}

			lpcStr[ dummy ] = 0;	// Null term string.
							
#ifdef ENCRYPTED_PASSWORD
			// Decrypt password.
			Random rndDecrypt;
			rndDecrypt.SetSeed( msg->packet_ID );
			for( dummy = 0; dummy < temp_length2; dummy++ ){
				lpcStr[ dummy ] ^= rndDecrypt;
			}
#endif				
			password = lpcStr;
			delete lpcStr;
            lpcStr = NULL;
		}
		else
		{
			password = "";
		}

		msg->Get((short *)(&hi_version));
		msg->Get((short *)(&lo_version));

		// If versions are ok
		if( 1/*hi_version == TFCServer->dwVersion*/ )
		{

            if( !account.IsEmpty() ){
                _LOG_DEBUG
                    LOG_DEBUG_HIGH,
                    "Sending account %s for authentication.",
                    (LPCTSTR)account
                LOG_
                
                // Create and fill structure to pass to async registering function.
	    		LPRQSTRUCT_REGISTER_ACCOUNT lpStruct = new RQSTRUCT_REGISTER_ACCOUNT;
            
			    FILL_ASYNC_PARAMS( lpStruct->sParams );

    			lpStruct->csAccount = account;
	    		lpStruct->csPassword = password;
                lpStruct->sockAddr = sockAddr;
				lpStruct->packetSeedID = msg->GetPacketSeedID();

                
				TRACE( "\r\n<v>ethod=%u.", theApp.sAuth.bAuthentificationMethod );
			    // Call asynchronous registering function.
                switch( theApp.sAuth.bAuthentificationMethod ){
                // VOP authentification.
                //case VOP_AUTH:  AsyncFuncQueue::GetMainQueue()->Call( AsyncRQFUNC_RegisterAccountVOP, lpStruct );
                  //  break;
                // ODBC authentification.
                case ODBC_AUTH: AsyncFuncQueue::GetMainQueue()->Call( AsyncRQFUNC_RegisterAccountODBC, lpStruct );
                    break;
                //case GOA_AUTH: AsyncFuncQueue::GetMainQueue()->Call( AsyncRQFUNC_RegisterAccountGOA, lpStruct );
                //    break;
                }

            }
		}else{						
			_LOG_PC 
                LOG_DEBUG_LVL1, 
                "User at IP %s was denied access because of wrong internal client version v%u (server v%u)",				
                (LPCTSTR)inet_ntoa( sockAddr.sin_addr ),
				hi_version,
				TFCServer->dwVersion
			LOG_

			CString csVersionError = "Wrong server version. Run T4C.exe to autopatch to new version.";
            
            sending << (char)1;	
            sending << (CString &)csVersionError;
            WorldPos wlPos = { -1, -1, -1 };
            CPacketManager::SendPacket( sending, sockAddr, -1, wlPos, FALSE );
		}			
	}
	catch(TFCPacketException *e)
	{
		LOG_PACKET_ERROR( "RQ_RegisterAccount" );
		delete e;
        if( lpcStr != NULL )
		{
            delete lpcStr;
        }
	}	

    RQ_FOOTER( "RQ_RegisterAccount" );
}

//////////////////////////////////////////////////////////////////////////////////////////
typedef struct _RQSTRUCT_DELETE_PLAYER{
	ASYNC_PACKET_FUNC_PARAMS sParams;
	CString csName;
}RQSTRUCT_DELETE_PLAYER, *LPRQSTRUCT_DELETE_PLAYER;

//////////////////////////////////////////////////////////////////////////////////////////
void AsyncRQFUNC_DeletePlayer
//////////////////////////////////////////////////////////////////////////////////////////
// Asyn deletion function
// 
(
 LPVOID lpData 
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPRQSTRUCT_DELETE_PLAYER lpStruct = (LPRQSTRUCT_DELETE_PLAYER)lpData;
	Players *user = lpStruct->sParams.user;
	TFCPacket sending;

    // Wait for saving.
    user->self->WaitForSaving();

	sending << (RQ_SIZE)RQ_DeletePlayer;

	//user->Lock();
	
	sending << user->self->DeleteCharacter( lpStruct->csName, user->GetAccount());			
	user->self->SendPlayerMessage( sending );
	
	//user->Unlock();

	user->UseUnlock(__FILE__, __LINE__);
	delete lpStruct;
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_DeletePlayer
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_DeletePlayer
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    TFCPacket sending;

	if( user->UsePicklock(__FILE__, __LINE__) ){
		/**********************************************************************************************/
		// Delete player	
		if(user->registred && !user->in_game && !user->boPreInGame) // deletes only if you are registred//FIX de PM pour éviter crash serveur si le mec delete un perso en cours de déco
		{
			//CString name;
			unsigned char temp_length;
		//	unsigned char temp_byte;
			LPBYTE lpbName = NULL;
		
			int dummy;
		
			// If user was previously in the reroll menu.
			if( user->boRerolling ){
				// Not rerolling anymore.
				user->boRerolling = FALSE;
				// Save rerolled data.
				user->self->SaveCharacter();
			}
			
			try{
				msg->Get((char *)(&temp_length));		
				lpbName = new BYTE[ temp_length + 1 ];
				// Retrieves the name
				for(dummy = 0; dummy < temp_length; dummy++){
					GET_BYTE( lpbName[ dummy ] );
				}
				lpbName[ temp_length ] = 0;
					
				// Prepare async deletion
				LPRQSTRUCT_DELETE_PLAYER lpStruct = new RQSTRUCT_DELETE_PLAYER;			
				FILL_ASYNC_PARAMS( lpStruct->sParams );
				lpStruct->csName = lpbName;
				delete lpbName;

				AsyncFuncQueue::GetMainQueue()->Call( AsyncRQFUNC_DeletePlayer, lpStruct );

			}catch(TFCPacketException *e){
				user->UseUnlock(__FILE__, __LINE__);
				if( lpbName != NULL ){
					delete lpbName;
				}
				LOG_PACKET_ERROR( "RQ_DeletePlayer" );
				delete e;
			}
		}else{
			user->UseUnlock(__FILE__, __LINE__);
		}
	}

    RQ_FOOTER( "RQ_DeletePlayer" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GodCreateObject
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_ViewBackpack
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    TFCPacket sending;

	/**************************************************************************************************/
	// View backpack, returns the objects in the user's backpack	
	if(user->in_game || user->boPreInGame )
	{
		WORD  wIndent;
		LPDWORD lpdwIndentList = NULL;
		Unit *lpuTarget;

		try
		{
			int i;	

			msg->Get( (short *)&wIndent );
			if( wIndent )
			{
				lpdwIndentList = new DWORD[ wIndent + 1 ];			
				for( i = 0; i < wIndent; i++ )
				{				
					msg->Get( (long *)&lpdwIndentList[ i ] );				
				}
				// null-terminated.
				lpdwIndentList[ wIndent ] = 0;
			}else{
				// Otherwise at least specify a null list.
				lpdwIndentList = new DWORD[ 1 ];
				lpdwIndentList[ 0 ] = 0;
			}
			
			lpuTarget = user->self->GetIndentItem( lpdwIndentList );

			if( lpuTarget ){
				sending << (RQ_SIZE)RQ_ViewBackpack;
				sending << (char)1;	// Of course player wants to view its backpack!
				sending << (long)lpuTarget->GetID();
				lpuTarget->PacketBackpack( sending );
			}
			
			user->self->SendPlayerMessage( sending );

			delete lpdwIndentList;
		}
		catch( TFCPacketException *e )
		{
			LOG_PACKET_ERROR( "RQ_ViewBackpack" );
			delete e;
			if( lpdwIndentList )
				delete lpdwIndentList;		
		}
	}

    RQ_FOOTER( "RQ_ViewBackpack" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_ViewEquipped
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_ViewEquipped
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;

    TFCPacket sending;
	/**************************************************************************************************/
	// View equiped objects, returns the objects equiped by the user, in the BodyPos order	
	if(user->in_game || user->boPreInGame){
		// puts the backpack into the packet		
		user->self->packet_equiped( sending );
		user->self->SendPlayerMessage( sending );
	}

    RQ_FOOTER( "RQ_ViewEquipped" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_ExitGame
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    /**************************************************************************************************/
	// Unregister account, exit game	
	    
	unsigned long lNow,lLastPlayerEvent;
	lNow = time(NULL);
	lLastPlayerEvent=user->self->lLastEventTime;
		 
        //special havoc (ajouter : "true ||" à la condition :)
	if ( lNow-lLastPlayerEvent>=13 || user->self->GetUnderBlock()==__SAFE_HAVEN || user->self->GetUnderBlock()==__INDOOR_SAFE_HAVEN ){//BLBLBL antiplug : 15 secondes d'inactivité avant de déconnecter un perso OU en zone PVP off
											//il faut mettre 2 secondes de moins ici, pour laisser le temps au pak d'arriver au client avant qu'il se ferme tout seul au bout de 15 sec^^
   	
	    /*_LOG_DEBUG
		    LOG_WARNING,
			"Received accepted exit pak from player %s.",
			(LPCTSTR)user->GetFullAccountName()
		LOG_*/
		

	    TFCPacket sending;
        sending << (RQ_SIZE)(RQ_SafePlug); //BLBLBL Antiplug : on informe le client
		sending << (char)1;	// 1 = C'est ok le joueur a été supprimé du serveur, le client peut se fermer direct
		user->self->SendPlayerMessage( sending );
		
		user->DeletePlayer();
    
		if( user->in_game ){
		    Broadcast::BCObjectRemoved( user->self->GetWL(), _DEFAULT_RANGE,
			    user->self->GetID()
			);
		}


	}else{

		_LOG_DEBUG
		    LOG_WARNING,
			"Received exit pak from player %s refused, since less than 15 sec (%d sec)",
			(LPCTSTR)user->GetFullAccountName(),
			lNow-lLastPlayerEvent
		LOG_

	}

    RQ_FOOTER( "RQ_ExitGame" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_EquipObject
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
	/***********************************************************************************************/
	// Equip's an object into the proper position
	unsigned long itemID;
	try{
		msg->Get((long *)(&itemID));
	
		user->self->equip_object(itemID);
	
	    TFCPacket sending;
        sending << (RQ_SIZE)(RQ_ViewBackpack);
		sending << (char)0;	// Only update
		sending << (long)user->self->GetID();
		user->self->PacketBackpack( sending );
		user->self->SendPlayerMessage( sending );

	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_EquipObject" )
		delete e;
	}

    RQ_FOOTER( "RQ_EquipObject" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_UnequipObject
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;

	/***********************************************************************************************/
	// Unequips an object..
	unsigned char position;
	try{
		msg->Get((char *)(&position));
	
		user->self->unequip_object(position);

	    TFCPacket sending;
		sending << (RQ_SIZE)(RQ_ViewBackpack);
		sending << (char)0;	// Only update
		sending << (long)user->self->GetID();
		user->self->PacketBackpack( sending );
		user->self->SendPlayerMessage( sending );

	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_UnequipObject" )
		delete e;		
	}

    RQ_FOOTER( "RQ_UnequipObject" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_UseObject
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    WorldPos WL = {0,0,0};
	unsigned long itemID;

	try{
		WorldPos ppos = user->self->GetWL();
		WorldMap *world = TFCMAIN::GetWorld(ppos.world);
		if(world)
		{
			msg->Get((short *)(&WL.X));
			msg->Get((short *)(&WL.Y));
			msg->Get((long  *)(&itemID));

			if(WL.X != 0 && WL.Y != 0)
			{ // check on the floor
				WorldPos wlUserPos = user->self->GetWL();
				// If door in usage range.
				int nTouchRange = user->self->ViewFlag( __FLAG_ARM_EXTENT );

				if( nTouchRange == 0 )
				{
					nTouchRange = _DEFAULT_TOUCH_RANGE;
				}

                Unit *item = world->FindNearUnit( WL, itemID );
                if( item != NULL )
				{
                    DWORD useRange = item->ViewFlag( __FLAG_USE_RANGE ) + nTouchRange;

		    		if( abs( WL.X - wlUserPos.X ) <= useRange &&
			    		abs( WL.Y - wlUserPos.Y ) <= useRange )
					{
                        item->SendUnitMessage( MSG_OnDisturbed, item, user->self, user->self );
						DWORD itemUsed = 0;
                        item->SendUnitMessage( MSG_OnUse, item, user->self, user->self, NULL, &itemUsed );
                    }
					else
					{
                        user->self->SendSystemMessage( _STR( 469, user->self->GetLang() ) );
                    }
                }
				else
				{
                    user->self->SendSystemMessage( _STR( 469, user->self->GetLang() ) );
                }
			}
			else
			{ // check in backpack
				user->self->use_item(itemID, user->self);
			}
		}
	}
	catch(TFCPacketException *e)
	{
		LOG_PACKET_ERROR( "RQ_UseObject" )
		delete e;
	}

    RQ_FOOTER( "RQ_UseObject" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_Attack
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

	/***********************************************************************************************/
	// Attack something
	WorldPos where = {0,0,0};	
	WorldPos userpos = {0,0,0};	
	Unit *target;
	BOOL done = FALSE;
	DWORD theID;    

	//BLBLBL antispeedhack, si on lance un attaque on vide le buffer de mouvement :
	user->Lock();
	user->MoveList.clear();
/*	user->lFirstRound = TFCMAIN::GetRound();//BL dès qu'un joueur est stoppé on reset son compteur ratio mouvement.
	user->lMoveCounter = 0;*/
	user->Unlock();

	try{
		WorldPos ppos = user->self->GetWL();
		WorldMap *world = TFCMAIN::GetWorld(ppos.world);
		if(world){
			msg->Get((short *)(&where.X));
			msg->Get((short *)(&where.Y));
			msg->Get((long *)(&theID));

			user->self->RemoveFlag( __FLAG_ROBBING );
			
			// if the ID is 0 then player requests a blind-attack 
			if(theID == 0){
                WorldPos nullWl = { 0, 0, 0 };
                Broadcast::BCMiss( user->self->GetWL(), _DEFAULT_RANGE,
                    user->self->GetID(),
                    0,
                    user->self->GetWL(),
                    nullWl
                );
			}else{
				user->self->Do(fighting);

				// then gets who we attack;
				userpos = user->self->GetWL();
				TRACE(_T("\r\nPos of user = (%u, %u), Wanted pos of target = (%u, %u)\r\n\r\n"), userpos.X, userpos.Y,
					where.X, where.Y);
				target = world->FindNearUnit(where, theID);
                if( target ){
                    int reachRange = _DEFAULT_REACH_RANGE;
                    int xRange = abs(userpos.X - where.X);
                    int yRange = abs(userpos.Y - where.Y);
                    
                    // If this is a ranged attack.
                    if( user->self->RangedAttack() ){
                        // Change the reach range to that of a few screens.
                        reachRange = 25;
                    }
    				if( xRange <= reachRange && yRange <= reachRange ){
                        if( GAME_RULES::InPVP( user->self, target ) ){
    						TRACE(_T("and found a target"));

                            // Then start auto-combat.
                            user->self->StartAutoCombat( 
                                Character::Attack( Character::Attack::normal, 0 ),
                                target
                            );
                        }else{
                            CString csText = _STR( 14, user->self->GetLang() );
                            TFCPacket sending;
			                sending << (RQ_SIZE)RQ_ServerMessage;
			                sending << (short)30;
			                sending << (short)3;
			                sending << (CString &)csText;
							sending << (long)0x000A64E0/*RGB( 0, 100, 255 )*/;
                            user->self->SendPlayerMessage( sending );

                            TRACE( "not in PVP.");
                        }
					}else{
                        Broadcast::BCMiss( user->self->GetWL(), _DEFAULT_RANGE,
                            user->self->GetID(),
                            target->GetID(),
                            user->self->GetWL(),
                            target->GetWL()
                        );

                        if( target->CanAttack() ){
                            if( target->GetType() == U_NPC ){
                                target->Do( fighting );
                                target->SetTarget( user->self );
                            }
                        }
                    }
                }else{
                    // Send a 'missing unit' message to the client.
                    TFCPacket sending;
                    sending << (RQ_SIZE)RQ_MissingUnit;
                    sending << (long)theID;
                    sending << (RQ_SIZE)RQ_Attack;
                    user->self->SendPlayerMessage( sending );
                }
			}
		}
	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_Attack" )
		delete e;
	}		

    RQ_FOOTER( "RQ_Attack" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GetPersonnalPClist
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;

    if( user->boLockedOut ){
        return;
    }

    
    TFCPacket sending;

	// If user was previously in the reroll menu.
	if( user->boRerolling ){
		// Not rerolling anymore.
		user->boRerolling = FALSE;
		// Save rerolled data.
		user->self->SaveCharacter();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	// This request sends the list of PCs attached to the player
	if(!user->in_game){
		{
			// Tells the client how many characters each account can have, so it can display
			// the 'New Character' option according to server rules.
			TFCPacket sending;
			sending << (RQ_SIZE)RQ_MaxCharactersPerAccountInfo;
			sending << (char)TFCMAIN::GetMaxCharactersPerAccount();
			user->self->SendPlayerMessage( sending );
		}

		TemplateList <CStringAndRace> *PCs = user->GetPCs();

		sending << (RQ_SIZE)RQ_GetPersonnalPClist;
		sending << (char)PCs->NbObjects();
		PCs->Lock();
		PCs->ToHead();
		CStringAndRace *PC;
		int i;
		while(PCs->QueryNext()){
			PC = PCs->Object();
			sending << (char)PC->name.GetLength();
			for(i = 0; i < PC->name.GetLength(); i++)
				sending << (char)(PC->name[i]);
			
			sending << (short)PC->race;
			sending << (short)PC->level;
		}
		PCs->Unlock();
		
		user->self->SendPlayerMessage( sending );
	}

    RQ_FOOTER( "RQ_GetPersonnalPCList" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_IndirectTalk
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	// This request handles non-personnalized talking.
	// If user is god.	
		BYTE bDirection = 0;
		DWORD dwID = 0;
		DWORD dwTextColor = 0;
		DWORD dwNameColor = RGB(255,0,0);
		LPBYTE lpbText = NULL;

		try{
			GET_LONG( dwID );
			GET_BYTE( bDirection );
			GET_LONG( dwTextColor );
			GET_STRING( lpbText );

	/*					    _LOG_TEXT
                                LOG_MISC_1,
                                "Received text %s.",
                                lpbText
                            LOG_*/

			if(  user->self->GetType() == U_OBJECT ) dwNameColor = U_OBJECT_COLOR
			else if ( user->self->GetType() == U_NPC ) dwNameColor = U_NPC_COLOR
			else if ( user->self->GetType() == U_PC ) {
				if ( user->IsGod() ) dwNameColor = U_GOD_COLOR
				else dwNameColor = U_PC_COLOR;
			}


            //user->self->Disturbed(); //BLBLBL : no longer disturb player for simple talking

            Character *lpCharacter = static_cast< Character * >( user->self );
            // If the pre-translation function allows message to continue.
            if( lpCharacter->PreTranslateInGameMessage( lpbText ) )
			{
				//scan la liste des mot pour trouver
                //si le mot est un mot clee et si le joueur peu executer ce mot clef...
               
                //user->self->AnalyseActionWorld((char*)lpbText); //permet de lancer les sorts en les parlant


                if( user->IsGod() ){
                    bool boSendFakeTalk = true;
                    bool boSendTalk     = true;
                    LPBYTE lpbSysopMessage = lpbText;

                    // If this character was appended.
                    if( lpbText[ 0 ] == '#' ){
                        if( strlen( reinterpret_cast< const char * >( lpbText ) ) > 0 ){
                            lpbSysopMessage = &lpbText[1];
                            boSendTalk = false;
                        }
                    }

			        // If this wasn't a sysop command
			        if( SysopCmd::VerifySysopCommand( user, lpbSysopMessage ) == FALSE ){
				        // Send normal message
				        if( user->boCanTalk && boSendTalk ){
                            _LOG_TEXT
                                LOG_MISC_1,
                                "Player %s says '%s'.",
                                (LPCTSTR)user->self->GetTrueName(),
                                lpbText
                            LOG_

                            if(user->in_game){
								CString m( lpbText );
                                // Create a new packet
                                TFCPacket sending;
                                sending << (RQ_SIZE)RQ_IndirectTalk;
                                sending << (long)dwID;
                                sending << (char)bDirection;
                                sending << (long)dwTextColor;
                                sending << (char)0; // not an NPC.
                                sending << (CString &)m;
                                sending << (CString &)user->self->GetName( user->self->GetLang() );
								sending << (long)dwNameColor;

                                Broadcast::BCast( user->self->GetWL(), _DEFAULT_RANGE, sending );
                            }

                            boSendFakeTalk = false;
						} else if (!boSendTalk) {
							{
								TFCPacket sending;
								CString csText;
								csText.Format("Invalid command: %s", lpbText);
								sending << (RQ_SIZE)RQ_ServerMessage;
								sending << (short)30;
								sending << (short)3;
								sending << (CString &)csText;
								sending << (long)RGB( 255, 0, 0 );
								user->Lock();
								user->self->SendPlayerMessage( sending );
								user->Unlock();
							}
						}
			        }
                    if( boSendFakeTalk ){                    
				        // Create a null message packet
				        TFCPacket sending;
				        sending << (RQ_SIZE)RQ_IndirectTalk;
				        sending << (long)dwID;
				        sending << (char)bDirection;
				        sending << (long)dwTextColor;
                        sending << (char)0; // not an NPC.
				        sending << (short)0;
                        sending << (short)0;
						sending << (long)dwNameColor;
				        user->self->SendPlayerMessage( sending );				        
			        }
	            }else{

					
					if( user->boCanTalk ){
                        _LOG_TEXT
                            LOG_MISC_1,
                            "Player %s says '%s'.",
                            (LPCTSTR)user->self->GetTrueName(),
                            lpbText
                        LOG_

                        if(user->in_game){
                            
							TextFilter.FilterMessage((char*)lpbText);//16/06/2009 filter for bad words Before broadcast to other players.

                            CString m( lpbText );
                            
							// Create a new packet
                            TFCPacket sending;
                            sending << (RQ_SIZE)RQ_IndirectTalk;
                            sending << (long)dwID;
                            sending << (char)bDirection;
                            sending << (long)dwTextColor;
                            sending << (char)0; // not an NPC.
                            sending << (CString &)m;
                            sending << (CString &)user->self->GetName( user->self->GetLang() );
							sending << (long)dwNameColor;

                            Broadcast::BCast( user->self->GetWL(), _DEFAULT_RANGE, sending );
                        }
		            }else{
						//BLBLBL pourquoi envoyer un paquet vide si le joueur ne peut pas parler ?

				        /*TFCPacket sending;
			            sending << (RQ_SIZE)RQ_IndirectTalk;
			            sending << (long)user->self->GetID();
			            sending << (char)1;
			            sending << (long)0;
                        sending << (char)0; // not an NPC.
			            sending << (short)0;
                        sending << (short)0;
						sending << (long)dwNameColor;
			            user->self->SendPlayerMessage( sending );*/
						
						//BLBLBL autant l'informer à la place qu'il ne peut pas parler :
						if(user->in_game){
							user->self->SendSystemMessage( "You cannot speak anymore.", RGB( 255, 0, 0 ) );
						}
		            }
	            }
            }

			delete lpbText;
		}catch( TFCPacketException *e ){
			if( lpbText != NULL ){
				delete lpbText;
			}
			LOG_PACKET_ERROR( "(Sysop)RQ_IndirectTalk" );
			delete e;
		}

    RQ_FOOTER( "RQ_IndirectedTalk" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_Shout
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;
    
    // If user can shout and page.
	
	// BEGIN : Mestoph -> Correction for shouts bugs if player not in game...	
		// Befor : if( user->boCanShout && user->boCanPage ){ 
    if( user->boCanShout && user->in_game){//BLBLBL le "&& user->boCanPage" n'a rien à faire la :)
	// END : Mestoph -> Correction for shouts bugs if player not in game...	

		//////////////////////////////////////////////////////////////////////////////////////////////
		// This function handles global (shout) broadcasted talking,		
        LPBYTE lpSender = NULL;
        LPBYTE lpText = NULL;
        DWORD  dwColor = 0;

        try{            
            if( user->CanShout() ){//on vérifie que le player peut shout vis à vis de son délai.
				//user->ToggleShout(); // steph désactivation
                // Get data to log.
                GET_STRING( lpSender );
                GET_LONG  ( dwColor );
                GET_STRING( lpText );


				



				if (!user->IsGod()){
					TextFilter.FilterMessage((char*)lpText);//16/06/2009 Filter bad words
				}

                ChatterChannels &cChatter = CPlayerManager::GetChatter();
                /*_LOG_SHOUTS
					LOG_MISC_1,
					"Player %s tryed to say in n public channel %s: %s",
					(LPCTSTR)lpSender,
					cChatter.GetMainChannel().c_str(),
					lpText
				LOG_*/
                cChatter.Talk( 
                    user, 
                    cChatter.GetMainChannel(), 
                    string( reinterpret_cast< char * >( lpText ) )
                );

                delete lpText;
                delete lpSender;
            }else{

                // Send a message to the user to tell him he can't shout right now.
				//You may not shout right now
                user->self->SendSystemMessage( _STR( 467, user->self->GetLang() ) );
            }
        }catch( TFCPacketException *e ){
            LOG_PACKET_ERROR( "RQ_Shout" )

            delete e;
            if( lpText != NULL ){
                delete lpText;
            }
            if( lpSender != NULL ){
                delete lpSender;
            }
        }
	}else{
        if (user->in_game) {//BLBLBL ajout un test voir si le joueur est ingame avant de tester tout ça sinon déco instantanée !
			// Send a shouts revoked message.
			time_t tTestExpiration;
			time(&tTestExpiration);

			if (user->lCutExpireDate>0 && user->lCutExpireDate<tTestExpiration) {
							
				user->Lock();
				user->boCanShout = TRUE;
				user->lCutExpireDate = 0;
				user->self->SendSystemMessage( "Your shouts have been automatically restored.", RGB( 0, 255, 0 ) );
				user->Unlock();

			}else if (user->lCutExpireDate>0){
				 // Get time in tm structure
				tm *tmTime = localtime( (const time_t*)&user->lCutExpireDate ); // steph tm *tmTime = localtime( (const time_t*)&user->lCutExpireDate ); au lieu de tm *tmTime = localtime( &user->lCutExpireDate );
      
				CString csTemp;
				csTemp.Format("Your shouts are revoked until %s.", asctime(tmTime));
				user->self->SendSystemMessage( csTemp, RGB( 255, 0, 0 ) );
			}else if (user->lCutExpireDate<0){
				 // Get time in tm structure
				tm *tmTime = localtime( (const time_t*)&user->lCutExpireDate ); // steph tm *tmTime = localtime( (const time_t*)&user->lCutExpireDate ); au lieu de tm *tmTime = localtime( &user->lCutExpireDate );
      
				CString csTemp;
				csTemp.Format("It seems there is a problem with your revoke delay : until %s. Contact a GM", asctime(tmTime));
				user->self->SendSystemMessage( csTemp, RGB( 255, 0, 0 ) );

			}else{
				user->self->SendSystemMessage( _STR( 7171, user->self->GetLang() ) );
			}
		}
    }

    RQ_FOOTER( "RQ_Shout" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_Page
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    /////////////////////////////////////////////////////////////////////////////////////////////
	// This function handles personnalized talking (to an ID, whisper/page)
    if( user->in_game ){
        unsigned char *message = NULL;
	    unsigned char *name = NULL;
	    unsigned int i = 0;
	    BOOL boFound = FALSE;
	    CString csAccount;
	    CString csSender = user->self->GetTrueName();
	    CString csMessage;

	    try{			
            if( user->CanPage() ){
                user->PageNotification();

                GET_STRING( name );
		        GET_STRING( message );

				if (!user->IsGod()){
					TextFilter.FilterMessage((char*)message);//16/06/2009 filter bad words
				}

		        csMessage = message;
                CString csPlayer = name;
                csPlayer.TrimRight();
                csPlayer.TrimLeft();
                bool boError = true;

                if( !csPlayer.IsEmpty() ){
                    bool boCanPageInvisible;
                    if( user->GetGodFlags() & GOD_CAN_SEE_ACCOUNTS ){
                        boCanPageInvisible = true;
                    }else{
                        boCanPageInvisible = false;
                    }

                    if( CPlayerManager::PageUser( user, csPlayer, csSender, csMessage, boCanPageInvisible ) ){
    	    		    // Send an ack to the client stating who we really pages ;)
	    	    	    TFCPacket sending;
						csPlayer += ": " + csMessage; // Makes it display the text you sent on the Page_ack msg 
		    	        csMessage = "";
			            sending << (RQ_SIZE)RQ_Page;
    			        sending << (CString &)csMessage;
	    		        sending << (CString &)csPlayer;
                        
			            user->self->SendPlayerMessage( sending );

                        boError = false;
		            }
                }else{
			        // Player not found! Send null ack.
			        csMessage = "";
			        TFCPacket sending;
			        sending << (RQ_SIZE)RQ_Page;
			        sending << (CString &)csMessage;
			        sending << (CString &)csMessage;
			        
			        user->self->SendPlayerMessage( sending );
		        }

		        delete name;
		        delete message;
            }else{
                // Notify the user that he cannot page right now.
                user->self->SendSystemMessage( _STR( 2777, user->self->GetLang() ) );
            }
	    
	    }catch(TFCPacketException *e){
		    LOG_PACKET_ERROR( "RQ_Page" )
		    delete e;
		    if(message)
			    delete message;
		    if(name)
			    delete name;
	    }
    }

    RQ_FOOTER( "RQ_Page" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_DirectedTalk
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    //////////////////////////////////////////////////////////////////////////////////////////////
	// This functions talks directly in game to a PC/NPC (caught by NPC)
	if(user->in_game){

		WorldPos where = {0,0,0};
		unsigned short nb_chars = 0;		
		TFCPacket otherPacket,censoredPacket;//BLBLBL nouveau packet dispo : un texte censuré
		unsigned char thisChar = 0;
		unsigned int i;
		auto_ptr< BYTE > message;
		BYTE bDirection = 0;
		char color;
		DWORD theID = 0;
		Unit *target;
		BOOL boProcess = TRUE;
		DWORD dwNameColor = RGB(255,0,0);

		try{
			WorldPos ppos = user->self->GetWL();
			WorldMap *world = TFCMAIN::GetWorld(ppos.world);
			if(world){
				msg->Get((short *)&where.X);
				msg->Get((short *)&where.Y);			
				msg->Get((long  *)&theID);

				// BEGIN : Mestoph -> Fix long talk...
					// 32 Number of case for the wight
					// 24 Number of case for the height
				if ((abs(where.X - ppos.X) <= 40) && (abs(where.Y - ppos.Y) <= 30))//BLBL 40 and 30
				{ 
	
				// END : Mestoph -> Fix long talk...

					msg->Get((char  *)&bDirection );
					msg->Get((long  *)&color);
					msg->Get((short *)&nb_chars);

	
					if(  user->self->GetType() == U_OBJECT ) dwNameColor = U_OBJECT_COLOR
					else if ( user->self->GetType() == U_NPC ) dwNameColor = U_NPC_COLOR
					else if ( user->self->GetType() == U_PC ) {
						if ( user->IsGod() ) dwNameColor = U_GOD_COLOR
						else dwNameColor = U_PC_COLOR;
					}

				
					TRACE(_T("The ID %u !! (%u %u)\r\n"),theID, where.X, where.Y);
					otherPacket << (RQ_SIZE)RQ_IndirectTalk;
					otherPacket << (long) user->self->GetID();
					otherPacket << (char) bDirection;					
					otherPacket << (long) color;
					otherPacket << (char)0; // not an NPC.

					censoredPacket << (RQ_SIZE)RQ_IndirectTalk;
					censoredPacket << (long) user->self->GetID();
					censoredPacket << (char) bDirection;					
					censoredPacket << (long) color;
					censoredPacket << (char)0; // not an NPC.					
					
					//if( user->boCanTalk ){//BLBLBL on doit toujours pouvoir parler aux pnj
						otherPacket << (short)nb_chars;			
						censoredPacket << (short)nb_chars;			

					// Mestoph : VÈrification de la taille des strings avant de lire le contenu du data
						/*
						TRACE(_T("\r\nNBchars = %u\r\n"), nb_chars);
						if(nb_chars){
							message = auto_ptr< BYTE >( new unsigned char[nb_chars + 1] );
							
							// Gets the message into another packet
							for(i = 0; i < nb_chars; i++){
								msg->Get(&thisChar);				
								message.get()[ i ] = thisChar;	// puts it in the local message (for NPCs)
								TRACE(_T("Sent %c"), thisChar);
								otherPacket << static_cast< char >( thisChar ); // and on the other packet for broadcasting
								censoredPacket << static_cast< char >( '*' );
							}
							message.get()[ nb_chars ] = 0; //16/06/2009 : replaced [ i ] by [ nb_chars ]
							
							/*if (!user->IsGod()){
								TextFilter.FilterMessage((char*)message.get());//16/06/2009 filter bad words
							}*/
							
							/*for (i = 0; i < nb_chars; i++){
								otherPacket << static_cast< char >(message.get()[i]);
							}*/

						/*}*/

						TRACE(_T("\r\nNBchars = %u\r\n"), nb_chars);
						if(msg->CheckLen(nb_chars))
						{
							message = auto_ptr< BYTE >( new unsigned char[nb_chars + 1] );
							
							// Gets the message into another packet
							for(i = 0; i < nb_chars; i++){
								msg->Get(&thisChar);				
								message.get()[ i ] = thisChar;	// puts it in the local message (for NPCs)
								TRACE(_T("Sent %c"), thisChar);
								otherPacket << static_cast< char >( thisChar ); // and on the other packet for broadcasting
								censoredPacket << static_cast< char >( '*' );
							}
							message.get()[ nb_chars ] = 0; //16/06/2009 : replaced [ i ] by [ nb_chars ]
							
							/*if (!user->IsGod()){
								TextFilter.FilterMessage((char*)message.get());//16/06/2009 filter bad words
							}*/
							
							/*for (i = 0; i < nb_chars; i++){
								otherPacket << static_cast< char >(message.get()[i]);
							}*/
						}
						else
						{
							message = auto_ptr< BYTE >( new unsigned char[1] );
							message.get()[ 0 ] = 0;
							CT4CLog::DebugLog((1 << 6), "Received crash attempt from character %s (%s) from IP : %s", (LPCTSTR)user->self->GetTrueName(), (LPCTSTR)user->GetFullAccountName(), (LPCTSTR)user->GetIP());
						}

						// End Mestoph
						otherPacket << (CString &)( user->self->GetName( user->self->GetLang() ) );
						censoredPacket << (CString &)( user->self->GetName( user->self->GetLang() ) );
	   		            
						
					/*}else{
						// Feedback client
						otherPacket << (short)0;
						otherPacket << (short)0;
						otherPacket << (long)dwNameColor;
						user->self->SendPlayerMessage( otherPacket );
						boProcess = FALSE;
					}*/
					otherPacket << (long)dwNameColor;
					censoredPacket << (long)dwNameColor;

					CONST BYTE *lpMessageSent = message.get() == NULL ? reinterpret_cast< CONST BYTE * >( "" ) : message.get();


					Character *lpCharacter = static_cast< Character * >( user->self );
					// If the pre-translation function allows message to continue.
					if( lpCharacter->PreTranslateInGameMessage( lpMessageSent ) ){
					    // If user is god.
						if( user->IsGod() ){
	                        const BYTE *lpSysopMessage = lpMessageSent;
							bool boTalk = true;
							if( lpMessageSent[ 0 ] == '#' && strlen( reinterpret_cast< const char * >( lpMessageSent ) ) > 1 ){
	                            lpSysopMessage = &lpMessageSent[1];
								boTalk = false;
							}                        
	
							// Process sysop commands.
							boProcess = !SysopCmd::VerifySysopCommand( user, lpSysopMessage );
							if( !user->boCanTalk || !boTalk ){
							    boProcess = FALSE;
							}                        
						}
	
						if( boProcess ){
	    			        // then shoot the talk to the targetted NPC
	    					target = world->FindNearUnit(where, theID);
	
							// Broadcast sent message to allow all player to see talking.
							if (user->boCanTalk) Broadcast::BCast(user->self->GetWL(), _DEFAULT_RANGE, otherPacket);//BLBLBL nouveau : un cut local peut parler aux pnj, sans faire chier le monde
							else Broadcast::BCast(user->self->GetWL(), _DEFAULT_RANGE, censoredPacket);//BLBLBL sinon on indique simplement qu'il parle au pnj
							//message[i] = 0;	
	
							if( target != NULL ){                        
	                            MultiLock( user->self, target );
								user->self->Disturbed();
	
								user->self->StopAutoCombat();
	
								target->SendUnitMessage(MSG_OnTalk, target, NULL, user->self, static_cast< void * >( const_cast< BYTE * >( lpMessageSent ) ), NULL);
		
								target->Unlock();
								user->self->Unlock();

								_LOG_TEXT
	                                LOG_MISC_1,
									"Player %s (talking to NPC %s) says '%s'.",
									(LPCTSTR)user->self->GetTrueName(),
									target->GetName( _DEFAULT_LNG ),
									lpMessageSent
								LOG_
	
							}else{
	                    	    // send a break conversation
								TFCPacket sending;
								sending << (RQ_SIZE)RQ_BreakConversation;
								user->self->SendPlayerMessage( sending );
							}
						    
							// Set the player's target to the NPC that it is talking to
							user->self->SetTarget( target );
						}else{
	                        TFCPacket sending;
							sending << (RQ_SIZE)RQ_BreakConversation;
							user->self->SendPlayerMessage( sending );
	
	
							// Send dummy message (ack).
							sending.Destroy();
							sending << (RQ_SIZE)RQ_IndirectTalk;
							sending << (long)theID;
							sending << (char)1;
							sending << (long)0;
							sending << (char)0; // not an NPC.
							sending << (short)0;
							sending << (short)0;
							sending << (long)dwNameColor;
							user->self->SendPlayerMessage( sending );
						}
					}

				// BEGIN : Mestoph -> Fix long talk...
				} else { 
	                        
					TFCPacket sending;
					// Send dummy ack
					sending << (RQ_SIZE)RQ_IndirectTalk;
					sending << (long)theID;
					sending << (char)1;
					sending << (long)0;
					sending << (char)0;
					sending << (short)0;
					sending << (short)0;
					sending << (long)dwNameColor;
					user->self->SendPlayerMessage( sending );

					// Write Cheat Log							
					_LOG_CHEAT
						LOG_MISC_1,
						"Player %s (Id %u, Acct %s, Lvl %u, Pos %u, %u, %u) use a longtalk hack to npc at (Pos %u, %u, %u).",
						(LPCTSTR)user->self->GetTrueName(),
						user->self->GetID(),
						(LPCTSTR)user->GetFullAccountName(),
						user->self->GetLevel(),
						ppos.X,
						ppos.Y,
						ppos.world,
						where.X,
						where.Y,
						where.world
					LOG_
				}
				// END : Mestoph -> Fix long talk...	

			}
		
		}catch(TFCPacketException *e){
			LOG_PACKET_ERROR( "RQ_DirectedTalk" )
			delete e;			
		}
	}

    RQ_FOOTER( "RQ_DirectedTalk" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_CastSpell
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

	WORD  wMana = 0;
	WORD  wSpell = 0;
	DWORD dwID = 0;
	WorldPos TargetPos = { 0, 0, user->self->GetWL().world };

	//BLBLBL antispeedhack, si on lance un sort on vide le buffer de mouvement :
	user->Lock();
	user->MoveList.clear();
/*	user->lFirstRound = TFCMAIN::GetRound();//BL dès qu'un joueur est stoppé on reset son compteur ratio mouvement.
	user->lMoveCounter = 0;*/
	user->Unlock();

	try{
		GET_WORD( wSpell );		
		GET_WORD( TargetPos.X );
		GET_WORD( TargetPos.Y );
		GET_LONG( dwID );
		
		if( dwID != 0 ){
			WorldPos ppos = user->self->GetWL();
			WorldMap *wl = TFCMAIN::GetWorld( ppos.world );
			if(wl){
				if( dwID == user->self->GetID() ){
                    // Start auto-combat.
                    user->self->StartAutoCombat(
                        Character::Attack( Character::Attack::spell, wSpell ),
                        user->self
                    );
				}else{
					Unit *lpuUnit = wl->FindNearUnit( TargetPos, dwID );
					if(lpuUnit){

                        // Vaporize spell.
                        if( wSpell == 10210 ){
                            user->self->CastSpell( wSpell, lpuUnit );
                        }else{
                            // Start auto-combat.
                            user->self->StartAutoCombat(
                                Character::Attack( Character::Attack::spell, wSpell ),
                                lpuUnit
                            );
                        }
                    }else{
                        TFCPacket sending;
                        sending << (RQ_SIZE)RQ_MissingUnit;
                        sending << (long)dwID;
                        sending << (RQ_SIZE)RQ_CastSpell;
                        user->self->SendPlayerMessage( sending );

                        TRACE( "\r\nCould not find target unit ID %u at ( %u, %u ).",
                            dwID, TargetPos.X, TargetPos.Y );

                    }
				}
			}
		}else{
            // If target position is empty, then this is a self-spell.
            if( TargetPos.X == 0 && TargetPos.Y == 0 ){
                // Start auto-combat.
                user->self->StartAutoCombat(
                    Character::Attack( Character::Attack::spell, wSpell ),
                    user->self
                );
            }else{
    			user->self->CastSpell( wSpell, TargetPos );
            }
		}

		// Send back ack.
		TFCPacket sending;
		sending << (RQ_SIZE)RQ_CastSpell;
		user->self->SendPlayerMessage( sending );

/*			_LOG_DEBUG   //BLBLBL 13/12/2010
                    LOG_MISC_1,
                    "Sent pak with spell effect %u", wSpell
			LOG_*/

	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_CastSpell" )
		delete e;
	}

    RQ_FOOTER( "RQ_CastSpell" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_BroadcastTextChange
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    // If the user has no target.
    if( user->self->GetTarget() != NULL ){
        // If the NPC is a private talk.
        if( user->self->GetTarget()->IsPrivateTalk() ){
            // Sent the message only to the player.
            user->self->SendPlayerMessage( *msg );

            return;
        }
    }
    // Broadcast text change.
    Broadcast::BCast(user->self->GetWL(), _DEFAULT_RANGE, *msg);            

    RQ_FOOTER( "RQ_BroadcastTextChange" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GetUnitName
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    TFCPacket sending;
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	// This request is sent by the client to get the name of the near unit of ID x
	DWORD dwID = 0;
	WorldPos wlUnitPos = {0,0,0};
	Unit *lpuUnit;
	CString csName;
	CString csPacketGuildName;//BLBLBL
	
	WorldPos ppos = user->self->GetWL();
	WorldMap *world = TFCMAIN::GetWorld(ppos.world);

	try{
		if(world){			
			msg->Get((long *)&dwID);
			msg->Get((short *)&wlUnitPos.X);
			msg->Get((short *)&wlUnitPos.Y);

			lpuUnit = world->FindNearUnit(wlUnitPos, dwID);
		
			if(lpuUnit){
				csName = lpuUnit->GetName( user->self->GetLang() );
				sending.Destroy();
				sending << (RQ_SIZE)RQ_GetUnitName;
				sending << (long)lpuUnit->GetID();
                
				DWORD color = RGB(255,0,0);
                if( lpuUnit->GetType() == U_OBJECT ){
                    Objects *obj = static_cast< Objects * >( lpuUnit );
                    if( obj->GetQty() > 1 ){
                        char buf[ 256 ];
                        csName += " x";
                        csName += itoa( obj->GetQty(), buf, 10 );
                    }
					color = U_OBJECT_COLOR;
                } else if (lpuUnit->GetType() == U_NPC ) {
					color = U_NPC_COLOR;
				} else if (lpuUnit->GetType() == U_PC ) {
					Character *lpChar = static_cast< Character * >( lpuUnit );
					if (lpChar->GetPlayer()->IsGod()) color = U_GOD_COLOR
					else color = U_PC_COLOR;
										
					csPacketGuildName = lpChar->GetGuildName();//Récupération du nom de guilde pour le paquet


				}


				sending << (CString &)csName;
				sending << (long)color;
				sending << (CString &)csPacketGuildName;//BLBLBL on envoie le nom de guilde
				sending << (long)0x00FFFF00;
		
		/*_LOG_DEBUG
            LOG_CRIT_ERRORS,
            "Sent guild name of %s (%s)",
			csName,
            csPacketGuildName
        LOG_*/
				user->self->SendPlayerMessage( sending );
            }else{
                sending << (RQ_SIZE)RQ_MissingUnit;
                sending << (long)dwID;
                sending << (RQ_SIZE)RQ_GetUnitName;
                
                user->self->SendPlayerMessage( sending );
            }
		}else{
		_LOG_DEBUG
            LOG_CRIT_ERRORS,
            "Attempted to ask unit details for an invalid World position."//BLBLBL ajouté du log.
        LOG_
		}
	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_GetUnitName" );
		delete e;
	}

    RQ_FOOTER( "RQ_GetUnitName" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_BreakConversation
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    /////////////////////////////////////////////////////////////////////////////////////////////
	// This request is sent by the client when it wants to break a conversation with a NPC
	DWORD dwID = 0;
	WorldPos wlUnitPos = {0,0,0};
	Unit *lpuUnit;
	WorldMap *world;

	try{
		msg->Get((long *)&dwID);
		msg->Get((short *)&wlUnitPos.X);
		msg->Get((short *)&wlUnitPos.Y);

		WorldPos ppos = user->self->GetWL();
		world = TFCMAIN::GetWorld(ppos.world);
		
		if(world){
			lpuUnit = world->FindNearUnit(wlUnitPos, dwID);
			if(lpuUnit){
				// if the unit can actually be stopped for talking (if it's a NPC).
				if(lpuUnit->GetType() == U_NPC){
					// If unit was "talking" to "user->self" (us)
					if(lpuUnit->IsDoing() == talking && lpuUnit->GetTarget() == user->self){						
						lpuUnit->Do(wandering);
						lpuUnit->SetTarget(lpuUnit->GetBond());
						wlUnitPos.X = wlUnitPos.Y = wlUnitPos.world = -1;
						lpuUnit->SetDestination(wlUnitPos);
					}
				}
			}
		}
	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_BreakConversation" );
		delete e;
	}

    RQ_FOOTER( "RQ_BreakConversation" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_ReturnToMenu
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{    
    RQ_HEADER;
    
    TFCPacket sending;
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// This request is sent to put the player out of the game, but still connected
	sending << (RQ_SIZE)RQ_ReturnToMenu;

	if(user->in_game){
		WorldPos ppos = user->self->GetWL();
		WorldMap *wl = TFCMAIN::GetWorld(ppos.world);
		if(wl){
			// removes the unit associated with the PC from the world
			wl->remove_world_unit(ppos, user->self->GetID());
			user->self->SaveCharacter(); // then save the character
			user->self->reset_character(); // then reset it to avoid any misunderstanding.
			user->in_game = FALSE;

            Broadcast::BCObjectRemoved( ppos, _DEFAULT_RANGE,
                user->self->GetID()
            );
		}
		sending << (char)0;
	}else{
		sending << (char)1;
	}

	user->self->SendPlayerMessage( sending );

    RQ_FOOTER( "RQ_ReturnToMenu" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GetSkillList
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    TFCPacket sending;
	
	user->self->PacketSkills( sending );
	user->self->SendPlayerMessage( sending );    	

    RQ_FOOTER( "RQ_GetSkillList" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_UseSkill
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;
    
    /////////////////////////////////////////////////////////////////////////////////////////
	// This request is used by the client to use a skill
	WorldPos wlTargetPos = { 0, 0, user->self->GetWL().world };
	DWORD dwID = 0;
	WORD wSkill = 0;
	try{
		msg->Get( (short *)&wSkill );
		msg->Get( (short *)&wlTargetPos.X );
		msg->Get( (short *)&wlTargetPos.Y );
		msg->Get( (long *) &dwID );

		TRACE( "\r\nUsing skill ID %u pos ( %u, %u ) PC %u", wSkill, wlTargetPos.X, wlTargetPos.Y, dwID );
		TRACE( " UserID = %u", user->self->GetID() );

		// if an ID was specified, skill is used on someone
		if( dwID != 0 ){
			WorldPos ppos = user->self->GetWL();
			WorldMap *wl = TFCMAIN::GetWorld(ppos.world);
			if( wl != NULL ){
                // If position is valid.
                if( wl->IsValidPosition( wlTargetPos ) ){
    				if( dwID == user->self->GetID() ){
	    				user->self->UseSkill( wSkill, user->self, NULL );
			    	}else{
				    	Unit *lpuUnit = wl->FindNearUnit(wlTargetPos, dwID);
					    if( lpuUnit != NULL ){
						    user->self->UseSkill(wSkill, lpuUnit, NULL);
                        }else{
                            TFCPacket sending;

                            sending << (RQ_SIZE)RQ_MissingUnit;
                            sending << (long)dwID;
                            sending << (RQ_SIZE)RQ_UseSkill;
                            user->self->SendPlayerMessage( sending );
                        }
				    }
                }
            }
		}else{
			user->self->UseSkill(wSkill, wlTargetPos);
		}


	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_UseSkill" );
		delete e;
	}

    RQ_FOOTER( "RQ_UseSkill" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GetStatus
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
// 	_LOG_DEBUG LOG_ALWAYS, "ASTERYTH RQ_GETSTATUS" LOG_
    RQ_HEADER;

    TFCPacket sending;
	
	user->self->PacketStatus( sending );	
	user->self->SendPlayerMessage( sending );

    RQ_FOOTER( "RQ_GetStatus" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GetPvpRanking
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    TFCPacket sending;
	
	user->self->PacketPvpRanking( sending );	
	user->self->SendPlayerMessage( sending );

    RQ_FOOTER( "RQ_GetPvpRanking" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_XPchanged
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    TFCPacket sending;

	/////////////////////////////////////////////////////////////////////////////////
	// This request only returns a new quantity of xp
	sending << (RQ_SIZE)RQ_XPchanged;
	sending << (long)(user->self->GetXP() >> 32);
	sending << (long)user->self->GetXP();

	user->self->SendPlayerMessage( sending );

    RQ_FOOTER( "RQ_XPchanged" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_HPchanged
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

	TFCPacket sending;

	sending << (RQ_SIZE)RQ_HPchanged;
	sending << (long)user->self->GetHP();
	sending << (long)user->self->GetMaxHP();

	user->self->SendPlayerMessage( sending );

    RQ_FOOTER( "RQ_HPchanged" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GetTime
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

	TFCPacket sending;
	
	/////////////////////////////////////////////////////////////////////////////////
	// This request sends the current time to the client,
	sending << (RQ_SIZE)RQ_GetTime;
	sending << (char )TFCTime::Second();
	sending << (char )TFCTime::Minute();
	sending << (char )TFCTime::Hour();
	sending << (char )TFCTime::Week();
	sending << (char )TFCTime::Day();
	sending << (char )TFCTime::Month();
	sending << (short)TFCTime::Year();

    WorldPos wlPos = { -1, -1, -1 };
    CPacketManager::SendPacket( sending, sockAddr, 0, wlPos, FALSE );

    RQ_FOOTER( "RQ_GetTime" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_SendPeriphericObjects
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    TFCPacket sending;
	bool boSend = false;
	/////////////////////////////////////////////////////////////////////////////////
	// This request sends the current time to the client,	
	if( user->in_game ){
		char     direction = 0;
		WorldPos where = {0,0,0};

		try{
			msg->Get( (char  *)&direction );
			msg->Get( (short *)&where.X );
			msg->Get( (short *)&where.Y );
			where.world = user->self->GetWL().world;

			WorldMap *wl = TFCMAIN::GetWorld( where.world );
	
			if( wl ){
				// If player asks for a valid position
				if( wl->IsValidPosition( where ) ){
					if(direction < 9 ){						
						boSend = //BLBLBL 03/12/2010 on regarde si y a qq chose à envoyer ou pas
						wl->packet_peripheral_units( 
                            where, 
                            _DEFAULT_RANGE,
							(DIR::MOVE)direction, 
                            sending,
                            user->self
                        );

                        if (boSend) user->self->SendPlayerMessage( sending ); //BLBL ajouté un if (boSend)

                    }	
				}
			}

		}catch( TFCPacketException *e ){
			LOG_PACKET_ERROR( "RQ_SendPeriphericObjects" );
			delete e;
		}
	}

    RQ_FOOTER( "RQ_SendPeriphericObjects" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_EnterChatterChannel
//////////////////////////////////////////////////////////////////////////////////////////
// Registers the player for a particular chatter channel
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    try{
        LPBYTE szChannel;
        LPBYTE szPassword;

        // Get the channel and password from the packet.
        GET_STRING( szChannel );
        auto_ptr< BYTE > cAutoDeleteChannel( szChannel );     // insure auto-deletion.
        GET_STRING( szPassword );                
        auto_ptr< BYTE > cAutoDeletePassword( szPassword );   // insure auto-deletion.
              
        // Chatter channels need STL strings. Convert.
        string csChannel( reinterpret_cast< const char *>( szChannel ) );
        string csPassword( reinterpret_cast< const char *>( szPassword ) );
        
        TRACE( "\nChannel='%s', Password='%s'.", csChannel.c_str(), csPassword.c_str() );

        ChatterChannels &cChatter = CPlayerManager::GetChatter();

        // If the user could be added to the chatter channel.
        if( !cChatter.Add( user, csChannel, csPassword ) ){
            CString cstrChannel = csChannel.c_str();

            // Send a RQ_EnterChatterChannel (this is an error).
            TFCPacket sending;
            sending << (RQ_SIZE)RQ_EnterChatterChannel;
            sending << (CString &)cstrChannel;
            user->self->SendPlayerMessage( sending );
        }else{
            // Send only the registered list of channels.
            cChatter.SendRegisteredChannelList( user );
        }
	}catch( TFCPacketException *e ){
		LOG_PACKET_ERROR( "RQ_EnterChatterChannel" );
		delete e;
	}
    
    RQ_FOOTER( "RQ_EnterChatterChannel" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_SendChatterMessage
//////////////////////////////////////////////////////////////////////////////////////////
// Sends a message to a specific chatter channel
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    try{
        LPBYTE szChannel;
        LPBYTE szMessage;

        // Get the channel and message from the packet.
        GET_STRING( szChannel );
        auto_ptr< BYTE > cAutoDeleteChannel( szChannel );     // insure auto-deletion.
        GET_STRING( szMessage );                
        auto_ptr< BYTE > cAutoDeleteMessage( szMessage);   // insure auto-deletion.

        if ( !user->IsGod() ) {
			TextFilter.FilterMessage((char*)szMessage);//16/06/2009 filter bad words
		}

        // Chatter channels need STL strings. Convert.
        string csChannel( reinterpret_cast< const char *>( szChannel ) );
        string csMessage( reinterpret_cast< const char *>( szMessage ) );

		// ADD BY MESTOPH 16/03/2009 : Correction for shouts bugs if player not in game
		if ( user->in_game ) 
 		{
			ChatterChannels &cChatter = CPlayerManager::GetChatter();
	        cChatter.Talk( user, csChannel, csMessage );
		}
		else
		{
			_LOG_DEBUG LOG_DEBUG_LVL1, 
				"Received a channel message while not in game on account \r\n\tAccountName : %s \tPlayer IP : %s (CC talk during TP ?)",
				(LPCTSTR)user->GetFullAccountName(),
				(LPCTSTR)user->GetIP()
			LOG_	
			//user->DeletePlayer();//BLBLBL cela fait crasher les joueurs qui parlent en se teleportant
		}
		// AND MOD				

	}catch( TFCPacketException *e ){
		LOG_PACKET_ERROR( "RQ_SendChatterMessage" );
		delete e;
	}

    RQ_FOOTER( "RQ_SendChatterMessage" );

}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GetChatterUserList
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the list of users in a specific chatter channel
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    try{
        LPBYTE szChannel;

        // Get the channel from the packet.
        GET_STRING( szChannel );
        auto_ptr< BYTE > cAutoDeleteChannel( szChannel );     // insure auto-deletion.

        // Chatter channels need STL strings. Convert.
        string csChannel( reinterpret_cast< const char *>( szChannel ) );

        ChatterChannels &cChatter = CPlayerManager::GetChatter();

        cChatter.SendChannelUsers( user, csChannel );

    }catch( TFCPacketException *e ){
		LOG_PACKET_ERROR( "RQ_GetChatterUserList" );
		delete e;
	}
    
    RQ_FOOTER( "RQ_GetChatterUserList" );

}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_RemoveFromChatterChannel
//////////////////////////////////////////////////////////////////////////////////////////
//  Removes the player from a chatter channel
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    try{
        LPBYTE szChannel;

        // Get the channel from the packet.
        GET_STRING( szChannel );
        auto_ptr< BYTE > cAutoDeleteChannel( szChannel );     // insure auto-deletion.

        // Chatter channels need STL strings. Convert.
        string csChannel( reinterpret_cast< const char *>( szChannel ) );

        ChatterChannels &cChatter = CPlayerManager::GetChatter();

        cChatter.Remove( user, csChannel );

        // Send only the registered list of channels.
        cChatter.SendRegisteredChannelList( user );
	}catch( TFCPacketException *e ){
		LOG_PACKET_ERROR( "RQ_RemoveFromChatterChannel" );
		delete e;
	}
    
    RQ_FOOTER( "RQ_RemoveFromChatterChannel" );

}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GetChatterChannelList
//////////////////////////////////////////////////////////////////////////////////////////
// Returns a list of all public chatter channel
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    try{
        ChatterChannels &cChatter = CPlayerManager::GetChatter();

        // Send only the registered list of channels.
        cChatter.SendRegisteredChannelList( user );

    }catch( TFCPacketException *e ){
		LOG_PACKET_ERROR( "RQ_GetPublicChatterChannelList" );
		delete e;
	}
    
    RQ_FOOTER( "RQ_GetPublicChatterChannelList" );

}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_ToggleChatterListening
//////////////////////////////////////////////////////////////////////////////////////////
//  Junks a list of items.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    try{

        BYTE *channelID;
        BYTE listenState;

        GET_STRING( channelID );
        GET_BYTE  ( listenState );

        ChatterChannels &cChatter = CPlayerManager::GetChatter();

        cChatter.ToggleListening( user, (const char *)channelID, ( listenState == 0 ? false : true ) );
        
        // Send only the registered list of channels.
        cChatter.SendRegisteredChannelList( user );

        delete channelID;

    }catch( TFCPacketException *e ){
        LOG_PACKET_ERROR( "RQ_ToggleChatterListening" );
        delete e;
    }


    RQ_FOOTER( "RQ_ToggleChatterListening" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GetOnlinePlayerList
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;
    
    CPlayerManager::PacketUserList( user );

    RQ_FOOTER( "RQ_GetOnlinePlayerList" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GetSkillStatPoints
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

	TFCPacket sending;
	
	/////////////////////////////////////////////////////////////////////////////////
	// Returns a list of the online users.
	sending << (short)user->self->GetSkillPoints();
	sending << (short)user->self->GetStatPoints();
	
	user->self->SendPlayerMessage( sending );

    RQ_FOOTER( "RQ_GetSkillStatPoints" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GoldChange
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

	TFCPacket sending;
	
	/////////////////////////////////////////////////////////////////////////////////
	// Returns the amount of gold on the player.
	sending << (RQ_SIZE)RQ_GoldChange;
	sending << (long)user->self->GetGold();

	user->self->SendPlayerMessage( sending );

    RQ_FOOTER( "RQ_GoldChange" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_ViewGroundItemIndentContent
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    TFCPacket sending;
	
	//////////////////////////////////////////////////////////////////////////////////////////
	// Allows to view the content of an item on the ground.
	if( user->in_game ){
		WorldPos wlPos = { 0, 0, 0 };
		DWORD dwID;
		Unit *lpuGroundUnit;
		Unit *lpuIndentUnit;
		WorldMap *wl;
		WORD wIndent;
		int i;
		LPDWORD lpdwIndentList = NULL;

		try{

			msg->Get( (short *)&wlPos.X );
			msg->Get( (short *)&wlPos.Y );
			msg->Get( (long  *)&dwID );
			msg->Get( (short *)&wIndent );

			if( wIndent ){
				lpdwIndentList = new DWORD[ wIndent ];
				for( i = 0; i < wIndent; i++ ){
					msg->Get( (long *)&lpdwIndentList[ i ] );
				}
				// null-terminated
				lpdwIndentList[ wIndent ] = 0;
			}		

			wl = TFCMAIN::GetWorld( user->self->GetWL().world );
			
			if( wl ){
				lpuGroundUnit = wl->FindNearUnit(wlPos, dwID);

				if( lpuGroundUnit ){
					// Get the indented item.
					lpuIndentUnit = lpuGroundUnit->GetIndentItem( lpdwIndentList );
					
					if( lpuIndentUnit ){
						sending << (RQ_SIZE)RQ_ViewGroundItemIndentContent;
						lpuIndentUnit->PacketBackpack( sending );
						user->self->SendPlayerMessage( sending );						
					}
				}
			}				

			delete lpdwIndentList;

		}catch( TFCPacketException *e ){
			LOG_PACKET_ERROR( "RQ_ViewGroundItemIndentContent" );
			delete e;
			if( lpdwIndentList )
				delete lpdwIndentList;
		}
	}

    RQ_FOOTER( "RQ_ViewGroundItemIndentContent" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_SendTrainSkillList
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

	//////////////////////////////////////////////////////////////////////////////////////////
	// When sent by the client, this request is used to train a skill.
	WorldPos wlPos = { 0, 0, 0 };
	DWORD dwID;
	Unit *lpuTarget;
	NPC_DATA npcData;
	TRAIN_DATA npcTrainData;
	WorldMap *world = NULL;
	WORD wNbSkills = 0;

	try{
		msg->Get( (short *)&wlPos.X );	// Approximative NPC position
		msg->Get( (short *)&wlPos.Y );
		msg->Get( (long  *)&dwID );		// ID of NPC who trains

		world = TFCMAIN::GetWorld( user->self->GetWL().world );
		
		if( world ){
			lpuTarget = world->FindNearUnit( wlPos, dwID );

			if( lpuTarget ){
                MultiLock( user->self, lpuTarget );

				msg->Get( (short *)&wNbSkills );	// Quantity of skills to train	

				npcData.DataID = __TRAIN_DATA;	// Train data exchange with NPC
				
				int i;
				for( i = 0; i < wNbSkills; i++ ){
					npcTrainData.wSkillID = npcTrainData.wSkillPnts = 0;
			
					msg->Get( (short *)&npcTrainData.wSkillID );	// ID of the skill to be trained
					msg->Get( (short *)&npcTrainData.wSkillPnts );	// Number of skill pnts to train
					
					// Init the NPC data exchange structure
					npcData.Data = &npcTrainData;
					
					// Then shoot the training request to the NPC
                    try{
                        lpuTarget->SendUnitMessage( MSG_OnNPCDataExchange, lpuTarget, NULL, user->self, &npcData, NULL );
                    }catch( ... ){
                        _LOG_DEBUG
                            LOG_CRIT_ERRORS,
                            "Crashed while sending message MSG_OnNPCDataExchange in RQFUNC_SendTrainSkillList"
                        LOG_
                                                
                        _LOG_DEBUG
                            LOG_CRIT_ERRORS,
                            "Packet: %s", 
                            msg->GetDebugPacketString()
                        LOG_
                        throw;
                    }
				}

                user->self->Unlock();
                lpuTarget->Unlock();
            }else{
                TFCPacket sending;
                sending << (RQ_SIZE)RQ_MissingUnit;                
                sending << (long)dwID;
                sending << (RQ_SIZE)RQ_SendTrainSkillList;

                user->self->SendPlayerMessage( sending );
            }
		}
					
	}catch( TFCPacketException *e ){
		LOG_PACKET_ERROR( "RQ_SendTrainSkillList" );
		delete e;
	}

    RQ_FOOTER( "RQ_SendTrainSkillList" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_SendTeachSkillList
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;
    
    //////////////////////////////////////////////////////////////////////////////////////////
	// When sent by the client, this request is used to be taught a skill
	WorldPos wlPos = { 0, 0, 0 };
	DWORD dwID;
	Unit *lpuTarget;
	
	WorldMap *world = NULL;

	try{
		msg->Get( (short *)&wlPos.X );	// Approximative NPC position
		msg->Get( (short *)&wlPos.Y );			
		msg->Get( (long  *)&dwID );		// ID of NPC who trains		
		
		// Fetch all trained skills until the packet is empty.
		list< WORD > taughtSkills;
		try{
			while(1){
				WORD skillId = 0;
				GET_WORD( skillId );
				taughtSkills.push_back( skillId );
			};
		}catch( TFCPacketException *e ){
			delete e;
		}


		wlPos.world = user->self->GetWL().world;


		world = TFCMAIN::GetWorld( user->self->GetWL().world );

		if( world ){			
			// then shoot the talk to the targetted NPC
			lpuTarget = world->FindNearUnit( wlPos, dwID );
			if( lpuTarget ){
                
                MultiLock( user->self, lpuTarget );

				// For all taught skills.
				list< WORD >::iterator a;
				for( a = taughtSkills.begin(); a != taughtSkills.end(); a++ ){
					
					TEACH_DATA npcTeachData = { *a };
					// Init the NPC data exchange structure
					NPC_DATA npcData = { __TEACH_DATA, &npcTeachData };

		            try{
			            lpuTarget->SendUnitMessage(MSG_OnNPCDataExchange, lpuTarget, NULL, user->self, &npcData, NULL );
				    }catch( ... ){
					    _LOG_DEBUG
						    LOG_CRIT_ERRORS,
							"Crashed while sending message MSG_OnNPCDataExchange in RQFUNC_SendTeachSkillList"
						LOG_
                                            
						_LOG_DEBUG
							LOG_CRIT_ERRORS,
							"Packet: %s", 
							msg->GetDebugPacketString()
						LOG_
						throw;
					}
				}

                user->self->Unlock();
                lpuTarget->Unlock();
            }else{
                TFCPacket sending;
                sending << (RQ_SIZE)RQ_MissingUnit;
                sending << (long)dwID;
                sending << (RQ_SIZE)RQ_SendTeachSkillList;

                user->self->SendPlayerMessage( sending );
            }
		}
					
	}catch( TFCPacketException *e ){
		LOG_PACKET_ERROR( "RQ_SendTeachSkillList" );
		delete e;		
	}

    RQ_FOOTER( "RQ_SendTeachSkillList" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_SendBuyItemList
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQ_PlayerMove
//
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

	try{
		DWORD dwID;
		WORD wNbItems;
		int i;
		Unit *lpShopUnit;
		WorldMap *wl;
		NPC_DATA npcData = { 0, NULL };
		SHOP_DATA npcShopData = { 0, 0, 0 };

		// Init the NPC data exchange structure
		npcData.DataID = __SHOP_DATA;
		npcData.Data = &npcShopData;

		WorldPos wlPos = { 0, 0, user->self->GetWL().world };
		
		wl = TFCMAIN::GetWorld( wlPos.world );

		if( wl ){
			npcShopData.Action = __BUY;

			GET_WORD( wlPos.X );
			GET_WORD( wlPos.Y );
			GET_LONG( dwID );

			// Find the unit
			lpShopUnit = wl->FindNearUnit( wlPos, dwID );

			if( lpShopUnit ){
                
                MultiLock( user->self, lpShopUnit );

				GET_WORD( wNbItems );

				for( i = 0; i < wNbItems; i++ ){
					GET_WORD( npcShopData.Item );
					GET_WORD( npcShopData.wQuantity );
                    try{
                        lpShopUnit->SendUnitMessage(MSG_OnNPCDataExchange, lpShopUnit, NULL, user->self, &npcData, NULL );
                    }catch( ... ){
                        _LOG_DEBUG
                            LOG_CRIT_ERRORS,
                            "Crashed while sending message MSG_OnNPCDataExchange in RQFUNC_SendBuyItemList"
                        LOG_
                                                
                        _LOG_DEBUG
                            LOG_CRIT_ERRORS,
                            "Packet: %s", 
                            msg->GetDebugPacketString()
                        LOG_
                        throw;
                    }

				}
                // Update backpack.
                {
                    TFCPacket sending;
				    sending << (RQ_SIZE)RQ_ViewBackpack;
				    sending << (char)0;	// Don't show backpack..
				    sending << (long)user->self->GetID();
				    user->self->PacketBackpack( sending );
                    user->self->SendPlayerMessage( sending );

                    // Update gold
                    user->self->SetGold( user->self->GetGold() );
                }
                
                user->self->Unlock();
                lpShopUnit->Unlock();
            }else{
                TFCPacket sending;
                sending << (RQ_SIZE)RQ_MissingUnit;
                sending << (long)dwID;
                sending << (RQ_SIZE)RQ_SendBuyItemList;

                user->self->SendPlayerMessage( sending );
            }
        }
	}catch( TFCPacketException *e ){
		LOG_PACKET_ERROR( "RQ_SendBuyItemList" );
		delete e;
	}

    RQ_FOOTER( "RQ_SendBuyItemList" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_SendSellItemList
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQ_PlayerMove
//
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

	try{
		DWORD dwID;
		WorldMap *wl;
		Unit *lpShopUnit;
		NPC_DATA npcData = { 0, NULL };
		SHOP_DATA npcShopData = { 0, 0, 0 };

		// Init the NPC data exchange structure
		npcData.DataID = __SHOP_DATA;
		npcData.Data = &npcShopData;

		WorldPos wlPos = { 0, 0, user->self->GetWL().world };		
		
		wl = TFCMAIN::GetWorld( wlPos.world );

		if( wl ){
			npcShopData.Action = __SELL;

			GET_WORD( wlPos.X );	// NPC pos
			GET_WORD( wlPos.Y );
			GET_LONG( dwID );		// NPC ID

			// Find the unit
			lpShopUnit = wl->FindNearUnit( wlPos, dwID );

			if( lpShopUnit ){
                MultiLock( user->self, lpShopUnit );

                // Fetch shop datas until packet ends.
                try{
                    while( 1 ){
                        GET_LONG( npcShopData.ID );	// ID of the backpack item to sell.
                        GET_LONG( npcShopData.wQuantity );
                        
                        lpShopUnit->SendUnitMessage(MSG_OnNPCDataExchange, lpShopUnit, NULL, user->self, &npcData, NULL );
                    }
                }catch( TFCPacketException * e){
                    delete e;
                }                

                user->self->Unlock();
                lpShopUnit->Unlock();
            }else{
                TFCPacket sending;
                sending << (RQ_SIZE)RQ_MissingUnit;
                sending << (long)dwID;
                sending << (RQ_SIZE)RQ_SendSellItemList;

                user->self->SendPlayerMessage( sending );
            }
		}

	}catch( TFCPacketException *e ){
		LOG_PACKET_ERROR( "RQ_SendSellItemList" );
		delete e;
	}

    RQ_FOOTER( "RQ_SendSellItemList" );
}

#define RQTRAIN_STAT( stat, text )	GET_BYTE( bTrain );\
	if( bTrain != 0 ){\
		dwStat = user->self->GetTrue##stat\
		(); if( user->self->UseStatPnts( bTrain ) ){\
			user->self->Set##stat\
			( (WORD)( dwStat + bTrain ) );\
GAME_RULES::CalcStatBonus( STAT_##stat\
	, bTrain, 0,user->self );\
            csText.Format( "Trained %u points in " text ". %u -> %u.", bTrain, dwStat, user->self->GetTrue##stat\
            () );\
            csReport += csText;\
		}\
	}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_SendStatTrain
//////////////////////////////////////////////////////////////////////////////////////////
// Sent by the client to train stats
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

	BYTE bTrain;
	DWORD dwStat;
    CString csReport;
    CString csText;

    csReport.Format( "Player %s trains stats.", (LPCTSTR)user->self->GetTrueName() );

	try{
        user->self->Lock();

		RQTRAIN_STAT( STR, "STR" );
		RQTRAIN_STAT( END, "END" );				
		RQTRAIN_STAT( AGI, "AGI" );
		GET_BYTE( bTrain ); // Get the byte but drop the training of willpower
		RQTRAIN_STAT( WIS, "WIS" );
		RQTRAIN_STAT( INT, "INT" );
		// ADD BY MESTOPH 
		GET_BYTE( bTrain ); // Get the byte but drop the training of luck
		// END

        user->self->Unlock();
        
        _LOG_PC
            LOG_MISC_1,
            (char *)(LPCTSTR)csReport
        LOG_
	}catch( TFCPacketException *e ){
		LOG_PACKET_ERROR( "RQ_SendStatTrain" );
		delete e;
	}

    RQ_FOOTER( "RQ_SendStatTrain" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_QueryItemName
//////////////////////////////////////////////////////////////////////////////////////////
// Sent by the client to query an item name on the backpack
// 
(
 PACKET_FUNC_PROTOTYPE // ...
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

	try
	{
		DWORD dwID;
		BYTE  whereToSearchFrom;
		enum ePlacesToSearch { PL_SEARCHBACKPACK=0, PL_SEARCHCHEST=1, PL_SEARCHMYTRADE=2, PL_SEARCHOTHERTRADE=3 };
		
		GET_BYTE( whereToSearchFrom );
		GET_LONG( dwID );

		BOOL boFound = FALSE;

		if (whereToSearchFrom == PL_SEARCHBACKPACK) {

			TemplateList<Unit> *lptluBackpack;

			if( user->self->GetGameOpContext() != NULL ){
				lptluBackpack = user->self->GetGameOpContext()->GetBackpack();
			}else{
				lptluBackpack = user->self->GetBackpack();
			}		

			lptluBackpack->Lock();
			lptluBackpack->ToHead();
			while( lptluBackpack->QueryNext() && !boFound ){
				Objects *obj = static_cast< Objects * >( lptluBackpack->Object() );

				if( obj->GetID() == dwID ){
					TFCPacket sending;
					sending << (RQ_SIZE)RQ_QueryItemName;
					sending << (char)PL_SEARCHBACKPACK;
					sending << (long)obj->GetID();
					CString csName = obj->GetName( user->self->GetLang() );
					sending << (CString)( csName );
					user->self->SendPlayerMessage( sending );
					boFound = TRUE;                
				}
			}
			lptluBackpack->Unlock();
		}

		else if (whereToSearchFrom == PL_SEARCHCHEST) {

			if (boFound == FALSE) {
				ItemContainer *lpicChest;
				if (user->self->GetGameOpContext() != NULL) {
					lpicChest = user->self->GetGameOpContext()->GetChest();
				} else {
					lpicChest = user->self->GetChest();
				}
				TemplateList<Objects> *tlChestList = lpicChest->LockAndGetList();
				tlChestList->ToHead();
				while( tlChestList->QueryNext() && !boFound ){
					Objects *obj = tlChestList->Object();

					if( obj->GetID() == dwID ){
						TFCPacket sending;
						sending << (RQ_SIZE)RQ_QueryItemName;
						sending << (char)PL_SEARCHCHEST;
						sending << (long)obj->GetID();
						CString csName = obj->GetName( user->self->GetLang() );
						sending << (CString)( csName );
						user->self->SendPlayerMessage( sending );
						boFound = TRUE;                
					}
				}
				lpicChest->UnlockAndReleaseList();
			}
		}

		else if (whereToSearchFrom == PL_SEARCHMYTRADE) {
			CString itemName("");
			BOOL itemFound = user->self->GetTradeMgr2()->GetItemName(dwID, itemName, user->self->GetLang());
			if (itemFound == TRUE) {
				TFCPacket sending;
				sending << (RQ_SIZE)RQ_QueryItemName;
				sending << (char)PL_SEARCHMYTRADE;
				sending << (long)dwID;
				sending << (CString)( itemName );
				user->self->SendPlayerMessage( sending );
			}
		}

		else if (whereToSearchFrom == PL_SEARCHOTHERTRADE) {
			CString itemName("");
			BOOL itemFound = user->self->GetTradeMgr2()->GetItemNameFromOther(dwID, itemName, user->self->GetLang());
			if (itemFound == TRUE) {
				TFCPacket sending;
				sending << (RQ_SIZE)RQ_QueryItemName;
				sending << (char)PL_SEARCHOTHERTRADE;
				sending << (long)dwID;
				sending << (CString)( itemName );
				user->self->SendPlayerMessage( sending );
			}
		}

	}catch( TFCPacketException *e ){
		LOG_PACKET_ERROR( "RQ_QueryItemName" );
		delete e;
	}

    RQ_FOOTER( "RQ_QueryItemName" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GetNearItems
//////////////////////////////////////////////////////////////////////////////////////////
// Sent by the client to retreive the local surrounding objects
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

	if( user->boPreInGame || user->in_game ){
		WorldPos wlPos = user->self->GetWL();
		WorldMap *lpWorld = TFCMAIN::GetWorld( wlPos.world );				
		if( lpWorld ){
			// Then send the list of all objects near the player.

            TFCPacket sending;

			int read;
			read = lpWorld->packet_inview_units( wlPos, sending, _DEFAULT_RANGE, user->self );
            if( read > 0 ){	
		        user->self->SendPlayerMessage( sending );
			}else{

			//BLBLBL Anti black screen : we always send a getneatitems :
			// Sends this to ensure player wont get stuck in a black screen when loading.
			//BLBLBLBL moved here instead of (after TFCPAcket sending)
			sending << (RQ_SIZE)RQ_GetNearItems;
			user->self->SendPlayerMessage( sending );
			sending.Destroy();
			
			}
		}
	}
    RQ_FOOTER( "RQ_GetNearItems" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_SendSpellList
//////////////////////////////////////////////////////////////////////////////////////////
// This request is sent by the client to query the list of spells owned by the player
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;
    try{
		BYTE bUpdate = 0;

		GET_BYTE( bUpdate );
		
		TFCPacket sending;
		user->self->PacketSpells( sending, bUpdate );
		user->self->SendPlayerMessage( sending );

	}catch( TFCPacketException *e ){
		LOG_PACKET_ERROR( "RQ_SendSpellList" );
		delete e;
	}

    RQ_FOOTER( "RQ_SendSpellList" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_QueryServerVersion
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the current server version and a list of available patch servers.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;
    
    //CString csText = "207.96.243.12";

    TFCPacket sending;    

    sending << (RQ_SIZE)RQ_QueryServerVersion;
    sending << static_cast< long >( TFCServer->dwVersion );
    
    vPatchServers.Lock();
    
    sending << static_cast< short >( vPatchServers.size() );
    
    vector< PATCH_SERVER >::iterator i;
    for( i = vPatchServers.begin(); i != vPatchServers.end(); i++ ){
        if( (*i).wPort == 0 ){
            sending << static_cast< short >( 11679 );
        }else{
            sending << static_cast< short >( (*i).wPort );
        }
        sending << (CString &)(*i).csIP;
    }

    vPatchServers.Unlock();

    WorldPos wlPos = { -1, -1, -1 };

    CPacketManager::SendPacket( sending, sockAddr, -1, wlPos, FALSE );

    RQ_FOOTER( "RQ_QueryServerVersion" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_MessageOfDay
//////////////////////////////////////////////////////////////////////////////////////////
// Message of the day querying packet.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;


    TFCPacket sending;

	sending.SetPacketSeedID( msg->GetPacketSeedID() );
    
    CString csText;
    
    sending << (RQ_SIZE)RQ_MessageOfDay;

    // If a motd was specified.
    if( csMotD != "\\INVALID\\" ){
         

        HANDLE hFile = CreateFile(
            (LPCTSTR)csMotD,
            GENERIC_READ,
            FILE_SHARE_READ,
            NULL,
            OPEN_EXISTING,
            0,
            NULL
        );

        // If file could be read.
        if( hFile != INVALID_HANDLE_VALUE ){
            LPBYTE lpBuffer = (LPBYTE)csText.GetBuffer( GetFileSize( hFile, NULL ) );
            DWORD dwRead = 0;

            ReadFile( hFile, lpBuffer, GetFileSize( hFile, NULL ) - 1, &dwRead, NULL );           

            csText.ReleaseBuffer( GetFileSize( hFile, NULL ) - 1 );

            TRACE( "\r\nMOTD = %s.", csText );
            CloseHandle( hFile );
        }
    }

    sending << (CString &)csText;

    WorldPos wlPos = { -1, -1, -1 };
    CPacketManager::SendPacket( sending, sockAddr, -1, wlPos, FALSE );

    RQ_FOOTER( "RQ_MessageOfTheDay" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_PuppetInformation
//////////////////////////////////////////////////////////////////////////////////////////
// Called by the client to query puppet information about a certain unit.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    try{
        DWORD dwID;
        WorldPos wlPos = { 0, 0, user->self->GetWL().world };
        Unit *lpUnit;

        GET_LONG( dwID );
        GET_WORD( wlPos.X );
        GET_WORD( wlPos.Y );

        TRACE( "\r\nQuerying pupping info for unit ID %u at ( %u, %u ).", dwID, wlPos.X, wlPos.Y );

        WorldMap *wlWorld = TFCMAIN::GetWorld( user->self->GetWL().world );

        if( wlWorld != NULL ){
            lpUnit = wlWorld->FindNearUnit( wlPos, dwID );
			if( lpUnit != NULL ){                
                TFCPacket sending;
                lpUnit->PacketPuppetInfo( sending );
                user->self->SendPlayerMessage( sending );
            }else{
                TFCPacket sending;
                sending << (RQ_SIZE)RQ_MissingUnit;
                sending << (long)dwID;
                sending << (RQ_SIZE)RQ_PuppetInformation;
                
                user->self->SendPlayerMessage( sending );
            }
        }
    }catch( TFCPacketException *e ){
		LOG_PACKET_ERROR( "RQ_PuppetInformation" );
		delete e;
    }

    RQ_FOOTER( "RQ_PuppetInformation" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_QueryUnitExistence
//////////////////////////////////////////////////////////////////////////////////////////
//  Queries the unit's existence.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    try{
        WorldPos wlPos = { 0, 0, user->self->GetWL().world };
        DWORD dwID;
        
        // Fetch packet information
        GET_LONG( dwID );
        GET_WORD ( wlPos.X );
        GET_WORD ( wlPos.Y );

        // Get the world instance.
        WorldMap *wlWorld = TFCMAIN::GetWorld( wlPos.world );
        if( wlWorld != NULL ){
            // Try to find the unit where 
            Unit *lpUnit = wlWorld->FindNearUnit( wlPos, dwID );
            
            bool boMissingUnit = false;
            // If the unit was not found.
            if( lpUnit == NULL ){
                boMissingUnit = true;
            }else{
                // If this unit is a character
                if( lpUnit->GetType() == U_PC ){
                    // Get its underlying player structure
                    Players *lpPlayer = static_cast< Character * >( lpUnit )->GetPlayer();

                    // If packets are not allowed to be send to this unit.
                    if( lpPlayer != NULL && 
                        !lpPlayer->self->GetInvisibleQuery()->SendPacketTo( user->self )
                    ){
                        // Declare it non-existent.
                        boMissingUnit = true;
                    }
                }
            }
            // If the unit was not found.
            if( boMissingUnit ){
                // Send a missing unit packet.
                TFCPacket sending;
                sending << (RQ_SIZE)RQ_MissingUnit;
                sending << (long)dwID;
                sending << (RQ_SIZE)RQ_QueryUnitExistence;
                
                user->self->SendPlayerMessage( sending );
            }else{
                // Packet the unit's popup information (the unit is certain to be non-NULL)
                TFCPacket sending;
                lpUnit->PacketPopup( lpUnit->GetWL(), sending );

                // Send that packet to the requester
                user->self->SendPlayerMessage( sending );
            }
        }
    }catch( TFCPacketException *e ){
        LOG_PACKET_ERROR( "RQ_QueryUnitExistence" );
        delete e;                                  
    }
    
    RQ_FOOTER( "RQ_QueryUnitExistence" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_UseItemByAppearance
//////////////////////////////////////////////////////////////////////////////////////////
//  Queries the unit's existence.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    try{
        WORD wAppearance = 0;

        GET_WORD( wAppearance );

		if ( !user->in_game ) return;

        // If character could not use such an item.
		// ADD BY MESTOPH : Check if pointer is NULL
		if( user->self == NULL )
		{
			_LOG_DEBUG LOG_DEBUG_LVL1, "user->self (%s) is NULL in UseItemByAppearance", user->GetAccount() LOG_;
		}
        else /* END ADD */ if( !user->self->UseItemByAppearance( wAppearance, user->self ) )
		{

            // Send a message telling the player that its out of this item.
            TFCPacket sending;
            sending << (RQ_SIZE)RQ_CannotFindItemByAppearance;
            sending << (short)wAppearance;

            user->self->SendPlayerMessage( sending );
        }

    }catch( TFCPacketException *e ){
        LOG_PACKET_ERROR( "RQ_UseItemByAppearance" );
        delete e;
    }
    
    RQ_FOOTER( "RQ_UseItemByAppearance" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_UpdateGroupMembers
//////////////////////////////////////////////////////////////////////////////////////////
// Sent by the client to receive a group members update.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{

}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_UpdateGroupInviteList
//////////////////////////////////////////////////////////////////////////////////////////
// Sent by the client to receive an invite list update.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{

}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GroupInvite
//////////////////////////////////////////////////////////////////////////////////////////
// Sent by the client to invite someone into his/her group. If group doesn't exist, it is
// created.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    try
	{
        DWORD dwID;
        GET_LONG ( dwID );

        if( dwID == user->self->GetID() ){
            user->self->SendSystemMessage(
                _STR( 7502, user->self->GetLang() )
            );
            return;
        }

        bool newlyCreated = false;

        // If the player isn't already in a group.
        if( user->self->GetGroup() == NULL )
		{
            // If a new group could not be created.
            if( Group::CreateGroup( user->self ) == NULL ){
                // Notify the user.
                user->self->SendSystemMessage( _STR( 2841, user->self->GetLang() ) );
            }
			else
			{
                newlyCreated = true;
            }
        }

        // If the group was created.
        if( user->self->GetGroup() != NULL )
		{
            bool dismissGroup = true;
            
            WorldPos wlPos = { 0, 0, user->self->GetWL().world };
            
            GET_WORD ( wlPos.X );
            GET_WORD ( wlPos.Y );

            WorldMap *wlWorld = TFCMAIN::GetWorld( user->self->GetWL().world );

            // World should never be NULL! Means that the GetWL().world is screwed up or wrong.
            ASSERT( wlWorld != NULL );            
            if( wlWorld != NULL )
			{
                
                // Try to find the unit.
                Unit *lpUnit = wlWorld->FindNearUnit( wlPos, dwID );

                if( lpUnit != NULL )
				{
                    // If the unit is a PC.
                    if( lpUnit->GetType() == U_PC )
					{
                        // Cast its character.
                        Character *lpCharacter = static_cast< Character * >( lpUnit );

                        // If target player isn't already in a group, or is
                        // in the asker's group.
                        if( lpCharacter->GetGroup() == NULL || lpCharacter->GetGroup() == user->self->GetGroup() )
						{
                        
                            // If the player could be invited.
                            if( user->self->GetGroup()->Invite( user->self, lpCharacter ) )
							{
                                // Don't dismiss the group.
                                dismissGroup = false;
                            }
                        }
						else
						{
                            // Notify player.
                            user->self->SendSystemMessage( _STR( 2843, user->self->GetLang() ) );
                        }
                    }
					else
					{
                        // Otherwise notify player.
                        user->self->SendSystemMessage( _STR( 2842, user->self->GetLang() ) );
                    }

                    // If the group was created with this request,
                    // and the request failed to invite anyone.
                    if( newlyCreated && dismissGroup )
					{
                        // Dismiss the group.
                        user->self->GetGroup()->Dismiss( user->self );
                    }
                }
            }
        }
    }catch( TFCPacketException *e ){
        LOG_PACKET_ERROR( "RQ_GroupInvite" );
        delete e;
    }
    
    RQ_FOOTER( "RQ_GroupInvite" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GroupJoin
//////////////////////////////////////////////////////////////////////////////////////////
// Allows a player to joins a group. The user must first have been invited by a group.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    // If user has binded group.
    if( user->self->GetGroup() != NULL ){
        // Try to join it.
        if( user->self->GetGroup()->Join( user->self ) )
		{
            // Notify player of succesfull addition to group.
            TFormat format;
            
            user->self->SendSystemMessage(
                format( 
                    _STR( 2844, user->self->GetLang() ), 
                    user->self->GetGroup()->GetLeader()->GetTrueName()
                )
            );
        }
    }

    RQ_FOOTER( "RQ_GroupJoin" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GroupLeave
//////////////////////////////////////////////////////////////////////////////////////////
// Allows a player to leave a group or refuse an invitation.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;
    
    // If user has a binded group
    if( user->self->GetGroup() != NULL ){
        // Leave it
        user->self->GetGroup()->Dismiss( user->self );
    }

    RQ_FOOTER( "RQ_GroupLeave" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GroupKick
//////////////////////////////////////////////////////////////////////////////////////////
// Allows a group leader to kickout a particular user.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    try{    
        // If player has a group.
        if( user->self->GetGroup() != NULL ){
            // If the leader of this group is this player.
            if( user->self->GetGroup()->GetLeader() == user->self ){
                // Get the ID of the character to kick.
                DWORD dwID;
                GET_LONG( dwID );

                // Dismiss this character.
                user->self->GetGroup()->Dismiss( dwID );
            }
        }
    }catch( TFCPacketException *e ){
        LOG_PACKET_ERROR( "RQ_GroupKick" );
        delete e;
    }

    RQ_FOOTER( "RQ_GroupKick" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_GroupToggleAutoSplit
//////////////////////////////////////////////////////////////////////////////////////////
// Toggles gold auto-splitting for groups.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    try{    
        // If player has a group.
        if( user->self->GetGroup() != NULL ){
            // If the leader of this group is this player.
            if( user->self->GetGroup()->GetLeader() == user->self ){

                BYTE bNewState = 0;

                GET_BYTE( bNewState );

                user->self->GetGroup()->ToggleAutoSplit( bNewState == 0 ? false : true );

            }
        }
    }catch( TFCPacketException *e ){
        LOG_PACKET_ERROR( "RQ_GroupToggleAutoSplit" );
        delete e;
    }

    RQ_FOOTER( "RQ_GroupToggleAutoSplit" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_JunkItems
//////////////////////////////////////////////////////////////////////////////////////////
//  Junks a list of items.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    try
	{

        DWORD id;
        DWORD qty;

        GET_LONG( id );
        GET_LONG( qty );

        user->self->JunkItems( id, qty, false );

    }
	catch( TFCPacketException *e )
	{
        LOG_PACKET_ERROR( "RQ_JunkItems" );
        delete e;
    }


    RQ_FOOTER( "RQ_JunkItems" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_TogglePage
//////////////////////////////////////////////////////////////////////////////////////////
//  Junks a list of items.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    try{

        BYTE newState;

        GET_BYTE( newState );

        if( newState == 0 ){
            user->TogglePage( false );
        }else{
            user->TogglePage( true );
        }

    }catch( TFCPacketException *e ){
        LOG_PACKET_ERROR( "RQ_TogglePage" );
        delete e;
    }

    RQ_FOOTER( "RQ_TogglePage" );
}

struct RQSTRUCT_QueryNameExistence{
    CString name;
    sockaddr_in sockAddr;
};

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::AsyncRQFUNC_QueryNameExistence
//////////////////////////////////////////////////////////////////////////////////////////
//  Asynchronously checks for a name into the database.
// 
(
 LPVOID lpData // Data.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQSTRUCT_QueryNameExistence *rq = reinterpret_cast< RQSTRUCT_QueryNameExistence * >( lpData );

    TFCPacket sending;
    
	if( !Character::IsNameValid( rq->name ) ){
        sending << (RQ_SIZE)RQ_QueryNameExistence;
        sending << (char)2; // name is invalid.
	}else{
        if( Players::NameExists( std::string( rq->name ) ) ){     
			sending << (RQ_SIZE)RQ_QueryNameExistence;
			sending << (char)1; // name exists
		}else{
			sending << (RQ_SIZE)RQ_QueryNameExistence;
			sending << (char)0;
		}
	}

    // Send packet to requesting IP.
    WorldPos wlPos = {-1,-1,-1};
    CPacketManager::SendPacket( sending, rq->sockAddr, -1, wlPos, FALSE );

    // Delete name string allocated in RQFUNC_QueryNameExistence.
    delete rq;
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_QueryNameExistence
//////////////////////////////////////////////////////////////////////////////////////////
//  Junks a list of items.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    try{

        LPBYTE name;

        GET_STRING( name );

        RQSTRUCT_QueryNameExistence *rq = new RQSTRUCT_QueryNameExistence;

        rq->name     = reinterpret_cast< const char * >( name );
        rq->sockAddr = sockAddr;        

        FormatPlayerName::Format( &rq->name );

        AsyncFuncQueue::GetMainQueue()->Call( AsyncRQFUNC_QueryNameExistence, rq );

        delete name;
    }catch( TFCPacketException *e ){
        LOG_PACKET_ERROR( "RQ_QueryNameExistence" );
        delete e;
    }

    RQ_FOOTER( "RQ_QueryNameExistence" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_QueryPatchServerInfo
//////////////////////////////////////////////////////////////////////////////////////////
// Queries patch server information
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    TFCPacket sending;

	sending.SetPacketSeedID( msg->GetPacketSeedID() );

    sending << (RQ_SIZE)RQ_QueryPatchServerInfo;
    sending << static_cast< long >( TFCServer->dwVersion );
    
    webPatchServer.Lock();
        
    sending << (CString &)webPatchServer.csIP;        
    sending << (CString &)webPatchServer.csImagePath;
    sending << (CString &)webPatchServer.csUserName;
    sending << (CString &)webPatchServer.csPassword;
    sending << (short)IntlText::GetDefaultLng();
    
    webPatchServer.Unlock();

    WorldPos wlPos = { -1, -1, -1 };
    CPacketManager::SendPacket( sending, sockAddr, -1, wlPos, FALSE );

    RQ_FOOTER( "RQ_QueryPatchServerInfo" )
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_Rob
//////////////////////////////////////////////////////////////////////////////////////////
//  Junks a list of items.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    try{
        DWORD objId = 0;

        GET_LONG( objId );

        user->self->Rob( objId );
    }catch( TFCPacketException *e ){
        LOG_PACKET_ERROR( "RQ_Rob" );
        delete e;
    }

    RQ_FOOTER( "RQ_Rob" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_AuthenticateServerVersion
//////////////////////////////////////////////////////////////////////////////////////////
// Authenticates the server version.
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
   RQ_HEADER;
   try{
        if( user->boLockedOut ){
            return;
        }

        DWORD clientVersion = 0;

        GET_LONG( clientVersion );

        TFCPacket sending;

		sending.SetPacketSeedID( msg->GetPacketSeedID() );

        if( clientVersion == TFCServer->dwVersion ){
            sending << (RQ_SIZE)RQ_AuthenticateServerVersion;
            sending << (long)1;

            // Allow access to the user.
            user->registred = TRUE;
        }else{
            sending << (RQ_SIZE)RQ_AuthenticateServerVersion;
            sending << (long)0;
        }

        user->self->SendPlayerMessage( sending );

    }catch( TFCPacketException *e ){
        LOG_PACKET_ERROR( "RQ_AuthenticateServerVersion" );
        delete e;
    }


    RQ_FOOTER( "RQ_AuthenticateServerVersion" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_ChestAddItemFromBackpack
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;


		/***********************************************************************************************/
	// Moves an item from the backpack to the chest
	DWORD dwItemID, dwQty;
	try{
		msg->Get(&dwItemID);
		msg->Get(&dwQty);
		user->self->MoveObjectFromBackpackToChest2(dwItemID, dwQty);
	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_ChestAddItemFromBackpack" )
		delete e;		
	}

    RQ_FOOTER( "RQ_ChestAddItemFromBackpack" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_ChestRemoveItemToBackpack
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;


	/***********************************************************************************************/
	// Moves an item from the chest to the backpack
	DWORD dwItemID, dwQty;
	try{
		msg->Get(&dwItemID);
		msg->Get(&dwQty);

		user->self->MoveObjectFromChestToBackpack2(dwItemID, dwQty);

	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_ChestRemoveItemToBackpack" )
		delete e;		
	}

    RQ_FOOTER( "RQ_ChestRemoveItemToBackpack" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_TradeInvite
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    RQ_HEADER;

    try{
		// Grab ID and pos, try to find the unit near this coords, if found, call TradeInvite function!
        DWORD dwID;
        GET_LONG ( dwID );

        WorldPos wlPos = { 0, 0, user->self->GetWL().world };
        GET_WORD ( wlPos.X );
        GET_WORD ( wlPos.Y );
        WorldMap *wlWorld = TFCMAIN::GetWorld( user->self->GetWL().world );

        // World should never be NULL! Means that the GetWL().world is screwed up or wrong.
        ASSERT( wlWorld != NULL );            
        if( wlWorld != NULL ){
            // Try to find the unit.
            Unit *lpUnit = wlWorld->FindNearUnit( wlPos, dwID );
            if( lpUnit != NULL ){
                // If the unit is a PC.
                if( lpUnit->GetType() == U_PC ){
                    // Cast its character.
                    Character *lpCharacter = static_cast< Character * >( lpUnit );
					user->self->TradeRequest(lpCharacter);
                }else{
                    // Otherwise notify player.
					//NEED ATTENTION HERE
                    user->self->SendSystemMessage( _STR( 12951, user->self->GetLang() ) );
                }
            }
        }
    }catch( TFCPacketException *e ){
        LOG_PACKET_ERROR( "RQ_TradeInvite" );
        delete e;
    }
    
    RQ_FOOTER( "RQ_TradeInvite" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_TradeCancel
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;


	try{
		user->self->TradeCancel();
	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_TradeCancel" )
		delete e;		
	}

    RQ_FOOTER( "RQ_TradeCancel" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_TradeSetStatus
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;

	try{
		WORD newStatus;
		GET_WORD(newStatus);
		user->self->TradeSetStatus((TradeMgr2::Status::CharacterStatus)newStatus);
	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_TradeSetStatus" )
		delete e;		
	}

    RQ_FOOTER( "RQ_TradeSetStatus" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_TradeAddItemFromBackpack
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;

	try{
		DWORD dwObjID, dwObjQty;
		GET_LONG(dwObjID);
		GET_LONG(dwObjQty);
		user->self->TradeAddItemFromBackpack(dwObjID, dwObjQty);
	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_TradeAddItemFromBackpack" )
		delete e;		
	}

    RQ_FOOTER( "RQ_TradeAddItemFromBackpack" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_TradeRemoveItemToBackpack
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;

	try{
		DWORD dwObjID, dwObjQty;
		GET_LONG(dwObjID);
		GET_LONG(dwObjQty);
		user->self->TradeRemoveItemToBackpack(dwObjID, dwObjQty);
	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_TradeRemoveItemToBackpack" )
		delete e;		
	}

    RQ_FOOTER( "RQ_TradeRemoveItemToBackpack" );
}
//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_TradeClear
//////////////////////////////////////////////////////////////////////////////////////////
// Message handler of packet type RQFUNC_
//
(
 PACKET_FUNC_PROTOTYPE // Packet sent to request, currently seeked after packet type.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;

	user->self->TradeClearItemsFromTrade();

    RQ_FOOTER( "RQ_TradeClear" );
}

void TFCMessagesHandler::RQFUNC_QueryItemInfo
(
 PACKET_FUNC_PROTOTYPE
)
{
	RQ_HEADER;
    try{
		TFCPacket sending;
		sending << (RQ_SIZE)RQ_QueryItemInfo;
		DWORD dwID;
		GET_LONG(dwID);
		Unit *lpUnit = Unit::GetByID(dwID);
		if (lpUnit)
		{
			if (lpUnit->GetType() == U_OBJECT)
			{
				sending << (char)0;
				sending << lpUnit->GetName(IntlText::GetDefaultLng());
				if(theApp.dwDisableItemInfo == 0) //ItemInfo is enabled...
				{
					_item *item;
					lpUnit->SendUnitMessage(MSG_OnGetUnitStructure,user->self,0,0,0,&item);
					sending << (short)item->appearance;
					sending << (char)item->cRadiance;
					sending << (short)item->armor.AC;
					sending << (short)item->armor.Dod;
					sending << (short)item->armor.End;
					sending << (long)(item->weapon.cDamage.GetMinBoost(user->self));
					sending << (long)(item->weapon.cDamage.GetMaxBoost(user->self));
					sending << (short)item->weapon.Att;
					sending << (short)item->weapon.Str;
					sending << (short)item->weapon.Agi;
					sending << (short)item->magic.nMinWis;
					sending << (short)item->magic.nMinInt;
					WORD plInt = user->self->GetTrueINT();
					WORD plWis = user->self->GetTrueWIS();
					sending << (short)item->tlBoosts.NbObjects();
					item->tlBoosts.ToHead();
					while (item->tlBoosts.QueryNext())
					{
						LPOBJECT_BOOST lpBoost = item->tlBoosts.Object();
						if (lpBoost->wStat > 10000 /* SkillBoostOffset */)
						{
							switch(lpBoost->wStat)
							{
							case 10001: // Stun Blow
								sending << (char)27;
								break;
							case 10002: // Powerful Blow
								sending << (char)28;
								break;
							case 10004: // First Aid
								sending << (char)29;
								break;
							case 10008: // Parry
								sending << (char)30;
								break;
							case 10009: // Meditate
								sending << (char)31;
								break;
							case 10011: // Dodge
								sending << (char)32;
								break;
							case 10012: // Attack
								sending << (char)33;
								break;
							case 10014: // Hide
								sending << (char)34;
								break;
							case 10015: // Rob
								sending << (char)35;
								break;
							case 10016: // Sneak
								sending << (char)36;
								break;
							case 10017: // Search
								sending << (char)37;
								break;
							case 10026: // Picklock
								sending << (char)38;
								break;
							case 10027: // Armor Penetration
								sending << (char)39;
								break;
							case 10028: // Peek
								sending << (char)40;
								break;
							case 10029: // Rapid Healing
								sending << (char)41;
								break;
							case 10035: // Archery
								sending << (char)42;
								break;
							case 10036: // Dual Weapons
								sending << (char)43;
								break;
							default: // Invalid or unused skill
								sending << (char)0;
							}
						}
						else
							sending << (char)lpBoost->wStat;
						if ((lpBoost->nMinWIS <= plWis) && (lpBoost->nMinINT <= plInt))
						{
							sending << (long)(lpBoost->bfBoost.GetMinBoost(user->self));
							sending << (long)(lpBoost->bfBoost.GetMaxBoost(user->self));
						}
						else
						{
							sending << (long)0;
							sending << (long)0;
						}
					}
				}
				else //Blank Window
				{
					sending << (short)0;
					sending << (char)0;
					sending << (short)0;
					sending << (short)0;
					sending << (short)0;
					sending << (long)0;
					sending << (long)0;
					sending << (short)0;
					sending << (short)0;
					sending << (short)0;
					sending << (short)0;
					sending << (short)0;
					sending << (short)0;
				}
			}
			else
			{
				sending << (char)2;
			}
		}
		else
		{
			sending << (char)1;
		}
		user->self->SendPlayerMessage(sending);
	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_QueryItemInfo" )
		delete e;		
	}
	RQ_FOOTER( "RQ_QueryItemInfo" );
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMessagesHandler::RQFUNC_SafePlug //BLBLBL new functino for antiplug
//////////////////////////////////////////////////////////////////////////////////////////
// Antiplug system allows to force the "character" to stay ingame for at least 30 seconds
// wether the character is being attacked/attacking/ during his logging off.
// the purpose is to prevent players from fleeing the combats by simply closing the application
//
// if we read 0  : means the client started the countdown
// if we read 1  : means the client stopped countdown
// 
(
 PACKET_FUNC_PROTOTYPE
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	RQ_HEADER;

	unsigned char status;
	try{
		msg->Get((char *)(&status));
		
		if (status == 0){
			user->self->boClientExitCountDown=true;

			//havoc mettre toujours à true (pour désactiver l'antiplug):
			if ( user->self->GetUnderBlock()==__SAFE_HAVEN || user->self->GetUnderBlock()==__INDOOR_SAFE_HAVEN ){
				//BLBLBL antiplug : 15 secondes d'inactivité avant de déconnecter un perso OU en zone PVP off
   	
				TFCPacket sending;
				sending << (RQ_SIZE)(RQ_SafePlug); //BLBLBL Antiplug : on informe le client
				sending << (char)1;	// 1 = C'est ok le client peut directement envoyer sa demande de fermeture
				user->self->SendPlayerMessage( sending );
					
			}
			
		}else{
			user->self->boClientExitCountDown=false;
		}

	}catch(TFCPacketException *e){
		LOG_PACKET_ERROR( "RQ_SafePlug" )
		delete e;		
	}

    RQ_FOOTER( "RQ_SafePlug" );
}
