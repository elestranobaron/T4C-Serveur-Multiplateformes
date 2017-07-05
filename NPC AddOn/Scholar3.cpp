#pragma hdrstop
#include "Scholar3.h"

Scholar3::Scholar3()
{}

Scholar3::~Scholar3()
{}

extern NPCstructure::NPC HighPriestGuntharNPC;

void Scholar3::Create( ){
	npc = HighPriestGuntharNPC;
	SET_NPC_NAME( "[12772]Scholar");
	npc.InitialPos.X = 1175;
	npc.InitialPos.Y = 1435;
	npc.InitialPos.world = 0;
}

void Scholar3::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 12570, "Fey is the language of faeries. Truly, for those who can hear it, there is no music that even compares to it.")

Command(INTL( 11966, "SOMALINA OUNDI INESORA"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) >= 35)
	Conversation
	INTL( 12571, "I beg your pardon? Ahh that's easy. That is fey for \"To\" \"recognize\" \"one's\" \"own\" \"ignorance\".")
ELSE
	Conversation
	INTL( 12572, "I beg your pardon? I think that's fey, but I don't yet know what it means...")
ENDIF

Command3(INTL( 11964, "DOS VANESLAE NAVIDAL"), INTL( 11965, "KADRIM LOK UNGRIM DOK"), INTL( 11967, "THARRGRA NETHDROVAR"))
INTL( 12562, "What? I have no idea what you just said.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 12573, "...sinamare lora... hmm...")
BREAK

Default
INTL( 12574, "...sinamare lora... I wonder what it means...")

EndTalk
}