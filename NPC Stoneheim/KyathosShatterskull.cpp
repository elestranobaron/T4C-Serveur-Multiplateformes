//////////////////////////////////////////////////////////////////////
// KyathosShatterskull.cpp: 
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "KyathosShatterskull.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

KyathosShatterskull::KyathosShatterskull()
{}

KyathosShatterskull::~KyathosShatterskull()
{}

extern NPCstructure::NPC KyathosShatterskullNPC;

void KyathosShatterskull::Create( ){
	npc = KyathosShatterskullNPC;
   SET_NPC_NAME(   "[10871]Kyathos Shatterskull" );
	npc.InitialPos.X = 875;
	npc.InitialPos.Y = 1010;
	npc.InitialPos.world = 0;
}

void KyathosShatterskull::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk		 

Begin
INTL( 8268, "Welcome to our town.")
			   
Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8269, "I go by the name of Kyathos Shatterskull.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8270, "I am a guard and my duty is to ensure that no skraugs will ever invade our land again.")

Command2(INTL( 554, "HELP"),INTL( 896, "QUEST"))
INTL( 8271, "I can't help you, stranger, but I'll tell you this: during your stay here in our town, "
"you either walk a straight line, or you deal with me.")

Command2(INTL( 8001, "ZION"),INTL( 8002, "THUNDERHEART"))
INTL( 8272, "You shouldn't associate with the likes of Thunderheart or Fatebringer. They're not people "
"who work for the greater good.")

Command2(INTL( 8017, "GLADDIUS"),INTL( 8018, "WINDCHASER"))
INTL( 8273, "He's another guard, like me. Don't get in our way, we're busy people.")

Command2(INTL( 8009, "THOR"),INTL( 8010, "GLAREFIRE"))
INTL( 8274, "See my weapons? See my armor? He made them. It cost me quite a bit, but I'm one of the best Centaur "
"warriors you can find, thanks to his superior equipment.")

Command2(INTL( 8013, "DIONYSUS"),INTL( 8014, "SILVERSTREAM"))
INTL( 8275, "We all like Dionysus. Whenever there's a dispute that's too petty for the King to handle, Dionysus steps "
"in and makes sure we're all treated fairly. We're indebted to him.")

Command2(INTL( 8046, "MALACHAI"),INTL( 8047, "FATEBRINGER"))
INTL( 8276, "Gladdius's not too worried about him, but I have reason to believe Malachai Fatebringer isn't always on "
"our side, if you know what I mean. I suspect he's dabbling in dark powers, but no one believes me.")

Command2(INTL( 1072, "KING"),INTL( 7998, "GRAVESOUL"))
INTL( 8277, "He was once married and had a heir, but they became sick and died many years ago. Our poor king never really "
"recovered and hasn't remarried. It was very tragic, really.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8278, "Say your prayers.")
FIGHT

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 1075, "Farewell.")
BREAK

Default
""
IF (rnd.roll(dice(1,5)) == 1)
   Conversation
	INTL( 8279, "I have no time for this. I have work to do.") BREAK 
ELSE
   Conversation
   INTL( 5758, "I have no interest in that matter.")
ENDIF


EndTalk
}
