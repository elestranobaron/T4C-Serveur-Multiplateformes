//////////////////////////////////////////////////////////////////////
// Edden.cpp: implementation of the Edden class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Edden.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Edden::Edden()
{}

Edden::~Edden()
{}

extern NPCstructure::NPC Royal_Guard;

void Edden::Create( ){
	npc = Royal_Guard;
	SET_NPC_NAME( "[2946]Edden" );
	npc.InitialPos.X = 1461;//1434;//1445;
	npc.InitialPos.Y = 2364;//2400;//2418; 
	npc.InitialPos.world = 0;
}

void Edden::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk


Begin
""
IF ((CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED) > CurrentRound) && (CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED) != 0))
 	IF ((CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED_BY)) == (CheckFlag(__FLAG_SHADEEN_PLAYER_B)))
      Conversation
		INTL( 4941, "AH! HA! I have finally caught you, thief! You're going directly to JAIL! Seize him, boys!")		
		 ;int nNumLightHealingPotions = CheckItem(__OBJ_LIGHT_HEALING_POTION);
		FOR(0, nNumLightHealingPotions)         // User loses all his potions of healing.
			TakeItem(__OBJ_LIGHT_HEALING_POTION)   
		ENDFOR
		;int nNumHealingPotions = CheckItem(__OBJ_HEALING_POTION);
		FOR(0, nNumHealingPotions) // User loses all his potions of life. 
			TakeItem(__OBJ_HEALING_POTION)
		ENDFOR
      TELEPORT( 209,2338,1 )                                 
      BREAK                        
	ELSE
		IF ( USER_GENDER == GENDER_MALE ) 
			Conversation
			INTL( 4942, "I apologize, my Lord, but the banker just got robbed and I am currently trying to catch the thief!")
			BREAK
		ELSE
			Conversation
			INTL( 4943, "I apologize, my Lady, but the banker just got robbed and I am currently trying to catch the thief!")
			BREAK
		ENDIF
	ENDIF
ELSE
	IF (CheckFlag(__FLAG_THIEF) == 1)
		RemFlag(__FLAG_THIEF)
	ENDIF
	Conversation
	INTL( 4944, "Welcome to the king's castle. Please wipe your boots before entering.")
ENDIF

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 4945, "That's the name of this island.")

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 4946, "I am Sir Edden.")

Command(INTL( 4947, "EDDEN"))
INTL( 4948, "Yes, I am a knight of \"Silversky\".")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 4949, "I \"guard\" the entrance to the castle, along with my friend here, Idas.")

Command(INTL( 998, "SILVERSKY"))
INTL( 4950, "It is a great town, but I still wish it wasn't so close to the castle.")

Command(INTL( 2505, "GUARD"))
INTL( 4951, "We are to stand here and keep any unwanted intruders from entering the castle.")

Command(INTL( 4952, "IDAS"))
INTL( 4953, "He is a good friend, that is for sure. We always help each other out, he and I.")

Command2(INTL( 1072, "KING"),INTL( 754, "THEODORE"))
INTL( 4954, "Have you come to see the king? Proceed then.")

Command(INTL( 3918, "VISITOR"))
INTL( 4955, "I haven't noticed anything out of the ordinary.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1293, "Have a nice day.") BREAK

Default
INTL( 4956, "That does not concern me.")

EndTalk

}
