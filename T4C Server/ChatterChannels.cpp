// ChatterChannels.cpp: implementation of the ChatterChannels class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "ChatterChannels.h"
#include <algorithm>
#include "TFCPacket.h"
#include "TFC_MAIN.h"
#include "PlayerManager.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;

// BEGIN : Mestoph -> Remove canal "Bugs" 
// const char Bugs[] = "Bugs";
// END : Mestoph -> Remove canal "Bugs" 


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ChatterChannels::ChatterChannels() : mainChannel( "Main" )
{
    Channel *lpChannel = &( mSystemChannels[ mainChannel ] );
    lpChannel->ciChannelID = mainChannel;

    //AddSystemChannel( Bugs ); //BLBLBL
	AddSystemChannel( "PVP" ); //BLBLBL
    
    publicChannelsForOperators = false;
}

ChatterChannels::~ChatterChannels()
{

}

//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::AddSystemChannel
//////////////////////////////////////////////////////////////////////////////////////////
//  Adds a system channel to the chatter channels.
// 
(
 std::string channelId
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cAutoLock( this );

    Channel *lpChannel = &( mSystemChannels[ channelId ] );
    lpChannel->ciChannelID = channelId;

}

//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::ClearSystemChannels( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Clears all system channels except the main one.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{   
    CAutoLock cAutoLock( this );

    mSystemChannels.clear();
    
    Channel *lpChannel = &( mSystemChannels[ mainChannel ] );
    lpChannel->ciChannelID = mainChannel;

//    AddSystemChannel( Bugs );
	AddSystemChannel( "PVP" ); //BLBLBL
}

//////////////////////////////////////////////////////////////////////////////////////////
string ChatterChannels::GetMainChannel( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the main channel's name
//////////////////////////////////////////////////////////////////////////////////////////
{
    return mainChannel;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool ChatterChannels::Add
//////////////////////////////////////////////////////////////////////////////////////////
// Add a player to a chatter channel, or create the chatter channel.
// 
(
 Players *lpPlayer,     // UserID of the player to add.
 ChannelID ciChannelID, // ID of the channel to add player to.
 string csPassword     // The password for the channel.
)
// Return: bool, true if the user could be added, false otherwise( wrong password).
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cAutoLock( this );

    // Get the channel.
    ChannelMap::iterator i = mChannels.find( ciChannelID );    

    Channel *lpChannel = NULL;

    // If the channel wasn't in the map.
    if( i == mChannels.end() ){

        // Try to find it in the system channels.
        i = mSystemChannels.find( ciChannelID );
        
        // If it couldn't be found in the system channels.
        if( i == mSystemChannels.end() ){
            // Get the channel (this will create a channel slot).
            lpChannel = &( mChannels[ ciChannelID ] );

            // Set the password.
            lpChannel->csPassword  = csPassword;

            // Set the channelID.
            lpChannel->ciChannelID = ciChannelID;
        }else{
            // No need to authenticate for system channels.
            lpChannel = &( (*i).second );
        }
    }else{
        lpChannel = &( (*i).second );
        // If passwords do not correspond and player isn't master.
        if( lpChannel->GetPassword() != csPassword && !( lpPlayer->GetGodFlags() & GOD_CHAT_MASTER ) ){
            // Verify if any channels are now empty.
            VerifyEmptyChannels();
        
            // Send a message sending the password was wrong
            lpPlayer->self->SendSystemMessage( _STR( 7506, lpPlayer->self->GetLang() ), RGB( 255, 0, 0 ) );

            // Refuse channel adding.
            return false;
        }
    }

    // Add the user to this channel.
	auto it = std::find_if(lpChannel->vUsers.begin(), lpChannel->vUsers.end(), [lpPlayer](Channel::ChannelUser & x) { return x.player == lpPlayer; });
	if (it == lpChannel->vUsers.end())
		lpChannel->vUsers.push_back( Channel::ChannelUser( lpPlayer ) );
    
    // Scroll through the new list of players.
    //Channel::UserCont::iterator j;
    //for( j = lpChannel->vUsers.begin(); j != lpChannel->vUsers.end(); j++ ){
    //    TRACE( "\n  %s.", (*j).player->self->GetTrueName() );
    //
    //    SendChannelUsers( (*j).player, lpChannel->GetID() );
    //}

    return true;
}
    
//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::Remove
//////////////////////////////////////////////////////////////////////////////////////////
// Remove a player from a chatter channel
// 
(
 Players *lpPlayer,     // ID of the user to remove.
 ChannelID ciChannelID  // The ID of the channel to remove the user from.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );
    
    ChannelMap::iterator i;

    // Try to find the channel
    i = mChannels.find( ciChannelID );

    // If the channel was not found.
    if( i == mChannels.end() ){
        
        // Try to find in system channels.
        i = mSystemChannels.find( ciChannelID );

        // If its not even in the system channels.
        if( i == mSystemChannels.end() ){
            return;
        }

        Channel &cChannel = (*i).second;

        // Try to find the player inside the system channel.
		auto k = std::find_if(cChannel.vUsers.begin(), cChannel.vUsers.end(), [lpPlayer](Channel::ChannelUser &x) {
			return lpPlayer == x.player;
		});

        // If the player wasn't found (??)
        if( k == cChannel.vUsers.end() ){
            return;
        }

        
        // If we were previously listening.
        if( k->listening ){

            // Simply toggle listening to false.
            k->listening = false;
            
            // To all users in the channel.
            //Channel::UserCont::const_iterator j;
            //for( j = cChannel.vUsers.begin(); j != cChannel.vUsers.end(); j++ ){
            //    // Send a user-listing update.
            //    SendChannelUsers( (*j).player, cChannel.GetID() );
            //}
        }
        
        // We cannot remove a user from a system channel.
        return;
    }

    Channel &cChannel = (*i).second;

    // Find the corresponding user in the chatter channel.
	auto j = std::find_if(cChannel.vUsers.begin(), cChannel.vUsers.end(), [lpPlayer](Channel::ChannelUser &x) {
		return lpPlayer == x.player;
	});

    // If the user was not found in the chatter channel.
    if( j == cChannel.vUsers.end() ){
        return;
    }

    // Remove it from the channel.
    cChannel.vUsers.erase( j );

    // To all users still in the channel.
    //for( j = cChannel.vUsers.begin(); j != cChannel.vUsers.end(); j++ ){
    //    // Send a user-listing update.
    //    SendChannelUsers( (*j).player, cChannel.GetID() );
    //}

    // Verify for empty channels.
    VerifyEmptyChannels();
}    

//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::Remove
//////////////////////////////////////////////////////////////////////////////////////////
// Remove any reference to a player in the chatter channels.
// 
(
 Players *lpPlayer // The player to remove from all chatter channels.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );
    
    ChannelMap::iterator i;

    // For all channels available
    for( i = mChannels.begin(); i != mChannels.end(); i++ ){
        Channel &cChannel = (*i).second;

        // If the player was erased from this set.
		cChannel.vUsers.remove_if([lpPlayer](Channel::ChannelUser &x) { return lpPlayer == x.player; });

    }

    // Search the system channels too.
    for( i = mSystemChannels.begin(); i != mSystemChannels.end(); i++ ){
        Channel &cChannel = (*i).second;

        // If the player was erased from this set.
		cChannel.vUsers.remove_if([lpPlayer](Channel::ChannelUser &x) { return lpPlayer == x.player; });
    }

    // Verify for empty channels.
    VerifyEmptyChannels();
}

//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::Talk
//////////////////////////////////////////////////////////////////////////////////////////
// Sends a message through a chatter channel.
// 
(
 Players *lpSender,     // ID of the sender.
 ChannelID ciChannelID, // Channel to send message from.
 string csMessage      // Message.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );

    // If user got squelched or has no more shouts.
    if( !lpSender->boCanShout /*|| !lpSender->boCanPage */){ //BLBLBL les pages n'ont rien à voir avec les CC...
		
        time_t tTestExpiration;
		time(&tTestExpiration);

		if (lpSender->lCutExpireDate>0 && lpSender->lCutExpireDate<tTestExpiration) {
						
			lpSender->Lock();
			lpSender->boCanShout = TRUE;
			lpSender->lCutExpireDate = 0;
			lpSender->self->SendSystemMessage( "Your pages have been automatically restored.", RGB( 0, 255, 0 ) );
			lpSender->Unlock();

		}else if (lpSender->lCutExpireDate>0){
		     // Get time in tm structure
			tm *tmTime = localtime( (const time_t*)&lpSender->lCutExpireDate ); // steph tm *tmTime = localtime( (const time_t*)&lpSender->lCutExpireDate ); au lieu de tm *tmTime = localtime( &lpSender->lCutExpireDate );
      
			CString csTemp;
			csTemp.Format("Your shouts are revoked until %s.", asctime(tmTime));
			lpSender->self->SendSystemMessage( csTemp, RGB( 255, 0, 0 ) );
		}else if (lpSender->lCutExpireDate<0){
		     // Get time in tm structure
			tm *tmTime = localtime( (const time_t*)&lpSender->lCutExpireDate ); // steph tm *tmTime = localtime( (const time_t*)&lpSender->lCutExpireDate ); au lieu de tm *tmTime = localtime( &lpSender->lCutExpireDate );
      
			CString csTemp;
			csTemp.Format("It seems there is a problem with your revoke delay : until %s. Contact a GM", asctime(tmTime));
			lpSender->self->SendSystemMessage( csTemp, RGB( 255, 0, 0 ) );

		}else{
			lpSender->self->SendSystemMessage( _STR( 7171, lpSender->self->GetLang() ), RGB( 255, 0, 0 ) );
		
		}
        
		//lpSender->self->SendSystemMessage( _STR( 7171, lpSender->self->GetLang() ) );
        return;
    }

    ChannelMap::iterator i;

    bool systemChannel = false;
    
    // Try to find the channel
    i = mChannels.find( ciChannelID );

    // If the channel was not found.
    if( i == mChannels.end() ){

        // Search the system channels.
        i = mSystemChannels.find( ciChannelID );
        if( i == mSystemChannels.end() ){
			return;
        }
        systemChannel = true;
    }

    Channel &cChannel = (*i).second;
	auto k = std::find_if(cChannel.vUsers.begin(), cChannel.vUsers.end(), [lpSender](Channel::ChannelUser &x) {
		return lpSender == x.player;
	});
    
    // If the user cannot be found in this channel (access right authentication) or isn't master.
    if( k == cChannel.vUsers.end() && !( lpSender->GetGodFlags() & GOD_CHAT_MASTER ) ){
        return;
    }

    if( k != cChannel.vUsers.end() ){
        // If the user isn't listening on the channel.
        if( !(*k).listening ){
            // It does not have the right to talk.
            return;
        }
    }

    if( systemChannel ){//BLBLBL le channel PVP est spécial
        // If the channel is locked by operators and the sender isn't a gameop
        if( (publicChannelsForOperators || ciChannelID=="PVP") && !( lpSender->GetGodFlags() & GOD_CHAT_MASTER ) ){
            //You may not shout right now
			lpSender->self->SendSystemMessage( _STR( 467, lpSender->self->GetLang() ), RGB( 255, 0, 0 ) );
            return;
        }

        // If the player cannot talk in public channels right now.
        if( !lpSender->CanShout() ){
			//You may not shout right now
            lpSender->self->SendSystemMessage( _STR( 467, lpSender->self->GetLang() ) );
            return;
        }
        lpSender->ToggleShout();

        _LOG_SHOUTS
            LOG_MISC_1,
            "Player %s said in public channel %s: %s",
            (LPCTSTR)lpSender->self->GetTrueName(),
            ciChannelID.c_str(),
            csMessage.c_str()
        LOG_
    }else{
        _LOG_PAGE
            LOG_MISC_1,
            "Player %s said in chatter channel %s: %s",
            (LPCTSTR)lpSender->self->GetTrueName(),
            ciChannelID.c_str(),
            csMessage.c_str()
        LOG_
    }


	/* BEGIN : Mestoph -> Remove canal "Bugs"
	// If this is the bugs system channel and the sender isn't the chat master
    if( systemChannel && ciChannelID == Bugs && !( lpSender->GetGodFlags() & GOD_CHAT_MASTER ) ){
        // Do not broadcast the message.
        return;        
    }
	END : Mestoph -> Remove canal "Bugs" */

    // Send the message to all players in the chatter channel.
    CString csSender     = lpSender->self->GetTrueName();
    CString csTheMessage = csMessage.c_str();
    CString csChatterID  = ciChannelID.c_str();

    // Scroll through the list of all player on this channel.
    Channel::UserCont::const_iterator j;
    for( j = cChannel.vUsers.begin(); j != cChannel.vUsers.end(); j++ ){
        
        // If the player is listening on the channel.
        if( (*j).listening ){            
            TFCPacket sending;
            sending << (RQ_SIZE)RQ_SendChatterMessage;
            sending << (CString &)csChatterID;
            sending << (CString &)csSender;
            sending << (CString &)csTheMessage;

            TRACE( "\nSending message to %s.", (*j).player->self->GetTrueName() );
        
            // Send them the message.
            (*j).player->self->SendPlayerMessage( sending );
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::SystemTalk //BLBLBL : new function to allow Server to talk on CCs
//////////////////////////////////////////////////////////////////////////////////////////
// Sends a message originated from the server program through a chatter channel.
// EG. For PVP messages
// 
(
 CString csEmitter,     // ID of the sender.
 ChannelID ciChannelID, // Channel to send message from.
 string csMessage      // Message.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );
   
    ChannelMap::iterator i;

    // Try to find the channel
    i = mChannels.find( ciChannelID );

    // If the channel was not found.
    if( i == mChannels.end() ){

        // Search the system channels.
        i = mSystemChannels.find( ciChannelID );
        if( i == mSystemChannels.end() ){
            return;//BLBL si aucune channel n'a pu être trouvée c'est que personne n'écoute ce canal, inutile d'envoyer.
        }
    }
    Channel &cChannel = (*i).second;
        
    // Send the message to all players in the chatter channel.
    CString csSender     = csEmitter;
    CString csTheMessage = csMessage.c_str();
    CString csChatterID  = ciChannelID.c_str();

    // Scroll through the list of all player on this channel.
    Channel::UserCont::const_iterator j;
    for( j = cChannel.vUsers.begin(); j != cChannel.vUsers.end(); j++ ){
        
        // If the player is listening on the channel.
        if( (*j).listening ){            
            TFCPacket sending;
            sending << (RQ_SIZE)RQ_SendChatterMessage;
            sending << (CString &)csChatterID;
            sending << (CString &)csSender;
            sending << (CString &)csTheMessage;

            TRACE( "\nSending message to %s.", (*j).player->self->GetTrueName() );
        
            // Send them the message.
            (*j).player->self->SendPlayerMessage( sending );
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::ToggleListening
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the new 'listening' state for a given channel.
// 
(
 Players *lpPlayer,     // The player requesting the state change.
 ChannelID ciChannelID, // The channel to change
 bool listenState       // The new listening state.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );
    
    ChannelMap::iterator i;
    
    // Try to find the channel
    i = mChannels.find( ciChannelID );

    // If the channel was not found.
    if( i == mChannels.end() ){

        // Search the system channels.
        i = mSystemChannels.find( ciChannelID );
        if( i == mSystemChannels.end() ){
            return;
        }
    }

    Channel &cChannel = (*i).second;
	auto k = std::find_if(cChannel.vUsers.begin(), cChannel.vUsers.end(), [lpPlayer](Channel::ChannelUser &x) {
		return lpPlayer == x.player;
	});

    // If the user isn't found in the chatter channel.
    if( k == cChannel.vUsers.end() ){
        return;
    }

    // Update the listening state.
    k->listening = listenState;

    // Scroll through the list of players.
    //Channel::UserCont::iterator j;
    //for( j = cChannel.vUsers.begin(); j != cChannel.vUsers.end(); j++ ){
    //    // Refresh the player list.
    //    SendChannelUsers( (*j).player, ciChannelID );
    //}

}

// Accessors        
//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::GetTotalChannelList
//////////////////////////////////////////////////////////////////////////////////////////
// Retreives the total list of channels.
// 
(
 vector< Channel > &vChannels // A container vector to put list of channels in.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );
    
    // Copy the map of system channels.
    ChannelMap::iterator i;
    for( i = mSystemChannels.begin(); i != mSystemChannels.end(); i++ ){
        vChannels.push_back( (*i).second );
    }

    // Copy map of channels into the provided container.    
    for( i = mChannels.begin(); i != mChannels.end(); i++ ){
        vChannels.push_back( (*i).second );
    }
}
    
//////////////////////////////////////////////////////////////////////////////////////////
bool ChatterChannels::GetChannelUsers
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the users in a chatter channel.
// 
(
 Players *lpPlayer,                 // The UserID of the player (for access right verification).
 ChannelID ciChannelID,             // The channel ID to get the list from.
 std::vector< Channel::ChannelUser > &vUsers   // The container into which we should copy the list of users.
)
// Return: bool, true of the list was obtained, false otherwise (player has access to chatter channel?)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );
    
    ChannelMap::iterator i;

    // Try to find the channel
    i = mChannels.find( ciChannelID );

    // If the channel was not found.
    if( i == mChannels.end() ){
        
        // Try to find it in the system channels.
        i = mSystemChannels.find( ciChannelID );

        if( i == mSystemChannels.end() ){
            return false;
        }
    }

    Channel &cChannel = (*i).second;
    // If the user is not god AND the channel has a password
    // AND the user isn't registered in this channel.
	auto k = std::find_if(cChannel.vUsers.begin(), cChannel.vUsers.end(), [lpPlayer](Channel::ChannelUser &x) {
		return lpPlayer == x.player;
	});


    if( !( lpPlayer->GetGodFlags() & GOD_CHAT_MASTER ) && 
        !( cChannel.csPassword.empty() ) &&
        k == cChannel.vUsers.end() ){        
        // Refuse access to user listing.
        return false;
    }

    // For all players in this channel.
    Channel::UserCont::iterator j;
    for( j = cChannel.vUsers.begin(); j != cChannel.vUsers.end(); j++ ){
        // If the player is not invisible.
        if( !(*j).player->boWhoInvisible ){
            // Add the player to the provided list of players.
            vUsers.push_back( (*j) );
        }
    }
    

    return true;
}
   
//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::GetRegisteredChannelList
//////////////////////////////////////////////////////////////////////////////////////////
// Retreives the list of channels a user is registered in.
// 
(
 Players *lpPlayer,                 // The ID of the player.
 std::vector< Channel > &vChannels  // The container of channels to put the list in.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );
    
    ChannelMap::iterator i;

    // For all channels available
    for( i = mChannels.begin(); i != mChannels.end(); i++ ){
        Channel &cChannel = (*i).second;

        // If the user is found in this channel
		auto k = std::find_if(cChannel.vUsers.begin(), cChannel.vUsers.end(), [lpPlayer](Channel::ChannelUser &x) {
			return lpPlayer == x.player;
		});

        if( k != cChannel.vUsers.end() ){
            // Add the channel to the list of registered channels for this user.
            vChannels.push_back( cChannel );            
        }
    }
}
    
//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::GetSystemChannelList
//////////////////////////////////////////////////////////////////////////////////////////
// Retreive the list of channels a user is allowed to view.
// 
(
 Players *lpPlayer,                 // The userID, for access-right verification.
 std::vector< Channel >&vChannels   // The container to put the channels in.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );

    ChannelMap::iterator i;

    // For all system channels.
    for( i = mSystemChannels.begin(); i != mSystemChannels.end(); i++ ){
        // Add them
        vChannels.push_back( (*i).second );
    }
}

// Private
//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::VerifyEmptyChannels( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Helper function which determines any empty channels and kills them.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock cLock( this );

    ChannelMap::iterator i;

    // For all non-system channels available
    for( i = mChannels.begin(); i != mChannels.end(); ){
        Channel &cChannel = (*i).second;

        TRACE( "\nvUsers.empty()=%u Password.empty()=%u.", cChannel.vUsers.empty(), cChannel.GetPassword().empty() );
        // If channel has no users
        if( cChannel.vUsers.empty() ){
            // Get a temporary iterator.
            ChannelMap::iterator iDelete = i;
            // Scroll to the next element
            i++;
            // Destroy the temporary iterator.
            mChannels.erase( iDelete );
        }else{
            // Otherwise simply scroll to next element.
            i++;
        }

    }

}

//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::PacketChannelList
//////////////////////////////////////////////////////////////////////////////////////////
//  Packets a channel list.
// 
(
 Players *target,
 std::vector< Channel > &vChannels, // The channel list to packet.
 TFCPacket &sending                 // The packet.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    sending << (short)vChannels.size();
    // For all channels
    vector< Channel >::iterator i;
    for( i = vChannels.begin(); i != vChannels.end(); i++ ){
        CString csChannelID = (*i).GetID().c_str();
        // Send the channel ID
        sending << (CString &)( csChannelID );

        // If player cannot be found inside this channel
		auto k = std::find_if((*i).vUsers.begin(), (*i).vUsers.end(), [target](Channel::ChannelUser &x) {
			return target == x.player;
		});

        
        if( k == (*i).vUsers.end() ){
            // It does not listen on the channel.
            sending << (char)0;
        }else{
            // Otherwise send the listening byte.
            sending << (char)( (*k).listening ? 1 : 0 );            
        }
    }
}
    
//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::SendTotalChannelList
//////////////////////////////////////////////////////////////////////////////////////////
// Sends the total list of channels to the lpPlayer.
// 
(
 Players *lpPlayer // The player to send the channel list to.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    vector< Channel > vChannels;

    // Get the total list of channels
    GetTotalChannelList( vChannels );

    TFCPacket sending;
    sending << (RQ_SIZE)RQ_GetChatterChannelList;
    PacketChannelList( lpPlayer, vChannels, sending );
    
    lpPlayer->self->SendPlayerMessage( sending );
}

 
//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::SendChannelUsers
//////////////////////////////////////////////////////////////////////////////////////////
// Sends the channel users to the lpPlayer.
// 
(
 Players *lpPlayer,     // The player to send the user listing to.
 ChannelID ciChannelID  // The chatter to retreive the users from.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    vector< Channel::ChannelUser > vUsers;
    
    TFCPacket sending;
    sending << (RQ_SIZE)RQ_GetChatterUserList;

    sending << (string &)ciChannelID;

    bool getAccountNames = false;
    if( lpPlayer->GetGodFlags() & GOD_CAN_SEE_ACCOUNTS ){
        getAccountNames = true;
    }

    // If the user could retreive the list of players in the chatter channel.
    if( GetChannelUsers( lpPlayer, ciChannelID, vUsers ) ){
        // Packet quantity of users.
        sending << (short)vUsers.size();
        
        // Scroll through the list of players.
        vector< Channel::ChannelUser >::iterator i;        
        for( i = vUsers.begin(); i != vUsers.end(); i++ ){
            // Get their names
            CString csName = (*i).player->self->GetTrueName();
            // Packet their names
            sending << (CString &)csName;
            sending << (CString &)(*i).player->self->GetTitle( getAccountNames );
			sending << (CString &)(*i).player->self->GetGuild(getAccountNames); // steph ajout

            sending << (char)( (*i).listening ? 1 : 0 );
        }                
    }else{
        sending << (short)0;
    }

    // Send packet.
    lpPlayer->self->SendPlayerMessage( sending );
}

//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::SendRegisteredChannelList
//////////////////////////////////////////////////////////////////////////////////////////
// Sends the channel listing to the lpPlayer
// 
(
 Players *lpPlayer // The player to send the listing to.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    vector< Channel > vChannels;

    // Get the list of private and system channels.
    GetSystemChannelList( lpPlayer, vChannels );
    GetRegisteredChannelList( lpPlayer, vChannels );

    TFCPacket sending;
    sending << (RQ_SIZE)RQ_GetChatterChannelList;
    PacketChannelList( lpPlayer, vChannels, sending );
    
    lpPlayer->self->SendPlayerMessage( sending );
}    

//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::AddToSystemChannels
//////////////////////////////////////////////////////////////////////////////////////////
// Adds a new player to all the system channels.
// 
(
 Players *lpPlayer // The player.
)
//////////////////////////////////////////////////////////////////////////////////////////
{    
    ChannelMap::iterator i;

    for( i = mSystemChannels.begin(); i != mSystemChannels.end(); i++ ){    
        Channel *lpChannel = &(*i).second;

        // Add the user to this channel.
		auto it = std::find_if(lpChannel->vUsers.begin(), lpChannel->vUsers.end(), [lpPlayer](Channel::ChannelUser & x) { return x.player == lpPlayer; });
		if(it == lpChannel->vUsers.end())
			lpChannel->vUsers.push_back(Channel::ChannelUser(lpPlayer));

    
        // Scroll through the new list of players.
        //Channel::UserCont::iterator j;
        //for( j = lpChannel->vUsers.begin(); j != lpChannel->vUsers.end(); j++ ){
        //    TRACE( "\n  %s.", (*j).player->self->GetTrueName() );
        //
        //    SendChannelUsers( (*j).player, lpChannel->GetID() );
        //}
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void ChatterChannels::SetOperatorPublicChannelControl
//////////////////////////////////////////////////////////////////////////////////////////
// Sets whether or not the public channels are now for operators only.
// 
(
 bool val
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    publicChannelsForOperators = val;
}