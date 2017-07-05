/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "ThorbinWildheart.H"

ThorbinWildheart::ThorbinWildheart()
{}

ThorbinWildheart::~ThorbinWildheart()
{}

extern NPCstructure::NPC ThorbinWildheartNPC;

void ThorbinWildheart::Create( void )
{
      npc = ( ThorbinWildheartNPC );
      SET_NPC_NAME( "[2989]Thorbin Wildheart" ); 
      npc.InitialPos.X = 1507; 
      npc.InitialPos.Y = 2544;
      npc.InitialPos.world = 0;
}

void ThorbinWildheart::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{
CONSTANT BEER = 1;
CONSTANT DRUM = 2;
CONSTANT KARMA = 3;

InitTalk

Begin
INTL( 5858, "Welcome to the humble tavern of the \"Troll's\" \"Armpit\".") 

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5859, "I am Thorbin Wildheart, \"bartender\" and owner of this fair \"tavern\".") 

Command2(INTL( 5860, "THORBIN"),INTL( 5861, "WILDHEART"))
INTL( 5862, "Yes, Thorbin Wildheart is the name.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 5863, "BARTENDER"))
INTL( 5864, "I am the bartender of this modest tavern. If it weren't for this "   
"lowlife \"Baldric\" \"Silverknife\" disturbing my customers "
"with his horrible songs, perhaps this tavern would be more popular.")

Command2(INTL( 4183, "BALDRIC"),INTL( 4070, "SILVERKNIFE"))
""
IF (CheckItem(__OBJ_BALDRIC_DRUM) >= 1)
	Conversation
	INTL( 5865, "You've been able to get Baldric's drum? No need to tell me how "
	"you did that stunt. Do ya want to give it to me so I can "
	"bury it six feet under?")
	SetYesNo(DRUM) 
ELSE
	Conversation	
	INTL( 5866, "Aye! And you know the worst? It's when he starts using that "
	"terrible drum of his. When that chaotic sound starts, all my "
	"customers flee the tavern. *grumble* If you can bring me his "
	"drum, I'll reward you.")
ENDIF

YES(DRUM)
IF (CheckItem(__OBJ_BALDRIC_DRUM) >= 1)
	TakeItem(__OBJ_BALDRIC_DRUM)
	IF (rnd.roll(dice(1,3)) == 1)
		Conversation
	   INTL( 5867, "Good, good. Hey, I tell you what. I got this cape of fire resistance left "
	   "by some drunken traveller. Here, take it. It's yours.")
		GiveItem(__OBJ_CAPE_OF_FIRE_RESISTANCE)
	ELSE
		Conversation
		INTL( 5868, "Thanks to you, friend. Hey, how 'bout a beer? Sounds good, eh? Here ya go!")
	   GiveItem(__OBJ_EMPTY_BEER_MUG)
	ENDIF
	;int nExpReward = 3000; 	
	GiveXP(nExpReward)
	Conversation
	FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), nExpReward)
ELSE
	Conversation
	INTL( 5869, "What the?! The drum disappeared! Where the hell did you hide it? "
	"And how were you able to do it so quickly?!")
ENDIF

NO(DRUM)
Conversation
INTL( 5870, "Oh well! But I warn you, friend... if I hear you using that thing "
"anywhere near my customers, I'll kick ya with the tip of my leather "
"boots. Aye!")

YesNoELSE(DRUM)
Conversation
INTL( 5871, "Uh?! You've been drinking lately again? Let me ask you again... "
"Do you want to give me the damn drum, yes or no?")
SetYesNo(DRUM)

Command2(INTL( 4002, "ELYSANA"),INTL( 4003, "BLACKROSE"))
INTL( 4226, "I have nothing to say about that poison-brewing witch.")

CmdAND(INTL( 535, "TROLL"),INTL( 5872, "ARMPIT"))
INTL( 5873, "Did you ever smell the odor coming from a troll's armpit? Yuck! You have to admit that it doesn't smell that bad around here though.")

Command(INTL( 4233, "TAVERN"))
INTL( 5874, "This tavern is usually frequented by \"sailors\" and \"adventurers\" in search for a good mug of ale.")

Command(INTL( 5875, "SAILOR"))
INTL( 5876, "Sailors are good lads but they are somewhat noisy when they're drunk.")

Command4(INTL( 1346, "DRINK"),INTL( 1304, "BUY"),INTL( 2355, "BEER"),INTL( 5877, " ALE "))
INTL( 5878, "Do you wish to buy a good mug of home brewed ale for only 10 gold pieces?") 
SetYesNo (BEER)

YES(BEER)
IF (Gold >= 10)
   TakeGold(10)
   GiveItem(__OBJ_EMPTY_BEER_MUG)
   Conversation
   INTL( 5879, "Here you go, you won't regret it! ")
ELSE
   Conversation
   INTL( 5880, "Beggars aren't tolerated around here. Don't bother any of my customers or I'll have to "
	"throw you out!")
ENDIF

NO(BEER)
Conversation
INTL( 5881, "I can assure you that you're missing something! ")

YesNoELSE(BEER)
Conversation
INTL( 5882, "Are you already drunk or what? You want a beer or not?")
SetYesNo(BEER)

Command(INTL( 4699, "GERAM"))
INTL( 5883, "\"Buy\" him a few beers and you'll have a friend for life.")

Command(INTL( 956, "ADVENTURER"))
INTL( 5884, "Adventurers often come to my tavern. I don't know why they come by so often but I always welcome them with a good mug of "
"ale. Once they're dead drunk, I usually can make them gamble fair amounts of money. Hehehe!")

Command(INTL( 3854, "RAVENWOOD"))
INTL( 5885, "Ravenwood is also known as the forest of the damned. Why you ask me? I don't really know but you should stay within the "
"limits of the city of Silversky. If you go out of the city, you will leave the protection of King Theodore's royal guards.")  

Command2(INTL( 3865, "VULTURE'S DEN"),INTL( 1492, "DESERT"))
INTL( 5886, "The Vulture's Den desert is located on the western part of the island of \"Raven's\" \"Dust\". The desert is a harsh environment and "
"very few living creatures are able to survive there. Deadly scorpions, sand worms and sand crawlers are some of the inhabitants "
"that you may encounter.")

Command(INTL( 1886, "KARMA"))
INTL( 7209, "For 250 gold pieces, I'll tell you about your karma. That comes with a beer, a good meal and lodging for the night, so it's "
"not a total waste. Will you pay?")
SetYesNo(KARMA)

YES(KARMA)
Conversation
INTL( 7210, "Excellent... ")
IF (Gold >= 250)
	TakeGold(250)
	IF (USER_KARMA>=400)
		Conversation
		INTL( 7211, "As I understand it, you're a Pure. That's as good as you're likely to get, I'd say. Congrats!")
	ELSEIF (USER_KARMA>=300)
		Conversation
		INTL( 7212, "You're a Blessed, which isn't at the top, but pretty darn close. Good work! Next stop: becoming a Pure.")
	ELSEIF (USER_KARMA>=200)
		Conversation
		INTL( 7213, "I hear you're Redeemed, which means you've accomplished a great deal of good deeds, but "
		"there's still room for improvement. Keep this up and you'll become a Blessed.")
	ELSEIF (USER_KARMA>=100)
		Conversation
		INTL( 7214, "You're a Good person, which is more than I can say about half the population of this island. Don't give up, "
		"you're on the right path to become a Redeemed.")
	ELSEIF (USER_KARMA>-100)
		Conversation
		INTL( 7215, "You're essentially unaligned, right between Good and Evil. You'll have to work harder one way or the other "
		"to answer your true calling.")
	ELSEIF( USER_KARMA <= -400 )
		Conversation
		INTL( 7216, "Anyone can see you're a Bane. That's as evil as you're likely to get. I'm not sure congratulations are in "
		"order, so if you'll excuse me, I've got other customers to attend.")
	ELSEIF (USER_KARMA<=-300)
		Conversation
		INTL( 7217, "Well, what do you know, you're a Cursed! We don't like your kind much around here, but at least you haven't "
		"fallen to the level of Impure yet. There's still hope for you.")
	ELSEIF (USER_KARMA<=-200)
		Conversation
		INTL( 7218, "You're Malignant, and that's no way to go, if you ask me. Keep this up and you'll become a Cursed. You should "
		"consider the path of good, my friend. Evil begets evil, and nothing good can come of that.")
	ELSEIF (USER_KARMA<=-100)
		Conversation
		INTL( 7219, "You're Evil, plain and simple, but you haven't become Malignant yet. There's still time for you to turn to good. "
		"At least I think so.")
	ELSE
		Conversation
		INTL( 7220, "I'm... not sure *what* you are, sorry...")
	ENDIF
ELSE
	Conversation
	INTL( 7221, "I'm afraid you don't have enough gold, you know. Please come back when you do.")
ENDIF

NO(KARMA)
Conversation
INTL( 7222, "Oh dear, if everyone refuses to buy anything, how am I going to make ends meet? I've got a wife and three children "
"to feed, you know.")

YesNoELSE(KARMA)
Conversation
INTL( 7223, "Just answer \"yes\" or \"no\", okay?")
SetYesNo(KARMA)

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 5887, "Get out of my tavern at once or I'll kick your... you know what!") 
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 4673, "Until we meet again my friend.")
BREAK

Default
INTL( 5888, "I don't know about that. Who do you think I am? Elvenstein or what?!")

EndTalk
}
