#pragma hdrstop
#include "GreyLeaf.H"

GreyLeaf::GreyLeaf()
{}

GreyLeaf::~GreyLeaf()
{}

extern NPCstructure::NPC GreyLeafNPC;

void GreyLeaf::Create( void )
{
        npc = ( GreyLeafNPC );
        SET_NPC_NAME( "[2952]GreyLeaf the daemon tree" );
        npc.InitialPos.X = 0;   // Need a location
        npc.InitialPos.Y = 0;   // Need a location
        npc.InitialPos.world = 0;
}

void GreyLeaf::OnDeath( UNIT_FUNC_PROTOTYPE )
{
    INIT_HANDLER
	if( target != NULL )
	{
   IF (CheckItem(__OBJ_GREEN_GEMSTONE) == 0) 
	   SHOUT(INTL( 1864, "..."))		
	ELSE
		SHOUT(INTL( 6320, "ARRRGH!"))
	ENDIF
   IF (CheckItem(__OBJ_BELLADONA_BERRIES) == 0)
      GiveItem(__OBJ_BELLADONA_BERRIES)
		PRIVATE_SYSTEM_MESSAGE(INTL( 10607, "You find some belladona berries.")) 
   ENDIF
   }
    CLOSE_HANDLER
	NPCstructure::OnDeath( UNIT_FUNC_PARAM );
}

void GreyLeaf::OnAttacked( UNIT_FUNC_PROTOTYPE )
{
	if( target != NULL )
	{
      IF (rnd.roll(dice(1,25)) )
         SUMMON( "Demon Tree", FROM_NPC(-4,X), FROM_NPC(-4,Y))
      ENDIF      
	}
	NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void GreyLeaf::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT INGREDIENT1 = 1; 
CONSTANT INGREDIENT2 = 2; 

InitTalk

Begin
""
IF (CheckItem(__OBJ_GREEN_GEMSTONE) == 0) 
	Conversation	// Cannot communicate if user does not have the 
	INTL( 1864, "...")          // green gemstone of the Forest Spirit. 
	BREAK	
ELSE
	Conversation
	INTL( 6321, "You dare to disturb me? What is it that you want?")
ENDIF

Command2(INTL( 3629, " NAME "),INTL( 485, "WHO ARE YOU"))
INTL( 6322, "I am known as Grey Leaf, elder of the Daemon Trees.")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 6323, "That does not concern you. But if you wish to make yourself "
"\"useful\" to me, then perhaps I could find something for you.")

Command(INTL( 6324, "USEFUL"))
""
IF ((CheckItem(__OBJ_POUCH_OF_BLACK_SNAKEROOT) >= 1) && (CheckItem(__OBJ_POUCH_OF_WOODY_NIGHTSHADE) >= 1))
	Conversation
	INTL( 6325, "I am impressed. You have brought back the \"Black\" \"Snakeroot\" and the \"Woody\" \"Nightshade\"? "
	"Now, will you give me the two ingredients I need?")
	SetYesNo(INGREDIENT1)
ELSE
	Conversation
	INTL( 6326, "If you want to make yourself useful to me, you could always try to fetch some "
	"\"Black\" \"Snakeroot\" and some \"Woody\" \"Nightshade\". I could reward you greatly if you could bring "
	"me these special ingredients.")
ENDIF

Command(INTL( 6327, "BLOODSTONE RING"))
INTL( 6328, "If you want this ring, you will have to prove yourself "
"\"useful\" to me in one way or another.")

Command(INTL( 6329, "BLACK SNAKEROOT"))
INTL( 6330, "If you want to make yourself \"useful\", you can always try to get me some.")

Command(INTL( 6331, "WOODY NIGHTSHADE"))
INTL( 6332, "If you want to make yourself \"useful\", you can always try to get me some.")

YES(INGREDIENT1)
IF ((CheckItem(__OBJ_POUCH_OF_BLACK_SNAKEROOT) >= 1) && (CheckItem(__OBJ_POUCH_OF_WOODY_NIGHTSHADE) >= 1))
	GiveItem(__OBJ_BLOODSTONE_RING) 
	TakeItem(__OBJ_POUCH_OF_BLACK_SNAKEROOT)
	TakeItem(__OBJ_POUCH_OF_WOODY_NIGHTSHADE)
	Conversation
	INTL( 6333, "You have done well. Take this bloodstone ring and get "
   "out of my face.")
	;int nExpReward = 4500; 	
	GiveXP(nExpReward)
	Conversation
	FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), nExpReward)
ELSE
	Conversation
	INTL( 6334, "What sort of trickery is this?! Some cheesy sleight-of-hand or weak magic? Do "
	"not make the mistake of lying to me once more or I shall obliterate you. Now, get me the "
	"\"ingredients\" I require!")
ENDIF

NO(INGREDIENT1)
Conversation
INTL( 6335, "No? How dare you? I am GreyLeaf, the Elder Daemon Tree. I could crush you with a single thought. "
"I suggest you that you re-consider. Will you give me the two ingredients I need?")
SetYesNo(INGREDIENT2)

YesNoELSE(INGREDIENT1)
Conversation
INTL( 11531, "Quit babbling to yourself. Did you answer yes or no?")
SetYesNo(INGREDIENT1)

YES(INGREDIENT2)
IF ((CheckItem(__OBJ_POUCH_OF_BLACK_SNAKEROOT) >= 1) && (CheckItem(__OBJ_POUCH_OF_WOODY_NIGHTSHADE) >= 1))
	GiveItem(__OBJ_ETHEREAL_AMULET) 
	TakeItem(__OBJ_POUCH_OF_BLACK_SNAKEROOT)
	TakeItem(__OBJ_POUCH_OF_WOODY_NIGHTSHADE)
	INTL( 6337, "You have done well. Take this ethereal amulet and get "
   "out of my face.")
	;int nExpReward = 3500; 	
	GiveXP(nExpReward)
	Conversation
	FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), nExpReward)
ELSE
	Conversation
	INTL( 6338, "What sort of trickery is this?! Some cheesy sleight-of-hand or weak magic? Do "
	"not make the mistake of lying to me once more or I shall obliterate you. Now, get me the "
	"\"ingredients\" I require!")
ENDIF

NO(INGREDIENT2)
INTL( 6339, "You have abused of my patience.")
FIGHT

YesNoELSE(INGREDIENT2) 
Conversation
INTL( 6336, "Quit babbling to yourself. Did you answer yes or no?")
SetYesNo(INGREDIENT1)

Command2(INTL( 5932, "BELLADONA"),INTL( 5933, "BERRIE"))
INTL( 6340, "They are mine... MINE! You'll have to walk on my trunk if you ever want them.")

Command2(INTL( 6341, "DAEMON"),INTL( 6342, "DEMON"))
INTL( 6343, "They obey my orders and mine alone.") 

Command(INTL( 6344, "HUMAN"))
INTL( 6345, "I despise the inferior race.")

Command(INTL( 3848, "ZHAKAR"))
INTL( 6346, "Zhakar, that clumsy old fool, is always after my \"belladona\" \"berries\" but they are mine.")

Command2(INTL( 3771, "?"),INTL( 793, "RAVEN'S DUST"))
INTL( 6347, "I have no time to answer the questions of an ignorant person.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 6348, "Daemon Trees! I've seen enough of that fool!")
  SUMMON( "Demon Tree", FROM_NPC(-4,X), FROM_NPC(-4,Y))
  SUMMON( "Demon Tree", FROM_NPC(-3,X), FROM_NPC(-3,Y))
  SUMMON( "Demon Tree", FROM_NPC(-2,X), FROM_NPC(-2,Y))
FIGHT

Command4(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"))
INTL( 6349, "It is about time.")
BREAK

Default
INTL( 6350, "Are you finished yet?")

EndTalk
}

