// Fali.cpp: implementation of the Fali class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Fali.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Fali::Fali()
{}

Fali::~Fali()
{}

extern NPCstructure::NPC FaliNPC;

//////////////////////////////////////////////////////////////////////////////////////////
void Fali::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Fali
//
{
    npc = FaliNPC;
    SET_NPC_NAME( "[3036]Fali" );
    npc.InitialPos.X = 2900;
    npc.InitialPos.Y = 1068;
	npc.InitialPos.world = 0;
    npc.boPrivateTalk = TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Fali::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Fali
//
{
InitTalk

Begin
INTL( 11749, "If there's one thing that's good about having all these guards around, it's that no one has "
"tried to \"steal\" anything from me since they got here. Feel free to \"look\" but let's keep "
"it civilized.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1296, "My name is Fali.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 1297, "I sell all those items. Please, feel free to have a \"look\".")

Command(INTL( 523, "ANNABELLE"))
INTL( 665, "I heard a rumor that she is much older than what she appears to be.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 7174, "Devilish monster? Cursed from beyond? Marked from eternity? Yeah, right!")

Command(INTL( 1298, "STEAL"))
INTL( 1299, "If you steal something, I swear you will regret it.")

Command2(INTL( 1300, "REGISTRATION"),INTL( 1301, "LETTER"))
INTL( 1302, "Hmmm? Rolph or Sigfried might want to see the lord's registration letter.")

Command2(INTL( 1303, "LOOK"),INTL( 1304, "BUY"))
INTL( 1305, "Here's what I have.")

CreateItemList
    AddBuyItem( 5, __OBJ_APPLE )
	AddBuyItem( 12, __OBJ_TORCH )
    AddBuyItem( 50, __OBJ_LIGHT_HEALING_POTION )
    AddBuyItem( 50, __OBJ_POTION_OF_MANA )
    AddBuyItem( 125, __OBJ_HEALING_POTION ) 
    AddBuyItem( 200, __OBJ_IRON_RING )

SendBuyItemList

Command(INTL( 1306, "SELL"))
INTL( 1307, "What is it that you wish to sell?")

CreateItemList
        AddSellItem( PAWNSHOP, 0, 100000 )
        AddSellItem( MAGIC, 0, 100000 )
        AddSellItem( POTION, 0, 100000 )
        AddSellItem( JEWEL, 0, 100000 )
        AddSellItem( MAGIC | JEWEL, 0, 100000 )
        AddSellItem( MAGIC | JEWEL | ARMOR, 0, 100000 )
SendSellItemList( INTL( 1308, "I do not see anything interesting.") )

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 1309, "Same to you... idiot!") BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1310, "Come back if you ever need anything.") BREAK

Default
INTL( 1311, "I do not feel like talking about that.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Fali::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Fali data function, handles her shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA
	
        NPC_SELL( 5, __OBJ_APPLE )
        NPC_SELL( 50, __OBJ_LIGHT_HEALING_POTION )
        NPC_SELL( 50, __OBJ_POTION_OF_MANA )
        NPC_SELL( 125, __OBJ_HEALING_POTION ) 

		NPC_SELL( 12, __OBJ_TORCH )
        NPC_SELL( 200, __OBJ_IRON_RING )

        NPC_BUY( PAWNSHOP, 0, 100000 )
        NPC_BUY( MAGIC, 0, 100000 )
        NPC_BUY( POTION, 0, 100000 )
		NPC_BUY( JEWEL, 0, 100000 )
		NPC_BUY( MAGIC | JEWEL, 0, 100000 )
        NPC_BUY( MAGIC | JEWEL | ARMOR, 0, 100000 )


      NPC_SOLD_ITEM( INTL( 1312, "Indeed, that is a fine choice.") )
      NPC_FAILED_SELL( INTL( 20, "You do not have enough money.") )
      NPC_BOUGHT_ITEM( INTL( 1313, "Here is your money.") )
	
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
