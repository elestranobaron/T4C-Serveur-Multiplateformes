#pragma hdrstop
#include "Urik.h"

Urik::Urik()
{}

Urik::~Urik()
{}

extern NPCstructure::NPC UrikNPC;

void Urik::Create( ){
	npc = UrikNPC;
	SET_NPC_NAME( "[12778]Urik");
	npc.InitialPos.X = 2622;
	npc.InitialPos.Y = 1498;
	npc.InitialPos.world = 0;
}

void Urik::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_NUMBER_OF_URIK_THIEVES_PRESENT) > 0)
	IF(USER_GENDER == GENDER_MALE) 
		Conversation
		INTL( 12651, "Get him!")
	ELSE
		Conversation
		INTL( 12652, "Get her!") 
	ENDIF 
	BREAK
ELSE
	IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 7)
		Conversation
		INTL( 12653, "What do you want? Can't you see I'm busy here? If you have something to ask of me, make it quick.")
	ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 7)
		Conversation
		INTL( 12654, "What? You were hired by Ethan to collect my duties? Are you mad? I've already told him that I paid "
		"double the fees last month... now get out of here, \"simpleton\"!")
	ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 8)
		Conversation
		INTL( 12655, "Alright, alright! Take the money... Now get out of here!")
		PRIVATE_SYSTEM_MESSAGE(INTL( 12656, "Urik gives you 1000 gold."))
		GiveGold(1000)
		GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 9)
		BREAK
	ELSE
		Conversation
		INTL( 12657, "I paid my dues no matter what you say! I have nothing else to say to you.")
	ENDIF
ENDIF

Command(INTL( 12658, "SIMPLETON"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 7)
	Conversation
	INTL( 12659, "Yes, simpleton. Have you ever seen your face in a mirror? You adventurers disgust me as much as your "
	"average beggar! End of conversation. I will not \"discuss\" this with you any longer.")
ELSE
	Conversation
	INTL( 12660, "I have work to do, you know.")
ENDIF

Command(INTL( 12661, "DISCUSS"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 7)
	Conversation
	INTL( 12662, "You want to \"bargain\" with me? Are you deaf? Hey... what was that? Bah, probably just another beggar. "
	"Filthy things, all of them! Anyway, like I was about to say, bargaining with you would be like sharing a "
	"bone with a dog and I won't fall to that level!")
ELSE
	Conversation
	INTL( 12660, "I have work to do, you know.")
ENDIF

Command(INTL( 12185, "BARGAIN"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 7)	
	IF(USER_GENDER == GENDER_MALE) 		
		Conversation
		INTL( 12663, "Enough of this! Men, get him!")
	ELSE
		Conversation
		INTL( 12664, "Enough of this! Men, get her!") 
	ENDIF 
	IF(CheckGlobalFlag(__GLOBAL_FLAG_ADDON_NUMBER_OF_URIK_THIEVES_PRESENT) == 0)
		SUMMON("URIKTHIEF", target->GetWL().X, target->GetWL().Y-1)
		SUMMON("URIKTHIEF", target->GetWL().X-1, target->GetWL().Y+1)
		SUMMON("URIKTHIEF", target->GetWL().X+1, target->GetWL().Y+1)		
	ENDIF
	BREAK
ELSE
	Conversation
	INTL( 4019, "I don't have time for this.")
ENDIF

Command(INTL( 483, "NAME"))
INTL( 12665, "Just call me Urik.")

Command(INTL( 12666, "URIK"))
INTL( 12667, "That's all you need to know about me.")

Command(INTL( 489, "WORK"))
INTL( 12668, "What does it look like? I'm the master tailor, that's what.")

CmdAND(INTL( 5726, "MASTER"), INTL( 12669, "TAILOR"))
INTL( 12670, "I supply the local shops with cloth and leather.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 4356, "Good riddance.")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 12671, "What the hell are you saying?")
ELSE
	Conversation
	INTL( 4019, "I don't have time for this.")
ENDIF

EndTalk
}


