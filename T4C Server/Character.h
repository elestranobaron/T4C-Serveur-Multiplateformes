// Character.h: interface for the Character class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARACTER_H__6EB985F4_D137_11D0_B543_C09D9B000000__INCLUDED_)
#define AFX_CHARACTER_H__6EB985F4_D137_11D0_B543_C09D9B000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define NB_CLASS	4

#define MAX_LEVEL 199

#define ANY_CLASS	-1
#define WARRIOR		0
#define MAGE		1
#define PRIEST		2 
#define THIEF		3
#define EQUIP_POSITIONS	16

#define GENDER_MALE         0
#define GENDER_FEMALE       1

#define DISTURB_CLOSECHEST	0x01
#define DISTURB_CLOSETRADE	0x02
#define DISTURB_UNHIDE		0x04
#define DISTURB_DONTCANCELROB 0x08

#include "Objects.h"
#include "SharedStructures.h"
#include "TFCPacket.h"
#include "Directions.h"
#include "Unit.h"
#include "Skills.h"
#include "StaticFlags.h"
#include "_item.h"
#include "Group.h"
#include <map>
#include <vector>
#include <list>
#include "SendPacketVisitor.h"
#include "ItemContainer.h"
#include "Trade.h"

//#include "Guilds.h"

// A visitor used by some packet sending functions to query wether the packet
// can be sent to the player or not.
class Players;
class AutoArrowRemove;
class EXPORT Character : public Unit
{
public:
	Character();	

	enum BodyPos
	{
		body		 = 0,// puppet
		feet		 = 1,// puppet
		gloves		 = 2,// puppet
		helm		 = 3,// puppet
		legs		 = 4,// puppet
		rings		 = 5,
		bracelets    = 6,
		necklace	 = 7,
		weapon_right = 8,// puppet
		weapon_left  = 9,// puppet
		two_hands    = 10,
		ring1        = 11,
		ring2        = 12,
		weapon       = 13,
		belt		 = 14,
		cape		 = 15,// puppet, used to be sleeves.
	};

	class ErrorCodes {
	public:
		enum TakeFromBackpack {
			ObjectTakenFromBackpack,
			ObjectCantBeDropped,
			ObjectNotFoundOnBackpack
		};
	};

	BOOL roll_stats();
	
	static void InitializeODBC( void );
	static void DestroyODBC( void );
    
    void	  SetPlayer( Players *Player);
    char      load_character(CString name, CString account, LPBYTE lpbAnswers );
	char      DeleteCharacter(CString name, CString account, BOOL Report = TRUE);
	char	  PutPlayerInGame( );

	static bool IsNameValid( CString &name );
	
	//	WorldPos  MoveUnit(DIR::MOVE where);
	WorldPos  teleport_character(WorldPos where);	
	
    void      GetUnit( WorldPos originalPos, Unit *obj );
	Unit *    DropUnit( WorldPos where, DWORD itemID, DWORD qty );

    void JunkItems( DWORD id, DWORD qty, bool gameop );


	ItemContainer* GetChest();
	void SetChest(ItemContainer *newChest);
	void MoveObjectFromBackpackToChest2( DWORD dwObjectID, DWORD dwQty );
	void MoveObjectFromChestToBackpack2( DWORD dwObjectID, DWORD dwQty );
	void ShowChest( void ); // Asks the client to show the chest interface
	void StopUsingChest( void );
	void SendChestContentPacket(void); //Send the character the chest packet! :)

	inline TradeMgr2* GetTradeMgr2(); // Returns a pointer to the trade manager;
	void TradeRequest(Character *invitedCharacter); // Invites or accept a trade
	void TradeCancel(); // Cancels the trade or invite
	void TradeFinish(); // Finish the trade
	void TradeSetStatus(TradeMgr2::Status::CharacterStatus newStatus); // Changes the status of the character within the trade
	void TradeAddItemFromBackpack(DWORD itemID, DWORD itemQty); // Add an item from the backpack to the trade
	void TradeRemoveItemToBackpack(DWORD itemID, DWORD itemQty); // Removes an item from the trade to the backpack
	void TradeClearItemsFromTrade(); // Removes all items from the trade back to the backpack

	unsigned long god_create_object(unsigned short which_item);

	char equip_object(unsigned long item_nb);
	char unequip_object(unsigned char from_where, bool remove = false );
	
	BOOL QueryEquip( Unit *lpuEquip, BYTE bItemType, BYTE bEquipPos, _item *item );

	void packet_equiped(TFCPacket &packet, bool gameop = false);
	void packet_stats(TFCPacket &packet, bool gameop = false);
	void PacketSkills( TFCPacket &packet, bool gameop = false );
	void PacketSpells( TFCPacket &packet, BYTE bUpdate, bool gameop = false );
	void PacketStatus( TFCPacket &packet, bool gameop = false );
	// asteryth pvp ranking
	void PacketPvpRanking( TFCPacket &packet, bool gameop = false );

	BOOL      can_get(WorldPos where, Objects *obj);	

	unsigned short memorized_spell[9];
	char memorize_spell(unsigned char where, unsigned short which_spell, unsigned long itemID);

	void use_item(unsigned long itemID, Unit *TargetPlayer);

	int attack(LPATTACK_STRUCTURE strike,   Unit *Target);
	int attacked(LPATTACK_STRUCTURE strike, Unit *Mechant);
	int hit(LPATTACK_STRUCTURE strike, Unit *WhoHit);
	int attack_hit(LPATTACK_STRUCTURE s_asBlow, Unit *lpuTarget);
	void Death( LPATTACK_STRUCTURE lpBlow, Unit *lpKiller );

	int GetGold();
	void SetGold(int newGold, BOOL boEcho = TRUE );
	
//	void save_character();
	void reset_character();

	WORD GetCorpse();
	BOOL Kill();
	
//	UINT GetAppearance();

	void SetXP(int XP); //__int64
	int GetXP(); //__int64

	TemplateList <Unit> *GetBackpack();
	void SetBackpack(TemplateList <Unit> *list);

	WorldPos MoveUnit(DIR::MOVE where, BOOL boAbsolute, bool boCompressMove, bool boBroadcastMove );

	WORD GetClan();
	void SetClan(WORD newClan);

	DWORD GetTrueMaxHP();
	void  SetMaxHP(DWORD newMax);

	DWORD GetHP();
	void  SetHP(DWORD newMax, bool boUpdate );

	WORD  GetTrueMaxMana();
	void  SetMaxMana(WORD newMax);
	
	WORD GetMana();
	void SetMana(WORD newMax, BOOL boEcho = TRUE );

	/* BEGIN : Mestoph -> Removed skill pray for not used in the server
	WORD GetFaith();
	void  SetFaith(WORD Faith);

	WORD GetMaxFaith();
	void  SetMaxFaith(WORD Faith);
	END : Mestoph -> Removed skill pray for not used in the server */

	EXHAUST GetExhaust();
	void SetExhaust(EXHAUST newExhaust);

	void	SetName(CString name);
	CString GetName( WORD wLang );
	CString GetName();
    void    SetPseudoName( CString csName );
    CString GetTrueName( void );

	BOOL SaveCharacter( BOOL boCallback = TRUE );
	int LoadCharacter(CString csName);

	Unit **GetEquipment( void );		

	void TrainUnit();

	Players *GetPlayer();
	inline unsigned int GetGodFlags(); //__int64


	BOOL UseSkillPnts( WORD bQuantity );
	BOOL UseStatPnts( BYTE bQuantity );

	BOOL TrainSkillPnt( int nID, int nQuantity, WORD wMax );

	static void InitXPchart();

	BOOL SendUnitMessage( UINT MessageID, Unit *self, Unit *medium, Unit *target, void *INparameters, void *OUTparameters );

	//LPWORD GetClassPoints();

	void SendPlayerMessage( TFCPacket &sending );

	inline BOOL UseSkill( int nID, Unit *uTarget, LPVOID lpValueOUT );
	inline BOOL UseSkill( int nID, WorldPos wlPos );

	inline BOOL CastSpell( WORD wSpellID, Unit *uTarget );
   inline BOOL CastSpellDirect( WORD wSpellID, Unit *uTarget );
	inline BOOL CastSpell( WORD wSpellID, WorldPos wlPos );

	inline BOOL UseSpellEnergy( WORD wEnergy );

	void Regenerate( void );

    LPUSER_SKILL LearnSkill( DWORD dwSkill, WORD wInitialStrength, bool boEcho, CString &errMsg );

	LPUSER_SKILL GetSkill(DWORD dwSkill);

	TemplateList<USER_SKILL> *GetSkillLists( void );
	TemplateList<USER_SKILL> *GetSpells( void );

	static int sm_n64XPchart[MAX_LEVEL]; //__int64

	WORD GetSkillPoints();
	WORD GetStatPoints();
    void SetStatPoints( WORD w ){
        wNbStatPnts = w;
    }

	void GiveSkillPoints( WORD wQuantity );

	double GetAC( void );
    double GetTrueAC( void );

	inline char GetAgressivness( void );
	inline void SetAgressivness( char cAgr );

	BOOL CanAttack( void );

	inline void WaitForSaving( void );

    BOOL CanEquip( Unit *lpuUnit, _item *lpProvidedItem = NULL, BOOL boEcho = TRUE, CString *reqText = NULL );

    inline WORD GetLang( void ) const;

    int  GetWeight( void );
    int  GetMaxWeight( void );
	int  GetFreeWeight( void );

    void SendPrivateMessage( CString &csMessage, Unit *lpuUnit, DWORD dwColor );

    int NextLevelXP( void ); //__int64
    int PreviousLevelXP( void ); //__int64
    int XPtoLevel( void ); //__int64

    void PacketPuppetInfo( TFCPacket &sending );

    void Disturbed( WORD pTriggers = 0 ); //Called when the unit gets disturbed. Parameter are which triggers will be triggered by the call

    bool PreTranslateInGameMessage( CString csText );

    static cODBCMage *GetODBC();

    bool UseItemByAppearance( WORD wAppearance, Unit *TargetPlayer );

    // Sets a character's group.    
    void SetGroup( Group *lpGroup );

    // Gets a character's group.
    Group *GetGroup( void );

    void VaporizeUnit( void );

    CString GetTitle( bool getAccountName );
    void    SetTitle( CString csNewTitle ){ csListingTitle = csNewTitle; csListingTitle.Remove('\''); };
	
	

	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout
	//////////////////////////////////////////////////////////////////////////////////////////
	CString GetGuild(bool getAccountName);
	void    SetGuild(CString csNewGuild) { csGuildName = csNewGuild; csGuildName.Remove('\''); };




	//BLBLBL GetGuildName/SetGuildName functions
	CString GetGuildName( void );
	void    SetGuildName( CString csNewGuildName );

	// asteryth guild
	void	SetGuildChestAccess(int newGuildChestAccess);
	int		GetGuildChestAccess();


    CString GetListingMiscDesc( void )             { return csListingMisc; };
    void    SetListingMiscDesc( CString csNewMisc ){ csListingMisc = csNewMisc; csListingMisc.Remove('\''); };
    
	// Guild stuff
	int		GetGuildPoints() const { return GuildPoints; };
	void	SetGuildPoints( int NewGuildPoints ) { GuildPoints = NewGuildPoints; };

	unsigned char GetGuildRank() const { return GuildRank; };
	void	SetGuildRank( unsigned char NewGuildRank ) { GuildRank = NewGuildRank; };

	//Guilds *GetGuild() const { return GuildRef; }
	//void	SetGuild(Guilds *NewGuild) { GuildRef = NewGuild; }

    void    CopySpells( Unit *lpSource );

    //void    MergeGold( void );

    struct Attack{
        friend Character;
        enum AttackType{ spell, normal, range };

        Attack( AttackType newAttackType, DWORD newSpellID ) :
            attackType( newAttackType ), spellID( newSpellID )
        {}
    private:
        AttackType attackType;        
        DWORD spellID;
    };

    void    StartAutoCombat( Attack attack, Unit *target );
    void    StopAutoCombat();
    bool    QueryAutoCombatState( Attack *attack = NULL );
    bool    ExecAutoCombat( void );
    void    RestorePreviousAutoCombatState();

    void    SetGameOpContext( Character *newContext ){
        gameopContext = newContext;
    }

    Character *GetGameOpContext( void ){
        return gameopContext;
    }

    
    void PacketBackpack( TFCPacket &sending, bool gameop = false );
    void PacketRobBackpack( Unit *robber, TFCPacket &sending );
	void SendBackpackContentPacket(); // Send to client an updated list of backpack's contents

    void AddToBackpack( Objects *obj );
	ErrorCodes::TakeFromBackpack TakeFromBackpack( DWORD itemID, DWORD itemQty, Objects *returnedObj, BOOL ignoreCannotDropFlag = false );
    
    virtual void SetLevel( WORD wLevel );

    void Rob( DWORD objId );

    bool RangedAttack();    

    DWORD EquipCount( WORD itemId );

    void ClearAllSkillsAndSpells();

    void BroadcastSeraphArrival();

    void TraceExhaust();

    bool CanInvite();

    virtual void RemoveReferenceTo( Unit *theUnit );

/* BEGIN : Remove BL Anti SpeedHack
	void CheckSpeedHack( WorldPos newPos );
END : Remove BL Anti SpeedHack */

	bool AnalyseActionWorld( char *pTxt );

	bool boAuthGM;

	// BEGIN : Black Lemming -> Antiplug system
	unsigned long lLastEventTime; //Usefull to know if player kept untouched for 15 seconds
	bool boClientExitCountDown;
	//END : Black Lemming -> Antiplug system
	
    //BEGIN : Black Lemming -> GM COMMAND : SENDBACK $ (to put player where he was before last teleport command)
	WorldPos	prevTeleportPos;
	//END : Black Lemming -> GM COMMAND : SENDBACK $ (to put player where he was before last teleport command)
	BOOL boLoaded;//BLBLBL passé en variable publique

	//BLBLBL : Ajout d'une variable pour mémoriser le fait qu'un personnage est en cours de sauvegarde
	BOOL boSavingOnProgress;
	//END : BLBLBL
private:
	WorldPos	initPos;
	WorldPos	prevPos;
	DWORD		initTime;

    DWORD lastInviteTime;

    virtual ~Character();

    void RangeAttack( Unit *target );
    static void AutoConfigUpdate( void );

    BOOL CreateCharacter(CString csName, LPBYTE lpbAnswers );

    //inline Unit *FindSmallestGoldStack( void );
    void SynchronizeGold( void );
    //bool SeparateGold( DWORD dwStackID, DWORD dwGoldAmount );

    inline void DestroyEquipment( void );

    WORD wLang;

    static void DataSaveCallback( DWORD dwSaveResult, LPVOID lpData );
    
    inline void SavingStart( void );
    inline void SavingStop( void );	
    BYTE numberOfSaveFailures; // Counts how many sucessive times it failed to save player.
    
    HANDLE hCreationEvent;
    mrevent mrev;
    
    inline void PacketSingleEquip( BYTE equip_pos, TFCPacket &sending );
    
    Group *lpGroup;
    
    Character *gameopContext;
    
    signed char cAgressive;
    
    int nCurrentWeight;
    
    WORD clan;
    
    DWORD MaxHP;
    DWORD HP;
    
    WORD MaxMana;
    WORD Mana;
    
    /* BEGIN : Mestoph -> Removed skill pray for not used in the server
	WORD MaxFaith;
    WORD Faith;
    BEGIN : Mestoph -> Removed skill pray for not used in the server */

    //BOOL boLoaded; //BLBL passage en public
    
    unsigned int xp; //__int64
    
    CString account;
    
    CString PlayerName;
    CString csPseudoName;
    
    // Title and extra information for user listing.
    CString csListingTitle;
    CString csListingMisc;
	CString csGuildName;//BLBLBL csGuildName
	int GuildChestAccess;
    
    // Guild ref, rank, points
    //Guilds *GuildRef;
    unsigned char GuildRank;
    int GuildPoints;
    
    BOOL KillMe;
    BOOL _died_;
    bool seraphAlreadyArrived;
    
    
    
    Players *ThisPlayer;
    
    EXHAUST exhaust;
    
    std::map< SkillID, SkillPnt > mSkillBoosts;
    

	int gold;

//	void CharacterIO(BOOL boSave);
	//WORD race;

	TemplateList <Unit> *backpack;	
	Unit *equipped[ EQUIP_POSITIONS ];

	ItemContainer *chest; // The chest :D
	BOOL boCharacterIsChesting; // Defines that the character is allowed to chest
	
	TradeMgr2 m_TradeMgr2; // The trade manager object

	//WORD ClassPoints[NB_CLASS];
	WORD wNbSkillPnts;
	WORD wNbStatPnts;

	TemplateList <USER_SKILL> tlusSkills[NB_SKILL_HOOKS];
	TemplateList <USER_SKILL> tlusSpells;	// All the spells.

	static BYTE m_bSkillPnt[ (MAX_LEVEL / 10) + 1 ];

    // Auto-combat
    bool autoCombatState;
    Attack autoCombatAttack;
    Attack prevAutoCombatAttack;
    bool   prevAutoCombatState;
    Unit  *prevTarget;


    friend AutoArrowRemove; 

    DWORD
        bRollSTR : 4,
        bRollEND : 4,
        bRollINT : 4,
        bRollAGI : 4;	
    DWORD
        bRollWIL : 4,
        bRollWIS : 4,
        bRollLCK : 4;        
};

#endif // !defined(AFX_CHARACTER_H__6EB985F4_D137_11D0_B543_C09D9B000000__INCLUDED_)
