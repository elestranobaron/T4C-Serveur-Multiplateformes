#pragma hdrstop
#include "NorimarSteelwind.h"

NorimarSteelwind::NorimarSteelwind()
{}

NorimarSteelwind::~NorimarSteelwind()
{}

extern NPCstructure::NPC NorimarSteelwindNPC;

void NorimarSteelwind::Create( void )
{
    npc = NorimarSteelwindNPC;
    SET_NPC_NAME( "[10901]Norimar Steelwind" );
    npc.InitialPos.X = 275;
    npc.InitialPos.Y = 785;
    npc.InitialPos.world = 0;
}

void NorimarSteelwind::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
INTL( 9967, "Speak hastily for I have a lot of work to do.")

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 9968, "I have no time for meaningless chit-chat.")
BREAK

Command2(INTL( 9969, "NORIMAR"),INTL( 9970, "STEELWIND"))
INTL( 9971, "Yes, I am Norimar Steelwind.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 9972, "Norimar Steelwind is the name. If you have some hard-earned gold pieces "
"that you want to \"deposit\" in the secured vault, I am the one to whom "
"you must speak.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 9973, "I am the banker of this town. I must keep track of all the \"deposits\" and "
"\"withdrawals\". I also ensure that thieves such as \"Daran\" \"Lightfoot\" "
"do not get access to the vault.")

Command2(INTL( 8284, "DARAN"),INTL( 8285, "LIGHTFOOT"))
INTL( 9974, "If you store your hard-earned gold in here, you will have nothing to fear "
"of this thief.")

Command2(INTL( 9975, "RESHA"),INTL( 9976, "MARSACK"))
INTL( 9977, "She is an odd lady. I wouldn't trust her but I must say that she is rich "
"and gold pieces usually win my trust quite easily.")

Command(INTL( 2316, "BANK"))
INTL( 9978, "The services I offer you are quite simple. You can \"deposit\" or "
"\"withdraw\" gold pieces or view your account's \"balance\".")
 
Command(INTL( 1764, "BALANCE"))
""
IF (CheckFlag(__FLAG_BANK_OF_WINDHOWL) > 1) 
	Conversation
	FORMAT(INTL( 1765, "You have %u gold pieces in your bank account."), CheckFlag( __FLAG_BANK_OF_WINDHOWL) )
ELSEIF (CheckFlag(__FLAG_BANK_OF_WINDHOWL) == 1) 
	Conversation
	INTL( 9979, "Pah! You only have 1 gold piece in your account. You should consider closing it.")
ELSE
	Conversation
	INTL( 9980, "You do not have an account here. You must first \"deposit\" if you want one.")
ENDIF

ParamCmd(INTL( 1767, "DEPOSIT $ GOLD"))
"";
int nDeposit = NUM_PARAM( 0 );
   IF (nDeposit < 1 )
       Conversation
       INTL( 1775, "I am not a foolish banker.")
   ELSEIF (nDeposit != 0 )
      IF (Gold >= nDeposit )
         TakeGold( nDeposit ) 
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 9981, "You deposit %u gold in the bank."), nDeposit) )			
         int nCurrentGold = CheckFlag( __FLAG_BANK_OF_WINDHOWL ) + nDeposit;
         GiveFlag( __FLAG_BANK_OF_WINDHOWL, nCurrentGold )
         LOG_GOLD_DEPOSIT( nCurrentGold, nDeposit, INTL( 9982, "the Stonecrest Bank (NPC)") )
         Conversation
         INTL( 1770, "Thank you! Your gold will be safe with me!")
      ELSE
         Conversation
         INTL( 1771, "You cannot deposit gold pieces you do not have.")
      ENDIF
   ELSE
		Conversation
		INTL( 9983, "You must tell me how much gold pieces you wish to deposit. For instance, "
		"if you would like to deposit 10 gold pieces, you would simply tell me "
		"{DEPOSIT} {10} {GOLD}. You may also \"withdraw\" or verify your \"balance\".")
   ENDIF

ParamCmd(INTL( 1774, "WITHDRAW $ GOLD"))
"";
   int nWithdraw = NUM_PARAM( 0 );
   IF (nWithdraw < 1 )
      Conversation
      INTL( 9984, "You won't fool me today.")
   ELSEIF (nWithdraw != 0 )
      IF (CheckFlag( __FLAG_BANK_OF_WINDHOWL ) >= nWithdraw )
         GiveGoldNoEcho( nWithdraw ) 
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 9985, "You withdraw %u gold from the bank."), nWithdraw) )			         
         int nCurrentGold = CheckFlag( __FLAG_BANK_OF_WINDHOWL ) - nWithdraw;
         GiveFlag( __FLAG_BANK_OF_WINDHOWL, nCurrentGold )
         LOG_GOLD_WITHDRAW( nCurrentGold, nWithdraw, INTL( 9982, "the Stonecrest Bank (NPC)") )
         Conversation
         INTL( 1776, "Remember that it is safer to store your gold pieces in our bank.")
      ELSE
         Conversation
         INTL( 1777, "I am truly sorry, but you do not have that many gold pieces in your account.")
      ENDIF
   ELSE
      Conversation
      INTL( 9986, "You must tell me how much gold pieces you wish to withdraw. For instance, "
      "if you would like to withdraw 10 gold pieces, you would simply tell me "
      "{WITHDRAW} {10} {GOLD}. You may also \"deposit\" or verify your \"balance\".")
   ENDIF

Command(INTL( 1780, "DEPOSIT"))
INTL( 9987, "You must tell me how much gold pieces you wish to deposit. For instance, "
"if you would like to deposit 10 gold pieces, you would simply tell me "
"{DEPOSIT} {10} {GOLD}. Of course, you may also view your \"balance\" or "
"\"withdraw\" gold from your account at any time you want except during "
"the night since we are closed.")

Command(INTL( 1782, "WITHDRAW"))
INTL( 9988, "You must tell me how much gold pieces you wish to withdraw. For instance, "
"if you would like to withdraw 10 gold pieces, you would simply tell me "
"{WITHDRAW} {10} {GOLD}. Of course, you may also view your \"balance\" or "
"\"deposit\" gold to your account at any time you want except during "
"the night since we are closed.")

Command2(INTL( 554, "HELP"),INTL( 4275, "HINT"))
INTL( 9989, "You're asking the wrong fellow. I have no help to give, not even to sell. Go see "
"the old gypsy if you need your future told, I hear she's quite accurate... if you "
"have the bank account to back it up.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 4652, "It was nice talking to you.")
BREAK

Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
   INTL( 5910, "What was that you said?")
ELSE
   Conversation
   INTL( 5758, "I have no interest in that matter.")
ENDIF

EndTalk
}


