//////////////////////////////////////////////////////////////////////
// Laren.cpp: implementation of the Laren class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Laren.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Laren::Laren()
{}

Laren::~Laren()
{}

extern NPCstructure::NPC Peasant;

void Laren::Create( ){
    npc = Peasant;
	SET_NPC_NAME( "[2964]Laren" );
    npc.InitialPos.X = 1497;
    npc.InitialPos.Y = 2534; 
	npc.InitialPos.world = 0;
}

void Laren::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 5399, "Hey!")

Command(INTL( 3629, " NAME "))
INTL( 5400, "My friends call me Laren. You look friendly enough so you can call me Laren too.")

Command(INTL( 5401, "LAREN"))
INTL( 5402, "That's what I said.")

Command(INTL( 489, "WORK"))
INTL( 5403, "I work in the \"fields\", but right now I'm taking it easy, if you know what I mean.")

Command (INTL( 1490, "FIELD"))
INTL( 5404, "It's damn tiring work I tell you, enough so that I'm really glad to come have a \"drink\" "
"here at the end of the day.")

Command2(INTL( 3905, "REYNEN"),INTL( 3906, "ASPICDART"))
INTL( 5405, "I don't know much about him, but I once overheard a conversation about him in a local inn. "
"Seems like there was a romance between him and Adriana, but it turned bad. She doesn't talk "
"about him, but maybe her assistant would know something. Why don't you try asking him?")

Command(INTL( 1346, "DRINK"))
INTL( 5406, "Heh, you here to have a drink too? That's good I suppose, I can use the company.")

Command(INTL( 3918, "VISITOR"))
INTL( 5407, "You're not asking the right person for that kind of information, friend. I just sit here and "
"drink.")

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 5408, "Maybe I'll see you later then.") BREAK

Default
INTL( 1791, "I don't know.")

EndTalk

}
