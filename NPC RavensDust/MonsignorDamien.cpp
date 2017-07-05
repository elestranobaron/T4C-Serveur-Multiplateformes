// MonsignorDamien.cpp: implementation of the MonsignorDamien class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "MonsignorDamien.h"
 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MonsignorDamien::MonsignorDamien()
{}

MonsignorDamien::~MonsignorDamien()
{}

extern NPCstructure::NPC MonsignorDamienNPC;

//////////////////////////////////////////////////////////////////////////////////////////
void MonsignorDamien::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Monsignor Damien
//
{
    npc = MonsignorDamienNPC;
    SET_NPC_NAME( "[2970]Monsignor Damien" );
    npc.InitialPos.X = 1030;
    npc.InitialPos.Y = 2090;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////
//  Monsignor Damien has been banished from the Church of Artherk a few
//  years ago. He was, back then, a very ambitious man looking to rise
//  quickly in the ranks of the church, and has been fairly successful
//  to date. When Shadeen arrived in town, having only recently become
//  immortal after drinking a special potion, she began stirring up
//  trouble and quickly clashed horns (so to speak) with Monsignor
//  Damien Malakai. Their underground confrontation drew little
//  attention, but caused many unexplained hardships to the people of
//  Silversky and the Kingdom of Goldmoon more specifically. There came
//  a time, however, when Shadeen got the upper hand through a traitor
//  in the church, and she framed Msgr. Damien, leading his superiors
//  to believe he had been spreading heresy. Damien was thrown out of
//  the church and was nearly driven mad by grief. While he acts all
//  nice and apparently honest, he's really very manipulative, trying
//  to get adventurers to side against him and to kill her. Upon finding
//  likely prospects, he summons minions that appear to work for Shadeen,
//  but actually work for him, so the PC believes she's turned against
//  him/her. After that, when the PC finally "realizes" that Shadeen has
//  betrayed him/her, s/he will ask Damien for help, which the devious
//  ex-priest will be delighted to give. At this point, he suggest that the
//  PC has his/her weapon enchanged for Elven Slaying, since he knows that
//  Shadeen has some Elven blood, and s/he can then "take care" of her.
//////////////////////////////////////////////////////////////////////////////////
//  __QUEST_DAMIEN_SUBPLOT
//  0: PC hasn't begun subplot yet.
//  1: PC has asked to know more about Shadeen; Assassins attempt on PC's life.
//  2: PC has been asked to killed Shadeen with elven-slaying weapon.
//  3: PC has gotten Elvenbane from Xanth
//  4: PC has killed Shadeen
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
void MonsignorDamien::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Monsignor Damien
//
{

CONSTANT MORE_ABOUT_SHADEEN = 1;
CONSTANT PRICE = 2;
CONSTANT PRICE2 = 3;
CONSTANT PRICE3 = 4;
CONSTANT ELVENBANE  = 5; 
InitTalk

Begin
INTL( 3693, "You wish to speak with me, my child?")
IF ((CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 1) || (CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 2)) 
	IF (CheckFlag(__QUEST_SEEK_SHADEEN) == 8) 
		GiveFlag(__QUEST_DAMIEN_SUBPLOT, 3) 
	ENDIF
ENDIF					 
IF ((CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 1) && (CheckItem(__OBJ_LETTER_FROM_DAMIEN_TO_XANTH) >= 1)) 
	GiveFlag(__QUEST_DAMIEN_SUBPLOT, 2) 
ENDIF 		

Command(INTL( 7696, "SWEAR ALLEGIANCE TO OGR"))
INTL( 7697, "Your devotion is admirable and it will not go unnoticed. However, I have other important matters to attend to right now, and "
"I do not have time to perform the necessary rites of initiation.")
       
Command(INTL( 11646, "ELVENBANE"))           
""
IF ((CheckFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD) == 1) && (CheckFlag(__DAMIEN_HAS_REMOVED_ELVENBANE) == 0)) 
	// It is assumed that the user has the elvenbane in its possession. 
	IF (CheckItem(__OBJ_ELVENBANE) == 1) 
		Conversation
		INTL( 11647, "As you are probably aware, the Elvenbane has served its purpose and is now useless. It is possible for me to break the enchantment but "
		"doing so will also destroy the blade. So, do you desire to be freed from its enchantment?")
		SetYesNo(ELVENBANE) 
	ELSE
		Conversation
		INTL( 11648, "As you are probably aware, the Elvenbane has served its purpose and is now useless. It is possible for me to break the enchantment but "
		"doing so will also destroy the blade. However, I cannot do so unless you willingly stop holding the blade in your hand. So, do "
		"you desire to be freed from its enchantment?")						
		SetYesNo(ELVENBANE) 
	ENDIF 	
ELSEIF (CheckFlag(__DAMIEN_HAS_REMOVED_ELVENBANE) == 1) 
	// The user got it removed previously. 
	Conversation
	INTL( 11649, "Ah, so the prodigal child longs to wield the Elvenbane once more, eh? Alas,  the blade is no more. Who knows, perhaps you'll wield " 		
	"it again in another life?") 
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 11650, "The Elvenbane is a formidable weapon indeed. It is one of the few weapons that can inflict mortal wounds to elves.")
ELSE
	Conversation
	INTL( 4333, "That is none of your concern.") 
ENDIF 

YES(ELVENBANE) 
IF (CheckItem( __OBJ_ELVENBANE)  == 0) 
	Conversation
	INTL( 11651, "Do not play games, child. If you wish to free yourself from the Elvenbane, you must stop holding onto it!") 
ELSE
	Conversation
	FORMAT(INTL( 11652, "And so, %s, I hereby release you from the Elvenbane's enchantment."), USER_NAME) 
	PRIVATE_SYSTEM_MESSAGE(INTL( 11653, "Monsignor Damien whispers a few arcane words and the Elvenbane crumbles into tiny metallic fragments.")) 
	TakeItem(__OBJ_ELVENBANE)  
	GiveFlag(__DAMIEN_HAS_REMOVED_ELVENBANE, 1) 
ENDIF 

NO(ELVENBANE)
Conversation
INTL( 11654, "As you wish. It is yours to bear for as long as you wish. If you ever change your mind, you know where to find me.") 

YesNoELSE(ELVENBANE) 
Conversation
INTL( 11655, "Well, do you want me to free you of the Elvenbane?") 
SetYesNo(ELVENBANE) 

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 3695, "I am called Damien, Damien the Damned.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 3697, "I preach to the winds, a single voice in a desert of madness. I plead for reason, "
"and sure enough, no one listens.")

Command(INTL( 3698, "DAMNED"))
INTL( 3699, "Yes indeed, I was condemned for my unorthodox beliefs, but only because the fools "
"above me in the church of Artherk could not see the greater design of the world. "
"But some day, I will show them all.")

Command2(INTL( 554, "HELP"),INTL( 3700, "KILL SHADEEN"))
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1)
	Conversation
	INTL( 10447, "Uh? I'm afraid I don't understand what you're talking about.") 
ELSE
	SWITCH(CheckFlag(__QUEST_DAMIEN_SUBPLOT))
		CASE(0)
			Conversation
			INTL( 3701, "I do not understand what you want, child.")
		ENDCASE
		CASE(1) // If PC was offered help against Shadeen:
			Conversation
			INTL( 3702, "You wish to kill Shadeen? Excellent! I will help you with whatever I can. As you probably know, "
			"the wench cannot be killed by conventional means. Although she seems invincible, I assure you she "
			"is not without a weakness. I am ready and willing to provide you with the \"means\" to kill her, but "
			"not without a price. Would you like to hear that price?")
			SetYesNo(PRICE)
		ENDCASE
		CASE(2)
			Conversation
			INTL( 3703, "I've told you, to kill Shadeen, you will need to perform three tasks. First, locate "
			"the fabled Blade of Ruin. Then, seek out Xanth. If you are to use the Blade of Ruin on "
			"Shadeen, He must enchant it. Finally, strike down Shadeen where she stands. After that, "
			"return here and I will \"reward\" you, and perhaps have more work for you.")
		ENDCASE
		CASE(3)
			Conversation
			INTL( 3704, "Well, my friend, now that you have the Elvenbane, you only need to strike her down, then "
			"return to me. If you wish, I may help you find a way to \"Stoneheim\"...")
		ENDCASE
		CASE(4)
			IF((CheckItem(__OBJ_SHADEEN_EARRINGS) == 0) && (CheckFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD) == 0))
				Conversation
				INTL( 7151, "What? You say you have killed Shadeen yet you lack the token of proof that I asked for. I don't care "
				"if you have to bring her back to life and kill her again, you're not going to Stoneheim until you "
				"bring me proof of Shadeen's death!")
			ELSE
				Conversation
				INTL( 3705, "Yes, you have done very good work indeed. I cannot thank you enough for your efforts."
				"You have toiled long and hard for our cause. Xanth and I have talked about you, and we both agree "
				"that you could do even more for Ogrimar if you went to \"Stoneheim\".") 				
				IF (CheckItem(__OBJ_SHADEEN_EARRINGS) > 0) 
					PRIVATE_SYSTEM_MESSAGE(INTL( 10448, "Monsignor Damien eagerly grabs Shadeen's earrings and stores them in his pouch."))
					TakeItem( __OBJ_SHADEEN_EARRINGS )   
				ENDIF 					 
				IF (CheckFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD) == 0) 
					GiveFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD, 1) 
				ENDIF
            ENDIF
		ENDCASE
		OTHERWISE
			Conversation
			INTL( 3706, "I... see.")
		ENDCASE
	ENDSWITCH
ENDIF 

Command(INTL( 6251, "STONEHEIM")) 
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1)
	Conversation
	INTL( 10449, "Stoneheim is just another island. If that will be all, I have more important things to do than "
	"teaching you geography.") 
ELSE
	IF (CheckFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD) == 1) 
		Conversation
		INTL( 10450, "Yes, it is time for you to leave for Stoneheim and join forces with us. The time has "
		"come to slay \"Makrsh\" \"P'Tangh\", and you just might be the person to do it. Once on Stoneheim, "
		"go to Stonecrest and seek Julian; he'll tell you what to do from there. The easiest "
		"and fastest way to go there is to perform the \"ritual\" \"of\" \"blood\".")	
	ELSE
		Conversation
		INTL( 10451, "You are not ready to leave Raven's Dust for Stoneheim just yet. You still have "
		"much to do here.")  
	ENDIF 		
ENDIF 

Command(INTL( 10452, "RITUAL OF BLOOD")) 
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1)
	Conversation
	INTL( 10453, "I'm afraid I cannot help you with this.")	
ELSEIF (CheckFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD) == 1) 
	Conversation
	INTL( 10454, "Alas, only that crazed mage Zhakar has the power to perform it flawlessly. You will have to "
	"ask him but he will undoubtedly assist you. That doesn't mean that Zhakar is one of us " 
	"but he doesn't really care whether you are a follower of Ogrimar or Artherk. Heck, I doubt "
	"he wouldn't even mind if you were \"Makrsh\" \"P'Tangh\" himself!") 
ELSE
	Conversation
	INTL( 10455, "You are not ready to leave Raven's Dust for Stoneheim just yet. You still have "
	"much to do here.")  
ENDIF 

Command2(INTL( 738, "MAKRSH"),INTL( 739, "P'TANGH")) 
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1)
	Conversation
	INTL( 1361, "Eh?")
ELSE
	Conversation
	INTL( 10456, "The Lich has been gaining power these past centuries. His strength is so great now that it "
	"rivals that of the gods. He must be stopped at the cost of y.. our lives in the name of our "
	"god, \"Ogrimar\".") 
ENDIF 

Command(INTL( 8606, "OGRIMAR")) 
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1)			// Some BS for good players. 
	Conversation
	INTL( 10457, "A terrible god is he. Please, do not speak his name in my presence.") 
ELSE
	Conversation
	INTL( 10458, "He is the god of Night, and represents terror and chaos. It is He who we have chosen to follow.") 
ENDIF 

Command(INTL( 3848, "ZHAKAR"))
INTL( 10459, "Zhakar resides in a crumbling tower located in the Wizard's Vale.")

Command(INTL( 7700, "STONECREST")) 
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1)
	Conversation
	INTL( 10460, "Stonecrest is the main town on the Stoneheim island.") 
ELSE
	Conversation
	INTL( 10461, "Stonecrest is the main town on the Stoneheim island. It is there that you are to meet Julian.") 
ENDIF 

Command(INTL( 9115, "JULIAN")) 
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1)
	Conversation
	INTL( 10462, "Julian? I've never had the pleasure of meeting someone whose name was Julian.") 
ELSE
	Conversation
	INTL( 10463, "He'll be the judge as whether you should be introduced to his master or not.") 
ENDIF 

CmdAND(INTL( 6126, "RIDDLE"),INTL( 4275, "HINT"))
INTL( 7150, "I am no master of riddles, I am afraid. Mayhaps you could ask Menark? I happen to know he won "
"last year's Tournament of Mystic Riddles, so he's sure to be your man.")

Command(INTL( 1581, "SHADEEN"))
""
IF (CheckFlag(__QUEST_SEEK_SHADEEN) < 7) // If PC hasn't received the Silver Feather yet...
	Conversation
	INTL( 3707, "I do not believe in speaking of people behind their backs, even if such people "
	"would not hesitate to do so to thwart my goals.")
ELSEIF (CheckFlag(__QUEST_SEEK_SHADEEN) == 7) // IF PC has received Silver Feather from Shadeen
	Conversation
	INTL( 3708, "Ah, very well, if you insist, I will tell you about her... She is a witch that has "
	"drunk a mixture of elven blood and other ingredients, and has acquired unholy eternal "
	"life as a result. She has also caused my fall from grace in the church, although "
	"in retrospect, I could perhaps thank her for the favor. Is that enough information?")
	SetYesNo(MORE_ABOUT_SHADEEN)
ELSE
	Conversation
	INTL( 3709, "You did the right thing, my friend. Killing Shadeen has made the world a better place.")
ENDIF

YES(MORE_ABOUT_SHADEEN)
	Conversation
	INTL( 3710, "I thought as much. However, I feel it would be in your best interest to let you know this much "
	"at least. I have heard that you have had dealings with her, and that your usefulness is coming to an end. "
	"In fact, I am surprised you have survived this long. Tell me, is your plan to \"kill\" \"Shadeen\" now?")
	IF(CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 0)
		GiveFlag(__QUEST_DAMIEN_SUBPLOT, 1)
	ENDIF
	IF (CheckFlag(__FLAG_ASSASSIN_SUMMONED) == 0)	
		SUMMON( "SHADEENMASKEDASSASSIN", FROM_NPC(rnd.roll(dice(1, 5))-3,X), FROM_NPC(rnd.roll(dice(1, 5))-3,Y))
		SUMMON( "SHADEENMASKEDASSASSIN", FROM_NPC(rnd.roll(dice(1, 5))-3,X), FROM_NPC(rnd.roll(dice(1, 5))-3,Y))
		SUMMON( "SHADEENMASKEDASSASSIN", FROM_NPC(rnd.roll(dice(1, 5))-3,X), FROM_NPC(rnd.roll(dice(1, 5))-3,Y))
		GiveFlag(__FLAG_ASSASSIN_SUMMONED, 1)
	ENDIF

NO(MORE_ABOUT_SHADEEN)
	Conversation
	INTL( 3711, "I will also tell you this, then. She is a devious woman, and not to be trusted. In fact, "
	"I hear you have had dealings with her, and that your usefulness is coming to an end. "
	"Should you wish for my \"help\" in preventing this, just ask for it.")
	IF(CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 0)
		GiveFlag(__QUEST_DAMIEN_SUBPLOT, 1)
	ENDIF
	IF (CheckFlag(__FLAG_ASSASSIN_SUMMONED) == 0)
		SUMMON( "SHADEENMASKEDASSASSIN", FROM_NPC(rnd.roll(dice(1, 5))-3,X), FROM_NPC(rnd.roll(dice(1, 5))-3,Y))
		SUMMON( "SHADEENMASKEDASSASSIN", FROM_NPC(rnd.roll(dice(1, 5))-3,X), FROM_NPC(rnd.roll(dice(1, 5))-3,Y))
		SUMMON( "SHADEENMASKEDASSASSIN", FROM_NPC(rnd.roll(dice(1, 5))-3,X), FROM_NPC(rnd.roll(dice(1, 5))-3,Y))
		GiveFlag(__FLAG_ASSASSIN_SUMMONED, 1)
	ENDIF

YesNoELSE(MORE_ABOUT_SHADEEN)
	Conversation
	INTL( 3712, "Are you certain that you do not wish to know more about her?" )
	SetYesNo(MORE_ABOUT_SHADEEN)
	
YES(PRICE)
	Conversation
	INTL( 3713, "I want for three things only: a \"gift\", a \"token\", and last but not least, \"abandon\".")
NO(PRICE)
	Conversation
	INTL( 3714, "I see, then I would ask that you leave immediately. I will not waste precious time with the "
	"likes of you!")
YesNoELSE(PRICE)
	Conversation
	INTL( 3715, "Well? Would you like to hear the price?")
	SetYesNo(PRICE)

Command(INTL( 617, "REWARD"))
""
SWITCH(CheckFlag(__QUEST_DAMIEN_SUBPLOT))
	CASE(0)
		Conversation
		INTL( 3701, "I do not understand what you want, child.")
	ENDCASE
	CASE(1) // If PC was offered help against Shadeen:
		Conversation
		INTL( 3716, "I know not what you mean.")
	ENDCASE
	CASE(2) // If PC has been given mission & instructions on how to kill Shadeen:
		Conversation
		INTL( 3717, "I've told you, I will reward you after you have killed Shadeen, not before.")
	ENDCASE
	CASE(3) // If PC has received Elvenbane but hasn't killed Shadeen yet:
		Conversation
		INTL( 3718, "Well, my friend, now that you have the Elvenbane, you only need to strike her down, then "
		"return to me. I will help you find a way to Stoneheim as a reward.")
	ENDCASE
	CASE(4) // If PC has killed Shadeen:
		IF((CheckItem(__OBJ_SHADEEN_EARRINGS) == 0) && (CheckFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD) == 0))
			Conversation
			INTL( 7151, "What? You say you have killed Shadeen yet you lack the token of proof that I asked for. I don't care "
			"if you have to bring her back to life and kill her again, you're not going to Stoneheim until you "
			"bring me proof of Shadeen's death!")
			GiveFlag(__QUEST_DAMIEN_SUBPLOT, 3)
		ELSE
			Conversation
			INTL( 3705, "Yes, you have done very good work indeed. I cannot thank you enough for your efforts."
			"You have toiled long and hard for our cause. Xanth and I have talked about you, and we both agree "
			"that you could do even more for Ogrimar if you went to \"Stoneheim\".") 									
			IF (CheckItem(__OBJ_SHADEEN_EARRINGS) >= 1) 
				PRIVATE_SYSTEM_MESSAGE(INTL( 10448, "Monsignor Damien eagerly grabs Shadeen's earrings and stores them in his pouch."))   	
				;int nNumEarrings = CheckItem(__OBJ_SHADEEN_EARRINGS);
				FOR(0, nNumEarrings) 
					TakeItem( nNumEarrings ) 
				ENDFOR 
			ENDIF 
			IF (CheckFlag(__FLAG_GOOD_QUEST_COMPLETED_ON_RD) == 0) 
				GiveFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD, 1) 
			ENDIF 
		ENDIF
	ENDCASE
	OTHERWISE
		Conversation
		INTL( 3706, "I... see.")
	ENDCASE
ENDSWITCH

Command(INTL( 3720, "GIFT"))
""
IF(CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 1)
	IF(CheckFlag(__FLAG_PAID_DAMIEN_PRICE) >= 1)
		Conversation
		INTL( 11656, "You have already paid the price. Now, I can give you the \"means\" to accomplish the task that lies ahead.") 
	ELSE
		Conversation
		INTL( 3721, "The gift I require is a simple thing. I ask only that you donate the small sum of 50000 gold pieces "
		"to aid my cause. ")
		IF(CheckFlag(__FLAG_DAMIEN_PRICE) == 0) // If user hasn't asked about anything yet
			GiveFlag(__FLAG_DAMIEN_PRICE, 2) // The user just asked about the gift
		ELSE
			IF(CheckFlag(__FLAG_DAMIEN_PRICE) % 2 != 0) // User has already asked about the token or the abandon
				GiveFlag(__FLAG_DAMIEN_PRICE, CheckFlag(__FLAG_DAMIEN_PRICE) * 2) // User has just asked about the gift
			ENDIF
			IF((CheckFlag(__FLAG_DAMIEN_PRICE) % 2 == 0) && (CheckFlag(__FLAG_DAMIEN_PRICE) % 3 == 0) && (CheckFlag(__FLAG_DAMIEN_PRICE) %5 == 0))
				Conversation
				INTL( 3722, "Now that you know what it is, tell me, are you willing to pay the price I ask for?")
				SetYesNo(PRICE2)
			ENDIF
		ENDIF
	ENDIF
ELSE
	Conversation
	INTL( 624, "What are you talking about?")
ENDIF

Command(INTL( 3723, "TOKEN"))
""
IF(CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 1)
	IF(CheckFlag(__FLAG_PAID_DAMIEN_PRICE) >= 1)
		Conversation
		INTL( 11657, "You have already paid the price. Now, I can give you the \"means\" to accomplish the task that lies ahead.") 
	ELSE
		Conversation
		INTL( 3724, "Once you have paid the price, I will tell you how to deal with Shadeen. After completing your task, "
		"I will require that you bring me a token to prove to me that you are true to your word. ")
		IF(CheckFlag(__FLAG_DAMIEN_PRICE) == 0) // If user hasn't asked about anything yet
			GiveFlag(__FLAG_DAMIEN_PRICE, 3) // The user just asked about the token
		ELSE
			IF(CheckFlag(__FLAG_DAMIEN_PRICE) % 3 != 0) // User has already asked about the gift or the abandon
				GiveFlag(__FLAG_DAMIEN_PRICE, CheckFlag(__FLAG_DAMIEN_PRICE) * 3) // User has just asked about the token
			ENDIF
			IF((CheckFlag(__FLAG_DAMIEN_PRICE) % 2 == 0) && (CheckFlag(__FLAG_DAMIEN_PRICE) % 3 == 0) && (CheckFlag(__FLAG_DAMIEN_PRICE) %5 == 0))
				Conversation
				INTL( 3722, "Now that you know what it is, tell me, are you willing to pay the price I ask for?")
				SetYesNo(PRICE2)
			ENDIF
		ENDIF
	ENDIF 
ELSE
	Conversation
	INTL( 624, "What are you talking about?")
ENDIF

Command(INTL( 3725, "ABANDON"))
""
IF(CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 1)
	IF(CheckFlag(__FLAG_PAID_DAMIEN_PRICE) >= 1)
			Conversation
			INTL( 11658, "You have already paid the price. Now, I can give you the \"means\" to accomplish the task that lies ahead.") 
	ELSE
		Conversation
		INTL( 3726, "It is quite simple actually. Abandon all faith in whatever god or gods you currently worship and swear "
		"allegiance to my master, Ogrimar, god of the night, for as long as you live. ")
		IF(CheckFlag(__FLAG_DAMIEN_PRICE) == 0) // If user hasn't asked about anything yet
			GiveFlag(__FLAG_DAMIEN_PRICE, 5) // The user just asked about the abandon
		ELSE
			IF(CheckFlag(__FLAG_DAMIEN_PRICE) % 5 != 0) // User has already asked about the gift or the token
				GiveFlag(__FLAG_DAMIEN_PRICE, CheckFlag(__FLAG_DAMIEN_PRICE) * 5) // User has just asked about the abandon
			ENDIF
			IF((CheckFlag(__FLAG_DAMIEN_PRICE) % 2 == 0) && (CheckFlag(__FLAG_DAMIEN_PRICE) % 3 == 0) && (CheckFlag(__FLAG_DAMIEN_PRICE) % 5 == 0))
				Conversation
				INTL( 3722, "Now that you know what it is, tell me, are you willing to pay the price I ask for?")
				SetYesNo(PRICE2)
			ENDIF
		ENDIF
	ENDIF
ELSE
	Conversation
	INTL( 624, "What are you talking about?")
ENDIF

YES(PRICE2)
	IF(Gold < 50000)
		Conversation
		INTL( 3727, "It would seem that you can't afford to pay me right now. As much as it pains me to have to "
		"wait longer before I can witness Shadeen's downfall, I cannot help you until you have enough "
		"gold to pay me entirely.")
	ELSE
		TakeGold(50000)
		GiveFlag(__FLAG_PAID_DAMIEN_PRICE, 1)
		Conversation
		INTL( 3728, "Excellent! I thank you for this generous contribution. It will be put to good use, I assure you. "
		"Also, I trust you will return here with the token I asked for once you've properly disposed of Shadeen. "
		"As for the matter of your allegiance, all you have to do is say 'I swear allegiance to Ogrimar' and you "
		"will become one of his devoted followers.")
	ENDIF
NO(PRICE2)
	Conversation
	INTL( 3729, "Urgh! That is very unfortunate. Seeing as how I am rather desperate, I will settle for a mere 25000 gold "
	"donation, along with the token of proof, and we can forget the pledge of fealty altogether. Is that more "
	"to your liking?")
	SetYesNo(PRICE3)
YesNoELSE(PRICE2)
	Conversation
	INTL( 3730, "Are you willing to pay the price I ask for?")
	SetYesNo(PRICE2)

YES(PRICE3)
	IF(Gold < 25000)
		Conversation
		INTL( 3731, "It would seem that you can't afford to pay me right now. As much as it pains me to have to "
		"wait longer before I can witness Shadeen's downfall, I cannot help you until you have enough "
		"gold to pay me entirely.")
	ELSE
		TakeGold(25000)
		GiveFlag(__FLAG_PAID_DAMIEN_PRICE, 2)
		Conversation
		INTL( 3732, "Yes, it will do for now I guess. I trust you will return here with the token I asked for once you've "
		"properly disposed of Shadeen.")
	ENDIF
NO(PRICE3)
	Conversation
	INTL( 3733, "I see, then I would ask that you leave this place immediately. I will not waste precious time with the "
	"likes of you!")
YesNoELSE(PRICE3)
	Conversation
	INTL( 3734, "Is this offer more to your liking?")
	SetYesNo(PRICE3)

Command(INTL( 3735, "MEANS"))
""
IF (CheckFlag(__QUEST_DAMIEN_SUBPLOT) >= 3) 
	Conversation
	INTL( 10464, "Now that you have the means to do it, I guess it's all up to you then.") 
ELSEIF(CheckFlag(__FLAG_PAID_DAMIEN_PRICE) >= 1)
	Conversation
	INTL( 3736, "Oh yes, I almost forgot. To kill Shadeen, you will need to perform three tasks. The first will be to locate "
	"and acquire a very special sword. This sword must be incredibly potent if it is to harm Shadeen in any way. "
	"I believe the fabled Blade of Ruin would suffice. For the second task, you will need to seek out the one called "
	"Xanth. He is a follower of Ogrimar, and a practitioner of the dark arts. If you are to use the Blade of Ruin on "
	"Shadeen, it must first be tampered and enchanted, and I believe that he is the one to do it. ")
	IF(CheckItem(__OBJ_LETTER_FROM_DAMIEN_TO_XANTH) == 0)
		IF(CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 1)
			GiveFlag(__QUEST_DAMIEN_SUBPLOT, 2)
			GiveItem(__OBJ_LETTER_FROM_DAMIEN_TO_XANTH)
			Conversation
			INTL( 3737, "Seek him out and show him this letter. {You} {receive} {a} {tightly} {wrapped} {scroll.} ")
		ENDIF		
	ELSE
		Conversation
		INTL( 3738, "Seek him out and show him the letter I gave you earlier. ")
	ENDIF
	Conversation
	INTL( 3739, "As for the last task, it will simply be to strike down Shadeen from where she stands. Once you have completed "
	"all three, return here and I may yet find a future use for your services.")
ELSEIF(CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 1)
	Conversation
	INTL( 3740, "I will not give you the means to kill Shadeen until you agree to pay the \"price\" I require.")
ELSE
	Conversation
	INTL( 624, "What are you talking about?")
ENDIF

Command(INTL( 3741, "BLADE OF RUIN"))
""
IF (CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 2)
	Conversation
	INTL( 3742, "Yes, that is the sword you will need to kill Shadeen.")
ELSE
	Conversation
	INTL( 3743, "I don't know what you're talking about.")
ENDIF

Command(INTL( 3744, "XANTH"))
""
IF (CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 2)
	Conversation
	INTL( 3745, "Unfortunately, I am not aware of his whereabouts. As you are a resourceful person, I have no doubt that "
	"you will succeed in finding him, even with my lack of information.")
ELSE
	Conversation
	INTL( 3743, "I don't know what you're talking about.")
ENDIF

Command(INTL( 3746, "PRICE"))
""
IF (CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 1)  
	IF(CheckFlag(__FLAG_PAID_DAMIEN_PRICE) >= 1)
		Conversation
		INTL( 11659, "You have already paid the price. Now, I can give you the \"means\" to accomplish the task that lies ahead.") 
	ELSE
		Conversation
		INTL( 3747, "I want for three things only: a \"gift\", a \"token\", and last but not least, \"abandon\".")
	ENDIF 
ELSE
	Conversation
	INTL( 624, "What are you talking about?")
ENDIF
	
Command5(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "),INTL( 3748, "DICK "))
INTL( 3749, "You appear troubled...")
BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 3750, "Safe travels to you.")
BREAK

Default
INTL( 3751, "That could be true.")

EndTalk

}

