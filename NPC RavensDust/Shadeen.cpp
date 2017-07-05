// Shadeen.cpp: implementation of the Shadeen class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Shadeen.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Shadeen::Shadeen()
{}

Shadeen::~Shadeen()
{}

extern NPCstructure::NPC ShadeenNPC;

void Shadeen::Create(){
	npc = ShadeenNPC;
	SET_NPC_NAME( "[2981]Shadeen the Dagger" );
    npc.InitialPos.X = 0; //Anywhere in Bloodbane's dungeon.
    npc.InitialPos.Y = 0; //She's pretending to be held prisoner
	npc.InitialPos.world = 0; //there, although that's not true...
}


//////////////////////////////////////////////////////////////////////
//  __QUEST_SEEK_SHADEEN
// 	0: Searching for Shadeen
// 	1: Given mission to poison Crowbanner
// 	2: Crowbanner poisoned; tells PC to gain 3 levels and lose 75 pts in karma
//  3: Tells PC about her "secret" (immortality); OPTIONAL VALUE
//  4: PC given mission to rob bank & steal book from Menark
//  5: PC successfully retrieved book from Menark.
//  6: Shadeen retrieved book from PC
//  7: Rewarded PC with Silver Feather
//  8: PC killed Shadeen
//////////////////////////////////////////////////////////////////////
//  __QUEST_GLOBAL_CABALLERO_ALIVE
// 	0: Yes (alive)
// 	1: No (dead)
//////////////////////////////////////////////////////////////////////
//  Shadeen's Quest is to first poison Rikken Crowbanner in order
//  for the PC to prove he's trustworthy. Then, once she trusts
//  him, she gives him a bit of information about the Obsidian
//  Conclave. She then tells him to go perform criminal deeds
//  (potential for more quests there) and will not give him any more 
//  work until he has gone up three levels and has lost at least 75 
//  points in karma. Once the PC has reached that goal, she will treat
//  him as a friend and will confide that she indeed had a relationsip
//  with Kalastor on Arakas, but does not want to return because she
//  is afraid of her own feelings towards him. She may also tell the
//  Player a secret: she's become immortal after drinking the blood
//  of an Elf (!!!). She then gives the PC a new quest: to kill Iago
//  Caballero, a troublesome adventuring knight who has been thwarting
//  her plans for the last few years. Caballero has a potion of 
//  revival, so he is always revived a day or so after being killed,
//  but that usually leaves Shadeen enough time to complete her
//  devious ploys. When the PC returns, she needs him and a "friend"
//  to do a mission for her: one must go to the bank and "fake" a
//  robbery while the other goes to Menark (chronicler) to mug him and
//  retrieve part of a book called "Chronicles of Doom," relating the
//  First Coming. This is a tricky quest: Player A (bank robber) must
//  do his work before Player B starts his, or the guards will swarm
//  Player B and the mission will fail. Upon receiving the book, she
//  will reward Players A and B with an item that she doesn't need
//  but they might find useful, a Silver Feather, a magical item
//  that can be used to perform a teleport ritual to Stoneheim.
//  
//  
//////////////////////////////////////////////////////////////////////


void Shadeen::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	if( target != NULL )
	{
		IF (CheckNPCFlag(__FLAG_SHADEEN_STOLEN_GOLD) > 0)
			GiveGold(CheckNPCFlag(__FLAG_SHADEEN_STOLEN_GOLD))
			RemNPCFlag(__FLAG_SHADEEN_STOLEN_GOLD)
		ENDIF			
		IF (CheckFlag(__QUEST_SEEK_SHADEEN) >= 7)
			GiveFlag( __QUEST_SEEK_SHADEEN, 8)
		ENDIF
		IF (CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 3)
			GiveFlag(__QUEST_DAMIEN_SUBPLOT,4)
			GiveItem(__OBJ_SHADEEN_EARRINGS)
		ENDIF
		IF (USER_KARMA <= (100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
			GiveKarma(2 * ( 500 - USER_KARMA ) / 500)
		ENDIF
		GiveXP(1000)
		SHOUT(INTL( 6227, "D-Darn it... I just hate... dying... again..."))
	}
    CLOSE_HANDLER
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void Shadeen::OnAttack( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	if( target != NULL )
	{
	TFormat FORMAT;
		
	SWITCH( rnd.roll(dice(1, 25)) ) 
		CASE(1)		
			IF (Gold > 0)
				;int nStolenGold =	rnd.roll(dice( 1, (Gold / 2) ) );
				GiveNPCFlag(__FLAG_SHADEEN_STOLEN_GOLD, CheckNPCFlag(__FLAG_SHADEEN_STOLEN_GOLD)+nStolenGold)
				TakeGoldNoEcho( nStolenGold )
				SHOUT(FORMAT(INTL( 6228, "My, oh my! You've dropped %u gold pieces."), nStolenGold))
			ENDIF				
		ENDCASE
		CASE(2)
      IF (CheckItem(__OBJ_LIGHT_HEALING_POTION) > 1)    // Heals 25 hit points
         TakeItem(__OBJ_LIGHT_HEALING_POTION)
			SHOUT(INTL( 6229, "Oh, a potion of healing? Finders keepers! *gulp* Heh! Heh!"))
			IF (NPC_HP != NPC_MAXHP)
				IF ((NPC_HP + 25) > NPC_MAXHP)
					self->SetHP( NPC_MAXHP, true)
				ELSE
					self->SetHP( NPC_HP + 25, true)				
				ENDIF									
			ENDIF			
		ENDIF
		ENDCASE
		CASE(3)
      IF (CheckItem(__OBJ_HEALING_POTION) > 1)  // Heals 50 hit points
         TakeItem(__OBJ_HEALING_POTION)                 
			SHOUT(INTL( 6230, "Oh my, you've dropped a potion, you clumsy oaf! Hmmm. Tasty!"))
			IF (NPC_HP != NPC_MAXHP)
				IF ((NPC_HP + 50) > NPC_MAXHP)
					self->SetHP( NPC_MAXHP, true)
				ELSE
					self->SetHP( NPC_HP + 50, true)				
				ENDIF
			ENDIF
		ENDIF			
		ENDCASE
		OTHERWISE
		ENDCASE
	ENDSWITCH
	}
    CLOSE_HANDLER
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void Shadeen::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	if( target != NULL )
	{	
		TFormat FORMAT;

		SWITCH( rnd.roll(dice(1, 20)) ) 
		CASE(1)		
			IF (Gold > 0)
				;int nStolenGold =	rnd.roll(dice( 1, (Gold / 2) ) );
				GiveNPCFlag(__FLAG_SHADEEN_STOLEN_GOLD, CheckNPCFlag(__FLAG_SHADEEN_STOLEN_GOLD)+nStolenGold)
				TakeGoldNoEcho( nStolenGold )
				SHOUT(FORMAT(INTL( 6228, "My, oh my! You've dropped %u gold pieces."), nStolenGold))
			ENDIF				
		ENDCASE
		CASE(2)
      IF (CheckItem(__OBJ_LIGHT_HEALING_POTION) > 1)    // Heals 25 hit points
         TakeItem(__OBJ_LIGHT_HEALING_POTION)
			SHOUT(INTL( 6229, "Oh, a potion of healing? Finders keepers! *gulp* Heh! Heh!"))
			IF (NPC_HP != NPC_MAXHP)
				IF ((NPC_HP + 25) > NPC_MAXHP)
					self->SetHP( NPC_MAXHP, true)
				ELSE
					self->SetHP( NPC_HP + 25, true)				
				ENDIF									
			ENDIF			
		ENDIF
		ENDCASE
		CASE(3)
      IF (CheckItem(__OBJ_HEALING_POTION) > 1)  // Heals 50 hit points
         TakeItem(__OBJ_HEALING_POTION)                 
			SHOUT(INTL( 6230, "Oh my, you've dropped a potion, you clumsy oaf! Hmmm. Tasty!"))
			IF (NPC_HP != NPC_MAXHP)
				IF ((NPC_HP + 50) > NPC_MAXHP)
					self->SetHP( NPC_MAXHP, true)
				ELSE
					self->SetHP( NPC_HP + 50, true)				
				ENDIF
			ENDIF
		ENDIF			
		ENDCASE
		OTHERWISE
		ENDCASE
	ENDSWITCH
	}
    CLOSE_HANDLER
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Shadeen::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT ACCEPT_MISSION = 1;
CONSTANT BURN = 2;    
CONSTANT ERRAND = 3;
CONSTANT PROMISE = 4;
CONSTANT GIVE_BOOK_TO_SHADEEN = 5;
CONSTANT BURN_SCROLL = 6; 

InitTalk

Begin
""
IF ((CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) OR (CheckFlag(__QUEST_KALASTOR_MISSION) == 0))
	Conversation
	INTL( 6231, "Goody-two-shoes like you aren't my kind. Take a hike.")
	BREAK
ELSE
	SWITCH(CheckFlag(__QUEST_SEEK_SHADEEN))
		CASE(0)
			Conversation
			INTL( 6232, "Hello there, sweetheart.")
		ENDCASE
		CASE(1)
			Conversation
			INTL( 6233, "Don't come back to me until you've taken care of poisoning the Bishop, y'hear?")
			BREAK
		ENDCASE
		CASE(2)
			Conversation
			INTL( 6234, "Welcome back. In case I haven't told you already, good job on the poison thing! "
			"That should keep this the Bishop off my case for a little while longer. "
			"So, how's life, friend? ")
			IF ((CheckFlag(__QUEST_TARGET_LEVEL) <= USER_LEVEL) && (CheckFlag(__QUEST_TARGET_KARMA) >= USER_KARMA))
				Conversation
				INTL( 6235, "You busy right now? I might have a \"mission\" for you.")
				GiveFlag(__QUEST_SEEK_SHADEEN,3)
			ENDIF
		ENDCASE
		CASE(3)
			Conversation
			INTL( 6236, "Well, looks like you've grown up quite a bit since you first did this little "
			"poison job for me. Good to see you again. If you're interested, I may have a \"mission\" "
			"for you.")
		ENDCASE
		CASE(4)
			Conversation
			INTL( 6237, "You've got your work cut out for you, don't you think? If you need a \"mission\" "
			"\"reminder\", just say so.")
		ENDCASE
		CASE(5)
			IF (CheckItem(__OBJ_CHRONICLES_OF_DOOM) >= 1)
				Conversation
				INTL( 6238, "Hello there, old friend. So I hear poor Menark's been robbed. *snicker* Good work. "
				"Can I have the book now?")
				TakeItem(__OBJ_CHRONICLES_OF_DOOM)
				GiveFlag(__QUEST_SEEK_SHADEEN,6)
				SetYesNo(GIVE_BOOK_TO_SHADEEN)
			ELSE
				Conversation
				INTL( 6239, "Hi. I hear you've done the job, congratulations. Now just go get that book and "
				"we'll talk.")
				BREAK
			ENDIF
		ENDCASE
		CASE(6)
			Conversation
			INTL( 6240, "Howdy, partner. Look, thanks for the book. I guess you deserve a \"reward\" for all "
			"your hard work. If you want one, of course.")
		ENDCASE
		CASE(7)
			Conversation
			INTL( 7158, "Howdy, partner. Sorry, don't have any work for you right now. Do what you want "
			"for now, but do NOT get involved with Monsignore Damien.")
		ENDCASE
		CASE(8)
			Conversation
			INTL( 6242, "Considering you killed me once, you'll understand if I want nothing to do with you.")
			BREAK
		ENDCASE
		OTHERWISE
			Conversation
			INTL( 1864, "...")
		ENDCASE
	ENDSWITCH
ENDIF

YES(GIVE_BOOK_TO_SHADEEN)
	Conversation
	INTL( 6243, "Aww, I'm kind of disappointed, you're just too easy to deal with. Oh well, I guess you might not "
	"be the professional con artist I thought you were. Don't worry about it, I'm sure you'll learn. "
	"Anyway, thanks for the book. I guess you deserve a \"reward\".")

NO(GIVE_BOOK_TO_SHADEEN)
	Conversation
	INTL( 6244, "*laugh* You really think I'd ask this politely? You forget who you're dealing with. I already "
	"have it. But I'm glad to see you're not so trustworthy... Kind of renews my faith in cynicism. "
	"Anyway, I guess you deserve a \"reward\" for your work, now.")
	IF (USER_KARMA >= (-100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
		GiveKarma(-3 * (500 + USER_KARMA) / 500)
	ENDIF

YesNoELSE(GIVE_BOOK_TO_SHADEEN)
	Conversation
	INTL( 6245, "Are we talking \"yes\" or \"no\", here?")
	SetYesNo(GIVE_BOOK_TO_SHADEEN)

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 6246, "I'm Shadeen, sometimes just called The Dagger for flavor.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 6247, "I don't really work, I've got other people to do that for me. Let's say I'm... "
"a businesswoman.")

Command(INTL( 617, "REWARD"))
""
IF (CheckFlag(__QUEST_SEEK_SHADEEN) == 6)
	Conversation
	INTL( 6248, "Fair enough. It may not seem like much, but if you ever wish to travel to Stoneheim, "
	"you'll need to perform a magical ritual to get there, since no boat ever goes that far. For that, "
	"you must own a magical Silver Feather, and you're in luck, that's just what you get for "
	"helping me. Also, now that I *know* you're one of us, I'll let all my contacts know "
	"you're working for the darkness, now. That should open you a few doors, but it'll close "
	"many others. Thanks again! ")
	GiveItem(__OBJ_SILVER_FEATHER)
	GiveFlag(__QUEST_SEEK_SHADEEN, 7)
	GiveFlag(__QUEST_FIXED_ALIGNMENT, -1)
	GiveXP(5000)
	PRIVATE_SYSTEM_MESSAGE(INTL( 4582, "{You} {have} {been} {awarded} {5,000} {experience} {points.}"))
ELSE
	Conversation
	INTL( 6249, "Reward for what?")
ENDIF

Command2(INTL( 4363, "MONSIGNOR"),INTL( 4364, "DAMIEN"))
INTL( 6250, "Him? Do you know anything about him? He's not too happy about what I did to him, so it'd probably "
"be wiser *NOT* to mention my name to him. *grin*")

Command(INTL( 6251, "STONEHEIM"))
INTL( 6252, "It's another island that lies somewhere west from here. That's where "
	 "you'll find the Centaurs and the Skraugs. Only the most powerful adventurers "
	 "can survive there.")

/*
Command(INTL( 5848, "WEATHERGATE"))
INTL( 6253, "Aaah, Weathergate... I really had good times, there, a long, long time ago. You should try "
"going there, if you've got the guts. Now, *there's* real adventure for you!")
*/

Command(INTL( 4194, "HARBINGER"))
""
IF (USER_LEVEL <= 40)
	Conversation
	INTL( 6254, "I don't think you're ready to hear about things like that. Better move on.")
ELSE
	Conversation
	INTL( 6255, "This is hard to talk about. Let's just say there's this ugly creature roaming the land, "
	"looking for *worthy* people, whatever that means. I'm not too sure what it wants, "
	"I've never encountered it, even if I've travelled a lot.")
ENDIF

Command(INTL( 1898, "SERAPH"))
""
IF (USER_LEVEL <= 30)
	Conversation
	INTL( 6256, "You're not ready to hear about this yet.")
ELSE
	Conversation
	INTL( 6257, "Well, all right, I can tell you this much: the Seraphs were so majestic that even the "
	"Elves looked like unkempt ruffians by comparison. They vanished back when mankind "
	"was barely learning to walk, perhaps even long before that. No one's ever seen them, "
	"except perhaps dragons.")
ENDIF

Command(INTL( 6258, "MISSION REMINDER"))
""
IF (CheckFlag(__QUEST_SEEK_SHADEEN) == 4)
	Conversation
	INTL( 6259, "The plan is quite simple. To be able to get \"Menark\"'s \"Chronicles\" \"of\" \"Doom\", you "
	"must create a diversion elsewhere in the town. To do this, you will need an accomplice that "
	"you trust for he will probably save your life. Give the \"scroll\" \"of\" \"evil\" \"deed\" "
	"to your accomplice. Then, he or she must meet \"Doremas\" for further instructions. If "
	"your friend succeeds in his or her mission, then you'll have the way clear for Menark during "
	"a short period of precious time. Good luck.")
ELSE
	Conversation
	INTL( 6260, "I don't know what mission you're talking about. Are you on a mission?")
ENDIF

Command3(INTL( 862, "INFO"),INTL( 554, "HELP"),INTL( 1533, "SECRET"))
""
SWITCH(CheckFlag(__QUEST_SEEK_SHADEEN))
	CASE(2)
		Conversation
		INTL( 6261, "Well, seeing as you've been pretty helpful so far, I guess I could give you "
		"a bit of information. There's something called the Obsidian Conclave, a group "
		"of dark wizards that are keeping themselves busy with some world-threatening "
		"nefarious plot. Now, if you want to know more, you'll have to do a few evil "
		"deeds and grow three more times in power.")
		GiveFlag(__QUEST_TARGET_LEVEL,USER_LEVEL+3)
		IF (USER_KARMA >= (-100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
			GiveFlag(__QUEST_TARGET_KARMA,USER_KARMA-75)
		ELSE
			GiveFlag(__QUEST_TARGET_KARMA,-175)
		ENDIF
	ENDCASE
	CASE(3)
		Conversation
		INTL( 6262, "Let me tell you a little secret, just as a small reward for all your help. There are "
		"people who walk this land who are immortal. Oh, sure, they can be killed, but they "
		"won't die from disease or old age. Pretty cool, don't you think?")
	ENDCASE
	OTHERWISE
		Conversation
		INTL( 6263, "There isn't anything I can do for you right now, honey.")
	ENDCASE
ENDSWITCH

Command(INTL( 6264, "OBSIDIAN CONCLAVE"))
""
IF (CheckFlag(__QUEST_SEEK_SHADEEN) >= 2)
	Conversation
	INTL( 6265, "You want to know more? Sure, why not. They're a group of discreet necromancers who "
	"are working for some powerful evil overlord. If you've met necromancers before, "
	"you can bet they were \"not\" members of the Obsidian Conclave. The Obsidian Wizards "
	"are discreet and almost never reveal themselves to the non-initiates. It took me "
	"twenty years to learn this, so you'd better be grateful.")
ELSE
	Conversation
	INTL( 6266, "That's not something you're ready to hear about.")
ENDIF

CmdAND(INTL( 6267, "WHO"),INTL( 6268, "IMMORTAL"))
""
IF (CheckFlag(__QUEST_SEEK_SHADEEN) >= 3)
	Conversation
	INTL( 6269, "I know someone who's immortal... But if I tell you, you have to promise not to repeat it "
	"to anyone. You promise?")
	SetYesNo(PROMISE)
ELSE
	Conversation
	INTL( 624, "What are you talking about?")
ENDIF

YES(PROMISE)
	Conversation
	INTL( 6270, "Well, if you must know, *I* am immortal, and quite strangely, even violent death isn't permanent. "
	"It's a special potion I drank, based on Elven blood, and my wounds heal even after I'm dead, so "
	"I never stay down forever. I'm not an undead, though, so don't try anything funny on me.")

NO(PROMISE)
	Conversation
	INTL( 6271, "Bah, no matter, it's not like your word would mean much anyway. To answer your question, I'm "
	"immortal, but if you tell anyone, it'll cost you.")

YesNoELSE(PROMISE)
	Conversation
	INTL( 6272, "How hard can it be to give a simple \"yes\" or \"no\"?")
	SetYesNo(PROMISE)

Command2(INTL( 4124, "POISON"),INTL( 4547, "CROWBANNER"))
""
IF (CheckFlag(__QUEST_SEEK_SHADEEN) >= 2)
	Conversation
	INTL( 6273, "Well, that was good work, got to admit it. Clever idea, that apple thing, got to "
	"hand it to you.")
ELSE
	Conversation
	INTL( 6274, "Uh huh. Really? Oh, you don't say? I'm fascinated... *yawn*")
ENDIF

Command(INTL( 643, "KALASTOR"))
""
IF (CheckFlag(__QUEST_SEEK_SHADEEN) <= 1) // If PC hasn't poisoned Crowbanner before...
	IF (CheckGlobalFlag(__QUEST_BISHOP_ILLNESS) == 1) //...and bishop is healthy
		IF ((CheckFlag(__QUEST_FIXED_ALIGNMENT) < 1) OR (USER_KARMA <= (-100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))) //...and PC is a "bad boy/girl":
			Conversation
			INTL( 6275, "Who? Who did you say? Kalastor? I... don't know what you're talking about. "
			"Hey, you strike me as a helpful kinda")
			IF (USER_GENDER == GENDER_MALE)
				Conversation
				INTL( 6276, "guy. ")
			ELSE
				Conversation
				INTL( 6277, "gal. ")
			ENDIF
			Conversation
			INTL( 6278, "Perhaps you'd give me a hand with something? What do you say?")
			SetYesNo(ACCEPT_MISSION)
		ELSE // If PC is too nice a person:
			Conversation
			INTL( 6279, "Hm. Somehow, I don't think people with your kind of reputation should concern "
			"themselves with people like Kalastor or myself. *smile*")
		ENDIF
	ELSE // If Bishop Crowbanner is already sick:
		Conversation
		INTL( 6280, "Kalastor, hm? Well, whether it's true or not, I can't really give you work to "
		"test you. Come back later, 'kay?")
	ENDIF
ELSE // PC has already poisoned Crowbanner...
	IF (CheckFlag(__QUEST_SEEK_SHADEEN) >= 3) //...and has earned Shadeen's trust:
		Conversation
		INTL( 6281, "Well, if you *must* know, yes, he and I were somewhat involved, a long time ago... But now, "
		"I prefer to stay away. Don't need any of this mushy stuff, it just gets in the way. He's "
		"pretty lovable, but he's a mortal and I'm not, so why go through all the trouble of getting "
		"attached if I'm going to lose him in the end, right?")
	ELSE // ...but isn't deemed trustworthy:
		Conversation
		INTL( 6282, "Kalastor or no Kalastor, I trust you for my own reasons already... as much as I can "
		"trust someone, anyway.")
	ENDIF
ENDIF

YES(ACCEPT_MISSION)
	Conversation
	INTL( 6283, "Great! Then I'd like you to poison Bishop Crowbanner for me. How? Hey, you figure "
	"it out, that's not my problem. Good luck!")
	GiveFlag(__QUEST_SEEK_SHADEEN,1)

NO(ACCEPT_MISSION)
	Conversation
	INTL( 6284, "Tough luck, I guess.")

YesNoELSE(ACCEPT_MISSION)
	Conversation
	INTL( 6285, "Uh huh. Okay, whatever.")

Command2(INTL( 988, "ELF"),INTL( 987, "ELVES"))
""
IF (CheckFlag(__QUEST_SEEK_SHADEEN) >= 3)
	Conversation
	INTL( 6286, "You're really a curious one, aren't you? Sure, Elves existed a long time ago, even if people "
	"are starting to believe they're just a fairy tale. Fact is--\"LISTEN\" \"CAREFULLY\", \"HERE\""
	"--there are Elves left in the world, but they're mad and very, very hard to find.")
ELSE
	Conversation
	INTL( 6287, "Not much to say about them, they vanished a long time ago, didn't they? We humans were just "
	"savages, so there's little remaining of their existence nowadays.")
ENDIF
	
Command(INTL( 5276, "MENARK"))
INTL( 6288, "Menark is a chronicler who works in the town's library with his assistant, \"Jeremiah\". "
"According to my sources, Menark has something quite valuable that I'd like to get my hands on.")

Command(INTL( 5272, "JEREMIAH"))
INTL( 6289, "You might say that he is Menark's eyes and ears. He has the never-ending task of witnessing "
"what happens and to report everything back to \"Menark\".")

Command(INTL( 4117, "DOREMAS"))
INTL( 6290, "Doremas is but a fool. However, he follows the orders much better than someone like "
"\"Baldric\" \"Silverknife\" who is simply too impredictable.")

Command2(INTL( 4183, "BALDRIC"),INTL( 4070, "SILVERKNIFE"))
INTL( 6291, "He's a real talented young man gifted with a loud mouth and a taste for troubles. He is "
"too reckless for my taste, that is why I deal only with his henchman, \"Doremas\".")

Command2(INTL( 5427, "CHRONICLES OF DOOM"),INTL( 5428, "CHRONICLE OF DOOM"))  
INTL( 6292, "The Chronicles of Doom relate of the forgotten events that occurred during the First Coming. \"Menark\", "
"the grumpy old chronicler who lives in Raven's Dust, is known to have a copy of that precious "
"document in his possession... I ABSOLUTELY NEED THIS BOOK, NO MATTER WHAT!!! I can assure you "
"that Menark guards it preciously, I've never been able to wrest it from him. ")
IF (CheckFlag(__QUEST_SEEK_SHADEEN) >= 3) // PC is trustworthy, ready to be told about the mission:
	Conversation
	INTL( 6293, "Be an angel and fetch it for me, 'kay? Would you agree to do this small \"errand\" for me? "
	"Don't you worry, dear, 'cause I got a plan! *smile*")
ENDIF

Command2(INTL( 1542, "MISSION"),INTL( 826, "ERRAND"))
""
IF (CheckFlag(__QUEST_SEEK_SHADEEN) >= 6) 
	Conversation
	INTL( 11520, "Heh, it looks like I have no more missions for you.")
ELSEIF (CheckFlag(__QUEST_SEEK_SHADEEN) <= 2) // If PC hasn't become trustworthy to Shadeen yet:
	Conversation
	INTL( 6294, "You're not ready for this yet, perhaps later.")
ELSEIF (CheckGlobalFlag(__QUEST_GLOBAL_CABALLERO_ALIVE) == 0) // PC is trustworthy, but Caballero is still alive:
	Conversation
	INTL( 6295, "I am truly sorry but Iago Caballero, that meddling knight, is still alive and keeps thwarting "
	"my plans. Someone has to get rid of him, otherwise he'll probably find a way to make my next "
	"mission fail as well.")
ELSE // PC trustworthy, Caballero dead...
	IF (CheckFlag(__FLAG_SHADEEN_PLAYER_A) == 0)  // User did not undertake the errand, yet. 
		Conversation 
		INTL( 6296, "The plan is quite simple. To be able to get \"Menark\"'s \"Chronicles\" \"of\" \"Doom\", you "
		"must create a diversion elsewhere in the town. To do this, you will need an accomplice that "
		"you trust for he will probably save your life. If you agree with this course of action, I "
		"will give you a \"scroll\" \"of\" \"evil\" \"deed\" that you will have to hand to your "
		"accomplice. Then, he or she will have to meet \"Doremas\" for further instructions. If "
		"your friend succeeds in his mission, then you'll have the way clear for Menark during "
		"a short period of precious time. So, do you think you're up for this simple task?")	
		SetYesNo(ERRAND)
	ELSE // User already has a the Flag of Shadeen. 
		IF (CheckItem(__OBJ_SCROLL_OF_EVIL_DEED) == 1)	
			Conversation
			INTL( 6297, "You already have a \"scroll\" \"of\" \"evil\" \"deed\"! If you want a new one, just "
			"say so, 'kay.")
		ELSEIF (CheckItem(__OBJ_SCROLL_OF_EVIL_DEED) > 1)
			Conversation
			INTL( 6298, "You have more than one scrolls? Ack! This is such a mess! I recommend you to ask me to "
			"burn all your \"scrolls\" \"of\" \"evil\" \"deed\" so that I can give you a brand "
			"new one. If you do not do so, how in hell will you know which one was yours to give to "
			"your accomplice?!")
		ELSE
			Conversation
			INTL( 6299, "If you need a new \"scroll\" \"of\" \"evil\" \"deed\", just say so! Remember, you must "
			"give the scroll to your accomplice and then, direct him to \"Doremas\" for further "
			"instructions.") 
		ENDIF	
	ENDIF
ENDIF

Command(INTL( 6300, "SCROLL OF EVIL DEED"))
""
IF (CheckGlobalFlag(__QUEST_GLOBAL_CABALLERO_ALIVE) == 0)
	Conversation
	INTL( 6301, "I am truly sorry but Iago Caballero, that meddling knight, is still alive and keeps thwarting "
	"my plans. Someone has to get rid of him, otherwise he'll probably find a way to make my next "
	"mission fail as well.")
ELSE
	IF (CheckFlag(__FLAG_SHADEEN_PLAYER_A) == 0)
		IF (USER_GENDER == GENDER_MALE) 
			Conversation
			INTL( 6302, "That's none of your business, lil' boy.")
		ELSE
			Conversation
			INTL( 6303, "That's none of your business, lil' girl.")
		ENDIF
	ELSE
		IF (CheckItem(__OBJ_SCROLL_OF_EVIL_DEED) == 1)
			Conversation
			INTL( 6304, "You already have a scroll of evil deed! Do you want me to burn it so I can give you a brand "
			"new one?")
			SetYesNo(BURN_SCROLL) 
		ELSEIF (CheckItem(__OBJ_SCROLL_OF_EVIL_DEED) >= 1)
			Conversation
			INTL( 6305, "You have a few scrolls of evil deed, some of them surely do not belong to you! Do you want "
			"me to burn all of them so I can give you a brand new one?")
			SetYesNo(BURN_SCROLL)
		ELSE 
			Conversation
			INTL( 6306, "I see that you've either lost the scroll or gave it to somebody not qualified for "
			"the job, eh? I betcha you want a new one, right?") 
			SetYesNo(BURN_SCROLL) 
		ENDIF
	ENDIF	
ENDIF	
	
YES(BURN_SCROLL)
IF (CheckItem(__OBJ_SCROLL_OF_EVIL_DEED) >= 1)
	TakeItem(__OBJ_SCROLL_OF_EVIL_DEED)
ENDIF
Conversation
INTL( 6307, "Here ya go. Remember to give the scroll only to somebody who can do the job properly else "
"you're wasting both my time and yours. Then, your accomplice must seek \"Doremas\" for further " 
"instructions.")
// I use the CurrentRound + 1 d 1000 as validation code. It is impossible to 'cheat'. 
GiveFlag(__FLAG_SHADEEN_PLAYER_A, CurrentRound+(rnd.roll(dice(1,1000)) ) )
GiveItem(__OBJ_SCROLL_OF_EVIL_DEED) 
GetItemHandle(__OBJ_SCROLL_OF_EVIL_DEED, EvilDeedScroll)
GiveUnitFlag(EvilDeedScroll,__ITEM_FLAG_SCROLL_OF_EVIL_DEED, CheckFlag(__FLAG_SHADEEN_PLAYER_A))

NO(BURN_SCROLL)
Conversation
INTL( 6308, "'Kay!")

YesNoELSE(BURN_SCROLL)
Conversation
INTL( 6309, "Erm? Yeah, whatever.")

YES(ERRAND)
	Conversation
	INTL( 6310, "I give you this \"scroll\" \"of\" \"evil\" \"deed\" that you must give to an accomplice in whom "
	"you have perfect trust lest you want to fail your task miserably. Then, he must meet \"Doremas\" "
	"for further instructions. Basically, your friend will have to rob the bank to create a diversion "
	"for the guards while you try to wrest the \"Chronicles\" \"of\" \"Doom\" from \"Menark\". Simple, "
	"isn't? I thought so, too. *smile*")
	;int nNumScrolls = CheckItem(__OBJ_SCROLL_OF_EVIL_DEED);
	FOR( 0, nNumScrolls)
		 TakeItem(__OBJ_SCROLL_OF_EVIL_DEED)
	ENDFOR
	GiveFlag(__FLAG_SHADEEN_PLAYER_A, CurrentRound+(rnd.roll(dice(1,1000)) ) )
	GiveFlag(__QUEST_SEEK_SHADEEN,4)
	GiveItem(__OBJ_SCROLL_OF_EVIL_DEED) 
	GetItemHandle(__OBJ_SCROLL_OF_EVIL_DEED, EvilDeedScroll)
	GiveUnitFlag( EvilDeedScroll, __ITEM_FLAG_SCROLL_OF_EVIL_DEED, CheckFlag(__FLAG_SHADEEN_PLAYER_A))

NO(ERRAND)
	Conversation
	INTL( 6311, "As you wish, ya big wuss.")

YesNoELSE(ERRAND)
	Conversation
	INTL( 6312, "Erm? Quit wasting my time, I need a clear answer. Was that a yes or a no?")
	SetYesNo(ERRAND)

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 6313, "Ha ha ha. You're funny. Kinda young for me, but funny.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 6314, "See you around... I hope.") BREAK

Default
INTL( 6315, "Keep talking, this is fascinating!")

EndTalk

}

