// PacketManager.h: interface for the CPacketManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKETMANAGER_H__17AFD9C8_48B7_11D2_83F1_00E02922FA40__INCLUDED_)
#define AFX_PACKETMANAGER_H__17AFD9C8_48B7_11D2_83F1_00E02922FA40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "CommCenter.h"
#include "TFCPacket.h"
#include "SharedStructures.h"
#include "Players.h"
#include "SendPacketVisitor.h"

#define COMM_INTR_PROTOTYPE sockaddr_in sockAddr, LPBYTE lpbBuffer, int nBufferSize
class CCommCenter;

class CPacketManager
{
public:
    static void Create();
    static void Destroy();

    static void PacketInterpret( COMM_INTR_PROTOTYPE );

    static void SendPacket( TFCPacket &pPacket, sockaddr_in sockAddr, int nBroadcastRange, WorldPos wlPos, BOOL boBroadcast, SendPacketVisitor *visit = NULL, bool inGame = true );

    static CCommCenter *GetCommCenter( void );

    static void PrintPacketReport( void );

    static void IncRecvPacketType( RQ_SIZE rqID );

private:
    static CCommCenter *lpComm;

};


#endif // !defined(AFX_PACKETMANAGER_H__17AFD9C8_48B7_11D2_83F1_00E02922FA40__INCLUDED_)
