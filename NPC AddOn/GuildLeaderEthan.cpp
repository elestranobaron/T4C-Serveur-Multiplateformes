#pragma hdrstop
#include "GuildLeaderEthan.h"

GuildLeaderEthan::GuildLeaderEthan()
{}

GuildLeaderEthan::~GuildLeaderEthan()
{}

extern NPCstructure::NPC GuildLeaderEthanNPC;

void GuildLeaderEthan::Create( ){
	npc = GuildLeaderEthanNPC;
	SET_NPC_NAME( "[12741]Guild Leader Ethan");
	npc.InitialPos.X = 1710;
	npc.InitialPos.Y = 1198;
	npc.InitialPos.world = 0;
}

void GuildLeaderEthan::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 6)
	Conversation
	INTL( 12169, "Welcome to the merchant's guild. What can I do for you?")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 6)
	Conversation
	INTL( 12170, "What? You're looking for Nomad? What kind of trouble has the little \"misfit\" gotten himself into now?")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 9)
	Conversation
	INTL( 12171, "Well? Have you talked to Urik yet? Hurry up then... time is money you know!")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 9)
	Conversation
	INTL( 12172, "I heard about how you dealt with Urik... nice work. Now then, let's see the \"money\".")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 10)
	IF(Gold>=2000)
		Conversation
		INTL( 12173, "Well, it's about time! Now give me that money so I can put it somewhere safe. Now, about \"Nomad\"...")
		TakeGold(2000)
		PRIVATE_SYSTEM_MESSAGE(INTL( 12174, "You give 2000 gold.to Ethan."))
		GiveXP(20000)
		PRIVATE_SYSTEM_MESSAGE(INTL( 9922, "You receive 20000 experience points."))
		GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 11)
	ELSE
		Conversation
		INTL( 12175, "I told you before, get me 2000 gold or you can forget about ever finding Nomad!")
		BREAK
	ENDIF
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 11)
	Conversation
	INTL( 12176, "Let's finish our business about \"Nomad\" so I can get back to work.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 12)
	Conversation
	INTL( 12177, "Did you find the house yet? I told you, it's somewhere in the south part of town.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 42)
	Conversation
	INTL( 12178, "I hope you succeed in bringing Nomad to justice, if he really is part of this Obsidian Conclave.")
ELSE
	Conversation
	INTL( 12179, "Word of your deeds has reached Windhowl, friend. I must say that I'm rather surprised to see you "
	"have survived this ordeal. Well done!")
ENDIF

Command(INTL( 12180, "MISFIT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 6)
	Conversation
	INTL( 12181, "Hah! Nomad is what we call a peculiar merchant. He's very \"aggressive\", and not just in his "
	"dealings with fellow guild members, but with clients as well... unless he really wants something, "
	"then he's all smiles.")
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

Command(INTL( 12183, "AGGRESSIVE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 6)
	Conversation
	INTL( 12184, "Add to that the fact that he can spot a good \"bargain\" a mile away, and you can understand why he is very "
	"unpopular amongst his fellow merchants.")
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

Command(INTL( 12185, "BARGAIN"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 6)
	Conversation
	INTL( 12186, "Aye, why just recently he came across what he called a \"Heartstone\". He was very excited about it too. "
	"Knowing him, he has already made a fortune with it.")
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

Command(INTL( 12187, "HEARTSTONE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 6)
	Conversation
	INTL( 12188, "Look, I would like to continue talking with you but I'm a very busy man. I must attend to a \"problem\" "
	"and each minute I spend talking is a minute I don't spend fixing it. If you don't mind...")
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

Command(INTL( 1640, "PROBLEM"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 6)
	Conversation
	INTL( 12189, "Bah! No one is to be trusted these days it seems! Urik the tailor master has neglected to pay his \"duties\" "
	"to the guild coffers and he still receives the benefits.")
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

Command2(INTL( 12190, "DUTY"), INTL( 12191, "DUTIES"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 6)
	Conversation
	INTL( 12192, "He says he paid double the standard fees last month knowing that he would have trouble paying this month. "
	"The problem is, the amount counted in the coffers says otherwise. People like him are what give merchants "
	"a bad name! Don't they know they shouldn't bite the hand that feeds them? Anyway, now for the \"mercenaries\"...")
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

Command(INTL( 12193, "MERCENAR"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 6)
	Conversation
	INTL( 12194, "Hey! You're a mercenary, aren't you? Would you do this small \"task\" for me? I will pay you and I can even help "
	"you find the Nomad. I'm a merchant after all, I know people.")
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

Command(INTL( 8627, "TASK"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 6)
	Conversation
	INTL( 12195, "I already told you who this is about in my ramblings. Urik the tailor master hasn't paid his duties this month. "
	"I need you to pay him a visit and recover the money he owes the guild. Look around town and I'm sure you will "
	"find him hiding in his shop.")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 7)
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

Command(INTL( 2261, "MONEY"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 9)
	IF(Gold>=1000)
		Conversation
		INTL( 12196, "Give me that money so I can put it somewhere safe. Now, about \"Nomad\"...")
		TakeGold(1000)
		GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 11)
		PRIVATE_SYSTEM_MESSAGE(INTL( 12197, "You give 1000 gold to Ethan."))
		GiveXP(40000)
		PRIVATE_SYSTEM_MESSAGE(INTL( 12198, "You receive 40000 experience points."))
	ELSE
		Conversation
		INTL( 12199, "You WHAT? You spent MY gold? Well, now you can pay back \"double\" what Urik gave you!")
		GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 10)
	ENDIF
ELSE
	Conversation
	INTL( 12200, "Unless you have some for me, I don't have anything to say.")
ENDIF

Command(INTL( 12201, "DOUBLE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 10)
	Conversation
	INTL( 12202, "That's what you get for trying to cross me! Now don't come back until you have 2000 gold!")
	BREAK
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

Command(INTL( 11802, "NOMAD"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 11)
	Conversation
	INTL( 12203, "Yes, I am coming to that. But first, I must be honest with you... I wasn't really rambling about Urik "
	"before. I was counting on the fact that you would take this job and teach him a \"lesson\".")
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

Command(INTL( 12204, "LESSON"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 11)
	Conversation
	INTL( 12205, "Oh don't worry, he really did owe me the money. You see, Urik is a friend of Nomad's and I \"suspect\" they "
	"are working together for someone else.")
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

Command(INTL( 12206, "SUSPECT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 11)
	Conversation
	INTL( 12207, "I was about to investigate myself before you came along. The other day, I overheard Urik talking to Nomad "
	"about the \"Obsidian\" \"Conclave\" or something like that.")
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

CmdAND(INTL( 12208, "OBSIDIAN"), INTL( 12209, "CONCLAVE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 11)
	Conversation
	INTL( 12210, "I don't know what it is, but from the sound of it, I can tell you right now it doesn't feel right. That's "
	"why I decided to \"help\" you find Nomad.")
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

Command(INTL( 554, "HELP"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 11)
	Conversation
	INTL( 12211, "I set an associate of mine on your tail while you paid your visit to Urik earlier. While you had him "
	"distracted, I had my associate steal a set of \"keys\" from behind Urik's counter.")
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

Command(INTL( 8191, "KEY"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 11)
	Conversation
	INTL( 12212, "I believe that one of these keys will open the door to Nomad's \"house\". Here you go, they're all yours.")
	GiveItem(__OBJ_NOMAD_HOUSE_KEY)
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 12)
	PRIVATE_SYSTEM_MESSAGE(INTL( 12213, "Ethan gives you a set of keys."))
ELSE
	Conversation
	INTL( 12214, "I believe that one of these keys will open the door to Nomad's \"house\".")
ENDIF

Command(INTL( 9161, "HOUSE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) >= 12)
	Conversation
	INTL( 12215, "His house is located somewhere in the south part of town. If you search inside, you might find some clue "
	"as to where he left.")
ELSE
	Conversation
	INTL( 12182, "I can't help you with that right now, I'm rather busy.")
ENDIF

Command(INTL( 483, "NAME"))
INTL( 12216, "My name is Ethan.")

Command(INTL( 12217, "ETHAN"))
INTL( 12218, "That's what I said, Ethan.")

Command(INTL( 489, "WORK"))
INTL( 12219, "I am the head of the merchant's guild.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 973, "Goodbye.")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 12220, "...36, 37, I'm sorry, you were saying?")
ELSE
	Conversation
	INTL( 12221, "If you don't have anything relevant to say, I must get back to my work now.")
ENDIF

EndTalk
}


