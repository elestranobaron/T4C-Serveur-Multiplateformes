//////////////////////////////////////////////////////////////////////
// Taliron.cpp: implementation of the Taliron class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Taliron.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Taliron::Taliron()
{}

Taliron::~Taliron()
{}

extern NPCstructure::NPC ShopKeeper;

void Taliron::Create( ){
	npc = ShopKeeper;
	SET_NPC_NAME( "[2984]Taliron" );
	npc.InitialPos.X = 1554;
	npc.InitialPos.Y = 2515;
	npc.InitialPos.world = 0;
}

void Taliron::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk
 
Begin
""
IF (TFCTime::IsDay())
	Conversation
	INTL( 5759, "Hello, and welcome!")	
ELSEIF (TFCTime::IsSleepTime())
	Conversation
	INTL( 7698, "*yawn* It's a bit late, don't you think? I hope what you've got to say is important.")
ELSE
	Conversation
	INTL( 5760, "Good evening.")
ENDIF

Command(INTL( 3694, " NAME"))
INTL( 5761, "Taliron is my name!")

Command(INTL( 5762, "TALIRON"))
INTL( 5256, "Yes, that is my name.")

Command(INTL( 489, "WORK"))
INTL( 5763, "I make the strongest and most durable \"armor\" around these parts!")

Command2(INTL( 916, "ARMOR"),INTL( 1304, "BUY"))
""
IF (TFCTime::IsSleepTime())
	Conversation
	INTL( 5765, "I would show you what I have for sale, but it is rather late. Come back tomorrow.")
ELSE
	Conversation
	INTL( 5764, "I have everything you need right here my friend! Just buy what you need!")
	CreateItemList
	
		AddBuyItem( 700,   __OBJ_RED_CAPE )
		AddBuyItem( 1086,  __OBJ_STUDDED_LEATHER_BELT )
		AddBuyItem( 1402,  __OBJ_STUDDED_LEATHER_GLOVES )
		AddBuyItem( 1510,  __OBJ_STUDDED_LEATHER_HELMET )
		AddBuyItem( 1579,  __OBJ_STUDDED_LEATHER_PANTS )
		AddBuyItem( 1372,  __OBJ_STUDDED_LEATHER_BOOTS )
	   AddBuyItem( 4538,  __OBJ_STUDDED_LEATHER_ARMOR )
		
	   AddBuyItem( 2308, __OBJ_RINGMAIL_GIRDLE )
	   AddBuyItem( 10039, __OBJ_RINGMAIL_ARMOR )
	   AddBuyItem( 3015, __OBJ_RINGMAIL_GAUNTLETS ) 
	   AddBuyItem( 3258, __OBJ_RINGMAIL_HELMET )
	   AddBuyItem( 3413, __OBJ_RINGMAIL_LEGGINGS )
	   AddBuyItem( 2949, __OBJ_RINGMAIL_BOOTS ) 

		AddBuyItem( 4694,  __OBJ_CHAINMAIL_GIRDLE )
		AddBuyItem( 20777, __OBJ_CHAINMAIL )
		AddBuyItem( 6165,  __OBJ_CHAINMAIL_GLOVES )
		AddBuyItem( 6670,  __OBJ_CHAINMAIL_COIF )
		AddBuyItem( 6992,  __OBJ_CHAINMAIL_LEGGINGS )
		AddBuyItem( 6072, __OBJ_CHAINMAIL_BOOTS) 

		AddBuyItem( 7389,  __OBJ_ROUND_SHIELD )
		AddBuyItem( 25990, __OBJ_LARGE_SHIELD )
	SendBuyItemList
ENDIF

Command(INTL( 1306, "SELL"))
""
IF (TFCTime::IsSleepTime())
	Conversation
	INTL( 5766, "You should come back during the day, we're closed at night.")
ELSE
	Conversation
	INTL( 2773, "What do you want to sell?")
	CreateItemList
		AddSellItem( ARMOR, 0, 100000 )
		AddSellItem( MAGIC | ARMOR, 0, 100000 )
		AddSellItem( JEWEL | ARMOR, 0, 100000 )
	AddSellItem( JEWEL | MAGIC | ARMOR, 0, 100000 )
	SendSellItemList(INTL( 1963, "I do not see anything interesting in your inventory."))
ENDIF

Command(INTL( 3918, "VISITOR"))
INTL( 5767, "I haven't seen anyone like that, maybe Belagan can tell you more.")

Command(INTL( 5363, "KIADUS"))
INTL( 5768, "His shop is just around the corner.")

Command(INTL( 4880, "SWORD"))
INTL( 5769, "I don't know anything about a sword. I only deal in armor.")

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 5770, "Come back anytime!") BREAK

Default
INTL( 5771, "I wouldn't know..")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Taliron::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Taliron data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA


   NPC_SELL( 700,   __OBJ_RED_CAPE )
	NPC_SELL( 1086,  __OBJ_STUDDED_LEATHER_BELT )
   NPC_SELL( 1402,  __OBJ_STUDDED_LEATHER_GLOVES )
   NPC_SELL( 1510,  __OBJ_STUDDED_LEATHER_HELMET )
   NPC_SELL( 1579,  __OBJ_STUDDED_LEATHER_PANTS )
   NPC_SELL( 1372,  __OBJ_STUDDED_LEATHER_BOOTS )
   NPC_SELL( 4538,  __OBJ_STUDDED_LEATHER_ARMOR )

   NPC_SELL( 2308,  __OBJ_RINGMAIL_GIRDLE )
   NPC_SELL( 10039, __OBJ_RINGMAIL_ARMOR )
   NPC_SELL( 3015,  __OBJ_RINGMAIL_GAUNTLETS ) 
   NPC_SELL( 3258,  __OBJ_RINGMAIL_HELMET )
   NPC_SELL( 3413,  __OBJ_RINGMAIL_LEGGINGS )
   NPC_SELL( 2949,  __OBJ_RINGMAIL_BOOTS ) 

	NPC_SELL( 4694,  __OBJ_CHAINMAIL_GIRDLE )
   NPC_SELL( 20777, __OBJ_CHAINMAIL )
   NPC_SELL( 6165,  __OBJ_CHAINMAIL_GLOVES )
   NPC_SELL( 6670,  __OBJ_CHAINMAIL_COIF )
   NPC_SELL( 6992,  __OBJ_CHAINMAIL_LEGGINGS )
   NPC_SELL( 6072,  __OBJ_CHAINMAIL_BOOTS) 

   NPC_SELL( 7389,  __OBJ_ROUND_SHIELD )
   NPC_SELL( 25990, __OBJ_LARGE_SHIELD )

   NPC_BUY( ARMOR, 0, 100000 )
   NPC_BUY( MAGIC | ARMOR, 0, 100000 ) 
   NPC_BUY( JEWEL | ARMOR, 0, 100000 )
	NPC_BUY( JEWEL | MAGIC | ARMOR, 0, 100000 )

	NPC_SOLD_ITEM( INTL( 5772, "Very good!") )
	NPC_FAILED_SELL( INTL( 5773, "You don't have enough gold!") )
	NPC_BOUGHT_ITEM( INTL( 5774, "There you go.") )
	
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
