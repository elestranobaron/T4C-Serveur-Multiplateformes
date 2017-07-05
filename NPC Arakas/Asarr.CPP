#pragma hdrstop
#include "Asarr.H"


Asarr::Asarr()
{}

Asarr::~Asarr()
{}

extern NPCstructure::NPC Brigand_Leader;

void Asarr::Create( void )
{
	npc = ( Brigand_Leader );
	SET_NPC_NAME( "[2894]Asarr" );
	npc.InitialPos.X = 2139; // Brigand camp (Montagne)
	npc.InitialPos.Y = 1226;
	npc.InitialPos.world = 0;
}

void Asarr::OnTalk( UNIT_FUNC_PROTOTYPE )
{
CONSTANT JOB = 1;
CONSTANT DIAMOND = 2;
CONSTANT STONE = 3;
CONSTANT TRAITOR = 4;
CONSTANT ACTION = 5;
CONSTANT REFERRAL = 6;
CONSTANT TAUNT_SUNROCK = 7;

InitTalk

Begin
""
IF (CheckFlag (__QUEST_USER_IS_A_TRAITOR) == 1)
	Conversation
	INTL( 574, "It was splendid! We attacked Lord Sunrock's men and we stole all "
	"the merchandise they had bought according to the report. But... Hmmmm, "
	"what's this? Ah, I see! Don't ya tell me, the poor Lord accused you "
	"of being a traitor, eh? Does it mean you want to chicken out on us?")
	SetYesNo(TRAITOR)
ELSEIF (CheckFlag (__QUEST_USER_IS_A_TRAITOR) == 2)
	Conversation
	INTL( 575, "I hope you'll be able to \"soften\" the situation with Lord Sunrock.")
ELSEIF (CheckFlag(__BLACK_MARKET) == 1)
	Conversation
	INTL( 576, "AH! It's you again, my friend. You should ask The Lurker about the "
	"market of shadows if you wish access.")
ELSE
	Conversation
	INTL( 577, "I am impressed you have made it this far through our caverns.") 
ENDIF

YES (TRAITOR)
Conversation
INTL( 578, "Ha! I knew you would not make a very good brigand after all. You sorely "
"lack the courage needed in this dangerous field of work. Still, I would "
"not like to see an increase of guardsmen in the forest. Perhaps we could "
"arrange something to \"soften\" the situation...")
GiveFlag( __QUEST_USER_IS_A_TRAITOR, 2)
IF (USER_KARMA>(-100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
	GiveKarma(-10*(500+USER_KARMA)/500)
ENDIF

NO (TRAITOR)
Conversation
INTL( 579, "Good! I know a good brigand when I see one! Heh! Heh! I'll tell you what, meet "
"my good friend The Lurker in Windhowl and ask him about the market of shadows. "
"Don't worry, he'll understand.")
GiveFlag(__QUEST_USER_IS_A_TRAITOR, 3)
IF (CheckFlag(__BLACK_MARKET) < 2) 
	GiveFlag(__BLACK_MARKET, 1)
ENDIF
IF (USER_KARMA>(-100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
	GiveKarma(-20*(500+USER_KARMA)/500)
ENDIF

YesNoELSE(TRAITOR)
Conversation
INTL( 580, "I need a straigth answer. Do you wish to quit, yes or no?")
SetYesNo(TRAITOR)

Command(INTL( 588, "SOFTEN"))
""
IF (CheckFlag( __QUEST_USER_IS_A_TRAITOR ) == 2)
	Conversation
	INTL( 589, "Perhaps I could give you this small wooden box of jewels. They are worthless to me, "
	"but Lord Sunrock has a weakness for jewels. Actually, I think that I'll SELL you the box. It's a "
	"fair price for your cowardice, don't you agree? You could then lie to him and say that you "
	"defeated us--yeah right! Do you agree with this plan of action?")
	SetYesNo(ACTION)
ELSE
	Conversation
	INTL( 591, "I have no clue about what you're talking about.")
ENDIF

YES (ACTION)
IF (CheckItem(__OBJ_BOX_OF_JEWELS))
	Conversation
	INTL( 7128, "Hey, you want another box of jewels? I'm sorry, but that's all you're gonna get out of me.")
ELSEIF (Gold > 1000)
	TakeGold(Gold/3)
	GiveItem(__OBJ_BOX_OF_JEWELS)
	Conversation
	INTL( 592, "I took some of your gold. It should be enough to pay for "
	"my expenses for saving your tainted reputation.")
ELSE
	Conversation
	INTL( 593, "Bah! You'll need more gold than this if you want this box of jewels!")
ENDIF

NO (ACTION)
Conversation
INTL( 594, "You might want to reconsider all this. If you don't play the game, Lord "
"Sunrock will still suspect that you are working with us.")

YesNoELSE (ACTION)
Conversation
INTL( 595, "You might want to reconsider all this. If you don't play the game, Lord "
"Sunrock will still suspect that you are working with us. Between the two of us, "
"I heard the jail in Windhowl is pretty small and filled with filthy rats.")

Command(INTL( 601, "REPORT"))
""
IF (CheckFlag(__QUEST_USER_IS_A_TRAITOR) > 0)
	Conversation
	INTL( 602, "It's not a good thing to further endanger your life. You will "
	"have to settle your differences with Lord Sunrock.")
ELSEIF (CheckFlag(__QUEST_BRIGAND_GOT_THE_REPORT) > 0)
	Conversation
	INTL( 603, "Be patient, you will know in time if the report was useful to us.")
ELSEIF (CheckItem(__OBJ_SIGFRIED_REPORT) >= 1 )
	GetItemHandle(__OBJ_SIGFRIED_REPORT, SigfriedReport)
	IF (CheckUnitFlag (SigfriedReport, __ITEM_QUEST_SIGFRIED_REPORT) == (CheckGlobalFlag (__GLOBAL_QUEST_SIGFRIED_REPORT)))
		Conversation
		INTL( 604, "You have brought a report from Sigfried? Interesting... You should hurry "
		"to Windhowl at once before Lord Sunrock suspects anything. If it proves "
		"useful to us, do not worry, you'll know. Get back to me and we'll "
		"reward you for your information.")
		GiveFlag( __QUEST_BRIGAND_GOT_THE_REPORT, USER_LEVEL ) 
	ELSE
		Conversation
		INTL( 605, "This report from Sigfried is outdated and thus useless to me! How "
		"can we steal from them if they have already sent their merchandise "
		"to the other town? Get outta my sight at once!")
	ENDIF
ELSEIF (CheckItem(__OBJ_ROLPH_REPORT) >= 1 )
	GetItemHandle(__OBJ_ROLPH_REPORT, RolphReport)
	IF (CheckUnitFlag (RolphReport, __ITEM_QUEST_ROLPH_REPORT) == (CheckGlobalFlag (__GLOBAL_QUEST_ROLPH_REPORT)))
		Conversation
		INTL( 606, "You have brought a report from Rolph? Interesting... You should hurry "
		"to Windhowl at once before Lord Sunrock suspects anything. If it proves "
		"useful to us, do not worry, you'll know. Get back to me and we'll "
		"reward you for your information.")
		GiveFlag( __QUEST_BRIGAND_GOT_THE_REPORT, USER_LEVEL ) 
	ELSE
		Conversation
		INTL( 607, "This report from Rolph is outdated. It's useless to me! How "
		"can we steal from them if they have already sent their merchandise "
		"to the other town? Get outta my sight at once!")
	ENDIF
ELSE
	Conversation
	INTL( 608, "I wonder if it could be useful to me...")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 581, "Be careful with what ya ask, but I will tell you my name. Asarr, leader "
"of all these \"brigands\".")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2670, "Balork's Brand? Huh?")

Command(INTL( 523, "ANNABELLE"))
INTL( 584, "I wonder who she is.")

Command2( INTL( 585, "SHADOW"), INTL( 586, "GUILD") )	
INTL( 587, "The Shadow Guild? No, that's not us, it's what we're part of. Its headquarters "
"are not on this island, nor on Raven's Dust. I'm the Guild's representative in "
"the Kingdom of Goldmoon.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 596, "Why would I have to work when I can steal the wealth of others as easily as "
"I would slay a goblin with my scimitar? Pfah! If I could get \"information\" "
"about transactions between Lighthaven and Windhowl, I could wreak havoc "
"and gain a fortune quite easily!")

Command(INTL( 597, "INFORMATION"))
INTL( 598, "I heard the merchants were hiring adventurers to bring a "
"\"report\" to Lord Sunrock in Windhowl...")

Command(INTL( 599, "SUNROCK"))
INTL( 600, "Lord Sunrock owns the town of Windhowl. He is selfish and he does not "
"want to share his wealth. But he will... Ah ha ha ha!")

Command(INTL( 565, "BRIGAND"))
INTL( 609, "We are proud of what we do. We treat the \"villagers\" of Lighthaven and "
"Windhowl like they have treated us a long time ago.")

Command(INTL( 610, "JOB"))
INTL( 611, "I think you need one, don't you? Will not be a hard task, I tell you. Are you "
"interested?")
SetYesNo (JOB)

YES (JOB)
	GiveFlag (__QUEST_BRIGAND_ROB_DIAMOND,1)
	Conversation
	INTL( 612, "Ya have to find a diamond and bring it back to me. It is a very special "
	"one, so you will have to keep it carefully. In Windhowl, search all the "
	"houses. In one of them, there will be a diamond. Lord Sunrock tends to "
	"lose them sometimes. If ya get back with a diamond, ask me "
	"for the \"reward\". I will not tell ya what it is until ya bring back a "
	"diamond.")

NO (JOB)
	Conversation
	INTL( 613, "Well, ya ain't as good as I thought.")

YesNoELSE (JOB)
	Conversation
	INTL( 614, "Why, you seem somewhat confused by this simple task.")

Command(INTL( 615, "VILLAGER"))
INTL( 616, "They treated us like beggars. They ain't gonna get away with that easily.")

Command(INTL( 617, "REWARD"))
""
IF (CheckFlag(__QUEST_BRIGAND_ROB_DIAMOND) == 2)
 Conversation
 INTL( 618, "You've already robbed one diamond and brought it back to me. You don't "
 "hafta prove yourself worthy anymore.")
ELSEIF (CheckFlag(__QUEST_BRIGAND_ROB_DIAMOND) == 1)
 Conversation
 INTL( 619, "D'ya have a diamond?")
 SetYesNo (DIAMOND)
ELSE
 Conversation
 INTL( 620, "What reward? Who do you think you are to ask me for a reward?")
ENDIF

YES (DIAMOND)
IF (CheckItem (__OBJ_DIAMOND) >= 1)
	GiveFlag (__QUEST_BRIGAND_ROB_DIAMOND, 2)
	GiveFlag (__FLAG_BRIGAND_TRUST,1)
	TakeItem (__OBJ_DIAMOND)
	Conversation
	INTL( 621, "Very well, I am truly impressed. I offer you free \"training\". That is good "
	"enough for an apprentice thief such as you.")
ELSE
	Conversation
	INTL( 622, "That is not the diamond I want. Locate it and return it to me.") BREAK
ENDIF

NO (DIAMOND)
Conversation
INTL( 623, "You have not finish the job yet. You'll have to go to Windhowl to find it.")

YesNoELSE (DIAMOND)
Conversation
INTL( 624, "What are you talking about?")

Command(INTL( 539, "GOBLIN"))
INTL( 625, "How do ya think we handle those little vermins? We simply let them do "
"the biggest part of our job, distract the villagers' attention. Why would "
"we bother ourselves wtih them? They have tried to bypass our caves, but they surely "
"do not have your skills. Goblin scouts occasionally find their way into our camp, "
"but will never successfully find it unless they come with their entire army.")

Command2(INTL( 496, "TEACH"),INTL( 495, "LEARN"))
""
IF (CheckFlag (__FLAG_BRIGAND_TRUST) > 0 )
	Conversation
	INTL( 2824, "You did a good job fetching one of Lord Sunrock's precious "
	"diamonds. When one of my associate will deem you ready, he or "
	"she will tell you to come back to me and then, I'll be able to "
	"teach you some pretty neat tricks.")
/*
 Conversation
 INTL( 626, "I said free \"training\" but that ain't free to learn.")
 CreateSkillList
 AddTeachSkill (__SKILL_PICKLOCK, 1, 800)
 CantLearnSkill (INTL( 627, "Sorry, you are too clumsy to learn this."))
 SendTeachSkillList 
*/
ELSE
	Conversation
	INTL( 628, "I will not teach anything to someone I do not \"trust\".")
ENDIF

Command(INTL( 502, "TRAIN"))
""
IF (CheckFlag (__FLAG_BRIGAND_TRUST) > 0)
	Conversation
	INTL( 2825, "You did a good job fetching one of Lord Sunrock's precious "
	"diamonds. When one of my associate will deem you ready, he or "
	"she will tell you to come back to me and then, I'll be able to "
	"teach you some pretty neat tricks.")
/*
 Conversation
 INTL( 629, "Why, I said free training? I do not remember. I'll reduce the cost.")
 CreateSkillList
 AddTrainSkill (__SKILL_PICKLOCK, 100, 25)
 CantLearnSkill (INTL( 630, "I can not train you more now."))
 SendTrainSkillList
*/
ELSE
 Conversation
 INTL( 631, "I do not \"trust\" you enough.")
ENDIF

Command(INTL( 632, "TRUST"))
INTL( 633, "Before I trust you, you will have to do a \"job\" for me. Heh heh heh...")

Command(INTL( 475, "STONE OF LIFE"))
""
IF ((CheckGlobalFlag (__QUEST_STONE_OF_LIFE) > 1) && (CheckGlobalFlag (__WHO_HAS_THE_STONE_FLAG) == 1 ))
	IF (CheckGlobalFlag (__TROLL_STONE_OF_LIFE) == 5 )
		Conversation
		INTL( 634, "I already gave that useless rock to somebody else.")
	ELSE
		IF (CheckFlag (__FLAG_BRIGAND_TRUST) == 0)
			Conversation
			INTL( 635, "I do not \"trust\" you enough to talk about that.")
		ELSE
			Conversation
			INTL( 636, "It was easy to wrest the stone from that stupid orc. Now, don't take this "
			"the wrong way, but let's talk business. If you want the stone, you'll hafta "
			"give me a thousand gold pieces. Is that a deal?")
			SetYesNo( STONE ) 
		ENDIF
	ENDIF
ELSE
	Conversation
	INTL( 637, "I don't really know about what you're talking about.")
ENDIF

YES ( STONE )
IF (Gold < 500 )
	Conversation
	INTL( 638, "You're really too poor for me to take that money. Thanks for the offer,"
	"but come back when you have more gold to offer.")
ELSE
	IF (Gold < 1000 )
		TakeGold(Gold)
		Conversation
		INTL( 639, "I understand, my friend, times are rough. Here, I'll take what "
		"you have and give you the stone anyway.")
		GiveGlobalFlag(__TROLL_STONE_OF_LIFE, 5 )
		GiveItem(__OBJ_STONE_OF_LIFE)
		GetItemHandle(__OBJ_STONE_OF_LIFE, StoneOfLife)
		GiveUnitFlag (StoneOfLife, __ITEM_QUEST_STONE_OF_LIFE, CheckGlobalFlag( __QUEST_STONE_OF_LIFE ))
	ELSE
		TakeGold(1000)
		Conversation
		INTL( 640, "It's nice doin' business with you.")
		GiveGlobalFlag(__TROLL_STONE_OF_LIFE, 5 )
		GiveItem(__OBJ_STONE_OF_LIFE)
		GetItemHandle(__OBJ_STONE_OF_LIFE, StoneOfLife)
		GiveUnitFlag (StoneOfLife, __ITEM_QUEST_STONE_OF_LIFE, CheckGlobalFlag( __QUEST_STONE_OF_LIFE ))
	ENDIF
ENDIF

NO ( STONE )
Conversation
INTL( 641, "You're missing a great deal my friend. I'm sure this rock is worth "
"more than a puny thousand gold pieces. Heh heh.")

YesNoELSE ( STONE )
Conversation
INTL( 642, "Perhaps you'll make your mind, some day. Ha ha ha.")

Command (INTL( 643, "KALASTOR"))
""
IF (CheckFlag (__HELP_ASARR) > 0 )
	Conversation
	INTL( 644, "Yeah, yeah, I've already told you all I know about him.")
ELSE
	IF (CheckFlag (__SEEK_ASARR) == 0 )
		Conversation
		INTL( 645, "What do I care about the little weasel! He's doing his own thing in Lighthaven,"
		"but it's really insignificant and hardly worth my intervention.")
	ELSE
		Conversation
		INTL( 646, "So the little runt is still operating his racket in Lighthaven? You a friend of his?")
		SetYesNo( REFERRAL )
	ENDIF
ENDIF

YES ( REFERRAL )
	IF (CheckFlag( __BLACK_MARKET) > 0)
		Conversation
		INTL( 647, "Guess you don't have much taste in friends, then. But no matter. I can always use some "
		"help in ripping off that bastard Lord Sunrock, if you're \"interested\".")
		GiveFlag ( __HELP_ASARR, 1 )
	ELSE
		Conversation
		INTL( 648, "No accounting for taste. If that'll be all, I'll walk you to the door.")
	ENDIF

NO ( REFERRAL )
	IF (CheckFlag (__BLACK_MARKET) > 0)
		Conversation
		INTL( 649, "Good. The little rat double-crossed me a long time ago, so any friend of his is no friend "
		"of mine. Look, I might have a job for you, if you're \"interested\".")
		GiveFlag ( __HELP_ASARR, 1 )
	ELSE
		Conversation
		INTL( 650, "Well, at least we have that in common. I never liked him much anyway. If I knew I could "
		"\"trust\" you, I'd have a job for you. But that's for later, I guess.")
	ENDIF

YesNoELSE ( REFERRAL )
	Conversation
	INTL( 651, "Yes or no? How hard can it be to choose?")
	SetYesNo ( REFERRAL )

Command ( INTL( 652, "INTERESTED") )
""
IF (CheckFlag (__HELP_ASARR) == 1 )
	Conversation
	INTL( 653, "I'd like you to deliver something to Lord Sunrock for me. You see, I like to taunt him "
	"once in a while and tell him what crime we're about to do. It drives him nuts "
	"because his troops are too inept to stop us. Would you do this for me?")
	SetYesNo ( TAUNT_SUNROCK )
ELSE
	Conversation
	INTL( 654, "I'm not sure what you're talking about...")
ENDIF

YES ( TAUNT_SUNROCK )
IF ( CheckItem ( __OBJ_LETTER_TO_SUNROCK ) == 0 )
	GiveItem ( __OBJ_LETTER_TO_SUNROCK )
	Conversation
	INTL( 655, "Fantastic! Here's a letter that I'd like you to deliver to him in person. Just mention it's "
	"\"from\" \"Asarr\", his friend. <grin> You should get a kick out of his little tantrum.")
ELSE
	Conversation
	INTL( 656, "Seeing as you already *have* the letter, why don't you go deliver it already?")
ENDIF

NO ( TAUNT_SUNROCK )
Conversation
INTL( 657, "Ah well, no big deal. I'll just find someone else.")

YesNoELSE ( TAUNT_SUNROCK )
Conversation
INTL( 658, "That's hardly an answer, friend.")
SetYesNo (TAUNT_SUNROCK )
	
Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 659, "Don't get lost on your way out.") BREAK

Default
INTL( 660, "That is none of your business.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Asarr::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_PICKLOCK, 100, 25 );
	CLOSE_NPC_DATA_TRAIN

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL (__SKILL_PICKLOCK, 1, 800)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH
CLOSE_NPC_DATA_EXCHANGE
