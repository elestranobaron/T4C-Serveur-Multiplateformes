#pragma hdrstop
#include "Scholar1.h"

Scholar1::Scholar1()
{}

Scholar1::~Scholar1()
{}

extern NPCstructure::NPC HighPriestGuntharNPC;

void Scholar1::Create( ){
	npc = HighPriestGuntharNPC;
	SET_NPC_NAME( "[12772]Scholar");
	npc.InitialPos.X = 1143;
	npc.InitialPos.Y = 1447;
	npc.InitialPos.world = 0;
}

void Scholar1::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 12559, "Ahh, the intricate beauty of the language of the Elves... truly there is nothing like it.")

Command(INTL( 11964, "DOS VANESLAE NAVIDAL"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) >= 35)
	Conversation
	INTL( 12560, "Excuse me? Ahh that's easy. That is elven for \"To\" \"look\" \"upon\" \"one's\" \"self\".")
ELSE
	Conversation
	INTL( 12561, "Excuse me? I think that's elven, but I don't yet know what it means...")
ENDIF

Command3(INTL( 11965, "KADRIM LOK UNGRIM DOK"), INTL( 11966, "SOMALINA OUNDI INESORA"), INTL( 11967, "THARRGRA NETHDROVAR"))
INTL( 12562, "What? I have no idea what you just said.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 12563, "...estae luminae... hmm...")
BREAK

Default
INTL( 12564, "...estae luminae... I wonder what it means...")

EndTalk
}