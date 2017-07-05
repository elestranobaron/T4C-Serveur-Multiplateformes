/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "TalonIrongaze.H"

TalonIrongaze::TalonIrongaze()
{}

TalonIrongaze::~TalonIrongaze()
{}

extern NPCstructure::NPC Warrior;

void TalonIrongaze::Create( void )
{
      npc = ( Warrior );
      SET_NPC_NAME( "[2985]Talon Irongaze" );  
      npc.InitialPos.X = 1372;//2796;//1383; 
      npc.InitialPos.Y = 2399;//226;//2312;
      npc.InitialPos.world = 0;//4;//0;
}

void TalonIrongaze::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{

CONSTANT TIGER = 1;
	
InitTalk

Begin
INTL( 5775, "How may I help you?")

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 5776, "Hello! How may I help you?")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 5777, "I am the guardian of the royal \"treasury\".")

Command(INTL( 4696, "COMBINATION"))
""
IF (CheckFlag(__QUEST_VAULT_CODE_THREE) == 0)
	Conversation
	INTL( 5778, "What the hell are you babbling about?")
ELSE
	Conversation
	INTL( 5779, "You want the 3rd number of the safe's combination? Are you out of your mind?! Hmmmm, well... "
	"lemme see... I guess it wouldn't hurt anyone if I'd tell you what's the third number since "
	"it's useless without the others. Heh! Heh! If you'd have the tooth of a \"tiger\", perhaps "
	"I'd tell you what's the third number. Do you have a tooth of a tiger for me somewhere in "
	"your inventory?")
	SetYesNo(TIGER)
ENDIF

Command(INTL( 5780, "TIGER"))
INTL( 5781, "I have always been rather fond of tigers.")

YES(TIGER)
""
IF (CheckItem(__OBJ_TIGER_TOOTH) >= 1)
	TakeItem(__OBJ_TIGER_TOOTH)
	Conversation
	FORMAT(INTL( 5782, "Oh, it such a nice tiger's tooth! I thank you, my friend. Anyhow, the third number "
	"of the combination is %u to the RIGHT. Shhh! Not that loud!!! Don't tell anyone that I told "
	"you or I'll get into troubles."), CheckFlag(__QUEST_VAULT_CODE_THREE))
ELSE
	Conversation
	INTL( 5783, "LIAR! You do not have a tiger's tooth!")
ENDIF

NO(TIGER)
Conversation
INTL( 5784, "*sigh* So be it.")

YesNoELSE(TIGER)
Conversation
INTL( 5785, "Uh? Nevermind, then.")

Command(INTL( 5786, "KING THEODORE"))
INTL( 5787, "King Theodore does not much care about his wealth. Hopefully, I am here "
"to ensure that his kingdom does not crumble to dust.")

Command(INTL( 1492, "DESERT"))
INTL( 5788, "The desert? That's not place I'd want to live.")

Command3(INTL( 5789, "TREASURE"),INTL( 2316, "BANK"),INTL( 5790, "TREASURY"))
INTL( 5791, "Perhaps you might want to \"deposit\" a few gold pieces in the royal "
"treasure chamber? It will be safe there.") 

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5792, "I go by the name of Talon Irongaze.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 5793, "Same to you! Goodbye.")
BREAK

Command(INTL( 1764, "BALANCE"))
FORMAT(INTL( 2318, "You have %u gold pieces in your account."), CheckFlag( __FLAG_BANK_OF_WINDHOWL ))

ParamCmd(INTL( 1767, "DEPOSIT $ GOLD"))
""
;int nDeposit = NUM_PARAM( 0 );
   IF (nDeposit < 1 )
       Conversation
       INTL( 2320, "Sorry, I am not fooled that easily!")
   ELSEIF (nDeposit != 0 )
      IF (Gold >= nDeposit )
        TakeGold( nDeposit ) 
        int nCurrentGold = CheckFlag( __FLAG_BANK_OF_WINDHOWL ) + nDeposit;
         GiveFlag( __FLAG_BANK_OF_WINDHOWL, nCurrentGold )
         LOG_GOLD_DEPOSIT( nCurrentGold, nDeposit, INTL( 5794, "the Silversky bank (Talon Irongaze)") )
         Conversation
         INTL( 1770, "Thank you! Your gold will be safe with me!")
      ELSE
         Conversation
         INTL( 5795, "But you do not have the gold pieces my friend!")
      ENDIF
   ELSE
        Conversation
        INTL( 5796, "If you want to deposit gold, you have to type deposit <x> gold where x "
        "is the amount of gold pieces you wish to deposit. You may also \"withdraw\" "
        "or verify your \"balance\".")
   ENDIF

ParamCmd(INTL( 1774, "WITHDRAW $ GOLD"))
""
;int nWithdraw = NUM_PARAM( 0 );
 IF (nWithdraw < 1 )
       Conversation
       INTL( 2320, "Sorry, I am not fooled that easily!")
 ELSEIF (nWithdraw != 0 )
      IF (CheckFlag( __FLAG_BANK_OF_WINDHOWL ) >= nWithdraw )
        GiveGold( nWithdraw ) 
        int nCurrentGold = CheckFlag( __FLAG_BANK_OF_WINDHOWL ) - nWithdraw;
        GiveFlag( __FLAG_BANK_OF_WINDHOWL, nCurrentGold )
        LOG_GOLD_WITHDRAW( nCurrentGold, nWithdraw, INTL( 5794, "the Silversky bank (Talon Irongaze)") )
        Conversation
        INTL( 2325, "Remember that it is safer that I keep them.")
      ELSE
         Conversation
        INTL( 1777, "I am truly sorry, but you do not have that many gold pieces in your account.")
      ENDIF
 ELSE
        Conversation
        INTL( 5797, "What? If you want to withdraw gold, you have to tell me how much you want "
        "to withdraw. Simply type 'withdraw <x> gold' where x is the amount of gold "
        "pieces you wish to withdraw. You might also want to \"deposit\" or verify "
        "your \"balance\".")
 ENDIF

Command(INTL( 1780, "DEPOSIT"))
INTL( 5798, "If you wish to deposit gold pieces in the Raven's Dust bank, you'll have "
"to tell me how many you wish to deposit. Just tell me 'deposit <x> gold' "
"where x is the amount of gold pieces you wish to deposit. Or perhaps "
"you would like to verify your \"balance\" or even \"withdraw\" gold "
"from the \"bank\".")

Command(INTL( 1782, "WITHDRAW"))
INTL( 5799, "If you want to withdraw gold pieces from your account, you will have to "
"tell me 'withdraw <x> gold' where x is the amount of gold pieces you "
"want to withdraw.")

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
""
IF (TFCTime::IsDay()) 
	Conversation 
    INTL( 5800, "Goodbye my friend.")
    BREAK
ELSE
	Conversation
    INTL( 5801, "Remember that it's dangerous to carry gold pieces during the night.") 
    BREAK
ENDIF

Default
""
IF (rnd.roll( dice( 1, 2 ) ) == 1) 
    Conversation
    INTL( 4675, "I don't have time for that nonsense.")
ELSE
    Conversation
    INTL( 7699, "What did you just say?")      
ENDIF
                     
EndTalk
}



