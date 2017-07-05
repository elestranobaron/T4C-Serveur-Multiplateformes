#pragma hdrstop
#include "Gwen.h"

Gwen::Gwen()
{}

Gwen::~Gwen()
{}

extern NPCstructure::NPC GwenNPC;

void Gwen::Create( void )
{
    npc = GwenNPC;
	SET_NPC_NAME( "[3006]Gwen" );
    npc.InitialPos.X = 1667;
    npc.InitialPos.Y = 1271;
	npc.InitialPos.world = 0;
    npc.boPrivateTalk = TRUE;
}

void Gwen::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
INTL( 2340, "Welcome my friend, welcome!")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2341, "I am Gwen, the best and only armor shopkeeper in town! You won't find "
"a better deal anywhere else, I assure you! Do you wish to \"buy\" or \"sell\" "
"anything?")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2342, "I work as an armorer. I sell imported armor and sometimes even make them "
"myself. Everything here is of the finest quality! Do you want to \"buy\" or "
"\"sell\" anything?")

Command(INTL( 523, "ANNABELLE"))
INTL( 584, "I wonder who she is.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 820, "Balork's curse? That's horrible!")

Command(INTL( 514, "WINDHOWL"))
INTL( 2343, "Windhowl? That is the name of this town.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 2344, "It is our sister town on the eastern part of this island. Another armorer "
"named \"Rolph\" has set up his armor shop there.")

Command(INTL( 2345, "ROLPH"))
INTL( 2346, "He is an armorer who lives in \"Lighthaven\". He is, of course, less "
"skilled than I am.")

Command(INTL( 1304, "BUY"))
INTL( 2347, "What do you wish to buy?")

CreateItemList

   AddBuyItem(  15,  __OBJ_CLOTH_PANTS )
   AddBuyItem(  15,  __OBJ_CLOTH_VEST )
   AddBuyItem( 212,  __OBJ_LEATHER_BELT )
   AddBuyItem( 248,  __OBJ_LEATHER_GLOVES )
   AddBuyItem( 261,  __OBJ_LEATHER_HELMET )
   AddBuyItem( 269,  __OBJ_LEATHER_PANTS )
   AddBuyItem( 245,  __OBJ_LEATHER_BOOTS )
   AddBuyItem( 607,  __OBJ_LEATHER_ARMOR )
   AddBuyItem( 700,  __OBJ_RED_CAPE )
   AddBuyItem( 1086, __OBJ_STUDDED_LEATHER_BELT )
   AddBuyItem( 1402, __OBJ_STUDDED_LEATHER_GLOVES )
   AddBuyItem( 1510, __OBJ_STUDDED_LEATHER_HELMET )
   AddBuyItem( 1579, __OBJ_STUDDED_LEATHER_PANTS )
   AddBuyItem( 1372, __OBJ_STUDDED_LEATHER_BOOTS )
   AddBuyItem( 4538, __OBJ_STUDDED_LEATHER_ARMOR )
   AddBuyItem( 3355, __OBJ_WOODEN_SHIELD )
   AddBuyItem( 7389, __OBJ_ROUND_SHIELD )

   AddBuyItem( 2308, __OBJ_RINGMAIL_GIRDLE )
   AddBuyItem( 10039,__OBJ_RINGMAIL_ARMOR )
   AddBuyItem( 3015, __OBJ_RINGMAIL_GAUNTLETS ) 
   AddBuyItem( 3258, __OBJ_RINGMAIL_HELMET )
   AddBuyItem( 3413, __OBJ_RINGMAIL_LEGGINGS )
   AddBuyItem( 2949, __OBJ_RINGMAIL_BOOTS ) 

SendBuyItemList

Command(INTL( 1306, "SELL"))
INTL( 2348, "What item do you wish to sell?")

CreateItemList
   AddSellItem( ARMOR, 0, 100000 )
    AddSellItem( MAGIC | ARMOR, 0, 100000 )
    AddSellItem( JEWEL | ARMOR, 0, 100000 )
    AddSellItem( MAGIC | JEWEL | ARMOR, 0, 100000)
SendSellItemList( INTL( 2349, "I do not see anything interesting enough for me to buy.") )

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 973, "Goodbye.") BREAK

Default
    INTL( 2331, "That is not my business.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Gwen::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Rolph data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

   NPC_SHOP_DATA

   NPC_SELL(  15,   __OBJ_CLOTH_PANTS )
   NPC_SELL(  15,   __OBJ_CLOTH_VEST )
   NPC_SELL( 212,   __OBJ_LEATHER_BELT )
   NPC_SELL( 248,   __OBJ_LEATHER_GLOVES )
   NPC_SELL( 261,   __OBJ_LEATHER_HELMET )
   NPC_SELL( 269,   __OBJ_LEATHER_PANTS )
   NPC_SELL( 245,   __OBJ_LEATHER_BOOTS )
   NPC_SELL( 607,   __OBJ_LEATHER_ARMOR )
   NPC_SELL( 700,   __OBJ_RED_CAPE )
   NPC_SELL( 1086,  __OBJ_STUDDED_LEATHER_BELT )
   NPC_SELL( 1402,  __OBJ_STUDDED_LEATHER_GLOVES )
   NPC_SELL( 1510,  __OBJ_STUDDED_LEATHER_HELMET )
   NPC_SELL( 1579,  __OBJ_STUDDED_LEATHER_PANTS )
   NPC_SELL( 1372,  __OBJ_STUDDED_LEATHER_BOOTS )
   NPC_SELL( 4538,  __OBJ_STUDDED_LEATHER_ARMOR )
   NPC_SELL( 3355,  __OBJ_WOODEN_SHIELD )
   NPC_SELL( 7389,  __OBJ_ROUND_SHIELD )

   NPC_SELL( 2308, __OBJ_RINGMAIL_GIRDLE )
	NPC_SELL( 10039, __OBJ_RINGMAIL_ARMOR )
   NPC_SELL( 3015, __OBJ_RINGMAIL_GAUNTLETS ) 
   NPC_SELL( 3258, __OBJ_RINGMAIL_HELMET )
   NPC_SELL( 3413, __OBJ_RINGMAIL_LEGGINGS )
   NPC_SELL( 2949, __OBJ_RINGMAIL_BOOTS ) 

   NPC_BUY( ARMOR, 0, 100000 )
   NPC_BUY( MAGIC | ARMOR, 0, 100000 )
   NPC_BUY( JEWEL | ARMOR, 0, 100000 )
   NPC_BUY( MAGIC | JEWEL | ARMOR, 0, 100000)

   NPC_SOLD_ITEM( INTL( 2350, "Indeed a very fine choice.") )
   NPC_FAILED_SELL( INTL( 2351, "You do not have enough money my friend!") )
   NPC_BOUGHT_ITEM( INTL( 2352, "Here is your money, come again!") )
	
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
