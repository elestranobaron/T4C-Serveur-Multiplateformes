//////////////////////////////////////////////////////////////////////
// Karahn.cpp: implementation of the Karahn class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Karahn.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Karahn::Karahn()
{}

Karahn::~Karahn()
{}

extern NPCstructure::NPC ShopKeeper;

void Karahn::Create( ){
	npc = ShopKeeper;
	SET_NPC_NAME( "[2898]A traveling merchant" );
	npc.InitialPos.X = 2286; 
	npc.InitialPos.Y = 124; 
	npc.InitialPos.world = 0;
}

void Karahn::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT BROWSE = 1;

InitTalk

Begin
""
IF (TFCTime::IsDay())
	Conversation
	INTL( 7090, "Good day to you, friend. What can I do for you on such a splendid day?")
ELSE
	Conversation
	INTL( 7091, "Good evening to you friend. How may I help you?")
ENDIF

Command(INTL( 483, "NAME"))
INTL( 7092, "I am known throughout these parts as Karahn.")

Command(INTL( 7093, "KARAHN"))
INTL( 5256, "Yes, that is my name.")

Command(INTL( 489, "WORK"))
INTL( 7094, "I travel the countryside selling my \"wares\".")

Command(INTL( 1959, "WARES"))
INTL( 7095, "Why, I deal in \"weapons\" of high quality! Would you like to take a look at them?")
SetYesNo(BROWSE)

Command(INTL( 1304, "BUY"))
INTL( 7096, "You want to see what I have to sell, is that it?")
SetYesNo(BROWSE)

YES(BROWSE)
	CreateItemList
		AddBuyItem( 87, __OBJ_RUSTED_SHORT_SWORD_1 )
		AddBuyItem( 1815, __OBJ_RUSTED_LONG_SWORD_1 )
		AddBuyItem( 15798, __OBJ_POLISHED_SHORT_SWORD_1 )
		AddBuyItem( 27969, __OBJ_POLISHED_LONG_SWORD_1 )
		AddBuyItem( 43587, __OBJ_POLISHED_BROADSWORD_1 )
		AddBuyItem( 7083, __OBJ_RUSTED_HAND_AXE_1 )
		AddBuyItem( 62661, __OBJ_POLISHED_HAND_AXE_1 )
		AddBuyItem( 87, __OBJ_RUSTED_DIRK_1 )
		AddBuyItem( 1815, __OBJ_RUSTED_DAGGER_1 )
		AddBuyItem( 15798, __OBJ_POLISHED_DIRK_1 )
		AddBuyItem( 27969, __OBJ_POLISHED_DAGGER_1 )
		AddBuyItem( 87, __OBJ_WOODEN_CLUB_1 )
		AddBuyItem( 7083, __OBJ_STEEL_REINFORCED_CLUB_1 )
		AddBuyItem( 15798, __OBJ_STEEL_REINFORCED_WARHAMMER_1 )
		AddBuyItem( 43587, __OBJ_FINE_STEEL_WARHAMMER_1 )
		AddBuyItem( 87, __OBJ_WOODEN_STAFF_1 )
		AddBuyItem( 1176, __OBJ_IRON_STAFF_1 )
		AddBuyItem( 3507, __OBJ_QUARTERSTAFF_1 )
		AddBuyItem( 7083, __OBJ_STAFF_OF_THORNS_1 )
		AddBuyItem( 87, __OBJ_ASHWOOD_FLATBOW_1 )
		AddBuyItem( 1815, __OBJ_ASHWOOD_LONGBOW_1 )
		AddBuyItem( 7083, __OBJ_ASHWOOD_REFLEX_BOW_1 )
		AddBuyItem( 15798, __OBJ_ELM_FLATBOW_1 )
		AddBuyItem( 27969, __OBJ_ELM_LONGBOW_1 )
		AddBuyItem( 43587, __OBJ_ELM_REFLEX_BOW_1 )
		AddBuyItem( 62661, __OBJ_ELM_RECURVE_BOW_1 )
	SendBuyItemList
NO(BROWSE)
	Conversation
	INTL( 7097, "I see, well you can always come back if you change your mind.")
YesNoELSE(BROWSE)
	Conversation
	INTL( 7098, "Would you like to take a look at my wares?")
	SetYesNo(BROWSE)
	
Command(INTL( 914, "WEAPON"))
INTL( 7099, "I have some of the best weapons you can find on this island. There's only one other "
"who can boast that he has better wares, and that's \"Seban\" \"Forgelot\".")

Command(INTL( 7100, "SEBAN FORGELOT"))
INTL( 7101, "As much as it pains me to say, he probably has the best weapons you'll find anywhere "
"on this island. Mind you, I'm not saying they are going to be cheap!")
	
Command(INTL( 1306, "SELL"))
INTL( 7102, "Hmm, I suppose I could take a peek to see if there's something I want.")
CreateItemList
	AddSellItem( WEAPON, 0, 100000 )
	AddSellItem( JEWEL | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | JEWEL | WEAPON, 0, 100000 )
SendSellItemList( INTL( 5370, "I'm sorry, but I don't see anything interesting in your inventory.") )

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 7103, "Come back if you need anything else.") BREAK

Default
INTL( 7104, "If you're not buying anything more, I'll be on my way then.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Karahn::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA
		NPC_SELL( 87, __OBJ_RUSTED_SHORT_SWORD_1 )
		NPC_SELL( 1815, __OBJ_RUSTED_LONG_SWORD_1 )
		NPC_SELL( 15798, __OBJ_POLISHED_SHORT_SWORD_1 )
		NPC_SELL( 27969, __OBJ_POLISHED_LONG_SWORD_1 )
		NPC_SELL( 43587, __OBJ_POLISHED_BROADSWORD_1 )
		NPC_SELL( 7083, __OBJ_RUSTED_HAND_AXE_1 )
		NPC_SELL( 62661, __OBJ_POLISHED_HAND_AXE_1 )
		NPC_SELL( 87, __OBJ_RUSTED_DIRK_1 )
		NPC_SELL( 1815, __OBJ_RUSTED_DAGGER_1 )
		NPC_SELL( 15798, __OBJ_POLISHED_DIRK_1 )
		NPC_SELL( 27969, __OBJ_POLISHED_DAGGER_1 )
		NPC_SELL( 87, __OBJ_WOODEN_CLUB_1 )
		NPC_SELL( 7083, __OBJ_STEEL_REINFORCED_CLUB_1 )
		NPC_SELL( 15798, __OBJ_STEEL_REINFORCED_WARHAMMER_1 )
		NPC_SELL( 43587, __OBJ_FINE_STEEL_WARHAMMER_1 )
		NPC_SELL( 87, __OBJ_WOODEN_STAFF_1 )
		NPC_SELL( 1176, __OBJ_IRON_STAFF_1 )
		NPC_SELL( 3507, __OBJ_QUARTERSTAFF_1 )
		NPC_SELL( 7083, __OBJ_STAFF_OF_THORNS_1 )
		NPC_SELL( 87, __OBJ_ASHWOOD_FLATBOW_1 )
		NPC_SELL( 1815, __OBJ_ASHWOOD_LONGBOW_1 )
		NPC_SELL( 7083, __OBJ_ASHWOOD_REFLEX_BOW_1 )
		NPC_SELL( 15798, __OBJ_ELM_FLATBOW_1 )
		NPC_SELL( 27969, __OBJ_ELM_LONGBOW_1 )
		NPC_SELL( 43587, __OBJ_ELM_REFLEX_BOW_1 )
		NPC_SELL( 62661, __OBJ_ELM_RECURVE_BOW_1 )

		NPC_BUY( WEAPON, 0, 100000 )
		NPC_BUY( JEWEL | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | JEWEL | WEAPON, 0, 100000 )

		NPC_SOLD_ITEM( INTL( 5774, "There you go.") )
		NPC_FAILED_SELL( INTL( 5398, "Come back when you have enough money.") )
		NPC_BOUGHT_ITEM( INTL( 7105, "There's your money.") )
	
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
