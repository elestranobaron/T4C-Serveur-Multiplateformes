/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "MorindinArrowmist.H"

MorindinArrowmist::MorindinArrowmist()
{}

MorindinArrowmist::~MorindinArrowmist()
{}

extern NPCstructure::NPC Hunter;    // I want an ARCHER damnit!

void MorindinArrowmist::Create( void )
{
      npc = ( Hunter );
      SET_NPC_NAME( "[2972]Morindin Arrowmist" );  
      npc.InitialPos.X = 706; 
      npc.InitialPos.Y = 1912;
      npc.InitialPos.world = 0;
}

void MorindinArrowmist::OnAttack( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnAttack( UNIT_FUNC_PARAM );
	switch(rnd(0, 4)){
	case 0: SHOUT(INTL( 2029, "Die!")); break;
	case 1: SHOUT(INTL( 5514, "Did that hurt?")); break;
	case 2: SHOUT(INTL( 5515, "Feel the PAIN!")); break;
	case 3: SHOUT(INTL( 5516, "Get ready to die!")); break;
	case 4: break;
	}
NPCstructure::OnAttack( UNIT_FUNC_PARAM );
}

void MorindinArrowmist::OnAttacked( UNIT_FUNC_PROTOTYPE ){
	NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
	 switch(rnd(0, 4)){
    case 0: SHOUT(INTL( 5517, "Ouch! Watch out!")); break;
    case 1: SHOUT(INTL( 2032, "Ow!")); break;
    case 2:	SHOUT(INTL( 5518, "You think that hurts?")); break;
    case 3:	SHOUT(INTL( 5519, "You won't get away with this!")); break;
    case 4:	break;
	}
NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}


void MorindinArrowmist::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{

CONSTANT TRANSLATE = 1;
CONSTANT ORCISH = 2; 
CONSTANT ANTELOPE = 3;

InitTalk

Begin
""
IF (CheckFlag(__QUEST_MORINDIN_IGNORED) == 1) // If PC is ignored (Royal Key #4 Quest)...
	IF( (USER_KARMA >= 150) && (USER_LEVEL >= 30)) //...but has improved as requested:
		RemFlag(__QUEST_MORINDIN_IGNORED)
		Conversation
		INTL( 5520, "Ah, I see you have finally grown. Very well, what can I do for you?")
	ELSE //...and still hasn't improved:
		Conversation
		INTL( 5521, "Become a better person and we shall speak.")
		BREAK
	ENDIF
ELSE // If PC isn't being ignored...
	IF (TFCTime::IsSleepTime())
	    Conversation
	    INTL( 5522, "Not now. I'm hunting the wild animals during the night!") BREAK
	ELSE
	    Conversation
	    INTL( 5523, "Greetings! What brings you in these woods?")
	ENDIF
ENDIF

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5524, "I am known as Morindin Arrowmist, the \"hunter\".")  

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 5525, "Cut the chit-chat, what do you want from me?")

Command(INTL( 5526, "HUNTER"))
INTL( 5527, "As a hunter, I have learned how to \"survive\" and sustain myself with the "
"resources that are hidden within the forest. I am always in search for "
"good quality \"antelope\" \"skins\" which I resell at the town after I have "
"tailored them into fine leather jackets. I am also a master tracker. I could follow "
"the tracks of anybody throughout the woods. Let's just say that I have "
"earned quite a few pennies as a bounty hunter. Nowadays I prefer to hunt "
"small animals however for I am not as young as I once was. Still, I can " 
"defend myself against any \"orcs\" or daemon trees that stand in my way.")

Command(INTL( 7295, "SURVIV"))
INTL( 5528, "To survive, you have to be able to mend your wounds. I could \"teach\" "
"you how to use the first aid technique that would help you accomplish that.")

Command(INTL( 5529, "ANTELOPE SKIN"))
""
IF (CheckItem(__OBJ_ANTELOPE_SKIN) >= 2) 
	Conversation
	INTL( 5530, "You have two antelope skins you'd be willing to trade to me?")
	SetYesNo(ANTELOPE)
ELSE
	Conversation
	INTL( 5531, "If you could find 2 antelope skins, I'd be willing to exchange them "
   "for a pouch of dandelion leaves. You might think they are worthless "
   "but I can assure you that they are rare enough around here to be worth "
   "quite a few pennies to some magic-users.")
ENDIF

YES(ANTELOPE)
IF (CheckItem(__OBJ_ANTELOPE_SKIN) >= 2) 
	TakeItem(__OBJ_ANTELOPE_SKIN)
	TakeItem(__OBJ_ANTELOPE_SKIN)
	GiveItem(__OBJ_POUCH_OF_DANDELION_LEAVES)
	Conversation
INTL( 5532, "I thank you for such fine antelope skins. As I've promised, I "	
    "give you this pouch of rare dandelion leaves.")
	;int nExpReward = 2500; 	
	GiveXP(nExpReward)
	Conversation
	FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), nExpReward)
ELSE
	Conversation
	INTL( 5533, "By the snake's tooth! The skins have disappeared!")
ENDIF

NO(ANTELOPE)
Conversation
INTL( 5068, "Too bad.")

YesNoELSE(ANTELOPE)
Conversation
FORMAT(INTL( 5534, "%s, you aren't making sense. Are you willing to trade the two "
       "antelope skins you have, yes or no?"), USER_NAME)
SetYesNo(ANTELOPE)

Command(INTL( 1794, "ROYAL KEY"))
INTL( 5535, "A royal key, me? ")
IF ((CheckFlag(__QUEST_ROYAL_KEY5) >= 12)) // If gone through the whole Kalir/Jamar exchange...
	IF( (USER_KARMA >= 150) && (USER_LEVEL >= 30)) //...and sufficiently good & powerful:
		Conversation
		INTL( 5536, "Indeed, I own such a key, and would gladly lend it to you if it will help "
		"the side of Light. ")
		IF (CheckItem(__OBJ_ROYAL_KEY_5) >= 1) // PC already has a key:
			Conversation
			INTL( 5537, "It appears, however, you already have one, so you don't need another.")
		ELSE // PC has no key, receives one:
			Conversation
			INTL( 5538, "Here it is. May it serve you in your quest for good.")
			GiveItem(__OBJ_ROYAL_KEY_5)
		ENDIF
	ELSE // PC isn't high enough level, or not good enough...
		Conversation
		INTL( 5539, "Increase your worth and power, and we will talk again. Until then, I will not "
		"hear your words.")
		GiveFlag(__QUEST_MORINDIN_IGNORED,1)
	ENDIF
ELSE // PC hasn't talked to Kalir or Jamar just yet.
	Conversation
	INTL( 5540, "Who told you that? Are you a spy or something? You won't hear a pip from me!")
ENDIF

Command2(INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 2392, "Let's begin.")
CreateSkillList
	AddTeachSkill( __SKILL_FIRST_AID, 1, 1000 )
	AddTeachSkill( __SKILL_PARRY, 1, 900 )
SendTeachSkillList

Command(INTL( 502, "TRAIN"))
INTL( 1481, "Very good, then let's begin your training.") 
CreateSkillList
	AddTrainSkill( __SKILL_DODGE, 5000, 10 )
	AddTrainSkill( __SKILL_ARCHERY, 5000, 15 )
	AddTrainSkill( __SKILL_FIRST_AID, 100, 30 )
	AddTrainSkill( __SKILL_PARRY, 100, 75 )
SendTrainSkillList

Command(INTL( 1492, "DESERT"))
INTL( 5552, "Even the best \"hunter\" in the world would find it hard to survive in "
"such as harsh environment.") 

Command(INTL( 744, "ORC"))
INTL( 5553, "Sometimes, I encounter orcs in the forest. Although I do not seek any "
"hostilities, they attack me on sight and I have to defend myself. I've "
"come to understand their crude language over the years. If you have "
"a document that needs to be \"translated\", perhaps I could help you.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 5554, "I am a hunter and an adventurer. I hunt small animals during the night "
"and sell the skins at the town at a fair price.")

Command(INTL( 5555, "TRANSLATE"))
""
IF (CheckFlag(__QUEST_FLAG_MORDRICK_STATUS) == 3) 
	Conversation
	INTL( 5556, "Mordrick Warstone has sent you? Fine then. Do you have a document you'd want me to translate?")
	SetYesNo(TRANSLATE)
ELSE
	Conversation
	INTL( 5557, "I do not see why I would help you translate anything.")
ENDIF

YES(TRANSLATE)
Conversation
INTL( 5558, "Good. However, it will cost you. 5000 gold pieces should be enough to cover "
"my troubles. Agreed?")
SetYesNo(ORCISH)

NO(TRANSLATE)
Conversation
INTL( 5487, "I understand.")

YesNoELSE(TRANSLATE)
Conversation
INTL( 5559, "Pardon me but did you just say a yes or a no?")
SetYesNo(TRANSLATE)

YES(ORCISH)
IF (CheckFlag(__FLAG_MORINDIN_ORCISH) == 1) 
	Conversation
	INTL( 5560, "I've already translated the document. Return to Mordrick Warstone.")
ELSEIF ((Gold >= 5000) && (CheckItem(__OBJ_PLANS) >=1) ) 
	Conversation
	INTL( 5561, "Good! Lemme start... hmm..vigulgul orkentug...shtuoongbouahur.. uguahrgubuaog... "
	"teita... pouahrgu teita... AH! Finished at last! That wasn't easy but I think I was able to "
	"descramble most of it. Bring this back to Mordrick with haste.")
	// kill human, southPark, cartman, die bart die
	GiveFlag(__FLAG_MORINDIN_ORCISH, 1)
	TakeGold(5000)
ELSEIF (CheckItem(__OBJ_PLANS) == 0 )
	Conversation
	INTL( 5562, "But you do not have a document to translate!")
ELSE 	// I assume that the user does not have enough gold pieces. 
	Conversation
	INTL( 5563, "You do not have the required 5000 gold pieces.")
ENDIF

NO(ORCISH)
Conversation
INTL( 1646, "As you wish.")

YesNoELSE(ORCISH)
Conversation
INTL( 5564, "Was that a yes or a no?")
SetYesNo(ORCISH)

Command(INTL( 3860, "GREYLEAF"))
INTL( 5565, "GreyLeaf is of much greater power than the usual demon trees you see in Ravenwood.")

Command2(INTL( 2563, "FOREST"),INTL( 3854, "RAVENWOOD"))
INTL( 5566, "That's the name of this forest. There's not many animals here though. "
"Perhaps I should think of moving into a more healthy forest such as one "
"that can be found on \"Arakas\".")

Command(INTL( 515, "ARAKAS"))
INTL( 5567, "Arakas is the island located north of this one.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 5568, "I see that I'm not in good company right now.") BREAK

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 5569, "Farewell friend.") BREAK

Default
""
IF (rnd.roll( dice( 1, 2 ) ) == 1)
    Conversation
    INTL( 4415, "I have no idea about what you are talking about.")
ELSE
    Conversation
    INTL( 4438, "Now that's something I did not know.")
ENDIF

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void MorindinArrowmist::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL( __SKILL_FIRST_AID, 1, 1000)
			TEACH_SKILL( __SKILL_PARRY, 1, 900 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_DODGE, 5000, 10 )
		TRAIN_SKILL( __SKILL_ARCHERY, 5000, 15 )
		TRAIN_SKILL( __SKILL_FIRST_AID, 100, 30 );
		TRAIN_SKILL( __SKILL_PARRY, 100, 75 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
}
