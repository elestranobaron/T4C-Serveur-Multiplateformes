/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "CelestinaWaterbreeze.H"

CelestinaWaterbreeze::CelestinaWaterbreeze()
{}

CelestinaWaterbreeze::~CelestinaWaterbreeze()
{}

extern NPCstructure::NPC CelestinaNPC;

void CelestinaWaterbreeze::Create( void )
{
      npc = ( CelestinaNPC );
      SET_NPC_NAME( "[2935]Celestina Waterbreeze" );  
      npc.InitialPos.X = 1499; 
      npc.InitialPos.Y = 2847;
      npc.InitialPos.world = 0;
}

void CelestinaWaterbreeze::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{

CONSTANT GET_KEY = 1;
CONSTANT KILLED_GUARDIAN = 2;
CONSTANT INGREDIENT = 5;

InitTalk

Begin
INTL( 4440, "What can I do to help you adventurer?")

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 4441, "Hi! What can I do for you?")

Command2(INTL( 4442, "CELESTINA"),INTL( 4443, "WATERBREEZE"))
INTL( 4444, "Indeed, Celestina Waterbreeze is my name.")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 4445, "I am Celestina Waterbreeze, sister of \"Dunikus\" \"Hornwind\".")

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 4446, "I do everything that has to be done. Since we are a small community, we "
"have to stick together and share the chores if we want to survive. Currently, " 
"I am trying to save this little \"tree\". As a druid, I feel that it "
"is my duty to protect nature no matter what.")

Command(INTL( 1794, "ROYAL KEY"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY6) >= 1)
	Conversation
	INTL( 4447, "Oh, yes, now I remember, you mean the key I got after trading with Tobias! "
	"I'd completely forgotten about it! Well, is this what you've come to get from "
	"me?")
	SetYesNo(GET_KEY)
ELSE
	Conversation
	INTL( 4448, "I'm sorry, I don't know what you're talking about...")
ENDIF

YES(GET_KEY)
Conversation
INTL( 4449, "I will tell you if you answer this question *truthfully*: Have you ever killed "
"even *one* Forest Guardian?")
SetYesNo(KILLED_GUARDIAN)

NO(GET_KEY)
Conversation
INTL( 4450, "Ah.")

YesNoELSE(GET_KEY)
Conversation
INTL( 3706, "I... see.")

YES(KILLED_GUARDIAN)
IF (CheckFlag(__GUARDIANS_KILLED) >= 1) // If PC killed Guardian and admits to it:
	Conversation
	INTL( 4451, "You speak the truth, and I am saddened that you would kill these gentle, harmless "
	"protectors of nature's work.")
	IF (USER_KARMA <= 100) // If PC's karma is "low":
		Conversation
		INTL( 7186, " I ask that you increase your worth to atone for this sin before I give you the key (\"give\" \"key\").)")
		GiveFlag(__QUEST_TARGET_KARMA, USER_KARMA + 75)
	ELSEIF (USER_KARMA <= 150 )// If PC's karma is already high:
		Conversation
		INTL( 7187, " I ask that you increase your worth to atone for this sin before I give you the key (\"give\" \"key\").)")
		GiveFlag(__QUEST_TARGET_KARMA, USER_KARMA + 50)
	ELSE
		Conversation
		INTL( 7188, " I know you have done much good already, however, so I will ask nothing else from you before I give you the key "
		"(\"give\" \"key\").")
		GiveFlag(__QUEST_TARGET_KARMA, USER_KARMA)
	ENDIF
	IF (CheckFlag(__QUEST_ROYAL_KEY6) == 1)
		GiveFlag(__QUEST_ROYAL_KEY6,2)
	ENDIF
ELSE // If PC hasn't killed Guardians but still pretends he did:
	Conversation
	INTL( 4452, "You are not speaking the truth, but at least you have not committed such a "
	"criminal act.")
	IF (USER_KARMA <= 100) // If PC's karma is "low":
		Conversation
		INTL( 7189, " Still, simply for being dishonest, I ask that you do good deeds, then return to ask "
		"for the key (\"give\" \"key\").")
		GiveFlag(__QUEST_TARGET_KARMA, USER_KARMA + 50)
	ELSEIF (USER_KARMA <= 150) // If PC's karma is already high:
		Conversation
		INTL( 7190, " Still, simply for being dishonest, I ask that you do good deeds, then return to ask "
		"for the key (\"give\" \"key\").")
		GiveFlag(__QUEST_TARGET_KARMA, USER_KARMA + 25)
	ELSE // IF PC's karma is potentially maxed out:
		Conversation
		INTL( 7191, " I know you have done much good already, however, so I will ask nothing else from you before I give you "
		"the key (\"give\" \"key\").")
		GiveFlag(__QUEST_TARGET_KARMA, USER_KARMA)
	ENDIF
	IF (CheckFlag(__QUEST_ROYAL_KEY6) == 1)
		GiveFlag(__QUEST_ROYAL_KEY6,3)
	ENDIF
ENDIF

NO(KILLED_GUARDIAN)
IF (CheckFlag(__GUARDIANS_KILLED) >= 1) // If PC killed Guardian, but denies it:
	Conversation
	INTL( 4453, "That is such a TRAGIC lie! Not only have you committed a *foul* act, but you "
	"have no shame and lie to me about it!")
	IF (USER_KARMA <= 100) // If PC's karma is "low":
		Conversation
		INTL( 7192, " I will not tell you of the key until you have greatly increased your worth. Only then will I "
		"tell you about the key you ask (\"give\" \"key\").")
		GiveFlag(__QUEST_TARGET_KARMA, USER_KARMA + 75)
	ELSEIF (USER_KARMA <= 150) // If PC's karma is already high:
		Conversation
		INTL( 7193, " I will not tell you of the key until you have increased your worth. Only then will I "
		"tell you about the key you ask (\"give\" \"key\").")
		GiveFlag(__QUEST_TARGET_KARMA, USER_KARMA + 50)
	ELSE // IF PC's karma is potentially maxed out:
		Conversation
		INTL( 7194, " Shame on you for lying! It is only because you have proven your worth time again that I will tell you about "
		"the key you ask (\"give\" \"key\").")
		GiveFlag(__QUEST_TARGET_KARMA, USER_KARMA)
		IF (CheckFlag(__QUEST_ROYAL_KEY6) == 1) // Do this once.
			GiveKarma(-10*(500+USER_KARMA)/500) // No karma check necessary because we know karma > 150:
		ENDIF
	ENDIF
	IF (CheckFlag(__QUEST_ROYAL_KEY6) == 1) // Do this once.
		GiveFlag(__QUEST_ROYAL_KEY6,4)
	ENDIF
ELSE // If PC hasn't killed Guardians and says so:
	Conversation
	INTL( 4454, "You are a honorable person, and one who respects nature. I do not keep the "
	"key myself, for it is too precious an item, but I have left it in the care of "
	"Mordrick Warstone, a noble knight. Please speak to him of the key and tell him "
	"I am vouching for your honesty.")
	GiveFlag(__QUEST_ROYAL_KEY6,5)
ENDIF

YesNoELSE(KILLED_GUARDIAN)
Conversation
INTL( 4455, "You must answer with 'yes' or 'no'.")
SetYesNo(KILLED_GUARDIAN)

Command(INTL( 4271, "CUTHANA"))
INTL( 4456, "This herb is extremely hard to find. You can only find it in the Cave of Fear, where lies "
"the corpse of King Theopold.")

CmdAND3(INTL( 4457, "FLASK"),INTL( 4458, "CRYSTAL"),INTL( 2590, "WATER"))
INTL( 4459, "I am afraid I do not know where you could find that.")

Command(INTL( 4460, "GIVE KEY"))
""
SWITCH(CheckFlag(__QUEST_ROYAL_KEY6))
	CASE(0)
		Conversation
		INTL( 4461, "Key? I'm not sure what you're talking about...")
	ENDCASE
	CASE(1)
		Conversation
		INTL( 4462, "What key is that?")
	ENDCASE
	CASE(2)
		IF (USER_KARMA >= CheckFlag(__QUEST_TARGET_KARMA))
			GiveFlag(__QUEST_ROYAL_KEY6,5)
			Conversation
			INTL( 4463, "I am sorry, but I do not have the key. I have left it in the care "
			"of a powerful knight, Mordrick Warstone. Speak to him of it, he will "
			"give it to you.")
		ELSE
			Conversation
			INTL( 4464, "Not yet, you need to improve further.")
		ENDIF
	ENDCASE
	CASE(3)
		IF (USER_KARMA >= CheckFlag(__QUEST_TARGET_KARMA))
			GiveFlag(__QUEST_ROYAL_KEY6,5)
			Conversation
			INTL( 4465, "I am sorry, but I do not have the key. I have left it in the care "
			"of a powerful knight, Mordrick Warstone. Speak to him of it, he will "
			"give it to you.")
		ELSE
			Conversation
			INTL( 4464, "Not yet, you need to improve further.")
		ENDIF
	ENDCASE
	CASE(4)
		IF (USER_KARMA >= CheckFlag(__QUEST_TARGET_KARMA))
			GiveFlag(__QUEST_ROYAL_KEY6,5)
			Conversation
			INTL( 4466, "I am sorry, but I do not have the key. I have left it in the care "
			"of a powerful knight, Mordrick Warstone. Speak to him of it, he will "
			"give it to you.")
		ELSE
			Conversation
			INTL( 4464, "Not yet, you need to improve further.")
		ENDIF
	ENDCASE
	CASE(5)
		Conversation
		INTL( 4467, "I have already told you, Mordrick Warstone has it. He keeps it safe for me.")
	ENDCASE
	OTHERWISE
		Conversation
		INTL( 4468, "I think I've told you enough about this key. Seek it elsewhere.")
	ENDCASE
ENDSWITCH

Command(INTL( 4469, "DEMON TREE"))
INTL( 4470, "The demon trees are the exact opposite of the \"Forest\" \"Guardians\".")

Command(INTL( 836, "FOREST GUARDIAN"))
INTL( 4471, "The Forest Guardians are working with us to protect nature from being "
"harmed.")

Command(INTL( 3844, "NIGHTBLADE"))
INTL( 4472, "The Nightblades are the elite assassins of \"Bane\" \"Blackblood\".")

Command2(INTL( 3862, "BANE"),INTL( 3863, "BLACKBLOOD"))
INTL( 4473, "Bane Blackblood is a mad man. I have heard rumors that he even has "
"spies lurking from inside the castle of \"King\" \"Theodore\".")

Command2(INTL( 754, "THEODORE"),INTL( 1072, "KING"))
INTL( 4474, "I do not care about King Theodore because he doesn't care for us either.")

Command(INTL( 680, "ORDER OF NATURE"))
INTL( 4475, "The Order of Nature is dedicated to the well-being of nature.")

Command2(INTL( 682, "YRIAN"),INTL( 683, "EARTHSONG"))
INTL( 4476, "Yrian Earthsong is an elder druid who founded the \"Order\" \"of\" \"Nature\". ")

Command(INTL( 475, "STONE OF LIFE"))
INTL( 4477, "I do not think it was a good idea to create the Stone of Life for its "
"powers could be used for evil.")

Command2(INTL( 841, "DUNIKUS"),INTL( 842, "HORNWIND"))
INTL( 4478, "Dunikus Hornwind is also a druid and he lives in northern Arakas with "
"his mentor, \"Yrian\" \"Earthsong\". Like my brother, I teach what \"knowledge\" I can "
"pass on to anyone I meet.")

Command(INTL( 4479, " TREE "))
""
IF (CheckItem(__OBJ_FLASK_OF_CRYSTAL_WATER) >= 2)
	Conversation
	FORMAT(INTL( 4480, "You've found two flasks of crystal water for my dying tree? You have done well, %s. "
	"Do you agree to give these to me?"), USER_NAME)
	SetYesNo(INGREDIENT)
ELSE
	Conversation
	FORMAT(INTL( 4481, "%s, this small tree will perish if you don't find me at least 2 flasks of "
	"crystal water. Perhaps you could find some for me, eh?"), USER_NAME)
ENDIF

YES(INGREDIENT)
IF (CheckItem(__OBJ_FLASK_OF_CRYSTAL_WATER) >= 2)
	TakeItem(__OBJ_FLASK_OF_CRYSTAL_WATER)
	TakeItem(__OBJ_FLASK_OF_CRYSTAL_WATER)	
	GiveItem(__OBJ_POUCH_OF_WILLOW_BARK)
	Conversation
	FORMAT(INTL( 4482, "Thank you, %s. See? The little tree is already feeling better. "
          "Take this little pouch of Willow bark. You will see, it will prove "
          "useful to you someday."), USER_NAME)
	;int nExpReward  = 8000; 	
	GiveXP(nExpReward)
	Conversation
	FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), nExpReward)
ELSE
	Conversation
	INTL( 4483, "What foul trick is this? The flasks have evaporated or what?")
ENDIF

NO(INGREDIENT)
Conversation
INTL( 4484, "I truly hope you have a good use for the flasks, then.")

YesNoELSE(INGREDIENT)
Conversation
INTL( 4485, "Could you please answer by a yes or a no?")
SetYesNo(INGREDIENT)

Command(INTL( 1381, "KNOWLEDGE"))
INTL( 4486, "Well, if you are interested, I can teach you how to cast certain \"spells\".")

Command3(INTL( 700, "SPELL"),INTL( 495, "LEARN"), INTL( 496, "TEACH"))
INTL( 7544, "I will teach you what I can.")
CreateSkillList
	AddTeachSkill (__SPELL_RESIST_FIRE, 19, 69617)
	AddTeachSkill (__SPELL_ICE_BALL, 20, 75825)
SendTeachSkillList

Command2(INTL( 1492, "DESERT"),INTL( 3865, "VULTURE'S DEN"))
INTL( 4514, "The desert is a desolated landscape where rare are those who can survive.")

Command(INTL( 3854, "RAVENWOOD"))
INTL( 4515, "Ravenwood is a dark forest where \"Bane\" \"Blackblood\"'s \"nightblades\" "
"are scattered. You may also encounter dangerous \"demon\" \"trees\" who "
"possess incredible magical powers.") 

Command(INTL( 746, "DRUID"))
INTL( 4516, "Yes, we are druids.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 4517, "Really? That is interesting indeed!")

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 4518, "Be careful! We cannot assure your protection out of our sanctuary.")
BREAK

Default
""
IF (rnd.roll( dice( 1, 2 ) ) == 1)
    Conversation
    INTL( 4519, "I am sorry but could you reformulate this for me.")
ELSE
    Conversation
    INTL( 4520, "I do not understand what you are saying.")
ENDIF

EndTalk
}
//////////////////////////////////////////////////////////////////////////////////////////
void CelestinaWaterbreeze::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_RESIST_FIRE, 19, 69617)
         TEACH_SKILL(__SPELL_ICE_BALL, 20, 75825)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE