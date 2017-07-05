// Structures shared through the different DLL's and TFC Server

//#include <afx.h>
#include <cmath>
#include "windows_linux.h"
#ifndef __SHAREDSTRUCTURES_H
#define __SHAREDSTRUCTURES_H

#define __PLAYER		1
#define __CREATURE		2
#define __OBJECT		3

#define __SHOP_DATA		0x1
#define __TEACH_DATA	0x2
#define __TRAIN_DATA	0x3


#define __BUY			0x1
// Returns a price but doesn't sell the item
#define __SELL			0x2

#define SAME_POS( wl_1, wl_2 ) (wl_1.X == wl_2.X && wl_1.Y == wl_2.Y && wl_1.world == wl_2.world)
//////////////////////////////////////////////////////////////////////////////////////////
struct WorldPos
{
	int X, Y;
	int world;

	bool operator== (const WorldPos &otherPos) const {
		return (X == otherPos.X && Y == otherPos.Y && world == otherPos.world);
	}
	bool AreInRange(const WorldPos &otherPos, int range) const {
		return ( world == otherPos.world && ::abs(X - otherPos.X) <= range && ::abs(Y - otherPos.Y) <= range );
	}
};
//////////////////////////////////////////////////////////////////////////////////////////
struct MonsterEncounter
{
	WORD wMinX, wMaxX;
	WORD wGroupID;
};
//////////////////////////////////////////////////////////////////////////////////////////
typedef struct _NPC_DATA{
	BYTE DataID;
	LPVOID Data;
} NPC_DATA, *LPNPC_DATA;
//////////////////////////////////////////////////////////////////////////////////////////
typedef struct _TEACH_DATA{
	WORD wSkillID;			// ID of the skill.
} TEACH_DATA, *LPTEACH_DATA;
//////////////////////////////////////////////////////////////////////////////////////////
typedef struct _TRAIN_DATA{
	WORD wSkillID;			// ID of the skill.
	WORD wSkillPnts;		// Number of skill points to spend on skill.
} TRAIN_DATA, *LPTRAIN_DATA;
//////////////////////////////////////////////////////////////////////////////////////////
typedef struct _SHOP_DATA{
	BYTE  Action;	// Either BUY or SELL
	WORD  Item;		// Item ID of the item (if buy)
	WORD  wQuantity;	// Quantity of items to buy.
	DWORD ID;		// ID of the item to sell (if sell)
} SHOP_DATA, *LPSHOP_DATA;


#define CANCEL_DEATH				0x01	// Cancels the death. Unit dying won't die.
#define DESTROY_UNIT_ON_DEATH		0x02	// Destroy this object even if death was cancelled.
#define SAVE_UNIT_ON_DEATH			0x04	// Don't remove this object from backpack or equipped.
#define DESTROY_BACKPACK			0x08	// Destroy backpack and equipped items.

//////////////////////////////////////////////////////////////////////////////////////////
typedef struct _DEATH_DATA{
	BYTE bDeathType;
} DEATH_DATA, *LPDEATH_DATA;

#endif
