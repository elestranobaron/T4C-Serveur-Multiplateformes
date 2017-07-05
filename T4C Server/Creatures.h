// Creatures.h: interface for the Creatures class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CREATURES_H__D16DFF13_F881_11D0_88E4_00E029058623__INCLUDED_)
#define AFX_CREATURES_H__D16DFF13_F881_11D0_88E4_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Objects.h"
#include "SharedStructures.h"
#include "Directions.h"
#include "Unit.h"
#include "Hive.h"


class EXPORT Creatures : public Unit
{
public:
	Creatures();
	
	// Monster behavior handling functions
	//void Action(CB::behave which, Unit *Target, signed long &strike = dummy);
		
	// Position handle functions
	WorldPos MoveCreature(DIR::MOVE where);
	
    WorldPos MoveUnit(DIR::MOVE where, BOOL boMoveAbsolute, bool boCompress, bool boBroadcastMove );

	// Combat Structures
	int hit(LPATTACK_STRUCTURE strike, Unit *WhoHit);
	void Death( LPATTACK_STRUCTURE lpBlow, Unit *WhoHit );
    int attacked(LPATTACK_STRUCTURE strike, Unit *Mechant){ return Unit::attacked( strike, Mechant ); };

	EXHAUST GetExhaust();
	void SetExhaust(EXHAUST newExhaust);

	WORD GetClan();
	void SetClan(WORD newClan);

	char GetAgressivness();
	void SetAgressivness(char newAgressive);

	WorldPos Destination();
	void SetDestination(WorldPos newDestination);

	UINT GetIdleTime();
	void SetIdleTime(UINT newTime);

	DWORD GetTrueMaxHP();
	void  SetMaxHP(DWORD newMax);

	DWORD GetHP();
	void  SetHP(DWORD newMax, bool boUpdate );

	WORD  GetTrueMaxMana();
	void  SetMaxMana(WORD newMax);
	
	WORD GetMana();
	void  SetMana(WORD newMax);

	void SetDetectRange( BYTE );
	BYTE GetDetectRange( void );

	void SetLastTeleport( WorldPos WL );
	WorldPos GetLastTeleport( void );

	BOOL CanAttack( void );
	void SetAttack( BOOL boCanAttack );

	BOOL CanMove( void );
	void SetCanMove( BOOL boCanMove );

	void SetBindedHive( Hive *lpHive );

    void SetPrivateTalk( BOOL boPrivate );
    BOOL IsPrivateTalk( void );

    void PacketPuppetInfo( TFCPacket &sending );

    void VaporizeUnit( void );

private:
    virtual ~Creatures();
    //void operator delete( void * ){};

    BOOL boPrivate;

	Hive *lpHive;

	BOOL boCanMove;
	BOOL boCanAttack;
	DWORD HP;
	DWORD MaxHP;

	WORD Mana;
	WORD MaxMana;
	
	BYTE bScanRange;

	EXHAUST exhaust;

	WorldPos dest;
	WorldPos wlLastTeleport;

	UINT IdleTime;

	WORD clan;						// clan with which the unit interacts
	char agressive;					// agressivness level
};
#endif // !defined(AFX_CREATURES_H__D16DFF13_F881_11D0_88E4_00E029058623__INCLUDED_)
