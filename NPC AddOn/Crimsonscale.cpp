#pragma hdrstop
#include "Crimsonscale.h"

Crimsonscale::Crimsonscale()
{}

Crimsonscale::~Crimsonscale()
{}

extern NPCstructure::NPC CrimsonscaleNPC;

void Crimsonscale::Create( void )

{
	npc = CrimsonscaleNPC;
	npc.appearance = 20028;
	SET_NPC_NAME( "[12727]Crimsonscale" );
	npc.InitialPos.X = 842; 
	npc.InitialPos.Y = 2220;
	npc.InitialPos.world = 1;
	npc.boPrivateTalk = TRUE;
}

void Crimsonscale::OnAttacked( UNIT_FUNC_PROTOTYPE ){
{}
}

void Crimsonscale::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void Crimsonscale::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 33)
	Conversation
	INTL( 11907, "What are you doing here, mortal? You are not supposed to be here... now get OUT!")
	BREAK
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11908, "Welcome, friend. I am Crimsonscale. As you have probably guessed, I was the one "
	"who sent you the \"letter\".")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 34)
	Conversation
	INTL( 11909, "You must now travel to the Great Library of Althea to discover the true reason behind Olin Haad's "
	"raid on Lighthaven. Ask around at the temple in Silversky if you do not know where it is located.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 42)
	Conversation
	INTL( 11910, "The stage is set for the final confrontation... if you fail, the entire world will pay the price.")
ELSE
	Conversation
	INTL( 11911, "Well met, hero of a new legend. If you came all the way here just to see me, I appreciate it, but "
	"you certainly have better things to do than chatting with an old dragon.")
ENDIF

Command(INTL( 1301, "LETTER"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11912, "The letter was a necessary precaution. You see, I could not contact you directly "
	"because of all the parties involved. You probably have hundreds of questions and "
	"we will come around to them in time. For now though, let us start from the \"beginning\".")
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

Command(INTL( 10323, "BEGIN"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11914, "You are what we call a New Breed, a child born with the pain of his predecessors. "
	"The Nameless Bard was one such child... he too, was \"chosen\".")
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

Command(INTL( 11915, "CHOSEN"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11916, "In our Dharma, it is said that in the wake of a lost god, his children will awake and "
	"will demand to be avenged. When Lothar the Just died, \"Justice\" \"died\" along with "
	"him.")
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

CmdAND(INTL( 11917, "JUSTICE"), INTL( 11918, "DIED"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11919, "When Gluriurl duped the elves, they received no justice from the Harbinger. They were "
	"simply destroyed. When the dwarves mistook the Harbinger for Gluriurl resurrected, they "
	"received no \"justice\" either.")
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

Command(INTL( 11917, "JUSTICE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11920, "We have stayed silent since the beginning of time, removed from the influence of the "
	"gods. But there was a day when even dragons could not remain idle... a day when the "
	"\"winds\" threatened the very existence of Althea.")
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

Command(INTL( 11921, "WIND"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11922, "The screams of the dying were so many that they woke us from our slumber. This is "
	"when we decided to intervene, to take action against the evil that was unraveling "
	"the threads of our existence. That day was called the \"Battle\" \"of\" \"Emanations\".")
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

Command2(INTL( 10739, "BATTLE"), INTL( 11923, "EMANATION"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11924, "Ironically, the ranks of the enemy were mostly made up of the ancient races that the "
	"corrupted one called Makrsh P'Tangh had ammased in his own army. He wanted to bring "
	"back the same god who had caused the downfall of his own kind. When we destroyed his "
	"Harvesters of Life, he withdrew from the battlefield and escaped with \"Olin\" \"Haad\".")
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

Command2(INTL( 11925, "OLIN"), INTL( 11926, "HAAD"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11927, "Olin Haad was one of us when we attacked the Harvesters of Life. He was doing so well "
	"that I decided to give him the responsibility of keeping the Skull of Gluriurl. For "
	"some reason I cannot explain, he was \"fascinated\" with the Skull.")
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

Command(INTL( 11928, "FASCINAT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11929, "He began to develop powers that are very akin to that of gods. He started to become "
	"arrogant, and even hostile when things did not go the way he wished them to. "
	"Eventually, we decided not to include him in our council meetings... shortly after "
	"that, he \"changed\" \"sides\".")
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

CmdAND(INTL( 11930, "CHANGE"), INTL( 11931, "SIDE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11932, "Olin Haad is responsible for the death of hundreds of our allies and brethren. We of "
	"the \"Council\" \"of\" \"the\" \"Eight\" need your help to defeat him. Regardless of "
	"whether you pray to Ogrimar or Artherk, we need your \"help\".")
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

CmdAND(INTL( 11933, "COUNCIL"), INTL( 11934, "EIGHT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11935, "After the Battle of Emanations, the eight most powerful dragons that remained banded "
	"together to form the council. We exist now to watch and guard places like this one. "
	"Some of us have already guided you in your journey. Take the gypsy, for example. She "
	"is one of us as well.")
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

Command(INTL( 554, "HELP"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11936, "When we destroyed the Harvesters of Life, we vowed never to kill another of our kind. "
	"Olin Haad is a dragon after all, and as much as it pains my heart to say it, we must "
	"\"prevent\" him from summoning Gluriurl. That's why I implore you to help us.")
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

Command(INTL( 11937, "PREVENT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11938, "Without further delay, you must travel to the \"Great\" \"Library\" of Althea. You "
	"must search within its walls to find the true reason behind Olin Haad's raid on "
	"Lighthaven. Once you find it, you must confront him with it. Now, I have \"something\" "
	"to give you that will help you on the rest of your journey.")
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

CmdAND(INTL( 11939, "GREAT"), INTL( 1429, "LIBRARY"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11940, "The Great Library of Althea is somewhere on this island. You should ask around at "
	"the temple of Silversky if you do not know of its location. Before you go, I have \"something\" "
	"to give you.")
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

Command(INTL( 4082, "SOMETHING"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 33)
	Conversation
	INTL( 11941, "This is a vial of my blood... when you are ready, consume it and you will feel "
	"something change inside of you. Also, this Armlet of Flames will come in handy I am certain. "
 	"This is just my way of helping you face the trials ahead.")
	PRIVATE_SYSTEM_MESSAGE(INTL( 11942, "Crimsonscale gives you a Vial of Dragon Blood, an Armlet of Flames and a Gem of Flames."))
	GiveItem(__OBJ_VIAL_OF_CRIMSONSCALE_BLOOD)		
	GiveItem(__OBJ_ARMLET_OF_FLAMES)
	GiveItem(__OBJ_GEM_OF_FLAMES)
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 34)
	//"This Armlet of Flames will come in handy I am certain. This is just my way of helping "
	//"you face the trials ahead."
	//PRIVATE_SYSTEM_MESSAGE("Crimsonscale gives you an Armlet of Flames and a Gem of Flames.")
	//GiveItem(__OBJ_ARMLET_OF_FLAMES)
	//GiveItem(__OBJ_GEM_OF_FLAMES)
	//GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 34)	
ELSE
	Conversation
	INTL( 11913, "This is not the time to talk about that.")
ENDIF

Command(INTL( 483, "NAME"))
INTL( 11943, "You may call me Crimsonscale.")

Command(INTL( 489, "WORK"))
INTL( 11944, "I watch over the lesser races. No matter what happens, balance must always be preserved.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 1075, "Farewell.")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 11945, "So many friends lost...")
ELSE
	Conversation
	INTL( 624, "What are you talking about?")
ENDIF

EndTalk
}