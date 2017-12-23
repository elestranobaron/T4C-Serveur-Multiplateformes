// Character.cpp: implementation of the Character class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Character.h"
#include "Random.h"
#include <math.h>
#include "WorldMap.h"
#include "ObjectFlagsListing.h"
#include "ObjectListing.h"
#include "tfc_main.h"
#include "Players.h"
//#include "TFC Messages\ReportError.h"
#include "Objects.h"
#include "TFCTimers.h"
#include "RaceListing.h"
#include "StatModifierFlagsListing.h"
#include "Broadcast.h"
#include "BlockingListing.h"
#include "Unit.h"
#include "SkillListing.h"
#include "_item.h"
#include "BoostListing.h"
#include "SpellListing.h"
#include "ODBCMage.h"
#include "TFC Server.h"
#include "IntlText.h"
#include "DynObjListing.h"
#include "TFCPacket.h"
#include "PacketManager.h"
#include "AutoConfig.h"
#include "RegKeyHandler.h"
#include "Format.h"
#include "MonsterStructure.h"
//#include "GlobalStatistics.h"
#include "QuestFlagsListing.h"
#include "WeatherEffect.h"
#include "PlayerManager.h"//BLBLBL ajouté cet include
#define _T
#include "PVPSentence.h"
#include <iterator>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DEATH_EFFECT_ID     30012
#define PVP_ADDING_POINT		10
// These are the database row IDs. The IDs MUST be SORTED and ORDERED
#define DB_ID					1
#define DB_AccountName			2
#define DB_wlX					3
#define DB_wlY					4
#define DB_wlWorld				5
#define DB_nClass				6
#define DB_CurrentHP			7
#define DB_MaxHP				8
#define DB_CurrentMana			9
#define DB_MaxMana				10
#define DB_Strength				11
#define DB_Endurance			12
#define DB_Agility				13
#define DB_Intelligence			14
//#define DB_WillPower			15
#define DB_Wisdom				15
#define DB_Level				16
#define DB_AttackSkill			17
#define DB_DodgeSkill			18
#define DB_Gold					19
#define DB_Appearance			20
#define DB_Corpse				21
#define DB_XP					22
#define DB_StatPnts				23
#define DB_SkillPnts			24
#define DB_Karma                25
#define DB_Gender               26
#define DB_ListingTitle         27
#define DB_ListingMisc          28
#define DB_MoveExhaust          29
#define DB_MentalExhaust        30
#define DB_AttackExhaust        31
#define DB_Luck					32
// asteryth guilds
#define DB_GuildName			33
#define DB_GuildID				34
#define DB_GuildChestAccess		35
// asteryth pvp ranking
#define DB_TotalDeathNumber		36
#define DB_TotalKillNumber		37
#define DB_CurrentDeathNumber	38
#define DB_CurrentKillNumber	39
#define DB_BestSerieMurder		40
#define DB_CurrentSerieMurder	41
#define DB_CurrentPvpPoint		42
#define TRACE printf
typedef struct __SYSTEMTIME
{
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME;
int Character::sm_n64XPchart[MAX_LEVEL]; //__int64

BYTE Character::m_bSkillPnt[ (MAX_LEVEL / 10) + 1 ] = {
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

const DWORD TIME_BEFORE_CORPSE_ROT = 15 MINUTES;
const DWORD MIN_LEVEL_DEATH_REPORT = 1;
const WorldPos wlStartPos = { 2944, 1059, 0 };
const WorldPos wlDeathPos = { 2948, 1041, 0 };

static BoostFormula startupGold;

//SpellEffect SpellInterface;
extern Random rnd;

extern CTFCServerApp theApp;

static struct vstring : public vector< string >, CLock{} vStartupItems;

#define BOW_POS     BodyPos::weapon_right
#define QUIVER_POS  BodyPos::weapon_left

//CharactersDB Character::dbCharacters;

cODBCMage ODBCCharWrite;
cODBCMage ODBCCharRead;
cODBCMage ODBCCharAsyncSave;

static CLock statsLock;

void WaitForAsyncSaveFunc( void ){
    ODBCCharAsyncSave.WaitForODBCShutdown();
}

void DisconnectCharODBC( void ){
    ODBCCharWrite.Disconnect();
    ODBCCharRead.Disconnect();
    ODBCCharAsyncSave.Disconnect();
}

#define TELL_PLAYER( __textID )		{TFCPacket sending;\
									/* Send a packet telling the user it cannot equip this weapon*/\
									CString csText;\
									csText = _STR( __textID, wLang );\
									sending << (RQ_SIZE)RQ_ServerMessage;\
									sending << (short)30;\
									sending << (short)3;\
                                    TRACE( "\r\nSending player message %s.", (LPCTSTR)csText );\
									sending << (CString &)csText;\
									sending << (long)0x000A64E0/*RGB( 0, 100, 255 )*/;\
									SendPlayerMessage( sending );}


void Character::TraceExhaust(){
   /* DWORD callerAddr;
    GET_CALLER_ADDR( callerAddr );
    EXHAUST ex = GetExhaust();
    _LOG_DEBUG
        LOG_DEBUG_LVL4,
        "Exhaust=%u,%u,%u (%u,%u,%u) - 0x%x",
        ex.move,
        ex.attack,
        ex.mental,
        loadMoveExhaust,
        loadAttackExhaust,
        loadMentalExhaust,
        callerAddr
    LOG_*/
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define addskill( id, hook, strength )	{LPUSER_SKILL lp = new USER_SKILL;\
	lp->nSkillID = id;\
	lp->nSkillPnts = strength;\
tlusSkills[hook].AddToTail(lp);}

#define addspell( id ){ LPUSER_SKILL lp = new USER_SKILL;\
	lp->nSkillID = id;\
	lp->nSkillPnts = 100;\
	tlusSpells.AddToTail( lp );\
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::AutoConfigUpdate( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Called whenever the registry changed.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    RegKeyHandler regKey;    
    CString csKey;    
    
    regKey.Open( /*HKEY_LOCAL_MACHINE*/NULL, T4C_KEY CHARACTER_KEY );

    vStartupItems.Lock();
    // Erase previous startup items.
    vStartupItems.erase( vStartupItems.begin(), vStartupItems.end() );

    int i = 1;
    // Fetch all local ip definitions.
    CString csItem = regKey.GetProfileString( "StartupItem1", "$NULL$" );
    while( csItem != "$NULL$" ){
        *back_inserter( vStartupItems ) = (LPCTSTR)csItem;
        
        csKey.Format( "StartupItem%u", ++i );
        csItem = regKey.GetProfileString( (LPCTSTR)csKey, "$NULL$" );
    }
    vStartupItems.Unlock();

    startupGold.SetFormula( regKey.GetProfileString( "StartupGold", "200+1d50" ) );
}


//////////////////////////////////////////////////////////////////////////////////////////
// Destroys the equipment.
void Character::DestroyEquipment( void ){
	int i, j;

    for(i = 0; i < EQUIP_POSITIONS; i++){
        if( equipped[i] != NULL ){
            // Check all other succeeding equip positions to see if its equipped twice (two-hands etc).
            for( j = i+1; j < EQUIP_POSITIONS; j++ ){                
                if( equipped[ j ] == equipped[ i ] ){
                    equipped[ j ] = NULL;
                }
            }
            equipped[i]->DeleteUnit();
            equipped[ i ] = NULL;
        }
    }
  
}

Character::Character() : 
    autoCombatAttack( Character::Attack::normal, 0 ),
    prevAutoCombatAttack( Character::Attack::normal, 0 ),
    gameopContext( 0 ),
	boCharacterIsChesting(false),
	m_TradeMgr2(*this),	
	numberOfSaveFailures( 0 ),
	boAuthGM( false )
{		
	// Create an event signaled ( player created by default ).
	// Avoids player to load before it has finished to save.
	//hCreationEvent = CreateEvent( NULL, TRUE, TRUE, NULL );
	mrevent_init(&mrev);

    SetStatus( IS_PLAYER | GetStatus() );
	
    wLang = IntlText::GetDefaultLng();

	Do(wandering);
	exhaust.move = 0;
	exhaust.attack = 0;
	exhaust.mental = 0;
    exhaust.boWalking = FALSE;
	
	SetBlock( __BLOCK_CAN_FLY_OVER );

	nClass = 0;

	_died_ = FALSE;
	gold = 0;
	// asteryth 
	GuildChestAccess = 0;

	ThisPlayer = NULL;
	KillMe = FALSE;
	account = "";
	SetName("");

	WorldPos WL;
	WL.X = 0xFFFFFFFF;
	WL.Y = 0xFFFFFFFF;
	WL.world = 0xFFFFFFFF;

	SetWL(WL);

	gold = 0;

	Create(U_PC, 0);
	
	TRACE(_T("Created a character %u %u %u!\r\n"), WL.X, WL.Y, WL.world);

	backpack = new TemplateList <Unit>;
	chest = new ItemContainer();

	int i;
	for(i = 0; i < EQUIP_POSITIONS; i++)
		equipped[i] = NULL;

//	for(i = 0; i < NB_CLASS; i++)
//		ClassPoints[i] = 0;

	wNbStatPnts = 0;
	wNbSkillPnts = 0;
	SetXP(0);

	boLoaded = FALSE;
	boSavingOnProgress = FALSE;//BLBLBL ajout d'une variable permettant de savoir si un personnage est en cours de sauvegarde
	                           //afind d'éviter de lancer deux requetes SQL en overlapping.

    bGender = GENDER_MALE;   // Default...
    nKarma  = 0;            // neutral by default

    SetLightResist( 5000 );

    lpGroup = NULL; // No group by default.

    // Display the arrival at 1st logon only.
    seraphAlreadyArrived = false;

    lastInviteTime = 0;

	boClientExitCountDown = false;//BLBLBL antiplug
	WorldPos prevTeleportPos;(void)prevTeleportPos;
	prevTeleportPos.X = 0xFFFFFFFF;
	prevTeleportPos.Y = 0xFFFFFFFF;
	prevTeleportPos.world = 0xFFFFFFFF;
}

Character::~Character()
{	
	if( backpack != NULL ){
        backpack->ToHead();
		while(backpack->QueryNext()){
			//backpack->DeleteAbsolute();
            backpack->Object()->DeleteUnit();
            backpack->Remove();
		}        
	
		delete backpack;
	}
	if ( chest != NULL ) delete chest;

    DestroyEquipment();
   
	TemplateList <USER_SKILL> tlDeletedSkills;
	BOOL boFound;

    int i;

	for( i = 0; i < NB_SKILL_HOOKS; i++ ){
		tlusSkills[ i ].ToHead();
		// Pass all the skills in the hook
		while( tlusSkills[ i ].QueryNext() ){
			// Check if pointer has already been deleted
			boFound = FALSE;
			tlDeletedSkills.ToHead();
			while( tlDeletedSkills.QueryNext() && !boFound ){
				if( tlDeletedSkills.Object() == tlusSkills[ i ].Object() ){
					boFound = TRUE;
				}
			}

			// If user skill hasn't been deleted.
			if( !boFound ){				
				tlDeletedSkills.AddToTail( tlusSkills[ i ].Object() );
				tlusSkills[ i ].DeleteAbsolute();
			}
		}
	}

	tlusSpells.ToHead();
	while( tlusSpells.QueryNext() ){
		tlusSpells.DeleteAbsolute();
	}
    pthread_cond_destroy(&mrev.cond);
    //CloseHandle( hCreationEvent );

    // The robbing flag is never persistent.
    RemoveFlag( __FLAG_ROBBING );
	RemoveFlag( __FLAG_PEEKING );

	TRACE(_T("Destroyed a character\r\n"));

}
void Character::SetPlayer(Players *Player){
	ThisPlayer = Player;
}


//////////////////////////////////////////////////////////////////////////////////////////
cODBCMage *Character::GetODBC( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the ODBC connection used for player selecting.
// 
// Return: cODBCMage, The ODBC connection
//////////////////////////////////////////////////////////////////////////////////////////
{
    return &ODBCCharRead;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::InitializeODBC( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Connects the characters' database.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	ODBCCharWrite.Connect( USERS_DSN, USERS_USER, USERS_PWD );
	ODBCCharRead.Connect( USERS_DSN, USERS_USER, USERS_PWD );
	ODBCCharAsyncSave.Connect( USERS_DSN, USERS_USER, USERS_PWD );
		
	// BEGIN : Mestoph -> What disable transaction méthode ? i have remove the comment
	ODBCCharRead.Lock();

	// Sets write connections' autocommit off
	ODBCCharWrite.ConnectOption( SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF );	
	ODBCCharAsyncSave.ConnectOption( SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF );	
	// END : Mestoph -> What disable transaction méthode ? i have remove the comment
/*	// Fetches all IDs in the characters table.
	ODBCCharRead.SendRequest( "SELECT UserID, AccountName, CurrentLevel FROM PlayingCharacters" );

	DWORD dwID = 0;
    DWORD totalRecordCount = 0;
    char  accountName[20];

    
//    GlobalStatistics::LevelStat lvl;

    map< string, DWORD > accountMap;

	// Fetch each rows.
	while( ODBCCharRead.Fetch() ){		
        DWORD level;

		ODBCCharRead.GetDWORD(  1, &dwID );
        ODBCCharRead.GetString( 2, accountName, 20 );
        ODBCCharRead.GetDWORD(  3, &level );*/
/*
        if( level <= 2 ){
            lvl.underLvl2++;
        }else if( level <= 5 ){
            lvl.underLvl5++;
        }else if( level <= 10 ){
            lvl.underLvl10++;
        }else if( level <= 25 ){
            lvl.underLvl25++;
        }else if( level <= 50 ){
            lvl.underLvl50++;
        }else if( level <= 75 ){
            lvl.underLvl75++;
        }else if( level <= 100 ){
            lvl.underLvl100++;
        }else if( level <= 125 ){
            lvl.underLvl125++;
        }else if( level <= 150 ){
            lvl.underLvl150++;
        }else{
            lvl.overLvl150++;
        }
*/
    /*    totalRecordCount++;
        accountMap[ accountName ]++;
	}*/

    /*DWORD avrgPlayersPerAccount = 0;
    if( accountMap.size() != 0 ){
        avrgPlayersPerAccount = totalRecordCount / accountMap.size();
    }*/

/*    GlobalStatistics::GetInstance()->SendRecordCount( 
        totalRecordCount, 
        accountMap.size(), 
        avrgPlayersPerAccount,
        lvl        
    );*/

	// Stop transaction.
	// BEGIN : Mestoph -> Not comment this rows !
	ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close
	ODBCCharRead.Unlock();
	// END : Mestoph -> Not comment this rows !
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::DestroyODBC( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Disconnects from the characters' database.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	ODBCCharRead.Disconnect( );
	ODBCCharWrite.Disconnect( );
}

//////////////////////////////////////////////////////////////////////////////////////////
void AssignValidID
//////////////////////////////////////////////////////////////////////////////////////////
// Assigns a valid ID to the given character.
// 
(
 Character *target // The character to set a valid ID to.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    ODBCCharRead.Lock();

	// Fetches all IDs in the characters table.
	ODBCCharRead.SendRequest( "SELECT UserID FROM PlayingCharacters ORDER BY UserID" );
	//BLBL à tester !
	/*CString csQuery;
	csQuery.Format( "SELECT UserID FROM PlayingCharacters WHERE PlayerName='%s' AND UserAccount='%s'", (LPCTSTR)target->GetName(), (LPCTSTR)target->GetTrueName() );
	ODBCCharRead.SendRequest( (LPCTSTR)csQuery );*/

	DWORD Id = 0;
    DWORD previousId = 0;
	// Fetch each rows.

/*	ODBCCharRead.Fetch();//BLBL on lit directement le UserID Attribué au player en question. :
	ODBCCharRead.GetDWORD( 1, &Id );//BLBL*/


	while( ODBCCharRead.Fetch() )
	{		
		ODBCCharRead.GetDWORD( 1, &Id );

        // If an Id gap was found.
        if( Id - previousId > 1 )
		{
            // Stop search.
            break;
        }
        previousId = Id;
	}
    ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

    // Assign an Id one bigger then the previousId.
    target->SetID( previousId + 1 );
	//target->SetID( Id );//BLBLBL

    ODBCCharRead.Unlock();
}

///////////////////////////////////////////////////////////////////////////////////////////
// This function inits the xp table
void Character::InitXPchart(){	

    // Set auto-update function :P
    CAutoConfig::AddRegUpdateCallback( AutoConfigUpdate );
    AutoConfigUpdate();

    int n64XP = 0; // __int64
    int nLevel = 0;
    int y = 0;
    int z = 10;
    
    sm_n64XPchart[ 0 ] = 0;

    for( nLevel = 1; nLevel < MAX_LEVEL; nLevel++ ){
        /*dX += ( 1000 * dInc );
        n64XP += (__int64)( dX );
        
        dIncFactor = dIncFactor - 0.001;
        dInc *= dIncFactor;*/

        if( nLevel <= 41 ){
            n64XP = static_cast< int >( pow( nLevel, 2.5 ) * ( 1000 + y ) ); // __int64
            y += z;
        }else if( nLevel <= 81 ){
            n64XP = static_cast< int >( pow( nLevel, 2.5 ) * ( 1000 + y ) ); // __int64
            y += z;
            z += 1;
        }else if( nLevel <= 121 ){
            n64XP = static_cast< int >( pow( nLevel, 2.5 ) * ( 1000 + y ) ); // __int64
            y += z;
            z += 4;
        }else if( nLevel <= 141 ){
            n64XP = static_cast< int >( pow( nLevel, 2.5 ) * ( 1000 + y ) ); // __int64
            y += z;
            z += 16;
        }else if( nLevel <= 161 ){
            n64XP = static_cast< int >( pow( nLevel, 2.5 ) * ( 1000 + y ) ); // __int64
            y += z;
            z += 64;
        }else if( nLevel <= 181 ){
            n64XP = static_cast< int >( pow( nLevel, 2.5 ) * ( 1000 + y ) ); // __int64
            y += z;
            z += 256;
        }else if( nLevel <= 191 ){
            n64XP = static_cast< int >( pow( nLevel, 2.5 ) * ( 1000 + y ) ); // __int64
            y += z;
            z += 1024;
        }else{
            n64XP = static_cast< int >( pow( nLevel, 2.5 ) * ( 1000 + y ) ); // __int64
            y += z;
            z += 4096;
        }
        Character::sm_n64XPchart[ nLevel ] = n64XP;
                
        TRACE( "\r\nLevel %u requires %I64u xp.", nLevel+1, n64XP );
    }
    TRACE( "test.." );
}


/***************************************************************************/
/***************************************************************************/
// Rerolls a character's stats.
BOOL Character::roll_stats()
{
	//TRACE("\r\nThis is the flag -> %u\r\n", ViewFlag(__FLAG_LEVEL));
	if(GetLevel() < 2){
	
		WorldPos WL;
		// starting pos..
		{
			BOOL boUseDefault = TRUE;
			if (theApp.dwCustomStartupPositionOnOff) { // server has a custom start position configured on registry.
				WL.X = theApp.dwCustomStartupPositionX;
				WL.Y = theApp.dwCustomStartupPositionY;
				WL.world = theApp.dwCustomStartupPositionW;
				// Test if its a valid position.
				WorldMap *wlWorld = TFCMAIN::GetWorld( WL.world );
				// If world exist and the position is valid, use custom start position else use the defaut
				if( wlWorld != NULL && wlWorld->IsValidPosition( WL ) ){
					boUseDefault = FALSE;
				}
			}

			if ( boUseDefault ) {
				WL.X = wlStartPos.X;
    			WL.Y = wlStartPos.Y;
				WL.world = wlStartPos.world;
			}


		}
		SetWL( WL );

//		DestroyStaticFlags();
		DestroyFlags();

		if ( theApp.dwCustomStartupSanctuaryOnOff) { // server has a custom startup sanctuary position set on registry
			WorldPos WLSanc;
			WLSanc.X	 = theApp.dwCustomStartupSanctuaryX;
			WLSanc.Y	 = theApp.dwCustomStartupSanctuaryY;
			WLSanc.world = theApp.dwCustomStartupSanctuaryW;

			// Test if its a valid position.
			WorldMap *wlWorld = TFCMAIN::GetWorld( WLSanc.world );
			// If world exist and the position is valid, use custom sanctuary position else use the defaut
			if( wlWorld != NULL && wlWorld->IsValidPosition( WLSanc ) ){
				DWORD dwStartSanctuary = ( ( (DWORD)( (WORD)WLSanc.X ) << 20 ) + ( (DWORD)( (WORD)WLSanc.Y ) << 8 ) + (DWORD)( (BYTE)WLSanc.world ) );
				SetFlag( __FLAG_DEATH_LOCATION, dwStartSanctuary);
			}

		}

		
		SetXP(0);
 
        TRACE( "\r\nSTR %u, AGI %u, END %u, INT %u, WIS %u, WIL %u, LCK %u.",
                bRollSTR,
                bRollAGI, bRollEND, bRollINT, bRollWIS, bRollWIL, bRollLCK );

        SetSTR( static_cast< WORD >( rnd( 0, 4 ) + 6 + bRollSTR ) );
        SetAGI( static_cast< WORD >( rnd( 0, 4 ) + 6 + bRollAGI ) );
        SetEND( static_cast< WORD >( rnd( 0, 4 ) + 6 + bRollEND ) );
        SetINT( static_cast< WORD >( rnd( 0, 4 ) + 6 + bRollINT ) );
        SetWIS( static_cast< WORD >( rnd( 0, 4 ) + 6 + bRollWIS ) );
		//SetLCK( static_cast< WORD >( rnd( 0, 4 ) + 90 + bRollLCK ) );//BLBLBL tous les joueurs doivent avoir 100 en luck !!!!
		SetLCK( static_cast< WORD >( 100 ) );

        SetSTR( GetSTR() > 22 ? 22 : GetSTR() );
        SetAGI( GetAGI() > 22 ? 22 : GetAGI() );
        SetEND( GetEND() > 22 ? 22 : GetEND() );
        SetINT( GetINT() > 22 ? 22 : GetINT() );
        SetWIS( GetWIS() > 22 ? 22 : GetWIS() );
		//SetLCK( GetLCK() > 110 ? 110 : GetLCK() );
		SetLCK( 100 );//BLBLBL tous les joueurs doivent avoir 100 en Luck dès le départ.

        SetATTACK( 15 );
        SetDODGE( 15 );

        SetMaxHP( rnd.roll( dice( 2, 5 ) ) + 48 + GetEND() );
        SetHP( GetMaxHP(), false );

        SetMaxMana( 10 + GetTrueINT() * 2 / 3 + GetTrueWIS() / 3 + rnd( 0, 5 ) );
        SetMana( GetMaxMana() );

        gold = startupGold.GetBoost( this );

    	return TRUE;
	}
return FALSE;
}


//////////////////////////////////////////////////////////////////////////////////////////
bool Character::IsNameValid
//////////////////////////////////////////////////////////////////////////////////////////
// Determines if a character's name is valid.
// 
(
 CString &name // The name
)
// Return: static bool, true if the name is valid.
//////////////////////////////////////////////////////////////////////////////////////////
{
    name.TrimLeft();
    name.TrimRight();

	// Only gets wanted characters
	CString check_name = name.SpanIncluding(_T("1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ -ïëöéèàùä"));//BLBLBL

	// If the packet is a valid one
	if( name.GetLength() > 1 && check_name == name && name.GetLength() <= 19){//BLBLBL
		return true;
	}
	return false;
}

/***********************************************************************************************/
// Loads a player into memory, either from a previously saved player, or create a new one
char Character::load_character(CString new_name, CString new_account, LPBYTE lpbAnswers )
{
    
		_LOG_DEBUG
			LOG_DEBUG_HIGH,
			"Reset_character %s.",
			new_name.c_str()
		LOG_
	reset_character();
    
    CString full_directory;
	//CFile player_file;

    new_name.TrimRight();
    new_name.TrimLeft();

/*		_LOG_DEBUG
			LOG_WARNING,
			"Trimmed name %s.",
			new_name
		LOG_*/

	
	// If the packet is a valid one
	if( IsNameValid( new_name ) )
	{

	/*	_LOG_DEBUG
			LOG_WARNING,
			"Name %s is valid.",
			new_name
		LOG_*/

		// If we want to create a new player
		if( lpbAnswers != NULL )
		{

	/*	_LOG_DEBUG
			LOG_WARNING,
			"New player creation.",
			new_name
		LOG_*/

			Players *pl = (Players *)ThisPlayer;
            if( pl != NULL ){
    			// Could not create player.
	    		if(pl->NbPlayers() >= TFCMAIN::GetMaxCharactersPerAccount()) return 4;
		    			
    			// If the player hasn't too many accounts
	    		// we check to see if the player already exists.
		    	// if it fails from opening the player's file, then it's ok ;)
			    TRACE(_T("\r\nOpening %s!"), (LPCTSTR)full_directory);	
			
    			if( CreateCharacter( new_name, lpbAnswers ) )
				{
	    			pl->AddPlayer(new_name, 0, 1);
		    		pl->SaveAccount();

		    		pl->boRerolling = TRUE;

				    return 0;
			    }else{
				    return 5;
			    }
            }else{
                return 5;
            }
		}else{ // If we want to load an already existing player and put it in_game

	/*	_LOG_DEBUG
			LOG_WARNING,
			"Already existing char.",
			new_name
		LOG_*/
			
			//SetStaticFlag(__FLAG_BLOCKING, 1);
			SetName(new_name);

/*		_LOG_DEBUG
			LOG_WARNING,
			"Set name to %s.",
			new_name
		LOG_*/


            int result = LoadCharacter(new_name);

/*		_LOG_DEBUG
			LOG_WARNING,
			"Loaded %s with result %d.",
			new_name, result
		LOG_*/
		

			if(result) 
				return (char)result;

			Players *pl = (Players *)ThisPlayer;
            if( pl != NULL )
			{                
                pl->Logon();
		_LOG_DEBUG
			LOG_WARNING,
			"Login character %s.",
			new_name.c_str()
		LOG_

            }
                        			
			boLoaded = TRUE;
			//account = new_account;
			return(0); // Loaded successfully
		}
	}
account.Empty();
//name.Empty();
return 8;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Add a query to the batch requests
#define ADD_QUERY	{ \
	LPSQL_REQUEST lpSql = new SQL_REQUEST;\
	lpSql->csQuery = csQuery;\
	lptlSQLRequests->AddToTail( lpSql );\
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::DataSaveCallback
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
 DWORD dwSaveStatus,	// Status of ODBC request
 LPVOID lpData			// The character object
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	Character *self = (Character *)lpData;

	if (dwSaveStatus == BATCH_SUCCEEDED) {
		_LOG_DEBUG
			LOG_DEBUG_HIGH,
			"Stopped saving (with success) character %s.",
			(LPCTSTR)self->GetTrueName()
		LOG_
		self->numberOfSaveFailures = 0;
	} else {
		_LOG_DEBUG
			LOG_WARNING,
			"FAILED saving character %s.",
			(LPCTSTR)self->GetTrueName()
		LOG_
		if (++self->numberOfSaveFailures > 2) {
			_LOG_DEBUG
				LOG_CRIT_ERRORS,
				"Reached maximum number of acceptable character save failures. Disconnecting character %s to avoid data loss and timewarps.",
				(LPCTSTR)self->GetTrueName()
			LOG_
			Players *selfPlayer = self->GetPlayer();
			TFCPacket sending;
			sending << (RQ_SIZE)RQ_ServerMessage;
			sending << (short)30;
			sending << (short)3;
			sending << (CString )CString("Server problem. You're being disconnected to avoid corruption of your character. Sorry for the inconvenience."); //origin (CString &)
			sending << (long)RGB(255,0,0);
			selfPlayer->Lock();
			self->SendPlayerMessage( sending );
			selfPlayer->dwKickoutTime = 2 SECONDS TDELAY;
			selfPlayer->Unlock();
		}
	}

	// Set saving event signaled ( save terminated ).
	self->SavingStop();
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Character::SaveCharacter( BOOL boCallback )
//////////////////////////////////////////////////////////////////////////////////////////
// Saves a character
// 
// Return: BOOL, TRUE if character could be saved.
//////////////////////////////////////////////////////////////////////////////////////////
{
	// Saving starts.

	if (boSavingOnProgress) {
		_LOG_DEBUG
			LOG_DEBUG_LVL3,
			"Save of character %s refused, a save is already on progress.",
			(LPCTSTR)GetTrueName()
		LOG_
		return TRUE;//FALSE; //BLBLBL si une sauvegarde du joueur est déjà en cours on arrête la nouvelle tentative de sauvegarde
	} else {
		_LOG_DEBUG
			LOG_DEBUG_LVL3,
			"Save of character %s accepted, no other save was on progress, starting now...",
			(LPCTSTR)GetTrueName()
		LOG_
		boSavingOnProgress = TRUE;//autrement on positionne le boolean qui indique qu'on vient de démarrer.
    }  
    if( boCallback )
	{
        SavingStart();
    }

    Lock();

    // Load the deferred loaded effects before saving.
    DeferredLoadEffects();

	CString csQuery;
	CString csTemp;
	DWORD dwUserID = GetID();
	BOOL boDBError = FALSE;	// if there is a database error.
		
	if( _died_ )
	{
		SetWL( wlDeathPos );
	}

	TemplateList< SQL_REQUEST > *lptlSQLRequests = new TemplateList< SQL_REQUEST >;

	/////////////////////////////////////////////////////////////////////////////////
	// Saves the objects	
	UINT i;
	BYTE lpszName[ 50 ];

    _LOG_DEBUG
        LOG_DEBUG_LVL3,
        "(Saving character %s) Deleting previous records.",
        (LPCTSTR)GetTrueName()
    LOG_

/*    Players *lpPlayer = static_cast< Players * >( this->GetPlayer() );//BLBLBL on choppe un handle sur le joueur qui tente de ramasser
	
	_LOG_DEBUG    
           LOG_DEBUG_LVL1,
            "Character %s at save have a move ratio of : %.2f refused moves per round",
            (LPCTSTR)GetTrueName(),
			lpPlayer->lMoveCounter/(TFCMAIN::GetRound()-lpPlayer->lFirstRound)
			
    LOG_
*/

    
	// Delete items owned by the player at last save.
	csQuery.Format( "DELETE FROM PlayerItems WHERE OwnerID=%u", GetID() );
	ADD_QUERY

	// Delete chest items owned by the player at last save.
	csQuery.Format( "DELETE FROM ChestItems WHERE OwnerID=%u", GetID() );
	ADD_QUERY

	// Delete everything related to this player.
	csQuery.Format( "DELETE FROM Flags WHERE BaseOwnerID=%d", GetID() );	
	ADD_QUERY

  	csQuery.Format( "DELETE FROM Boosts WHERE BaseOwnerID=%d", GetID() );
	ADD_QUERY

	csQuery.Format( "DELETE FROM Effects WHERE BaseOwnerID=%d", GetID() );
	ADD_QUERY

    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Saving backpack"
    LOG_

	MultiLock(backpack, m_TradeMgr2.GetCLock());
	BOOL isTradeValidAndTrading = TRUE;
	if (m_TradeMgr2.IsTradeValid() != TradeMgr2::ErrorCodes::IsTrading) {
		m_TradeMgr2.GetCLock()->Unlock();
		isTradeValidAndTrading = FALSE;
	}
	// Begin by saving the backpack

	backpack->ToHead();
	while( backpack->QueryNext() && !boDBError ){
		Objects *obj = static_cast< Objects * >( backpack->Object() );

        

		// If the item is not gold and if the unit name ID could be found
		if( obj->GetStaticReference() != __OBJ_GOLD && Unit::GetNameFromID( obj->GetStaticReference(), (LPTSTR)(LPCTSTR)lpszName, U_OBJECT ) ){
			// Insert new object into PlayerItems table
			csQuery.Format( 
				"INSERT INTO PlayerItems( ObjID, OwnerID, EquipPos, ObjType, Qty ) VALUES ( "
				"%u,"
				"%u,"
				"0,"
				"'%s',"
                "%u"
				" )",
				obj->GetID(),
				dwUserID,					
				lpszName,
                obj->GetQty()
			);

			ADD_QUERY
			
            // If the object is shared.
            if( !obj->IsUnique() ){
                // Remove the charges flag to avoid cluttering the database.
                obj->RemoveFlag( __FLAG_CHARGES );
            }


			// Then save the object's specific flags.
			if( obj->SaveFlags( lptlSQLRequests, GetID() ) ){
				boDBError = TRUE;
			}

			// Save the object's boosts.
			if( obj->SaveBoosts( lptlSQLRequests, GetID() ) ){
				boDBError = TRUE;
			}

            
            // If the object is shared.
            if( !obj->IsUnique() ){
                // Re-set the flags to continue playing.
                obj->SetFlag( __FLAG_CHARGES, 1 );
            }

		}
	}




    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Saving items being traded"
    LOG_

	/////////////////////////////////////////////////////////////////////////////////////
	// Save the items that are on the trade container as if they were on user's backpack

	if (isTradeValidAndTrading == TRUE) {
		ItemContainer *tradeItemContainer = m_TradeMgr2.GetItemContainer();
		TemplateList<Objects> *tloTradeItems = tradeItemContainer->LockAndGetList();
		tloTradeItems->ToHead();
		while( tloTradeItems->QueryNext() && !boDBError ){
			Objects *obj = tloTradeItems->Object();

			// If the item is not gold and if the unit name ID could be found
			if( obj->GetStaticReference() != __OBJ_GOLD && Unit::GetNameFromID( obj->GetStaticReference(), (LPTSTR)(LPCTSTR)lpszName, U_OBJECT ) ){
				// Insert new object into PlayerItems table
				csQuery.Format( 
					"INSERT INTO PlayerItems( ObjID, OwnerID, EquipPos, ObjType, Qty ) VALUES ( "
					"%u,"
					"%u,"
					"0,"
					"'%s',"
					"%u"
					" )",
					obj->GetID(),
					dwUserID,					
					lpszName,
					obj->GetQty()
				);

				ADD_QUERY
				
				// If the object is shared.
				if( !obj->IsUnique() ){
					// Remove the charges flag to avoid cluttering the database.
					obj->RemoveFlag( __FLAG_CHARGES );
				}


				// Then save the object's specific flags.
				if( obj->SaveFlags( lptlSQLRequests, GetID() ) ){
					boDBError = TRUE;
				}

				// Save the object's boosts.
				if( obj->SaveBoosts( lptlSQLRequests, GetID() ) ){
					boDBError = TRUE;
				}

        
				// If the object is shared.
				if( !obj->IsUnique() ){
					// Re-set the flags to continue playing.
					obj->SetFlag( __FLAG_CHARGES, 1 );
				}

			}
		}
		tradeItemContainer->UnlockAndReleaseList();
		m_TradeMgr2.GetCLock()->Unlock();
	}





	backpack->Unlock();

    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Saving equipment"
    LOG_

	/////////////////////////////////////////////////////////////////////////////////////
	// Then save equipped objects
	{
		int j;		
		
        for(j = 0; j < EQUIP_POSITIONS; j++){
            int nEquipPos = j + 1;
			
			// If item is equipped
			Objects *obj = static_cast< Objects *>( equipped[j] );
			if( obj != NULL ){
                // If object is equipped in both hands.
                if( j == weapon_right && equipped[ weapon_left ] == equipped[ weapon_right ] ){
                    nEquipPos = two_hands + 1;
                }

                if(!( j == weapon_left && equipped[ weapon_left ] == equipped[ weapon_right ] ) ){
				    // If unit name ID could be found
				    if( Unit::GetNameFromID( obj->GetStaticReference(), (LPTSTR)(LPCTSTR)lpszName, U_OBJECT ) ){
					    // Insert new object into PlayerItems table
					    csQuery.Format( 
						    "INSERT INTO PlayerItems( ObjID, OwnerID, EquipPos, ObjType, Qty ) VALUES ( "
						    "%u,"
						    "%u,"
						    "%u,"
						    "'%s',"
						    "%u"
                            ")",
						    obj->GetID(),
						    dwUserID,
						    nEquipPos,
						    lpszName,
                            obj->GetQty()
					    );
					    
					    ADD_QUERY
				    
					    // Then save the object's specific flags
					    if( obj->SaveFlags( lptlSQLRequests, GetID() ) ){
						    boDBError = TRUE;
					    }
					    // Save the object's boosts.
					    if( obj->SaveBoosts( lptlSQLRequests, GetID() ) ){
						    boDBError = TRUE;
					    }
				    }				
                }
			}
		}
	}


    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Saving chest"
    LOG_

	/////////////////////////////////////////////////////////////////////////////////////
	// Save user chest

	// Begin by saving the chest
	TemplateList<Objects> *tlChestList = chest->LockAndGetList();

	tlChestList->ToHead();
	while( tlChestList->QueryNext() && !boDBError ){
		Objects *obj = tlChestList->Object();
       
		// If the unit name ID could be found
		if( Unit::GetNameFromID( obj->GetStaticReference(), (LPTSTR)(LPCTSTR)lpszName, U_OBJECT ) ){
			// Insert new object into PlayerItems table
			csQuery.Format( 
				"INSERT INTO ChestItems( ObjID, OwnerID, ObjType, Qty ) VALUES ( "
				"%u,"
				"%u,"
				"'%s',"
                "%u"
				" )",
				obj->GetID(),
				dwUserID,					
				lpszName,
                obj->GetQty()
			);

			ADD_QUERY
			
            // If the object is shared.
            if( !obj->IsUnique() ){
                // Remove the charges flag to avoid cluttering the database.
                obj->RemoveFlag( __FLAG_CHARGES );
            }


			// Then save the object's specific flags.
			if( obj->SaveFlags( lptlSQLRequests, GetID() ) ){
				boDBError = TRUE;
			}

			// Save the object's boosts.
			if( obj->SaveBoosts( lptlSQLRequests, GetID() ) ){
				boDBError = TRUE;
			}

            
            // If the object is shared.
            if( !obj->IsUnique() ){
                // Re-set the flags to continue playing.
                obj->SetFlag( __FLAG_CHARGES, 1 );
            }

		}
	}
	chest->UnlockAndReleaseList();


    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Saving skills"
    LOG_
	
	/////////////////////////////////////////////////////////////////////////////////////
	// Save user skills
	{
		csQuery.Format( "DELETE FROM PlayerSkills WHERE OwnerID=%u", dwUserID );

		ADD_QUERY
		
		for(i = 0; i < NB_SKILL_HOOKS; i++){
			tlusSkills[i].Lock();
			tlusSkills[i].ToHead();
			while( tlusSkills[i].QueryNext() && !boDBError ){
				LPUSER_SKILL lpusUserSkill = tlusSkills[i].Object();

                _LOG_DEBUG
                    LOG_DEBUG_LVL4,
                    "Character %s (ID %u) saving skill %u with %u pnts.",
                    (LPCTSTR)GetName( _DEFAULT_LNG ),
                    dwUserID,
                    lpusUserSkill->GetSkillID(),
                    lpusUserSkill->GetTrueSkillPnts()
                LOG_

				// Then save the user-skill.
				csQuery.Format( 
					"INSERT INTO PlayerSkills( OwnerID, SkillID, SkillPnts ) VALUES ( "
					"%u,"	// OwnerID.
					"%u,"	// SkillID.
					"%u"	// SkillPnts.	
					" )",
					dwUserID,
					lpusUserSkill->GetSkillID(),
					lpusUserSkill->GetTrueSkillPnts()
				);

				ADD_QUERY
			}
			tlusSkills[i].Unlock();
		}				

	}
    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Saving effects"
    LOG_

	// Save effects
	if( SaveEffects( lptlSQLRequests, GetID() ) ){
		boDBError = TRUE;
	}
    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Saving boosts"
    LOG_

	// Save the boosts
	if( SaveBoosts( lptlSQLRequests, GetID() ) ){
		boDBError = TRUE;
	}

    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Saving spells"
    LOG_
	//////////////////////////////////////////////////////////////////////////////////////////
	// Then save the player's spells.
	{
		LPUSER_SKILL lpUserSkill;
		tlusSpells.Lock();
		tlusSpells.ToHead();

		csQuery.Format( "DELETE FROM PlayerSpells WHERE OwnerID=%u", dwUserID );

		ADD_QUERY
		while( tlusSpells.QueryNext() && !boDBError ){
			lpUserSkill = tlusSpells.Object();

			csQuery.Format(
				"INSERT INTO PlayerSpells( OwnerID, SpellID ) VALUES ( "
				"%u,"
				"%u"
				" )",
				dwUserID,
				lpUserSkill->GetSkillID()
			);
			
			ADD_QUERY
		}


		tlusSpells.Unlock();
	}		

    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Saving flags"
    LOG_

	// Save the user's flags.
	if( SaveFlags( lptlSQLRequests, GetID() ) ){
		boDBError = TRUE;
	}

    TRACE( "\r\nnKarma=%d.", nKarma );

    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Saving character data."
    LOG_

    CString csName = GetTrueName();
    csName.TrimRight();
    csName.TrimLeft();
    SetName( csName );

    DWORD moveExhaust = 0, mentalExhaust = 0, attackExhaust = 0;
    
    DWORD curRound = TFCMAIN::GetRound();

    EXHAUST exhaust = GetExhaust();
    if( exhaust.move > curRound )
	{
        moveExhaust = ( exhaust.move - curRound ) * 50;
    }
    if( exhaust.mental > curRound )
	{
        mentalExhaust = ( exhaust.mental - curRound ) * 50;
    }
    if( exhaust.attack > curRound )
	{
        attackExhaust = ( exhaust.attack - curRound ) * 50;
    }

	// Build the primary UPDATE query
	csQuery.Format(
		"UPDATE PlayingCharacters SET "
		"PlayerName='%s',"
        "Strength=%u,"
		"Endurance=%u,"
		"Agility=%u,"
		"Intelligence=%u,"
		//"WillPower=%u,"
		"Wisdom=%u,"
		"Luck=%u,"
		"AttackSkill=%u,"
		"DodgeSkill=%u,"
		"XP=%f,"
		"CurrentLevel=%u,"
		"CurrentHP=%u,"
		"MaxHP=%u,"
		"CurrentMana=%u,"
		"MaxMana=%u,"
		"Gold=%u,"
		"wlX=%u,"
		"wlY=%u,"
		"wlWorld=%u,"
		"SkillPnts=%u,"
		"StatPnts=%u,"
		"Corpse=%u,"
		"Appearance=%u,"
        "Karma=%d,"
        "Gender=%u,"
        "ListingTitle='%s',"
        "ListingMisc='%s',"
        "MoveExhaust=%u,"
        "MentalExhaust=%u,"
        "AttackExhaust=%u,"
		// asteryth guild
		"GuildName='%s'," // BLBLBL Update GuildName field in SaveCharacter
		"GuildID=%i, "
		"GuildChestAccess=%i, "
		// asteryth pvp ranking
		"TotalDeathNumber=%i, "
		"TotalKillNumber=%i, "
		"CurrentDeathNumber=%i, "
		"CurrentKillNumber=%i, "
		"BestSerieMurder=%i, "
		"CurrentSerieMurder=%i, "
		"CurrentPvpPoint=%i "
		"WHERE UserID=%u",

        (LPCTSTR)GetTrueName().c_str(),
		GetTrueSTR(),
		GetTrueEND(),
		GetTrueAGI(),
		GetTrueINT(),
		//GetTrueWIL(),
		GetTrueWIS(),
		GetTrueLCK(),			
		GetTrueATTACK(),
		GetTrueDODGE(),
		(double)GetXP(),
		GetLevel(),
		GetHP(),
		GetTrueMaxHP(),
		GetMana(),
		GetTrueMaxMana(),
		GetGold(),
		GetWL().X,
		GetWL().Y,
		GetWL().world,
		wNbSkillPnts,
		wNbStatPnts,
		Corpse,
		Appearance,
        nKarma,
        bGender,
        (LPCTSTR)csListingTitle.c_str(),
        (LPCTSTR)csListingMisc.c_str(),
        moveExhaust,
        mentalExhaust,
        attackExhaust,
		// asteryth guild
		//(LPCTSTR)csGuildName, // BLBLBL // asteryth modifié pour avoir un get/set
		GetGuildName().c_str(),
		GetGuildID(),
		GetGuildChestAccess(),
		// asteryth pvp ranking
		GetTotalDeathNumber(),
		GetTotalKillNumber(),
		GetCurrentDeathNumber(),
		GetCurrentKillNumber(),
		GetBestSerieMurder(),
		GetCurrentSerieMurder(),
		GetCurrentPvpPoint(),
		GetID()
	);

	ADD_QUERY

	ODBCCharAsyncSave.Lock();//BLBLBL je tente de remettre un lock ICI pour éviter les cas de double sauvegarde de personnages
	                         // notamment en cas où un joueur ramasse un objet pendant sa sauvegarde automatique (ça le fait planter)
    if( boCallback ){
        _LOG_DEBUG
            LOG_DEBUG_HIGH,
            "Sending batch saving with callback"
        LOG_
        
        _LOG_DEBUG    
            LOG_DEBUG_LVL1,
            "Starting saving character %s. (callback)",
            (LPCTSTR)GetTrueName()
        LOG_

        ODBCCharAsyncSave.SendBatchRequest( lptlSQLRequests, DataSaveCallback, this , "CharAsyncSave");
    }else{
        _LOG_DEBUG
            LOG_DEBUG_HIGH,
            "Sending batch saving without callback"
        LOG_
        _LOG_DEBUG    
            LOG_DEBUG_LVL1,
            "Starting saving character %s. (no-callback)",
            (LPCTSTR)GetTrueName()
        LOG_

		ODBCCharAsyncSave.SendBatchRequest( lptlSQLRequests, NULL, this ,"CharAsyncSave");
    }
	ODBCCharAsyncSave.Unlock();

    Unlock();
	boSavingOnProgress=FALSE;//BLBLBL on indique que la sauvegarde du personnage est terminée pour permettre à nouveau de pouvoir sauvegarder.
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Load character specific structures and defines.
//
#define FETCH_BYTE( Row )	ODBCChar.GetBYTE( Row, &bTemp );
#define FETCH_WORD( Row )	ODBCCharRead.GetWORD( Row, &wTemp ); TRACE( ".%u", wTemp );
#define FETCH_DWORD( Row )  ODBCCharRead.GetDWORD( Row, &dwTemp ); TRACE( ".%u", dwTemp );
#define FETCH_SWORD( Row )  ODBCCharRead.GetSWORD( Row, &sTemp ); TRACE( ".%d", sTemp );
#define FETCH_SDWORD( Row ) ODBCCharRead.GetSDWORD( Row, &lTemp ); TRACE( ".%d", lTemp );

typedef struct _LOADED_ITEM{
	BYTE	bEquipPos;
	DWORD	dwObjID;
    DWORD   dwQty;
	BYTE	lpszObjType[ 50 ];
} LOADED_ITEM;

//////////////////////////////////////////////////////////////////////////////////////////
int Character::LoadCharacter
//////////////////////////////////////////////////////////////////////////////////////////
// Loads a character.
// 
(
 CString csName // The character name to load.
)
// Return: int, unused.
//////////////////////////////////////////////////////////////////////////////////////////
{
    gold = 0;

	Players *pl = (Players *)ThisPlayer;
    if( pl == NULL )
	{
        return 6;
    }

    TraceExhaust();

    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Locking ODBC"
    LOG_
	CString csQuery;

#ifdef MSSQLSERVER
	csQuery.Format( "SELECT TOP 1 "//BLBLBL 05/01/2011
#else*/
	csQuery.Format( "SELECT "//BLBLBL 05/01/2011
#endif
        "UserID,"
        "AccountName,"
        "wlX,"
        "wlY,"
        "wlWorld,"
        "nClass,"
        "CurrentHP,"
        "MaxHP,"
        "CurrentMana,"
        "MaxMana,"
        "Strength,"
        "Endurance,"
        "Agility,"
        "Intelligence,"
        //"WillPower,"
        "Wisdom,"
        "CurrentLevel,"
        "AttackSkill,"
        "DodgeSkill,"
        "Gold,"
        "Appearance,"
        "Corpse,"
        "XP,"
        "StatPnts,"
        "SkillPnts,"
        "Karma,"
        "Gender,"
        "ListingTitle,"
        "ListingMisc,"
        "MoveExhaust,"
        "MentalExhaust,"
        "AttackExhaust,"
		"Luck,"
		// asteryth guild
		"GuildName," // BLBLBL Champs GuildName en 33eme position dans la requete
		"GuildID,"
		"GuildChestAccess,"
		// asteryth pvp ranking
		"TotalDeathNumber,"
		"TotalKillNumber,"
		"CurrentDeathNumber,"
		"CurrentKillNumber,"
		"BestSerieMurder,"
		"CurrentSerieMurder,"
		"CurrentPvpPoint"
#ifdef MSSQLSERVER
	        " FROM PlayingCharacters WHERE PlayerName='%s'", (LPCTSTR)csName );
#else
	        " FROM PlayingCharacters WHERE PlayerName='%s' LIMIT 1", (LPCTSTR)csName );
#endif

	// Lock the ODBC connection
	ODBCCharRead.Lock();
	ODBCCharRead.SendRequest( (LPCTSTR)csQuery );
    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Fetching data"
    LOG_

	// If user was fetched, it exists
	if( ODBCCharRead.Fetch() )
	{
		char lpszUserName[20];

        WORD	wTemp;
		DWORD	dwTemp;
		double  dblTemp;
 //       short   sTemp;
        long    lTemp;

        FETCH_DWORD( DB_ID );
		SetID( dwTemp );

		// Get the binded user name.
		ODBCCharRead.GetString( DB_AccountName, lpszUserName, 20 );

        _LOG_DEBUG
            LOG_DEBUG_HIGH,
            "Got user name"
        LOG_

        TRACE( "..!%s!..", lpszUserName );
		// If the case insensitive account name isn't the same, do not load player.
		if( CMP( lpszUserName, (LPCTSTR)pl->GetAccount() ) == 0 )
		{
//			SetStaticFlagsReference(this);
        _LOG_DEBUG
            LOG_DEBUG_HIGH,
            "Starting data fetching"
        LOG_
    
			WorldPos wlPos;
            DWORD dwGold;
			
			FETCH_DWORD( DB_wlX );
				wlPos.X = dwTemp;
			FETCH_DWORD( DB_wlY );
				wlPos.Y = dwTemp;
			FETCH_DWORD( DB_wlWorld );
				wlPos.world = dwTemp;
            SetWL(wlPos);            

			FETCH_DWORD( DB_CurrentHP );
				SetHP( dwTemp, false );
			FETCH_DWORD( DB_MaxHP );
				SetMaxHP( dwTemp );
			FETCH_WORD( DB_CurrentMana );
				SetMana( wTemp );
			FETCH_WORD( DB_MaxMana );
				SetMaxMana( wTemp );
//	FETCH_WORD( DB_CurrentFaith );
//		SetFaith( wTemp );
//	FETCH_WORD( DB_MaxFaith );
//		SetMaxFaith( wTemp );
            
            FETCH_WORD( DB_Strength );
				SetSTR( wTemp );
			FETCH_WORD( DB_Endurance );
				SetEND( wTemp );
			FETCH_WORD( DB_Agility );
				SetAGI( wTemp );
			FETCH_WORD( DB_Intelligence );
				SetINT( wTemp );
			FETCH_WORD( DB_Wisdom );
				SetWIS( wTemp );

			FETCH_WORD( DB_Level );
				SetLevel( wTemp );

			FETCH_WORD( DB_AttackSkill );
				SetATTACK( wTemp );
			FETCH_WORD( DB_DodgeSkill );
				SetDODGE( wTemp );

			FETCH_DWORD( DB_Gold );
				dwGold = dwTemp;

			FETCH_WORD( DB_Appearance );
				Appearance = wTemp;
			FETCH_WORD( DB_Corpse );
				Corpse = wTemp;
			
			ODBCCharRead.GetDouble( DB_XP, &dblTemp );
			SetXP( (uint64_t)dblTemp );//signed __int64
            TRACE( ".%f", dblTemp );
		
			FETCH_WORD( DB_StatPnts );
				wNbStatPnts = wTemp;
            FETCH_WORD( DB_SkillPnts );
				wNbSkillPnts = wTemp;

			FETCH_WORD( DB_nClass );
				nClass = (BYTE)wTemp;
				
//			FETCH_WORD( DB_WarriorSkill );
//				ClassPoints[ WARRIOR ] = wTemp;	
//			FETCH_WORD( DB_MageSkill );
//				ClassPoints[ MAGE ] = wTemp;	
//			FETCH_WORD( DB_PriestSkill );
//				ClassPoints[ PRIEST ] = wTemp;	
//			FETCH_WORD( DB_ThiefSkill );
//				ClassPoints[ THIEF ] = wTemp;								


            FETCH_SDWORD( DB_Karma );
                nKarma = lTemp;

            TRACE( "\r\nFetching Karma, %d.", nKarma );

            FETCH_WORD( DB_Gender );
                bGender = static_cast< BYTE>( wTemp );

            
            char szListing[ 1024 ];
            szListing[ 0 ] = 0;
            ODBCCharRead.GetString( DB_ListingTitle, szListing, 1024 );
            //csListingTitle = szListing;
			SetTitle(szListing);

            szListing[ 0 ] = 0;
            ODBCCharRead.GetString( DB_ListingMisc, szListing, 1024 );
            //csListingMisc = szListing;
			SetListingMiscDesc(szListing);
            
            TraceExhaust();

            loadMoveExhaust = loadMentalExhaust = loadAttackExhaust = 0;

            FETCH_DWORD( DB_MoveExhaust );
            loadMoveExhaust = dwTemp;

            FETCH_DWORD( DB_MentalExhaust );
            loadMentalExhaust = dwTemp;

            FETCH_DWORD( DB_AttackExhaust );
            loadAttackExhaust = dwTemp;            

			FETCH_WORD( DB_Luck );
			SetLCK( wTemp );

			// asteryth guild
			// BLBLBL Guild Load start
			szListing[ 0 ] = 0;
            ODBCCharRead.GetString( DB_GuildName, szListing, 1024 );
            //csGuildName = szListing;
			SetGuildName(szListing);

			FETCH_SDWORD( DB_GuildID );
				SetGuildID( lTemp );

			FETCH_SDWORD( DB_GuildChestAccess );
				SetGuildChestAccess( lTemp );
			//_LOG_DEBUG LOG_ALWAYS, "DB GUILD CHEST ACCESS %i", lTemp LOG_

			// asteryth pvp ranking
			FETCH_SDWORD( DB_TotalDeathNumber );
				SetTotalDeathNumber( lTemp );

			FETCH_SDWORD( DB_TotalKillNumber );
				SetTotalKillNumber( lTemp );

			FETCH_SDWORD( DB_CurrentDeathNumber );
				SetCurrentDeathNumber( lTemp );

			FETCH_SDWORD( DB_CurrentKillNumber );
				SetCurrentKillNumber( lTemp );

			FETCH_SDWORD( DB_BestSerieMurder );
				SetBestSerieMurder( lTemp );

			FETCH_SDWORD( DB_CurrentSerieMurder );
				SetCurrentSerieMurder( lTemp );

			FETCH_SDWORD( DB_CurrentPvpPoint );
				SetCurrentPvpPoint( lTemp );



			TRACE( "\r\nLoaded position %u %u %u.", wlPos.X, wlPos.Y, wlPos.world );			            

			// close previous fetch
			ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

            TraceExhaust();

            _LOG_DEBUG
                LOG_DEBUG_HIGH,
                "Loading flags"
            LOG_

			//////////////////////////////////////////////////////////////////////////////////////////			
			// Load the user flags.
			LoadFlags( ODBCCharRead, GetID() );            

            if( ViewFlag( __FLAG_LIGHT_RESIST ) == 0 ){
                SetLightResist( 5000 );
            };

			// close previous fetch
			ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

			//////////////////////////////////////////////////////////////////////////////////////////			
			// Load user items.
			{				
				DWORD dwTempID;



				//////////////////////////////////////////////////////////////////////////////////////////
				// steph ajout de INT
				//////////////////////////////////////////////////////////////////////////////////////////
				const INT DB_ObjID =		1;
                const INT DB_EquipPos =		2;
				const INT DB_ObjType =		3;
                const INT DB_Qty =          4;




				//Unit *lpuItem;
				LOADED_ITEM *lpLoadedItem;
				
				// Temporary list which will contain the loaded items.				
				TemplateList < LOADED_ITEM > tlLoadedItems;

                _LOG_DEBUG
                    LOG_DEBUG_HIGH,
                    "Fetching objects"
                LOG_

				csQuery.Format( "SELECT ObjID, EquipPos, ObjType, Qty FROM PlayerItems WHERE OwnerID=%u", GetID() );

				if( ODBCCharRead.SendRequest( (LPCTSTR)csQuery ) )
				{
					// Scroll through all fetched records.
					while( ODBCCharRead.Fetch() )
					{						
						lpLoadedItem = new LOADED_ITEM;

                        ODBCCharRead.GetDWORD ( DB_ObjID,    &lpLoadedItem->dwObjID );
                        ODBCCharRead.GetBYTE  ( DB_EquipPos, &lpLoadedItem->bEquipPos );
						ODBCCharRead.GetString( DB_ObjType,  (LPTSTR)lpLoadedItem->lpszObjType, 50 );
                        ODBCCharRead.GetDWORD ( DB_Qty,      &lpLoadedItem->dwQty );
                        if( lpLoadedItem->dwQty == 0 )
						{
                            lpLoadedItem->dwQty = 1;
                        }

						// Add them to the loaded items list.
						tlLoadedItems.AddToTail( lpLoadedItem );
					}

					// close the previous fetch operation
					ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

                    int w;
                    for( w = 0; w < EQUIP_POSITIONS; w++ )
					{
                        equipped[ w ] = 0;                        
                    }


					// Scroll through the loaded items
					tlLoadedItems.ToHead();
					while( tlLoadedItems.QueryNext() )
					{
						lpLoadedItem = tlLoadedItems.Object();

                        Objects *lpuItem = new Objects();
                        
                        // If object could be created
                        if( lpuItem->Create( U_OBJECT, Unit::GetIDFromName( (LPCSTR)lpLoadedItem->lpszObjType, U_OBJECT, TRUE ) ) )
						{
                            
                            // Temporarly replace the unit's ID to load its flags, boosts and effects
                            dwTempID = lpuItem->GetID();
                            lpuItem->SetID( lpLoadedItem->dwObjID );
                            
                            lpuItem->SetQty( lpLoadedItem->dwQty );
                            
                            _item *itemStructure = NULL;
                            
                            lpuItem->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &itemStructure );
                            
                            int chargeValue = 0;
                            if( itemStructure != NULL && itemStructure->magic.charges < 0 ){
                                chargeValue = -1;
                            }
                            
                            // Flush the object's CHARGE flag created by ObjectStructure
                            // If the object has flags, they will be loaded.
                            lpuItem->SetFlag( __FLAG_CHARGES, chargeValue );

							// Load the object's flags and boosts
							lpuItem->LoadFlags( ODBCCharRead, GetID() );							
							ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

                            // If the item is not unique, set its charge to 1 since
                            // it wasn't saved to avoid cluttering the database.
                            if( !lpuItem->IsUnique() ){
                                lpuItem->SetFlag( __FLAG_CHARGES, 1 );
                            }

							// Load the object's boosts
							lpuItem->LoadBoosts( ODBCCharRead, GetID() );
							ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

                            // Reset the item's ID to its newly assigned one.
							lpuItem->SetID( dwTempID );

							// If item is in the backpack;
							if( lpLoadedItem->bEquipPos == 0 )
							{
								// Add it to the backpack.
                                AddToBackpack( lpuItem );
							}
							else if( lpLoadedItem->bEquipPos <= EQUIP_POSITIONS )
							{
                                if( lpLoadedItem->bEquipPos - 1 == two_hands )
								{                                    
                                    if( equipped[ weapon_right ] != NULL )
									{
                                        equipped[ weapon_right ]->DeleteUnit();
                                    }
                                    if( equipped[ weapon_left ] != equipped[ weapon_right ] && 
                                        equipped[ weapon_left ] != NULL )
									{
                                        equipped[ weapon_left ]->DeleteUnit();
                                    }
                                    equipped[ weapon_right ] = equipped[ weapon_left ] = lpuItem;

                                }
								else
								{
    								// otherwise add it to its equip position.
	    							if( equipped[ lpLoadedItem->bEquipPos - 1 ] != NULL )
									{
		    							// Crush current equipped item.
			    						equipped[ lpLoadedItem->bEquipPos - 1 ]->DeleteUnit();
				    				}
    
	    							equipped[ lpLoadedItem->bEquipPos - 1 ] = lpuItem;
                                }
							}
						}
						else
						{
							lpuItem->DeleteUnit();
						}
						tlLoadedItems.DeleteAbsolute();
                        //tlLoadedItems.Object()->DeleteUnit();
                        //tlLoadedItems.Remove();
					}
				}
				// close previous fetch operation.
				ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close
			}
            TFCPacket sending;
            packet_equiped( sending );
            SendPlayerMessage( sending );
            
            // Now that all 'gold' items have been loaded, set the true gold.
            SetGold( dwGold, false );
			

			//////////////////////////////////////////////////////////////////////////////////////////			
			// Load user's chest items.
			{				
				DWORD dwTempID;



				//////////////////////////////////////////////////////////////////////////////////////////
				// steph ajout de INT
				//////////////////////////////////////////////////////////////////////////////////////////
				const INT DB_ObjID =		1;
                const INT DB_EquipPos =		2;
				const INT DB_ObjType =		3;
                const INT DB_Qty =          4;



				LOADED_ITEM *lpLoadedItem;
				
				// Temporary list which will contain the loaded items.				
				TemplateList < LOADED_ITEM > tlLoadedItems;

                _LOG_DEBUG
                    LOG_DEBUG_HIGH,
                    "Fetching chest objects"
                LOG_

				csQuery.Format( "SELECT ObjID, 0, ObjType, Qty FROM ChestItems WHERE OwnerID=%u", GetID() );

				if( ODBCCharRead.SendRequest( (LPCTSTR)csQuery ) ){
					// Scroll through all fetched records.
					while( ODBCCharRead.Fetch() ){						

						lpLoadedItem = new LOADED_ITEM;


                        ODBCCharRead.GetDWORD ( DB_ObjID,    &lpLoadedItem->dwObjID );
                        lpLoadedItem->bEquipPos = 0;
						ODBCCharRead.GetString( DB_ObjType,  (LPTSTR)lpLoadedItem->lpszObjType, 50 );
                        ODBCCharRead.GetDWORD ( DB_Qty,      &lpLoadedItem->dwQty );
                        if( lpLoadedItem->dwQty == 0 ){
                            lpLoadedItem->dwQty = 1;
                        }

						// Add them to the loaded items list.
						tlLoadedItems.AddToTail( lpLoadedItem );
					}

					// close the previous fetch operation
					ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

					// Scroll through the loaded items
					tlLoadedItems.ToHead();
					while( tlLoadedItems.QueryNext() ){
						lpLoadedItem = tlLoadedItems.Object();

                        Objects *lpuItem = new Objects();
                        
                        // If object could be created
                        if( lpuItem->Create( U_OBJECT, Unit::GetIDFromName( (LPCSTR)lpLoadedItem->lpszObjType, U_OBJECT, TRUE ) ) ){
                            
                            // Temporarly replace the unit's ID to load its flags, boosts and effects
                            dwTempID = lpuItem->GetID();
                            lpuItem->SetID( lpLoadedItem->dwObjID );
                            
                            lpuItem->SetQty( lpLoadedItem->dwQty );
                            
                            _item *itemStructure = NULL;
                            
                            lpuItem->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &itemStructure );
                            
                            int chargeValue = 0;
                            if( itemStructure != NULL && itemStructure->magic.charges < 0 ){
                                chargeValue = -1;
                            }
                            
                            // Flush the object's CHARGE flag created by ObjectStructure
                            // If the object has flags, they will be loaded.
                            lpuItem->SetFlag( __FLAG_CHARGES, chargeValue );

							// Load the object's flags and boosts
							lpuItem->LoadFlags( ODBCCharRead, GetID() );							
							ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

                            // If the item is not unique, set its charge to 1 since
                            // it wasn't saved to avoid cluttering the database.
                            if( !lpuItem->IsUnique() ){
                                lpuItem->SetFlag( __FLAG_CHARGES, 1 );
                            }

							// Load the object's boosts
							lpuItem->LoadBoosts( ODBCCharRead, GetID() );
							ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

                            // Reset the item's ID to its newly assigned one.
							lpuItem->SetID( dwTempID );

                            //Put item into chest.
							chest->Put( lpuItem, true );
						}else{
							lpuItem->DeleteUnit();
						}
						tlLoadedItems.DeleteAbsolute();
					}
				}
				// close previous fetch operation.
				ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close
			}
			
			//////////////////////////////////////////////////////////////////////////////////
			// Load user skills
			{



				//////////////////////////////////////////////////////////////////////////////////////////
				// steph ajout de INT
				//////////////////////////////////////////////////////////////////////////////////////////
				const INT DB_SkillID		= 1;
				const INT DB_SKSkillPnts	= 2;
				


				csQuery.Format( "SELECT SkillID, SkillPnts FROM PlayerSkills WHERE OwnerID=%u ORDER BY SkillID", GetID() ); // BLBLL Ajouté ORDER BY SkillID pour que les skills soient toujours executés dans le meme ordre chez tous les joueurs.

                _LOG_DEBUG
                    LOG_DEBUG_HIGH,
                    "Fetching skills"
                LOG_

				if( ODBCCharRead.SendRequest( (LPCTSTR)csQuery ) )
				{
					
					// Scroll through all fetched records.
					while( ODBCCharRead.Fetch() )
					{																		
						WORD wSkillID = 0;
						WORD wSkillPnts = 0;
                        WORD wSkillPntsBackup = wNbSkillPnts;

						// Fetch skill data.
						ODBCCharRead.GetWORD( DB_SkillID, &wSkillID );
						ODBCCharRead.GetWORD( DB_SKSkillPnts, &wSkillPnts );
						                                                                        
                        // Give the maximum skill points to make sure the loaded skill is learned.
                        wNbSkillPnts = 0xFFFF;
                        CString errMsg;
						LPUSER_SKILL lpusUserSkill = LearnSkill( wSkillID, wSkillPnts, false, errMsg );

						// If skill could be trained.
						if( lpusUserSkill )
						{
							// cheat a little.. j/k, set skill points.
							lpusUserSkill->SetSkillPnts( wSkillPnts );
						}
                        if( lpusUserSkill != NULL ){
                            _LOG_DEBUG
                                LOG_DEBUG_LVL4,
                                "Character %s (ID %u) succesfully loaded skill %u with %u pnts.",
                                (LPCTSTR)GetName( _DEFAULT_LNG ),
                                GetID(),
                                wSkillID,
                                wSkillPnts
                            LOG_
                        }else{
                            _LOG_DEBUG
                                LOG_DEBUG_LVL1,
                                "Character %s (ID %u) could NOT load skill %u with %u pnts! ErrMsg=%s",
                                (LPCTSTR)GetName( _DEFAULT_LNG ),
                                GetID(),
                                wSkillID,
                                wSkillPnts,
                                (LPCTSTR)errMsg
                            LOG_
                        }


                        // Restore skill points.
                        wNbSkillPnts = wSkillPntsBackup;
					}
				}

                LPUSER_SKILL lpUserSkill = GetSkill( __SKILL_ARCHERY );
                // If the user does not have the archery skill
                if( lpUserSkill == NULL ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL3,
                        "Skill Archery(%u) was not found on character %s (ID %u). Creating default skill value.",
                        __SKILL_ARCHERY,
                        (LPCTSTR)GetName( _DEFAULT_LNG ),
                        GetID()
                    LOG_
                    
                    CString errMsg;
                    WORD wSkillPntsBackup = wNbSkillPnts;
                    wNbSkillPnts = 0xFFFF;
                    // Learn the archery skill at 15 points.
					LPUSER_SKILL lpusUserSkill = LearnSkill( __SKILL_ARCHERY, 15, false, errMsg );
					// If skill could be trained.
					if( lpusUserSkill )
					{
						// cheat a little.. j/k, set skill points.
						lpusUserSkill->SetSkillPnts( 15 );
                    }else{
                        _LOG_DEBUG
                            LOG_CRIT_ERRORS,
                            "Character %s (ID %u) could NOT create archery skill! ErrMsg=%s",
                            (LPCTSTR)GetName( _DEFAULT_LNG ),
                            GetID(),
                            (LPCTSTR)errMsg
                        LOG_
                    }
                    wNbSkillPnts = wSkillPntsBackup;
                }


			}

			// close previous fetch operation
			ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

			//////////////////////////////////////////////////////////////////////////////////////////
			// Then load the user spells.
			{


				//////////////////////////////////////////////////////////////////////////////////////////
				// steph ajout de INT
				//////////////////////////////////////////////////////////////////////////////////////////
				const INT DB_SpellID	= 1;
				const INT DB_SpellPnts	= 2;



				LPUSER_SKILL lpSkill;

				// Flush current spell list.
				tlusSpells.ToHead();
				while( tlusSpells.QueryNext() )
				{
					tlusSpells.DeleteAbsolute();
				}
				
				csQuery.Format( "SELECT SpellID FROM PlayerSpells WHERE OwnerID=%u", GetID() );

				if( ODBCCharRead.SendRequest( (LPCTSTR)csQuery ) )
				{			
					
					// Scroll through all fetched records.
					while( ODBCCharRead.Fetch() )
					{																		
						lpSkill = new USER_SKILL;
						/*ZeroMemory*/bzero( lpSkill, sizeof( USER_SKILL ) );
						
						DWORD dwSkillID = 0;
                        ODBCCharRead.GetDWORD( DB_SpellID, &dwSkillID );
						lpSkill->SetSkillPnts( 0 );
                        lpSkill->SetSkillID  ( dwSkillID );
												
						tlusSpells.AddToTail( lpSkill );
					}
				}
			}
			// close previous fetch operation
			ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

			//////////////////////////////////////////////////////////////////////////////////////////			
			// Load the spell effects.
			LoadEffects( ODBCCharRead, GetID() );
			ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

			//////////////////////////////////////////////////////////////////////////////////////////
			// Load the boosts
			LoadBoosts( ODBCCharRead, GetID() );
			
            _LOG_DEBUG
                LOG_DEBUG_HIGH,
                "Ending LoadCharacter1"
            LOG_
            
            //ODBCCharRead.Cancel();
	
			ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close
			ODBCCharRead.Unlock();

			BoostFormula bfChestEncumbrance;
			BOOL boFormulaHaveErrors = !(bfChestEncumbrance.SetFormula( theApp.csChestEncumbranceBoostFormula ));
			chest->SetMaxWeight( bfChestEncumbrance.GetBoost( this ) );

			if ( boFormulaHaveErrors ) {
				_LOG_DEBUG
					LOG_CRIT_ERRORS,
					"Chest encumbrance formula have errors in it. Chest will have 0 encumbrance. Triggered while loading player %s (acct %s)",
					(LPCTSTR)csName,
					(LPCTSTR)lpszUserName
				LOG_
			}
			
			return 0;
		}
		else
		{
			LPCTSTR strings[3] = {(LPCTSTR)pl->GetAccount(), (LPCTSTR)csName, (LPCTSTR)lpszUserName };
			// The user %1!s! tried to access the character %2!s! (property of %3!s!) 	
//			ReportError(__WARNING_NOT_ALLOWED_CHARACTER_ACCESS, 3, strings);					
            _LOG_DEBUG
                LOG_DEBUG_HIGH,
                "Ending LoadCharacter2"
            LOG_

			ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close
			ODBCCharRead.Unlock();

			return 10;
		}
	}

	ODBCCharRead.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close
	ODBCCharRead.Unlock();

    _LOG_DEBUG
        LOG_DEBUG_HIGH,
        "Ending LoadCharacter3"
    LOG_
    

	return 6;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Creates a new character, returns FALSE if it could not create a new character
BOOL Character::CreateCharacter(CString csName, LPBYTE lpbAnswers ){

	Players *pl = (Players *)ThisPlayer;
    if( pl == NULL ){
        return FALSE;
    }

	csName.TrimRight();
    csName.TrimLeft();

	CString csQuery;

#ifdef MSSQLSERVER
	csQuery.Format( "SELECT TOP 1 UserID FROM PlayingCharacters WHERE PlayerName='%s'", (LPCTSTR)csName );//BLBLBL 05/01/2011
#else
	csQuery.Format( "SELECT UserID FROM PlayingCharacters WHERE PlayerName='%s' LIMIT 1", (LPCTSTR)csName );//BLBLBL 05/01/2011
#endif
	ODBCCharWrite.Lock();
	ODBCCharWrite.SendRequest( (LPCTSTR)csQuery );
	
	// If player doesn't already exist
	if( !ODBCCharWrite.Fetch() ){
		// Cancel last fetch operation
		ODBCCharWrite.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

        _LOG_PC
            LOG_MISC_1,
            "Created player '%s' for user %s.",
            (LPCTSTR)csName,
            (LPCTSTR)(pl->GetFullAccountName())
        LOG_

		//backpack->AnnihilateList();	        
        backpack->ToHead();
        while( backpack->QueryNext() )
		{
            backpack->Object()->DeleteUnit();
            backpack->Remove();
        }

		chest->ResetContainer();
        
		// Assigns a valid new ID to this character.
		AssignValidID( this );//BLBLBL si on met l'autoincrément dans la base faudra penser
							  //à déplacer cette partie APRES avoir inséré le personnage, 
							  //sinon on peut pas connaitre l'ID affecté par la BDD

        char szAccount[ 1024 ];
        Players::QuotedAccount( szAccount, pl->GetAccount() );

		SetLevel(1);

        SetName(csName);		
		Corpse = 1;

        nKarma  = 0;            // neutral by default
	
        // Create a gem of destiny, its a *must*
        Objects *objNewObject = new Objects;
		TRACE( "..%u..", __OBJ_GEM_OF_DESTINY );
        if( objNewObject->Create( U_OBJECT, __OBJ_GEM_OF_DESTINY ) )
		{
			backpack->AddToTail( objNewObject );
		}else{
			objNewObject->DeleteUnit();
		}

        // Create all startup items on player.
        vector< string >::iterator k;
                    
        WORD wObjID;            
        vStartupItems.Lock();
        for( k = vStartupItems.begin(); k != vStartupItems.end(); k++ )
		{
            // If the object's numerical ID could be found.
            wObjID = Unit::GetIDFromName( (*k).c_str(), U_OBJECT, TRUE );
            if( wObjID != 0 ){
                objNewObject = new Objects;
                // Create this object.
                if( objNewObject->Create( U_OBJECT, wObjID ) )
				{
	        		backpack->AddToTail( objNewObject );
		        }else{
			        objNewObject->DeleteUnit();
		        }
            }
        }
        vStartupItems.Unlock();

		WORD wSkillPntsBackup = wNbSkillPnts;
        CString errMsg;
        wNbSkillPnts = 0xFFFF;
        
        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Creating skill Archery(%u) on character creation of %s (ID %u).",
            __SKILL_ARCHERY,
            (LPCTSTR)GetName( _DEFAULT_LNG ),
            GetID()
        LOG_

        LPUSER_SKILL lpusUserSkill = LearnSkill( __SKILL_ARCHERY, 15, false, errMsg );
		// If skill could be trained.
		if( lpusUserSkill )
		{
			// cheat a little.. j/k, set skill points.
			lpusUserSkill->SetSkillPnts( 15 );
		}

        wNbSkillPnts = wSkillPntsBackup;



		//////////////////////////////////////////////////////////////////////////////////////////
		// steph ajout de INT
		//////////////////////////////////////////////////////////////////////////////////////////
        const INT Warrior = 0;
        const INT Mage    = 1;
        const INT Thief   = 2;
        const INT Priest  = 3;
        const INT Normal  = 4;
		const INT NbQuestions = 4;



        int i;
        int nPnts = 0;

        // Since our players are way far from undeads.
        SetLightResist( 5000 );

        for( i = 0; i < 5; i++ )
		{
            nPnts += lpbAnswers[ i ];
        }            

        if( nPnts == NbQuestions )
		{                                
            nPnts = lpbAnswers[ 0 ];
            for( i = 1; i < 5; i++ ){
                if( lpbAnswers[ i ] > nPnts )
				{                        
                    Appearance = i;
                    TRACE( "\r\nNew appearance should be %u.", Appearance );
                    nPnts = lpbAnswers[ i ];
                }
            }

            // Male
            if( lpbAnswers[ 5 ] == GENDER_MALE )
			{
                SetGender( GENDER_MALE );
                Appearance = __PLAYER_PUPPET;
            }
			else 
            // Female    
            if( lpbAnswers[ 5 ] == GENDER_FEMALE )
			{
                SetGender( GENDER_FEMALE );
                Appearance = __PLAYER_FEMALE_PUPPET;
            }
			else
            // Default
            {
                SetGender( GENDER_MALE );
                Appearance = __PLAYER_PUPPET;
            }

            TRACE( "\r\nOfficial appearance should be %u.", Appearance );                

            bRollSTR = 0;
            bRollEND = 0;
            bRollINT = 0;
            bRollAGI = 0;    
            bRollWIL = 0;
            bRollWIS = 0;
            bRollLCK = 0;        

            // Set default (bonus) stats.
            for( i = 0; i < 5; i++ )
			{
                nPnts = lpbAnswers[ i ];
                switch( i ){
                case Warrior:
                    TRACE( "\r\nWarrior Points=%u.", nPnts );
                    bRollSTR += static_cast< DWORD >( 3.5 * nPnts );
                    bRollAGI += static_cast< DWORD >( 1.5 * nPnts );
                    bRollEND += static_cast< DWORD >( 3.5 * nPnts );
                    bRollINT += static_cast< DWORD >( 0.5 * nPnts );
                    bRollWIS += static_cast< DWORD >( 0.5 * nPnts );
                    bRollWIL += static_cast< DWORD >( 1.5 * nPnts );
                    bRollLCK += static_cast< DWORD >( 1.5 * nPnts );
                    break;
                case Mage:
                    TRACE( "\r\nMage Points=%u.", nPnts );
                    bRollSTR += static_cast< DWORD >( 0.5 * nPnts );
                    bRollAGI += static_cast< DWORD >( 1.5 * nPnts );
                    bRollEND += static_cast< DWORD >( 0.5 * nPnts );
                    bRollINT += static_cast< DWORD >( 3.5 * nPnts );
                    bRollWIS += static_cast< DWORD >( 1.5 * nPnts );
                    bRollWIL += static_cast< DWORD >( 3.5 * nPnts );
                    bRollLCK += static_cast< DWORD >( 1.5 * nPnts );
                    break;
                case Thief:
                    TRACE( "\r\nThief Points=%u.", nPnts );
                    bRollSTR += static_cast< DWORD >( 3.5 * nPnts );
                    bRollAGI += static_cast< DWORD >( 3.5 * nPnts );
                    bRollEND += static_cast< DWORD >( 1.5 * nPnts );
                    bRollINT += static_cast< DWORD >( 1.5 * nPnts );
                    bRollWIS += static_cast< DWORD >( 0.5 * nPnts );
                    bRollWIL += static_cast< DWORD >( 0.5 * nPnts );
                    bRollLCK += static_cast< DWORD >( 2.0 * nPnts );
                    break;
                case Priest:
                    TRACE( "\r\nPriest Points=%u.", nPnts );
                    bRollSTR += static_cast< DWORD >( 1.5 * nPnts );
                    bRollAGI += static_cast< DWORD >( 0.5 * nPnts );
                    bRollEND += static_cast< DWORD >( 1.5 * nPnts );
                    bRollINT += static_cast< DWORD >( 1.5 * nPnts );
                    bRollWIS += static_cast< DWORD >( 3.5 * nPnts );
                    bRollWIL += static_cast< DWORD >( 3.5 * nPnts );
                    bRollLCK += static_cast< DWORD >( 0.5 * nPnts );
                    break;
                case Normal:
                    TRACE( "\r\nNormal Points=%u.", nPnts );
                    bRollSTR += static_cast< DWORD >( 1.5 * nPnts );
                    bRollAGI += static_cast< DWORD >( 1.5 * nPnts );
                    bRollEND += static_cast< DWORD >( 1.5 * nPnts );
                    bRollINT += static_cast< DWORD >( 1.5 * nPnts );
                    bRollWIS += static_cast< DWORD >( 1.5 * nPnts );
                    bRollWIL += static_cast< DWORD >( 1.5 * nPnts );
                    bRollLCK += static_cast< DWORD >( 3.5 * nPnts );
                    break;
                }
            }
        }

        // Do a first roll of the stats
        roll_stats();

        TraceExhaust();

        // Build the INSERT query
		csQuery.Format(	    
    		"INSERT INTO PlayingCharacters ("
            "UserID,"//BLBLL A tester : virer ce champs et mettre un autoincrément dans la base.
	    	"PlayerName,"
            "AccountName,"
            "Strength,"
		    "Endurance,"
		    "Agility,"
		    "Intelligence,"
		    //"WillPower,"
		    "Wisdom,"
		    "Luck,"
		    "AttackSkill,"
		    "DodgeSkill,"
		    "XP,"
		    "CurrentLevel,"
		    "CurrentHP,"
		    "MaxHP,"
		    "CurrentMana,"
		    "MaxMana,"
		    "Gold,"
		    "wlX,"
		    "wlY,"
		    "wlWorld,"
		    "SkillPnts,"
		    "StatPnts,"
		    "Corpse,"
		    "Appearance,"
            "Karma,"
            "Gender,"
            "ListingTitle,"
            "ListingMisc,"
            "MoveExhaust,"
            "MentalExhaust,"
            "AttackExhaust"
            ")VALUES("
            "%u,"   //"UserID"//BLBLL A tester : virer ce champs et mettre un autoincrément dans la base.
	    	"'%s'," //"PlayerName,"
            "'%s'," //"AccountName,"
            "%u,"   //"Strength,"
		    "%u,"   //"Endurance,"
		    "%u,"   //"Agility,"
		    "%u,"   //"Intelligence,"
		    //"%u,"   //"WillPower,"
		    "%u,"   //"Wisdom,"
		    "%u,"   //"Luck,"
		    "%u,"   //"AttackSkill,"
		    "%u,"   //"DodgeSkill,"
		    "%f,"   //"XP,"
		    "%u,"   //"CurrentLevel,"
		    "%u,"   //"CurrentHP,"
		    "%u,"   //"MaxHP,"
		    "%u,"   //"CurrentMana,"
		    "%u,"   //"MaxMana,"
		    "%u,"   //"Gold,"
		    "%u,"   //"wlX,"
		    "%u,"   //"wlY,"
		    "%u,"   //"wlWorld,"
		    "%u,"   //"SkillPnts,"
		    "%u,"   //"StatPnts,"
		    "%u,"   //"Corpse,"
		    "%u,"   //"Appearance,"
            "%d,"   //"Karma,"
            "%u,"   //"Gender,"
            "'',"   //"ListingTitle,"
            "'',"   //"ListingMisc",
            "0,"    // MoveExhaust
            "0,"    // MentalExhaust
            "0)",   // AttackExhaust
            GetID(),//BLBLL A tester : virer ce champs et mettre un autoincrément dans la base.
            (LPCTSTR)GetTrueName(),
            (LPCTSTR)szAccount,
		    GetTrueSTR(),
		    GetTrueEND(),
		    GetTrueAGI(),
		    GetTrueINT(),
		    //GetTrueWIL(),
		    GetTrueWIS(),
		    //GetTrueLCK(),			
			100,//BLBLBL tout le monde doit avoir 100 en chance dès le départ !!!!
		    GetTrueATTACK(),
		    GetTrueDODGE(),
		    (double)GetXP(),
		    GetLevel(),
		    GetHP(),
		    GetTrueMaxHP(),
		    GetMana(),
		    GetTrueMaxMana(),
		    GetGold(),
		    GetWL().X,
		    GetWL().Y,
		    GetWL().world,
		    wNbSkillPnts,
		    wNbStatPnts,
		    Corpse,
		    Appearance,
            nKarma,
            bGender,
            (LPCTSTR)csListingTitle,
            (LPCTSTR)csListingMisc
	    );
		
		//_LOG_DEBUG LOG_ALWAYS, "CREATE REQUEST", csQuery LOG_
		//_LOG_DEBUG LOG_ALWAYS, "%s", csQuery LOG_
		//_LOG_DEBUG LOG_ALWAYS, "CREATE REQUEST", csQuery LOG_
		
        // If INSERT query was successful
		if(	ODBCCharWrite.SendRequest( (LPCTSTR)csQuery ) )
		{
    		// Commit data.
	    	ODBCCharWrite.Commit();

		    ODBCCharWrite.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close
		    ODBCCharWrite.Unlock();

            TraceExhaust();

            //AssignValidID( this );//BLBLBL si on a réussi à mettre l'autoincrément en place
									//il faut déplcer ici le AssignValidID déplacé cette partie 
									//APRES avoir inséré le personnage, sinon on peut pas connaitre 
									//l'ID affecté par la BDD

            return TRUE;
		}
	}

	ODBCCharWrite.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close
	ODBCCharWrite.Unlock();

	return FALSE;// character already exists!

}
/************************************************************************************/
// flushes a character, deletes everything (files and cie)
char Character::DeleteCharacter(CString ch_name, CString ch_account, BOOL Report)
{
	CString csQuery;
	char lpszUserName[20];
	BOOL boDeleteError = FALSE;
	DWORD dwID = 0;

	ODBCCharWrite.Lock();

#ifdef MSSQLSERVER
	csQuery.Format( "SELECT TOP 1 AccountName, UserID FROM PlayingCharacters WHERE PlayerName='%s'", (LPCTSTR)ch_name );//BLBLBL 05/01/2011
#else
	csQuery.Format( "SELECT AccountName, UserID FROM PlayingCharacters WHERE PlayerName='%s' LIMIT 1", (LPCTSTR)ch_name );//BLBLBL 05/01/2011
#endif

	ODBCCharWrite.SendRequest( (LPCTSTR)csQuery );
	
	// If user exists
	if( ODBCCharWrite.Fetch() ){

		// Get the username.
		ODBCCharWrite.GetString( 1, lpszUserName, 20 );
		ODBCCharWrite.GetDWORD ( 2, &dwID );
		
		// If player is owned by the calling account.
		if( CMP( lpszUserName, (LPCTSTR)ch_account ) == 0 )
		{

            _LOG_PC
                LOG_MISC_1,
                "Player %s (IP %s) deleted his character %s.",
                lpszUserName,
                (LPCTSTR)( reinterpret_cast< Players *>( ThisPlayer )->GetIP() ),
                (LPCTSTR)ch_name
            LOG_

			// Cancel previous fetch operation
			ODBCCharWrite.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close

			// Are we deleting right off the bat or are we taking it from the account for later purging?
			if (theApp.dwDisableIndirectDelete == 0) {
				// Ok, lets just remove it from account, allowing it to be restored later by an operator.

				SYSTEMTIME sysTime; 
				GetLocalTime(&sysTime);
				CString csTimeStamp;
				csTimeStamp.Format("$%04d%02d%02d%02d%02d%02d-%03d$",
					sysTime.wYear, 
					sysTime.wMonth,
					sysTime.wDay,
					sysTime.wHour, 
					sysTime.wMinute,
					sysTime.wSecond,
					rand()%1000
				);
				csQuery.Format( "UPDATE PlayingCharacters SET PlayerName='%s%s', AccountName='DeletedFrom:%s' WHERE PlayerName='%s'", (LPCTSTR)csTimeStamp, (LPCTSTR)ch_name, (LPCTSTR)ch_account, (LPCTSTR)ch_name  );//BLBLBL 05/01/2011 (retrait de top)
				// Send the deletion request
				if( !ODBCCharWrite.SendRequest( (LPCTSTR)csQuery ) ){
					boDeleteError = TRUE;
				}
			} else {
				// Delete it! Who cares for character restoring/backup? Mwouhahahahaha

				// Create a deletion query
				csQuery.Format( "DELETE FROM PlayingCharacters WHERE PlayerName='%s'", (LPCTSTR)ch_name );

				// Send the deletion request
				if( !ODBCCharWrite.SendRequest( (LPCTSTR)csQuery ) ){
					boDeleteError = TRUE;
				}

				csQuery.Format( "DELETE FROM Boosts WHERE BaseOwnerID=%d", dwID );			
				if( !ODBCCharWrite.SendRequest( (LPCTSTR)csQuery ) )
				{
					boDeleteError = TRUE;
				}

				csQuery.Format( "DELETE FROM Effects WHERE BaseOwnerID=%d", dwID );
				if( !ODBCCharWrite.SendRequest( (LPCTSTR)csQuery ) ){
					boDeleteError = TRUE;
				}
				
				csQuery.Format( "DELETE FROM Flags WHERE BaseOwnerID=%d", dwID );
				if( !ODBCCharWrite.SendRequest( (LPCTSTR)csQuery ) ){
					boDeleteError = TRUE;
				}

				csQuery.Format( "DELETE FROM PlayerItems WHERE OwnerID=%d", dwID );
				if( !ODBCCharWrite.SendRequest( (LPCTSTR)csQuery ) ){
					boDeleteError = TRUE;
				}

				csQuery.Format( "DELETE FROM PlayerSkills WHERE OwnerID=%d", dwID );
				if( !ODBCCharWrite.SendRequest( (LPCTSTR)csQuery ) ){
					boDeleteError = TRUE;
				}

				csQuery.Format( "DELETE FROM PlayerSpells WHERE OwnerID=%d", dwID );
				if( !ODBCCharWrite.SendRequest( (LPCTSTR)csQuery ) ){
					boDeleteError = TRUE;
				}
			}

			if( !boDeleteError ){
				Players *pl = (Players *)ThisPlayer;
				
				if( pl )
				{
					pl->RemovePlayer( ch_name );
				}
				
				/*if(Report){
					// Param: 1 = Account who deleted ..
					//		  2 = the player deleted
					//		  3 = path of the backuped file.
					LPCTSTR strings[3] = {(LPCTSTR)ch_account, (LPCTSTR)ch_name, "Fake 'TODO' BackupDir"};
					ReportError(__INFO_ACCOUNT_DELETED_PLAYER, 3, strings);
				
					ODBCCharWrite.Commit();
					ODBCCharWrite.Cancel();
					ODBCCharWrite.Unlock();
					
					return 0;
				}*/
                
                {
                    TFCPacket sending;
		            TemplateList <CStringAndRace> *PCs = pl->GetPCs();
                    sending << (RQ_SIZE)RQ_GetPersonnalPClist;
		            sending << (char)PCs->NbObjects();
		            PCs->Lock();
		            PCs->ToHead();
		            CStringAndRace *PC;
		            int i;
		            while(PCs->QueryNext())
					{
			            PC = PCs->Object();
			            sending << (char)PC->name.GetLength();
			            for(i = 0; i < PC->name.GetLength(); i++)
				            sending << (char)(PC->name[i]);
			            
			            sending << (short)PC->race;
			            sending << (short)PC->level;
		            }
		            PCs->Unlock();
		            
		            SendPlayerMessage( sending );
                }

				ODBCCharWrite.Commit();
				ODBCCharWrite.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close
				ODBCCharWrite.Unlock();
				return 0;
			}
			else
			{
				ODBCCharWrite.Rollback();
				ODBCCharWrite.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close
				ODBCCharWrite.Unlock();
				return 3;
			}
			
		}
		else
		{
			// Param: 1 = account of wrongfull player
			//        2 = name of player he wanted to delete
			//        3 = account of player who owns the potential victim
			//LPCTSTR strings[3] = {(LPCTSTR)ch_account, (LPCTSTR)ch_name, lpszUserName };
			//ReportError(__WARNING_NOT_ALLOWED_DELETION, 3, strings);
			   
			ODBCCharWrite.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close
			ODBCCharWrite.Unlock();
			return 2; // Not your player! BASTARD!!
		}	
	}
	ODBCCharWrite.CloseCursor();//BLBLBL 11/12/2010 : Cancel=>Close
	ODBCCharWrite.Unlock();
		
	return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::GetUnit
//////////////////////////////////////////////////////////////////////////////////////////
// Get's an object from the ground, doesn't check if it can (a prior call to 
// "can_get" must be done)
(
 WorldPos originalPos,
 Unit *tobj // The object fetched from the ground.
)
//////////////////////////////////////////////////////////////////////////////////////////
{   
    Disturbed(DISTURB_CLOSECHEST|DISTURB_CLOSETRADE|DISTURB_UNHIDE);

    if( tobj->GetType() != U_OBJECT ){
        return;
    }

    Objects *obj = static_cast< Objects * >( tobj );
    Players *lpPlayer = static_cast< Players * >( GetPlayer() );//BLBLBL on choppe un handle sur le joueur qui tente de ramasser
    
	// Remove the hidden flag.
    obj->RemoveFlag( __FLAG_HIDDEN );
    

    // if the object is withing getting range					
	DWORD dwReason = OBJECT_DISTURB_GET;
	
    bool add = true;
    
    obj->SendUnitMessage(MSG_OnDisturbed, obj, NULL, this, &dwReason );
	if( obj->GetMark() & MARK_DELETION )
	{
        // If the object is new empty.
        obj->Remove();
        if( obj->GetQty() == 0 )
		{
            // Delete and don't add it to the backpack.
            obj->DeleteUnit();
            add = false;
        }
	}
    
    // The item got deleted while being get
    if( !add )
	{
        return;
    }
    // If this is a gold stack.
    if( obj->GetStaticReference() == (UINT)__OBJ_GOLD )
	{
        // Add the gold directly to player.
        SetGold( GetGold() + obj->GetQty() );

        return;
    }

    _item *lpItem = NULL;

    obj->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItem );

    if( lpItem == NULL )
	{
        return;
    }

    // Determine how many of this item can be carried by the user.
    DWORD maxQty;
    if( lpItem->size == 0 || ( lpPlayer->GetGodFlags() & GOD_CAN_SUMMON_ITEMS )){//BLBLBL GM can always pick up an item
        maxQty = 0xFFFFFFFF;
    }
	else
	{
         maxQty = ( GetMaxWeight() - GetWeight() ) / lpItem->size;
    }
    
    // Impossible
    if( maxQty == 0 )
	{
        ASSERT( 0 );
        return;
    }

    // If the item has more items than the user can carry.
    if( obj->GetQty() > maxQty )
	{
        // Determine how many need to stay on the ground.
        DWORD qty = obj->GetQty() - maxQty;

        // Create a new object of this type.
        Objects *newObj = new Objects;
        if( newObj->Create( U_OBJECT, obj->GetStaticReference() ) )
		{
            // Set its quantity to the remainder.
            newObj->SetQty( qty );

            // Deposit the new unit where it was gotten.
            WorldMap *wl = TFCMAIN::GetWorld( originalPos.world );

            wl->deposit_unit( originalPos, newObj );

            newObj->BroadcastPopup( originalPos );


            // Set the backpack object's quantity to the max possible quantity.
            obj->SetQty( maxQty );
        }
		else
		{
            newObj->DeleteUnit();
        }
    }

    AddToBackpack( obj );

    // Shoot a backpack update.
	TFCPacket sending;

	sending << (RQ_SIZE)RQ_ViewBackpack;
	sending << (char)0;	// Do not show content of backpack, only update it.
	sending << (long)GetID();
	PacketBackpack(sending);

	SendPlayerMessage( sending );

    sending.Destroy();
    packet_equiped( sending );
    SendPlayerMessage( sending );
}
/**************************************/
// Verifies that an object can be get.
BOOL Character::can_get(WorldPos where, Objects *obj)
{	
    ASSERT( obj->GetType() == U_OBJECT );
    // You can only get items! Nothing else!
    if( obj->GetType() != U_OBJECT ){
        _LOG_DEBUG
            LOG_WARNING,
            "Player %s tried to get a non-item named %s.",
            GetTrueName().c_str(),
            obj->GetName( _DEFAULT_LNG ).c_str()
        LOG_
        return false;
    }
    
    _item *lpItem = NULL;
	Players *lpPlayer = static_cast< Players * >( GetPlayer() );//BLBLBL on choppe un handle sur le joueur qui tente de ramasser

    obj->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItem );

    if( lpItem != NULL ){

        
		if ( lpPlayer->GetGodFlags() & GOD_CAN_SUMMON_ITEMS ) {//BLBLBL a GM can pick up anything anywhere on screen

		      if( lpItem->dwDropFlags & CANNOT_GET_ITEM ) return FALSE;//Except non-get items (decors)
		      else return TRUE;
		}
		
		// If the quantity of weight left on player can hold at least
        // one of these items.
        if( ( GetMaxWeight() - GetWeight() ) >= lpItem->size )
		{

	        int nTouchRange = ViewFlag( __FLAG_ARM_EXTENT );

	        if( nTouchRange == 0 ){
		        nTouchRange = _DEFAULT_TOUCH_RANGE;
	        }

	        // If object is not within range.
	        if(!(abs(where.X - GetWL().X) < _DEFAULT_TOUCH_RANGE && abs(where.Y - GetWL().Y) < _DEFAULT_TOUCH_RANGE))
		        return FALSE;

            TRACE( "\n Drop flags=%u.", lpItem->dwDropFlags );

	        // If object can be get.
	        if( lpItem->dwDropFlags & CANNOT_GET_ITEM ) 
		        return FALSE;	        
	        
	        return TRUE;
        }
		else
		{
            TELL_PLAYER( 17 );
        }
    }

    return FALSE;
}


//////////////////////////////////////////////////////////////////////////////////////////
Unit * Character::DropUnit
//////////////////////////////////////////////////////////////////////////////////////////
//  Drops a unit from the backpack to the ground.
// 
(
 WorldPos where, // Where to drop the unit
 DWORD itemId,   // The ID of the item to drop.
 DWORD qty       // The quantity of items from a stack to drop.
)
// Return: Unit *, The dropped unit, NULL if drop failed.
//////////////////////////////////////////////////////////////////////////////////////////
{
	Disturbed();
    
	BOOL done = FALSE;
	BOOL endsearch = FALSE;	
	DWORD dwReason = OBJECT_DISTURB_DROP;

	int nThrowRange = ViewFlag( __FLAG_ARM_EXTENT );

	if( nThrowRange == 0 ){
		nThrowRange = 10;
	}

	// If it cannot be thrown/dropped
	if( !( abs(where.X - GetWL().X) < nThrowRange && abs(where.Y - GetWL().Y) < nThrowRange ) ){
        return NULL;
    }

	// Get the world
	WorldMap *wl = TFCMAIN::GetWorld( GetWL().world );
    if( wl == NULL ){
        return NULL;
    }

    DWORD qtySave = qty;

	backpack->Lock();
    backpack->ToHead();
	while( backpack->QueryNext() )
	{
        qty = qtySave;

		Objects *obj = static_cast< Objects * >( backpack->Object() );
					
		if( obj->GetID() != itemId )
		{
            continue;
        }
        // If user does not have any gold and wants to drop a gold stack.
        if( obj->GetStaticReference() == (UINT)__OBJ_GOLD && GetGold() == 0 )
		{
            continue;
        }

        // If the quantity is bigger than the total quantity.
        if( obj->GetQty() < qty )
		{
            // Adjust it.
            qty = obj->GetQty();
        }

        _item *lpItem = NULL;

        obj->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItem );
			
        if( lpItem == NULL )
		{
            continue;
        }
        // Can it be dropped? :)
		if( lpItem->dwDropFlags & CANNOT_DROP_ITEM )
		{
            // This object cannot be dropped.
            SendSystemMessage( _STR( 7694, GetLang() ) );
            continue;
        }
		// we flush it from the backpack
		obj->SendUnitMessage(MSG_OnDisturbed, obj, NULL, this, &dwReason );
		if( obj->GetMark() & MARK_DELETION )
		{						
			obj->Remove( qty );
            if( obj->GetQty() == 0 )
			{
                backpack->Object()->DeleteUnit();
                backpack->Remove();
            }
            backpack->Unlock();
			return NULL;						
		}

        // If the player dropped at the player's spot.
        if( where.X == GetWL().X && where.Y == GetWL().Y )
		{
            // Find a new valid spot, around the player.
			
            WorldPos newPos = wl->FindValidSpot( where, 3, true );//BLBLBL on cherche à poser le plus près possible du perso
		
            // If the given spot is valid.
            if( newPos.X != -1 && newPos.Y != -1 )
			{                                
                // Use it.
                where = newPos;
            }
        }

        if( !wl->IsValidPosition( where ) || wl->IsBlocking(where) )
		{
            SendSystemMessage( _STR( 468, GetLang() ) );
            continue;
        }
        
        WorldPos wlCollidePos;
        Unit *lpDummy;
        wl->GetCollisionPos( GetWL(), where, &wlCollidePos, &lpDummy );

        // If the collision pos does not corresponds to the desired spot.
        if( wlCollidePos.X != where.X || wlCollidePos.Y != where.Y )
		{
            SendSystemMessage( _STR( 468, GetLang() ) );
        }

    
        bool forceQtyToOne = false;
        Objects *droppedObj;
        // If there are more than 1 item in the backpack
        if( obj->GetQty() > 1 )
		{
            // Create a copy of the backpack item
            droppedObj = new Objects();
            if( !droppedObj->Create( U_OBJECT, obj->GetStaticReference() ) )
			{
                droppedObj->DeleteUnit();
                continue;
            }
            // Set the quantity of items to the quantity of dropped items.
            droppedObj->SetQty( qty );
        }
		else
		{
            // Used the backpack item as the dropped item.
            droppedObj = obj;
            // Add 1 qty count to avoid deleting the unit.
            forceQtyToOne = true;

            backpack->Remove();
        }

        char lpszID[ 256 ];
        Unit::GetNameFromID( droppedObj->GetStaticReference(), lpszID, U_OBJECT );

        _LOG_ITEMS
            LOG_MISC_1,
            "Player %s dropped %u item %s ID( %s ) at ( %u, %u, %u )",
            GetTrueName().c_str(),
            qty,
            droppedObj->GetName( _DEFAULT_LNG ).c_str(),
            lpszID,
            where.X,
            where.Y,
            where.world
        LOG_

		wl->deposit_unit( where, droppedObj );
		droppedObj->BroadcastPopup( where );//BLBLBL

        bool updateGold = false;
        DWORD goldUpdate = 0;
        // If this is a gold stack.
        if( obj->GetStaticReference() == (UINT)__OBJ_GOLD )
		{
            // Gets its gold value.
            if( qty < GetGold() )
			{
                // Remove gold directly from player.
                goldUpdate = GetGold() - qty;
            }

            updateGold = true;
        }

        // Remove the quantity of objects dropped from the backpack item.
        
        if( forceQtyToOne )
		{
            obj->SetQty( 1 );
        }
		else
		{
            obj->Remove( qty );
        }

        if( obj->GetQty() == 0 )
		{
            backpack->Remove();
            obj->DeleteUnit();
        }

	    // Shoot a backpack update.
	    TFCPacket sending;

	    sending << (RQ_SIZE)RQ_ViewBackpack;
	    sending << (char)0;	// Do not show content of backpack, only update it.
	    sending << (long)GetID();
	    PacketBackpack(sending);

	    SendPlayerMessage( sending );					
        backpack->Unlock();

        if( updateGold )
		{
            // Reset the gold amount (after the backpack was released).
            SetGold( goldUpdate );
        }
		return droppedObj;
    }
    backpack->Unlock();

	/*// Shoot a backpack update.
	TFCPacket sending;

	sending << (RQ_SIZE)RQ_ViewBackpack;
	sending << (char)0;	// Do not show content of backpack, only update it.
	sending << (long)GetID();
	PacketBackpack(sending);

	SendPlayerMessage( sending );*/

	return NULL;
}

/************************************************************************************************/
// Creates an object into a user's backpack, should be a god-only function
unsigned long Character::god_create_object(unsigned short which_item)
{	
	Objects *new_item = new Objects;
	new_item->Create(U_OBJECT, which_item);
	backpack->Lock();
    backpack->AddToTail(new_item);
    backpack->Unlock();

	return new_item->GetID();	
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Character::CanEquip
//////////////////////////////////////////////////////////////////////////////////////////
// Determines if an item can be equipped.
// 
(
 Unit *lpuEquip,    // Item
 _item *lpItem,      // Item structure, used if provided.
 BOOL boEcho,
 CString *reqText   // Text to put the reqs in, if any.
)
// Return: BOOL, TRUE can equip.
//////////////////////////////////////////////////////////////////////////////////////////
{
    BOOL boReturn = TRUE;
    if( lpuEquip->GetType() == U_OBJECT || lpItem != NULL )
	{
        // If an item structure wasn't provided
        if( lpItem == NULL )
		{
            // Fetch item structure.
            lpuEquip->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItem );
        }

        TFormat format;

        bool prev = false;
        if( reqText != NULL )
		{
            *reqText = _STR( 7277, GetLang() );
        }

        if( reqText != NULL ){
            if( lpItem->armor.End != 0 )
			{
                *reqText += format( _STR( 7280, GetLang() ), lpItem->armor.End );
                prev = true;
            }
        }

        TRACE( "\r\nThis armor's endurance=%u", lpItem->armor.End );
        // If player doesn't have the required endurance.
        if( !( GetTrueEND() >= lpItem->armor.End ) )
		{
            if( boEcho )
			{
                TELL_PLAYER( 8 );
            }
            boReturn = FALSE;
        }




        if( reqText != NULL )
		{
            if( lpItem->weapon.Str != 0 )
			{
                *reqText += format( _STR( 7279, GetLang() ), lpItem->weapon.Str );
                prev = true;
            }
        }

        // If player doesn't have the required strength.
        if( !( GetTrueSTR() >= lpItem->weapon.Str ) )
		{
            if( boEcho )
			{
                TELL_PLAYER( 1 );
            }
            boReturn = FALSE;
        }
        
        if( reqText != NULL ){
            if( lpItem->weapon.Att != 0 ){
                *reqText += format( _STR( 11406, GetLang() ), lpItem->weapon.Att );
            }
        }
        if( !( GetTrueATTACK() >= lpItem->weapon.Att ) )
		{
            if( boEcho )
			{
                TELL_PLAYER( 11405 );
            }
            boReturn = FALSE;
        }

        TRACE( "\r\nboReturn = %u, Item MinInt=%u MinWis=%u, Player Int=%u Wis=%u.",
            boReturn,
            lpItem->magic.nMinInt,
            lpItem->magic.nMinWis,
            GetTrueINT(),
            GetTrueWIS()
        );
        if( reqText != NULL ){
            if( lpItem->magic.nMinInt != 0 )
			{
                if( prev )
				{
                    *reqText += ", ";
                }
        
                *reqText += format( _STR( 7282, GetLang() ), lpItem->magic.nMinInt );
                prev = true;
            }
            if( lpItem->magic.nMinWis != 0 )
			{
                if( prev )
				{
                    *reqText += ", ";
                }
        
                *reqText += format( _STR( 7283, GetLang() ), lpItem->magic.nMinWis );
                prev = true;
            }
            if( lpItem->weapon.Agi != 0 )
			{
                if( prev )
				{
                    *reqText += ", ";
                }

                *reqText += format( _STR( 7281, GetLang() ), lpItem->weapon.Agi );
                prev = true;
            }

            if( prev )
			{
                *reqText += ".";
            }else{
                *reqText += _STR( 7286, GetLang() );
            }
        }

        // If player doesn't have enough int/wis to equip the object.
        if( lpItem->magic.nMinInt > GetTrueINT() )
		{
            if( boEcho )
			{
                TELL_PLAYER( 15 );
            }
            boReturn = FALSE;
        }
        if( lpItem->magic.nMinWis > GetTrueWIS() )
		{
            if( boEcho )
			{
                TELL_PLAYER( 21 );
            }
            boReturn = FALSE;
        }
        if( !( GetTrueAGI() >= lpItem->weapon.Agi ) )
		{
            if( boEcho )
			{
                TELL_PLAYER( 7847 );
            }
            boReturn = FALSE;
        }

    }
   
    return boReturn;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Character::QueryEquip
//////////////////////////////////////////////////////////////////////////////////////////
// Queries the stat reduction/requirements when equipping an item
// 
(
 Unit *lpuEquip,	// The item equipped.
 BYTE bItemType,	// The equip position where this object should be.
 BYTE bEquipPos,	// the equip pos.
 _item *item		// the 'item' structure of the item.
)
// Return: BOOL, TRUE if item can be equipped.
//////////////////////////////////////////////////////////////////////////////////////////
{
   BOOL boReturn = TRUE;
   
   //////////////////////////////////////////////////////////////////////////////////////////	
   // if item is a weapon. ( 1 = WEAPON1, 2 = WEAPON2 )
   if( bItemType == 1 || bItemType == 2 )
   {
      WORD wStr = GetSTR();
      WORD wAgi = GetAGI();
      int nDamBonus = 0;
      int nAttSkillBonus = 0;
      
      // If user has more then enough strength. 
      if( CanEquip( lpuEquip, item ) )
      {
         
         nDamBonus = 0;//( wStr - item->weapon.Str ) / 5;			
         
         // If player has an overall damage bonus
         if( nDamBonus != 0 )
         {
            if( bItemType == 1 )
            {
               SetBoost( BOOST_EQUIP_WEAPON1_DAM, STAT_DAMAGE, nDamBonus );
            }
            else
            {
               SetBoost( BOOST_EQUIP_WEAPON2_DAM, STAT_DAMAGE, nDamBonus );
            }
         }
         else
         {
            if( bItemType == 1 )
            {// Otherwise remove the unnecessary boost
               RemoveBoost( BOOST_EQUIP_WEAPON1_DAM );
            }
            else
            {
               RemoveBoost( BOOST_EQUIP_WEAPON2_DAM );
            }
         }
      }
      else
      {                
         return FALSE;
      }
   }
   else
	// if item is an armor	
	if( bItemType == 3 )
	{
					
		// User must have enough endurance.
		if( CanEquip( lpuEquip, item ) )
		{
			int nDodgeBoost = 0;

			// Remove the dodge skill malus.
			nDodgeBoost -= item->armor.Dod;

			if( nDodgeBoost != 0 )
			{
				switch( bEquipPos )
				{
					case body:		SetBoost( BOOST_EQUIP_ARMOR_BODY_DODGE, STAT_DODGE, nDodgeBoost ) ;		break;
					case feet:		SetBoost( BOOST_EQUIP_ARMOR_FEET_DODGE, STAT_DODGE, nDodgeBoost ) ;		break;
					case gloves:	SetBoost( BOOST_EQUIP_ARMOR_GLOVES_DODGE, STAT_DODGE, nDodgeBoost );	break;
					case helm:		SetBoost( BOOST_EQUIP_ARMOR_HELM_DODGE, STAT_DODGE, nDodgeBoost ) ;		break;
					case legs:		SetBoost( BOOST_EQUIP_ARMOR_LEGS_DODGE, STAT_DODGE, nDodgeBoost ) ;		break;
					case cape:	    SetBoost( BOOST_EQUIP_ARMOR_SLEEVES_DODGE, STAT_DODGE, nDodgeBoost );	break;
				}
			}
			else
			{
				switch( bEquipPos )
				{
					case body:		RemoveBoost( BOOST_EQUIP_ARMOR_BODY_DODGE ) ;	break;
					case feet:		RemoveBoost( BOOST_EQUIP_ARMOR_FEET_DODGE ) ;	break;
					case gloves:	RemoveBoost( BOOST_EQUIP_ARMOR_GLOVES_DODGE );	break;
					case helm:		RemoveBoost( BOOST_EQUIP_ARMOR_HELM_DODGE ) ;	break;
					case legs:		RemoveBoost( BOOST_EQUIP_ARMOR_LEGS_DODGE ) ;	break;
					case cape:	    RemoveBoost( BOOST_EQUIP_ARMOR_SLEEVES_DODGE ) ;break;
				}
			}
        }else{
            boReturn = FALSE;
        }
	}

	return boReturn;
}



/*************************************************************************************************/
// Equips an object (from backpack to proper worn position)
// Only equipped items are treated for magical abilities
char Character::equip_object(unsigned long item_number)
{ 
   Disturbed();
   if( item_number )
   {
      BOOL boFound = FALSE;		
      unsigned long nb = 0;
      int ipos;
      
      Objects *equippedItem = NULL;
      
      backpack->Lock();
      backpack->ToHead();
      while( backpack->QueryNext() && !boFound)
      {
         Objects *obj = static_cast< Objects * >( backpack->Object() );
         if( obj->GetID() == item_number )
         {
            _item *itemStructure = NULL;
            
            // Get the item structure.
            obj->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &itemStructure );
            
            if( itemStructure == NULL )
            {
               continue;
            }
            
            // If this is a quiver.
            if( itemStructure->itemStructureId == 12 )
            {
               // Equip the WHOLE quiver (which full quantity).
               equippedItem = obj;
               backpack->Remove();
            }
            else
            {
               // Remove the item from the backpack if its stack is not empty.
               obj->Remove();
               if( obj->GetQty() == 0 )
               {
                  backpack->Remove();
                  
                  // If the item is now empty, use it as the equipped object
                  // Avoids having to make a copy of it and allows 
                  // unique items to be added.
                  obj->SetQty( 1 );
                  equippedItem = obj;
               }
               else
               {
                  // Make a copy of this item type.
                  equippedItem = new Objects;
                  
                  // If creating a copy failed.
                  if( !equippedItem->Create( U_OBJECT, obj->GetStaticReference() ) )
                  {
                     equippedItem->DeleteUnit();
                     equippedItem = NULL;
                  }
               }
            }
            boFound = TRUE;				
         }
      }
      
      // If the item was in the backpack
      if( boFound && equippedItem != NULL )
      {
         // Set to true if the item should be re-added to the backpack.
         bool addToBackpack = false;
         
         // Check to see if an item of the same type is already equipped.
         int z;
         bool boSame = false;
         for( z = 0; z < EQUIP_POSITIONS; z++ )
         {
            if( equipped[ z ] != NULL )
            {
               if( equipped[ z ]->GetStaticReference() == equippedItem->GetStaticReference() )
               {
                  boSame = true;
               }
            }
         }
         
         // If the item can be equipped.
         if( !boSame )
         {
            BOOL boEquip = TRUE;
            _item *lpItemStructure = NULL;
            
            // Get the item structure.
            equippedItem->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItemStructure );
            
            if( lpItemStructure )
            {
               ipos = lpItemStructure->equip_position;
               TRACE("\r\nipos=%u\r\n", ipos);
               if(ipos >= 0 && ipos < EQUIP_POSITIONS) // avoids access violation
               {
                  DWORD dwCallReason = OBJECT_DISTURB_EQUIP;
                  
                  // If this is a bow.
                  if( lpItemStructure->weapon.ranged && lpItemStructure->itemStructureId != 12 )
                  {
                     // Verify that the equipped unit is a quiver.
                     if( equipped[ QUIVER_POS ] )
                     {
                        _item *is = NULL;
                        // Get the item structure.
                        equipped[ QUIVER_POS ]->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &is );
                        
                        // If this is not a quiver.
                        if( is == NULL || is->itemStructureId != 12 )
                        {
                           TELL_PLAYER( 7883 );
                           boEquip = FALSE;
                        }
                     }
                  }
                  else if( ipos == BOW_POS )
                  {
                     // Verify that the equipped unit is NOT a quiver.
                     if( equipped[ QUIVER_POS ] )
                     {
                        _item *is = NULL;
                        // Get the item structure.
                        equipped[ QUIVER_POS ]->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &is );
                        
                        // If this is a quiver.
                        if( is == NULL || is->itemStructureId == 12 )
                        {
                           TELL_PLAYER( 7885 );
                           boEquip = FALSE;
                        }
                     }
                  }
                  // If this is a quiver.
                  if( lpItemStructure->itemStructureId == 12 )
                  {
                     // Verify that the equipped unit is a bow.
                     if( equipped[ BOW_POS ] )
                     {
                        _item *is = NULL;
                        // Get the item structure.
                        equipped[ BOW_POS ]->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &is );
                        
                        // If this is not a bow.
                        if( is == NULL || !is->weapon.ranged )
                        {
                           TELL_PLAYER( 7884 );
                           boEquip = FALSE;
                        }
                     }
                  }
                  else if( ipos == QUIVER_POS )
                  {
                     // Verify that the equipped unit is NOT a bow.
                     if( equipped[ BOW_POS ] )
                     {
                        _item *is = NULL;
                        // Get the item structure.
                        equipped[ BOW_POS ]->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &is );
                        
                        // If this is a bow
                        if( is == NULL || is->weapon.ranged )
                        {
                           TELL_PLAYER( 7886 );
                           boEquip = FALSE;
                        }
                     }
                  }
                  
                  if( boEquip )
                  {
                     switch(ipos)
                     {
                        case two_hands: // If it's a two handed weapon, it's special
                           if(!equipped[weapon_left] && !equipped[weapon_right])
                           {
                              // If user can equip this item
                              if( QueryEquip( equippedItem, 1, ipos, lpItemStructure ) )
                              {
                              
                                 equipped[weapon_right] = equippedItem; // Both hands point to the same object
                                 equipped[weapon_left] = equippedItem; // only one hand will be processed!!
                                 equippedItem->SendUnitMessage(MSG_OnDisturbed, equippedItem, NULL, this, &dwCallReason );
                              
                                 if( equippedItem->GetMark() & MARK_DELETION )
                                 {
                                    equippedItem->DeleteUnit();
                                    equipped[ weapon_right ] = equipped[ weapon_left ] = NULL;
                                    boEquip = FALSE;
                                 }
                              }
                              else
                              {
                                 boEquip = FALSE;
                              }
                           }
                           else
                           {
                              TELL_PLAYER( 9 );
                              boEquip = FALSE;
                           }
                        break;
                        case rings:
                           // Checks both ring spaces for free
                           if(!equipped[ring1])
                           {
                              if( CanEquip( equippedItem, lpItemStructure ) ) 
                              {
                                 equipped[ring1] = equippedItem;
                                 equippedItem->SendUnitMessage(MSG_OnDisturbed, equippedItem, NULL, this, &dwCallReason );
                                 if( equippedItem->GetMark() & MARK_DELETION )
                                 {
                                    equippedItem->DeleteUnit();
                                    equipped[ ring1 ] = NULL;
                                    boEquip = FALSE;
                                 }
                              }
                              else
                              {
                                 boEquip = FALSE;
                              }
                           }
                           else if(!equipped[ring2])
                           {
                              if( CanEquip( equippedItem, lpItemStructure ) )
                              {
                                 equipped[ring2] = equippedItem;					
                                 equippedItem->SendUnitMessage(MSG_OnDisturbed, equippedItem, NULL, this, &dwCallReason );
                                 if( equippedItem->GetMark() & MARK_DELETION )
                                 {
                                    equippedItem->DeleteUnit();
                                    equipped[ ring2 ] = NULL;
                                    boEquip = FALSE;
                                 }
                              }
                              else
                              {
                                 boEquip = FALSE;
                              }
                           }
                           else
                           {
                              TELL_PLAYER( 10 );
                              boEquip = FALSE;
                           }
                        break;
                        case weapon: // case weapon actually means "any of the two hands"
                           if(!equipped[weapon_right])
                           {
                              // If user can equip this item
                              if( QueryEquip( equippedItem, 1, ipos, lpItemStructure ) )
                              {
                              
                                 equipped[weapon_right] = equippedItem;
                                 equippedItem->SendUnitMessage(MSG_OnDisturbed, equippedItem, NULL, this, &dwCallReason );
                                 if( equippedItem->GetMark() & MARK_DELETION )
                                 {
                                    equippedItem->DeleteUnit();
                                    equipped[ weapon_right ] = NULL;
                                    boEquip = FALSE;
                                 }
                              }
                              else
                              {
                                 boEquip = FALSE;
                              }							
                           }
                           else if(!equipped[weapon_left])
                           { // otherwise check left
                              // Tell player he cannot wield two weapons at same time.
                              TELL_PLAYER( 11 );
                              boEquip = FALSE;	
                           }
                           else
                           {
                              // Otherwise re-add the object in the backpack
                              TELL_PLAYER( 12 );								
                              boEquip = FALSE;
                           }
                        break;
                           // If its an armor piece.
                        case body:
                        case feet:
                        case gloves:
                        case helm:
                        case legs:
                        case belt:
                        case cape: 
                           if(!equipped[ipos])
                           {
                              // If user can equip this item
                              if( QueryEquip( equippedItem, 3, ipos, lpItemStructure ) )
                              {
                                 
                                 equipped[ipos] = equippedItem;
                                 equippedItem->SendUnitMessage(MSG_OnDisturbed, equippedItem, NULL, this, &dwCallReason );
                                 if( equippedItem->GetMark() & MARK_DELETION )
                                 {
                                    equippedItem->DeleteUnit();
                                    equipped[ ipos ] = NULL;
                                    boEquip = FALSE;
                                 }
                              }
                              else
                              {
                                 boEquip = FALSE;
                              }							
                           }
                           else
                           {
                              TELL_PLAYER( 13 )
                                 boEquip = FALSE;
                           }
                        break;
                        /*
                        default: // Otherwise, if it's a normal position
                           if(!equipped[ipos])
                           {
                              if( CanEquip( equippedItem, lpItemStructure ) )
                              {
                                 equipped[ipos] = equippedItem;
                                 equippedItem->SendUnitMessage(MSG_OnDisturbed, equippedItem, NULL, this, &dwCallReason );
                                 if( equippedItem->GetMark() & MARK_DELETION )
                                 {
                                    equippedItem->DeleteUnit();
                                    equipped[ ipos ] = NULL;
                                    boEquip = FALSE;
                                 }
                              }
                              else
                              {
                                 boEquip = FALSE;
                              }
                           }
                           else
                           {
                              TELL_PLAYER( 13 );
                              // Otherwise re-add the object in the backpack
                              boEquip = FALSE;
                           }
                        break;
                        */
                        default: // Otherwise, if it's a normal position
                           if(!equipped[ipos])
                           {
                              if( CanEquip( equippedItem, lpItemStructure ) )
                              {
                              
                              
                                 LPUSER_SKILL userSkill = GetSkill(__SKILL_TWOWEAPONS   );
                                 if(lpItemStructure->item_type == 1/*WEAPON*/ && lpItemStructure->equip_position == 9 /*weapon_left*/ && userSkill == NULL && !lpItemStructure->weapon.ranged )
                                 {
                                    //try to equip dual weapon without skill...                                 
                                    TELL_PLAYER( 12962 );
                                    boEquip = FALSE;
                                 }
                                 else
                                 {
                                    equipped[ipos] = equippedItem;
                                    equippedItem->SendUnitMessage(MSG_OnDisturbed, equippedItem, NULL, this, &dwCallReason );
                                    if( equippedItem->GetMark() & MARK_DELETION )
                                    {
                                       equippedItem->DeleteUnit();
                                       equipped[ ipos ] = NULL;
                                       boEquip = FALSE;
                                    }
                                 }
                              }
                              else
                              {
                                 boEquip = FALSE;
                              }
                           }
                           else
                           {
                              TELL_PLAYER( 13 );
                              // Otherwise re-add the object in the backpack
                              boEquip = FALSE;
                           }
                        break;
                      }
                  }
                  
                  if( !boEquip )
                  {
                     // Otherwise re-add the object in the backpack
                     addToBackpack = true;
                  }
                  else
                  {
                     // Sending an OnEquip message for boosts
                     equippedItem->SendUnitMessage(MSG_OnEquip, equippedItem, NULL, this );
                     
                     // Send stat update
                     TFCPacket sending;
                     
                     PacketStatus( sending );	
                     SendPlayerMessage( sending );
                     
                     sending.Destroy();
                     PacketSkills( sending );
                     SendPlayerMessage( sending );
                     
                     // Shoot the puppet packet to all on-screen.
                     sending.Destroy();
                     if( IsPuppet() )
                     {
                        PacketPuppetInfo ( sending );
                        Broadcast::BCast( GetWL(), _DEFAULT_RANGE, sending );//BLBL 20=>_DEFAULT_RANGE
                     }
                     
                     // Send the equipment.
                     sending.Destroy();
                     packet_equiped( sending );
                     SendPlayerMessage( sending );
                  }
               }
               else
               {
                  SendSystemMessage( _STR( 7247, GetLang() ) );
                  addToBackpack = true;
               }
            }
         }
         else
         {                
            // Send same message.
            TELL_PLAYER( 471 );
            addToBackpack = true;
         }
         if( addToBackpack )
         {
            AddToBackpack( equippedItem );
         }
      }
      backpack->Unlock();
   }	
   return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////
char Character::unequip_object
//////////////////////////////////////////////////////////////////////////////////////////
// Unequip an item (from worn to backpack)
// 
(
 unsigned char ipos, // The position to unequip.
 bool remove         // Removes the item but does not put it in the backpack
)
// Return: char,  Unused.
//////////////////////////////////////////////////////////////////////////////////////////
{
    Disturbed();

    // This avoids any attempt to se beyond existing equiping positions
	if(ipos >= 0 && ipos < EQUIP_POSITIONS && ipos != rings && ipos != weapon){

		Unit *lpuItem = equipped[ ipos ];
		
		// If there is an equipped unit.
		if( lpuItem )
		{
			for(int i=0;i<theApp.m_aStillItems.size();i++)
			{
				if(theApp.m_aStillItems[i] == lpuItem->GetStaticReference())
				{
					TFCPacket sending;
					if( IsPuppet() )
					{
						packet_equiped ( sending );
						SendPlayerMessage( sending );
					}
					return 0; // this item cant unequip...
				}
			}

            // If two handed weapon.
            if( ( ipos == weapon_right || ipos == weapon_left ) && equipped[ weapon_right ] == equipped[ weapon_left ] ){
                // Remove item from both equip positions.
                equipped[ weapon_right ] = equipped[ weapon_left ] = NULL;
            }
     
			
			equipped[ ipos ] = NULL;

			// Remove boost associated with unit
			switch( ipos ){
				case weapon_right:
					RemoveBoost( BOOST_EQUIP_WEAPON1_DAM );
					RemoveBoost( BOOST_EQUIP_WEAPON1_ATTACK );
					break;				
				case weapon_left:
					RemoveBoost( BOOST_EQUIP_WEAPON2_DAM );
					RemoveBoost( BOOST_EQUIP_WEAPON2_ATTACK );
					break;
				case two_hands:
					RemoveBoost( BOOST_EQUIP_WEAPON1_DAM );
					RemoveBoost( BOOST_EQUIP_WEAPON1_ATTACK );
					break;
				case body:		RemoveBoost( BOOST_EQUIP_ARMOR_BODY_DODGE ) ;break;
				case feet:		RemoveBoost( BOOST_EQUIP_ARMOR_FEET_DODGE ) ;break;
				case gloves:	RemoveBoost( BOOST_EQUIP_ARMOR_GLOVES_DODGE ) ;break;
				case helm:		RemoveBoost( BOOST_EQUIP_ARMOR_HELM_DODGE ) ;break;
				case legs:		RemoveBoost( BOOST_EQUIP_ARMOR_LEGS_DODGE ) ;break;
				case cape:	    RemoveBoost( BOOST_EQUIP_ARMOR_SLEEVES_DODGE ) ;break;
			}

			// Remove the item's boost.
			//RemoveBoost( lpItemStructure->boost.wBoostID );
			lpuItem->SendUnitMessage(MSG_OnUnequip, lpuItem, NULL, this );

            if( !remove ){
                AddToBackpack( static_cast< Objects * >( lpuItem ) );
            }
            
            // Send stat update.
            TFCPacket sending;
	        PacketStatus( sending );	
	        SendPlayerMessage( sending );

            sending.Destroy();
            PacketSkills( sending );
	        SendPlayerMessage( sending );        

            // Shoot the puppet packet to all on-screen.
            sending.Destroy();
            if( IsPuppet() ){
                PacketPuppetInfo ( sending );
                //NMNMNM 20
                Broadcast::BCast( GetWL(), _DEFAULT_RANGE, sending );//BLBLBL 30=>_DEFAULT_RANGE
            }

            sending.Destroy();
            packet_equiped( sending );
            SendPlayerMessage( sending );
        }
	}	
return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::PacketSingleEquip
//////////////////////////////////////////////////////////////////////////////////////////
// Packets a single equip position
// 
(
 BYTE equip_pos,	// The equip position
 TFCPacket &sending	// The packet
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	Unit *lpuUnit = equipped[ equip_pos ];
	if( lpuUnit ){
        Objects *lpuObject = static_cast< Objects * >( lpuUnit );
		TRACE( "..%u..", equip_pos );
		sending << (long)lpuUnit->GetID();
		sending << (short)lpuUnit->GetAppearance();
        sending << (short)lpuUnit->GetStaticReference();
        sending << (short)static_cast< Objects * >( lpuUnit )->GetQty();
        // Only unique items may have charges.
        if( lpuObject->IsUnique() ){
            sending << (long)lpuObject->ViewFlag( __FLAG_CHARGES );
        }else{
            sending << (long)0;
        }

		sending << (CString )lpuUnit->GetName( GetLang() );
	}
	else
	{
		CString csNull;
		csNull = "";
		sending << (long)0;
		sending << (short)0;
        sending << (short)0;
        sending << (short)0;
        sending << (long)0;
		sending << (CString)csNull;
	}
}

/*****************************************************************************************/
// Puts the equiped objects in a packet
void Character::packet_equiped(TFCPacket &packet, bool gameop)
{

    if( gameopContext != NULL && !gameop )
	{
        gameopContext->packet_equiped( packet, true );
        return;
    }
	
	// scans all equiped positions
	packet << (RQ_SIZE)RQ_ViewEquiped;
    if( RangedAttack() ){
        packet << (char)1;
    }else{
        packet << (char)0;
    }

	PacketSingleEquip( body, packet );
	PacketSingleEquip( gloves, packet );
	PacketSingleEquip( helm, packet );
	PacketSingleEquip( legs, packet );
	PacketSingleEquip( bracelets, packet );
	PacketSingleEquip( necklace, packet );
	PacketSingleEquip( weapon_right, packet );
	PacketSingleEquip( weapon_left, packet );
	PacketSingleEquip( ring1, packet );
	PacketSingleEquip( ring2, packet );
	PacketSingleEquip( belt, packet );
	PacketSingleEquip( cape, packet );
	PacketSingleEquip( feet, packet );
}
/***********************************************************************************************/
// Memorizes a spell in the memorize box
char Character::memorize_spell(unsigned char where, unsigned short which_spell, unsigned long GetID)
{
	return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Character::UseSpellEnergy
//////////////////////////////////////////////////////////////////////////////////////////
// Spends mana.
// 
(
 WORD wMana		// How much mana to spend.
)
// Return: BOOL, TRUE if player could spent this mana.
//////////////////////////////////////////////////////////////////////////////////////////
{
	int nCurrentEnergy = GetMana();
	
    // Use mana
	nCurrentEnergy -= wMana;	    
    
    nCurrentEnergy = nCurrentEnergy < 0 ? 0 : nCurrentEnergy;
    
    SetMana( nCurrentEnergy );	   

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Character::CastSpell
//////////////////////////////////////////////////////////////////////////////////////////
// This function allows a user to cast a spell
// 
(
 WORD wSpellID,		// The spell's ID.
 Unit *uTarget		// The target unit of the spell 
)
// Return: BOOL, TRUE if spell message was sent.
//////////////////////////////////////////////////////////////////////////////////////////
{	
	BOOL boReturn = FALSE;	

    TRACE( "\r\nReceive spell ID=%u", wSpellID );
	
    LPSPELL_STRUCT lpSpell     = SpellMessageHandler::GetSpell( wSpellID );
	LPUSER_SKILL   lpUserSpell = GetSkill( wSpellID );

	Disturbed(DISTURB_CLOSECHEST|DISTURB_CLOSETRADE|DISTURB_UNHIDE);
    DispellInvisibility();
    

    bool restorePreviousState = false;

	// If spell exists and user has it
	if( lpSpell != NULL && lpUserSpell != NULL )
	{

        // If this is an attack spell which does not target self.
        if( lpSpell->attackSpell && uTarget != this )
		{

        }
		else 
        // If this is a non-attack spell and previous autocombat is spell.
        if( !lpSpell->attackSpell && autoCombatAttack.attackType == Attack::spell )
		{
            // Restore previous combat mode.            
            restorePreviousState = true;
        }

        EXHAUST sExhaust = GetExhaust();

        // If player isn't exhausted.
        if( sExhaust.mental <= TFCMAIN::GetRound() )
		{
		    WORD wManaCost = static_cast< WORD >( lpSpell->bfManaCost.GetBoost( this, uTarget ) );
            
            // If player has enough mana.
            if( GetMana() >= wManaCost )
			{
//                MessageBeep( -1 );
                
                /*if( uTarget == NULL ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL4,
                        "Player %s cast spell ID %u (without target).",
                        (LPCTSTR)GetTrueName(),
                        wSpellID,
                        (LPCTSTR)uTarget->GetName( _DEFAULT_LNG )
                    LOG_
                }else{
                    _LOG_DEBUG
                        LOG_DEBUG_LVL4,
                        "Player %s cast spell ID %u on target %s.",
                        (LPCTSTR)GetTrueName(),
                        wSpellID,
                        (LPCTSTR)uTarget->GetName( _DEFAULT_LNG )
                    LOG_
                }*/

                // If the target of the spell is self and this is an attack spell.
                // Or if the spell is not an attack spell and the current auto-combat
                //    mode is spell mode.
                if( lpSpell->attackSpell && uTarget == this/* ||
                    !lpSpell->attackSpell && autoCombatAttack.attackType == Attack::spell*/ )
				{
                    StopAutoCombat();
                }
                    

                // Activate the spell!
                boReturn = SpellMessageHandler::ActivateSpell(
			        wSpellID,			
			        this,
			        NULL,
			        uTarget,
			        uTarget->GetWL()
		        );
                // If the spell didn't fail
                if( boReturn )
				{
                    // Deduct mana.
                    UseSpellEnergy( wManaCost );
                }
				else
				{
                    if( !restorePreviousState )
					{
                        // Stop autocombat if the spell did not function.
                        StopAutoCombat();
                    }
                }
            }
			else
			{
				// If player ran out of mana in casting autocombat.
                if( autoCombatAttack.attackType == Attack::spell )
				{
                    StopAutoCombat();
                }

                TELL_PLAYER( 19 );
            }
        }
		else
		{
            TELL_PLAYER( 18 );
        }

        if( restorePreviousState )
		{
            RestorePreviousAutoCombatState();
        }
    }

	return boReturn;
}

//////////////////////////////////////////////////////////////////////////////////////////
// This function allows a user to cast a spell
// 
// Return: BOOL, TRUE if spell message was sent.
// BLInfo : it seems to be linked to spells which are not linked to Spellbook
//          like effects, sub-hooks and stuff, for spell book, check next function.
//////////////////////////////////////////////////////////////////////////////////////////
BOOL Character::CastSpellDirect(WORD wSpellID,Unit *uTarget)
{	
   BOOL boReturn = FALSE;	
   
   TRACE( "\r\nReceive spell ID=%u", wSpellID );
   
   LPSPELL_STRUCT lpSpell     = SpellMessageHandler::GetSpell( wSpellID );

   Disturbed(DISTURB_CLOSECHEST|DISTURB_CLOSETRADE|DISTURB_UNHIDE);
   DispellInvisibility();
   
  
   
   // If spell exists and user has it
   if( lpSpell != NULL)
   {
      // Activate the spell!
      boReturn = SpellMessageHandler::ActivateSpell(wSpellID,this,NULL,uTarget,uTarget->GetWL());
   }
   
   return boReturn;
}


//////////////////////////////////////////////////////////////////////////////////////////
BOOL Character::CastSpell
//////////////////////////////////////////////////////////////////////////////////////////
// This function allows a user to cast a spell
// 
(
 WORD wSpellID,		// The spell's ID.
 WorldPos wlPos		// WorldPos of target spell area. 
)
// Return: BOOL, TRUE if spell message was sent.
//////////////////////////////////////////////////////////////////////////////////////////
{
	BOOL boReturn = FALSE;

    TRACE( "\r\nReceive spell ID=%u", wSpellID );

	LPSPELL_STRUCT lpSpell     = SpellMessageHandler::GetSpell( wSpellID );
	LPUSER_SKILL   lpUserSpell = GetSkill( wSpellID );

	Disturbed(DISTURB_CLOSECHEST|DISTURB_CLOSETRADE|DISTURB_UNHIDE);
    DispellInvisibility();


	// If spell exists and user has it
	if( lpSpell != NULL && lpUserSpell != NULL )
	{
        EXHAUST sExhaust = GetExhaust();

        // If player isn't exhausted.
        if( sExhaust.mental <= TFCMAIN::GetRound() )
		{
            // Get the mana cost.
            WORD wManaCost = static_cast< WORD >( lpSpell->bfManaCost.GetBoost( this ) );
            
            if( GetMana() >= wManaCost ){
                /*if( wlPos.X == 0 && wlPos.Y == 0 ){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL4,
                        "Player %s cast spell ID %u on himself",
                        (LPCTSTR)GetTrueName(),
                        wSpellID,
                        wlPos.X,
                        wlPos.Y,
                        GetWL().world                    
                    LOG_
                }else{
                    _LOG_DEBUG
                        LOG_DEBUG_LVL4,
                        "Player %s cast spell ID %u on position %u, %u, %u.",
                        (LPCTSTR)GetTrueName(),
                        wSpellID,
                        wlPos.X,
                        wlPos.Y,
                        GetWL().world                    
                    LOG_
                }*/
                                
                // Activate the spell!
		        boReturn = SpellMessageHandler::ActivateSpell(
			        wSpellID,		
			        this,
			        NULL,
			        NULL,
			        wlPos
                );

                if( boReturn )
				{
                    // Deduct mana.
                    UseSpellEnergy( wManaCost );
                }
            }
			else
			{
                TELL_PLAYER( 19 );
            }
        }
		else
		{
            TELL_PLAYER( 18 );
        }
	}

	return boReturn;
}


//////////////////////////////////////////////////////////////////////////////////////////
void Character::use_item
//////////////////////////////////////////////////////////////////////////////////////////
//  Uses an item. Also used for robbing.
// 
(
 unsigned long which_item, // The ID of the item to use/rob.
 Unit *TargetPlayer        // Object's usage target.
)
//////////////////////////////////////////////////////////////////////////////////////////
{



	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
    const INT InBackpack = 1;
    const INT InEquip = 2;



    Disturbed();
    
    BOOL done = FALSE;
    DWORD dwReason = OBJECT_DISTURB_USE;

    int nWhere;

    if(!backpack)
	{
        return;
    }

	Objects *lpuUnit = NULL;
    backpack->Lock();
    backpack->ToHead();
	while(backpack->QueryNext() && !done)
	{
		lpuUnit = static_cast< Objects *>( backpack->Object() );
		if( lpuUnit->GetID() == which_item)
		{
			lpuUnit->SendUnitMessage(MSG_OnDisturbed, lpuUnit, this, this, &dwReason );
			if( lpuUnit->GetMark() & MARK_DELETION )
			{				
	            // Update the quantity.
                lpuUnit->Remove();
                if( lpuUnit->GetQty() == 0 )
				{
                    backpack->Object()->DeleteUnit();
                    backpack->Remove();
                }
			}
			else
			{
				done = TRUE;
			}
		}
			
	}
    backpack->Unlock();

    // if it wasn't found in the backpack
	if( !done )
	{
		// checks for any equiped spellbook
		int i;
		for(i = 0; i < EQUIP_POSITIONS; i++)
		{
			if(equipped[i])
				if( equipped[i]->GetID() == which_item)
				{
					 // if it is equiped, use it!
                    lpuUnit = static_cast< Objects * >( equipped[i] );
					lpuUnit->SendUnitMessage(MSG_OnDisturbed, lpuUnit, this, this, &dwReason );
					if( lpuUnit->GetMark() & MARK_DELETION )
					{
                        lpuUnit->DeleteUnit();
						equipped[ i ] = NULL;
					}
					else
					{
						done = TRUE;
                        nWhere = i;
					}
				}
		}
    }
	else
	{
        nWhere = 0xFFFF;
    }

	// If the item wasn't found in the equipment.
    if( !done )
	{
        return;
    }

    DWORD itemUsed = 0;
	lpuUnit->SendUnitMessage(MSG_OnUse, lpuUnit, this, TargetPlayer, NULL, &itemUsed );

	// If the itemUsed flag wasn't set.
	if( itemUsed == 0 )
	{
		// Tell the user that using the item did nothing.
		TELL_PLAYER( 7683 );
	}

    // If unit must not be deleted.
    if( !( lpuUnit->GetMark() & MARK_DELETION ) )
	{
        return;
    }

    // Item must be removed from backpack
    if( nWhere == 0xFFFF )
	{
        // Find item
	    backpack->Lock();
        backpack->ToHead();
	    done = FALSE;
        while(backpack->QueryNext() && !done )
		{
		    Objects *backpackItem = static_cast< Objects * >( backpack->Object() );
            
            // If object was found
            if( lpuUnit == backpackItem )
			{
                backpackItem->Remove();
                if( backpackItem->GetQty() == 0 )
				{
                    // Remove item from backpack.                                
                    backpack->Object()->DeleteUnit();
                    backpack->Remove();
                }

                done = TRUE;
            }
        }
        backpack->Unlock();

        // If backpack changed
        if( done )
		{
            // Update user's backpack.
            TFCPacket sending;
            sending << (RQ_SIZE)RQ_ViewBackpack;
			sending << (char)0;	// Player may not want to view its backpack.
			sending << (long)GetID();
			PacketBackpack( sending );
            SendPlayerMessage( sending );
        }
    // Item must be removed from its equip position.
    }
	else
	{
        // Delete the equipped item
        if( equipped[ nWhere ] != NULL )
		{
            lpuUnit = static_cast< Objects * >( equipped[ nWhere ] );
            equipped[ nWhere ] = NULL;
            lpuUnit->DeleteUnit();
        }           
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
bool Character::UseItemByAppearance
//////////////////////////////////////////////////////////////////////////////////////////
//  Uses an item according to its visual appearance.
// 
(
 WORD wAppearance,		// The item's appearance.
 Unit *TargetPlayer		// Object's usage target.
)
// Return: bool, true if an item was found, false instead.
//////////////////////////////////////////////////////////////////////////////////////////
{
    DWORD dwReason = OBJECT_DISTURB_USE;
    bool boDestroyItem = false;

	Disturbed();//DC
    // If there is no backpack.
    if( backpack == NULL )
	{
        return false;
    }

    Objects *lpItem = NULL; // Item not found by default.
       
    backpack->Lock();
    backpack->ToHead();
    // Scroll through the backpack    
    while( backpack->QueryNext() && lpItem == NULL )
	{
        // If an item with the requested appearance is found.
        if( backpack->Object()->GetStaticReference() == wAppearance )
		{
            // Set it as the used item.
            lpItem = static_cast< Objects * >( backpack->Object() );
			lpItem->SendUnitMessage(MSG_OnDisturbed, lpItem, this, this, &dwReason );
			if( lpItem->GetMark() & MARK_DELETION )
			{				
	            // Update the quantity.//DC
                lpItem->Remove();
                if( lpItem->GetQty() == 0 )
				{
                    backpack->Object()->DeleteUnit();
                    backpack->Remove();
                }
			}else{
				boDestroyItem = TRUE;
			}
        }
    }
    backpack->Unlock();

    if( lpItem != NULL )
	{        
        // Send an OnUse message.
        DWORD itemUsed = 0;
		lpItem->SendUnitMessage(MSG_OnUse, lpItem, this, TargetPlayer, NULL, &itemUsed );

		// If the itemUsed flag wasn't set.
		if( itemUsed == 0 )
		{
			// Tell the user that using the item did nothing.
			TELL_PLAYER( 7683 );
		}

        // If the OnUse message destroyed the item
        if( lpItem->GetMark() & MARK_DELETION )
		{
            boDestroyItem = true;
		}
		else
		{
            boDestroyItem = false;
        }

		bool done = false;
        if( boDestroyItem == true )
		{
			// Find item
			backpack->Lock();
			backpack->ToHead();
			while(backpack->QueryNext() && !done )
			{
				Objects *backpackItem = static_cast< Objects * >( backpack->Object() );
				// If object was found
				if( lpItem == backpackItem )
				{
					backpackItem->Remove();
					if( backpackItem->GetQty() == 0 )
					{
						// Remove item from backpack.                                
						backpack->Object()->DeleteUnit();
						backpack->Remove();
					}
					
					done = TRUE;
				}
			}
			backpack->Unlock();
		}

		if(done == true )
		{
			// Update backpack 
			TFCPacket sending;
			sending << (RQ_SIZE)RQ_ViewBackpack;
			sending << (char)0;	// Player may not want to view its backpack.
			sending << (long)GetID();
			PacketBackpack( sending );
			SendPlayerMessage( sending );
		}
        return true;
    }
    
    // Nothing found.
    return false;

}

////////////////////////////////////////////////////////////////////////////////////////////
// this function should return the ThisPlayer member of a Character (virtual)

Players *Character::GetPlayer(){return ThisPlayer;};

/////////////////////////////////////////////////////////////////////////////////////////////////
// This function trains a player
void Character::TrainUnit(){
	const int WarriorHP = 32;
	const int PriestHP =  25;
	const int ThiefHP = 28;
	const int MageHP = 22;

	
	WORD wLevel = GetLevel();
	
    if(wLevel >= MAX_LEVEL)
	{
		return;
    }
	else if( wLevel == 0 )
	{
        wLevel = 1;
    }


	TFCPacket sending;
	//	TRACE("\r\n\r\nMust have %G, have %G for level %u\r\n", (double)sm_n64XPchart[dwLevel], (double)GetXP(), dwLevel);
	sending << (RQ_SIZE)RQ_XPchanged;
	sending << (long)(GetXP() >> 32);
	sending << (long)GetXP();

	SendPlayerMessage( sending );


	if(sm_n64XPchart[wLevel] < GetXP())
	{
		// If level is under MAX_LEVEL, gain a level!!
		if( wLevel < MAX_LEVEL )
		{
            CString csReport;
            CString csText;

            // Set the value in Unit but do not echo the value until the end of the training
            // session by using Character::SetLevel()
            wLevel++;          			
            Unit::SetLevel( wLevel );
			
            csReport.Format( "Player %s gained a level! ( now level %u ).", (LPCTSTR)GetTrueName(), wLevel );

			wNbStatPnts += 5;
			wNbSkillPnts += (WORD)( m_bSkillPnt[ (WORD)wLevel / 10 ] );

            csText.Format( "\r\n   Gained 5 stat points and %u skill points.", m_bSkillPnt[ (WORD)wLevel / 10 ] );
            csReport += csText;
				
			DWORD dwHPGain;

			DWORD dwMaxHP = GetTrueMaxHP();          
            DWORD dwHP = GetHP();

            dwHPGain = rnd.roll( dice( 1, 3 ) ) + 5 + ( GetTrueEND() / 20 ); 
            
            dwMaxHP += dwHPGain;
            dwHP += dwHPGain;
            
            csText.Format( "\r\n   Gained %u hit points. Now ( %u/%u )", dwHPGain, dwHP, dwMaxHP );
            csReport += csText;

            SetMaxHP( dwMaxHP );
			SetHP( dwHP, true );

            WORD wManaGain;
            WORD wMaxMana = GetTrueMaxMana();
            WORD wMana = GetMana();

            wManaGain = rnd( 1, 3 ) + 2 + ( GetTrueINT() / 30 ) + ( GetTrueWIS() / 60 );
            
            wMaxMana    += wManaGain;
            wMana       += wManaGain;

            csText.Format( "\r\n   Gained %u mana points. Now ( %u/%u )", wManaGain, wMana, wMaxMana );
            csReport += csText;

            SetMaxMana( wMaxMana );
            SetMana( wMana );
            
			tlusSkills[Hook_OnTraining].ToHead();
			while(tlusSkills[Hook_OnTraining].QueryNext())
			{
				LPUSER_SKILL lpusUserSkill = tlusSkills[Hook_OnTraining].Object();
			
				Skills::ExecuteSkill(lpusUserSkill->GetSkillID(), HOOK_TRAINING,
					this, NULL, NULL, NULL, NULL, lpusUserSkill);
			}

			sending.Destroy();

            _LOG_PC
                LOG_MISC_1,
                (char *)(LPCTSTR)csReport
            LOG_

            // Update the level and echo the change to the player and the group members.
            SetLevel(wLevel);

            // If player is in a group.
            if( GetGroup() != NULL )
			{
                // Update all members.
                GetGroup()->UpdateGroupListing();
            }
			
			TRACE(_T("\r\nPlayer gained his level %u\r\n"), wLevel);
		}
	}
}

/*******************************************************************************************************/
int Character::attack(LPATTACK_STRUCTURE blow, Unit *Target)
{	
	// If this call is only a call to query the AttackSkill
    Disturbed(DISTURB_CLOSECHEST|DISTURB_CLOSETRADE);

    // Minimum of 500ms move and attack exhaust.
    DealExhaust( 500, 0, 500 );

	blow->Strike += GAME_RULES::GetNaturalDamage(this);
	blow->lAttackSkill = GetATTACK();

	// calculate precision here
	blow->Precision = GAME_RULES::GetBlowPrecision(blow->lAttackSkill, blow->lDodgeSkill, GetAGI(), Target->GetAGI() );
	
	int attackID;
	if(equipped[body])         equipped[body]        ->SendUnitMessage(MSG_OnAttack, equipped[body], this, Target, blow, &attackID);
	if(equipped[feet])         equipped[feet]        ->SendUnitMessage(MSG_OnAttack, equipped[feet], this, Target, blow, &attackID);
	if(equipped[gloves])       equipped[gloves]      ->SendUnitMessage(MSG_OnAttack, equipped[gloves], this, Target, blow, &attackID);
	if(equipped[helm])         equipped[helm]        ->SendUnitMessage(MSG_OnAttack, equipped[helm], this, Target, blow, &attackID);
	if(equipped[legs])         equipped[legs]        ->SendUnitMessage(MSG_OnAttack, equipped[legs], this, Target, blow, &attackID);
	if(equipped[belt])         equipped[belt]        ->SendUnitMessage(MSG_OnAttack, equipped[belt], this, Target, blow, &attackID);
	if(equipped[cape])         equipped[cape]        ->SendUnitMessage(MSG_OnAttack, equipped[cape], this, Target, blow, &attackID);
	if(equipped[ring1])        equipped[ring1]       ->SendUnitMessage(MSG_OnAttack, equipped[ring1], this, Target, blow, &attackID);	
	if(equipped[ring2])        equipped[ring2]       ->SendUnitMessage(MSG_OnAttack, equipped[ring2], this, Target, blow, &attackID);
	if(equipped[bracelets])    equipped[bracelets]   ->SendUnitMessage(MSG_OnAttack, equipped[bracelets], this, Target, blow, &attackID);
	if(equipped[necklace])     equipped[necklace]    ->SendUnitMessage(MSG_OnAttack, equipped[necklace], this, Target, blow, &attackID);
	if(equipped[weapon_right]) equipped[weapon_right]->SendUnitMessage(MSG_OnAttack, equipped[weapon_right], this, Target, blow, &attackID);		
	if(equipped[weapon_right] != equipped[weapon_left] )// if it's not a two handed weapon
   {
      if(equipped[weapon_left])
      {
         _item *obj = NULL;
		   equipped[weapon_left ]->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &obj);
		 // NIGHTMARE:: Fix problem on left hand with arrow hook
         if(obj && obj->item_type == 1 && obj->weapon.ranged == 0)
         {
            // on compte pas le strike ici des dual weapon, le skill comptera le degat...
         }
         else
            equipped[weapon_left] ->SendUnitMessage(MSG_OnAttack, equipped[weapon_left], this, Target, blow, &attackID);
      }
   }
	

	blow->Strike += QueryBoost( STAT_DAMAGE );
        
    // If the target isn't the attacker. Defensive purposes only.
    if( Target != this )
	{
        QueryEffects( MSG_OnAttack, blow, NULL, Target );
    }

return 1; // attack ID 1
}
/*******************************************************************************************************/
int Character::attacked(LPATTACK_STRUCTURE blow, Unit *attacker)
{
/*		body		 = 0,
		feet		 = 1,
		gloves		 = 2,
		helm		 = 3,
		legs		 = 4,
		rings		 = 5,
		bracelets    = 6,
		necklace	 = 7,
		weapon_right = 8,
		weapon_left  = 9,
		two_hands    = 10,.
		ring1        = 11,
		ring2        = 12,
		weapon       = 13*/
//	blow->Strike -= (ViewFlag(__FLAG_END) / 15);
	WORD wDisturbedFlags = 0|DISTURB_CLOSECHEST|DISTURB_CLOSETRADE;
	if (theApp.dwRobWhileBeingAttackedEnabled) wDisturbedFlags |= DISTURB_DONTCANCELROB;
    Disturbed(wDisturbedFlags);

	// Call OnAttacked for all equipped objects.
    if(equipped[ring1])		equipped[ring1]		->SendUnitMessage(MSG_OnAttacked, equipped[ring1], this, attacker, blow, NULL);
	if(equipped[ring2])		equipped[ring2]		->SendUnitMessage(MSG_OnAttacked, equipped[ring2], this, attacker, blow, NULL);
	if(equipped[bracelets]) equipped[bracelets]	->SendUnitMessage(MSG_OnAttacked, equipped[bracelets], this, attacker, blow, NULL);
	if(equipped[necklace])	equipped[necklace]	->SendUnitMessage(MSG_OnAttacked, equipped[necklace], this, attacker, blow, NULL);
	if(equipped[body])		equipped[body]		->SendUnitMessage(MSG_OnAttacked, equipped[body], this, attacker, blow, NULL);
    if(equipped[belt])		equipped[belt]		->SendUnitMessage(MSG_OnAttacked, equipped[belt], this, attacker, blow, NULL);
	if(equipped[feet])		equipped[feet]		->SendUnitMessage(MSG_OnAttacked, equipped[feet], this, attacker, blow, NULL);
	if(equipped[gloves])	equipped[gloves]	->SendUnitMessage(MSG_OnAttacked, equipped[gloves], this, attacker, blow, NULL);
	if(equipped[helm])		equipped[helm]		->SendUnitMessage(MSG_OnAttacked, equipped[helm], this, attacker, blow, NULL);
	if(equipped[legs])		equipped[legs]		->SendUnitMessage(MSG_OnAttacked, equipped[legs], this, attacker, blow, NULL);
	if(equipped[cape])      equipped[cape]        ->SendUnitMessage(MSG_OnAttacked, equipped[cape], this, attacker, blow, NULL);
    // If item isn't a two handed weapon
    if( equipped[ weapon_right ] == equipped[ weapon_left ] )
	{
        if(equipped[ weapon_right ]) equipped[ weapon_right ]->SendUnitMessage(MSG_OnAttacked, equipped[ weapon_right ], this, attacker, blow, NULL);
    }
	else
	{
        // Otherwise query both hand positions for any shields.
        if(equipped[ weapon_right ]) equipped[ weapon_right ]->SendUnitMessage(MSG_OnAttacked, equipped[ weapon_right ], this, attacker, blow, NULL);
        if(equipped[ weapon_left ]) equipped[ weapon_left ]->SendUnitMessage  (MSG_OnAttacked, equipped[ weapon_left ],  this, attacker, blow, NULL);
    }
    
    // Deduct the player's AC from the blow.
    blow->Strike -= GetAC();
    // Strike cannot be < 0
    blow->Strike = blow->Strike < 0 ? 0 : blow->Strike;
    
    TRACE(_T("Player got attacked, Strike = %u\r\n"), blow->Strike);

	// Then process all attacked-intrinsic skills
	tlusSkills[Hook_OnAttacked].ToHead();
	
	while(tlusSkills[Hook_OnAttacked].QueryNext())
	{
		LPUSER_SKILL lpusUserSkill = tlusSkills[Hook_OnAttacked].Object();
		
		Skills::ExecuteSkill(lpusUserSkill->GetSkillID(), HOOK_ATTACKED,
			this, NULL, attacker, blow, NULL, lpusUserSkill);
	}


    // If the attacking unit isn't this character.
    if( attacker != this ){
	    QueryEffects( MSG_OnAttacked, blow, NULL, attacker );
    }

	//	*strike = 0; // aren't we a bit powerfull eh? :)
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::Death
//////////////////////////////////////////////////////////////////////////////////////////
// kills the player
// 
(
	LPATTACK_STRUCTURE blow,	// Attack structure that killed the player, NULL if none,
	Unit *WhoHit				// Unit who killed the player, NULL if none.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	const int LUCK_LIFE_SAVER = 1000;

    Players *lpPlayer = static_cast< Players * >( GetPlayer() );


    // If character is already dead or is a god which cannot die.
    if( IsDead() || ( lpPlayer->GetGodFlags() & GOD_CANNOT_DIE ) )
	{
        SetHP(0, true);
        return;
    }
    // If player isn't in-game.
    if( !lpPlayer->in_game )
	{
        SetHP(1, true);
		_LOG_DEATH
            LOG_DEBUG_LVL1,
            "Player %s (Pos %u, %u, %u ) got killed while NOT ingame, hu ?",
            (LPCTSTR)lpPlayer->self->GetTrueName(),           
            lpPlayer->self->GetWL().X,
            lpPlayer->self->GetWL().Y,
            lpPlayer->self->GetWL().world
        LOG_
        return;
    }

    KillCreature();
    
	Lock();

	// Tell the player that the gem of destiny saved it.
	TELL_PLAYER( 16 );	

    StopAutoCombat();
	
    Players *thisPlayer = GetPlayer();
	if( WhoHit != NULL )
	{
		// Creature who hit no longer is in combat
		WhoHit->Do(wandering);
		WhoHit->SetTarget(WhoHit->GetBond());

        if( WhoHit->GetType() == U_PC ){
            
            Character *targetChar = static_cast< Character * >( WhoHit );
            Players *targetPlayer = targetChar->GetPlayer();

            if( WhoHit == this ){
                _LOG_DEATH
                    LOG_MISC_1,
                    "Player %s (Id %u, Acct %s, Lvl %u, Pos %u, %u, %u) killed himself (DoT)",
                    (LPCTSTR)GetTrueName(),
                    GetID(),
                    (LPCTSTR)thisPlayer->GetFullAccountName(),
                    GetLevel(),
                    GetWL().X,
                    GetWL().Y,
                    GetWL().world
                LOG_
            }else{
                _LOG_DEATH
                    LOG_MISC_1,
                    "PVP: Player %s (Id %u, Acct %s, Lvl %u, Pos %u, %u, %u) killed by player %s (Id %u, Acct %s, Lvl %u, Pos %u, %u, %u)",
                    (LPCTSTR)GetTrueName(),
                    GetID(),
                    (LPCTSTR)thisPlayer->GetFullAccountName(),
                    GetLevel(),
                    GetWL().X,
                    GetWL().Y,
                    GetWL().world,
                    (LPCTSTR)WhoHit->GetName( _DEFAULT_LNG ),
                    WhoHit->GetID(),
                    (LPCTSTR)targetPlayer->GetFullAccountName(),
                    WhoHit->GetLevel(),
                    WhoHit->GetWL().X,
                    WhoHit->GetWL().Y,
                    WhoHit->GetWL().world
                LOG_

				//BLBLBL : System to report PVP deaths on PVP channel.
				PVPSentence pvp;
				pvp.SayOnDeathChannel((LPCTSTR)WhoHit->GetName( _DEFAULT_LNG ),(LPCTSTR)GetTrueName());

            }
        }else{
            _LOG_DEATH
                LOG_MISC_1,
                "Player %s (Id %u, Acct %s, Lvl %u, Pos %u, %u, %u ) got killed by monster %s",
                (LPCTSTR)GetTrueName(),
                GetID(),
                (LPCTSTR)thisPlayer->GetFullAccountName(),
                GetLevel(),
                GetWL().X,
                GetWL().Y,
                GetWL().world,
                (LPCTSTR)WhoHit->GetName( _DEFAULT_LNG )
            LOG_
        }
    }else{
        _LOG_DEATH
            LOG_DEBUG_LVL1,
            "Player %s (Id %u, Acct %s, Lvl %u, Pos %u, %u, %u ) got killed by some unknown unit.",
            (LPCTSTR)GetTrueName(),
            GetID(),
            (LPCTSTR)thisPlayer->GetFullAccountName(),
            GetLevel(),
            GetWL().X,
            GetWL().Y,
            GetWL().world
        LOG_
    }

	TRACE(_T("DEATH"));
//	WorldMap *wl;
//	Unit *obj;

	// Create a death data structure and query each objects
	// to know if any of them can do anything about this death.
//	DEATH_DATA ddDeathData;

	BOOL boSavePlayer = FALSE;
	CString csText;
	CString csTemp;

    SendGlobalEffectMessage( MSG_OnDeath, NULL, NULL, NULL );
	/*
    // If player is high enough to be worth having a death report.
	if(GetLevel() > MIN_LEVEL_DEATH_REPORT)
	{
		csText = "\r\nCurrent stats:\r\n";
		csTemp.Format(_T("	LEVEL:	%u\r\n"), GetLevel());
		csText += csTemp;
		csTemp.Format(_T("	HP:	%u\r\n"), GetMaxHP());
		csText += csTemp;
		csTemp.Format(_T("	AGI:	%u(%u)\r\n"), GetTrueAGI(), GetAGI());
		csText += csTemp;
		csTemp.Format(_T("	END:	%u(%u)\r\n"), GetTrueEND(), GetEND());
		csText += csTemp;
		csTemp.Format(_T("	INT:	%u(%u)\r\n"), GetTrueINT(), GetINT());
		csText += csTemp;
		csTemp.Format(_T("	STR:	%u(%u)\r\n"), GetTrueSTR(), GetSTR());
		csText += csTemp;
		csTemp.Format(_T("	WIS:	%u(%u)"), GetTrueWIS(), GetWIS());
		csText += csTemp;
        backpack->Lock();

        _LOG_DEATH
            LOG_DEBUG_LVL2,
            (char *)(LPCTSTR)csText
        LOG_
        csText.Empty();
        csTemp.Empty();

   		csTemp += _T("\r\nBackpack: ");

        
        if( backpack->NbObjects() == 0 ){
            csTemp = _T("(empty)");
        }
		else
		{        
            int nItemsLogged = 0;
            backpack->ToHead();		
	
	    	while(backpack->QueryNext()){
		    	csTemp += backpack->Object()->GetName( GetLang() );
			    csTemp += _T(", ");
                if( !(nItemsLogged % 10) && nItemsLogged != 0 ){
                    _LOG_DEATH
                        LOG_DEBUG_LVL2,
                        (char *)(LPCTSTR)csTemp
                    LOG_
                    csTemp.Empty();
                }
                nItemsLogged++;
		    }
        }
        backpack->Unlock();
        _LOG_DEATH
            LOG_DEBUG_LVL2,
            (char *)(LPCTSTR)csTemp
        LOG_
        
		csTemp = _T("\r\nEquipped: ");
                		
		int nItemsLogged = 0;
        int i;
		for(i = 0; i < EQUIP_POSITIONS; i++)
		{
            
			if(equipped[i])
			{
				csTemp += equipped[i]->GetName( GetLang() );
				csTemp += _T(", ");
                if( !(nItemsLogged % 10) && nItemsLogged != 0 ){
                    _LOG_DEATH
                        LOG_DEBUG_LVL2,
                        (char *)(LPCTSTR)csTemp
                    LOG_
                    csTemp.Empty();
                }
                nItemsLogged++;
			}
		}
        _LOG_DEATH
            LOG_DEBUG_LVL2,
            (char *)(LPCTSTR)csTemp
        LOG_
        csText.Empty();
    }*/

    // Get the WL before it is changed.
    WorldPos wlPlayerPos = GetWL();

    __int64_t nXP = xp; // __int64

    DWORD goldLoss = 0;

	// If player died in an Arena Location
	list< sArenaLocation >::iterator i;
	bool boFound = false;	
	for( i = theApp.arenaLocationList.begin(); i != theApp.arenaLocationList.end(); ++i )
	{
		// If player is in the same world as the current location
		if( wlPlayerPos.world == (*i).wlTopLeft.world )
		{
			// If player is in the good x range
			if( wlPlayerPos.X >= (*i).wlTopLeft.X && wlPlayerPos.X <= (*i).wlBottomRight.X )
			{
				// And if player is in the good y range
				if( wlPlayerPos.Y >= (*i).wlTopLeft.Y && wlPlayerPos.Y <= (*i).wlBottomRight.Y )
				{
					// Player is in this kind of area!
					boFound = true;					
					break;
				}
			}
		}
	}

	// Normal death
	if( boFound == false )
	{
		// List of objects which should be spilled on the floor as the player 'dies'
		TemplateList< Unit > equipSpillList;
		TemplateList< Unit > invSpillList;
		GAME_RULES::DeathPenalties( this, WhoHit, &invSpillList, &equipSpillList, goldLoss );

		DWORD oldGold = GetGold();
		if( goldLoss < oldGold ){
			SetGold( oldGold - goldLoss );
		}else{
			SetGold( 0 );
		}

		csTemp.Format( "\r\nPlayer lost %u gold pieces.", goldLoss );

		csText.Empty();
		csTemp.Empty();

		// If player is high enough to be worth logging.
		if( GetLevel() > MIN_LEVEL_DEATH_REPORT ){
			// Log xp loss.
			DWORD dwXPloss = static_cast< DWORD >( nXP - xp );
			csTemp.Format( "\r\nPlayer lost %u experience points.", dwXPloss );
			csText += csTemp;
			int nItemsLogged = 0;
        
			csText += "\r\nInventory items lost: ";
			// Scroll through the list of items lost on the floor.
			if( invSpillList.NbObjects() == 0 ){
				csText += "(none)";
			}else{    
				invSpillList.ToHead();
				while( invSpillList.QueryNext() ){            
					csTemp.Format( "%s, ", invSpillList.Object()->GetName( _DEFAULT_LNG ).c_str() );
					csText += csTemp;
					if( !(nItemsLogged % 10) && nItemsLogged != 0 ){
						_LOG_DEATH
							LOG_DEBUG_LVL2,
							(char *)(LPCTSTR)csText
						LOG_
						csText.Empty();                
					}
					nItemsLogged++;
				}
			}
			nItemsLogged = 0;
			_LOG_DEATH
				LOG_DEBUG_LVL2,
				(char *)(LPCTSTR)csText
			LOG_
        
			csText = "\r\nEquipped items lost: ";
			// Scroll through the list of items lost on the floor.
			if( equipSpillList.NbObjects() == 0 ){
				csText += "(none)";
			}else{    
				equipSpillList.ToHead();
				while( equipSpillList.QueryNext() ){            
					csTemp.Format( "%s, ", equipSpillList.Object()->GetName( _DEFAULT_LNG ).c_str() );
					csText += csTemp;
					if( !(nItemsLogged % 10) && nItemsLogged != 0 ){
						_LOG_DEATH
							LOG_DEBUG_LVL2,
							(char *)(LPCTSTR)csText
						LOG_
						csText.Empty();                
					}
					nItemsLogged++;
				}
			}
		}
		_LOG_DEATH
			LOG_DEBUG_LVL2,
			(char *)(LPCTSTR)csText
		LOG_
		csText.Empty();                


		Unit *lpObject;
		//unsigned int param[4];
		//int k = rnd( 0, 7 );//BLBL déplacé plus bas et initialisé à 0

		// Transfert the inventory and equipped spill list into a single list for dropping.
		TemplateList< Unit > tlObjSpillList;
		invSpillList.ToHead();
		while( invSpillList.QueryNext() ){
			tlObjSpillList.AddToTail( invSpillList.Object() );
		}
		equipSpillList.ToHead();
		while( equipSpillList.QueryNext() ){
			tlObjSpillList.AddToTail( equipSpillList.Object() );
		}

		WorldMap *wlWorld = TFCMAIN::GetWorld( wlPlayerPos.world );
		if( wlWorld ){    
			// Disperse all spilled items around the unit's corpse.
			tlObjSpillList.ToHead();
			int k = 0;
			while( tlObjSpillList.QueryNext() ){

				lpObject = tlObjSpillList.Object();
				WorldPos wlFoundPos = wlPlayerPos;
				/*switch( k++ ){ 
					case 0: wlFoundPos.Y = wlPlayerPos.Y + rnd( 1, 2 ); break;
					case 1: wlFoundPos.X = wlPlayerPos.X + rnd( 1, 2 ); break;
					case 2: wlFoundPos.Y = wlPlayerPos.Y - rnd( 1, 2 ); break;
					case 3: wlFoundPos.X = wlPlayerPos.X - rnd( 1, 2 ); break;
					case 4: wlFoundPos.X = wlPlayerPos.X + rnd( 1, 2 );
							wlFoundPos.Y = wlPlayerPos.Y + rnd( 1, 2 ); break;
					case 5: wlFoundPos.X = wlPlayerPos.X + rnd( 1, 2 );
							wlFoundPos.Y = wlPlayerPos.Y - rnd( 1, 2 ); break;
					case 6: wlFoundPos.X = wlPlayerPos.X - rnd( 1, 2 ); 
							wlFoundPos.Y = wlPlayerPos.Y + rnd( 1, 2 ); break;
					case 7: wlFoundPos.X = wlPlayerPos.X - rnd( 1, 2 );
							wlFoundPos.Y = wlPlayerPos.Y - rnd( 1, 2 ); break;
				} 
				k = k > 7 ? 0 : k;*///BLBLBL : on pose tout au sol direct
				
				// If spot isn't a valid one, make the world find it..!
				if( wlWorld->IsBlocking( wlFoundPos ) ){
					wlFoundPos = wlWorld->FindValidSpot( wlPlayerPos, 3, true );//BLBLBL 3=>4=>3
				   //true dans le dernier parametre car on ne veut surtout pas que des items se vaporize en ne trouvant pas de place !
				}

				// if it found a valid position
				if ( wlWorld->IsValidPosition(wlFoundPos) ) {
			
					wlWorld->deposit_unit( wlFoundPos, lpObject );
					//lpObject->BroadcastPopup( wlFoundPos,1 );//BLBL ici y a un ,1 pour lancer un broadcast REEL à tous les gens autour.
					lpObject->BroadcastPopup( wlFoundPos );//visiblement le 1 marche pas bien mieux, je le vire
						
					// Log spilled item.
					_LOG_ITEMS
						LOG_MISC_1,
						"Player %s 's death at ( %u, %u, %u ) spilled item %s ID( %u ) at ( %u, %u, %u ).",
						(LPCTSTR)GetTrueName(),
						wlPlayerPos.X,
						wlPlayerPos.Y,
						wlPlayerPos.world,
						(LPCTSTR)lpObject->GetName( _DEFAULT_LNG ),
						lpObject->GetStaticReference(),
						wlFoundPos.X,
						wlFoundPos.Y,
						wlFoundPos.world
					LOG_
    							
					//lpObject->BroadcastPopup( wlPlayerPos );//BLBL je vire pour voir //BLBL OK alors ici, y a pas le ,1 (donc on informe juste le joueur qui a droppé)
				}else{
					// Log spilled item.
					_LOG_ITEMS
						LOG_MISC_1,
						"Player %s 's death at ( %u, %u, %u ) deleted item %s ID( %u ) instead of drop at ( %u, %u, %u ) because invalid coord.",
						(LPCTSTR)GetTrueName(),
						wlPlayerPos.X,
						wlPlayerPos.Y,
						wlPlayerPos.world,
						(LPCTSTR)lpObject->GetName( _DEFAULT_LNG ),
						lpObject->GetStaticReference(),
						wlFoundPos.X,
						wlFoundPos.Y,
						wlFoundPos.world
					LOG_
					// If no position could be found, destroy the object.
					//tlObjSpillList.DeleteAbsolute();
					tlObjSpillList.Object()->DeleteUnit();
					tlObjSpillList.Remove();
				}
			}
		}else{
			// If no world object could be fetch, destroy list of objects.
			//tlObjSpillList.AnnihilateList();
			tlObjSpillList.ToHead();
			while( tlObjSpillList.QueryNext() ){
				tlObjSpillList.Object()->DeleteUnit();
				tlObjSpillList.Remove();
			}
					_LOG_ITEMS
						LOG_MISC_1,
						"Player %s's death at ( %u, %u, %u ) spilled no items, since world value was not valid.",
						(LPCTSTR)GetTrueName(),
						wlPlayerPos.X,
						wlPlayerPos.Y,
						wlPlayerPos.world
					LOG_

		}

		// Finally fetch death position.
		DWORD dwPosValue = ViewFlag( __FLAG_DEATH_LOCATION );
		BOOL  boDefaultPos = FALSE;
		WorldPos wlTeleportPos;
		
		if( dwPosValue == 0 ){
			// If flag doesn't exist use default death position.
			boDefaultPos = TRUE;
		}else{	
			wlTeleportPos.X = ( (WORD)( dwPosValue >> 20 ) ) & 0x0FFF;	// Strip the first 4 bits of the word.
			wlTeleportPos.Y = ( (WORD)( dwPosValue >> 8 )  ) & 0x0FFF;
			wlTeleportPos.world = ( (BYTE)( dwPosValue ) & 0xFF );

			WorldMap *wlWorld = TFCMAIN::GetWorld( wlTeleportPos.world );

			// If world doesn't exist use default death position.
			if( wlWorld == NULL ){
				boDefaultPos = TRUE;
			}else{
				// If worldpos isn't a valid position use default death position.
				if( !wlWorld->IsValidPosition( wlTeleportPos ) ){
					boDefaultPos = TRUE;
				}
			}
		}
		
		if( boDefaultPos ){
			// Use default death pos.
			wlTeleportPos = wlDeathPos;
		}

		TFCPacket sending;
		sending << (RQ_SIZE)RQ_XPchanged;
		sending << (long)(GetXP() >> 32);
		sending << (long)GetXP();

		SendPlayerMessage( sending );

		WorldPos wlNull = { 0, 0, 0 };
    
		Broadcast::BCSpellEffect( wlPlayerPos, _DEFAULT_RANGE, DEATH_EFFECT_ID, GetID(), 0, wlPlayerPos,wlNull,GetNextGlobalEffectID(),0);//BLBL 20=>_DEFAULT_RANGE

		//BL note : systeme qui lance un sort à la mort du joueur, mais ça ne marche pas bien :
/*		if(theApp.dwDeadSpellID == 0x00)
		{
		   Broadcast::BCSpellEffect( wlPlayerPos, 20, DEATH_EFFECT_ID, GetID(), 0, wlPlayerPos,wlNull,GetNextGlobalEffectID(),0);
		}
		else
		{
		   Broadcast::BCSpellEffect( wlPlayerPos, 20, DEATH_EFFECT_ID, GetID(), 0, wlPlayerPos,wlNull,GetNextGlobalEffectID(),0);
		   BOOL bRet = CastSpellDirect(theApp.dwDeadSpellID, this );
		   if(bRet)
			 Sleep(1000);
		}*/

		//BLBLBL 12/05/2011 tryied to add onDie spell
		if (theApp.dwDeadSpellID != 0x00) {
			CastSpellDirect(theApp.dwDeadSpellID, this );
		}
    

		/*
		   old code to make a pvp ranking by flag
		   changed to be save inside the character table in the database
		// Avoid a crash when vaporizing the unit lol
		if( WhoHit != NULL )
		{		
			// Increase the death flags if a player killed me		
			if( WhoHit->GetType() == U_PC )
			{
				DWORD dwDeathValue = ViewFlag( __FLAG_DEATH_NUMBER, 0 );
				DWORD dwKillValue = WhoHit->ViewFlag( __FLAG_KILL_NUMBER, 0 );
				
				int bPoints = false;
			
				bPoints = CAutoConfig::GetIntValue( T4C_KEY "PVPDeath", "CRIME_POINTS" );

				// Sysop don't wanna count the crime but prefers the point system
				if( bPoints == 1 )
				{
					// Determines the points to give or to take away
					int Range = WhoHit->GetLevel() - this->GetLevel();

					//if( Range >= 100 )//09/12/2010 BLBLBL Score quand on tue un personnage, je vire le malus si on tue un trop faible
					//{
					//	dwDeathValue++;
					//	dwKillValue -= 5;
					//}			
					//else if( Range >= 70 )
					//{
					//	dwDeathValue++;
					//	dwKillValue -= 3;
					//}			
					//else if( Range > 35 )
					//{
					//	dwDeathValue++;
					//	dwKillValue -= 1;
					//}
					//else 
					if (Range >= -25 && Range <= 15 )
					{
						dwDeathValue++;
						dwKillValue++;
					}
					else 
					if( Range <= -100 )
					{
						dwDeathValue++;
						dwKillValue += 4;
					}
					else if( Range <= -50 )
					{
						dwDeathValue++;
						dwKillValue += 3;
					}
					else if( Range < -25 )
					{
						dwDeathValue++;
						dwKillValue += 2;
					}
				}
				else
				{
					dwDeathValue++;
					dwKillValue++;
				}

				SetFlag( __FLAG_DEATH_NUMBER, dwDeathValue );
				WhoHit->SetFlag( __FLAG_KILL_NUMBER, dwKillValue );			
			}
		} */ // asteryth désactivation


		// Avoid a crash when vaporizing the unit lol
		if( WhoHit != NULL )
		{		
			// Increase the death flags if a player killed me
			// and if the player isn't in my guild 
			if( WhoHit->GetType() == U_PC) // && (WhoHit->GetGuildID() != -1 || WhoHit->GetGuildID() != this->GetGuildID())) Commenté tant que y a pas de guilde.
			{
				// asteryth pvp ranking
				// victim stats
				// asteryth DEBUG pour test à commenter par la suite
				
				//_LOG_DEBUG LOG_ALWAYS, "-----" LOG_
				//_LOG_DEBUG LOG_ALWAYS, "PVP Ranking START" LOG_	
				
				int victimTotalDeathNumber = this->GetTotalDeathNumber();
				int victimCurrentDeathNumber = this->GetCurrentDeathNumber();
				int victimBestSerieMurder = this->GetBestSerieMurder();
				int victimCurrentSerieMurder = this->GetCurrentSerieMurder();
				// asteryth DEBUG pour test à commenter par la suite
				// _LOG_DEBUG LOG_ALWAYS, "victimTotalDeathNumber: %i, victimCurrentDeathNumber: %i, victimBestSerieMurder: %i, victimCurrentSerieMurder: %i", victimTotalDeathNumber, victimCurrentDeathNumber, victimBestSerieMurder, victimCurrentSerieMurder LOG_
				// killer stats
				int killerTotalKillNumber = WhoHit->GetTotalKillNumber();
				int killerCurrentKillNumber = WhoHit->GetCurrentKillNumber();
				int killerBestSerieMurder = WhoHit->GetBestSerieMurder();
				int killerCurrentSerieMurder = WhoHit->GetCurrentSerieMurder();
				int killerCurrentPvpPoint = WhoHit->GetCurrentPvpPoint();
				
				// asteryth DEBUG pour test à commenter par la suite
				// _LOG_DEBUG 
				// LOG_ALWAYS, 
				// "killerTotalKillNumber: %i, killerCurrentKillNumber: %i, killerBestSerieMurder: %i, killerCurrentSerieMurder: %i, killerCurrentPvpPoint: %i",
				// killerTotalKillNumber, 
				// killerCurrentKillNumber, 
				// killerBestSerieMurder, 
				// killerCurrentSerieMurder, 
				// killerCurrentPvpPoint 
				// LOG_

				// used for calcul
				int range = this->GetLevel() - WhoHit->GetLevel();
				// PVP_ADDING_POINT = 10
				int adding_point = PVP_ADDING_POINT;
				
				adding_point += range / 10;
				if (victimCurrentSerieMurder >= 0)
				{
					adding_point += victimCurrentSerieMurder;
					if (victimCurrentSerieMurder > victimBestSerieMurder)
						this->SetBestSerieMurder(victimCurrentSerieMurder);
					if (victimCurrentSerieMurder > 0)
						this->SetCurrentSerieMurder(0);
					else
						this->SetCurrentSerieMurder(-1);
				}
				else
				{
					adding_point += victimCurrentSerieMurder / 10;
					this->SetCurrentSerieMurder(victimCurrentSerieMurder - 1);
				}
				if (adding_point <= 0)
					adding_point = 1;
				
				// increase death numbers of the victim
				this->SetTotalDeathNumber(victimTotalDeathNumber + 1);
				this->SetCurrentDeathNumber(victimCurrentDeathNumber + 1);
				// increase killer stats
				WhoHit->SetCurrentPvpPoint(killerCurrentPvpPoint + adding_point);
				if (killerCurrentSerieMurder >= 0)
				{
					WhoHit->SetCurrentSerieMurder(killerCurrentSerieMurder + 1);
					if ((killerCurrentSerieMurder + 1) >= killerBestSerieMurder)
						WhoHit->SetBestSerieMurder(killerCurrentSerieMurder + 1);
				}
				else
				{
					WhoHit->SetCurrentSerieMurder(1);
					if (1 >= killerBestSerieMurder)
						WhoHit->SetBestSerieMurder(1);
				}
				WhoHit->SetTotalKillNumber(killerTotalKillNumber + 1);
				WhoHit->SetCurrentKillNumber(killerCurrentKillNumber + 1);

				TFCPacket stats;
                this->PacketPvpRanking( stats );	
                this->SendPlayerMessage( stats );
				Players *killer = CPlayerManager::GetCharacter(WhoHit->GetName( _DEFAULT_LNG ));
				if (killer)
				{
					stats.Destroy();
					killer->self->PacketPvpRanking( stats );
					killer->self->SendPlayerMessage( stats );
				}
				
				
				// asteryth DEBUG pour test à commenter par la suite
				// _LOG_DEBUG LOG_ALWAYS, "victimTotalDeathNumber: %i, victimCurrentDeathNumber: %i, victimBestSerieMurder: %i, victimCurrentSerieMurder: %i , killerTotalKillNumber: %i, killerCurrentKillNumber: %i, killerBestSerieMurder: %i, killerCurrentSerieMurder: %i, killerCurrentPvpPoint: %i",
				// this->GetTotalDeathNumber(), 
				// this->GetCurrentDeathNumber(), 
				// this->GetBestSerieMurder(), 
				// this->GetCurrentSerieMurder(), 
				// WhoHit->GetTotalKillNumber(), 
				// WhoHit->GetCurrentKillNumber(), 
				// WhoHit->GetBestSerieMurder(), 
				// WhoHit->GetCurrentSerieMurder(), 
				// WhoHit->GetCurrentPvpPoint() 
				// LOG_
				// _LOG_DEBUG LOG_ALWAYS, "PVP Ranking STOP" LOG_
				// _LOG_DEBUG LOG_ALWAYS, "BY ASTERYTH" LOG_
				// _LOG_DEBUG LOG_ALWAYS, "-----" LOG_				
				
			}
		}

		// Teleport user to its death location.
		Teleport( wlTeleportPos, 1 );		//BLBL ai tenté de mettre le téléport AVANT le send global effect

		/////////////
		// Activate the trigger
		SendGlobalEffectMessage( MSG_OnDeath, NULL, NULL, NULL );//BL note : removes/kill all spells/effects

	}
	else
	{
		// Teleport died user to defined recall pos
		if( TFCMAIN::GetWorld( (*i).wlRecallTarget.world )->IsValidPosition( (*i).wlRecallTarget )  )
			Teleport( (*i).wlRecallTarget, 1 );
		else
			Teleport( wlDeathPos, 1 );

		// Teleport attacker to another defined recall pos
		if( TFCMAIN::GetWorld( (*i).wlRecallAttacker.world )->IsValidPosition( (*i).wlRecallAttacker ) && WhoHit != NULL )
			WhoHit->Teleport( (*i).wlRecallAttacker, 1 );

		/////////////
		// Activate the trigger
		SendGlobalEffectMessage( MSG_OnDeath, NULL, NULL, NULL );
	}

	// Set the unit's under block to SAFE_HAVEN to avoid that a PC already at the death pos, casting a normal block,
	// kills the player.
	SetUnderBlock( __INDOOR_SAFE_HAVEN );	

	Unlock();
}
/*******************************************************************************************************/
int Character::hit(LPATTACK_STRUCTURE blow, Unit *WhoHit)
{

	Lock();

	this->Disturbed();//BLBLBL on disturb en cas où on est hit

	// Then process all hit-intrinsic skills
	tlusSkills[Hook_OnHit].ToHead();
	
	while(tlusSkills[Hook_OnHit].QueryNext()){
		LPUSER_SKILL lpusUserSkill = tlusSkills[Hook_OnHit].Object();
		
		Skills::ExecuteSkill(lpusUserSkill->GetSkillID(), HOOK_HIT,
			this, NULL, WhoHit, blow, NULL, lpusUserSkill);
	}

    // If the unit who hit isn't this character.
    if( WhoHit != this ){
        QueryEffects( MSG_OnHit, blow, NULL, WhoHit );
    }

	// This is the final hit, it basically handles death :)
	int HP    = GetHP();
	int MaxHP = GetMaxHP();
	
	TRACE(_T("Max HP = %u "), MaxHP);
	TRACE(_T("HP before hit on player %d"), HP);

	Players *user = (Players *)ThisPlayer;

    if( user != NULL ){
	    if( !( user->GetGodFlags() & GOD_INVINCIBLE ) )
		{
		    HP -= (int)blow->Strike;	
		    TRACE(_T(",,HP after hit on player %d"), HP);
    	}
    }

    // Call OnHit for all equipped items.
    if(equipped[ring1])		equipped[ring1]		->SendUnitMessage(MSG_OnHit, equipped[ring1], this, WhoHit, blow, NULL);
	if(equipped[ring2])		equipped[ring2]		->SendUnitMessage(MSG_OnHit, equipped[ring2], this, WhoHit, blow, NULL);
	if(equipped[bracelets]) equipped[bracelets]	->SendUnitMessage(MSG_OnHit, equipped[bracelets], this, WhoHit, blow, NULL);
	if(equipped[necklace])	equipped[necklace]	->SendUnitMessage(MSG_OnHit, equipped[necklace], this, WhoHit, blow, NULL);
	if(equipped[body])		equipped[body]		->SendUnitMessage(MSG_OnHit, equipped[body], this, WhoHit, blow, NULL);
    if(equipped[belt])		equipped[belt]		->SendUnitMessage(MSG_OnHit, equipped[belt], this, WhoHit, blow, NULL);
	if(equipped[feet])		equipped[feet]		->SendUnitMessage(MSG_OnHit, equipped[feet], this, WhoHit, blow, NULL);
	if(equipped[gloves])	equipped[gloves]	->SendUnitMessage(MSG_OnHit, equipped[gloves], this, WhoHit, blow, NULL);
	if(equipped[helm])		equipped[helm]		->SendUnitMessage(MSG_OnHit, equipped[helm], this, WhoHit, blow, NULL);
	if(equipped[legs])		equipped[legs]		->SendUnitMessage(MSG_OnHit, equipped[legs], this, WhoHit, blow, NULL);
    // If item isn't a two handed weapon
    if( equipped[ weapon_right ] == equipped[ weapon_left ] )
	{
        if(equipped[ weapon_right ]) equipped[ weapon_right ]->SendUnitMessage(MSG_OnHit, equipped[ weapon_right ], this, WhoHit, blow, NULL);
    }
	else
	{
        // Otherwise query both hand positions for any shields.
        if(equipped[ weapon_right ]) equipped[ weapon_right ]->SendUnitMessage(MSG_OnHit, equipped[ weapon_right ], this, WhoHit, blow, NULL);
        if(equipped[ weapon_left ]) equipped[ weapon_left ]->SendUnitMessage  (MSG_OnHit, equipped[ weapon_left ],  this, WhoHit, blow, NULL);
    }
    

    if( HP < 0 )
	{
        HP = 0;
    }
	TFCPacket sending;	
	sending << (RQ_SIZE)RQ_HPchanged; // user already in game or not registred
	sending << (long)HP;
	sending << (long)MaxHP;	
	SendPlayerMessage( sending );

	TRACE( "--Sent message" );
			
	sending.Destroy( );

    if( user != NULL && user->in_game ){
	    if(HP <= 0 && !( user->GetGodFlags() & GOD_INVINCIBLE || user->GetGodFlags() & GOD_CANNOT_DIE ) ){ // if player kinda died..	
            // kill the player.
	        Death( blow, WhoHit );
	    
		    Unlock();
		    return( -1 );
	    }
		else
		{
		    SetHP( HP, false );
	    }
    }
	
	TRACE( "\r\nExiting trainunit" );

	Unlock();
	
	return 0;
}

/*******************************************************************************************/
BOOL Character::Kill(){
	return KillMe;
}
/*******************************************************************************************/
WORD Character::GetCorpse(){
	return Corpse;
}
/***********************************************************************************************/
// Basically resets everything there is to reset on a player
void Character::reset_character(){
	WorldPos WL;
	WL.X = 0xFFFFFFFF;
	WL.Y = 0xFFFFFFFF;
	WL.world = 0xFFFFFFFF;
	SetWL(WL);

	// Destroy all static and dynamic flags on the PC
//	DestroyStaticFlags();
	DestroyFlags();
	
	// removes equipped objects
    DestroyEquipment();

	// removes the backpack	
    backpack->ToHead();
    while(backpack->QueryNext())
	{
        backpack->Object()->DeleteUnit();
        backpack->Remove();
    }

	//Clears the chest
	chest->ResetContainer();


	SetHP(0, false);
	SetMaxHP(1);
	SetMana(0);
	SetMaxMana(0);
	
	SetXP(0);
	SetGold(0, FALSE );
//	int i;
//    for(i = 0; i < NB_CLASS; i++)
//		ClassPoints[i] = 0;

	wNbSkillPnts = 0;
	wNbStatPnts = 0;
	Corpse = 0;
	Appearance = 0;

}
//////////////////////////////////////////////////////////////////////////////////////////////////
/*UINT Character::GetAppearance(){
	return Appearance;
}
void Character::SetAppearance( WORD wAppearance ){
	Appearance = wAppearance;
}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////
int Character::GetXP(){ // __int64
    CAutoLock autoStatsLock( &statsLock );
	return xp;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void Character::SetXP(int XP){ // __int64
    CAutoLock autoStatsLock( &statsLock );
	xp = XP;
}
//////////////////////////////////////////////////////////////////////////////////////////////
TemplateList <Unit> *Character::GetBackpack(){
	return backpack;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Character::SetBackpack(TemplateList <Unit> *LList){
	backpack = LList;
}
//////////////////////////////////////////////////////////////////////////////////////////////
ItemContainer *Character::GetChest() {
	return chest;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Character::SetChest(ItemContainer *newChest){
	chest = newChest;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Character::packet_stats(TFCPacket &packet, bool gameop){
			/*const int __FLAG_AGI					= 20000;
			const int __FLAG_CHA					= 20001;
			const int __FLAG_END					= 20002;
			const int __FLAG_INT					= 20003;
			const int __FLAG_LCK					= 20004;
			const int __FLAG_STR					= 20005;
			const int __FLAG_WIL					= 20006;
			const int __FLAG_WIS					= 20007;
			const int __FLAG_HP						= 20008;*/
	
    if( gameopContext != NULL && !gameop ){
        gameopContext->packet_stats( packet, true );
        return;
    }
    
    packet << (char)GetAGI();
	packet << (char)GetEND();
	packet << (char)GetINT();
	packet << (char)0; // luck
	packet << (char)GetSTR();
	packet << (char)0; // wil
	packet << (char)GetWIS();
	packet << (long)GetMaxHP();
	packet << (long)GetHP();
	packet << (short)GetMaxMana();
	packet << (short)GetMana();
}

///////////////////////////////////////////////////////////////////////////////////////////////
WorldPos Character::MoveUnit(DIR::MOVE where, BOOL boAbsolute, bool boCompressMove, bool boBroadcastMove ){    
	
	WORD wDisturbedFlags = 0|DISTURB_CLOSECHEST|DISTURB_CLOSETRADE;//|DISTURB_UNHIDE; <- If you put UNHIDE, how do you want to use Sneak?!
	
	if (theApp.dwRobWhileWalkingEnabled) wDisturbedFlags |= DISTURB_DONTCANCELROB;
		Disturbed(wDisturbedFlags);

    Players *player = (Players *)ThisPlayer;
	BOOL god = FALSE;
	bool boBroadcast = boBroadcastMove;
	
	if( player != NULL ) {
		if( player->GetGodFlags() & GOD_NO_CLIP ){
			god = TRUE;
		}
        // If god has true invisibility
        /*if( player->GetGodFlags() & GOD_TRUE_INVISIBILITY || 
            player->self->ViewFlag( __FLAG_INVISIBILITY ) != 0 ){
            boBroadcast = false;
        }*/
	}

	// If move is absolute, then godly move!
	if( boAbsolute )
		god = TRUE;

	WorldPos WL;
	WorldPos CurrentWL = GetWL();
 
	int west = where == 1 ? 8 : where - 1;
	int east = where == 8 ? 1 : where + 1;
	int nMovedPos = where;

	WL = Unit::MoveUnit(where, god, boCompressMove, boBroadcast );

	if( SAME_POS( WL, CurrentWL ) ){
		WL = Unit::MoveUnit( (DIR::MOVE)west, god, boCompressMove, boBroadcast );
		nMovedPos = west;

		if( SAME_POS( WL, CurrentWL ) ){
			WL = Unit::MoveUnit( (DIR::MOVE)east, god, boCompressMove, boBroadcast );
			nMovedPos = east;
		}
	}

	// If unit actually moved
	if( !( SAME_POS( WL, CurrentWL ) ) && !( player->GetGodFlags() & GOD_NO_MONSTERS ) ){
		if( nMovedPos != 0 ){
			if( nMovedPos > 8 ){ nMovedPos = 8; };
			if( nMovedPos < 1 ){ nMovedPos = 1; };
			
			WorldMap *wlWorld = TFCMAIN::GetWorld( CurrentWL.world );
			if( wlWorld != NULL ){
				// Check for any popuped up hives
				wlWorld->VerifyPeripheralHives( CurrentWL, (DIR::MOVE)nMovedPos );
			}
		}
	}

    // If the player is hidden and doesn't have the sneak skill.
    LPUSER_SKILL uskill = GetSkill( __SKILL_SNEAK );
    if( ViewFlag( __FLAG_HIDDEN ) != 0 ){
        if( uskill == NULL || uskill->GetSkillPnts( this ) == 0 ){            
			Unhide();
        }
    }


	// Then process all move-intrinsic skills
	tlusSkills[Hook_OnMove].ToHead();	
	while(tlusSkills[Hook_OnMove].QueryNext())
	{
		LPUSER_SKILL lpusUserSkill = tlusSkills[Hook_OnMove].Object();
		
		Skills::ExecuteSkill(lpusUserSkill->GetSkillID(), HOOK_MOVE,
			this, NULL, NULL, &WL, NULL, lpusUserSkill);
	}

	// Check the weather unit personnal state
	// Only check if there's at least 1 effect ON
	/*if( WeatherEffect::GetInstance()->AreEffectsOff() == false )
	{
		WeatherEffect::GetInstance()->CheckWeatherState( this, WL );
	}*/		

	return WL;
}
/////////////////////////////////////////////////////////////////////////////////////////
WORD Character::GetClan(){
	return clan;
}
/////////////////////////////////////////////////////////////////////////////////////////
void Character::SetClan(WORD newClan){
	clan = newClan;
}
/////////////////////////////////////////////////////////////////////////////////////////
// This functions returns the max HP of a player
DWORD Character::GetTrueMaxHP(){
	return MaxHP ? MaxHP : 1;
}
/////////////////////////////////////////////////////////////////////////////////////////
// This functions returns the max HP of a player
void Character::SetMaxHP(DWORD newHP){
	MaxHP = newHP;

    TFCPacket sending;
    sending << (RQ_SIZE)RQ_HPchanged;
    sending << (long)GetHP();
    sending << (long)GetMaxHP();
    SendPlayerMessage( sending );
}
/////////////////////////////////////////////////////////////////////////////////////////
// This functions returns the max HP of a player
DWORD Character::GetHP(){
	return HP;
}
/////////////////////////////////////////////////////////////////////////////////////////
// This functions returns the max HP of a player
void Character::SetHP(DWORD newHP, bool boUpdate ){
    // If HP actually changed.
    if( HP != newHP )
	{
        HP = newHP;

        if( boUpdate )
		{
		      TFCPacket sending;
		      sending << (RQ_SIZE)RQ_HPchanged;
		      sending << (long)GetHP();
		      sending << (long)GetMaxHP();
		      SendPlayerMessage( sending );

            // If player is in a group.
            if( GetGroup() != NULL ){
                // Tell the group of the update.
                GetGroup()->SendHpUpdate( this );
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
// This functions returns the max HP of a player
WORD Character::GetTrueMaxMana(){
	return MaxMana;
}
/////////////////////////////////////////////////////////////////////////////////////////
// This functions returns the max HP of a player
void Character::SetMaxMana(WORD newMaxMana){
	MaxMana = newMaxMana;
}
/////////////////////////////////////////////////////////////////////////////////////////
// This functions returns the max HP of a player
WORD Character::GetMana(){
	return Mana;
}
/////////////////////////////////////////////////////////////////////////////////////////
// This functions returns the max HP of a player
void Character::SetMana(WORD newMana, BOOL boEcho ){	    
    
	if (Mana != newMana) { //BLBLBL on ne modifie que si ça a changé !
	
	Mana = newMana;

    if( boEcho ){
        TFCPacket sending;
        sending << (RQ_SIZE)RQ_ManaChanged;
        sending << (short)newMana;

        SendPlayerMessage( sending );
    }

	}
}


/////////////////////////////////////////////////////////////////////////////////////////
// Returns the gold on the player
int Character::GetGold(){
    CAutoLock autoStatsLock( &statsLock );
	return gold;
}
/////////////////////////////////////////////////////////////////////////////////////////
// Sets the gold on a player
void Character::SetGold(int newGold, BOOL boEcho ){
    CAutoLock autoStatsLock( &statsLock );
    // Can't hold any debts :) rofl
	DWORD dwOldGold = gold;
    
    newGold = newGold < 0 ? 0 : newGold;
	gold = newGold;
        
    SynchronizeGold();

	if( boEcho && newGold > dwOldGold )
	{
        char buf[ 1024 ];
        sprintf( buf, _STR( 7508, GetLang() ), gold - dwOldGold );
        //SendSystemMessage( buf ); // steph désactivation
    }
	TFCPacket sending;
	sending << (RQ_SIZE)RQ_GoldChange;

    if( gameopContext != NULL )
	{
        sending << (long)gameopContext->GetGold();   
    }
	else
	{
		sending << (long)newGold;
    }
	SendPlayerMessage( sending );
}

// asteryth guilds
////////////////////////////////////////////////////////////////////////////////////////
// sets the guildname of the character
void Character::SetGuildName(CString newGuildName){
	csGuildName = newGuildName;
	csGuildName.Remove('\'');
}
////////////////////////////////////////////////////////////////////////////////////////
// returns the guildname of the character
CString Character::GetGuildName(){
    return csGuildName;
}

////////////////////////////////////////////////////////////////////////////////////////
// sets the guildname of the character
// no access = -1
void Character::SetGuildChestAccess(int newGuildChestAccess){
	GuildChestAccess = newGuildChestAccess;
}
////////////////////////////////////////////////////////////////////////////////////////
// returns the guildname of the character
int Character::GetGuildChestAccess(){
    return GuildChestAccess;
}


////////////////////////////////////////////////////////////////////////////////////////
// sets the name of the character
void Character::SetName(CString newName){
	PlayerName = newName;
}
////////////////////////////////////////////////////////////////////////////////////////
// returns the name of the character
CString Character::GetName(){
    // If the pseudoname doesn't exist.
    if( csPseudoName.IsEmpty() ){
        // Return the true player name.
        return PlayerName;
    }
    // Otherwise return the pseudo name.
    return csPseudoName;
}
// Wrapper for the GetName() function
CString Character::GetName(WORD wLang)
{
	return GetName();
}

//////////////////////////////////////////////////////////////////////////////////////////
CString Character::GetTrueName( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the only true name of a character. If you know you're getting the name of
// a character in a non-game related purpose, use this function.
// 
// Return: CString, The true name.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return PlayerName;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::SetPseudoName
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets a character's pseudo name. The character's name will be displayed this way,
//  but it won't affect other functions.
// 
(
 CString csName // The new pseudo-name
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    csPseudoName = csName;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// returns the exhaust of a PC
EXHAUST Character::GetExhaust(){		
	return exhaust;
}
/////////////////////////////////////////////////////////////////////////////////////////////
// Sets the exhaust of a PC
void Character::SetExhaust(EXHAUST dfd){	

	long lTime;
	lTime = time(NULL);
	this->lLastEventTime=lTime;
	
	//sur havoc on desactive ça
	 	
	if (dfd.move > exhaust.move) {
		if (this->boClientExitCountDown) {//BLBLBL : si on sait que le client est justement en train de décompter à ce moment
			TFCPacket sending; //on lui envoie un paquet lui demandant d'arrêter de compte, puisque le perso a été disturbed/exhaust (ie : entangle)
			sending << (RQ_SIZE)(RQ_SafePlug); //BLBLBL Antiplug : on informe le client qu'on a du annuler la déco
			sending << (char)0;	// 0 = Il faut annuler le compteur
			SendPlayerMessage( sending );
			this->boClientExitCountDown=false;//on met à false, pour éviter de flooder le client de paquets indiquant qu'il doit stopper le compteur
		}
	}
	exhaust = dfd;

}
//////////////////////////////////////////////////////////////////////////////////////////////
// Uses bQuantity skill pnts, returns TRUE if the decrementation was posible
BOOL Character::UseSkillPnts(WORD bQuantity){
	if(wNbSkillPnts < bQuantity)
		return FALSE;

	wNbSkillPnts = (WORD)( wNbSkillPnts - bQuantity );

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Uses bQuantity stat pnts, returns TRUE if the decrementation was posible
BOOL Character::UseStatPnts(BYTE bQuantity){
	if(wNbStatPnts < bQuantity)
		return FALSE;

	wNbStatPnts -= (WORD)bQuantity;

	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////
// Adds skill points to a skill
BOOL Character::TrainSkillPnt(int nID, int nQuantity, WORD wMax ){
	
	LPUSER_SKILL lpusUserSkill = GetSkill( nID );
	
	if(lpusUserSkill){
        // If NPC can't teach more
        if( lpusUserSkill->GetTrueSkillPnts() + nQuantity > wMax ){            
            nQuantity = wMax - lpusUserSkill->GetTrueSkillPnts();
        }

        if( nQuantity > 0 )
		{
    		// Uses skill points
	    	if( UseSkillPnts( (WORD)nQuantity ) )
			{
		    	// If ID is a skill
			    if( nID < SPELL_ID_OFFSET )
				{
    				Skills::TrainSkill(this, lpusUserSkill, nQuantity);
	    		}
				else
				{
		    		// Otherwise, if its a spell.
			    	lpusUserSkill->SetSkillPnts( lpusUserSkill->GetTrueSkillPnts() + nQuantity );
			    }
		    }
			else
			{
			    return FALSE;
		    }
        }
		else
		{
            return FALSE;
        }
	}

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Called when character succefully hits
int Character::attack_hit(LPATTACK_STRUCTURE s_asBlow, Unit *lpuTarget){
	Disturbed(DISTURB_CLOSECHEST|DISTURB_CLOSETRADE);

    // Query attack hit effects
    QueryEffects( MSG_OnAttackHit, s_asBlow, NULL, lpuTarget );

    int attackID;
    // Query objects for attackhit

	if(equipped[body])		equipped[body]		->SendUnitMessage(MSG_OnAttackHit, equipped[body], this, lpuTarget, s_asBlow, &attackID);
    if(equipped[belt])		equipped[belt]		->SendUnitMessage(MSG_OnAttackHit, equipped[belt], this, lpuTarget, s_asBlow, &attackID);
	if(equipped[feet])		equipped[feet]		->SendUnitMessage(MSG_OnAttackHit, equipped[feet], this, lpuTarget, s_asBlow, &attackID);
	if(equipped[gloves])	equipped[gloves]	->SendUnitMessage(MSG_OnAttackHit, equipped[gloves], this, lpuTarget, s_asBlow, &attackID);
	if(equipped[helm])		equipped[helm]		->SendUnitMessage(MSG_OnAttackHit, equipped[helm], this, lpuTarget, s_asBlow, &attackID);
	if(equipped[legs])		equipped[legs]		->SendUnitMessage(MSG_OnAttackHit, equipped[legs], this, lpuTarget, s_asBlow, &attackID);
    if(equipped[ring1])        equipped[ring1]       ->SendUnitMessage(MSG_OnAttackHit, equipped[ring1], this, lpuTarget, s_asBlow, &attackID);
	if(equipped[ring2])        equipped[ring2]       ->SendUnitMessage(MSG_OnAttackHit, equipped[ring2], this, lpuTarget, s_asBlow, &attackID);
	if(equipped[bracelets])    equipped[bracelets]   ->SendUnitMessage(MSG_OnAttackHit, equipped[bracelets], this, lpuTarget, s_asBlow, &attackID);
	if(equipped[necklace])     equipped[necklace]    ->SendUnitMessage(MSG_OnAttackHit, equipped[necklace], this, lpuTarget, s_asBlow, &attackID);
	if(equipped[weapon_right]) equipped[weapon_right]->SendUnitMessage(MSG_OnAttackHit, equipped[weapon_right], this, lpuTarget, s_asBlow, &attackID);		
	if(equipped[weapon_right] != equipped[weapon_left])// if it's not a two handed weapon	
   {
      if(equipped[weapon_left])
      {
         _item *obj = NULL;
		   equipped[weapon_left ]->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &obj);
		 // NIGHTMARE:: Fix problem on left hand with arrow hook
         if(obj && obj->item_type == 1 && obj->weapon.ranged == 0)
         {
            // on compte pas le strike ici des dual weapon, le skill comptera le degat...
         }
         else
            equipped[weapon_left] ->SendUnitMessage(MSG_OnAttackHit, equipped[weapon_left], this, lpuTarget, s_asBlow, &attackID);
      }
   }


    // Process all attack-intrinsic skills
	tlusSkills[Hook_OnAttack].ToHead();
	
	while(tlusSkills[Hook_OnAttack].QueryNext()){
		LPUSER_SKILL lpusUserSkill = tlusSkills[Hook_OnAttack].Object();
	
		Skills::ExecuteSkill(lpusUserSkill->GetSkillID(), HOOK_ATTACK,
			this, NULL, lpuTarget, s_asBlow, NULL, lpusUserSkill);
	}

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// Hooks the unit SendUnitMessage function to capture special messages
BOOL Character::SendUnitMessage(UINT MessageID, Unit *self, Unit *medium, Unit *target, 
							void *valueIN, void *valueOUT){
	
	BOOL boReturnValue = FALSE;

	switch(MessageID){
	case MSG_OnGetUnitStructure:
		*(Character **)(valueOUT) = this;
		boReturnValue = TRUE;
	break;
	}


	return boReturnValue;
}
/////////////////////////////////////////////////////////////////////////////////////////////
// Returns the class points of a unit, for U_PC only
//LPWORD Character::GetClassPoints(){
//	return ClassPoints;
//}
////////////////////////////////////////////////////////////////////////////////////////////////
// This function sends a packet message to a player through the unit interface which is 
// the only handled structure of DLLs.
void Character::SendPlayerMessage(TFCPacket &sending){

    Players *lpPlayer = (Players *)ThisPlayer;
    
    // If player hasn't been deleted.
    if( lpPlayer != NULL )
	{
        WorldPos wlPos = { -1, -1, -1 };

		// Send message.
        CPacketManager::SendPacket(
            sending,
            lpPlayer->IPaddr,
            -1,
            wlPos,
            FALSE 
        );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
// This function uses a normal use skill
BOOL Character::UseSkill(int nID, Unit *uTarget, LPVOID lpValueOUT ){
	BOOL boFound = FALSE;
	BOOL boSuccess = FALSE;

    Disturbed(DISTURB_UNHIDE);

    DispellInvisibility();

	TRACE(" Using skill ID %u on target ID %u", nID, uTarget->GetID() );

	tlusSkills[ Hook_None ].ToHead();	
	while( tlusSkills[ Hook_None ].QueryNext() && !boFound )
	{
		LPUSER_SKILL lpusUserSkill = tlusSkills[ Hook_None ].Object();
		
		if( lpusUserSkill->GetSkillID() == nID )
		{
			// Retreive the target's pos to ensure skills receives its worldpos member
			WorldPos wlUnitPos = uTarget->GetWL();
			// Send use if used target
			int nReturn = Skills::ExecuteSkill( lpusUserSkill->GetSkillID(), HOOK_USE | HOOK_USE_TARGET_UNIT,
				this, NULL, uTarget, &wlUnitPos, lpValueOUT, lpusUserSkill );

			boFound = TRUE;
			
			if( nReturn == SKILL_SUCCESSFULL || nReturn == SKILL_PERSONNAL_FEEDBACK_SUCCESSFULL )
			{
				boSuccess = TRUE;
			}
		}
	}

	return boSuccess;
}
/////////////////////////////////////////////////////////////////////////////////////////////
// This function uses a normal skill
BOOL Character::UseSkill(int nID, WorldPos wlPos){
	BOOL boFound = FALSE;

    Disturbed(DISTURB_UNHIDE);

    DispellInvisibility();

	int nHook = 0;
	if( wlPos.X == 0 && wlPos.Y == 0 && wlPos.world == 0 )
	{			
		nHook = HOOK_USE_TARGET_POS;	// If a target pos was set, skill is used with target pos.
	}
	
	nHook |= HOOK_USE;	// Skill used.

	// Then process all move-intrinsic skills
	tlusSkills[Hook_None].ToHead();	
	while(tlusSkills[Hook_None].QueryNext() && !boFound)
	{
		LPUSER_SKILL lpusUserSkill = tlusSkills[Hook_None].Object();
		
		if(lpusUserSkill->GetSkillID() == nID )
		{
			// Send use without target
			Skills::ExecuteSkill(lpusUserSkill->GetSkillID(), nHook,
				this, NULL, NULL, &wlPos, NULL, lpusUserSkill);
			boFound = TRUE;
		}
	}
	
	return boFound;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// These functions update faith

/* BEGIN : Mestoph -> Removed skill pray for not used in the server
WORD Character::GetFaith(){
	return Faith;
}
WORD Character::GetMaxFaith(){
	return (WORD)(MaxFaith ? MaxFaith : 1);
}
void Character::SetFaith(WORD newFaith){
	Faith = newFaith;
};
void Character::SetMaxFaith(WORD newMaxFaith){
	MaxFaith = newMaxFaith;
};
END : Mestoph -> Removed skill pray for not used in the server */

//////////////////////////////////////////////////////////////////////////////////////////
void Character::Regenerate( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Regenerates mana and HP. Called at a regular (2 minutes) time.
// Will also call regeneration-specific skills
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	BOOL boFound = FALSE;
	
	GAME_RULES::HPregen( this );
	GAME_RULES::ManaRegen( this );
	//GAME_RULES::FaithRegen( this );
	
	// Then process all regen-intrinsic
	tlusSkills[Hook_OnRegen].ToHead();	
	while(tlusSkills[Hook_OnRegen].QueryNext() && !boFound)
	{
		LPUSER_SKILL lpusUserSkill = tlusSkills[Hook_OnRegen].Object();
		
		Skills::ExecuteSkill(lpusUserSkill->GetSkillID(), HOOK_REGEN,
				this, NULL, NULL, NULL, NULL, lpusUserSkill);		
	}
}


#define ADD_TO_TRAINING_LIST( WhichList )	/*if(Skills::IsSkillLearnable(dwSkill, this))*/{\
                                                tlusSkills[ WhichList ].Lock();\
												tlusSkills[ WhichList ].AddToTail(lpusNewSkill);\
                                                tlusSkills[ WhichList ].Unlock();\
												boFoundOwner = TRUE;\
											}




//////////////////////////////////////////////////////////////////////////////////////////
LPUSER_SKILL Character::LearnSkill
//////////////////////////////////////////////////////////////////////////////////////////
// Appends a skill to the list of learned skills.
// 
(
 DWORD dwSkill, // Skill ID of the skill to learn
 WORD wCost,		// Cost of skill, and initial strength
 bool boEcho,       // true if we should echo messages.
 CString &errMsg
)
// Return: LPUSER_SKILL, user skill or NULL if train failed.
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPUSER_SKILL lpusNewSkill = NULL;

	// If we DON'T have enough skill points to learn this skill
	if( wCost > wNbSkillPnts ){
        if( boEcho ){
            SendSystemMessage( _STR( 40, GetLang() ) );
        }
        errMsg.Format( 
            "Not enough skill points for skill %u! Cost %u, skill pnts=%u.",
            dwSkill,
            wCost, 
            wNbSkillPnts 
        );
        return NULL;
    }

	TRACE( "\r\nSkillID %u cost %u.", dwSkill, wCost );


	// If dwSkill is a skill
	if( dwSkill < SPELL_ID_OFFSET )
	{
		// Gets the skill pointer of the skill ID
		LPSKILL lpSkill = Skills::GetSkill(dwSkill);

		if(lpSkill){
			// If player doesn't already have the skill
			if(!GetSkill(dwSkill))
			{
				BOOL boFoundOwner = FALSE;
				
				// If a skill has multiple hook, they should all share the same object
				lpusNewSkill = new USER_SKILL;
				lpusNewSkill->SetSkillID( dwSkill );
				lpusNewSkill->SetSkillPnts( 1 );	// Gets the cost in skill points.
				
				// If skill is useable, append it to the useable skills.
				if(lpSkill->nHook & HOOK_USE || lpSkill->nHook & HOOK_USE_TARGET_UNIT || lpSkill->nHook & HOOK_USE_TARGET_POS || lpSkill->nHook & HOOK_NOTHING )
				{
					// if player can actually train this skill
					ADD_TO_TRAINING_LIST( Hook_None )			
				}
				// If skill is cast on attacks.
				if(lpSkill->nHook & HOOK_ATTACK)
				{
					// if player can actually train this skill
					ADD_TO_TRAINING_LIST( Hook_OnAttack )
				}
				// If skill is cast when being attacked.
				if(lpSkill->nHook & HOOK_ATTACKED)
				{
					// if player can actually train this skill
					ADD_TO_TRAINING_LIST( Hook_OnAttacked)
				}
				// If skill is cast when being hit.
				if(lpSkill->nHook & HOOK_HIT)
				{
					// if player can actually train this skill
					ADD_TO_TRAINING_LIST( Hook_OnHit )
				}
				// If skill is used when moving.
				if(lpSkill->nHook & HOOK_MOVE)
				{
					// if player can actually train this skill
					ADD_TO_TRAINING_LIST( Hook_OnMove )
				}
				// If skill is used when training.
				if(lpSkill->nHook & HOOK_TRAINING)
				{
					// if player can actually train this skill
					ADD_TO_TRAINING_LIST( Hook_OnTraining )
				}
				// If skill is used when regenerating.
				if(lpSkill->nHook & HOOK_REGEN)
				{
					ADD_TO_TRAINING_LIST( Hook_OnRegen )
				}
			
				// If no function used this object, then delete it.
				if(!boFoundOwner){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL1,
                        "Could not find correct training hook for spell id %u.",
                        dwSkill
                    LOG_

					delete lpusNewSkill;
					lpusNewSkill = NULL;

                    errMsg.Format( "Could not find any training hook for skill %u.", dwSkill );
				}else{
                    _LOG_DEBUG
                        LOG_DEBUG_LVL4,
                        "Successfully taught skill %u.",
                        dwSkill
                    LOG_

					// Deduct the skill points
					wNbSkillPnts -= wCost;

                    if( boEcho )
					{
                        char buf[ 1024 ];
                        sprintf( buf, _STR( 7845, GetLang() ), lpSkill->GetName( GetLang() ) );
                        SendSystemMessage( buf );
                    }

					// Add the class points relative to this skill to the player
//					ClassPoints[ THIEF ] += lpSkill->lpsaAttrib->ClassPnts[ THIEF ];
//					ClassPoints[ WARRIOR ] += lpSkill->lpsaAttrib->ClassPnts[ WARRIOR ];
//					ClassPoints[ MAGE ] += lpSkill->lpsaAttrib->ClassPnts[ MAGE ];
//					ClassPoints[ PRIEST ] += lpSkill->lpsaAttrib->ClassPnts[ PRIEST ];
				}
            }
			else
			{
                errMsg.Format( "Player already has the skill %u.", dwSkill );
            }
        }else{
            _LOG_DEBUG
                LOG_DEBUG_LVL1,
                "User tried to learn an unexisting skill ( ID %u ).",
                dwSkill
            LOG_
            errMsg.Format( "Skill %u does not exist.", dwSkill );
        }
	}
	else
	{
		LPSPELL_STRUCT lpSpell = SpellMessageHandler::GetSpell( (WORD)dwSkill );
		// If spell exists
		if( lpSpell != NULL ){
			// Check if player already has this spell
			tlusSpells.Lock();

			BOOL boFound = FALSE;
			tlusSpells.ToHead();
			while( tlusSpells.QueryNext() && !boFound )
			{
				if( tlusSpells.Object()->GetSkillID() == (int)dwSkill )
				{
					boFound = TRUE;
				}
			}
			// If player doesn't already have this spell.
			if( !boFound )
			{			
				lpusNewSkill = new USER_SKILL;
				// If a skill has multiple hook, they should all share the same object			
				lpusNewSkill->SetSkillID( dwSkill );
				lpusNewSkill->SetSkillPnts( 1 );	// Gets the cost in skill points.

                // Deduct the skill points
                wNbSkillPnts -= wCost;

                if( boEcho )
				{
                    char buf[ 1024 ];
                    sprintf( buf, _STR( 7844, GetLang() ), lpSpell->GetName( GetLang() ) );
                    SendSystemMessage( buf );
                }

				// Add the class points relative to this skill to the player
//				ClassPoints[ THIEF ] += lpSpell->saAttrib.ClassPnts[ THIEF ];
//				ClassPoints[ WARRIOR ] += lpSpell->saAttrib.ClassPnts[ WARRIOR ];
//				ClassPoints[ MAGE ] += lpSpell->saAttrib.ClassPnts[ MAGE ];
//				ClassPoints[ PRIEST ] += lpSpell->saAttrib.ClassPnts[ PRIEST ];

				tlusSpells.AddToTail( lpusNewSkill );
            }
			else
			{
                errMsg.Format( "Player already has the spell %u.", dwSkill );
            }
			tlusSpells.Unlock();
        }
		else
		{
            errMsg.Format( "Spell %u does not exist.", dwSkill );
        }

	}
		return lpusNewSkill;
}

//////////////////////////////////////////////////////////////////////////////////////////
LPUSER_SKILL Character::GetSkill
//////////////////////////////////////////////////////////////////////////////////////////
// This function returns the user-skill associated to the player.
// 
(
 DWORD dwSkill // The skill to query.
)
// Return: LPUSER_SKILL, A pointer to the user-skill, or NULL
//////////////////////////////////////////////////////////////////////////////////////////
{
	// Search through all the hooks for the first occurence of Skill. If a skill
	// is in multiple hooks, its object is shared by the lists so this will always return
	// the correct object.
	
	LPUSER_SKILL lpUserSkill = NULL;

	// If the ID is a spell
	if( dwSkill >= SPELL_ID_OFFSET ){
		tlusSpells.ToHead();
		while( tlusSpells.QueryNext() && lpUserSkill == NULL )
		{
			if( tlusSpells.Object()->GetSkillID() == (int)dwSkill )
			{
				lpUserSkill = tlusSpells.Object();
                lpUserSkill->SetSkillPnts( 1 );
			}
		}
	}
	else
	{
		int i;		
		for(i = 0; i < NB_SKILL_HOOKS; i++)
		{
			tlusSkills[i].Lock();
			tlusSkills[i].ToHead();
			while(tlusSkills[i].QueryNext() && lpUserSkill == NULL )
			{
				// If it found the skill, it returns it.
				if(tlusSkills[i].Object()->GetSkillID() == (int)dwSkill)
				{
					lpUserSkill = tlusSkills[i].Object();
				}
			}
			tlusSkills[i].Unlock();
		}
	}
	// nothing found.
	return lpUserSkill;
}

//////////////////////////////////////////////////////////////////////////////////////////
TemplateList <USER_SKILL> *Character::GetSkillLists( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the skills inside a template list. 
// 
// Return: TemplateList <USER_SKILL>, 
//////////////////////////////////////////////////////////////////////////////////////////
{
	return tlusSkills;
}


//////////////////////////////////////////////////////////////////////////////////////////
char Character::PutPlayerInGame( void )
//////////////////////////////////////////////////////////////////////////////////////////
// This functions puts the loaded player in game.
// 
// Return: char, 0 if the player was put in game, 1 otherwise
//////////////////////////////////////////////////////////////////////////////////////////
{
	if( boLoaded )
	{		
		TRACE("\r\nHerE1");
		
		WorldMap *wl;
			BOOL IsGod = FALSE;

		Unit *binded_unit;
		wl = TFCMAIN::GetWorld((WORD)GetWL().world);
        if( wl != NULL )
		{
		    binded_unit = wl->create_world_unit(U_PC, GetAppearance(), GetWL(), this);
			    
		    // if unit wasn't create well euh..
		    int i;
		    WorldPos OldPos = GetWL();				
		    WorldPos CurPos;
		    if(!binded_unit){
			    TRACE("\r\nHerE2");

                i = 1;
                while( i < 9 && binded_unit != NULL )
				{
				    CurPos = OldPos;
				    switch(i){
				    case 1: CurPos.Y--;
						    SetWL(CurPos);
					    break;
				    case 2: CurPos.Y++;
						    SetWL(CurPos);
					    break;
				    case 3: CurPos.X--;
						    SetWL(CurPos);
					    break;
				    case 4: CurPos.X--;
						    SetWL(CurPos);
					    break;
				    case 5: CurPos.X--;
						    CurPos.Y--;
						    SetWL(CurPos);
					    break;
				    case 6: CurPos.X++;
						    CurPos.Y--;
						    SetWL(CurPos);
					    break;
				    case 7: CurPos.X--;	
						    CurPos.Y++;
						    SetWL(CurPos);
					    break;
				    case 8: CurPos.X++;	
						    CurPos.Y++;
						    SetWL(CurPos);
					    break;
				    }						
				    binded_unit = wl->create_world_unit(U_PC, GetAppearance(), GetWL(), this, IsGod);

                    i++;
			    }
            }		
		}
	
		if( binded_unit )
		{
			return 0;		
		}
	
	}
	
	return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////
WORD Character::GetSkillPoints( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the quantity of skill points available for wasting in skills.
// 
// Return: WORD, the skill points
//////////////////////////////////////////////////////////////////////////////////////////
{
	return wNbSkillPnts;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::GiveSkillPoints
//////////////////////////////////////////////////////////////////////////////////////////
// Gives skill points to a user.
// 
(
 WORD wQuantity // The quantity of skill points to add.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	wNbSkillPnts += wQuantity;
}

//////////////////////////////////////////////////////////////////////////////////////////
WORD Character::GetStatPoints( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the quantity of stat points available for wasting in stats.
// 
// Return: WORD, the quantity of stat points
//////////////////////////////////////////////////////////////////////////////////////////
{
	return wNbStatPnts;
}

//////////////////////////////////////////////////////////////////////////////////////////
double Character::GetAC( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the player's AC
// 
// Return: WORD, the AC
//////////////////////////////////////////////////////////////////////////////////////////
{
	// Get the boosted AC.
    double dblAC = QueryBoost( STAT_AC );
		
    // Get the true AC
    dblAC += GetTrueAC();

    TRACE( "\r\n--Total AC %f.", dblAC );

    if( dblAC <= 0 )
	{
        return 0;
    }
	else
	{
        return dblAC;
    }
}       

//////////////////////////////////////////////////////////////////////////////////////////
double Character::GetTrueAC( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the unboosted AC of a character.
// 
// Return: double, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    double dblAC = 0;
    
    if( equipped[ body ] )			dblAC += equipped[ body ]->GetAC();
	if( equipped[ feet ] )			dblAC += equipped[ feet ]->GetAC();
	if( equipped[ gloves ] )		dblAC += equipped[ gloves ]->GetAC();
	if( equipped[ helm ] )			dblAC += equipped[ helm ]->GetAC();
    if( equipped[ legs ] )			dblAC += equipped[ legs ]->GetAC();
    if( equipped[ cape ] )		    dblAC += equipped[ cape ]->GetAC();
    if( equipped[ belt ] )			dblAC += equipped[ belt ]->GetAC();
	if( equipped[ ring1 ] )			dblAC += equipped[ ring1 ]->GetAC();
	if( equipped[ ring2 ] )			dblAC += equipped[ ring2 ]->GetAC();
	if( equipped[ bracelets ] )		dblAC += equipped[ bracelets ]->GetAC();
	if( equipped[ necklace ] )		dblAC += equipped[ necklace ]->GetAC();
    if( equipped[ weapon_right ] )	dblAC += equipped[ weapon_right ]->GetAC();
    if( equipped[ weapon_right ] != equipped[ weapon_left ] && equipped[ weapon_left ] != NULL ) 
	{
		dblAC += equipped[ weapon_left ]->GetAC();
	}

    TRACE( "\r\n--Total AC %f.", dblAC );

    if( dblAC <= 0 )
	{
        return 0;
    }
	else
	{
        return dblAC;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
char Character::GetAgressivness( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the current agressivness of the player.
// 
// Return: signed char, the agressivness
//////////////////////////////////////////////////////////////////////////////////////////
{
	return cAgressive;
}


//////////////////////////////////////////////////////////////////////////////////////////
void Character::SetAgressivness
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the agressivness of the unit
// 
(
 char cAgr // the new agressivness
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	cAgressive = cAgr;
}

//////////////////////////////////////////////////////////////////////////////////////////
Unit **Character::GetEquipment( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the equipment array of the player.
// 
// Return: Unit *, the equipment array
//////////////////////////////////////////////////////////////////////////////////////////
{
	return equipped;
}

//////////////////////////////////////////////////////////////////////////////////////////
TemplateList<USER_SKILL> *Character::GetSpells( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the list of user spells.
// 
// Return: TemplateList<USER_SKILL>, The list of user spells
//////////////////////////////////////////////////////////////////////////////////////////
{
	return &tlusSpells;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Character::CanAttack( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Determines if the character can attack.
// 
// Return: BOOL, always TRUE for characters.
//////////////////////////////////////////////////////////////////////////////////////////
{
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::WaitForSaving( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Locked when player has been created but not yet saved.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	WaitForSingleObject( hCreationEvent, INFINITE );	
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::SavingStart( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Called when starting to commit data.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	_LOG_DEBUG
        LOG_DEBUG_HIGH,
        "SavingStart %s.",
        (LPCTSTR)GetTrueName()
    LOG_

    pthread_cond_t m_condition;
	pthread_cond_broadcast(&m_condition);
    //ResetEvent( hCreationEvent );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::SavingStop( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Called to signal end of creation.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	_LOG_DEBUG
        LOG_DEBUG_LVL1,
        "Finished async saving character %s.",
        (LPCTSTR)GetTrueName()
    LOG_

    pthread_cond_t m_condition;
	pthread_cond_broadcast(&m_condition);
    //SetEvent( hCreationEvent );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::PacketSkills
//////////////////////////////////////////////////////////////////////////////////////////
// PAckets the skills
//
(
 TFCPacket &sending,
 bool gameop
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( gameopContext != NULL && !gameop ){
        gameopContext->PacketSkills( sending, true );
        return;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////
	// This request should return all the player's skills
	TemplateList <USER_SKILL> *tlusSkills = GetSkillLists( );
	
	int i;
	BOOL boSent;
	LPUSER_SKILL lpUserSkill;
	LPSKILL lpSkill;

	TemplateList <USER_SKILL> tlSentSkills;
			
	for( i = 0; i < NB_SKILL_HOOKS; i++ )
	{
		
		tlusSkills[i].ToHead();
		while(tlusSkills[i].QueryNext() )
		{
			lpUserSkill = tlusSkills[i].Object();
		
			// Only send existing skills
			TRACE( "--%u--", lpUserSkill->GetSkillID() );
			
			if( Skills::GetSkill( lpUserSkill->GetSkillID() ) != NULL )
			{

				// first verify that this skills hasn't been already sent in an earlier hook
				boSent = FALSE;
				tlSentSkills.ToHead();
				while( tlSentSkills.QueryNext() )
				{
					if( tlSentSkills.Object() == lpUserSkill )
					{
						boSent = TRUE;
					}
				}

				// If skill wasn't found, add it to the list to send.
				if( !boSent ){
					tlSentSkills.AddToTail( lpUserSkill );
				}
			}
		}
	}
	
	sending << (RQ_SIZE)RQ_GetSkillList;
	sending << (short)( tlSentSkills.NbObjects() + 2 );
	
	CString csText;

	// First send the attack and dodge skills
	sending << (short)__SKILL_ATTACK;
	sending << (char)0;
	sending << (short)GetATTACK();
    sending << (short)GetTrueATTACK();
	//csText = "Attack";
	sending << (CString )CString( _STR( 449, GetLang() ) ) ;
    sending << (CString )CString( _STR( 7889, GetLang() ) ) ;
	
	sending << (short)__SKILL_DODGE;
	sending << (char)0;
	sending << (short)GetDODGE();
    sending << (short)GetTrueDODGE();
	//csText = "Dodge";
	sending << (CString )CString( _STR( 450, GetLang() ) );
    sending << (CString )CString( _STR( 7890, GetLang() ) );

	tlSentSkills.ToHead();
	while( tlSentSkills.QueryNext() )
	{
		lpUserSkill = tlSentSkills.Object();

		lpSkill = Skills::GetSkill( lpUserSkill->GetSkillID() );		

		sending << (short)lpUserSkill->GetSkillID();
		// Skill usable on a unit.
		if( lpSkill->nHook & HOOK_USE_TARGET_UNIT )
		{
			sending << (char)3;
		}
		else
		// Skill usable on a target position.	
		if( lpSkill->nHook & HOOK_USE_TARGET_POS )
		{
			sending << (char)2;
		}
		else
		// skill usable without further information.
		if( lpSkill->nHook & HOOK_USE )
		{
			sending << (char)1;
		}
		else
		{
		// Skill not usable.		
			sending << (char)0;
		}

		sending << (short)lpUserSkill->GetSkillPnts( this );
        sending << (short)lpUserSkill->GetTrueSkillPnts();
		sending << (CString )(CString)lpSkill->GetName( GetLang() );
        sending << (CString )(CString)lpSkill->GetDesc( GetLang() );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::PacketSpells
//////////////////////////////////////////////////////////////////////////////////////////
// Packets the spells
// 
(
 TFCPacket &sending,	// The packet
 BYTE bUpdate,			// Non-zero if this packet only updates without displaying the spelllist.
 bool gameop
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( gameopContext != NULL && !gameop )
	{
        gameopContext->PacketSpells( sending, bUpdate, true );
        return;
    }
	
    TemplateList <USER_SKILL> *lptlusSpells;
	LPUSER_SKILL lpUserSkill;
	LPSPELL_STRUCT lpSpell;
		
	lptlusSpells = GetSpells();	

	sending << (RQ_SIZE)RQ_SendSpellList;
	sending << (char)bUpdate;		
	sending << (short)GetMana();
	sending << (short)GetMaxMana();
//	sending << (short)GetFaith();
//	sending << (short)GetMaxFaith();
	sending << (short)lptlusSpells->NbObjects();

	lptlusSpells->Lock();
	lptlusSpells->ToHead();		
	while( lptlusSpells->QueryNext() )
	{
		lpUserSkill = lptlusSpells->Object();

		lpSpell = SpellMessageHandler::GetSpell( lpUserSkill->GetSkillID() );

		if( lpSpell != NULL )
		{			
			sending << (short)lpUserSkill->GetSkillID();
			//sending << (short)lpUserSkill->nSkillPnts;
			//sending << (char)lpSpell->bSpellType;
			BYTE bTarget = lpSpell->bTarget;
            //switch( bTarget ){
            //case TARGET_UNIT_LIVING_NONSELF:
            //case TARGET_UNIT_ANY_NONSELF:
            //case TARGET_UNIT_PC_NONSELF:
            //case TARGET_UNIT_LIVING_FAVOR_NPC:
            //case TARGET_UNIT_LIVING_FAVOR_NPC_NONSELF:
            //    bTarget = TARGET_UNIT_ANY;
            //}
            sending << (char)bTarget;
			sending << (short)lpSpell->bfManaCost.GetBoost( this );
            sending << (long)lpSpell->bfDuration.GetBoost( this );
            sending << (short)lpSpell->saAttrib.Level;
            sending << (short)lpSpell->bElementType;            
            sending << (short)lpSpell->bDamageType;
            sending << (long)lpSpell->dwIcon;
            sending << lpSpell->GetDesc( GetLang() );

			sending << (CString)( lpSpell->GetName( GetLang() ) );
		}else{
			sending << (short)0;
		}
	}
	lptlusSpells->Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::PacketStatus
//////////////////////////////////////////////////////////////////////////////////////////
// PAckets the user's status
// 
(
 TFCPacket &sending, // The packet
 bool gameop
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	//////////////////////////////////////////////////////////////////////////////////
	// This request is sent by the client to query its stats/hp/mana alouette
	
    // If the gameop set a context.
    if( gameopContext != NULL && !gameop )
	{
        // Use this context.
        gameopContext->PacketStatus( sending, true );
        return;
    }

    sending << (RQ_SIZE)RQ_GetStatus;
	sending << (long)GetHP();
	sending << (long)GetMaxHP();
	sending << (short)GetMana();
	sending << (short)GetMaxMana();
	sending << (long)(GetXP() >> 32);
	sending << (long)GetXP();
	sending << (short)GetAC();
    sending << (short)GetTrueAC();
	sending << (short)GetSTR();
	sending << (short)GetEND();
	sending << (short)GetAGI();
	sending << (short)0; // wil
	sending << (short)GetWIS();
	sending << (short)GetINT();
	sending << (short)GetLCK(); // lck
	sending << (short)GetStatPoints();
    sending << (short)GetTrueSTR();
    sending << (short)GetTrueEND();
    sending << (short)GetTrueAGI();
    sending << (short)0; // wil
    sending << (short)GetTrueWIS();
    sending << (short)GetTrueINT();
    sending << (short)GetTrueLCK(); // lck
    sending << (short)GetLevel();
    sending << (short)GetSkillPoints();
    sending << (short)GetWeight();
    sending << (short)GetMaxWeight();
    sending << (short)GetKarma();
    sending << (short)GetTrueMaxHP();

	sending << (short)GetWaterPower();
	sending << (short)GetEarthPower();
	sending << (short)GetAirPower();
	sending << (short)GetFirePower();
	sending	<< (short)GetLightPower();
	sending	<< (short)GetDarkPower();
	sending << (short)GetWaterResist();
	sending << (short)GetEarthResist();
	sending << (short)GetAirResist();
	sending << (short)GetFireResist();
	sending	<< (short)GetLightResist();
	sending	<< (short)GetDarkResist();

	sending << (short)GetTrueWaterPower();
	sending << (short)GetTrueEarthPower();
	sending << (short)GetTrueAirPower();
	sending << (short)GetTrueFirePower();
	sending	<< (short)GetTrueLightPower();
	sending	<< (short)GetTrueDarkPower();
	sending << (short)GetTrueWaterResist();
	sending << (short)GetTrueEarthResist();
	sending << (short)GetTrueAirResist();
	sending << (short)GetTrueFireResist();
	sending	<< (short)GetTrueLightResist();
	sending	<< (short)GetTrueDarkResist();

}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::PacketPvpRanking
//////////////////////////////////////////////////////////////////////////////////////////
// PAckets the user's status
// 
(
 TFCPacket &sending, // The packet
 bool gameop
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	//////////////////////////////////////////////////////////////////////////////////
	// This request is sent by the client to query its stats/hp/mana alouette
	
    // If the gameop set a context.
    if( gameopContext != NULL && !gameop )
	{
        // Use this context.
        gameopContext->PacketPvpRanking( sending, true );
        return;
    }
	
	sending << (RQ_SIZE)RQ_GetPvpRanking;
	sending << (long)GetTotalDeathNumber();
	sending << (long)GetTotalKillNumber();
	sending << (long)GetCurrentDeathNumber();
	sending << (long)GetCurrentKillNumber();
	sending << (long)GetBestSerieMurder();
	sending << (long)GetCurrentSerieMurder();
	sending << (long)GetCurrentPvpPoint();
	
}

//////////////////////////////////////////////////////////////////////////////////////////
WORD Character::GetLang( void ) const
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the language associated to a character.
// 
// Return: WORD, the language.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return wLang;
}

//////////////////////////////////////////////////////////////////////////////////////////
int Character::GetMaxWeight( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Gets the maximum weight a character can hold.
// 
// Return: int, the maximum weight.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return ( GetSTR() * 500 / ( 100 + GetSTR() ) );
}

//////////////////////////////////////////////////////////////////////////////////////////
int Character::GetWeight( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the current weight of the player.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    int nWeight = 0;

    // Get weight of backpack
    backpack->Lock();
    backpack->ToHead();
    while( backpack->QueryNext() )
	{
        Objects *obj = static_cast< Objects * >( backpack->Object() );
        nWeight += obj->GetWeight() * obj->GetQty();
    }
    backpack->Unlock();

    // Get weight of equipped objects.
    int i;
    for( i = 0; i < EQUIP_POSITIONS; i++ )
	{
        if( equipped[ i ] != NULL )
		{
            if( i == weapon_left )
			{
                // If this isn't a two handed weapon.
                if( equipped[ weapon_right ] != equipped[ weapon_left ] )
				{
                    nWeight += equipped[ i ]->GetWeight();
                }
            }
			else
			{
                nWeight += equipped[ i ]->GetWeight();
            }
        }
    }
    
    return nWeight;
}

//////////////////////////////////////////////////////////////////////////////////////////
int Character::GetFreeWeight( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Gets the free weight that the character can use to hold more items
// IMPORTANT: this will move around the list pointer of backpack, thus invalidating
//				the current object being pointed by the backpack!
//				Trying this will certainly fail:
//				backpack->QueryNext(); GetFreeWeight(); backpack->Remove();
// 
// Return: int, the available weight.
//////////////////////////////////////////////////////////////////////////////////////////
{
    int currentWeight	= GetWeight();
	int maxWeight		= GetMaxWeight();
	if (currentWeight >= maxWeight) return 0;
	return (maxWeight - currentWeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::SendPrivateMessage
//////////////////////////////////////////////////////////////////////////////////////////
// Sends a private NPC message to this character.
// 
(
 CString &csMessage,    // The message to be sent.
 Unit *lpuTarget,       // The unit which talks.
 DWORD dwColor          // Talk color.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	BYTE bDirection = 0;	
	signed int Xoff, Yoff;

    WorldPos wlUs   = lpuTarget->GetWL();
	WorldPos wlThem = GetWL();
	
	Xoff = (wlThem.X - wlUs.X + 11) * 3;
	Yoff = (wlThem.Y - wlUs.Y + 16) * 2;

	if( Yoff > 30 )
	{
		if( Xoff > 30 )
		{
			Xoff -= 30;
			Yoff -= 30;
			if( Xoff > 2 * Yoff )
			{
				bDirection = KP_EAST;
			}
			else if( Yoff > Xoff * 2 )
			{
				bDirection = KP_SOUTH;
			}
			else
			{
				bDirection = KP_SOUTHEAST;
			}
		}
		else
		{
			Yoff -= 30;
			Xoff = 30 - Xoff;
			if( Xoff > 2*Yoff )
			{
				bDirection = KP_WEST;
			}
			else if( Yoff > 2 * Xoff )
			{
				bDirection = KP_SOUTH;
			}
			else 
			{
				bDirection = KP_SOUTHWEST;
			}
		}
	}
	else
	{
		if( Xoff > 30 )
		{
			Xoff -= 30;
			Yoff = 30 - Yoff;
			if( Xoff > 2 * Yoff )
			{
				bDirection = KP_EAST;
			}
			else if( Yoff > Xoff * 2 )
			{
				bDirection = KP_NORTH;
			}
			else
			{
				bDirection = KP_NORTHEAST;
			}
		}
		else
		{
			Yoff = 30 - Yoff;
			Xoff = 30 - Xoff;
			if( Xoff > 2*Yoff )
			{
				bDirection = KP_WEST;
			}
			else if( Yoff > 2 * Xoff )
			{
				bDirection = KP_NORTH;
			}
			else 
			{
				bDirection = KP_NORTHWEST;
			}
		}
	}

	DWORD dwNameColor = RGB(255,0,0);
    TFCPacket sending;

    sending << (RQ_SIZE)__EVENT_SHOUT;
    sending << (long)lpuTarget->GetID();
    sending << (char)bDirection;
    sending << (long)dwColor;
    if( lpuTarget->GetType() != U_PC )
	{
        sending << (char)1; // an NPC.
		dwNameColor = U_NPC_COLOR;
    }else{
        sending << (char)0; // not an NPC.
		Players *TargetPlayer = static_cast< Players * >(lpuTarget->GetPlayer());
		if ( TargetPlayer->IsGod() ) dwNameColor = U_GOD_COLOR
		else dwNameColor = U_PC_COLOR;
    }
    sending << (CString &)csMessage;
    sending << (CString )lpuTarget->GetName( GetLang() );
	sending << (long)dwNameColor;

    SendPlayerMessage( sending ); 
}

//////////////////////////////////////////////////////////////////////////////////////////
int Character::NextLevelXP( void ) // __int64
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the XP needed to raise next level.
// 
// Return: __int64, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    WORD wLevel = GetLevel();

    if( wLevel >= MAX_LEVEL )
	{
		wLevel = MAX_LEVEL - 1;
    }
	else if( wLevel == 0 )
	{
        wLevel = 1;
    }
    
    return sm_n64XPchart[ wLevel ];
}
//////////////////////////////////////////////////////////////////////////////////////////
int Character::PreviousLevelXP( void ) // __int64
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the XP needed to raise next level.
// 
// Return: __int64, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    WORD wLevel = GetLevel() - 1;
    
    if( wLevel >= MAX_LEVEL )
	{
        wLevel = MAX_LEVEL - 1;
    }
	else if( wLevel == 0 )
	{
        wLevel = 1;
    }
    
    return sm_n64XPchart[ wLevel ];
}

//////////////////////////////////////////////////////////////////////////////////////////
int Character::XPtoLevel( void ) // __int64
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the XP left before raising to next level.
// 
// Return: __int64, 
//////////////////////////////////////////////////////////////////////////////////////////
{
	try {
		WORD wLevel = GetLevel();

		if( wLevel >= MAX_LEVEL ){
			wLevel = MAX_LEVEL - 1;
		}else if( wLevel == 0 ){
			wLevel = 1;
		}

		return sm_n64XPchart[ wLevel ] - GetXP();
	} catch(...) {
        try{
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "Crashed Character::XPtoLevel, character %s.",
                GetName( _DEFAULT_LNG ).c_str()
            LOG_
        }catch(...){
        }
        throw;
	}
}

#define PACKET_POS( __pos ) wValue = equipped[ __pos ] ? equipped[ __pos ]->GetAppearance() : 0;\
                            TRACE( "\r\n%u.", wValue );\
                            sending << (short)wValue

//////////////////////////////////////////////////////////////////////////////////////////
void Character::PacketPuppetInfo
//////////////////////////////////////////////////////////////////////////////////////////
// Packets the puppet information of a player.
// 
(
 TFCPacket &sending // The packet in which to put the puppet information.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    WORD wValue;

    sending << (RQ_SIZE)RQ_PuppetInformation;
    sending << (long) GetID();
    PACKET_POS( body );
    PACKET_POS( feet );
    PACKET_POS( gloves );
    PACKET_POS( helm );
    PACKET_POS( legs );
    PACKET_POS( weapon_right );
    PACKET_POS( weapon_left );
    PACKET_POS( cape );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::Disturbed( WORD pTriggers )
//////////////////////////////////////////////////////////////////////////////////////////
//  Called whenever the character gets disturbed (moves, use item, use skill, cast spell)
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Stop meditating.
    RemoveFlag( __FLAG_MEDITATING );

	long lTime;
	lTime = time(NULL);
	this->lLastEventTime=lTime;
	
	//sur havoc on desactive ça
	 
	if (this->boClientExitCountDown) {//BLBLBL : si on sait que le client est justement en train de décompter à ce moment
		TFCPacket sending; //on lui envoie un paquet lui demandant d'arrêter de compte, puisque le perso a été disturbed
		sending << (RQ_SIZE)(RQ_SafePlug); //BLBLBL Antiplug : on informe le client qu'on a du annuler la déco
		sending << (char)0;	// 0 = Il faut annuler le compteur
		SendPlayerMessage( sending );
		this->boClientExitCountDown=false;//on met à false, pour éviter de flooder le client de paquets indiquant qu'il doit stopper le compteur
	}


	if ( !(pTriggers & DISTURB_DONTCANCELROB) ) {
		// if this trigger is not present... Stop robbing!
		if( ViewFlag( __FLAG_ROBBING ) != 0 ){
			SetTarget( NULL );
			RemoveFlag( __FLAG_ROBBING );
    
			TFCPacket sending;
			sending << (RQ_SIZE)RQ_DispellRob;
			SendPlayerMessage( sending );
		}
	}

	// Block from using chest and close interface
	if (pTriggers & DISTURB_CLOSECHEST) {
		if (boCharacterIsChesting == TRUE) StopUsingChest();
	}

	if (pTriggers & DISTURB_CLOSETRADE) {
		m_TradeMgr2.CancelDisturbed();
	}

	if (pTriggers & DISTURB_UNHIDE) {
		Unhide();
	}

}

//////////////////////////////////////////////////////////////////////////////////////////
bool Character::PreTranslateInGameMessage
//////////////////////////////////////////////////////////////////////////////////////////
//  Pre-translates all messages that come from the console.
// 
(
 CString csString // The string that was send to the console.
)
// Return: bool, true if the message should be sent to everyone on the screen too.
//////////////////////////////////////////////////////////////////////////////////////////
{
    bool boReturn = true;
    
    return boReturn;
}

    
//////////////////////////////////////////////////////////////////////////////////////////
void Character::SetGroup
//////////////////////////////////////////////////////////////////////////////////////////
// Sets a character's group.    
// 
(
 Group *lpNewGroup // The group.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // A group should never be set twice. A Character cannot have two groups.
    ASSERT( lpGroup == NULL );
    lpGroup = lpNewGroup;
}    
    
//////////////////////////////////////////////////////////////////////////////////////////
Group *Character::GetGroup( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Gets a character's group.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return lpGroup;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::VaporizeUnit( void )
//////////////////////////////////////////////////////////////////////////////////////////
// You can't really 'vaporize' a player.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    ATTACK_STRUCTURE Blow;
    memset( &Blow, 0, sizeof( Blow ) );
    
    // Simply kill the player.
	Death( &Blow, NULL );	
}


//////////////////////////////////////////////////////////////////////////////////////////
void Character::CopySpells
//////////////////////////////////////////////////////////////////////////////////////////
//  Copies the spells from a given unit into this character.
// 
(
 Unit *lpSource // This unit.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // NPC.
    if( lpSource->GetType() == U_NPC )
	{
        // Get the MOB structure.
        MonsterStructure *lpMob;
        lpSource->SendUnitMessage( MSG_OnGetUnitStructure, lpSource, NULL, NULL, NULL, &lpMob );
        
        // If there was a mob structure.
        if( lpMob != NULL )
		{        
            // Flush this user's spells.
            tlusSpells.AnnihilateList();

            vector< LPMONSTER_ATTACK >::iterator i;
            for( i = lpMob->vlpRangeAttacks.begin(); i != lpMob->vlpRangeAttacks.end(); i++ )
			{
                // If this is a spell attack.
                if( (*i)->GetType() == SPELL_ATTACK )
				{
                    MONSTER_SPELL_ATTACK *lpMonsterSpell = static_cast< LPMONSTER_SPELL_ATTACK >(*i);

                    // Create a new UserSpell
                    USER_SKILL *lpUserSkill = new USER_SKILL;
                    lpUserSkill->SetSkillPnts( 0 );                    
                    lpUserSkill->SetSkillID( lpMonsterSpell->wSpellID );

                    TRACE( "\nAdding spell %u.", lpUserSkill->GetSkillID() );

                    // Add it to the user's list of spells.
                    tlusSpells.AddToTail( lpUserSkill );
                }
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::StartAutoCombat
//////////////////////////////////////////////////////////////////////////////////////////
// Starts auto-combat.
// 
(
 Attack attack,  // The attack to start.
 Unit *target
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    prevAutoCombatAttack = autoCombatAttack;
    prevAutoCombatState = autoCombatState;
    prevTarget = GetTarget();
    
    autoCombatState = true;
    autoCombatAttack = attack;
    SetTarget( target );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::StopAutoCombat( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Stops auto-combat.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    autoCombatState = false;
}

//////////////////////////////////////////////////////////////////////////////////////////
bool Character::QueryAutoCombatState
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the auto-combat state and the attack style.
(
    Attack *attack // The attack style to fill. NULL if information isn't needed.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( attack != NULL )
	{
        *attack = autoCombatAttack;
    }
    return autoCombatState;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::RestorePreviousAutoCombatState( void )
//////////////////////////////////////////////////////////////////////////////////////////
// This function returns the previously saved auto combat state before the last 
// SetAutoCombat call.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    bool tmpState = prevAutoCombatState;
    Attack tmpAttack = prevAutoCombatAttack;
    Unit *tmpTarget = prevTarget;

    prevAutoCombatState = false;
    prevAutoCombatAttack = autoCombatAttack;
    prevTarget = GetTarget();

    autoCombatState = tmpState;
    autoCombatAttack = tmpAttack;
    SetTarget( tmpTarget );
}

//////////////////////////////////////////////////////////////////////////////////////////
bool Character::ExecAutoCombat( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Executes auto-combat if attack or spell exhaustion has ended.
// 
// Returns: bool, true if an attack was executed.
//////////////////////////////////////////////////////////////////////////////////////////
{    
    Unit *target = GetTarget();
    // If target doesn't exist
    if( target == NULL )
	{
		StopAutoCombat();
        return false;
    }

    if( target->ViewFlag( __FLAG_INVISIBILITY ) != 0 && ViewFlag( __FLAG_DETECT_INVISIBILITY ) == 0 && this != target )
	{

        StopAutoCombat();
        return true;
    }
    if( target->ViewFlag( __FLAG_HIDDEN ) != 0 && ViewFlag( __FLAG_DETECT_HIDDEN ) == 0 && this != target )
	{

        StopAutoCombat();
        return true;
    }


    // Calculate the range between the two players.
    int nXdiff = abs( GetWL().X - target->GetWL().X );
    int nYdiff = abs( GetWL().Y - target->GetWL().Y );
    int nRange = ::sqrt((double) nXdiff * nXdiff + nYdiff * nYdiff ); // steph ajout de (double)

    // If player is currently robbing.
    if( ViewFlag( __FLAG_ROBBING ) != 0 )
	{

        const INT PeekRange = 2; // steph ajout de INT

        // If the player is still within range.
        if( nRange <= PeekRange )
		{
            return true;
        }
        
        // Otherwise, cancel robbing.
        SetTarget( NULL );
        RemoveFlag( __FLAG_ROBBING );
        
        TFCPacket sending;
        sending << (RQ_SIZE)RQ_DispellRob;
        SendPlayerMessage( sending );

        return true;
    }

    // If auto combat is off or player doesn't have a target.
    if( !QueryAutoCombatState() )
	{
        return false;
    }

	// If the target is too far away.
	if( nRange >= 25 )
	{
		// Stop combat.
		SetTarget( NULL );
		StopAutoCombat();		
		return false;
	}

    if( target->GetType() == U_PC )
	{
        Character *lpChar = static_cast< Character * >( target );
        Players *targetPl = reinterpret_cast< Players * >( lpChar->GetPlayer() );
		if ( targetPl == NULL ){	//DC for GPs
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "DC - GPs - target player object is null."
            LOG_
			StopAutoCombat();
			return false;
		}							//DC for GPs
        if( !targetPl->in_game )
		{
            StopAutoCombat();
            return false;
        }
    }
	
    EXHAUST exhaust = GetExhaust();

    if( autoCombatAttack.attackType == Attack::normal )
	{
        // If target isn't in PVP
        if( !GAME_RULES::InPVP( this, target ) )
		{

            CString csText = _STR( 14, GetLang() );
            TFCPacket sending;
		    sending << (RQ_SIZE)RQ_ServerMessage;
		    sending << (short)30;
		    sending << (short)3;
		    sending << (CString &)csText;
			sending << (long)0x000A64E0/*RGB( 0, 100, 255 )*/;
            SendPlayerMessage( sending );

            SetTarget( NULL );
            StopAutoCombat();

            return false;
        }

        // If player is still physically exhausted.
        if( exhaust.attack > TFCMAIN::GetRound() )
		{
            return false;
        }

        // Lock target and this character.
        MultiLock( this, target );

        WorldPos targetPos = target->GetWL();
        WorldPos userPos   = GetWL();

        int xRange = abs( userPos.X - targetPos.X );
        int yRange = abs( userPos.Y - targetPos.Y );
        int reachRange = _DEFAULT_REACH_RANGE;
        
        bool rangedAttack = RangedAttack();
        if( rangedAttack )
		{
            reachRange = 25;
        }

        // If this is not a ranged attack, check if the current weapon is a bow.
        if( equipped[ BOW_POS ] != NULL && !rangedAttack )
		{
	        _item *itemStructure = NULL;

        	// Get the item structure.
            equipped[ BOW_POS ]->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &itemStructure );

            // If the weapon is a ranged weapon.
            if( itemStructure == NULL || itemStructure->weapon.ranged )
			{
                // Tell the user that the user cannot attack normally with a bow.
                SendSystemMessage( _STR( 7846, GetLang() ) );

                StopAutoCombat();
                
                Unlock();
                target->Unlock();
                return false;
            }
        }

        // If player isn't in range of target.
        if( xRange > reachRange || yRange > reachRange )
		{
            Unlock();
            target->Unlock();            
            return false;
        }

        if( !rangedAttack )
		{
            bool blockedPath = false;
			try {
				// Attack.
				TFCMAIN::Attack( this, target, blockedPath );
			} catch(...) {
                try{
                    _LOG_DEBUG
                        LOG_CRIT_ERRORS,
                        "Crashed Character::ExecAutoCombat while calling TFCMAIN::Attack, Character %s target %s(%u) type %u.",
                        GetName( _DEFAULT_LNG ).c_str(),
                        target->GetName( _DEFAULT_LNG ).c_str(),
                        target->GetStaticReference(),
                        target->GetType()
                    LOG_
                }catch(...){
                }
                throw;
			}
        }else{
            RangeAttack( target );
        }

        Unlock();
        target->Unlock();        
    
    }
	else if( autoCombatAttack.attackType == Attack::spell )
	{
        // If player is still mentally exhausted.
        if( exhaust.mental > TFCMAIN::GetRound() )
		{
            return false;
        }
        // Lock target and this character.
        MultiLock( this, target );

        // Cast spell on target.
        CastSpell( autoCombatAttack.spellID, target );

        Unlock();
        target->Unlock();
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::PacketBackpack
//////////////////////////////////////////////////////////////////////////////////////////
//  Packets the user backpack.
// 
(
 TFCPacket &sending,
 bool gameop
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( gameopContext != NULL && !gameop )
	{
        gameopContext->PacketBackpack( sending, true );
        return;
    }

    TemplateList <Unit> *lptluBackpack = GetBackpack();
	
	if( lptluBackpack != NULL )
	{
		lptluBackpack->Lock();
		lptluBackpack->ToHead();

		sending << (short)lptluBackpack->NbObjects();

        while( lptluBackpack->QueryNext() )
		{
			Objects *lpuObject = static_cast< Objects * >( lptluBackpack->Object() );
			sending << (short)lpuObject->GetAppearance();
			sending << (long) lpuObject->GetID();
            sending << (short)lpuObject->GetStaticReference();
            sending << (long) lpuObject->GetQty();

            // Only unique items may have charges.
            if( lpuObject->IsUnique() ){
                sending << (long)lpuObject->ViewFlag( __FLAG_CHARGES );
            }
			else
			{
                sending << (long)0;
            }
		}
		lptluBackpack->Unlock();
	}
	else
	{
		sending << (short)0;
	}

    // If ANY backpack update occur, remove the robbing flag.
    RemoveFlag( __FLAG_ROBBING );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::PacketRobBackpack
//////////////////////////////////////////////////////////////////////////////////////////
//  Packets the robber's backpack.
// 
(
 Unit *robber,
 TFCPacket &sending // 
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TemplateList <Unit> *lptluBackpack = GetBackpack();
	
	if( lptluBackpack != NULL ){
		lptluBackpack->Lock();
		lptluBackpack->ToHead();

		sending << (short)lptluBackpack->NbObjects();

        while( lptluBackpack->QueryNext() )
		{
			Objects *lpuObject = static_cast< Objects * >( lptluBackpack->Object() );
			sending << (short)lpuObject->GetAppearance();
			sending << (long) lpuObject->GetID();
            sending << (short)lpuObject->GetStaticReference();
            sending << (long) lpuObject->GetQty();
            sending << (CString )lpuObject->GetName( robber->GetLang() );
		}
		lptluBackpack->Unlock();
	}
	else
	{
		sending << (short)0;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
void Character::JunkItems
//////////////////////////////////////////////////////////////////////////////////////////
//  Junks a list of items
// 
(
 DWORD id,  // ID if item stack to junk from.
 DWORD qty, // Quantity of items to junk from the stack.
 bool gameop
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( gameopContext != NULL && !gameop )
	{
        gameopContext->JunkItems( id, qty, true );
        return;
    }

    CAutoLock autoLock( backpack );

    bool junked = false;
    bool updateGold = false;
    DWORD newGold = 0;
    backpack->ToHead();
    while( backpack->QueryNext() )
	{
        Objects *u = static_cast< Objects * >( backpack->Object() );
        if( u->GetID() == id )
		{
			_item *item = NULL;

			// Get the item structure.
			u->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &item );

			// If the item can be junked.
            if( item != NULL && (!( item->dwDropFlags & CANNOT_JUNK_ITEM ) || gameop) ){
                if( u->GetStaticReference() == __OBJ_GOLD ){
                    updateGold = true;
                    if( qty < GetGold() )
					{
                        newGold = GetGold() - qty;
                    }
                }

				// Get the right qty for logging purposes
				DWORD logQty;
				if (qty > u->GetQty()) logQty = u->GetQty();
				else logQty = qty;
				// Get the name of the item:)
				char lpszID[ 256 ];
				Unit::GetNameFromID( u->GetStaticReference(), lpszID, U_OBJECT );

				_LOG_ITEMS
					LOG_MISC_1,
					"Player %s junked %u item %s ID( %s )",
					GetTrueName().c_str(),
					logQty,
					u->GetName( _DEFAULT_LNG ).c_str(),
					lpszID
				LOG_

                u->Remove( qty );
                if( u->GetQty() == 0 )
				{                
                    u->DeleteUnit();
                    backpack->Remove();
                }

                junked = true;
            }
			else
			{
                TFormat format;
                SendSystemMessage(
                    format(
                        _STR( 7260, GetLang() ),
                        u->GetName( GetLang() ).c_str()
                    )
                );
            }
            break;
        }
    }

    if( updateGold )
	{
        SetGold( newGold );
    }

    // If any item got junked
    if( junked )
	{
        // Send a backpack update.
        TFCPacket sending;
        sending << (RQ_SIZE)RQ_ViewBackpack;
		sending << (char)0;
		sending << (long)GetID();
		PacketBackpack( sending );

        SendPlayerMessage( sending );
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
void Character::AddToBackpack
//////////////////////////////////////////////////////////////////////////////////////////
//  Adds an object, safely, to the backpack
// 
(
 Objects *obj // The object
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	_item *itemStructure = NULL;

	// Get the item structure.
	obj->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &itemStructure );

	// If this is a Quiver.
    if( itemStructure != NULL && itemStructure->itemStructureId == 12 ){
        // First search the equipped items.
        int i;
        for( i = 0; i < EQUIP_POSITIONS; i++ ){
            if( equipped[ i ] == NULL ){
                continue;
            };
            if( equipped[ i ]->GetStaticReference() == obj->GetStaticReference() ){
                // Simply add the item's quantity to this item.
                static_cast< Objects * >( equipped[ i ] )->Add( obj->GetQty() );

                // Delete this item's instance (replaced by the equipped item).
                obj->DeleteUnit();
                
                // Exit the function
                return;
            }
        }
    }    
    

    backpack->Lock();
    // If the object is NOT unique add it directly.
    bool add = true;
    if( !obj->IsUnique() ){
        backpack->ToHead();
        while( backpack->QueryNext() ){
            Objects *backpackItem = static_cast< Objects * >( backpack->Object() );

            // If an item of the same type was found.
            if( backpackItem->GetStaticReference() == obj->GetStaticReference() ){
                // Simply add the item's quantity to this item.
                backpackItem->Add( obj->GetQty() );

                // Delete this item's instance (replaced by the item in the backpack).
                obj->DeleteUnit();

                // Do not add the object to the backpack.
                add = false;

                break;
            }
        }
    }

    // If the object should be added to the backpack (not found or unique).
    if( add ){
        backpack->AddToTail( obj );

        TFCPacket sending;
        sending << (RQ_SIZE)RQ_UpdateWeight;
        sending << (long)GetWeight();
        sending << (long)GetMaxWeight();
    }
    backpack->Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::SynchronizeGold( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Synchronizes the gold stack with the current player's gold
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    backpack->Lock();
    backpack->ToHead();
    
    bool found = false;
    while( backpack->QueryNext() ){
        // If gold was found.
        Objects *obj = static_cast< Objects * >( backpack->Object() );
        if( obj->GetStaticReference() == __OBJ_GOLD ){
            // If a stack of gold was already found.
            if( found ){
                // Delete this stack of gold.
                obj->DeleteUnit();
                backpack->Remove();
            }else{            
                // Set its quantity equal to the quantity of gold on the player.
                obj->SetQty( GetGold() );
                found = true;
            }            
        }
    }

    // If not stack of gold was found.
    if( !found ){
        // Create a new one.
        Objects *obj = new Objects;
        if( obj->Create( U_OBJECT, __OBJ_GOLD ) ){
            obj->SetQty( GetGold() );

            backpack->AddToTail( obj );
        }else{
            obj->DeleteUnit();
        }
    }

    backpack->Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
CString Character::GetTitle( bool getAccountName )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the player's title
// 
// Return: CString, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( getAccountName ){
        Players *pl = static_cast< Players * >( GetPlayer() );

        ASSERT( pl != NULL );
        if( pl == NULL ){
            return csListingTitle;
        }
        return pl->GetFullAccountName();
    }


    return csListingTitle; 
};




//////////////////////////////////////////////////////////////////////////////////////////
// steph ajout
//////////////////////////////////////////////////////////////////////////////////////////
CString Character::GetGuild(bool getAccountName)
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the player's guild
// 
// Return: CString, 
//////////////////////////////////////////////////////////////////////////////////////////
{
	if (getAccountName) {
		Players *pl = static_cast< Players * >(GetPlayer());

		ASSERT(pl != NULL);
		if (pl == NULL) {
			return csGuildName;
		}
		return pl->GetFullAccountName();
	}


	return csGuildName;
};





//////////////////////////////////////////////////////////////////////////////////////////
void Character::SetLevel
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets the character's level
// 
(
 WORD dwLevel // The new level
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    Unit::SetLevel( dwLevel );

    // Update all group members to reflect the level change.
    Group *group = GetGroup();
    if( group != NULL ){
        vector< Character * > members;
        group->GetGroupMembers( members );

        int i;
        for( i = 0; i < members.size(); i++ ){
            group->SendGroupMembers( members[ i ] );
        }
    }
   
 	TFCPacket sending;
    sending << (RQ_SIZE)RQ_LevelUp;
	sending << (short)dwLevel;
	if (dwLevel > MAX_LEVEL) dwLevel = MAX_LEVEL-1; // sm_n64XPchart is an array of MAX_LEVEL size, cant go over this index on it.
	sending << (long)(Character::sm_n64XPchart[dwLevel] >> 32);
	sending << (long)Character::sm_n64XPchart[dwLevel];
	sending << (long)GetHP();
    sending << (long)GetMaxHP();
    sending << (short)GetMana();
	sending << (short)GetMaxMana();	

	SendPlayerMessage( sending );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::Rob
//////////////////////////////////////////////////////////////////////////////////////////
//  Robs the character.
// 
(
 DWORD objId // The Id of the object to rob.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    DWORD dwRobID = ViewFlag( __FLAG_ROBBING );        

    if( dwRobID == 0 ){
        TELL_PLAYER( 25 );
        return;
    }
    WorldMap *wlWorld = TFCMAIN::GetWorld( GetWL().world );

    if( !wlWorld ){
        RemoveFlag( __FLAG_ROBBING );
        return;
    }



    // Get the target unit.
    Unit *target = GetTarget();
    if( target == NULL ){
        TELL_PLAYER( 25 );
        RemoveFlag( __FLAG_ROBBING );
        return;
    }
    
    // Use Rob on the target unit.
    UseSkill( __SKILL_ROB, target, (LPVOID)objId );

    RemoveFlag( __FLAG_ROBBING );
    SetTarget( NULL );
}

//////////////////////////////////////////////////////////////////////////////////////////
bool Character::RangedAttack( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Queries whether the player is attacking with ranged weapons.
// 
// Return: bool, true if the attacker is attacking with a range weapon.
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Requires a bow and a quiver, both equipped.
    if( equipped[ BOW_POS ] == NULL || equipped[ QUIVER_POS ] == NULL ){
        return false;
    }
	_item *itemStructure = NULL;

	// Get the item structure.
    equipped[ BOW_POS ]->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &itemStructure );

	// If this is not a ranged weapon.
    if( itemStructure == NULL || !itemStructure->weapon.ranged ){
        return false;
    }

	// Get the item structure.
    equipped[ QUIVER_POS ]->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &itemStructure );

	// If this is not a quiver.
    if( itemStructure == NULL || itemStructure->itemStructureId != 12 ){
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////
void GetArrowHitTest
//////////////////////////////////////////////////////////////////////////////////////////
// Gets the hit test of an arrow shot at the given target.
// 
(
 ATTACK_STRUCTURE &blow,    // The blow structure to fill-in.
 Character *self,           // The attacker.
 Unit *target,              // The target.
 _item *quiverData,         // The quiver data.
 _item *bowData             // The bow data.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	blow.lDodgeSkill = target->GetDODGE();
	blow.lDodgeSkill = blow.lDodgeSkill > 0 ? blow.lDodgeSkill : 1;

    // Return if any of the two opponents are in a safe area.
    if( (self->GetUnderBlock() == __SAFE_HAVEN || self->GetUnderBlock() == __INDOOR_SAFE_HAVEN ||
	    target->GetUnderBlock() == __SAFE_HAVEN || target->GetUnderBlock() == __INDOOR_SAFE_HAVEN )
        && target->GetType() == U_PC && self->GetType() == U_PC ){
        
        blow.Precision = -1;
        return;
    }

    // If the two units are in PVP
    if( !GAME_RULES::InPVP( self, target ) ){
        blow.Precision = -1;
        return;
    }


    // Calculate the range between the two players.
    int nXdiff = abs( self->GetWL().X - target->GetWL().X );
    int nYdiff = abs( self->GetWL().Y - target->GetWL().Y );
    int nRange = ::sqrt((double) nXdiff * nXdiff + nYdiff * nYdiff ); // steph ajout de (double)
    
    
    // Calculate damage done by the attacker.
    self->attack( &blow, target );

    // Get the damage dealt by the arrows in the quiver.
    double arrowDmg = quiverData->weapon.cDamage.GetBoost( self, target, 0, 0, nRange );

    // Deal the damage using the bow's damage, passing the arrow damage
    // as the 'x' boost parameter.
    blow.Strike += bowData->weapon.cDamage.GetBoost( self, target, arrowDmg, 0, nRange );

    // Set true strike (before AC calculation).
    blow.TrueStrike = blow.Strike;

	// Get the archery skill.
    DWORD archerySkill = 1;
    {
        LPUSER_SKILL archery = self->GetSkill( __SKILL_ARCHERY );
        if( archery != NULL ){
            archerySkill = archery->GetSkillPnts( self );
        }
    }
    
	archerySkill = archerySkill > 0 ? archerySkill : 1;
	
    blow.lAttackSkill = archerySkill;

    // Set the blow's precision.
	blow.Precision = GAME_RULES::GetBlowPrecision( 
        archerySkill, 
        blow.lDodgeSkill,
        self->GetAGI(),
        target->GetAGI()
    );
}

//////////////////////////////////////////////////////////////////////////////////////////
void BroadcastArrow
//////////////////////////////////////////////////////////////////////////////////////////
// Broadcasts an arrow-type packet.
// 
(
 TFCPacket &sending,    // The packet.
 WorldPos fromPos,      // The from position of the arrow.
 WorldPos toPos         // The to position of the arrow.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Calculate the broadcasting range.
    WorldPos midPos = { 0, 0, fromPos.world };    

    int xDiff = fromPos.X - toPos.X;
    int yDiff = fromPos.Y - toPos.Y;

    midPos.X = xDiff / 2 + toPos.X;
    midPos.Y = yDiff / 2 + toPos.Y;

    // Add the distance between the mid pos and the farest unit
    // to the default broadcasting range.
	// BLBL en clair : on broadcast à partir du centre de la trajectoire de la flèche pour informer tous les gens
	// se trouvant sur le trajet de celle ci.
    int range;
    if( xDiff > yDiff ){
        range = xDiff / 2 + _DEFAULT_RANGE;
    }else{
        range = yDiff / 2 + _DEFAULT_RANGE;
    }

    Broadcast::BCast( midPos, range, sending );
}

//////////////////////////////////////////////////////////////////////////////////////////
void MakeArrowMiss
//////////////////////////////////////////////////////////////////////////////////////////
// Makes an arrow miss the target starting from 'self'.
// 
(
 Unit *self,            // The attacker.
 WorldPos targetPos,    // The target position.
 bool collision         // True if the miss was due to a collision.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Broadcast the miss.
    TFCPacket sending;
    sending << (RQ_SIZE)RQ_ArrowMiss;
    sending << (long)self->GetID();
    sending << (short)targetPos.X;
    sending << (short)targetPos.Y;
    if( collision ){
        sending << (char)1;
    }else{
        sending << (char)0;
    }

    BroadcastArrow( sending, self->GetWL(), targetPos );
};

//////////////////////////////////////////////////////////////////////////////////////////
void DealArrowDamage
//////////////////////////////////////////////////////////////////////////////////////////
// Deals damage done by an arrow that succesfully hit its target.
// 
(
 Character *self,           // The unit attacking.
 Unit *target,              // The arrow's target.
 ATTACK_STRUCTURE &blow     // The blow.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    double preACstrike = blow.Strike;

    if( target->GetType() == U_HIVE || target->GetType() == U_OBJECT ){
        return;
    }

	// If target can attack
	if( target->CanAttack() ){
        if( target->GetType() == U_NPC ){
			// Force unit into fight
			target->Do( fighting );
			target->SetTarget( self );
        }
	}

    // If attack is previously hidden.
    if( self->ViewFlag( __FLAG_HIDDEN ) ){
        // Hit more!!! Mouahahahahha
        blow.Strike = blow.Strike * ( 149 + rnd.roll( dice( 1, 50 ) ) ) / 100;
    }

    // Dispell any invisibility on the attack.
    self->DispellInvisibility();

	// Got hit, so cannot be stun anymore
	if( target->ViewFlag( __FLAG_STUN ) ){
		// Hit more!!! MouAHaHahAHahahAHa
		blow.Strike *= 15; // * 1.5, in integers..
		blow.Strike /= 10;

		// Removes the stun timer possibily associated with it					
		target->RemoveFlag(__FLAG_STUN);
	}
				
	// Tell attacker that the attack hit!
	self->attack_hit( &blow, target );

    // Target is move-frozen for 500 ms.
	//target->DealExhaust( 0, 0, 500 );
	
	// Tell target that it is being attacked.
    target->attacked( &blow, self );

	if(blow.Strike < 0){
		blow.Strike = 0;
	}

	double postACstrike = blow.Strike;// Save POST-AC strike value

    // Proccess triggered skills and god flags and get final damage value.
	// Hit the target with the blow!
    int result = target->hit( &blow, self );
			
    // GameOp stuff
    if( self->GetType() == U_PC ){
        Players *lpPlayer = static_cast< Character *>( self )->GetPlayer();
        if( lpPlayer != NULL ){
            if( lpPlayer->GetGodFlags() & GOD_DEVELOPPER ){
                TFormat format;
                self->SendSystemMessage(
                    format(
                        "Attack hits %s for %.2f damages (%.2f post-AC damages, %.2f final damage, %.2f true damage).",
                        (LPCTSTR)target->GetName(_DEFAULT_LNG),
                        preACstrike,
						postACstrike,
                        blow.Strike,
						blow.TrueStrike
                    )
                );
            }
        }
    }
    if( target->GetType() == U_PC ){
        Players *lpPlayer = static_cast< Character *>( target )->GetPlayer();
        if( lpPlayer != NULL ){
            if( lpPlayer->GetGodFlags() & GOD_DEVELOPPER ){
                TFormat format;
                target->SendSystemMessage(
                    format(
                        "You were hit by %s for %.2f damages (%.2f post-AC damages, %.2f final damage).",
                        (LPCTSTR)self->GetName(_DEFAULT_LNG),
                        preACstrike,
						postACstrike,
                        blow.Strike
                    )
                );
            }
        }
    }

    // Check for level gains.
    self->TrainUnit();

    // Broadcast the attack.
    TFCPacket sending;
    sending << (RQ_SIZE)RQ_ArrowHit;
    sending << (long)self->GetID();
    sending << (long)target->GetID();
    sending << (char)( target->GetHP() * 100 / target->GetMaxHP() );

    BroadcastArrow( sending, self->GetWL(), target->GetWL() );

	// If the unit got killed.
    if( result == -1 ){
        Broadcast::BCObjectChanged( target->GetWL(), _DEFAULT_RANGE,//BLBLBL _DEFAULT_RANGE+5 => _DEFAULT_RANGE 
            target->GetCorpse(),
		    target->GetID(),
            self->GetInvisibleQuery()
        );
    }
};

// This class will auto-remove an arrow from the quiver upon destruction.
class AutoArrowRemove{
public:
    AutoArrowRemove( Character *iself, Objects *iquiver, _item *iquiverData ) : 
      self( iself ), quiver( iquiver ), quiverData( iquiverData ){            
    }
    ~AutoArrowRemove(){

        if( quiverData->weapon.infiniteAmmo ){
            return;
        }
        // Remove an arrow from the quiver
        quiver->Remove();
        // If the quiver is now empty.
        if( quiver->GetQty() == 0 ){
            // Remove it from the equipped and destroy it.
            self->equipped[ Character::QUIVER_POS ] = NULL;
            quiver->DeleteUnit();
        }
        TFCPacket sending;
        self->packet_equiped( sending );
        self->SendPlayerMessage( sending );
    }
private:
    Character *self;
    Objects *quiver;
    _item *quiverData;
};

//////////////////////////////////////////////////////////////////////////////////////////
void Character::RangeAttack
//////////////////////////////////////////////////////////////////////////////////////////
// Attacks a target using a ranged weapon.
// 
(
 Unit *target // The target of the attack.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // If the player doesn't have a ranged weapon and quiver equipped.
    if( !RangedAttack() ){
        return;
    }

    // If the players are in a safe haven.
    if( GAME_RULES::InSafeHaven( this, target ) ){
        StopAutoCombat();

        // Notify the attacker.
        TFCPacket sending;
        sending << (RQ_SIZE)RQ_ServerMessage;
        sending << (short)30;
        sending << (short)3;
        CString csText = _STR( 22, GetLang() );
        sending << (CString &)csText;   
		sending << (long)0x000A64E0/*RGB( 0, 100, 255 )*/;
        SendPlayerMessage( sending );
        return;
	}

    // Cannot attack while stunned.
    if( ViewFlag( __FLAG_STUN ) != 0 ){
        return;               
    }    
    
    // Get the weapon and quiver.
    Objects *weapon = static_cast< Objects * >( equipped[ BOW_POS ] );
    Objects *quiver = static_cast< Objects * >( equipped[ QUIVER_POS ] );
	
    _item *weaponData = NULL;
    _item *quiverData = NULL;
    
	// Get the item structures.
    weapon->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &weaponData );
    quiver->SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &quiverData );

    WorldMap *wl = TFCMAIN::GetWorld( GetWL().world );

    // If any of the structures couldn't be fetched.
    if( weaponData == NULL || quiverData == NULL || wl == NULL ){
        return;
    }

    WorldPos thisPos = GetWL();
    WorldPos targetPos = target->GetWL();
    WorldPos foundPos;
    Unit *foundUnit;
    
    AutoArrowRemove autoArrowRemove( this, quiver, quiverData );

    const INT Limit = 10; // steph ajout de INT
    int i;    
    for( i = 0; i < Limit; i++ ){
        // Check if any unit lies between the attacker and the target.
        if( !wl->GetCollisionPos( thisPos, targetPos, &foundPos, &foundUnit ) ){
            foundUnit = target;
        }
        // If a unit was found.
        if( foundUnit != NULL ){
            // Do hit test with this unit.
            ATTACK_STRUCTURE blow;
            memset( &blow, 0, sizeof( ATTACK_STRUCTURE ) );

            GetArrowHitTest( blow, this, foundUnit, quiverData, weaponData );

            // If the blow hit the unit.
            if( blow.Precision > 0 || foundUnit->ViewFlag( __FLAG_STUN ) != 0 ){
                // Deal a minimum of 500ms move and attack exhaust
                DealExhaust( 500, 0, 1000 );

                // Deal arrow blow.
                DealArrowDamage( this, foundUnit, blow );
                return;
            }else{
                // If the missed unit is the target
                if( foundUnit == target ){
                    // Deal a minimum of 500ms move and attack exhaust
                    DealExhaust( 500, 0, 1000 );

                    // Make the arrow miss.
                    MakeArrowMiss( this, target->GetWL(), false );
                    return;
                }

                // Continue, using the found unit as the new position.
                thisPos = foundUnit->GetWL();
            }
        }else{
            // Deal a minimum of 500ms move and attack exhaust
            DealExhaust( 500, 0, 1000 );
            // Then deal the weapon's exhaust
            DealExhaust( weaponData->weapon.cDealtExhaust.GetBoost( this ), 0, 0 );
            
            Players *pl = reinterpret_cast< Players * >( GetPlayer() );
            if( pl->GetGodFlags() & GOD_DEVELOPPER ){
                SendSystemMessage( "Arrow hit something which is not a unit." );
            }
            // If the quiver doesn't have infinite ammo
            if( !quiverData->weapon.infiniteAmmo ){
                // Make auto-combat stop to avoid spending ammo.
                StopAutoCombat();
            }


            // Make the arrow miss
            MakeArrowMiss( this, foundPos, true );
            return;
        }
    }

    // The arrow tried too many times, make it miss.
    MakeArrowMiss( this, target->GetWL(), false );
}

//////////////////////////////////////////////////////////////////////////////////////////
DWORD Character::EquipCount
//////////////////////////////////////////////////////////////////////////////////////////
// Returns how many of the provided item is equipped by the character.
// 
(
 WORD itemId // The item to search for.
)
// Return: DWORD, How many items equipped at that position.
//////////////////////////////////////////////////////////////////////////////////////////
{
    int i;
    for( i = 0; i < EQUIP_POSITIONS; i++ ){
        if( equipped[ i ] == NULL ){
            continue;
        }
        if( equipped[ i ]->GetStaticReference() == itemId ){
            return static_cast< Objects * >( equipped[ i ] )->GetQty();
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::ClearAllSkillsAndSpells( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Clears all skills and spells and skill points and stat points.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	TemplateList <USER_SKILL> tlDeletedSkills;
	BOOL boFound;

    int i;

	for( i = 0; i < NB_SKILL_HOOKS; i++ ){
		tlusSkills[ i ].ToHead();
		// Pass all the skills in the hook
		while( tlusSkills[ i ].QueryNext() ){
			// Check if pointer has already been deleted
			boFound = FALSE;
			tlDeletedSkills.ToHead();
			while( tlDeletedSkills.QueryNext() && !boFound ){
				if( tlDeletedSkills.Object() == tlusSkills[ i ].Object() ){
					boFound = TRUE;
				}
			}

			// If user skill hasn't been deleted.
			if( !boFound ){				
				tlDeletedSkills.AddToTail( tlusSkills[ i ].Object() );
				tlusSkills[ i ].DeleteAbsolute();
			}
            
            tlusSkills[ i ].Remove();
		}
	}

	tlusSpells.ToHead();
	while( tlusSpells.QueryNext() ){
		tlusSpells.DeleteAbsolute();
	}



    // Just relearn archery at 15.
    wNbSkillPnts = 0xFFFF;
    CString errMsg;

    _LOG_DEBUG
        LOG_DEBUG_LVL1,
        "Character %s (ID %u) is being cleared of all its spells and skills. (remort?)",
        (LPCTSTR)GetName( _DEFAULT_LNG ),
        GetID()
    LOG_

    LPUSER_SKILL lpusUserSkill = LearnSkill( __SKILL_ARCHERY, 15, false, errMsg );
	// If skill could be trained.
	if( lpusUserSkill ){
		// cheat a little.. j/k, set skill points.
		lpusUserSkill->SetSkillPnts( 15 );
    }else{
        _LOG_DEBUG
            LOG_CRIT_ERRORS,
            "ClearAllSkillsAndSpells(remort): Character %s (ID %u) could NOT create skill Archery(%u)! ErrMsg=%s",
            (LPCTSTR)GetName( _DEFAULT_LNG ),
            GetID(),
            __SKILL_ARCHERY,
            (LPCTSTR)errMsg
        LOG_
    }

	wNbSkillPnts = 0;
	wNbStatPnts = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::BroadcastSeraphArrival( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Broadcast's the seraph arrival
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( seraphAlreadyArrived ){
        // Simply broadcast popup.
        BroadcastPopup( GetWL(), true );
        return;
    }

    TFCPacket sending;
    sending << (RQ_SIZE)RQ_SeraphArrival;
    PacketPopup( GetWL(), sending );
    PacketPuppetInfo( sending );

    seraphAlreadyArrived = true;
    
    Broadcast::BCast( GetWL(), _DEFAULT_RANGE, sending, GetInvisibleQuery() );
}

//////////////////////////////////////////////////////////////////////////////////////////
bool Character::CanInvite( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Determines if a player can be invited right now.
// 
// Return: bool, true if the player can be invited
//////////////////////////////////////////////////////////////////////////////////////////
{
    DWORD currentRound = TFCMAIN::GetRound();
    if( lastInviteTime < currentRound ){
        lastInviteTime = 30 SECONDS TDELAY;
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::RemoveReferenceTo
//////////////////////////////////////////////////////////////////////////////////////////
// Removes references pointing to theUnit
// 
(
 Unit *theUnit // The unit about to be deleted.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( prevTarget == theUnit ){
        prevTarget = NULL;
    }
    Unit::RemoveReferenceTo( theUnit );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::MoveObjectFromBackpackToChest2
//////////////////////////////////////////////////////////////////////////////////////////
// Move the object from backpack to the chest
// 
(
 DWORD dwObjectID, 
 DWORD dwQty 
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	if (boCharacterIsChesting == FALSE) {
		SendSystemMessage( _STR( 12916, GetLang() ) ); // You must click on a chest to use it
		StopUsingChest();
		return;
	}

	if (gameopContext != NULL) {
		// Editing other user chest is not allowed for gameops. Perhaps we could add it later?
		SendSystemMessage( _STR( 12952, wLang ) );
		return;
	}

	/* IMPORTANT NOTE:
	 *		This could have been put inside the while, after making sure the 
	 *		item is there and droppable, but calling a boostformula that countains
	 *		itemcount() will invalidate the current pointer inside of backpack
	 *		This got moved here to avoid that
	 */
	// If the server is configurated to recalculate the chest encumbrance in real time, update it
	if (theApp.dwChestEncumbranceUpdatedLive == 1) {
		BoostFormula bfChestEncumbrance;
		bfChestEncumbrance.SetFormula( theApp.csChestEncumbranceBoostFormula );
		chest->SetMaxWeight( bfChestEncumbrance.GetBoost(this) );
	}
	/* End of note */

	// If the chest has 0 max enc, its not allowed to put anything on it, even 0enc items like gold.
	if (chest->GetMaxWeight() == 0) {
		// No space left on chest
		SendSystemMessage( _STR( 12917, GetLang() ) );
		return;
	}

	Objects *droppedObj = NULL;
	backpack->Lock();
    backpack->ToHead();
	while( backpack->QueryNext() ){

		Objects *obj = static_cast<Objects*>(backpack->Object());

		if (obj->GetID() == dwObjectID) {

			_item *lpItem = NULL;
			obj->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItem );
			if( lpItem == NULL ){
				continue;
			} else if( lpItem->dwDropFlags & CANNOT_DROP_ITEM ){
				// This object cannot be dropped.
				SendSystemMessage( _STR( 7694, GetLang() ) );
				break;
			}

			if ( dwQty > obj->GetQty() ) dwQty = obj->GetQty();


			// Determine how many of this item can be carried by the user.
			DWORD maxQty;
			if ( obj->GetStaticReference() == (UINT)__OBJ_GOLD ) { // If the user is trying to chest gold..
				maxQty = GetGold(); // Do not allow it to chest more gold than it have
				obj->SetQty(maxQty); // and make sure the gold object he is using have the right amount as Qty
			} else if( obj->GetWeight() == 0 ){
				maxQty = 0xFFFFFFFF;
			}else{
				 maxQty = ( chest->GetFreeWeight() ) / obj->GetWeight();
			}
    
			// Impossible
			if( maxQty == 0 ){
				// No space left on chest
				SendSystemMessage( _STR( 12917, GetLang() ) );
				break;
			}
			
			if (dwQty > maxQty) {
				dwQty = maxQty;
			}

			bool forceQtyToOne = false;
			// If there are more than 1 item in the backpack
			if( obj->GetQty() > 1 ){
				// Create a copy of the backpack item
				droppedObj = new Objects();
				if( !droppedObj->Create( U_OBJECT, obj->GetStaticReference() ) ){
					droppedObj->DeleteUnit();
					continue;
				}
				// Set the quantity of items to the quantity of dropped items.
				droppedObj->SetQty( dwQty );
			}else{
				// Used the backpack item as the chest item.
				droppedObj = obj;
				// Add 1 qty count to avoid deleting the unit.
				forceQtyToOne = true;

				backpack->Remove();
			}

			// Remove the quantity of objects dropped from the backpack item.
        
			if( forceQtyToOne ){
				obj->SetQty( 1 );
			}else{
				obj->Remove( dwQty );
			}
			if( obj->GetQty() == 0 ){
				backpack->Remove();
				obj->DeleteUnit();
			}

			break;
		}
					
    }
	backpack->Unlock();

	if (droppedObj != NULL) {
		//Save name and ID to use on LOG
		CString csItemName = droppedObj->GetName(_DEFAULT_LNG);
		char szItemID[256];
		Unit::GetNameFromID( droppedObj->GetStaticReference(), szItemID, U_OBJECT );

		if( droppedObj->GetStaticReference() == (UINT)__OBJ_GOLD ){
			SetGold( GetGold() - droppedObj->GetQty(), false );
		}

		if ( !chest->Put(droppedObj) ) {
			if( droppedObj->GetStaticReference() == (UINT)__OBJ_GOLD ){
				SetGold( GetGold() + droppedObj->GetQty(), false );
			}
			AddToBackpack(droppedObj);
		} else {

			// Shoot a chest update!
			SendChestContentPacket();
			// Shoot a backpack update.
			TFCPacket sending;

			sending << (RQ_SIZE)RQ_ViewBackpack;
			sending << (char)0;	// Do not show content of backpack, only update it.
			sending << (long)GetID();
			PacketBackpack(sending);

			SendPlayerMessage( sending );

			_LOG_ITEMS
				LOG_MISC_1,
				"Player %s added %u item %s ID( %s ) to chest",
				GetTrueName().c_str(),
				dwQty,
				csItemName.c_str(),
				szItemID
			LOG_
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////
void Character::MoveObjectFromChestToBackpack2
//////////////////////////////////////////////////////////////////////////////////////////
// Move the object from backpack to the chest
// 
(
 DWORD dwObjectID, 
 DWORD dwQty 
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	if (boCharacterIsChesting == FALSE) {
		StopUsingChest();
		SendSystemMessage( _STR( 12916, GetLang() ) );
		return;
	}

	if (gameopContext != NULL) {
		// Editing other user chest is not allowed for gameops. Perhaps we could add it later?
		SendSystemMessage( _STR( 12952, wLang ) );
		return;
	}

	int iObjWeight=0;
	if ( chest->GetItemWeight(dwObjectID, iObjWeight) ) {


		// Determine how many of this item can be carried by the user.
		DWORD maxQty;
		if( iObjWeight == 0 ){
			maxQty = 0x7FFFFFFF;
		}else if (GetWeight() >= GetMaxWeight()) {
			maxQty = 0;
		} else {
			maxQty = ( GetMaxWeight() - GetWeight() ) / iObjWeight;
		}
    
		// Impossible
		if( maxQty == 0 ){
			SendSystemMessage( _STR( 17, wLang ) );
			return;
		}

		// If the item has more items than the user can carry.
		if( dwQty > maxQty ){
			dwQty = maxQty;
		}

		Objects *obj = chest->Take(dwObjectID, dwQty);
		if (obj != NULL) {

			CString csItemName = obj->GetName(_DEFAULT_LNG);
			char szItemID[256];
			Unit::GetNameFromID( obj->GetStaticReference(), szItemID, U_OBJECT );


			if( obj->GetStaticReference() == (UINT)__OBJ_GOLD ){
				SetGold( GetGold() + obj->GetQty(), false );
			} else { // Only call AddToBackpack if the object is not a gold pile
				AddToBackpack(obj);
			}

			// Shoot a chest update!
			SendChestContentPacket();
			// Shoot a backpack update.
			TFCPacket sending;

			sending << (RQ_SIZE)RQ_ViewBackpack;
			sending << (char)0;	// Do not show content of backpack, only update it.
			sending << (long)GetID();
			PacketBackpack(sending);

			SendPlayerMessage( sending );

			_LOG_ITEMS
				LOG_MISC_1,
				"Player %s removed %u item %s ID( %s ) from chest",
				GetTrueName().c_str(),
				dwQty,
				csItemName.c_str(),
				szItemID
			LOG_

		} else {
			SendSystemMessage( _STR( 12918, GetLang() ) );
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////
void Character::SendChestContentPacket
//////////////////////////////////////////////////////////////////////////////////////////
// Send a packet with chest contents.
// 
(
 void
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	TFCPacket packet;

	packet << (RQ_SIZE)RQ_ChestContents;
	if (gameopContext != NULL) {
		gameopContext->chest->GetPacket(packet);
	} else {
		chest->GetPacket(packet);
	}
	SendPlayerMessage(packet);
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::ShowChest (void)
//////////////////////////////////////////////////////////////////////////////////////////
// Makes client shows the chest
//////////////////////////////////////////////////////////////////////////////////////////
{

	boCharacterIsChesting = TRUE;

	//Update chest contents
	SendChestContentPacket();
	//Update backpack contents
	SendBackpackContentPacket();

	//Ask client to show the chest interface
	TFCPacket packet;
	packet << (RQ_SIZE)RQ_ShowChest;
	SendPlayerMessage(packet);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Character::StopUsingChest (void)
//////////////////////////////////////////////////////////////////////////////////////////
// Makes client hide the chest
//////////////////////////////////////////////////////////////////////////////////////////
{

	boCharacterIsChesting = FALSE;
	//Ask client to hide the chest interface
	TFCPacket packet;
	packet << (RQ_SIZE)RQ_HideChest;
	SendPlayerMessage(packet);
}

TradeMgr2* Character::GetTradeMgr2() {
	return &m_TradeMgr2;
}

void Character::TradeRequest(Character *invitedCharacter) {
	switch (m_TradeMgr2.Request(invitedCharacter->m_TradeMgr2)) {
	case TradeMgr2::ErrorCodes::InvalidParameters:
		{
			m_TradeMgr2.TradeSendInfoMessage(12919);
			//"You can't ask this character for a trade."
		} break;
	case TradeMgr2::ErrorCodes::NotCloseEnoughForTrade:
		{
			m_TradeMgr2.TradeSendInfoMessage(12920);
			//SendInfoMessage("You must come closer before trading.");
		} break;
	case TradeMgr2::ErrorCodes::InvitorIsTrading:
		{
			m_TradeMgr2.TradeSendInfoMessage(12921);
			//SendInfoMessage("You're in middle of a trade. Can't make any more request.");
		} break;
	case TradeMgr2::ErrorCodes::TargetIsTrading:
		{
			m_TradeMgr2.TradeSendInfoMessage(12923);
			//SendSystemMessage("This character is in middle of a trade!");
		} break;
	case TradeMgr2::ErrorCodes::InvitorIsAlreadyInvitingTarget:
		{
			m_TradeMgr2.TradeSendInfoMessage(12924);
			//SendSystemMessage("You have already requested this char for a trade!");
		} break;
	case TradeMgr2::ErrorCodes::InviteDone:
		{
		} break;
	case TradeMgr2::ErrorCodes::TradeStarted:
		{
		} break;
	default:
		{
			// Unexpected! Crash!
			_LOG_DEBUG
				LOG_CRIT_ERRORS,
				"Character::TradeRequest() unhandled ErrorCode. Crashing at line %i",
				__LINE__
			LOG_
			throw logic_error("Character::TradeRequest() unhandled ErrorCode.");
		}
	}
}
void Character::TradeCancel() {
	switch (m_TradeMgr2.Cancel()) {
	case TradeMgr2::ErrorCodes::NoTradeToCancel:
		{
			m_TradeMgr2.TradeSendInfoMessage(12927);
			//			SendSystemMessage("Trade invalid. Can't cancel.");
		} break;
	case TradeMgr2::ErrorCodes::InviteCancelled:
		{
			m_TradeMgr2.TradeSendInfoMessage(12928);
			//			SendSystemMessage("Request cancelled.");
		} break;
	case TradeMgr2::ErrorCodes::TradeCancelled:
		{
		} break;
	default:
		{
			// Unexpected! Crash!
			_LOG_DEBUG
				LOG_CRIT_ERRORS,
				"Character::TradeCancel() unhandled ErrorCode. Crashing at line %i",
				__LINE__
			LOG_
			throw logic_error("Character::TradeCancel() unhandled ErrorCode.");
		}
	}
}
void Character::TradeFinish() {
	switch (m_TradeMgr2.Finish()) {
	case TradeMgr2::ErrorCodes::NoTradeToFinish:
		{
			m_TradeMgr2.TradeSendInfoMessage(12930);
//			SendSystemMessage("Trade invalid. Can't finish.");
		} break;
	case TradeMgr2::ErrorCodes::CantFinishAnInvite:
		{
			m_TradeMgr2.TradeSendInfoMessage(12931);
			//			SendSystemMessage("Cant finish a request. Operation only valid for running trades.");
		} break;
	case TradeMgr2::ErrorCodes::CantFinishImproperCharacterStatus:
		{
			m_TradeMgr2.TradeSendInfoMessage(12932);
			//			SendSystemMessage("Characters status invalid for finishing");
		} break;
	case TradeMgr2::ErrorCodes::TradeFinished:
		{
		} break;
	default:
		{
			// Unexpected! Crash!
			_LOG_DEBUG
				LOG_CRIT_ERRORS,
				"Character::TradeFinish() unhandled ErrorCode. Crashing at line %i",
				__LINE__
			LOG_
			throw logic_error("Character::TradeFinish() unhandled ErrorCode.");
		}
	}
}
void Character::TradeSetStatus(TradeMgr2::Status::CharacterStatus newStatus) {
	switch(m_TradeMgr2.SetCharacterStatus(newStatus)) {
	case TradeMgr2::ErrorCodes::NoTradeToSetCharacterStatus:
		{
			m_TradeMgr2.TradeSendInfoMessage(12934);
			//			SendSystemMessage("Trade invalid. Can't set status.");
		} break;
	case TradeMgr2::ErrorCodes::CharacterStatusInvalid:
		{
			m_TradeMgr2.TradeSendInfoMessage(12935);
			//			SendSystemMessage("Invalid status.");
		} break;
	case TradeMgr2::ErrorCodes::CharacterStatusSet:
		{
			//m_TradeMgr2.TradeSendInfoMessage();
			//			SendSystemMessage("Status set.");
		} break;
	case TradeMgr2::ErrorCodes::CharacterStatusSetAndTradeFinished:
		{
//			m_TradeMgr2.TradeSendInfoMessage(12933);
			//			SendSystemMessage("Trade finished.");
		} break;
	default:
		{
			// Unexpected! Crash!
			_LOG_DEBUG
				LOG_CRIT_ERRORS,
				"Character::TradeSetStatus() unhandled ErrorCode. Crashing at line %i",
				__LINE__
			LOG_
			throw logic_error("Character::TradeSetStatus() unhandled ErrorCode.");
		}
	}
}
void Character::TradeAddItemFromBackpack(DWORD itemID, DWORD itemQty) {

	CAutoLock __autolock(backpack); // Lock the backpack
	CAutoLock __autolock2(m_TradeMgr2.GetCLock()); // Lock the TradeMgr

	// Is this trade valid for adding item?
	if (m_TradeMgr2.IsTradeValid() != TradeMgr2::ErrorCodes::IsTrading) {
		// If not, drop a message and return.
		m_TradeMgr2.TradeSendInfoMessage(12936);
		//		SendSystemMessage("Invalid Trade. Can't add item.");
		return;
	}
	
	//If yes, continue and try to add the item for trade.

	BOOL objFoundOnBackpack = FALSE;
	Objects *droppedObj = NULL;
    backpack->ToHead();
	while( backpack->QueryNext() ){

		Objects *obj = static_cast<Objects*>(backpack->Object());

		if (obj->GetID() == itemID) {

			objFoundOnBackpack = TRUE;

			_item *lpItem = NULL;
			obj->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItem );
			if( lpItem == NULL ){
				continue;
			} else if( lpItem->dwDropFlags & CANNOT_DROP_ITEM ){
				// This object cannot be dropped.
				SendSystemMessage( _STR( 7694, GetLang() ) );
				break;
			}

			if ( itemQty > obj->GetQty() ) itemQty = obj->GetQty();

			// Determine how many of this item can be carried by the user.
			DWORD maxQty;
			if ( obj->GetStaticReference() == (UINT)__OBJ_GOLD ) { // If the user is trying to trade gold..
				maxQty = GetGold(); // Do not allow it to trade more gold than it have
				obj->SetQty(maxQty); // and make sure the gold object he is using have the right amount as Qty
			} else if( obj->GetWeight() == 0 ){
				maxQty = 0xFFFFFFFF;
			}else{
				maxQty = ( m_TradeMgr2.GetFreeWeight() ) / obj->GetWeight();
			}
    
			// Impossible
			if( maxQty == 0 ){
				// No space left on trade
// NEEDS A MESSAGE HERE!
				m_TradeMgr2.TradeSendInfoMessage(12937);
				//SendSystemMessage( _STR( 12917, GetLang() ) );
				break;
			}
			
			if (itemQty > maxQty) {
				itemQty = maxQty;
			}

			bool forceQtyToOne = false;
			// If there are more than 1 item in the backpack
			if( obj->GetQty() > 1 ){
				// Create a copy of the backpack item
				droppedObj = new Objects();
				if( !droppedObj->Create( U_OBJECT, obj->GetStaticReference() ) ){
					droppedObj->DeleteUnit();
					continue;
				}
				// Set the quantity of items to the quantity of dropped items.
				droppedObj->SetQty( itemQty );
			}else{
				// Used the backpack item as the chest item.
				droppedObj = obj;
				// Add 1 qty count to avoid deleting the unit.
				forceQtyToOne = true;

				backpack->Remove();
			}

			// Remove the quantity of objects dropped from the backpack item.
        
			if( forceQtyToOne ){
				obj->SetQty( 1 );
			}else{
				obj->Remove( itemQty );
			}
			if( obj->GetQty() == 0 ){
				backpack->Remove();
				obj->DeleteUnit();
			}

			break;
		}
					
    }

	if (droppedObj != NULL) { // There the refered item was found and taken from backpack!

		if( droppedObj->GetStaticReference() == (UINT)__OBJ_GOLD ){
			SetGold( GetGold() - droppedObj->GetQty(), false );
		}

		switch (m_TradeMgr2.AddItemToTrade(droppedObj)) {
		case TradeMgr2::ErrorCodes::ItemAdded:
			{
			} break;
		case TradeMgr2::ErrorCodes::ItemCantBeAdded:
			{
				if( droppedObj->GetStaticReference() == (UINT)__OBJ_GOLD ){
					SetGold( GetGold() + droppedObj->GetQty(), false );
				}
				AddToBackpack(droppedObj);
				m_TradeMgr2.TradeSendInfoMessage(12942);
//								SendSystemMessage("Item nao pode ser adicionado");
			} break;
		case TradeMgr2::ErrorCodes::TradeInvalidForItemAdding:
			{
				m_TradeMgr2.TradeSendInfoMessage(12936);
				//				SendSystemMessage("Trade invalido. Impossivel adicionar item.");
			} break;
		default:
			{
				// Unexpected! Crash!
				_LOG_DEBUG
					LOG_CRIT_ERRORS,
					"Character::TradeAddItemFromBackpack() unhandled ErrorCode. Crashing at line %i",
					__LINE__
				LOG_
				throw logic_error("Character::TradeAddItemFromBackpack() unhandled ErrorCode.");
			}
		}
	} else if( objFoundOnBackpack == FALSE ) { // No such item was found on backpack!
		m_TradeMgr2.TradeSendInfoMessage(12943);
		SendBackpackContentPacket();
		//		SendSystemMessage("Item not found!");
	}

}
void Character::TradeRemoveItemToBackpack(DWORD itemID, DWORD itemQty) {
	Objects *removedObj = NULL;
	switch (m_TradeMgr2.RemoveItemFromTrade(itemID, itemQty, removedObj)) {
	case TradeMgr2::ErrorCodes::ItemRemoved:
		{
			if (removedObj->GetStaticReference() == (UINT)__OBJ_GOLD) {
				SetGold( GetGold() + removedObj->GetQty(), false );
			} else {
				AddToBackpack(removedObj);
			}
			SendBackpackContentPacket();
			//			SendSystemMessage("Item removed");
		} break;
	case TradeMgr2::ErrorCodes::ItemCantBeRemoved:
		{
			m_TradeMgr2.TradeSendInfoMessage(12944);
			//			SendSystemMessage("Can't remove item!");
		} break;
	case TradeMgr2::ErrorCodes::TradeInvalidForItemRemoving:
		{
			m_TradeMgr2.TradeSendInfoMessage(12945);
			//			SendSystemMessage("Trade invalid. Can't remove item.");
		} break;
	default:
		{
			// Unexpected! Crash!
			_LOG_DEBUG
				LOG_CRIT_ERRORS,
				"Character::TradeRemoveItemToBackpack() unhandled ErrorCode. Crashing at line %i",
				__LINE__
			LOG_
			throw logic_error("Character::TradeRemoveItemToBackpack() unhandled ErrorCode.");
		}
	}
}

void Character::TradeClearItemsFromTrade()
{
	switch (m_TradeMgr2.ClearItemsFromTrade()) {
	case TradeMgr2::ErrorCodes::NoTradeToClear:
		{
			m_TradeMgr2.TradeSendInfoMessage(12946);
			//			SendSystemMessage("Trade invalid. Can't clear.");
		} break;
	case TradeMgr2::ErrorCodes::TradeCleared:
		{
			m_TradeMgr2.TradeSendInfoMessage(12947);
			//			SendSystemMessage("Trade cleared.");
		} break;
	default:
		{
			// Unexpected! Crash!
			_LOG_DEBUG
				LOG_CRIT_ERRORS,
				"Character::TradeClearItemsFromTrade() unhandled ErrorCode. Crashing at line %i",
				__LINE__
			LOG_
			throw logic_error("Character::TradeClearItemsFromTrade() unhandled ErrorCode.");
		}
	}
}

Character::ErrorCodes::TakeFromBackpack Character::TakeFromBackpack( DWORD itemID, DWORD itemQty, Objects *returnedObj, BOOL ignoreCannotDropFlag ) {
    DWORD qtySave = itemQty;

	CAutoLock __autoLock(backpack);
    backpack->ToHead();
	while( backpack->QueryNext() ){
		Objects *obj = static_cast< Objects * >( backpack->Object() );

		if( obj->GetID() != itemID ) { continue; }

        // If user does not have any gold and wants to drop a gold stack.
        if( obj->GetStaticReference() == (UINT)__OBJ_GOLD && GetGold() == 0 ) { break; }

        itemQty = qtySave;

        // If the quantity is bigger than the total quantity.
		if (obj->GetStaticReference() == (UINT)__OBJ_GOLD && GetGold() < itemQty) {
			itemQty = GetGold();
		} else if( obj->GetQty() < itemQty ) {
            // Adjust it.
            itemQty = obj->GetQty();
        }

        _item *lpItem = NULL;
        obj->SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItem );
        if( lpItem == NULL ){
            continue;
        }

        // Can it be dropped? :)
		if (ignoreCannotDropFlag == FALSE) {
			if( lpItem->dwDropFlags & CANNOT_DROP_ITEM ){
				// This object cannot be dropped.
				return ErrorCodes::ObjectCantBeDropped;
			}
		}

        bool forceQtyToOne = false;
        Objects *droppedObj;
        // If there are more than 1 item in the backpack
        if( obj->GetQty() > 1 ){
            // Create a copy of the backpack item
            droppedObj = new Objects();
            if( !droppedObj->Create( U_OBJECT, obj->GetStaticReference() ) ){
                droppedObj->DeleteUnit();
                continue;
            }
            // Set the quantity of items to the quantity of dropped items.
            droppedObj->SetQty( itemQty );
        }else{
            // Used the backpack item as the dropped item.
            droppedObj = obj;
            // Add 1 qty count to avoid deleting the unit.
            forceQtyToOne = true;

            backpack->Remove();
        }

        bool updateGold = false;
        DWORD goldUpdate = 0;
        // If this is a gold stack.
        if( obj->GetStaticReference() == (UINT)__OBJ_GOLD ){
            // Gets its gold value.
            if( itemQty < GetGold() ){
                // Remove gold directly from player.
                goldUpdate = GetGold() - itemQty;
            }

            updateGold = true;
        }

        // Remove the quantity of objects dropped from the backpack item.
        
        if( forceQtyToOne ){
            obj->SetQty( 1 );
        }else{
            obj->Remove( itemQty );
        }
        if( obj->GetQty() == 0 ){
            backpack->Remove();
            obj->DeleteUnit();
        }
//        backpack->Unlock();

        if( updateGold ){
            // Reset the gold amount (after the backpack was released).
            SetGold( goldUpdate );
        }
		returnedObj = droppedObj;
		return ErrorCodes::ObjectTakenFromBackpack;
    }
//    backpack->Unlock();
	return ErrorCodes::ObjectNotFoundOnBackpack;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Character::SendBackpackContentPacket()
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Shoot a backpack update.
	TFCPacket sending;

	sending << (RQ_SIZE)RQ_ViewBackpack;
	sending << (char)0;	// Do not show content of backpack, only update it.
	sending << (long)GetID();
	PacketBackpack(sending);
	SendPlayerMessage( sending );
}

//////////////////////////////////////////////////////////////////////////////////////////
unsigned int Character::GetGodFlags( void ) // __int64
//////////////////////////////////////////////////////////////////////////////////////////
{
	Players *user = (Players *)ThisPlayer;
    if( user != NULL ) return user->GetGodFlags();
	return 0;
}

/* BEGIN : Remove BL Anti SpeedHack
void Character::CheckSpeedHack( WorldPos newPos )
{
	// If the player just logged in
	if( !initTime )
	{
		initTime = TFCMAIN::GetRound();
		initPos  = newPos;
	}
	// if the player has been teleported
	else if( abs(prevPos.X-newPos.X) > 1 || abs(prevPos.Y-newPos.Y) > 1 || prevPos.world != newPos.world )
	{
		if( this->GetGodFlags() & GOD_DEVELOPPER )
		{
			CString csMessage;
			csMessage.Format( "TP detected (%d,%d,%d)->(%d,%d,%d)", prevPos.X, prevPos.Y, prevPos.world, newPos.X, newPos.Y, newPos.world );
			this->SendSystemMessage( csMessage );
		}

		initTime = TFCMAIN::GetRound();
		initPos = newPos;
	}
	// time elapsed, verify how far the player ran
	else if( (initTime + 1 SECONDS) <= TFCMAIN::GetRound() )
	{
		int x = abs( initPos.X - newPos.X );
		int y = abs( initPos.Y - newPos.Y );

		if( (x > 5 || y > 5) || (x >= 5 && y >= 5) )  //BLBLBLBL modif de 6 à 5 (test)
		{
			/*_LOG_PC
				LOG_WARNING,
				"Player %s (Account %s) moved a little to fast (SpeedHack?). (x = %d / y = %d)",
				this->GetTrueName(),
				this->GetPlayer()->GetFullAccountName(),
				x, y
			LOG_*/

			// Then increaste exhaust time 
/*
			exhaust.move += 100 MILLISECONDS;

			if( this->GetGodFlags() & GOD_DEVELOPPER )
			{
				CString csMessage;
				csMessage.Format( "You walked too fastly. Exhaust time penalty." );
				this->SendSystemMessage( csMessage );
			}	
		}					

		initTime = TFCMAIN::GetRound();
		initPos = newPos;
	}

	prevPos = newPos;
}
END : Remove BL Anti SpeedHack */

bool Character::AnalyseActionWorld(char *pTxt)
{
   for(int i=0;i<theApp.m_aSpellWorld.size();i++)
   {
      if(CMP(pTxt,theApp.m_aSpellWorld[i].strText.GetBuffer(0)) == 0)
      {
         // le texte fait partie de la liste...
//         if(ViewFlag(theApp.m_aSpellWorld[i].uiFlagID)==1 || ViewFlag(__FLAG_TEST_WORLD_SPELL) == 1)
         {
            //la personne peu lancer ce sort... ou peu lancer tous les sorts
            //CastSpellNoCheck((WORD)theApp.m_aSpellWorld[i].uiSpellID,this);
         }
         return true;
      }
   }
   return false;
}
