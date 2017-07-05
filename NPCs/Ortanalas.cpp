//////////////////////////////////////////////////////////////////////
// Ortanalas.cpp: implementation of the Ortanalas class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Ortanalas.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Ortanalas::Ortanalas()
{}

Ortanalas::~Ortanalas()
{}
 
extern NPCstructure::NPC OrtanalasNPC;

void Ortanalas::Create( void ){
	npc = OrtanalasNPC;
	SET_NPC_NAME( "[3053]Ortanalas" );
	npc.InitialPos.X = 2924;
	npc.InitialPos.Y = 1093;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

void Ortanalas::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	switch(rnd(0, 1)){
	case 0: SHOUT(INTL( 1378, "AHHHHHHHHHHHHHH!")); break;
	case 1: SHOUT(INTL( 1379, "HELP!")); break;
	}

	self->Do(flee);
	self->SetTarget(target);
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}


void Ortanalas::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
INTL( 2221, "What can I do for you?")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1924, "I am Ortanalas, the great assistant of \"Jagar\" Kar.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 1925, "I am the assistant trainer of \"Jagar\" \"Kar\", the chief trainer of this town. "
"It is not an easy job, let me tell you. If you ever need to \"train\" your skills, I would be "
"glad to help you." )

Command2(INTL( 495, "LEARN"), INTL( 496, "TEACH"))
INTL( 7523, "Unfortunately, I am not yet experienced enough to teach. I can only train the skills that my "
"master \"Jagar\" \"Kar\" teaches.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 1929, "That's nonsense!")

Command(INTL( 523, "ANNABELLE"))
INTL( 1760, "I have heard of that woman, but I never saw her myself.")

Command(INTL( 1930, "JAGAR"))
INTL( 1931, "Bah! He can barely fit through a door frame because of the size of his head! "
"I tell you, if I could, I'd show him a thing or two. Luckily for him, the "
"lord pays me well to be his assistant. He thinks he's a master warrior, but "
"he's only a big lazy tub of turd. He makes me clean all his clothes, "
"shine his old rusty armor collection, and I do all the work when it comes to "
"training people. True, he had some days of glory when he was the king's "
"assistant and he can be one tough lad in combat. It's a shame he doesn't put his "
"talent to better use. Oh well, I guess it's all the better for me... That "
"way it will be much easier to take his place *grin*.")

Command2(INTL( 7524, "SKILLS"), INTL( 502, "TRAIN"))
INTL( 1481, "Very good, then let's begin your training.") 
CreateSkillList
	AddTrainSkill( __SKILL_ATTACK, 5000, 10 )
	AddTrainSkill( __SKILL_ARCHERY, 5000, 15 )
	AddTrainSkill( __SKILL_STUN_BLOW, 100, 20 )
	AddTrainSkill( __SKILL_POWERFULL_BLOW, 100, 50 )
SendTrainSkillList

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"))
INTL( 973, "Goodbye.") BREAK

Default
INTL( 1944, "Is this all?")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Ortanalas::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Ortanalas data function
// 
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE
	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_ATTACK, 5000, 10 )
		TRAIN_SKILL( __SKILL_ARCHERY, 5000, 15 )
		TRAIN_SKILL( __SKILL_STUN_BLOW, 100, 20 )
		TRAIN_SKILL( __SKILL_POWERFULL_BLOW, 100, 50 )
	CLOSE_NPC_DATA_TRAIN
CLOSE_NPC_DATA_EXCHANGE
}