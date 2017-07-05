//////////////////////////////////////////////////////////////////////
// Halam.cpp: implementation of the Halam class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Halam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Halam::Halam()
{}

Halam::~Halam()
{}

extern NPCstructure::NPC HalamNPC;

//////////////////////////////////////////////////////////////////////////////////////////
void Halam::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Halam
//
{
	npc = HalamNPC;
	SET_NPC_NAME( "[3039]Halam" );
    npc.InitialPos.X = 2848;
    npc.InitialPos.Y = 1067;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Halam::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Halam
//
{

CONSTANT BRIBE = 1;
CONSTANT KARMA = 2;

InitTalk

Begin
""
IF (CheckFlag(__QUEST_GOBLIN_GEENA_GO_SEE_HALAM) == 1)
   Conversation
   INTL( 1340, "You're the one who cured Geena? I can never thank you enough. She's a "
   "good woman to have around. Here... ")
   RemFlag(__QUEST_GOBLIN_GEENA_GO_SEE_HALAM)
   IF (rnd.roll(dice(1, 3) ) == 1)
      Conversation
      INTL( 1341, "one drunken fool left this girdle of courage the other day...  I hope it serves you well.")
      GiveItem(__OBJ_GIRDLE_OF_COURAGE)
   ELSE
      Conversation
      INTL( 1342, "I found this ring of the bear lying around. Perhaps you'll find a "
      "use for it...")
      GiveItem(__OBJ_RING_OF_THE_BEAR)
   ENDIF
ELSE
   Conversation
   INTL( 11752, "I'm really tired of those damned guards tearing up the place. I can't make a living if I "
   "have to keep replacing those tables everyday!")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1344, "My name is Halam Tors! Pleased to meet you!")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 1345, "I'm the \"innkeeper\" of this inn! Would you like a \"drink\"? This is the "
"best ale around! It's also the only one around! *laugh*")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 820, "Balork's curse? That's horrible!")

Command(INTL( 523, "ANNABELLE"))
INTL( 584, "I wonder who she is.")

Command(INTL( 1346, "DRINK"))
INTL( 1347, "Have a seat and I'll send Geena to you as soon as she's free.")

Command(INTL( 1348, "INNKEEPER"))
INTL( 1349, "As an innkeeper, I hear strange \"rumors\" from everyone.  \"Travelers\" "
"often come here to buy a mug of ale or two!")

Command(INTL( 1350, "RUMOR"))
INTL( 1351, "I heard many rumors! Some are about \"goblins\", others about \"atrocities\", "
"but seldom are they about the \"temple\". I even heard people talking about "
"\"dragons\"! But I warn ya, it's only rumors, you know!")

Command(INTL( 7175, "TRAVELER"))
INTL( 1352, "They usually come from all around, but these last few months, I haven't "
"seen many.  Business isn't going too well.")

Command(INTL( 1353, "GLUM SWORD"))
INTL( 1354, "Don't know what you're talking about, friend.")

Command(INTL( 791, "GLOOMBLADE"))
INTL( 1355, "Oh, that! Yes, it's a pretty impressive magical sword, although I'm told only "
"sinister fellows use it. Something like a boosted version of a Nightsword, I think.")

Command(INTL( 1356, "NIGHTSWORD"))
INTL( 1357, "Nightswords are pretty nifty items for people who like to dwell into darkness. I seem "
"to remember a fellow who once made some, but for some reason, I can't seem to remember "
"his name or where he lives... Heh heh... Perhaps you'd care to jog my memory with a "
"thousand gold pieces?")
SetYesNo(BRIBE)

YES(BRIBE)
	IF (Gold >= 1000)
		TakeGold(1000)
		Conversation
		INTL( 1358, "Thanks! You're a pal! The fellow's name was... um... Something like Jagar Kar, "
		"I think... Anyway, he has a very large collection of Nightswords, so perhaps he "
		"could sell you one.")
	ELSE
		Conversation
		INTL( 1359, "Bah, what a fraud! You don't have the money, I don't have the memory.")
		BREAK
	ENDIF

NO(BRIBE)
Conversation
INTL( 1360, "Oh well. Perhaps it's not as important to you as I thought.")

YesNoELSE(BRIBE)
Conversation
INTL( 1361, "Eh?")
SetYesNo(BRIBE)

Command(INTL( 539, "GOBLIN"))
INTL( 1362, "The inhabitants of Arakas have too many problems with the goblins. They need "
"all the help they can get! It is rumored that Righul's Mountains, located "
"north of Arakas, are infested by those ugly goblins! But that's not the "
"worst! It is also said that an evil necromancer--as if a necromancer could "
"be anything else--is leading this army! If he could be defeated, it would help us "
"more than anything! Except maybe another mug of ale.")

Command(INTL( 1363, "ATROCIT"))
INTL( 1364, "They say that there are many atrocities lurking in the cave south of here. You "
"should go have a look! It is not that far. Although, I have also heard that "
"they had moved somewhere to the west... Or was it the north? Oh, I don't "
"really know.")

Command(INTL( 1365, "TEMPLE"))
INTL( 1366, "I heard a mage talking about a dungeon under the temple of Lighthaven! "
"I've been living here for 20 years and I never knew!")

Command(INTL( 1367, "DRAGON"))
INTL( 1368, "Not many have seen a dragon, they have all taken shelter and they do not "
"bother people. Have you seen the huge one we trapped? Now that's what I call a real dragon.") 

Command(INTL( 1369, "MATO"))
INTL( 1370, "Mato? It's the biggest forest on Arakas.  If you wish to travel on Arakas, "
"you won't find a way around this forest!")

Command(INTL( 1886, "KARMA"))
INTL( 7237, "It'll cost ya 50 GP if you want me to tell you your worth. That comes with a beer, so it's "
"not a total waste. Heh heh. Will you pay?")
SetYesNo(KARMA)

YES(KARMA)
Conversation
INTL( 7238, "Very good, very good... ")
IF (Gold >= 50)
	TakeGold(50)
	IF (USER_KARMA>=400)
		Conversation
		INTL( 7211, "As I understand it, you're a Pure. That's as good as you're likely to get, I'd say. Congrats!")
	ELSEIF (USER_KARMA>=300)
		Conversation
		INTL( 7212, "You're a Blessed, which isn't at the top, but pretty darn close. Good work! Next stop: becoming a Pure.")
	ELSEIF (USER_KARMA>=200)
		Conversation
		INTL( 7239, "I hear you're Redeemed, which means you've accomplished a great deal of good deeds, but "
		"there's still room for improvement. Keep this up and you'll become a Blessed.")
	ELSEIF (USER_KARMA>=100)
		Conversation
		INTL( 7240, "You're a Good person, which is more than I can say about half the population of this island. Don't give up, "
		"you're on the right path to become a Redeemed.")
	ELSEIF (USER_KARMA>-100)
		Conversation
		INTL( 7241, "You're essentially unaligned, right between Good and Evil. You'll have to work harder one way or the other "
		"to answer your true calling.")
	ELSEIF( USER_KARMA <= -400 )
		Conversation
		INTL( 7242, "Anyone can see you're a Bane. That's as evil as you're likely to get. I'm not sure congratulations are in "
		"order, so if you'll excuse me, I've got other customers to attend.")
	ELSEIF (USER_KARMA<=-300)
		Conversation
		INTL( 7243, "Well, what do you know, you're a Cursed! We don't like your kind much around here, but at least you haven't "
		"fallen to the level of Impure yet. There's still hope for you.")
	ELSEIF (USER_KARMA<=-200)
		Conversation
		INTL( 7244, "You're Malignant, and that's no way to go, if you ask me. Keep this up and you'll become a Cursed. You should "
		"consider the path of good, my friend. Evil begets evil, and nothing good can come of that.")
	ELSEIF (USER_KARMA<=-100)
		Conversation
		INTL( 7245, "You're Evil, plain and simple, but you haven't become Malignant yet. There's still time for you to turn to good. "
		"At least I think so.")
	ELSE
		Conversation
		INTL( 7220, "I'm... not sure *what* you are, sorry...")
	ENDIF
ELSE
	Conversation
	INTL( 7234, "I'm afraid you don't have enough gold on you. Please come again.")
ENDIF

NO(KARMA)
Conversation
INTL( 7246, "Aw, that's too bad, I've got all this beer to sell and no one to sell it to.")

YesNoELSE(KARMA)
Conversation
INTL( 7236, "I'd be happy with a simple \"yes\" or \"no\", you know?")
SetYesNo(KARMA)

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 1371, "I could throw you out for using such foul language.")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 1372, "Well, good day to you!") BREAK

Default
INTL( 1373, "Just when I thought I had heard it all, you come up with something new!")

EndTalk
}
