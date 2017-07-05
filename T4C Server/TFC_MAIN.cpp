// TFC_MAIN.cpp: implementation of the TFC_MAIN class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "TFC_MAIN.h"
#include "TFC ServerDlg.h"
#include "TFCPacket.h"
//#include "StaticObjects.h"
#include "SharedStructures.h"
#include "Broadcast.h"
#include "Directions.h"
//#include "TFC Messages\svrmsg.h"
#include "Creatures.h"
#include "Attack.h"
#include "ObjectFlagsListing.h"
#include "TFCException.h"
#include "TFCServerGP.h"
#include "TFCTimers.h"
#include "TFCTime.h"
#include "Random.h"
#include <eh.h>
#include <process.h>
//#include "UsersDB.H"
#include "Skills.h"
#include "ODBCMage.h"
#include "BlockingListing.h"
#include "RegKeyHandler.h"
#include "IntlText.h"
#include "AutoConfig.h"
#include "format.h"
#include "ThreadMonitor.h"
//BLBLBLB
#include "WeatherEffect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

LONG __stdcall DefaultExcpFilter( LPEXCEPTION_POINTERS lp );

extern CTFCServerApp theApp;
extern CTFCServerDlg *MainDlg;
extern TemplateList <Players> SocketPlayerList;

//TemplateList <Players> UsersList; // Auxiliary users list
TemplateList <Unit> UnitsToCreate;
extern TemplateList< Unit> AddCreatureList;

TFC_MAIN* TFCServer;

void FetchExceptionFunction(unsigned int u, EXCEPTION_POINTERS* pExp){
	TFCException *excp = new TFCException;
	excp->SetException(pExp);
	throw excp;
}
// Variables for personnal mailing //////////////////////////////////////////////////////////
Random rnd;

WorldMap *TFCMAIN::GetWorld(unsigned short which)
{
	if(which < TFCServer->world_number) return &TFCServer->World[which];
	else return NULL;
}

CString TFCMAIN::GetHomeDir()
{	return theApp.sPaths.csBinaryPath;}

/////////////////////////////////////////////////////////////////////////////////////////////
DWORD TFCMAIN::GetColosseum()
{	return theApp.sColosseum;}

DWORD TFCMAIN::GetDoppelganger()
{	return theApp.sDoppelganger;}

DWORD TFCMAIN::GetBattleMode()
{	return theApp.sBattleMode;}

DWORD TFCMAIN::GetMaxRemorts()
{	return theApp.sMaxRemorts;}

DWORD TFCMAIN::GetMaxCharactersPerAccount()
{	return theApp.sMaxCharactersPerAccount;}

//BATLLE MODE CFG//
DWORD TFCMAIN::GetXptm1killtm2()
{	return theApp.sxptm1killtm2;}

DWORD TFCMAIN::GetGoldtm1killtm2()
{	return theApp.sgoldtm1killtm2;}

DWORD TFCMAIN::GetKarmatm1killtm2()
{	return theApp.skarmatm1killtm2;}

DWORD TFCMAIN::GetXptm2killtm1()
{	return theApp.sxptm2killtm1;}

DWORD TFCMAIN::GetGoldtm2killtm1()
{	return theApp.sgoldtm2killtm1;}

DWORD TFCMAIN::GetKarmatm2killtm1()
{	return theApp.skarmatm2killtm1;}

DWORD TFCMAIN::GetXplostsameteam()
{	return theApp.sxplostsameteam;}

DWORD TFCMAIN::GetGoldlostsameteam()
{	return theApp.sgoldlostsameteam;}

DWORD TFCMAIN::GetKarmagaintk()
{	return theApp.skarmagaintk;}

DWORD TFCMAIN::GetKarmalosttk()
{	return theApp.skarmalosttk;}

DWORD TFCMAIN::GetBonuskill1()
{	return theApp.sbonuskill1;}

DWORD TFCMAIN::GetBonuskill2()
{	return theApp.sbonuskill2;}

DWORD TFCMAIN::GetBonuskill3()
{	return theApp.sbonuskill3;}

DWORD TFCMAIN::GetXpbonus1()
{	return theApp.sxpbonus1;}

DWORD TFCMAIN::GetXpbonus2()
{	return theApp.sxpbonus2;}

DWORD TFCMAIN::GetXpbonus3()
{	return theApp.sxpbonus3;}

DWORD TFCMAIN::GetGoldbonus1()
{	return theApp.sgoldbonus1;}

DWORD TFCMAIN::GetGoldbonus2()
{	return theApp.sgoldbonus2;}

DWORD TFCMAIN::GetGoldbonus3()
{	return theApp.sgoldbonus3;}


/////////////////////////////////////////////////////////////////////////////////////////////
// Adds a monster for auto-life
void TFCMAIN::AddMonster(Unit *theCreature){
	AddCreatureList.Lock();
	AddCreatureList.AddToHead(theCreature);
	AddCreatureList.Unlock();

	theCreature->BroadcastPopup( theCreature->GetWL() );

	theCreature->SendUnitMessage( MSG_OnPopup, theCreature, NULL, NULL,
								   NULL, NULL );
}
/*
void TFCMAIN::Broadcast(WorldPos where, unsigned char range, TFCPacket &sending){
	Broadcast::BCast(where, range, sending);

}
void TFCMAIN::Broadcast(unsigned int event, WorldPos where, unsigned char range, unsigned int *param){
	Broadcast::BCast(event, where, range, param);
}*/

WORD TFCMAIN::GetMaxWorlds(){
	return TFCServer->world_number;
}

TemplateList <TFCMAIN::_FUNC> TFCMAIN::tlFuncList;

void TFCMAIN::RegisterUnitStartupFunction( UNITSTARTUPFUNC lpFunc ){
	_FUNC *sFunc = new _FUNC;
	sFunc->lpFunc = lpFunc;
	tlFuncList.AddToTail( sFunc );
}

void TFCMAIN::CallUnitStartupFunctions( void ){
	_FUNC *sFunc;
	tlFuncList.ToHead();
	while( tlFuncList.QueryNext() ){
		sFunc = tlFuncList.Object();
		sFunc->lpFunc();
		tlFuncList.DeleteAbsolute();
	}
}

static HANDLE hHeartHandle = NULL;

static DWORD  _round = 0;

////////////////////////////////////////////

//////////////////////////////////////////////
UINT CALLBACK HeartBeat
//////////////////////////////////////////////////////////////////////////////////////////
// This thread ticks the rounds each 50ms
// 
(
 LPVOID nil
)
// Return: static void, 
//////////////////////////////////////////////////////////////////////////////////////////
{
	CAutoThreadMonitor tmMonitor("HeartBeat");
    DWORD initialTime = GetRunTime();
	DWORD dummyRound = 0;
	DWORD currentTime = 0;

    while( 1 ){
        // Heartbeats each 50ms
        Sleep( 50 );
        
        // Do incrementation in unsigned
        //DWORD 
		dummyRound = ::_round;
        dummyRound++;

        // Each 20 rounds (1 second)
        if( ( dummyRound % 20 ) == 0 ){
            //DWORD 
			currentTime = GetRunTime();
			
            // If GetRunTime() looped
            if( currentTime < initialTime ){
                // Reset the initial time.
                initialTime = currentTime;
            }else{
                // Rectify the current round according to the actual
                // elapsed time. Accounts for the time lost processing
                // the heartbeat.
                dummyRound = ( currentTime - initialTime ) / 50;
            }
        }


        // Set new round to this value
        /*InterlockedExchange( 
            reinterpret_cast< long * >( &round ), 
            static_cast< long >( dummyRound ) 
        );*/
		::_round = dummyRound;//BLBL as told by Chaotik.

              /*      _LOG_DEBUG
                        LOG_DEBUG_LVL1,
                        "NEW ROUND VALUE %i.",
                        round
                    LOG_*/

        
        // Increment clock
        TFCTime::IncTime();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void TFCMAIN::StartBeat( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Starts the heartbeat.
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( hHeartHandle == NULL ){
        UINT threadId;
        hHeartHandle = (HANDLE)_beginthreadex(
            NULL, 0, HeartBeat, NULL, 0, &threadId );

        // Set above priority to heartbeat increments.
        SetThreadPriority( hHeartHandle, THREAD_PRIORITY_HIGHEST );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
unsigned long TFCMAIN::GetRound( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Returns the current round
// 
// Return: unsigned long, 
//////////////////////////////////////////////////////////////////////////////////////////
{
	return ::_round;
}


////////////////////////////////////////////////////////////////////////////////////////////
// For attacking
int TFCMAIN::Attack(Unit *Attacker, Unit *Target, bool &blockedPath )
{
    blockedPath = false;
    MultiLock( Attacker, Target );
    
	WorldPos wlAttPos = Attacker->GetWL();	
	WorldPos wlTarPos = Target->GetWL();

	WorldMap *wlWorld = GetWorld( wlAttPos.world );
	BOOL boAttack = TRUE;


    // If a collision is detected.
    WorldPos blockPos = { 0, 0, 0 };
    Unit *collideUnit = NULL;
    if( wlWorld->GetCollisionPos( wlAttPos, wlTarPos, &blockPos, &collideUnit ) ){
        
		// If the target unit isn't the target and the block pos isn't the target pos.
        if( collideUnit != Target && 
            ( blockPos.X != wlTarPos.X || blockPos.Y != wlTarPos.Y ) ){
            if( Attacker->GetType() == U_NPC ){
                Attacker->SetTarget( NULL );
                Attacker->Do( wandering );
            }
            blockedPath = true;
            Attacker->Unlock();
            Target->Unlock();
            return 0;
        }
    }


	if( Target != Attacker && Target->GetType() != U_OBJECT && Target->GetType() != U_HIVE && boAttack ){

		if( wlWorld != NULL ){
			// If any of them is in a safe-haven.
			if( 
                (   // If either the attacker or the attacked is on a safe-haven
                    Attacker->GetUnderBlock() == __SAFE_HAVEN 
                        || 
                    Attacker->GetUnderBlock() == __INDOOR_SAFE_HAVEN 
                        ||
                    Attacker->GetUnderBlock() == __BLOCK_ABSOLUTE//BLBLBL : ajouté test pour éviter que des tricheurs ayant réussi à être sur une case bloquante puisse tuer d'autres joueurs.
                        ||
                    Attacker->GetUnderBlock() == __BLOCK_CAN_FLY_OVER//BLBLBL : ajouté test pour éviter que des tricheurs ayant réussi à être sur une case bloquante puisse tuer d'autres joueurs.
                        ||
                    Attacker->GetUnderBlock() == __BLOCK_DEEP_WATER//BLBLBL : ajouté test pour éviter que des tricheurs ayant réussi à être sur une case bloquante puisse tuer d'autres joueurs.
                        ||
                    Attacker->GetUnderBlock() == __BLOCK_SHALLOW_WATER//BLBLBL : ajouté test pour éviter que des tricheurs ayant réussi à être sur une case bloquante puisse tuer d'autres joueurs.
                        ||
				    Target->GetUnderBlock() == __SAFE_HAVEN
                        ||
                    Target->GetUnderBlock() == __INDOOR_SAFE_HAVEN 
                        ||
                    Target->GetUnderBlock() == __BLOCK_ABSOLUTE//BLBLBL : ajouté test pour éviter que des tricheurs ayant réussi à être sur une case bloquante puisse tuer d'autres joueurs.
                        ||
                    Target->GetUnderBlock() == __BLOCK_CAN_FLY_OVER//BLBLBL : ajouté test pour éviter que des tricheurs ayant réussi à être sur une case bloquante puisse tuer d'autres joueurs.
                        ||
                    Target->GetUnderBlock() == __BLOCK_DEEP_WATER//BLBLBL : ajouté test pour éviter que des tricheurs ayant réussi à être sur une case bloquante puisse tuer d'autres joueurs.
                        ||
                    Target->GetUnderBlock() == __BLOCK_SHALLOW_WATER//BLBLBL : ajouté test pour éviter que des tricheurs ayant réussi à être sur une case bloquante puisse tuer d'autres joueurs.
                )
                    && 
                (   // If both the attacker and target are players.
                    Attacker->GetType() == U_PC 
                        && 
                    Target->GetType() == U_PC 
                )
            ){
                if( Attacker->GetType() == U_PC ){
                    static_cast< Character * >( Attacker )->StopAutoCombat();
                }

                TFCPacket sending;
                sending << (RQ_SIZE)RQ_ServerMessage;
                sending << (short)30;
                sending << (short)3;
                CString csText = _STR( 22, Attacker->GetLang() );
                sending << (CString &)csText;
				sending << (long)0x000A64E0/* RGB( 0, 100, 255 )*/;
                Attacker->SendPlayerMessage( sending );
				// Do not attack
				boAttack = FALSE;
			}
		}
		
		//		Attacker->Lock();
//		Target->Lock();
		// If player/unit isn't stun and in attack range            
		if( !Attacker->ViewFlag( __FLAG_STUN ) && boAttack &&
			abs( wlAttPos.X - wlTarPos.X ) <= _DEFAULT_TOUCH_RANGE &&
			abs( wlAttPos.Y - wlTarPos.Y ) <= _DEFAULT_TOUCH_RANGE 
		){
        /*    CString csText;
            CString csTwo;
            if( Attacker->GetType() == U_PC ){
                csText.Format( "Player %s attacks ", Attacker->GetName() );
            }else{
                csText.Format( "Monster %s attacks ", Attacker->GetName() );
            }

            if( Target->GetType() == U_PC ){
                csTwo.Format( "player %s.", Target->GetName() );
            }else{
                csTwo.Format( "monster %s.", Target->GetName() );
            }
            csText += csTwo;
            
            _LOG
                LOG_DEBUG_LVL1,
                (char *)(LPCTSTR)csText
            LOG_*/

              			
			int attackID; // which attack was cast
			int dodgeID;  // what was dodge
			int result;	  // result of the attack (death?)
			DWORD DodgeSkill, AttackSkill;
			
            ATTACK_STRUCTURE Blow;
            memset( &Blow, 0, sizeof( ATTACK_STRUCTURE ) );
			
			/*Unit *NewTarget = Target->GetTarget();
			// If target doesn't have a target
			if( NewTarget == NULL ){
				// Change the target's target to face the attacker
				Target->SetTarget( Attacker );
				if( Target->CanAttack() ){
					Target->Do( fighting );					
				}else{
					Target->Do( flee );
				}
			};*/

			// Get the attack first, since we determine the attack skill at runtime 
			// (monster may have multiple attacks with multiple attack skills)
			Blow.lDodgeSkill = Target->GetDODGE();
			Blow.lDodgeSkill = Blow.lDodgeSkill > 0 ? Blow.lDodgeSkill : 1;

			DodgeSkill = Blow.lDodgeSkill;

			attackID = Attacker->attack(&Blow, Target );
            Blow.TrueStrike = Blow.Strike;    // Set true strike.
			
            double dblPreACstrike = Blow.Strike;

//			DodgeSkill = Target->ViewFlag(__FLAG_DODGE_SKILL);
//			DodgeSkill = DodgeSkill > 0 ? DodgeSkill : 1;

			AttackSkill	= Attacker->GetATTACK();
			TRACE(_T("AttackSkill %d"), AttackSkill);
			AttackSkill = AttackSkill > 0 ? AttackSkill : 1;
			// If attack skill wasn't set by the 'attack' function
			if(!Blow.lAttackSkill){
				Blow.lAttackSkill = AttackSkill;
			}

			//TRACE(_T("\r\nAttackSkill %u vs DodgeSkill %u (exhaust %u, %u)\r\n"), AttackSkill, DodgeSkill, Blow.exhaust.attack, Blow.exhaust.move);

			TRACE( _T("\r\nAttackerPos( %u, %u ) vs DefenderPos( %u, %u )\r\n"),
				Attacker->GetWL().X, Attacker->GetWL().Y, Target->GetWL().X, Target->GetWL().Y );
			TRACE( _T("\r\nThe attacker is %s and the target %s\r\n"),
				Attacker->GetName( _DEFAULT_LNG ), Target->GetName( _DEFAULT_LNG ) );


//                Attacker->DealExhaust( Blow.exhaust.attack, Blow.exhaust.mental, Blow.exhaust.move );

			// If precision wasn't set by one of the called functions..
			if(!Blow.Precision){
				Blow.Precision = GAME_RULES::GetBlowPrecision(AttackSkill, DodgeSkill, Attacker->GetAGI(), Target->GetAGI() );
			}

			// If target can attack
			if( Target->CanAttack() ){
                if( Target->GetType() == U_NPC ){
				    // Force unit into fight
				    Target->Do( fighting );
				    Target->SetTarget( Attacker );
                }
			}

			if(Blow.Precision > 0 || Target->ViewFlag(__FLAG_STUN)) {

                // If attack is previously hidden.
                if( Attacker->ViewFlag( __FLAG_HIDDEN ) ){
                    // Hit more!!! Mouahahahahha
                    Blow.Strike = Blow.Strike * ( 149 + rnd.roll( dice( 1, 50 ) ) ) / 100;
                }


                // Dispell any invisibility on the attack.
                Attacker->DispellInvisibility();

				// Got hit, so cannot be stun anymore
				if( Target->ViewFlag( __FLAG_STUN ) ){
					// Hit more!!! MouAHaHahAHahahAHa
					Blow.Strike *= 15; // * 1.5, in integers..
					Blow.Strike /= 10;

					// Removes the stun timer possibily associated with it					
					Target->RemoveFlag(__FLAG_STUN);
				}
				
				// If attacker is berserk
				int nBerserk = Attacker->ViewFlag( __FLAG_BERSERK );
				if( nBerserk > 0 ){
					// Hit more!!! mouhahaHAhahaha
					double dblDam = Blow.Strike * 2;
					Blow.Strike *= ( ( nBerserk / 25 ) + 1 );
					Blow.Strike += dblDam;
				}

				// Attack hit! This time, query without a target to enable "skill" checking
				Attacker->attack_hit(&Blow, Target);

    			// Target is move-frozen for 500 ms.
				Target->DealExhaust( 0, 0, 500 );
				// analyse, I don't care
			
				dodgeID = Target->attacked(&Blow, Attacker);
				//AfxMessageBox("8\r\n");
				TRACE(_T("Attack of %d(defense)!!"), Blow.Strike);
				//AfxMessageBox("9\r\n");
			
				if(Blow.Strike < 0){
					Blow.Strike = 0;
				}

				double dblPostACstrike = Blow.Strike; // Save POST-AC strike value
				
				// Proccess triggered skills and god flags and get final damage value.
				result = Target->hit(&Blow, Attacker);

                if( Attacker->GetType() == U_PC ){
                    Players *lpPlayer = static_cast< Character *>( Attacker )->GetPlayer();
                    if( lpPlayer != NULL ){
                        if( lpPlayer->GetGodFlags() & GOD_DEVELOPPER ){
                            TFormat format;
                            Attacker->SendSystemMessage(
                                format(
                                    "Attack hits %s for %.2f damages (%.2f post-AC damages, %.2f final damage).",
                                    (LPCTSTR)Target->GetName(_DEFAULT_LNG),
                                    dblPreACstrike,
									dblPostACstrike,
                                    Blow.Strike
                                )
                            );
                        }
                    }
                }
                if( Target->GetType() == U_PC ){
                    Players *lpPlayer = static_cast< Character *>( Target )->GetPlayer();
                    if( lpPlayer != NULL ){
                        if( lpPlayer->GetGodFlags() & GOD_DEVELOPPER ){
                            TFormat format;
                            Target->SendSystemMessage(
                                format(
                                    "You were hit by %s for %.2f damages (%.2f post-AC damages, %.2f final damage).",
                                    (LPCTSTR)Attacker->GetName(_DEFAULT_LNG),
                                    dblPreACstrike,
									dblPostACstrike,
                                    Blow.Strike
                                )
                            );
                        }
                    }
                }

				//AfxMessageBox("11\r\n");
				TRACE(_T("Training unit\r\n"));

				Attacker->TrainUnit();

		#ifdef __ENABLE_LOG
				if(__LOG > 60){
					CString logmsg;
					//AfxMessageBox("13\r\n");
					logmsg.Format("Unit ID#%u (%s) attacks unit ID#%u (%s) for %u damage.", Attacker->GetID(), 
						Attacker->GetName(), Target->GetID(), Target->GetName(), Blow.Strike);
					//AfxMessageBox("14\r\n");
					__LOG((LPCTSTR)logmsg);
					//AfxMessageBox("15\r\n");
				}
		#endif

				if( result != -1 ){
					TRACE( "\r\nBroadcasting attack" );

                    TRACE( "\r\nAttackerID=%u. TargetID=%u.", Attacker->GetID(), Target->GetID() );

                    Broadcast::BCAttack( Attacker->GetWL(), _DEFAULT_RANGE,
                        Attacker->GetID(),
                        Target->GetID(),
                        (Target->GetHP() * 100 / Target->GetMaxHP()),
                        Attacker->GetWL(),
                        Target->GetWL(),
                        Attacker->GetInvisibleQuery()
                    );

				}else{ // Kill me, do anything you want
                    Broadcast::BCAttack( Attacker->GetWL(), _DEFAULT_RANGE,
                        Attacker->GetID(),
                        Target->GetID(),
                        (Target->GetHP() * 100 / Target->GetMaxHP()),
                        Attacker->GetWL(),
                        Target->GetWL(),
                        Attacker->GetInvisibleQuery()
                    );

                    bool display = true;
                    if( Target->GetType() == U_PC ){                   
                        Character *pc = static_cast< Character * >( Target );
                        Players *pl = static_cast< Players * >( pc->GetPlayer() );
                        if( pl != NULL && ( pl->GetGodFlags() & GOD_CANNOT_DIE ) ){
                            display = false;
                        }
                    }

                    if( display ){
                        Broadcast::BCObjectChanged( Target->GetWL(), _DEFAULT_RANGE,//BLBLBL _DEFAULT_RANGE+5 => _DEFAULT_RANGE
                            Target->GetCorpse(),
                            Target->GetID(),
                            Attacker->GetInvisibleQuery()
                        );
                    }
				}
				
//				Attacker->Unlock();
//				Target->Unlock();			
			}else{
                Broadcast::BCMiss( Attacker->GetWL(), _DEFAULT_RANGE,
                    Attacker->GetID(),
                    Target->GetID(),
                    Attacker->GetWL(),
                    Target->GetWL(),
                    Attacker->GetInvisibleQuery()
                );
			}
						
			TRACE( "\r\nUnlocking units." );
			Attacker->Unlock();
			Target->Unlock();

			return 20; // dunno why actually.. this is 1 second exhaust			
		}
    }else{
        // Reset target if target happened to attack a hive.
        if( Target->GetType() == U_HIVE ){
            Attacker->SetTarget( Attacker->GetBond() );
        }
    }

    Attacker->Unlock();
    Target->Unlock();
    
    return 0;
}
/*TFCServerSocket remote;*/

//StaticObjects *Static_Objects_TABLE;

/***************************************/

/***************************************/

//////////////////////////////////////////////////////////////////////////////////////////
BOOL LoadDLLList
//////////////////////////////////////////////////////////////////////////////////////////
// Loads a dll list listed in the registry into the process's address space. If it
// fails to load a DLL, the function reports the error in the event manager.
//
(
 LPCTSTR lpszToken,							// The token used to load the list.
 TemplateList <HINSTANCE> *lptlDLLInstance	// Pointer to list which will contain the list
											// of loaded DLLs
)
// Return: LPHINSTANCE, Null terminated array of HINSTANCES containing the handles
// to all loaded DLLs.
//////////////////////////////////////////////////////////////////////////////////////////
{	
	BOOL boError = TRUE;
    BOOL boFound = TRUE;
	int i = 1;
	
	CString DLLname;
	CString csString;

    RegKeyHandler regKey;

    if( regKey.Open( HKEY_LOCAL_MACHINE, T4C_KEY EXTENSION_DLL_KEY ) ){
	    /////////////////////////////////////////////////////////////////////
	    // Loads the namespecs of the different DLLs associated to the objects
	    do{
		    csString.Format( "%s%u", lpszToken, i );
		    
		    DLLname = regKey.GetProfileString( csString, _T("NO MORE DLLs") );
		    if( DLLname != _T("NO MORE DLLs")){			    
                HINSTANCE *lphInstance = new HINSTANCE;
                try{
                    TRACE( "\r\n..%s..", (LPCTSTR)DLLname );
			        (*lphInstance) = LoadLibrary( DLLname );
                }catch(...){
                    _LOG_DEBUG
                        LOG_DEBUG_LVL1,
                        "Crashed while loading DLL file %s.",
                        (LPCTSTR)DLLname
                    LOG_
                    END_LOG;
                    exit( CRASH_LOADING_EXTENSION_DLL );
                }
			    if( *lphInstance != NULL ){
                    boError = FALSE;
				    lptlDLLInstance->AddToTail( lphInstance );
			    }else{
                    DWORD dwErr = GetLastError();
                    TRACE( "\r\nError=0x%x, %u.", dwErr, dwErr );
                    _LOG_DEBUG
                        LOG_DEBUG_LVL1,
                        "Couldn't load DLL file %s specified in the registry.(err=0x%x(%u))",
                        DLLname,
                        dwErr,
                        dwErr
                    LOG_

				    TRACE( "\r\nUnable to load DLL file %s", (LPCTSTR)DLLname );
				    delete lphInstance;
			    }
			    i++;
		    }else{
			    boFound = FALSE;
		    }
	    }while( boFound );
	    
	    if( i == 0 ){
            _LOG_DEBUG
                LOG_CRIT_ERRORS,
                "T4C Server does not have enough required DLLs to run."
            LOG_
            END_LOG
//		    ReportError(__FATAL_NO_REQUIRED_DLL);
		    exit( FATAL_NO_REQUIRED_DLL1 );
	    }

        regKey.Close();
    }

    return !boError;
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void ObjectListing( void );
void SkillRegistration( void );
void RegisterObjects( void );

//////////////////////////////////////////////////////////////////////////////////////////
 TFC_MAIN::TFC_MAIN( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creates the world. This is the primary initialisation of the server.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{	
    dwVersion = SERVER_CONNECTION_HI_VERSION;

	Skills::Create();

	Unit::InitializeMessagesProcs( );

	ObjectTimer::Create( );

	SpellMessageHandler::Create( );		
    
    // Initialize ODBC
	Players::InitializeODBC();
	
    SetUnhandledExceptionFilter( DefaultExcpFilter );

	Character::InitializeODBC();    
	Character::InitXPchart();
	
    /*if( !LoadDLLList( "ObjectDLL", &tlDllInstance ) ){
        _LOG_DEBUG
            LOG_CRIT_ERRORS,
            "\r\n     Cannot find any item DLL. Server is useless without items."
            "\r\n     Run T4C Server Setup from the control panel and add item DLLs."
        LOG_
     
        END_LOG
        exit( FATAL_NO_REQUIRED_DLL2 );
    }*/

    if( !LoadDLLList( "NPCDLL",    &tlDllInstance ) ){
        _LOG_DEBUG
            LOG_CRIT_ERRORS,
            "\r\n     Cannot find any NPC DLL. Server is useless without NPCs."
            "\r\n     Run T4C Server Setup from the control panel and add NPC DLLs."
        LOG_

        END_LOG
        exit( FATAL_NO_REQUIRED_DLL3 );
    }	
    /*if( !LoadDLLList( "SpellDLL",  &tlDllInstance ) ){
        _LOG_DEBUG
            LOG_CRIT_ERRORS,
            "\r\n     Cannot find any spell DLL. Server is useless without spells or skills."
            "\r\n     Run T4C Server Setup from the control panel and add spell DLLs."
        LOG_
        END_LOG
        exit( FATAL_NO_REQUIRED_DLL4 );
    }*/

    RegisterObjects();
    SkillRegistration();

	// Now that all the DLLs have been loaded and the units registered, initialize the global variables
	ObjectListing();

	// Then call all the DLL's unit startup functions.
	TFCMAIN::CallUnitStartupFunctions();    

	world_number = 0;
	
	TRACE(_T("%u"), GetLastError());

	flush_time =  ( theApp.sGeneral.dwTimeBeforeWarning * 20 ) / 1000; //BL Note : 1 round lasts 50ms, 20 rounds = 1 second that's why it's converted from seconds to number of rounds
	max_chances = (unsigned char)theApp.sGeneral.wNbWarnings; // BL note : read nbWarnings from registry or 5 by default. NbWarning chances.
    
	World = NULL;
	
	TFCTIME MaxTime;
	TFCTIME TimeLine;

	MaxTime.seconds = 60;
	MaxTime.minutes = 60;
	MaxTime.hours = 24;
	MaxTime.days = 7;
	MaxTime.weeks = 4;
	MaxTime.months = 12;
	
	TimeLine.seconds = 0;
	TimeLine.minutes = 0;
	TimeLine.hours   = 7;
	TimeLine.days    = 2;
	TimeLine.weeks   = 0;
	TimeLine.months  = 6;
	TimeLine.years   = 1997;

	TFCTime::Create(TimeLine, MaxTime);

    RegKeyHandler regKey;
    regKey.Open( HKEY_LOCAL_MACHINE, "Software\\Vircom\\The 4th Coming Server\\GeneralConfig" );

    // Fetch version from registry, otherwise default to the executable's version.
    dwVersion = regKey.GetProfileInt( "Version", SERVER_CONNECTION_HI_VERSION );
    regKey.Close();

    CAutoConfig::AddRegString( T4C_KEY GEN_CFG_KEY,   "SuperUser", "", HKEY_LOCAL_MACHINE );    
}

TFC_MAIN::~TFC_MAIN()
{
	if(World != NULL) delete [] World;

	// Uninitialize the DLLs
	TFCServer->tlDllInstance.ToHead();
	while( TFCServer->tlDllInstance.QueryNext() ){
		FreeLibrary( (*TFCServer->tlDllInstance.Object() ) );
		TFCServer->tlDllInstance.DeleteAbsolute();
	}		

}



/********************/
 