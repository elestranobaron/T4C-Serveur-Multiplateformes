//////////////////////////////////////////////////////////////////////
// Haden.cpp: implementation of the Haden class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Haden.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Haden::Haden()
{}

Haden::~Haden()
{}

extern NPCstructure::NPC HadenNPC;

void Haden::Create( ){
	npc = HadenNPC;
	SET_NPC_NAME( "[2954]Haden" );
	npc.InitialPos.X = 0;
	npc.InitialPos.Y = 0; 
	npc.InitialPos.world = 0;
}

void Haden::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	if( target != NULL )
	{
		TFormat FORMAT;

		IF((CheckFlag(__QUEST_VISITOR_SPOTTED) == 7) && (CheckFlag(__FLAG_KILLED_HADEN) == 0))
			GiveFlag(__FLAG_KILLED_HADEN, 1)
			GiveFlag(__QUEST_VISITOR_SPOTTED, 8)
			SHOUT(FORMAT(INTL( 7077, "Damn you! You'll pay for this, %s!"), USER_NAME))
			IF(CheckItem(__OBJ_BLADE_OF_RUIN) == 0)
				GiveItem(__OBJ_BLADE_OF_RUIN)
			ENDIF
		ELSE
			SHOUT(INTL( 7078, "Damn you!"))
		ENDIF

	}
    CLOSE_HANDLER

	NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void Haden::OnTalk( UNIT_FUNC_PROTOTYPE )

{

// GiveKarma (50*(500-USER_KARMA)/500)
// GiveKarma (-50*(500-USER_KARMA)/500)
CONSTANT DUEL = 1;
CONSTANT SWORD = 2;	
CONSTANT STORY = 3;	
CONSTANT STORY2 = 4;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_KILLED_HADEN) == 1)
	Conversation
	INTL( 7079, "You again! This time I'll put an end to your miserable life once and for all!") FIGHT
ELSE
	Conversation
	INTL( 5805, "What do you want?")
ENDIF

Command(INTL( 3629, " NAME "))
INTL( 7080, "My name is no concern of yours.")

Command(INTL( 4020, "HADEN"))
""
IF(CheckFlag(__QUEST_VISITOR_SPOTTED) == 7)
	Conversation
	INTL( 7081, "So, you know about me, how unfortunate... for YOU!") FIGHT
ELSE
	Conversation
	INTL( 7082, "Never heard of him.")
ENDIF

Command(INTL( 489, "WORK"))
INTL( 7083, "What I do with my time is none of your business.")

Command(INTL( 5374, "SISTER"))
INTL( 7084, "I don't have a sister.")

Command(INTL( 4023, "AMANDRA"))
""
IF(CheckFlag(__QUEST_VISITOR_SPOTTED) == 7)
	Conversation
	INTL( 7085, "So, you know about my sister. What do you want from me?")
ELSE
	Conversation
	INTL( 7086, "I don't know anyone named Amandra. You know you're really starting to annoy me, now get outta "
	"here before I sharpen my blade with your bones!")
ENDIF

Command(INTL( 3918, "VISITOR"))
""
IF(CheckFlag(__QUEST_VISITOR_SPOTTED) == 7)
	Conversation
	INTL( 7081, "So, you know about me, how unfortunate... for YOU!") FIGHT
ELSE
	Conversation
	INTL( 7087, "I have better things to do than listening to you.")
ENDIF

Command2(INTL( 4045, "FIGHT"),INTL( 4046, "DUEL"))
INTL( 7088, "You want a fight? Then I'll give you one! En garde!") FIGHT

Command(INTL( 3741, "BLADE OF RUIN"))
""
IF(CheckFlag(__QUEST_VISITOR_SPOTTED) == 7)
	Conversation
	INTL( 7089, "Hah! You want the Blade of Ruin? Then come and get it!") FIGHT
ELSE
	Conversation
	INTL( 7087, "I have better things to do than listening to you.")
ENDIF

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 1864, "...") BREAK

Default
INTL( 7087, "I have better things to do than listening to you.")

EndTalk

}
