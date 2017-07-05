#pragma hdrstop
#include "WindhowlSamaritan.H"

WindhowlSamaritan::WindhowlSamaritan()
{}

WindhowlSamaritan::~WindhowlSamaritan()
{}

extern NPCstructure::NPC Samaritan;

void WindhowlSamaritan::Create( void )
{
	npc = ( Samaritan );
	SET_NPC_NAME( "[2909]Windhowl Samaritan" );
	npc.InitialPos.X = 1794; 
	npc.InitialPos.Y = 1275; 
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

void WindhowlSamaritan::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF (CheckFlag ( __OFFENSIVE_TALK ) < 10 )
	Conversation
	INTL( 1077, "Welcome to Windhowl, friend. How may I help you?")
ELSE
	Conversation
	INTL( 1078, "Us Samaritans don't like people who speak foul language. Leave me be.")
	GiveFlag ( __OFFENSIVE_TALK, (CheckFlag ( __OFFENSIVE_TALK ) - 1 ) )
	BREAK
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1079, "I'm the official Windhowl Samaritan.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1080, "My job's to answer any questions you have... Well, almost. I don't know everything, "
"but I try anyway. I'm specialized in travelling, exploration and the \"world\" in general.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 1081, "It's a shame that so many have been cursed by this fiend from below! I have no cure for "
"you, but perhaps you should seek someone who does. I believe she's long gone from these "
"parts, but Annabelle would surely help you if she knew of your plight.")

Command(INTL( 884, "WORLD"))
INTL( 1082, "By now, you're certainly aware that this is the world of Althea, and that you're walking on the "
"island of Arakas in the Kingdom of Goldmoon. I'm paid to sing the merits of our good king, so "
"please don't say anything bad about him. Perhaps I could tell you about the \"races\" who live here?")

Command(INTL( 1083, "RACE"))
INTL( 1084, "There are several races living in this world. Sages and Loremasters divide them between the Higher "
"Races and the Lesser Races. Of the Higher Races, only humans still walk the world. Both the Elves "
"and the Dwarves are gone, they say. The Lesser Races include the \"Goblins\" and the \"Orcs\". For obvious "
"reasons, humans don't get along very well with the Lesser Races.")

Command2(INTL( 539, "GOBLIN"),INTL( 744, "ORC"))
INTL( 1085, "Goblins are by far smaller than Orcs, but they are also more numerous. They're also more savage and "
"less educated. Orcs aren't very bright, mind you, but they're still a bit more evolved than the Goblins. "
"Me, I'd never give the time of day to either one, I'd just run in the other direction. Those two races "
"are pretty impressive in combat, and I don't have a death wish.")

Command(INTL( 1086, "LANGUAGE"))
INTL( 1087, "Ah, I see you're a clever one. Few people ask me about this. Yes, some other races speak a different "
"tongue than ours. Take the Orcs, for instance. They call their language Orkentung, or something like "
"that, and if you can make sense of it, you can *really* earn their trust. But then again, who'd want "
"that, eh?")

Command(INTL( 1088, "ORKENTUNG"))
INTL( 1089, "Hard to pronounce, eh? Well, anyway, if you're really interested, I'll tell you a secret. I know a bit "
"of Orkentung, studied it with an orc who's friendly to humans. Anyway, I'm no expert, but it's not "
"entirely different from our own, just pronounced really weird. For starters, they simplify some letters, "
"like the *th* sounds, which become *d* sounds. Oh, and they don't have the verb *to be*. Pretty strange, "
"wouldn't you say? But that's how they talk.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 1090, "Lighthaven's not quite as civilized as \"Windhowl\", but I would think the people are nicer there, "
"and crime isn't as prevalent as it is here. And with all the monsters and bandits roaming the "
"route between here and there, trade has been very bad for them. A real shame, if you ask me.")

Command(INTL( 514, "WINDHOWL"))
INTL( 1091, "We're pretty happy with the way \"Lord\" \"Sunrock\" has been running things, but even he hasn't been "
"able to rid us of the bandits and monsters. Ah well. Even the mighty can fail, I guess.")

Command(INTL( 1092, "LORD SUNROCK"))
INTL( 1093, "Not the most gentle of fellows, for sure, but one who speaks his mind honestly and defends the "
"interests of the citizens of Windhowl with an iron fist. You may not like him, but you have to "
"respect his resolve. He always has a mission or two to give to people, so perhaps you should visit "
"him and offer your services.")

Command(INTL( 888, "SAMARITAN"))
INTL( 1094, "There's one of us Samaritans in almost every city. We answer your questions. Of course, you could "
"always read the manual, but in case you didn't, we're there for you.")

Command2(INTL( 890, "CITY"),INTL( 891, "CITIES"))
INTL( 1095, "Cities are fairly save. On the island of Arakas--where we are right now--you have only two cities: "
"\"Lighthaven\" and \"Windhowl\". We don't know much about the other cities in the world.")

Command2(INTL( 700, "SPELL"),INTL( 1096, "MAGIC"))
INTL( 1097, "I don't know much about magic myself, but there are dozens of skilled magicians who can teach you "
"more about it. You just have to ask the right questions, of course. Me, I just know it's got "
"something to do with \"Karma\", but I've never cared much for magic, so don't ask me any more.")

Command(INTL( 1886, "KARMA"))
INTL( 1099, "It's like I said, I don't know much about it. Ask someone else, perhaps some wizard...")

Command(INTL( 896, "QUEST"))
INTL( 1100, "Quests, as I'm sure you know by now, abound, and the brave and mighty adventurers such as yourself "
"are never out of work if they wish to undertake them. You just have to know who to ask, what to say "
"and what items or information they need. Also, you should distinguish minor quests the major one. "
"Indeed, there's something tragic happening in the world, and if you really want to do something about "
"it, just visit Balork in the dungeon below the temple in Lighthaven, and you'll know what I mean.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 1101, "Ooh, big vocabulary, I see... Grow up, willya?")
GiveFlag ( __OFFENSIVE_TALK , ( CheckFlag ( __OFFENSIVE_TALK ) + 1 ) )
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 933, "Thank you for spending some time with an old man. Come again.")
BREAK

Default
INTL( 1102, "I'm sorry, could you rephrase that? I'm somewhat old and easily confused by young people "
"such as yourself.")

EndTalk
}

