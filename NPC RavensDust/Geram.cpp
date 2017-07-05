//////////////////////////////////////////////////////////////////////
// Geram.cpp: implementation of the Geram class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Geram.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Geram::Geram()
{}

Geram::~Geram()
{}

extern NPCstructure::NPC GeramNPC;

void Geram::Create( ){
    npc = GeramNPC;
	SET_NPC_NAME( "[2949]Geram" );
    npc.InitialPos.X = 1500;
    npc.InitialPos.Y = 2547;
	npc.InitialPos.world = 0;
}

void Geram::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT GOLD = 1;
CONSTANT WORK = 2;
CONSTANT BEER = 3;

InitTalk

Begin
INTL( 5053, "Please, could you spare a gold piece?")
SetYesNo(GOLD)

YES(GOLD)
	IF (Gold >= 1)
		TakeGold(1)
		Conversation
		INTL( 5054, "Thank you very much!")
	ELSE
		Conversation
		INTL( 5055, "I see, you are as poor as I am.")
	ENDIF

NO(GOLD)
	IF (Gold >= 1)
		Conversation
		INTL( 5056, "Please, I beg you! Have some compassion for an old beggar!")
		SetYesNo(GOLD)
	ELSE
		Conversation
		INTL( 5055, "I see, you are as poor as I am.")
	ENDIF

YesNoELSE(GOLD)
	IF (Gold >= 1)
		Conversation
		INTL( 5057, "Please, I'm begging you!")
		SetYesNo(GOLD)
	ELSE
		Conversation
		INTL( 5055, "I see, you are as poor as I am.")
	ENDIF
	
Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 5058, "Hullo!")

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 5059, "Umm, let's see now, I think it was Geram.")

Command(INTL( 4699, "GERAM"))
INTL( 5060, "... oh, are you talking to me? It's been so long since someone spoke that name to me.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 5061, "I don't have any work. Would you happen to be offering me some by any chance?")
SetYesNo(WORK)
  
YES(WORK)
	Conversation
	INTL( 5062, "I don't believe you.")
NO(WORK)
	Conversation
	INTL( 5063, "I thought so.")
YesNoELSE(WORK)
   Conversation
	INTL( 5063, "I thought so.")

Command(INTL( 4696, "COMBINATION"))
""
IF (CheckFlag(__QUEST_VAULT_CODE_TWO) == 0)
	Conversation
	INTL( 5064, "That's not of your business.")
ELSE
	Conversation
	INTL( 5065, "Bah! You want the 2nd number of the combination? I tell you what... I'd trade a mug of ale "
	"anytime for that so-called secret number. So, do you have a lil' mug of fresh ale for me?")
	SetYesNo(BEER)
ENDIF

YES(BEER)
IF (CheckItem(__OBJ_EMPTY_BEER_MUG) == 0)
	Conversation
	INTL( 5066, "Don't try to fool me, I can see that you don't have one.")
ELSE
	TakeItem(__OBJ_EMPTY_BEER_MUG)
	Conversation
	FORMAT(INTL( 5067, "Thank you for the mug of ale! *glurp* *slurp* *aaah* That was quite refreshing. "
	"*hic* Oops, sorry about that, burps happen you know. *smile* Anyhow, I won't make you "
	"wait any longer. The 2nd number of the combination is %u to the LEFT."),CheckFlag(__QUEST_VAULT_CODE_TWO))
ENDIF

NO(BEER)
Conversation
INTL( 5068, "Too bad.")

YesNoELSE(BEER)
Conversation
INTL( 5069, "Uh? Are you drunk or what? Bah!")

Command2(INTL( 3905, "REYNEN"),INTL( 3906, "ASPICDART"))
INTL( 5070, "HIM! He's the reason I'm so poor! That devil took everything I had through gambling, "
"my money, my home and even my wife Adriana! What a tragedy!")

Command(INTL( 3918, "VISITOR"))
INTL( 5071, "A visitor? Well, you folks all look the same to me you know... you're all rich!")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 698, " ASS "),INTL( 697, "ASSHOLE"))
INTL( 5072, "Such evolved language, you probably have a coin or two to spare...")
IF (Gold >= 2)
   TakeGold( rnd.roll(dice(1,2)) )
ENDIF

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 5073, "Goodbye...") BREAK

Default
INTL( 5074, "I don't know...")

EndTalk

}
