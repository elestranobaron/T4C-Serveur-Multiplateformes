#pragma hdrstop
#include "HerewaldIronbender.h"

HerewaldIronbender::HerewaldIronbender()
{}

HerewaldIronbender::~HerewaldIronbender()
{}

extern NPCstructure::NPC HerewaldIronbenderNPC;

void HerewaldIronbender::Create( void )
{
   npc = HerewaldIronbenderNPC;
   SET_NPC_NAME( "[10859]Herewald Ironbender" );
   npc.InitialPos.X = 285;
   npc.InitialPos.Y = 765;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

void HerewaldIronbender::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT BROWSE = 1; 
CONSTANT LOOKINGTOSHOP = 2; 

InitTalk
				 
Begin
INTL( 5409, "Greetings, have you come here to \"shop\"?") 
SetYesNo(LOOKINGTOSHOP) 

YES(LOOKINGTOSHOP) 
Conversation
INTL( 8465, "Heh, then I can assure you that you've come to the right place. I'm sure "
"that you'll find what you need in my shop.")

NO(LOOKINGTOSHOP) 
Conversation
INTL( 8466, "Then you've got no business here!")
BREAK

YesNoELSE(LOOKINGTOSHOP)
Conversation
INTL( 8467, "Well, are you here to shop or not?")
SetYesNo(LOOKINGTOSHOP) 

Command2(INTL( 8468, "HEREWALD"),INTL( 8469, "IRONBENDER"))
INTL( 2535, "Yes?")

Command2(INTL( 4275, "HINT"),INTL( 554, "HELP"))
INTL( 8470, "Don't ask me, ask someone who knows. Hey, why don't you ask that old dame, "
"Chryseida? She's a fortune-teller, I'm sure she'll help... for a price.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8471, "The name is Herewald Ironbender.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 8472, "I am the town's armorsmith. If you want to \"buy\" an armor, come to me "
"first and I will make you a deal you cannot refuse.")

Command3(INTL( 1304, "BUY"),INTL( 1960, "SHOP"),INTL( 916, "ARMOR"))
INTL( 8473, "I have some the strongest armors you can find around. They'll never let you "
"down in the middle of a fight. Do you want to have a look at my selection?")
SetYesNo(BROWSE)

YES(BROWSE)
	CreateItemList	
		AddBuyItem( 20777, __OBJ_CHAINMAIL )
		AddBuyItem( 6165,  __OBJ_CHAINMAIL_GLOVES )
		AddBuyItem( 6670,  __OBJ_CHAINMAIL_COIF )
		AddBuyItem( 4694,  __OBJ_CHAINMAIL_GIRDLE )		
		AddBuyItem( 6992,  __OBJ_CHAINMAIL_LEGGINGS )
		AddBuyItem( 6072,  __OBJ_CHAINMAIL_BOOTS) 
		AddBuyItem( 35404, __OBJ_SCALE_MAIL )
		AddBuyItem( 10456, __OBJ_SCALEMAIL_GAUNTLETS )
		AddBuyItem( 11319, __OBJ_SCALEMAIL_HELMET )
		AddBuyItem( 7945,  __OBJ_SCALEMAIL_PROTECTOR )
		AddBuyItem( 11868, __OBJ_SCALEMAIL_LEGGINGS ) 		
		AddBuyItem( 10220, __OBJ_SCALEMAIL_BOOTS )		
		AddBuyItem( 25990, __OBJ_LARGE_SHIELD )
		AddBuyItem( 43408, __OBJ_TOWER_SHIELD ) 
	SendBuyItemList

NO(BROWSE)
Conversation
INTL( 8474, "That's it! I've lost enough time with you.")
BREAK

YesNoELSE(BROWSE)
Conversation
INTL( 8475, "Will you take a look at what I have for sale?")
SetYesNo(BROWSE)

Command(INTL( 5628, "ORACLE"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) >= 1)
	Conversation
	INTL( 8476, "Whatever it is, I'm sure it's very powerful. Make sure you don't go there "
	"unprepared, and that means you should be wearing good \"armor\".")
ELSE
	Conversation
	INTL( 8477, "It's none of my business, and it certainly ain't none of yours.")
ENDIF

Command(INTL( 1306, "SELL"))
INTL( 8478, "So, it is your turn to sell some wares, eh?")
CreateItemList
	AddSellItem( ARMOR, 0, 100000 )
	AddSellItem( MAGIC | ARMOR, 0, 100000 )
	AddSellItem( JEWEL | ARMOR, 0, 100000 )
	AddSellItem( JEWEL | MAGIC | ARMOR, 0, 100000 )
SendSellItemList( INTL( 8144, "You have nothing I want.") )

Command4(INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"))
INTL( 8479, "Feel free to come back if you need something else.")	
BREAK

Default
INTL( 8482, "I don't know anything about that.")
EndTalk
}

void HerewaldIronbender::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
{
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA
		NPC_SELL( 20777, __OBJ_CHAINMAIL )
		NPC_SELL( 6165,  __OBJ_CHAINMAIL_GLOVES )
		NPC_SELL( 6670,  __OBJ_CHAINMAIL_COIF )
		NPC_SELL( 4694,  __OBJ_CHAINMAIL_GIRDLE )		
		NPC_SELL( 6992,  __OBJ_CHAINMAIL_LEGGINGS )
		NPC_SELL( 6072,  __OBJ_CHAINMAIL_BOOTS) 
		NPC_SELL( 35404, __OBJ_SCALE_MAIL )
		NPC_SELL( 10456, __OBJ_SCALEMAIL_GAUNTLETS )
		NPC_SELL( 11319, __OBJ_SCALEMAIL_HELMET )
		NPC_SELL( 7945,  __OBJ_SCALEMAIL_PROTECTOR )
		NPC_SELL( 11868, __OBJ_SCALEMAIL_LEGGINGS ) 		
		NPC_SELL( 10220, __OBJ_SCALEMAIL_BOOTS )		
		NPC_SELL( 25990, __OBJ_LARGE_SHIELD )
		NPC_SELL( 43408,	__OBJ_TOWER_SHIELD ) 

		NPC_BUY( ARMOR, 0, 100000 )
		NPC_BUY( MAGIC | ARMOR, 0, 100000 )
		NPC_BUY( JEWEL | ARMOR, 0, 100000 )
		NPC_BUY( JEWEL | MAGIC | ARMOR, 0, 100000 )

		NPC_SOLD_ITEM( INTL( 8483, "Here you are, now is there anything else?") )
		NPC_FAILED_SELL( INTL( 8484, "Come back when you have enough gold, I'll be waiting.") )
		NPC_BOUGHT_ITEM( INTL( 8485, "Hmm, I don't know what I will do with this, but perhaps I can sell it for a profit.") )

	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE

}
