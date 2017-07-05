// ************************************************************************
// ***                                                                  ***
//      File Name: World Objects.DLL
//      Project:   Basic object file for TFC
//      Creation:  August 3rd, 1997
//      Author:    Francois Leblanc (FL)
// ***                                                                  ***
// ************************************************************************
// ***                                                                  ***
//      Change History
//
//         Date            Ver.	   Author	   Purpose
//         08-03-1997      1.0     FL          Initial development
//
//      Description
//				Provides a basic object event interpreter for TFC Server
// ***                                                                  ***
//	************************************************************************
// *** Copyright (c) 1997-1998 Vritual Dreams (r). All rights reserved. ***

#include "stdafx.h"
#include "World Objects.h"

#include "Container.h"
#include "Sword.h"
#include "Armor.h"
#include "SpellBook.h"
#include "Doors.h"
#include "Bag.h"
#include "StandardObject.h"
#include "Food.h"
#include "Potions.h"
#include "Book.h"
#include "DestinyGem.H"
#include "GemOfLife.h"
#include "IcySaber.h"
#include "Gold.h"
#include "Sign.h"
#include "Bow.h"
#include "ItemAreaLink.h"
#include "ChestStructure.h"

// Decor objects..
extern StandardObject DECOR001;
extern StandardObject DECOR002;
extern StandardObject DECOR003;
extern StandardObject DECOR004;
extern StandardObject DECOR005;
extern StandardObject DECOR006;
extern StandardObject DECOR007;
extern StandardObject DECOR008;
extern StandardObject DECOR009;
extern StandardObject DECOR010;
extern StandardObject DECOR011;
extern StandardObject DECOR012;
extern StandardObject DECOR013;
extern StandardObject DECOR014;
extern StandardObject DECOR015;
extern StandardObject DECOR016;
extern StandardObject DECOR017;
extern StandardObject DECOR018;

// standard objects
extern StandardObject CAMP_FIRE;
extern StandardObject WOODEN_CHAIR;
extern StandardObject WOODEN_ROUND_CHAIR;
extern StandardObject WOODEN_CHAIR_2;
extern StandardObject WOODEN_ROUND_CHAIR_2;
extern StandardObject WOODEN_CHAIR_FLIP;
extern StandardObject WOODEN_CHAIR_2_FLIP;
extern StandardObject WOODEN_ROUND_CHAIR_2_FLIP;
extern StandardObject WOODEN_CHAIR_REV;
extern StandardObject WOODEN_CHAIR_2_REV;
extern StandardObject WOODEN_ROUND_CHAIR_2_REV;
extern StandardObject WOODEN_CHAIR_I_REV;
extern StandardObject WOODEN_CHAIR_2_I_REV;
extern StandardObject WOODEN_ROUND_CHAIR_2_I_REV;

extern StandardObject EMPTY_MUG;
extern StandardObject BEER_MUG;
extern StandardObject BEER_MUG_TOO_FULL;
extern StandardObject EMPTY_GLASS;
extern StandardObject BEVERAGE;
extern StandardObject CUP_FULL;
extern StandardObject WOODEN_CUP;
extern StandardObject WOODEN_BOWL;
extern StandardObject WOODEN_VASE;
extern StandardObject KITCHEN_BOWL;
extern StandardObject KITCHEN_SPOON;
extern StandardObject KITCHEN_FORK;
extern StandardObject KITCHEN_KNIFE;
extern StandardObject ROULEAU_A_PATE;
extern StandardObject BROOM_ON_WALL;
extern StandardObject BROOM_ON_FLOOR;

extern StandardObject BANJO;
extern StandardObject TAMBOUR;
extern StandardObject LONG_WHOOL_BALL;
extern StandardObject WHOOL_BALL;
extern StandardObject GREEN_WHOOL_BALL;
extern StandardObject BLUE_WHOOL_BALL;
extern StandardObject CHANDELLE;
extern StandardObject CHANDELLE_SUR_PIED;
extern StandardObject MIRROR;
extern StandardObject PINCES;
extern StandardObject BALANCE;
extern StandardObject HOURGLASS2;
extern StandardObject EPROUVETTE_6_PACKS;
extern StandardObject EPROUVETTE_3_PACKS;
extern StandardObject EPROUVETTE_ALONE;
extern StandardObject BUCHE_DE_BOIS;
extern StandardObject LONGUE_VUE;
extern StandardObject WOOD_PACK_CLASSED;
extern StandardObject WOOD_PACK_MIXED;
extern StandardObject FISHING_POLE;

// Quest Items
extern StandardObject LETTER_FOR_MERCHANT;
extern StandardObject FAKE_DRAGON_TOOTH;
extern StandardObject DECAYED_BAT_WINGS;

// Food
extern Food JAMBON;
extern Food LONG_SAUSAGE;
extern Food SAUSAGE_PACK;
extern Food FAT_JAMBON;
extern Food CHICKEN;
extern Food BREAD;
extern Food PACK_OF_PASTRIES;
extern Food DEAD_FISHES;

// Potions
extern Potions BLUE_POTION;
extern Potions YELLOW_POTION;
extern Potions BLACK_POTION;
extern Potions PURPLE_POTION;


// Doors
extern Doors WOODEN_DOOR;
extern Doors WOODEN_DOOR_FLIP;

// Books
extern Book ROMANCE_BOOK;
extern Food LETTUCE;

extern Gold GOLD;


void RegisterObjects(){

    TFCMAIN::RegisterUnitStartupFunction( ObjectStatsSetup );
	
	REGISTER_OBJECT_STRUCTURE( Sword,			1  )	
	REGISTER_OBJECT_STRUCTURE( Armor,			2  )
	REGISTER_OBJECT_STRUCTURE( Book,			3  )
	REGISTER_OBJECT_STRUCTURE( Container,		4  )
	REGISTER_OBJECT_STRUCTURE( Doors,			5  )
	REGISTER_OBJECT_STRUCTURE( Food,			6  )
	REGISTER_OBJECT_STRUCTURE( Potions,			7  )	
	REGISTER_OBJECT_STRUCTURE( StandardObject,	8  )
    REGISTER_OBJECT_STRUCTURE( DestinyGem,      9  )
    REGISTER_OBJECT_STRUCTURE( Gold,            10 )
    REGISTER_OBJECT_STRUCTURE( Sign,            11 )
    REGISTER_OBJECT_STRUCTURE( StandardObject,  12 ) // Quivers
    REGISTER_OBJECT_STRUCTURE( Bow,             13 ) // Bows
	REGISTER_OBJECT_STRUCTURE( ItemAreaLink,	14 ) // AreaLinks
	REGISTER_OBJECT_STRUCTURE( ChestStructure,  15 ) // Item Banks (Online Mule)


    REGISTER_OBJECT( GOLD );

	REGISTER_OBJECT( DECOR001 )
	REGISTER_OBJECT( DECOR002 )
	REGISTER_OBJECT( DECOR003 )
	REGISTER_OBJECT( DECOR004 )
	REGISTER_OBJECT( DECOR005 )
	REGISTER_OBJECT( DECOR006 )
	REGISTER_OBJECT( DECOR007 )
	REGISTER_OBJECT( DECOR008 )
	REGISTER_OBJECT( DECOR009 )
	REGISTER_OBJECT( DECOR010 )
	REGISTER_OBJECT( DECOR011 )
	REGISTER_OBJECT( DECOR012 )
	REGISTER_OBJECT( DECOR013 )
	REGISTER_OBJECT( DECOR014 )
	REGISTER_OBJECT( DECOR015 )
	REGISTER_OBJECT( DECOR016 )
	REGISTER_OBJECT( DECOR017 )
	REGISTER_OBJECT( DECOR018 )

    ///////////////////////////////////////
	// Doors
	REGISTER_OBJECT( WOODEN_DOOR )	
	REGISTER_OBJECT( WOODEN_DOOR_FLIP )
	REGISTER_OBJECT_( WOODEN_DOOR, "CLOSED_WOODEN_DOOR" )
	REGISTER_OBJECT_( WOODEN_DOOR_FLIP, "CLOSED_WOODEN_DOOR_FLIP" )

	//////////////////////////////////////
	// Potions
	REGISTER_OBJECT( BLUE_POTION )
	REGISTER_OBJECT( YELLOW_POTION )
	REGISTER_OBJECT( BLACK_POTION )
	REGISTER_OBJECT( PURPLE_POTION )

	///////////////////////////////////////
	// Romance books
	REGISTER_OBJECT( ROMANCE_BOOK )


	/////////////////////////////////////////////////////////
	// Food, very few often used
	REGISTER_OBJECT( JAMBON )
	REGISTER_OBJECT( LONG_SAUSAGE )
	REGISTER_OBJECT( SAUSAGE_PACK )
	REGISTER_OBJECT( FAT_JAMBON )
	REGISTER_OBJECT( CHICKEN )
	REGISTER_OBJECT( BREAD )
	REGISTER_OBJECT( PACK_OF_PASTRIES )
	REGISTER_OBJECT( DEAD_FISHES )


	///////////////////////////////////////////////
	// Quest items
	REGISTER_OBJECT( LETTER_FOR_MERCHANT )
	REGISTER_OBJECT( FAKE_DRAGON_TOOTH )

	////////////////////////////////////////
	// Unmapped "standard" objects, least used objects
	REGISTER_OBJECT( CAMP_FIRE )
	REGISTER_OBJECT( WOODEN_CHAIR )
	REGISTER_OBJECT( WOODEN_ROUND_CHAIR )
	REGISTER_OBJECT( WOODEN_CHAIR_2 )
	REGISTER_OBJECT( WOODEN_ROUND_CHAIR_2 )
	REGISTER_OBJECT( WOODEN_CHAIR_FLIP )
	REGISTER_OBJECT( WOODEN_CHAIR_2_FLIP )
	REGISTER_OBJECT( WOODEN_ROUND_CHAIR_2_FLIP )
	REGISTER_OBJECT( WOODEN_CHAIR_REV )
	REGISTER_OBJECT( WOODEN_CHAIR_2_REV )
	REGISTER_OBJECT( WOODEN_ROUND_CHAIR_2_REV )
	REGISTER_OBJECT( WOODEN_CHAIR_I_REV )
	REGISTER_OBJECT( WOODEN_CHAIR_2_I_REV )
	REGISTER_OBJECT( WOODEN_ROUND_CHAIR_2_I_REV )
	REGISTER_OBJECT( EMPTY_MUG )
	REGISTER_OBJECT( BEER_MUG )
	REGISTER_OBJECT( BEER_MUG_TOO_FULL )
	REGISTER_OBJECT( EMPTY_GLASS )
	REGISTER_OBJECT( BEVERAGE )
	REGISTER_OBJECT( CUP_FULL )
	REGISTER_OBJECT( WOODEN_CUP )
	REGISTER_OBJECT( WOODEN_BOWL )
	REGISTER_OBJECT( WOODEN_VASE )
	REGISTER_OBJECT( KITCHEN_BOWL )
	REGISTER_OBJECT( KITCHEN_SPOON )
	REGISTER_OBJECT( KITCHEN_FORK )
	REGISTER_OBJECT( KITCHEN_KNIFE )
	REGISTER_OBJECT( ROULEAU_A_PATE )
	REGISTER_OBJECT( BROOM_ON_WALL )
	REGISTER_OBJECT( BROOM_ON_FLOOR )
	// 2nd batch
	REGISTER_OBJECT( BANJO )
	REGISTER_OBJECT( TAMBOUR )
	REGISTER_OBJECT( LONG_WHOOL_BALL )
	REGISTER_OBJECT( WHOOL_BALL )
	REGISTER_OBJECT( GREEN_WHOOL_BALL )
	REGISTER_OBJECT( BLUE_WHOOL_BALL )
	REGISTER_OBJECT( CHANDELLE )
	REGISTER_OBJECT( CHANDELLE_SUR_PIED )
	REGISTER_OBJECT( MIRROR )
	REGISTER_OBJECT( PINCES )
	REGISTER_OBJECT( BALANCE )
	//REGISTER_OBJECT( HOURGLASS2 )
	REGISTER_OBJECT( EPROUVETTE_6_PACKS )
	REGISTER_OBJECT( EPROUVETTE_3_PACKS )
	REGISTER_OBJECT( EPROUVETTE_ALONE )
	REGISTER_OBJECT( BUCHE_DE_BOIS )
	REGISTER_OBJECT( LONGUE_VUE )
	REGISTER_OBJECT( WOOD_PACK_CLASSED )
	REGISTER_OBJECT( WOOD_PACK_MIXED )
	REGISTER_OBJECT( FISHING_POLE )
	REGISTER_OBJECT( LETTUCE )

}