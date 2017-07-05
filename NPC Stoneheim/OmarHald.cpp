#pragma hdrstop
#include "OmarHald.h"

OmarHald::OmarHald()
{}

OmarHald::~OmarHald()
{}

extern NPCstructure::NPC OmarHaldNPC;

void OmarHald::Create( void )
{
        npc = OmarHaldNPC;
        SET_NPC_NAME( "[10902]Omar Hald" );
        npc.InitialPos.X = 305;
        npc.InitialPos.Y = 840;
        npc.InitialPos.world = 0;
}

void OmarHald::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT RAWCRYSTAL = 1;
CONSTANT BROWSE = 2; 

InitTalk

Begin
INTL( 2369, "Hello.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 9132, "I am Omar Hald, the renowned jeweler.")

Command4(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"),INTL( 9133, "JEWELER"))
INTL( 9134, "I am the town's jeweler. I am particularly skilled when it comes to polishing \"raw\" \"crystals\". "
"You might also be interested to \"buy\" some of my wares.")

Command(INTL( 9135, "RAW CRYSTAL"))
INTL( 9136, "You can find raw crystals in the caves on the eastern side of Stoneheim. The skraugs are "
"particularly fond of them. I have developed an expertise that allows me to polish these "
"raw crystals into a fine gem of courage. However, I require 9 raw crystals and 50,000 gold "
"for my services to create a single gem.")
IF (CheckItem(__OBJ_RAW_CRYSTAL) >= 9)
	Conversation
	INTL( 9137, " Hmmm, I see that you have the required raw crystals in your possession. Shall I polish them "
	"into a single gem of courage? I am sure that my work will please you.")
	SetYesNo(RAWCRYSTAL)
ENDIF 

YES(RAWCRYSTAL)
	IF ((CheckItem(__OBJ_RAW_CRYSTAL) >= 9) && (Gold > 50000))
		Conversation
		INTL( 9138, "I'll polish these 9 raw crystals... please wait... all done! You are now the owner of a finely polished "
		"gem of courage.")
		PRIVATE_SYSTEM_MESSAGE(INTL( 9139, "You give the raw crystals along with 50000 gold to Omar."))
		PRIVATE_SYSTEM_MESSAGE(INTL( 9140, "Omar gives you a gem of courage!")) 
		FOR(0,9) 
			TakeItem(__OBJ_RAW_CRYSTAL) 
		ENDFOR
		TakeGold(50000)
		GiveItem(__OBJ_GEM_OF_COURAGE) 
	ELSEIF (Gold > 50000) 
		IF (CheckItem(__OBJ_RAW_CRYSTAL) == 0) 
			Conversation
			INTL( 9141, "You don't even have a single raw crystal. I cannot create a gem out of thin air!")
		ELSEIF (CheckItem(__OBJ_RAW_CRYSTAL) == 8) 
			Conversation
			INTL( 9142, "You have 8 raw crystals. You only need another one and I can get to work.")
		ELSE
			Conversation
			FORMAT(INTL( 9143, "You need %u additional raw crystals."), ( 9 - CheckItem(__OBJ_RAW_CRYSTAL)))		
		ENDIF
	ELSE
		Conversation
		INTL( 9144, "I require a fee 50,000 gold to accomplish this delicate work.")
	ENDIF

NO(RAWCRYSTAL)
	Conversation
	INTL( 4223, "So be it.")

YesNoELSE(RAWCRYSTAL)
	Conversation
	INTL( 9145, "Do you want me to polish your raw crystals or not?")
	SetYesNo(RAWCRYSTAL)

Command2(INTL( 1304, "BUY"),INTL( 1960, "SHOP"))
INTL( 11337, "Do you want to take a look at my selection of expertly crafted jewelry?")
SetYesNo(BROWSE)

YES(BROWSE)
	CreateItemList	
		AddBuyItem( 3870 , __OBJ_RING_OF_THE_ADEPT )	 
		AddBuyItem( 4590 , __OBJ_RING_OF_THE_HEALER )	 
		AddBuyItem( 9000 , __OBJ_RING_OF_THE_PRIEST ) 
		AddBuyItem( 10497, __OBJ_TEMPLAR_RING ) 
	SendBuyItemList
	
NO(BROWSE)
	Conversation
	INTL( 8474, "That's it! I've lost enough time with you.") BREAK

YesNoELSE(BROWSE) 
	Conversation
	INTL( 8475, "Will you take a look at what I have for sale?")
	SetYesNo(BROWSE)

Command(INTL( 1306, "SELL"))
INTL( 8478, "So, it is your turn to sell some wares, eh?")
CreateItemList
   AddSellItem( JEWEL , 0, 100000 )
SendSellItemList( INTL( 8144, "You have nothing I want.") )

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 9146, "I've had enough of you. Leave my house at once!")
BREAK

Command4(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"))
INTL( 1075, "Farewell.")
BREAK

Default
""
IF (rnd.roll(dice(1,2) ) == 1)
   Conversation
   INTL( 9147, "Well, that's an interesting fact.")
ELSE
   Conversation
   INTL( 9148, "I'm afraid I cannot help you.")
ENDIF

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////
void OmarHald::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////

NPC_DATA_EXCHANGE

	NPC_SHOP_DATA      	

	
	NPC_SELL( 3870 , __OBJ_RING_OF_THE_ADEPT )	 
	NPC_SELL( 4590 , __OBJ_RING_OF_THE_HEALER )	 
	NPC_SELL( 9000 , __OBJ_RING_OF_THE_PRIEST ) 
	NPC_SELL( 10497, __OBJ_TEMPLAR_RING ) 

		NPC_BUY( JEWEL, 0, 100000 )
		NPC_SOLD_ITEM( INTL( 8483, "Here you are, now is there anything else?") )
		NPC_FAILED_SELL( INTL( 8484, "Come back when you have enough gold, I'll be waiting.") )
      NPC_BOUGHT_ITEM( INTL( 9149, "Hmm, I don't know what I'll do with this, but perhaps I can sell it for a profit.") )
	CLOSE_NPC_SHOP_DATA

CLOSE_NPC_DATA_EXCHANGE


