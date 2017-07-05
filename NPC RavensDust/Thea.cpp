//////////////////////////////////////////////////////////////////////
// Thea.cpp: implementation of the Thea class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Thea.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Thea::Thea()
{}

Thea::~Thea()
{}

extern NPCstructure::NPC TheaNPC;

void Thea::Create( ){
    npc = TheaNPC;
	SET_NPC_NAME( "[2987]Thea" );
    npc.InitialPos.X = 1503; 
    npc.InitialPos.Y = 2526; 
	npc.InitialPos.world = 0;
}

void Thea::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 5831, "How do you do my friend? Sit down and I'll be right with you.")
	
Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5832, "My name is Thea.")

Command(INTL( 5833, "THEA"))
INTL( 5834, "Pleased to meet you.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 5835, "Well, if you'll just \"sit\" down somewhere, I'll show you what my work is.")

Command(INTL( 5836, "SIT"))
INTL( 5837, "Well if you want me to bring you a \"drink\" or something, you have to sit down!")

Command3(INTL( 5838, "GOSSIP"),INTL( 1350, "RUMOR"),INTL( 5839, "RUMOUR"))
INTL( 5840, "Yes, I guess it's true what they say... I really don't mean to pry into people's "
"affairs, but it's kind of hard to *not* hear what they say when I wait their "
"tables... Anyway, I tend to know a lot about what happens in these parts.")

Command(INTL( 1794, "ROYAL KEY"))
""
IF (TFCTime::IsDay()) // Thea doesn't talk about anything but work during the day.
	Conversation
	INTL( 5841, "Royal keys, royal keys... I might know something, but I'm not too sure. Perhaps "
	"you could return at a time when I've got more time to chat?")
ELSE
	Conversation
	INTL( 5842, "Yeah, I guess I can tell you a bit about it, now that most of the customers are gone. "
	"There was a priestess here, a few years ago, who was on a quest to *give* a special "
	"key to someone. I hear she managed to do it and left the island after that. That's "
	"not much, I know, but I never said I knew all the details. Hope this helps.")
	IF (CheckFlag(__QUEST_ROYAL_KEY4) == 0)
		GiveFlag(__QUEST_ROYAL_KEY4, 1)
	ENDIF
ENDIF

Command(INTL( 4271, "CUTHANA"))
INTL( 5843, "We don't sell any of that stuff here, sorry.")

Command(INTL( 5844, "PRIESTESS"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY4) >= 1) // If PC has already asked about the Royal Keys...
	Conversation
	INTL( 5845, "Um... I *think* she went back to Arakas, but I see so many people come and go, "
	"I wouldn't know for sure. I guess you'll have to go find out yourself.")
	IF (CheckFlag(__QUEST_ROYAL_KEY4) == 1) // To indicate that PC knows where to find Moonrock
		GiveFlag(__QUEST_ROYAL_KEY4, 2)
	ENDIF
ELSE // PC is asking about the priestess out of the blues.
	Conversation
	INTL( 5846, "Priestess? What priestess? I'm not sure I understand.")
ENDIF

Command(INTL( 755, "ISLAND"))
INTL( 5847, "This is the island of Raven's Dust. The Kingdom of Goldmoon also comprises the island "
"of Arakas. There is another islands northwest from here, but I don't really know "
"where it is. I believe it's called Stoneheim.")

/*
Command(INTL( 5848, "WEATHERGATE"))
INTL( 5849, "I don't know much about it, except that it's one of the *biggest* cities in the world. "
"Oh, and I hear the weather around it is really bad, so that's why there are never any "
"boats to and from there.")
*/

Command(INTL( 515, "ARAKAS"))
INTL( 5850, "That's the other island in the Kingdom of Goldmoon. Many adventurers seem to come from "
"there. They often move on to Stoneheim or return to Arakas.")

Command(INTL( 956, "ADVENTURER"))
INTL( 5851, "Seems like there's trouble brewing in the world, these days. My father always used to "
"talk about how heroes would rise to save the world when the end would come... Maybe "
"we're getting so many heroes because the world's about to come to an end.")

Command2(INTL( 741, "4TH COMING"),INTL( 1882, "FOURTH COMING"))
INTL( 5852, "Oh, now I remember!! That's what my daddy used to call the end of the world!")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 5853, "You're standing on it! Pretty neat, eh?")

Command(INTL( 1346, "DRINK"))
INTL( 5854, "Like I said, just find a seat and I'll be right with you. Right now, I have to get "
"back to work.") BREAK

/*

FOOD & BEAR

It might be nice if people could buy drink & food from Thea, such as chickens, beer,
etc. The chicken might heal 5 HPs, while the beer could reduce your INT by 3 and
increase your LUCK by 5, or something like that, for a "game time" hour.

*/

Command(INTL( 3918, "VISITOR"))
INTL( 5855, "We get many folks in here, some strangers, and others a just locals. We get too many "
"strangers in a day for me to single one out for you.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 5856, "Have a nice day now!") BREAK

Default
INTL( 5857, "Actually, I'm really busy now so please ask someone else.") BREAK

EndTalk

}
