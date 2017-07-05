//////////////////////////////////////////////////////////////////////
// Yolak.cpp: implementation of the Yolak class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Yolak.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Yolak::Yolak()
{}

Yolak::~Yolak()
{}

extern NPCstructure::NPC YolakNPC;

//Name: Yolak.
//Statistique: Windhowl Paysan.
//Position: (2167, 635)
//World: 0
//Description: Shopkeeper.
//Body: Shopkeeper.

//////////////////////////////////////////////////////////////////////////////////////////
void Yolak::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Yolak
//
{
	npc = YolakNPC;
	SET_NPC_NAME( "[3028]Yolak" );
	npc.InitialPos.X = 1649;
	npc.InitialPos.Y = 1243;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Yolak::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Yolak
//
{

InitTalk

Begin
INTL( 2769, "Come in, come in!")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2770, "I am Yolak. I sell items of all kind. Do you wish to \"buy\" or \"sell\" "
"anything currently?")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2771, "I sell items of any kind. Do you wish to \"buy\" or \"sell\" anything?")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 7174, "Devilish monster? Cursed from beyond? Marked from eternity? Yeah, right!")

Command(INTL( 523, "ANNABELLE"))
INTL( 584, "I wonder who she is.")

Command(INTL( 1304, "BUY"))
INTL( 2772, "Well, what do you wish to buy?")
									   
IF (CheckFlag(__QUEST_ISLAND_ACCESS) == 1)
	CreateItemList
		AddBuyItem( 12, __OBJ_TORCH )
		AddBuyItem( 50, __OBJ_LIGHT_HEALING_POTION )
		AddBuyItem( 50, __OBJ_POTION_OF_MANA )
		AddBuyItem( 125, __OBJ_HEALING_POTION ) 
		AddBuyItem( 5000, __OBJ_SCROLL_OF_LIGHTHAVEN )
		AddBuyItem( 10000, __OBJ_SCROLL_OF_WINDHOWL )
		AddBuyItem( 25000, __OBJ_SCROLL_OF_SILVERSKY )
	SendBuyItemList
ELSEIF (CheckFlag(__QUEST_ISLAND_ACCESS) == 2)
	CreateItemList
		AddBuyItem( 12, __OBJ_TORCH )
		AddBuyItem( 50, __OBJ_LIGHT_HEALING_POTION )
		AddBuyItem( 50, __OBJ_POTION_OF_MANA )
		AddBuyItem( 125, __OBJ_HEALING_POTION ) 
		AddBuyItem( 5000, __OBJ_SCROLL_OF_LIGHTHAVEN )
		AddBuyItem( 10000, __OBJ_SCROLL_OF_WINDHOWL )
		AddBuyItem( 25000, __OBJ_SCROLL_OF_SILVERSKY )
		AddBuyItem( 50000, __OBJ_SCROLL_OF_STONECREST ) 
	SendBuyItemList
ELSE
	CreateItemList
		AddBuyItem( 12, __OBJ_TORCH )
		AddBuyItem( 50, __OBJ_LIGHT_HEALING_POTION )
		AddBuyItem( 50, __OBJ_POTION_OF_MANA )
		AddBuyItem( 125, __OBJ_HEALING_POTION ) 
		AddBuyItem( 5000, __OBJ_SCROLL_OF_LIGHTHAVEN )
		AddBuyItem( 10000, __OBJ_SCROLL_OF_WINDHOWL )
	SendBuyItemList
ENDIF

Command(INTL( 1306, "SELL"))
INTL( 2773, "What do you want to sell?")

CreateItemList
  AddSellItem( PAWNSHOP, 0, 100000 )
  AddSellItem( MAGIC, 0, 100000 )
  AddSellItem( POTION, 0, 100000 )
  AddSellItem( JEWEL, 0, 100000 )
  AddSellItem( MAGIC | JEWEL, 0, 100000 )
  AddSellItem( MAGIC | JEWEL | ARMOR, 0, 100000 )
SendSellItemList( INTL( 2743, "Sorry but I do not see anything interesting in your inventory!") )

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 973, "Goodbye.") BREAK

Default

INTL( 2774, "Don't bother with this.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Yolak::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA
  NPC_SELL( 50, __OBJ_LIGHT_HEALING_POTION )
  NPC_SELL( 50, __OBJ_POTION_OF_MANA )
  NPC_SELL( 125, __OBJ_HEALING_POTION ) 
		NPC_SELL( 5000, __OBJ_SCROLL_OF_LIGHTHAVEN )
		NPC_SELL( 10000, __OBJ_SCROLL_OF_WINDHOWL )
		NPC_SELL( 25000, __OBJ_SCROLL_OF_SILVERSKY ) 
		NPC_SELL( 50000, __OBJ_SCROLL_OF_STONECREST ) 
		NPC_SELL( 12, __OBJ_TORCH )

  NPC_BUY( PAWNSHOP, 0, 100000 )
  NPC_BUY( MAGIC, 0, 100000 )
  NPC_BUY( POTION, 0, 100000 )
		NPC_BUY( JEWEL, 0, 100000 )
		NPC_BUY( MAGIC | JEWEL, 0, 100000 )
  NPC_BUY( MAGIC | JEWEL | ARMOR, 0, 100000 )

		NPC_SOLD_ITEM( INTL( 2748, "Indeed, that is a fine choice of yours.") )
		NPC_FAILED_SELL( INTL( 2749, "Oy! You do not have enough money my friend!") )
		NPC_BOUGHT_ITEM( INTL( 2775, "Here's ya money") )
	
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
