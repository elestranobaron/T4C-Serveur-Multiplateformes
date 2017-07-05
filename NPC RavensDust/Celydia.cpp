//////////////////////////////////////////////////////////////////////
// Celydia.cpp: implementation of the Celydia class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Celydia.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Celydia::Celydia()
{}

Celydia::~Celydia()
{}

extern NPCstructure::NPC CelydiaNPC;

void Celydia::Create( ){
    npc = CelydiaNPC;
	SET_NPC_NAME( "[2936]Celydia" );
    npc.InitialPos.X = 1445;//1439;//1426;
    npc.InitialPos.Y = 2371;//2339;//2349;
	npc.InitialPos.world = 0;//0;
}

void Celydia::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF (TFCTime::IsSleepTime())
	Conversation
	INTL( 4522, "Please, it is getting late. You should go home now.")
	BREAK
ELSE
	Conversation 
	INTL( 4521, "Hello there! Please feel welcome in the castle of our great \"king\"!")	
ENDIF

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 4523, "I am Celydia, a faithful \"servant\" of our good king.")

Command(INTL( 4524, "CELYDIA"))
INTL( 4525, "Tell me if there is anything I can do for you.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 4526, "I am at his majesty's service. As one of his servants, I must do my best to provide him with "
"whatever he wishes for.")

Command(INTL( 1794, "ROYAL KEY"))
""
IF (CheckFlag(__QUEST_DEAD_BROTHERS) >= 12)
	Conversation
	INTL( 4527, "Oh, wait, now that I think about it, I remember seeing one such key on the king's "
	"desk a few years ago. It was very, very ornate, and caught my attention. I remember "
	"it well because a few days later, the king was furious at the loss of a precious family "
	"heirloom... I never saw the key after that. I think the king mentioned that a thief calling "
	"himself  \"Reynen\" \"Aspicdart\" had signed his burglary.")
ELSE
	Conversation
	INTL( 4528, "I'm not sure I should tell you anything about this...")
ENDIF

Command2(INTL( 3905, "REYNEN"),INTL( 3906, "ASPICDART"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY1) == 1)
	Conversation
	INTL( 4529, "I don't know where that rogue is hiding now. You'll have to ask around town, maybe "
	"someone's seen him lately.")
ELSEIF (CheckFlag(__QUEST_DEAD_BROTHERS) >= 12)
	Conversation
	INTL( 4530, "He was never found after presumably stealing the king's key. I don't know much more "
	"about him, I'm afraid, except that he's very, very handsome. If you find him, you "
	"can tell me if that rumor's true, right?")
	GiveFlag(__QUEST_ROYAL_KEY1,1)
ELSE
	Conversation
	INTL( 4531, "Isn't he some sort of well-known thief? I'd love to meet him, I hear all good "
	"thieves are tall, dark and handsome... *sigh*")
ENDIF

Command(INTL( 4532, "SERVANT"))
INTL( 4533, "I really must get on with my duties... unless there is something more you want to ask me.")

Command(INTL( 1072, "KING"))
INTL( 4534, "He is good, but also very demanding. It is a good thing I am not his only aid, because I don't "
"think I could ever keep up.")

Command(INTL( 3918, "VISITOR"))
INTL( 4535, "I'm afraid I can't very well keep an eye on everyone that enters the castle.")

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 4536, "Farewell, and don't get lost inside the castle.") BREAK

Default
INTL( 4537, "I have no knowledge of that.")

EndTalk

}
