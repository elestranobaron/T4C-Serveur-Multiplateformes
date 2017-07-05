#pragma hdrstop
#include "Balork.H"

_Balork::_Balork()
{}

_Balork::~_Balork()
{}

extern NPCstructure::NPC Balork;

void _Balork::Create( void )
{
        npc = ( Balork );
        SET_NPC_NAME( "[3030]Balork" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 1;
}


void _Balork::OnDeath( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
		TFormat FORMAT;

	//		IF (CheckFlag(__QUEST_CUTHANA) < 4)
				
	IF (CheckFlag(__QUEST_ISLAND_ACCESS) == 0)     // User must NOT have attained RD yet.
		IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) != -1) // User must NOT be an evil character.
			GiveFlag(__BALORK_BRAND, 1)
			GiveFlag(__BALORK_KILLED, 1)
			SHOUT(FORMAT(INTL( 1213, "ARGH! You win for now, but you shall bear my mark! "
			"By Nazagoth, I Brand you, %s!"), USER_NAME) )	
			IF (USER_KARMA >= (-50*(CheckFlag(__QUEST_ISLAND_ACCESS)+1)) && USER_KARMA <= (50*(CheckFlag(__QUEST_ISLAND_ACCESS)+1))) // Mostly neutral people
				GiveKarma(5*(500-USER_KARMA)/500) // Brings karma up
			ENDIF		  
		ELSE
			SHOUT(FORMAT(INTL( 10430, "ARGH! You will perish by my hand eventually, %s."), USER_NAME)) 	 
		ENDIF
	ELSE
		SHOUT(FORMAT(INTL( 10430, "ARGH! You will perish by my hand eventually, %s."), USER_NAME)) 	 
	ENDIF
	}
	NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

/*
__BALORK_BRAND FLAG
	0: User hasn't been branded by Balork
	1: User has been marked by Balork's dying curse
	2: User has had the Brand removed by Princess Delilah.
*/

void _Balork::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT WORK = 1;
CONSTANT SWORD = 2;

InitTalk

// If the user is a Good seraph or has a good alignment, Balork will start fighting as 
// soon as the user click on him. This prevents good characters from starting the evil 
// quest. 
//
// If the character is an Evil seraph, Balork will not curse the character. Additionally,
// Balork will not curse (or re-curse) a character that has already completed the 
// quest on Arakas. 
//
//	There is a check in the Begin that verifies if the character has the Brand. If 
// the character has the brand, Balork will start fighting as soon as the user click 
// on him. 
//

Begin
""
IF ((CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= 1) && (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1))
	Conversation
	INTL( 11342, "You again? I see that you've grown some wings. BAH! Even that won't save your puny life this time!")
	FIGHT
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1)
	Conversation
	INTL( 11344, "You again? This time, I swear you won't get away so easily!")
	FIGHT
ELSEIF (CheckFlag(__BALORK_BRAND) == 1) 
	Conversation	
	INTL( 11345, "Heh, you still bear my curse. Now, I'll finish you off!") 
	FIGHT
ELSE
	Conversation
	INTL( 1214, "Well well, what have we here? A miserable little dirty traveler!")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1215, "I am Balork, servant of the \"darkness\".") 

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 1216, "Whatever I spend my time doing, it is none of your concern.") 
  
Command(INTL( 10431, "DARKNESS")) 
""
IF (CheckFlag(__BALORK_KILLED) == 1) 
	Conversation
	INTL( 10432, "Heh, you're going to see a lot of it very soon.")
	FIGHT
ELSE
	Conversation
	INTL( 10433, "There is no point following the path of light. Only through darkness can one "
	"achieve respect and power. Hmmmm. You are a puny mortal, but I sense perhaps "
	"there is a spark of \"evil\" within you, desperately seeking to ignite.")
ENDIF 

Command4(INTL( 2379, "CHURCH"),INTL( 2122, "KILHIAM"),INTL( 2120, "MOONROCK"),INTL( 1243, "ARTHERK")) 
""
IF (CheckFlag(__BALORK_KILLED) == 1) 
	Conversation
	INTL( 10434, "You still owe me some blood, worm.")
	FIGHT
ELSEIF (CheckFlag(__KNOWS_EVIL_PASSWORD) == 1) 
	Conversation
	INTL( 10435, "BAH! There is nothing to be said about the church of Artherk and all these pious weaklings. "
	"You must visit Kalastor on the surface if you wish to walk the path of darkness. ")
ELSE
	Conversation
	FORMAT(INTL( 10436, "Uh? Tell me %s, have you been sent here on behalf of the Church of Artherk to try to put "
	"an end to my devilish existence?"), USER_NAME) 
	PRIVATE_SYSTEM_MESSAGE(INTL( 10437, "Balork's eyes gleam with pure malice.")) 
	SetYesNo (WORK)
ENDIF 

YES(WORK)
	Conversation
	INTL( 1217, "Splendid! Prepare to meet the edge of my blade!") 
	FIGHT 

NO(WORK)
	Conversation
	INTL( 1218, "Coward! Do you really think I will let you live?") 
	FIGHT 

YesNoELSE(WORK)
	Conversation
	INTL( 1219, "Have you been sent here by the goody-two shoes on the surface to put an "
	"end to my existence?") 
	SetYesNo(WORK) 

Command2(INTL( 1220, "EVIL"),INTL( 1221, "FOUL DEED"))
INTL( 1222, "Aaah, now these are words to my liking. Perhaps you would like to join the darkness? "
"I could use some help in undermining the authority of the priests who dwell above me. "
"Would you accept such a mission?")
SetYesNo(SWORD)

YES(SWORD)
	Conversation
	INTL( 1223, "All right, then, here is what you must do. Visit Kalastor, an ally of mine, and tell "
	"him our password, \"Nightingale\". He will know what to do from there.")
	GiveFlag(__KNOWS_EVIL_PASSWORD, 1)

NO(SWORD)
	Conversation
	INTL( 1224, "Then stop wasting my time!") BREAK

YesNoELSE(SWORD)
	Conversation
	INTL( 1225, "Mmm... If you can not handle such a simple question, perhaps you are not the one "
	"to help me. So, yes or no?")
   SetYesNo(SWORD)

Command(INTL( 1539, "NIGHTINGALE")) 
""
IF (CheckFlag(__KNOWS_EVIL_PASSWORD) == 1) 
	Conversation
	INTL( 11643, "Shh! This you must whisper only to my ally, Kalastor.")
ELSE
	Conversation
	INTL( 11644, "Bah, you are starting to bore me, human.")
ENDIF 


Command(INTL( 791, "GLOOMBLADE"))
""
IF (USER_LEVEL >= 15)
	Conversation
	INTL( 3624, "You will have to find somebody else to forge you a Gloomblade for I will not.")
ELSE
	Conversation
	INTL( 1227, "BAH! I do not care for your questions, weakling!")		
ENDIF

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
""
IF (CheckFlag(__KNOWS_EVIL_PASSWORD) >= 1) 
	Conversation
	INTL( 10438, "Farewell, worm. If you haven't done so already, meet Kalastor on the surface.")
	BREAK 
ELSEIF (CheckFlag(__BALORK_KILLED) == 1) 
	Conversation
	INTL( 10439, "Where do you think you're going? You still owe me another duel, worm.")
	CastSpellSelf(__SPELL_NPC_CANTRIP_PENTACLE) 
	FIGHT
ELSE
	Conversation
	INTL( 10440, "Flee while you still can, mortal.")
	PRIVATE_SYSTEM_MESSAGE(INTL( 10441, "Balork grins malevolently.")) 
	BREAK 
ENDIF 

 
Default
INTL( 1229, "Stop wasting my time and leave before I paint the floor with your blood!")

EndTalk
}
