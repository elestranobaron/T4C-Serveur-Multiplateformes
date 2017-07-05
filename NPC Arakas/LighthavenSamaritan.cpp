#pragma hdrstop
#include "LighthavenSamaritan.H"

LighthavenSamaritan::LighthavenSamaritan()
{}

LighthavenSamaritan::~LighthavenSamaritan()
{}

extern NPCstructure::NPC Samaritan;

void LighthavenSamaritan::Create( void )
{
	npc = ( Samaritan );
	SET_NPC_NAME( "[2901]Lighthaven Samaritan" );
	npc.InitialPos.X = 2931; 
	npc.InitialPos.Y = 1072;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

/* The Lighthaven Samaritan Speech.
 * Modified by Desboys (SD) according to writers' work.
 * TODO: Put the new quest's strings into the LNG files.
*/
void LighthavenSamaritan::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT QUESTION = 1;

InitTalk

Begin
""
IF (CheckFlag ( __OFFENSIVE_TALK ) < 10 )
#ifdef DESBOYSISDUMB
	// (SD : 11/04/05)
	IF (CheckFlag ( __FLAG_NUMBER_OF_REMORTS ) > 2 )
		Conversation
		INTL( 12959, "Hello again, my friend. It looks to me as if you have been traveling quite a bit. Seems that you are becoming quite the \"adventurer\" ")
	// End of mod.
	ELSE
#endif
		Conversation
		INTL( 848, "Hello. Welcome to Lighthaven. Do you have any questions?")
		SetYesNo ( QUESTION )
#ifdef DESBOYSISDUMB
	ENDIF
#endif
ELSE
	Conversation
	INTL( 849, "Your manner of speech is too offensive for my taste. Go away.")
    GiveFlag ( __OFFENSIVE_TALK, (CheckFlag ( __OFFENSIVE_TALK ) - 1 ) )
	BREAK
ENDIF

YES ( QUESTION )
    Conversation
	INTL( 850, "Wonderful. I'm here to answer them. If you notice I've put the \"emphasis\" on "
	"a \"keyword\", simply say that word and I'll give you further information on it.")
NO ( QUESTION )
    Conversation
	INTL( 851, "No problem, friend. Come back when you need to know something. I'll be glad to help.")
YesNoELSE ( QUESTION )
    Conversation
	INTL( 852, "Just answer \"yes\" or \"no\", all right?")
	SetYesNo ( QUESTION )

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 853, "You can call me the Lighthaven Samaritan.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 854, "I just stay here all day and answer \"questions\" about this place. That's what I do."
"Perhaps I might send you on an \"errand\" if that is what you wish.")

Command(INTL( 523, "ANNABELLE"))
INTL( 855, "Annabelle? I heard she is a lovely lady, but somewhat odd even though I've never " 
"seen her myself.") 

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 856, "Curse that Balork and his Brand! There are many who walk the land "
"and bear his mark.")

Command(INTL( 857, "KEYWORD"))
INTL( 858, "Not every NPC uses keywords, but most folks have something specific to say about certain "
"topics. Make note of them and bring it up in the conversation. They might have more to say "
"than it first appears.")

Command(INTL( 859, "EMPHASIS"))
INTL( 860, "There you go. You're a quick study.")

Command3(INTL( 861, "QUESTION"),INTL( 862, "INFO"),INTL( 554, "HELP"))
INTL( 863, "I can tell you about several things, but I need to know whether you want \"basic\" "
"information or \"advanced\" information. So which one is it?")

Command (INTL( 864, "BASIC"))
INTL( 865, "It's not always easy to start adventuring, I know. I was once a young person, just like you, "
"and I wish I had had someone to show me the ropes back then. Anyway, back to business... When "
"talking to people, you can always ask them their \"name\" and about their \"work\". Most "
"will gladly tell you more. Try it, you'll see. Then ask me again to tell you about "
"\"functions\".")

Command ( INTL( 866, "FUNCTION") )
INTL( 867, "There are some magic buttons that can help you memorize some of the basic functions. F1 gives "
"you a summary of online help. F2 makes you drink a healing potion so you don't have to rummage "
"through your backpack in the middle of combat. The rest are documented in your reference tome. "
"Would you like me to tell you more about \"weapons\", \"armors\" and various \"items\"? Or "
"would you like me to talk about \"communication\" and \"advanced\" features?")

Command(INTL( 868, "COMMUNICATION"))
INTL( 869, "Ah, someone who likes to talk... That's great, because you'll find plenty of people to talk to "
"in this world. There are communication tools such as \"paging\" and \"shouting\" that can help "
"you contact other individuals elsewhere who can answer some of your questions.")

Command2(INTL( 870, "PAGING"),INTL( 871, "PAGE"))
INTL( 872, "The \"page\" command allows you to privately send a message to someone who is not nearby or with "
"whom you want to have a private conversation in public, sort of like whispering. You simply type "
"/<name> <text>, where <name> is the name of the person you want to talk to and <text> is the "
"message you want this person to receive. If you do not want to receive pages, you can press <ESC> "
"and toggle your page option to off.")

Command(INTL( 873, "SHOUT"))
INTL( 874, "The \"shout\" command allows you to send public messages for everyone to read. You simply type "
":<text>, where <text> is the message you want to send to everyone. If you do not want to be disturbed "
"by shouts, you can press <ESC> and toggle your shout option to off.")

Command(INTL( 875, "ADVANCED"))
INTL( 876, "If you're all right with the \"basics\" I've already explained, how about we now discuss some "
"more serious topics, such as \"spells\", \"skills\", and \"quests\"? Or would you rather hear "
"more about the \"environment\", the \"world\" and the \"cities\"?")

Command(INTL( 877, "ENVIRONMENT"))
INTL( 878, "The main thing you have to remember is that night and day follow each other in succession. When "
"it's night, it's usually darker outside than during daytime. Sometimes, you need a \"torch\" to "
"see around. That's especially true when you go inside \"caves\" and \"dungeons\".")

Command(INTL( 879, "TORCH"))
INTL( 880, "You can buy those at any merchant's store. They're pretty inexpensive, they don't weigh much, "
"and you can bet you'll find them useful when you go into \"caves\" and \"dungeons\". You can "
"sometimes find them in treasure chests.")

Command2(INTL( 881, "CAVE"),INTL( 882, "DUNGEON"))
INTL( 883, "Caves and dungeons are dark, dangerous places. Dungeons, because they were man-built, occasionally "
"have torches on the walls, so they tend to be lighter than caves. Caves, which exist because of "
"some fluke of nature, are much darker. It would be foolish to enter them without a light source.")

Command(INTL( 884, "WORLD"))
INTL( 885, "This is the world of Althea, but I'm sure you already know that. You are in the Kingdom of Goldmoon, "
"on the island of Arakas, one of the two islands of the kingdom. This is the city of \"Lighthaven\"; "
"the other city southwest of here is \"Windhowl\".")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 886, "This is the town of Lighthaven. We live fairly quiet lives, but there has been a great deal of "
"trouble lately, what with the goblins and undeads and orcs and demons and brigands and all these "
"adventurers roaming about. Just ask other people here about these... You'll see. Anyway, if you "
"want my advice, don't leave town unless you're trained and armed to the teeth, or you have someone "
"to protect you.")

Command (INTL( 514, "WINDHOWL"))
INTL( 887, "Windhowl is a larger town lying southwest from here. It takes a bit to get there, but the people "
"are friendly enough. Lord Sunrock rules the town with an iron fist. If you go there, make sure "
"to visit the Windhowl \"Samaritan\" and ask him a few questions.")

Command(INTL( 888, "SAMARITAN"))
INTL( 889, "There's one like me in almost every city. Our job is to make life easier for you. Of course, if "
"you want more information, you could always read the manual...")

Command2(INTL( 890, "CITY"),INTL( 891, "CITIES"))
INTL( 892, "Cities are fairly safe. On the island of Arakas--where we are right now--you have only two cities: "
"\"Lighthaven\" and \"Windhowl\". There are many more cities in the world beyond, but we don't "
"have much to do with them.")

Command(INTL( 700, "SPELL"))
INTL( 893, "Magic is present in the world of Althea. Its nature is complex and I won't get into it, but "
"suffice it to say that it is manipulated with \"mana\", the equivalent of an individual's "
"magical strength and endurance. Spells can only be \"learned\" from certain \"teachers\", but only "
"if the student is gifted enough and has already learned the \"pre-requisites\".")

Command(INTL( 894, "SKILL"))
INTL( 895, "Skills represent learned abilities which allow you to accomplish certain feats during the course "
"of your adventures. They must be learned from a \"teacher\". Often, teachers will not train a "
"student who does not have certain natural abilities (\"stats\") or has not reached a certain "
"\"level\" of expertise.")

Command(INTL( 896, "QUEST"))
""
	GiveFlag ( __KNOW_ABOUT_QUEST , 1 )
	Conversation
	INTL( 897, "During the course of your adventures, several inhabitants of the world will ask you for assistance "
	"in return for certain rewards, whether it be gold, items or information. We refer to this as "
	"quests. Make sure you jot down a few notes when you embark on a quest, lest you never finish it "
	"and miss some important clue. Quests can either be \"minor\" or \"major\", depending on whether "
	"they have something to do with the over-arcing storyline or not.")

Command2(INTL( 898, "MINOR"),INTL( 899, "MAJOR"))
""
IF ( CheckFlag ( __KNOW_ABOUT_QUEST ) > 0 )
	Conversation
	INTL( 900, "The 4th Coming is a complex tale, one which you will discover as you go along. Some of the "
	"missions you will undertake may have to do with the grand scheme behind the scenes; we call "
	"those major quests. Some other quests are just side tracks which you don't have to follow; "
	"we call those minor quests. They are not always necessary to further the plot, so you can ignore "
	"them if you prefer.")
ELSE
	Conversation
	INTL( 901, "I'm not sure I understand what you mean? Are you talking about \"quests\"?")
ENDIF

Command(INTL( 902, "MANA"))
INTL( 903, "Everyone has mana, but not everyone has enough of it or knows how to use it to weave magic. Those "
"who do must spend a great deal of mana. Usually, the more mana is spent, the more powerful the "
"spell. Mana is spent with every spell, but rest and potions can help regenerate it, just like "
"physical damage (\"hit\" \"points\").")

Command2(INTL( 502, "TRAIN"),INTL( 495, "LEARN"))
INTL( 904, "You don't know everything you need to know when you start adventuring. You'll quickly realize "
"there are \"skills\" and \"spells\" that you need to learn, and you can only get that training from specific "
"teachers living all over this island--and beyond.")

CmdAND(INTL( 905, "PRE"),INTL( 906, "REQUISITE"))
INTL( 907, "Sometimes, in order to \"learn\" something, some tutors will expect you to have already learned "
"something more basic, what we call a pre-requisite. They won't always tell you what it is, though, "
"so you may need to ask around and find someone who can tell you what you're missing. \"Teachers\" "
"are like that, I guess. Help yourself and they'll help you.")

Command(INTL( 908, "TEACHER"))
INTL( 909, "Yeah, you need those if you're to learn anything. Sure, you may think that because you can wield "
"a sword you could train someone in using it too, but it's not that simple. You need to know what "
"you're doing, so you need someone who's willing to \"train\" you. Most teachers will ask you "
"for some money, however, so don't visit a potential tutor empty handed.")

Command(INTL( 910, "STAT"))
INTL( 911, "We rate everyone according to a restricted number of values, named stats, which represent that "
"person's strengths and weaknesses. Most starting stats range roughly between 10 and 20, but these "
"values tend to go up with levels. You can see your stats by pressing <ctrl-s>.")

Command(INTL( 912, "LEVEL"))
INTL( 913, "As you gain experience, your skills and stats go up. Your level will also go up. A level indicates "
"how far along you've come and how generally powerful your character is. ")

Command(INTL( 914, "WEAPON"))
INTL( 915, "There are dozens of weapons in the game, some more powerful than others. The price is usually a "
"good indication of their combat effectiveness, but not always, so don't rely on that. Try them "
"out and you'll soon figure out which one allows you to do more damage in combat. Say, perhaps "
"you'd like me to tell you a bit about \"combat\"?")

Command (INTL( 916, "ARMOR"))
INTL( 917, "Kind of like weapons, there are a good number of armors available; some are good, some are bad, "
"and some are both good and bad for you. Check your stats carefully and you should quickly find "
"out which ones protect you better. Say, perhaps you'd like me to tell you a bit about "
"\"combat\"?")

Command(INTL( 918, "COMBAT"))
INTL( 919, "It's all pretty simple, really. You use a \"weapon\" to attack and wear \"armor\" to defend yourself. "
"If the attacker's power is higher than your defenses (also called AC, for armor class), "
"you may end up taking damage (\"hit\" \"points\", or HPs). If you lose all your HPs, you die. This "
"isn't the tragic end, however, since you own a Gem of Destiny. That will take you back to the "
"temple, where you can get healed and resume your journeys.")

Command(INTL( 920, "HIT POINT"))
INTL( 921, "Hit points measure how tough you are and how much punishment you can take before dying. The higher "
"your level, the more hit points you tend to have. Endurance also plays a factor in the number of "
"hit points you have. Hit points recover over time, but you can also use \"healing\" methods.")

Command(INTL( 569, "HEAL"))
INTL( 922, "Other than time, two things can heal you: spells and potions. Potions can be bought in shops or "
"found in chests. Spells can be learned from a \"teacher\". You can also ask some priests to heal "
"you. Some do it for free, some do it for money.")

Command (INTL( 923, "ITEM"))
INTL( 924, "You start with some items in your backpack (press ctrl-i to have your backpack pop up). Use them "
"wisely. Replacing them may cost you money, so don't throw them away unless your backpack is "
"full and you absolutely need the space. Most items are useful, but not all of them, so don't "
"expect every mug of beer to be of great value.")

Command(INTL( 826, "ERRAND"))
""
IF (CheckFlag(__NEWBIE_QUEST) == 0)
    Conversation
    INTL( 925, "So.. you wish to do an errand for me? Very well then... let's see... "
    "Go into the temple's basement and slay at least 15 rats. Then, come "
    "back to me and I shall give you a reward.")
    GiveFlag(__NEWBIE_QUEST, 1 )
ELSEIF (CheckFlag(__NEWBIE_QUEST) == 2)
    Conversation
    INTL( 926, "You have already done the simple errand I gave you. It is time for "
    "you to go on your own. Perhaps you would like to explore deeper in the "
    "dungeon...")
ELSEIF ((CheckFlag(__NEWBIE_QUEST) == 1) && (CheckFlag(__RATS_KILLED) >= 15))
    int nRatsKilled = CheckFlag( __RATS_KILLED );
    Conversation
    INTL( 927, "You have killed ") C( nRatsKilled ) INTL( 928, " rats? That's great."
    "You have now accomplished your first errand. That wasn't hard was it? "
    "{You} {have} {been} {awarded} {2500} {experience} {points.}")
    GiveXP(2500)
    GiveFlag(__NEWBIE_QUEST, 2) 
    RemFlag(__RATS_KILLED) 
ELSE
    int nRatsKilled = CheckFlag( __RATS_KILLED );
    int nCurrentRatsKilled = 15 - nRatsKilled;
    Conversation
    INTL( 929, "You have killed only ") C( nRatsKilled ) INTL( 930, " rats. You will "
    "have to slay at least ") C( nCurrentRatsKilled ) INTL( 931, " more of these small "
    "rodents before your errand is completed.")
ENDIF

// (SD : 11/04/05)
#ifdef DESBOYSISDUMB
Command("ADVENTURER")
INTL( 12960, "I must say I am a bit surprised. I remember when you first came to Lighthaven you were "
"rather inexperienced. Although, I suppose, we were all \"youthful\" at one time...")

Command("YOUTHFUL")
INTL( 12961, "Ha! Yes, even an old man like me was once ambitious in his youth. And back then we "
"had to learn for ourselves the way of the world! Feels like only yesteday that I was "
"traveling the lands... but alas, that is ancient \"history\"...")

Command("HISTORY")
INTL( 12962, "So you want to hear my story, eh? I guess I could tell you a little about my \"past\".")

Command("PAST")
"I have told very few about my past. It seemed it better not to stir up old feelings "
"around here. I try to not dwell on old times, but help young travelers, such as you "
"once were. You \"remind\" me of myself at your age..."

Command("REMIND")
"I came to Lighthaven as a young man, searching for a life other then a farmer's son. "
"I started with odd jobs around town, running errands for the merchants and priests. "
"It paid a decent wage, and I got to know the important people of the \"towns\"."

Command("TOWNS")
"Often times I was asked to travel to Windhowl, delivering packages and documents. "
"Many nights I would be sweeping in the Drunken Dragon's Inn, listening to the drifters "
"tell their stories of the world outside of Arakas. I wanted to travel like them, see "
"the world. Then one night a \"strange\" man came to the inn."

Command("STRANGE")
"Not that I could see his face. I just knew he had a powerful presence about him, even "
"under that hooded cape. He was kind enough, though he hardly spoke. On the second night "
"he was there, he asked me to bring a sealed message to the priests in Lighthaven, and "
"paid me greatly for doing so. When I brought it to the priest, he thanked me and gave "
"me \"something\" to return to the man at the inn."

Command("SOMETHING")
"It was a ring with an odd crest on it. I hurried back to Windhowl and gave him the ring. "
"He then asked me questions about my family and such. He never answered any of mine though. "
"At the end of the night, he asked me if I would be interested in becoming his apprentice. "
"Not that I knew what he really did at the time, but without a second thought I \"agreed\"."

Command("AGREED")
"The following morning we set off, and so began my education in the world of adventuring. "
"For many years we travelled Althea, recovering lost artifacts for the church. Along the "
"way he taught me how to fight and survive in the wilderness. He taught me a great many "
"things. And then one morning he was \"gone\"."

Command("GONE")
"I awoke at our campsite and he had vanished. All of his things were gone as well. I "
"searched for months to find a trace of him, but there was no use... I still do not know "
"whatever happened to him. Eventually, I returned to Lighthaven, where I was a hired "
"\"escort\" for the church."

Command("ESCORT")
"By then the roads had become quite dangerous. Brigands were rampantly attacking travellers "
"between the towns. And so the priests hired me to protect certain members of the town that "
"might be in danger when travelling alone. Most of the time it was priests carrying food "
"and medicine, but occaisonally it would be a wealthy merchant transporting goods. I made "
"sure \"every\" convoy arrived safely."

Command("EVERY")
"Well almost every convoy... only once was I ever taken off guard. That is not something I "
"wish to discuss any further. After that I retired from guarding the townfolk. I swore I "
"would never pick up a sword again. Since then I remain here, warning young adventurers on "
"the dangers outside of the towns and how they might prepare themselves. On occasion, I will "
"be asked to find someone \"trustworthy\" in running an errand or two..."

Command("TRUSTWORTHY")
"You? Yes, I suppose you have proved yourself capable of handling great tasks. Actually "
"there is something I might be able to entrust to you, if you are \"willing\"..."

Command("WILLING")
"Uh... Oh... My head... I'm sorry, dear \"adventurer\", i can't tell you more."
#endif
// End of mod.

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 932, "That's hardly appropriate language! This will not win you friends here.")
GiveFlag ( __OFFENSIVE_TALK , ( CheckFlag ( __OFFENSIVE_TALK ) + 1 ) )
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 933, "Thank you for spending some time with an old man. Come again.")
BREAK

Default
INTL( 934, "I'm sorry, could you rephrase that? I'm somewhat old and easily confused by young people "
"such as yourself.")

EndTalk
}

/*
From Scarlett:
Lighthaven Samaritan
(seraph only?)

:Hello again, my friend. It looks to me as if you have been traveling quite a bit. Seems that you are becoming quite the "adventurer".

Adventurer: I must say I am a bit surprised. I remember when you first came to Lighthaven you were rather inexperienced. Although, I suppose, we were all "youthful" at one time...

Youthful: Ha! Yes, even an old man like me was once ambitious in his youth. And back then we had to learn for ourselves the way of the world! Feels like only yesteday that I was traveling the lands... but alas, that is ancient "history"...

History: So you want to hear my story, eh? I guess I could tell you a little about my past.

Past: I have told very few about my past. It seemed it better not to stir up old feelings around here. I try to not dwell on old times, but help young travelers, such as you once were. You "remind" me of myself at your age...

Remind: I came to Lighthaven as a young man, searching for a life other then a farmer's son. I started with odd jobs around town, running errands for the merchants and priests. It paid a decent wage, and I got to know the important people of the "towns".

Towns: Often times I was asked to travel to Windhowl, delivering packages and documents. Many nights I would be sweeping in the Drunken Dragon's Inn, listening to the drifters tell their stories of the world outside of Arakas. I wanted to travel like them, see the world. Then one night a "strange" man came to the inn.

Strange: Not that I could see his face. I just knew he had a powerful presence about him, even under that hooded cape. He was kind enough, though he hardly spoke. On the second night he was there, he asked me to bring a sealed message to the priests in Lighthaven, and paid me greatly for doing so. When I brought it to the priest, he thanked me and gave me "something" to return to the man at the inn.

Something: It was a ring with an odd crest on it. I hurried back to Windhowl and gave him the ring. He then asked me questions about my family and such. He never answered any of mine though. At the end of the night, he asked me if I would be interested in becoming his apprentice. Not that I knew what he really did at the time, but without a second thought I "agreed".

Agreed: The following morning we set off, and so began my education in the world of adventuring. For many years we travelled Althea, recovering lost artifacts for the church. Along the way he taught me how to fight and survive in the wilderness. He taught me a great many things. And then one morning he was "gone".

Gone: I awoke at our campsite and he had vanished. All of his things were gone as well. I searched for months to find a trace of him, but there was no use... I still do not know whatever happened to him. Eventually, I returned to Lighthaven, where I was a hired "escort" for the church.

Escort: By then the roads had become quite dangerous. Brigands were rampantly attacking travellers between the towns. And so the priests hired me to protect certain members of the town that might be in danger when travelling alone. Most of the time it was priests carrying food and medicine, but occaisonally it would be a wealthy merchant transporting goods. I made sure "every" convoy arrived safely.

Every: Well almost every convoy... only once was I ever taken off guard. That is not something I wish to discuss any further. After that I retired from guarding the townfolk. I swore I would never pick up a sword again. Since then I remain here, warning young adventurers on the dangers outside of the towns and how they might prepare themselves. On occasion, I will be asked to find someone "trustworthy" in running an errand or two...

Trustworthy: You? Yes, I suppose you have proved yourself capable of handling great tasks. Actually there is something I might be able to entrust to you, if you are "willing"...

*/