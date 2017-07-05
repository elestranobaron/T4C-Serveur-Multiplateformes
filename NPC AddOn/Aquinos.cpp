#pragma hdrstop
#include "Aquinos.h"

Aquinos::Aquinos()
{}

Aquinos::~Aquinos()
{}

extern NPCstructure::NPC HighPriestGuntharNPC;

void Aquinos::Create( ){
	npc = HighPriestGuntharNPC;
	SET_NPC_NAME( "[12723]Scholar Aquinos");
	npc.InitialPos.X = 1557;
	npc.InitialPos.Y = 2405;
	npc.InitialPos.world = 0;
}

void Aquinos::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT TarnianGiveTablet = 1;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 28)
	Conversation
	INTL( 11877, "Hail traveler. If you don't mind, I'm very busy with my research, so let's keep it short.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 28)
	Conversation
	INTL( 11878, "Hail traveler! I received word from Antonian so I was expecting your \"visit\".")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 29)
	Conversation
	INTL( 11879, "Have you found the cave yet? Remember, take the road northwest until you reach the second fork. From there, "
	"go west until the road ends and then keep going west to find the cave in the mountain range.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 42)
	Conversation
	INTL( 11880, "The road ahead is long for you, brave adventurer. I trust you will remain steadfast until the end.")
ELSE
	Conversation
	INTL( 11881, "Welcome, great hero! I can see the light of our dear Artherk shining down on you.")
ENDIF

Command(INTL( 11882, "VISIT"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 28)
	Conversation
	INTL( 11883, "The message said you were looking for the Nameless Bard... I'm still not sure how comfortable I feel about "
	"divulging his \"location\" to someone I barely know though...")
ELSE
	Conversation
	INTL( 11848, "I really should return to my chores now...")
ENDIF

Command(INTL( 9153, "LOCATION"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 28)
	Conversation
	INTL( 11884, "Well, if Antonian trusts you, then I suppose I should as well. He's always been a good judge of character "
	"you know. After all, he counts me among his friends! Heh heh. Alright, it's settled then. I will tell you "
	"\"where\" the Nameless Bard resides, so to speak.")
ELSE
	Conversation
	INTL( 11848, "I really should return to my chores now...")
ENDIF

Command(INTL( 8761, "WHERE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 28)
	Conversation
	INTL( 11885, "Because of his nature, the Nameless Bard lives deep inside a cave far to the west. Take the road out of town "
	"heading northwest, then at the second fork, the one where the road continues on north and branches off to the "
	"northwest, take the northwest route. Follow that road until it ends, then keep going west until you reach "
	"the mountain range. The entrance to the cave can be found in that viscinity.")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 29)
ELSE
	Conversation
	INTL( 11848, "I really should return to my chores now...")
ENDIF


Command(INTL( 483, "NAME"))
INTL( 11886, "I am Aquinos the scholar.")

Command(INTL( 489, "WORK"))
INTL( 11887, "I am researching intelligent creatures and documenting their behavior.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 973, "Goodbye.")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 11888, "That is not part of my research.")
ELSE
	Conversation
	INTL( 11889, "I don't know anything about that I'm afraid.")
ENDIF


EndTalk
}