//////////////////////////////////////////////////////////////////////
// Jalus.cpp: implementation of the Jalus class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Jalus.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Jalus::Jalus()
{}

Jalus::~Jalus()
{}
 
extern NPCstructure::NPC JalusNPC;

//////////////////////////////////////////////////////////////////////////////////////////
void Jalus::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Jalus
//
{
	npc = JalusNPC;
	SET_NPC_NAME( "[3043]Jalus" );
  npc.InitialPos.X = 2838;
  npc.InitialPos.Y = 1177;
	npc.InitialPos.world = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
void Jalus::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of Jalus
//
{
InitTalk

Begin
INTL( 11756, "Why do they have to step on my crops? Somebody should take care of those guards so we can all "
"go on living peacefully.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1488, "I am Jalus. Pleased to meet you.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 1489, "Nice \"field\", isn't it? I take care of it and make sure everything will be "
"all right for the next day!")

Command(INTL( 1490, "FIELD"))
INTL( 1491, "Everybody has to \"eat\", right? Well, I've never met someone who didn't "
"have to. That would be pretty handy in the \"desert\".")

Command(INTL( 1492, "DESERT"))
INTL( 1493, "There are no deserts on Arakas, so you don't have to worry about that.")

Command(INTL( 1494, "DAY"))
INTL( 1495, "Is the day almost over already? My eyes aren't what they used to be. I usually know "
"that night has come when I start feeling \"hungry\".")

Command2(INTL( 1496, "EAT"),INTL( 1497, "HUNGRY"))
INTL( 1498, "I heard there is a giant cow somewhere in this realm. If you ever get lucky "
"enough to catch a glimpse of it, please let me know! How I would love to bite down "
"on a nice, juicy steak right now.")

Command(INTL( 1499, "BLIND"))
INTL( 1500, "Poor me, I never thought I would go blind some day. Now I know it won't be "
"long. Nevertheless, I know that even blind I could tend to my crops as an "
"\"expert\" would.")

Command(INTL( 1501, "EXPERT"))
INTL( 1502, "You can only reach the level of expertise that I have after many years of work.")

Command3(INTL( 510, "BRAND"),INTL( 509, "BALORK"),INTL( 582, "BALORK'S CURSE"))
INTL( 1503, "That's a fairy tale.")

Command(INTL( 523, "ANNABELLE"))
INTL( 1504, "I don't know that woman. Sorry I couldn't help you.")

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
""
IF (TFCTime::IsDay())
  Conversation
  INTL( 1505, "Good day my friend!") BREAK
ELSE 
  Conversation
  INTL( 1506, "Good night! I'm feeling somewhat sleepy!") BREAK
ENDIF

Default
INTL( 1507, "Hearing goes away with age, I hear.")

EndTalk

}
