// ChamberlainThomar.cpp: implementation of the ChamberlainThomar class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "ChamberlainThomar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ChamberlainThomar::ChamberlainThomar()
{}

ChamberlainThomar::~ChamberlainThomar()
{}

extern NPCstructure::NPC ChamberlainThomarNPC;

//////////////////////////////////////////////////////////////////////////////////////////
void ChamberlainThomar::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Chamberlain Thomar
//
{
    npc = ChamberlainThomarNPC;
    SET_NPC_NAME( "[2937]Chamberlain Thomar" );
    npc.InitialPos.X = 1450;//2833;//1417; // Castle in Silversky
    npc.InitialPos.Y = 2358;//227;//2340; // Castle in Silversky
	npc.InitialPos.world = 0;//4;//0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void ChamberlainThomar::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Chamberlain Thomar
//
{

CONSTANT GET_CUTHANA = 1;
CONSTANT OATH = 2;
CONSTANT QUEST = 3;

InitTalk

Begin
INTL( 4538, "Welcome to King Theodore's castle. May I be of assistance?")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 4539, "I am Chamberlain Thomar. I manage the daily affairs of this castle. Not a thing "
"happens here that I do not know about. How may I help you?")

Command2(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"))
INTL( 4540, "I work here as chamberlain of the castle. I attend all domestic matters within "
"the castle. One could say I am the eyes and ears of these walls. I am also "
"the one you must ask if you wish an \"audience\" with our good king.")

Command2(INTL( 4541, "PRINCESS"),INTL( 1005, "DELILAH"))
INTL( 4542, "The poor princess is most distraught, lately. You see, her mentor, Bishop Rikken "
"Crowbanner, has fallen deathly ill, and she has become very quiet and depressed "
"as a result. Perhaps I could help you?")

Command(INTL( 4271, "CUTHANA"))
""
IF (CheckFlag(__QUEST_CUTHANA) >= 1)
	Conversation
	INTL( 4543, "You can find that herb somewhere in a deep, deep dungeon, I hear. The trick is "
	"finding someone who'll tell you which one, when to go, etc. Sadly, I cannot "
	"help you with that.")
ELSE
	Conversation
	INTL( 4544, "If you find the herb, be sure to give it to Princess Delilah.")
ENDIF

Command3(INTL( 4545, "BISHOP"),INTL( 4546, "RIKKEN"),INTL( 4547, "CROWBANNER"))
INTL( 4548, "A very holy man, he is. All priests and priestesses under his tutelage demonstrate "
"the utmost loyalty to him and his ideals. That is a rare thing, nowadays.")

Command4(INTL( 509, "BALORK"),INTL( 543, "CURSE"),INTL( 510, "BRAND"),INTL( 1001, "MARK"))
""
IF (CheckFlag(__QUEST_ISLAND_ACCESS) == 0) // If the user isn't supposed to be here:
	Conversation
	INTL( 4549, "An interesting tale you spin. It means little to me, however.")
ELSE
	Conversation
	INTL( 4550, "You tell a fascinating story, my friend, one that I would not believe "
	"from just anyone. But your eyes tell me the truth about your trials, and "
	"I would like to \"help\" you.")
ENDIF

Command2(INTL( 4363, "MONSIGNOR"),INTL( 4364, "DAMIEN"))
INTL( 4551, "Monsignore Damien is a most evil man, I'm told. Someone once told me he was still alive, "
"hiding in some hold and biding his time until he could exact his revenge. I'm a little "
"unclear as to the details, I'm afraid.")

Command(INTL( 554, "HELP"))
""
IF (CheckFlag(__QUEST_ISLAND_ACCESS) == 0) // If the user isn't supposed to be here:
	Conversation
	INTL( 4552, "Sorry, I cannot do that.")
ELSE
	IF (CheckGlobalFlag(__QUEST_BISHOP_ILLNESS) == 0)
		Conversation
		INTL( 4553, "In truth, I can do little for you myself, but Princess Delilah surely could, "
		"if she was not so caught up in grief over the bishop's illness. Perhaps if "
		"you could help cure what ails him. That would be a \"noble\" \"gesture\".")
	ELSE
		Conversation
		INTL( 4554, "I am uncertain as to what kind of help you need, and I'm rather busy right "
		"at this moment... Perhaps later.")
	ENDIF
ENDIF

Command3(INTL( 4545, "BISHOP"),INTL( 4546, "RIKKEN"),INTL( 4547, "CROWBANNER"))
""
IF (CheckGlobalFlag(__QUEST_BISHOP_ILLNESS) == 0) // If the bishop is ill:
	Conversation
	INTL( 4555, "This is terrible! Bishop Crowbanner is ill again! This MUST stop!")
ELSE // Bishop is in good health.
	Conversation
	INTL( 4556, "He is in good health, at the moment, but who knows when he will have a relapse... "
	"It keeps happening to him, the poor man. This is terrible, I tell you.")
ENDIF

Command(INTL( 4557, "NOBLE GESTURE"))
""
IF (CheckFlag(__QUEST_ISLAND_ACCESS) == 0) // If PC isn't supposed to be here:
	Conversation
	INTL( 4558, "There are so few noble people, nowadays...")
ELSE
	IF (CheckGlobalFlag(__QUEST_BISHOP_ILLNESS) == 0) // If Crowbanner is ill...
		Conversation
		INTL( 4559, "There is a special herb, \"cuthana\", that has some miraculous healing properties. "
		"Perhaps if you could find some, it might help restore Bishop Crowbanner's health. "
		"Would you undertake such a quest?")
		SetYesNo(GET_CUTHANA)
	ELSE // No quest to give to PC at present (Crowbanner healthy)
		Conversation
		INTL( 4560, "Would that there was a hero in this land, to rally the people and restore "
		"the faith of our people in the monarchy. *sigh*")
	ENDIF
ENDIF

YES(GET_CUTHANA)
IF (CheckFlag(__QUEST_CUTHANA) >= 3) // If PC has already done the Cuthana Quest:
	Conversation
	INTL( 4561, "I am loathe to ask you to do this again, but for the sake of the Bishop, I "
	"fear that I must. Thank you for your dedication. May Artherk light your path.")
ELSE // PC has never done the Cuthana Quest:
	Conversation
	INTL( 4562, "Marvelous! Please give the cuthana herbs to Princess Delilah upon your return. "
	"Good luck. May Artherk walk with you.")
ENDIF
GiveFlag(__QUEST_CUTHANA, 1)

NO(GET_CUTHANA)
Conversation
INTL( 4563, "That is unfortunate, but I understand you may have more important matters to attend. "
"Artherk watches over you.")

YesNoELSE(GET_CUTHANA)
Conversation
INTL( 4564, "I see.")

CmdAND(INTL( 1072, "KING"),INTL( 754, "THEODORE"))
INTL( 4565, "I hope you are not thinking ill of our great king!")

Command(INTL( 1794, "ROYAL KEY"))
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) < 1) // If PC is not a Champion of Light
	Conversation						 
	INTL( 7505, "You must be a \"Champion\" \"of\" \"Light\" else I will not help you.") 
ELSE // PC is a Champion of Light
	IF (CheckFlag(__QUEST_ROYAL_KEY2) <= 4) // Terwin hasn't told the PC about Thomar's key yet.
		Conversation
		INTL( 4566, "Such keys are very rare.")
	ELSEIF (CheckFlag(__QUEST_ROYAL_KEY2) == 5) // Terwin's spilled the beans, so to speak. PC knows Thomar has a key.
		IF (USER_KARMA >= 100) // If the PC has high enough karma...
			Conversation
			INTL( 4567, "I find you of remarkable character, and could indeed lend you my key, but I "
			"would first require that you swear an Oath of Worthiness, by which you promise "
			"to never again perform an evil deed. Will you do so?")
			SetYesNo(OATH)
		ELSE // PC is told to first become more worthy.
			Conversation
			INTL( 4568, "Yes, it's true, I have such a key, but until the day you have become a more worthy "
			"individual, I cannot trust you enough to discuss this matter with you.")
		ENDIF
	ELSEIF (CheckFlag(__QUEST_ROYAL_KEY2) == 6) // PC ordained Champion of Light, hasn't received Royal Key #2
		Conversation
		INTL( 4569, "Very well. Here is the key I promised.")
		GiveFlag(__QUEST_ROYAL_KEY2,7)
		GiveItem(__OBJ_ROYAL_KEY_2)
	ELSE // PC has received Royal Key #2 already.
		Conversation
		INTL( 4570, "You already received the key once. That should have been enough. ")
		IF (CurrentRound < (CheckGlobalFlag(__GLOBAL_QUEST_ROYAL_KEY2_TIMER)-72000)) // There was a server crash messing up the timer:
			IF (CurrentRound > 72000) // ...and server crashed more than an hour ago:
				Conversation
				INTL( 4571, "Very well, here is another one... Please don't lose it, this time.")
				GiveFlag(__QUEST_ROYAL_KEY2, CheckFlag(__QUEST_ROYAL_KEY2)+1)
				GiveItem(__OBJ_ROYAL_KEY_2)
				GiveGlobalFlag(__GLOBAL_QUEST_ROYAL_KEY2_TIMER,0)
			ELSE // PC won't get another key for a while.
				Conversation
				FORMAT(INTL( 4572, "Ask me again in %u hours, not a MINUTE before!"),CheckFlag(__QUEST_ROYAL_KEY2)-5)
				GiveGlobalFlag(__GLOBAL_QUEST_ROYAL_KEY2_TIMER, CheckFlag(__QUEST_ROYAL_KEY2)-5 HOURS TDELAY)
			ENDIF
		ELSEIF ((CheckGlobalFlag(__GLOBAL_QUEST_ROYAL_KEY2_TIMER) <= CurrentRound) && (CheckFlag(__GLOBAL_QUEST_ROYAL_KEY2_TIMER) != 0)) // PC can receive another key again.
			Conversation
			INTL( 4571, "Very well, here is another one... Please don't lose it, this time.")
			GiveFlag(__QUEST_ROYAL_KEY2, CheckFlag(__QUEST_ROYAL_KEY2)+1)
			GiveItem(__OBJ_ROYAL_KEY_2)
			GiveGlobalFlag(__GLOBAL_QUEST_ROYAL_KEY2_TIMER,0)
		ELSE // PC won't get another key for a while.
			Conversation
			FORMAT(INTL( 4572, "Ask me again in %u hours, not a MINUTE before!"),CheckFlag(__QUEST_ROYAL_KEY2)-5)
			GiveGlobalFlag(__GLOBAL_QUEST_ROYAL_KEY2_TIMER, CheckFlag(__QUEST_ROYAL_KEY2)-5 HOURS TDELAY)
		ENDIF
	ENDIF
ENDIF

Command2(INTL( 4573, "CHAMPION"),INTL( 4574, "LIGHT"))
INTL( 4575, "Champions of Light are individuals who have sworn to uphold the good cause. Only a select few "
"are worthy of this title, and I am one of those who can bestow it upon you. In order to become "
"such a person, you must \"swear\" \"fealty\" by taking an \"Oath\" \"of\" \"Worthiness\".")

Command2(INTL( 4576, "SWEAR FEALTY"),INTL( 4577, "OATH OF WORTHINESS"))
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) 
	Conversation
	FORMAT(INTL( 10444, "You've already taken the oath of worthiness, %s."), USER_NAME) 
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1) 
	Conversation
	FORMAT(INTL( 10445, "Your reputation is tainted with questionable acts and shady acquaintances. I do not "
	"think that you will ever be able to redeem yourself enough to swear the Oath of "
	"Worthiness. I pity you %s, for the path you've chosen will inevitably lead to your demise."), USER_NAME) 				
ELSE
	Conversation
	INTL( 4578, "So you wish to become a Champion of Light? ")
	IF (USER_KARMA >= 100) // If the PC has high enough karma...
		Conversation
		INTL( 4579, "I find you of remarkable character, and could indeed make you swear the Oath of "
		"Worthiness, by which you promise to never again perform an evil deed. Will you do so?")
		SetYesNo(OATH)
	ELSE // If the PC's karma is too low...
		Conversation
		INTL( 4580, "I find your character somewhat lacking, although I have no doubt your desire to improve "
		"may change that. Perhaps later, once you have redeemed your soul through good deeds...")
	ENDIF
ENDIF 

YES(OATH)
Conversation
INTL( 4581, "Excellent! You are now a Champion of Light! We will spread the word about your choice. "
"This will undoubtedly close you some doors with some individuals, but will open others.")
GiveFlag(__QUEST_FIXED_ALIGNMENT, 1)
IF (CheckFlag(__QUEST_ROYAL_KEY2) == 5) // If this is the first time taking the oath:
	GiveFlag(__QUEST_ROYAL_KEY2, 6)
	GiveXP(5000)
	Conversation
	INTL( 4582, "{You} {have} {been} {awarded} {5,000} {experience} {points.}")
ENDIF

NO(OATH)
INTL( 4583, "You need more time to think, that's understandable. Stepping into the path of the light "
"is no small decision. Take all the time you need.")

YesNoELSE(OATH)
INTL( 4584, "I need a clear answer, yes or no?")
SetYesNo(OATH)

Command(INTL( 4585, "AUDIENCE"))
""
IF (CheckFlag(__FLAG_AUDIENCE_W_KING) == 1)
   Conversation
   INTL( 4586, "You do not need my approval, you can already have an audience with "
   "our king.")
ELSEIF (CheckFlag(__FLAG_TITLE_MORDRICK) == 2)
   Conversation
   FORMAT(INTL( 4587, "You seek an audience with our good king? I see that you have been "
   "accepted by Mordrick Warstone... thus, I give you the right to "
   "an audience with King Theodore XIII. %s, remember to bow down "
   "in front of our Majesty."), USER_NAME) 
   GiveFlag(__FLAG_AUDIENCE_W_KING, 1) 
ELSEIF (CheckFlag(__FLAG_CHAMBERLAIN_TASK) == 1)
   Conversation
   INTL( 4588, "You seek an audience with our good king? Since you've successfully "
   "accomplished the task I had set for you, I hereby allow you to have "
   "an audience with King Theodore XIII. Remember to bow down in front "
   "of our Majesty.")
   GiveFlag(__FLAG_AUDIENCE_W_KING, 1)  
ELSE
   Conversation
   INTL( 4589, "You seek an audience with his Majesty? Know that I cannot allow everybody "
   "to have an audience with the king as his time is precious. Therefore, "
   "I have prepared a \"quest\" for those who would like to speak with the king.")
ENDIF


Command(INTL( 896, "QUEST"))
""
IF (CheckFlag(__FLAG_CHAMBERLAIN_TASK) == 1)
   Conversation
   INTL( 4590, "You have already completed the quest I had set for you.")
ELSE
   IF ((CheckNPCFlag(__NPC_THOMAR_FLAG_DELAY) < CurrentRound) && (CheckNPCFlag(__NPC_THOMAR_FLAG_DELAY) != 0))
           GiveNPCFlag(__NPC_THOMAR_FLAG_DELAY, 0)
   ENDIF
   
   // User is (or has been) involved in the Quest.
   IF (CheckFlag(__QUEST_FLAG_THOMAR_VALIDATION) != 0)
      IF ((CheckNPCFlag(__NPC_THOMAR_FLAG_DELAY) == CheckFlag(__QUEST_FLAG_THOMAR_VALIDATION)) && (CheckNPCFlag(__NPC_THOMAR_FLAG_DELAY) != 0))
         IF (CheckFlag(__FLAG_COUNTER_THOMAR) < 10) 
         // User has not completed the Quest yet but still has time.  
            ;int nTimeLeft = (CheckNPCFlag(__NPC_THOMAR_FLAG_DELAY) - CurrentRound) / 1200; 
            Conversation
            FORMAT(INTL( 4591, "You still have to slay %u more Rogue Mages! You have %u minutes left to complete "
            "your quest."), 10 - CheckFlag(__FLAG_COUNTER_THOMAR), nTimeLeft) 
         ELSE
         // User has completed the Quest in time. 
            Conversation
            INTL( 4592, "Great job! I hereby give you the right to an audience with "
            "our king. Whenever you need to speak to the king in the future, "
            "come to me and ask for another \"audience\".")
            GiveFlag(__FLAG_AUDIENCE_W_KING, 1)
            GiveFlag(__FLAG_CHAMBERLAIN_TASK, 1)
            RemFlag(__FLAG_COUNTER_THOMAR)
            RemFlag(__QUEST_FLAG_THOMAR_VALIDATION)
            GiveNPCFlag(__NPC_THOMAR_FLAG_DELAY, 0)    
         ENDIF
      ELSE
      // User did not make it in time.  
         Conversation
         FORMAT(INTL( 4593, "I am truly sorry but you are too late, %s! If you wish to, you "
                "could try again the \"quest\" again."), USER_NAME)
         RemFlag(__QUEST_FLAG_THOMAR_VALIDATION)
         RemFlag(__FLAG_COUNTER_THOMAR) 
      ENDIF
   ELSE // User has NOT been involved in the Quest. 
      IF (CheckNPCFlag(__NPC_THOMAR_FLAG_DELAY) != 0)
      // Quest is running currently. 
         Conversation
         INTL( 4594, "I apologize but somebody else is already trying to do the quest.")
      ELSE
      // Quest is not running currently. Perhaps the user wants to give it a shot?
         Conversation
         INTL( 4595, "Do you want to give it a try? You'll have to slay at least 10 Rogue Mages within "
         "30 minutes.")
         SetYesNo(QUEST) 
      ENDIF
   ENDIF
ENDIF

YES(QUEST)
Conversation
INTL( 4596, "Good. Now, go slay 10 of the rogue mages around the town who cause "
"a threat to our king.")
GiveNPCFlag(__NPC_THOMAR_FLAG_DELAY, 30 MINUTES TDELAY) 
GiveFlag(__QUEST_FLAG_THOMAR_VALIDATION, CheckNPCFlag(__NPC_THOMAR_FLAG_DELAY) )
RemFlag(__FLAG_COUNTER_THOMAR) // This forces the counter to be resetted. 

NO(QUEST)
Conversation
INTL( 4597, "As you wish, my friend.")

YesNoELSE(QUEST)
Conversation
INTL( 4598, "I'll assume you've said no.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 4564, "I see.") BREAK

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 4599, "Be well. May Artherk protect you.")
BREAK

Default
INTL( 4600, "If that will be all, I must return to my prayers.")

EndTalk

}

