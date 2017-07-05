//////////////////////////////////////////////////////////////////////
// Samuel.cpp: implementation of the Samuel class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Samuel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Samuel::Samuel()
{}

Samuel::~Samuel()
{}

extern NPCstructure::NPC Nobleman;

void Samuel::Create( ){
    npc = Nobleman;
    SET_NPC_NAME( "[2980]Samuel" );
    npc.InitialPos.X = 1379;//;//2819;//1402; 
    npc.InitialPos.Y = 2389;//493;//2323; 
    npc.InitialPos.world = 0;//4;//0;
}

void Samuel::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT APPLEWAX = 1;
CONSTANT CandleOfEternity = 2;

InitTalk

Begin
INTL( 5721, "Stand up straight in front of the king.")

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 5722, "I have no time to spare for this.")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5723, "You may call me \"Master\" \"Samuel\".")

Command(INTL( 5726, "MASTER"))
INTL( 5727, "Make sure you remember it!")

Command(INTL( 5724, "SAMUEL"))
INTL( 5725, "I should have you thrown out of the castle or even in the "
"\"prison\" for your impoliteness!")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 5728, "I am the \"King\"'s advisor. I help him in the decision-making process.")

Command(INTL( 1072, "KING"))
INTL( 5729, "What? How can you not know our great King \"Theodore\" the XIIIth? You must be a beggar then!")

Command(INTL( 754, "THEODORE"))
INTL( 5730, "You will address his Majesty by his rightful title.")

Command(INTL( 3918, "VISITOR"))
INTL( 5731, "We don't get any unusual visitors in the castle! Well, now that you mention it, you look "
"rather strange.")

Command(INTL( 537, "CASTLE"))
INTL( 5732, "This is the castle of King Theodore XII.")

Command(INTL( 4131, "PRISON"))
INTL( 5733, "The prison under the Castle is no longer in use. Dark creatures led by a malevolent being "
"that goes by the name of \"Death\" \"Jester\" have taken over. We thought it was easier to "
"simply condemn the prison rather than attempting to fight the de.. Hmmmm. I mean them...")

Command(INTL( 5734, "DEATH JESTER"))
""
IF (CheckFlag(__QUEST_FLAG_DEATH_JESTER_DONE) == 1)
	Conversation
   INTL( 5735, "You have already helped us. However, you should know that it is "
   "futile to fight the dead. The dark soul of the Death Jester simply "
   "have to enter another one of the many skeletal corpses in the dungeon "
   "to revive once more to trouble our nights.")
ELSEIF (CheckFlag(__QUEST_FLAG_KILLED_DEATH_JESTER) == 0)
   IF (CheckItem(__OBJ_DEATH_JESTER_SKULL) >= 1)
      Conversation
      INTL( 5736, "You do have its filthy skull but you did not vanquish the foe "
      "by yourself. Therefore, you are not worthy of being rewarded!") 
		;int nNumSkulls = CheckItem(__OBJ_DEATH_JESTER_SKULL);
      FOR(0, nNumSkulls )
         TakeItem(__OBJ_DEATH_JESTER_SKULL)
      ENDFOR
   ELSE
      Conversation
      INTL( 5737, "Sometimes, we can hear its horrible wail of despair throughout the "
      "entire Castle of Theodore XIII. If you could bring back its skull "
      "as the proof that you vanquished this terrible foe, I shall "
      "reward you greatly for the few moments of peace it will provide us.")
   ENDIF
ELSE
   IF (CheckItem(__OBJ_DEATH_JESTER_SKULL) == 0)
      Conversation
      INTL( 5738, "You do not even have the skull. Get back down there and finish "
	   "it off!")
   ELSE
		;int nNumSkulls = CheckItem(__OBJ_DEATH_JESTER_SKULL);
      FOR(0, nNumSkulls )            
         TakeItem(__OBJ_DEATH_JESTER_SKULL) 
      ENDFOR
      Conversation
      INTL( 5739, "You have defeated the Death Jester and brought back its ugly "
      "skeleton head? I must admit that I misjudged your skills at first, "
      "my friend. Good. Take this \"scarab\" \"protector\" and wear it "
      "around your waist. {You} {have} {been} {awarded} {30000} "
       "{experience} {points.}")
      GiveItem(__OBJ_SCARAB_PROTECTOR)     
      GiveXP(30000)
      RemFlag(__QUEST_FLAG_KILLED_DEATH_JESTER)
      GiveFlag(__QUEST_FLAG_DEATH_JESTER_DONE,1)
   ENDIF
ENDIF
 
CmdAND(INTL( 5038, "WAX"),INTL( 4648, "APPLE"))
""
IF (CheckFlag(__QUEST_WAX_APPLE) == 0)
   Conversation
   INTL( 5740, "You want an apple made of wax? What will you do with it? Nothing? "
   "Pardon me, but I do not have time to mold something that will end "
   "up in the trash can.") 
ELSEIF (CheckFlag(__QUEST_FLAG_DEATH_JESTER_DONE) == 1)
   Conversation
   INTL( 5741, "I need 10 units of wax and a small fee of 1000 gold pieces for "
   "the work involved if you want a small apple made of wax. Does "
   "that sound fair enough for you?")
   SetYesNo(APPLEWAX) 
ELSE
   Conversation
   INTL( 5742, "You want me to mold you an apple made of wax? Fine but you'll have "
   "to do something for me. I want you to get us rid of the horrible "
   "\"Death\" \"Jester\" who troubles our nights with his dark jests.")
ENDIF

YES(APPLEWAX)
""
IF (CheckItem(__OBJ_WASP_WAX) >= 10)
   IF (Gold >= 1000)
      Conversation
      INTL( 5743, "Let's proceed... ")
      FOR(0, 10)
         TakeItem(__OBJ_WASP_WAX)
      ENDFOR
      IF (rnd.roll(dice(1,10)) > 1) 
         Conversation
         INTL( 5744, "Done! I've finished the wax apple. Here you go. Beautiful, isn't? I "
         "hope you are satisfied.")
         GiveItem(__OBJ_WAX_APPLE)
         TakeGold(1000)
      ELSE
         Conversation
         INTL( 5745, "ARGH! #@!$!@#*#@$* I missed the mold again! I'm sorry, my friend, "
         "you'll have to get 10 more units of wax if you want me to try "
         "again to create a beautiful apple of wax.")
      ENDIF
   ELSE
      Conversation
      INTL( 5746, "I am sorry but you do not have the 1000 gold pieces. I cannot "
      "work for free because my time is simply too precious.")
   ENDIF
ELSE
   ;int nWaxUnits = 10 - CheckItem(__OBJ_WASP_WAX);
   Conversation
   FORMAT(INTL( 5747, "You need %u more wax units if you want me to mold you a "
          "nice apple made of wax. Seek the flying Death Stingers "
          "in the forest for they sometimes carry the precious wax "
          "I require."), nWaxUnits)
ENDIF

NO(APPLEWAX)
Conversation
INTL( 5748, "Your choice.")

YesNoELSE(APPLEWAX)
Conversation
INTL( 4598, "I'll assume you've said no.")

CmdAND(INTL( 9734, "CANDLE"),INTL( 9735, "ETERNITY")) 
INTL( 10148, "I could mold a candle of eternity but that would require five units of \"wax\" along with 5000 gold.")  
IF ((CheckItem(__OBJ_WASP_WAX) >= 5) && (Gold >= 5000)) 
	Conversation
	INTL( 10149, " Ah, I see that you already have the five units of \"wax\" and the required fee in your "
	"possession. Shall I get started and mold a brand new candle of eternity for you?") 
	SetYesNo(CandleOfEternity) 
ENDIF 

YES(CandleOfEternity) 
	IF (CheckItem(__OBJ_WASP_WAX) < 5)
		Conversation
		INTL( 10150, "How can I mold the candle if you don't have the 5 \"wax\" units I asked you to bring?")
	ELSEIF (Gold < 5000) 
		Conversation
		INTL( 10151, "Hey, I'm just trying to help you. If you don't want to pay a measly 5000 gold, then you "
		"should be on your way.")	
	ELSE
		PRIVATE_SYSTEM_MESSAGE(INTL( 10152, "You give the wax units along with 5000 gold to Samuel.")) 		
		Conversation
		INTL( 10154, "Great! Let me get to work, then...") 
		;int nWaxUnits = 5 - CheckItem(__OBJ_WASP_WAX);
		FOR(0, 5) 
			TakeItem(__OBJ_WASP_WAX)
		ENDFOR
		TakeGold(5000)  
		GiveItem(__OBJ_CANDLE_OF_ETERNITY) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 10155, "Samuel melts the wax into a candle mold.")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 10156, "Samuel gives you a candle of eternity."))	
		IF ((CheckItem(__OBJ_WASP_WAX) < 5) && (Gold < 5000)) 
			Conversation
			INTL( 10608, " All done! Hmmm. I see that you enough wax units to make another candle. Do you want "
			"me to mold another candle of eternity for only 5000 gold?")
			SetYesNo(CandleOfEternity) 
		ELSE		
			Conversation
			INTL( 10157, " All done! If you need another one, feel free to come back.") 
		ENDIF
	ENDIF 

NO(CandleOfEternity) 
	Conversation
	INTL( 8220, "Come back if you ever change your mind.") 

YesNoELSE(CandleOfEternity) 
	Conversation
	INTL( 10158, "Well, do you want a candle of eternity or not?")
	SetYesNo(CandleOfEternity)

Command(INTL( 5038, "WAX"))
INTL( 5749, "I am not sure who told you about my special hobby but I do enjoy creating various "
"objects in wax such as candles, fruits, etc.") 

CmdAND( INTL( 5750, "SCARAB"),INTL( 5751, "PROTECTOR"))
INTL( 5752, "I have a few of those. It gives an additional protection to its wearear against "
"all spells.") 

Command2(INTL( 4002, "ELYSANA"),INTL( 4003, "BLACKROSE"))
INTL( 4226, "I have nothing to say about that poison-brewing witch.")

Command(INTL( 4124, "POISON"))
INTL( 5753, "Why would you want to know how to create poison?") 

Command(INTL( 4884, "TANNED"))
INTL( 5754, "The king has request some animal skin from you and you need someone to "
"have it tanned? Let me see... hmmm.. I think that Drardos might be "
"the man for the task.")

Command(INTL( 4873, "DRARDOS"))
INTL( 5755, "He operates a small shop somewhere in the town.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 5756, "I could have called the guards to throw you in the \"prison\" for such filthy words.")
BREAK

Command4(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"))
INTL( 5757, "Bow before you leave.") BREAK

Default
INTL( 5758, "I have no interest in that matter.")

EndTalk

}
