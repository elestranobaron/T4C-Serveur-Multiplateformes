//////////////////////////////////////////////////////////////////////
// Metanas.cpp: implementation of the Metanas class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Metanas.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Metanas::Metanas()
{}

Metanas::~Metanas()
{}

extern NPCstructure::NPC MetanasNPC;
 
void Metanas::Create( ){
    npc = MetanasNPC;
	SET_NPC_NAME( "[2967]Metanas" );
    npc.InitialPos.X = 1510; 
    npc.InitialPos.Y = 2530; 
	npc.InitialPos.world = 0;
}

void Metanas::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 5452, "Grumble... pick a seat and sit down! You're making me nervous.")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5453, "Metanas is the name, not that it concerns you.")

Command(INTL( 5454, "METANAS"))
INTL( 5455, "If you keep saying my name like that, you'll find that it's considerably harder to pronounce "
"without any teeth in your mouth!")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 5456, "Well, what does it look like I'm doing? I'm keeping an eye on the \"patrons\", that's what I'm "
"doing!")

Command(INTL( 5457, "PATRON"))
INTL( 5458, "See those two by the table over there? They know what it feels like to have my boot stamped all "
"across their faces. Just give me one good reason and I'll do the same to you!")

Command(INTL( 3918, "VISITOR"))
INTL( 5459, "Of course I've seen a strange visitor! This is a tavern you idiot!")

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 5460, "Get out if you're done, otherwise stop bothering me and sit down!") BREAK

Default
INTL( 5461, "Bah! Nonsense!")

EndTalk

}
