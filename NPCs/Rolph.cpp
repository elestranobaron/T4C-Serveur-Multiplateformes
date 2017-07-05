// Rolph.cpp: implementation of the Rolph class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Rolph.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Rolph::Rolph()
{}

Rolph::~Rolph()
{}

extern NPCstructure::NPC ShopKeeper;

void Rolph::Create(){
	npc = ShopKeeper;
	SET_NPC_NAME( "[3055]Rolph" );
	npc.InitialPos.X = 2901;
	npc.InitialPos.Y = 1069;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

void Rolph::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	switch(rnd(0, 1)){
	case 0: SHOUT(INTL( 1378, "AHHHHHHHHHHHHHH!")); break;
	case 1: SHOUT(INTL( 1379, "HELP!")); break;
	}

	self->Do(flee);
	self->SetTarget(target);
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Rolph::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
INTL( 11778, "Welcome, welcome! Business has been booming since these guards came to town. Everyone is buying \"armor\" "
"these days it seems!")
IF (CheckItem(__OBJ_MERCHANT_LETTER) == 0)
  RemFlag(__QUEST_ROLPH_REPORT)
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1946, "My name is Rolph, I am the greatest armorer around!")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1947, "I own the best armor shop in all of \"Goldmoon\"! Although nowadays, "
"with those damned \"goblins\", I'm not selling much.")

Command(INTL( 523, "ANNABELLE"))
INTL( 1948, "I heard that she has Elven blood running in her veins. Methinks it is untrue "
"because we all know that Elves have been wiped out a long time ago. Or "
"were they?") 

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 1949, "Balork's curse? That's horrible! Hmmm... Are sure you don't want "
"to \"buy\" something?")

Command(INTL( 753, "GOLDMOON"))
INTL( 1950, "Goldmoon is the kingdom regrouping all the villages on the islands "
"of \"Arakas\" and \"Raven's\" \"Dust\", and I can tell you, you won't find a "
"better armorer than me on any of these islands! Well, actually, maybe on "
"Raven's Dust and the town of Windhowl too... Oh well.")
 
Command(INTL( 793, "RAVEN'S DUST"))
INTL( 1951, "It's the island where the castle of Theodore XIII is located.")

Command(INTL( 515, "ARAKAS"))
INTL( 1952, "Aye, that's the name of this island. It is home to the towns of Lighthaven "
"and Windhowl.")

Command(INTL( 539, "GOBLIN"))
INTL( 1953, "Goblins... They are everywhere now! Some small groups sometimes succeed "
"in passing Windhowl's defenses and terrorize the citizens. Usually, they get "
"killed by brigands, or by our great guards, whom, I might add, are all "
"equipped with gear from my fabulous shop.")

Command2(INTL( 1300, "REGISTRATION"),INTL( 1301, "LETTER"))
""
;int nMyVar = CheckGlobalFlag( __GLOBAL_QUEST_ROLPH_REPORT );
IF ( CheckFlag( __QUEST_ROLPH_REPORT ) == nMyVar && nMyVar != 0)
  Conversation
  INTL( 1954, "You're still in Lighthaven? It is imperative that you deliver the report I gave you "
  "to Lord Sunrock's as soon as possible.")
ELSE
  IF (CheckGlobalFlag (__GLOBAL_QUEST_ROLPH_REPORT) > CurrentRound)
    ;int nTimeLeft = ((CheckGlobalFlag(__GLOBAL_QUEST_ROLPH_REPORT) - CurrentRound) / 1200);
    Conversation
    FORMAT(INTL( 2804, "You have registered yourself at the lord's office? I am truly sorry, but "
    "I have already sent someone to deliver a report to Windhowl. Perhaps I'll have "
    "an errand for you in %u minutes."), nTimeLeft)
  ELSE
    IF (CheckItem(__OBJ_MERCHANT_LETTER) >= 1 )
      TakeItem(__OBJ_MERCHANT_LETTER)
			 RemFlag(__QUEST_MERCHANT)
     IF (USER_LEVEL > 4)
      GiveGlobalFlag(__GLOBAL_QUEST_ROLPH_REPORT, 1 HOURS TDELAY )
      GiveItem(__OBJ_ROLPH_REPORT)  
      GetItemHandle(__OBJ_ROLPH_REPORT, RolphReport)
      GiveUnitFlag (RolphReport, __ITEM_QUEST_ROLPH_REPORT, CheckGlobalFlag( __GLOBAL_QUEST_ROLPH_REPORT ))
      GiveFlag(__QUEST_ROLPH_REPORT, CheckGlobalFlag( __GLOBAL_QUEST_ROLPH_REPORT ))
      Conversation
      INTL( 1956, "Great! Please deliver this precious document to Lord Sunrock as fast as "
      "you can without stopping in the woods. The brigands might attempt to "
      "hinder your errand, so be careful!")
     ELSE
      Conversation
      INTL( 7184, "I highly doubt you would be able to make it to Windhowl at your level.")
     ENDIF
    ELSE
      Conversation
      INTL( 1957, "You will have to register yourself with the Lord of Lighthaven, Kirlor Dhul, "
      "if you would like to work for the merchants. Bring me back the letter "
      "proving that you are properly registered.")
    ENDIF
  ENDIF
ENDIF


Command(INTL( 1435, "LORD"))
INTL( 1958, "The lord's office is at the east side of town.")

Command3(INTL( 1959, "WARES"),INTL( 1960, "SHOP"), INTL( 916, "ARMOR"))
INTL( 1961, "I buy and sell armor. Do you wish to \"buy\" or \"sell\" any?")

Command(INTL( 1304, "BUY"))
INTL( 1962, "I forge the toughest armors in all of \"Goldmoon\"! Which one do you want?")

CreateItemList
  AddBuyItem( 15, __OBJ_CLOTH_PANTS )
  AddBuyItem( 15, __OBJ_CLOTH_VEST )
  AddBuyItem( 212, __OBJ_LEATHER_BELT )
  AddBuyItem( 248, __OBJ_LEATHER_GLOVES )
  AddBuyItem( 261, __OBJ_LEATHER_HELMET )
  AddBuyItem( 269, __OBJ_LEATHER_PANTS )
  AddBuyItem( 245, __OBJ_LEATHER_BOOTS )
  AddBuyItem( 607, __OBJ_LEATHER_ARMOR )
  AddBuyItem( 700, __OBJ_RED_CAPE )
  AddBuyItem( 1086, __OBJ_STUDDED_LEATHER_BELT )
  AddBuyItem( 1402, __OBJ_STUDDED_LEATHER_GLOVES )
  AddBuyItem( 1510, __OBJ_STUDDED_LEATHER_HELMET )
  AddBuyItem( 1579, __OBJ_STUDDED_LEATHER_PANTS )
  AddBuyItem( 1372, __OBJ_STUDDED_LEATHER_BOOTS )
  AddBuyItem( 4538, __OBJ_STUDDED_LEATHER_ARMOR )
  AddBuyItem( 3355, __OBJ_WOODEN_SHIELD )
SendBuyItemList

Command(INTL( 1306, "SELL"))
INTL( 1307, "What is it that you wish to sell?")
CreateItemList
  AddSellItem( ARMOR, 0, 100000 )
  AddSellItem( MAGIC | ARMOR, 0, 100000 )
  AddSellItem( JEWEL | ARMOR, 0, 100000 )
  AddSellItem( JEWEL | MAGIC | ARMOR, 0, 100000 )

SendSellItemList(INTL( 1963, "I do not see anything interesting in your inventory."))

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 1964, "Feel free to visit my shop again!") BREAK

Default
INTL( 1965, "Err, I don't quite understand.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Rolph::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Rolph data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA

  NPC_SELL( 15, __OBJ_CLOTH_PANTS )
  NPC_SELL( 15, __OBJ_CLOTH_VEST )
	NPC_SELL( 212, __OBJ_LEATHER_BELT )
  NPC_SELL( 248, __OBJ_LEATHER_GLOVES )
  NPC_SELL( 261, __OBJ_LEATHER_HELMET )
  NPC_SELL( 269, __OBJ_LEATHER_PANTS )
  NPC_SELL( 245, __OBJ_LEATHER_BOOTS )
  NPC_SELL( 607, __OBJ_LEATHER_ARMOR )
  NPC_SELL( 700, __OBJ_RED_CAPE ) 
  NPC_SELL( 1086, __OBJ_STUDDED_LEATHER_BELT )
  NPC_SELL( 1402, __OBJ_STUDDED_LEATHER_GLOVES )
  NPC_SELL( 1510, __OBJ_STUDDED_LEATHER_HELMET )
  NPC_SELL( 1579, __OBJ_STUDDED_LEATHER_PANTS )
  NPC_SELL( 1372, __OBJ_STUDDED_LEATHER_BOOTS )
  NPC_SELL( 4538, __OBJ_STUDDED_LEATHER_ARMOR )
	NPC_SELL( 3355, __OBJ_WOODEN_SHIELD )

  NPC_BUY( ARMOR, 0, 100000 )
  NPC_BUY( MAGIC | ARMOR, 0, 100000 )
  NPC_BUY( JEWEL | ARMOR, 0, 100000 )
  NPC_BUY( JEWEL | MAGIC | ARMOR, 0, 100000 )

  NPC_SOLD_ITEM( INTL( 1966, "A fine choice it is!") )
  NPC_FAILED_SELL( INTL( 1967, "You don't have enough money!") )
  NPC_BOUGHT_ITEM( INTL( 1968, "Here's your money, friend.") )
	
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
