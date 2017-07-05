//////////////////////////////////////////////////////////////////////
// RylethCth.cpp: implementation of the RylethCth class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "RylethCth.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RylethCth::RylethCth()
{}

RylethCth::~RylethCth()
{}

extern NPCstructure::NPC Mage;

//Nom: R'yleth Cth.
//Statistique: Windhowl Mage.
//Position: (2122, 636)
//World: 0
//Description: Guildmaster.
//Body: Mage.

//////////////////////////////////////////////////////////////////////////////////////////
void RylethCth::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of RylethCth
//
{
	npc = Mage;
	SET_NPC_NAME( "[3021]R'yleth Cth" );
	npc.InitialPos.X = 1604;
	npc.InitialPos.Y = 1244;
	npc.InitialPos.world = 0;  
}

//////////////////////////////////////////////////////////////////////////////////////////
void RylethCth::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of RylethCth
//
{

InitTalk

Begin
INTL( 2667, "What is a commoner like you doing here?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2668, "My name? Ignorant! I am R'yleth Cth and may you not forget it. I don't have "
"time to babble while there is still so much work to \"do\".")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2669, "Surely you jest! I am the greatest mage in this town, and maybe even in "
"all of \"Goldmoon\".")

Command(INTL( 523, "ANNABELLE"))
INTL( 584, "I wonder who she is.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2670, "Balork's Brand? Huh?")

Command(INTL( 1304, "BUY"))
""
Conversation
INTL( 2673, "Scrolls 'R Us, at your service...")
CreateItemList
	AddBuyItem((11111/USER_LEVEL), __OBJ_PLAIN_BLANK_SCROLL)
SendBuyItemList

Command(INTL( 2677, " DO "))
INTL( 2678, "Yes, researching new spells is a long and tiresome task, and as endless as "
"time. Moreover, I have to \"teach\" would-be mages the great art, which is "
"consuming much of my time.")

Command(INTL( 753, "GOLDMOON"))
INTL( 2679, "Goldmoon is the kingdom which contains the islands of Raven's Dust and "
"Arakas. Although it is a big kingdom, I am probably the highest ranking "
"and most powerful mage in all of it.")

Command(INTL( 496, "TEACH"))
INTL( 2680, "Don't tell me you need to learn new spells? I'm rather busy at the "
"moment, perhaps you should come back later.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 973, "Goodbye.") BREAK

Default
INTL( 2312, "I knew you would ask.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void RylethCth::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA

	NPC_SELL((11111/USER_LEVEL), __OBJ_PLAIN_BLANK_SCROLL)

	NPC_SOLD_ITEM( INTL( 2681, "Here it is.") )
	NPC_FAILED_SELL( INTL( 2682, "You need money to buy here.") )
	
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
