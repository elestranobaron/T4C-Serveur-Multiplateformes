// TFC Server.h : main header file for the TFC SERVER application
//
#define __TFC_SERVER_EXE

//#define CHANGE_THIS

#if !defined(AFX_TFCSERVER_H__BC8F3066_A74F_11D0_9B9E_444553540000__INCLUDED_)
#define AFX_TFCSERVER_H__BC8F3066_A74F_11D0_9B9E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#ifndef __AFXWIN_H__
//	#error include 'stdafx.h' before including this file for PCH
//#endif

#define MESSAGES_THREADS    1

void ReportLastError(void);

//#include "TFC Messages\ReportError.h"
#include "T4CLog.h"
#include "DebugLogger.h"
#include "resource.h"		// main symbols
//#include <afxtempl.h>
#include "TFCException.h"
#include "WorldMap.h"

#define ROUND_TIMER 1
#define TIME_SPAN   2

#define LOG_BUF_SIZE	4096

#define USERS_DSN		(LPCTSTR)theApp.csDBDns
#define USERS_USER		(LPCTSTR)theApp.csDBUser
#define USERS_PWD	    (LPCTSTR)theApp.csDBPwd

#define T4C_KEY			    "Software\\Vircom\\The 4th Coming Server\\"
#define AUTH_KEY		    "Authentication"
#define NETWORK_KEY		    "Network"
#define GEN_CFG_KEY		    "GeneralConfig"
#define PATHS_KEY		    "Paths"
#define EXTENSION_DLL_KEY   "ExtensionDLLs"
#define LANGUAGE_KEY        "LanguageDLLs"
#define PATCH_KEY           "PatchServers"
#define CHARACTER_KEY       "Characters"
#define CONTACT_KEY         "Contact"
#define ORACLE_HEART_BEAT   "Oracle heart beat"
#define CFG_BATTLE_MODE		"BattleMode" // DialSoft ADD for The Battle Mode

// BEGIN : Mestoph -> Anti SpeedHack
//#define CHEAT_KEY			"CheatProtection"
//#define SH_DEF_MOVMENTS		35  //75, BL : apparement speedhack reglé à 1.2 passe avec cette valeur
//#define SH_DEF_DELAY		5  //10, BL : trop large pour détecter les "petits coups d'accelerateur"
// END : Mestoph -> Anti SpeedHack

//#define DEBUG_EXCEPTION

//#define VOP_AUTH    0
#define ODBC_AUTH   1
//#define GOA_AUTH    2

	typedef struct _AUTHENTIFICATION{
    _AUTHENTIFICATION() : m_StripRealmPartOfAccount( false ){
    }

	BYTE    bAuthentificationMethod;
	
	CString csODBC_Account;
    CString csODBC_Credits;
	CString csODBC_DBPwd;
	CString csODBC_DBUser;
    CString csODBC_DSN;
	CString csODBC_Where;
    //CString csODBC_Privilege;
	//CString csODBC_PrivilegeValue;
	CString csODBC_Pwd;
	CString csODBC_Table;
	BOOL	boODBC_DeductCredits;
	
	//CString csVOP_NASIP;
	//CString csVOP_SECIP;
	//WORD    wVOP_SECPort;
	
    WORD    wAcctPort;
    CString csAcctIP;
    
    WORD    w2ndAuthPort;
    CString cs2ndAuthIP;
    WORD    w2ndAcctPort;
    CString cs2ndAcctIP;

    //CString csVOP_Secret;
    //CString csRealm;
    //CString csWGKey;
    //CString csRemoteWGKey;

    bool    m_StripRealmPartOfAccount;

    //WORD    vopLogLevels;
    //CString vopLogFile;

    //WORD    csWGFlag;
	//WORD    csVOP_NASPort;

} AUTHENTIFICATION;

typedef struct _NETWORK{
	CString csRecvIP;
    CString csSendIP;
    WORD	wRecvPort;
    WORD    wSendPort;
} NETWORK;

typedef struct _ORACLE_HB{
    WORD	csDelay;
    WORD    csState;
} ORACLE_HB;

typedef struct _GENERAL_CONFIG{
	WORD  wNbWarnings;
	DWORD dwTimeBeforeWarning;
	CString csLang;
} GENERAL_CONFIG;

typedef struct _PATHS{
	CString csBinaryPath;
	CString csLogPath;
} PATHS;

struct LICENSE_OPT{
    LICENSE_OPT(){
        wMaxUsers = 0xFFFF;
        loadDb = false;
    }

    bool loadDb;
    WORD wMaxUsers;
};

struct CONTACT{
    CString csCompanyName;
    CString csAdminEmail;
};

typedef struct _sMagicWorldSpell
{
   CString strText;
   DWORD   uiSpellID;
   DWORD   uiFlagID;
}sMagicWorldSpell;

// Area for arenas (no drops, special recall)
typedef struct _sArenaLocation
{
	WorldPos wlTopLeft;
	WorldPos wlBottomRight;
	WorldPos wlRecallTarget;
	WorldPos wlRecallAttacker;
}sArenaLocation;

/////////////////////////////////////////////////////////////////////////////
// CTFCServerApp:
// See TFC Server.cpp for the implementation of this class
//
class CTFCServerApp //: public CWinApp
{
public:
	CTFCServerApp();
    ~CTFCServerApp();

    CString csMachineName;

	AUTHENTIFICATION sAuth;
	NETWORK          sNetwork; 
	GENERAL_CONFIG	 sGeneral;
	PATHS            sPaths;
    LICENSE_OPT      sLicense;

    CONTACT          sContact;

	ORACLE_HB		 sOracleHB;

    bool serverStarted;

    LPCTSTR szServerAcctID;

	CString csDBDns;
	CString csDBUser;
    CString csDBPwd;
    
    HANDLE hCrtReportFile;
  
	BOOL InService;
	HANDLE hPipeMain;
	DWORD	sColosseum;
	DWORD	sDoppelganger;
	DWORD   sBattleMode;
	DWORD	sMaxRemorts;
	DWORD	sMaxCharactersPerAccount;
	DWORD	dwCustomStartupPositionOnOff;
	DWORD	dwCustomStartupPositionX;
	DWORD	dwCustomStartupPositionY;
	DWORD	dwCustomStartupPositionW;
	DWORD	dwCustomStartupSanctuaryOnOff;
	DWORD	dwCustomStartupSanctuaryX;
	DWORD	dwCustomStartupSanctuaryY;
	DWORD	dwCustomStartupSanctuaryW;
	DWORD	dwChestEncumbranceUpdatedLive;
	CString	csChestEncumbranceBoostFormula;
	DWORD	dwLogXPGains;
	DWORD	dwHideUncoverEffectDisabled;
	DWORD	dwRobWhileWalkingEnabled;
	DWORD	dwRobWhileBeingAttackedEnabled;
	DWORD	dwDisableIndirectDelete;
	DWORD	dwDebugSkillParryDisabled; //Temporary option to disable parry if it turns buggy. This option will be removed soon.
	//BATTLEMODE CFG//
	DWORD	sxptm1killtm2;
	DWORD	sgoldtm1killtm2;
	DWORD	skarmatm1killtm2;
	DWORD	sxptm2killtm1;
	DWORD	sgoldtm2killtm1;
	DWORD	skarmatm2killtm1;
	DWORD	sxplostsameteam;
	DWORD	sgoldlostsameteam;
	DWORD	skarmagaintk;
	DWORD	skarmalosttk;

	DWORD	sbonuskill1;
	DWORD	sbonuskill2;
	DWORD	sbonuskill3;
	DWORD	sxpbonus1;
	DWORD	sxpbonus2;
	DWORD	sxpbonus3;
	DWORD	sgoldbonus1;
	DWORD	sgoldbonus2;
	DWORD	sgoldbonus3;
	DWORD	dwDeadSpellID;	
	//BATTLEMODE CFG//

	DWORD	dwDisableItemInfo;
	DWORD	dwEncryptedPassword;
	DWORD	dwPasswordCaseSensitive;

	DWORD   dwScriptLoopLength;
	DWORD	dwPVPDropDisabled;

	// BEGIN : Mestoph -> Anti SpeedHack
/*	int		iSpeedHackDelay;
	int		iSpeedHackMaxMovments;*/
	// END : Mestoph -> Anti SpeedHack

    //CArray<sMagicWorldSpell,sMagicWorldSpell> m_aSpellWorld;
    //CArray<int,int> m_aStillItems;
	
	std::vector<std::pair<sMagicWorldSpell,sMagicWorldSpell> > m_aSpellWorld;
	std::vector<std::pair<int,int> > m_aStillItems;

	list< sArenaLocation > arenaLocationList;

private:
	DWORD last_PlayerMainDeadlockFlag;
	DWORD last_TFCMainDeadlockFlag;

	DWORD last_PlayerMainTime;
	DWORD last_TFCMainTime;

	BYTE current_check;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TFCSERVER_H__BC8F3066_A74F_11D0_9B9E_444553540000__INCLUDED_)
