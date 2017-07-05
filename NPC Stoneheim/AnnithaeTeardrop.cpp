#pragma hdrstop
#include "AnnithaeTeardrop.h"

AnnithaeTeardrop::AnnithaeTeardrop()
{}

AnnithaeTeardrop::~AnnithaeTeardrop()
{}

extern NPCstructure::NPC AnnithaeTeardropNPC;

void AnnithaeTeardrop::Create( void )
{
        npc = AnnithaeTeardropNPC;
        SET_NPC_NAME( "[10825]Annithae Teardrop" );
        npc.InitialPos.X = 300;
        npc.InitialPos.Y = 830;
        npc.InitialPos.world = 0;
}
 
void AnnithaeTeardrop::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT PEARL = 1; 

InitTalk

Begin
""
IF (TFCTime::IsSleepTime())
	Conversation
	INTL( 9786, "A peculiar time to come knocking at my door... What are you doing "
	"still up at this time of the night if I may ask?")
ELSE
	Conversation
	INTL( 9787, "Hello there. What can I do for you?")
ENDIF

Command2(INTL( 8323, "ANNITHAE"),INTL( 8326, "TEARDROP"))
INTL( 2535, "Yes?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
FORMAT(INTL( 9788, "I am Annithae Teardrop. And you are...? %s? I am pleased to make "
"your acquaintance. I hope that your stay in our fair little town will be "
"enjoyable."), USER_NAME) 

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 9789, "I tend to the chores I have to do around the house. In my spare time, I sometimes craft necklaces "
"with the nice pearls I find. You see the one I'm wearing right now? I've made it myself.")

Command(INTL( 11328, "TEAR-SHAPED PEARL")) 
INTL( 9791, "A tear-shaped pearl? Yes, I have a few of those. Why d'you ask, you need one? Well, I could depart myself of "
"one tear-shaped pearl but it will cost you... let me see... 12,000 gold. I think it is fair enough "
"since these are quite rare. Do we have a deal?")
SetYesNo(PEARL) 

CmdAND3(INTL( 7703, "TEAR"),INTL( 7704, "SHAPED"),INTL( 7705, "PEARL"))
INTL( 9791, "A tear-shaped pearl? Yes, I have a few of those. Why d'you ask, you need one? Well, I could depart myself of "
"one tear-shaped pearl but it will cost you... let me see... 12,000 gold. I think it is fair enough "
"since these are quite rare. Do we have a deal?")
SetYesNo(PEARL) 
					  
YES(PEARL)
	IF (Gold > 12000)
		Conversation
		INTL( 9792, "Thank you, here is your tear-shaped pearl.")
		PRIVATE_SYSTEM_MESSAGE(INTL( 9793, "You give 12000 gold to Annithae.")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 9794, "Annithae gives you a tear-shaped pearl.")) 
		TakeGold(12000) 
		GiveItem(__OBJ_TEAR_SHAPED_PEARL) 
	ELSE
		Conversation
		INTL( 9795, "I'm afraid you do not have enough gold.")
	ENDIF

NO(PEARL)
	Conversation
	INTL( 9796, "That is too bad. Come back if you ever change your mind.")

YesNoELSE(PEARL)
	Conversation
	INTL( 9797, "Well, do you want to buy one of my tear-shaped pearls?")
	SetYesNo(PEARL)

CmdAND(INTL( 7705, "PEARL"),INTL( 7712, "WISDOM"))
INTL( 9798, "Alas, I don't have any of those. However, I have a friend in Lighthaven, Moonrock I think her name is, that "
"might help you.")

Command(INTL( 7705, "PEARL"))
INTL( 9790, "I don't really need your help finding them as I can find them by myself but thank you "
"for offering your help. See? I already have alot of these nice tear-shaped pearls.")

Command5(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 1919, "WHORE"),INTL( 698, " ASS "))
INTL( 9799, "I misjudged you for I thought that you were a decent person. Obviously, I was wrong.")
BREAK

Command2(INTL( 554, "HELP"),INTL( 4275, "HINT"))
INTL( 9800, "I'm afraid I'm not very good at this. If you need assistance with your quests, why don't "
"you ask Chryseida the fortune teller? Her advice is expensive and it doesn't always come "
"the first time, but it's always accurate and reliable when it *does* come.")

Command4(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"))
INTL( 9801, "I sincerely hope to see you soon.")
BREAK

Default
""
IF (rnd.roll(dice(1,2) ) == 1)
   Conversation
   INTL( 9802, "I am afraid I cannot help you with that.")
ELSE
   Conversation
   INTL( 5396, "I honestly don't know.")
ENDIF

EndTalk
}
