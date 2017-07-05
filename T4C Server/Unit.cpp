// Unit.cpp: implementation of the Unit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TFC Server.h"
#include "Unit.h"
#include "TFC_MAIN.H"
#include "WorldMap.h"
#include "CreatureListing.h"
#include "MonsterStructure.h"
#include "Random.h"
#include "_item.h"
#include "BlockingListing.h"
#include "IntlText.h"
#include "SpellMessageHandler.h"
#include "QuestFlagsListing.h"
#include "SpellListing.h"
#include <algorithm>
#include <set>

// Maximum quantity of recursive calls to allow when querying effects.
// Effects may trigger other effects on the same unit, which can easely 
// cause stack overflows.
#define MAX_EFFECT_STACK_LEVELS 1
#define MAX_MESSAGE_STACK_LEVELS 1

#pragma warning(disable:4786)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern TFC_MAIN *TFCServer;
extern CTFCServerApp theApp;

#define MAX_STARTUP_IDS				0x00100000  // 1048576 max static objects/NPCs
#define GLOBAL_ID_OFFSET			0x00100000

UINT							Unit::CurrentGlobalID	= GLOBAL_ID_OFFSET; 
//TemplateList <UINT>				Unit::UsedIDs;
BaseReferenceMessages *			Unit::lpMessagesProc[65536];
TemplateList <Unit::UNIT_TYPE>	Unit::tlUnitTypes;
std::map<DWORD,Unit *> Unit::unit_map;
extern Random rnd;

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::InitializeMessagesProcs( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Initializes the message procs.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{	
	int i;
	for( i = 0; i < 65536; i++ ){
		// No message handling by default
		lpMessagesProc[ i ] = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
WORD Unit::RegisterUnitMessageHandler
//////////////////////////////////////////////////////////////////////////////////////////
// Registers a message handler for message handling on a unit.
// 
(
 WORD wBaseReferenceID,					// Base reference ID of unit.
 BaseReferenceMessages *lpMessageUnit,	// Message handler.
 LPCTSTR lpszUnitName,					// Pointer to the name of the unit.
 BYTE bUnitType,						// Kind of unit to register
 BOOL boFindNextValidID,				// TRUE if function should assign the next valid ID.
 BOOL boForceRegistration
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	if( wBaseReferenceID == 0 ){
		return 0;
	}

	if( !boForceRegistration && GetIDFromName( lpszUnitName, 0, TRUE ) != 0 ){
		_LOG_DEBUG LOG_DEBUG_LVL1, "Two units are using the same global string ID %s.", lpszUnitName LOG_
		wBaseReferenceID = 0;
	}else{
		if( boFindNextValidID ){
			while( lpMessagesProc[ wBaseReferenceID ] ){
				wBaseReferenceID++;
			}
		}
		if( lpMessagesProc[ wBaseReferenceID ] == NULL ){
			_LOG_DEBUG
				LOG_DEBUG_HIGH,
				"Registering unit %u name %s type %u.",
				wBaseReferenceID,
				lpszUnitName,
				bUnitType
			LOG_
			
			UNIT_TYPE *lpUnitType = new UNIT_TYPE;
			lpUnitType->bUnitType = bUnitType;
			lpUnitType->csName = lpszUnitName;
			lpUnitType->wBaseReferenceID = wBaseReferenceID;

			lpMessageUnit->wBindedReferenceID = wBaseReferenceID;

			tlUnitTypes.AddToTail( lpUnitType );

			lpMessagesProc[ wBaseReferenceID ] = lpMessageUnit;
		}else{
			wBaseReferenceID = 0;
			_LOG_DEBUG LOG_DEBUG_LVL1, "Two units are using the same numerical ID %u. [%s]", 
								 wBaseReferenceID,
								 lpszUnitName
			LOG_
		}
	}

	TRACE( "\r\nRegistering ID %u", wBaseReferenceID );

	return wBaseReferenceID;	// Returns the actual ID of the newly created unit.
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Unit::GetNameFromID
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the registered unit name from its static reference ID.
// 
(
 WORD wID,			// The static reference ID of the unit
 LPTSTR lpszName,	// The buffer where the name will be put.
 BYTE bUnitType		// The unit type to search for.
)
// Return: BOOL, TRUE if function found the name, FALSE otherwise.
//////////////////////////////////////////////////////////////////////////////////////////
{
	UNIT_TYPE *lpUnitType;
	
	tlUnitTypes.Lock();
	// Find the ID
	tlUnitTypes.ToHead();
	while( tlUnitTypes.QueryNext() ){
		lpUnitType = tlUnitTypes.Object();

		// If we found the kind of unit we were searching for.
		if( lpUnitType->bUnitType == bUnitType || bUnitType == 0 ){
			// If name matches the unit name ( case sensitive )
			if( lpUnitType->wBaseReferenceID == wID ){
				strcpy( lpszName, (LPCTSTR)lpUnitType->csName );
				tlUnitTypes.Unlock();
				return TRUE;	// name found
			}

		}
	}
	tlUnitTypes.Unlock();

	return FALSE;	// Name not found
}
//////////////////////////////////////////////////////////////////////////////////////////
void Unit::UnRegisterUnits( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Unregisters and cleans all registered units
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	tlUnitTypes.ToHead();
	while( tlUnitTypes.QueryNext() ){
		tlUnitTypes.DeleteAbsolute();
	}

}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::UnregisterUnit( WORD wBaseReferenceID )
{
    tlUnitTypes.ToHead();
    while( tlUnitTypes.QueryNext() ){
        UNIT_TYPE *unitType = tlUnitTypes.Object();
        if( unitType->wBaseReferenceID == wBaseReferenceID ){
            tlUnitTypes.DeleteAbsolute();
        }
    }

    lpMessagesProc[ wBaseReferenceID ] = NULL;
}

Unit *Unit::GetByID(DWORD id)
{
	std::map<DWORD, Unit*>::iterator i = unit_map.find(id);
	if (i == unit_map.end()) return NULL;
	return (*i).second;
}

void Unit::DUMPUnits()
{
	{
		_LOG_DEBUG LOG_ALWAYS, "Listing all the %u existing units", unit_map.size() LOG_
		Unit *x;
		std::map<DWORD, Unit*>::iterator i = unit_map.begin();
		while (i!=unit_map.end()){
			x = (*i).second;
			if (x) {
				_LOG_DEBUG
					LOG_ALWAYS,
					"DU type %i ID %i (%s)",
					x->GetType(),
					(*i).first,
					x->GetName(_DEFAULT_LNG)
				LOG_
			}
			++i;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
WORD Unit::GetIDFromName
//////////////////////////////////////////////////////////////////////////////////////////
// This fonction finds the base reference ID of a registered NPC using its textual name.
// 
(
 CString csName,			// The name of the NPC.
 BYTE bUnitType,			// Unit type to search for.
 BOOL boInsensitiveSearch	// TRUE if unit name search is case insensitive.
)
// Return: WORD, The base reference ID of the registered NPC, 0 if name wasn't found.
//////////////////////////////////////////////////////////////////////////////////////////
{
	UNIT_TYPE *lpUnitType;
	
	// Find the ID
	tlUnitTypes.Lock();
	tlUnitTypes.ToHead();
	while( tlUnitTypes.QueryNext() ){
		lpUnitType = tlUnitTypes.Object();

		// If we found the kind of unit we were searching for.
		if( lpUnitType->bUnitType == bUnitType || bUnitType == 0 ){
			// If name matches the unit name ( case sensitive )
			if( !boInsensitiveSearch ){
				if( lpUnitType->csName == csName ){
					tlUnitTypes.Unlock();
					return lpUnitType->wBaseReferenceID;
				}
			}else{
				if( stricmp( (LPCTSTR)lpUnitType->csName, (LPCTSTR)csName ) == 0 ){
					tlUnitTypes.Unlock();
					return lpUnitType->wBaseReferenceID;
				}
			}

		}
	}
	tlUnitTypes.Unlock();
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Unit::SendGlobalUnitMessage
//////////////////////////////////////////////////////////////////////////////////////////
// Sends a message to all units registered.
// 
(
 UINT MessageID,		// The ID of the message
 UNIT_FUNC_PROTOTYPE
)
/////////////////////////////////////////////////////////////////////////////////////////
{
	DWORD wI;

	// Send all units this message
	for( wI = 0; wI < 65536; wI++ ){
		try{
		if( lpMessagesProc[ wI ] ){
#ifdef CHANGED_MESSAGES
#error "Change messages in Unit::SendGlobalUnitMessage()"
#endif			
			switch( MessageID ){
			case MSG_OnAttack: 
					lpMessagesProc[ wI ]->OnAttack( UNIT_FUNC_PARAM );
				break;
			case MSG_OnAttacked:
					lpMessagesProc[ wI ]->OnAttacked( UNIT_FUNC_PARAM );
				break;
			case MSG_OnDisturbed:
					lpMessagesProc[ wI ]->OnDisturbed( UNIT_FUNC_PARAM );
				break;
			case MSG_OnUse:
					lpMessagesProc[ wI ]->OnUse( UNIT_FUNC_PARAM );
				break;
			case MSG_OnTimer:
					lpMessagesProc[ wI ]->OnTimer( UNIT_FUNC_PARAM );
				break;
			case MSG_OnInitialise:
					lpMessagesProc[ wI ]->OnInitialise( UNIT_FUNC_PARAM );
				break;
			case MSG_OnTalk:
					lpMessagesProc[ wI ]->OnTalk( UNIT_FUNC_PARAM );
				break;
			case MSG_OnQuerySchedule:
					lpMessagesProc[ wI ]->OnQuerySchedule( UNIT_FUNC_PARAM );
				break;
			case MSG_OnView:
					lpMessagesProc[ wI ]->OnView( UNIT_FUNC_PARAM );
				break;
			case MSG_OnNoMoreShots:
					lpMessagesProc[ wI ]->OnNoMoreShots( UNIT_FUNC_PARAM );
				break;
			case MSG_OnMove:
					lpMessagesProc[ wI ]->OnMove( UNIT_FUNC_PARAM );
				break;
			case MSG_OnDeath:
					lpMessagesProc[ wI ]->OnDeath( UNIT_FUNC_PARAM );
				break;
			case MSG_OnHit:
					lpMessagesProc[ wI ]->OnHit( UNIT_FUNC_PARAM );
				break;
			case MSG_OnEquip:
					lpMessagesProc[ wI ]->OnEquip( UNIT_FUNC_PARAM );
				break;
			case MSG_OnUnequip:
					lpMessagesProc[ wI ]->OnUnequip( UNIT_FUNC_PARAM );
				break;
			case MSG_OnServerInitialisation:
					lpMessagesProc[ wI ]->OnServerInitialisation( UNIT_FUNC_PARAM, (WORD)wI );
				break;
			case MSG_OnServerTermination:
					lpMessagesProc[ wI ]->OnServerTermination( UNIT_FUNC_PARAM );
				break;
			case MSG_OnNPCDataExchange:
					lpMessagesProc[ wI ]->OnNPCDataExchange( UNIT_FUNC_PARAM );
				break;
			case MSG_OnGetUnitStructure:
					lpMessagesProc[ wI ]->OnGetUnitStructure( UNIT_FUNC_PARAM );
				break;
			case MSG_OnPopup:
					lpMessagesProc[ wI ]->OnPopup( UNIT_FUNC_PARAM );
				break;
            case MSG_OnAttackHit:
                    lpMessagesProc[ wI ]->OnAttackHit( UNIT_FUNC_PARAM );
                break;
            case MSG_OnDestroy:
                    lpMessagesProc[ wI ]->OnDestroy( UNIT_FUNC_PARAM );
                break;
			}
		}
		}catch(...){
			_LOG_DEBUG
				LOG_CRIT_ERRORS,
				"Crashed sending message %u to structure %u (self=0x%x, medium=0x%x, target=0x%x, valueIN=0x%x, valueOUT=0x%x)",
				MessageID,
				wI,
				self, medium, target,
				valueIN, valueOUT
			LOG_
			throw;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
// Default message mapping
#ifdef CHANGED_MESSAGES
#error "Change messages in BaseReferenceMessages(), at start of Unit.cpp"
#endif

void BaseReferenceMessages::OnAttack( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnAttacked( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnDisturbed( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnUse( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnTimer( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnTalk( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnQuerySchedule( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnInitialise( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnView( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnNoMoreShots( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnMove( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnDeath( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnHit( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnEquip( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnUnequip( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnServerInitialisation( UNIT_FUNC_PROTOTYPE, WORD wBaseReferenceID ){};
void BaseReferenceMessages::OnServerTermination( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnGetUnitStructure( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnPopup( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnAttackHit( UNIT_FUNC_PROTOTYPE ){};
void BaseReferenceMessages::OnDestroy( UNIT_FUNC_PROTOTYPE ){};

//std::map<DWORD,Unit *> Unit::unit_map;
//std::map<DWORD,Unit *> Unit::unit_map;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Unit::Unit( bool boDbgLock )
{
    queryInvisible.SetUnit( this );
    
    // Unit always has a reference count of 1 by default.
    dwRefCount = 1;

    // Unit isn't 'dead' by default.
    boDead = false;

	bStatus = 0;
    wlOriginalPos.X = wlOriginalPos.Y = wlOriginalPos.world = -1;

	WL.X = WL.Y = WL.world = 0;
	speed = 50; // default speed
	doing = nothing;
	ToBeKilled = TRUE;  // Only NPCs should not be killed by the system
	Bond = NULL;
	Target = NULL;
	GlobalID = 0xFFFFFFFF;
	wlUpperLimit.X = wlUpperLimit.Y = wlUpperLimit.world = -1;
	wlLowerLimit.X = wlLowerLimit.Y = wlLowerLimit.world = -1;

	lptlEffectList = NULL;
	lptlBoostList = new TemplateList <BOOST>;
	bBlock = bCurrentBlocking = __BLOCK_NONE;
    cRadiance = 0;
    wLevel = 0;

    UnitType = 0;

    StatINT = StatSTR = StatEND = StatAGI = StatWIL = StatWIS = StatLCK = StatDODGE = StatATTACK = 0;

    boInvisible = false;

    // Stack level for effects starts at 0.
    effectStackLevel = 0;
    messageStackLevel = 0;

    loadMentalExhaust = 0;
    loadMoveExhaust = 0;
    loadAttackExhaust = 0;

	userSpeed = 1;//Nombre de cases pour chaque ordre de déplacement

	bRainState=0;//BLBLBL 08/12/2010 initially no weather effect
	bFogState=0;
	bSnowState=0;

	// asteryth guild
	GuildID = -1;
	// asteryth pvp ranking
	TotalDeathNumber = TotalKillNumber = CurrentDeathNumber = CurrentKillNumber = BestSerieMurder = CurrentSerieMurder = CurrentPvpPoint = 0;

}

Unit::~Unit()
{	
	if( GetType() == U_OBJECT ){
		ObjectTimer::RemoveObject( this );
	}
    
    LPUNIT_EFFECT lpEffect;

    if( lptlEffectList != NULL ){
		lptlEffectList->ToHead();
		while( lptlEffectList->QueryNext() ){
            lpEffect = lptlEffectList->Object();

        	if( lpEffect->lpFunc ){
		        lpEffect->lpFunc( MSG_OnDestroy, lpEffect->dwEffect, this, NULL, NULL, lpEffect->lpData, NULL );
			}
			lptlEffectList->DeleteAbsolute();
		}
		delete lptlEffectList;
	}

	if( lptlBoostList != NULL ){
		lptlBoostList->ToHead();
		while( lptlBoostList->QueryNext() ){
			lptlBoostList->DeleteAbsolute();
		}
		delete lptlBoostList;
	}
	unit_map[GlobalID]=0;
	TRACE(_T("Destroyed a unit with address 0x%x "), this);
}

//////////////////////////////////////////////////////////////////////////////////////////
bool Unit::DeleteUnit( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Deletes a unit. If the unit has a zero reference count, it is removed from memory.
// 
// Return: bool, true if the unit was deleted from memory.
//////////////////////////////////////////////////////////////////////////////////////////
{    
    // Synchronize all unit deletions.
    static CLock globalUnitDeletionLock;
    CAutoLock globalLock( &globalUnitDeletionLock );
    
    dwRefCount--;
    if( dwRefCount == 0 ){
        SendUnitMessage( MSG_OnDestroy, this, NULL, NULL );
        // Use global operator delete.
        ::delete this;
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::CreateVirtualUnit( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Simply increase the reference count so next delete will only 'virtually' destroy
//  the unit.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    dwRefCount++;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// This is a TIMERCALLBACK function which clean corpses after a while
void Unit::CleanCorpse( TIMERCALLBACK_PROTOTYPE ){
	Unit *puCorpse = (Unit *)lpData;
	WorldPos wlPos = puCorpse->GetWL();
	
	WorldMap *wl = TFCMAIN::GetWorld(wlPos.world);
	
	if(wl){
		wl->remove_world_unit(wlPos, puCorpse->GetID());

        Broadcast::BCObjectRemoved( wlPos, _DEFAULT_RANGE,
            puCorpse->GetID()
        );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Creates a unit (You MUST call this function!!)
BOOL Unit::Create(UINT Type, UINT Reference){
    // If a base message handler has been defined for this unit
    // or if this unit is a character (doesn't need a base message handler).
    if( lpMessagesProc[ Reference ] || Type == U_PC ){
		BOOL ReturnValue = TRUE;
		//void *StaticFlagAddr = NULL;
		
		// if CurrentGlobalID has reach the end of the string
 		if(CurrentGlobalID == 0xFFFFFFFF){
			// Then go back to the lowest offset of the global IDs and skip the static IDs
			CurrentGlobalID = GLOBAL_ID_OFFSET + MAX_STARTUP_IDS;
		}
		unit_map[CurrentGlobalID] = this;
		SetID( CurrentGlobalID ++ );

		
		// Sets the basic stats of the unit
		UnitType = Type;
		Appearance = BaseReferenceID = Reference;
		
		// Then dispatch an initialisation message.	
		bool boInit = true;
        if( SendUnitMessage(MSG_OnInitialise, this, NULL, NULL, &boInit, NULL) ){
            ReturnValue = boInit;
            if( !boInit ){
                _LOG_DEBUG
                    LOG_DEBUG_LVL1,
                    "Failed to create unit ID %u (Type %u).", Reference, Type
                LOG_
            }
        }else{
            ReturnValue = false;
        }

    	return ReturnValue;
	}
    BaseReferenceID = 0;
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Unit::SendUnitMessage
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
 UINT MessageID,		// Message to send
 UNIT_FUNC_PROTOTYPE	// self/medium/target/valueIN/valueOUT
)
// Return: BOOL, TRUE if message could be sent
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Returns FALSE if the dispatcher failed to find the static unit
	ASSERT( BaseReferenceID <= 65535 );
    if( BaseReferenceID > 65535 ){
		return FALSE;
	}
	if( lpMessagesProc[ BaseReferenceID ] ){
#ifdef CHANGED_MESSAGES
#error "Change messages in Unit::SendUnitMessage()"
#endif			
		bMarker = 0;	// clears the marker before any message call.
		
		switch( MessageID ){
		case MSG_OnAttack: 
                if( messageStackLevel >= MAX_MESSAGE_STACK_LEVELS ){
                    return FALSE;
                }
                messageStackLevel++;
				lpMessagesProc[ BaseReferenceID ]->OnAttack( UNIT_FUNC_PARAM );
                messageStackLevel--;
			break;
		case MSG_OnAttacked:
                if( messageStackLevel >= MAX_MESSAGE_STACK_LEVELS ){
                    return FALSE;
                }
                messageStackLevel++;
				lpMessagesProc[ BaseReferenceID ]->OnAttacked( UNIT_FUNC_PARAM );
                messageStackLevel--;
			break;
		case MSG_OnDisturbed:
				lpMessagesProc[ BaseReferenceID ]->OnDisturbed( UNIT_FUNC_PARAM );
			break;
		case MSG_OnUse:
				lpMessagesProc[ BaseReferenceID ]->OnUse( UNIT_FUNC_PARAM );
			break;
		case MSG_OnTimer:
				lpMessagesProc[ BaseReferenceID ]->OnTimer( UNIT_FUNC_PARAM );
			break;
		case MSG_OnInitialise:
				lpMessagesProc[ BaseReferenceID ]->OnInitialise( UNIT_FUNC_PARAM );
			break;
		case MSG_OnTalk:
				lpMessagesProc[ BaseReferenceID ]->OnTalk( UNIT_FUNC_PARAM );
			break;
		case MSG_OnQuerySchedule:
				lpMessagesProc[ BaseReferenceID ]->OnQuerySchedule( UNIT_FUNC_PARAM );
			break;
		case MSG_OnView:
				lpMessagesProc[ BaseReferenceID ]->OnView( UNIT_FUNC_PARAM );
			break;
		case MSG_OnNoMoreShots:
				lpMessagesProc[ BaseReferenceID ]->OnNoMoreShots( UNIT_FUNC_PARAM );
			break;
		case MSG_OnMove:
				lpMessagesProc[ BaseReferenceID ]->OnMove( UNIT_FUNC_PARAM );
			break;
		case MSG_OnDeath:
				lpMessagesProc[ BaseReferenceID ]->OnDeath( UNIT_FUNC_PARAM );
			break;
		case MSG_OnHit:
                if( messageStackLevel >= MAX_MESSAGE_STACK_LEVELS ){
                    return FALSE;
                }
                messageStackLevel++;
				lpMessagesProc[ BaseReferenceID ]->OnHit( UNIT_FUNC_PARAM );
                messageStackLevel--;
			break;
		case MSG_OnEquip:
				lpMessagesProc[ BaseReferenceID ]->OnEquip( UNIT_FUNC_PARAM );
			break;
		case MSG_OnUnequip:
				lpMessagesProc[ BaseReferenceID ]->OnUnequip( UNIT_FUNC_PARAM );
			break;
		case MSG_OnNPCDataExchange:
				// We cannot allow this to happen when the units are not close enough!
				// BUY, SELL, TEACH, TRAIN and LEARN can only happen face to face!
				if (GetWL().AreInRange(target->GetWL(), 13) == FALSE) {
					return FALSE;
				}
				lpMessagesProc[ BaseReferenceID ]->OnNPCDataExchange( UNIT_FUNC_PARAM );
			break;
		case MSG_OnGetUnitStructure:
				lpMessagesProc[ BaseReferenceID ]->OnGetUnitStructure( UNIT_FUNC_PARAM );
			break;
		case MSG_OnPopup:
				lpMessagesProc[ BaseReferenceID ]->OnPopup( UNIT_FUNC_PARAM );
			break;
		case MSG_OnDestroy:
				lpMessagesProc[ BaseReferenceID ]->OnDestroy( UNIT_FUNC_PARAM );
			break;
        case MSG_OnAttackHit:
                if( messageStackLevel >= MAX_MESSAGE_STACK_LEVELS ){
                    return FALSE;
                }
                messageStackLevel++;
                lpMessagesProc[ BaseReferenceID ]->OnAttackHit( UNIT_FUNC_PARAM );
                messageStackLevel--;
            break;
        default:
            return FALSE;
            break;
		}
	}else{
        if( GetType() == U_HIVE || GetType() == 0 ){
            return TRUE;
        }

        DWORD callerAddr;
        GET_CALLER_ADDR( callerAddr );

        // A message was sent to a unit which does not have a message handler.
        ASSERT( false );

        _LOG_DEBUG
            LOG_DEBUG_LVL1,
            "Tried to send unit message %u to unit %s, type %u staticID %u. Caller=0x%x.",
            MessageID,
            (LPCTSTR)GetName( _DEFAULT_LNG ),
            GetType(),
            BaseReferenceID,
            callerAddr
        LOG_

		return FALSE;
	}

	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Returns U_OBJECT, U_PC or U_NPC
char Unit::GetType(){
	return UnitType;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Returns the position of the unit
WorldPos Unit::GetWL(){
	return WL;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Sets the position of a unit (warning, this does not teleport the unit!)
void Unit::SetWL(WorldPos pos){
    // Unit position setting is critical.
    if( wlOriginalPos.X == -1 || wlOriginalPos.Y == -1 || wlOriginalPos.world == -1 ){
		wlOriginalPos = pos;
	}
	WL = pos;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Returns the DWORD global ID of the unit
UINT Unit::GetID(){
	return GlobalID;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Sets the ID of the unit
void Unit::SetID(UINT ID){
	GlobalID = ID;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Returns the reference of the unit
UINT Unit::GetStaticReference(){
	return BaseReferenceID;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Sends an 'attack' message to the base reference.
int Unit::attack(LPATTACK_STRUCTURE blow, Unit *Target){	
	int attackID = 0;	
	QueryEffects( MSG_OnAttack, blow, NULL, Target );
	SendUnitMessage(MSG_OnAttack, this, NULL, Target, blow, &attackID);
	blow->Strike += QueryBoost( STAT_DAMAGE );
return attackID;
}
////////////////////////////////////////////////////////////////////////////////////////////////////	
// Sends an 'attacked' message to the base reference.
int Unit::attacked(LPATTACK_STRUCTURE blow, Unit *Mechant){	
	int dodgeID;
	QueryEffects( MSG_OnAttacked, blow, NULL, Mechant );
	SendUnitMessage(MSG_OnAttacked, this, NULL, Mechant, blow, &dodgeID);
return dodgeID;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Sends a 'hit' message to the base reference.
int Unit::hit(LPATTACK_STRUCTURE blow, Unit *WhoHit){
	int status;
	QueryEffects( MSG_OnHit, blow, NULL, WhoHit );
	SendUnitMessage(MSG_OnHit, this, NULL, WhoHit, blow, &status);
return status;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// Sent message when an attack successfully hits
int Unit::attack_hit(LPATTACK_STRUCTURE s_asBlow, Unit *lpuTarget){
    QueryEffects( MSG_OnAttackHit, s_asBlow, NULL, lpuTarget );
    SendUnitMessage( MSG_OnAttackHit, this, NULL, lpuTarget, s_asBlow );
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Unit::Death( LPATTACK_STRUCTURE lpBlow, Unit *lpuKiller ){
}

//////////////////////////////////////////////////////////////////////////////////////////
CString Unit::GetName
//////////////////////////////////////////////////////////////////////////////////////////
//  Gets the name of a unit.
// 
(
 WORD wLang // The language in which to fetch the unit's name
)
// Return: CString, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    char szName[ 256 ];        
    bool boNameFound = false;

	switch(GetType()){
	case U_NPC:{
		MonsterStructure *npc = NULL;
		SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &npc);
        if(npc){
            if( npc->name != NULL ){
                strcpy( szName, npc->name );
                boNameFound = true;
            }else{
                szName[ 0 ] = 0;                
            }
        }else{
            return("[anonymous NPC]");
        }
	}break;
	case U_OBJECT:{
		_item *obj = NULL;
		SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &obj);
        if(obj){
            if( obj->name != NULL ){
                strcpy( szName, obj->name );
                boNameFound = true;
            }else{
                szName[ 0 ] = 0;                
            }
        }else{
            return("[unnamed object]");
        }
	}break;
    default:
        szName[ 0 ] = 0;
    break;
	}
    
    // If a name was found.
    if( boNameFound ){
        // Check if it was defined in another language.
        return IntlText::ParseString( szName, wLang );
    }

    return szName;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// This function is implemented only for virtual purposes
void Unit::SetName(CString newname){
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// ID of the icon showed on the server
UINT Unit::GetAppearance(){
	return Appearance; // since usually the reference ID will be the same as the appearance
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Set the ID of the icon
void Unit::SetAppearance(UINT new_appearance){
	Appearance = new_appearance;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Only players need XP, this function is provided for virtual purposes
void Unit::SetXP(__int64 xp){
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// Only players need XP, this function is provided for virtual purposes
__int64 Unit::GetXP(){
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// Only U_OBJECT and U_PC have backpacks, this function is provided for virtual purposes
TemplateList <Unit> *Unit::GetBackpack(){
	return NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// This function is provided for virtual purposes
void Unit::SetBackpack(TemplateList <Unit> *LList){	
}
//////////////////////////////////////////////////////////////////////////////////////////////
// This function is provided for virtual purposes
TemplateList <Unit> *Unit::GetEquipped(){
	return NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// This function is provided for virtual purposes
void Unit::SetEquipped(TemplateList <Unit> *LList){	
}
//////////////////////////////////////////////////////////////////////////////////////////////
// This function is provided for virtual purposes
EXHAUST Unit::GetExhaust(){
	EXHAUST tmp = {0,0,0};
	return tmp;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// This function is provided for virtual purposes
void Unit::SetExhaust(EXHAUST newExhaust){
}
//////////////////////////////////////////////////////////////////////////////////////////////
// Returns current unit behavior (for U_NPCs and U_OBJECT)
BYTE Unit::IsDoing(){
	return doing;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a unit behavior
void Unit::Do(BYTE newDoing){
	doing = newDoing;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// This function is provided for virtual purposes
WorldPos Unit::Destination(){
	WorldPos dummy;
	dummy.X = 0;		// 0 is getting nowhere, -1 is wandering aimlessly
	dummy.Y = 0;
	dummy.world = 0;
	return dummy;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// This function is provided for virtual purposes
void Unit::SetDestination(WorldPos newPos){
}
//////////////////////////////////////////////////////////////////////////////////////////////
// Moves a unit in the map
// Returns the new position of the unit
WorldPos Unit::MoveUnit(DIR::MOVE where, BOOL boAbsolute, bool boCompressMove, bool boBroadcastMove){	
	Lock();	

    WorldPos WL = GetWL();
	BOOL blocked = FALSE;
	
	WorldPos CurrentWL = GetWL();

	if(!ViewFlag(__FLAG_STUN)){

		WorldMap *world = TFCMAIN::GetWorld(WL.world);
	
		switch(where)
		{
		case DIR::north: 
				WL.Y -= userSpeed;
			break;

		case DIR::northeast:
				WL.Y -= userSpeed;
				WL.X += userSpeed;
			break;

		case DIR::east:
				WL.X += userSpeed;
			break;

		case DIR::southeast:
				WL.Y += userSpeed;
				WL.X += userSpeed;
			break;

		case DIR::south:
				WL.Y += userSpeed;
			break;

		case DIR::southwest:
				WL.Y += userSpeed;
				WL.X -= userSpeed;
			break;

		case DIR::west:
				WL.X -= userSpeed;
			break;

		case DIR::northwest:
				WL.X -= userSpeed;
				WL.Y -= userSpeed;
			break;
		}
    	
        boBroadcast = !boBroadcast; //BL : apparement on n'envoie qu'un seul mouvement sur 2 avec ce systeme de "compression"...


        bool boSendMove = true;

        // If the user wants to use compressed movement sending.
        if( boCompressMove ){
            // Set move broadcasting to the current broadcast state (true or false).
            boSendMove = boBroadcast;
        }

        // If movement is NOT to be sent
        if( !boBroadcastMove  ){
            boSendMove = false;
        }
        
		//4 aout 2009 : apparement ça cause des lags d'après les joueurs... on enlève à nouveau pour rééssayer.
		//13 janvier : nouvelle tentative !! oula, bah en fait ça fait carré rouge sur carré rouge et 
		//apparement des pointes à 6mb d'upload sur la bande passante du servuer ...
		//boSendMove = true;//BLBLBL 28 juillet 2009 : test de toujours envoyer le broadcast, (donc plus de "compression")
						  //en espérant que cela réduise les ghosts de monstres qui du coup peuvent ne pas se trouver
						  //à l'endroit où le client pense qu'ils sont.
						  //en espérant aussi réduire les "sauts temporels" en cas de lag ou de speedhack volontaire
						  //d'un GM (en bidouillant le userspeed).
			
		if( !world->move_world_unit(CurrentWL, WL, GetID(), (char)where, boAbsolute, boSendMove ) ){
			WL = CurrentWL;
		}else{	
			world->QueryEffects(WL, this); // Checks for any "area" effects that might affect what we stepped in
			WL = GetWL();	// Worldpos may have changed
			// search move effects
			QueryEffects( MSG_OnMove, NULL, NULL, NULL );
		}
			
	}else{
		WL = CurrentWL;
	}

    Unlock();

//	SetWL(WL);
return WL;
}
////////////////////////////////////////////////////////////////////////////////////////////
// Get the exhaust relative to the speed of the unit (when moving)
BYTE Unit::GetSpeedExhaust(){
	if(!speed) speed = 1;
	return (200 / speed); // returns speed in rounds of exhaust
}
////////////////////////////////////////////////////////////////////////////////////////
// Returns the speed (moves per 10 seconds)
BYTE Unit::GetSpeed(){
	return speed;
}
////////////////////////////////////////////////////////////////////////////////////////
// Sets a new speed (moves per 10 seconds)
void Unit::SetSpeed(BYTE newSpeed){
	speed = newSpeed;
}
/////////////////////////////////////////////////////////////////////////////////////////
// Units are _NEUTRAL by default, This function is provided for virtual purposes
char Unit::GetAgressivness(){
	return _NEUTRAL;
}
/////////////////////////////////////////////////////////////////////////////////////////
// This function is provided for virtual purposes
void Unit::SetAgressivness(char newAgressive){	
}
/////////////////////////////////////////////////////////////////////////////////////////
// This function is provided for virtual purposes
WORD Unit::GetClan(){
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
// This function is provided for virtual purposes
void Unit::SetClan(WORD newClan){
}
//////////////////////////////////////////////////////////////////////////////////////////////
// Returns the unit targetted (talk or fight) by the unit.
Unit *Unit::GetTarget(){
	return Target;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a target (talk or fight, depending on what the unit DOes)
void Unit::SetTarget(Unit *newTarget){
	// If the target changed.
    if( Target != newTarget ){
        if( newTarget != NULL && ( newTarget->GetType() == U_OBJECT || newTarget->GetType() == U_HIVE ) ){
            return;
        }
        Target = newTarget;
/*
        DWORD callerAddr = 0;
        __asm{
            push eax
            mov eax, dword ptr[ ebp + 4 ]
            mov callerAddr, eax
            pop eax
        };

        _LOG_DEBUG
            LOG_DEBUG_LVL4,
            "Unit %u 0x%u set target to 0x%x. ThreadId=%u Caller=0x%08x",
            GetID(),
            this,
            Target,
            GetCurrentThreadId(),
            callerAddr
        LOG_*/
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
// Returns the corpse (Icon) of the unit
WORD Unit::GetCorpse(){
	return Corpse;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// Sets a new corpse (Icon) for the unit
void Unit::SetCorpse(WORD newCorpse){
	Corpse = newCorpse;
}
////////////////////////////////////////////////////////////////////////////////////////////
// This function is provided for virtual purposes
UINT Unit::GetIdleTime(){
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////
// This function is provided for virtual purposes
void Unit::SetIdleTime(UINT newTime){
}
/////////////////////////////////////////////////////////////////////////////////////////
// This funtions returns TRUE if the system is allowed to kill the unit because it was idle
BOOL Unit::SystemDestroy(){
	return ToBeKilled;
}
/////////////////////////////////////////////////////////////////////////////////////////
// This functions sets the condition. See Unit::SystemDestroy()
void Unit::SetSystemDestroy(BOOL value){
	ToBeKilled = value;
}
/////////////////////////////////////////////////////////////////////////////////////////
// This functions is here only for virtual purposes
DWORD Unit::GetTrueMaxHP(){
	return 1;
}

DWORD Unit::GetMaxHP(){
    DWORD maxHP = GetTrueMaxHP();
	int boost = QueryBoost( STAT_MAX_HP );
    
    // If the boost give positive max HP
    if( (int)maxHP + boost > 0 ){
        maxHP += boost;
    }else{
        maxHP = 1;
    }
	
    return maxHP;
}

/////////////////////////////////////////////////////////////////////////////////////////
// This functions is here only for virtual purposes
void Unit::SetMaxHP(DWORD NewHP){
}

/////////////////////////////////////////////////////////////////////////////////////////
// This functions is here only for virtual purposes
DWORD Unit::GetHP(){
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
// This functions is here only for virtual purposes
void Unit::SetHP(DWORD NewHP, bool boUpdate ){	
}


/////////////////////////////////////////////////////////////////////////////////////////
// This functions is here only for virtual purposes
WORD Unit::GetTrueMaxMana(){
	return 1;
}

WORD Unit::GetMaxMana(){
    WORD maxMana = GetTrueMaxMana();
	int boost = QueryBoost( STAT_MAX_MANA );
    
    // If the boost give positive max HP
    if( (int)maxMana + boost > 0 ){
        maxMana += boost;
    }else{
        maxMana = 1;
    }
	
    return maxMana;
}

/////////////////////////////////////////////////////////////////////////////////////////
// This functions is here only for virtual purposes
void Unit::SetMaxMana(WORD NewHP){
}

/////////////////////////////////////////////////////////////////////////////////////////
// This functions is here only for virtual purposes
WORD Unit::GetMana(){
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
// This functions is here only for virtual purposes
void Unit::SetMana(WORD NewHP, BOOL boEcho ){	
}

/////////////////////////////////////////////////////////////////////////////////////////
// This functions is provided for virtual purposes
int Unit::GetGold(){
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
// This functions is provided for virtual purposes
void Unit::SetGold(int newGold, BOOL boEcho ){
}

///////////////////////////////////////////////////////////////////////////////////////
// This function teleports a unit anywhere in the world.
BOOL Unit::Teleport(WorldPos to, BYTE How){

	WorldPos from = GetWL();
	WorldMap *SourceWorld = TFCMAIN::GetWorld( from.world );
	WorldMap *TargetWorld = TFCMAIN::GetWorld( to.world );

//	TRACE("Teleporting from ( %u %u %u ) to ( %u %u %u )\r\n",from.X, from.Y, from.world, to.X, to.Y, to.world);
	_LOG_WORLD
        LOG_DEBUG_LVL1,
        "Unit %s teleported from ( %u, %u, %u ) to ( %u, %u, %u ) addr( 0x%x )",
        (LPCTSTR)GetName( _DEFAULT_LNG ),
        from.X,
        from.Y,
        from.world,
        to.X,
        to.Y,
        to.world,
        this
    LOG_

	Lock();
    if(SourceWorld && TargetWorld){
		if(SourceWorld->IsValidPosition(from) && TargetWorld->IsValidPosition(to)){
            
            SetLastTeleport( to );

			SourceWorld->remove_world_unit(from, GetID());			

			SetWL( to );

			// then send a broadcast..
            Broadcast::BCObjectRemoved( from, 40, //BLBLBL 2 avril 2009 : _DEFAULT_RANGE au lieu de 40, remis 40..
                GetID()
            );
			
			// Only handle this part if its a PC which entered the teleport
			if( UnitType == U_PC ){
				TFCPacket sending;

				sending << (RQ_SIZE)RQ_TeleportPlayer;
				sending << (short)to.X;
				sending << (short)to.Y;
				sending << (short)to.world;

				SendPlayerMessage( sending );

				// Get the Character structure
				Character *ThisCharacter = static_cast<Character *>( this );

				// Stop the AutoCombat to prevent possibility of xp
				// if player isn't on the WorldMap
				ThisCharacter->StopAutoCombat();

				// Save character before putting it out of game
				//ThisCharacter->SaveCharacter();

                {
				    Players *pPlayer = (Players *)ThisCharacter->GetPlayer();

                    if( pPlayer != NULL ){
				        // Remove player from the game and put it in pre-in game waiting state.
						
						//BLBLBL Truc bizare ici, à vérifier pourquoi on sort du ingame
						//ça a l'air de causer des freezes (le joueur ne peut plut bouger/lancer de sort)
						//mais peut continuer à lire les CC et voir les autres choses bouger à son écran.

				        pPlayer->in_game = FALSE;
				        pPlayer->boPreInGame = TRUE;

                        // If the god doesn't have the GOD_NO_MONSTERS flag.
                        if( !( pPlayer->GetGodFlags() & GOD_NO_MONSTERS ) ){
				            TargetWorld->VerifyInviewHives( to );
                        }
                    }
                }

				sending.Destroy();//sending est re-peuplé à l'appel de packet_inview_units plusbas

                int read;
				read = TargetWorld->packet_inview_units( to, sending, 40, this );//BLBLBL _DEFAULT_RANGE visiblement trop peu, pour la porte de du couloir oracle, je vais essayer 40

                // If items were packetted.
                if( read > 0 ){	
                    SendPlayerMessage( sending );
                }

								  

			}else{
				TargetWorld->deposit_unit( to, this );

				// If unit isn't a player teleport it rightaway
                BroadcastPopup( to );
			}
		
        Unlock();
		return TRUE;
		}
		
	}
Unlock();
return FALSE;
}

////////////////////////////////////////////////////////////////////////////////////////////
// These function set "bonds" (a unit to which they "belong")
Unit *Unit::GetBond(){return Bond;};
/////////////////////////////////////////////////////////////////////////////////////////
void Unit::SetBond(Unit *newBond){
	Bond = newBond;
};


///////////////////////////////////////////////////////////////////////////////////////////
// This functions returns TRUE if wlPos is whithin the limit of the wlUpper/LowerLimit.
BOOL Unit::IsInLimit(WorldPos wlPos){
	// If there is no limit (-1) then return TRUE
	if(wlLowerLimit.X == -1 || wlLowerLimit.Y == -1 || wlUpperLimit.X == -1 || wlUpperLimit.Y== 1)
		return TRUE;

	// else check if it is whitin the limit "box"
	if(wlPos.X >= wlLowerLimit.X && wlPos.X <= wlUpperLimit.X && 
		wlPos.Y >= wlLowerLimit.Y && wlPos.Y <= wlUpperLimit.Y) return TRUE;

	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////
// This functions set the lower world limit of the unit
void Unit::SetLowerLimit(WorldPos wlPos){
	wlLowerLimit = wlPos;
}
/////////////////////////////////////////////////////////////////////////////////////////////
// This functions set the upper world limit 
void Unit::SetUpperLimit(WorldPos wlPos){
	wlUpperLimit = wlPos;
}
////////////////////////////////////////////////////////////////////////////////////////////
// Sets the destination of the monster to the center of it's limit
void Unit::GotoLimit(void){	
	WorldPos wlNewDest = {((wlUpperLimit.X - wlLowerLimit.X) / 2) + wlLowerLimit.X,
						  ((wlUpperLimit.Y - wlLowerLimit.Y) / 2) + wlLowerLimit.Y, 
							GetWL().world};
	
	SetDestination(wlNewDest);
}

////////////////////////////////////////////////////////////////////////////////////////////
// this function should return the ThisPlayer member of a Character (virtual)
void *Unit::GetPlayer(){return NULL;};

///////////////////////////////////////////////////////////////////////////////////////////
// This function, well, trains a unit :) virtual function
void Unit::TrainUnit(){}

/////////////////////////////////////////////////////////////////////////////////////////////
// These function get and set the level
WORD Unit::GetLevel(){
	return wLevel;
}
void Unit::SetLevel(WORD wNewLevel){
	wLevel = wNewLevel;
}
/////////////////////////////////////////////////////////////////////////////////////////////
// This function returns the class of the unit, U_NPC and _PLAYER only..
BYTE Unit::GetClass(){
	return nClass;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Returns the class points of a unit, for U_PC only
LPWORD Unit::GetClassPoints(){
	return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////
// virtual fonction
void Unit::SendPlayerMessage(TFCPacket &sending){
}

/*
//////////////////////////////////////////////////////////////////////////////////////////////
// virtual function
WORD Unit::GetFaith(){
	return 0;
}
WORD Unit::GetMaxFaith(){
	return 1;
}
void Unit::SetFaith(WORD fds){};
void Unit::SetMaxFaith(WORD fds){};
*/
//////////////////////////////////////////////////////////////////////////////////////////////
// virtual function
BOOL Unit::UseSkillPnts(BYTE bQuantity){return FALSE;};
BOOL Unit::UseStatPnts(BYTE bQuantity){return FALSE;};

BOOL Unit::UseSkill(int nID, Unit *target, LPVOID lpValueOUT ){return FALSE;};

BOOL Unit::UseSkill(int nID, WorldPos wlPos){return FALSE;};

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::Talk
//////////////////////////////////////////////////////////////////////////////////////////
// Allows a unit, whichever type, to talk
// 
(
 LPCTSTR Message, // Message to say.
 DWORD dwColor,   // Color of message.
 Unit *lpuTalkTo  // Unit to who we talk to.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	BYTE bDirection = 0;	
	signed int Xoff, Yoff;

	if( lpuTalkTo ){
		WorldPos wlUs   = GetWL();
		WorldPos wlThem = lpuTalkTo->GetWL();
		
		Xoff = (wlThem.X - wlUs.X + 11) * 3;
		Yoff = (wlThem.Y - wlUs.Y + 16) * 2;
	
		if( Yoff > 30 ){
			if( Xoff > 30 ){
				Xoff -= 30;
				Yoff -= 30;
				if( Xoff > 2 * Yoff ){
					bDirection = KP_EAST;
				}else if( Yoff > Xoff * 2 ){
					bDirection = KP_SOUTH;
				}else{
					bDirection = KP_SOUTHEAST;
				}
			}else{
				Yoff -= 30;
				Xoff = 30 - Xoff;
				if( Xoff > 2*Yoff ){
					bDirection = KP_WEST;
				}else if( Yoff > 2 * Xoff ){
					bDirection = KP_SOUTH;
				}else {
					bDirection = KP_SOUTHWEST;
				}
			}
		}else{
			if( Xoff > 30 ){
				Xoff -= 30;
				Yoff = 30 - Yoff;
				if( Xoff > 2 * Yoff ){
					bDirection = KP_EAST;
				}else if( Yoff > Xoff * 2 ){
					bDirection = KP_NORTH;
				}else{
					bDirection = KP_NORTHEAST;
				}
			}else{
				Yoff = 30 - Yoff;
				Xoff = 30 - Xoff;
				if( Xoff > 2*Yoff ){
					bDirection = KP_WEST;
				}else if( Yoff > 2 * Xoff ){
					bDirection = KP_NORTH;
				}else {
					bDirection = KP_NORTHWEST;
				}
			}
		}
	}

    CString msg( Message );

	DWORD dwNameColor = RGB(255,0,0);
    TFCPacket sending;
    sending << (RQ_SIZE)__EVENT_SHOUT;
    sending << (long)GetID();
    sending << (char)bDirection;
    sending << (long)dwColor;
    if( GetType() != U_PC ){
        sending << (char)1; // an NPC.
		dwNameColor = U_NPC_COLOR;
    }else{
        sending << (char)0; // not an NPC.
		Players *TargetPlayer = static_cast< Players * >(GetPlayer());
		if ( TargetPlayer->IsGod() ) dwNameColor = U_GOD_COLOR
		else dwNameColor = U_PC_COLOR;
    }
    sending << (CString &)msg;
    sending << (CString &)GetName( GetLang() );
	sending << (long)dwNameColor;
	
	TRACE( "\r\nSent color %u and direction %u\r\n", dwColor, bDirection );

    Broadcast::BCast( GetWL(), 24, sending );//BLBLBL 20 => 24 (pour que les paroles locales atteignent tout l'écran 1024)
}

// virtual
void Unit::SetDetectRange( BYTE ){};
BYTE Unit::GetDetectRange( void ){ return 0; };


//////////////////////////////////////////////////////////////////////////////////////////
Unit *Unit::GetIndentItem
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the item content of the item within the item whithin the item [...]
// of the indent item list.
// 
(
 DWORD *lpdwIndent
)
// Return: TemplateList <Unit>, The content of the last item in the indent list.
//////////////////////////////////////////////////////////////////////////////////////////
{				
	TemplateList <Unit> *tluBackpack;
	Unit *lpuUnit = this;
	BOOL boFound = TRUE;

	// If we have a null hierarchy list
	if( lpdwIndent[ 0 ] == 0 ){
		// return the user as the backpack owner
		return this;
	}

	int i = 0;
	if( lpdwIndent && lpuUnit ){

		// Start of indent list	
		do{
			// Get the backpack of the current item 
			tluBackpack = lpuUnit->GetBackpack();
			
			boFound = FALSE;
			// if it has a backpack
			if( tluBackpack ){
				// searches in the backpack		
				tluBackpack->Lock();
				tluBackpack->ToHead();
				while( tluBackpack->QueryNext() && !boFound ){
					// If this backpack has the next item in the indent list
					if( tluBackpack->Object()->GetID() == lpdwIndent[i] ){
						boFound = TRUE;
						lpuUnit = tluBackpack->Object();
					}
				}
				tluBackpack->Unlock();
			}
			i++;
		}while( lpdwIndent[i] && boFound );
	}

	if( boFound ){
		// packet the last units backpack
		return lpuUnit;
	}else{
		return NULL;
	}

}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::PacketBackpack
//////////////////////////////////////////////////////////////////////////////////////////
// Puts the content of the unit's backpack into a packet. Does NOT add the leading 
// packet type ID.
//
(
 TFCPacket &sending, bool gameop // The packet.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
}
//////////////////////////////////////////////////////////////////////////////////////////
double Unit::GetAC( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Unit's AC
// 
// Return: WORD, the AC.
//////////////////////////////////////////////////////////////////////////////////////////
{
    double dblValue = QueryBoost( STAT_AC );
    
    switch(GetType()){
	case U_OBJECT:{
		_item *obj = NULL;
		SendUnitMessage(MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &obj);
		if(obj){
			double ret = obj->armor.AC + dblValue;
            if( ret <= 0 ){ return 0; }else{ return ret; };
		}
    }break;
    case U_NPC:{
        MonsterStructure *monster = NULL;
        SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &monster );
        if( monster ){
			double ret = monster->AC + dblValue;
            if( ret <= 0 ){ return 0; }else{ return ret; };
        }
    } break;	
	}

return( 0 );
}
//////////////////////////////////////////////////////////////////////////////////////////
LPUSER_SKILL Unit::GetSkill
//////////////////////////////////////////////////////////////////////////////////////////
// This function returns the user-skill associated to the player.
// 
(
 DWORD dwSkill // The skill to query.
)
{ return NULL; }

//////////////////////////////////////////////////////////////////////////////////////////
WORD Unit::GetSkillPoints( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the number of skill points
//
{ return 0; };

void Unit::SetLastTeleport( WorldPos WL ){
}

WorldPos Unit::GetLastTeleport( void ){
	WorldPos wlPos = { 0, 0, 0 };
	return wlPos;
}

//////////////////////////////////////////////////////////////////////////////////////////
WorldPos Unit::OriginalWorldPos( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the first set position of the unit.
// 
// Return: WorldPos, The first set position of the unit.
//////////////////////////////////////////////////////////////////////////////////////////
{
	return wlOriginalPos;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::AddEffect
//////////////////////////////////////////////////////////////////////////////////////////
// Adds a spell effect to a unit.
// 
(
 LPUNIT_EFFECT lpSpellEffect // The spell effect.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	Lock();
	if( lptlEffectList == NULL ){
		lptlEffectList = new TemplateList <UNIT_EFFECT>;
	}	

	lptlEffectList->Lock();
	lptlEffectList->AddToTail( lpSpellEffect );
	lptlEffectList->Unlock();

    Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::RemoveEffect
//////////////////////////////////////////////////////////////////////////////////////////
// Removes a specific effect from a unit.
// 
(
 DWORD dwEffect // The effect ID to remove
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	Lock();
	if( lptlEffectList != NULL ){
		LPUNIT_EFFECT lpEffect;
		lptlEffectList->Lock();
		lptlEffectList->ToHead();
		while( lptlEffectList->QueryNext() ){
			lpEffect = lptlEffectList->Object();
			if( lpEffect->dwEffect == dwEffect ){
				// Send a destroy message to the effect
				if( lpEffect->lpFunc ){
					lpEffect->lpFunc( MSG_OnDestroy, dwEffect, this, NULL, NULL, lpEffect->lpData, NULL );
				}
				// Destroy the effect item
				lptlEffectList->DeleteAbsolute();
			}
		}
		lptlEffectList->Unlock();
		
		// If there are no more effects destroy the effect list.
		if( lptlEffectList->NbObjects() == 0 ){
			delete lptlEffectList;
			lptlEffectList = NULL;
		}
	}
	Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::DispellEffectWithFlag
//////////////////////////////////////////////////////////////////////////////////////////
//  Dispells an effect which has the specified binded flag
// 
(
 DWORD flagId // The binded flag to search for.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock autoLock( this );
    
    // If the functions hasn't been recursively called too many times.
    if( effectStackLevel >= MAX_EFFECT_STACK_LEVELS ){
        return;
    }

	// Query all effects	
	LPUNIT_EFFECT lpEffect;

	if( lptlEffectList == NULL ){
        return;
    }

    // Function called, augment stack level.
    effectStackLevel++;

    TemplateList < UNIT_EFFECT > tlCallList;
		
	lptlEffectList->Lock();
	lptlEffectList->ToHead();

	while( lptlEffectList->QueryNext() ){
		lpEffect = lptlEffectList->Object();

        if( lpEffect->bindedFlag == flagId ){
			if( lpEffect->lpFunc ){
				tlCallList.AddToTail( lpEffect );
			}
		}
    }
	lptlEffectList->Unlock();

	tlCallList.ToHead();
	while( tlCallList.QueryNext() ){
		lpEffect = tlCallList.Object();
		lpEffect->lpFunc( MSG_OnDispell, lpEffect->dwEffect, this, NULL, NULL, lpEffect->lpData, NULL );
	};

    // Function is ending, decrease stack level.
    effectStackLevel--;	
}

//////////////////////////////////////////////////////////////////////////////////////////
LPUNIT_EFFECT Unit::GetEffect
//////////////////////////////////////////////////////////////////////////////////////////
// Returns a specific effect.
// 
(
 DWORD dwEffect // The effect to get
)
// Return: LPUNIT_EFFECT, the returned spell effect, NULL if none found.
//////////////////////////////////////////////////////////////////////////////////////////
{
	Lock();
	LPUNIT_EFFECT lpEffect = NULL;
	if( lptlEffectList != NULL ){
		
		BOOL boFound = FALSE;
		lptlEffectList->Lock();
		lptlEffectList->ToHead();
		while( lptlEffectList->QueryNext() && !boFound ){
			lpEffect = lptlEffectList->Object();

			if( lpEffect->dwEffect == dwEffect ){
				boFound = TRUE;
			}
		}
		lptlEffectList->Unlock();

		if( !boFound ){
			lpEffect = NULL;
		}
	}
	Unlock();

	return lpEffect;
}
//////////////////////////////////////////////////////////////////////////////////////////
TemplateList<UNIT_EFFECT>* Unit::GetAllEffects( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the list of all spells on a unit
// 
// Return: TemplateList<UNIT_EFFECT>*, pointer to this list. NULL if no effects
//////////////////////////////////////////////////////////////////////////////////////////
{
	return lptlEffectList;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Unit::DestroyEffects( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Destroys every effects on the unit.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	Lock();

	LPUNIT_EFFECT lpEffect;

	if( lptlEffectList != NULL ){

		lptlEffectList->Lock();

		lptlEffectList->ToHead();
		while( lptlEffectList->QueryNext() ){
			lpEffect = lptlEffectList->Object();
			if( lpEffect->lpFunc ){
				lpEffect->lpFunc( MSG_OnDestroy, lpEffect->dwEffect, this, NULL, NULL, lpEffect->lpData, NULL );
			}
			// Destroy the effect item
			lptlEffectList->DeleteAbsolute();
		}
		lptlEffectList->Unlock();

		delete lptlEffectList;
		lptlEffectList = NULL;
	}

	Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::SendGlobalEffectMessage
//////////////////////////////////////////////////////////////////////////////////////////
// Sends a message to all effects on a unit.
// 
(
 BYTE bMsgType,     // Type of message to send.
 LPVOID lpMsgData,  // User data
 Unit *medium,      // ..
 Unit *target       // ..
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	try{
		LPUNIT_EFFECT lpEffect;
		TemplateList< UNIT_EFFECT > tlCallList;

		Lock();
		if( lptlEffectList != NULL ){
			lptlEffectList->Lock();

			// Add the effect to the call list.
			lptlEffectList->ToHead();
			while( lptlEffectList->QueryNext() ){		
				tlCallList.AddToTail( lptlEffectList->Object() );
			}
			lptlEffectList->Unlock();
		}    

		try{
			tlCallList.ToHead();
			while( tlCallList.QueryNext() ){
				lpEffect = tlCallList.Object();

				if ( lpEffect->lpFunc == NULL ){	//DC for GPs
					_LOG_DEBUG
						LOG_CRIT_ERRORS,
						"DC - GPs - lpEffect->lpFunc is a null pointer while SendGlobalEffectMessage."
					LOG_
				}else{								//DC for GPs
					lpEffect->lpFunc( bMsgType, lpEffect->dwEffect, this, NULL, NULL, lpEffect->lpData, NULL );
				}
			}

			Unlock();
		}catch(...){
			_LOG_DEBUG LOG_CRIT_ERRORS, "Crashed at Unit::SendGlobalEffectMessage, Call List handling.." LOG_
		}
	} catch(...){
		_LOG_DEBUG LOG_CRIT_ERRORS, "Crashed at Unit::SendGlobalEffectMessage" LOG_
		throw;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
void Unit::QueryEffects
//////////////////////////////////////////////////////////////////////////////////////////
// Queries all the effects and sends them the specific message.
// 
(
 BYTE bMsgType,		// Which effects are targetted and should be called.
 LPVOID lpUserData,	// The user data relative to this message.
 Unit *medium,      // The medium.
 Unit *target       // The target.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    CAutoLock autoLock( this );
    
    // If the functions hasn't been recursively called too many times.
    if( effectStackLevel < MAX_EFFECT_STACK_LEVELS ){
        // Function called, augment stack level.
        effectStackLevel++;

	    // Query all attack effects	
	    LPUNIT_EFFECT lpEffect;

	    if( lptlEffectList ){
		    TemplateList < UNIT_EFFECT > tlCallList;
		    
		    lptlEffectList->Lock();
		    lptlEffectList->ToHead();

		    while( lptlEffectList->QueryNext() ){
			    lpEffect = lptlEffectList->Object();

//			    TRACE( "\r\n--%u vs %u. Name: %s ID: %u", lpEffect->bEffectType, bMsgType, GetName( _DEFAULT_LNG ), GetStaticReference() );
                if( lpEffect->bEffectType == bMsgType ){
				    if( lpEffect->lpFunc ){
					    //lpEffect->lpFunc( bMsgType, lpEffect->wEffect, this, lpEffect->lpData, lpUserData );
					    tlCallList.AddToTail( lpEffect );
				    }
			    }
		    }
		    
		    lptlEffectList->Unlock();

		    tlCallList.ToHead();
		    while( tlCallList.QueryNext() ){
			    lpEffect = tlCallList.Object();
				if ( lpEffect == NULL ){				//DC for GPs
					_LOG_DEBUG
						LOG_CRIT_ERRORS,
						"DC - GPs - lpEffect is a null pointer while QueryEffects."
					LOG_
				}else if ( lpEffect->lpFunc == NULL ){	//DC for GPs
					_LOG_DEBUG
						LOG_CRIT_ERRORS,
						"DC - GPs - lpEffect->lpFunc is a null pointer while QueryEffects."
					LOG_
				}else{									//DC for GPs
					try
					{
				    lpEffect->lpFunc( bMsgType, lpEffect->dwEffect, this, medium, target, lpEffect->lpData, lpUserData );
					}
					catch(...)
					{
					_LOG_DEBUG
						LOG_CRIT_ERRORS,
						"DC - GPs - lpEffect->lpFunc is a FUBAR pointer while QueryEffects."
					LOG_
					}
				}
		    };
	    }

        // Function is ending, decrease stack level.
        effectStackLevel--;	
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::VerifyTimers( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Verifies all the timer effects on the unit
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( PickLock() ){
	    // Query all attack effects	
	    LPUNIT_EFFECT lpEffect;

	    TemplateList < UNIT_EFFECT > tlCallList;

	    if( lptlEffectList != NULL ){
		    lptlEffectList->Lock();
		    lptlEffectList->ToHead();

		    while( lptlEffectList->QueryNext() ){
			    lpEffect = lptlEffectList->Object();

			    if( lpEffect->dwTimer != 0 ){
				    if( lpEffect->dwTimer <= TFCMAIN::GetRound() ){
					    if( lpEffect->lpFunc ){						
						    tlCallList.AddToTail( lpEffect );
						    // Only remove timer, it will be destroyed later
						    lptlEffectList->Remove();
					    }else{
						    // destroy effect if it isn't going to trigger.
						    lptlEffectList->DeleteAbsolute();
					    }
				    }
			    }
		    }	

		    lptlEffectList->Unlock();

		    if( lptlEffectList->NbObjects() == 0 ){
			    delete lptlEffectList;
			    lptlEffectList = NULL;
		    }

		    tlCallList.ToHead();
		    while( tlCallList.QueryNext() ){
			    lpEffect = tlCallList.Object();
				if ( lpEffect == NULL ){				//DC for GPs
					_LOG_DEBUG
						LOG_CRIT_ERRORS,
						"DC - GPs - lpEffect is a null pointer while VerifyTimers."
					LOG_
				}else if ( lpEffect->lpFunc == NULL ){	//DC for GPs
					_LOG_DEBUG
						LOG_CRIT_ERRORS,
						"DC - GPs - lpEffect->lpFunc is a null pointer while VerifyTimers."
					LOG_
				}else{									//DC for GPs
					lpEffect->lpFunc( MSG_OnTimer, lpEffect->dwEffect, this, NULL, NULL, lpEffect->lpData, NULL );
					lpEffect->lpFunc( MSG_OnDestroy, lpEffect->dwEffect, this, NULL, NULL, lpEffect->lpData, NULL );
					tlCallList.DeleteAbsolute();	// Now destroy the effect item
				}
			}           
	    }	    
        Unlock();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
signed char Unit::GetRadiance( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Get's the unit's radiance
// 
// Return: signed char, the unit's radiance
//////////////////////////////////////////////////////////////////////////////////////////
{
    int nRadiance = cRadiance;

    // Add up any radiance boost.
    nRadiance += (int)( QueryBoost( STAT_RADIANCE ) );

    // Radiance cannot be less than -100% and not more than 100%
    nRadiance = nRadiance < -100 ? -100 : nRadiance;
    nRadiance = nRadiance >  100 ?  100 : nRadiance;

	return (char)( nRadiance );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::SetRadiance
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the radiance of a unit
// 
(
 signed char cNewRadiance // The new radiance
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	cRadiance = cNewRadiance;
}

//////////////////////////////////////////////////////////////////////////////////////////
DIR::MOVE Unit::QueryDirection
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the direction which the unit should go to reach wlTarget
// 
( 
 WorldPos wlTarget	// The target position.
)
// Return: DIR::MOVE, the direction the unit should move to
//////////////////////////////////////////////////////////////////////////////////////////
{
	DIR::MOVE direction;	
	if(wlTarget.X < WL.X) direction = DIR::west;
	if(wlTarget.X > WL.X) direction = DIR::east;

	if(wlTarget.Y < WL.Y && direction == DIR::west) direction = DIR::northwest;
	else if(wlTarget.Y < WL.Y && direction == DIR::east) direction = DIR::northeast;
	else if(wlTarget.Y < WL.Y) direction = DIR::north;
		if(wlTarget.Y > WL.Y && direction == DIR::west) direction = DIR::southwest;
	else if(wlTarget.Y > WL.Y && direction == DIR::east) direction = DIR::southeast;
	else if(wlTarget.Y > WL.Y) direction = DIR::south;
	
	return direction;
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Unit::UseSpellEnergy
//////////////////////////////////////////////////////////////////////////////////////////
// Uses spell energy, purely virtual
// 
(
 WORD wMana
)
// Return: BOOL, always FALSE
//////////////////////////////////////////////////////////////////////////////////////////
{
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::SetMark
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the marker
// 
(
 BYTE bNewMark // the current marker
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	bMarker = bNewMark;
}

//////////////////////////////////////////////////////////////////////////////////////////
BYTE Unit::GetMark( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Gets the current marker
// 
// Return: BYTE, the marker
//////////////////////////////////////////////////////////////////////////////////////////
{
	return bMarker;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::AddBoost
//////////////////////////////////////////////////////////////////////////////////////////
// Adds a boost to the unit
// 
(
 LPBOOST lpBoost // The boost structure
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	lptlBoostList->Lock();
	lptlBoostList->AddToTail( lpBoost );
	lptlBoostList->Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::AddBoost
//////////////////////////////////////////////////////////////////////////////////////////
// Adds a boost
// 
(
 DWORD dwBoostID,	// The boost ID
 WORD wStat,	// The stat to boost 
 int nBoost		// The boost to assign to the stat.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TRACE( "\r\nAdding boost ID %u for stat %u of value %d", 
        dwBoostID,
        wStat,
        nBoost
    );
    
    if( nBoost != 0 ){
        LPBOOST lpBoost = new BOOST;
	    lpBoost->dwBoostID = dwBoostID;
	    lpBoost->wStat = wStat;
        char str[ 14 ];
    
        // If formula was ok
        if( lpBoost->bfBoost.SetFormula( itoa( nBoost, str, 10 ) ) ){
            // Add boost.
            AddBoost( lpBoost );
        }else{
            _LOG_DEBUG
                LOG_DEBUG_LVL3,
                "Unit::AddBoost2| Boost %u's formula could not be set for stat %u: %s.",
                dwBoostID,
                wStat,
                str
            LOG_
    	    // Otherwise destroy it.
            delete lpBoost;
        }
    }else{
        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Unit::AddBoost2| Stat %u's boost %u on unit %s was 0 and not added.",
            wStat,
            dwBoostID,
            (LPCTSTR)GetName(_DEFAULT_LNG)
        LOG_
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::AddBoost
//////////////////////////////////////////////////////////////////////////////////////////
// Adds a boost
// 
(
 DWORD dwBoostID,             // The boost ID.
 WORD wStat,               // The boosted stat.
 const char *lpszFormula    // The boost formula.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPBOOST lpBoost = new BOOST;
	lpBoost->dwBoostID = dwBoostID;
	lpBoost->wStat = wStat;
    if( lpBoost->bfBoost.SetFormula( lpszFormula ) ){
        AddBoost( lpBoost );
    }else{
        _LOG_DEBUG
            LOG_DEBUG_LVL3,
            "Unit::AddBoost3| Boost %u's formula could not be set for stat %u: %s.",
            dwBoostID,
            wStat,
            lpszFormula
        LOG_

        delete lpBoost;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::RemoveBoost
//////////////////////////////////////////////////////////////////////////////////////////
// Removes a boost
// 
(
 DWORD dwBoostID // The boost ID to remove
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	if( lptlBoostList != NULL ){
		BOOL boFound = FALSE;

		lptlBoostList->Lock();
		lptlBoostList->ToHead();
		while( lptlBoostList->QueryNext()/* && !boFound*/ ){
			if( lptlBoostList->Object()->dwBoostID == dwBoostID ){
				lptlBoostList->DeleteAbsolute();
				//boFound = TRUE;
			}
		}
		lptlBoostList->Unlock();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::RemoveBoostFromStat
//////////////////////////////////////////////////////////////////////////////////////////
//  Removes all boosts associated to the specified stat.
// 
(
 WORD wStat // 
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	if( lptlBoostList != NULL ){
		BOOL boFound = FALSE;

		lptlBoostList->Lock();
		lptlBoostList->ToHead();
		while( lptlBoostList->QueryNext()/* && !boFound*/ ){
			if( lptlBoostList->Object()->wStat == wStat ){
				lptlBoostList->DeleteAbsolute();
				//boFound = TRUE;
			}
		}
		lptlBoostList->Unlock();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
LPBOOST Unit::GetBoost
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the boost structure of a given boost
// 
(
 DWORD dwBoostID // The boost ID to search for
)
// Return: LPBOOST, The boost structure. NULL if none found.
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPBOOST lpBoost = NULL;
	
	if( lptlBoostList != NULL ){
		BOOL boFound = FALSE;

		lptlBoostList->Lock();
		lptlBoostList->ToHead();
		while( lptlBoostList->QueryNext() && !boFound ){
			lpBoost = lptlBoostList->Object();
			if( lpBoost->dwBoostID == dwBoostID ){				
				boFound = TRUE;
			}
		}
		lptlBoostList->Unlock();
		// If boost wasn't found.
		if( !boFound ){
			// Set a NULL boost
			lpBoost = NULL;
		}
	}

	return lpBoost;
}

//////////////////////////////////////////////////////////////////////////////////////////
int Unit::QueryBoost
//////////////////////////////////////////////////////////////////////////////////////////
// Queries all the boosts associated with a given stat and returns the total.
// 
(
 WORD wStat // The stat.
)
// Return: int, the resulting boost
//////////////////////////////////////////////////////////////////////////////////////////
{
	double dblBoost = 0;

	if( lptlBoostList != NULL ){

		LPBOOST lpBoost;
		lptlBoostList->Lock();
		lptlBoostList->ToHead();
		while( lptlBoostList->QueryNext() ){
			lpBoost = lptlBoostList->Object();
            //TRACE( "\r\nBoosted stat %u vs wanted stat %u.", lpBoost->wStat, wStat );
			if( lpBoost->wStat == wStat ){
				dblBoost += lpBoost->bfBoost.GetBoost( this );
			}
		}
		lptlBoostList->Unlock();
	}

	return (int)( dblBoost );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::SetBoost
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the boost of an already existing boost.
// 
(
 DWORD dwBoostID,	// The boost ID to set.
 WORD wStat,	// The stat to boost, only used if boost didn't already exist.
 int nNewBoost	// The new boost.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	BOOL boFound = FALSE;

	if( lptlBoostList != NULL ){
		LPBOOST lpBoost;
		lptlBoostList->Lock();
		lptlBoostList->ToHead();
		while( lptlBoostList->QueryNext() && !boFound ){
			lpBoost = lptlBoostList->Object();

			if( lpBoost->dwBoostID == dwBoostID ){
                char str[ 14 ];
				lpBoost->bfBoost.SetFormula( itoa( nNewBoost, str, 10 ) );
				boFound = TRUE;
			}
		}
		lptlBoostList->Unlock();
	}

	// If skill wasn't set, create it.
	if( !boFound ){
		AddBoost( dwBoostID, wStat, nNewBoost );
	}
}


#define GET_STAT( stat ) WORD Unit::Get##stat\
( void ){\
	int nStat = Stat##stat\
	; nStat += QueryBoost( STAT_##stat\
	); nStat = nStat < 0 ? 0 : nStat;\
	return (WORD)nStat;\
}

WORD Unit::GetSTR( void ){
	int nStat = StatSTR;
	nStat += QueryBoost( STAT_STR );
	nStat = nStat < 0 ? 0 : nStat;
	return (WORD)nStat;
}


GET_STAT( INT )
GET_STAT( END )

GET_STAT( AGI )
GET_STAT( WIS )
GET_STAT( ATTACK )
GET_STAT( DODGE )
GET_STAT( LCK )

WORD Unit::GetTrueINT( void ){ return StatINT; }
WORD Unit::GetTrueEND( void ){ return StatEND; }
WORD Unit::GetTrueSTR( void ){ return StatSTR; }
WORD Unit::GetTrueAGI( void ){ return StatAGI; }
WORD Unit::GetTrueWIS( void ){ return StatWIS; }
WORD Unit::GetTrueATTACK( void ){ return StatATTACK; }
WORD Unit::GetTrueDODGE( void ){ return StatDODGE; }
WORD Unit::GetTrueLCK( void ) { return StatLCK; }

void Unit::SetINT( WORD bStat ){ StatINT = bStat; }
void Unit::SetEND( WORD bStat ){ StatEND = bStat; }
void Unit::SetSTR( WORD bStat ){ StatSTR = bStat; }
void Unit::SetAGI( WORD bStat ){ StatAGI = bStat; }
void Unit::SetWIS( WORD bStat ){ StatWIS = bStat; }
void Unit::SetATTACK( WORD bStat ){ StatATTACK = bStat; }
void Unit::SetDODGE( WORD bStat ){ StatDODGE = bStat; }
void Unit::SetLCK( WORD bStat ) { StatLCK = bStat; }

// asteryth pvp ranking
int Unit::GetTotalDeathNumber( void ){ return TotalDeathNumber; }
int Unit::GetTotalKillNumber( void ){ return TotalKillNumber; }
int Unit::GetCurrentDeathNumber( void ){ return CurrentDeathNumber; }
int Unit::GetCurrentKillNumber( void ){ return CurrentKillNumber; }
int Unit::GetBestSerieMurder( void ){ return BestSerieMurder; }
int Unit::GetCurrentSerieMurder( void ){ return CurrentSerieMurder; }
int Unit::GetCurrentPvpPoint( void ){ return CurrentPvpPoint; }

void Unit::SetTotalDeathNumber( int bStat )	{ TotalDeathNumber = bStat;	}
void Unit::SetTotalKillNumber( int bStat )	{ TotalKillNumber = bStat;}
void Unit::SetCurrentDeathNumber( int bStat ){ CurrentDeathNumber = bStat; }
void Unit::SetCurrentKillNumber( int bStat ){ CurrentKillNumber = bStat; }
void Unit::SetBestSerieMurder( int bStat ){ BestSerieMurder = bStat; }
void Unit::SetCurrentSerieMurder( int bStat ){ CurrentSerieMurder = bStat; }
void Unit::SetCurrentPvpPoint( int bStat ){ CurrentPvpPoint = bStat; }
/*
**
*/
int Unit::GetGuildID( void ){ return GuildID; }
void Unit::SetGuildID( int bStat ){ GuildID = bStat; }

void Unit::SetUndead( WORD wUndead ){};
WORD Unit::GetUndead( void ){ return 0; };


//////////////////////////////////////////////////////////////////////////////////////////
void BinaryToString
//////////////////////////////////////////////////////////////////////////////////////////
// Converts a binary buffer into a user readable string (in hexadecimal format).
// 
(
 LPBYTE lpBuffer,	// The binary buffer
 LPBYTE lpString,	// Pointer to the resulting string data, must be large enough (dwBufferSize * 2) !.
 DWORD dwBufferSize // The buffer size
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	DWORD i;
	BYTE bData;

	for( i = 0; i < dwBufferSize * 2; i++ ){
		
		// Fetch first 4 bits
		if( !( i % 2 ) ){
			bData = (BYTE)( lpBuffer[ i >> 1 ] & 0xF0 ) >> 4;
		}
		// Fetch second 4 bits
		else{
			bData = (BYTE)( lpBuffer[ i >> 1 ] & 0x0F );
		}

		switch( bData ){
		case 0:  lpString[ i ] = '0'; break;
		case 1:  lpString[ i ] = '1'; break;
		case 2:  lpString[ i ] = '2'; break;
		case 3:  lpString[ i ] = '3'; break;	
		case 4:  lpString[ i ] = '4'; break;
		case 5:  lpString[ i ] = '5'; break;
		case 6:  lpString[ i ] = '6'; break;
		case 7:  lpString[ i ] = '7'; break;	
		case 8:  lpString[ i ] = '8'; break;
		case 9:  lpString[ i ] = '9'; break;
		case 10: lpString[ i ] = 'A'; break;
		case 11: lpString[ i ] = 'B'; break;	
		case 12: lpString[ i ] = 'C'; break;
		case 13: lpString[ i ] = 'D'; break;
		case 14: lpString[ i ] = 'E'; break;
		case 15: lpString[ i ] = 'F'; break;	
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////
// Add a query to the batch requests
#define ADD_QUERY	{ \
	LPSQL_REQUEST lpSql = new SQL_REQUEST;\
	lpSql->csQuery = csQuery;\
	lptlSQLRequests->AddToTail( lpSql );\
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Unit::SaveEffects
//////////////////////////////////////////////////////////////////////////////////////////
// Saves all effects binded with the unit into the provided vdArray
// 
(
 TemplateList< SQL_REQUEST > *lptlSQLRequests,
 DWORD dwBaseOwnerID
)
//////////////////////////////////////////////////////////////////////////////////////////
{		
	CString csQuery;
	BOOL boDBError = FALSE;
		
	TemplateList <UNIT_EFFECT> *lptlEffectList = GetAllEffects();

	Lock();
		
	if( lptlEffectList != NULL ){
		LPUNIT_EFFECT lpEffect;
					
		lptlEffectList->Lock();
		lptlEffectList->ToHead();
		

		while( lptlEffectList->QueryNext() ){
			lpEffect = lptlEffectList->Object();

            DATA_SAVE sSaveData;
		    ZeroMemory( &sSaveData, sizeof( DATA_SAVE ) );

			if( lpEffect->lpFunc != NULL ){
				lpEffect->lpFunc( MSG_OnSavePlayer, lpEffect->dwEffect,
					this, NULL, NULL, lpEffect->lpData, &sSaveData );
			}

			if( sSaveData.bSave != DO_NOT_SAVE ){
				
				if( sSaveData.bBufferSize > 0 && sSaveData.bBufferSize < 128 ){
					// Alloc buffer and make conversion.
					BYTE lpbTextData[ 256 ]; // Maximum SQL string length
                    TRACE( "\r\nBuffer size %u", sSaveData.bBufferSize );
					BinaryToString( sSaveData.lpbData, lpbTextData, sSaveData.bBufferSize );
                    lpbTextData[ sSaveData.bBufferSize * 2 ] = 0;
                    delete sSaveData.lpbData;

				    csQuery.Format( 
					    "INSERT INTO Effects(OwnerID,BaseOwnerID,EffectID,EffectType,Timer,EffectData,TotalDuration,BindedSpellID,BindedFlagID) VALUES ( "
					    "%d,"	// OwnerID
                        "%d,"   // BaseOwnerID
					    "%d,"	// EffectID
					    "%d,"	// EffectType
					    "%d,"	// Timer
					    "'%s'," // EffectData
                        "%d,"   // TotalDuration
                        "%u,"   // BindedSpellID
                        "%u)",  // BindedFlagID
					    GetID(),
                        dwBaseOwnerID,
					    lpEffect->dwEffect,
					    lpEffect->bEffectType,
					    ( lpEffect->dwTimer - TFCMAIN::GetRound() ),
					    lpbTextData,
                        lpEffect->dwTotalDuration,
                        lpEffect->bindedSpellID,
                        lpEffect->bindedFlag
				    );

                    _LOG_DEBUG
                        LOG_DEBUG_LVL3,
                        "Saved effect %u, bufsize=%u, lpbData=0x%x, bSave=%u",
                        lpEffect->dwEffect,
	                    sSaveData.bBufferSize,
	                    sSaveData.lpbData,
	                    sSaveData.bSave
                    LOG_

                    ADD_QUERY
                }
			}			
		}

		lptlEffectList->Unlock();
	}

	Unlock();

	return boDBError;
}


//////////////////////////////////////////////////////////////////////////////////////////
void StringToBinary
//////////////////////////////////////////////////////////////////////////////////////////
// Converts an hexadecimal data string into a binary buffer
// 
(
 LPBYTE lpszString, // The string to convert from.
 LPBYTE lpbBuffer,	// The resulting buffer. Must be able to hold dwSize / 2 bytes.
 DWORD dwSize		// The size of the string data.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	DWORD i;	

	for( i = 0; i < ( dwSize >> 1 ); i++ ){
		// First byte is the higher 4 bits
		switch( lpszString[ i << 1 ] ){
		case '0': lpbBuffer[ i ] = 0x0 << 4; TRACE("0"); break;
		case '1': lpbBuffer[ i ] = 0x1 << 4; TRACE("1"); break;
		case '2': lpbBuffer[ i ] = 0x2 << 4; TRACE("2"); break;
		case '3': lpbBuffer[ i ] = 0x3 << 4; TRACE("3"); break;
		case '4': lpbBuffer[ i ] = 0x4 << 4; TRACE("4"); break;
		case '5': lpbBuffer[ i ] = 0x5 << 4; TRACE("5"); break;
		case '6': lpbBuffer[ i ] = 0x6 << 4; TRACE("6"); break;
		case '7': lpbBuffer[ i ] = 0x7 << 4; TRACE("7"); break;
		case '8': lpbBuffer[ i ] = 0x8 << 4; TRACE("8"); break;
		case '9': lpbBuffer[ i ] = 0x9 << 4; TRACE("9"); break;
		case 'A': lpbBuffer[ i ] = 0xA << 4; TRACE("a"); break;
		case 'B': lpbBuffer[ i ] = 0xB << 4; TRACE("b"); break;
		case 'C': lpbBuffer[ i ] = 0xC << 4; TRACE("c"); break;
		case 'D': lpbBuffer[ i ] = 0xD << 4; TRACE("d"); break;
		case 'E': lpbBuffer[ i ] = 0xE << 4; TRACE("e"); break;
		case 'F': lpbBuffer[ i ] = 0xF << 4; TRACE("f"); break;
		default:  lpbBuffer[ i ] = 0x0 << 4; TRACE("-"); break;
		}
		// Second byte is the lower 4 bits
		switch( lpszString[ ( i << 1 ) + 1 ] ){
		case '0': lpbBuffer[ i ] |= 0x0; TRACE("0"); break;
		case '1': lpbBuffer[ i ] |= 0x1; TRACE("1"); break;
		case '2': lpbBuffer[ i ] |= 0x2; TRACE("2"); break;
		case '3': lpbBuffer[ i ] |= 0x3; TRACE("3"); break;
		case '4': lpbBuffer[ i ] |= 0x4; TRACE("4"); break;
		case '5': lpbBuffer[ i ] |= 0x5; TRACE("5"); break;
		case '6': lpbBuffer[ i ] |= 0x6; TRACE("6"); break;
		case '7': lpbBuffer[ i ] |= 0x7; TRACE("7"); break;
		case '8': lpbBuffer[ i ] |= 0x8; TRACE("8"); break;
		case '9': lpbBuffer[ i ] |= 0x9; TRACE("9"); break;
		case 'A': lpbBuffer[ i ] |= 0xA; TRACE("a"); break;
		case 'B': lpbBuffer[ i ] |= 0xB; TRACE("b"); break;
		case 'C': lpbBuffer[ i ] |= 0xC; TRACE("c"); break;		
		case 'D': lpbBuffer[ i ] |= 0xD; TRACE("d"); break;
		case 'E': lpbBuffer[ i ] |= 0xE; TRACE("e"); break;
		case 'F': lpbBuffer[ i ] |= 0xF; TRACE("f"); break;
		default:  lpbBuffer[ i ] |= 0x0; TRACE("-"); break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::LoadEffects
//////////////////////////////////////////////////////////////////////////////////////////
// Loads the effects earlier saved inside the given vdArray
// 
(
 cODBCMage &Connection,
 DWORD dwBaseOwnerID
)
//////////////////////////////////////////////////////////////////////////////////////////
{


	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
	const INT DB_EffectID		= 1;
	const INT DB_EffectType		= 2;
	const INT DB_Timer			= 3;
	const INT DB_EffectData		= 4;
    const INT DB_TotalDuration	= 5;
    const INT DB_BindedSpellID  = 6;
    const INT DB_BindedFlagID   = 7;
	


	CString csQuery;

	csQuery.Format(	"SELECT EffectID, EffectType, Timer, EffectData, TotalDuration, BindedSpellID, BindedFlagID FROM Effects WHERE OwnerID=%d AND BaseOwnerID=%d", GetID(), dwBaseOwnerID );
	
//DC	As USERS_DSN, USERS_USER, USERS_PWD are unknown at this level, we do not implement RetryConnection at this time.
//DC	BOOL SendRequestSuccess = true;
//DC	if ( !Connection.SendRequest( (LPCTSTR)csQuery ) ){
//DC		  if ( !Connection.RetryConnection(USERS_DSN, USERS_USER, USERS_PWD,
//DC			  (LPCTSTR)csQuery,0) ){
//DC			SendRequestSuccess = false;
//DC		  }
//DC	}
//DC	if( SendRequestSuccess ){	

	if( Connection.SendRequest( (LPCTSTR)csQuery ) ){
		// Scroll through the fetched records.
		while( Connection.Fetch() ){
            LOAD_EFFECT_DATA eff;
			char szData[ 256 ];

            Connection.GetDWORD ( DB_EffectID, &eff.effectId );
            Connection.GetWORD( DB_EffectType, &eff.effectType );
			Connection.GetDWORD( DB_Timer, &eff.effectTimer );
			Connection.GetString( DB_EffectData, (LPTSTR)szData, 256 );
            Connection.GetSDWORD( DB_TotalDuration, (long*)&eff.totalDuration );
            Connection.GetDWORD( DB_BindedSpellID, &eff.bindedSpellId );
            Connection.GetDWORD( DB_BindedFlagID, &eff.bindedFlagId );
            eff.effectData = szData;

		    deferredEffectLoad.push_back( eff );
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::DeferredLoadEffects( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Loads the unit effects
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    Lock();

    list< LOAD_EFFECT_DATA >::iterator i;

    for( i = deferredEffectLoad.begin(); i != deferredEffectLoad.end(); i++ ){
        LPUNIT_EFFECT lpEffect = new UNIT_EFFECT;
	                    
        lpEffect->dwTimer = (*i).effectTimer TDELAY;
        lpEffect->dwEffect = (*i).effectId;
        lpEffect->bEffectType = (BYTE)(*i).effectType;
        lpEffect->dwTotalDuration = (*i).totalDuration;
        lpEffect->bindedSpellID = (*i).bindedSpellId;
        lpEffect->bindedFlag = (*i).bindedFlagId;

	    DWORD dwStrLen = (*i).effectData.GetLength();

	    // Query the spell effect manager to get the binded effect function.
	    lpEffect->lpFunc = UnitEffectManager::GetEffectProc( lpEffect->dwEffect );
	    
	    if( dwStrLen > 0 ){
            TRACE( "\r\nString len %u", dwStrLen );
            BYTE lpszData[ 512 ];

            strcpy( (char *)lpszData, (*i).effectData );
            
            DATA_SAVE sSaveData;
            ZeroMemory( &sSaveData, sizeof( DATA_SAVE ) );
		    // If there was string data, convert it
		    sSaveData.bBufferSize = (BYTE)( dwStrLen / 2 );
		    sSaveData.lpbData = new BYTE[ dwStrLen / 2 + 1 ];
		    
		    TRACE( "String: %s.", lpszData );
            StringToBinary( lpszData, sSaveData.lpbData, dwStrLen );
		    // Then tell the particular effect that data has been loaded.
		    if( lpEffect->lpFunc != NULL ){
                _LOG_DEBUG
                    LOG_DEBUG_LVL3,
                    "Loading effect %u with data %s.",
                    lpEffect->dwEffect,
                    lpszData
                LOG_

			    lpEffect->lpFunc( MSG_OnLoadPlayer, lpEffect->dwEffect, this, NULL, NULL, lpEffect, &sSaveData );

			    TRACE( "\r\nAdding effect %u type %u triggering at %u (Current round: %u)",
				    lpEffect->dwEffect,
				    lpEffect->bEffectType,
				    lpEffect->dwTimer,
				    TFCMAIN::GetRound()
			    );

			    // Add the effect to the player
			    AddEffect( lpEffect );

            }else{
                _LOG_DEBUG
                    LOG_DEBUG_LVL1,
                    "Effect function for effect %u does not exist.",
                    lpEffect->dwEffect
                LOG_
            }
		    
		    delete sSaveData.lpbData;
	    }
    }
    deferredEffectLoad.clear();

    if( lptlBoostList != NULL ){
        lptlBoostList->Lock();

        list< LOAD_BOOST_DATA >::iterator q;
        for( q = deferredBoostLoad.begin(); q != deferredBoostLoad.end(); q++ ){
		    LPBOOST lpBoost = new BOOST;

		    lpBoost->dwBoostID = (*q).dwBoostID;
		    lpBoost->wStat = (*q).wStat;

            // If formula was ok.
            if( lpBoost->bfBoost.SetFormula( (*q).boostFormula ) ){
			    // Add the boost.
			    lptlBoostList->AddToTail( lpBoost );
            }else{
                // otherwise remove boost.
                delete lpBoost;
            }
        }
        lptlBoostList->Unlock();
    }
    deferredBoostLoad.clear();

    if( GetType() == U_PC ){
        Character *pc = static_cast< Character * >( this );

        pc->TraceExhaust();
    }

    DealExhaust( loadAttackExhaust, loadMentalExhaust, loadMoveExhaust );

    loadAttackExhaust = loadMentalExhaust = loadMoveExhaust = 0;

    if( GetType() == U_PC ){
        Character *pc = static_cast< Character * >( this );

        pc->TraceExhaust();

        // If the player has already remorted.
        if( ViewFlag( __FLAG_NUMBER_OF_REMORTS ) != 0 ){
            WorldPos wlPos = { 0, 0, 0 };
            // Cast the permanent remort spell.
            SpellMessageHandler::ActivateSpell( __SPELL_REMORT_AURA, this, NULL, NULL, wlPos );
        }

        // AddOn spell
        if( ViewFlag( __FLAG_ADDON_STORYLINE_PROGRESS ) >= 4 ){
            WorldPos wlPos = { 0, 0, 0 };
            // Cast the permanent wrath of the ancients spell.
            SpellMessageHandler::ActivateSpell( __SPELL_WRATH_OF_THE_ANCIENTS, this, NULL, this, wlPos );           
        }
    }


    Unlock();
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Unit::SaveBoosts
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
 TemplateList< SQL_REQUEST > *lptlSQLRequests,
 DWORD dwBaseOwnerID
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	LPBOOST lpBoost;
	CString csQuery;
	BOOL boDBError = FALSE;
		
	if( lptlBoostList != NULL ){
		
		lptlBoostList->Lock();
		lptlBoostList->ToHead();

		while( lptlBoostList->QueryNext() && !boDBError ){
			lpBoost = lptlBoostList->Object();

			csQuery.Format(
				"INSERT INTO Boosts(OwnerID,BaseOwnerID,BoostID,Stat,Boost) VALUES ( "
				"%d,"	// OwnerID
				"%d,"   // BaseOwnerID
                "%d,"	// BoostID
				"%d,"	// Stat
				"'%s'"	// Boost
				" )",
				GetID(),
                dwBaseOwnerID,
				lpBoost->dwBoostID,
				lpBoost->wStat,
				lpBoost->bfBoost.GetOriginalFormula()
			);

			ADD_QUERY
		}
		lptlBoostList->Unlock();
	}


	return boDBError;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::LoadBoosts
//////////////////////////////////////////////////////////////////////////////////////////
// Loads the boosts from a a given array and stores them on this unit.
// 
(
 cODBCMage &Connection,
 DWORD dwBaseOwnerID
)
//////////////////////////////////////////////////////////////////////////////////////////
{	


	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
	const INT DB_BoostID = 1;
	const INT DB_Stat = 2;
	const INT DB_Boost = 3;


	
	CString csQuery;
	csQuery.Format(	"SELECT BoostID, Stat, Boost FROM Boosts WHERE OwnerID=%d AND BaseOwnerID=%d", GetID(), dwBaseOwnerID );
	    
    lptlBoostList->Lock();
    lptlBoostList->AnnihilateList();
    lptlBoostList->Unlock();

	if( Connection.SendRequest( (LPCTSTR)csQuery ) ){
//DC	BOOL SendRequestSuccess = true;
//DC	if ( !Connection.SendRequest( (LPCTSTR)csQuery ) ){
//DC		  if ( !Connection.RetryConnection(USERS_DSN, USERS_USER, USERS_PWD,
//DC			  (LPCTSTR)csQuery,0) ){
//DC			SendRequestSuccess = false;
//DC		  }
//DC	}

//DC	As USERS_DSN, USERS_USER, USERS_PWD are unknown at this level, we do not implement RetryConnection at this time.

		// Scroll through the fetched records.
		while( Connection.Fetch() ){
			LOAD_BOOST_DATA lbd;
            char str[ 256 ];

			Connection.GetDWORD(  DB_BoostID, &lbd.dwBoostID );
			Connection.GetWORD(   DB_Stat,    &lbd.wStat );
			Connection.GetString( DB_Boost,  str, 256 );
            
            lbd.boostFormula = str;

            deferredBoostLoad.push_back( lbd );
		}
	}	
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Unit::SaveFlags
//////////////////////////////////////////////////////////////////////////////////////////
// 
// 
(
 TemplateList< SQL_REQUEST > *lptlSQLRequests,
 DWORD dwBaseOwnerID
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	CString csQuery;
	BOOL boDBError = FALSE;
//	LPINT FlagValues;
//	UINT *FlagIDs;
//	UINT  FlagLength;

	// First save the dynamic flags.
	//FlagLength = GetFlags(&FlagValues, &FlagIDs);
    FlagCont cFlags;
    GetFlags( cFlags );

    FlagCont::iterator i;
	
	for( i = cFlags.begin(); i != cFlags.end(); i++ )	{
		
		csQuery.Format( 
			"INSERT INTO Flags(OwnerID,BaseOwnerID,FlagID,FlagValue,DynamicFlag) VALUES ("
			"%d,"	// OwnerID
			"%d,"   // BaseOwnerID
            "%u,"	// FlagID
			"%d,"	// FlagValue
			"1"		// DynamicFlag
			" )",
			GetID(),
            dwBaseOwnerID,
			(*i).first,   // FlagID
			(*i).second   // FlagValue
		);
	
		ADD_QUERY
	}
    
	return boDBError;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::LoadFlags
//////////////////////////////////////////////////////////////////////////////////////////
// Load the flags associated to a unit.
//
(
 cODBCMage &Connection,
 DWORD dwBaseOwnerID
)
//////////////////////////////////////////////////////////////////////////////////////////
{


	//////////////////////////////////////////////////////////////////////////////////////////
	// steph ajout de INT
	//////////////////////////////////////////////////////////////////////////////////////////
	const INT DB_FlagID			= 1;
	const INT DB_FlagValue		= 2;
	const INT DB_DynamicFlag	= 3;


	CString csQuery;
	DWORD dwID;
	long lValue;
	BYTE  bType;


	csQuery.Format( "SELECT FlagID, FlagValue, DynamicFlag FROM Flags WHERE OwnerID=%d AND BaseOwnerID=%d", GetID(), dwBaseOwnerID );

	if( Connection.SendRequest( (LPCTSTR)csQuery ) ){
//DC	BOOL SendRequestSuccess = true;
//DC	if ( !Connection.SendRequest( (LPCTSTR)csQuery ) ){
//DC		  if ( !Connection.RetryConnection(USERS_DSN, USERS_USER, USERS_PWD,
//DC			  (LPCTSTR)csQuery,0) ){
//DC			SendRequestSuccess = false;
//DC		  }
//DC	}

//DC	As USERS_DSN, USERS_USER, USERS_PWD are unknown at this level, we do not implement RetryConnection at this time.

		// Fetch the found record.
		while( Connection.Fetch() ){
			Connection.GetDWORD( DB_FlagID, &dwID );
			Connection.GetSDWORD( DB_FlagValue, &lValue );
			Connection.GetBYTE ( DB_DynamicFlag, &bType );
            
			// If found flag is a dynamic flag.
			//if( bType == 1 ){
				SetFlag( dwID, lValue );
			//}else{
			//	// If unit is a PC
			//	if( UnitType == U_PC ){
			//		Character *lpChar = static_cast< Character * >( this );
			//		lpChar->SetStaticFlag( (UINT)dwID, (int)dwValue );
			//	}
			//}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Unit::CanAttack( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Determines if a unit can attack
// 
// Return: BOOL, TRUE if this unit can attack.
//////////////////////////////////////////////////////////////////////////////////////////
{
	return FALSE;
}
void Unit::SetAttack( BOOL boCanAttack ){};

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::SetBlock
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the block
// 
(
 BYTE bNewBlock
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	bBlock = bNewBlock;
}

//////////////////////////////////////////////////////////////////////////////////////////
BYTE Unit::GetBlock( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the block
// 
// Return: BYTE, the block
//////////////////////////////////////////////////////////////////////////////////////////
{
	return bBlock;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::SetUnderBlock
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the under block
// 
(
 BYTE bBlock
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	if (bCurrentBlocking!=__BLOCK_NONE && bBlock== __BLOCK_NONE) {
		WorldPos wpTemp;
		wpTemp = this->GetWL();
	}
	bCurrentBlocking = bBlock;
}

//////////////////////////////////////////////////////////////////////////////////////////
BYTE Unit::GetUnderBlock( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the under block
// 
// Return: BYTE, The under block
//////////////////////////////////////////////////////////////////////////////////////////
{
	return bCurrentBlocking;
}

// Used by Creatures.cpp
//////////////////////////////////////////////////////////////////////////////////////////
void Unit::SetCanMove
//////////////////////////////////////////////////////////////////////////////////////////
// Sets if creature can move or stands still.
// 
(
 BOOL boNewCanMove
)
//////////////////////////////////////////////////////////////////////////////////////////
{}

//////////////////////////////////////////////////////////////////////////////////////////
BOOL Unit::CanMove( void )
//////////////////////////////////////////////////////////////////////////////////////////
// TRUE if creature has the ability to actually move!!
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
WORD Unit::GetLang( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Units return the default language.
// 
// Return: WORD, the default language.
//////////////////////////////////////////////////////////////////////////////////////////
{
    return IntlText::GetDefaultLng();
}

//////////////////////////////////////////////////////////////////////////////////////////
BYTE Unit::GetStatus( void )
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
{
    return bStatus;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::SetStatus
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the status.
// 
(
 BYTE bNewStatus // The status
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    bStatus = bNewStatus;
}

//////////////////////////////////////////////////////////////////////////////////////////
int Unit::GetWeight( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns the weight of the unit.
// 
// Return: int, the weight.
//////////////////////////////////////////////////////////////////////////////////////////
{
    int nWeight = 0;

    if( GetType() == U_OBJECT ){
        _item *lpItem = NULL;

        SendUnitMessage( MSG_OnGetUnitStructure, NULL, NULL, NULL, NULL, &lpItem );

        nWeight = lpItem->size;
    }

    return nWeight;
}

//////////////////////////////////////////////////////////////////////////////////////////
int Unit::GetMaxWeight( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Returns 0
// 
// Return: int, 
//////////////////////////////////////////////////////////////////////////////////////////
{
    return 0;
}

void Unit::SetPrivateTalk( BOOL boPrivateTalk ){
}

BOOL Unit::IsPrivateTalk( void ){
    return FALSE;
}

void Unit::SendPrivateMessage( CString &csMessage, Unit *lpuUnit, DWORD dwColor ){};


//////////////////////////////////////////////////////////////////////////////////////////
void Unit::PacketUnitInformation
//////////////////////////////////////////////////////////////////////////////////////////
// Appends a unit's information to a packet which needs it, like Move or AddObject
// 
(
 TFCPacket &sending // The packet to append the unit's data to.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
	sending << (short)GetAppearance();
	sending << (long) GetID();
	sending << (char) GetRadiance();
    sending << (char) GetStatus();
    sending << (char) (GetMaxHP() == 0 ? 0 : GetHP() * 100 / GetMaxHP() );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::PacketPuppetInfo
//////////////////////////////////////////////////////////////////////////////////////////
//  Packets packet information for a normal unit.
// 
(
 TFCPacket &sending // 
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    // Fill empty puppet packet.
    sending << (RQ_SIZE)RQ_PuppetInformation;
    sending << (long) GetID();
    sending << (short)0;
    sending << (short)0;
    sending << (short)0;
    sending << (short)0;
    sending << (short)0;
    sending << (short)0;
    sending << (short)0;
    sending << (short)0;
    sending << (short)0;
    sending << (short)0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::DealExhaust
//////////////////////////////////////////////////////////////////////////////////////////
//  Deals exhaust
// 
(
 DWORD dwAttack, // Attack exhaust in milliseconds
 DWORD dwMental, // Mental exhaust in milliseconds
 DWORD dwMove    // Move exhaust in milliseconds
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    EXHAUST sExhaust = GetExhaust();

    // If previous mental exhaustion is off.
    if( sExhaust.mental < TFCMAIN::GetRound() ){
        // Create a new exhaust.
        sExhaust.mental = TFCMAIN::GetRound() + ( dwMental MILLISECONDS );
    }else{
        DWORD dwNewExhaust = (DWORD)dwMental MILLISECONDS;
        // If old exhaust is smaller than this spell's induced exhaust
        if( sExhaust.mental - TFCMAIN::GetRound() < dwNewExhaust ){
            // Set exhaust to spell exhaust.
            sExhaust.mental = TFCMAIN::GetRound() + dwNewExhaust;
        }
    }
    // If previous move exhaustion is off.
    if( sExhaust.move < TFCMAIN::GetRound() ){
        // Create a new exhaust.
        sExhaust.move = TFCMAIN::GetRound() + ( dwMove MILLISECONDS );
    }else{
        DWORD dwNewExhaust = dwMove MILLISECONDS;
        // If old exhaust is smaller than this spell's induced exhaust
        if( sExhaust.move - TFCMAIN::GetRound() < dwNewExhaust ){
            // Set exhaust to spell exhaust.
            sExhaust.move = TFCMAIN::GetRound() + dwNewExhaust;
        }
    }
	
    // If previous mental exhaustion is off.
    if( sExhaust.attack < TFCMAIN::GetRound() ){
        // Create a new exhaust.
        sExhaust.attack = TFCMAIN::GetRound() + ( dwAttack MILLISECONDS );
    }else{
        DWORD dwNewExhaust = dwAttack MILLISECONDS;
        // If old exhaust is smaller than this spell's induced exhaust
        if( sExhaust.attack - TFCMAIN::GetRound() < dwNewExhaust ){
            // Set exhaust to spell exhaust.
            sExhaust.attack = TFCMAIN::GetRound() + dwNewExhaust;
        }
    }

//	_LOG_DEBUG LOG_DEBUG_LVL4, "Setting new exhaust Mental %u,Move %u,Atk %u.", sExhaust.mental,sExhaust.move,sExhaust.attack LOG_//BLBLBL ajouté un peu d'info

    // Set new exhaust.
    SetExhaust( sExhaust );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::BroadcastPopup
//////////////////////////////////////////////////////////////////////////////////////////
//  Broadcasts that the unit just appeared.
// 
(
 WorldPos wlAppearPos,
 int nBroadcast //BLBL dans le prototype de la fonction, il semble que la valeur soit mise à true par défaut !
				//(ce qui est rassurant dans un sens)
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    TFCPacket sending;
    // Packet popup information
    PacketPopup( wlAppearPos, sending );

    // If we broadcast popup
    if( nBroadcast ){
        Broadcast::BCast( wlAppearPos, _DEFAULT_RANGE, sending, GetInvisibleQuery() );
	/*	_LOG_DEBUG
            LOG_MISC_1,
            "Broadcasted pop up at %d, %d, %d",
            wlAppearPos.X,
			wlAppearPos.Y,
			wlAppearPos.world            
        LOG_*/
    }else{
        SendPlayerMessage( sending );
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::PacketPopup
//////////////////////////////////////////////////////////////////////////////////////////
//  Puts the popup information into a packet, with header.
// 
(
 WorldPos wlAppearPos, // The appearance position
 TFCPacket &sending    // The packet to put the information in.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    sending << (RQ_SIZE)10004;
    sending << (short)wlAppearPos.X;
    sending << (short)wlAppearPos.Y;
    sending << (short)GetAppearance();
    sending << (long)GetID();
    sending << (char)GetRadiance();
    sending << (char)GetStatus();
    sending << (char)( GetMaxHP() == 0 ? 0 : GetHP() * 100 / GetMaxHP() );
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::SetKarma
//////////////////////////////////////////////////////////////////////////////////////////
//  Sets the user's karma to a new value.
// 
(
 int nInt // The new karma value.
)
//////////////////////////////////////////////////////////////////////////////////////////
{ 
    // If karma went down,
    if( nInt < nKarma ){
        SendSystemMessage( _STR( 7127, GetLang() ) );

        _LOG_PC
            LOG_MISC_1,
            "Player %s's karma went down to %d",
            (LPCTSTR)GetName( GetLang() ),
            nInt
        LOG_
    }
    // If karma went up.
    else if( nInt > nKarma ){
        SendSystemMessage( _STR( 7126, GetLang() ) );
        _LOG_PC
            LOG_MISC_1,
            "Player %s's karma went up to %d",
            (LPCTSTR)GetName( GetLang() ),
            nInt
        LOG_
    }
    nKarma = nInt; 
}

//////////////////////////////////////////////////////////////////////////////////////////
bool Unit::QueryInvisible::SendPacketTo
//////////////////////////////////////////////////////////////////////////////////////////
//  Determines whether the packet can be sent to the target player or not. Checks
// for invisibility flag.
// 
(
 Unit *target
)
// Return: bool, true or false. 
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( unit == target ){
        return true;
    }

    if( unit->GetType() == U_PC ){
        Character *ch = static_cast< Character * >( unit );                
        if( ch->GetPlayer()->GetGodFlags() & GOD_TRUE_INVISIBILITY ){
            return false;
        }
    }

    
    bool ret = true;
    // If this unit is invisible and the target doesn't detect it.
    if( unit->ViewFlag( __FLAG_INVISIBILITY ) != 0 && 
        target->ViewFlag( __FLAG_DETECT_INVISIBILITY ) == 0 ){
        ret = false;
    }

    // If the unit is hidden and the target doesn't detect it.
    if( unit->ViewFlag( __FLAG_HIDDEN ) != 0 &&
        target->ViewFlag( __FLAG_DETECT_HIDDEN ) == 0 ){
        ret = false;
    }

    return ret;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Unit::QueryInvisible::SetUnit
//////////////////////////////////////////////////////////////////////////////////////////
// Sets the character for the query invisible class.
// 
(
 Unit *ich
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    unit = ich;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::DispellInvisibility( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Removes any hidden or invisibility status from the unit.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    DispellEffectWithFlag( __FLAG_INVISIBILITY );
    Unhide();
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::Unhide( void )
//////////////////////////////////////////////////////////////////////////////////////////
//  Unhides a unit.
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
    // If unit isn't already hidden.
    if( ViewFlag( __FLAG_HIDDEN ) == 0 ){
        return;
    }
    
    // Remove the hidden flag.
    RemoveFlag( __FLAG_HIDDEN );

    WorldPos wlPos = GetWL();

    // Broadcast the unit's popup.
    BroadcastPopup( wlPos );

	SendSystemMessage( _STR(12956, GetLang() ) );
    

	if (theApp.dwHideUncoverEffectDisabled == 0) {
		// Broadcast the unhide effect
		Broadcast::BCSpellEffect( wlPos, _DEFAULT_RANGE,//BLBLBL 30=>_DEFAULT_RANGE
			30100, // <-- Effect ID
			GetID(),
			GetID(),
			wlPos,
			wlPos,
			GetNextGlobalEffectID(),
			0
		);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void Unit::RemoveReferenceTo
//////////////////////////////////////////////////////////////////////////////////////////
// Removes any reference to the pointer to unit.
// 
(
 Unit *theUnit // The unit.
)
//////////////////////////////////////////////////////////////////////////////////////////
{
    if( GetBond() == theUnit ){
        SetBond( NULL );
    }
    if( GetTarget() == theUnit ){
        SetTarget( GetBond() );
    }
}
