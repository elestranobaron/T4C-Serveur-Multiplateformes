// *******************************************************************************************
// ***                                                                                     ***
//      File Name: ChatterChannels.h
//      Project:   T4C Server
//      Plateform: Windows NT
//      Creation:  26/4/1999
//      Author:    Francois Leblanc (FL)
// ***                                                                                     ***
// *******************************************************************************************
// ***                                                                                     ***
//      Change History
//
//         Date            Ver.      Author         Purpose
//         26/4/1999       1.0       FL             Initial developpement
//
//      Description
//          This is a class which handled chatter channels.
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***             Copyright (c) 1997-1999 Vircom inc. All rights reserved.                ***


#if !defined(AFX_CHATTERCHANNELS_H__C1BE8A83_FBFB_11D2_84F0_00E02922FA40__INCLUDED_)
#define AFX_CHATTERCHANNELS_H__C1BE8A83_FBFB_11D2_84F0_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#pragma warning( disable:4786 )
#endif // _MSC_VER >= 1000

#include <map>
#include <set>
#include <list>
#include <string>
#include "Lock.h"
#include "Players.h"

class ChatterChannels : public CLock
{
public:
	ChatterChannels();
	virtual ~ChatterChannels();

    typedef std::string ChannelID;

    // Handles channel-specific data.
    class Channel{
        friend ChatterChannels;
    public:
        // Accessors
        inline const std::string GetPassword( void ) const;

        inline const ChannelID GetID( void ) const;

        Channel &operator = ( const Channel &cChannel ){
            vUsers      = cChannel.vUsers;
            csPassword  = cChannel.csPassword;            
            return *this;
        }
        
    private:
        class ChannelUser{
        public:
            ChannelUser( Players *newPlayer ) : player( newPlayer ), listening( true ){}

            Players *player;
            bool     listening;            
        };

        class UserCompare{
        public:
            bool operator()( const ChannelUser &left, const ChannelUser &right ) const{
                return( left.player < right.player );
            }
        };

        typedef std::list< ChannelUser> UserCont;

        ChannelID                ciChannelID;
        UserCont                 vUsers;
        std::string              csPassword;
    };

    string GetMainChannel();

    // Add a player to a chatter channel, or create the chatter channel.
    bool Add( Players *lpPlayer, ChannelID ciChannelID, std::string csPassword = "" );

    // Remove a player from a chatter channel
    void Remove( Players *lpPlayer, ChannelID ciChannelID );

    // Remove any reference to a player in the chatter channels.
    void Remove( Players *lpPlayer );

    // Sends a message through a chatter channel.
    void Talk( Players *lpSender, ChannelID ciChannelID, std::string csMessage );

    // BLBLBL Sends a message through a chatter channel originated from the SYSTEM
    void SystemTalk( CString csEmitter, ChannelID ciChannelID, std::string csMessage );

    // Accessors
    // Retreives the total list of channels.
    void GetTotalChannelList( std::vector< Channel > &vChannels );

    // Returns the users in a chatter channel.
    bool GetChannelUsers( Players *lpPlayer, ChannelID ciChannelID, std::vector< Channel::ChannelUser > &vUsers );

    // Retreives the list of channels a user is registered in.
    void GetRegisteredChannelList( Players *lpPlayer, std::vector< Channel > &vChannels );

    // Retreive the list of channels a user is allowed to view.
    void GetSystemChannelList( Players *lpPlayer, std::vector< Channel >&vChannels );

    // Sends the total list of channels to the lpPlayer.
    void SendTotalChannelList( Players *lpPlayer );

    // Sends the channel users to the lpPlayer.
    void SendChannelUsers( Players *lpPlayer, ChannelID ciChannelID );

    // Sends the channel listing to the lpPlayer
    void SendRegisteredChannelList( Players *lpPlayer );

    // Sets the new 'listening' state for a given channel.
    void ToggleListening( Players *lpPlayer, ChannelID ciChannelID, bool listenState );

    // Adds a new player to all the system channels.
    void AddToSystemChannels( Players *lpPlayer );

    // Add a new system channel
    void AddSystemChannel( std::string channelId );

    // Clears all system channels except Main
    void ClearSystemChannels();

    void SetOperatorPublicChannelControl( bool val );

private:    
    class ChannelCompare{
    public:
        bool operator()( const std::string csLeft, const std::string csRight ) const{
            return( CMP( csLeft.c_str(), csRight.c_str() ) < 0 );
        }
    };
    
    typedef std::map< ChannelID, Channel, ChannelCompare > ChannelMap;

    void VerifyEmptyChannels( void );

    void PacketChannelList( Players *target, std::vector< Channel > &vChannels, TFCPacket &sending );

    string mainChannel;

    // Map of channels handled by the class.
    ChannelMap mChannels;

    ChannelMap mSystemChannels;

    bool publicChannelsForOperators;
};

// Chatter class.
//////////////////////////////////////////////////////////////////////////////////////////
const std::string ChatterChannels::Channel::GetPassword( void ) const
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the chatter channel's password.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return csPassword;
}

//////////////////////////////////////////////////////////////////////////////////////////
const ChatterChannels::ChannelID ChatterChannels::Channel::GetID( void ) const
//////////////////////////////////////////////////////////////////////////////////////////
// Return the chatter channel's binded ID.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return ciChannelID;
}

#endif // !defined(AFX_CHATTERCHANNELS_H__C1BE8A83_FBFB_11D2_84F0_00E02922FA40__INCLUDED_)
