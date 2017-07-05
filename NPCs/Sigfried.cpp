/////////////////////////////////////////////////////////////////////
// Sigfried.cpp: implementation of the Sigfried class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Sigfried.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Sigfried::Sigfried()
{}

Sigfried::~Sigfried()
{}

extern NPCstructure::NPC ShopKeeper;

void Sigfried::Create(){
	npc = ShopKeeper;
	SET_NPC_NAME( "[3057]Sigfried" );
	npc.InitialPos.X = 2921;
	npc.InitialPos.Y = 1041;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

void Sigfried::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	switch(rnd(0, 1)){
	case 0: SHOUT(INTL( 1378, "AHHHHHHHHHHHHHH!")); break;
	case 1: SHOUT(INTL( 1379, "HELP!")); break;
	}

	self->Do(flee);
	self->SetTarget(target);
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Sigfried::OnTalk( UNIT_FUNC_PROTOTYPE )
{
CONSTANT DRAGONTOOTH = 1;
CONSTANT TIGERTOOTH = 2;
CONSTANT BROWSE = 3;

InitTalk

Begin
INTL( 11780, "Welcome to my \"shop\". My stock is somewhat smaller than usual these days. Everyone is buying a weapon or "
"two just in case the guards try anything... you know how it is.")
IF (CheckItem(__OBJ_MERCHANT_LETTER) == 0)
	RemFlag(__QUEST_SIGFRIED_REPORT)
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1992, "My name is Sigfried, I am the son of \"Geirfres\" the dwarf!")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 1993, "I own the best weapons shop in all the nearby lands! I inherited it from "
"my father, \"Geirfres\".")

Command(INTL( 523, "ANNABELLE"))
INTL( 1994, "I couldn't say.")

Command2(INTL( 510, "BRAND"),INTL( 509, "BALORK"))
INTL( 1995, "Balork is indeed a monster.") 

Command(INTL( 1996, "GEIRFRES"))
INTL( 1997, "He was the greatest dwarf warrior that ever lived! He killed thousands of "
"goblins each day, even on holidays! He hunted dragons for fun, and fought "
"gods in his spare time! And don't you dare think that I am lying, because "
"I have a dragon's \"tooth\" to prove it. I'm sure you envy him. After all, "
"who wouldn't? If you want to honor his memory, go out and kill as many "
"goblins as you can!")

Command3(INTL( 1998, "PART"),INTL( 1999, "GIVE"),INTL( 2000, "DRAGON TOOTH"))
""
IF (CheckFlag(__FLAG_SIGFRIED_SCAM) == 2)
	;int nDragonTooth = CheckItem(__OBJ_DRAGON_TOOTH); 
	FOR (0, nDragonTooth )
			TakeItem(__OBJ_DRAGON_TOOTH)
			GiveItem(__OBJ_TIGER_TOOTH)
	ENDFOR
	Conversation
	INTL( 2001, "You do not have to rub it in. You know of my shameless scam. I won't try to fool you "
	"again. The teeth I have are actually tiger's teeth. Still, they might be useful... Hmm... "
	"Well... Do you want to buy one tiger's tooth for 200 gold pieces?")
	SetYesNo(TIGERTOOTH)
ELSEIF (CheckFlag(__FLAG_SIGFRIED_SCAM) == 1)
	IF (CheckItem(__OBJ_DRAGON_TOOTH) >= 1)
		;int nDragonTooth = CheckItem(__OBJ_DRAGON_TOOTH); 
		FOR (0, nDragonTooth )
			TakeItem(__OBJ_DRAGON_TOOTH)
			GiveItem(__OBJ_TIGER_TOOTH)
		ENDFOR
		Conversation
		INTL( 2002, "Okay. I admit it! The tooth I sold you wasn't really a dragon tooth. It's actually "
		"the tooth of a tiger. Please don't tell anyone.")
		GiveFlag(__FLAG_SIGFRIED_SCAM, 2)
	ELSE
		Conversation
		INTL( 2003, "Argh. Who told you that I wasn't selling real dragon teeth? Shhh. Keep it down! It will "
		"ruin me if anybody knew about that.")
		GiveFlag(__FLAG_SIGFRIED_SCAM, 2) 
	ENDIF
ELSE
	Conversation
	INTL( 2004, "For a mere 200 gold pieces, I will give you this dragon tooth. Well, are you interested?")
	SetYesNo(DRAGONTOOTH)
ENDIF

Command(INTL( 2005, "TOOTH"))
INTL( 2006, "This tooth serves as a reminder of the great many feats my father "
"accomplished. For a modest fee, I will be willing to \"part\" with it...")

YES(DRAGONTOOTH)
Conversation
INTL( 2007, "Let me see your gold... ")
IF (Gold >= 200)
	Conversation
	INTL( 2008, "Here ya go! You should take great care of that precious tooth.")
	TakeGold(200)
	GiveItem(__OBJ_DRAGON_TOOTH)
ELSE
	Conversation
	INTL( 2009, "HEY! Are you trying to rip me off? I should call the guards down on you! Fortunately "
	"for you, I am in a rather good mood today. Come back when you have enough "
	"gold pieces. Perhaps you might want to \"sell\" some of your items.")
ENDIF

NO(DRAGONTOOTH)
Conversation
INTL( 2010, "You are missing out on an incredible opportunity.")

YesNoELSE(DRAGONTOOTH)
Conversation
INTL( 2011, "Whatever.")

YES(TIGERTOOTH)
IF (Gold >= 200)
	Conversation
	INTL( 2012, "Here ya go! I thank you for your discretion about my little scam. All the money I make "
	"is reinvested to forge better weapons for you, my favorite customer.")
	TakeGold(200)
	GiveItem(__OBJ_TIGER_TOOTH)
ELSE
	Conversation
	INTL( 2013, "You do not have enough gold pieces.")	
ENDIF

NO(TIGERTOOTH)
Conversation
INTL( 2014, "I know it's not a dragon tooth, but it could be useful... I think.")

YesNoELSE(TIGERTOOTH) 
Conversation
INTL( 2011, "Whatever.")


Command2(INTL( 1300, "REGISTRATION"),INTL( 1301, "LETTER"))
""
;int nMyVar = CheckGlobalFlag( __GLOBAL_QUEST_SIGFRIED_REPORT );

IF ( CheckFlag( __QUEST_SIGFRIED_REPORT ) == nMyVar && nMyVar != 0)
	Conversation
	INTL( 2015, "You again? What are you waiting for delivering my report to Lord Sunrock? I "
	"surely hope that you have not lost my report because if so, I will not "
	"supply you a new one and you can say goodbye to Lord Sunrock's reward.")
ELSE
	IF (CheckGlobalFlag (__GLOBAL_QUEST_SIGFRIED_REPORT) > CurrentRound)
		;int nTimeLeft = ((CheckGlobalFlag(__GLOBAL_QUEST_SIGFRIED_REPORT) - CurrentRound) / 1200);
		Conversation
		FORMAT(INTL( 2835, "You have registered yourself at the lord's office? I am truly sorry, but "
		"I have already sent someone to deliver a report to Windhowl. Perhaps I'll have "
		"an errand for you in %u minutes."), nTimeLeft)           
	ELSE
		IF (CheckItem(__OBJ_MERCHANT_LETTER) >= 1 )
			TakeItem(__OBJ_MERCHANT_LETTER)
	 		RemFlag(__QUEST_MERCHANT)
			IF (USER_LEVEL > 4)
				GiveGlobalFlag(__GLOBAL_QUEST_SIGFRIED_REPORT, 1 HOURS TDELAY )
				GiveItem(__OBJ_SIGFRIED_REPORT) 
				GetItemHandle(__OBJ_SIGFRIED_REPORT, SigfriedReport)
				GiveUnitFlag (SigfriedReport, __ITEM_QUEST_SIGFRIED_REPORT, CheckGlobalFlag( __GLOBAL_QUEST_SIGFRIED_REPORT ))
				GiveFlag(__QUEST_SIGFRIED_REPORT, CheckGlobalFlag( __GLOBAL_QUEST_SIGFRIED_REPORT ))
				Conversation
				INTL( 2017, "I thank you, brave adventurer, for accepting to deliver this report to "
				"Lord Sunrock of Windhowl. I have not had business in our fair sister "
				"town in months! I hope you will be able to easily take out the brigands "
				"that might stand in your way. Simply take the road out of town and "
				"follow it straight to Windhowl. Be careful! This letter must not fall "
				"in the wrong hands, it contains important information regarding my shop.") 
			ELSE
				Conversation
				INTL( 1645, "I highly doubt you would be able to make it to Windhowl at your level.")
			ENDIF
		ELSE
			Conversation
			INTL( 2018, "You will have to register yourself with the Lord of Lighthaven, Kirlor Dhul, "
			"if you would like to work for the merchants. Bring me back the letter "
			"proving that you are rightfully registered.")
		ENDIF
	ENDIF
ENDIF

Command(INTL( 1435, "LORD"))
INTL( 1958, "The lord's office is at the east side of town.")

Command(INTL( 2019, "GRAVEYARD"))
INTL( 2020, "Perhaps you should go and have a look at it. Be careful you don't go there "
"at night though.")

Command(INTL( 1960, "SHOP"))
INTL( 2021, "Do you wish to \"buy\" or \"sell\" anything?")

Command(INTL( 1304, "BUY"))
INTL( 2022, "I have the greatest weapons of all! I forge them here myself. Some of them have even "
"been blessed by the monks at the temple, mind you. Would you like to take a look at them?")
SetYesNo(BROWSE)

YES(BROWSE)
	CreateItemList
		AddBuyItem( 29, __OBJ_RUSTED_SHORT_SWORD )
		AddBuyItem( 605, __OBJ_RUSTED_LONG_SWORD )
		AddBuyItem( 2361, __OBJ_RUSTED_HAND_AXE )
		AddBuyItem( 29, __OBJ_RUSTED_DIRK )
		AddBuyItem( 605, __OBJ_RUSTED_DAGGER )
		AddBuyItem( 29, __OBJ_WOODEN_CLUB )
		AddBuyItem( 2361, __OBJ_STEEL_REINFORCED_CLUB )
		AddBuyItem( 29, __OBJ_WOODEN_STAFF )
		AddBuyItem( 392, __OBJ_IRON_STAFF )
		AddBuyItem( 29, __OBJ_ASHWOOD_FLATBOW )
		AddBuyItem( 605, __OBJ_ASHWOOD_LONGBOW )
		AddBuyItem( 2361, __OBJ_ASHWOOD_REFLEX_BOW )
		AddBuyItem( 100, __OBJ_WOODEN_ARROW )
	SendBuyItemList
NO(BROWSE)
	Conversation
	INTL( 3630, "That's too bad.")
YesNoELSE(BROWSE)
	Conversation
	INTL( 3631, "Well, do you want to see them or not?")
	SetYesNo(BROWSE)

Command(INTL( 1306, "SELL"))
INTL( 2023, "Well then, let's see what you have for sale...")
CreateItemList
	AddSellItem( WEAPON, 0, 100000 )
	AddSellItem( JEWEL | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | WEAPON, 0, 100000 )
	AddSellItem( MAGIC | JEWEL | WEAPON, 0, 100000 )
SendSellItemList(INTL( 2024, "I am sorry, but I do not see anything interesting in your inventory!") )

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1338, "Have a good day.") BREAK

Default
INTL( 2025, "I have no idea.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Sigfried::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Data exchange section of Sigfried, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_SHOP_DATA

		NPC_SELL( 29, __OBJ_RUSTED_SHORT_SWORD )
		NPC_SELL( 605, __OBJ_RUSTED_LONG_SWORD )
		NPC_SELL( 2361, __OBJ_RUSTED_HAND_AXE )
		NPC_SELL( 29, __OBJ_RUSTED_DIRK )
		NPC_SELL( 605, __OBJ_RUSTED_DAGGER )
		NPC_SELL( 29, __OBJ_WOODEN_CLUB )
		NPC_SELL( 2361, __OBJ_STEEL_REINFORCED_CLUB )
		NPC_SELL( 29, __OBJ_WOODEN_STAFF )
		NPC_SELL( 392, __OBJ_IRON_STAFF )
		NPC_SELL( 29, __OBJ_ASHWOOD_FLATBOW )
		NPC_SELL( 605, __OBJ_ASHWOOD_LONGBOW )
		NPC_SELL( 2361, __OBJ_ASHWOOD_REFLEX_BOW )
		NPC_SELL( 100, __OBJ_WOODEN_ARROW )

		NPC_BUY( WEAPON, 0, 100000 )
		NPC_BUY( JEWEL | WEAPON, 0, 100000 )
		NPC_BUY( MAGIC | WEAPON, 0, 100000 )
	 NPC_BUY( MAGIC | JEWEL | WEAPON, 0, 100000 )

		NPC_SOLD_ITEM( INTL( 2026, "Indeed, a fine choice.") )
		NPC_FAILED_SELL( INTL( 2027, "You don't have enough money for it!") )
		NPC_BOUGHT_ITEM( INTL( 2028, "Heh heh, very nice!") )

	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE
