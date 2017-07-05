//////////////////////////////////////////////////////////////////////
// Jeremiah.cpp: implementation of the Jeremiah class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Jeremiah.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Jeremiah::Jeremiah()
{}

Jeremiah::~Jeremiah()
{}

extern NPCstructure::NPC JeremiahNPC;
 
void Jeremiah::Create( ){
    npc = JeremiahNPC;
	SET_NPC_NAME( "[2958]Jeremiah" );
    npc.InitialPos.X = 1408;//2859;//1344;
    npc.InitialPos.Y = 2315;//218;//2377;
	npc.InitialPos.world = 0;//4;//0;
}

void Jeremiah::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 5270, "Hello there!")

Command(INTL( 3629, " NAME "))
INTL( 5271, "I am called Jeremiah.")

Command(INTL( 5272, "JEREMIAH"))
INTL( 5273, "Personally, I think it's a wonderful name.")

Command(INTL( 489, "WORK"))
INTL( 5274, "Hah! You want to know what I do for a living? Then I'll tell you! I travel the world over "
"in search of whatever is \"worth\" searching for! Sounds interesting? It is, let me tell you "
"my friend!")

Command(INTL( 1024, "WORTH"))
INTL( 5275, "Well, part of my work is to bring back the details of my findings and explorations to "
"\"Menark\". He can then scribe all my notes into books that are available to everyone.")

Command(INTL( 5276, "MENARK"))
INTL( 5277, "He is getting too old to travel, so all he does is write into those books there. "
"I suppose I should be grateful because it leaves all the travelling to me!")

Command(INTL( 3918, "VISITOR"))
INTL( 5278, "Hmm, now that you mention it, I have noticed a strange individual searching through the records "
"awhile ago. I didn't really pay him much heed, seeing as he was very polite upon entering and "
"leaving the grounds.")

Command2(INTL( 5279, "BOOKS"),INTL( 5280, "RECORD"))
INTL( 5281, "The books you see all around you were all written by Menark. I can't imagine reading all of "
"them, let alone writing them. Menark is very courageous, in his own way.")

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 5282, "Have a nice day, friend.") BREAK

Default
INTL( 5283, "I don't know what you are talking about.")

EndTalk

}
