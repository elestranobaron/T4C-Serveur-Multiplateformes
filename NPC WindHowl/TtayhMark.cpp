//////////////////////////////////////////////////////////////////////
// TtayhMark.cpp: implementation of the TtayhMark class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "TtayhMark.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TtayhMark::TtayhMark()
{}
																												 
TtayhMark::~TtayhMark()
{}

extern NPCstructure::NPC Shopkeeper;

//Nom: Ttayh Mark.
//Statistique: Windhowl Paysan.
//Position: (2257, 547)
//World: 0
//Description: Weapon Shopkeeper.
//Body: Shopkeeper.

//////////////////////////////////////////////////////////////////////////////////////////
void TtayhMark::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of TtayhMark
//
{
	npc = Shopkeeper;
	SET_NPC_NAME( "[3025]Ttayh Mark" );
	npc.InitialPos.X = 1734;
	npc.InitialPos.Y = 1194;
	npc.InitialPos.world = 0; 
	npc.boPrivateTalk = TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void TtayhMark::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of TtayhMark
//
{

CONSTANT BROWSE = 1;
CONSTANT BM = 2; 

InitTalk

Begin
INTL( 2733, "Step right in and look at the \"greatest\" weapons around.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2734, "I am Ttayh, the best weaponsmith around! Do you wish to \"buy\" or "
"\"sell\" anything?")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2735, "I sell weapons of any sort, and of the \"greatest\" quality too! They are "
"as sharp as a dragon's claw and can resist rust! You won't find anything "
"better. Do you wish to \"buy\" or \"sell\" anything?")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2670, "Balork's Brand? Huh?")

Command(INTL( 523, "ANNABELLE"))
INTL( 7207, "I heard she is much older than she appears to be.")

Command(INTL( 514, "WINDHOWL"))
INTL( 2736, "Windhowl is such a beautiful town to visit!")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 2737, "I heard that Lord Sunrock would like to receive reports from merchants "
"in Lighthaven.")

Command(INTL( 2730, "BLACK MARKET"))
""
IF (CheckFlag(__BLACK_MARKET) != 2)
	Conversation
	INTL( 2738, "I do not know about that. *cough*")
ELSE
	IF (TFCTime::IsDay())
		Conversation
		INTL( 2739, "I do not operate the black market during the day. It's too dangerous.") 
		GiveNPCFlag(__TTAYH_MARK_BLACK_MARKET, rnd.roll( dice( 1, 10 ) ))
	ELSE
		Conversation
		INTL( 2740, "Our business has to be dealt swiftly and in silence. Do you want "
		"to have a look at what I have today?")
		SetYesNo(BM)		
	ENDIF
ENDIF

YES(BM)
IF (USER_LEVEL <= 9)											
	IF (CheckNPCFlag (__TTAYH_MARK_BLACK_MARKET) <= 5 )	
		CreateItemList 
			AddBuyItem( 74,		__OBJ_LIGHT_HEALING_POTION)
			AddBuyItem( 1722,		__OBJ_RING_OF_LIGHT)
			AddBuyItem( 2319,		__OBJ_RING_OF_CONFIDENCE)
		SendBuyItemList
	ELSEIF (CheckNPCFlag (__TTAYH_MARK_BLACK_MARKET) <= 8 )	
		CreateItemList 
			AddBuyItem( 183,		__OBJ_MANA_ELIXIR)
			AddBuyItem( 609,		__OBJ_LEATHER_BELT_OF_SURVIVAL)		
			AddBuyItem( 1901,		__OBJ_RING_OF_THE_BEAR)
		SendBuyItemList
	ELSE
		CreateItemList 
			AddBuyItem( 183,		__OBJ_HEALING_POTION)
			AddBuyItem( 1722,		__OBJ_RING_OF_LIGHT)
			AddBuyItem( 6847,		__OBJ_STAFF_OF_THORNS_1)
		SendBuyItemList
	ENDIF
ELSEIF (USER_LEVEL <= 15) 
	IF (CheckNPCFlag (__TTAYH_MARK_BLACK_MARKET) <= 5 )	
		CreateItemList 
			AddBuyItem( 2319,		__OBJ_RING_OF_CONFIDENCE)
			AddBuyItem( 14894,	__OBJ_SILVER_AXE)		
		SendBuyItemList
	ELSEIF (CheckNPCFlag (__TTAYH_MARK_BLACK_MARKET) <= 8 )	
		CreateItemList 
			AddBuyItem( 74,		__OBJ_LIGHT_HEALING_POTION)
			AddBuyItem( 183,		__OBJ_HEALING_POTION)
			AddBuyItem( 3445,		__OBJ_RING_OF_ACCURACY)
			AddBuyItem( 6847,		__OBJ_STAFF_OF_THORNS_1)
		SendBuyItemList
	ELSE
		CreateItemList 
			AddBuyItem( 183,		__OBJ_MANA_ELIXIR)
			AddBuyItem( 609,		__OBJ_BUCKLE_OF_LOCKPICKS)
			AddBuyItem( 1901,		__OBJ_RING_OF_THE_BEAR)
			AddBuyItem( 1722,		__OBJ_RING_OF_LIGHT)
			AddBuyItem( 2319,		__OBJ_RING_OF_CONFIDENCE)
		SendBuyItemList
	ENDIF
ELSEIF (USER_LEVEL <= 19)
	IF (CheckNPCFlag (__TTAYH_MARK_BLACK_MARKET) <= 5 )	
		CreateItemList 
			AddBuyItem( 3445,		__OBJ_RING_OF_ACCURACY)
			AddBuyItem( 14894,	__OBJ_SILVER_AXE)		
		SendBuyItemList
	ELSEIF (CheckNPCFlag (__TTAYH_MARK_BLACK_MARKET) <= 8 )	
		CreateItemList 
			AddBuyItem( 74,		__OBJ_LIGHT_HEALING_POTION)
			AddBuyItem( 609,		__OBJ_LEATHER_BELT_OF_SURVIVAL)		
			AddBuyItem( 6847,		__OBJ_STAFF_OF_THORNS_1)
		SendBuyItemList
	ELSE
		CreateItemList 
			AddBuyItem( 1901,		__OBJ_RING_OF_THE_BEAR)
			AddBuyItem( 609,		__OBJ_BUCKLE_OF_LOCKPICKS)
			AddBuyItem( 14894,	__OBJ_SILVER_AXE)		
		SendBuyItemList
	ENDIF
ELSE // ELSEIF (USER_LEVEL <= 30)
	IF (CheckNPCFlag (__TTAYH_MARK_BLACK_MARKET) <= 5 )	
		CreateItemList 
			AddBuyItem( 183,		__OBJ_MANA_ELIXIR)
			AddBuyItem( 3445,		__OBJ_RING_OF_ACCURACY)
		SendBuyItemList
	ELSEIF (CheckNPCFlag (__TTAYH_MARK_BLACK_MARKET) <= 8 )	
		CreateItemList 
			AddBuyItem( 183,		__OBJ_HEALING_POTION)
			AddBuyItem( 1722,		__OBJ_RING_OF_LIGHT)
			AddBuyItem( 3445,		__OBJ_RING_OF_ACCURACY)
			AddBuyItem( 14894,	__OBJ_SILVER_AXE)		
		SendBuyItemList
	ELSE
		CreateItemList 
			AddBuyItem( 74,		__OBJ_LIGHT_HEALING_POTION)
			AddBuyItem( 1901,		__OBJ_RING_OF_THE_BEAR)
		SendBuyItemList
	ENDIF
ENDIF

NO(BM)
Conversation
INTL( 3635, "That's too bad really.")

YesNoELSE(BM)
Conversation
INTL( 3636, "Well, do you want to see my wares or not?")
SetYesNo(BM)	

Command(INTL( 1304, "BUY"))
INTL( 2741, "Ahh! Buying from me is usually a great investment! You want to see my wares?")
SetYesNo(BROWSE)

YES(BROWSE)
	CreateItemList
		AddBuyItem( 5266, __OBJ_POLISHED_SHORT_SWORD )
		AddBuyItem( 9323, __OBJ_POLISHED_LONG_SWORD )
		AddBuyItem( 14529, __OBJ_POLISHED_BROADSWORD )
		AddBuyItem( 20887, __OBJ_POLISHED_HAND_AXE )
		AddBuyItem( 5266, __OBJ_POLISHED_DIRK )
		AddBuyItem( 9323, __OBJ_POLISHED_DAGGER )
		AddBuyItem( 5266, __OBJ_STEEL_REINFORCED_WARHAMMER )
		AddBuyItem( 14529, __OBJ_FINE_STEEL_WARHAMMER )
		AddBuyItem( 1169, __OBJ_QUARTERSTAFF )
		AddBuyItem( 2361, __OBJ_STAFF_OF_THORNS )
		AddBuyItem( 5266, __OBJ_ELM_FLATBOW )
		AddBuyItem( 9323, __OBJ_ELM_LONGBOW )
		AddBuyItem( 14529, __OBJ_ELM_REFLEX_BOW )
		AddBuyItem( 20887, __OBJ_ELM_RECURVE_BOW )
		AddBuyItem( 1500, __OBJ_PINPOINT_ARROW )
	SendBuyItemList
NO(BROWSE)
	Conversation
	INTL( 7208, "That's too bad, really.")
YesNoELSE(BROWSE)
	Conversation
	INTL( 3636, "Well, do you want to see my wares or not?")
	SetYesNo(BROWSE)

Command(INTL( 1306, "SELL"))
INTL( 2742, "You want me to take some of the weapons off your hands? Let's have a look then...")
CreateItemList
	AddSellItem( WEAPON, 0, 100000 )
	AddSellItem( MAGIC | WEAPON, 0, 100000 )
	AddSellItem( JEWEL | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | JEWEL | WEAPON, 0, 100000 )
SendSellItemList( INTL( 3637, "I'm sorry but I do not see anything interesting in your inventory.") )

Command(INTL( 2744, "GREATEST"))
INTL( 2745, "Yes, I forge weapons right here and even supply a part of our \"army\". My "
"weapon forging skills were only evenly matched by my long lost brother, Lance. "
"I wonder where he could be now.")

Command(INTL( 1751, "ARMY"))
INTL( 2746, "Our army is indeed a great one. It has prevented the goblin hordes from "
"conquering our kingdom time and again.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 973, "Goodbye.") BREAK

Default
INTL( 2747, "I do not know about that.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void TtayhMark::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA

		NPC_SELL( 5266, __OBJ_POLISHED_SHORT_SWORD )
		NPC_SELL( 9323, __OBJ_POLISHED_LONG_SWORD )
		NPC_SELL( 14529, __OBJ_POLISHED_BROADSWORD )
		NPC_SELL( 20887, __OBJ_POLISHED_HAND_AXE )
		NPC_SELL( 5266, __OBJ_POLISHED_DIRK )
		NPC_SELL( 9323, __OBJ_POLISHED_DAGGER )
		NPC_SELL( 5266, __OBJ_STEEL_REINFORCED_WARHAMMER )
		NPC_SELL( 14529, __OBJ_FINE_STEEL_WARHAMMER )
		NPC_SELL( 1169, __OBJ_QUARTERSTAFF )
		NPC_SELL( 2361, __OBJ_STAFF_OF_THORNS )
		NPC_SELL( 5266, __OBJ_ELM_FLATBOW )
		NPC_SELL( 9323, __OBJ_ELM_LONGBOW )
		NPC_SELL( 14529, __OBJ_ELM_REFLEX_BOW )
		NPC_SELL( 20887, __OBJ_ELM_RECURVE_BOW )
		NPC_SELL( 1500, __OBJ_PINPOINT_ARROW )

		// ******************** BLACK MARKET ********************* // 

		NPC_SELL( 74,		__OBJ_LIGHT_HEALING_POTION)
		NPC_SELL( 183,		__OBJ_HEALING_POTION)
		NPC_SELL( 183,		__OBJ_MANA_ELIXIR) 		
		NPC_SELL( 1722,	__OBJ_RING_OF_LIGHT)
		NPC_SELL( 1901,	__OBJ_RING_OF_THE_BEAR)
		NPC_SELL( 2319,	__OBJ_RING_OF_CONFIDENCE)
		NPC_SELL( 6847,	__OBJ_STAFF_OF_THORNS_1)
		NPC_SELL( 14894,	__OBJ_SILVER_AXE)
		NPC_SELL( 3445,	__OBJ_RING_OF_ACCURACY)
		NPC_SELL( 609,		__OBJ_BUCKLE_OF_LOCKPICKS)
		NPC_SELL( 609,		__OBJ_LEATHER_BELT_OF_SURVIVAL)		
		
		NPC_BUY( WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | WEAPON, 0, 100000 )
		NPC_BUY( JEWEL | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | JEWEL | WEAPON, 0, 100000 )

		NPC_SOLD_ITEM( INTL( 1312, "Indeed, that is a fine choice.") )
		NPC_FAILED_SELL( INTL( 2351, "You do not have enough money my friend!") )
		NPC_BOUGHT_ITEM( INTL( 2750, "Here's your money.") )

	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
