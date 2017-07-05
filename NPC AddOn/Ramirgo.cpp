#pragma hdrstop
#include "Ramirgo.h"

Ramirgo::Ramirgo()
{}

Ramirgo::~Ramirgo()
{}

extern NPCstructure::NPC OlinHaad1NPC;

void Ramirgo::Create( ){
	npc = OlinHaad1NPC;
	SET_NPC_NAME( "[12769]Ramirgo");
	npc.InitialPos.X = 402;
	npc.InitialPos.Y = 2613;
	npc.InitialPos.world = 0;
}

void Ramirgo::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void Ramirgo::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void Ramirgo::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 39)
	Conversation
	INTL( 12529, "I am the guardian of this shrine and you may not pass.")
	BREAK
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 39)
	Conversation
	INTL( 12530, "I am the \"guardian\" of this shrine. I guard with my essence the great sword of Lothar, the God of "
	"Justice.")
ELSE
	Conversation
	INTL( 12531, "You already have Caledbolg. You have no business being here, thus I may not let you pass.")
	BREAK
ENDIF

Command(INTL( 4313, "GUARDIAN"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 39)
	Conversation
	INTL( 12532, "That is what I am... nothing more, nothing less. I see that you have Artherk's Darkstone. As it is "
	"written, you may \"enter\" the shrine without any reprisal from me.")
ELSE
	Conversation
	INTL( 12533, "I am here to guard this sanctuary, not to talk.")
ENDIF

Command(INTL( 7296, "ENTER")) 
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 39)
	Conversation
	INTL( 712, "Very well.")
	TELEPORT(1746, 1524, 1)
	BREAK
ELSE
	Conversation
	INTL( 12533, "I am here to guard this sanctuary, not to talk.")
ENDIF

Command(INTL( 489, "WORK"))
INTL( 12534, "To guard this shrine until the end of time... such is my fate.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 12535, "Until the end of time...")
BREAK

Default
INTL( 12533, "I am here to guard this sanctuary, not to talk.")

EndTalk
}