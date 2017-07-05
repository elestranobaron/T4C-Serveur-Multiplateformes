//////////////////////////////////////////////////////////////////////
// SebanForgelot.cpp: implementation of the SebanForgelot class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "SebanForgelot.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SebanForgelot::SebanForgelot()
{}

SebanForgelot::~SebanForgelot()
{}

extern NPCstructure::NPC ShopKeeper;

void SebanForgelot::Create( ){
	npc = ShopKeeper;
	SET_NPC_NAME( "[2907]A wandering merchant" );
	npc.InitialPos.X = 2172; 
	npc.InitialPos.Y = 500; 
	npc.InitialPos.world = 0;
}

void SebanForgelot::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT BROWSE = 1;

InitTalk					 

Begin
INTL( 7106, "Yes, what do you want?")

Command(INTL( 483, "NAME"))
INTL( 7107, "I go by the name of Seban Forgelot.")

Command(INTL( 7108, "SEBAN"))
INTL( 7109, "Yes, that's me.")

Command(INTL( 489, "WORK"))
INTL( 7110, "You haven't heard of the great Seban? Fine, I will tell you then. I make the very best "
"\"weapons\" you'll find anywhere on this island. I forge them in my \"workshop\" and "
"then sell them to whoever I meet in my travels. I'm sure you will want to \"buy\" some of "
"them.")

Command(INTL( 7111, "WORKSHOP"))
INTL( 7112, "I will never reveal the location of my secret workshop to a simpleton like you!")

Command(INTL( 1304, "BUY"))
INTL( 7113, "Of course you want to buy, who wouldn't? Will you take a look at my selection?")
SetYesNo(BROWSE)

YES(BROWSE)
	CreateItemList
		AddBuyItem( 290, __OBJ_RUSTED_SHORT_SWORD_2 )
		AddBuyItem( 6050, __OBJ_RUSTED_LONG_SWORD_2 )
		AddBuyItem( 52660, __OBJ_POLISHED_SHORT_SWORD_2 )
		AddBuyItem( 93230, __OBJ_POLISHED_LONG_SWORD_2 )
		AddBuyItem( 145290, __OBJ_POLISHED_BROADSWORD_2 )
		AddBuyItem( 23610, __OBJ_RUSTED_HAND_AXE_2 )
		AddBuyItem( 208870, __OBJ_POLISHED_HAND_AXE_2 )
		AddBuyItem( 290, __OBJ_RUSTED_DIRK_2 )
		AddBuyItem( 6050, __OBJ_RUSTED_DAGGER_2 )
		AddBuyItem( 52660, __OBJ_POLISHED_DIRK_2 )
		AddBuyItem( 93230, __OBJ_POLISHED_DAGGER_2 )
		AddBuyItem( 290, __OBJ_WOODEN_CLUB_2 )
		AddBuyItem( 23610, __OBJ_STEEL_REINFORCED_CLUB_2 )
		AddBuyItem( 52660, __OBJ_STEEL_REINFORCED_WARHAMMER_2 )
		AddBuyItem( 145290, __OBJ_FINE_STEEL_WARHAMMER_2 )
		AddBuyItem( 290, __OBJ_WOODEN_STAFF_2 )
		AddBuyItem( 3920, __OBJ_IRON_STAFF_2 )
		AddBuyItem( 11690, __OBJ_QUARTERSTAFF_2 )
		AddBuyItem( 23610, __OBJ_STAFF_OF_THORNS_2 )
		AddBuyItem( 290, __OBJ_ASHWOOD_FLATBOW_2 )
		AddBuyItem( 6050, __OBJ_ASHWOOD_LONGBOW_2 )
		AddBuyItem( 23610, __OBJ_ASHWOOD_REFLEX_BOW_2 )
		AddBuyItem( 52660, __OBJ_ELM_FLATBOW_2 )
		AddBuyItem( 93230, __OBJ_ELM_LONGBOW_2 )
		AddBuyItem( 145290, __OBJ_ELM_REFLEX_BOW_2 )
		AddBuyItem( 208870, __OBJ_ELM_RECURVE_BOW_2 )
	SendBuyItemList
NO(BROWSE)
	Conversation
	INTL( 7114, "No? NO?!? If you're not going to buy anything, then I suggest you leave immediately.")
YesNoELSE(BROWSE)
	Conversation
	INTL( 7115, "Will you look at the wonderful selection of weapons I have for sale?")
	SetYesNo(BROWSE)
	
Command(INTL( 914, "WEAPON"))
INTL( 7116, "Truly, I have the very best weapons you'll find anywhere on this island. Feel free to "
"look around and \"buy\" what you like!")

Command(INTL( 1306, "SELL"))
INTL( 7117, "I don't see what you could possibly have to offer me, but I'll oblige you anyway.")
CreateItemList
	AddSellItem( WEAPON, 0, 100000 )
	AddSellItem( JEWEL | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | JEWEL | WEAPON, 0, 100000 )
SendSellItemList( INTL( 7118, "It seems there is nothing you have that I want after all. Too bad.") )

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 7119, "Alright then, no need to stay around me any longer, off you go now!") BREAK

Default
INTL( 7120, "It's very simple actually, the only words I want to hear from you are \"buy\" "
"and \"bye\".")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void SebanForgelot::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA
		NPC_SELL( 290, __OBJ_RUSTED_SHORT_SWORD_2 )
		NPC_SELL( 6050, __OBJ_RUSTED_LONG_SWORD_2 )
		NPC_SELL( 52660, __OBJ_POLISHED_SHORT_SWORD_2 )
		NPC_SELL( 93230, __OBJ_POLISHED_LONG_SWORD_2 )
		NPC_SELL( 145290, __OBJ_POLISHED_BROADSWORD_2 )
		NPC_SELL( 23610, __OBJ_RUSTED_HAND_AXE_2 )
		NPC_SELL( 208870, __OBJ_POLISHED_HAND_AXE_2 )
		NPC_SELL( 290, __OBJ_RUSTED_DIRK_2 )
		NPC_SELL( 6050, __OBJ_RUSTED_DAGGER_2 )
		NPC_SELL( 52660, __OBJ_POLISHED_DIRK_2 )
		NPC_SELL( 93230, __OBJ_POLISHED_DAGGER_2 )
		NPC_SELL( 290, __OBJ_WOODEN_CLUB_2 )
		NPC_SELL( 23610, __OBJ_STEEL_REINFORCED_CLUB_2 )
		NPC_SELL( 52660, __OBJ_STEEL_REINFORCED_WARHAMMER_2 )
		NPC_SELL( 145290, __OBJ_FINE_STEEL_WARHAMMER_2 )
		NPC_SELL( 290, __OBJ_WOODEN_STAFF_2 )
		NPC_SELL( 3920, __OBJ_IRON_STAFF_2 )
		NPC_SELL( 11690, __OBJ_QUARTERSTAFF_2 )
		NPC_SELL( 23610, __OBJ_STAFF_OF_THORNS_2 )
		NPC_SELL( 290, __OBJ_ASHWOOD_FLATBOW_2 )
		NPC_SELL( 6050, __OBJ_ASHWOOD_LONGBOW_2 )
		NPC_SELL( 23610, __OBJ_ASHWOOD_REFLEX_BOW_2 )
		NPC_SELL( 52660, __OBJ_ELM_FLATBOW_2 )
		NPC_SELL( 93230, __OBJ_ELM_LONGBOW_2 )
		NPC_SELL( 145290, __OBJ_ELM_REFLEX_BOW_2 )
		NPC_SELL( 208870, __OBJ_ELM_RECURVE_BOW_2 )

		NPC_BUY( WEAPON, 0, 100000 )
		NPC_BUY( JEWEL | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | JEWEL | WEAPON, 0, 100000 )

		NPC_SOLD_ITEM( INTL( 7121, "Here you are. Enjoy!") )
		NPC_FAILED_SELL( INTL( 5398, "Come back when you have enough money.") )
		NPC_BOUGHT_ITEM( INTL( 1313, "Here is your money.") )
	
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
