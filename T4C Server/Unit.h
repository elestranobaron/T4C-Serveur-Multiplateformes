// *******************************************************************************************
// ***                                                                                     ***
//      File Name: Unit.h
//      Project:   TFC Server
//      Plateform: Windows NT 4.0 Workstation/Server
//      Creation:  15/1/1998
//      Author:    Francois Leblanc (FL)
// ***                                                                                     ***
// *******************************************************************************************
// ***                                                                                     ***
//      Change History
//
//         Date            Ver.      Author         Purpose
//         ??/??/1997      1.0       FL             Initial developpement
//
//      Description
//          Provides a common structure for all unit (objects, NPCs and PCs). Specific
//      behaviors are derived in Creatures and Objects.
// ***                                                                                     ***
//	*******************************************************************************************
// ***           Copyright (c) 1997-1998 Virtual Dreams. All rights reserved.              ***


#pragma warning( disable : 4786 )

#if !defined(AFX_UNIT_H__7F4A9E93_0C24_11D1_BCD5_00E029058623__INCLUDED_)
#define AFX_UNIT_H__7F4A9E93_0C24_11D1_BCD5_00E029058623__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "stdafx.h"
#include "Colors.h"
#include "SharedStructures.h"
#include "Messages.h"
#include "Doings.h"
#include "Directions.h"
#include "StatModifierFlagsListing.h"
#include "TFCPacket.h"
#include "TFCTimers.h"
#include "DynamicFlags.h"
#include "UnitEffectManager.h"
#include "vdlist.h"
#include "ObjectTimer.h"
#include "ODBCMage.h"
#include "Lock.h"
#include "BoostFormula.h"
#include "SendPacketVisitor.h"
#include <list>
#include <map>

#define UNIT_FUNC_PROTOTYPE	Unit *self, Unit *medium, Unit *target, LPVOID valueIN, LPVOID valueOUT
#define UNIT_FUNC_PARAM		self, medium, target, valueIN, valueOUT

typedef int SkillID;
typedef int SkillPnt;

class Unit;

#define DO_NOT_SAVE		1

typedef struct _DATA_SAVE{
	BYTE    bBufferSize;
	LPBYTE  lpbData;
	BYTE	bSave;
} DATA_SAVE, *LPDATA_SAVE;

typedef struct _EXHAUST{
	DWORD attack;
	DWORD move;
    BOOL  boWalking;
	DWORD mental;
} EXHAUST, *LPEXHAUST;

typedef struct _INDUCED_EXHAUST{
    BoostFormula bfAttack;
    BoostFormula bfMove;
    BoostFormula bfMental;
} INDUCED_EXHAUST, *LPINDUCED_EXHAUST;

typedef struct _ATTACK_STRUCTURE{
	double Strike;		// Damage variable.
    double TrueStrike;  // True strike of player.
	signed long Precision;	// Precision of blow variable.
	signed long lDodgeSkill;	// Attack skill of attacker
	signed long lAttackSkill;	// Dodge skill of defender
	//EXHAUST		exhaust;
} ATTACK_STRUCTURE, *LPATTACK_STRUCTURE;

typedef struct _BOOST{	
    DWORD dwBoostID;
	WORD wStat;
	BoostFormula bfBoost;
} BOOST, *LPBOOST;



#define STAT_INT			1
#define STAT_END			2
#define STAT_STR			3
#define STAT_WIS			4
#define STAT_LCK			5
#define STAT_AGI			6
#define STAT_ATTACK			8
#define STAT_DODGE			9
#define STAT_DAMAGE			10
#define STAT_RADIANCE       11
#define STAT_AIR_RESIST     12
#define STAT_FIRE_RESIST    13
#define STAT_WATER_RESIST   14
#define STAT_EARTH_RESIST   15
#define STAT_AIR_POWER      16
#define STAT_FIRE_POWER     17
#define STAT_WATER_POWER    18
#define STAT_EARTH_POWER    19
#define STAT_AC             20
#define STAT_LIGHT_RESIST   21
#define STAT_DARK_RESIST    22
#define STAT_LIGHT_POWER    23
#define STAT_DARK_POWER     24
#define STAT_MAX_HP         25
#define STAT_MAX_MANA       26

// This is the offset for skill boosts. SkillID + this offset = StatBoostID.
#define SKILL_BOOST_OFFSET  10000

// Status bits
#define CAN_TALK            0x01
#define IS_PLAYER           0x02

//////////////////////////////////////////////////////////////////////////////////////////
// This class provides the common structures for a message handler.
// A message handling function *must* include this class in order for it to
// have the ability to interpret different messages.
class EXPORT BaseReferenceMessages{
// Class unit will call those functions, but we don't want any non-derived class to use 
// them.
friend Unit;

protected:
#ifdef CHANGED_MESSAGES
#error "Change messages in BaseReferenceMessages.h, class header"
#endif	
	// The different message functions
	virtual void OnAttack( UNIT_FUNC_PROTOTYPE );
	virtual void OnAttacked( UNIT_FUNC_PROTOTYPE );
	virtual void OnDisturbed( UNIT_FUNC_PROTOTYPE );
	virtual void OnUse( UNIT_FUNC_PROTOTYPE );
	virtual void OnTimer( UNIT_FUNC_PROTOTYPE );
	virtual void OnInitialise( UNIT_FUNC_PROTOTYPE );
	virtual void OnTalk( UNIT_FUNC_PROTOTYPE );
	virtual void OnQuerySchedule( UNIT_FUNC_PROTOTYPE );
	virtual void OnView( UNIT_FUNC_PROTOTYPE );
	virtual void OnNoMoreShots( UNIT_FUNC_PROTOTYPE );
	virtual void OnMove( UNIT_FUNC_PROTOTYPE );
	virtual void OnDeath( UNIT_FUNC_PROTOTYPE );
	virtual void OnHit( UNIT_FUNC_PROTOTYPE );
    virtual void OnAttackHit( UNIT_FUNC_PROTOTYPE );
	virtual void OnEquip( UNIT_FUNC_PROTOTYPE );
	virtual void OnUnequip( UNIT_FUNC_PROTOTYPE );
	virtual void OnServerInitialisation( UNIT_FUNC_PROTOTYPE, WORD wBaseReferenceID );
	virtual void OnServerTermination( UNIT_FUNC_PROTOTYPE );
	virtual void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
	virtual void OnGetUnitStructure( UNIT_FUNC_PROTOTYPE );
	virtual void OnPopup( UNIT_FUNC_PROTOTYPE );
    virtual void OnDestroy( UNIT_FUNC_PROTOTYPE );

public:
	WORD wBindedReferenceID;
};

#define OBJECT_DISTURB_EQUIP		1
#define OBJECT_DISTURB_GET			2
#define OBJECT_DISTURB_DROP			3
#define OBJECT_DISTURB_USE			4
#define OBJECT_DISTURB_ROB			5

#define MARK_DELETION				0x01

// Changed from _PC constants due to clash with _PC defined in <tchar.h>
const BYTE U_PC		= 1;
const BYTE U_NPC	= 2;
const BYTE U_OBJECT	= 3;
const BYTE U_HIVE	= 4;
const BYTE U_EQUIP = 5;//BLBLBL to work with Conjure (equip) spell effect

#define U_PC_COLOR		RGB(0,255,0);
#define U_GOD_COLOR		RGB(255,255,255);//BLBLBL 255,255,255
#define U_NPC_COLOR		RGB(255,255,0);
#define U_OBJECT_COLOR	RGB(0,255,255);

// User skill structure, defines the user's skill power.
class USER_SKILL{
public:
    // The bodies are defined after the class Unit definition.

    SkillID GetSkillID(); // inline

    SkillPnt GetSkillPnts( Unit *lpUnit ); // inline

    SkillPnt GetTrueSkillPnts( void );// inline

    void SetSkillPnts( SkillPnt nPnt );// inline

    void SetSkillID( SkillID nID );// inline

private:
    SkillID  nSkillID;
    SkillPnt nSkillPnts;
};
typedef USER_SKILL * LPUSER_SKILL;


//////////////////////////////////////////////////////////////////////////////////////////
// This class handles units!
class EXPORT Unit : public DynamicFlags, public CLock
{	
public:	
	static void DUMPUnits();
    Unit( bool boDebugLock = false );

	static void InitializeMessagesProcs( void );
	static WORD RegisterUnitMessageHandler( WORD wBaseReferenceID, 
											BaseReferenceMessages *lpMessageUnit,
											LPCTSTR lpszName,
											BYTE bUnitType,
											BOOL boFindNextValidID,
                                            BOOL boForceRegistration = FALSE
										  );
	static void UnRegisterUnits( void ); // Encore une extra qualification d origine
    static void UnregisterUnit( WORD wBaseReferenceID );
	static Unit *GetByID(DWORD id);
	static void SendGlobalUnitMessage( UINT MessageID, Unit *self, Unit *medium, Unit *target, LPVOID valueIN = NULL, LPVOID valueOUT = NULL );

	static WORD GetIDFromName( CString csName, BYTE bUnitType = 0, BOOL boInsensitiveSearch = FALSE );
	static BOOL GetNameFromID( WORD wID, LPTSTR lpszNameHolder, BYTE bUnitType = 0 );

	void *GetPlayer(); //inline

	static void CleanCorpse( TIMERCALLBACK_PROTOTYPE );

	virtual BOOL Create(UINT UnitType, UINT BaseReferenceID);

	char GetType();//inline dehors				// Returns the type (U_PC, U_NPC or U_OBJECT) of the current unit.	
	
	virtual WorldPos GetWL();			// Gets the position of the current unit
	virtual void SetWL(WorldPos pos);	// Sets the position of the unit.

	// Dispatches a message to the static unit message handler.
	virtual BOOL SendUnitMessage(UINT MessageID, Unit *self, Unit *medium, Unit *target, void *INparameters = NULL, void *OUTparameters = NULL);

	virtual UINT GetStaticReference();	// Returns the BaseReferenceID

	virtual UINT GetAppearance();
	virtual void SetAppearance(UINT new_appearance);
	
	UINT GetID(); //inline dehors				// Gives the global ID of the unit
	void SetID(UINT ID);			// Sets (of necessary) the global ID of the unit // inline

	// Fighting functions
	virtual int attack  (LPATTACK_STRUCTURE strike, Unit *Target );
	virtual int attacked(LPATTACK_STRUCTURE strike, Unit *Mechant) = 0;
	virtual int hit     (LPATTACK_STRUCTURE strike, Unit *WhoHit);
	virtual int attack_hit(LPATTACK_STRUCTURE strike, Unit *Target);
	virtual void Death( LPATTACK_STRUCTURE lpBlow, Unit *WhoHit );

	virtual CString GetName( WORD wLang );
	virtual void SetName(CString newname);

	virtual void SetXP(int xp); //__int64
	virtual int GetXP(); //__int64
    virtual int NextLevelXP( void ){ return 0;}; //__int64
    virtual int XPtoLevel( void ){ return 0; }; //__int64


	virtual TemplateList <Unit> *GetBackpack();
	virtual void SetBackpack(TemplateList <Unit> *backpack);

	virtual TemplateList <Unit> *GetEquipped();
	virtual void SetEquipped(TemplateList <Unit> *equipped);

	virtual EXHAUST GetExhaust();
	virtual void SetExhaust(EXHAUST newExhaust);

    // Deals the exhaust.
    virtual void DealExhaust( DWORD dwAttack, DWORD dwMental, DWORD dwMove );
	
	virtual BYTE IsDoing();
	virtual void Do(BYTE behavior);

	virtual BYTE GetSpeed();
	virtual BYTE GetSpeedExhaust();
	virtual void SetSpeed(BYTE newSpeed);

	virtual WorldPos Destination();
	virtual void SetDestination(WorldPos where);

	virtual char GetAgressivness();
	virtual void SetAgressivness(char newAgressive);

	virtual WORD GetClan();
	virtual void SetClan(WORD newClan);

	virtual Unit *GetTarget();
	virtual void SetTarget(Unit *newTarget);

	virtual	WorldPos MoveUnit(DIR::MOVE where, BOOL boMoveAbsolute, bool boCompressMove, bool boBroadcastMove);

	virtual WORD GetCorpse();
	virtual void SetCorpse(WORD newCorpse);

	virtual UINT GetIdleTime();
	virtual void SetIdleTime(UINT newTime);

	virtual BOOL SystemDestroy();
	virtual void SetSystemDestroy(BOOL value);

	virtual DWORD GetMaxHP();
    virtual DWORD GetTrueMaxHP();
	virtual void  SetMaxHP(DWORD HP);

	virtual DWORD GetHP();
	virtual void  SetHP(DWORD HP, bool boUpdate );

	virtual WORD GetMaxMana();
    virtual WORD GetTrueMaxMana();
	virtual void  SetMaxMana(WORD Mana);

	virtual WORD GetMana();
	virtual void  SetMana(WORD Mana, BOOL boEcho = TRUE );
/* (SD 11/08/05) removing this old attribute that is useless
	virtual WORD GetFaith();
	virtual void  SetFaith(WORD sdf);

	virtual WORD GetMaxFaith();
	virtual void  SetMaxFaith(WORD dsf);
*/
	virtual int GetGold();
	virtual void SetGold(int amount, BOOL boEcho = TRUE );
	
	virtual BOOL Teleport(WorldPos where, BYTE TeleportVisualEffect);

	virtual void SetBond(Unit *bond);
	virtual Unit *GetBond();

	virtual BOOL IsInLimit(WorldPos wlPos);
	virtual void GotoLimit(); // Sets the destination to the 'limit' of the NPC

	virtual void SetUpperLimit(WorldPos wlPos);
	virtual void SetLowerLimit(WorldPos wlPos);
    virtual WorldPos GetUpperLimit( void ){ return wlUpperLimit; };
    virtual WorldPos GetLowerLimit( void ){ return wlLowerLimit; };

	virtual void TrainUnit();	
	virtual BOOL UseSkillPnts(BYTE bQuantity);
	virtual BOOL UseStatPnts(BYTE bQuantity);


	virtual WORD GetLevel();
	virtual void SetLevel( WORD dwLevel);

	virtual BYTE GetClass();
	
	virtual LPWORD GetClassPoints();

	virtual void SendPlayerMessage(TFCPacket &sending);

	virtual BOOL UseSkill(int nID, Unit *target, LPVOID lpValueOUT = NULL );

	virtual BOOL UseSkill(int nID, WorldPos wlTarget);

	virtual void Talk( LPCTSTR Message, DWORD dwColor = LIGHT_YELLOW, Unit *TalkTo = NULL );

	virtual void SetDetectRange( BYTE bNewRange );
	virtual BYTE GetDetectRange( void );

	virtual Unit *GetIndentItem( DWORD * lpdwIndentList );

	virtual double GetAC( void );

	virtual void PacketBackpack( TFCPacket &sending, bool gameop = false );

	virtual LPUSER_SKILL GetSkill( DWORD dwSkillID );
	virtual WORD GetSkillPoints( void );

	virtual void SetLastTeleport( WorldPos wlPOS );
	virtual WorldPos GetLastTeleport( void );

	inline WorldPos OriginalWorldPos( void );

	inline void AddEffect( LPUNIT_EFFECT lpSpellEffect );	
	inline void RemoveEffect( DWORD dwEffect );
    inline void DispellEffectWithFlag( DWORD flagId );
	inline LPUNIT_EFFECT GetEffect( DWORD dwEffect );
	inline TemplateList<UNIT_EFFECT>* GetAllEffects( void );
	inline void DestroyEffects( void );
	inline void QueryEffects( BYTE bMsgType, LPVOID lpMsgData, Unit *medium, Unit *target );
    inline void SendGlobalEffectMessage( BYTE bMsgType, LPVOID lpMsgData, Unit *medium, Unit *target );

	inline void VerifyTimers( void );

	inline signed char GetRadiance( void );
	inline void SetRadiance( signed char cNewRadiance );

	inline DIR::MOVE QueryDirection( WorldPos wlTargetPos );

	virtual BOOL UseSpellEnergy( WORD wMana );

	inline void SetMark( BYTE bMark );
	inline BYTE GetMark( void );

	void SetUndead( WORD wUndead );
	WORD GetUndead( void );

	inline void AddBoost( LPBOOST lpBoost );
	inline void AddBoost( DWORD dwBoostID, WORD wStat, const char *lpszFormula );
    inline void AddBoost( DWORD dwBoostID, WORD wStat, int nBoost );
    inline void RemoveBoostFromStat( WORD wStat );
	inline void RemoveBoost( DWORD dwBoostID );
	inline LPBOOST GetBoost( DWORD dwBoostID );
	inline void SetBoost( DWORD dwBoostID, WORD wStat, BoostFormula bfBoost );
    inline void SetBoost( DWORD dwBoostID, WORD wStat, int nBoost );
	int QueryBoost( WORD wStat );
	
	WORD GetINT( void );// inline
	WORD GetEND( void );// inline
	WORD GetSTR( void );// inline
	WORD GetAGI( void );// inline
	WORD GetWIS( void );// inline
	WORD GetATTACK( void );// inline
	WORD GetDODGE( void );// inline
	WORD GetLCK( void );// inline

	WORD GetTrueINT( void );// inline
	WORD GetTrueEND( void );// inline
	WORD GetTrueSTR( void );// inline
	WORD GetTrueAGI( void );// inline
	WORD GetTrueWIS( void );// inline
	WORD GetTrueATTACK( void );// inline
	WORD GetTrueDODGE( void );// inline
	WORD GetTrueLCK( void );// inline
	
	void SetINT( WORD bStat );// inline
	void SetEND( WORD bStat );// inline
	void SetSTR( WORD bStat );// inline
	void SetAGI( WORD bStat );// inline
	void SetWIS( WORD bStat );// inline
	void SetATTACK( WORD bStat );// inline
	void SetDODGE( WORD bStat );// inline
	void SetLCK( WORD bStat );// inline

	// asteryth pvp ranking
	inline int GetTotalDeathNumber( void );
	inline int GetTotalKillNumber( void );
	inline int GetCurrentDeathNumber( void );
	inline int GetCurrentKillNumber( void );
	inline int GetBestSerieMurder( void );
	inline int GetCurrentSerieMurder( void );
	inline int GetCurrentPvpPoint( void );
	
	inline void SetTotalDeathNumber( int bStat );
	inline void SetTotalKillNumber( int bStat );
	inline void SetCurrentDeathNumber( int bStat );
	inline void SetCurrentKillNumber( int bStat );
	inline void SetBestSerieMurder( int bStat );
	inline void SetCurrentSerieMurder( int bStat );
	inline void SetCurrentPvpPoint( int bStat );
	
	// asteryth guild
	inline int GetGuildID( void );
	inline void SetGuildID( int bStat );
	
	virtual BOOL CanAttack();
	virtual void SetAttack( BOOL boCanAttack );

	// Unit database storage functions. 
	inline BOOL SaveBoosts( TemplateList< SQL_REQUEST > *lptlRequests, DWORD dwBaseOwnerID );
	inline void LoadBoosts( cODBCMage &ODBCConnection, DWORD dwBaseOwnerID );

	inline BOOL SaveEffects( TemplateList< SQL_REQUEST > *lptlRequests, DWORD dwBaseOwnerID );
	inline void LoadEffects( cODBCMage &ODBCConnection, DWORD dwBaseOwnerID );
    // Starts the effects loaded in LoadEffects.
    void DeferredLoadEffects( void );

	inline BOOL SaveFlags( TemplateList< SQL_REQUEST > *lptlRequests, DWORD dwBaseOwnerID );
	inline void LoadFlags( cODBCMage &ODBCConnection, DWORD dwBaseOwnerID );

	void SetBlock( BYTE bBlock );
	BYTE GetBlock( void );

	void SetUnderBlock( BYTE bBlock );
	BYTE GetUnderBlock( void );

	virtual BOOL CanMove( void );
	virtual void SetCanMove( BOOL boCanMove );

    virtual WORD GetLang( void );

    void SetStatus( BYTE bStatus );
    BYTE GetStatus( void );

    virtual int GetWeight( void );
    virtual int GetMaxWeight( void );

    virtual void SetPrivateTalk( BOOL boPrivate );
    virtual BOOL IsPrivateTalk( void );

    virtual void SendPrivateMessage( CString &csMessage, Unit *lpuUnit, DWORD dwColor = LIGHT_YELLOW );

    virtual void PacketUnitInformation( TFCPacket &sending );

    void SendSystemMessage( CString csText, DWORD dwColor = 0x0A64E0/*RGB( 0, 100, 255 )*/ ){
        const INT RQ_ServerMessage = 63; // steph ajout de INT
        TFCPacket sending;
		sending << (RQ_SIZE)RQ_ServerMessage;
		sending << (short)30;
		sending << (short)3;        
		sending << (CString &)csText;
		sending << (long) dwColor;
		SendPlayerMessage( sending );
    }

	void SendInfoMessage( CString csText, DWORD color = 0x0A64E0/*0xFF6400*/, DWORD type = 0 ){
		// 0xFF6400 => RGB(0,100,255) => default sysmsg color (blue)
        const INT RQ_InfoMessage = 102; // steph ajout de INT
        TFCPacket sending;
		sending << (RQ_SIZE)RQ_InfoMessage;
		sending << (long)type;
		sending << (long)color;
		sending << (CString &)csText;
		SendPlayerMessage( sending );
    }

    virtual BYTE GetGender( void ){ return bGender; };
    virtual void SetGender( BYTE bByte ){ bGender = bByte; };

    virtual int  GetKarma( void ){ return nKarma; };
    virtual void SetKarma( int nInt );

    // Elemental resistance variables. Uses the flags interface.
    int  GetAirResist  ( void ){ return ViewFlag( __FLAG_AIR_RESIST )   + QueryBoost( STAT_AIR_RESIST )   + 100; };
    int  GetWaterResist( void ){ return ViewFlag( __FLAG_WATER_RESIST ) + QueryBoost( STAT_WATER_RESIST ) + 100; };
    int  GetFireResist ( void ){ return ViewFlag( __FLAG_FIRE_RESIST )  + QueryBoost( STAT_FIRE_RESIST )  + 100; };
    int  GetEarthResist( void ){ return ViewFlag( __FLAG_EARTH_RESIST ) + QueryBoost( STAT_EARTH_RESIST ) + 100; };
    int  GetLightResist( void ){ return ViewFlag( __FLAG_LIGHT_RESIST ) + QueryBoost( STAT_LIGHT_RESIST ) + 100; };
    int  GetDarkResist ( void ){ return ViewFlag( __FLAG_DARK_RESIST ) + QueryBoost( STAT_DARK_RESIST )   + 100; };

    // Get unboosted elemental resistances.
    int  GetTrueAirResist  ( void ){ return ViewFlag( __FLAG_AIR_RESIST )   + 100; };
    int  GetTrueWaterResist( void ){ return ViewFlag( __FLAG_WATER_RESIST ) + 100; };
    int  GetTrueFireResist ( void ){ return ViewFlag( __FLAG_FIRE_RESIST )  + 100; };
    int  GetTrueEarthResist( void ){ return ViewFlag( __FLAG_EARTH_RESIST ) + 100; };
    int  GetTrueLightResist( void ){ return ViewFlag( __FLAG_LIGHT_RESIST ) + 100; };
    int  GetTrueDarkResist ( void ){ return ViewFlag( __FLAG_DARK_RESIST )  + 100; };
    
    // Set elemental resistance.
    void SetAirResist  ( int nValue ){ SetFlag( __FLAG_AIR_RESIST,   nValue - 100 ); };
    void SetWaterResist( int nValue ){ SetFlag( __FLAG_WATER_RESIST, nValue - 100 ); };
    void SetFireResist ( int nValue ){ SetFlag( __FLAG_FIRE_RESIST,  nValue - 100 ); };
    void SetEarthResist( int nValue ){ SetFlag( __FLAG_EARTH_RESIST, nValue - 100 ); };
    void SetLightResist( int nValue ){ SetFlag( __FLAG_LIGHT_RESIST, nValue - 100 ); };
    void SetDarkResist ( int nValue ){ SetFlag( __FLAG_DARK_RESIST,  nValue - 100 ); };

    // Elemental power variables. Uses the flags interface.
    int  GetAirPower  ( void ){ return ViewFlag( __FLAG_AIR_POWER )   + QueryBoost( STAT_AIR_POWER )   + 100; };
    int  GetWaterPower( void ){ return ViewFlag( __FLAG_WATER_POWER ) + QueryBoost( STAT_WATER_POWER ) + 100; };
    int  GetFirePower ( void ){ return ViewFlag( __FLAG_FIRE_POWER )  + QueryBoost( STAT_FIRE_POWER )  + 100; };
    int  GetEarthPower( void ){ return ViewFlag( __FLAG_EARTH_POWER ) + QueryBoost( STAT_EARTH_POWER ) + 100; };
    int  GetLightPower( void ){ return ViewFlag( __FLAG_LIGHT_POWER ) + QueryBoost( STAT_LIGHT_POWER )  + 100; };
    int  GetDarkPower ( void ){ return ViewFlag( __FLAG_DARK_POWER )  + QueryBoost( STAT_DARK_POWER ) + 100; };

    // Get unboosted elemental power.
    int  GetTrueAirPower  ( void ){ return ViewFlag( __FLAG_AIR_POWER )   + 100; };
    int  GetTrueWaterPower( void ){ return ViewFlag( __FLAG_WATER_POWER ) + 100; };
    int  GetTrueFirePower ( void ){ return ViewFlag( __FLAG_FIRE_POWER )  + 100; };
    int  GetTrueEarthPower( void ){ return ViewFlag( __FLAG_EARTH_POWER ) + 100; };
    int  GetTrueLightPower( void ){ return ViewFlag( __FLAG_LIGHT_POWER ) + 100; };
    int  GetTrueDarkPower ( void ){ return ViewFlag( __FLAG_DARK_POWER )  + 100; };
    
    // Set elemental power.
    void SetAirPower  ( int nValue ){ SetFlag( __FLAG_AIR_POWER,   nValue - 100 ); };
    void SetWaterPower( int nValue ){ SetFlag( __FLAG_WATER_POWER, nValue - 100 ); };
    void SetFirePower ( int nValue ){ SetFlag( __FLAG_FIRE_POWER,  nValue - 100 ); };
    void SetEarthPower( int nValue ){ SetFlag( __FLAG_EARTH_POWER, nValue - 100 ); };
    void SetLightPower( int nValue ){ SetFlag( __FLAG_LIGHT_POWER, nValue - 100 ); };
    void SetDarkPower ( int nValue ){ SetFlag( __FLAG_DARK_POWER,  nValue - 100 ); };

    virtual void PacketPuppetInfo( TFCPacket &sending );

    bool IsPuppet( void ){ return IsPuppetID( GetAppearance() ); };
    static bool IsPuppetID( WORD wAppearanceID ){
        return wAppearanceID == 10011 || wAppearanceID == 10012;
    }

    void PacketOutline( TFCPacket &sending ){
        sending << (long)GetID();
        sending << (char)(GetMaxHP() == 0 ? 0 : GetHP() * 100 / GetMaxHP());
    };

    void BroadcastPopup( WorldPos wlAppearPos, int nBroadcastPopup = true );
    void PacketPopup( WorldPos wlAppearPos, TFCPacket &sending );

    virtual bool DeleteUnit( void );
    virtual void CreateVirtualUnit();
        
    bool IsDead( void ){ return boDead; };
    void ResetDeath( void ){ boDead= false; };

    bool IsVisible( void ){ return !boInvisible; };
    void SetVisibility( bool boVisible ){ boInvisible = !boVisible; };

    // Total annihilation of unit, what does it do? 
    virtual void VaporizeUnit( void ) = 0;

    void KillCreature( void ){ boDead = true; };

    bool LastMoveWasBroadcasted( void ){
        return boBroadcast;
    }    

    class QueryInvisible : public SendPacketVisitor{
    public:
        void SetUnit( Unit *ich );
        virtual bool SendPacketTo( Unit *target );
    protected:
        Unit *GetUnit(){ return unit; };
    private:
        Unit *unit;
    };

    virtual QueryInvisible *GetInvisibleQuery(){
        return &queryInvisible;
    }

    virtual void Unhide();
    virtual void DispellInvisibility();

    virtual void RemoveReferenceTo( Unit *theUnit );

	void  SetUserSpeed( short sVal ) { userSpeed = sVal; }
	short GetUserSpeed( void ) { return userSpeed; }

	BOOL bRainState;//BLBLBL 08/12/2010 ajout des variables pour gestion météo
	BOOL bSnowState;
	BOOL bFogState;

protected:
     QueryInvisible queryInvisible;

	BYTE nClass; // class of the unit
    virtual ~Unit() = 0; // pure base class.    
//    virtual ~Unit();   
    
    //void operator delete( void *lpVoid ){};

    bool boBroadcast;
private:
    bool  boInvisible;

    DWORD dwRefCount;

	short userSpeed;

	// This structure saves the names of all units
	struct UNIT_TYPE{
		CString csName;
		BYTE bUnitType;
		WORD wBaseReferenceID;
	};

	// The player's stat.
	WORD StatINT;
	WORD StatEND;
	WORD StatSTR;
	WORD StatAGI;
	WORD StatWIL;
	WORD StatWIS;
	WORD StatLCK;	
	WORD StatDODGE;
	WORD StatATTACK;
	
	// asteryth pvp ranking
	int TotalDeathNumber;
	int TotalKillNumber;
	int CurrentDeathNumber;
	int CurrentKillNumber;
	int BestSerieMurder;
	int CurrentSerieMurder;
	int CurrentPvpPoint;

	// asteryth guild
	int GuildID;

	static UINT CurrentGlobalID;
	//static TemplateList <UINT> UsedIDs;    
	
	static std::map<DWORD,Unit *> unit_map;

	// This table points to all the messages procedures.
	static BaseReferenceMessages *lpMessagesProc[ 65536 ];
	// This list holds all the global unit specifications
	static TemplateList <UNIT_TYPE> tlUnitTypes;

	BYTE bMarker;    

protected:
	BYTE UnitType;					// Type of unit (U_PC, U_NPC or U_OBJECT)
	UINT BaseReferenceID;			// Reference to 'static' unit encapsulated in the message DLL
	UINT GlobalID;					// Global unit ID
	WORD Appearance;				// Icon that will be shown to the user.

    BYTE bGender;
    int  nKarma;

    WORD Corpse;					// Icon of corpse to show after death.    

    DWORD loadMentalExhaust;
    DWORD loadMoveExhaust;
    DWORD loadAttackExhaust;

private:
    struct LOAD_EFFECT_DATA{
	    DWORD effectId;
	    WORD  effectType;
	    DWORD effectTimer;
        DWORD totalDuration;
        DWORD bindedSpellId;
	    CString effectData;
        DWORD bindedFlagId;
    };
    struct LOAD_BOOST_DATA{
        DWORD dwBoostID;
        WORD  wStat;
        CString boostFormula;
    };
    std::list< LOAD_EFFECT_DATA > deferredEffectLoad;
    std::list< LOAD_BOOST_DATA > deferredBoostLoad;

    // Prohibit assignements for units.
    INT PROHIBIT_ASSIGNEMENT( Unit& ); // steph ajout de INT // ne peut déclarer le parametre comme etant de type abstrait unit -> ajout de réf
	
    BYTE bStatus;                   // General status of unit.
	BYTE doing;						// Sets what the creature is doing now
	BYTE speed;						// Sets the speed (moves per 200 rounds) (10 game minutes)

	signed char cRadiance;					// The radiance level of the item.
    bool boDead;

	Unit *Bond;

//	CString  Name;					// String defining the name of the unit
	WorldPos WL;					// World position of the unit
	WorldPos wlOriginalPos;			// Original world position of unit.

	WorldPos wlUpperLimit;
	WorldPos wlLowerLimit;

	Unit *Target;					// Target

	char ToBeKilled;				// Indicates this unit should be killed after
									// a certain time being time.
	WORD wLevel;	

	BYTE bBlock;					// Block casted by the unit.
	BYTE bCurrentBlocking;			// Blocking under the unit.

	TemplateList <UNIT_EFFECT> *lptlEffectList;
	TemplateList <BOOST>		*lptlBoostList;

    DWORD messageStackLevel;
    DWORD effectStackLevel;

};

SkillID USER_SKILL::GetSkillID(){
    return nSkillID;
}

SkillPnt USER_SKILL::GetSkillPnts( Unit *lpUnit ){
    int boost = lpUnit->QueryBoost( SKILL_BOOST_OFFSET + nSkillID ) * -1;
	if ( boost > nSkillPnts ){
		return nSkillPnts = 0;
	}
	else{
		return nSkillPnts - boost;
	}
}

SkillPnt USER_SKILL::GetTrueSkillPnts( void ){
    return nSkillPnts;
}

void USER_SKILL::SetSkillPnts( SkillPnt nPnt ){
    nSkillPnts = nPnt;
}

void USER_SKILL::SetSkillID( SkillID nID ){
    nSkillID = nID;
}


#endif // !defined(AFX_UNIT_H__7F4A9E93_0C24_11D1_BCD5_00E029058623__INCLUDED_)

