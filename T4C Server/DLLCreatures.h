// *******************************************************************************************
// ***                                                                                     ***
//      File Name: Creatures.h
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
//         15/1/1998       1.0       FL             Initial developpement
//
//      Description
//          Header file for creature making
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***           Copyright (c) 1997-1998 Virtual Dreams. All rights reserved.              ***

#include "CreatureListing.h"
#include "AttackListing.h"
#include "Unit.h"
#include "MonsterStructure.h"
#include "ClanListing.h"
#include "SimpleMonster.h"
#include "NPCstructure.h"
#include "T4CLog.h"
#include "Apparence.h"


void MonsterStatSetup( void );
void InitCreatures( void );

const int _NORMAL_ATTACK = 1;
const int _SPECIAL1 = 2;

#define BASE_MONSTER_ID     20000

//////////////////////////////////////////////////////////////////////////////////////////
#define INIT_MONSTER_STAT_SETUP	static WORD wIDCount = 0; void MonsterStatSetup(){ \
TRACE( "\r\n====!wIDCount=%u..!====", wIDCount );\
  LPBOOL lpInit = new BOOL[ wIDCount + 1 ]; \
{\
  int i;\
    for( i = 0; i < wIDCount; i++ ){\
        lpInit[ i ] = FALSE;\
    }\
}\
try{ \
MonsterStructure *MOB;\
MONSTER_ATTACK   *lpMonsterAttack;
//////////////////////////////////////////////////////////////////////////////////////////
#define CLOSE_MONSTER_STAT_SETUP	} catch( ... ){ \
    _LOG_DEBUG\
        LOG_DEBUG_LVL2,\
        "Caught exception in MonsterStatSetup. File %s",\
        __FILE__\
    LOG_;\
} \
{\
    int i;\
    for( i = 0; i < wIDCount; i++ ){\
        if( lpInit[ i ] == FALSE ){\
            char name[256];\
            Unit::GetNameFromID( i + BASE_MONSTER_ID, name, U_NPC );\
            _LOG_DEBUG\
                LOG_DEBUG_LVL2,\
                "Monster ID %u (%s) has not been setup.",\
                i + BASE_MONSTER_ID,\
                name\
            LOG_\
        }\
    }\
}\
delete lpInit;\
}

    /*MOB->nDeathGiveFlag = 0;\
    MOB->nDeathFlagValue = 0;\
    MOB->boDeathFlagIncrement = TRUE;\*/

//////////////////////////////////////////////////////////////////////////////////////////
#define SET_MONSTER( Object )	MOB = Object.GetMonsterStructure();\
	MOB->boCanAttack = TRUE;\
	MOB->creature = _NORMAL;\
	MOB->block = 1;\
	MOB->MaxGold = 0;\
	MOB->MinGold = 0;\
	MOB->speed = 50;\
	MOB->cAttackLag = dice( 4, 500 );\
	MOB->bLagChance = 30;\
	MOB->cStopLen = dice( 9, 500 );\
	MOB->STR = 0;\
	MOB->END = 0;\
	MOB->AGI = 0;\
	MOB->AGI = 0;\
	MOB->INT = 0;\
	MOB->WIL = 0;\
	MOB->WIS = 0;\
	MOB->LCK = 0;\
    MOB->boInit = true;\
    MOB->wBody = MOB->wFeet = MOB->wGloves = MOB->wHelm = MOB->wLegs = MOB->wWeapon = MOB->wShield = MOB->wCape = 0;\
    MOB->AirResist = MOB->WaterResist = MOB->FireResist = MOB->EarthResist = MOB->LightResist = MOB->DarkResist = 0;\
    MOB->AirPower  = MOB->WaterPower  = MOB->FirePower  = MOB->EarthPower  = MOB->LightPower  = MOB->DarkPower  = 0;\
    MOB->boCanExitBuilding = TRUE;\
    if( MOB->wBaseReferenceID >= BASE_MONSTER_ID && MOB->wBaseReferenceID - BASE_MONSTER_ID < wIDCount ){\
        if( lpInit[ MOB->wBaseReferenceID - BASE_MONSTER_ID ] == TRUE ){\
            char name[ 256 ];\
            Unit::GetNameFromID( MOB->wBaseReferenceID, name, U_NPC );\
            _LOG_DEBUG\
                LOG_DEBUG_LVL2,\
                "Monster ID %u (%s) has already been set.",\
                MOB->wBaseReferenceID,\
                name\
            LOG_\
        }else{\
            lpInit[ MOB->wBaseReferenceID - BASE_MONSTER_ID ] = TRUE;\
        }\
    }

//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_NAME( __Name )	MOB->name = __Name;
							
//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_APPEARANCE( __Appear ) MOB->appearance = __MOBAPPEAR_##__Appear\
	                           ;MOB->Corpse = __MOBAPPEAR_CORPSE_##__Appear\
							   ;

#define MOB_OBJ_APPEARANCE( __Appear ) MOB->appearance = __OBJGROUP_##__Appear\
                                    ;MOB->Corpse = 0;

#define MOB_DRESS_BODY( __ObjID )     MOB->wBody   = __OBJGROUP_##__ObjID\
    ;
#define MOB_DRESS_FEET( __ObjID )     MOB->wFeet   = __OBJGROUP_##__ObjID\
    ;
#define MOB_DRESS_GLOVES( __ObjID )   MOB->wGloves = __OBJGROUP_##__ObjID\
    ;
#define MOB_DRESS_HELM( __ObjID )     MOB->wHelm   = __OBJGROUP_##__ObjID\
    ;
#define MOB_DRESS_LEGS( __ObjID )     MOB->wLegs   = __OBJGROUP_##__ObjID\
    ;
#define MOB_DRESS_WEAPON( __ObjID )   MOB->wWeapon = __OBJGROUP_##__ObjID\
    ;
#define MOB_DRESS_SHIELD( __ObjID )   MOB->wShield = __OBJGROUP_##__ObjID\
    ;
#define MOB_DRESS_CAPE( __ObjID )     MOB->wCape  = __OBJGROUP_##__ObjID\
    ;

#define MOB_NPC_APPEARANCE( __Appear ) MOB->appearance = __NPC_##__Appear\
								;MOB->Corpse = __NPC_CORPSE_##__Appear\
								;

//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_CAN_EXIT_BUILDING( __value )    MOB->boCanExitBuilding = __value;
//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_AGRESSIVNESS( __Agress ) MOB->agressive = __Agress;
//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_CLAN( __Clan )	MOB->clan = __CLAN_##__Clan\
						;
//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_HP( __HP )	MOB->HP = __HP;
//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_DODGE_SKILL( __Skill ) MOB->DodgeSkill = __Skill;
//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_AC( __AC ) MOB->AC = __AC;
//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_SPEED( __Speed, __AttackLag, __LagChance, __LagLen ) MOB->speed = __Speed;\
	MOB->cAttackLag = __AttackLag;\
	MOB->bLagChance = __LagChance;\
	MOB->cStopLen = __LagLen;

#define MOB_UNDEAD( __Undead )	MOB->wUndead = Unit::GetIDFromName( __Undead );

//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_STR( __Stat ) MOB->STR = __Stat;
#define MOB_END( __Stat ) MOB->END = __Stat;
#define MOB_DEX( __Stat ) MOB->AGI = __Stat;
#define MOB_AGI( __Stat ) MOB->AGI = __Stat;
#define MOB_INT( __Stat ) MOB->INT = __Stat;
#define MOB_WIL( __Stat ) MOB->WIL = __Stat;
#define MOB_WIS( __Stat ) MOB->WIS = __Stat;
#define MOB_LCK( __Stat ) MOB->LCK = __Stat;

#define MOB_WATER_RESIST( __stat ) MOB->WaterResist = __stat;
#define MOB_FIRE_RESIST( __stat )  MOB->FireResist = __stat;
#define MOB_EARTH_RESIST( __stat ) MOB->EarthResist = __stat;
#define MOB_AIR_RESIST( __stat )   MOB->AirResist = __stat;
#define MOB_LIGHT_RESIST( __stat ) MOB->LightResist = __stat;
#define MOB_DARK_RESIST( __stat )  MOB->DarkResist = __stat;

#define MOB_WATER_POWER( __stat )  MOB->WaterPower = __stat;
#define MOB_FIRE_POWER( __stat )   MOB->FirePower = __stat;
#define MOB_EARTH_POWER( __stat )  MOB->EarthPower = __stat;
#define MOB_AIR_POWER( __stat )    MOB->AirPower = __stat;
#define MOB_LIGHT_POWER( __stat )  MOB->LightPower = __stat;
#define MOB_DARK_POWER( __stat )   MOB->DarkPower = __stat;

//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_TYPE( __type ) MOB->creature = __type;
//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_LEVEL( __Level ) MOB->level = __Level;
//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_XP_PER_HIT( __XP ) MOB->XPperHit = __XP;
#define MOB_XP_DEATH( __XP ) MOB->XPperDeath = __XP;
//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_MAX_GOLD( __Gold ) MOB->MaxGold = __Gold;
#define MOB_MIN_GOLD( __Gold ) MOB->MinGold = __Gold;


//////////////////////////////////////////////////////////////////////////////////////////
// For attacks, create either close-range physical attacks or long/short range spells.
#define MOB_CREATE_PHYSICAL_ATTACK      lpMonsterAttack = new MONSTER_ATTACK;\
                                        MOB->vlpMonsterAttacks.push_back( lpMonsterAttack );

#define MOB_CREATE_SPELL_ATTACK( __minrange, __maxrange ) lpMonsterAttack = new MONSTER_SPELL_ATTACK;\
                                lpMonsterAttack->nMinRange = __minrange;\
                                lpMonsterAttack->nMaxRange = __maxrange;\
                                MOB->vlpRangeAttacks.push_back( lpMonsterAttack );

//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_ATTACK_DMG_ROLL( __Roll ) if( !lpMonsterAttack->DamageRoll.SetFormula( __Roll ) ){\
_LOG_DEBUG LOG_DEBUG_LVL1, "Wrong damage formula on monster %s.", MOB->name LOG_}
//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_ATTACK_SKILL( __Str ) lpMonsterAttack->AttackSkill = __Str;
//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_ATTACK_PERCENTAGE( __Hit ) lpMonsterAttack->AttackDoingPercentage = __Hit;
#define MOB_ATTACK_SPELL( __Spell ) static_cast< MONSTER_SPELL_ATTACK * >( lpMonsterAttack )->wSpellID = __Spell;


//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_ITEM( __ItemID, __ItemPercentage ) { ItemToGive sItem; sItem.ItemID = __ItemID;\
                                                 sItem.ItemGivePercentage = __ItemPercentage;\
                                                 MOB->vDeathItems.push_back( sItem );\
                                               }

//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_CAN_ATTACK( _att ) MOB->boCanAttack = _att;

//////////////////////////////////////////////////////////////////////////////////////////
#define MOB_DEATH_FLAG( __flag, __value, __increment ) { sDeadFlag sFlag; sFlag.nDeathGiveFlag = __flag;\
                                                         sFlag.nDeathFlagValue = __value;\
                                                         sFlag.boDeathFlagIncrement = __increment;\
                                                         MOB->vOnDeathFlag.push_back(sFlag);\
                                                       }


//////////////////////////////////////////////////////////////////////////////////////////
#define INIT_CREATURE_DATA static AFX_EXTENSION_MODULE CreaturesDLL;\
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)\
{\
	UNREFERENCED_PARAMETER(lpReserved);\
	switch(dwReason) {\
    case DLL_PROCESS_ATTACH: \
            TFCMAIN::RegisterUnitStartupFunction( MonsterStatSetup );\
			InitCreatures();\
		break;\
    case DLL_THREAD_ATTACH: break;\
	case DLL_THREAD_DETACH: break;\
    case DLL_PROCESS_DETACH: \
		break;\
    }\
return 1;\
}\
void InitCreatures( void ){

//////////////////////////////////////////////////////////////////////////////////////////
#define REGISTER_CREATURE( ID, GlobalIDName )	ID.GetMonsterStructure()->wBaseReferenceID = Unit::RegisterUnitMessageHandler( BASE_MONSTER_ID, &ID, GlobalIDName, U_NPC, TRUE );\
                                                wIDCount++;

//////////////////////////////////////////////////////////////////////////////////////////
#define END_INIT_CREATURE_DATA ;};