#pragma hdrstop
#include "Filandrius.h"

Filandrius::Filandrius()
{}

Filandrius::~Filandrius()
{}

extern NPCstructure::NPC FilandriusNPC;

void Filandrius::Create( ){
	npc = FilandriusNPC;
	SET_NPC_NAME( "[12737]Filandrius");
	npc.InitialPos.X = 985;
	npc.InitialPos.Y = 1465;
	npc.InitialPos.world = 0;
}

void Filandrius::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void Filandrius::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void Filandrius::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT Ready = 1;
CONSTANT GoUp = 2;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 0)
	Conversation
	INTL( 12110, "Welcome to the arcane floor. My name is Filandrius and I'm the high sorcerer of this library. "
	"My specialty is \"foreign\" \"magic\".")
ELSEIF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 1)
	Conversation
	INTL( 12111, "Already done? Oh... you shouldn't give me false hopes like that you know. Remember, Anthor "
	"is wandering on the island of Stoneheim... on the eastern part I think. Now hurry up and get me "
	"that book!")
ELSEIF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 2)
	Conversation
	INTL( 12112, "Hah! That didn't take you so long. Thank you very much! This really makes my day you know. Here, "
	"as promised... and if you want to \"learn\" some spells, just let me know.")
	PRIVATE_SYSTEM_MESSAGE(INTL( 12113, "You give the Tome of Arcane Knowledge to Filandrius."))
	TakeItem(__OBJ_TOME_OF_ARCANE_KNOWLEDGE)
	GiveItem(__OBJ_BELT_OF_UNSTABLE_PROTECTION)
	GiveItem(__OBJ_GEM_OF_UNSTABLE_PROTECTION)
	PRIVATE_SYSTEM_MESSAGE(INTL( 12114, "Filandrius gives you a Belt of Unstable Protection and a Gem of Unstable Protection"))
	GiveFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS, 3)
ELSEIF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 3)
	IF(CheckItem(__OBJ_HEL_SOULSTONE) >= 1)
		Conversation
		INTL( 12115, "Welcome back, friend. Oh! I never noticed before, but you carry a Soulstone! My oh my, this is "
		"\"interesting\".")
	ELSE
		Conversation
		INTL( 12116, "Welcome back, friend. Are you here to learn some \"spells\" or just browsing?")
	ENDIF
ELSEIF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 4)
	IF(CheckItem(__OBJ_HEL_SOULSTONE) >= 1)
		IF(CheckItem(__OBJ_JORMUNGAND_SOULSTONE) >= 1)
			IF(CheckItem(__OBJ_FENRIR_SOULSTONE) >= 1)
				Conversation
				INTL( 12117, "You have all the soulstones! Wonderful! Now all you need to do is head to the centaur village "
				"on Stoneheim and look for the portal.")
			ELSE
				Conversation
				INTL( 12118, "Very good, you have two soulstones now! Only one more to go and you can enter the portal!")
			ENDIF
		ELSE
			IF(CheckItem(__OBJ_FENRIR_SOULSTONE) >= 1)
				Conversation
				INTL( 12118, "Very good, you have two soulstones now! Only one more to go and you can enter the portal!")
			ELSE
				Conversation
				INTL( 12119, "No luck finding the other guardians yet? Keep trying and I know you'll succeed.")
			ENDIF
		ENDIF
	ELSE
		IF(CheckItem(__OBJ_JORMUNGAND_SOULSTONE) >= 1)
			IF(CheckItem(__OBJ_FENRIR_SOULSTONE) >= 1)
				Conversation
				INTL( 12118, "Very good, you have two soulstones now! Only one more to go and you can enter the portal!")
			ELSE
				Conversation
				INTL( 12120, "You only have one soulstone eh? Then hurry up and get the other two!")
			ENDIF
		ELSE
			IF(CheckItem(__OBJ_FENRIR_SOULSTONE) >= 1)
				Conversation
				INTL( 12120, "You only have one soulstone eh? Then hurry up and get the other two!")
			ELSE
				Conversation
				INTL( 12121, "What happened with all your soulstones? You should try and find them again... "
				"this is very important!")
			ENDIF
		ENDIF
	ENDIF
ELSEIF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 5)
	Conversation
	INTL( 12122, "What? There was a creature waiting behind the portal? Wow! I didn't know about that. So it was "
	"a Harvester of Life, was it? Well thanks for the information. Now, if you don't need that little "
	"red gem, I'm ready to relieve you of its \"burden\", heh heh.")
ELSE
	Conversation
	INTL( 12123, "Welcome back my good friend. What brings you to the Great Library of Althea?")
ENDIF

CmdAND(INTL( 12124, "FOREIGN"), INTL( 1096, "MAGIC"))
""
IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 0)
	Conversation
	INTL( 12125, "Looks like I got your attention with that one eh? My job is simple enough, I collect and "
	"translate ancient magic, be it artifacts or spells. I just may be in \"need\" for someone "
	"as well-trained as yourself.")
ELSE
	Conversation
	INTL( 12126, "Now is not the time for this conversation.")
ENDIF

Command(INTL( 12127, "NEED"))
""
IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 0)
	IF(USER_LEVEL >= 50)
		Conversation
		INTL( 12128, "I've just finished translating an ancient text containing important information on a tome called "
		"\"Filnar'thir\", the Tome of Arcane Knowledge.")
	ELSE
		Conversation
		INTL( 12129, "I may require your services sometime in the future. There's a new project I'm working on and I'm "
		"still in the preliminary stages of research.")
	ENDIF
ELSE
	Conversation
	INTL( 12126, "Now is not the time for this conversation.")
ENDIF

Command(INTL( 12130, "FILNAR"))
""
IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 0)
	IF(USER_LEVEL >= 50)
		Conversation
		INTL( 12131, "That's what I want. Have you ever heard about Anthor the Mad? I suppose not... Anthor was the pride "
		"of the human civilization in the dwarven era. He devised many wonders and with the fall of the dwarfs, "
		"he helped make the human civilization what it is today. Unfortunately, like every flower, he bloomed "
		"under the light and faded in the \"darkness\".")
	ELSE
		Conversation
		INTL( 12126, "Now is not the time for this conversation.")
	ENDIF
ELSE
	Conversation
	INTL( 12126, "Now is not the time for this conversation.")
ENDIF

Command(INTL( 10431, "DARKNESS"))
""
IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 0)
	IF(USER_LEVEL >= 50)
		Conversation
		INTL( 12132, "He eventually met Makrsh P'Tangh... The lich did something that cost poor Anthor his sanity. Today "
		"he roams aimlessly on the island of Stoneheim, searching for something. I read somewhere that he "
		"would find peace only in death. That makes today his lucky day as I've developed a particular "
		"interest in the book he carries. If you've a bit of spare time, I would greatly appreciate it if you "
		"could \"get\" \"it\" for me.")
	ELSE
		Conversation
		INTL( 12126, "Now is not the time for this conversation.")
	ENDIF
ELSE
	Conversation
	INTL( 12126, "Now is not the time for this conversation.")
ENDIF

CmdAND(INTL( 12133, "GET"), INTL( 12134, "IT"))
""
IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 0)
	IF(USER_LEVEL >= 50)
		Conversation
		INTL( 12135, "If you were to bring me the tome, I would reward you for your efforts. I can even teach you some of "
		"the ancient spells that are found in the book. Before you go, you should know that Anthor will not "
		"be a pushover. Bring friends... bring lots of friends.")
		GiveFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS, 1)
	ELSE
		Conversation
		INTL( 12126, "Now is not the time for this conversation.")
	ENDIF
ELSE
	Conversation
	INTL( 12126, "Now is not the time for this conversation.")
ENDIF

Command(INTL( 12136, "BROWS"))
""
IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) >= 3)
	Conversation
	INTL( 12137, "Alright then, feel free to look around as you please.")
ELSE
	Conversation
	INTL( 12126, "Now is not the time for this conversation.")
ENDIF

Command(INTL( 938, "INTERESTING"))
""
IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 3)
	Conversation
	INTL( 12138, "Well, I read about these soulstones awhile back. It was written that they were used to open a gate to "
	"\"countless\" \"riches\".")
ELSE
	Conversation
	INTL( 12126, "Now is not the time for this conversation.")
ENDIF

CmdAND(INTL( 12139, "COUNTLESS"), INTL( 12140, "RICHES"))
""
IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 3)
	Conversation
	INTL( 12141, "I sure know how to get your attention, don't I? Anyway, three \"soulstones\" are needed to open the "
	"gate.")
ELSE
	Conversation
	INTL( 12126, "Now is not the time for this conversation.")
ENDIF

Command(INTL( 12142, "SOULSTONE"))
""
IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 3)
	Conversation
	INTL( 12143, "As you have probably guessed, the other two soulstones are guarded by creatures not unlike the one "
	"you defeated to get the soulstone that's in your possession. Unfortunately, I don't know where the "
	"other two guardians are located... but I can give you their \"names\".")
ELSE
	Conversation
	INTL( 12126, "Now is not the time for this conversation.")
ENDIF

Command(INTL( 12144, "NAMES"))
""
IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 3)
	Conversation
	INTL( 12145, "The three guardians are called Jormungand, Hel and Fenrir. Once you've found all three soulstones, "
	"look for the portal near the centaur village on Stoneheim. Be careful though, as I've read that once "
	"the soulstones are used to enter the portal, they are consumed by the portal's energies.")
	GiveFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS, 4)
ELSE
	Conversation
	INTL( 12126, "Now is not the time for this conversation.")
ENDIF

Command(INTL( 12146, "BURDEN"))
""
IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) == 5)
	Conversation
	INTL( 12147, "Oh no, it's no trouble at all. And here you go, for all the trouble you've been through. I'm sure "
	"you'll enjoy this as much as I did.")
	TakeItem(__OBJ_CRYSTAL_OF_PROVIDENCE)
	PRIVATE_SYSTEM_MESSAGE(INTL( 12148, "You give the Crystal of Providence to Filandrius."))
	GiveItem(__OBJ_BRACER_OF_THE_IMMORTAL)
	GiveItem(__OBJ_GEM_OF_THE_IMMORTALS)
	PRIVATE_SYSTEM_MESSAGE(INTL( 12149, "Filandrius gives you a Bracer of the Immortals and a Gem of the Immortals."))
	GiveFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS, 6)
ELSE
	Conversation
	INTL( 12126, "Now is not the time for this conversation.")
ENDIF

Command3(INTL( 700, "SPELL"),INTL( 495, "LEARN"),INTL( 496, "TEACH"))
""
IF(CheckFlag(__FLAG_ADDON_FILANDRIUS_QUEST_PROGRESS) >= 3)
	Conversation
	INTL( 12150, "These are some of the more useful spells contained within the book.")
	CreateSkillList
		AddTeachSkill (__SPELL_FIRESTORM, 30, 205808)
		AddTeachSkill (__SPELL_METEOR, 38, 350000)
		AddTeachSkill (__SPELL_AVALANCHE, 32, 238292)
		AddTeachSkill (__SPELL_TSUNAMI, 37, 323328)
		AddTeachSkill (__SPELL_INFERNO, 32, 243937)
		AddTeachSkill (__SPELL_TORNADO, 31, 221753)
		AddTeachSkill (__SPELL_HURRICANE, 34, 273152) 
		AddTeachSkill (__SPELL_ICE_SHIELD, 33, 249648)
		AddTeachSkill (__SPELL_LIGHTHAVEN_PORTAL, 10, 297712)
		AddTeachSkill (__SPELL_DRUIDS_POINT_PORTAL, 10, 297712)
		AddTeachSkill (__SPELL_SILVERSKY_PORTAL, 10, 297712)
		AddTeachSkill (__SPELL_STONECREST_PORTAL, 10, 297712)
		AddTeachSkill (__SPELL_SUNKEN_WOODS_PORTAL, 10, 297712)
		AddTeachSkill (__SPELL_WINDHOWL_PORTAL, 10, 297712)
		AddTeachSkill (__SPELL_WIZARDS_VALE_PORTAL, 10, 297712)
	SendTeachSkillList
ELSE
	Conversation
	INTL( 12126, "Now is not the time for this conversation.")
ENDIF

Command(INTL( 483, "NAME"))
INTL( 12151, "I am Filandrius, high sorcerer of this library.")

Command(INTL( 489, "WORK"))
INTL( 12152, "As I said before, I am the high sorcerer.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 973, "Goodbye.")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 12153, "I don't know what you mean by that.")
ELSE
	Conversation
	INTL( 12154, "I don't understand.")
ENDIF

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Filandrius::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL (__SPELL_FIRESTORM, 30, 205808)
			TEACH_SKILL (__SPELL_METEOR, 38, 350000)
			TEACH_SKILL (__SPELL_AVALANCHE, 32, 238292)
			TEACH_SKILL (__SPELL_TSUNAMI, 37, 323328)
			TEACH_SKILL (__SPELL_INFERNO, 32, 243937)
			TEACH_SKILL (__SPELL_TORNADO, 31, 221753)
			TEACH_SKILL (__SPELL_HURRICANE, 34, 273152) 
			TEACH_SKILL (__SPELL_ICE_SHIELD, 33, 249648)
			TEACH_SKILL (__SPELL_LIGHTHAVEN_PORTAL, 10, 297712)
			TEACH_SKILL (__SPELL_DRUIDS_POINT_PORTAL, 10, 297712)
			TEACH_SKILL (__SPELL_SILVERSKY_PORTAL, 10, 297712)
			TEACH_SKILL (__SPELL_STONECREST_PORTAL, 10, 297712)
			TEACH_SKILL (__SPELL_SUNKEN_WOODS_PORTAL, 10, 297712)
			TEACH_SKILL (__SPELL_WINDHOWL_PORTAL, 10, 297712)
			TEACH_SKILL (__SPELL_WIZARDS_VALE_PORTAL, 10, 297712)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE
}