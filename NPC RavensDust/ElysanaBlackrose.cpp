/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "ElysanaBlackrose.H"

ElysanaBlackrose::ElysanaBlackrose()
{}

ElysanaBlackrose::~ElysanaBlackrose()
{}

extern NPCstructure::NPC ElysanaNPC;

void ElysanaBlackrose::Create( void )
{
      npc = ( ElysanaNPC );
      SET_NPC_NAME( "[2947]Elysana Blackrose" );  
      npc.InitialPos.X = 1561;
      npc.InitialPos.Y = 2471;
      npc.InitialPos.world = 0;
}

void ElysanaBlackrose::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{

CONSTANT THEPOTION = 1;
CONSTANT GEMSTONE = 2;
CONSTANT PROMISE = 3;
CONSTANT INGREDIENT = 4;
CONSTANT KEY_RIDDLE = 5;
CONSTANT KEY_RIDDLE2 = 6;

InitTalk

Begin
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) >= 1)
	Conversation
	FORMAT(INTL( 4957, "Is it truly you, %s? I have been expecting you."), USER_NAME)
ELSE
	IF (TFCTime::IsDay())
		Conversation
		INTL( 4958, "Lovely day, isn't it?")
	ELSE
		Conversation
		INTL( 4959, "A strange time to come knocking... No matter, I'm always up at "
		"this hour. I do my best work at night.")
	ENDIF
ENDIF

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 4960, "I am Elysana Blackrose, sorceress of Raven's Dust.")

Command2(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"))
INTL( 4961, "I do not have any specific occupation. I am devoted to my studies of "
"the \"mystical\" \"arts\" and I spend most of my spare time with my books. If you could " 
"help me, I would be grateful if you could fetch some \"ingredients\". Also, "
"I may have a \"green\" \"gemstone\" in which you might be interested if "
"you intend to talk with tree people.")

Command(INTL( 2076, "INGREDIENT"))
""
IF ((CheckItem(__OBJ_POUCH_OF_WOODY_NIGHTSHADE) >= 1) && (CheckItem(__OBJ_POUCH_OF_BLUE_COHOSH) >= 1) && (CheckItem(__OBJ_POUCH_OF_WITCH_HAZEL) >=1))
	Conversation
	FORMAT(INTL( 4962, "You were able to gather all three ingredients, %s? That's nice. Now, would you like "
	"to trade them to me?"), USER_NAME) 
	SetYesNo(INGREDIENT) 
ELSE
	Conversation
	FORMAT(INTL( 4963, "%s? I am awfully busy. You'd be an angel if you could get some ingredients for me. I need "
	"some Woody Nightshade, a little pinch of Blue Cohosh and perhaps a tiny bit of "
	"Witch Hazel."), USER_NAME) 
ENDIF

YES(INGREDIENT)
IF ((CheckItem(__OBJ_POUCH_OF_WOODY_NIGHTSHADE) >= 1) && (CheckItem(__OBJ_POUCH_OF_BLUE_COHOSH) >= 1) && (CheckItem(__OBJ_POUCH_OF_WITCH_HAZEL) >=1))
	TakeItem(__OBJ_POUCH_OF_WOODY_NIGHTSHADE)
	TakeItem(__OBJ_POUCH_OF_BLUE_COHOSH)
	TakeItem(__OBJ_POUCH_OF_WITCH_HAZEL)
    GiveItem(__OBJ_BLACK_LIZARDSKIN_BOOTS)
	Conversation
	INTL( 4964, "Ah, you found the ingredients I needed. If you find more of these 3 ingredients, feel free to "
	"come back and I'll trade them for a pair of black lizardskin boots.")
	;int nExpReward = 8000; 	
	GiveXP(nExpReward)
	Conversation
	FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), nExpReward)
ELSE
	Conversation
	INTL( 4965, "I am sorry but you are missing an ingredient or two, dear.")
ENDIF

NO(INGREDIENT)
Conversation
INTL( 3962, "Darn it!")

YesNoELSE(INGREDIENT)
Conversation
INTL( 4966, "Uh? I guess that meant no.")

Command(INTL( 4271, "CUTHANA"))
INTL( 4967, "The herb you seek does not grow on the surface of the world, but rather in the deepest "
"caves of this island. And no, before you ask, I don't have any to sell.")

Command(INTL( 4968, "MYSTICAL ARTS"))
INTL( 4969, "They are my passion in life. I have been gifted since the day I was born. It would be a pleasure "
"to share my \"knowledge\" with you.")

Command(INTL( 1381, "KNOWLEDGE"))
INTL( 7554, "I have learned many spells over the years, two of which I have designed myself. These two I would "
"be willing to \"teach\" you.")

Command2(INTL( 496, "TEACH"), INTL( 495, "LEARN"))
INTL( 7555, "Here they are then.")
CreateSkillList
	AddTeachSkill (__SPELL_MINOR_COMBAT_SENSE, 13, 23808)
	AddTeachSkill (__SPELL_MANA_BURST, 15, 40192)
SendTeachSkillList

CmdAND(INTL( 4991, "GREEN"),INTL( 4992, "GEMSTONE")) 
INTL( 4993, "Perhaps you might be interested in buying a green gemstone of the Forest Spirit. "
"It will only cost you 20000 gold pieces, do you want to buy one?")
SetYesNo(GEMSTONE) 

YES(GEMSTONE)
IF (Gold >= 20000)
	TakeGold(20000)
	GiveItem(__OBJ_GREEN_GEMSTONE)
	Conversation
	INTL( 4994, "Good.")	
ELSE
	;int nCurrentGold = 20000 - Gold; 
	Conversation
	FORMAT(INTL( 4995, "You do not have enough gold. You need %u more."), nCurrentGold) 
ENDIF

NO(GEMSTONE)
Conversation
INTL( 4893, "Fine.")

YesNoELSE(GEMSTONE)
Conversation
INTL( 4996, "I'll consider this as a no.")

Command(INTL( 4992, "GEMSTONE"))
INTL( 4997, "What gemstone?")

Command(INTL( 1794, "ROYAL KEY"))
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) // Will only talk about keys with a Champion of Light.
	SWITCH(CheckFlag(__QUEST_ROYAL_KEY3))
		CASE(0) // Hasn't asked PC to bring ether yet.
			FORMAT(INTL( 4998, "Before I help you, %s, I'd like you to bring me some \"ether\"."), USER_NAME)
			GiveFlag(__QUEST_ROYAL_KEY3,1)
		ENDCASE
		CASE(1) // Waiting for PC to bring ether
			Conversation
			INTL( 4999, "Bring me some \"ether\", then we can talk about the royal keys, all right?")
		ENDCASE
		CASE(2) // Has told PC to go ask Zhakar for the Royal Key #3
			Conversation
			INTL( 5000, "Um... I'm really sorry, you'll have to ask you to go looking for the key "
			"so far, but... *ahem* well, Zhakar has it...")
		ENDCASE
		OTHERWISE
			Conversation
			INTL( 5001, "Those royal keys... Many people are asking about them, lately... Speaking of keys, "
			"would you like to hear a riddle?")
			SetYesNo(KEY_RIDDLE)
		ENDCASE
	ENDSWITCH
ELSE
	Conversation
	INTL( 5002, "I would only talk about the royal keys to a \"Champion of Light\". Gain some reputation "
	"and perhaps we can discuss this matter again.")
ENDIF

YES(KEY_RIDDLE)
	Conversation
	INTL( 5003, "Can you name a key that doesn't open a door?")
	SetYesNo(KEY_RIDDLE2)

NO(KEY_RIDDLE)
	Conversation
	INTL( 5004, "Never mind, then.")

YesNoELSE(KEY_RIDDLE)
	Conversation
	INTL( 1521, "Yes or no?")
	SetYesNo(KEY_RIDDLE)

YES(KEY_RIDDLE2)
	Conversation
	INTL( 5005, "Good for you. You're smarter than you look.")

NO(KEY_RIDDLE2)
	Conversation
	INTL( 5006, "Well, there's actually more than just one, but a MONKEY is a good example. Get it? "
	"Mon-KEY? Ah, never mind, you just don't have a sense of humor.")

YesNoELSE(KEY_RIDDLE2)
	Conversation
	INTL( 5007, "Um... whatever you say.")

Command(INTL( 5008, "CHAMPION OF LIGHT"))
INTL( 5009, "Champions of Light are men and women who have dedicated themselves to the cause of pure good. "
"They must take a special oath and have done far more good deeds than evil deeds.")

Command2(INTL( 5010, "ETHER"),INTL( 5011, "BLUISH LIQUID"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY3) == 1) // If PC has been asked to bring back ether...
	IF (CheckItem(__OBJ_FLASK_OF_BLUISH_LIQUID) > 0) // ...and actually has some:
		TakeItem(__OBJ_FLASK_OF_BLUISH_LIQUID)
		Conversation
		FORMAT(INTL( 5012, "Thank you, %s. "),USER_NAME)
		Conversation
		INTL( 5013, "Now, wouldn't you rather receive a potion of serious healing rather than pursue that silly key?")
		SetYesNo(THEPOTION)
	ELSE // ...but doesn't have ether:
		Conversation
		INTL( 5014, "If you ever get some ether, I'll make you a special potion with it. If you've never seen what ether looks like, it's a \"bluish\" \"liquid\".")
	ENDIF
ELSE // PC hasn't yet been asked to bring back ether.
	Conversation
	INTL( 5015, "Ether has a bluish tint. It's very useful in brewing magical potions.") 	
ENDIF

YES(THEPOTION)
Conversation
INTL( 5016, "Excellent. Here's your potion!")
GiveItem(__OBJ_SERIOUS_HEALING_POTION)

NO(THEPOTION)
Conversation
INTL( 5017, "Ah... Well, if you *really* want that key... It's just... I didn't think you'd be "
"able to find me ether, so... well... *ahem* I kind of sold it to Zhakar... But if you "
"go see him and tell him I sent you, perhaps he'll accept to give you a copy? I really "
"hope so. {You} {have} {been} {awarded} {5,000} {experience} {points.}")
GiveFlag(__QUEST_ROYAL_KEY3, 2)
GiveXP(5000)

YesNoELSE(THEPOTION)
Conversation
INTL( 5018, "Eh? I don't get it.")

Command(INTL( 5019, "BITCH"))
INTL( 5020, "Hey, watch your language!") BREAK

CmdAND(INTL( 3862, "BANE"),INTL( 3863, "BLACKBLOOD"))
INTL( 5021, "Not much can be said about him...")

Command(INTL( 1492, "DESERT"))
INTL( 5022, "It is said that somewhere beneath the desert lies an underground dungeon "
"where treasures and mysteries can be found.")

Command(INTL( 4124, "POISON"))
""
SWITCH(CheckFlag(__QUEST_ELYSANA_MAKE_POISON))
	CASE(0)
		IF (CheckFlag(__QUEST_SEEK_SHADEEN) >= 1) // If PC has been given mission to poison Crowbanner:
			Conversation
			INTL( 5023, "I... I don't like being involved with people like you, but I can tell you're not "
			"going to take no for an answer. I'll do it, but you must promise never to tell "
			"anyone about this. Agreed?")
			SetYesNo(PROMISE)
		ELSE
			Conversation
			INTL( 5024, "I don't do poisons, sorry.")
		ENDIF
	ENDCASE
	CASE(1)
		IF ((CheckItem(__OBJ_KRAANIAN_EYES) >= 1) && (CheckItem(__OBJ_SAPPHIRE_GEM) >= 1) && (CheckItem(__OBJ_WAX_APPLE) >= 1))
			Conversation
			INTL( 5025, "Very well, let me prepare your poison and come back in an hour.")
			TakeItem(__OBJ_KRAANIAN_EYES)
			TakeItem(__OBJ_SAPPHIRE_GEM)
			TakeItem(__OBJ_WAX_APPLE)
			GiveFlag(__QUEST_ELYSANA_MAKE_POISON,2)
			GiveFlag(__QUEST_TIMER_MAKE_POISON,1 HOUR TDELAY)
		ELSE
			Conversation
         INTL( 5026, "Bring me the ingredients I've already told you about: some \"Kraanian\" \"eyes\", a \"wax\" \"apple\" "
         "and a \"sapphire\" \"gem\". At least one of each, or I can't prepare the poison.")
		ENDIF
	ENDCASE
	CASE(2)
		IF (CurrentRound < (CheckFlag(__QUEST_TIMER_MAKE_POISON)-72000)) // There was a server crash messing up the timer:
			IF (CurrentRound > 72000) // ...and server crashed more than an hour ago:
				Conversation
				INTL( 5027, "Okay, here's your poison. It looks like an apple, but whoever bites it "
				"will become gravely ill. Sorry, I don't make poisons that kill. Now take "
				"it and go before people start asking questions.")
				GiveItem(__OBJ_POISON_APPLE)
				RemFlag(__QUEST_ELYSANA_MAKE_POISON)
				RemFlag(__QUEST_TIMER_MAKE_POISON)
			ELSE //...server crashed, but less than an hour ago:
				;int nTimeLeft = (72000 - CurrentRound) / (1 MINUTE);
				Conversation
				FORMAT(INTL( 5028, "Sorry, I made a mess and had to start all over. Please come back in %u minutes."),nTimeLeft)
			ENDIF
		ELSE // Server hasn't crashed, everything proceeding as normal...
			IF ((CheckFlag(__QUEST_TIMER_MAKE_POISON) < (CurrentRound + (1 MINUTE))) && (CheckFlag(__QUEST_TIMER_MAKE_POISON) != 0))
				Conversation
				INTL( 5029, "Okay, here's your poison. It looks like an apple, but whoever bites it "
				"will become gravely ill. Sorry, I don't make poisons that kill. Now take "
				"it and go before people start asking questions.")
				GiveItem(__OBJ_POISON_APPLE)
				RemFlag(__QUEST_ELYSANA_MAKE_POISON)
				RemFlag(__QUEST_TIMER_MAKE_POISON)
			ELSE
				;int nTimeLeft = ((CheckFlag(__QUEST_TIMER_MAKE_POISON) - CurrentRound) / (1 MINUTE));
				Conversation
				FORMAT(INTL( 5030, "The poison isn't ready yet, sorry. Please come back in %u minutes."),nTimeLeft)
			ENDIF
		ENDIF
	ENDCASE
ENDSWITCH

YES(PROMISE)
   IF (CheckFlag(__QUEST_KRAANIAN_EYES) == 0)  // Used for the mini-Quest
      GiveFlag(__QUEST_KRAANIAN_EYES, 1)       // of gathering the eyes. 
   ENDIF

   IF (CheckFlag(__QUEST_WAX_APPLE) == 0)   // Used for the mini-Quest
      GiveFlag(__QUEST_WAX_APPLE, 1)        // of gathering the wax apple. 
   ENDIF

   IF (CheckFlag(__QUEST_SAPPHIRE_GEM) == 0)   // Used for the mini-Quest
      GiveFlag(__QUEST_SAPPHIRE_GEM, 1)        // of gathering the sapphire gem.
   ENDIF
	GiveFlag(__QUEST_ELYSANA_MAKE_POISON,1)
	Conversation
   INTL( 5031, "Very well. Then I need you to gather some components for me: some \"Kraanian\" \"eyes\", "
   "a \"wax\" \"apple\", and a \"sapphire\" \"gem\". Then come back and ask me again about your \"poison\".")

NO(PROMISE)
	Conversation
	INTL( 5032, "Then, I really cannot help you.")

YesNoELSE(PROMISE)
	Conversation
	INTL( 5033, "This answer is unacceptable. You must answer by a \"yes\" or a \"no\"!")
	SetYesNo(PROMISE)

Command(INTL( 700, "SPELL"))
""
IF (USER_INT < 60 )
    Conversation
    INTL( 5034, "You do not look gifted enough to learn spells worth of being taught.")
ELSE
    Conversation
    INTL( 5035, "I sense that your mind is quite swift. Swift enough to learn powerful "
    "spells? Perhaps. But that is not for me to judge. You alone will have to "
    "prove yourself worthy.")
ENDIF

CmdAND(INTL( 4160, "KRAANIAN"),INTL( 3955, "EYE"))
""
IF (CheckFlag(__QUEST_KRAANIAN_EYES) == 0)
   Conversation
   INTL( 5036, "I don't see for what purpose would you need some kraanian eyes.") 
ELSE
   Conversation
   INTL( 5037, "I think that perhaps the wizard Zhakar has some left since most of his "
   "studies are based on the kraanian species.")
ENDIF

CmdAND(INTL( 5038, "WAX"),INTL( 4648, "APPLE"))
""
IF (CheckFlag(__QUEST_WAX_APPLE) == 0)
   Conversation
   INTL( 5039, "I think that a wax apple is a beautiful decoration on a table.")
ELSE
   Conversation
   INTL( 5040, "Where you could get one? Perhaps the king's advisor, Samuel, could help "
   "you. I've seen some of his creations and I must say that they are "
   "exquisite.")
ENDIF

Command(INTL( 5041, "SAPPHIRE"))
""
IF (CheckFlag(__QUEST_SAPPHIRE_GEM) == 0)
   Conversation
   INTL( 5042, "Sapphire gem? That's my birthday's rock.")
ELSE
   Conversation
   INTL( 5043, "If there's somebody on the island who could have some sapphire gems, "
   "it's King Theodore XIII. I doubt he'd give you some though.")
ENDIF

Command(INTL( 502, "TRAIN"))
INTL( 5044, "Do I look like your personal spiritual trainer? If you wish to train "
"yourself in the mystical arts, you should think about reading a few "
"books.") 

CmdAND(INTL( 5045, "FORTUNE"),INTL( 5046, "TELLER"))
INTL( 5047, "Some inhabitants think that I am a fortune teller. How far they are from "
"the truth! I have, however, the ability to \"foresee\" a few things sometimes.")

Command(INTL( 754, "THEODORE"))
INTL( 5048, "King Theodore's kingdom of Goldmoon is falling apart.") 

Command(INTL( 5049, "FORESEE"))
FORMAT(INTL( 5050, "I foresee that you shall achieve a greater state of mind and body in %u more experience points."),XP_TO_LEVEL)

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 5051, "I should turn you into a fly and change myself into a frog so I can eat you.")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
""
IF (TFCTime::IsDay())
	Conversation
    INTL( 1075, "Farewell.")
    BREAK
ELSE
	Conversation
    INTL( 5052, "We never know what we may encounter in the heart of the night.") 
    BREAK
ENDIF

Default
INTL( 4439, "Perhaps I should give a thought about that.") 

EndTalk
}
//////////////////////////////////////////////////////////////////////////////////////////
void ElysanaBlackrose::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_MINOR_COMBAT_SENSE, 13, 23808)
         TEACH_SKILL(__SPELL_MANA_BURST, 15, 40192)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE