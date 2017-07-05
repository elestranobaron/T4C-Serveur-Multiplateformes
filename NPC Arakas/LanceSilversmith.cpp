//////////////////////////////////////////////////////////////////////
// LanceSilversmith.cpp: implementation of the LanceSilversmith class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "LanceSilversmith.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LanceSilversmith::LanceSilversmith()
{}

LanceSilversmith::~LanceSilversmith()
{}

//Description: Magical Weapons/Armors Smith

extern NPCstructure::NPC NakedTorso_Smith;

void LanceSilversmith::Create(){
	npc = NakedTorso_Smith;
	SET_NPC_NAME( "[2899]Lance Silversmith" );
	npc.InitialPos.X = 2580;
	npc.InitialPos.Y = 690;
	npc.InitialPos.world = 0;
}

void LanceSilversmith::OnTalk( UNIT_FUNC_PROTOTYPE )
{

InitTalk

Begin
""
IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 12) 
	;int nNumLetters = CheckItem(__OBJ_SILVERSMITH_LETTER);
	FOR(0, nNumLetters)  
		TakeItem(__OBJ_SILVERSMITH_LETTER)
	ENDFOR 
	Conversation
	INTL( 10085, "You've brought back a parchment written by the hand of \"Thor\" \"Glarefire\" himself? "
	"Give me a few moments to read it, will you?  Hmm. it appears that you are in need of "
	"three \"hammers\" \"of\" \"finality\" to pursue your holy quest? Then, rejoice yourself "
	"for you came to the right place.")	
	PRIVATE_SYSTEM_MESSAGE(INTL( 10086, "You give the parchment to Lance Silversmith.")) 	  
	GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 13) 	
ELSEIF (USER_LEVEL <= 15)
	Conversation
	INTL( 774, "Don't bother me. Come back when you've grown a little.")
	BREAK
ELSE
	Conversation
	INTL( 775, "*Grumble* What is it you want?")
ENDIF

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 776, "I am a master smith. If you need some weapons or armors, \"forged\" or "
"\"improved\", I'm your man. If not, might as well be on your way. *Mutter*")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 777, "Will these questions ever end? You can call me Silversmith. Lance is my first "
"name. *sigh*")

Command2(INTL( 778, "FORGED"),INTL( 779, "IMPROVED"))
INTL( 780, "I can build special weapons or armors for you, if you provide me with the "
"basic materials and components, and have the gold pieces to afford my services. "
"I can create a \"Blessed\" \"Chainmail\", a \"Gloomblade\", or a \"Demonblade\".")

Command(INTL( 787, "MAKE GLOOMBLADE"))
INTL( 788, "Very well...")
IF ((CheckItem(__OBJ_SCROLL_OF_ENCHANTMENT) >= 1) AND (CheckItem(__OBJ_NIGHTSWORD) >= 1) AND (CheckItem(__OBJ_RING_OF_DARKNESS) >= 1) AND (Gold >= 10000))
	TakeItem(__OBJ_SCROLL_OF_ENCHANTMENT)
	TakeItem(__OBJ_NIGHTSWORD)
	TakeItem(__OBJ_RING_OF_DARKNESS)
	TakeGold(10000)
	GiveItem(__OBJ_GLOOMBLADE)
	Conversation
	INTL( 789, "Here we go! You're now the proud owner of a Gloomblade.")
ELSE
	Conversation
	INTL( 790, "You weren't listening, were you?! ONE Scroll of Enchantment, one Nightsword, a Ring "
	"of Darkness and 10,000 gold pieces. How hard is it to understand?? Come back "
	"when you've got it all.")
ENDIF

Command(INTL( 791, "GLOOMBLADE"))
INTL( 792, "The Gloomblade is a weapon of darkness, one that I am loathe to make. But I have "
"sworn to uphold the balance of this world, so I make good swords and evil swords. "
"It's up to people to make appropriate use of them. I require a Scroll of Enchantment, "
"a Nightsword, a Ring of Darkness and, of course, my usual fee of 10,000 gold pieces. "
"When you have all this, ask me to \"make\" \"gloomblade\".")

Command(INTL( 781, "MAKE BLESSED CHAINMAIL"))
INTL( 782, "All right...")
IF ((CheckItem(__OBJ_SCROLL_OF_ENCHANTMENT) >= 1) AND (CheckItem(__OBJ_CHAINMAIL) >= 1) AND (Gold >= 5500))
	TakeItem(__OBJ_SCROLL_OF_ENCHANTMENT)
	TakeItem(__OBJ_CHAINMAIL)
	TakeGold(5500)
	GiveItem(__OBJ_BLESSED_CHAINMAIL_ARMOR)
	Conversation
	INTL( 783, "Here we go! One Blessed Chainmail, to go.")
ELSE
	Conversation
	INTL( 784, "Idiot! I SAID one Scroll of Enchantment, one Chainmail and 5,500 gold "
	"pieces. Do you understand the words that are coming out of my mouth? "
	"It can't be that hard, can it? So begone and don't come back until you've "
	"got everything. By the gods, you youngsters never pay attention!")
ENDIF

Command(INTL( 785, "BLESSED CHAINMAIL"))
INTL( 786, "Aah, a good choice... Building such an armor requires a Scroll of Enchantment, "
"a Chainmail, and 5,500 gold pieces for my service. When you've got all these, come back "
"and ask me to \"make\" \"blessed\" \"chainmail\".")

Command(INTL( 2826, "MAKE DEMONBLADE"))
""
IF (USER_KARMA <= -100)
	IF ((CheckItem(__OBJ_SCROLL_OF_ENCHANTMENT) >= 1) AND (CheckItem(__OBJ_CHAOS_SWORD) >= 1) AND (CheckItem(__OBJ_DEMON_SKULL) >= 1) AND (CheckItem(__OBJ_NECKLACE_OF_THE_BLACK_HEART) >= 1) AND (Gold >= 8000))
		TakeItem(__OBJ_SCROLL_OF_ENCHANTMENT)
		TakeItem(__OBJ_CHAOS_SWORD)
		TakeItem(__OBJ_DEMON_SKULL)
		TakeItem(__OBJ_NECKLACE_OF_THE_BLACK_HEART)
		TakeGold(8000)
		GiveItem(__OBJ_DEMONBLADE)
		PRIVATE_SYSTEM_MESSAGE(INTL( 10087, "Lance Silversmith gives you a demonblade.")) 
		Conversation
		INTL( 7907, "Here it is... Congratulations, it's all yours, now. You should do only evil with "
		"this sword, but some individuals sometimes manage to turn evil into good, somehow. "
		"Good luck.")
	ELSE
		Conversation
		INTL( 7908, "You just don't get it, do you? I said a Scroll of Enchantment, a Chaos Sword, a "
		"Demon Skull, a Necklace of the Black Heart and NO LESS than 8,000 gold pieces. Stop wasting my time, I've "
		"got better things to do with it!")
	ENDIF
ELSE
	Conversation
	INTL( 7909, "I do not sense enough evil in you to give you that sword. You should ask me for "
	"something else, but not that sword.")
ENDIF

Command(INTL( 2828, "DEMONBLADE"))
INTL( 7910, "The Demonblade is decidedly an evil weapon, but in order to do the greatest evil, it will "
"serve both good or evil masters. I, however, only give it to evil individuals. I ask that "
"you bring me a Scroll of Enchantment, a Chaos Sword, a Demon Skull, a Necklace of the Black Heart, "
"and 8,000 gold pieces. Once you have gathered all this, ask me to \"make\" \"demonblade\".")

CmdAND3(INTL( 6535, "MAKE"),INTL( 5672, "HAMMER"),INTL( 8050, "FINALITY"))
""
IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) >= 14) 	
	Conversation							 
	INTL( 10088, "I have already made the three hammers of finality that you needed.")
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 13) 	
	IF ((CheckItem(__OBJ_FINE_STEEL_WARHAMMER)>= 1) && (CheckItem(__OBJ_SCROLL_OF_ENCHANTMENT) >= 1) && (Gold >= 4000) )
		Conversation
		INTL( 10089, "All right, I'll get to work.... It is done! You are the proud owner of a hammer of finality!")
		PRIVATE_SYSTEM_MESSAGE(INTL( 10090, "You give 4000 gold to Lance.")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 10091, "Lance gives you a hammer of finality.")) 
		TakeItem(__OBJ_FINE_STEEL_WARHAMMER) 
		TakeItem(__OBJ_SCROLL_OF_ENCHANTMENT) 	
		TakeGold(4000) 
		GiveItem(__OBJ_HAMMER_OF_FINALITY) 
		GiveFlag( __FLAG_COUNTER_HAMMER_OF_FINALITY, (CheckFlag(__FLAG_COUNTER_HAMMER_OF_FINALITY)+1) ) 	
		IF (CheckFlag(__FLAG_COUNTER_HAMMER_OF_FINALITY) == 3)		
			GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 14) 
			SUMMON("MOBSHADOWSTALKER", FROM_USER(1, X), FROM_USER(1, Y) ) 
			//SUMMON("MOBSHADOWSTALKER", FROM_USER(1, X), FROM_USER(1,Y) ) 
			//SUMMON("MOBSHADOWSTALKER", FROM_USER(0, X), FROM_USER(0,Y) ) 
			//SUMMON("MOBSHADOWSTALKER", FROM_USER(-1, X), FROM_USER(0,Y) )		
			PRIVATE_SYSTEM_MESSAGE(INTL( 9750, "You sense some evil lurking nearby, sending shivers up your spine."))
		ENDIF
	ELSE
		Conversation
		INTL( 10092, "In order for me to create a hammer of hinality, I will require one scroll of enchantment, one fine steel "
		"warhammer and a small fee of 4000 gold for my services.")
	ENDIF
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) <= 12) 	
	Conversation
	INTL( 9738, "I cannot help you with this for the moment.")
ELSE
	Conversation
	INTL( 10093, "You would not know what to do with a hammer of finality.")
ENDIF 
 
CmdAND(INTL( 4880, "SWORD"),INTL( 3990, "MAJESTY"))
INTL( 10605, "I'm afraid that forging a sword of majesty isn't my area of expertise. You should "
"ask \"Thor\" \"Glarefire\" of Stoneheim instead. If I can help you for anything else, "
"feel free to ask and I'll see what I can do.") 

CmdAND(INTL( 5672, "HAMMER"),INTL( 8050, "FINALITY"))
""
IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 14) 	
	Conversation
	INTL( 10094, "I have already made the three Hammers of Finality that you needed.")
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 13) 
	Conversation
	INTL( 10095, "Hammers of Finality are extremely prized items, not so much because of their fighting capabilities, but "
	"beacause of their comforting inner power. It is said that the nails it hammers never come out no matter "
	"what. In order for me to create a Hammer, I will require one scroll of enchantment, one fine steel warhammer and "
	"a small fee of 4000 gold for my services. Once you have gathered all that is required, ask me to "
	"\"make\" \"hammer\" \"of\" \"finality\" and I'll get to work right away.")
ELSEIF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) <= 12) 
	Conversation
	INTL( 9738, "I cannot help you with this for the moment.")
ELSE 
	Conversation
	INTL( 10017, "You wouldn't know what to do with a hammer of finality.")
ENDIF 

Command2(INTL( 8009, "THOR"),INTL( 8010, "GLAREFIRE"))
INTL( 10096, "Thor Glarefire is a centaur blacksmith who taught me everything I know.")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 794, "Raven's Dust? Been there, done that... A quaint little island, although not much is "
"ever happening there. *hrmph* A few monsters, evil sorcerers and thugs... Perhaps I "
"can interest you in some of my wares...")

Command(INTL( 515, "ARAKAS"))
INTL( 795, "Arakas, you say? *Cough* You... you're still looking for that island? Well, "
"if you don't know where it is by now, then we really have no business together.")

Command(INTL( 754, "THEODORE"))
INTL( 796, "The Sleeping King, we call him, but not in front of the guards. He's not really "
"a bad king, he just doesn't do what a king should do. Think that's seditious? "
"Blasted right it is! *Arumph* Problem with that? Didn't think so.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 797, "Oh, wonderful, you've just discovered new words!") BREAK

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 798, "Yeah, whatever.") BREAK

Default
INTL( 799, "Hm. *shrug* Like I care.")

EndTalk

}
