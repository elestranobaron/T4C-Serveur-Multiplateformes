#pragma hdrstop
#include "Lantalir.H"

Lantalir::Lantalir()
{}

Lantalir::~Lantalir()
{}

extern NPCstructure::NPC LantalirNPC; 
 
void Lantalir::Create( void )
{
	npc = ( LantalirNPC );
	SET_NPC_NAME( "[2900]Lantalir Rainmist" ); 
	npc.InitialPos.X = 2801;
	npc.InitialPos.Y = 220; 
	npc.InitialPos.world = 0;
}

void Lantalir::OnTalk( UNIT_FUNC_PROTOTYPE )

{
InitTalk

Begin
INTL( 800, "I greet you to our camp, a haven of peace in this rough land. Join me in my \"meditation\".")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 801, "Lantalir Rainmist is the name. I have the peculiar ability, for "
"one so young as I am, to summon the rain with a single thought.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 802, "I was an orphan, but Yrian raised me into the man I am now. "
"He then recruited me into the \"Order\" \"of\" \"Nature\". Even though "
"I am still an apprentice, I have grown in powers quite rapidly."
"My current work is to protect the forest from the \"goblin\"'s "
"vicious attacks and various other \"errands\".")

Command(INTL( 803, "MEDITATION"))
INTL( 804, "To meditate is to heal the soul. The art of meditation is a discipline that takes time to master. "
"If you wish, I could \"teach\" you how to use it.")

Command2(INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 812, "Very good, let us begin then.")
CreateSkillList
	AddTeachSkill( __SKILL_MEDITATE, 1, 3000 )
SendTeachSkillList

Command(INTL( 502, "TRAIN"))
INTL( 815, "Very good, then let us begin your training.") 
CreateSkillList
	AddTrainSkill( __SKILL_MEDITATE, 100, 100 )
SendTrainSkillList

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 820, "Balork's curse? That's horrible!")

Command(INTL( 523, "ANNABELLE"))
INTL( 821, "Annabelle? I heard she is a lovely lady, but somewhat odd, even though I've never " 
"seen her myself.") 

Command(INTL( 822, "FEYLOR"))
""
IF (CheckNPCFlag (__BOOK_OF_FEYLOR_QUEST) > CurrentRound)
	Conversation
	INTL( 823, "The book of Feylor? I am studying it right now, even though a few "
	"pages are missing or have crumbled to dust. It is very peculiar, "
	"it seems as if each time I read those pages, they disappear in "
	"front of my eyes. I can not explain this and yet... Oh well! *sigh*")
ELSE
	IF (CheckItem (__OBJ_BOOK_OF_FEYLOR) >= 1 )
		GiveNPCFlag(__BOOK_OF_FEYLOR_QUEST, rnd.roll( dice( 1, 2 ) ) HOURS TDELAY)
		TakeItem(__OBJ_BOOK_OF_FEYLOR)
		GiveItem(__OBJ_SAPPHIRE_BRACELET) 
		GiveXP(2500)
		Conversation
		INTL( 824, "You have found the book of Feylor I seek? Wonderful! I can now "
		"further my studies. I had another book, but for some reasons, it "
		"disappeared. Isn't that odd, don't you think? It's not important "
		"anyhow since you have brought me another copy. I give you this "
		"magnificient sapphire bracelet in exchange. {You} "
		"{have} {been} {awarded} {2500} {experience} {points.}")
		// This Quest can be looped. The 1,2 hours delay ensure that this
		// cannot be exploited so easily though. 
	ELSE
		Conversation
		INTL( 825, "\"Yrian\" \"Earthsong\" has given me the \"errand\" of retrieving a long-lost "
		"book named the book of Feylor.")
	ENDIF
ENDIF

Command(INTL( 826, "ERRAND"))
""
IF (CheckNPCFlag (__BOOK_OF_FEYLOR_QUEST) > CurrentRound)
	Conversation
	INTL( 827, "\"Yrian\" \"Earthsong\" always gives me many tasks to complete.")
ELSE
	Conversation
	INTL( 828, "One of them consists of retrieving the book of \"Feylor\". It was lost "
	"a few decades ago in the now-ruined city hidden behind the mountains "
	"to the south. Even though I have gained a fair amount of power, I am "
	"still not strong enough to delve into the \"labyrinth\" that is supposed "
	"to lead into the \"Ruined\" \"City\".")
ENDIF

Command(INTL( 829, "LABYRINTH"))
INTL( 830, "I do not even know where the entrance is located exactly. However, I do "
"know that it is required to go through it if one wants to reach the "
"\"Ruined\" \"City\".")

Command(INTL( 831, "RUINED CITY"))
INTL( 832, "Decades ago, the city was abandoned for reasons unknown and the main "
"mountain entrance was sealed. The only way to reach it is to go through "
"the \"labyrinth\".")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 833, "Lighthaven is a town located on the south eastern part of this "
"island. Its sister town is named \"Windhowl\" and is located "
"on the south western part.")

Command(INTL( 514, "WINDHOWL"))
INTL( 834, "The inhabitants of Windhowl do not share our concerns for "
"nature, they are much too busy doing business with Lighthaven "
"and fighting brigands.")

Command(INTL( 539, "GOBLIN"))
INTL( 835, "The goblins are controlled by \"Jarko\" the necromancer and they are "
"not bright enough to understand that if they do not stop the "
"desecration of the forest at once, we will all perish. The "
"\"Forest\" \"Guardians\" are doing a good job of eliminating them "
"on sight, however.")

Command(INTL( 836, "FOREST GUARDIAN"))
INTL( 837, "The Forest Guardians are trees that are able to walk. Do not attack "
"them, they are our friends and they are very powerful.")

Command(INTL( 746, "DRUID"))
INTL( 838, "I am still an apprentice, but once I am a true disciple, I shall rightly "
"earn the title of Druid.")

Command2(INTL( 682, "YRIAN"),INTL( 683, "EARTHSONG"))
INTL( 839, "He is our leader and I consider him as my father. He is also the bearer "
"of the \"Stone\" \"of\" \"Life\".")

Command(INTL( 475, "STONE OF LIFE"))
INTL( 840, "The Stone of Life can drastically increase the strength of our "
"elemental magic. \"Yrian\" \"Earthsong\" once allowed me to use its power "
"to summon a rainstorm, but he made me stop it promptly, for it is "
"not a good thing to tamper with the weather.") 

Command2(INTL( 841, "DUNIKUS"),INTL( 842, "HORNWIND"))
INTL( 843, "Dunikus? Did you know that he can control winds? Really, I've seen him "
"hovering a few feets above the ground. The air swirled about him like "
"a small tornado.")

Command2(INTL( 541, "JARKO"),INTL( 693, "NECROMANCER"))
INTL( 844, "Jarko? Sorry, but I do not really want to talk about him.")

Command(INTL( 680, "ORDER OF NATURE"))
INTL( 845, "The Order of Nature was created to preserve nature. We rarely rely "
"on violence, for we do not wish harm to nobody. Sadly, it seems "
"the only viable solution against foul creatures such as \"goblins\". The leader "
"and founder of our order is \"Yrian\" \"Earthsong\".")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 846, "The key is to protect nature, remember that my friend.") BREAK

Default
INTL( 847, "Hmmmmm! Sorry I can not help you on that one.")

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Lantalir::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Rolph data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL( __SKILL_MEDITATE, 1, 3000 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

	NPC_DATA_TRAIN		
		TRAIN_SKILL( __SKILL_MEDITATE, 100, 100 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
}
