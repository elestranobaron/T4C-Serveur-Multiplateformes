// MarnecSunim.cpp: implementation of the MarnecSunim class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "MarnecSunim.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MarnecSunim::MarnecSunim()
{}

MarnecSunim::~MarnecSunim()
{}

extern NPCstructure::NPC MarnecSunimNPC;

void MarnecSunim::Create(){ 
	npc = MarnecSunimNPC;
	SET_NPC_NAME( "[3049]Marnec Sunim" );
  npc.InitialPos.X = 2918;
  npc.InitialPos.Y = 1178;
	npc.InitialPos.world = 0;
	npc.clan = __CLAN_LIGHTHAVEN;	
}

void MarnecSunim::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	switch(rnd(0, 1)){
	case 0: SHOUT(INTL( 1378, "AHHHHHHHHHHHHHH!")); break;
	case 1: SHOUT(INTL( 1379, "HELP!")); break;
	}

	self->Do(flee);
	self->SetTarget(target);
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void MarnecSunim::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
INTL( 11770, "I'm tired of hiding from them... Please Artherk, free us from our misery...")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1743, "I am Marnec Sunim, the greatest \"farmer\" around!")

Command(INTL( 1744, "FARMER"))
INTL( 1745, "My ancestors have been farmers for generations now. I have \"secrets\" which "
"help me grow food that has made me famous. I am not very rich yet, but I'm "
"sure it's just a matter of time.")

Command(INTL( 1746, "SECRETS"))
INTL( 1747, "I'm sorry, but my farmer's secrets are only passed down from father to son.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1748, "I am the town's greatest farmer! And I tell you, it isn't going as well as "
"it used to. Those damned \"brigands\" are really starting to annoy me. "
"It's a shame our town's \"army\" is too small to give them a good beating. "
"One of these days I tell ya, I'm going to pay them a small visit. "
"It's just that I'm too busy to do it now with my farm and all, you know...")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 820, "Balork's curse? That's horrible!")

Command(INTL( 523, "ANNABELLE"))
INTL( 584, "I wonder who she is.")

Command(INTL( 565, "BRIGAND"))
INTL( 1749, "They are attacking everyone who tries to cross the forest. Trading with "
"\"Windhowl\" has been nearly impossible lately because of them. Perhaps "
"you could help the \"merchants\" doing some business with Windhowl if you "
"are a true adventurer.")
	 
Command(INTL( 1257, "MERCHANT"))
INTL( 2795, "These days, it is near impossible for the merchants of our fair city to do business with our "
"sister town, \"Windhowl\". If you would like to help one of our merchants, you must talk to "
"\"Lord\" \"Kirlor\" and \"register\" yourself. He will then give you a letter that you must "
"give to either \"Sigfried\" or \"Rolph\". They'll give you a report that must be delivered "
"to Lord Sunrock in Windhowl as fast as possible.")

Command(INTL( 1648, "REGISTER"))
INTL( 2796, "You must say this to \"Lord\" \"Kirlor\", not me!")

Command(INTL( 2518, "SIGFRIED"))
INTL( 2781, "Sigfried is the town's weaponsmith.")

Command(INTL( 2345, "ROLPH"))
INTL( 7163, "Rolph is the town's armorer.")

Command(INTL( 1436, "KIRLOR"))
INTL( 2783, "He is the town's Lord.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 1607, "Lighthaven is the name of our fair city.")

Command(INTL( 514, "WINDHOWL"))
INTL( 1750, "It is the largest town on this island, and is located west of the forest. ")

Command(INTL( 1751, "ARMY"))
INTL( 1752, "Our army is so small that it can't even take out the \"brigands\"' hideout. "
"Fortunatly, \"Murmuntag\" sometimes goes in the forest and cleans up the "
"road for a day or two.")

Command(INTL( 1037, "MURMUNTAG"))
INTL( 1753, "He's quite a big fellow, I tell you. Not very intelligent, but strong as an "
"ox, maybe even stronger.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1754, "I'll return to work now, goodbye.") BREAK

Default
INTL( 1755, "What?")

EndTalk

}
