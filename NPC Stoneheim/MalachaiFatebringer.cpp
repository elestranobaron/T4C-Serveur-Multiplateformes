#pragma hdrstop
#include "MalachaiFatebringer.h"

MalachaiFatebringer::MalachaiFatebringer()
{}

MalachaiFatebringer::~MalachaiFatebringer()
{}

extern NPCstructure::NPC MalachaiFatebringerNPC;

void MalachaiFatebringer::Create( ){
	npc = MalachaiFatebringerNPC;
	SET_NPC_NAME("[10873]Malachai Fatebringer");
	npc.InitialPos.X = 900;
	npc.InitialPos.Y = 1110;
	npc.InitialPos.world = 0;
}

void MalachaiFatebringer::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk	 

Begin
INTL( 7964, "State your business here or be on your way.")
PRIVATE_SYSTEM_MESSAGE(INTL( 7965, "There's something very wrong with this centaur, but you can't put your finger on what exactly."))
	
Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 7966, "I am called Malachai Fatebringer.")
PRIVATE_SYSTEM_MESSAGE(INTL( 7967, "Something tells you you shouldn't trust this centaur."))
 
Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 7968, "I am a manaweaver by profession. I can create powerful magical items if you have the gold.")
PRIVATE_SYSTEM_MESSAGE(INTL( 7969, "There's something suspicious about him."))

Command2(INTL( 554, "HELP"),INTL( 896, "QUEST"))
INTL( 7970, "I have no help to give, nor quest to suggest, but should you happen to have \"Scrolls\" \"of\" "
"\"Horse\" \"Friendship\" on you, be sure to drop by and let me know.")
PRIVATE_SYSTEM_MESSAGE(INTL( 7971, "Malachai grins maliciously. Better be careful around him."))

CmdAND3(INTL( 1159, "SCROLL"),INTL( 10221, "HORSE"),INTL( 7973, "FRIENDSHIP"))
""
IF(CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP) < 1)
	Conversation
	INTL( 7974, "Those items should NEVER leave Centaur hands. I'm glad to see you have none on yourself, "
	"or I might be very, very displeased.")
ELSE
	Conversation
	INTL( 7975, "These scrolls do not belong to you! I take them back, but I am no thief, so here's "
	"something in return.")
	;int nNumScrollsTaken = rnd.roll(dice(1,CheckItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP)));
	;int nExpReward = USER_LEVEL*2000*nNumScrollsTaken;
	PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7976, "You have just lost %u Scrolls of Horse Friendship."),nNumScrollsTaken))	
	PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
	GiveXP(nExpReward)
	FOR(0,nNumScrollsTaken)
		TakeItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP)		
		SWITCH( rnd.roll(dice(1,4)))
			CASE(1)
				GiveItem(__OBJ_ASSASSIN_BLADE)
				PRIVATE_SYSTEM_MESSAGE(INTL( 7977, "Malachai gives you an \"Assassin's\" \"Blade\"."))
			ENDCASE
			CASE(2)
				GiveItem(__OBJ_GRIM_BLADE_OF_WAR)
				PRIVATE_SYSTEM_MESSAGE(INTL( 7978, "Malachai gives you a \"Grim\" \"Blade\" \"of\" \"War\"."))
			ENDCASE
			CASE(3)
				GiveItem(__OBJ_ROBE_OF_HELL)
				PRIVATE_SYSTEM_MESSAGE(INTL( 7979, "Malachai gives you a \"Robe\" \"of\" \"Hell\"."))
			ENDCASE
			CASE(4)
				GiveItem(__OBJ_BOW_OF_CENTAUR_SLAYING)
				PRIVATE_SYSTEM_MESSAGE(INTL( 7980, "Malachai gives you a \"Bow\" \"of\" \"Centaur\" \"Slaying\"."))
			ENDCASE
			OTHERWISE
				Conversation
				INTL( 7981, "{ILLEGAL} {STRING}. Please report this to bugs@the4thcoming.com.")
		ENDSWITCH
	ENDFOR
ENDIF
PRIVATE_SYSTEM_MESSAGE(INTL( 7983, "You get the feeling mentioning those scrolls to him is never a good idea."))

CmdAND(INTL( 7984, "ASSASSIN"),INTL( 7985, "BLADE"))
INTL( 7986, "That's a poisoned blade. It goes through armor like a hot knife through butter. I'm "
"told mostly thieves use it.")
PRIVATE_SYSTEM_MESSAGE(INTL( 7987, "You sense some dark purpose behind this explanation."))

CmdAND3(INTL( 7988, "GRIM"),INTL( 7985, "BLADE"),INTL( 7989, "WAR"))
INTL( 7990, "A great warrior's sword. I'm sure you could wage a great war wielding it.")

PRIVATE_SYSTEM_MESSAGE(INTL( 7987, "You sense some dark purpose behind this explanation."))

CmdAND(INTL( 7991, "ROBE"),INTL( 7992, "HELL"))
INTL( 7993, "The Robe of Hell is useful to mages who wish to seek immunity against fire and darkness. "
"Perhaps you should try it on and see how it looks on you.")
PRIVATE_SYSTEM_MESSAGE(INTL( 7987, "You sense some dark purpose behind this explanation."))

CmdAND3(INTL( 7994, "BOW"),INTL( 7995, "CENTAUR"),INTL( 7996, "SLAY"))
INTL( 7997, "Aaah, it would be a shame if a human archer started using that bow against my people. "
"I'm certain it would make our king look very bad, wouldn't you agree?")
PRIVATE_SYSTEM_MESSAGE(INTL( 7987, "You sense some dark purpose behind this explanation."))

Command2(INTL( 1072, "KING"),INTL( 7998, "GRAVESOUL"))
INTL( 7999, "A weakling! He believes in his own sanctimonious, righteous act, but I am not fooled by it. "
"He is guilty of something, and even though he hides it well, I'm confident Zion Thunderheart "
"will eventually expose him.")
PRIVATE_SYSTEM_MESSAGE(INTL( 8000, "This centaur is involved in dark plots, you just know it."))

Command2(INTL( 8001, "ZION"),INTL( 8002, "THUNDERHEART"))
INTL( 8003, "He should be the king! None of this weak-hearted compassion and nonsensical trading with humans. "
"Let Zion rule and take us on the path to reclaim *our* Stoneheim!")

PRIVATE_SYSTEM_MESSAGE(INTL( 8004, "The two must be working together towards some dark goal.") )

Command2(INTL( 8005, "KYATHOS"),INTL( 8006, "SHATTERSKULL"))
INTL( 8007, "Dumb as a doorknob! He can fight pretty good, but his ridiculous equipment is what makes him good, "
"not his skill. Some day, I'll show him who's the better warrior!")
PRIVATE_SYSTEM_MESSAGE(INTL( 8008, "Somehow, you get the impression Malachai is scared of him."))

Command2(INTL( 8009, "THOR"),INTL( 8010, "GLAREFIRE"))
INTL( 8011, "A rank amateur! He thinks his manasmithing is better than my manaweaving, but that's because I've "
"never challenged his little creations with my own. I've made swords and armors that could slay him "
"in one blow!")
PRIVATE_SYSTEM_MESSAGE(INTL( 8012, "Malachai doesn't appear as confident in his abilities as he says he is."))

Command2(INTL( 8013, "DIONYSUS"),INTL( 8014, "SILVERSTREAM"))
INTL( 8015, "A delusional idiot! I want nothing to do with the likes of him. Religion is for those who do not "
"have the strength to stand proud and tall on their own. I don't need a god to tell me I'm worth "
"something, I already know that!")
PRIVATE_SYSTEM_MESSAGE(INTL( 8016, "Regardless of what he says, Malachai seems a little worried and agitated when he says the word 'religion'."))

Command2(INTL( 8017, "GLADDIUS"),INTL( 8018, "WINDCHASER"))
INTL( 8019, "Brawns with no brains! He thinks he's all that, he thinks he's noble and selfless, but I know better. "
"He and his ilk only want to be seen as great heroes and protectors, when all they do is walk around with "
"a sword and pretend they're something else. It makes me sick!")
PRIVATE_SYSTEM_MESSAGE(INTL( 8008, "Somehow, you get the impression Malachai is scared of him."))

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8020, "Leave at once, you're wasting my time.")
PRIVATE_SYSTEM_MESSAGE(INTL( 8021, "Malachai glares at you evilly."))
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 1075, "Farewell.")
PRIVATE_SYSTEM_MESSAGE(INTL( 8022, "Malachai seems relieved to see you leave."))
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1) 
	Conversation
	INTL( 3921, "Please try to be more specific.")
ELSE
	Conversation
	INTL( 5250, "I don't think that concerns me.")
ENDIF
PRIVATE_SYSTEM_MESSAGE(INTL( 8023, "You somehow feel you don't want to waste this centaur's time."))


EndTalk
}
