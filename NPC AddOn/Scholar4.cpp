#pragma hdrstop
#include "Scholar4.h"

Scholar4::Scholar4()
{}

Scholar4::~Scholar4()
{}

extern NPCstructure::NPC HighPriestGuntharNPC;

void Scholar4::Create( ){
	npc = HighPriestGuntharNPC;
	SET_NPC_NAME( "[12772]Scholar");
	npc.InitialPos.X = 1190;
	npc.InitialPos.Y = 1460;
	npc.InitialPos.world = 0;
}

void Scholar4::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 12575, "The language of Dragons is regal and majestic. To understand it completely, one must study it for several lifetimes.")

Command(INTL( 11967, "THARRGRA NETHDROVAR"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) >= 35)
	Conversation
	INTL( 12576, "What did you just say? Ahh that's easy. That is dragon for \"One\" \"must\" \"open\" \"these\" \"eyes\".")
ELSE
	Conversation
	INTL( 12577, "What did you just say? I think that's dragon, but I don't yet know what it means...")
ENDIF

Command3(INTL( 11964, "DOS VANESLAE NAVIDAL"), INTL( 11965, "KADRIM LOK UNGRIM DOK"), INTL( 11966, "SOMALINA OUNDI INESORA"))
INTL( 12562, "What? I have no idea what you just said.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 12578, "...dostnarrr vrathkrraaa... hmm...")
BREAK

Default
INTL( 12579, "...dostnarrr vrathkrraaa... I wonder what it means...")

EndTalk
}