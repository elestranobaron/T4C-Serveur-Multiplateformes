//////////////////////////////////////////////////////////////////////
// Jamar.cpp: implementation of the Jamar class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Jamar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Jamar::Jamar()
{}

Jamar::~Jamar()
{}

extern NPCstructure::NPC DesertNomad;

void Jamar::Create( ){
    npc = DesertNomad;
	SET_NPC_NAME( "[2957]Jamar" );
    npc.InitialPos.X = 1491; 
    npc.InitialPos.Y = 2501; 
	npc.InitialPos.world = 0;
}

MAKE_FUNC( GiveLetter )

IF (CheckItem(__OBJ_LETTER_TO_JAMAR) >= 1) // If PC has a letter from Kalir...
	IF (CheckFlag(__QUEST_ROYAL_KEY5) >= 9) //...and was asked by Kalir to deliver it:
		Conversation
		INTL( 5251, " Oh, a letter from Kalir?? Thank you! I was getting a little "
		"worried about him. This letter says where he is, so I can "
		"join him a little later. Thanks for bringing it here. Please take "
		"this letter to him so he knows where to meet me...")
		;int nNumLetters = CheckItem(__OBJ_LETTER_TO_JAMAR); 
		FOR(0, nNumLetters )
			TakeItem(__OBJ_LETTER_TO_JAMAR)
		ENDFOR
		IF ((CheckFlag(__QUEST_ROYAL_KEY5) == 9) && (CheckItem(__OBJ_LETTER_TO_KALIR) == 0))
			GiveItem(__OBJ_LETTER_TO_KALIR)
			GiveFlag(__QUEST_ROYAL_KEY5,10)
		ENDIF
	ELSE // If the letter was taken or stolen, but not given by Kalir:
		;int nNumLetters = CheckItem(__OBJ_LETTER_TO_JAMAR); 
		FOR(0, nNumLetters )				
			TakeItem(__OBJ_LETTER_TO_JAMAR)
		ENDFOR
		Conversation
		INTL( 5252, "Thanks! Unfortunately, the date is too old and I don't think Kalir will "
		"still be where this letter says he is. Still, thanks for taking the time "
		"to bring this. If you see Kalir again, please tell him I'm looking for him.")
	ENDIF
ELSE //  If the PC has no letter from Kalir, valid or not:
	Conversation
	INTL( 5253, "I'd love to get a letter from Kalir...")
ENDIF

END_FUNC

void Jamar::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
INTL( 2369, "Hello.")

Command(INTL( 3629, " NAME "))
INTL( 5254, "I am Jamar.")

Command(INTL( 5255, "JAMAR"))
INTL( 5256, "Yes, that is my name.")

Command(INTL( 489, "WORK"))
INTL( 5257, "I \"travel\" the \"desert\" with my \"friend\", Kalir.")

Command(INTL( 4142, "KALIR")) 
INTL( 5258, "He is still in the desert somewhere, lagging behind as usual.")
CALL_FUNC( GiveLetter )

Command(INTL( 5259, "TRAVEL"))
INTL( 5260, "Well, I feel more alive when I am walking under the desert sun.")

Command(INTL( 554, "HELP"))
INTL( 5261, "If you would like to give me something, just type \"give <item name>\" and that should do it. "
"For instance, if you would like to give me, say, a letter, you should say \"give letter\".")

Command(INTL( 5262, "GIVE LETTER"))
""
CALL_FUNC( GiveLetter )

Command(INTL( 1794, "ROYAL KEY"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY5) >= 10)
	Conversation
	INTL( 5263, "Hm? No, I don't have such a key. It's Kalir who's got it, sorry...")
ELSE
	Conversation
	INTL( 5264, "Hm... No, I don't think I want to talk about that.")
ENDIF

Command(INTL( 1492, "DESERT"))
INTL( 5265, "The desert west of here is not one to be taken lightly.")

Command(INTL( 5266, "FRIEND"))
INTL( 5267, "Kalir and I have been friends for many years now.")

Command(INTL( 3918, "VISITOR"))
INTL( 5268, "I have not seen anyone like that.")

Command3(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 973, "Goodbye.") BREAK

Default
INTL( 5269, "I am sorry, but I do not know what you are talking about.")

EndTalk

}
