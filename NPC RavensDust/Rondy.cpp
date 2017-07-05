/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Rondy.H"

Rondy::Rondy()
{}

Rondy::~Rondy()
{}

extern NPCstructure::NPC RondyNPC;

void Rondy::Create( void )
{
      npc = ( RondyNPC );
      SET_NPC_NAME( "[2978]Rondy" );  
      npc.InitialPos.X = 1594; 
      npc.InitialPos.Y = 2502;
      npc.InitialPos.world = 0;
}

void Rondy::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{
CONSTANT FISH = 1;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_RONDY_HATRED) >= (USER_LEVEL-5))
	Conversation
	INTL( 5696, "Whatta scum ya ar'! Ya killed all m'ah swee' an' lovin' pigs. By tha scythe "
	"of m'ah gran' father, I'll get ya!")
	FIGHT
ELSE 
	IF(CheckFlag(__FLAG_RONDY_HATRED) != 0)
		Conversation
		INTL( 5697, "Been a while since ya kill all m'ah pigs.. Ah'm forgettin' ya 'cause "
		"I think ya matured enough.")
		RemFlag(__FLAG_RONDY_HATRED) 
	ELSE
		Conversation
		INTL( 5698, "Howdy stranger! 'ow's it goin' fer ya?")
      GiveNPCFlag( __RONDY_GAME, rnd.roll ( dice( 1, 100 ) )) 
      GiveNPCFlag( __RONDY_ATTEMPTS, 10 )
   ENDIF
ENDIF

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 5699, "Ah'm the town's farmer. I have the uneasy yet rewarding task of tending "
"t' my field and animals.")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5700, "Ah'm Rondy, the best farmer you'll ever see in the East. No wheat can "
"resist fer long t'my scythe and I.")

Command(INTL( 4701, "RONDY"))
INTL( 5701, "Oy! That's the name.")

Command(INTL( 1744, "FARMER"))
INTL( 5702, "Ah'm a farmer allright. Ya can see the crops behind m'ah house.")

Command(INTL( 5703, "FARM"))
INTL( 5704, "Ah'm very proud of m'ah farm.")

Command(INTL( 3854, "RAVENWOOD"))
INTL( 5705, "Ravenwood forest is cursed I tell ya. Mayhaps the \"druids\" will be "
"able t' do somethin' 'bout it.")

Command(INTL( 746, "DRUID"))
INTL( 5706, "The druids' camp is located west of the town.")

Command(INTL( 1492, "DESERT"))
INTL( 5707, "Oy! Methinks nothin' could grow there. Not enough water ya know.")

Command(INTL( 3865, "VULTURE'S DEN"))
INTL( 5708, "Tha' is the \"desert\"'s name.")

Command(INTL( 4696, "COMBINATION"))
""
IF (CheckFlag(__QUEST_VAULT_CODE_ONE) == 0)
	Conversation
	INTL( 11519, "I have absolutely no idea 'bout what ya are talkin'.")
ELSE
	Conversation
	INTL( 5710, "Well... so ya want the 1st number o' the safe's combination? Hmmmm... I do need "
	"sum' money. I tell ya whut, ah'm gonna play a lil' game with ya an' you can \"guess\" "
	"the number until ya get it right for 1000 gold pieces per attempt.")	
ENDIF	

ParamCmd(INTL( 5711, "GUESS $"))
""
IF (CheckFlag(__QUEST_VAULT_CODE_ONE) == 0)
	Conversation
	INTL( 5712, "I don't see why ya would want t' play m'ah game fer now.")
ELSE
	;int nPlayerGuess = NUM_PARAM ( 0 );
	;int nFarmerGuess = CheckFlag(__QUEST_VAULT_CODE_ONE);
	IF ((nPlayerGuess < 1 ) || (nPlayerGuess > 50 ))
		Conversation
		INTL( 5713, "The number is between 1 and 50. Try again.") 
	ELSE
		IF (Gold < 1000)
			Conversation
			INTL( 5714, "Ah'm truly sorry but ya don't have the 1000 gold pieces I require per attempt!")
		ELSE
			TakeGold(1000)
			IF (nPlayerGuess == nFarmerGuess)
				Conversation
				FORMAT( INTL( 5715, "Correct! The first number of the combination is %u to the RIGHT."), nFarmerGuess)
			ELSEIF (nPlayerGuess < nFarmerGuess)
				Conversation
				INTL( 5716, "Tha number Ah'm thinkin' is HIGHER than that!")
			ELSE
				Conversation
				INTL( 5717, "Tha number Ah'm thinkin' is LOWER than that!")	
			ENDIF
		ENDIF
	ENDIF
ENDIF

Command(INTL( 5718, "GUESS"))
""
IF (CheckFlag(__QUEST_VAULT_CODE_ONE) == 0)
	Conversation
	INTL( 5712, "I don't see why ya would want t' play m'ah game fer now.")
ELSE
	Conversation
	INTL( 5719, "T' play m'ah guess game, ya simply have t' tell me what number ya think it is and I'll "
	"tell ya if the right number is higher or lower. For example, if ya think the number is "
	"10, ya simply have t' write \"GUESS\" \"10\".")
ENDIF

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 5720, "Out of my sight or I'll make ya eat manure!")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 4674, "Farewell stranger.")
BREAK

Default
INTL( 5709, "I have absolutely no idea what ya are talkin' about.")

EndTalk
}

