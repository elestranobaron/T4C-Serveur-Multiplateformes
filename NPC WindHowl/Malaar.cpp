//////////////////////////////////////////////////////////////////////
// Malaar.cpp: implementation of the Malaar class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Malaar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Malaar::Malaar()
{}

Malaar::~Malaar()
{}

extern NPCstructure::NPC MalaarNPC;

//Nom: Malaar.
//Statistique: Windhowl Priest.
//Position: (2208, 557)
//World: 0
//Description: Arch Bishop.
//Body: Priest.


//////////////////////////////////////////////////////////////////////////////////////////
void Malaar::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Malaar
//
{
	npc = MalaarNPC;
	SET_NPC_NAME( "[3015]Malaar" );
	npc.InitialPos.X = 1690;
	npc.InitialPos.Y = 1165;
	npc.InitialPos.world = 0;  
}

//////////////////////////////////////////////////////////////////////////////////////////
void Malaar::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Malaar
//
{

CONSTANT DONATION = 1
CONSTANT DONATION2 = 2
CONSTANT DONATION3=3

InitTalk

Begin
INTL( 2541, "Are thou here to seek guidance, my friend?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2542, "I am Malaar, a bishop of Artherk's \"church\".")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2543, "I am a bishop of \"Artherk\". It is my life's work to follow the path of "
"light.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2544, "Ach! So that fiend Balork has cursed you too? I know a traveller to whom it "
"happened, a long time ago... When I saw him again, he said something about "
"a certain \"Annabelle\" curing him.")

Command(INTL( 523, "ANNABELLE"))
INTL( 2545, "Young, lovely Annabelle, how we miss her! She could heal the sick and comfort "
"the downtrodden. She would hear your plight and help you, no doubt. If she "
"were still alive, that is.")

Command(INTL( 2546, "DONATION"))
""
IF (Gold>10000)
 Conversation
	INTL( 2547, "We would gladly accept a donation from you, if you would be so kind as "
	"to make one. Would you perhaps have 10,000 gold pieces to offer to "
	"Artherk?")
	SetYesNo(DONATION)
ELSE
 Conversation
 INTL( 2548, "We do accept donations, but not from people who are not rich. Once you "
 "have made your fortune, please return and we will be glad to take your "
 "money in exchange for Artherk's blessings.")
ENDIF

YES(DONATION)
IF (Gold>=10000)
	Conversation
	INTL( 2549, "That is most generous of you!! Thank you so much! No doubt, Artherk "
	"will bless you for this.")
	IF (USER_KARMA<(100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
		GiveKarma(20*(500-USER_KARMA)/500)
	ENDIF
	TakeGold(10000)
ELSE	
	Conversation
	INTL( 11727, "Ah, but it seems that you don't have enough gold.") 
ENDIF


NO(DONATION)
	Conversation
	INTL( 2550, "Ah, that is too bad indeed... Perhaps you would not mind giving "
	"a smaller donation, around a thousand gold pieces?")
	SetYesNo(DONATION2)
YesNoELSE(DONATION)
	Conversation
	INTL( 2551, "Please, a yes or no would suffice...")
	SetYesNo(DONATION)

YES(DONATION2)

IF (Gold>=1000)
	Conversation
	INTL( 2552, "Wonderful! You are indeed a blessed individual! Artherk be with you.")
	IF (USER_KARMA<(75*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
		GiveKarma(10*(500-USER_KARMA)/500)
	ENDIF
	TakeGold(1000)
ELSE	
	Conversation
	INTL( 11727, "Ah, but it seems that you don't have enough gold.") 
ENDIF


NO(DONATION2)
	Conversation
	INTL( 2553, "I... see. Then perhaps you would be content with a simple donation of "
	"250 gold pieces?")
	SetYesNo(DONATION3)
YesNoELSE(DONATION2)
	Conversation
	INTL( 2554, "What was that again? Did you say \"yes\" or \"no\"?")
	SetYesNo(DONATION2)

YES(DONATION3)
IF (Gold>=250)
	Conversation
	INTL( 2555, "Very well. I thank you in the name of Artherk.")
	IF (USER_KARMA<(50*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
		GiveKarma(5*(500-USER_KARMA)/500)
	ENDIF
	TakeGold(250)
ELSE	
	Conversation
	INTL( 11727, "Ah, but it seems that you don't have enough gold.") 
ENDIF


NO(DONATION3)
	Conversation
	INTL( 2556, "Ah... Well, then perhaps you have changed your mind and should "
	"return when you feel like being generous. May Artherk light your "
	"path.")
YesNoELSE(DONATION3)
	Conversation
	INTL( 2557, "I do not quite understand. Was that a \"yes\" or a \"no\"?")
	SetYesNo(DONATION3)

Command(INTL( 1243, "ARTHERK"))
INTL( 2558, "Artherk is the god of mending and help. He is the only god worshiped "
"in the kingdom of \"Goldmoon\", I believe. Most of his many followers have "
"the unending task of helping people and praying for those lost in darkness.")

Command(INTL( 753, "GOLDMOON"))
INTL( 2559, "Ahhh, what a great kingdom it is. Our fair King \"Theodore\" rules "
"wisely and the people are kind of heart. None follow any god other than the "
"great \"Artherk\", and rightfully so, since he is the only god worshipped "
"by our church. There is also a long forgotten \"temple\" on Goldmoon, but I "
"do not know if it was dedicated to \"Artherk\".")

Command(INTL( 754, "THEODORE"))
INTL( 2560, "Ahhh! What a wonderful king! He sends us \"donations\" every month and, in "
"return, we tell everyone how great a king he is.")

Command(INTL( 2379, "CHURCH"))
INTL( 2561, "There are many churches of Artherk throughout the land. Most of the other "
"churches follow a dark path, however. Beware of those that hide their work "
"from the eyes of the people.")

Command(INTL( 1365, "TEMPLE"))
INTL( 2562, "That ancient temple? Oh, well, I do not know much about it. It lies in "
"the forest in the center of Arakas. I think it is near the center but "
"I don't have any time to spend on finding such a mysterious place.")

// Command(INTL( 2563, "FOREST"))
// INTL( 2564, "The forest of Mato is great indeed. Further to the north, there is a druid "
// "encampment and, not far from there, lie the dark \"caves\", home to the goblins. "
// "You can reach almost every location on Arakas from Mato.")
// 
//Command(INTL( 881, "CAVE"))
//INTL( 2565, "What can I say, they're just dumb and slow creatures that only know how to "
//"fight. We'll have no problem dealing with them.")

Command(INTL( 515, "ARAKAS"))
INTL( 2566, "You still don't know what Arakas is?")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2567, "Go freely my friend.") BREAK

Default
INTL( 2220, "Only Artherk could help you.")

EndTalk

}
