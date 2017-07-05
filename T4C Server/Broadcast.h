// Broadcast.h: interface for the Broadcast class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROADCAST_H__533D36A3_D2A7_11D0_B549_86A3B4000000__INCLUDED_)
#define AFX_BROADCAST_H__533D36A3_D2A7_11D0_B549_86A3B4000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TFCPacket.h"
#include "SharedStructures.h"
#include "EventListing.h"
#include "SendPacketVisitor.h"

class EXPORT Broadcast  
{
public:
	static void Create();

	static void BCast(WorldPos where, unsigned char range, TFCPacket &packet, SendPacketVisitor *packetVisitor = NULL );

    static void BCObjectChanged( WorldPos where, unsigned char range, 
                    WORD  objectType,
                    DWORD objectId, 
                    SendPacketVisitor *packetVisitor = NULL );
    
    static void BCObjectRemoved( WorldPos where, unsigned char range,
                    DWORD objectId,
                    SendPacketVisitor *packetVisitor = NULL );

    static void BCAttack( WorldPos where, unsigned char range, 
                    DWORD attackerId, 
                    DWORD defenderId,        // The target's ID.
                    char  hpPercentage,    // The Hp percentage.
                    WorldPos attackerPos,  // The attacker's position.
                    WorldPos defenderPos,  // The defender's position.
                    SendPacketVisitor *packetVisitor = NULL );

    static void BCMiss( WorldPos where, unsigned char range,
                    DWORD attackerId,
                    DWORD defenderId,      // The defender's ID.
                    WorldPos attackerPos,  // The attacker's position.
                    WorldPos defenderPos,  // The defender's position.
                    SendPacketVisitor *packetVisitor = NULL );

    static void BCSkillUsed( WorldPos where, unsigned char range,
                    WORD skillId,          // The skill ID.
                    SendPacketVisitor *packetVisitor = NULL );

    static void BCSpellEffect( WorldPos where, unsigned char range,
                    WORD spellId,
                    DWORD casterId,
                    DWORD targetId,
                    WorldPos casterPos,
                    WorldPos targetPos,
                    DWORD spellEffectId,
                    DWORD spellChildId,
                    SendPacketVisitor *packetVisitor = NULL );

    static void BCServerMessage( WorldPos where, unsigned char range,
                    CString serverMsg,
                    SendPacketVisitor *packetVisitor = NULL,
					DWORD color = 0x000A64E0/*RGB( 0, 100, 255 )*/);
	static void BCWeatherMsg( WorldPos where, unsigned char range, 
						   DWORD weatherEffect,
						   short value,
						   SendPacketVisitor *packetVisitor = NULL );

};

//extern Broadcast *__declspec(dllexport)bcast;

#endif // !defined(AFX_BROADCAST_H__533D36A3_D2A7_11D0_B549_86A3B4000000__INCLUDED_)
