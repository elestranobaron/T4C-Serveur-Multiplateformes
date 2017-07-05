#pragma hdrstop
#include "RhodarHeatforge.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RhodarHeatforge::RhodarHeatforge()
{}

RhodarHeatforge::~RhodarHeatforge()
{}

extern NPCstructure::NPC ShopKeeper;

void RhodarHeatforge::Create(){
        npc = ShopKeeper;
        SET_NPC_NAME( "[2977]Rhodar Heatforge" );
        npc.InitialPos.X = 1493; 
        npc.InitialPos.Y = 2423;
        npc.InitialPos.world = 0;
}

void RhodarHeatforge::OnTalk( UNIT_FUNC_PROTOTYPE )
{
CONSTANT BROWSE = 1;
CONSTANT HAMMER = 2; 
CONSTANT GOBLIN = 3; 

InitTalk

Begin
""
IF (TFCTime::IsSleepTime())
	Conversation
	INTL( 5665, "Sorry, we're closed during the night and I'm off to bed.")
	BREAK	
ELSE		
	Conversation
	INTL( 5664, "We are selling the very best \"weapons\" you could find on Raven's Dust.")
ENDIF
 
Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5666, "The name is Rhodar Heatforge but people usually call me Rhodar.")

Command2(INTL( 5576, "RHODAR"),INTL( 5577, "HEATFORGE"))
INTL( 5667, "Yes, that's my name.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 5668, "I am the weaponsmith of the village. I forge all my weapons myself from ore obtained in the mountains.")

Command2(INTL( 914, "WEAPON"),INTL( 1304, "BUY"))
INTL( 5669, "You want to buy something, is that it?")
SetYesNo(BROWSE)

YES(BROWSE)
	CreateItemList
		AddBuyItem( 28394, __OBJ_FINE_STEEL_SHORT_SWORD )
		AddBuyItem( 37053, __OBJ_FINE_STEEL_LONG_SWORD )
		AddBuyItem( 46861, __OBJ_FINE_STEEL_BROADSWORD )
		AddBuyItem( 57821, __OBJ_FINE_STEEL_SCIMITAR )
      AddBuyItem( 57821, __OBJ_FINE_STEEL_SCIMITAR_DUAL )
		AddBuyItem( 83191, __OBJ_HIGH_METAL_SHORT_SWORD )
		AddBuyItem( 57821, __OBJ_FINE_STEEL_HAND_AXE )
      AddBuyItem( 57821, __OBJ_FINE_STEEL_HAND_AXE_DUAL )
		AddBuyItem( 83191, __OBJ_FINE_STEEL_BATTLE_AXE )
		AddBuyItem( 20887, __OBJ_FINE_STEEL_DAGGER )
      AddBuyItem( 20887, __OBJ_FINE_STEEL_DAGGER_DUAL )
		AddBuyItem( 37053, __OBJ_HIGH_METAL_DAGGER )
		AddBuyItem( 37053, __OBJ_HICKORY_FLATBOW )
		AddBuyItem( 46861, __OBJ_HICKORY_LONGBOW )
		AddBuyItem( 57821, __OBJ_HICKORY_REFLEX_BOW )
		AddBuyItem( 69930, __OBJ_HICKORY_RECURVE_BOW )
		AddBuyItem( 83191, __OBJ_HICKORY_COMPOUND_BOW )
		AddBuyItem( 15000, __OBJ_BONE_TIPPED_ARROW )
	SendBuyItemList
NO(BROWSE)
	Conversation
	INTL( 5670, "I'm sorry to hear that.")
YesNoELSE(BROWSE)
	Conversation
	INTL( 5671, "Well, do you want to buy something or not?")
	SetYesNo(BROWSE)

Command(INTL( 5672, "HAMMER"))
""
IF (CheckItem(__OBJ_RHODAR_HAMMER) >= 1)
	Conversation
	FORMAT(INTL( 5673, "Wait a minute! Lemme see that hammer you have... hey, that's mine!!! How did you find it?! Ah.. Qardos.. that wretched blackguard... of course! If I was a bit younger, I swear "
	"I'd put this hammer to good use. Now, will you give it back to me?"), USER_NAME)
	SetYesNo(HAMMER)
ELSE
	Conversation
	INTL( 5674, "What about it?")
ENDIF

YES(HAMMER)
	IF (CheckItem(__OBJ_RHODAR_HAMMER) >= 1)
		TakeItem(__OBJ_RHODAR_HAMMER)
		Conversation
		INTL( 5675, "Thanks, friend. Here, I give ya 3500 gold pieces for your troubles. I can "	
		"get back to work by forging some \"Goblin\" \"Slayer\".")
		GiveGold(3500)
		;int nExpReward = 8000; 	
		GiveXP(nExpReward)
		Conversation
		FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), nExpReward)
	ELSE
		Conversation
		INTL( 5676, "I ain't fooled that easily. I can see that you do not have my hammer!")
	ENDIF
NO(HAMMER)
	Conversation
	INTL( 5677, "Let me put it this way. There's only one answer I wanna hear from you, and that "
	"answer is \"yes\".")
	SetYesNo(HAMMER)
YesNoELSE(HAMMER)
	Conversation
	INTL( 5678, "Pardon? Did you say yes or no?")
	SetYesNo(HAMMER)

Command(INTL( 5679, "GOBLIN SLAYER"))
""
IF (CheckFlag(__GOBLINS_KILLED_BY_HERO) >= 500)
	Conversation
	FORMAT(INTL( 5680, "Hey, you've killed %u goblins, right? Looks like you hate them as much as I do. "
	"Come with me in the back of the store, I've got something to show you that might "
	"be useful. Look at this beautiful sword, it's a Goblin Slayer sword. It has "
	"the uncanny ability of literally destroying goblins. It's yours if you're willing to "
	"pay the fair price of 25000 gold pieces. Does that sound fair to you?"), CheckFlag(__GOBLINS_KILLED_BY_HERO))
	SetYesNo(GOBLIN)
ELSE
	Conversation
	INTL( 5681, "This weapon is not for someone like you.")
ENDIF

YES(GOBLIN)
IF (Gold >= 25000)
	TakeGold(25000)
	GiveItem(__OBJ_GOBLIN_SLAYER)
	RemFlag(__GOBLINS_KILLED_BY_HERO)
	Conversation
	INTL( 5682, "Here's your brand new sword. I assure you that you won't be disappointed.")
ELSE
	;int nGold = 25000 - Gold; 
	Conversation
	FORMAT(INTL( 4995, "You do not have enough gold. You need %u more."), nGold)
ENDIF

NO(GOBLIN)
Conversation
INTL( 5068, "Too bad.")

YesNoELSE(GOBLIN)
Conversation
INTL( 5683, "Are you saying that you want this sword or not?")
SetYesNo(GOBLIN)

Command(INTL( 1492, "DESERT"))
INTL( 5684, "The desert of \"Vulture's\" \"Den\" is nearly as hot as my forge. You shouldn't go there or I'll lose yet another good customer.") 

Command(INTL( 3865, "VULTURE'S DEN"))
INTL( 5685, "That's the name of the desert on the west part of the island.")

Command(INTL( 1306, "SELL"))
INTL( 2773, "What do you want to sell?")
CreateItemList
	AddSellItem( WEAPON, 0, 100000 )
	AddSellItem( JEWEL | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | JEWEL | WEAPON, 0, 100000 )
SendSellItemList(INTL( 5370, "I'm sorry, but I don't see anything interesting in your inventory.") )

Command(INTL( 3854, "RAVENWOOD"))
INTL( 5686, "I would not go there if I were you. Unless you're wielding one of my great weapons of course.")

Command(INTL( 5687, "BROWNBARK"))
INTL( 5688, "Brownbark is a woodcutter who lives somewhere in Ravenwood "
"with his son, Anrak.")

Command2(INTL( 3862, "BANE"),INTL( 3863, "BLACKBLOOD"))
INTL( 5689, "Bane Blackblood wants to rule over the island of Raven's Dust but he won't "
"as \"King\" \"Theodore\" \"XIII\"'s guards are using my weapons. *smile*")

Command2(INTL( 1072, "KING"),INTL( 754, "THEODORE"))
INTL( 5690, "I heard he won the throne by sleeping. I wish I could do the same.")

Command2(INTL( 4185, "GHUNDARG"),INTL( 4186, "RUMBLEFOOT"))
INTL( 5691, "He is the orc leader.")

Command(INTL( 3868, "ALTHEA"))
INTL( 5692, "Althea is the name of the world in which you are.")

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 5693, "Do not be afraid to come back to my shop if you need anything else.")
BREAK

Default
INTL( 4675, "I don't have time for that nonsense.")

EndTalk
}
//////////////////////////////////////////////////////////////////////////////////////////
void RhodarHeatforge::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Data exchange section of RhodarHeatforge, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA
			NPC_SELL( 28394, __OBJ_FINE_STEEL_SHORT_SWORD )
			NPC_SELL( 37053, __OBJ_FINE_STEEL_LONG_SWORD )
			NPC_SELL( 46861, __OBJ_FINE_STEEL_BROADSWORD )
			NPC_SELL( 57821, __OBJ_FINE_STEEL_SCIMITAR )
         NPC_SELL( 57821, __OBJ_FINE_STEEL_SCIMITAR_DUAL )
			NPC_SELL( 83191, __OBJ_HIGH_METAL_SHORT_SWORD )
			NPC_SELL( 57821, __OBJ_FINE_STEEL_HAND_AXE )
         NPC_SELL( 57821, __OBJ_FINE_STEEL_HAND_AXE_DUAL )
			NPC_SELL( 83191, __OBJ_FINE_STEEL_BATTLE_AXE )
			NPC_SELL( 20887, __OBJ_FINE_STEEL_DAGGER )
         NPC_SELL( 20887, __OBJ_FINE_STEEL_DAGGER_DUAL )
			NPC_SELL( 37053, __OBJ_HIGH_METAL_DAGGER )
			NPC_SELL( 37053, __OBJ_HICKORY_FLATBOW )
			NPC_SELL( 46861, __OBJ_HICKORY_LONGBOW )
			NPC_SELL( 57821, __OBJ_HICKORY_REFLEX_BOW )
			NPC_SELL( 69930, __OBJ_HICKORY_RECURVE_BOW )
			NPC_SELL( 83191, __OBJ_HICKORY_COMPOUND_BOW )
			NPC_SELL( 15000, __OBJ_BONE_TIPPED_ARROW )

          NPC_BUY( WEAPON, 0, 100000 )
          NPC_BUY( JEWEL | WEAPON, 0, 100000 )
          NPC_BUY( MAGIC | WEAPON, 0, 100000 )
			NPC_BUY( MAGIC | JEWEL | WEAPON, 0, 100000)

          NPC_SOLD_ITEM( INTL( 5694, "Ahh yes, a fine choice.") )
          NPC_FAILED_SELL( INTL( 5695, "You do not have enough money for that.") )
          NPC_BOUGHT_ITEM( INTL( 2028, "Heh heh, very nice!") )
	
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
