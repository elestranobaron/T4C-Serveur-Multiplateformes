//////////////////////////////////////////////////////////////////////
// GreyarEedy.cpp: implementation of the GreyarEedy class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "GreyarEedy.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GreyarEedy::GreyarEedy()
{}

GreyarEedy::~GreyarEedy()
{}

extern NPCstructure::NPC GreyarEedyNPC;

//Nom: Greyar Eedy.
//Statistique: Windhowl noble.
//Position: (2138, 601) Lord's Office.
//World: 0
//Description: Banker.
//Body: __NPC_RICH_PAYSAN
//OnAttacked: "THIEF! HELP!"

//////////////////////////////////////////////////////////////////////////////////////////
void GreyarEedy::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of GreyarEedy
//
{
	npc = GreyarEedyNPC;
	SET_NPC_NAME( "[3004]Greyard Eedy" );
	npc.InitialPos.X = 1620;
	npc.InitialPos.Y = 1209;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
void GreyarEedy::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of GreyarEedy
//
{
InitTalk

Begin
INTL( 2313, "One hundred and twelve, one hundred... Grr, you made me lose my count.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2314, "My name? Humpf what a waste of time. Oh well, if you insist, I am Greyar "
"Eedy.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2315, "Isn't it obvious? I am the banker of this town. I keep track of all the "
"\"deposits\" and \"withdrawals\" everyone makes. Now be quick, it is a very "
"demanding job and I have other matters to attend to.")

Command(INTL( 523, "ANNABELLE"))
INTL( 1158, "I do not know much about that woman.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 7174, "Devilish monster? Cursed from beyond? Marked from eternity? Yeah, right!")

Command(INTL( 2316, "BANK"))
INTL( 2317, "The Bank of Windhowl will provide you with a secure way of keeping your "
"gold pieces away from the brigands. You may \"deposit\", \"withdraw\" or "
"verify your \"balance\". I do not even operate the bank during the night "
"because I am far too scared of being robbed by cloaked brigands in the "
"shadows of the night.")

Command(INTL( 1764, "BALANCE"))
    FORMAT(INTL( 2318, "You have %u gold pieces in your account."), CheckFlag( __FLAG_BANK_OF_WINDHOWL ))

ParamCmd(INTL( 1767, "DEPOSIT $ GOLD"))
"";
int nDeposit = NUM_PARAM( 0 );
  IF (nDeposit < 1 )
    Conversation
    INTL( 2320, "Sorry, I am not fooled that easily!")
  ELSEIF (nDeposit != 0 )
   IF (Gold >= nDeposit )
    TakeGold( nDeposit ) 
    int nCurrentGold = CheckFlag( __FLAG_BANK_OF_WINDHOWL ) + nDeposit;
    GiveFlag( __FLAG_BANK_OF_WINDHOWL, nCurrentGold )

    LOG_GOLD_DEPOSIT( nCurrentGold, nDeposit, INTL( 2321, "the Windhowl bank (Greyar Eedy)") )

     Conversation
     INTL( 1770, "Thank you! Your gold will be safe with me!")
   ELSE
     Conversation
     INTL( 2322, "But you don't have the gold pieces, my friend!")
   ENDIF
  ELSE
    Conversation
    INTL( 2323, "If you want to deposit gold, you have to type 'deposit <x> gold' where <x> "
    "is the amount of gold pieces you wish to deposit. You may also \"withdraw\" "
    "or verify your \"balance\".")
  ENDIF

ParamCmd(INTL( 1774, "WITHDRAW $ GOLD"))
"";
int nWithdraw = NUM_PARAM( 0 );
 IF (nWithdraw < 1 )
    Conversation
    INTL( 2320, "Sorry, I am not fooled that easily!")
 ELSEIF (nWithdraw != 0 )
   IF (CheckFlag( __FLAG_BANK_OF_WINDHOWL ) >= nWithdraw )
    GiveGold( nWithdraw ) 
    int nCurrentGold = CheckFlag( __FLAG_BANK_OF_WINDHOWL ) - nWithdraw;
    GiveFlag( __FLAG_BANK_OF_WINDHOWL, nCurrentGold )

    LOG_GOLD_WITHDRAW( nCurrentGold, nWithdraw, INTL( 2321, "the Windhowl bank (Greyar Eedy)") )

    Conversation
    INTL( 2325, "Remember that it is safer that I keep them.")
   ELSE
     Conversation
    INTL( 1777, "I am truly sorry, but you do not have that many gold pieces in your account.")
   ENDIF
 ELSE
    Conversation
    INTL( 2326, "What? If you want to withdraw gold, you have to tell me how much you want "
    "to withdraw. Simply type 'withdraw <x> gold' where <x> is the amount of gold "
    "pieces you wish to withdraw. You might also want to \"deposit\" or verify "
    "your \"balance\".")
 ENDIF

Command(INTL( 1780, "DEPOSIT"))
INTL( 2328, "If you wish to deposit gold pieces in the Windhowl bank, you'll have "
"to tell me how many you wish to deposit. Just tell me 'deposit <x> gold' "
"where <x> is the amount of gold pieces you wish to deposit. Or perhaps "
"you would like to verify your \"balance\" or even \"withdraw\" gold "
"from the \"bank\".")

Command(INTL( 1782, "WITHDRAW"))
INTL( 2329, "If you want to withdraw gold pieces from your account, you will have to "
"tell me 'withdraw <x> gold' where <x> is the amount of gold pieces you "
"want to withdraw.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2330, "One, two, three...") BREAK

Default
INTL( 2331, "That is not my business.")

EndTalk

}
