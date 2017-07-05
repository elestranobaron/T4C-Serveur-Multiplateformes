#pragma hdrstop
#include "Torgas.H"

Torgas::Torgas()
{}

Torgas::~Torgas()
{}

extern NPCstructure::NPC TorgasNPC;

void Torgas::Create( void )
{
      npc = ( TorgasNPC ) ;
      SET_NPC_NAME( "[10931]Torgas" );
      npc.InitialPos.X = 370; 
      npc.InitialPos.Y = 805;
      npc.InitialPos.world = 0;
}

void Torgas::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
INTL( 5831, "How do you do my friend? Sit down and I'll be right with you.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8423, "You can call me Torgas.")

Command(INTL( 8424, "TORGAS"))
INTL( 3881, "Yeah, that's me.")
												 
Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 8425, "I am the bartender and owner of this tavern.")

Command2(INTL( 8323, "ANNITHAE"),INTL( 8326, "TEARDROP"))
INTL( 8426, "It is a pity that she does not come here more often. I'm sure she'd "
"attract more customers around here.")

Command(INTL( 5628, "ORACLE"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) >= 1)
	Conversation
	INTL( 8427, "Heh heh... You're not the first to ask and I'm sure you're not going to be "
	"the last. In these troubled times, many people seek him, I hear. Anyway, to make "
	"a short story long, I really wish I could help you locate him, but I've hardly "
	"any idea where you should start looking. Perhaps you could ask around? Perhaps "
	"the old gypsy could help you on your quest? Sorry, I should go, I hear a customer "
	"calling... Let's say \"goodbye\", okay?")
ELSE
	Conversation
	INTL( 8200, "Some other time, perhaps.")
	PRIVATE_SYSTEM_MESSAGE(INTL( 8428, "Torgas smiles politely, but you sense he doesn't like your kind much."))
ENDIF

Command2(INTL( 554, "HELP"),INTL( 4275, "HINT"))
INTL( 8429, "I wish I could help you, but I'm no seer. If that's what you're looking for, "
"why don't you check with the old fortune-teller? I think her name is Yolangda "
"or something... Rumor has it she's good... and very expensive.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8430, "I can smell cheap ale all over you. I think you've had enough to drink "
"for the day.")
BREAK

Command4(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"))
INTL( 8431, "Feel free to come back whenever you want.") 
BREAK

Default
""
IF (rnd.roll(dice(1, 3) ) == 1)
   Conversation
   INTL( 8432, "Never heard about that.")
ELSE
   Conversation
   INTL( 5250, "I don't think that concerns me.")
ENDIF

EndTalk
}

