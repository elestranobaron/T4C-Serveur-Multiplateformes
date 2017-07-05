// Broadcast.cpp: implementation of the Broadcast class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "Broadcast.h"
#include "tfc_main.h"
#include "TFCPacket.h"
#include "SharedStructures.h"
#include "PacketManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static sockaddr_in sockDummyAddr;

//////////////////////////////////////////////////////////////////////////////////////////
void Broadcast::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Create the broadcasting class.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    sockDummyAddr;
    memset( &sockDummyAddr, 0, sizeof( sockaddr_in ) );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Broadcast::BCast
//////////////////////////////////////////////////////////////////////////////////////////
// Broadcast a packet. This is the best function to broadcast.
// 
(
 WorldPos where,        // For local broadcasts
 unsigned char range,   // Range of local broadcasts, 0 for global broadcast.
 TFCPacket &sending,    // The packet to send,
 SendPacketVisitor *packetVisitor //BLinfo : parfois c'est GetInvisibleQuery() qui donne ce param 
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Old protocol needed range to be 0 for global broadcasts.
    int nRange = range == 0 ? -1 : range;

    // Send message.
    CPacketManager::SendPacket(
        sending,
        sockDummyAddr,
        nRange,
        where,
        TRUE,
        packetVisitor
    );
}
/*
//////////////////////////////////////////////////////////////////////////////////////////
void Broadcast::BCMove
//////////////////////////////////////////////////////////////////////////////////////////
// Broadcast a move
// 
(
 WorldPos where, // 
 unsigned char range // 
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TFCPacket packet;
    //packet << (short)0; // Event type packet
    packet << (RQ_SIZE)__EVENT_OBJECT_MOVED
		    packet << (short)where.X;
		    packet << (short)where.Y;     // where the player has moved (is now)
		    //packet << (short)where.world;
		    packet << (long) param[0];    // param[0] is the player's ID
		    packet << (short)param[1];	 // player appearance;
		    packet << (char)param[2];	// player's radiance.
            packet << (char)param[3];   // unit's status byte.
	    } break;
    // When a player drops an object
    case __EVENT_OBJECT_APPEARED:
	    {
    #ifdef _DEBUG
		    ASSERT(param != NULL);
    #endif
		    packet << (short)where.X;
		    packet << (short)where.Y;	
		    packet << (short)param[0]; // The object type (appearance)
		    packet << (long)param[1]; // hurray 32bit compilers! this is possible without loss of data
								      // param[0] is the itemID
		    packet << (char)param[2]; // how the object appeared (effect)
		    packet << (char)param[3];	// the object's radiance.
            packet << (char)param[4];  // the object's outline status.
	    } break;
    case __EVENT_OBJECT_APPEARED_LIST:
	    {
    #ifdef _DEBUG
		    ASSERT(param != NULL);
    #endif
		    packet << (short)where.X;
		    packet << (short)where.Y;	
		    packet << (short)param[0]; // The object type (appearance)
		    packet << (long)param[1]; // hurray 32bit compilers! this is possible without loss of data
								      // param[0] is the itemID
		    packet << (char)param[2]; // how the object appeared (effect)
	    } break;
*/
//////////////////////////////////////////////////////////////////////////////////////////
void Broadcast::BCObjectChanged
//////////////////////////////////////////////////////////////////////////////////////////
// Broadcast an object changed.
// 
(
 WorldPos where,        // For local broadcasts
 unsigned char range,   // Range of local broadcasts, 0 for global broadcast.
 WORD  objectType,      // The new object type
 DWORD objectId,        // The object's ID.
 SendPacketVisitor *packetVisitor
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TFCPacket sending;
    sending << (RQ_SIZE)__EVENT_OBJECT_CHANGED;
    sending << (short)objectType;
    sending << (long)objectId;

    BCast( where, range, sending, packetVisitor );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Broadcast::BCObjectRemoved
//////////////////////////////////////////////////////////////////////////////////////////
// Broadcast an object removal.
// 
(
 WorldPos where,        // For local broadcasts
 unsigned char range,   // Range of local broadcasts, 0 for global broadcast.
 DWORD objectId,        // The object's ID.
 SendPacketVisitor *packetVisitor
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TFCPacket sending;
    sending << (RQ_SIZE)__EVENT_OBJECT_REMOVED;
    sending << (char)0; // how the object was removed (effect) = 0
	sending << (long)objectId; // ID of the object
    BCast( where, range, sending, packetVisitor );
}
    // If something died
   /* case __EVENT_SOMETHING_DIED:
	    {
    #ifdef _DEBUG
		    ASSERT(param != NULL);
    #endif		
		    packet << (long)param[0]; // PlayerID
	    }break;

    case __EVENT_SHOUT:
	    {
    #ifdef _DEBUG
		    ASSERT(param != NULL);
    #endif
		    packet << (long)param[0];		// ID
		    packet << (char)param[3];		// direction
		    packet << (long)param[2];		// color
            packet << (char)param[5]; // not an NPC.
		    // message
            char *str = (char *)param[1];
		    packet << (short)strlen(str);
		    
		    i = 0;
		    while(str[i]) packet << (char)str[i++];

            // name
            str = (char *)param[4];
            packet << (short)strlen(str);
		    
            i = 0;
		    while(str[i]) packet << (char)str[i++];
	    }break;
*/

//////////////////////////////////////////////////////////////////////////////////////////
void Broadcast::BCAttack
//////////////////////////////////////////////////////////////////////////////////////////
// Broadcast an attack.
// 
(
 WorldPos where,        // For local broadcasts
 unsigned char range,   // Range of local broadcasts, 0 for global broadcast.
 DWORD attackerId,        // The attacker's ID.
 DWORD defenderId,        // The target's ID.
 char  hpPercentage,    // The Hp percentage.
 WorldPos attackerPos,  // The attacker's position.
 WorldPos defenderPos,  // The defender's position.
 SendPacketVisitor *packetVisitor
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TFCPacket sending;
    sending << (RQ_SIZE)__EVENT_ATTACK;
    sending << (long)attackerId; // ID of the attacker
    sending << (long)defenderId; // ID of the attacked
    sending << (char)0; // kind of attack used
    sending << (char)0; // kind of dodge used		        
    sending << (char)hpPercentage; // Pourcentage of   HP vs MaxHP
    sending << (short)attackerPos.X; // Attacker X pos
    sending << (short)attackerPos.Y; // Attacker Y pos
    sending << (short)defenderPos.X;
    sending << (short)defenderPos.Y;
	
    BCast( where, range, sending, packetVisitor );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Broadcast::BCMiss
//////////////////////////////////////////////////////////////////////////////////////////
// Broadcast a miss.
//
(
 WorldPos where,        // For local broadcasts
 unsigned char range,   // Range of local broadcasts, 0 for global broadcast.
 DWORD attackerId,      // The attacker's ID.
 DWORD defenderId,      // The defender's ID.
 WorldPos attackerPos,  // The attacker's position.
 WorldPos defenderPos,  // The defender's position.
 SendPacketVisitor *packetVisitor
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TFCPacket sending;
    sending << (RQ_SIZE)__EVENT_MISS;
    sending << (long)attackerId; // attacker's ID
    sending << (long)defenderId; // defender's ID
    sending << (short)attackerPos.X; // attacker X pos
    sending << (short)attackerPos.Y; // attacker Y pos
    sending << (short)defenderPos.X;
    sending << (short)defenderPos.Y;

    BCast( where, range, sending, packetVisitor );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Broadcast::BCSkillUsed
//////////////////////////////////////////////////////////////////////////////////////////
// Broadcast a skill usage
// 
(
 WorldPos where,        // For local broadcasts
 unsigned char range,   // Range of local broadcasts, 0 for global broadcast.
 WORD skillId,          // The skill ID.
 SendPacketVisitor *packetVisitor
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TFCPacket sending;
    sending << (RQ_SIZE)__EVENT_SKILL_USED;
    sending << (short)skillId;
    sending << (short)0;

    BCast( where, range, sending, packetVisitor );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Broadcast::BCSpellEffect
//////////////////////////////////////////////////////////////////////////////////////////
// Broadcast a spell effect.
// 
(
 WorldPos where,        // For local broadcasts
 unsigned char range,   // Range of local broadcasts, 0 for global broadcast.
 WORD spellId,
 DWORD casterId,
 DWORD targetId,
 WorldPos casterPos,
 WorldPos targetPos,
 DWORD spellEffectId,
 DWORD spellChildId,
 SendPacketVisitor *packetVisitor
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TFCPacket sending;
    sending << (RQ_SIZE)__EVENT_SPELL_EFFECT;//RQ_CastSpell
    sending << (short)spellId;  // SpellID
    sending << (long) casterId;  // Caster's ID.
    sending << (long) targetId;  // Target's ID.
    sending << (short)targetPos.X;  // Target XPos.
    sending << (short)targetPos.Y;  // Target YPos.
    sending << (short)casterPos.X;  // Caster's XPos.
    sending << (short)casterPos.Y;  // Caster's YPos.
    sending << (long)spellEffectId;  // The spell effect's unique ID.
    sending << (long)spellChildId;  // The spell effect's child effect ID.

    BCast( where, range, sending, packetVisitor );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Broadcast::BCServerMessage
//////////////////////////////////////////////////////////////////////////////////////////
// Broadcast a server message
// 
(
 WorldPos where,        // For local broadcasts
 unsigned char range,   // Range of local broadcasts, 0 for global broadcast.
 CString serverMsg,
 SendPacketVisitor *packetVisitor,
 DWORD color
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TFCPacket sending;
    sending << (RQ_SIZE)RQ_ServerMessage;
    sending << (short)30;
    sending << (short)3;
    sending << (CString &)serverMsg;
	sending << (long)color;

    BCast( where, range, sending, packetVisitor );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Broadcast::BCWeatherMsg
//////////////////////////////////////////////////////////////////////////////////////////
// Broadcast a rain message
// 
(
 WorldPos where,        // For local broadcasts
 unsigned char range,   // Range of local broadcasts, 0 for global broadcast.
 DWORD weatherEffect,   // Snow, Fog, Rain, ...
 short value,			// Value of the msg (on/off)
 SendPacketVisitor *packetVisitor
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TFCPacket sending;
    sending << (RQ_SIZE)RQ_WeatherMsg;
	sending << (long)weatherEffect;
    sending << (short)value;

    BCast( where, range, sending, packetVisitor );
}
