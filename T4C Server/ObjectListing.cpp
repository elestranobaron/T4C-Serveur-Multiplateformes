// *******************************************************************************************
// ***                                                                                     ***
//      File Name: ObjectListing.cpp
//      Project:   TFC Server
//      Plateform: Windows NT 4.0 Workstation/Server
//      Creation:  17/2/1998
//      Author:    Francois Leblanc (FL)
// ***                                                                                     ***
// *******************************************************************************************
// ***                                                                                     ***
//      Change History
//
//         Date            Ver.      Author         Purpose
//         17/2/1998       1.0       FL             Initial developpement
//
//      Description
//          This files creates and initialisez the global variables.
//          
// ***                                                                                     ***
//	*******************************************************************************************
// ***           Copyright (c) 1997-1998 Virtual Dreams. All rights reserved.              ***

#include "stdafx.h"
#include "TFC Server.h"
#include "Unit.h"

//////////////////////////////////////////////////////////////////////////////////////////
#define CREATE_VAR( VarName )	__OBJ_##VarName\
= Unit::GetIDFromName( #VarName\
	, U_OBJECT );
//////////////////////////////////////////////////////////////////////////////////////////

#define EXP_VAR	extern "C" int __declspec( dllexport ) 

// Decor objects..
EXP_VAR __OBJ_DECOR001 = 0;
EXP_VAR __OBJ_DECOR002 = 0;
EXP_VAR __OBJ_DECOR003 = 0;
EXP_VAR __OBJ_DECOR004 = 0;
EXP_VAR __OBJ_DECOR005 = 0;
EXP_VAR __OBJ_DECOR006 = 0;
EXP_VAR __OBJ_DECOR007 = 0;
EXP_VAR __OBJ_DECOR008 = 0;
EXP_VAR __OBJ_DECOR009 = 0;
EXP_VAR __OBJ_DECOR010 = 0;
EXP_VAR __OBJ_DECOR011 = 0;
EXP_VAR __OBJ_DECOR012 = 0;
EXP_VAR __OBJ_DECOR013 = 0;
EXP_VAR __OBJ_DECOR014 = 0;
EXP_VAR __OBJ_DECOR015 = 0;
EXP_VAR __OBJ_DECOR016 = 0;
EXP_VAR __OBJ_DECOR017 = 0;
EXP_VAR __OBJ_DECOR018 = 0;

// standard objects
EXP_VAR __OBJ_CAMP_FIRE = 0;
EXP_VAR __OBJ_WOODEN_CHAIR = 0;
EXP_VAR __OBJ_WOODEN_ROUND_CHAIR = 0;
EXP_VAR __OBJ_WOODEN_CHAIR_2 = 0;
EXP_VAR __OBJ_WOODEN_ROUND_CHAIR_2 = 0;
EXP_VAR __OBJ_WOODEN_CHAIR_FLIP = 0;
EXP_VAR __OBJ_WOODEN_CHAIR_2_FLIP = 0;
EXP_VAR __OBJ_WOODEN_ROUND_CHAIR_2_FLIP = 0;
EXP_VAR __OBJ_WOODEN_CHAIR_REV = 0;
EXP_VAR __OBJ_WOODEN_CHAIR_2_REV = 0;
EXP_VAR __OBJ_WOODEN_ROUND_CHAIR_2_REV = 0;
EXP_VAR __OBJ_WOODEN_CHAIR_I_REV = 0;
EXP_VAR __OBJ_WOODEN_CHAIR_2_I_REV = 0;
EXP_VAR __OBJ_WOODEN_ROUND_CHAIR_2_I_REV = 0;

EXP_VAR __OBJ_EMPTY_MUG = 0;
EXP_VAR __OBJ_BEER_MUG = 0;
EXP_VAR __OBJ_BEER_MUG_TOO_FULL = 0;
EXP_VAR __OBJ_EMPTY_GLASS = 0;
EXP_VAR __OBJ_BEVERAGE = 0;
EXP_VAR __OBJ_CUP_FULL = 0;
EXP_VAR __OBJ_WOODEN_CUP = 0;
EXP_VAR __OBJ_WOODEN_BOWL = 0;
EXP_VAR __OBJ_WOODEN_VASE = 0;
EXP_VAR __OBJ_KITCHEN_BOWL = 0;
EXP_VAR __OBJ_KITCHEN_SPOON = 0;
EXP_VAR __OBJ_KITCHEN_FORK = 0;
EXP_VAR __OBJ_KITCHEN_KNIFE = 0;
EXP_VAR __OBJ_ROULEAU_A_PATE = 0;
EXP_VAR __OBJ_BROOM_ON_WALL = 0;
EXP_VAR __OBJ_BROOM_ON_FLOOR = 0;

EXP_VAR __OBJ_BANJO = 0;
EXP_VAR __OBJ_TAMBOUR = 0;
EXP_VAR __OBJ_LONG_WHOOL_BALL = 0;
EXP_VAR __OBJ_WHOOL_BALL = 0;
EXP_VAR __OBJ_GREEN_WHOOL_BALL = 0;
EXP_VAR __OBJ_BLUE_WHOOL_BALL = 0;
EXP_VAR __OBJ_CHANDELLE = 0;
EXP_VAR __OBJ_CHANDELLE_SUR_PIED = 0;
EXP_VAR __OBJ_MIRROR = 0;
EXP_VAR __OBJ_PINCES = 0;
EXP_VAR __OBJ_BALANCE = 0;
EXP_VAR __OBJ_HOURGLASS = 0;
EXP_VAR __OBJ_EPROUVETTE_6_PACKS = 0;
EXP_VAR __OBJ_EPROUVETTE_3_PACKS = 0;
EXP_VAR __OBJ_EPROUVETTE_ALONE = 0;
EXP_VAR __OBJ_BUCHE_DE_BOIS = 0;
EXP_VAR __OBJ_LONGUE_VUE = 0;
EXP_VAR __OBJ_WOOD_PACK_CLASSED = 0;
EXP_VAR __OBJ_WOOD_PACK_MIXED = 0;
EXP_VAR __OBJ_FISHING_POLE = 0;

// Quest Items
EXP_VAR __OBJ_LETTER_FOR_MERCHANT = 0;
EXP_VAR __OBJ_FAKE_DRAGON_TOOTH = 0;
EXP_VAR __OBJ_DECAYED_BAT_WINGS = 0;

// Food
EXP_VAR __OBJ_JAMBON = 0;
EXP_VAR __OBJ_LONG_SAUSAGE = 0;
EXP_VAR __OBJ_SAUSAGE_PACK = 0;
EXP_VAR __OBJ_FAT_JAMBON = 0;
EXP_VAR __OBJ_CHICKEN = 0;
EXP_VAR __OBJ_BREAD = 0;
EXP_VAR __OBJ_PACK_OF_PASTRIES = 0;
EXP_VAR __OBJ_DEAD_FISHES = 0;

// Potions
EXP_VAR __OBJ_BLUE_POTION = 0;
EXP_VAR __OBJ_YELLOW_POTION = 0;
EXP_VAR __OBJ_BLACK_POTION = 0;
EXP_VAR __OBJ_PURPLE_POTION = 0;


// Doors
EXP_VAR __OBJ_WOODEN_DOOR = 0;
EXP_VAR __OBJ_WOODEN_DOOR_FLIP = 0;

// Books
EXP_VAR __OBJ_ROMANCE_BOOK = 0;
EXP_VAR __OBJ_LETTUCE = 0;

EXP_VAR __OBJ_GOLD = 0;


//////////////////////////////////////////////////////////////////////////////////////////
void ObjectListing( void )
//////////////////////////////////////////////////////////////////////////////////////////
// This function should be called to initialize the global variables
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
	CREATE_VAR( GOLD );
    
    CREATE_VAR( DECOR001 )
	CREATE_VAR( DECOR002 )
	CREATE_VAR( DECOR003 )
	CREATE_VAR( DECOR004 )
	CREATE_VAR( DECOR005 )
	CREATE_VAR( DECOR006 )
	CREATE_VAR( DECOR007 )
	CREATE_VAR( DECOR008 )
	CREATE_VAR( DECOR009 )
	CREATE_VAR( DECOR010 )
	CREATE_VAR( DECOR011 )
	CREATE_VAR( DECOR012 )
	CREATE_VAR( DECOR013 )
	CREATE_VAR( DECOR014 )
	CREATE_VAR( DECOR015 )
	CREATE_VAR( DECOR016 )
	CREATE_VAR( DECOR017 )
	CREATE_VAR( DECOR018 )

	///////////////////////////////////////
	// Doors
	CREATE_VAR( WOODEN_DOOR )	
	CREATE_VAR( WOODEN_DOOR_FLIP )
	//CREATE_VAR( WOODEN_DOOR, "CLOSED_WOODEN_DOOR" )
	//CREATE_VAR( WOODEN_DOOR_FLIP, "CLOSED_WOODEN_DOOR_FLIP" )

	//////////////////////////////////////
	// Potions
	CREATE_VAR( BLUE_POTION )
	CREATE_VAR( YELLOW_POTION )
	CREATE_VAR( BLACK_POTION )
	CREATE_VAR( PURPLE_POTION )

	///////////////////////////////////////
	// Romance books
	CREATE_VAR( ROMANCE_BOOK )


	/////////////////////////////////////////////////////////
	// Food, very few often used
	CREATE_VAR( JAMBON )
	CREATE_VAR( LONG_SAUSAGE )
	CREATE_VAR( SAUSAGE_PACK )
	CREATE_VAR( FAT_JAMBON )
	CREATE_VAR( CHICKEN )
	CREATE_VAR( BREAD )
	CREATE_VAR( PACK_OF_PASTRIES )
	CREATE_VAR( DEAD_FISHES )


	///////////////////////////////////////////////
	// Quest items
	CREATE_VAR( LETTER_FOR_MERCHANT )
	CREATE_VAR( FAKE_DRAGON_TOOTH )

	////////////////////////////////////////
	// Unmapped "standard" objects, least used objects
	CREATE_VAR( CAMP_FIRE )
	CREATE_VAR( WOODEN_CHAIR )
	CREATE_VAR( WOODEN_ROUND_CHAIR )
	CREATE_VAR( WOODEN_CHAIR_2 )
	CREATE_VAR( WOODEN_ROUND_CHAIR_2 )
	CREATE_VAR( WOODEN_CHAIR_FLIP )
	CREATE_VAR( WOODEN_CHAIR_2_FLIP )
	CREATE_VAR( WOODEN_ROUND_CHAIR_2_FLIP )
	CREATE_VAR( WOODEN_CHAIR_REV )
	CREATE_VAR( WOODEN_CHAIR_2_REV )
	CREATE_VAR( WOODEN_ROUND_CHAIR_2_REV )
	CREATE_VAR( WOODEN_CHAIR_I_REV )
	CREATE_VAR( WOODEN_CHAIR_2_I_REV )
	CREATE_VAR( WOODEN_ROUND_CHAIR_2_I_REV )
	CREATE_VAR( EMPTY_MUG )
	CREATE_VAR( BEER_MUG )
	CREATE_VAR( BEER_MUG_TOO_FULL )
	CREATE_VAR( EMPTY_GLASS )
	CREATE_VAR( BEVERAGE )
	CREATE_VAR( CUP_FULL )
	CREATE_VAR( WOODEN_CUP )
	CREATE_VAR( WOODEN_BOWL )
	CREATE_VAR( WOODEN_VASE )
	CREATE_VAR( KITCHEN_BOWL )
	CREATE_VAR( KITCHEN_SPOON )
	CREATE_VAR( KITCHEN_FORK )
	CREATE_VAR( KITCHEN_KNIFE )
	CREATE_VAR( ROULEAU_A_PATE )
	CREATE_VAR( BROOM_ON_WALL )
	CREATE_VAR( BROOM_ON_FLOOR )
	// 2nd batch
	CREATE_VAR( BANJO )
	CREATE_VAR( TAMBOUR )
	CREATE_VAR( LONG_WHOOL_BALL )
	CREATE_VAR( WHOOL_BALL )
	CREATE_VAR( GREEN_WHOOL_BALL )
	CREATE_VAR( BLUE_WHOOL_BALL )
	CREATE_VAR( CHANDELLE )
	CREATE_VAR( CHANDELLE_SUR_PIED )
	CREATE_VAR( MIRROR )
	CREATE_VAR( PINCES )
	CREATE_VAR( BALANCE )
	CREATE_VAR( HOURGLASS )
	CREATE_VAR( EPROUVETTE_6_PACKS )
	CREATE_VAR( EPROUVETTE_3_PACKS )
	CREATE_VAR( EPROUVETTE_ALONE )
	CREATE_VAR( BUCHE_DE_BOIS )
	CREATE_VAR( LONGUE_VUE )
	CREATE_VAR( WOOD_PACK_CLASSED )
	CREATE_VAR( WOOD_PACK_MIXED )
	CREATE_VAR( FISHING_POLE )


}