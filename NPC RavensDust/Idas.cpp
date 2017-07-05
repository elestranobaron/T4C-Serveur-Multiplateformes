//////////////////////////////////////////////////////////////////////
// Idas.cpp: implementation of the Idas class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Idas.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Idas::Idas()
{}

Idas::~Idas()
{}

extern NPCstructure::NPC Normal_Guard;

void Idas::Create( ){
    npc = Normal_Guard;
	SET_NPC_NAME( "[2956]Idas" );
    npc.InitialPos.X = 1400;//1378;//1453; 
    npc.InitialPos.Y = 2424;//2387;//2409; 
	npc.InitialPos.world = 0;
}

void Idas::OnTalk( UNIT_FUNC_PROTOTYPE )

{

InitTalk

Begin
""
IF ((CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED) > CurrentRound) && (CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED) != 0))
 	IF ((CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED_BY)) == (CheckFlag(__FLAG_SHADEEN_PLAYER_B)))
      Conversation
		INTL( 5230, "AH! AH! I have finally caught you, thief! You're going directly to JAIL! Seize him now, fellows!")		
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
	INTL( 5231, "Welcome. Be sure to wipe your boots before proceeding inside.")
ENDIF

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 5232, "Sir Idas, at your service.")

Command(INTL( 4952, "IDAS"))
INTL( 5233, "I am one of the knights of \"Silversky\".")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 5234, "Like Edden, my duty is to \"guard\" the entrance to the castle.")

Command(INTL( 998, "SILVERSKY"))
INTL( 5235, "Contrary to Edden here, I think the city should be closer to the castle.")

Command(INTL( 2505, "GUARD"))
INTL( 5236, "I must say it gets quite tiresome sometimes. I think I am getting too old for this.")

Command(INTL( 4947, "EDDEN"))
INTL( 5237, "Although much younger than me, I still consider him a good friend.") 

Command2(INTL( 1072, "KING"),INTL( 754, "THEODORE"))
INTL( 5238, "Go on inside.")

Command2(INTL( 3905, "REYNEN"),INTL( 3906, "ASPICDART"))
INTL( 5239, "Yes, I know this thief very well. Caught him red-handed, once, but he managed to escape me, "
"that fox! He's caused a great deal of trouble in these parts, especially when he meddled "
"with the lonely wives of many honest men. *hmpf* We don't like his kind around here, so I hope "
"you're no friend of his.")

Command(INTL( 3918, "VISITOR"))
INTL( 5240, "I have not seen anyone suspicious. Even if I did, he would probably be in the dungeon right now.")

/* This has been too much troubles for little good. Therefore, I have commented it out. 

Command2(INTL( 1070, "WAGER"),INTL( 5207, "GAME"))
FORMAT(INTL( 5241, "So %s, you want to give a shot at the lottery game Edden and I play? It's "
"quite simple, really. You tell me the number you wish to \"pick\" and give me "
"1000 gold pieces. Then, I'll pick a number out of this bag. If you have "
"the same number, you'll win. Then, I'll put that number back in the bag "
"and I'll do this 4 more times! This means you can win up to five times! "
"Surely you don't want to lose the opportunity to be a rich man or woman."
"Heh! Heh! Oh, and by the way, the number you choose has to be between "
"1 and 12."), USER_NAME) 

ParamCmd(INTL( 5242, "PICK $"))
""
;int nWhatNumberYouPicked = NUM_PARAM( 0 );
// * * * Parameters weren't entered correctly * * * 
IF (nWhatNumberYouPicked == 0)
	Conversation
	INTL( 5243, "You have to tell me what is the number you wish to pick for the lottery. For example, if you want to "
   "pick number 11, just say {PICK} {11} and you are in business. The number you "
   "choose has to be between 1 and 12.")
// * * * Picked number isn't between 1 and 12 * * * 
ELSEIF ((nWhatNumberYouPicked > 12) || (nWhatNumberYouPicked < 1))
	Conversation
   INTL( 5244, "You must pick a number between 1 and 12.")
// * * * Not enough gold pieces * * * 
ELSEIF (Gold < 1000) 
	Conversation
   INTL( 5245, "You do not have the required 1000 gold pieces!")
ELSE
	TakeGold(1000)	
	int nMatches = 0;
   int nFirstNumber =  rnd.roll( dice(1, 12) );
   int nSecondNumber = rnd.roll( dice(1, 12) );
   int nThirdNumber =  rnd.roll( dice(1, 12) );
   int nFourthNumber = rnd.roll( dice(1, 12) );
   int nFifthNumber =  rnd.roll( dice(1, 12) );

	if (nFirstNumber == nWhatNumberYouPicked)
		++nMatches;
	if (nSecondNumber == nWhatNumberYouPicked)
		++nMatches;
	if (nThirdNumber == nWhatNumberYouPicked)
		++nMatches;
	if (nFourthNumber == nWhatNumberYouPicked)
		++nMatches;
	if (nFifthNumber == nWhatNumberYouPicked)
		++nMatches;
	Conversation
	FORMAT(INTL( 5246, "The five numbers I've picked are: {%u}, {%u}, {%u}, {%u}, {%u}."), nFirstNumber,nSecondNumber,nThirdNumber,nFourthNumber,nFifthNumber) 	
	IF(nMatches == 0)		
		Conversation
		INTL( 5247, " It appears that your number wasn't picked at all. Better luck next time!")
	ELSEIF(nMatches == 1)
		Conversation
      INTL( 5248, " Your number was picked once. I give you back the 1000 gold pieces you wagered.")       
		GiveGold(1000)
	ELSE
		Conversation
		FORMAT(INTL( 7692, " Your number was picked %u times. You win %u GPs!"), nMatches, (1000*nMatches*nMatches))
      GiveGold((1000*nMatches)*nMatches)
   ENDIF 
   BREAK
ENDIF
*/ 


Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2387, "Good day.") BREAK

Default
INTL( 5250, "I don't think that concerns me.")

EndTalk

}
