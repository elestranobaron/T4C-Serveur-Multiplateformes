//////////////////////////////////////////////////////////////////////
// Terwin.cpp: implementation of the Terwin class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Terwin.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Terwin::Terwin()
{}

Terwin::~Terwin()
{}

extern NPCstructure::NPC Guard_set_two;

void Terwin::Create( ){
    npc = Guard_set_two;
	SET_NPC_NAME( "[2986]Terwin" );
    npc.InitialPos.X = 1393;//2845;//1379;
    npc.InitialPos.Y = 2417;//460;//2354;
	npc.InitialPos.world = 0;//4;//0;
}

void Terwin::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT THEPOTION = 1;
CONSTANT BRIBE = 2;

InitTalk

Begin
INTL( 5802, "You had better behave in front of the king!")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5803, "You will address me as Sir Terwin.")

Command(INTL( 5804, "TERWIN"))
INTL( 5805, "What do you want?")

Command2(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"))
INTL( 5806, "I am a member of the \"king\"'s personal \"guards\".")

Command(INTL( 2505, "GUARD"))
INTL( 5807, "Don't think that I am as soft-hearted as those two weaklings at the front gate.")

Command(INTL( 5808, "POTION OF HERO"))
""
IF ((CheckFlag(__QUEST_ROYAL_KEY2) == 2) && (CheckItem(__OBJ_POTION_OF_HEROISM) >= 1))
	Conversation
	INTL( 5809, "Well! I see you have one such potion on yourself! Would you care to part with it?")
	SetYesNo(THEPOTION)
ELSE
	Conversation
	INTL( 5810, "Love those potions. One potion a day keeps your enemies away.")
ENDIF

YES(THEPOTION)
IF (CheckItem(__OBJ_POTION_OF_HEROISM) >= 1)
	TakeItem(__OBJ_POTION_OF_HEROISM)
	Conversation
	INTL( 5811, "Many thanks! I'm in your debt!")
	GiveFlag(__QUEST_ROYAL_KEY2,3)
ELSE
	Conversation
	INTL( 5812, "You don't have one! What gives??")
ENDIF

NO(THEPOTION)
Conversation
INTL( 5813, "I'm crushed. *sigh*")

YesNoELSE(THEPOTION)
Conversation
INTL( 1361, "Eh?")
YesNoELSE(THEPOTION)

Command(INTL( 1794, "ROYAL KEY"))
""
IF (CheckFlag(__QUEST_DEAD_BROTHERS) >= 12) // Has begun Royal Keys Quests...
	IF (CheckFlag(__QUEST_ROYAL_KEY2) <= 3) // But hasn't met Terwin's conditions to start RKQ #2...
		Conversation
		INTL( 5814, "Oh, you mean *those* keys?!? *Arumph* I do not believe a \"honest\" guard "
		"such as me would discuss these matters with a peon like you.")
		IF (CheckFlag(__QUEST_ROYAL_KEY2) == 0)
			GiveFlag(__QUEST_ROYAL_KEY2,1)
		ENDIF
	ELSE // PC has earned Terwin's trust through various bribes...
		Conversation
		INTL( 5815, "Well, since we're such good friends, I guess there's no harm in telling you "
		"who's got such a key, right? Go ask Chamberlain Thomar, he owns one. But "
		"you haven't heard this from me, okay?")
		IF (CheckFlag(__QUEST_ROYAL_KEY2) == 4) // If the PC hasn't heard this before...
			GiveFlag(__QUEST_ROYAL_KEY2,5)
		ENDIF
	ENDIF
ELSE // If the PC hasn't begun the Royal Key Quest...
	Conversation
	INTL( 5816, "The king has many keys, I'm sure. They are no concern of yours.")
ENDIF

Command2(INTL( 4952, "IDAS"),INTL( 4947, "EDDEN"))
INTL( 5817, "Bah! Weaklings I say!")

Command(INTL( 5818, "HONEST"))
""
SWITCH(CheckFlag(__QUEST_ROYAL_KEY2))
	CASE(0) // Royal Key Quest #2 hasn't begun yet.
		Conversation
		INTL( 5819, "That's right, I'm a *very* strict and honest guard! Can't bribe me, no sir-ree!")
	ENDCASE
	CASE(1) // User has asked Terwin about *Royal Key*...
		IF (USER_KARMA <= 50) // ...but isn't deemed worthy to pursue this quest.
			Conversation
			INTL( 5820, "*Hrmph* I find you of questionable character. I prefer to not discuss these "
			"matters with one of your ilk. Return when you have done more good deeds than "
			"bad ones.")
		ELSE // PC is a worthy person, but Terwin would like a Potion of Heroism first
			Conversation
			INTL( 5821, "My character is beyond reproach and I will not speak to one who isn't my "
			"friend... But perhaps we could become closer if you were to bring me a "
			"\"potion\" \"of\" \"heroism\". I hear they taste quite good.")
			GiveFlag(__QUEST_ROYAL_KEY2,2)
		ENDIF
	ENDCASE
	CASE(2) // PC hasn't given Terwin the potion he wants yet.
		Conversation
		INTL( 5822, "I'm sure we can talk some more after I've had a drink of \"potion of heroism\".")
	ENDCASE
	CASE(3) // Terwin has finally had his potion! But he's feeling a bit poor... :)
		Conversation
		INTL( 5823, "Still... even honest men need to make a living, if you get my drift... *cough* Got "
		"a few thousand coins to spare? Like... *cough* five thousand?")
		SetYesNo(BRIBE)
	ENDCASE
	OTHERWISE // Terwin's finished his part of the deal.
		Conversation
		INTL( 5819, "That's right, I'm a *very* strict and honest guard! Can't bribe me, no sir-ree!")
	ENDCASE
ENDSWITCH

YES(BRIBE)
IF (Gold >= 5000)
	TakeGold(5000)
	GiveFlag(__QUEST_ROYAL_KEY2,4)
	Conversation
	INTL( 5824, "Well, then, I guess I could answer a few questions about the \"royal keys\"...")
ELSE
	Conversation
	INTL( 5825, "Hah! You don't have enough gold! Forget about it!")
ENDIF

NO(BRIBE)
Conversation
INTL( 5826, "Suit yourself.")

YesNoELSE(BRIBE)
Conversation
INTL( 5827, "I... see. Well, not really, but...")

Command2(INTL( 1072, "KING"),INTL( 754, "THEODORE"))
INTL( 5828, "If I ever find that you have come to bear his majesty ill-will, you will regret ever setting "
"foot in this castle.")

Command(INTL( 3918, "VISITOR"))
INTL( 4019, "I don't have time for this.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 5829, "If you say so.") BREAK

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1864, "...") BREAK

Default
INTL( 5830, "That is none of my business.")

EndTalk

}
