/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "JonHamhoo.H"

JonHamhoo::JonHamhoo()
{}

JonHamhoo::~JonHamhoo()
{}

extern NPCstructure::NPC JonHamhooNPC;
 
void JonHamhoo::Create( void )
{
      npc = ( JonHamhooNPC );
      SET_NPC_NAME( "[2959]Jon Hamhoo" );
      npc.InitialPos.X = 1426;//1416;//1480;
      npc.InitialPos.Y = 2353;//2342;//2375;
      npc.InitialPos.world = 0;
}

void JonHamhoo::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{

InitTalk

Begin
INTL( 5284, "Hey, can't you see that I'm busy? Say what you have to say and be on your "
"way... I don't have all day you know!")

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 5285, "Hello!") 

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5286, "I am Jon Hamhoo, your humble servant.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 5287, "I am the royal cook. I am the one who has to cook all the meals for "
"the entire castle. Not to mention about King \"Theodore\"'s "
"insatiable appetite. My occupation is not an easy one as you see. "
"Especially during the day, I never have a moment to myself.")

Command(INTL( 1794, "ROYAL KEY"))
INTL( 5288, "Yeah, we made this cake for His Majesty's forty-fifth birthday. It was a *huge* "
"cake, and through a really \"odd story\", it turned out to be put into the cake "
"and was found by someone...")
IF (CheckFlag(__QUEST_ROYAL_KEY5) == 0)
	GiveFlag(__QUEST_ROYAL_KEY5,1)
ENDIF

Command(INTL( 5289, "ODD STORY"))
INTL( 5290, "Well, it went like this... The king's youngest son, Theokrat, found the key in his "
"father's apartments... Sort of took it without permission. Anyway, as he was wandering "
"in the castle's corridors, he chanced upon a group of thieves who had snuck inside "
"the castle to steal expensive tapestries... But you don't care to hear \"the rest\", "
"do you?")
IF (CheckFlag(__QUEST_ROYAL_KEY5) == 1)
	GiveFlag(__QUEST_ROYAL_KEY5,2)
ENDIF

Command4(INTL( 5291, "THE REST"),INTL( 5292, "MORE"),INTL( 5293, "GO ON"),INTL( 4123, " YES "))
""
SWITCH(CheckFlag(__QUEST_ROYAL_KEY5))
	CASE(2)
		Conversation
		INTL( 5294, "Ah, well, as you wish... In any case, the thieves saw the young prince and started "
		"running after him. Fortunately, His Highness knew the castle well and managed to evade "
		"them, but not before losing the key somewhere along the way in the castle's dungeons. "
		"It was found some time after by a wandering atrocity that had dug its way into "
		"the dungeons. Want to hear \"more\"?")
		GiveFlag(__QUEST_ROYAL_KEY5,3)
	ENDCASE
	CASE(3)
		Conversation
		INTL( 5295, "Excellent! You're my kind of person, always ready to listen to a good tale. "
		"As I was saying, an atrocity found the key. It wandered back to the outside "
		"world through the tunnel it had dug and travelled some distance north of here, "
		"in the mountains. There, it was slain by none other than Morindin Arrowmist, "
		"who left its carcass there to rot. Still want to hear \"more\"?")
		GiveFlag(__QUEST_ROYAL_KEY5,4)
	ENDCASE
	CASE(4)
		Conversation
		INTL( 5296, "So! The key stayed in the mountains for weeks, until it was found by a passing "
		"adventurer named Magnus Kai. He was a honest man and looked all over the kingdom "
		"to find the key's owner. It took him weeks, but he finally arrived at our doors "
		"and learned that the king had lost that very key and was rather distressed "
		"about its disappearance. Anyway... want to hear \"the rest\"?")
		GiveFlag(__QUEST_ROYAL_KEY5,5)
	ENDCASE
	CASE(5)
		Conversation
		INTL( 5297, "Well, Kai returned the key, even though it appears a copy had been made to "
		"replace the original, and was invited to the king's birthday feast. That's not "
		"how the story of that key ends, however. I'll spare you the details, but in a "
		"nutshell, the key was mistakenly dropped in the cake mixture by Chamberlain "
		"Thomar was visiting my kitchen. Hear \"the rest\"?")
		GiveFlag(__QUEST_ROYAL_KEY5,6)
	ENDCASE
	CASE(6)
		Conversation
		INTL( 5298, "Anyway! It turned out to be a *huge* cake, like I said earlier, and the guests "
		"numbered in the thousands, all of whom got a piece of the cake. It appears "
		"the key was found by one of those guests, who kept it. A tragic story, really. "
		"I guess that's one key we won't see any time soon. Want me to \"go on\"?")
		GiveFlag(__QUEST_ROYAL_KEY5,7)
	ENDCASE
	CASE(7)
		Conversation
		INTL( 5299, "Well, I never really knew for sure, seeing as I'm kind of stuck in this kitchen "
		"and all, but I hear two uninvited guests named Jalir and Kamar, or something "
		"like that, may have found the key. I have *no* idea where they live now, though, "
		"so good luck in finding them.")
		GiveFlag(__QUEST_ROYAL_KEY5,8)
	ENDCASE
	OTHERWISE
		Conversation
		INTL( 5300, "I can't talk right now, please come back later!")
		BREAK
	ENDCASE
ENDSWITCH

Command3(INTL( 754, "THEODORE"),INTL( 3990, "MAJESTY"),INTL( 1072, "KING"))
INTL( 5301, "I wonder where King Theodore stores all the food he eats. He always sleeps, "
"but somehow always seems to find time to eat my meals.")  

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 3768, "Raven's Dust is the name of this island.")

Command(INTL( 3854, "RAVENWOOD"))
INTL( 5302, "It doesn't look quite like your usually peaceful forest.")

Command2(INTL( 3865, "VULTURE'S DEN"),INTL( 1492, "DESERT"))
INTL( 5303, "I never went in the desert nor do I want to.")

Command2(INTL( 3862, "BANE"),INTL( 3863, "BLACKBLOOD"))
INTL( 5304, "It is rumored that Blackblood has a daughter.")

Command(INTL( 3848, "ZHAKAR"))
INTL( 5305, "Zhakar? He is the old mage who lives secluded in his tower.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 5306, "That's not a smart thing to say to a man holding a butcher's knife.")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 5307, "Fine! I have still have work to do.") 
BREAK

Default
""
IF (rnd.roll( dice( 1, 2 ) ) == 1)
    Conversation
    INTL( 4012, "Perhaps others would like to know about that.")
ELSE
    Conversation
    INTL( 4438, "Now that's something I did not know.")
ENDIF

EndTalk

}

