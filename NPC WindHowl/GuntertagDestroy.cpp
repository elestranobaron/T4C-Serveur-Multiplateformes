//////////////////////////////////////////////////////////////////////
// GuntertagDestroy.cpp: implementation of the GuntertagDestroy class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "GuntertagDestroy.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GuntertagDestroy::GuntertagDestroy()
{}

GuntertagDestroy::~GuntertagDestroy()
{}

extern NPCstructure::NPC GuntertagDestroyNPC;

//Nom: Guntertag Destroy.
//Statistique: Guntertag.
//Position: (2331, 665)
//World: 0
//Description: Orc Guard.
//Body: Guard.
//OnAttack

//////////////////////////////////////////////////////////////////////////////////////////
void GuntertagDestroy::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of GuntertagDestroy
//
{
    npc = GuntertagDestroyNPC;
	SET_NPC_NAME( "[3005]Guntertag Destroy" );
    npc.InitialPos.X = 1813;
    npc.InitialPos.Y = 1273;
	npc.InitialPos.world = 0;
    npc.appearance = __NPC_ORC;

}

//////////////////////////////////////////////////////////////////////////////////////////
void GuntertagDestroy::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of GuntertagDestroy
//
{
InitTalk

Begin
""
IF (CheckFlag(__QUEST_USER_IS_A_TRAITOR) >= 3) 
	Conversation
	INTL( 7160, "*snort* You not welcome here! ME CRUSH YOU! *grunt*")
	FIGHT 
ELSE
	Conversation 
   INTL( 2332, "GUUUNNTEEERRTAGGG DESTROY!!!! UUHHRRR UUHHRR!! WHAT DO YOU WANT?")
ENDIF

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2333, "*Grunt* Guntertag is lieutenant of guard! *Snort* Guntertag crush goblins "
"*snort*. Urggh!")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2334, "I am GUNTERTAG DESTROY! *grunt*, Brother of *snort* \"Murmuntag\" Destroy. "
"*grunt* Uuaaarrrgghhh!")

Command(INTL( 523, "ANNABELLE"))
INTL( 2335, "Guntertag does *grunt* not know!")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 2336, "*snort* Dunno! *grunt*")

Command(INTL( 1037, "MURMUNTAG"))
INTL( 2337, "Murmuntag is brother of *snort* Guntertag. He lives in *grunt* Lighthaven. "
"Together, Murmuntag and Guntertag could crush *snort* *grunt* anything.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2338, "*Snort*") BREAK

Default
INTL( 2339, "*Grunt*")

EndTalk 
}
