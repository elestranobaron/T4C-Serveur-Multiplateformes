#pragma hdrstop
#include "Adriana.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Adriana::Adriana()
{}

Adriana::~Adriana()
{}

extern NPCstructure::NPC AdrianaNPC;

void Adriana::Create( ){
    npc = AdrianaNPC;
    SET_NPC_NAME( "[2912]Adriana" );
    npc.InitialPos.X = 1585; 
    npc.InitialPos.Y = 2528;
    npc.InitialPos.world = 0;
}

void Adriana::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT BOOK_WARFARE = 1;

InitTalk

Begin
INTL( 3878, "Hey you! You look like you need some \"training\"!")
	
Command(INTL( 3629, " NAME "))
INTL( 3879, "Call me Adriana!")

Command(INTL( 3880, "ADRIANA"))
INTL( 3881, "Yeah, that's me.")

Command(INTL( 489, "WORK"))
INTL( 3882, "If you want help developing those fighting skills, you've come to the right place! I have a very "
"useful skill I can \"teach\" you. You won't find all the tricks I can "
"teach you in a \"book\", that much I can tell you!")

Command2(INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 1479, "Very good, this is what I can teach you.")
CreateSkillList
	AddTeachSkill( __SKILL_ARMOR_PENETRATION, 1, 7500 )
	AddTeachSkill( __SKILL_POWERFULL_BLOW, 1, 2500 )
   /*IF( UserSkill(__SKILL_POWERFULL_BLOW) >0 && UserSkill(__SKILL_STUN_BLOW) >0)
      AddTeachSkill( __SKILL_TWOWEAPONS, 1, 10000 )
   ENDIF*/
SendTeachSkillList

Command(INTL( 502, "TRAIN"))
INTL( 1481, "Very good, then let's begin your training.") 
CreateSkillList
	AddTrainSkill( __SKILL_ARMOR_PENETRATION, 100, 300 )
   AddTrainSkill( __SKILL_TWOWEAPONS, 500, 500 )
SendTrainSkillList

Command(INTL( 3903, "BELAGAN"))
INTL( 3904, "So you've met my assistant? He's alright, I guess.")

Command2(INTL( 3905, "REYNEN"),INTL( 3906, "ASPICDART"))
INTL( 3907, "I have nothing to say about him! Ask someone else!")

Command(INTL( 3908, "BOOK OF WARFARE"))
""
IF (CheckItem(__OBJ_BOOK_OF_WARFARE) >= 1)
	Conversation
	INTL( 3909, "Hey! You've got a Book of Warfare on you? Think you'd be interested in trading it? "
	"I'll give you a Blade of Sharpness in return. So, what do you say, yes or no?")
	SetYesNo(BOOK_WARFARE)
ELSE
	Conversation
	INTL( 3910, "I hear it's a fascinating book, but it's extremely hard to find... No, I don't have "
	"any copies to spare. Maybe you want to ask Belagan, he always asks everyone for one.")
ENDIF

YES(BOOK_WARFARE)
IF (CheckItem(__OBJ_BOOK_OF_WARFARE) >= 1)
	Conversation
	INTL( 3911, "Great! Here's your blade. Thanks!")
	TakeItem(__OBJ_BOOK_OF_WARFARE)
	GiveItem(__OBJ_BLADE_OF_SHARPNESS)
ELSE
	Conversation
	INTL( 3912, "Where's the Book of Warfare? I cannot befooled that easily, you know!")
ENDIF

NO(BOOK_WARFARE)
Conversation
INTL( 3913, "Ah well. Was worth asking.")

YesNoELSE(BOOK_WARFARE)
Conversation
INTL( 3914, "Uh huh. Right. Whatever.")

Command(INTL( 1427, "BOOK"))
INTL( 3915, "Hmmm. I am not exactly the bookworm-type but if you ever get a grip on a book "
"called the \"Book\" \"of\" \"Warfare\", I would be immensely grateful if you "
"could give it to me.")

Command(INTL( 3916, "COOK"))
INTL( 3917, "I tell you, that boy's cooking is pretty amazing! If he only had a little more enthusiasm "
"and determination, he could start his own tavern!")

Command(INTL( 3918, "VISITOR"))
INTL( 3919, "There have been several adventurers seeking my training, but none that seemed too unusual.")

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 3920, "Come back if you ever need more training!")
BREAK

Default
INTL( 3921, "Please try to be more specific.")

EndTalk

}

//////////////////////////////////////////////////////////////////////////////////////////
void Adriana::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Rolph data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL( __SKILL_ARMOR_PENETRATION, 1, 7500 )
			TEACH_SKILL( __SKILL_POWERFULL_BLOW, 1, 2500 )
         TEACH_SKILL( __SKILL_TWOWEAPONS       , 1, 10000 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_ARMOR_PENETRATION, 100, 300 )
      TRAIN_SKILL( __SKILL_TWOWEAPONS       , 500, 500 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
}
