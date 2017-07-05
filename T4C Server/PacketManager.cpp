#include "stdafx.h"
#include "TFC Server.h"
#include "CommCenter.h"
#include "PacketManager.h"
#include "TFCMessagesHandler.h"
#include "PlayerManager.h"
#include "format.h"
//#include "../T4C Monitor/T4C MonitorMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CTFCServerApp theApp;

#define MAX_PACKET_VISITORS 100
#define ACKDELAYFACTOR 1.2 //BLBLBL 07/12/2010 ajouté une variable d'ajustement des time outs réseau, valeur normale 1, connexion lente : 1.2 ou 1.5 // steph 1.2 au lieu de 1

//////////////////////////////////////////////////////////////////////////////////////////
// CommCenter performance monitoring visitor class for specific packets.
class CPacketVisitor : public CPacketMonitor{
public:
    CPacketVisitor( WORD wNewPacketID ) :
        dwSentTimes( 0 ), dwResentTimes( 0 ), wPacketID( wNewPacketID ), dwReceivedTimes( 0 ), qwTotalSize( 0 )
    {
        ++totalPacketVisitors;
        if( !CanLog() ){
            return;
        }
        
        TFormatW wFormat;
        // Creates an object for each packet type.
        unsigned short *lpFormat;
        if( wNewPacketID < 100 ){
            lpFormat = (unsigned short*)( L"%02u"); // steph lpFormat = (unsigned short*)( L"%02u"); au lieu de lpFormat = L"%02u";
        }else{
            lpFormat = (unsigned short*)( L"%u"); // steph lpFormat = (unsigned short*)( L"%u"); au lieu de lpFormat = L"%u";
        }
//        idInst = CPrfData::GetInstance()->AddInstance( PRFOBJ_PACKETS, wFormat( lpFormat, wNewPacketID ) );//BLBLBL 17/12/2010 je vire t4c monitor
    };

    ~CPacketVisitor(){};
    
    // Called each time the packet is being sent through the network
    virtual void PacketSent( void ){
        if( CanLog() ){
//            CPrfData::GetInstance()->GetCtr32( PRFPCK_SENT_PACKET_TYPE_SEC, idInst )++; //BLBLBL 17/12/2010 je vire t4c monitor
        }

        InterlockedIncrement( reinterpret_cast< long * >( &dwSentTimes ) );
    };
    // Called each time the packet is resent (ack timed out).
    virtual void PacketResent( void ){
        if( CanLog() ){
//            CPrfData::GetInstance()->GetCtr32( PRFPCK_SENT_ACK_SEC, idInst )++;//BLBLBL 17/12/2010 je vire t4c monitor
        }

        InterlockedIncrement( reinterpret_cast< long * >( &dwResentTimes ) );
    };
    // Called when the CommCenter no longer needs the packet.
    virtual void Delete( void ){
    }

    // Called each time a packet of a certain type is received by the message handler.
    void PacketReceived( void ){
        dwReceivedTimes++;
        if( CanLog() ){
//            CPrfData::GetInstance()->GetCtr32( PRFPCK_RECV_PACKET_TYPE_SEC, idInst )++;//BLBLBL 17/12/2010 je vire t4c monitor
        }
    }

    void AddPacket( DWORD dwSize ){
        qwTotalSize = qwTotalSize + dwSize;
        dwTotalPackets++;
    }

    double AvrgSize(){         
        return dwTotalPackets == 0 ? 0 : static_cast< double >( qwTotalSize / dwTotalPackets ); 
    };
    WORD   PacketID(){ return wPacketID; };
    DWORD  SentTimes(){ return dwSentTimes; };
    DWORD  ResentTimes(){ return dwResentTimes; };

    __int64 TotalSize(){ return qwTotalSize; };
    DWORD   TotalPackets(){ return dwTotalPackets; };

    DWORD   ReceivedTimes(){ return dwReceivedTimes; };

    bool CanLog(){
        return totalPacketVisitors < MAX_PACKET_VISITORS;
    }
private:
    // Perf counter instance ID.
//    CPrfData::INSTID  idInst;//BLBLBL 17/12/2010 je vire t4c monitor

    static  DWORD totalPacketVisitors;
    __int64 qwTotalSize;
    DWORD   dwTotalPackets;
    WORD    wPacketID;    
    DWORD   dwReceivedTimes;
    DWORD   dwSentTimes;
    DWORD   dwResentTimes;   
};

DWORD CPacketVisitor::totalPacketVisitors = 0;

//////////////////////////////////////////////////////////////////////////////////////////
// CommCenter Performance monitoring visitor class.
class CCommVisitor : public CCommMonitor {
    // Called each time a packet is sent through the network
    virtual void PacketSent( DWORD dwPacketSize ){
        // Update sent packet performance counters.
//        PERF_CNT( PRFNET_OUT_PACKETS_SEC )++;//BLBLBL 17/12/2010 je vire t4c monitor
//        PERF_CNT( PRFNET_OUT_BYTES_SEC   ) += dwPacketSize;//BLBLBL 17/12/2010 je vire t4c monitor
    }
    // Called each time a packet is being received.
    virtual void PacketReceived( DWORD dwPacketSize ){
        // Updates received packets performance counters.
//        PERF_CNT( PRFNET_IN_PACKETS_SEC )++;//BLBLBL 17/12/2010 je vire t4c monitor
//        PERF_CNT( PRFNET_IN_BYTES_SEC   ) += dwPacketSize;//BLBLBL 17/12/2010 je vire t4c monitor
    }
    // Called each time a packet ack was received.
    virtual void AckReceived( void ){
//        PERF_CNT( PRFNET_RECV_ACK_SEC )++;//BLBLBL 17/12/2010 je vire t4c monitor
    }
    // Called each time a packet is being resent through the resend mechanism.
    virtual void AckRetransmit( void ){
//        PERF_CNT( PRFNET_SENT_ACK_SEC )++;
    }
    // Called each time the sending packet queue changes size.
    virtual void SendQueueUpdate( DWORD dwSize, QueueAction qAction ){
//        PERF_CNT( PRFNET_SEND_PACKET_QUEUE_LEN ) = dwSize;
//        switch( qAction ){
//        case Queued:   PERF_CNT( PRFNET_SEND_QUEUED_SEC )++; break;//BLBLBL 17/12/2010 je vire t4c monitor
//        case Unqueued: PERF_CNT( PRFNET_SEND_UNQUEUED_SEC )++; break;
//        }
    }
    // Called each time the interpretation queue changes size.
    virtual void IntrQueueUpdate( DWORD dwSize, QueueAction qAction  ){
//        PERF_CNT( PRFNET_IN_PACKET_QUEUE_LEN )   = dwSize;    //BLBLBL 17/12/2010 je vire t4c monitor
//        switch( qAction ){
//        case Queued:   PERF_CNT( PRFNET_INTR_QUEUED_SEC )++; break;
//        case Unqueued: PERF_CNT( PRFNET_INTR_UNQUEUED_SEC )++; break;
//        }
    }
    // Called each time the receiving queue changes size.
    virtual void RecvQueueUpdate( DWORD dwSize, QueueAction qAction  ){
//        PERF_CNT( PRFNET_RECV_PACKET_QUEUE_LEN ) = dwSize;
//        switch( qAction ){
//        case Queued:   PERF_CNT( PRFNET_RECV_QUEUED_SEC )++; break;//BLBLBL 17/12/2010 je vire t4c monitor
//        case Unqueued: PERF_CNT( PRFNET_RECV_UNQUEUED_SEC )++; break;
//        }
    }
    // Called earch time the presend queue is updated.
    virtual void PreSendQueueUpdate( DWORD dwSize, QueueAction qAction ){
//        PERF_CNT( PRFNET_PRESEND_PACKET_QUEUE_LEN ) = dwSize;//BLBLBL 17/12/2010 je vire t4c monitor
//        switch( qAction ){
//        case Queued:   PERF_CNT( PRFNET_PRESEND_QUEUED_SEC )++; break;
//        case Unqueued: PERF_CNT( PRFNET_PRESEND_UNQUEUED_SEC )++; break;
//        }
    }

};

// File-scope objects.
namespace{
    CCommVisitor             cCommObserver;
    CPacketVisitor          *vPacketVisitor[ RQ_QUANTITY + 100 ];



	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
    const INT VISIT_SOMETHING_DIED = RQ_QUANTITY + 1;
    const INT VISIT_ATTACK         = RQ_QUANTITY + 2;
    const INT VISIT_MISS           = RQ_QUANTITY + 3;
    const INT VISIT_SKILL_USED     = RQ_QUANTITY + 4;
    const INT VISIT_ADD_OBJECT     = RQ_QUANTITY + 5;



    bool boDestroyed = false;
};

CCommCenter *CPacketManager::lpComm = NULL;

CLock destroyCommLock;

//////////////////////////////////////////////////////////////////////////////////////////
void LogPacketVisitor
//////////////////////////////////////////////////////////////////////////////////////////
//  Logs a packet visitor.
// 
(
 CPacketVisitor *lpVisitor // The packet visitor to log.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( lpVisitor != NULL ){
         DWORD  dwSentTimes   = lpVisitor->SentTimes();
         DWORD  dwResentTimes = lpVisitor->ResentTimes();
         WORD   wPacketID     = lpVisitor->PacketID();
         double dblPercent;

         if( dwSentTimes == 0 ){
            dblPercent = 0;
         }else{
            dblPercent = static_cast< double >( dwResentTimes ) * 100.0 / static_cast< double >( dwSentTimes );
         }
         
         _LOG_DEBUG
             LOG_DEBUG_LVL2,
             "RQ( %u ) sent %ux, resent %ux."
             " %2.2f%% resent packets. "
             "Avrg packet size: %ub, "
             "total of %I64ub. Packet recvd %ux.",
             wPacketID,
             dwSentTimes,
             dwResentTimes,
             dblPercent,
             static_cast< DWORD >( lpVisitor->AvrgSize() ),
             lpVisitor->TotalSize(),
             lpVisitor->ReceivedTimes()
         LOG_
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void CPacketManager::IncRecvPacketType
//////////////////////////////////////////////////////////////////////////////////////////
//  Increments the counter of received packet per type.
// 
(
 RQ_SIZE rqID // The request that was received.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CPacketVisitor *lpPacketVisitor;
    if( rqID > 10000 ){
        switch( rqID ){
        case __EVENT_SOMETHING_DIED:
            lpPacketVisitor = vPacketVisitor[ VISIT_SOMETHING_DIED ];
            break;
        case __EVENT_ATTACK:
            lpPacketVisitor = vPacketVisitor[ VISIT_ATTACK ];
            break;
        case __EVENT_MISS:
            lpPacketVisitor = vPacketVisitor[ VISIT_MISS ];
            break;
        case __EVENT_SKILL_USED:
            lpPacketVisitor = vPacketVisitor[ VISIT_SKILL_USED ];
            break;
        case 10004:
            lpPacketVisitor = vPacketVisitor[ VISIT_ADD_OBJECT ];
            break;
        default:
            lpPacketVisitor = NULL;
            break;
        };
    }else{
        lpPacketVisitor = vPacketVisitor[ rqID ];
    } 

    if( lpPacketVisitor != NULL ){
        lpPacketVisitor->PacketReceived();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void CPacketManager::PrintPacketReport( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Prints a report about packet sending in the debug log file.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // If the debug logger was specified
    if( CT4CLog::GetLog( LOG_DEBUG ) != NULL ){
        // If debug lvl3 was enabled.
        if( CT4CLog::GetLog( LOG_DEBUG )->GetLogLevels() & LOG_DEBUG_LVL1 ){            
            int i;

            for( i = 1; i != RQ_QUANTITY + 100; i++ ){
                LogPacketVisitor( vPacketVisitor[ i ] );
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void CPacketManager::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Create an instance for all possible packet visitors.
    int i;
    for( i = 0; i < RQ_QUANTITY; i++ ){        
        TRACE( "\r\nIniting packet %u.", i );
        vPacketVisitor[ i ] = new CPacketVisitor( i );
    }
    vPacketVisitor[ VISIT_SOMETHING_DIED ] = new CPacketVisitor( __EVENT_SOMETHING_DIED );
    vPacketVisitor[ VISIT_ATTACK ]         = new CPacketVisitor( __EVENT_ATTACK );
    vPacketVisitor[ VISIT_MISS ]           = new CPacketVisitor( __EVENT_MISS );
    vPacketVisitor[ VISIT_SKILL_USED ]     = new CPacketVisitor( __EVENT_SKILL_USED );
    vPacketVisitor[ VISIT_ADD_OBJECT ]     = new CPacketVisitor( 10004 );

    lpComm = new CCommCenter( &cCommObserver );
    //lpComm->SetCommMonitor(&cCommObserver);

    _LOG_DEBUG
        LOG_DEBUG_LVL4,
        "Initializing CPacketManager"
    LOG_

    char *szSendIP;
    char *szRecvIP;
    WORD wSendPort = theApp.sNetwork.wSendPort;
    WORD wRecvPort = theApp.sNetwork.wRecvPort;

    if( !theApp.sNetwork.csSendIP.IsEmpty() ){
        szSendIP = const_cast< char * >( static_cast< LPCTSTR >( theApp.sNetwork.csSendIP ) );
    }else{
        szSendIP = NULL;
    }

/*		CString txt;
		txt.Format( _T(szSendIP) );//BLBLBL vérification pour voir si c'est bien l'ip du panneau de configuration
		AfxMessageBox(txt);*/

    if( !theApp.sNetwork.csRecvIP.IsEmpty() ){
        szRecvIP = const_cast< char * >( static_cast< LPCTSTR >( theApp.sNetwork.csRecvIP ) );
    }else{
        szRecvIP = NULL;
    }

    if( !lpComm->Create( PacketInterpret, wRecvPort, wSendPort, szRecvIP, szSendIP ) ){
	    CString txt;
		txt.Format( _T("Could not initialize server's communication module") );
		AfxMessageBox(txt);
		exit( CANNOT_BIND_TO_PORT );
	}

//FIXME REMOVEME    lpComm->RegisterMSCommFunc( CPlayerManager::MSComGetUserList );
}

//////////////////////////////////////////////////////////////////////////////////////////
void CPacketManager::Destroy( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Destroys the packet manager.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock autoLock( &destroyCommLock );

    boDestroyed = true;
    delete lpComm;
    lpComm = NULL;
}


//////////////////////////////////////////////////////////////////////////////////////////
void CPacketManager::PacketInterpret
//////////////////////////////////////////////////////////////////////////////////////////
// This function does a preminilary inspection of the packet to lock global resources.
// 
(
 COMM_INTR_PROTOTYPE // The packet data information.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TFCPacket pRecv;
//	bool boWebPatchOnly = false;

    // If packet manager was shut down, return.
    if( boDestroyed ){
        return;
    }

    // Set the packet to the received buffer.
    if( !pRecv.SetBuffer( lpbBuffer, nBufferSize ) ){
        return;
    }
	/* Its no longer used. Replaced by new crypt.
    // If packet could not be decrypted (wrong checksum).
    if( !pRecv.DecryptPacket(0) ){
	    if( !pRecv.DecryptPacket(1) ){
	        TRACE( "..?" );
		    return;
		}
		boWebPatchOnly = true;
    }
	*/

    RQ_SIZE rqPacketID = 0;
    BOOL boTerminate = FALSE;


    try{
        // Fetch the packet type.
        pRecv.Get( (RQ_SIZE *)&rqPacketID );
    }catch( TFCPacketException *e ){
        TRACE( "\r\nPacket ID not found!!" );

        _LOG_DEBUG
            LOG_DEBUG_LVL1,
            "Sent undefined packet ID to client."
        LOG_
        
        delete e;
        boTerminate = TRUE;
    }

    if( boTerminate ){
        return;
    }

/*	if (rqPacketID != 10) { 
	    _LOG_DEBUG   //BLBLBL 13/12/2010
            LOG_CRIT_ERRORS,
            "Received a network pak number %u",rqPacketID
        LOG_
	}*/

/*	if (boWebPatchOnly) {
		switch ( rqPacketID ) {
		case RQ_QueryNameExistence:
		case RQ_RegisterAccount:
		case RQ_GetTime:
		case RQ_QueryServerVersion:
		case RQ_QueryPatchServerInfo:
		case RQ_MessageOfDay:
	    case RQ_AuthenticateServerVersion:
			break;
		default:
			return;
		}
	}*/

    TRACE( "\r\nReceiving RQ=%u.", rqPacketID );

    // Determines which packets need which resources.
    switch( rqPacketID ){

		 /*{
			// Fetch player resource.
			Players *lpPlayer;

			// Fetch player resource corresponding to the packet's address
			lpPlayer = CPlayerManager::GetPlayerResource( sockAddr );

			// If a player resource could be fetched
			if( lpPlayer != NULL ){
				lpPlayer->ResetIdle();
				CPlayerManager::FreePlayerResource( lpPlayer );
			}
			
		}*/
	case RQ_MoveNorth:
    case RQ_MoveNorthEast:
    case RQ_MoveEast:
    case RQ_MoveSouthEast:
    case RQ_MoveSouth:
    case RQ_MoveSouthWest:
    case RQ_MoveWest:
    case RQ_MoveNorthWest:
    case RQ_GetPlayerPos:
   case RQ_Ack:
    case RQ_GetObject:
    case RQ_DepositObject:
    case RQ_PutPlayerInGame:
    case RQ_DeletePlayer:
    case RQ_SendPeriphericObjects:
    case RQ_GodCreateObject:
    case RQ_ViewBackpack:
    case RQ_ViewEquiped:
    case RQ_ExitGame:
    case RQ_EquipObject:
    case RQ_UnequipObject:
    case RQ_UseObject:
    case RQ_Attack:
    case RQ_CreatePlayer:
    case RQ_GetPersonnalPClist:
    case RQ_IndirectTalk:
    case RQ_Shout:
    case RQ_Page:
    case RQ_DirectedTalk:
    case RQ_Reroll:
    case RQ_CastSpell:
    case RQ_HPchanged:
    case RQ_BroadcastTextChange:
    case RQ_GetUnitName:
    case RQ_BreakConversation:
    case RQ_LevelUp:
    case RQ_ReturnToMenu:
    case RQ_GetSkillList:
    case RQ_SendTrainSkillList:
    case RQ_SendBuyItemList:
    case RQ_UseSkill:
    case RQ_GetStatus:
    case RQ_XPchanged:
    case RQ_FromPreInGameToInGame:
    //case RQ_YouDied:
    case RQ_EnterChatterChannel:
    case RQ_SendChatterMessage:
    case RQ_GetChatterUserList:
    case RQ_GetOnlinePlayerList:
    case RQ_GetSkillStatPoints:
    case RQ_GoldChange:
    case RQ_ViewGroundItemIndentContent:
    case RQ_SendTeachSkillList:
    case RQ_SendSellItemList:
    case RQ_TeleportPlayer:
    case RQ_SendStatTrain:
    case RQ_QueryItemName:
    case RQ_GetNearItems:
    case RQ_PlayerFastMode:
    case RQ_SendSpellList:
    case RQ_ServerMessage:
	case RQ_InfoMessage:
    case RQ_SpellEffect:
    case RQ_ManaChanged:
    case RQ_PuppetInformation:
    case RQ_QueryUnitExistence:
    case RQ_UseItemByAppearance:
    case RQ_RemoveFromChatterChannel:
    case RQ_GetChatterChannelList:
    case RQ_ToggleChatterListening:
    case RQ_JunkItems:
    case RQ_GroupInvite:
    case RQ_GroupJoin:
    case RQ_GroupLeave:
    case RQ_GroupKick:
    case RQ_GroupToggleAutoSplit:
    case RQ_TogglePage:
    case RQ_Rob:
    case RQ_AuthenticateServerVersion:
	case RQ_ChestAddItemFromBackpack:
	case RQ_ChestRemoveItemToBackpack:
	case RQ_TradeInvite:
	case RQ_TradeCancel:
	case RQ_TradeSetStatus:
	case RQ_TradeAddItemFromBackpack:
	case RQ_TradeRemoveItemToBackpack:
	case RQ_TradeClear:
	case RQ_TradeStarted:
	case RQ_QueryItemInfo:
	case RQ_SafePlug ://BLBLBL new pak for antiplug system

        // Fetch player resource.
        Players *lpPlayer;

        // Fetch player resource corresponding to the packet's address
        lpPlayer = CPlayerManager::GetPlayerResource( sockAddr );

        // If a player resource could be fetched
        if( lpPlayer != NULL ){
            TRACE( "\r\nFetched player resource." );
            // Reset Idle time on player.
            lpPlayer->ResetIdle();//BLBL Chaque pak recu, on reset l'idle time du joueur

            // Send packet for interpretation
            TFCMessagesHandler::DispatchPacket( &pRecv, lpPlayer, rqPacketID, sockAddr );

            TRACE( "\r\nFreeing player resource" );
            // Frees the player resource after it has been analyzed.
            CPlayerManager::FreePlayerResource( lpPlayer );
        }        
        break;
    case RQ_QueryNameExistence:
    case RQ_RegisterAccount:
    case RQ_GetTime:
    case RQ_QueryServerVersion:
    case RQ_QueryPatchServerInfo:
    case RQ_MessageOfDay:
		TFCMessagesHandler::DispatchPacket( &pRecv, NULL, rqPacketID, sockAddr );
		   break;
    }   
}

#define SETACK( __ackdelay, __maxack ) dwAckDelay = __ackdelay * ACKDELAYFACTOR ; dwMaxAck = __maxack; break;//BLBLBL 07/12/2010 ajouté une variable d'ajustement global des délais de time out

//////////////////////////////////////////////////////////////////////////////////////////
void CPacketManager::SendPacket
//////////////////////////////////////////////////////////////////////////////////////////
// Sends a packet to the remote client.
// 
(
 TFCPacket     &pPacket,              // The packet.
 sockaddr_in    sockAddr,             // Adress of target client.
 int            nBroadcastRange,      // Range to broadcast message.
 WorldPos       wlCenter,             // Center from which to broadcast.
 BOOL           boBroadcast,          // TRUE if packet should be broadcast.
 SendPacketVisitor *sendPacketVisitor,// An object to visitor before sending
                                      // the packet to a player.
 bool           inGame                // Send only to ingame units.
 
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // If packet manager was shut down, return.
    if( boDestroyed ){
        return;
    }
    
    static DWORD dwLastReportTime = 0;
    const  INT ReportTime = 300000;// Five minutes per report. // steph ajout de INT
    
    RQ_SIZE rqPacketID = pPacket.GetPacketID();
	
	//BLBLBL si le packet est invalide on envoie rien : 02/12/2010
	if (rqPacketID == 0) {	
		_LOG_DEBUG
                    LOG_MISC_1,
                    "Sent pak with ID 0"
		LOG_
		return;
	}

	/*if (rqPacketID != 10 && rqPacketID != 1) {		
	_LOG_DEBUG
                    LOG_MISC_1,
                    "Sent pak with ID %u", rqPacketID
			LOG_
	}*/

    BOOL  boSend = TRUE;

    // Unsafe packet by default. //BLBL ? in commCenter.cpp line 555 it says, if dwMaxAck != 0 it's a safe packet..
    DWORD dwAckDelay = 1000;
    DWORD dwMaxAck   = 5;
  
/* BL : For reference, the numbered values of pack types :
#define	RQ_MoveNorth					1 
#define	RQ_MoveNorthEast				2 
#define	RQ_MoveEast						3 
#define	RQ_MoveSouthEast				4 
#define	RQ_MoveSouth					5 
#define	RQ_MoveSouthWest				6 
#define	RQ_MoveWest						7 
#define RQ_MoveNorthWest				8 
#define RQ_GetPlayerPos					9 
#define RQ_Ack							10 
#define RQ_GetObject					11 
#define RQ_DepositObject				12 
#define RQ_PutPlayerInGame				13 
#define RQ_RegisterAccount				14 
#define RQ_DeletePlayer					15 
#define RQ_SendPeriphericObjects		16 
#define RQ_GodCreateObject				17 
#define RQ_ViewBackpack					18
#define RQ_ViewEquiped					19 
#define RQ_ExitGame						20 
#define RQ_EquipObject					21 
#define RQ_UnequipObject				22 
#define RQ_UseObject					23 
#define RQ_Attack						24 
#define RQ_CreatePlayer					25 
#define RQ_GetPersonnalPClist			26 		
#define RQ_IndirectTalk					27 
#define RQ_Shout						28 
#define RQ_Page							29 
#define RQ_DirectedTalk					30 
#define RQ_Reroll						31
#define RQ_CastSpell					32 
#define RQ_HPchanged					33
#define RQ_BroadcastTextChange			34
#define RQ_GetUnitName					35
#define RQ_BreakConversation			36
#define RQ_LevelUp						37
#define RQ_ReturnToMenu					38
#define RQ_GetSkillList					39
#define RQ_SendTrainSkillList			40
#define RQ_SendBuyItemList				41
#define RQ_UseSkill						42
#define RQ_GetStatus					43
#define RQ_XPchanged					44
#define RQ_GetTime						45
#define RQ_FromPreInGameToInGame		46
#define RQ_YouDied						47
#define RQ_AddRemoveChatterChannel		48
#define RQ_SendChatterChannelMessage	49
#define RQ_GetChatterUserList		    50
#define RQ_GetOnlinePlayerList			51
#define RQ_GetSkillStatPoints			52
#define RQ_GoldChange					53
#define RQ_ViewGroundItemIndentContent	54
#define RQ_SendTeachSkillList			55
#define RQ_SendSellItemList				56
#define RQ_TeleportPlayer				57
#define RQ_SendStatTrain				58
#define RQ_QueryItemName				59
#define RQ_GetNearItems					60
#define RQ_PlayerFastMode				61
#define RQ_SendSpellList				62
#define RQ_ServerMessage				63
#define RQ_SpellEffect                  64
#define RQ_ManaChanged                  67
#define RQ_GetChatterChannelList        75
#define RQ_CreateEffectStatus           83
#define RQ_DispellEffectStatus          84
#define RQ_UpdateGroupMemberHp          87
#define RQ_UpdateWeight                 92
#define RQ_Rob                          93
#define RQ_DispellRob                   94
#define RQ_ArrowMiss                    95
#define RQ_ArrowHit                     96
#define RQ_GodFlagUpdate                97
#define RQ_SeraphArrival                98
#define RQ_AuthenticateServerVersion    99
#define RQ_Seraph                       100
#define RQ_InfoMessage                  102
#define RQ_MaxCharactersPerAccountInfo  103
#define RQ_WeatherMsg					104
#define RQ_OpenURL						105
// Chest Packets
#define RQ_ChestContents				106
#define RQ_ChestAddItemFromBackpack		107
#define RQ_ChestRemoveItemToBackpack	108
#define RQ_ShowChest					109
#define RQ_HideChest					110
// Trade Packets
#define RQ_TradeContents				111
#define RQ_TradeAddItemFromBackpack		112
#define RQ_TradeRemoveItemToBackpack	113
#define RQ_TradeInvite					116
#define RQ_TradeSetStatus				117
#define	RQ_TradeCancel					118
#define RQ_TradeClear					119
#define RQ_TradeStarted					120
#define RQ_TradeFinish					121
#define RQ_QueryItemInfo   			122
// Guilds
#define RQ_SafePlug					123
#define RQ_GuildGetMembers				124//usused for now.
#define RQ_GuildInvite					125
#define RQ_GuildKick					126
#define RQ_GuildLeave					127
#define RQ_GuildAlterRights				128
#define RQ_GuildRename					129
#define RQ_GuildInviteAnswer			130
#define RQ_GetPvpRanking				131	// asteryth pvp ranking
	*/	
    // Determine the packet's security level.
    switch( rqPacketID ){

	//BLBLBL Modification de tous les timings, vu avec Chaotik, on teste :)
    /*case RQ_MoveNorth:              SETACK( 250, 1 );
    case RQ_MoveNorthEast:          SETACK( 250, 1 );
    case RQ_MoveEast:               SETACK( 250, 1 );
    case RQ_MoveSouthEast:          SETACK( 250, 1 );
    case RQ_MoveSouth:              SETACK( 250, 1 );
    case RQ_MoveSouthWest:          SETACK( 250, 1 );
    case RQ_MoveWest:               SETACK( 250, 1 );
    case RQ_MoveNorthWest:          SETACK( 250, 1 );
    case RQ_GetPlayerPos:           SETACK( 250, 1 );
    case RQ_Ack:                    SETACK( 0, 0 );
	case RQ_SafePlug:				SETACK(500,3);

    case RQ_GetObject:              SETACK( 250, 3 );
    case RQ_DepositObject:          SETACK( 250, 3 );
    case RQ_PutPlayerInGame:        SETACK( 3000,  5 );

    case RQ_RegisterAccount:        SETACK( 250, 3 );
    case RQ_DeletePlayer:           SETACK( 250, 3 );
    case RQ_SendPeriphericObjects:  SETACK( 250, 3 );
    case RQ_GodCreateObject:        SETACK( 250, 3 );
    case RQ_ViewBackpack:           SETACK(  500, 3 );
    case RQ_ViewEquiped:            SETACK(  500, 3 );
    case RQ_ExitGame:               SETACK( 1000, 5 );
    case RQ_EquipObject:            SETACK( 250, 3 );
    case RQ_UnequipObject:          SETACK( 250, 3 );
    case RQ_UseObject:              SETACK( 250, 3 );
    case RQ_Attack:                 SETACK(  500, 3 );
    case RQ_CreatePlayer:           SETACK( 1000, 5 );
    case RQ_GetPersonnalPClist:     SETACK( 250, 5 );
    case RQ_IndirectTalk:           SETACK( 250, 3 );
    case RQ_Page:                   SETACK( 250, 3 );
    case RQ_DirectedTalk:           SETACK( 250, 2 );
    case RQ_Reroll:                 SETACK( 1000, 2 );
    case RQ_CastSpell:              SETACK( 250, 3 );
    case RQ_HPchanged:              SETACK( 0, 0 );
    case RQ_BroadcastTextChange:    SETACK( 250, 3 );
    case RQ_GetUnitName:            SETACK( 250, 3 );
    case RQ_BreakConversation:      SETACK( 250, 3 );
    case RQ_LevelUp:                SETACK( 250, 5 );
    case RQ_ReturnToMenu:           SETACK( 0, 0 );
    case RQ_GetSkillList:           SETACK( 250, 5 );
    case RQ_SendTrainSkillList:     SETACK( 500, 3 );
    case RQ_SendBuyItemList:        SETACK( 500, 3 );
    case RQ_UseSkill:               SETACK( 250, 3 );
    case RQ_GetStatus:              SETACK( 500, 3 );
    case RQ_XPchanged:              SETACK( 0, 0 );
    case RQ_FromPreInGameToInGame:  SETACK( 500, 5 );
    case RQ_YouDied:                SETACK( 500, 5 );
    case RQ_EnterChatterChannel:    SETACK( 500, 3 );
    case RQ_SendChatterMessage:     SETACK( 250, 3 );
    case RQ_GetChatterUserList:     SETACK( 250, 3 );
    case RQ_GetOnlinePlayerList:    SETACK( 250, 2 );
    case RQ_GetSkillStatPoints:     SETACK( 500, 3 );
    case RQ_GoldChange:             SETACK( 0, 0 );
    case RQ_ViewGroundItemIndentContent:    SETACK( 0, 0 );
    case RQ_SendTeachSkillList:     SETACK( 500, 3 );
    case RQ_SendSellItemList:       SETACK( 500, 3 );
    case RQ_TeleportPlayer:         SETACK( 250, 4 );
    case RQ_SendStatTrain:          SETACK( 1000, 3 );
    case RQ_QueryItemName:          SETACK( 750, 3 );
    case RQ_GetNearItems:           SETACK( 250, 5 );
    case RQ_PlayerFastMode:         SETACK( 1000, 2 );
    case RQ_SendSpellList:          SETACK( 250, 4 );
    case RQ_ServerMessage:          SETACK( 500, 3 );
	case RQ_InfoMessage:            SETACK( 500, 3 );
    case RQ_SpellEffect:            SETACK( 250, 3 );
    case RQ_ManaChanged:            SETACK( 0, 0 );
    case RQ_GetTime:                SETACK( 0, 0 );
    case RQ_PuppetInformation:      SETACK( 750, 3 );
    case RQ_QueryServerVersion:     SETACK( 1000, 3 );
    case RQ_MessageOfDay:           SETACK( 1000, 3 );
    case RQ_UnitUpdate:             SETACK( 500, 2 );//BLBLBL Remis à 2, car apparement 3 change rien.
    case RQ_MissingUnit:            SETACK( 250, 5 ); //NMNMNM
    case RQ_QueryUnitExistence:     SETACK( 250, 3 );
    case RQ_UseItemByAppearance:    SETACK( 250, 4 );
    case RQ_CannotFindItemByAppearance: SETACK( 250, 3 );
    case RQ_RemoveFromChatterChannel:   SETACK( 500, 3 );
    case RQ_GetChatterChannelList:      SETACK( 500, 3 );
    case RQ_CreateEffectStatus:         SETACK( 500, 3 );
    case RQ_DispellEffectStatus:        SETACK( 500, 3 );
    case RQ_UpdateGroupMembers:         SETACK( 500, 3 );
    case RQ_UpdateGroupInviteList:      SETACK( 500, 3 );
    case RQ_GroupInvite:                SETACK( 500, 3 );
    case RQ_GroupJoin:                  SETACK( 500, 3 );
    case RQ_GroupLeave:                 SETACK( 500, 3 );
    case RQ_GroupKick:                  SETACK( 500, 3 );
    case RQ_NotifyGroupDisband:         SETACK( 500, 3 );
    case RQ_ToggleChatterListening:     SETACK( 500, 3 );    
    case RQ_UpdateGroupMemberHp:        SETACK( 500, 3 );
    case RQ_GroupToggleAutoSplit:       SETACK( 500, 3 );
    case RQ_QueryNameExistence:         SETACK( 500, 3 );
    case RQ_QueryPatchServerInfo:       SETACK( 500, 3 );
    case RQ_UpdateWeight:               SETACK( 500, 3 );
    case RQ_Rob:                        SETACK( 500, 3 );
    case RQ_DispellRob:                 SETACK( 500, 3 );
    case RQ_ArrowMiss:                  SETACK( 250, 3 );
    case RQ_ArrowHit:                   SETACK( 250, 3 );
    case RQ_GodFlagUpdate:               SETACK( 1000, 3 );
    case RQ_SeraphArrival:          SETACK( 1000, 3 );
    case RQ_AuthenticateServerVersion: SETACK( 1000, 5 );
    case RQ_Remort: SETACK( 1000, 8 );
    case __EVENT_SOMETHING_DIED:    SETACK( 250, 4 );
    case __EVENT_ATTACK:            SETACK( 500, 3 );
    case __EVENT_MISS:              SETACK( 0, 0 );
    case __EVENT_SKILL_USED:        SETACK( 250, 3 );
    case 10004:                     SETACK( 250, 4 );//BLBLBL : POP UP item on floor ? tentative de passer de 1000,3 à 1000,7 comme getNearItems.
	case RQ_MaxCharactersPerAccountInfo: SETACK( 1000, 3 );
	case RQ_WeatherMsg:					 SETACK( 1000, 3 );
	case RQ_OpenURL:					SETACK( 1000, 3 );
	case RQ_ChestContents:				SETACK( 500, 5 );
	case RQ_ChestAddItemFromBackpack:	SETACK( 500, 5 );
	case RQ_ChestRemoveItemToBackpack:	SETACK( 500, 5 );
	case RQ_ShowChest:					SETACK( 500, 5 );
	case RQ_HideChest:					SETACK( 500, 5 );

	case RQ_TradeInvite: case RQ_TradeCancel: case RQ_TradeSetStatus: 
	case RQ_TradeAddItemFromBackpack:	case RQ_TradeRemoveItemToBackpack:
	case RQ_TradeClear: case RQ_TradeStarted: case RQ_TradeContents: 
	case RQ_TradeFinish: SETACK( 500, 5 );
	
	case RQ_QueryItemInfo: SETACK(1000,3);*/

	/*case RQ_MoveNorth:              SETACK( 0, 0 );
    case RQ_MoveNorthEast:          SETACK( 0, 0 );
    case RQ_MoveEast:               SETACK( 0, 0 );
    case RQ_MoveSouthEast:          SETACK( 0, 0 );
    case RQ_MoveSouth:              SETACK( 0, 0 );
    case RQ_MoveSouthWest:          SETACK( 0, 0 );
    case RQ_MoveWest:               SETACK( 0, 0 );
    case RQ_MoveNorthWest:          SETACK( 0, 0 );
    case RQ_GetPlayerPos:           SETACK( 0, 0 );
    case RQ_Ack:                    SETACK( 0, 0 );
	case RQ_SafePlug:				SETACK(500,3);//BLBLBL : new pak for antiplug system. 5=>3

    case RQ_GetObject:              SETACK( 500, 14 );//BLBLBL alignement avec les valeurs coté client 1000,5 => 14,500
    case RQ_DepositObject:          SETACK( 500, 14 );
    case RQ_PutPlayerInGame:        SETACK( 1000,  7 );//BLBLBL alignement avec les valeur client 5=>7

    case RQ_RegisterAccount:        SETACK( 500, 10 );//BLBLBL alignement avec les valeur client
    case RQ_DeletePlayer:           SETACK( 1000, 5 );
    case RQ_SendPeriphericObjects:  SETACK( 500, 14 );//BLBLBL ^^
    case RQ_GodCreateObject:        SETACK( 500, 14 );
    case RQ_ViewBackpack:           SETACK(  500, 5 );
    case RQ_ViewEquiped:            SETACK(  500, 5 );
    case RQ_ExitGame:               SETACK( 1000, 5 );
    case RQ_EquipObject:            SETACK( 1000, 5 );
    case RQ_UnequipObject:          SETACK( 1000, 5 );
    case RQ_UseObject:              SETACK( 1000, 5 );
    case RQ_Attack:                 SETACK(  500, 3 );
    case RQ_CreatePlayer:           SETACK( 1000, 5 );
    case RQ_GetPersonnalPClist:     SETACK( 1000, 5 );
    case RQ_IndirectTalk:           SETACK( 1500, 3 );
    case RQ_Page:                   SETACK( 1500, 3 );
    case RQ_DirectedTalk:           SETACK( 1500, 2 );
    case RQ_Reroll:                 SETACK( 1000, 2 );
    case RQ_CastSpell:              SETACK( 1000, 5 );
    case RQ_HPchanged:              SETACK( 500, 5 );//BLBLBL alignement au client 0,0=>500,5
    case RQ_BroadcastTextChange:    SETACK( 1000, 3 );
    case RQ_GetUnitName:            SETACK( 1000, 3 );
    case RQ_BreakConversation:      SETACK( 1000, 5 );
    case RQ_LevelUp:                SETACK( 2000, 5 );
    case RQ_ReturnToMenu:           SETACK( 0, 0 );
    case RQ_GetSkillList:           SETACK( 1000, 3 );
    case RQ_SendTrainSkillList:     SETACK( 1500, 3 );
    case RQ_SendBuyItemList:        SETACK( 1500, 3 );
    case RQ_UseSkill:               SETACK( 1000, 3 );
    case RQ_GetStatus:              SETACK( 1500, 3 );
    case RQ_XPchanged:              SETACK( 0, 0 );
    case RQ_FromPreInGameToInGame:  SETACK( 1500, 5 );
    case RQ_YouDied:                SETACK( 1000, 5 );
    case RQ_EnterChatterChannel:    SETACK( 1000, 5 );
    case RQ_SendChatterMessage:     SETACK( 1000, 5 );
    case RQ_GetChatterUserList:     SETACK( 1000, 5 );
    case RQ_GetOnlinePlayerList:    SETACK( 1500, 2 );
    case RQ_GetSkillStatPoints:     SETACK( 1000, 3 );
    case RQ_GoldChange:             SETACK( 0, 0 );
    case RQ_ViewGroundItemIndentContent:    SETACK( 0, 0 );
    case RQ_SendTeachSkillList:     SETACK( 1000, 3 );
    case RQ_SendSellItemList:       SETACK( 1000, 3 );
    case RQ_TeleportPlayer:         SETACK( 750,  5 );
    case RQ_SendStatTrain:          SETACK( 1000, 3 );
    case RQ_QueryItemName:          SETACK( 750, 3 );
    case RQ_GetNearItems:           SETACK( 1000, 7 );
    case RQ_PlayerFastMode:         SETACK( 1000, 2 );
    case RQ_SendSpellList:          SETACK( 1250, 3 ); 
    case RQ_ServerMessage:          SETACK( 1500, 5 );
	case RQ_InfoMessage:            SETACK( 1500, 5 );
    case RQ_SpellEffect:            SETACK( 500, 5 );
    case RQ_ManaChanged:            SETACK( 500, 5 );//BLBLBL alignement au client 0,0=>500,5
    case RQ_GetTime:                SETACK( 0, 0 );
    case RQ_PuppetInformation:      SETACK( 750, 3 );
    case RQ_QueryServerVersion:     SETACK( 1000, 3 );
    case RQ_MessageOfDay:           SETACK( 1000, 3 );
    case RQ_UnitUpdate:             SETACK( 500, 2 );
    case RQ_MissingUnit:            SETACK( 1000, 5 );
    case RQ_QueryUnitExistence:     SETACK( 1000, 3 );
    case RQ_UseItemByAppearance:    SETACK( 1000, 3 );
    case RQ_CannotFindItemByAppearance: SETACK( 1000, 3 );
    case RQ_RemoveFromChatterChannel:   SETACK( 1000, 3 );
    case RQ_GetChatterChannelList:      SETACK( 1000, 3 );
    case RQ_CreateEffectStatus:         SETACK( 1000, 3 );
    case RQ_DispellEffectStatus:        SETACK( 1000, 3 );
    case RQ_UpdateGroupMembers:         SETACK( 1000, 3 );
    case RQ_UpdateGroupInviteList:      SETACK( 1000, 3 );
    case RQ_GroupInvite:                SETACK( 1000, 3 );
    case RQ_GroupJoin:                  SETACK( 1000, 3 );
    case RQ_GroupLeave:                 SETACK( 1000, 3 );
    case RQ_GroupKick:                  SETACK( 1000, 3 );
    case RQ_NotifyGroupDisband:         SETACK( 1000, 3 );*/
    
	case RQ_MoveNorth:              		SETACK( 0, 0 );//BLBLBL 07/12/2010 en provenance des sources 1.25
    case RQ_MoveNorthEast:          		SETACK( 0, 0 );
    case RQ_MoveEast:               		SETACK( 0, 0 );
    case RQ_MoveSouthEast:          		SETACK( 0, 0 );
    case RQ_MoveSouth:              		SETACK( 0, 0 );
    case RQ_MoveSouthWest:          		SETACK( 0, 0 );
    case RQ_MoveWest:               		SETACK( 0, 0 );
    case RQ_MoveNorthWest:          		SETACK( 0, 0 );
    case RQ_GetPlayerPos:           		SETACK( 0, 0 );
    case RQ_Ack:                    		SETACK( 0, 0 );
    case RQ_GetObject:              		SETACK( 1000, 5 );
    case RQ_DepositObject:          		SETACK( 1000, 5 );
    case RQ_PutPlayerInGame:        		SETACK( 1000, 5 );
    case RQ_RegisterAccount:        		SETACK( 1000, 5 );
    case RQ_DeletePlayer:           		SETACK( 1000, 5 );
    case RQ_SendPeriphericObjects:  		SETACK( 1000, 5 );
    case RQ_GodCreateObject:        		SETACK( 1000, 5 );
    case RQ_ViewBackpack:           		SETACK(  500, 5 );
    case RQ_ViewEquiped:            		SETACK(  500, 5 );
    case RQ_ExitGame:               		SETACK( 1000, 5 );
    case RQ_EquipObject:            		SETACK( 1000, 5 );
    case RQ_UnequipObject:          		SETACK( 1000, 5 );
    case RQ_UseObject:              		SETACK( 1000, 5 );
    case RQ_Attack:                 		SETACK(  500, 3 );
    case RQ_CreatePlayer:           		SETACK( 1000, 5 );
    case RQ_GetPersonnalPClist:     		SETACK( 1000, 5 );
    case RQ_IndirectTalk:           		SETACK( 1500, 3 );
	case RQ_Shout:           				SETACK( 1500, 3 );
    case RQ_Page:                   		SETACK( 1500, 3 );
    case RQ_DirectedTalk:           		SETACK( 1500, 2 );
    case RQ_Reroll:                 		SETACK( 1000, 2 );
    case RQ_CastSpell:              		SETACK( 1000, 5 );
    case RQ_HPchanged:              		SETACK( 0, 0 );
    case RQ_BroadcastTextChange:    		SETACK( 1000, 3 );
    case RQ_GetUnitName:            		SETACK( 1000, 3 );
    case RQ_BreakConversation:      		SETACK( 1000, 5 );
    case RQ_LevelUp:                		SETACK( 2000, 5 );
    case RQ_ReturnToMenu:           		SETACK( 0, 0 );
    case RQ_GetSkillList:           		SETACK( 1000, 3 );
    case RQ_SendTrainSkillList:     		SETACK( 1500, 3 );
    case RQ_SendBuyItemList:        		SETACK( 1500, 3 );
    case RQ_UseSkill:               		SETACK( 1000, 3 );
    case RQ_GetStatus:              		SETACK( 1500, 3 );
    case RQ_XPchanged:              		SETACK( 0, 0 );
    case RQ_FromPreInGameToInGame:  		SETACK( 1000, 5 );
    case RQ_YouDied:                		SETACK( 1000, 5 );
    case RQ_EnterChatterChannel:    		SETACK( 1000, 5 );
    case RQ_SendChatterMessage:     		SETACK( 1000, 5 );
    case RQ_GetChatterUserList:     		SETACK( 1000, 5 );
    case RQ_GetOnlinePlayerList:    		SETACK( 1500, 2 );
    case RQ_GetSkillStatPoints:     		SETACK( 1000, 3 );
    case RQ_GoldChange:             		SETACK( 0, 0 );
    case RQ_ViewGroundItemIndentContent:    SETACK( 0, 0 );
    case RQ_SendTeachSkillList:     		SETACK( 1000, 3 );
    case RQ_SendSellItemList:       		SETACK( 1000, 3 );
    case RQ_TeleportPlayer:         		SETACK( 750,  5 );
    case RQ_SendStatTrain:          		SETACK( 1000, 3 );
    case RQ_QueryItemName:          		SETACK( 750, 3 );
    case RQ_GetNearItems:           		SETACK( 1000, 1 );
    case RQ_PlayerFastMode:         		SETACK( 1000, 2 );
    case RQ_SendSpellList:          		SETACK( 1250, 3 );
    case RQ_ServerMessage:          		SETACK( 1500, 5 );
	case RQ_InfoMessage:					SETACK( 1500, 5 );
    case RQ_SpellEffect:            		SETACK( 500, 5 );
    case RQ_ManaChanged:            		SETACK( 0, 0 );
    case RQ_GetTime:                		SETACK( 0, 0 );
    case RQ_PuppetInformation:      		SETACK( 750, 3 );
    case RQ_QueryServerVersion:     		SETACK( 1000, 3 );
    case RQ_MessageOfDay:           		SETACK( 1000, 3 );
    case RQ_UnitUpdate:             		SETACK( 500, 2 );
    case RQ_MissingUnit:            		SETACK( 1000, 2 );
    case RQ_QueryUnitExistence:     		SETACK( 1000, 3 );
    case RQ_UseItemByAppearance:    		SETACK( 1000, 3 );
    case RQ_CannotFindItemByAppearance: 	SETACK( 1000, 3 );
    case RQ_RemoveFromChatterChannel:   	SETACK( 1000, 3 );
    case RQ_GetChatterChannelList:      	SETACK( 1000, 3 );
    case RQ_CreateEffectStatus:         	SETACK( 500, 3 );//10/12/2010 BLBLBL je diminue un poil
    case RQ_DispellEffectStatus:        	SETACK( 500, 3 );//10/12/2010 BLBLBL je diminue un poil
    case RQ_UpdateGroupMembers:         	SETACK( 1000, 3 );
    case RQ_UpdateGroupInviteList:      	SETACK( 1000, 3 );
    case RQ_GroupInvite:                	SETACK( 1000, 3 );
    case RQ_GroupJoin:                  	SETACK( 1000, 3 );
    case RQ_GroupLeave:                 	SETACK( 1000, 3 );
    case RQ_GroupKick:                  	SETACK( 1000, 3 );
    case RQ_NotifyGroupDisband:         	SETACK( 1000, 3 );

    case RQ_ToggleChatterListening:     SETACK( 1000, 3 );    
    case RQ_UpdateGroupMemberHp:        SETACK( 1000, 3 );
    case RQ_GroupToggleAutoSplit:       SETACK( 1000, 3 );
    case RQ_QueryNameExistence:         SETACK( 1000, 3 );
    case RQ_QueryPatchServerInfo:       SETACK( 1000, 8 );
    case RQ_UpdateWeight:               SETACK( 1000, 3 );
    case RQ_Rob:                        SETACK( 1000, 3 );
    case RQ_DispellRob:                 SETACK( 1000, 3 );
    case RQ_ArrowMiss:                  SETACK( 500, 3 );
    case RQ_ArrowHit:                   SETACK( 500, 3 );
    case RQ_GodFlagUpdate:               SETACK( 1000, 3 );
    case RQ_SeraphArrival:          SETACK( 1000, 3 );
    case RQ_AuthenticateServerVersion: SETACK( 1000, 5 );
    case RQ_Remort: SETACK( 1000, 8 );
    case __EVENT_SOMETHING_DIED:    SETACK( 750, 5 );
    case __EVENT_ATTACK:            SETACK( 500, 3 );
    case __EVENT_MISS:              SETACK( 0, 0 );
    case __EVENT_SKILL_USED:        SETACK( 1000, 3 );
    case 10004:                     SETACK( 1000, 3 );
	case RQ_MaxCharactersPerAccountInfo: SETACK( 1000, 3 );
	case RQ_WeatherMsg:					 SETACK( 1000, 3 );
	case RQ_OpenURL:					SETACK( 1000, 3 );
	case RQ_ChestContents:				SETACK( 500, 5 );
	case RQ_ChestAddItemFromBackpack:	SETACK( 500, 5 );
	case RQ_ChestRemoveItemToBackpack:	SETACK( 500, 5 );
	case RQ_ShowChest:					SETACK( 500, 5 );
	case RQ_HideChest:					SETACK( 500, 5 );

	case RQ_TradeInvite: case RQ_TradeCancel: case RQ_TradeSetStatus: 
	case RQ_TradeAddItemFromBackpack:	case RQ_TradeRemoveItemToBackpack:
	case RQ_TradeClear: case RQ_TradeStarted: case RQ_TradeContents: 
	case RQ_TradeFinish: SETACK( 500, 5 );
	// asteryth pvp ranking
	case RQ_GetPvpRanking:                SETACK( 500, 3 );
	
	case RQ_QueryItemInfo: SETACK(1000,3);

	case RQ_SafePlug:				SETACK(1000,3); //BLBLBL: new pak for antiplug system. 5=>3

    break;
        // If packet isn't a valid request
    default:
        boSend = FALSE;
		_LOG_DEBUG
                    LOG_MISC_1,
                    "Could not send packet %u invalid request ! PacketManager.cpp line 838", rqPacketID
        LOG_
        break;
    }

    if( boSend ){        
        // Retreive the packet buffer.
        LPBYTE lpbBuffer = NULL;
        int    nBufferSize = 0;

        //pPacket.EncryptPacket(); Its no longer used. Replaced by new crypt.
        pPacket.GetBuffer( lpbBuffer, nBufferSize );


        // If packet should be broadcasted.
        if( boBroadcast ){
            vector < sockaddr_in > vAddress;

            // If center or range isn't valid, packet is globally broadcasted.
            if( wlCenter.X == -1 || wlCenter.Y == -1 || wlCenter.world == -1 || nBroadcastRange == -1 ){
                CPlayerManager::GetGlobalBroadcastAddress( vAddress, sendPacketVisitor, inGame );
            }else{
                // Otherwise packet is only broadcasted locally            
                CPlayerManager::GetLocalBroadcastAddress ( vAddress, wlCenter, nBroadcastRange, sendPacketVisitor );
            }

            // Send message to all recipients.
            vector< sockaddr_in >::iterator i;

            for( i = vAddress.begin(); i != vAddress.end(); i++ ){
                                
                TRACE( "\r\nBSending %u.", rqPacketID );                               

                CPacketVisitor *lpPacketVisitor;
                if( rqPacketID > 10000 ){
                    switch( rqPacketID ){
                    case __EVENT_SOMETHING_DIED:
                        lpPacketVisitor = vPacketVisitor[ VISIT_SOMETHING_DIED ];
                        break;
                    case __EVENT_ATTACK:
                        lpPacketVisitor = vPacketVisitor[ VISIT_ATTACK ];
                        break;
                    case __EVENT_MISS:
                        lpPacketVisitor = vPacketVisitor[ VISIT_MISS ];
                        break;
                    case __EVENT_SKILL_USED:
                        lpPacketVisitor = vPacketVisitor[ VISIT_SKILL_USED ];
                        break;
                    case 10004:
                        lpPacketVisitor = vPacketVisitor[ VISIT_ADD_OBJECT ];
                        break;
                    default:
                        lpPacketVisitor = NULL;
                        break;
                    };
                }else{
                    lpPacketVisitor = vPacketVisitor[ rqPacketID ];
                } 
                
                if( lpPacketVisitor != NULL ){
                    lpPacketVisitor->AddPacket( nBufferSize );
                }
               

                // Send packet.
				// On envoie utilisant CCommCenter::SendPacket (l'envoi physique, par Windows)
                lpComm->SendPacket(
                    (*i),
                    lpbBuffer,
                    nBufferSize,
                    dwAckDelay,//BLBLBL cette valeur est initialisée dans la macro SET_ACK
                    dwMaxAck/*,//BLBLBL idem
                    lpPacketVisitor*/
                );


            }
        }else{
            TRACE( "\r\nSending %u.", rqPacketID );
            CPacketVisitor *lpPacketVisitor;
            if( rqPacketID > 10000 ){
                switch( rqPacketID ){
                case __EVENT_SOMETHING_DIED:
                    lpPacketVisitor = vPacketVisitor[ VISIT_SOMETHING_DIED ];
                    break;
                case __EVENT_ATTACK:
                    lpPacketVisitor = vPacketVisitor[ VISIT_ATTACK ];
                    break;
                case __EVENT_MISS:
                    lpPacketVisitor = vPacketVisitor[ VISIT_MISS ];
                    break;
                case __EVENT_SKILL_USED:
                    lpPacketVisitor = vPacketVisitor[ VISIT_SKILL_USED ];
                    break;
                case 10004:
                    lpPacketVisitor = vPacketVisitor[ VISIT_ADD_OBJECT ];
                    break;
                default:
                    lpPacketVisitor = NULL;
                    break;
                };
            }else{
                lpPacketVisitor = vPacketVisitor[ rqPacketID ];
            } 

            if( lpPacketVisitor != NULL ){
                lpPacketVisitor->AddPacket( nBufferSize );
            }
            
/*			if (rqPacketID != 10 && rqPacketID != 1) {//BLBLBL on logue pas les demandes d'ack au client ni les déplacements de PNJ...
			_LOG_DEBUG
                LOG_DEBUG_HIGH,
                "Sending direct packet type %u.", rqPacketID
            LOG_
			}*/

            // Send packet directly to client.
            lpComm->SendPacket( 
                sockAddr,
                lpbBuffer,
                nBufferSize,
                dwAckDelay,
                dwMaxAck/*,
                lpPacketVisitor*/
            );
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
CCommCenter *CPacketManager::GetCommCenter( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the const CommCenter object.
// 
// Return: const CCommCenter, the CommCenter
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock autoLock( &destroyCommLock );
    return lpComm;
}