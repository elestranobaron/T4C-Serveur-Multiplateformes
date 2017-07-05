//////////////////////////////////////////////////////////////////////
// RenegadeOrcLeader.cpp: implementation of Renegade Orc Leader
//
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "RenegadeOrcLeader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RenegadeOrcLeader::RenegadeOrcLeader()
{}

RenegadeOrcLeader::~RenegadeOrcLeader()
{}

extern NPCstructure::NPC _RenegadeOrcLeader;

//////////////////////////////////////////////////////////////////////////////////////////
void RenegadeOrcLeader::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of Renegade Orc Leader
//
	{
	npc = _RenegadeOrcLeader;
	SET_NPC_NAME( "[2906]Renegade Orc Leader" );
	npc.InitialPos.X = 0; 
	npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void RenegadeOrcLeader::OnDeath(UNIT_FUNC_PROTOTYPE)
{
	if(target != NULL)
	{
		// Renegade Orc Leader is a good guy.
		IF (USER_KARMA >= (-100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)))
			GiveKarma(-3*(500+USER_KARMA)/500)
		ENDIF
	}
	NPCstructure::OnDeath(UNIT_FUNC_PARAM);
}

//////////////////////////////////////////////////////////////////////////////////////////
void RenegadeOrcLeader::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of RenegadeOrcLeader
// 

{

CONSTANT DARKSWORD = 1;
CONSTANT GIVESCROLL = 2;

InitTalk

Begin
INTL( 1031, "Morgrath strong!")

Command(INTL( 1032, "Morgrath"))
INTL( 1033, "Me! Morgrath! Me!")

Command(INTL( 483, "NAME"))
INTL( 1034, "Me Morgrath, me very strong. *snort* Me see, me kill.")

Command(INTL( 489, "WORK"))
INTL( 1035, "\"Jarko\" pay me. Great gold he pay. *snort*")

Command2(INTL( 541, "JARKO"),INTL( 693, "NECROMANCER"))
INTL( 1036, "Powerful wizard he is. *snort* Me listen him or him be maaaaaaad... *grunt*")

Command(INTL( 1037, "MURMUNTAG"))
INTL( 1038, "He very strong, but me better. *grunt*")

Command(INTL( 535, "TROLL"))
INTL( 1039, "*snort*.. H... He scary. Me don't like him. *grunt*")

Command(INTL( 565, "BRIGAND"))
INTL( 1040, "They stupid, they attack me. *snort* But me attack them. *grunt* They run. *snort* Fast!")

Command(INTL( 539, "GOBLIN"))
INTL( 1041, "Goblins are weak, but orc are *snort*... stronger.. Much stronger!")

Command(INTL( 475, "STONE OF LIFE"))
""
IF (CheckGlobalFlag (__QUEST_STONE_OF_LIFE) > 1 ) 
	IF (CheckGlobalFlag (__WHO_HAS_THE_STONE_FLAG) == 1 ) // BRIGAND #1
		Conversation 
		INTL( 1042, "Morgrath not have pretty stone. Morgrath was attacked by mean "
		"brigands. Took pretty rock from Morgrath. Too many of them. "
		"Morgrath could not do anything. Asarr has rock. Master Jarko will be "
		"mad at Morgrath. Mad! Mad! *grunt* *snort*")
	ELSE 
		Conversation // TROLL #2
		INTL( 1043, "Morgrath don't have stone. Morgrath swear! *grunt* Big troll took rock "
		"from Morgrath! Troll strong! Too strong for Morgrath! *snort*")
	ENDIF
ELSE
	Conversation
	INTL( 1044, "*snort* Don't know what you talk about. *grunt*")
ENDIF

Command2(INTL( 513, "LIGHTHAVEN"),INTL( 514, "WINDHOWL"))
INTL( 1045, "*snort* Lighthaven is small human town like Windhowl. *grunt*")

Command2(INTL( 793, "RAVEN'S DUST"),INTL( 1046, "TELEPORT"))
INTL( 1047, "Morgrath sometimes have weird \"scribble-papers\" from Master Jarko. *snort* Not know how "
"to read, so Morgrath drop or give them.")

Command(INTL( 7129, "SCRIBBLE-PAPER"))
INTL( 7130, "Jarko call them scroll, you want scribble-paper from *snort* Morgrath?")
SetYesNo(GIVESCROLL)

YES(GIVESCROLL)
	IF (CheckFlag(__QUEST_KALASTOR_MISSION) == 1)
		IF(USER_LEVEL >= 25)
			Conversation
			INTL( 1050, "Uhh... *grunt* Morgrath give human magic scribble-paper if give Morgrath "
			"big glum sword. You agree with that?")
			SetYesNo(DARKSWORD)
		ELSE
			Conversation
			INTL( 11529, "Grrr! Morgrath think you liar! You look too weak to get real glum sword. Sword fake, Morgrath say!")
		ENDIF
	ELSE
		Conversation
		INTL( 1051, "Morgrath not have that. *grunt*")
	ENDIF
NO(GIVESCROLL)
	Conversation
	INTL( 11530, "Grrr! Morgrath think you liar! You look too weak to get real glum sword. Sword fake, Morgrath say!")
YesNoELSE(GIVESCROLL)
	Conversation
	INTL( 7132, "Big dumb weakling want scribble-paper or no?")
	SetYesNo(GIVESCROLL)

Command2(INTL( 1048, "DROP SCROLL"),INTL( 1049, "GIVE SCROLL"))
""
IF (CheckFlag(__QUEST_KALASTOR_MISSION) == 1)
	IF(USER_LEVEL >= 25)
		Conversation
		INTL( 1050, "Uhh... *grunt* Morgrath give you magic scribble-paper if give Morgrath "
		"big glum sword. You agree with that?")
		SetYesNo(DARKSWORD)
	ELSE
		Conversation
		INTL( 7131, "Grrr! Morgrath think you liar! You look too weak to get real glum sword. Sword fake, Morgrath say!")
	ENDIF
ELSE
	Conversation
	INTL( 1051, "Morgrath not have that. *grunt*")
ENDIF

YES(DARKSWORD)
Conversation
INTL( 1052, "Okay...")
IF (CheckItem(__OBJ_GLOOMBLADE) >= 1)
	Conversation
	INTL( 1053, "Morgrath takes sword, gives scribble-paper. Er... *grunt* Have runny nose, so "
	"scribble-paper a bit messy...")
	TakeItem(__OBJ_GLOOMBLADE)
	GiveItem(__OBJ_SCROLL_OF_SILVERSKY)
	IF (CheckFlag(__QUEST_ISLAND_ACCESS) == 0) 
		GiveFlag(__QUEST_ISLAND_ACCESS,1)
	ENDIF 
ELSE
	Conversation
	INTL( 1054, "ARRR! You lied! You not have glum sword!! *GRUNT* ME ANGRY!!! DIE!")
	FIGHT
ENDIF

NO(DARKSWORD)
Conversation
INTL( 1055, "*snort* Morgrath sad... Morgrath wants big sword. Big warriors have big swords...")

YesNoELSE(DARKSWORD)
Conversation
INTL( 1056, "Urgh... *snarl* You not make sense.")

Command3(INTL( 517, "FAREWELL"),INTL( 518, "BYE"),INTL( 519, "LEAVE"))
INTL( 1057, "Me see you again, me kill! *snort*")
BREAK

Default
INTL( 1058, "*snort* Me don't understand! *grunt*")

EndTalk
}





