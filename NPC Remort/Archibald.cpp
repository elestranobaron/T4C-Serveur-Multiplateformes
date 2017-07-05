#pragma hdrstop
#include "Archibald.h"

Archibald::Archibald()
{}

Archibald::~Archibald()
{}

extern NPCstructure::NPC ArchibaldNPC;

void Archibald::Create( ){
    npc = ArchibaldNPC;
	SET_NPC_NAME( "[10939]Archibald" );
    npc.InitialPos.X = 829;
    npc.InitialPos.Y = 1447; 
	npc.InitialPos.world = 0;
}
 
void Archibald::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT GOFOREST = 1;

InitTalk
						  
Begin
""
IF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= 1)
	Conversation
	INTL( 10609, "Welcome, great Seraph.")
ELSE
	Conversation
	INTL( 10610, "Hm. I don't see any wings on your back. Come back later.")
	BREAK
ENDIF

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 10611, "I am called Archibald. I only speak to Seraphs. If you're interested in "
"visiting the \"Forest\" \"of\" \"No\" \"Return\", I'm your man.")

Command(INTL( 10612, "ARCHIBALD"))
INTL( 10613, "That's my name, yes.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 10614, "I'm just a traveller. Did you know I've been to the \"Forest\" \"of\" \"No\" \"Return\"?")

CmdAND3(INTL( 2563, "FOREST"),INTL( 1331, "NO"),INTL( 6167, "RETURN"))
INTL( 10615, "I know this spell that can take someone there. To get back, though, you're on your own. "
"Do you want to go?")
SetYesNo(GOFOREST)

YES(GOFOREST)
	Conversation
	INTL( 10616, "As you wish. Good luck!")	
	TELEPORT(2778,2006,0)
	BREAK

NO(GOFOREST)
	Conversation
	INTL( 10617, "Whatever you say, boss.")

YesNoELSE(GOFOREST)
	Conversation
	INTL( 10618, "Just say \"yes\" or \"no\".")
	SetYesNo(GOFOREST)

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 5408, "Maybe I'll see you later then.")
BREAK

Default
INTL( 1791, "I don't know.")

EndTalk

}
