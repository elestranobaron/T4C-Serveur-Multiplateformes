////////////////////////////////////////////////////////////////////////////////////////
// Initializes the object's stats.. duh?
#include "stdafx.h"
// Forbids ObjectsListing.h
#include "Sword.h"
#include "Armor.h"
#include "Doors.h"
#include "SpellBook.h"
#include "StandardObject.h"
#include "Bag.h"
#include "Food.h"
#include "Potions.h"
#include "Book.h"
#include "Container.h"
#include "World Objects.h"
#include "DestinyGem.h"
#include "GemOfLife.h"
#include "IcySaber.h"
#include "Gold.h"

#include "..\Apparence.h"

// TO DELETE
StandardObject DECOR001;
StandardObject DECOR002;
StandardObject DECOR003;
StandardObject DECOR004;
StandardObject DECOR005;
StandardObject DECOR006;
StandardObject DECOR007;
StandardObject DECOR008;
StandardObject DECOR009;
StandardObject DECOR010;
StandardObject DECOR011;
StandardObject DECOR012;
StandardObject DECOR013;
StandardObject DECOR014;
StandardObject DECOR015;
StandardObject DECOR016;
StandardObject DECOR017;
StandardObject DECOR018;

// standard objects
StandardObject CAMP_FIRE;
StandardObject WOODEN_CHAIR;
StandardObject WOODEN_ROUND_CHAIR;
StandardObject WOODEN_CHAIR_2;
StandardObject WOODEN_ROUND_CHAIR_2;
StandardObject WOODEN_CHAIR_FLIP;
StandardObject WOODEN_CHAIR_2_FLIP;
StandardObject WOODEN_ROUND_CHAIR_2_FLIP;
StandardObject WOODEN_CHAIR_REV;
StandardObject WOODEN_CHAIR_2_REV;
StandardObject WOODEN_ROUND_CHAIR_2_REV;
StandardObject WOODEN_CHAIR_I_REV;
StandardObject WOODEN_CHAIR_2_I_REV;
StandardObject WOODEN_ROUND_CHAIR_2_I_REV;

StandardObject EMPTY_MUG;
StandardObject BEER_MUG;
StandardObject BEER_MUG_TOO_FULL;
StandardObject EMPTY_GLASS;
StandardObject BEVERAGE;
StandardObject CUP_FULL;
StandardObject WOODEN_CUP;
StandardObject WOODEN_BOWL;
StandardObject WOODEN_VASE;
StandardObject KITCHEN_BOWL;
StandardObject KITCHEN_SPOON;
StandardObject KITCHEN_FORK;
StandardObject KITCHEN_KNIFE;
StandardObject ROULEAU_A_PATE;
StandardObject BROOM_ON_WALL;
StandardObject BROOM_ON_FLOOR;

StandardObject BANJO;
StandardObject TAMBOUR;
StandardObject LONG_WHOOL_BALL;
StandardObject WHOOL_BALL;
StandardObject GREEN_WHOOL_BALL;
StandardObject BLUE_WHOOL_BALL;
StandardObject CHANDELLE;
StandardObject CHANDELLE_SUR_PIED;
StandardObject MIRROR;
StandardObject PINCES;
StandardObject BALANCE;
StandardObject HOURGLASS2;
StandardObject EPROUVETTE_6_PACKS;
StandardObject EPROUVETTE_3_PACKS;
StandardObject EPROUVETTE_ALONE;
StandardObject BUCHE_DE_BOIS;
StandardObject LONGUE_VUE;
StandardObject WOOD_PACK_CLASSED;
StandardObject WOOD_PACK_MIXED;
StandardObject FISHING_POLE;

// Quest Items
StandardObject LETTER_FOR_MERCHANT;
StandardObject FAKE_DRAGON_TOOTH;
StandardObject DECAYED_BAT_WINGS;

// Food
Food JAMBON;
Food LONG_SAUSAGE;
Food SAUSAGE_PACK;
Food FAT_JAMBON;
Food CHICKEN;
Food BREAD;
Food PACK_OF_PASTRIES;
Food DEAD_FISHES;

// Potions
Potions BLUE_POTION;
Potions YELLOW_POTION;
Potions BLACK_POTION;
Potions PURPLE_POTION;


// Doors
Doors WOODEN_DOOR;
Doors WOODEN_DOOR_FLIP;
 
// Books
Book ROMANCE_BOOK;

Food LETTUCE;
Gold GOLD;

//////////////////////////////////////////////////////////////////////////////////////////
// Last added objects


//////////////////////////////////////////////////////////////////////////////////////////
INIT_OBJECT_STAT_SETUP
//////////////////////////////////////////////////////////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////////////////
// Some quest objects

	SET_OBJECT                              ( DECAYED_BAT_WINGS )
	OBJ_NAME                                ( "[343]decaying bat wings" )
	OBJ_APPEARANCE                  ( BANJO )
	OBJ_TYPE                                ( JUNK )
	OBJ_SIZE                                ( 11 )
	OBJ_COST                                ( CANNOT_SELL )


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

	SET_OBJECT                       ( LETTUCE )
	OBJ_NAME                         ( "[344]good lettuce" )
	OBJ_APPEARANCE                   ( FRUIT_9 )	// laitue
	OBJ_SIZE                         ( 18 )
	OBJ_TYPE                         ( PAWNSHOP )
	OBJ_BLOCK                        ( __BLOCK_NONE )
	OBJ_COST                         ( 0 )
    //  OBJ_REGAIN_HP                    ( 1 d 10, 3 )  ( hp gain, usable how many time )


/////////////////////////////////////////////////////////////////////////////////////////
// Doors
SET_NAME( WOODEN_DOOR, "[345]wooden door" );
WOODEN_DOOR.appearance = __OBJGROUP_WOODEN_DOOR_CLOSED;
WOODEN_DOOR.lock.key = 0;
WOODEN_DOOR.dwDropFlags = CANNOT_HIDE;
WOODEN_DOOR.size = 1000000;

SET_NAME( WOODEN_DOOR_FLIP, "[345]wooden door" );
WOODEN_DOOR_FLIP.appearance = __OBJGROUP_WOODEN_DOOR_CLOSED_I;
WOODEN_DOOR_FLIP.lock.key = 0;
WOODEN_DOOR_FLIP.dwDropFlags = CANNOT_HIDE;
WOODEN_DOOR_FLIP.size = 1000000;

//////////////////////////////////////////////////////////////////////////////////////////
// Standard objects (no mapping, plain view/get/drop
SET_NAME( CAMP_FIRE, "[346]camp fire" );
CAMP_FIRE.appearance =                          __OBJGROUP_ARROW;
CAMP_FIRE.size = 1000000;

SET_NAME( WOODEN_CHAIR, "[347]wooden chair" );
WOODEN_CHAIR.appearance =                       __OBJGROUP_WOODEN_CHAIR;
WOODEN_CHAIR.blocking = __BLOCK_CAN_FLY_OVER;
WOODEN_CHAIR.dwDropFlags = CANNOT_HIDE;
WOODEN_CHAIR.size = 1000000;

SET_NAME( WOODEN_ROUND_CHAIR, "[347]wooden chair" );
WOODEN_ROUND_CHAIR.appearance =         __OBJGROUP_WOODEN_ROUND_CHAIR;
WOODEN_ROUND_CHAIR.blocking = __BLOCK_CAN_FLY_OVER;
WOODEN_ROUND_CHAIR.dwDropFlags = CANNOT_HIDE;
WOODEN_ROUND_CHAIR.size = 1000000;

SET_NAME( WOODEN_CHAIR_2, "[347]wooden chair" );
WOODEN_CHAIR_2.appearance =                     __OBJGROUP_WOODEN_CHAIR_2;
WOODEN_CHAIR_2.blocking = __BLOCK_CAN_FLY_OVER;
WOODEN_CHAIR_2.dwDropFlags = CANNOT_HIDE;
WOODEN_CHAIR_2.size = 1000000;

SET_NAME( WOODEN_ROUND_CHAIR_2, "[347]wooden chair" );
WOODEN_ROUND_CHAIR_2.appearance =       __OBJGROUP_WOODEN_ROUND_CHAIR_2;
WOODEN_ROUND_CHAIR_2.blocking = __BLOCK_CAN_FLY_OVER;
WOODEN_ROUND_CHAIR_2.dwDropFlags = CANNOT_HIDE;
WOODEN_ROUND_CHAIR_2.size = 1000000;

SET_NAME( WOODEN_CHAIR_FLIP, "[347]wooden chair" );
WOODEN_CHAIR_FLIP.appearance =                  __OBJGROUP_WOODEN_CHAIR_I;
WOODEN_CHAIR_FLIP.blocking = __BLOCK_CAN_FLY_OVER;
WOODEN_CHAIR_FLIP.dwDropFlags = CANNOT_HIDE;
WOODEN_CHAIR_FLIP.size = 1000000;

SET_NAME( WOODEN_CHAIR_2_FLIP, "[347]wooden chair" );
WOODEN_CHAIR_2_FLIP.appearance =                __OBJGROUP_WOODEN_CHAIR_2_I;
WOODEN_CHAIR_2_FLIP.blocking = __BLOCK_CAN_FLY_OVER;
WOODEN_CHAIR_2_FLIP.dwDropFlags = CANNOT_HIDE;
WOODEN_CHAIR_2_FLIP.size = 1000000;

SET_NAME( WOODEN_ROUND_CHAIR_2_FLIP, "[347]wooden chair" );
WOODEN_ROUND_CHAIR_2_FLIP.appearance =  __OBJGROUP_WOODEN_ROUND_CHAIR_2_I;
WOODEN_ROUND_CHAIR_2_FLIP.blocking = __BLOCK_CAN_FLY_OVER;
WOODEN_ROUND_CHAIR_2_FLIP.dwDropFlags = CANNOT_HIDE;
WOODEN_ROUND_CHAIR_2_FLIP.size = 1000000;

SET_NAME( WOODEN_CHAIR_REV, "[347]wooden chair" );
WOODEN_CHAIR_REV.appearance =                           __OBJGROUP_2_WOODEN_CHAIR;
WOODEN_CHAIR_REV.blocking = __BLOCK_CAN_FLY_OVER;
WOODEN_CHAIR_REV.dwDropFlags = CANNOT_HIDE;
WOODEN_CHAIR_REV.size = 1000000;

SET_NAME( WOODEN_CHAIR_2_REV, "[347]wooden chair" );
WOODEN_CHAIR_2_REV.appearance  =                        __OBJGROUP_2_WOODEN_CHAIR_2;
WOODEN_CHAIR_2_REV.blocking = __BLOCK_CAN_FLY_OVER;
WOODEN_CHAIR_2_REV.size = 1000000;

SET_NAME( WOODEN_ROUND_CHAIR_2_REV, "[347]wooden chair" );
WOODEN_ROUND_CHAIR_2_REV.appearance  =          __OBJGROUP_2_WOODEN_ROUND_CHAIR_2;
WOODEN_ROUND_CHAIR_2_REV.blocking = __BLOCK_CAN_FLY_OVER;
WOODEN_ROUND_CHAIR_2_REV.dwDropFlags = CANNOT_HIDE;
WOODEN_ROUND_CHAIR_2_REV.size = 1000000;

SET_NAME( WOODEN_CHAIR_I_REV, "[347]wooden chair" );
WOODEN_CHAIR_I_REV.appearance  =                        __OBJGROUP_2_WOODEN_CHAIR_I;
WOODEN_CHAIR_I_REV.blocking = __BLOCK_CAN_FLY_OVER;
WOODEN_CHAIR_I_REV.dwDropFlags = CANNOT_HIDE;
WOODEN_CHAIR_I_REV.size = 1000000;

SET_NAME( WOODEN_CHAIR_2_I_REV, "[347]wooden chair" );
WOODEN_CHAIR_2_I_REV.appearance  =                      __OBJGROUP_2_WOODEN_CHAIR_2_I;
WOODEN_CHAIR_2_I_REV.blocking = __BLOCK_CAN_FLY_OVER;
WOODEN_CHAIR_2_I_REV.size = 1000000;

SET_NAME( WOODEN_ROUND_CHAIR_2_I_REV, "[347]wooden chair" );
WOODEN_ROUND_CHAIR_2_I_REV.appearance  =        __OBJGROUP_2_WOODEN_ROUND_CHAIR_2_I;
WOODEN_ROUND_CHAIR_2_I_REV.blocking = __BLOCK_CAN_FLY_OVER;
WOODEN_ROUND_CHAIR_2_I_REV.dwDropFlags = CANNOT_HIDE;
WOODEN_ROUND_CHAIR_2_I_REV.size = 1000000;

SET_NAME( EMPTY_MUG, "[348]empty mug" );
EMPTY_MUG.appearance =                          __OBJGROUP_EMPTY_MUG;
SET_NAME( BEER_MUG, "[349]beer mug" );
BEER_MUG.appearance =                           __OBJGROUP_BEER_MUG;
SET_NAME( BEER_MUG_TOO_FULL, "[349]beer mug" );
BEER_MUG_TOO_FULL.appearance =          __OBJGROUP_BEER_MUG_TOO_FULL;
SET_NAME( EMPTY_GLASS, "[350]empty glass" );
EMPTY_GLASS.appearance =                        __OBJGROUP_EMPTY_GLASS;
SET_NAME( BEVERAGE, "[351]beverage" );
BEVERAGE.appearance =                           __OBJGROUP_BEVERAGE;
SET_NAME( CUP_FULL, "[352]full cup" );
CUP_FULL.appearance =                           __OBJGROUP_CUP_FULL;
SET_NAME( WOODEN_CUP, "[353]wooden cup" );
WOODEN_CUP.appearance =                         __OBJGROUP_WOODEN_CUP;
SET_NAME( WOODEN_BOWL, "[354]wooden bowl" );
WOODEN_BOWL.appearance =                        __OBJGROUP_WOODEN_BOWL;
SET_NAME( WOODEN_VASE, "[355]wooden vase" );
WOODEN_VASE.appearance =                        __OBJGROUP_WOODEN_VASE;
SET_NAME( KITCHEN_BOWL, "[356]bowl" );
KITCHEN_BOWL.appearance =                       __OBJGROUP_KITCHEN_BOWL;
SET_NAME( KITCHEN_SPOON, "[357]spoon" );
KITCHEN_SPOON.appearance =                      __OBJGROUP_KITCHEN_SPOON;
SET_NAME( KITCHEN_FORK, "[358]fork" );
KITCHEN_FORK.appearance =                       __OBJGROUP_KITCHEN_FORK;
SET_NAME( KITCHEN_KNIFE, "[359]butter knife" );
KITCHEN_KNIFE.appearance =                      __OBJGROUP_KITCHEN_KNIFE;
SET_NAME( ROULEAU_A_PATE, "[360]rolling pin" );
ROULEAU_A_PATE.appearance =                     __OBJGROUP_ROULEAU_A_PATRE;
SET_NAME( BROOM_ON_WALL, "[361]broom" );
BROOM_ON_WALL.appearance =                      __OBJGROUP_BROOM_ON_WALL;
SET_NAME( BROOM_ON_FLOOR, "[361]broom" );
BROOM_ON_FLOOR.appearance =                     __OBJGROUP_BROOM_ON_FLOOR;

SET_NAME( BANJO, "[362]banjo" );
BANJO.appearance =                                      __OBJGROUP_BANJO;
SET_NAME( TAMBOUR, "[363]drum" );
TAMBOUR.appearance =                            __OBJGROUP_TAMBOUR;
SET_NAME( LONG_WHOOL_BALL, "[364]whool ball" );
LONG_WHOOL_BALL.appearance =            __OBJGROUP_LONG_WHOOL_BALL;
SET_NAME( WHOOL_BALL, "[364]whool ball" );
WHOOL_BALL.appearance =                         __OBJGROUP_WHOOL_BALL;
SET_NAME( GREEN_WHOOL_BALL, "[365]green whool ball" );
GREEN_WHOOL_BALL.appearance =           __OBJGROUP_GREEN_WHOOL_BALL;
SET_NAME( BLUE_WHOOL_BALL, "[366]blue whool ball" );
BLUE_WHOOL_BALL.appearance =            __OBJGROUP_BLUE_WHOOL_BALL;
SET_NAME( CHANDELLE, "[367]candle" );
CHANDELLE.appearance =                          __OBJGROUP_CHANDELLE;
SET_NAME( CHANDELLE_SUR_PIED, "[367]candle" );
CHANDELLE_SUR_PIED.appearance =         __OBJGROUP_CHANDELLE_SUR_PIED;
SET_NAME( MIRROR, "[368]mirror" );
MIRROR.appearance =                                     __OBJGROUP_MIRROR;
SET_NAME( PINCES, "[369]pliers" );
PINCES.appearance =                                     __OBJGROUP_PINCES;
SET_NAME( BALANCE, "[370]scale" );
BALANCE.appearance =                            __OBJGROUP_BALANCE;
SET_NAME( HOURGLASS2, "[371]hour glass" );
HOURGLASS2.appearance =                          __OBJGROUP_HOURGLASS;
SET_NAME( EPROUVETTE_6_PACKS, "[372]test tubes" );
EPROUVETTE_6_PACKS.appearance =         __OBJGROUP_EPROUVETTE_6_PACKS;
SET_NAME( EPROUVETTE_3_PACKS, "[372]test tubes" );
EPROUVETTE_3_PACKS.appearance =         __OBJGROUP_EPROUVETTE_3_PACKS;
SET_NAME( EPROUVETTE_ALONE, "[373]test tube" );
EPROUVETTE_ALONE.appearance =           __OBJGROUP_EPROUVETTE_ALONE;
SET_NAME( BUCHE_DE_BOIS, "[374]wooden log" );
BUCHE_DE_BOIS.appearance =                      __OBJGROUP_BUCHE_DE_BOIS;
SET_NAME( LONGUE_VUE, "[375]telescope" );
LONGUE_VUE.appearance =                         __OBJGROUP_LONGUE_VUE;
SET_NAME( WOOD_PACK_CLASSED, "[376]stack of wooden logs" );
WOOD_PACK_CLASSED.appearance =          __OBJGROUP_WOOD_PACK_CLASSED;
WOOD_PACK_CLASSED.size = 1000000;
SET_NAME( WOOD_PACK_MIXED, "[376]stack of wooden logs" )
WOOD_PACK_MIXED.appearance =            __OBJGROUP_WOOD_PACK_MIXED;
WOOD_PACK_MIXED.size = 1000000;

SET_NAME( FISHING_POLE, "[377]fishing pole" );
FISHING_POLE.appearance =                       __OBJGROUP_FISHING_POLE;


///////////////////////////////////////////////////////////////////////////////////////////
// Food
SET_NAME( JAMBON, "[378]ham" );
JAMBON.appearance =                                     __OBJGROUP_JAMBON;
SET_NAME( LONG_SAUSAGE, "[379]sausage" );
LONG_SAUSAGE.appearance =                       __OBJGROUP_LONG_SAUSAGE;
SET_NAME( SAUSAGE_PACK, "[379]sausage" );
SAUSAGE_PACK.appearance =                       __OBJGROUP_SAUSAGE_PACK;
SET_NAME( FAT_JAMBON, "[378]ham" );
FAT_JAMBON.appearance =                         __OBJGROUP_FAT_JAMBON;
SET_NAME( CHICKEN, "[380]chicken" );
CHICKEN.appearance =                            __OBJGROUP_CHIKEN;
SET_NAME( BREAD, "[381]bread" );
BREAD.appearance =                                      __OBJGROUP_BREAD;
SET_NAME( PACK_OF_PASTRIES, "[382]pastry" );
PACK_OF_PASTRIES.appearance =           __OBJGROUP_PACK_OF_PASTRIES;
SET_NAME( DEAD_FISHES, "[383]dead fish" );
DEAD_FISHES.appearance =                        __OBJGROUP_DEAD_FISHES;

////////////////////////////////////////////////////////////////////////////////////////////
// potions
SET_NAME( BLUE_POTION, "[384]blue potion" );
BLUE_POTION.appearance =        __OBJGROUP_BLUE_POTION;
// TODO spell in potions!               
SET_NAME( YELLOW_POTION, "[385]yellow potion" );
YELLOW_POTION.appearance =      __OBJGROUP_YELLOW_POTION;
SET_NAME( BLACK_POTION, "[386]black potion" );
BLACK_POTION.appearance =       __OBJGROUP_BLACK_POTION;
SET_NAME( PURPLE_POTION, "[387]purple potion" );
PURPLE_POTION.appearance =      __OBJGROUP_PURPLE_POTION;

//////////////////////////////////////////////////////////////////////////////////////////
// Quest items
SET_NAME( LETTER_FOR_MERCHANT, "[388]letter for merchant" );
LETTER_FOR_MERCHANT.appearance = __OBJGROUP_SCROLL_OUVERT;
LETTER_FOR_MERCHANT.text.csText = "[389]This looks like an administrative paper signed by the lord of LightHaven.";
SET_NAME( FAKE_DRAGON_TOOTH, "[390]dragon tooth" );
FAKE_DRAGON_TOOTH.appearance = __OBJGROUP_ARROW;

// Books
SET_NAME( ROMANCE_BOOK, "[391]romance book" );
ROMANCE_BOOK.appearance = __OBJGROUP_RED_BOOK;
ROMANCE_BOOK.text.csText = "[392]The books is about the story of a delicate young elven female\
 fallen hopelessly in love with a strong female troll. You passionatly devour the book,\
 to find out that the elf child finally gets crushed by her lover. A small tear drops from\
 your eye to your cheek, crushing your feelings like a troll would crush an elf.";


SET_NAME( DECOR001, "[152]Chest" );
DECOR001.appearance = __OBJGROUP_CHEST;
DECOR001.blocking   = __BLOCK_CAN_FLY_OVER;
SET_NAME( DECOR002, "[152]Chest" );
DECOR002.appearance = __OBJGROUP_CHEST_OPEN;
DECOR002.blocking   = __BLOCK_CAN_FLY_OVER;
SET_NAME( DECOR003, "[7268]Basket" );
DECOR003.appearance = __OBJGROUP_BASKET_CLOSE;
DECOR003.blocking   = __BLOCK_CAN_FLY_OVER;
SET_NAME( DECOR004, "[7268]Basket" );
DECOR004.appearance = __OBJGROUP_BASKET_OPEN;
DECOR004.blocking   = __BLOCK_CAN_FLY_OVER;
SET_NAME( DECOR005, "[7269]Backpack" );
DECOR005.appearance = __OBJGROUP_BACKPACK;
SET_NAME( DECOR006, "[7270]Bandages" );
DECOR006.appearance = __OBJGROUP_BANDAGES_PACK;// specific to bandages
SET_NAME( DECOR007, "[7271]Key hold" );
DECOR007.appearance = __OBJGROUP_KEY_HOLD;     // specific to keys
SET_NAME( DECOR008, "[7272]Gold bar" );
DECOR008.appearance = __OBJGROUP_GOLD_BAR_PACK;// specific to gold bars
SET_NAME( DECOR009, "[7273]Bronze bar" );
DECOR009.appearance = __OBJGROUP_BRONZE_BAR_PACK;// specific to bronze bars
SET_NAME( DECOR010, "[7274]Iron bar" );
DECOR010.appearance = __OBJGROUP_IRON_BAR_PACK;// specific to iron bars
SET_NAME( DECOR011, "[7268]Basket" );
DECOR011.appearance = __OBJGROUP_WATERBASKET;// specific to water
SET_NAME( DECOR012, "[7268]Basket" );
DECOR012.appearance = __OBJGROUP_EMPTY_BASKET;// waterbasket, empty
SET_NAME( DECOR013, "[7275]Arrow pack" );
DECOR013.appearance = __OBJGROUP_ARROW_PACK;// specific to arrows.
SET_NAME( DECOR014, "[7268]Basket" );
DECOR014.appearance = __OBJGROUP_BASKET_FULL_WATER;// ahh bordel, meme affaire!
DECOR014.blocking   = __BLOCK_CAN_FLY_OVER;
SET_NAME( DECOR015, "[7268]Basket" );
DECOR015.appearance = __OBJGROUP_BASKET_FULL_FRUIT;//ahh bordel, meme affaire!
DECOR015.blocking   = __BLOCK_CAN_FLY_OVER;
SET_NAME( DECOR016, "[7276]Crates" );
DECOR016.appearance = __OBJGROUP_CRATES;
DECOR016.blocking   = __BLOCK_CAN_FLY_OVER;
SET_NAME( DECOR017, "[7276]Crates" );
DECOR017.appearance = __OBJGROUP_RECTANGLE_CRATES;
DECOR017.blocking   = __BLOCK_CAN_FLY_OVER;
SET_NAME( DECOR018, "[7276]Crates" );
DECOR018.appearance = __OBJGROUP_CUBIQ_CRATES;
DECOR018.blocking   = __BLOCK_CAN_FLY_OVER;

// Gold
GOLD.appearance   = __OBJGROUP_COINS_PILE;
SET_NAME( GOLD, "[33]Gold" );
	
CLOSE_INIT_OBJECT_STAT_SETUP

void ObjectDLLDestroy(){

}
