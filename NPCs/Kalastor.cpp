//////////////////////////////////////////////////////////////////////
// Kalastor.cpp: implementation of the Kalastor class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Kalastor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Kalastor::Kalastor()
{}

Kalastor::~Kalastor()
{}

extern NPCstructure::NPC KalastorNPC;
 
void Kalastor::Create( ){
	npc = KalastorNPC;
	SET_NPC_NAME( "[3044]Kalastor" );
	npc.InitialPos.X = 2882;
	npc.InitialPos.Y = 1128;
	npc.InitialPos.world = 0;
}

void Kalastor::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT ROB = 1;
CONSTANT TRUST = 2;
CONSTANT JOB = 3;
CONSTANT MONEY = 4;
CONSTANT SEEKSHADEEN = 5;

InitTalk

Begin
""
IF( CheckGlobalFlag( __GLOBAL_QUEST_WHO_IS_INFECTED ) == 3 ) 
        GiveNPCFlag( __NPC_FLAG_KALASTOR_INFECTED, rnd.roll(dice(15, 4) ) MINUTES TDELAY )
	GiveGlobalFlag( __GLOBAL_QUEST_WHO_IS_INFECTED, 0 )
ENDIF
IF (CheckNPCFlag( __NPC_FLAG_KALASTOR_INFECTED) > CurrentRound)
	IF(CheckItem(__OBJ_ELIXIR_OF_PURITY) > 0)
		Conversation  // still infected.
		INTL( 1508, "Uh? The Lurker gave you an elixir of purity? I guess it'll have to do... "
		"Hmmm... Not bad, not bad at all! I am already feelin' better. Here... Tell "
		"you what... ")
                TakeItem(__OBJ_ELIXIR_OF_PURITY) 
		Conversation
		FORMAT(INTL( 1509, "I hope %u gold pieces is enough for your trouble."), 1500+(USER_LEVEL*200))
		GiveGold(1500+(USER_LEVEL*200))
		GiveNPCFlag(__NPC_FLAG_KALASTOR_INFECTED, 0) 
	ELSE                
		Conversation
		INTL( 1510, "Argh! I've been infected with the fever... must get... "
		"information to... Lurker... NOW!")
		GiveFlag(__QUEST_CURE_KALASTOR, 1)
		BREAK
	ENDIF
ELSEIF ((CheckNPCFlag( __NPC_FLAG_KALASTOR_INFECTED ) < CurrentRound) && (CheckNPCFlag( __NPC_FLAG_MURMUNTAG_INFECTED ) != 0 ))
	Conversation
	INTL( 1511, "Well... I'm a tough guy. I was able to heal the goblin fever "
	"without your help finally.")
	GiveNPCFlag( __NPC_FLAG_KALASTOR_INFECTED, 0)
ELSE	
	SWITCH(CheckFlag(__SHAKE_EDGAR))
		CASE(2)
			Conversation
			INTL( 1512, "What, Edgar's getting too tough for you? Whatcha waitin' for?")
		ENDCASE
		CASE(3)
			Conversation
			INTL( 1513, "Oh, it's you again! Good to see you. I hear you gave Edgar a good "
			"roughing up. Did you get the money too?")
			SetYesNo(MONEY)
		ENDCASE
		CASE(4)
			IF (CheckFlag(__BLACK_MARKET) == 0)
				Conversation
            INTL( 1514, "Hey thanks! But you'll have to earn access to the black market now.")			
			ELSE
				Conversation
				INTL( 1515, "Welcome back, friend. Now that you're one of us, I'm sure we can find "
				"something for you to do. Come back here often and ask me if I have a "
				"\"mission\" for you.")
            GiveFlag(__QUEST_THREAD, 4)
			ENDIF
		ENDCASE
		OTHERWISE
			Conversation
			INTL( 1516, "Yes, can I help you?")
			PRIVATE_SYSTEM_MESSAGE(INTL( 11757, "Kalastor quickly glances out the window, as if looking for someone."))
		ENDCASE
	ENDSWITCH
ENDIF

YES(MONEY)
	Conversation
	INTL( 1517, "Excellent! Let's see it...")
	IF (Gold>=1000)
		Conversation
		INTL( 1518, "All right, all there. Good work, my friend, good work. I'll be sure to put in "
		"a good word for you to my superiors. Heh! Heh!")
		TakeGold(1000)
		IF (USER_KARMA >(-100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
			GiveKarma(-20*(500+USER_KARMA)/500)
		ENDIF
		GiveFlag(__SHAKE_EDGAR,4)
		IF (CheckFlag(__BLACK_MARKET) == 0)
			Conversation
			INTL( 10527, " You should consider gaining access to the black market now. That'll give you "
			"more useful contacts for the future.")
		ELSE
			Conversation
			INTL( 10528, " Now that you're one of us, I'm sure we can find "
			"something for you to do. Come back here often and ask me if I have a "
			"\"mission\" for you.")
			GiveFlag(__QUEST_THREAD, 4)
		ENDIF
	ELSE
		Conversation
      INTL( 1519, "WHAT?? Are you trying to trick me? There's not enough money there! ")
		TakeGold(Gold)
		BREAK
	ENDIF

NO(MONEY)
	Conversation
	INTL( 1520, "Well, I guess you're not as good a liar as you thought. You got the money, "
	"I know it, so what have you done with it? One can only wonder...")

YesNoELSE(MONEY)
	Conversation
	INTL( 1521, "Yes or no?")
	SetYesNo(MONEY)

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1522, "My name is Kalastor, but don't tell anybody. If you don't keep it a \"secret\", "
"you'll soon find yourself without a purse.")

Command(INTL( 643, "KALASTOR"))
INTL( 1523, "Yes, that's my name. You're pretty sharp, aren't you?")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1524, "I am an apprentice \"thief\". I could show you how to rob someone later if "
"you like. All you have to do is close your eyes and open your purse while you "
"ask for training.")

Command(INTL( 523, "ANNABELLE"))
INTL( 1525, "I don't know where she is.")

Command2(INTL( 509, "BALORK"),INTL( 510, "BRAND"))
""
IF (CheckFlag(__BALORK_BRAND) == 1)	// If PC killed Balork
	Conversation					// Evil Quest is blocked.
	INTL( 3628, "So you killed him? Good for you, too bad for the rest of us. S'okay, though, he'll come "
	"back to life in a little while. His corporeal form regenerates over time, so it's not like "
	"you did any permanent damage.")
ELSE											// If PC hasn't killed Balork (yet)...
	IF (CheckFlag(__KNOWS_EVIL_PASSWORD) == 0)	// ...and doesn't know the evil password:
		Conversation
		INTL( 1526, "Not the friendliest of people, for sure. He's big, he's red and he's got a "
		"mean axe. Oh yeah, and he's really, really \"evil\".")
	ELSE										// ...and knows the evil password:
		Conversation
		INTL( 1527, "So, how did your encounter with him go? Yeah, that's about what I thought. "
		"I can see what he likes in you. So, did he give you a password? D'ya remember it? "
		"Can you tell me what it is?")
		GiveFlag(__QUEST_THREAD,1)
	ENDIF
ENDIF

Command(INTL( 1220, "EVIL"))
""
IF (CheckFlag(__QUEST_THREAD) == 0)
	Conversation
	INTL( 1528, "There's indeed a great evil that walks the land, but personally, I'd prefer "
	"to stay away from it, like... *cough* like honest folks do.")
ELSE
	Conversation
	INTL( 1529, "Like I said, Balork's not someone to be trifled with. Never make fun of him that "
	"to his face. He'd tear your head off and feed it to some \"abominations\". "
	"Erk! These things give me the shivers.")
	IF (CheckFlag(__QUEST_THREAD) == 1 )
		GiveFlag(__QUEST_THREAD,2)
	ENDIF
ENDIF

Command(INTL( 1530, "ABOMINATION"))
""
IF (CheckFlag(__QUEST_THREAD) == 2)
	Conversation
	INTL( 1531, "Ugly, fast and very powerful. If you're gonna go fight them, make sure you're "
	"loaded up with healing potions.")
ELSE
	Conversation
	INTL( 1532, "Yeah, abominations exist. They are rumored to be rather vicious beasts that "
	"roam the underworld. Never seen 'em myself.")
ENDIF

Command(INTL( 1533, "SECRET"))
INTL( 1534, "Yes, my master calls himself \"Shadow\" Stalker. He never told me his real "
"name.")

Command(INTL( 565, "BRIGAND"))
""
IF (CheckFlag(__KNOWS_EVIL_PASSWORD) == 1)
	Conversation
	INTL( 1535, "They live west from here, between here and Windhowl. They won't know who "
	"you are, so they may attack you. Don't mess with them, they're mean and tough.")
ELSE
	Conversation
	INTL( 1536, "*snigger* Honest folks like me don't mingle with brigands. Wouldn't know the "
	"first thing about them, really.")
ENDIF

Command(INTL( 970, "THIEF"))
""
IF (CheckFlag(__KNOWS_EVIL_PASSWORD) > 1)
	Conversation
	INTL( 1537, "Yes, my master has taught me the ways of \"robbing\" and the like. I'm also quite "
	"adept at dodging, and I could probably \"train\" you in that field, seeing as it is very useful "
	"for a thief. Heh heh.")
ELSE
	Conversation
	INTL( 1538, "I hear there are thieves in this town, but I don't think I've ever seen one. "
	"*chuckle* Really. Take my word for it.")
ENDIF

Command(INTL( 1539, "NIGHTINGALE"))
""
IF (CheckFlag(__KNOWS_EVIL_PASSWORD) > 0)
	Conversation
	INTL( 1540, "Ah, well then, it appears you wish to take part in the darker side of the world. "
	"That's great news, really. Welcome to the world of fame and fortune! There's a "
	"lot of stuff going on in this town, but we don't \"trust\" you yet, so you'll have "
	"to do \"earn\" it by doing \"missions\" for us.")
	GiveFlag(__QUEST_THREAD,3)
ELSE
	Conversation
	INTL( 1541, "Whatever do you mean, my dear, good friend? This means nothing to me.")
ENDIF

Command2(INTL( 610, "JOB"),INTL( 1542, "MISSION"))
""
SWITCH(CheckFlag(__QUEST_THREAD))
	CASE(0)
		Conversation
		INTL( 1543, "What do I look like to you, an employment center? I don't give work to people "
		"who aren't members of the Shadow Guild. Go away.")
	ENDCASE
	CASE(1)
		Conversation
		INTL( 1544, "It's not because you know a silly password that I'll give you work.")
	ENDCASE
	CASE(2)
		Conversation
		INTL( 1545, "Okay, so you know a little bit of this, a little bit of that. Don't make you "
		"no associate of mine. Get work elsewhere...")
	ENDCASE
	CASE(3)
		Conversation
		INTL( 1546, "Heh heh, welcome to the guild, friend. Always nice to see a fresh face among "
		"us. Okay, so are you ready to get to work?")
		SetYesNo(JOB)
	ENDCASE
	CASE(4)
		Conversation
		INTL( 1547, "Yeah, I got a job for you, but this time, it's kind of a personal one. There's "
		"this lady friend of mine, who's disappeared a while back. Last time I heard about her, she was headed for Raven's Dust. Her name's "
		"Shadeen... Think you could look her up?")
		SetYesNo(SEEKSHADEEN)
	ENDCASE
ENDSWITCH

YES(SEEKSHADEEN)
	Conversation
	INTL( 1548, "Excellent. I knew you'd eventually help me. She was last seen - or so I hear - on "
	"her way to \"Raven's\" \"Dust\". Said she wanted to loot the king's treasury, the fool! "
	"Anyway, you should know she's a warrior and a rogue, and completely untrustworthy. "
	"Don't believe her and don't fall into her traps.")
	GiveFlag(__QUEST_KALASTOR_MISSION,1)

NO(SEEKSHADEEN)
	Conversation
	INTL( 1549, "Ah well. I figured it was worth a shot. I'll just have to find someone better.")

YesNoELSE(SEEKSHADEEN)
	Conversation
	INTL( 1550, "Speak up, I can't hear you when you mumble like this.")
	SetYesNo(SEEKSHADEEN)

YES(JOB)
Conversation
INTL( 1551, "I need you to go check up on a friend of mine, \"Edgar\" Gimplestratten, a "
"merchant who lives not far from here. He owes me some protection money, but "
"he just won't pay. Why don't you go \"shake\" him up a bit.")
GiveFlag(__SHAKE_EDGAR,1)

NO(JOB)
Conversation
INTL( 1552, "Well, I guess you'll have to come back when you're ready, then.")

YesNoELSE(JOB)
Conversation
INTL( 1553, "Hm? I didn't quite hear that.")
SetYesNo(JOB)

Command(INTL( 1554, "EDGAR"))
INTL( 1555, "Edgar? Edgar Gimplestratten? A pain in the back, if y'ask me. He owes me a lot "
"of money. I work my @$$ off for him and what do I get? Rejection! Scorn! I "
"tell you, this world is all upside down!")

Command(INTL( 1556, "SHAKE"))
""
IF (CheckFlag(__SHAKE_EDGAR) == 1)
	Conversation
	INTL( 1557, "Just tell him my \"name\" and that you're there to collect the protection "
	"fee he owes me. Then come back and tell me all about it.")
ELSE
	Conversation
	INTL( 1558, "Huh? What do you mean? Want me to shake your hand or something? *sigh* "
	"People nowadays make less and less sense...")
ENDIF

Command2(INTL( 496, "TEACH"),INTL( 495, "LEARN"))
INTL( 1559, "I have nothing to teach you.")

Command2(INTL( 632, "TRUST"),INTL( 1560, "EARN"))
""
IF (CheckFlag(__QUEST_THREAD) == 3)
	Conversation
	INTL( 1561, "What, you would think we're gullible enough to trust you just like that? No, "
	"we will test your resolve before we tell you more about who's who, and what's "
	"going on.")
ELSE
	Conversation
	INTL( 1562, "A hard thing to earn, these days, wouldn't you say?")
	SetYesNo(TRUST)
ENDIF

YES(TRUST)
	Conversation
	INTL( 1563, "Glad to hear you say that.")
NO(TRUST)
	Conversation
	INTL( 1564, "Really? You're an odd one...")
YesNoELSE(TRUST)
	Conversation
	INTL( 1565, "Um... er... right, as you say.")

Command(INTL( 793, "RAVEN'S DUST"))
""
IF (CheckFlag(__QUEST_THREAD) <=2)
	Conversation
	INTL( 1566, "You don't know much about geography, do you? It's the other island that makes "
	"the Kingdom of Goldmoon, ruled by our <cough> beloved <cough> King "
	"\"Theodore\" \"XIII\".")
ELSE
	Conversation
	INTL( 1567, "I'd love to start an operation on Raven's Dust, but there's no real way to get "
	"there, nowadays. It'd take a powerful wizard to teleport me there, but I don't "
	"know of any in this town. Perhaps in Windhowl?")
ENDIF

Command2(INTL( 1072, "KING"),INTL( 754, "THEODORE"))
""
IF (CheckFlag(__QUEST_THREAD) <= 2)
	Conversation
	INTL( 1568, "Aaah, what a <cough> GREAT <choke> King we have, wouldn't you say? But I can't "
	"complain. If he didn't spend his time sleeping, boozing and womanizing, I'd be "
	"out of a job. *grin*")
ELSE
	Conversation
	INTL( 1569, "I hear his treasure is pretty impressive. Anyone who can make it there would be "
	"a very notorious thief in a matter of days! But I don't know anyone who's this "
	"good, I think.")
ENDIF
	
Command(INTL( 1570, "SHADOW GUILD"))
""
IF (CheckFlag(__KNOWS_EVIL_PASSWORD) > 0)
	INTL( 1571, "You want to know more about the Shadow Guild? Perhaps you do, and perhaps you "
	"don't... At the very least, I can tell you it's a guild of thieves... and more.")
ELSE
	Conversation
	INTL( 1572, "Huh? Shadow what? I have no idea what you're talking about. You think "
	"I'm a \"thief\" or something? Heh heh")
ENDIF

Command(INTL( 1573, "ROBBING"))
INTL( 1574, "Well, yes, actually I just stole your purse! Do you want it back?")
TakeGold (rnd.roll( dice( 1, 15 ) ))
SetYesNo(ROB)
YES(ROB)
     TakeGold (3)
     Conversation
     INTL( 1575, "Well, here it is!")
NO(ROB)
     TakeGold (11)
     Conversation
     INTL( 1576, "Oh well, I'll give it back to you anyway.")
YesNoELSE(ROB)
     Conversation
     INTL( 1577, "Don't take it that way, I was just kidding. *laugh*")

Command(INTL( 585, "SHADOW"))
INTL( 1578, "Don't tell him I told you his name.")

Command2(INTL( 496, "TEACH"), INTL( 495, "LEARN"))
INTL( 7517, "I do not have the skills necessary to teach you anything.")

Command(INTL( 502, "TRAIN"))
INTL( 1579, "Very good, let's begin.")
CreateSkillList
	AddTrainSkill( __SKILL_PEEK, 100, 25 )
	AddTrainSkill( __SKILL_DODGE, 5000, 10 )
	AddTrainSkill( __SKILL_ARCHERY, 5000, 15 )
SendTrainSkillList

Command(INTL( 1581, "SHADEEN"))
""
IF (CheckFlag(__QUEST_THREAD) == 4)
	Conversation
	INTL( 1582, "We're just friends, okay? So don't give me these looks! Sheez... Some people "
	"are just busybodies...")
ELSE
	Conversation
	INTL( 1583, "Yeah, there was a Shadeen girl that was operating here a while back. Haven't "
	"seen her in a while, though.")
ENDIF

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 1584, "Uh huh. Awesome use of the language. Care to try again?") BREAK

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1585, "Next time, bring more gold! Just kidding. *smile*") BREAK

Default
INTL( 1586, "Was that a joke? Thought so...")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Kalastor::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Kalastor data function
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_PEEK, 100, 25 )
		TRAIN_SKILL( __SKILL_DODGE, 5000, 10 )
		TRAIN_SKILL( __SKILL_ARCHERY, 5000, 15 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
