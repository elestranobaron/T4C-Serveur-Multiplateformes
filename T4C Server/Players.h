// Players.h: interface for the Players class.
//
// This file handles players, will probably hold structures
// for the "player flags" ie: quest flags.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYERS_H__C2AF9A46_AC25_11D0_9B9E_444553540000__INCLUDED_)
#define AFX_PLAYERS_H__C2AF9A46_AC25_11D0_9B9E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Character.h"
#include "Objects.h"
#include "Lock.h"
//#include "WINSOCK.H"
#include <netinet/in.h>
#include <list>

#define MAX_CHATTERS	5

struct CStringAndRace{
	CString name;
	WORD level;
	WORD race;
};

struct ChatterChannel{
	CString Pwd;
	DWORD   ID;
};


//////////////////////////////////////////////////////////////////////////////////////////
// Defines the different god flags.
#define GOD_NO_CLIP								0x0000000000000001 //   0
#define GOD_NO_MONSTERS							0x0000000000000002 //   1
#define GOD_CAN_TELEPORT						0x0000000000000004 //   2
#define GOD_CAN_TELEPORT_USER					0x0000000000000008 //   3
#define GOD_CAN_ZAP								0x0000000000000010 //   4
#define GOD_CAN_SQUELCH							0x0000000000000020 //   5
#define GOD_CAN_REMOVE_SHOUTS					0x0000000000000040 //   6
#define GOD_CAN_SUMMON_MONSTERS					0x0000000000000080 //   7
#define GOD_CAN_SUMMON_ITEMS					0x0000000000000100 //   8
#define GOD_CAN_SET_USER_FLAG					0x0000000000000200 //   9 
#define GOD_CAN_EDIT_USER						0x0000000000000400 //   10
#define GOD_CAN_EDIT_USER_STAT					0x0000000000000800 //   11
#define GOD_CAN_EDIT_USER_HP					0x0000000000001000 //   12
#define GOD_CAN_EDIT_USER_MANA_FAITH			0x0000000000002000 //   13
#define GOD_CAN_EDIT_USER_XP_LEVEL				0x0000000000004000 //   14
#define GOD_CAN_EDIT_USER_NAME					0x0000000000008000 //   15
#define GOD_CAN_EDIT_USER_APPEARANCE_CORPSE		0x0000000000010000 //   16
#define GOD_CAN_EDIT_USER_SPELLS				0x0000000000020000 //   17
#define GOD_CAN_EDIT_USER_SKILLS				0x0000000000040000 //   18
#define GOD_CAN_EDIT_USER_BACKPACK				0x0000000000080000 //   19
#define GOD_CAN_VIEW_USER						0x0000000000100000 //   20
#define GOD_CAN_VIEW_USER_STAT					0x0000000000200000 //   21
#define GOD_CAN_VIEW_USER_BACKPACK				0x0000000000400000 //   22
#define GOD_CAN_VIEW_USER_SPELLS				0x0000000000800000 //   23
#define GOD_CAN_VIEW_USER_SKILLS				0x0000000001000000 //   24
#define GOD_CAN_VIEW_USER_APPEARANCE_CORPSE		0x0000000002000000 //   25
#define GOD_CAN_LOCKOUT_USER					0x0000000004000000 //   26
#define GOD_CAN_SLAY_USER						0x0000000008000000 //   27
#define GOD_CAN_COPY_USER						0x0000000010000000 //   28
#define GOD_CAN_EMULATE_MONSTER					0x0000000020000000 //   29
#define GOD_INVINCIBLE							0x0000000040000000 //   30
#define GOD_DEVELOPPER							0x0000000080000000 //   31
#define GOD_CAN_SHUTDOWN                        0x0000000100000000 //   32
#define GOD_CAN_SEE_ACCOUNTS                    0x0000000200000000 //   33
#define GOD_CAN_GIVE_GOD_FLAGS                  0x0000000400000000 //   34
#define GOD_UNLIMITED_SHOUTS                    0x0000000800000000 //   35
#define GOD_TRUE_INVISIBILITY                   0x0000001000000000 //   36
#define GOD_CAN_EMULATE_SYSTEM                  0x0000002000000000 //   37
#define GOD_CHAT_MASTER                         0x0000004000000000 //   38
#define GOD_CANNOT_DIE                          0x0000008000000000 //   39
#define GOD_CAN_RUN_CLIENT_SCRIPTS              0x0000010000000000 //   40
#define GOD_BOOST_XP                            0x0000020000000000 //   41
#define GOD_MODERATOR_GUARDIAN                  0x0000040000000000 //   42
#define GOD_ROYAL_GUARD_CHIEF                   0x0000080000000000 //   43

#define UPDATE_GOD_CAN_RUN_CLIENT_SCRIPTS   1
#define UPDATE_GOD_CAN_SLAY_USER            2

class EXPORT Players : public CLock
{
public:
	Players();
	virtual ~Players();    

	void            SetInGame(BOOL status);
	CString         GetIP();

	int             GetPort();
	BOOL            IsGod();
	void            SetGodMode(BOOL asd);


	UINT            NbPlayers();
	
	BOOL            SaveAccount(BOOL boPositioned = FALSE);
	BOOL            LoadAccount(CString name);

	void            AddPlayer(CString name, WORD race, WORD level);
	void            ModifyPlayer(CString name, WORD race, WORD level);
	void            RemovePlayer(CString name);
	void            AddToHistory(unsigned long historyDate, CString historyText);//BLBLBL pour enregistrer l'historique des punitions modo.

    static char *   QuotedAccount( char szBuffer[], CString csAccount ); // passage par ref
	void            SetAccount(CString name);
	CString         GetAccount() const;
    CString         GetFullAccountName() const; // Account + realm
    CString         GetRealm() const;

	void            SetPwd(CString pwd);
	CString         GetPwd() const;

	TemplateList <CStringAndRace> *GetPCs();	

	void                SetGodFlags( unsigned int i64Flags ); //__int64
	unsigned int    GetGodFlags(); //__int64

	static void     InitializeODBC( void );
	static void     DestroyODBC( void );

	void            UseDeathLock();
	void            UseUnlock( const char *lpszFileName, int nLineNumber );
	BOOL            UsePicklock( const char *lpszFileName, int nLineNumber );

    void            SetCredits( DWORD dwCredits );
    DWORD           GetCredits( void );

    void            BeginSession( void );

    void            WriteCreditDeduction( void );

    double          GetOnlineTime( void );

    void            SetNextSave( void );
    void            QueryNextSave( void );

    void            ResetIdle( void );
    BOOL            IsIdle( void );
        
    void            DeletePlayer( void ){ boDeletionFlag = TRUE; };
    BOOL            Delete( void ){ return boDeletionFlag; };

    BOOL            CreditDeduction( void ){ return cCreditDeduction == 0 ? FALSE : TRUE; };
    //void            QueryAuthWatchDog( void );    

    void            Logon( void );
    void            Logoff( void );
    
    bool            CanPage( void );
    void            PageNotification( void );

    bool CanShout( void );
    void ToggleShout( void );        

    bool            CanPVP(){ return boCanPVP; };
    void            SetPVP( bool boCanUserPVP ){ boCanPVP = boCanUserPVP; };

    void            SetRadiusPortID( DWORD dwPortID ){ dwRadiusPortID = dwPortID; };

    static bool     AccountLogged( const CString &csAccountName, LPCSTR szIP );
	static int 		IPLogged( LPCSTR szIP );
    static bool     AccountHeartBeat( void );
    static void     AccountLoggonFailed( const CString &csAccountName );
    static bool     NameExists( const string &name );	

    void            TogglePage( bool newState ){
        pages = newState;
    }

    bool            PageState( void ){
        return pages;
    }

    void SetFullPVP( bool state ){
        boFullPVP = state;
    }

    bool IsFullPVP( void ){
        return boFullPVP;
    }

    bool IsLoading();

    // Personnal structures. Old artifacts (aren't accessed through functions ).
    Character      *self;
    sockaddr_in     IPaddr;
    DWORD           dwRegenTime;
    DWORD           dwKickoutTime;
    //DWORD           dwAuthWatchDogTime;

    // Credit handling
    char cMinutesLeft;
    char cCreditDeduction;

	// InGame flags
    BOOL in_game;
	BOOL boPreInGame;	  
	BOOL registred;
	BOOL boRerolling;

    // General player flags
    BOOL boCanTalk;
	BOOL boCanShout;
	long lCutExpireDate;
	BOOL boLockedOut;
	long lLockExpireDate;
    BOOL boCanPage;
	BOOL god_mode;
    BOOL boWhoInvisible;
    
    // Idle time checking
    unsigned char IdleChances;
    unsigned int  IdleTime;

	unsigned long m_timeout;

	// BEGIN : Mestoph -> Anti SpeedHack
	/*int iCountMovement;
	int iSpeedHackTime;
	BOOL bSpeedHackWarned;*/
	// END : Mestoph -> Anti SpeedHack


	// BEGIN : BL -> Anti Speedhack (2nd try)
	unsigned long lLastRoundMove;
//	int MoveList[5];//pour stocker les 5 prochains mouvements 
	
	//void SaveMove(int direction);
	//int GetMove();
	std::list<int>   MoveList;
//	unsigned long lFirstRound;
//	unsigned long lMoveCounter; //compte le nombre de paquets reçus non pris

	// END : BL -> Anti Speedhack (2nd try)

	bool boSanctuPlug;
	
private:
    DWORD loadingCount;
    bool  pages;
    bool  boCanPVP;
    bool  boFullPVP;

    DWORD dwRadiusPortID;
    
    DWORD dwPlayerAcctID;

    DWORD dwNextPageTime;
    DWORD dwNextPageCount;

    bool  boIdle;

    DWORD dwNextShout;

    DWORD dwNextSave;

    time_t ttLogTime;

    DWORD dwCredits;

	unsigned int i64GodFlags; //__int64

	CString m_Account;
	CString m_Password;
    CString m_Realm;

	//TemplateList <CStringAndRace> PCs;
	TemplateList <CStringAndRace> *pPCs;

	CLock csUsageLock;

    static DWORD dwAutoSaveFrequency;

    BOOL boDeletionFlag;
};

#endif // !defined(AFX_PLAYERS_H__C2AF9A46_AC25_11D0_9B9E_444553540000__INCLUDED_)
