// PlayerManager.h: interface for the CPlayerManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYERMANAGER_H__17AFD9C7_48B7_11D2_83F1_00E02922FA40__INCLUDED_)
#define AFX_PLAYERMANAGER_H__17AFD9C7_48B7_11D2_83F1_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "Players.h"
#include "Lock.h"
#include <vector>
#include <string>
#include "ChatterChannels.h"

using namespace std;

class Players;
class ChatterChannels;

typedef pair< string, string > UserInfo;

class EXPORT CPlayerManager  
{
public:
    static void Create( void );
    static void Destroy( void );

    // Player resource checking.
    static Players *GetPlayerResource( sockaddr_in sockAddr );
    static void     FreePlayerResource( Players *lpPlayer );
	static BOOL		SearchForConnection( const sockaddr_in &sockAddr ); // search the registered users to see if this address match any connected user. Returns TRUE when found.

    static Players *CreatePlayer( sockaddr_in sockAddr, CString csAccountName );
    static void     DeletePlayer( Players *lpPlayer, BOOL boIdle = FALSE );
    
    // Fetches the IPs of all players targetted by a broadcasted message.
    static void GetGlobalBroadcastAddress( vector< sockaddr_in > &vAddresses, SendPacketVisitor *packetVisitor, bool inGame = true );
    static void GetLocalBroadcastAddress ( vector< sockaddr_in > &vAddresses, WorldPos wlPos, int nRange, SendPacketVisitor *packetVisitor );
    
    // Returns user names or adresses.
    static BOOL PageUser( Players *sender, CString &csName, CString csSender, CString csMessage, bool boCanPageInvisible );
    static void PacketUserList( Players *lpUser );
    
    static int  GetUserCount( void ){ return nUserCount; };

    static BOOL VerifyPlayerUnique( Players *lpPlayer );

    static Players *GetCharacter( CString csName );

    static bool MSComGetUserList( BYTE bCode, LPBYTE &lpBuffer, int &nBufferLen );

    static void SaveAll( void );

    static void RemoveTargetReferences( Unit *targetUnit );

    static ChatterChannels &GetChatter( void );

    static void RefreshSystemChannels();

    static int      GetnBufferSize( void ){ return nBufferSize; };
    static Players **GetBufferList( void ){ return lpRegisteredUsers; };
    static CLock   *GetLockFetch( void ){ return &cFetchLock; };

protected:
    static void GrowBufferSpace( void );
    static void PlayerMaintenance( LPVOID lpData );

    static void AsyncDeletePlayer( LPVOID lpData );

    static HANDLE hDeletionIo;

    static Players **lpRegisteredUsers;
    static int nUserCount;
    static int nBufferSize;

    static CLock cUserLock;
    static CLock cMaintenanceLock;
    static CLock cFetchLock;

    static HANDLE hMaintenanceThread;
    
    static ChatterChannels *lpChatter;
};

#endif // !defined(AFX_PLAYERMANAGER_H__17AFD9C7_48B7_11D2_83F1_00E02922FA40__INCLUDED_)
