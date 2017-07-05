#pragma hdrstop
#include "Amelia.h"

Amelia::Amelia()
{}

Amelia::~Amelia()
{}

extern NPCstructure::NPC GypsyNPC;

void Amelia::Create( ){
	npc = GypsyNPC;
	SET_NPC_NAME( "[12720]Amelia");
	npc.InitialPos.X = 2953;
	npc.InitialPos.Y = 1093;
	npc.InitialPos.world = 0;
}

void Amelia::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT FirstQuestion = 1;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 21)
	Conversation
	INTL( 11811, "Hello there, traveler.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 21)
	Conversation
	INTL( 11812, "Please don't \"kill\" me! I didn't see anything!")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 22)
	Conversation
	INTL( 11813, "Have you found the High Priest yet? You must hurry and help him! I think I saw his captors heading "
	"southwest of the west bridge out of town.")
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 42)
	Conversation
	INTL( 11814, "I heard about what you did for the High Priest... that was very brave of you.")
ELSE
	Conversation
	INTL( 11815, "Thank you for everything you did for us. I wish you good luck on your adventures, brave hero!")
ENDIF

Command(INTL( 11816, "KILL"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 21)
	Conversation
	INTL( 11817, "No I swear! I was just passing by and I didn't... Huh? You're not with \"them\"? Oh thank god!")
ELSE
	Conversation
	INTL( 11818, "I... I don't feel like talking about that right now.")
ENDIF

Command(INTL( 11819, "THEM"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 21)
	Conversation
	INTL( 11820, "There were at least six of them and they attacked the High Priest. Before he even had a chance to react, "
	"he was taken away by the \"brigands\". I think I saw \"where\" they went.")
ELSE
	Conversation
	INTL( 11818, "I... I don't feel like talking about that right now.")
ENDIF

Command(INTL( 565, "BRIGAND"))
""
IF((CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 21)||(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 22))
	Conversation
	INTL( 11821, "I think they work for the necromancer because the guards didn't do anything to stop them... Oh please! "
	"You must do something! The townspeople don't dare oppose them.")
ELSE
	Conversation
	INTL( 11818, "I... I don't feel like talking about that right now.")
ENDIF

Command(INTL( 8761, "WHERE"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 21)
	Conversation
	INTL( 11822, "They took the west bridge out of town... I think they went southwest after that, but I can't be sure.")
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 22)
ELSE
	Conversation
	INTL( 11818, "I... I don't feel like talking about that right now.")
ENDIF
	
Command(INTL( 483, "NAME"))
INTL( 11823, "My name is Amelia.")

Command(INTL( 489, "WORK"))
INTL( 11824, "Oh, I was just on my way to talk to the mayor.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 1075, "Farewell.")
BREAK

Default
""
IF (rnd.roll( dice(1,2) ) == 1)
	Conversation
	INTL( 5074, "I don't know...")
ELSE
	Conversation
	INTL( 11825, "I don't understand what you mean.")
ENDIF


EndTalk
}