// Murmuntag.cpp: implementation of the Murmuntag class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Murmuntag.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Murmuntag::Murmuntag()
{}

Murmuntag::~Murmuntag()
{}

extern NPCstructure::NPC MurmuntagDestroyNPC;

void Murmuntag::Create(){
	npc = MurmuntagDestroyNPC;
	SET_NPC_NAME( "[3052]Murmuntag" );
	npc.InitialPos.X = 2848;
	npc.InitialPos.Y = 1126;
	npc.InitialPos.world = 0;
	npc.appearance = __NPC_ORC;
	npc.clan = __CLAN_LIGHTHAVEN;
}

void Murmuntag::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT TRAIN = 1
CONSTANT FEET = 2

InitTalk

Begin
""
IF( CheckGlobalFlag( __GLOBAL_QUEST_WHO_IS_INFECTED ) == 1 ) 
    GiveNPCFlag( __NPC_FLAG_MURMUNTAG_INFECTED, rnd.roll(dice(15, 4) ) MINUTES TDELAY )
	GiveGlobalFlag( __GLOBAL_QUEST_WHO_IS_INFECTED, 0 )
ENDIF
IF (CheckNPCFlag( __NPC_FLAG_MURMUNTAG_INFECTED) > CurrentRound)  
	IF(CheckItem(__OBJ_POUCH_OF_YELLOW_POWDER) > 0)
		TakeItem(__OBJ_POUCH_OF_YELLOW_POWDER)
		Conversation
		INTL( 1843, "You have yellow powder? Give Murmuntag... *grunt* Murmuntag feel better already..*snort* ")
    Conversation
   FORMAT(INTL( 1844, "{You} {have} {been} {awarded} {%u} {experience} {points.}"),(1000+(USER_LEVEL*100)))
   GiveXP(1000+(USER_LEVEL*100))
		GiveNPCFlag(__NPC_FLAG_MURMUNTAG_INFECTED, 0)
	ELSE
		Conversation // still infected.
   INTL( 1845, "...Feel no good. Goblin... yellow dots. Then, me"
   "hot... pouch of yellow powd... Cure Murmuntag. *grunt*.")
   BREAK
	ENDIF
ELSEIF ((CheckNPCFlag( __NPC_FLAG_MURMUNTAG_INFECTED ) < CurrentRound) && (CheckNPCFlag( __NPC_FLAG_MURMUNTAG_INFECTED ) != 0 ))
	Conversation
	INTL( 1846, "Murmuntag heal hot fever. *snort* Murmuntag feel much better. *grunt*")
	GiveNPCFlag( __NPC_FLAG_MURMUNTAG_INFECTED, 0)
ELSE	
	Conversation
	INTL( 1847, "*grunt* *snort*")
ENDIF

Command3(INTL( 483, "NAME"),INTL( 1037, "MURMUNTAG"),INTL( 485, "WHO ARE YOU"))
INTL( 1848, "Me Murmuntag! Me good orc! Me friend with human like \"Elmert\" *grunt* "
"Me strong! Me crush enemies! \"Urgh!\"")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1849, "\"Murmuntag\" guard town. \"Elmert\" say kill, Murmuntag kill! *snort*")

Command(INTL( 1850, "ELMERT"))
INTL( 1851, "Elmert guard master. *grunt* Elmert pay Murmuntag to protect town. "
"*snort*.")

Command(INTL( 1852, "URGH!"))
INTL( 1853, "This battle cry. Uuuuurrrrrggghhh... Scare \"monsters\" baaadly. Only great "
"\"warriors\" have battle cry.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 1854, "*snort* Me could kill Balork easily! Me do \"urgh\" and him flee.")

Command(INTL( 523, "ANNABELLE"))
INTL( 1855, "*snort* *grunt* Don't know.")

Command(INTL( 1856, "MONSTER"))
INTL( 1857, "Near city. They come many from cave. But me always scare them.")

Command(INTL( 1858, "WARRIOR"))
INTL( 1859, "You great warrior? Not great like Murmuntag! Can help you become great, Murmuntag \"train\" "
"you hard!")

Command(INTL( 502, "TRAIN"))
INTL( 1860, "Urgh!")
CreateSkillList
	AddTrainSkill( __SKILL_ATTACK, 5000, 10 )
SendTrainSkillList

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"))
INTL( 1862, "Me go destroy goblins now. *grunt*") BREAK

Default
INTL( 1863, "*snort*")

EndTalk

}
//////////////////////////////////////////////////////////////////////////////////////////
void Murmuntag::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Murmuntag data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_ATTACK, 5000, 10 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
