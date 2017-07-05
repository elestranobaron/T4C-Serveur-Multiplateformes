#pragma hdrstop
#include "Librarian2.h"

Librarian2::Librarian2()
{}

Librarian2::~Librarian2()
{}

extern NPCstructure::NPC HighPriestGuntharNPC;

void Librarian2::Create( ){
	npc = HighPriestGuntharNPC;
	SET_NPC_NAME( "[12746]Librarian");
	npc.InitialPos.X = 1078;
	npc.InitialPos.Y = 1452;
	npc.InitialPos.world = 0;
}

void Librarian2::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void Librarian2::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void Librarian2::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT Findings = 1;

InitTalk

Begin
INTL( 12379, "I am currently researching into matters concerning the Harbinger. Would you like to hear what I "
"have found so far?")
SetYesNo(Findings)

YES(Findings)
	Conversation
	INTL( 12380, "The Harbinger was sent to Althea to restore the balance between good and evil. He first came to see "
	"the elves, which were as proud and arrogant as the gods. The Harbinger told them about their "
	"responsibility towards the gods as the chosen race. In their selfrighteousness, the elves laughed "
	"in his face and said they were creatures of the forest and thus, needed no gods to watch over them. "
	"The Harbinger warned them of the consequences of his \"second\" \"coming\", and disappeared.")
NO(Findings)
	Conversation
	INTL( 12381, "Alright, let me know later if you change your mind.")
	BREAK
YesNoELSE(Findings)
	Conversation
	INTL( 12382, "Would you like to hear about the Harbinger or not?")
	SetYesNo(Findings)

Command2(INTL( 12383, "SECOND"), INTL( 742, "COMING"))
INTL( 12384, "Despite the warnings, the elves continued to ignore the gods. When Death returned one thousand years "
"later, the elves refused to repent and were nearly all destroyed. The Harbinger then went to see the "
"dwarves and announced that they were now the chosen race. He also informed them of their new "
"responsibilities and duties towards the gods, and the \"consequences\" of his next visit, should they fail "
"in the task set before them.")

Command(INTL( 12385, "CONSEQUENCE"))
INTL( 12386, "One thousand years later, the Harbinger returned to see the dwarves in what was now his third coming to "
"the world of mortals. Very much impressed with the society the dwarves had evolved into, the Harbinger "
"came to see them in his true form. The dwarves, confused by such a horrible apparition, attacked him "
"thinking he was a demon from the deepest pits of hell. Death did not take this affront lightly and "
"transformed the entire dwarven race into mindless atrocities, condemned to eternally roam the land as "
"hideous creatures, shunned by all. He then left the dwawrves to their misery and sought out the \"humans\".")

Command(INTL( 6344, "HUMAN"))
INTL( 12387, "The Harbinger told our ancestors that they were the chosen race. He told them about the proud elves and "
"the bold dwarves and warned them about his next coming. Their task was to preserve the balance between "
"good and evil, and remain steadfast in faith.")

Command(INTL( 483, "NAME"))
INTL( 12388, "My name is Jeremiah.")

Command(INTL( 489, "WORK"))
INTL( 12389, "I am doing research on the Harbinger and the influence he has had on our society.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 973, "Goodbye.")
BREAK

Default
INTL( 8482, "I don't know anything about that.")

EndTalk
}