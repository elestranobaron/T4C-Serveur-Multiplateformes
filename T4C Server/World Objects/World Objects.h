// *******************************************************************************************
// ***                                                                                     ***
//      File Name: World Objects.h
//      Project:   TFC Server
//      Plateform: Windows NT 4.0 Workstation/Server
//      Creation:  17/1/1998
//      Author:    Francois Leblanc (FL)
// ***                                                                                     ***
// *******************************************************************************************
// ***                                                                                     ***
//      Change History
//
//         Date            Ver.      Author         Purpose
//         17/1/1998       1.0       FL             Initial developpement
//
//      Description
//          Defines all that is to be defined for world objects
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***           Copyright (c) 1997-1998 Virtual Dreams. All rights reserved.              ***

#include "..\Unit.h"
#include "..\ObjectListing.h" // Header file that contains all object ID's
#include "..\TFC_MAIN.h"
#include "..\Broadcast.h"
#include "..\DynObjManager.h"
#include "..\random.h"


void ObjectStatsSetup();
void ObjectDLLDestroy();
void RegisterObjects();

#define INIT_OBJECT_STAT_SETUP	void ObjectStatsSetup(){\
									ObjectStructure *THE_ITEM;
#define CLOSE_INIT_OBJECT_STAT_SETUP	}

//////////////////////////////////////////////////////////////////////////////////////////
// To easely edit items
#define SET_OBJECT( object )	THE_ITEM = &object;
#define OBJ_NAME( NaMe )	THE_ITEM->name = new char[ strlen( NaMe ) + 1 ];\
							strcpy( THE_ITEM->name, NaMe );
#define OBJ_APPEARANCE( __appearance ) THE_ITEM->appearance = __OBJGROUP_##__appearance\
																;
#define OBJ_EQUIP( __position ) THE_ITEM->equip_position = Character::__position;								
#define OBJ_BLOCK( __block ) THE_ITEM->blocking = __block;
#define OBJ_TYPE( __type ) THE_ITEM->item_type = __type;
#define OBJ_COST( __cost )	THE_ITEM->cost = __cost;
#define OBJ_SIZE( sizeo )	THE_ITEM->size = sizeo;	
#define OBJ_ARMOR_AC( ac )	THE_ITEM->armor.AC = ac;
#define OBJ_ARMOR_DODGE_MALUS( dod ) THE_ITEM->armor.Dod = dod;
#define OBJ_ARMOR_MIN_END( end ) THE_ITEM->armor.End = end;		
#define OBJ_WEAPON_DMG_ROLL( __formula ) THE_ITEM->weapon.cDamage.SetFormula( __formula );
#define OBJ_WEAPON_ATTRIBUTES( att, str, agi ) THE_ITEM->weapon.Att = att;\
											THE_ITEM->weapon.Str = str;\
											THE_ITEM->weapon.Agi = agi;
#define OBJ_LOCK_KEY( __key )	THE_ITEM->lock.key = __key;
#define OBJ_SPELL( __spell, __charges ) THE_ITEM->magic.spell = __spell;\
									THE_ITEM->magic.charges = __charges;
#define OBJ_TEXT( __text )	THE_ITEM->text.csText = __text;
#define OBJ_CONTAINER( __size, __space )/*	THE_ITEM->container.size = __size;\
										THE_ITEM->container.space = __space;*/
#define OBJ_MINLVL( Classe, Level )		THE_ITEM->MinLevel[ Classe ] = Level;
#define OBJ_EXHAUST( exhaustg )			THE_ITEM->exhaust = exhaustg;
#define OBJ_RADIANCE( _rad )			THE_ITEM->radiance = _rad;
#define OBJ_RESISTANCE( _res )			THE_ITEM->bResistance = _res;

#define OBJ_ATTR_BOOST( __boostID, __stat, __boost, __minwis, __minint )	THE_ITEM->boost.wStat = __stat;\
																			THE_ITEM->boost.nBoost = __boost;\
																			THE_ITEM->boost.nMinWIS = __minwis;\
																			THE_ITEM->boost.nMinINT = __minint;\
																			THE_ITEM->boost.wBoostID = __boostID;

//////////////////////////////////////////////////////////////////////////////////////////
// Registers an object
#define REGISTER_OBJECT( object ) Unit::RegisterUnitMessageHandler( 1, &object, #object\
																	, U_OBJECT, TRUE );

#define REGISTER_OBJECT_( object, ID ) Unit::RegisterUnitMessageHandler( 1, &object, ID, U_OBJECT, TRUE );

#define REGISTER_OBJECT_STRUCTURE( __Class, StructureID ) DynObjManager::RegisterObjectStructureCallback( StructureID, __Class::CreateObject );

//////////////////////////////////////////////////////////////////////////////////////////
// Stops an object data block
#define CLOSE_INIT_OBJECT_DATA	};