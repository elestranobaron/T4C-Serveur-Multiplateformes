//////////////////////////////////////////////////////////////////////
// Rawlin.cpp: implementation of the Rawlin class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Rawlin.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Rawlin::Rawlin()
{}

Rawlin::~Rawlin()
{}

void Rawlin::OnAttack( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
      SWITCH (rnd.roll(dice(1,25)))
         CASE (1)
            SHOUT(INTL( 3752, "I know how to forge a weapon and I surely know how to use one!"))
         ENDCASE
         CASE (2)     
            SHOUT(INTL( 3753, "Heh... you bleed! Come bleed some more."));
         ENDCASE
         OTHERWISE
         ENDCASE
      ENDSWITCH
   }
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void Rawlin::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
		TFormat FORMAT;
      SWITCH (rnd.roll(dice(1,25)))
         CASE (1)
            SHOUT(INTL( 3754, "Ow! That hurts!"))
         ENDCASE
         CASE (2)
            SHOUT(INTL( 3755, "What have I done to you?"))
         ENDCASE
         CASE (3)
            SHOUT(FORMAT(INTL( 3756, "HEEEELLLPPP! %s is attempting to murder me!"),USER_NAME)) 
         ENDCASE
         OTHERWISE
         ENDCASE
      ENDSWITCH
   }
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

extern NPCstructure::NPC RawlinNPC;

void Rawlin::Create( ){
	npc = RawlinNPC;
   SET_NPC_NAME( "[2898]A traveling merchant" );
	npc.InitialPos.X = 1589; 
	npc.InitialPos.Y = 2315;
	npc.InitialPos.world = 0;
}

void Rawlin::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT BROWSE = 1; 

InitTalk

Begin
INTL( 3757, "Hey there! You look like an adventurer who could use a good \"weapon\".")

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
FORMAT(INTL( 3758, "Hello %s, I am pleased to make your acquaintance."), USER_NAME) 

Command(INTL( 3759, "RAWLIN"))
INTL( 3760, "Yes, that is the name.")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 3761, "Rawlin is the name.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 3762, "I wander around the country, selling my skillfully crafted \"weapons\" to "
"whoever's wealthy enough to purchase one.")

Command(INTL( 914, "WEAPON"))
INTL( 3763, "I am sure that you won't be disappointed if you ever \"buy\" a weapon from me. "
"Would you care to have a look at what I have?")
SetYesNo(BROWSE)

Command(INTL( 1304, "BUY"))
INTL( 3764, "You'd like to buy a weapon, eh? I'm sure I have the perfect weapon to match "
"your fighting style. Would you care to have a look at the weapons I have for sale?")
SetYesNo(BROWSE)

YES(BROWSE)
	CreateItemList
		AddBuyItem( 85182,  __OBJ_FINE_STEEL_SHORT_SWORD_1 )
		AddBuyItem( 111159, __OBJ_FINE_STEEL_LONG_SWORD_1 )
		AddBuyItem( 140583, __OBJ_FINE_STEEL_BROADSWORD_1 )
		AddBuyItem( 173463, __OBJ_FINE_STEEL_SCIMITAR_1 )
      AddBuyItem( 173463, __OBJ_FINE_STEEL_SCIMITAR1_DUAL )
		AddBuyItem( 249573, __OBJ_HIGH_METAL_SHORT_SWORD_1 )
		AddBuyItem( 173463, __OBJ_FINE_STEEL_HAND_AXE_1 )
      AddBuyItem( 173463, __OBJ_FINE_STEEL_HAND_AXE1_DUAL )
		AddBuyItem( 249573, __OBJ_FINE_STEEL_BATTLE_AXE_1 )
		AddBuyItem( 62661,  __OBJ_FINE_STEEL_DAGGER_1 )
      AddBuyItem( 62661,  __OBJ_FINE_STEEL_DAGGER1_DUAL )
		AddBuyItem( 111159, __OBJ_HIGH_METAL_DAGGER_1 )
		AddBuyItem( 111159, __OBJ_FINE_STEEL_MACE_1 )
      AddBuyItem( 111159, __OBJ_FINE_STEEL_MACE1_DUAL )
		AddBuyItem( 173463, __OBJ_HIGH_METAL_MACE_1 )
		AddBuyItem( 292803, __OBJ_HIGH_METAL_FLAIL_1 )
		AddBuyItem( 11898,  __OBJ_BO_1 )
		AddBuyItem( 17955,  __OBJ_RANG_KWAN_1 )
		AddBuyItem( 27969,  __OBJ_TETSUBO_1 )
		AddBuyItem( 111159, __OBJ_HICKORY_FLATBOW_1 )
		AddBuyItem( 140583, __OBJ_HICKORY_LONGBOW_1 )
		AddBuyItem( 173463, __OBJ_HICKORY_REFLEX_BOW_1 )
		AddBuyItem( 209790, __OBJ_HICKORY_RECURVE_BOW_1 )
		AddBuyItem( 249573, __OBJ_HICKORY_COMPOUND_BOW_1 )
	SendBuyItemList
NO(BROWSE)
	Conversation
	INTL( 3630, "That's too bad.")
YesNoELSE(BROWSE) 
	Conversation
	INTL( 3765, "So, you want to see the weapons I have for sale or not?")
	SetYesNo(BROWSE) 

Command(INTL( 1306, "SELL"))
INTL( 3766, "Let's see what you have... ")
CreateItemList    
		AddSellItem( WEAPON, 0, 100000 )
		AddSellItem( JEWEL | WEAPON, 0, 100000 )
		AddSellItem( MAGIC | WEAPON, 0, 100000 )
		AddSellItem( MAGIC | JEWEL | WEAPON, 0, 100000 )
SendSellItemList(INTL( 3767, "Hrmm. I am sorry but there is nothing in your inventory that I'd like to buy."))

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 3768, "Raven's Dust is the name of this island.")

Command(INTL( 998, "SILVERSKY"))
INTL( 3769, "That is the town where the castle of King Theodore XIII is located. It is located "
"somewhere to the south-east of the island.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 3770, "I doubt I'll make a sale with you today.") BREAK

Command(INTL( 3771, "?"))
""
SWITCH(rnd.roll(dice(1,3)))
	CASE(1)
		Conversation
		INTL( 3772, "You should ask someone else about that.")
	ENDCASE
	CASE(2)
		Conversation	
		INTL( 3773, "You ask too many questions. Are you here to \"buy\" or not?")
	ENDCASE
	CASE(3)
	INTL( 3774, "Heh. Do I look like Elvenstein?")
	ENDCASE
ENDSWITCH

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 3775, "Do not hesitate to come back if you need a good weapon.")
BREAK

Default
""
IF (rnd.roll(dice(1,2)) == 1)
	Conversation
	INTL( 3776, "Please, be brief. I have other customers waiting.")
ELSE
	Conversation
	INTL( 3777, "I have no time for this.")
ENDIF

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Rawlin::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Data exchange section of Rawlin.
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA

		NPC_SELL( 85182,  __OBJ_FINE_STEEL_SHORT_SWORD_1 )
		NPC_SELL( 111159, __OBJ_FINE_STEEL_LONG_SWORD_1 )
		NPC_SELL( 140583, __OBJ_FINE_STEEL_BROADSWORD_1 )
		NPC_SELL( 173463, __OBJ_FINE_STEEL_SCIMITAR_1 )
      NPC_SELL( 173463, __OBJ_FINE_STEEL_SCIMITAR1_DUAL )
		NPC_SELL( 249573, __OBJ_HIGH_METAL_SHORT_SWORD_1 )
		NPC_SELL( 173463, __OBJ_FINE_STEEL_HAND_AXE_1 )
      NPC_SELL( 173463, __OBJ_FINE_STEEL_HAND_AXE1_DUAL )
		NPC_SELL( 249573, __OBJ_FINE_STEEL_BATTLE_AXE_1 )
		NPC_SELL( 62661,  __OBJ_FINE_STEEL_DAGGER_1 )
      NPC_SELL( 62661,  __OBJ_FINE_STEEL_DAGGER1_DUAL )
		NPC_SELL( 111159, __OBJ_HIGH_METAL_DAGGER_1 )
		NPC_SELL( 111159, __OBJ_FINE_STEEL_MACE_1 )
      NPC_SELL( 111159, __OBJ_FINE_STEEL_MACE1_DUAL )
		NPC_SELL( 173463, __OBJ_HIGH_METAL_MACE_1 )
		NPC_SELL( 292803, __OBJ_HIGH_METAL_FLAIL_1 )
		NPC_SELL( 11898,  __OBJ_BO_1 )
		NPC_SELL( 17955,  __OBJ_RANG_KWAN_1 )
		NPC_SELL( 27969,  __OBJ_TETSUBO_1 )
		NPC_SELL( 111159, __OBJ_HICKORY_FLATBOW_1 )
		NPC_SELL( 140583, __OBJ_HICKORY_LONGBOW_1 )
		NPC_SELL( 173463, __OBJ_HICKORY_REFLEX_BOW_1 )
		NPC_SELL( 209790, __OBJ_HICKORY_RECURVE_BOW_1 )
		NPC_SELL( 249573, __OBJ_HICKORY_COMPOUND_BOW_1 )

		NPC_BUY( WEAPON, 0, 100000 )
		NPC_BUY( JEWEL | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | JEWEL | WEAPON, 0, 100000 )

		NPC_SOLD_ITEM( INTL( 3778, "Yes, a fine choice indeed.") )
		NPC_FAILED_SELL( INTL( 3779, "You do not have enough gold to buy this.") )
		NPC_BOUGHT_ITEM( INTL( 3780, "It's nice doing business with you.") )

	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE