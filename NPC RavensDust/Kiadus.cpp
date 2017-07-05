//////////////////////////////////////////////////////////////////////
// Kiadus.cpp: implementation of the Kiadus class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Kiadus.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Kiadus::Kiadus()
{}

Kiadus::~Kiadus()
{}

extern NPCstructure::NPC ShopKeeper;

void Kiadus::Create( ){
    npc = ShopKeeper;
	SET_NPC_NAME( "[2962]Kiadus" );
    npc.InitialPos.X = 1439;//2895;//1467; 
    npc.InitialPos.Y = 2359;//269;//2395; 
	npc.InitialPos.world = 0;//4;//0;
}

void Kiadus::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT BROWSE = 1;
CONSTANT SWORD = 2;
CONSTANT BRIBE = 3;

InitTalk

Begin
""
IF (TFCTime::IsDay())
	Conversation
	INTL( 5360, "Ahh, good day my friend!")
ELSEIF (TFCTime::IsEvening())
	Conversation
	INTL( 5361, "Good evening, friend.")
ELSE
	Conversation
	INTL( 7695, "Hello, friend.")
ENDIF

Command(INTL( 3629, " NAME "))
INTL( 5362, "I am called Kiadus.")

Command(INTL( 5363, "KIADUS"))
INTL( 2535, "Yes?")

Command(INTL( 489, "WORK"))
INTL( 5364, "I sell \"weapons\", my friend!")

Command2(INTL( 914, "WEAPON"), INTL( 1304, "BUY"))
INTL( 5365, "Would you like to take a look at what I have to offer?")
SetYesNo(BROWSE)

YES(BROWSE)
	IF (TFCTime::IsSleepTime())
		Conversation
		INTL( 5366, "I'm sorry, friend, but you'll have to come back later when the sun is up.")		
	ELSE
	
	CreateItemList
			AddBuyItem( 37053, __OBJ_FINE_STEEL_MACE )
         AddBuyItem( 37053, __OBJ_FINE_STEEL_MACE_DUAL )
			AddBuyItem( 57821, __OBJ_HIGH_METAL_MACE )
			AddBuyItem( 97601, __OBJ_HIGH_METAL_FLAIL )
			AddBuyItem( 3966,  __OBJ_BO )
			AddBuyItem( 5985,  __OBJ_RANG_KWAN )
			AddBuyItem( 9323,  __OBJ_TETSUBO )
		SendBuyItemList
	ENDIF
NO(BROWSE)
	Conversation
	INTL( 5367, "Well, that's fine with me, but you don't know what you're missing!")
YesNoELSE(BROWSE)
	Conversation
	INTL( 5368, "Make up your mind! Do you want to take a look at what I have to offer, yes or no?")
	SetYesNo(BROWSE)

Command(INTL( 1306, "SELL"))
""
IF (TFCTime::IsSleepTime())
	Conversation
	INTL( 5366, "I'm sorry, friend, but you'll have to come back later when the sun is up.")
ELSE
	Conversation
	INTL( 5369, "What do you wish to sell?")
	CreateItemList
		AddSellItem( WEAPON, 0, 100000 )
		AddSellItem( JEWEL | WEAPON, 0, 100000 )
		AddSellItem( MAGIC | WEAPON, 0, 100000 )
		AddSellItem( MAGIC | JEWEL | WEAPON, 0, 100000 )
	SendSellItemList( INTL( 5370, "I'm sorry, but I don't see anything interesting in your inventory.") )
ENDIF

Command(INTL( 3918, "VISITOR"))
""
IF (CheckFlag(__QUEST_VISITOR_SPOTTED) < 4)
	Conversation
	INTL( 5371, "I haven't seen anyone out of the ordinary.")
ELSEIF (CheckFlag(__QUEST_VISITOR_SPOTTED) == 4)
	Conversation
	INTL( 5372, "Well, a few moments ago a strange fellow stopped by with an eerie-looking \"sword\". He said he would "
	"greatly appreciate it if I took it off his hands. I did what any other weaponsmith would've "
	"done! I bought it! I think the lad said he had a \"sister\" living in this very town.")
	GiveFlag(__QUEST_VISITOR_SPOTTED, 5)
	GiveFlag(__FLAG_ASKED_ABOUT_SWORD, 1)
ELSEIF (CheckFlag(__QUEST_VISITOR_SPOTTED) >= 5)
	Conversation
	INTL( 5373, "I don't know where exactly he went to, but he said he was going to see his \"sister\" first.")
ENDIF

Command(INTL( 5374, "SISTER"))
""
IF(CheckFlag( __FLAG_PAID_KIADUS_BRIBE) == 2)
	Conversation
	INTL( 5375, "Hmm, it would seem I have forgotten what her name is again. If you would give me another 2000 gold, "
	"I'm sure I would remember it again. So how about it?")
	SetYesNo(BRIBE)
ELSEIF(CheckFlag( __FLAG_PAID_KIADUS_BRIBE) == 1)
	Conversation
	INTL( 5376, "Oh, you want her name, that's right! I almost forgot again, heh. If I remember correctly, the name of his "
	"sister was Amandra.")
	GiveFlag( __FLAG_PAID_KIADUS_BRIBE, 2)
ELSE
	INTL( 5377, "Hmm, I don't quite remember what her name was, perhaps a little gold would refresh my memory. How about "
	"giving me 2000 gold?")
	SetYesNo(BRIBE)
ENDIF

YES(BRIBE)
	IF(Gold >= 2000)
		TakeGold(2000)
		Conversation
		INTL( 5378, "Thank you very much!")
		GiveFlag( __FLAG_PAID_KIADUS_BRIBE, 1)
	ELSEIF(Gold >= 1000)
		TakeGold(Gold)
		Conversation
		INTL( 5379, "You don't quite have enough, but I'll take it anyway.")
	ELSE
		Conversation
		INTL( 5380, "It would seem you don't have enough gold. Come back when you do.")
	ENDIF

NO(BRIBE)
	Conversation
	INTL( 5381, "Hmm, fine then. I suggest you leave my store, unless you want to buy something, that is.")

YesNoELSE(BRIBE)
	Conversation
	INTL( 5382, "So how about it? Do you want to give me 2000 gold in exchange for his sister's name?")
	SetYesNo(BRIBE)

Command(INTL( 4880, "SWORD"))
""
SWITCH(CheckFlag(__FLAG_ASKED_ABOUT_SWORD))
	CASE(0)
		Conversation
		INTL( 11518, "Sword? I'm sorry but I don't sell swords.")
	ENDCASE
	CASE(1)
		Conversation
		INTL( 5384, "I haven't really had time to study it much, but it sure looks like a strong blade.")
	ENDCASE
	CASE(2)
		Conversation
		INTL( 5385, "Heh, you want the sword eh? Well, you can forget about it! I seriously doubt you would have enough money "
		"to buy it!")
		GiveFlag( __FLAG_ASKED_ABOUT_SWORD, 3)
	ENDCASE
	CASE(3)
		Conversation
		INTL( 5386, "Hmmm, okay I'll sell it to you. How about for 100,000,000,000 gold? Ha ha ha! I told you I'm "
		"not selling it! Besides, you could never pay the price I would ask for it.")
		GiveFlag( __FLAG_ASKED_ABOUT_SWORD, 4)
	ENDCASE
	CASE(4)
		Conversation
		INTL( 5387, "Ha ha ha! You drive a hard bargain! Very well, I will sell you the sword you ask for. Are you willing "
		"to pay the small sum of 25000 gold for it?")
		SetYesNo(SWORD)
	ENDCASE
	CASE(5)
		Conversation
		INTL( 5388, "You have enough money now? Well don't just stand there, do you want to buy the sword or not?")
		SetYesNo(SWORD)
	ENDCASE
	CASE(6)
		IF(CheckItem(__OBJ_FAKE_BLADE_OF_RUIN) == 0) 
			Conversation
			INTL( 11725, "You've lost the special sword I sold you? That was one of a kind you numbskull! Harumpft, and you need a new one now, eh? " 
			"Very well then, here's another one from my secret stash.") 
			 GiveItem( __OBJ_FAKE_BLADE_OF_RUIN)
	
		ELSE
			Conversation
			INTL( 5389, "I already sold you the only special sword I had, now begone unless you want to \"buy\" something else!")			
		ENDIF
	ENDCASE
	CASE(7)
		Conversation
		INTL( 5390, "What? The sword was a fake? I had no idea, I swear!")
		GiveFlag( __FLAG_ASKED_ABOUT_SWORD, 8)
	ENDCASE
	CASE(8)
		Conversation
		INTL( 5391, "Alright, alright! I'll give you part of your money back, that's the best I can do. Here's "
		"5000 gold, now leave because that's all you're going to get!")
		GiveGold(5000)
		GiveFlag( __FLAG_ASKED_ABOUT_SWORD, 9)
	ENDCASE
	OTHERWISE
		Conversation
		INTL( 5383, "Sword? I have many swords for sale. I even have a few axes.")
	ENDCASE
ENDSWITCH

YES(SWORD)
	IF(Gold >= 25000)
		TakeGold(25000)
		Conversation
		INTL( 5392, "Thank you very much, and this is for you!")
		GiveItem( __OBJ_FAKE_BLADE_OF_RUIN)
		GiveFlag( __FLAG_ASKED_ABOUT_SWORD, 6)
	ELSE
		Conversation
		INTL( 5380, "It would seem you don't have enough gold. Come back when you do.")
		GiveFlag( __FLAG_ASKED_ABOUT_SWORD, 5)
	ENDIF
NO(SWORD)
	Conversation
	INTL( 5393, "I really think you're making a mistake, but it's your decision.")
YesNoELSE(SWORD)
	Conversation
	INTL( 5394, "Well, do you want to buy it or not?")
	SetYesNo(SWORD)

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 5395, "Feel free to stop by anytime!") BREAK

Default
INTL( 5396, "I honestly don't know.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Kiadus::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA
		NPC_SELL( 37053, __OBJ_FINE_STEEL_MACE )
      NPC_SELL( 37053, __OBJ_FINE_STEEL_MACE_DUAL )
		NPC_SELL( 57821, __OBJ_HIGH_METAL_MACE )
		NPC_SELL( 97601, __OBJ_HIGH_METAL_FLAIL )
		NPC_SELL( 3966,  __OBJ_BO )
		NPC_SELL( 5985,  __OBJ_RANG_KWAN )
		NPC_SELL( 9323,  __OBJ_TETSUBO )

		NPC_BUY( WEAPON, 0, 100000 )
		NPC_BUY( JEWEL | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | JEWEL | WEAPON, 0, 100000 )

		NPC_SOLD_ITEM( INTL( 5397, "Very good indeed!") )
		NPC_FAILED_SELL( INTL( 5398, "Come back when you have enough money.") )
		NPC_BOUGHT_ITEM( INTL( 2750, "Here's your money.") )

	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
