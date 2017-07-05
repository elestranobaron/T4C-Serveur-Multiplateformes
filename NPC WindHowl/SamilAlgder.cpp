//////////////////////////////////////////////////////////////////////
// SamilAlgder.cpp: implementation of the SamilAlgder class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "SamilAlgder.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SamilAlgder::SamilAlgder()
{}

SamilAlgder::~SamilAlgder()
{}

extern NPCstructure::NPC SamilAlgderNPC;
 
//Nom: Samil Algder.
//Statistique: Windhowl Priest.
//Position: (2222, 550)
//World: 0
//Description: Fine clothed priest.
//Body: Priest.

//////////////////////////////////////////////////////////////////////////////////////////
void SamilAlgder::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of SamilAlgder
//
{
	npc = SamilAlgderNPC;
	SET_NPC_NAME( "[3022]Samil Algder" );
	npc.InitialPos.X = 1704;
	npc.InitialPos.Y = 1158;
	npc.InitialPos.world = 0;  
}

//////////////////////////////////////////////////////////////////////////////////////////
void SamilAlgder::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of SamilAlgder
//
{

InitTalk

Begin
INTL( 2683, "Welcome in \"Artherk\"'s church.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2684, "I am called Samil Algder, and I am pleased to meet you.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2685, "My work, if it can be called that, is to follow the path set by \"Artherk\". "
"I also have the task to bless our \"troops\" before they go into "
" a confrontation, and to attend to their wounds when they come back.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2686, "Balork cursed you, you say? I'm sorry to hear that. If \"Annabelle\" the "
"Blessed One was still here, she might be able to help you. But she's long "
"gone, now. I hear a troll took her away to feast upon her.") 

Command(INTL( 523, "ANNABELLE"))
INTL( 2687, "I knew her well, that Annabelle. Lovelier than an Elf--not that I know "
"what Elves look like, they left this world a long, long time ago. But yes, "
"you'd love to meet her...")

Command(INTL( 2688, "TROOP"))
INTL( 2689, "Yes, we have a rather big army here in Windhowl, but we need all the troops "
"we can find, for the \"goblins\" are relentless in their assaults. "
"As a result, our troops need godly blessing before they go into combat, to help them "
"fight longer and harder.")

Command(INTL( 539, "GOBLIN"))
INTL( 2690, "The goblins are becoming increasingly deadly nowadays. I know not by what "
"sadistic means they have accomplished it, but some of them have been seen "
"wielding magical weapons!")

Command(INTL( 2691, "HEALING"))
INTL( 2692, "Ask another priest.")

Command(INTL( 2693, "MALAAR"))
INTL( 2694, "He's the Archbishop of this church.")

Command(INTL( 2695, "BLESSINGS"))
INTL( 2696, "I spend most of my time with the troops, but another priest will gladly "
"help you.")

Command(INTL( 1243, "ARTHERK"))
INTL( 2697, "Artherk is a kind and just god. I would follow him beyond the edge of the world "
"if I had to.")

Command(INTL( 746, "DRUID"))
INTL( 2698, "Druids can be very powerful, but they don't follow the true path of good. "
"I do not dislike their ways, but I'd rather become a great priest.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2699, "May Artherk protect you in your visions.") BREAK

Default
INTL( 2220, "Only Artherk could help you.")

EndTalk

}
