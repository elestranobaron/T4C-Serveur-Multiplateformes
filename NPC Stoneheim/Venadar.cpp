#pragma hdrstop
#include "Venadar.h"

Venadar::Venadar()
{}

Venadar::~Venadar()
{}

extern NPCstructure::NPC VenadarNPC;

void Venadar::Create( ){
	npc = VenadarNPC;
	SET_NPC_NAME( "[10935]A frightening beast");
	npc.InitialPos.X = 0;		// 2345
	npc.InitialPos.Y = 0;		// 545
	npc.InitialPos.world = 0;	// 2
}

void Venadar::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	TFormat FORMAT;
	if( target != NULL )
	{
		GiveFlag(__FLAG_USER_HAS_KILLED_VENADAR, 1);
	}

	NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void Venadar::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF(CheckFlag(__FLAG_USER_HAS_KILLED_VENADAR) == 1 && CheckFlag(__FLAG_QUEST_FOR_BONES) == 1)
	Conversation
	INTL( 10235, "Enough, please! If you want the ring so bad and you want to throw your life away then here it is. Now leave me be!")
	GiveItem(__OBJ_ANCIENT_RING)
	GiveFlag(__FLAG_QUEST_FOR_BONES, 2)
	PRIVATE_SYSTEM_MESSAGE(INTL( 10236, "Venadar gives you an ancient ring."))
ELSE
	Conversation
	INTL( 10237, "You should not be here, this place has a strong \"taint\" of evil in it.")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 10238, "My name? Urgh... I have been down here for so long... I do not remember what I was called in the world of men.")

Command(INTL( 8991, "VENADAR"))
INTL( 10239, "Hmm... that name sounds vaguely familiar.")
												 
Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 10240, "There is a strong \"presence\" of evil in this place. Do you not see what this evil has done to me? I am condemned to remain "
"in this place forever. The only remaining thing for me to do is to prevent others from suffering the same fate.")

Command2(INTL( 10241, "TAINT"), INTL( 10242, "PRESENCE"))
""
IF(CheckFlag(__FLAG_QUEST_FOR_BONES) >= 1)
	Conversation
	INTL( 10243, "This is where the \"Bones\" \"of\" \"Ogrimar\" were hidden long ago. Unfortunately, they have long since disappeared "
	"from here but the taint of the dark one remains.")
ELSE
	Conversation
	INTL( 10244, "A powerful relic of darkness was once hidden here. Although the object itself is no longer here, its taint still remains.")
ENDIF

CmdAND(INTL( 10231, "BONES"), INTL( 8606, "OGRIMAR"))
""
IF(CheckFlag(__FLAG_QUEST_FOR_BONES) >= 1)
	Conversation
	INTL( 10245, "There was an individual that came searching for the Bones some time in the past. He was very clever and was able to "
	"slip past me but he lost a valuable \"object\" behind when I attempted to stop him from escaping with the Bones.")
ELSE
	Conversation
	INTL( 10246, "This is not something that we should be talking about...")
ENDIF

Command(INTL( 10247, "OBJECT"))
""
IF(CheckFlag(__FLAG_QUEST_FOR_BONES) >= 1)
	Conversation
	INTL( 10248, "The individual left behind a mysterious \"ring\". I know not if this was by accident or if he intended to leave it behind.")
ELSE
	Conversation
	INTL( 10246, "This is not something that we should be talking about...")
ENDIF

Command(INTL( 8039, "RING"))
""
IF(CheckFlag(__FLAG_USER_HAS_KILLED_VENADAR) == 1 && CheckFlag(__FLAG_QUEST_FOR_BONES) >= 1)
	Conversation
	INTL( 10249, "I have already given you the ring! What else do you want from me?")
ELSEIF(CheckFlag(__FLAG_QUEST_FOR_BONES) == 1)
	Conversation
	INTL( 10250, "What? You want the ring? No! I cannot let you have it. I... this ring is... you cannot... NO!")
	FIGHT
ELSE
	Conversation
	INTL( 10246, "This is not something that we should be talking about...")
ENDIF

Command4(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"))
INTL( 10251, "Heed my advice and leave this place.")
BREAK

Default
INTL( 10252, "What? I fear I know nothing of what you speak of.")

EndTalk
}