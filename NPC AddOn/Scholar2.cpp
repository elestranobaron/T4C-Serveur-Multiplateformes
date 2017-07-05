#pragma hdrstop
#include "Scholar2.h"

Scholar2::Scholar2()
{}

Scholar2::~Scholar2()
{}

extern NPCstructure::NPC HighPriestGuntharNPC;

void Scholar2::Create( ){
	npc = HighPriestGuntharNPC;
	SET_NPC_NAME( "[12772]Scholar");
	npc.InitialPos.X = 1165;
	npc.InitialPos.Y = 1469;
	npc.InitialPos.world = 0;
}

void Scholar2::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 12565, "Vigor and heart are what make up the language of the Dwarves! There is no other language quite like it.")

Command(INTL( 11965, "KADRIM LOK UNGRIM DOK"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) >= 35)
	Conversation
	INTL( 12566, "Eh? Ahh that's easy. That is dwarven for \"One\" \"must\" \"only\" \"have\" \"eyes\".")
ELSE
	Conversation
	INTL( 12567, "Eh? I think that's dwarven, but I don't yet know what it means...")
ENDIF

Command3(INTL( 11964, "DOS VANESLAE NAVIDAL"), INTL( 11966, "SOMALINA OUNDI INESORA"), INTL( 11967, "THARRGRA NETHDROVAR"))
INTL( 12562, "What? I have no idea what you just said.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 12568, "...dorak tindarr... hmm...")
BREAK

Default
INTL( 12569, "...dorak tindarr... I wonder what it means...")

EndTalk
}