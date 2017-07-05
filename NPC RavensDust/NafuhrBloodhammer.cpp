#pragma hdrstop
#include "NafuhrBloodhammer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NafuhrBloodhammer::NafuhrBloodhammer()
{}

NafuhrBloodhammer::~NafuhrBloodhammer()
{}

extern NPCstructure::NPC ShopKeeper_set_two;

void NafuhrBloodhammer::Create(){
        npc = ShopKeeper_set_two;
        SET_NPC_NAME( "[2973]Nafuhr Bloodhammer" );
        npc.InitialPos.X = 1446;
        npc.InitialPos.Y = 2454;
        npc.InitialPos.world = 0;
}

void NafuhrBloodhammer::OnTalk( UNIT_FUNC_PROTOTYPE )
{								   
InitTalk

Begin
""
IF (Gold < 2000 )
	Conversation
	INTL( 5570, "Sorry, beggars are not allowed in my shop. And stop wandering around! You're annoying my customers.")
	BREAK
ELSE
	Conversation
	INTL( 5571, "Do not hesitate to tell me if I can be of assistance to you, my dearest customer.")
ENDIF	

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5572, "I am Nafuhr BloodHammer. Peculiar name isn't it? It comes from my dwarven \"heritage\".")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 5573, "I am the village's blacksmith. Although I know how to forge weapons, I leave this in the expert hands of "
"\"Rhodar\" \"Heatforge\". My speciality is crafting strong and durable armors.") 

Command(INTL( 5574, "HERITAGE"))
INTL( 5575, "You look somewhat surprised that dwarven blood runs freely through my veins. "
"I had a \"great\" \"grandfather\" who was a dwarf while his wife was human.")   	  

Command2(INTL( 5576, "RHODAR"),INTL( 5577, "HEATFORGE"))
INTL( 5578, "This is the smith you must seek if you are looking to buy a good weapon.")
	  	  	  
Command(INTL( 5579, "GREAT GRANDFATHER"))
INTL( 5580, "The name was Moridhar Rumblehill. He was an awesome warrior who could not "
"be bested in one-on-one combat. In fact, he even fought the powerful dragons of Firesky. Alas, "
"he never learn to retreat and eventually ended up crushed by a \"dragon\".")  

Command2(INTL( 5581, "DWARF"),INTL( 5582, "DWARV"))
INTL( 5583, "I wonder what happened exactly to that race.") 

Command2(INTL( 5584, "MORIDHAR"),INTL( 5585, "RUMBLEHILL"))
INTL( 5586, "Yes, that's the name of my \"great\" \"grandfather\".")

CmdAND(INTL( 1367, "DRAGON"),INTL( 2005, "TOOTH"))
""
IF ((CheckItem(__OBJ_TIGER_TOOTH) >= 1) && (CheckFlag(__FLAG_SIGFRIED_SCAM) == 2))
	Conversation
	INTL( 5587, "The dragon tooth was a tiger's tooth in reality? I knew it. It's so small, even a "
	"baby wyrm has bigger teeth!")
ELSEIF ((CheckItem(__OBJ_DRAGON_TOOTH) >= 1) && (CheckFlag(__FLAG_SIGFRIED_SCAM) >= 1))
	Conversation
	INTL( 5588, "The dragon's tooth you have is a fake one.")  
ELSEIF (CheckItem(__OBJ_DRAGON_TOOTH) >= 1)
	Conversation
	INTL( 5589, "This is no true dragon tooth! Have you looked at it? It's so damn small. I think you've got ripped off.")
	GiveFlag(__FLAG_SIGFRIED_SCAM,1)
ELSE
	Conversation
	INTL( 5590, "A dragon tooth? I don't have any but I know when I see one. \"Moridhar\" \"Rumblehill\", "
	"my great grandfather was a dragon slayer.") 
ENDIF

Command(INTL( 10429, "TEETH")) 
""
IF ((CheckItem(__OBJ_TIGER_TOOTH) >= 1) && (CheckFlag(__FLAG_SIGFRIED_SCAM) == 2))
	Conversation
	INTL( 5587, "The dragon tooth was a tiger's tooth in reality? I knew it. It's so small, even a "
	"baby wyrm has bigger teeth!")
ELSEIF ((CheckItem(__OBJ_DRAGON_TOOTH) >= 1) && (CheckFlag(__FLAG_SIGFRIED_SCAM) >= 1))
	Conversation
	INTL( 5588, "The dragon's tooth you have is a fake one.")  
ELSEIF (CheckItem(__OBJ_DRAGON_TOOTH) >= 1)
	Conversation
	INTL( 5589, "This is no true dragon tooth! Have you looked at it? It's so damn small. I think you've got ripped off.")
	GiveFlag(__FLAG_SIGFRIED_SCAM,1)
ELSE
	Conversation
	INTL( 5590, "A dragon tooth? I don't have any but I know when I see one. \"Moridhar\" \"Rumblehill\", "
	"my great grandfather was a dragon slayer.") 
ENDIF


Command(INTL( 1367, "DRAGON"))
INTL( 7923, "The dragons are fearsome creatures. They have razon-sharp talons, \"teeth\" that can bite "
"through the strongest armors and some are even rumored to breathe fire! Fortunately, most of the " 
"evil dragons have mysteriously disappeared from Althea.")

Command3(INTL( 1037, "MURMUNTAG"),INTL( 5110, "VUNTERTAG"),INTL( 2183, "GUNTERTAG"))
INTL( 5591, "Even though Murmuntag, Vuntertag and Guntertag are on the right side, they are still orcs "
"and cannot be trusted. They will fight on your side (or against you) for a pouch of coins "
"and a bread crust.")

Command(INTL( 5592, "MOTHER"))
INTL( 5593, "She was a brave woman. I wish I'd known her better.") 

Command(INTL( 744, "ORC"))
INTL( 5594, "Orcs *cannot* be trusted. Incidentally, Raven's Dust is plagued by an orc campment located "
"somewhere in the north. They have battle siege weapons that could do severe damages to our "
"castle but fortunately for us, they are so heavy that even the orcish brutes cannot bring them "
"within range.") 

Command2(INTL( 1304, "BUY"),INTL( 916, "ARMOR"))
INTL( 5595, "You will not be disappointed with my very durable pieces of armor.")
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
   AddBuyItem( 20777,  __OBJ_CHAINMAIL )
   AddBuyItem( 6165,  __OBJ_CHAINMAIL_GLOVES )
   AddBuyItem( 6670,  __OBJ_CHAINMAIL_COIF )
   AddBuyItem( 6992,  __OBJ_CHAINMAIL_LEGGINGS )
   AddBuyItem( 6072, __OBJ_CHAINMAIL_BOOTS) 
  
	AddBuyItem( 7389,  __OBJ_ROUND_SHIELD )
	AddBuyItem( 25990, __OBJ_LARGE_SHIELD )

SendBuyItemList

Command(INTL( 1306, "SELL"))
INTL( 1307, "What is it that you wish to sell?")
CreateItemList
    AddSellItem( ARMOR, 0, 100000 )
    AddSellItem( MAGIC | ARMOR, 0, 100000 )
    AddSellItem( JEWEL | ARMOR, 0, 100000 )
    AddSellItem( MAGIC | JEWEL | ARMOR, 0, 100000 )

SendSellItemList(INTL( 5596, "Sorry but I don't see anything in your inventory that I would need right now.")) 

Command(INTL( 3918, "VISITOR"))
""
IF (CheckFlag(__QUEST_VISITOR_SPOTTED) < 2)
	Conversation
	INTL( 5597, "I have customers to tend to so if anyone strange walked in front of my store, I probably missed it.")
ELSEIF (CheckFlag(__QUEST_VISITOR_SPOTTED) == 2)
	Conversation
	INTL( 5598, "Ahh yes, it would seem you just missed him. Quite a strange man that was, I can tell you. He seemed "
	"rather in a hurry to leave town. I would assume that he was heading to Boreas' shop, so if you hurry, "
	"you might still catch up with him.")
	GiveFlag(__QUEST_VISITOR_SPOTTED, 3)
ELSEIF (CheckFlag(__QUEST_VISITOR_SPOTTED) >= 3)
	Conversation
	INTL( 5599, "Like I said, I don't know for sure, but I think he might have been heading for Boreas' shop.")
ENDIF	

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 5600, "Farewell dearest customer.") BREAK

Default
INTL( 4012, "Perhaps others would like to know about that.")

EndTalk
}
//////////////////////////////////////////////////////////////////////////////////////////
void NafuhrBloodhammer::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// NafuhrBloodhammer data function, handles his shop
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

   NPC_SELL( 2308, __OBJ_RINGMAIL_GIRDLE )
   NPC_SELL( 10039, __OBJ_RINGMAIL_ARMOR )
   NPC_SELL( 3015, __OBJ_RINGMAIL_GAUNTLETS ) 
   NPC_SELL( 3258, __OBJ_RINGMAIL_HELMET )
   NPC_SELL( 3413, __OBJ_RINGMAIL_LEGGINGS )
   NPC_SELL( 2949, __OBJ_RINGMAIL_BOOTS ) 

	NPC_SELL( 4694,  __OBJ_CHAINMAIL_GIRDLE )
   NPC_SELL( 20777,  __OBJ_CHAINMAIL )
   NPC_SELL( 6165,  __OBJ_CHAINMAIL_GLOVES )
   NPC_SELL( 6670,  __OBJ_CHAINMAIL_COIF )
   NPC_SELL( 6992,  __OBJ_CHAINMAIL_LEGGINGS )
   NPC_SELL( 6072, __OBJ_CHAINMAIL_BOOTS) 

   NPC_SELL( 7389,  __OBJ_ROUND_SHIELD )
   NPC_SELL( 25990, __OBJ_LARGE_SHIELD )
 
   NPC_BUY( ARMOR, 0, 100000 )
   NPC_BUY( MAGIC | ARMOR, 0, 100000 )
   NPC_BUY( JEWEL | ARMOR, 0, 100000 )
  NPC_BUY( MAGIC | JEWEL | ARMOR, 0, 100000 )

   NPC_SOLD_ITEM( INTL( 1966, "A fine choice it is!") )
   NPC_FAILED_SELL( INTL( 1967, "You do not have enough money!") )
   NPC_BOUGHT_ITEM( INTL( 1968, "Here's your money, friend.") )
	
   CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
