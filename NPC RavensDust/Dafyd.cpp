//////////////////////////////////////////////////////////////////////
// Dafyd.cpp: implementation of the Dafyd class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Dafyd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Dafyd::Dafyd()
{}

Dafyd::~Dafyd()
{}

void Dafyd::OnAttack( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
      SWITCH (rnd.roll(dice(1,25)))
         CASE (1)
            SHOUT(INTL( 6400, "I'll not stand idle while you desecrate this land. Prepare to fight!"))
         ENDCASE
         CASE (2)     
            SHOUT(INTL( 6401, "I will rid this world of your presence even if it kills me!"))
         ENDCASE
         OTHERWISE
         ENDCASE
      ENDSWITCH
   }
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void Dafyd::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
   if( target != NULL )
   {
		TFormat FORMAT;
      SWITCH (rnd.roll(dice(1,25)))
         CASE (1)
            SHOUT(INTL( 6402, "Stop at once!"))
         ENDCASE
         CASE (2)
            SHOUT(INTL( 6403, "Stop I say!"))
         ENDCASE
         CASE (3)
            SHOUT(FORMAT(INTL( 6404, "Is there no end to this?! You will pay for your folly, %s!"),USER_NAME)) 
         ENDCASE
         OTHERWISE
         ENDCASE
      ENDSWITCH
   }
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

extern NPCstructure::NPC DafydNPC;

void Dafyd::Create( ){
	npc = DafydNPC;
   SET_NPC_NAME( "[2940]A peaceful traveler" );
	npc.InitialPos.X = 440; 
	npc.InitialPos.Y = 2285;
	npc.InitialPos.world = 0;
}

void Dafyd::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT BROWSE = 1; 

InitTalk

Begin
INTL( 6405, "Hail, fellow traveler!")

Command3(INTL( 2034, "HELLO"),INTL( 2035, " HI "), INTL( 6357, "HAIL"))
INTL( 6406, "Greetings, I gladly welcome your company in this desolate place.")

Command(INTL( 6407, "DAFYD"))
INTL( 6408, "That is my name, yes.")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 6409, "I am called Dafyd.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 6410, "I come from a land far from here in search of new and interesting objects to add "
"to my \"collection\".")

Command(INTL( 5896, "COLLECTION"))
INTL( 6411, "Well, so far I have accumulated a great deal of \"weapons\" and \"armor\" of a rather high "
"quality. Unfortunately, I cannot carry everything I own, so I am restrained to bringing only "
"a few weapons.")

Command(INTL( 916, "ARMOR"))
INTL( 6412, "As I said before, it is quite impossible for me to carry all of my armor collection without "
"the use of a charriot or wagon of some kind.")

Command(INTL( 914, "WEAPON"))
INTL( 6413, "The weapons in my collection are among the very finest you will ever see around these parts.")

Command(INTL( 1304, "BUY"))
INTL( 6414, "What? You wish to buy one of them? Hmm, I don't know about that. I suppose there is no harm "
"in it, I can always find another one. Well, do you want to take a look at what I have?")
SetYesNo(BROWSE)

YES(BROWSE)
	CreateItemList
		AddBuyItem( 283940, __OBJ_FINE_STEEL_SHORT_SWORD_2 )
		AddBuyItem( 370530, __OBJ_FINE_STEEL_LONG_SWORD_2 )
		AddBuyItem( 468610, __OBJ_FINE_STEEL_BROADSWORD_2 )
		AddBuyItem( 578210, __OBJ_FINE_STEEL_SCIMITAR_2 )
      AddBuyItem( 578210, __OBJ_FINE_STEEL_SCIMITAR2_DUAL )
		AddBuyItem( 831910, __OBJ_HIGH_METAL_SHORT_SWORD_2 )
		AddBuyItem( 578210, __OBJ_FINE_STEEL_HAND_AXE_2 )
      AddBuyItem( 578210, __OBJ_FINE_STEEL_HAND_AXE2_DUAL )
		AddBuyItem( 831910, __OBJ_FINE_STEEL_BATTLE_AXE_2 )
		AddBuyItem( 208870, __OBJ_FINE_STEEL_DAGGER_2 )
      AddBuyItem( 208870, __OBJ_FINE_STEEL_DAGGER2_DUAL )
		AddBuyItem( 370530, __OBJ_HIGH_METAL_DAGGER_2 )
		AddBuyItem( 370530, __OBJ_FINE_STEEL_MACE_2 )
      AddBuyItem( 370530, __OBJ_FINE_STEEL_MACE2_DUAL )
		AddBuyItem( 578210, __OBJ_HIGH_METAL_MACE_2 )
		AddBuyItem( 976010, __OBJ_HIGH_METAL_FLAIL_2 )
		AddBuyItem( 39660 , __OBJ_BO_2 )
		AddBuyItem( 59850 , __OBJ_RANG_KWAN_2 )
		AddBuyItem( 93230 , __OBJ_TETSUBO_2 )
		AddBuyItem( 370530, __OBJ_HICKORY_FLATBOW_2 )
		AddBuyItem( 468610, __OBJ_HICKORY_LONGBOW_2 )
		AddBuyItem( 578210, __OBJ_HICKORY_REFLEX_BOW_2 )
		AddBuyItem( 699300, __OBJ_HICKORY_RECURVE_BOW_2 )
		AddBuyItem( 831910, __OBJ_HICKORY_COMPOUND_BOW_2 )
	SendBuyItemList
NO(BROWSE)
	Conversation
	INTL( 6415, "Oh well, I don't mind that much.")
YesNoELSE(BROWSE) 
	Conversation
	INTL( 6416, "Do you want to take a look at what I have or not?")
	SetYesNo(BROWSE) 

Command(INTL( 1306, "SELL"))
INTL( 6417, "Let me take a look at what you have for sale...")
CreateItemList    
	AddSellItem( WEAPON, 0, 100000 )
	AddSellItem( JEWEL | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | JEWEL | WEAPON, 0, 100000 )
SendSellItemList(INTL( 6418, "Hmm, I don't see anything I could add to my collection... that is too bad."))

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 6419, "Raven's Dust is the island you are on, friend.")

Command(INTL( 998, "SILVERSKY"))
INTL( 6420, "I do not like towns all that much, to tell you the truth. I would rather be outside in the "
"wilderness with all the wild beasts than the \"simple-minded\" people of that city.")

Command(INTL( 6421, "MINDED"))
INTL( 6422, "They are so caught up with their petty disputes that they don't even notice the \"enemy\" is advancing "
"upon them even as we speak.")

Command(INTL( 6423, "ENEMY"))
INTL( 6424, "Why, the orcs of course! Have you been living in a dungeon all your life? ...Oh dear, please forgive my "
"loss of temper. I tend to become rather hostile when I start to think of the \"happenings\" of this isle.")

Command(INTL( 6425, "HAPPENINGS"))
INTL( 6426, "The orcs move ever closer and all the king thinks of doing is sleeping. The people of that town are no better, "
"mind you. All they do is quarrel amongst themselves about whether the king is fit to rule or not. It is a "
"sad thing, I tell you.")

Command(INTL( 744, "ORC"))
INTL( 6427, "Their numbers are ever increasing, and there is not much anyone can do about it. I imagine they will someday "
"overtake the town, and I pray for a swift death for any who will still be there when it happens.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 6428, "I will not tolerate such language from anyone. You should leave now.") BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 6429, "Good luck in your travels, friend.")
BREAK

Default
""
IF (rnd.roll(dice(1,2)) == 1)
	Conversation
	INTL( 6430, "I don't know, friend.")
ELSE
	Conversation
	INTL( 6431, "That is not my concern at the moment.")
ENDIF

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Dafyd::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Data exchange section of Dafyd.
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA

		NPC_SELL( 283940, __OBJ_FINE_STEEL_SHORT_SWORD_2 )
		NPC_SELL( 370530, __OBJ_FINE_STEEL_LONG_SWORD_2 )
		NPC_SELL( 468610, __OBJ_FINE_STEEL_BROADSWORD_2 )
		NPC_SELL( 578210, __OBJ_FINE_STEEL_SCIMITAR_2 )
      NPC_SELL( 578210, __OBJ_FINE_STEEL_SCIMITAR2_DUAL )
		NPC_SELL( 831910, __OBJ_HIGH_METAL_SHORT_SWORD_2 )
		NPC_SELL( 578210, __OBJ_FINE_STEEL_HAND_AXE_2 )
      NPC_SELL( 578210, __OBJ_FINE_STEEL_HAND_AXE2_DUAL )
		NPC_SELL( 831910, __OBJ_FINE_STEEL_BATTLE_AXE_2 )
		NPC_SELL( 208870, __OBJ_FINE_STEEL_DAGGER_2 )
      NPC_SELL( 208870, __OBJ_FINE_STEEL_DAGGER2_DUAL )
		NPC_SELL( 370530, __OBJ_HIGH_METAL_DAGGER_2 )
		NPC_SELL( 370530, __OBJ_FINE_STEEL_MACE_2 )
      NPC_SELL( 370530, __OBJ_FINE_STEEL_MACE2_DUAL )
		NPC_SELL( 578210, __OBJ_HIGH_METAL_MACE_2 )
		NPC_SELL( 976010, __OBJ_HIGH_METAL_FLAIL_2 )
		NPC_SELL( 39660 , __OBJ_BO_2 )
		NPC_SELL( 59850 , __OBJ_RANG_KWAN_2 )
		NPC_SELL( 93230 , __OBJ_TETSUBO_2 )
		NPC_SELL( 370530, __OBJ_HICKORY_FLATBOW_2 )
		NPC_SELL( 468610, __OBJ_HICKORY_LONGBOW_2 )
		NPC_SELL( 578210, __OBJ_HICKORY_REFLEX_BOW_2 )
		NPC_SELL( 699300, __OBJ_HICKORY_RECURVE_BOW_2 )
		NPC_SELL( 831910, __OBJ_HICKORY_COMPOUND_BOW_2 )

		NPC_BUY( WEAPON, 0, 100000 )
		NPC_BUY( JEWEL | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | JEWEL | WEAPON, 0, 100000 )

		NPC_SOLD_ITEM( INTL( 6432, "Very well, here you go.") )
		NPC_FAILED_SELL( INTL( 6433, "It seems you do not have enough gold to pay the price I ask for.") )
		NPC_BOUGHT_ITEM( INTL( 6434, "Ahh yes, this will make a splendid addition to my collection.") )

	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE