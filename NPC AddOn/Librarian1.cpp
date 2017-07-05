#pragma hdrstop
#include "Librarian1.h"

Librarian1::Librarian1()
{}

Librarian1::~Librarian1()
{}

extern NPCstructure::NPC HighPriestGuntharNPC;

void Librarian1::Create( ){
	npc = HighPriestGuntharNPC;
	SET_NPC_NAME( "[12746]Librarian");
	npc.InitialPos.X = 1081;
	npc.InitialPos.Y = 1470;
	npc.InitialPos.world = 0;
}

void Librarian1::OnAttacked( UNIT_FUNC_PROTOTYPE ){
}

void Librarian1::OnInitialise( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );

	WorldPos wlPos = { 0,0,0 };
	self->SetDestination( wlPos );
	self->Do( nothing );
	self->SetCanMove( FALSE );
}

void Librarian1::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT Findings = 1;

InitTalk

Begin
INTL( 12358, "I have been searching through old records about the Celestial War these past few days. Would "
"you like to hear my findings?")
SetYesNo(Findings)

YES(Findings)
	Conversation
	INTL( 12359, "In ancient times, long before the era of humans, a god named Gluriurl came into this world to make "
	"a pact with the king of elves, Oberon. Gluriurl had promised him limitless power in \"exchange\" "
	"\"for\" \"the\" \"essence\" of the god of Light, Artherk.")
NO(Findings)
	Conversation
	INTL( 12360, "Very well then, let me know if you change your mind.")
	BREAK
YesNoELSE(Findings)
	Conversation
	INTL( 12361, "Would you like to hear about the Celestial War or not?")
	SetYesNo(Findings)

Command2(INTL( 12362, "EXCHANGE"), INTL( 10112, "ESSENCE"))
INTL( 12363, "The elves were the race Artherk cherished the most. He loved them like a father loves his children. The "
"god of Corruption knew that to get to the god of Light, he would have to reach through the elves. He also "
"knew that Artherk had fallen for an elven maiden and used this knowledge to design a ritual in which "
"he could temporarily trap Artherk's essence inside a \"physical\" \"body\".")

Command2(INTL( 12364, "PHYSIC"), INTL( 12317, "BODY"))
INTL( 12365, "The god of Corruption knew that even in a physical form, Artherk would prove stronger than any other mortal "
"foe, but he would be no match against another god. He instilled the gift of sight on Oberon and forced "
"him to foresee the coming of the Harbinger. Oberon, fearful for the fate of his people, made a deal with "
"the god of Chaos, \"Ogrimar\", as instructed by Gluriurl.")

Command2(INTL( 12366, "CHAOS"), INTL( 8606, "OGRIMAR"))
INTL( 12367, "The gods of Chaos and Corruption conspired to rid the celestial realm of Artherk's presence. After "
"receiving the gifts promised him by Ogrimar, Oberon, possessed by Gluriurl, attacked the god "
"of Light in his physical form at the peak of the ritual. A great battle ensued during which Artherk was "
"nearly defeated. Just as Gluriurl was about to strike the finishing blow, \"Lothar\" \"the\" \"Just\" "
"appeared in the form of a great dragon of crimson scales and he slew Gluriurl, who had been weakened by "
"the fight.")

Command2(INTL( 12368, "LOTHAR"), INTL( 12369, "JUST"))
INTL( 12370, "The god of Justice sacrificed himself by imprisoning the essence of Gluriurl inside his own heart, "
"releasing Oberon form its hold in the process. When the Harbinger came to punish the elves, Ogrimar "
"\"abandonned\" them to their fate.")

Command(INTL( 3725, "ABANDON"))
INTL( 12371, "Oberon was marked as a traitor to his race and the one responsible for the downfall of his people. He "
"received the curse of unlife and became Makrsh P'Tangh, which means the Traitorous One in the ancient "
"elven tongue. The elves were taken by Death save for a few of the wisest, who were imprisoned by the "
"Harbinger into what is called the \"Elvenweave\", a beautiful and intricate tapestry created by Artherk "
"himself.")

Command(INTL( 12372, "ELVENWEAVE"))
INTL( 12373, "The tapestry depicts the majestic elven city that was buried by the human town of Lighthaven. Many believe "
"that the ruins of Anwynn, the elven city, still lay beneath the human town. Some legends even say that "
"deep inside one of its temples lies the \"heart\" of Lothar the Just.")

Command(INTL( 12339, "HEART"))
INTL( 12374, "That's right. It is also said that should the heart be found and desecrated, Gluriurl could be brought back to life again.")
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 35)
	PRIVATE_SYSTEM_MESSAGE(INTL( 12375, "You suddenly realize what Olin Haad is planning... to bring Gluriurl back to life!"))
	PRIVATE_SYSTEM_MESSAGE(INTL( 12376, "You receive 500000 experience points."))
	GiveXP(500000)
	GiveFlag(__FLAG_ADDON_STORYLINE_PROGRESS, 36)
ENDIF

Command(INTL( 483, "NAME"))
INTL( 12377, "My name is Thomas.")

Command(INTL( 489, "WORK"))
INTL( 12378, "I gather information on the Celestial War and any other subject that is closely related to it.")

Command5(INTL( 519, "LEAVE"), INTL( 518, "BYE"), INTL( 520, "QUIT"), INTL( 517, "FAREWELL"), INTL( 521, "EXIT"))
INTL( 973, "Goodbye.")
BREAK

Default
INTL( 8482, "I don't know anything about that.")

EndTalk
}