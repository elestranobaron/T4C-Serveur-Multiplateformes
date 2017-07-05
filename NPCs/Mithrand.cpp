#pragma hdrstop
#include "Mithrand.h"

Mithrand::Mithrand()
{}

Mithrand::~Mithrand()
{}

extern NPCstructure::NPC Nobleman;

void Mithrand::Create(){
	npc = Nobleman;
	SET_NPC_NAME( "[3050]Mithrand" );
	npc.InitialPos.X = 2961;
	npc.InitialPos.Y = 1093;
	npc.InitialPos.world = 0;
	npc.boPrivateTalk = TRUE;
}

void Mithrand::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	switch(rnd(0, 1)){
	case 0: SHOUT(INTL( 1378, "AHHHHHHHHHHHHHH!")); break;
	case 1: SHOUT(INTL( 1756, "HELP! GUARDS! GUARDS!")); break;
	}
	self->Do(flee);
	self->SetTarget(target);
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Mithrand::OnTalk( UNIT_FUNC_PROTOTYPE )
{
InitTalk

Begin
""
IF(CheckFlag(__FLAG_ADDON_STORYLINE_PROGRESS) == 21)
	Conversation
	INTL( 11771, "I heard something from outside earlier but I am too busy with work to go see what happened.")
ELSE
	Conversation
	INTL( 1757, "Yes? What do you want? I am \"working\", so be quick.")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 1758, "My name is Mithrand. I \"work\" for the town's \"Lord\".")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 1759, "I work for Kirlor, the \"Lord\" of Lighthaven.")

Command(INTL( 523, "ANNABELLE"))
INTL( 7180, "I have heard of that woman, but I never saw her myself.")

Command2(INTL( 509, "BALORK"),INTL( 510, "BRAND"))
INTL( 7181, "Devilish monster? Cursed from beyond? Marked from eternity? Yeah, right!")

Command(INTL( 1435, "LORD"))
INTL( 1761, "His name is Kirlor Dhul. He is the first and only Lord this town ever had. "
"Probably the last one too if that blasted \"King\" doesn't do anything soon. ")

Command(INTL( 1072, "KING"))
INTL( 1762, "Yes, Theodore XIII. He is the King of \"Goldmoon\", and it almost looks like "
"he doesn't care what happens to the kingdom.")

Command(INTL( 753, "GOLDMOON"))
INTL( 1763, "Don't you know anything? Goldmoon is the kingdom regrouping all the towns "
"on the islands of \"Arakas\" and \"Raven's\" \"Dust\".")

Command(INTL( 1764, "BALANCE"))
FORMAT(INTL( 1765, "You have %u gold pieces in your bank account."), CheckFlag( __FLAG_BANK_OF_WINDHOWL) )

ParamCmd(INTL( 1767, "DEPOSIT $ GOLD"))
"";
int nDeposit = NUM_PARAM( 0 );
  IF (nDeposit < 1 )
    Conversation
    INTL( 1768, "I am not a foolish banker!")
  ELSEIF (nDeposit != 0 )
   IF (Gold >= nDeposit )
     TakeGold( nDeposit ) 
     int nCurrentGold = CheckFlag( __FLAG_BANK_OF_WINDHOWL ) + nDeposit;
     GiveFlag( __FLAG_BANK_OF_WINDHOWL, nCurrentGold )
     LOG_GOLD_DEPOSIT( nCurrentGold, nDeposit, INTL( 7182, "the Lighthaven Bank (Mithrand)") )
     Conversation
     INTL( 1770, "Thank you! Your gold will be safe with me!")
   ELSE
     Conversation
     INTL( 1771, "You cannot deposit gold pieces you do not have.")
   ENDIF
  ELSE
    Conversation
    INTL( 1772, "You must tell me how much gold pieces you wish to deposit. For instance, "
    "if you would like to deposit 10 gold pieces, you would simply tell me "
    "{DEPOSIT} {10} {GOLD}. You may also \"withdraw\" or verify your \"balance\".")
  ENDIF

Command(INTL( 2316, "BANK"))
INTL( 2797, "Yes, I am the banker of Lighthaven's bank.")

ParamCmd(INTL( 1774, "WITHDRAW $ GOLD"))
"";
  int nWithdraw = NUM_PARAM( 0 );
  IF (nWithdraw < 1 )
   Conversation
   INTL( 1775, "I am not a foolish banker.")
  ELSEIF (nWithdraw != 0 )
   IF (CheckFlag( __FLAG_BANK_OF_WINDHOWL ) >= nWithdraw )
     GiveGold( nWithdraw ) 
     int nCurrentGold = CheckFlag( __FLAG_BANK_OF_WINDHOWL ) - nWithdraw;
     GiveFlag( __FLAG_BANK_OF_WINDHOWL, nCurrentGold )
     LOG_GOLD_WITHDRAW( nCurrentGold, nWithdraw, INTL( 1769, "the LightHaven Bank (Mithrand)") )
     Conversation
     INTL( 1776, "Remember that it is safer to store your gold pieces in our bank.")
   ELSE
     Conversation
     INTL( 1777, "I am truly sorry, but you do not have that many gold pieces in your account.")
   ENDIF
  ELSE
   Conversation
   INTL( 1778, "You must tell me how many gold pieces you wish to withdraw. For instance, "
   "if you would like to withdraw 10 gold pieces, you would simply tell me "
   "{WITHDRAW} {10} {GOLD}. You may also \"deposit\" or verify your \"balance\".")
  ENDIF

  Command(INTL( 1780, "DEPOSIT"))
INTL( 1781, "You must tell me how many gold pieces you wish to deposit. For instance, "
"if you would like to deposit 10 gold pieces, you would simply tell me "
"{DEPOSIT} {10} {GOLD}. Of course, you may also view your \"balance\" or "
"\"withdraw\" gold from your account at any time you want except during "
"the night since we are closed.")

Command(INTL( 1782, "WITHDRAW"))
INTL( 1783, "You must tell me how many gold pieces you wish to withdraw. For instance, "
"if you would like to withdraw 10 gold pieces, you would simply tell me "
"{WITHDRAW} {10} {GOLD}. Of course, you may also view your \"balance\" or "
"\"deposit\" gold to your account at any time you want except during "
"the night since we are closed.")

Command(INTL( 793, "RAVEN'S DUST"))
INTL( 1784, "Bah! I'm getting tired of your ignorance... Go bother someone else!") BREAK

Command(INTL( 515, "ARAKAS"))
INTL( 1785, "Humpf! It is the name of the island you are currently on.")
		 
Command(INTL( 1257, "MERCHANT"))
INTL( 2798, "These days, it is near impossible for the merchants of our fair city to do business with our "
"sister town, \"Windhowl\". If you would like to help one of our merchants, you must talk to "
"\"Lord\" \"Kirlor\" and \"register\" yourself. He will then give you a letter that you must "
"give to either \"Sigfried\" or \"Rolph\". They'll give you a report that must be delivered "
"to \"Lord\" \"Sunrock\" in Windhowl as fast as possible.")

Command(INTL( 1648, "REGISTER"))
INTL( 2799, "You must say this to \"Lord\" \"Kirlor\", not me!")

Command(INTL( 2518, "SIGFRIED"))
INTL( 2781, "Sigfried is the town's weaponsmith.")

Command(INTL( 2345, "ROLPH"))
INTL( 7163, "Rolph is the town's armorer.")

Command(INTL( 1436, "KIRLOR"))
INTL( 2783, "He is the town's Lord.")

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 1607, "Lighthaven is the name of our fair city.")

Command(INTL( 514, "WINDHOWL"))
INTL( 1789, "The westernmost town of the island, Windhowl is falling prey to many wandering "
"brigands and other assortments of strange creatures.")

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 520, "QUIT"),INTL( 521, "EXIT"))
INTL( 1790, "About time.") BREAK

Default
INTL( 1791, "I don't know.")

EndTalk

}
