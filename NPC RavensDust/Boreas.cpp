//////////////////////////////////////////////////////////////////////
// Boreas.cpp: implementation of the Boreas class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Boreas.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Boreas::Boreas()
{}

Boreas::~Boreas()
{}
 
extern NPCstructure::NPC BoreasNPC;

void Boreas::Create( ){
    npc = BoreasNPC;
	SET_NPC_NAME( "[2920]Boreas" );
	npc.InitialPos.X = 1525; // NEED A POSITION FOR THIS NPC!!!!!
	npc.InitialPos.Y = 2562; // NEED A POSITION FOR THIS NPC!!!!!
	npc.InitialPos.world = 0;
}

void Boreas::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT PLANT = 1;
CONSTANT GIVEPLANT = 2;
CONSTANT GIVEPLANT2 = 3;
CONSTANT PERSUADE = 4;
CONSTANT PERSUADE2 = 5;
CONSTANT PERSUADE3 = 6;
CONSTANT PERSUADE4 = 7;

InitTalk

Begin
INTL( 4240, "Welcome to my store.")

Command(INTL( 3694, " NAME"))
INTL( 4241, "Just call me Boreas.")

Command(INTL( 4242, "BOREAS"))
INTL( 4243, "Yes, just Boreas.")

Command(INTL( 489, "WORK"))
INTL( 4244, "My trade is in the brewing of potions of which I am very skilled. If you "
"travel alot, then you had better \"buy\" something to keep you alive in case of danger. "
"I also have a few \"scrolls\" in which you might be interested as well.")

Command(INTL( 1159, "SCROLL"))
INTL( 4245, "Yes.. I have plenty of scrolls that you could use. Especially if you need "
"a fast way of going back and forth between \"Arakas\" and \"Raven's\" \"Dust\".")

Command(INTL( 666, "POTION"))
INTL( 4246, "I have several different kinds of potions, all of which are for \"sale\".")

Command2(INTL( 1304, "BUY"),INTL( 4247, "SALE"))
INTL( 4248, "Ahh, a customer!") 

	IF (CheckFlag(__QUEST_ISLAND_ACCESS) == 1)
		CreateItemList
			AddBuyItem( 12, __OBJ_TORCH )
			AddBuyItem( 50, __OBJ_LIGHT_HEALING_POTION )
			AddBuyItem( 50, __OBJ_POTION_OF_MANA )
			AddBuyItem( 125, __OBJ_HEALING_POTION )
			AddBuyItem( 150, __OBJ_MANA_ELIXIR ) 
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
			AddBuyItem( 150, __OBJ_MANA_ELIXIR ) 
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
			AddBuyItem( 150, __OBJ_MANA_ELIXIR ) 
			AddBuyItem( 5000, __OBJ_SCROLL_OF_LIGHTHAVEN )
			AddBuyItem( 10000, __OBJ_SCROLL_OF_WINDHOWL )
		SendBuyItemList
	ENDIF

Command(INTL( 1306, "SELL"))
	INTL( 1307, "What is it that you wish to sell?")

	CreateItemList
		AddSellItem( PAWNSHOP, 0, 100000 )
		AddSellItem( MAGIC, 0, 100000 )
		AddSellItem( POTION, 0, 100000 )
		AddSellItem( JEWEL, 0, 100000 )
		AddSellItem( MAGIC | JEWEL, 0, 100000 ) 
		AddSellItem( MAGIC | JEWEL | ARMOR, 0, 100000 )
	SendSellItemList( INTL( 4250, "Come back when you have something I need!") )

Command(INTL( 3918, "VISITOR"))
""
IF (CheckFlag(__QUEST_VISITOR_SPOTTED) < 3)
	Conversation
	INTL( 4252, "Business isn't what it used to be, so if anyone strange had entered my store, I would've seen "
	"him right away.")
ELSEIF (CheckFlag(__QUEST_VISITOR_SPOTTED) == 3)
	Conversation
	INTL( 4253, "Ahh, perhaps you are referring to the young fellow that was just here a moment ago. He looked quite "
	"the nervous lot, to tell you the truth. I don't know if he was in trouble, but he sure seemed to be "
	"in quite a hurry. He did ask me where Kiadus' shop was located, if that helps you.")
	GiveFlag(__QUEST_VISITOR_SPOTTED, 4)
ELSEIF (CheckFlag(__QUEST_VISITOR_SPOTTED) >= 4)
	Conversation
	INTL( 4254, "I distinctly remember him asking me where Kiadus' shop was located. Perhaps you should see if he is "
	"still there.")
ENDIF	

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 4255, "Eh, that's the name of this island.")

Command(INTL( 998, "SILVERSKY"))
INTL( 4257, "Yes, this town is named Silversky.")

Command(INTL( 515, "ARAKAS"))
INTL( 4258, "Raven's Dust's sister island located somewhere to the north.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 4259, "A small town on \"Arakas\".")

Command(INTL( 514, "WINDHOWL"))
INTL( 4260, "Yet another town of \"Arakas\".")

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 4261, "I hope I'll see you again!") BREAK
	
Default
INTL( 2025, "I have no idea.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Boreas::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Boreas data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA
	
		NPC_SELL( 12, __OBJ_TORCH )
		NPC_SELL( 50, __OBJ_LIGHT_HEALING_POTION )
		NPC_SELL( 50, __OBJ_POTION_OF_MANA )
		NPC_SELL( 125, __OBJ_HEALING_POTION ) 
		NPC_SELL( 150, __OBJ_MANA_ELIXIR) 
		NPC_SELL( 5000, __OBJ_SCROLL_OF_LIGHTHAVEN )
		NPC_SELL( 10000, __OBJ_SCROLL_OF_WINDHOWL )
		NPC_SELL( 25000, __OBJ_SCROLL_OF_SILVERSKY )
		NPC_SELL( 50000, __OBJ_SCROLL_OF_STONECREST ) 

		NPC_BUY( PAWNSHOP, 0, 100000 )
		NPC_BUY( MAGIC, 0, 100000 )
		NPC_BUY( POTION, 0, 100000 )
		NPC_BUY( JEWEL, 0, 100000 )
		NPC_BUY( MAGIC | JEWEL, 0, 100000 )
		NPC_BUY( MAGIC | JEWEL | ARMOR, 0, 100000 )


		NPC_SOLD_ITEM( INTL( 4262, "Very good.") )
		NPC_FAILED_SELL( INTL( 4263, "You seem to be short of funds right now. Come back later.") )
		NPC_BOUGHT_ITEM( INTL( 4264, "Splendid, here is the money I owe you.") )
	
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
