#pragma hdrstop
#include "PrincessDelilah.h"

PrincessDelilah::PrincessDelilah()
{}

PrincessDelilah::~PrincessDelilah()
{}

extern NPCstructure::NPC PrincessDelilahNPC;

void PrincessDelilah::Create( void )
{
    npc = PrincessDelilahNPC;
    SET_NPC_NAME( "[2975]Princess Delilah" );
    npc.InitialPos.X = 1387;//2830;//1420; 
    npc.InitialPos.Y = 2361;//671;//2320; 
	npc.InitialPos.world = 0;//4;//0;
}

void PrincessDelilah::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT PAID_IN_GOLD = 1;
CONSTANT REMOVE_CURSE = 2;

InitTalk

/*
__QUEST_CUTHANA FLAG
	Flag can be reset to 1 by Chamberlain Thomar
	0: User hasn't received the Cuthana Quest yet.
	1: User has begun the Cuthana Quest.
	2: User has completed the Cuthana Quest, but hasn't been rewarded.
	3: User has asked for gold as payment for the Cuthana Quest.
	4: User has asked for Balork's Brand to be removed as payment for the Cuthana Quest.
*/

Begin
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 5602, "Oh! I heard of you! You are a horrible person! Please go away!")
	BREAK
ELSE
	IF (CheckGlobalFlag(__QUEST_BISHOP_ILLNESS) == 0) //If the Bishop is ill again...
		IF (CheckFlag(__QUEST_CUTHANA) == 0) //If the user isn't looking for cuthana herb...
			Conversation
			INTL( 5603, "Please... Talk to the chamberlain... and ask him for help..")
			BREAK
		ELSE
			IF (CheckItem(__OBJ_CUTHANA_HERB) == 0) //If the user is looking for the herb, but has none...
				Conversation
				INTL( 5604, "Please find as much cuthana as you can...")
				BREAK
			ELSE // If the user is questing for the cuthana herb AND has some...
				Conversation //...she says thanks and takes everything the user's got.
				INTL( 5605, "Oh dear! You found some! How marvelous! Now perhaps Bishop Crowbanner will "
				"get well! How can I ever \"repay\" you?")
				;int nCuthana = CheckItem(__OBJ_CUTHANA_HERB); 
				FOR (0, nCuthana ) //Delilah takes all cuthana herbs...
					TakeItem(__OBJ_CUTHANA_HERB)
				ENDFOR
				IF (USER_KARMA <= (100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1))) //...and rewards the PC with good karma.
					GiveKarma(30*(500-USER_KARMA)/500)
				ENDIF
				GiveFlag(__QUEST_CUTHANA, 2) //Flag to indicate she hasn't rewarded user yet.
				GiveGlobalFlag(__QUEST_BISHOP_ILLNESS, 1)
				GiveGlobalFlag(__GLOBAL_QUEST_CROWBANNER_TIMER, rnd.roll(dice(1,6))*4 HOURS TDELAY)
			ENDIF
		ENDIF
	ELSE //The Bishop's not ill, but might get sick again... :)
		IF (CheckFlag(__QUEST_CUTHANA) == 2) //If the user hasn't been paid for helping yet...
			Conversation
			INTL( 5606, "I am still indebted to you. Please, don't hesitate to tell me what I can do "
			"to help.")
		ELSE //Otherwise Delilah speaks to no one for very long.
			Conversation
			INTL( 5607, "I must pray so the bishop doesn't have a relapse...")
		ENDIF
	ENDIF
ENDIF

Command(INTL( 5608, "REPAY"))
""
IF (CheckFlag(__QUEST_CUTHANA) == 2) //If user hasn't been repaid for his favor yet...
	Conversation
	INTL( 5609, "What would satisfy you? Just name your reward, whether it's a \"prayer\", \"healing\", "
	"\"curse\" removal, or... \"gold\", and it will be so. Make your choice carefully.")
ELSE //Otherwise, don't be greedy.
	Conversation
	INTL( 5610, "I believe that has already been done...")
ENDIF

Command3(INTL( 1909, "GOLD"),INTL( 2261, "MONEY"),INTL( 5611, "WEALTH"))
""
IF (CheckFlag(__QUEST_CUTHANA) == 2) //If the user wishes to be repaid with money...
	IF (USER_KARMA <= (-50*(CheckFlag(__QUEST_ISLAND_ACCESS)+1))) // ...and is an evil bastard...
		Conversation
		INTL( 5612, "Oh... I should have expected someone like you would ask for something as mundane "
		"as money for a good deed. Are you certain this is what you want?")
		SetYesNo(PAID_IN_GOLD) //User gets a chance to back off.
	ELSE // If the user *isn't* an evil bastard...
		Conversation
		INTL( 5613, "I... am sorry, I thought there was some good in you. Are you certain "
		"this is what you want?")
		SetYesNo(PAID_IN_GOLD) //User gets a chance to back off.
	ENDIF
ELSE //If the user has already been repaid...
	Conversation
	INTL( 5614, "I believe you have already received what you deserved, have you not?")
ENDIF

YES(PAID_IN_GOLD)
IF (USER_KARMA <= (-50*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
	Conversation
	INTL( 5615, "Very well, you shall have your reward, then.")
ELSEIF (USER_KARMA >= (50*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
	Conversation
	INTL( 5616, "Here is your reward. Please be on your way.")
ELSE
	Conversation
	INTL( 5617, "So be it...")
ENDIF
GiveGold(10000)
GiveFlag(__QUEST_CUTHANA, 3)
IF ((USER_KARMA <= (-50*(CheckFlag(__QUEST_ISLAND_ACCESS)+1))) && (USER_KARMA >= (-100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1))))
	GiveKarma(-20*(500+USER_KARMA)/500)
ELSEIF (USER_KARMA >= (50*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
	GiveKarma(-10*(500+USER_KARMA)/500)
ENDIF

NO(PAID_IN_GOLD)
Conversation
INTL( 5618, "I am relieved to hear that.")

Command4(INTL( 509, "BALORK"),INTL( 1001, "MARK"),INTL( 510, "BRAND"),INTL( 543, "CURSE"))
""
IF (CheckFlag(__BALORK_BRAND) >= 1) //If user has been cursed by Balork
	IF (CheckFlag(__QUEST_CUTHANA) == 2) // If the user mentions this before being repaid...
		Conversation //Delilah offers to help...
		INTL( 5619, "I see that you have been cursed by that evil demon, Balork. Perhaps I "
		"could repay your generous deed by helping you with that? Would that "
		"be agreeable with you?")
		SetYesNo(REMOVE_CURSE)
	ELSE // Otherwise, generic answer.
		Conversation
		INTL( 5620, "It appears you bear Balork's Brand... It is a blemish upon your soul...")
	ENDIF
ELSE
	Conversation
	INTL( 5621, "That demon! I hear he has fled our island to do his evil work in Arakas. But it is "
	"only a matter of time before the Champions of Artherk destroy him permanently.")
ENDIF

YES(REMOVE_CURSE)
Conversation
INTL( 5622, "I will gladly do so! I sense, however, there is a great destiny ahead of you, and "
"that removing Balork's Brand will not change that. I cannot tell you more than this "
"feeling I have. Perhaps you should seek the answers in \"Stoneheim\"... In any case... There... "
"Your curse is lifted. You are free again.")
PRIVATE_SYSTEM_MESSAGE(INTL( 10465, "She lays her hand upon your head and murmurs a long prayer.")) 

GiveFlag(__QUEST_CUTHANA, 4)
RemFlag(__BALORK_BRAND)
IF ((USER_KARMA) <=(100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
	GiveKarma(20*(500-USER_KARMA)/500)
ENDIF
GiveFlag(__FLAG_GOOD_QUEST_COMPLETED_ON_RD, 1)
	;int nNumKeys = CheckItem(__OBJ_ROYAL_KEY_1);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_1 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_2);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_2 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_3);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_3 )  
	ENDFOR
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_4);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_4 )  
	ENDFOR
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_5);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_5 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_6);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_6 )  
	ENDFOR 

NO(REMOVE_CURSE)
Conversation
INTL( 5623, "As you wish...")

YesNoELSE(REMOVE_CURSE)
Conversation
INTL( 5624, "I didn't hear what you said.")
SetYesNo(REMOVE_CURSE)

Command(INTL( 6251, "STONEHEIM")) 
""
IF (CheckFlag(__FLAG_GOOD_QUEST_COMPLETED_ON_RD) == 0) 
	Conversation
	INTL( 10466, "I've never been on the island of Stoneheim but I've heard rumors that it is the field "
	"of a great battle between the forces of good and evil.")
ELSE
   Conversation
	INTL( 10467, "I sense great evil on Stoneheim. I know you have already done much for us and I hate to impose "
	"upon you yet again, but perhaps you could find it in your heart to travel there and investigate "
	"what is happening there. I, for one, would sleep better at night knowing you are taking care of "
	"this. In order to reach Stoneheim, you will need Zhakar's help first, though.")		
	IF ((CheckFlag(__QUEST_ISLAND_ACCESS) < 2) && (CheckItem(__OBJ_SILVER_FEATHER) == 0)) 
		Conversation
		INTL( 10494, " Oh, and I almost forgot. You will need this silver feather to reach Stoneheim. It will " 
		"be required by Zhakar if you are to request his help.") 
		PRIVATE_SYSTEM_MESSAGE(INTL( 10495, "Princess Delilah gives you a silver feather.")) 
		GiveItem(__OBJ_SILVER_FEATHER) 
	ENDIF
ENDIF 

Command(INTL( 3848, "ZHAKAR")) 
INTL( 10468, "He is a bit eccentric but I sense that he is a good person at heart. Plus, he is a wizard of "
"immense power. You should treat him with respect. I sure wouldn't want him to be mad at me.")

Command2(INTL( 4545, "BISHOP"),INTL( 4547, "CROWBANNER"))
INTL( 5625, "Bishop Crowbanner is a kind man. Because he has always been my \"mentor\", I feel it is my duty to "
"see to it that he is treated with the same care as he would for me.")

Command(INTL( 5626, "MENTOR"))
INTL( 5627, "Yes, he has been my tutor for many years now, in fact more than I can remember. Bishop Crowbanner knows "
"more about the workings of the world than most men seek in their lifetime. Since you have been good to him, "
"I am certain he would gladly teach you a thing or two.")

Command(INTL( 5628, "ORACLE"))
INTL( 5629, "The Oracle has disappeared a long time ago, but could foretell the future. I'm afraid I "
"know little of these matters. Perhaps Sorcerer Zhakar could help you.")

Command(INTL( 5630, "PRAY"))
FORMAT(INTL( 5631, "I will pray for you tonight, %s, and hope that Artherk will save your soul."),USER_NAME)

Command(INTL( 569, "HEAL"))
""
IF (USER_MAXHP == USER_HP)
	Conversation
	INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
	Conversation
	INTL( 5632, "Of course! I will gladly heal you. May Artherk watch over you.")
	CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
	HealPlayer(USER_MAXHP)
	PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
ENDIF

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5633, "My name is Delilah, daughter of \"King Theodore\".")

Command2(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"))
INTL( 5634, "I am the king's daughter and a priestess of Artherk.")

CmdAND(INTL( 1072, "KING"),INTL( 754, "THEODORE"))
INTL( 5635, "Yes, the king is my father. Since he sleeps so much, I have taken it upon myself "
"to pray for the peace and well-being of all the citizens of our beautiful kingdom.")

CmdAND(INTL( 5636, "MEET"),INTL( 754, "THEODORE"))
INTL( 5637, "I'm afraid it's not possible to meet with my father. He is very busy with the affairs "
"of the state and has no time for visitors.")

CmdAND(INTL( 6126, "RIDDLE"),INTL( 4275, "HINT"))
INTL( 7156, "Oh, I wouldn't know, but Menark certainly would.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 5638, "That is SO foul!") BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 4599, "Be well. May Artherk protect you.") BREAK

Default
INTL( 4600, "If that will be all, I must return to my prayers.")

EndTalk

}
