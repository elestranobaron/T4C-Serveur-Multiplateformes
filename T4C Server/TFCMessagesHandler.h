// *******************************************************************************************
// ***                                                                                     ***
//      File Name: TFCMessagesHandler.h
//      Project:   TFC Server
//      Plateform: Windows NT 4.0 Workstation/Server
//      Creation:  14/1/1998
//      Author:    Francois Leblanc (FL)
// ***                                                                                     ***
// *******************************************************************************************
// ***                                                                                     ***
//      Change History
//
//         Date            Ver.      Author         Purpose
//         14/1/1998       1.0       FL             Initial developpement
//
//      Description
//          Provides a jump table for the packet messages functions. The dispatcher
//	verifies which function should interpret a specific message and then calls it.
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***           Copyright (c) 1997-1998 Virtual Dreams. All rights reserved.              ***


#if !defined(AFX_TFCMESSAGESHANDLER_H__01C599A4_8D10_11D1_BDF5_00E029058623__INCLUDED_)
#define AFX_TFCMESSAGESHANDLER_H__01C599A4_8D10_11D1_BDF5_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TFC_MAIN.H"

#define PACKET_FUNC_PROTOTYPE	TFCPacket *msg, Players *user, RQ_SIZE rqRequestID, sockaddr_in sockAddr
#define PACKET_FUNC_PARAM	msg, user, rqRequestID, sockAddr

#define GET_WORD( data )	msg->Get( (short *)&data );
#define GET_BYTE( data )	msg->Get( (char *)&data );
#define GET_CHAR( data )	msg->Get( (char *)&data );
#define GET_LONG( data )	msg->Get( (long *)&data );
// Mestoph : VÈrification de la taille des strings avant de lire le contenu du data

/*#define GET_STRING( data )	{ int __i; WORD wLen;\
	msg->Get( (short *)&wLen );\
	data = new BYTE[ wLen + 1 ];\
	for( __i = 0; __i < wLen; __i++ ){\
		msg->Get( (char *)&data[ __i ] );\
	} data[ __i ] = 0; }*/
#define GET_STRING( data )	{ int __i;\
	WORD wLen;\
	msg->Get( (short *)&wLen );\
	if (msg->CheckLen(wLen))\
	{\
		data = new BYTE[ wLen + 1 ];\
		for( __i = 0; __i < wLen; __i++ )\
		{\
			msg->Get( (char *)&data[ __i ] );\
		}\
		data[ __i ] = 0;\
	}\
	else\
	{\
		data = new BYTE[ 1 ];\
		data[ 0 ] = 0;\
		CT4CLog::DebugLog((1 << 6), "Received crash attempt from character %s (%s) from IP : %s", (LPCTSTR)user->self->GetTrueName(), (LPCTSTR)user->GetFullAccountName(), (LPCTSTR)user->GetIP());\
	}}
typedef void (*LPPACKET_FUNC)( PACKET_FUNC_PROTOTYPE );
typedef struct _LOCAL_USER{
    DWORD dwIP;
    DWORD dwNetmask;
} LOCAL_USER, *LPLOCAL_USER;

class TFCMessagesHandler  
{
public:
	// Create the handler
	static void Create( void );
    static void Destroy( void );
	
	// Dispatches a message
	static void DispatchPacket( PACKET_FUNC_PROTOTYPE );
	
	// Registers a function at which ID 'ID'
	static void RegisterFunction( LPPACKET_FUNC, RQ_SIZE rqRequestID );

    static cODBCMage *GetODBCAuth( void );


    static bool IsLocalIP( sockaddr_in sockAddr );
private:
	// All the message functions
	static void RQFUNC_Ack( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_PlayerMove( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_GetObject( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_DepositObject( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_PutPlayerInGame( PACKET_FUNC_PROTOTYPE );
	static void AsyncRQFUNC_RegisterAccountVOP( LPVOID lpData );
    static void AsyncRQFUNC_RegisterAccountODBC( LPVOID lpData );
    static void AsyncRQFUNC_RegisterAccountGOA( LPVOID lpData );
    static void RQFUNC_RegisterAccount( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_DeletePlayer( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_SendPeriphericObjects( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_GodCreateObject( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_ViewBackpack( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_ViewEquipped( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_ExitGame( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_EquipObject( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_UnequipObject( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_UseObject( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_Attack( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_CreatePlayer( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_GetPersonnalPClist( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_IndirectTalk( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_Shout( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_Page( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_DirectedTalk( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_Reroll( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_CastSpell( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_HPchanged( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_BroadcastTextChange( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_GetUnitName( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_BreakConversation( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_ReturnToMenu( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_GetSkillList( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_SendTrainSkillList( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_UseSkill( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_GetStatus( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_XPchanged( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_GetTime( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_FromPreInGameToInGame( PACKET_FUNC_PROTOTYPE );	
	static void RQFUNC_EnterChatterChannel( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_SendChatterMessage( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_GetChatterUserList( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_GetOnlinePlayerList( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_GetSkillStatPoints( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_GoldChange( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_ViewGroundItemIndentContent( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_SendTeachSkillList( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_SendBuyItemList( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_SendSellItemList( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_SendStatTrain( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_QueryItemName( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_GetNearItems( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_SendSpellList( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_QueryServerVersion( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_MessageOfDay( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_PuppetInformation( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_QueryUnitExistence( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_UseItemByAppearance( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_RemoveFromChatterChannel( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_GetChatterChannelList( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_UpdateGroupMembers( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_UpdateGroupInviteList( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_GroupInvite( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_GroupJoin( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_GroupLeave( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_GroupKick( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_JunkItems( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_ToggleChatterListening( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_GroupToggleAutoSplit( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_TogglePage( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_QueryNameExistence( PACKET_FUNC_PROTOTYPE );
    static void AsyncRQFUNC_QueryNameExistence( LPVOID lpData );
    static void RQFUNC_QueryPatchServerInfo( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_Rob( PACKET_FUNC_PROTOTYPE );
    static void RQFUNC_AuthenticateServerVersion( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_ChestRemoveItemToBackpack( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_ChestAddItemFromBackpack( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_TradeInvite( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_TradeCancel( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_TradeSetStatus( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_TradeAddItemFromBackpack( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_TradeRemoveItemToBackpack( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_TradeClear( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_QueryItemInfo( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_SafePlug( PACKET_FUNC_PROTOTYPE );
	static void RQFUNC_GetPvpRanking( PACKET_FUNC_PROTOTYPE ); // asteryth pvp ranking
private:    
    static DWORD GetUserMax( sockaddr_in sockAddr );
    static void MaxUserUpdate( void );

    static TemplateList <LOCAL_USER> tlLocalUsers;
    static DWORD dwMaxLocalUsers;
    static DWORD dwMaxRemoteUsers;
};

#endif // !defined(AFX_TFCMESSAGESHANDLER_H__01C599A4_8D10_11D1_BDF5_00E029058623__INCLUDED_)
