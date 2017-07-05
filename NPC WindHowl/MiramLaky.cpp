// MiramLaky.cpp: implementation of the MiramLaky class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "MiramLaky.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MiramLaky::MiramLaky()
{}

MiramLaky::~MiramLaky()
{}

extern NPCstructure::NPC MiramLakyNPC;

//////////////////////////////////////////////////////////////////////////////////////////
void MiramLaky::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of MiramLaky
//
{
	npc = MiramLakyNPC;
	SET_NPC_NAME( "[3018]Miram Laky" );
	npc.InitialPos.X = 1741;
	npc.InitialPos.Y = 1306;
	npc.InitialPos.world = 0;  
}

//////////////////////////////////////////////////////////////////////////////////////////
void MiramLaky::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of MiramLaky
//
{

InitTalk

Begin
INTL( 2640, "Yes? I'm quite busy now, so I'll ask you to be quick.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2641, "My name is Miram Laky, son of \"Rothar\" Laky.")

Command(INTL( 2642, "ROTHAR"))
INTL( 2643, "My father was a great man. I don't know what he did, but I'm sure he "
"did something great, like fighting off dragons or something. I heard "
"he was an adventurer, you know. Unfortunately, he's been gone for about "
"fifteen years now and I haven't seen him since.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2644, "Isn't it obvious by looking around? I take care of the fields. I harvest "
"many kinds of vegetables. We've only two farmers in this town to feed "
"the whole population. It isn't much I tell ya! Sometimes we even need to "
"get some food from \"Lighthaven\".")

Command(INTL( 523, "ANNABELLE"))
INTL( 2645, "Oh, I don't know if she's dead or alive for sure, but she left us to find "
"her true love years ago... Some say she lives with a troll, now. Me? I "
"just think it's hogwash and she died.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2646, "Curse that Balork and his Brand! There are many like you who walk the land "
"and bear his mark. I tell you, friend, you have to seek Annabelle, blessed be "
"her eyes! She'll know what to do.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 2647, "It's the village east of here, but then again, you look like you come from "
"there anyway. I wonder how you got passed the brigands... They have been "
"harrassing anyone that tries to cross over to this town, lately. "
"This \"island\" is doomed to chaos if nothing more is done about the evil "
"lurking around.")

Command(INTL( 755, "ISLAND"))
INTL( 2648, "Don't you know anything? You're on the island of Arakas!")

Command(INTL( 539, "GOBLIN"))
INTL( 2649, "I heard they're using magic swords now! I don't know about you, but I don't "
"trust anything about that magic stuff. It always gave me the creeps.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2650, "I hope next year will be better.") BREAK

Default
INTL( 2651, "My father would know.")

EndTalk

}
