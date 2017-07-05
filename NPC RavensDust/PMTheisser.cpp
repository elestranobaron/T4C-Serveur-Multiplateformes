#pragma hdrstop
#include "PMTheisser.H"

PMTheisser::PMTheisser()
{}

PMTheisser::~PMTheisser()
{}

extern NPCstructure::NPC GrimishNPC;

void PMTheisser::Create( void )
{
        npc = ( GrimishNPC );
        SET_NPC_NAME( "PM Theisser" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}

void PMTheisser::OnAttack( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER

  	if( target != NULL )
	{
         IF (Gold >= 1)
            TakeGold(1) // takes one gold per attack he does. 
         ENDIF

	}

    CLOSE_HANDLER
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void PMTheisser::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
  	if( target != NULL )
	{
         IF (CheckItem(__OBJ_HEALING_POTION) >= 1)
            TakeItem(__OBJ_HEALING_POTION) 
         ENDIF

	}
    CLOSE_HANDLER
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}



void PMTheisser::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
  	
    if( target != NULL )
	{
         GiveGold(10000)     
	}
    
    CLOSE_HANDLER
    NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void PMTheisser::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT TICKET = 1; 
CONSTANT QUEST = 2; 

InitTalk

Begin
""
IF(lpUser->GetGodFlags() & GOD_CAN_SUMMON_MONSTERS)
   Conversation
   INTL( 6021, "Well well.")
ELSE
	Conversation
	INTL( 7301, "Unauthorized user entry... communication terminated.")
	BREAK
ENDIF

ParamCmd(INTL( 7248, "VIEW $"))
""
IF ( NUM_PARAM(0) == 0)
	Conversation
	INTL( 7249, "VIEW <Global Flag Number>")
ELSE
	Conversation
	FORMAT(INTL( 7250, "Global Flag %u is currently set to %u."), NUM_PARAM(0), CheckGlobalFlag( NUM_PARAM(0))) 
ENDIF




/*******************/
/** LOTTERY START **/
/*******************/

Command(INTL( 5438, "ODD"))
""
IF (CheckNPCFlag(__NPC_NAME_LOTTERY_AMOUNT_USERS) == 0)
   Conversation
   INTL( 6022, "We're currently not holding a lottery. You can always \"buy\" \"a\" \"ticket\" for the next one, though.") 
ELSEIF (CheckNPCFlag(__NPC_NAME_LOTTERY_CHECK) == 16)
   Conversation
   FORMAT(INTL( 6023, "There will be no more lottery held until winner #%u "
   "comes forth to \"claim\" the \"jackpot\"."), CheckNPCFlag(__NPC_NAME_LOTTERY_WINNER) )
ELSE   
	IF (CheckNPCFlag(__NPC_NAME_LOTTERY_AMOUNT_USERS) == 1)
		Conversation
		INTL( 6024, "If nobody else buys a lottery ticket, you'll get your money back.")
	ELSE
		Conversation
		FORMAT(INTL( 6025, "The odds of winning the \"jackpot\" are 1 in %u. This could be your lucky day!"), CheckNPCFlag(__NPC_NAME_LOTTERY_AMOUNT_USERS))
	ENDIF
ENDIF

CmdAND("BUY","TICKET")  // BUY A TICKET, BUY TICKET
""
IF ((CheckNPCFlag(__NPC_NAME_LOTTERY_START) < CurrentRound) && (CheckNPCFlag(__NPC_NAME_LOTTERY_START) != 0 ))
   Conversation
   INTL( 6030, "I cannot sell another lottery ticket until the winner \"claims\" the \"jackpot\".")   
ELSEIF (CheckFlag(__FLAG_NAME_LOTTERY_VALIDATION) != 0)
   Conversation
   INTL( 6031, "You say that you already have a number? Then, you must \"validate\" it "
   "at once to see if you are a winner!")
ELSEIF (CheckNPCFlag(__NPC_NAME_LOTTERY_CHECK) == 16)
   Conversation
   FORMAT(INTL( 6032, "There will be no more lottery held until the winner comes forth to \"claim\" the "
	"\"jackpot\". The winning number is %u."), CheckNPCFlag(__NPC_NAME_LOTTERY_WINNER) )
ELSE
   Conversation
   INTL( 6033, "It will cost you a mere 1000 gold pieces for an entry in the \"lottery\". Do you agree "
	"to pay that fee?")
   SetYesNo(TICKET)
ENDIF

CmdAND(INTL( 7195, "PURCHASE"),INTL( 7196, "TICKET"))
""
IF ((CheckNPCFlag(__NPC_NAME_LOTTERY_START) < CurrentRound) && (CheckNPCFlag(__NPC_NAME_LOTTERY_START) != 0 ))
   Conversation
   INTL( 6030, "I cannot sell another lottery ticket until the winner \"claims\" the \"jackpot\".")   		
ELSEIF (CheckFlag(__FLAG_NAME_LOTTERY_VALIDATION) != 0)
   Conversation
   INTL( 6031, "You say that you already have a number? Then you must \"validate\" it "
   "at once to see if you are a winner!")
ELSEIF (CheckNPCFlag(__NPC_NAME_LOTTERY_CHECK) == 16)
   Conversation
	FORMAT(INTL( 6032, "There will be no more lottery held until the winner comes forth to \"claim\" the "
	"\"jackpot\". The winning number is %u."), CheckNPCFlag(__NPC_NAME_LOTTERY_WINNER) )   
ELSE
   Conversation
   INTL( 6033, "It will cost you a mere 1000 gold pieces for an entry in the \"lottery\". Do you agree "
	"to pay that fee?")
   SetYesNo(TICKET)
ENDIF

YES(TICKET)
   IF (Gold >= 1000)
      TakeGold(1000)      
      GiveNPCFlag(__NPC_NAME_LOTTERY_JACKPOT, (CheckNPCFlag(__NPC_NAME_LOTTERY_JACKPOT)+1000))
      GiveNPCFlag(__NPC_NAME_LOTTERY_AMOUNT_USERS, (CheckNPCFlag(__NPC_NAME_LOTTERY_AMOUNT_USERS)+1))
      IF (CheckNPCFlag(__NPC_NAME_LOTTERY_START) == 0)
         GiveNPCFlag(__NPC_NAME_LOTTERY_START, 2 HOURS TDELAY)         
      ENDIF
      Conversation
      FORMAT(INTL( 6034, "Congratulations! Your number for the lottery is %u and there is currently %u gold pieces in the jackpot! Good luck!"), CheckNPCFlag(__NPC_NAME_LOTTERY_AMOUNT_USERS) , CheckNPCFlag(__NPC_NAME_LOTTERY_JACKPOT))
      GiveFlag(__FLAG_NAME_LOTTERY_TICKET, (CheckNPCFlag(__NPC_NAME_LOTTERY_AMOUNT_USERS)) )
      GiveFlag(__FLAG_NAME_LOTTERY_VALIDATION, (CheckNPCFlag(__NPC_NAME_LOTTERY_START)) )
   ELSE
      Conversation
      INTL( 6035, "The fee is 1000 gold pieces, no more, no less.")
   ENDIF

NO(TICKET)
Conversation
INTL( 6036, "Sad. This could make you a rich person.")

YesNoELSE(TICKET)
Conversation
INTL( 6037, "Do you agree to pay the fee of 1000 gold pieces to enter the lottery?")
SetYesNo(TICKET)

CmdAND("LOTTERY","TIME") // WHAT IS THE LOTTERY TIME, TIME OF THE LOTTERY, LOTTERY TIME
""
// * * * CHECK HERE IF IT IS TIME TO PICK A LUCKY NUMBER * * * 
IF ((CheckNPCFlag(__NPC_NAME_LOTTERY_START) != 0) && (CheckNPCFlag(__NPC_NAME_LOTTERY_CHECK) != 16) && (CheckNPCFlag(__NPC_NAME_LOTTERY_START) <= CurrentRound))
   GiveNPCFlag(__NPC_NAME_LOTTERY_WINNER, rnd.roll( dice( 1, CheckNPCFlag(__NPC_NAME_LOTTERY_AMOUNT_USERS) ) ) )
   GiveNPCFlag(__NPC_NAME_LOTTERY_CHECK, 16)
   GiveNPCFlag(__NPC_NAME_LOTTERY_ELAPSE_TIME, rnd.roll( dice(2, 45, 60) ) MINUTES TDELAY )
   Conversation
   FORMAT(INTL( 6038, "It is time to pick yet another lucky winner! The number of the winner is... #%u!"),CheckNPCFlag(__NPC_NAME_LOTTERY_WINNER) )
ELSEIF (CheckNPCFlag(__NPC_NAME_LOTTERY_START) == 0)
   Conversation
   INTL( 6039, "We're currently not holding a lottery. Perhaps you'd want to \"buy\" \"a\" \"ticket\"?")
ELSEIF (CheckNPCFlag(__NPC_NAME_LOTTERY_CHECK) == 16)
   Conversation
   FORMAT(INTL( 6040, "There will be no more lottery held until winner #%u comes forth to \"claim\" "
	"the \"jackpot\"."), CheckNPCFlag(__NPC_NAME_LOTTERY_WINNER) )
ELSE
   int nLotteryTime = ((CheckNPCFlag(__NPC_NAME_LOTTERY_START) - CurrentRound) / 1200)
   Conversation
   FORMAT(INTL( 7197, "The lottery pick will be held in %u minutes."),nLotteryTime)
ENDIF

Command2(INTL( 6042, "CLAIM"),INTL( 6043, "VALIDATE"))
""
// * * * CHECK HERE IF THE WINNER FORGOT TO CLAIM HIS JACKPOT * * * 
;int nLotteryTime = ((CheckNPCFlag(__NPC_NAME_LOTTERY_START) - CurrentRound) / 1200)
IF ((CheckNPCFlag(__NPC_NAME_LOTTERY_ELAPSE_TIME) <= CurrentRound) && (CheckNPCFlag(__NPC_NAME_LOTTERY_ELAPSE_TIME) != 0) && (CheckNPCFlag(__NPC_NAME_LOTTERY_CHECK) == 16) )
	GiveNPCFlag(__NPC_NAME_LOTTERY_ELAPSE_TIME, 0)
	GiveNPCFlag(__NPC_NAME_LOTTERY_START, 0)
	GiveNPCFlag(__NPC_NAME_LOTTERY_WINNER, 0)
	GiveNPCFlag(__NPC_NAME_LOTTERY_AMOUNT_USERS, 0)
	GiveNPCFlag(__NPC_NAME_LOTTERY_CHECK, 0)	
// * * * JACKPOT IS LEFT UNTOUCHED FOR THE NEXT DRAW
ENDIF

// * * * CHECK HERE IF IT IS TIME TO PICK A LUCKY NUMBER * * * 
IF ((CheckNPCFlag(__NPC_NAME_LOTTERY_START) != 0) && (CheckNPCFlag(__NPC_NAME_LOTTERY_CHECK) != 16) && (CheckNPCFlag(__NPC_NAME_LOTTERY_START) <= CurrentRound))
	GiveNPCFlag(__NPC_NAME_LOTTERY_WINNER, rnd.roll( dice( 1, CheckNPCFlag(__NPC_NAME_LOTTERY_AMOUNT_USERS) ) ) )
	GiveNPCFlag(__NPC_NAME_LOTTERY_CHECK, 16)
	GiveNPCFlag(__NPC_NAME_LOTTERY_ELAPSE_TIME, rnd.roll( dice(2, 45, 60) ) MINUTES TDELAY )
ENDIF

// * * * USER HAS A VALID TICKET BUT THE LOTTERY PICK DID NOT HAPPEN YET * * * 
IF ((CheckFlag(__FLAG_NAME_LOTTERY_VALIDATION) == CheckNPCFlag(__NPC_NAME_LOTTERY_START)) && (CheckNPCFlag(__NPC_NAME_LOTTERY_CHECK) != 16))
	Conversation
	FORMAT(INTL( 6041, "The lottery pick will be held in %u minutes."),nLotteryTime)  
// * * * USER DOES NOT HAVE A VALID TICKET -- OUTDATED TICKET * * * 
ELSEIF (((CheckFlag(__FLAG_NAME_LOTTERY_VALIDATION) != CheckNPCFlag(__NPC_NAME_LOTTERY_START)) && (CheckFlag(__FLAG_NAME_LOTTERY_VALIDATION))))
	Conversation
	INTL( 6044, "Either you did not claim your prize in time or you aren't a winner because your lottery ticket is "
	"outdated. Better luck next time. Perhaps you might want to buy another \"ticket\".")	
   RemFlag(__FLAG_NAME_LOTTERY_VALIDATION)
   RemFlag(__FLAG_NAME_LOTTERY_TICKET)
// * * * USER HAS CORRECT VALIDATION FLAG AND THE DRAW OCCURED BUT ISN'T THE WINNER)
ELSEIF (((CheckFlag(__FLAG_NAME_LOTTERY_VALIDATION) == CheckNPCFlag(__NPC_NAME_LOTTERY_START)) && (CheckNPCFlag(__NPC_NAME_LOTTERY_CHECK) == 16)) && (CheckFlag(__FLAG_NAME_LOTTERY_TICKET) != CheckNPCFlag(__NPC_NAME_LOTTERY_WINNER)) && (CheckNPCFlag(__NPC_NAME_LOTTERY_CHECK) == 16))
	Conversation
	FORMAT(INTL( 6045, "It appears that you aren't the winner of the \"jackpot\". Better luck next time. The winner of "
	"the jackpot is number #%u."), CheckNPCFlag(__NPC_NAME_LOTTERY_WINNER) ) 
	RemFlag(__FLAG_NAME_LOTTERY_VALIDATION)
   RemFlag(__FLAG_NAME_LOTTERY_TICKET)
// * * * C O N G R A T U L A T I O N S, USER HAS WON THE JACKPOT  * * * 
ELSEIF ((CheckNPCFlag(__NPC_NAME_LOTTERY_START) == CheckFlag(__FLAG_NAME_LOTTERY_VALIDATION)) && (CheckFlag(__FLAG_NAME_LOTTERY_VALIDATION) != 0) && (CheckFlag(__FLAG_NAME_LOTTERY_TICKET) == CheckNPCFlag(__NPC_NAME_LOTTERY_WINNER)) && (CheckFlag(__FLAG_NAME_LOTTERY_TICKET) != 0 ))
	Conversation
	FORMAT(INTL( 6046, "Congratulations! You've just won the JACKPOT of %u gold pieces!"), CheckNPCFlag(__NPC_NAME_LOTTERY_JACKPOT))
	GiveGold(CheckNPCFlag(__NPC_NAME_LOTTERY_JACKPOT) )
	GiveNPCFlag(__NPC_NAME_LOTTERY_CHECK,0)
	GiveNPCFlag(__NPC_NAME_LOTTERY_JACKPOT, 0 )
	GiveNPCFlag(__NPC_NAME_LOTTERY_START, 0)
	GiveNPCFlag(__NPC_NAME_LOTTERY_AMOUNT_USERS, 0)
	GiveNPCFlag(__NPC_NAME_LOTTERY_WINNER, 0)
	GiveNPCFlag(__NPC_NAME_LOTTERY_ELAPSE_TIME, 0)
	RemFlag(__FLAG_NAME_LOTTERY_VALIDATION)
	RemFlag(__FLAG_NAME_LOTTERY_TICKET)
// * * * USER DOES NOT HAVE A TICKET AT ALL * * *
ELSEIF ((CheckFlag(__FLAG_NAME_LOTTERY_TICKET) == 0) && (CheckFlag(__FLAG_NAME_LOTTERY_VALIDATION) == 0 ))
	Conversation
	INTL( 6047, "You must \"buy\" \"a\" \"ticket\" if you want a shot at winning the \"jackpot\".")
ELSE
// * * * PRAY GOD THAT THE USER WON'T SEE THIS * * * 
	Conversation
	INTL( 6048, "{The} {script} {should} {have} {ended} {previously.} {Please} {report} {this} {bug} {to} {Vircom} {immediately.}")
ENDIF

Command(INTL( 6026, "JACKPOT"))
""
IF (CheckNPCFlag(__NPC_NAME_LOTTERY_JACKPOT) == 0)
   Conversation
   INTL( 6027, "There is currently no jackpot.")
ELSEIF (CheckNPCFlag(__NPC_NAME_LOTTERY_CHECK) == 16)
   Conversation
   FORMAT(INTL( 6028, "The jackpot is currently at %u gold pieces. However, we already have a winner if he or she would care to \"claim\" it."), CheckNPCFlag(__NPC_NAME_LOTTERY_JACKPOT) )  
ELSE
   Conversation
   FORMAT(INTL( 6029, "The jackpot is currently at %u gold pieces. I could tell you what are the \"odds\" of winning it if you want."), CheckNPCFlag(__NPC_NAME_LOTTERY_JACKPOT) )
ENDIF

Command(INTL( 6049, "LOTTERY"))
INTL( 6050, "The lottery system is quite simple. First, you must \"buy\" \"a\" \"ticket\" from me for only 1000 "
"gold pieces. I'll pick the winner exactly 2 hours after the first ticket has been bought. I can tell "
"you the \"lottery\" \"time\" if you ask me. If the winner does not \"claim\" the \"jackpot\" after a "
"while, the gold pieces are automatically added to the next jackpot.")

/*******************/
/** LOTTERY END **/
/*******************/

Command2(INTL( 1070, "WAGER"),INTL( 5207, "GAME"))
INTL( 6051, "It is quite simple to play the game I host and be a very rich person. You tell me what number you "
"wish to \"pick\" and give me 1000 gold pieces. Then, I pick 5 numbers out of this sack. Each time "
"I pick your number, you win 1000 gold pieces! You can win up to {FIVE} times your wager. I'm telling "
"you, this could be your lucky day!")

ParamCmd(INTL( 5242, "PICK $"))
""
;int nWhatNumberYouPicked = NUM_PARAM( 0 );
// * * * Parameters weren't entered correctly * * * 
IF (nWhatNumberYouPicked == 0)
	Conversation
	INTL( 6052, "You have to tell me what is the number you wish to pick for the lottery. For example, if you want to "
   "pick number 10, just say {PICK} {10} and you are in business. The number you "
   "choose has to be between 1 and 10.")
// * * * Picked number isn't between 1 and 10 * * * 
ELSEIF ((nWhatNumberYouPicked > 10) || (nWhatNumberYouPicked < 1))
	Conversation
   INTL( 6053, "You must pick a number between 1 and 10.")
// * * * Not enough gold pieces * * * 
ELSEIF (Gold < 1000) 
	Conversation
	INTL( 6054, "You do not have the required 1000 gold pieces.")
ELSE
	TakeGold(1000)	
	int nMatches = 0;
   int nFirstNumber =  rnd.roll( dice(1, 10) );
   int nSecondNumber = rnd.roll( dice(1, 10) );
   int nThirdNumber =  rnd.roll( dice(1, 10) );
   int nFourthNumber = rnd.roll( dice(1, 10) );
   int nFifthNumber =  rnd.roll( dice(1, 10) );

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
		INTL( 6055, " Your number was picked only once. Therefore, I give you the 1000 gold pieces you wagered.")
		GiveGold(1000)
	ELSE
		Conversation
		FORMAT(INTL( 5249, " Your number was picked %u times. Congratulations, you win %u gold pieces!"), nMatches, (1000*nMatches*nMatches))
      GiveGold((1000*nMatches)*nMatches)
	ENDIF   // 1000,4000,9000, 16000, 25000
ENDIF










Command(INTL( 6056, "START GOBLIN"))
""
IF (CheckGlobalFlag(__GLOBAL_FLAG_GOBLIN_QUEST) == 1) 
   Conversation
   INTL( 6057, "Sorry but the Goblin Invasion Quest is currently running.")
ELSE   
   SUMMON ("DORKENROTSMELL", 2690, 905 )            
   GiveGlobalFlag(__GLOBAL_FLAG_GOBLIN_QUEST, 1) 
ENDIF	


Command(INTL( 6058, "SUICIDE"))
FORMAT(INTL( 6059, "As you wish, Master %s."),USER_NAME)
;self->SetHP( self->GetHP(), true ); 
BREAK

Command(INTL( 6060, "ANOTHERCLOCK"))
""
IF (TFCTime::IsEvening())
	Conversation
	FORMAT(INTL( 6061, "Have a nice evening, %s. It is currently %u:%u in the world of Althea."), USER_NAME,(TFCTime::Hour()), (TFCTime::Minute()))
ELSEIF (TFCTime::IsAfterNoon())
	Conversation
	FORMAT(INTL( 6062, "Good afternoon, %s. It is currently %u:%u in the world of Althea."), USER_NAME,(TFCTime::Hour()), (TFCTime::Minute()))
ELSEIF (TFCTime::IsMorning())
	Conversation
	FORMAT(INTL( 6063, "Good morning, %s. It is currently %u:%u in the world of Althea."), USER_NAME,(TFCTime::Hour()), (TFCTime::Minute()))  
ELSE
	Conversation
	FORMAT(INTL( 6064, "%s? You should be in bed at this time. It is currently %u:%u in the world of Althea."), USER_NAME,(TFCTime::Hour()), (TFCTime::Minute()))
ENDIF

Command(INTL( 6065, "CLOCK"))
FORMAT(INTL( 6066, "It is currently %u:%u in the world of Althea."), (TFCTime::Hour()), (TFCTime::Minute()))

Command5(INTL( 518, "BYE"),INTL( 519, "LEAVE"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 6067, "Bye.") BREAK

Default
INTL( 6068, "No.")

EndTalk
}
