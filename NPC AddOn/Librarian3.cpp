#pragma hdrstop
#include "Librarian3.h"

Librarian3::Librarian3()
{}

Librarian3::~Librarian3()
{}

extern NPCstructure::NPC HighPriestGuntharNPC;

void Librarian3::Create( ){
	npc = HighPriestGuntharNPC;
	SET_NPC_NAME( "[12746]Librarian");
	npc.InitialPos.X = 1066;
	npc.InitialPos.Y = 1464;
	npc.InitialPos.world = 0;
}

void Librarian3::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void Librarian3::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void Librarian3::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT Findings = 1;

InitTalk

Begin
INTL( 12390, "I see that you carry a Darkstone... as it happens, I was just studying some old records that spoke of "
"Darkstones. Would you like to hear what I've discovered?")
SetYesNo(Findings)

YES(Findings)
	Conversation
	INTL( 12391, "In one such record, I found the following passage, 'For each \"Darkseed\" that blooms, a thousand "
	"men will perish.'. It is said that a Darkstone is the heart of a god that was slain during the "
	"Celestial War. Three Darkstones are known to exist. The first is the heart of \"Artherk\", currently "
	"believed to be lost to any mortal. The second, which is rumored to have been found, is the heart of "
	"\"Gluriurl\". The last is the heart of \"Lothar\".")
NO(Findings)
	Conversation
	INTL( 12392, "I see... I'll be here if you change your mind.")
	BREAK
YesNoELSE(Findings)
	Conversation
	INTL( 12393, "Would you like to hear what I've discovered about the Darkstone or not?")
	SetYesNo(Findings)

Command(INTL( 12394, "DARKSEED"))
INTL( 12395, "A Darkseed is a darkstone in its early stage of development planted on this plane of existence by the "
"gods in order to give them a mortal body. The only Darkseed that is not known to have evolved into a "
"darkstone is that of Ogrimar. If the ancient texts are to be believed, then one could quite possibly find "
"Ogrimar somewhere on Althea.")

Command(INTL( 1243, "ARTHERK"))
INTL( 12396, "Even though Gluriurl didn't have time to absorb Artherk's essence, in the end the god of Light was still "
"slain. It is now known that his essence has survived and returned to his own plane and answers our everyday "
"prayers, but his heart remains in this land.")

Command(INTL( 12397, "GLURIURL"))
INTL( 12398, "As the darkest of all hearts, the heart of Gluriurl is the only one known to have retained some magical "
"energies. This phenomenon gives uncertain proof that Gluriurl is not truly dead, but rather in some kind "
"of slumber, awaiting to be brought back to life.")

Command(INTL( 12368, "LOTHAR"))
INTL( 12399, "Very little is known about the heart of Lothar. Legends say that it contains the bound essence of the dead "
"god of \"Corruption\" but no one knows for certain.")

Command(INTL( 12400, "CORRUPTION"))
INTL( 12401, "Yes, and it is also believed that should the heart be broken, Gluriurl would return to this land and exact revenge "
"on all life.")
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 35)
	PRIVATE_SYSTEM_MESSAGE(INTL( 12375, "You suddenly realize what Olin Haad is planning... to bring Gluriurl back to life!"))
	PRIVATE_SYSTEM_MESSAGE(INTL( 12376, "You receive 500000 experience points."))
	GiveXP(500000)
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 36)
ENDIF
 
Command(INTL( 483, "NAME"))
INTL( 12402, "My name is Geoffrey.")

Command(INTL( 489, "WORK"))
INTL( 12403, "My main field of research is artifacts and relics of the past.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 973, "Goodbye.")
BREAK

Default
INTL( 8482, "I don't know anything about that.")

EndTalk
}