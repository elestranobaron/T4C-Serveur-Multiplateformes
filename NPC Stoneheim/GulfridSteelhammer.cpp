#pragma hdrstop
#include "GulfridSteelhammer.h"

GulfridSteelhammer::GulfridSteelhammer()
{}

GulfridSteelhammer::~GulfridSteelhammer()
{}

extern NPCstructure::NPC GulfridSteelhammerNPC;

void GulfridSteelhammer::Create( ){
	npc = GulfridSteelhammerNPC;
	SET_NPC_NAME( "[10857]Gulfrid Steelhammer" );
	npc.InitialPos.X = 220; 
	npc.InitialPos.Y = 760; 
	npc.InitialPos.world = 0; 
	npc.boPrivateTalk = TRUE;
}			  

void GulfridSteelhammer::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT BROWSE = 1;

InitTalk					 

Begin
INTL( 2221, "What can I do for you?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8134, "I am called Gulfrid Steelhammer.")

Command(INTL( 8135, "GULFRID"))
INTL( 8136, "That's me alright.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 8137, "I am the town weaponsmith. I sell my \"wares\" to whoever is in need of a \"weapon\". "
"Luckily for me, there is no shortage of need here, what with the feud between the "
"races.")

Command2(INTL( 1959, "WARES"),INTL( 914, "WEAPON"))
INTL( 8138, "I see I've caught your attention, eh? Well, perhaps you would like to take a closer look "
"at just what I have to sell?")
SetYesNo(BROWSE)

Command(INTL( 5628, "ORACLE"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) >= 1)
	Conversation
	INTL( 8139, "Only those with godly keys, such as the Key of Artherk, can ever hope to "
	"find him.")
ELSE
	Conversation
	INTL( 8140, "I don't think this is something we should be talking about. If people saw me "
	"talking with someone like you, it might tarnish my good name.")
ENDIF

Command(INTL( 1304, "BUY"))
INTL( 7113, "Of course you want to buy, who wouldn't? Will you take a look at my selection?")
SetYesNo(BROWSE)

YES(BROWSE)
CreateItemList
	CreateItemList
		AddBuyItem( 97601, __OBJ_HIGH_METAL_LONG_SWORD )
		AddBuyItem( 113163, __OBJ_HIGH_METAL_BROADSWORD )
		AddBuyItem( 129874, __OBJ_HIGH_METAL_SCIMITAR )
		AddBuyItem( 147737, __OBJ_HIGH_METAL_BASTARD_SWORD )
      AddBuyItem( 147737, __OBJ_HIGH_METAL_BASTARD_SWORD_DUAL )
		AddBuyItem( 147737, __OBJ_HIGH_METAL_HAND_AXE )
		AddBuyItem( 186913, __OBJ_HIGH_METAL_BATTLE_AXE )
		AddBuyItem( 57821, __OBJ_MITHRIL_DAGGER )
		AddBuyItem( 83191, __OBJ_MITHRIL_BLADE )
      AddBuyItem( 83191, __OBJ_MITHRIL_BLADE_DUAL )
		AddBuyItem( 147737, __OBJ_MITHRIL_FLAIL )
		AddBuyItem( 113163, __OBJ_OAK_FLATBOW )
		AddBuyItem( 129874, __OBJ_OAK_LONGBOW )
		AddBuyItem( 147737, __OBJ_OAK_REFLEX_BOW )
		AddBuyItem( 166749, __OBJ_OAK_RECURVE_BOW )
		AddBuyItem( 186913, __OBJ_OAK_COMPOUND_BOW )
		AddBuyItem( 208226, __OBJ_OAK_COMPOSITE_BOW )
		AddBuyItem( 75000, __OBJ_FLIGHT_ARROW )
	SendBuyItemList

SendBuyItemList

NO(BROWSE)
Conversation
INTL( 8141, "No? No?!? If you're not going to buy anything, then I suggest you leave immediately.")

YesNoELSE(BROWSE)
Conversation
INTL( 7115, "Will you look at the wonderful selection of weapons I have for sale?")
SetYesNo(BROWSE)
	
Command(INTL( 914, "WEAPON"))
INTL( 8142, "Truly, I have the very best weapons you'll find anywhere on this island. Feel free to "
"look around and \"buy\" what you like!")

Command(INTL( 1306, "SELL"))
INTL( 8143, "I don't see what you could possibly have to offer me, but I'll oblige you "
"anyway.")
CreateItemList
	AddSellItem( WEAPON, 0, 100000 )
	AddSellItem( JEWEL | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | JEWEL | WEAPON, 0, 100000 )
SendSellItemList( INTL( 8144, "You have nothing I want.") )

Command2(INTL( 554, "HELP"),INTL( 4275, "HINT"))
INTL( 8145, "If it's advice you seek, go see Yolangda the gypsy. You might find her advice "
"expensive, but if you're desperate, I'm sure she's the one to talk to.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 698, " ASS "),INTL( 697, "ASSHOLE"))
INTL( 8146, "Leave my shop at once, you're wasting my time.")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8148, "Thanks for the business, until we meet again.")
BREAK

Default
INTL( 8151, "If it has nothing to do with weapons, then I probably know nothing about it.")

EndTalk

}

void GulfridSteelhammer::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )

NPC_DATA_EXCHANGE

	NPC_SHOP_DATA
     	NPC_SELL( 97601, __OBJ_HIGH_METAL_LONG_SWORD )
		NPC_SELL( 113163, __OBJ_HIGH_METAL_BROADSWORD )
		NPC_SELL( 129874, __OBJ_HIGH_METAL_SCIMITAR )
		NPC_SELL( 147737, __OBJ_HIGH_METAL_BASTARD_SWORD )
      NPC_SELL( 147737, __OBJ_HIGH_METAL_BASTARD_SWORD_DUAL )
		NPC_SELL( 147737, __OBJ_HIGH_METAL_HAND_AXE )
		NPC_SELL( 186913, __OBJ_HIGH_METAL_BATTLE_AXE )
		NPC_SELL( 57821, __OBJ_MITHRIL_DAGGER )
		NPC_SELL( 83191, __OBJ_MITHRIL_BLADE )
      NPC_SELL( 83191, __OBJ_MITHRIL_BLADE_DUAL )
		NPC_SELL( 147737, __OBJ_MITHRIL_FLAIL )
		NPC_SELL( 113163, __OBJ_OAK_FLATBOW )
		NPC_SELL( 129874, __OBJ_OAK_LONGBOW )
		NPC_SELL( 147737, __OBJ_OAK_REFLEX_BOW )
		NPC_SELL( 166749, __OBJ_OAK_RECURVE_BOW )
		NPC_SELL( 186913, __OBJ_OAK_COMPOUND_BOW )
		NPC_SELL( 208226, __OBJ_OAK_COMPOSITE_BOW )
		NPC_SELL( 75000, __OBJ_FLIGHT_ARROW )

      NPC_BUY( WEAPON, 0, 100000 )
      NPC_BUY( JEWEL | WEAPON, 0, 100000 )
      NPC_BUY( MAGIC | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | JEWEL | WEAPON, 0, 100000 )

		NPC_SOLD_ITEM( INTL( 8152, "Here you are, enjoy!") )
		NPC_FAILED_SELL( INTL( 5398, "Come back when you have enough money.") )
		NPC_BOUGHT_ITEM( INTL( 1313, "Here is your money.") )
	
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE

