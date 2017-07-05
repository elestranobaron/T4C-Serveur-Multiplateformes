// Edgar.cpp: implementation of the Edgar class.
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Edgar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Edgar::Edgar()
{}

Edgar::~Edgar()
{}

extern NPCstructure::NPC EdgarNPC;

void Edgar::Create(){
	npc = EdgarNPC;
	SET_NPC_NAME( "[3034]Edgar Gimplestratten" );
	npc.InitialPos.X = 0; //2855
	npc.InitialPos.Y = 0; //1165
	npc.InitialPos.world = 0;
}

void Edgar::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	if( target != NULL )
	{
	SWITCH(CheckFlag(__SHAKE_EDGAR))
		CASE(0)  // PC hasn't been told (yet) by Kalastor to kill Edgar:
			SHOUT(INTL( 1247, "Why did you do this to me? You bastard!"))
		ENDCASE
		CASE(1)  // PC hasn't been told (yet) by Kalastor to kill Edgar:
			SHOUT(INTL( 1247, "Why did you do this to me? You bastard!"))
		ENDCASE
		CASE(2)  // PC Has been told to kill Edgar and does so for the first time:
			GiveFlag(__SHAKE_EDGAR, 3)
			GiveGold(1000)
			SHOUT(INTL( 1248, "Blast you, brigand! Here's your money! Now leave me be!"))
		ENDCASE
		OTHERWISE  // PC Has been told to kill Edgar and does so for the nth time:
			SHOUT(INTL( 1249, "Not you again! DAMN YOU!"))
		ENDCASE
	ENDSWITCH
	// Edgar is a good guy.
	IF (USER_KARMA >= (-100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
		GiveKarma(-5*(500+USER_KARMA)/500)
	ENDIF
	}
    CLOSE_HANDLER
NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void Edgar::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT KALASTOR = 1;

InitTalk

Begin
""
IF ((CheckFlag(__SHAKE_EDGAR)>1) ) //OR (USER_KARMA<-50))
	Conversation
	INTL( 1250, "I will not speak with people of your ilk!") BREAK
ELSEIF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 42)
	Conversation
	INTL( 11744, "It looks like it's gonna be another one of those days... speak your business and be quick about it "
	"before the \"guards\" come back.")
ELSE
	Conversation
	INTL( 11745, "I heard about what you did for us... thanks.")
ENDIF

Command(INTL( 2505, "GUARD"))
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) < 42)
	Conversation
	INTL( 11746, "They're giving us a hard time that's for sure.")
ELSE
	Conversation
	INTL( 11747, "Yeah, thanks for taking care of that necromancer. Maybe his guards will leave us alone now.")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1252, "I'm Head Merchant Edgar Gimplestratten, if you like formal titles, or just Edgar, "
"if you're more the relaxed type.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1253, "I'm the master of the Lighthaven \"Merchant\" \"Guild\", the LMG as we call it for short. I "
"used to be an adventurer, but I decided to settle down a few years ago and fight the good "
"fight with money rather than with my sword.")

Command(INTL( 523, "ANNABELLE"))
INTL( 1254, "There have been plenty of people asking about her, lately. Who is she?")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 582, "BALORK'S CURSE"))
INTL( 1255, "I wouldn't know. Ask a priest or something.")

Command(INTL( 515, "ARAKAS"))
INTL( 1256, "This island's name is Arakas.")

Command2(INTL( 1257, "MERCHANT"),INTL( 586, "GUILD"))
INTL( 1258, "Yes, even a small place such as \"Lighthaven\" has its own merchants' guild. "
"It's necessary to keep trading smooth, especially with the \"goblins\" and \"brigands\" "
"disrupting everything these days.")

Command(INTL( 539, "GOBLIN"))
INTL( 1259, "Ah, they're everywhere, these days! Like the plague! You get outta town, you run "
"into armed goblins. ARMED! What's this world coming to! It's a disaster for "
"Lighthaven's economy, if you ask me.")

Command(INTL( 514, "WINDHOWL"))
INTL( 1260, "It's like I tell everyone, everybody there is just a little too bent on making money. "
"They forget to be nice to their neighbors, to help each other, to actually care, if you "
"get my drift.")

Command(INTL( 565, "BRIGAND"))
INTL( 1261, "<Sigh> As if fighting goblins wasn't enough, we've got to fight our own kind. "
"Not something I'm particularly proud of, as a human. We should be looking out "
"for each other, not killing each other. What good is money if it's blood money?")

Command(INTL( 1262, "TRADE"))
INTL( 1263, "Trade? WHAT trade? With all the trouble on the island, it's not like we are making "
"loads of money, eh? If you wanna help, go kill some of those \"goblins\" out there.")

Command(INTL( 956, "ADVENTURER"))
INTL( 1264, "There are many adventurers running in the streets, lately, and that'd be a good "
"thing if they were all fine folks. Some just prey upon the weak, though, and we'd "
"prefer not to have them here if we had a choice.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 1265, "A lovely town, don't you think? \"Windhowl\" is a bit larger, but I think it's not as "
"lively as Lighthaven. And the people here are nicer, too. Windhowl is just too "
"mercantile.")

Command3(INTL( 643, "KALASTOR"),INTL( 1266, "COLLECT"),INTL( 1267, "PROTECTION"))
""
IF (CheckFlag(__SHAKE_EDGAR)==1)
	GiveFlag(__SHAKE_EDGAR,2) 
	Conversation
	INTL( 1268, "Oh no you don't! I'm not about to give in to the likes of you! If you want the "
	"money, you'll have to knock me out!")
	FIGHT
ELSE
	Conversation
	INTL( 1269, "Sounds like you know Kalastor. He runs a protection racket in town. Are ye "
	"his friend?")
	SetYesNo(KALASTOR)
ENDIF

YES(KALASTOR)
	Conversation
	INTL( 1270, "Then you're no friend of mine!") BREAK
NO(KALASTOR)
	Conversation
	INTL( 1271, "All is well, then.")
YesNoELSE(KALASTOR)
	Conversation
	INTL( 1272, "Not much of an answer, is it?")

Command2(INTL( 565, "BRIGAND"),INTL( 1273, "RUFFIANS"))
INTL( 1274, "It isn't easy, trading in Lighthaven. We have some ruthless thieves' guild in town who "
"operates a \"protection\" racket on our merchants, and we have brigands who roam "
"the countryside, waylaying traders who travel between Lighthaven and Windhowl. Let me "
"tell you, it's been slim pickings, of late.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 1275, "What?!? Get lost!")
IF (USER_KARMA>(-25*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
	GiveKarma(-5*(500+USER_KARMA)/500)
ENDIF
BREAK

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1075, "Farewell.") BREAK

Default
INTL( 1276, "Uh huh.")

EndTalk

}

