#pragma hdrstop
#include "MordrickWarstone.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MordrickWarstone::MordrickWarstone()
{}

MordrickWarstone::~MordrickWarstone()
{}

extern NPCstructure::NPC Royal_Guard;

void MordrickWarstone::Create(){
        npc = Royal_Guard;
        SET_NPC_NAME( "[2971]Mordrick Warstone" );
        npc.InitialPos.X = 1427;//1425;//1440;
        npc.InitialPos.Y = 2389;//2387;//2381;
        npc.InitialPos.world = 0;
}

void MordrickWarstone::OnTalk( UNIT_FUNC_PROTOTYPE )
{
CONSTANT ENROLL = 1;

InitTalk

Begin
""
IF ((CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED) > CurrentRound) && (CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED) != 0))
 	IF ((CheckGlobalFlag(__GLOBAL_BANK_HAS_BEEN_ROBBED_BY)) == (CheckFlag(__FLAG_SHADEEN_PLAYER_B)))
      Conversation
		INTL( 5462, "AH HA! I have finally caught you, thief! You're going directly to JAIL! Guards! Seize him!")		
		;int nNumLightHealingPotions = CheckItem(__OBJ_LIGHT_HEALING_POTION);
		FOR(0, nNumLightHealingPotions)         // User loses all his potions of healing.
			TakeItem(__OBJ_LIGHT_HEALING_POTION)   
		ENDFOR
		;int nNumHealingPotions = CheckItem(__OBJ_HEALING_POTION);
		FOR(0, nNumHealingPotions) // User loses all his potions of life. 
			TakeItem(__OBJ_HEALING_POTION)
		ENDFOR
      TELEPORT( 209,2338,1 )                                 
      BREAK                        
	ELSE
		IF ( USER_GENDER == GENDER_MALE ) 
			Conversation
			INTL( 4942, "I apologize, my Lord, but the banker just got robbed and I am currently trying to catch the thief!")
			BREAK
		ELSE
			Conversation
			INTL( 4943, "I apologize, my Lady, but the banker just got robbed and I am currently trying to catch the thief!")
			BREAK
		ENDIF
	ENDIF
ELSE
	IF (CheckFlag(__FLAG_THIEF) == 1)
		RemFlag(__FLAG_THIEF)
	ENDIF
	IF (TFCTime::IsDay())
			Conversation
			INTL( 5463, "It seems as if we are having yet another fine day.")
	ELSE
			Conversation
			INTL( 5464, "I am somewhat tired at this time. I hope what you have to say is important.")       
	ENDIF
ENDIF

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5465, "I am known as Mordrick Warstone, Knight of Might and protector of "
"King \"Theodore\" XIIIth.")

Command4(INTL( 489, "WORK"),INTL( 5466, "KNIGHT"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 5467, "I am the Knight of Might. This title has been bestowed upon me by the "
"King himself. I have pledged on my honor that I will "
"defend King \"Theodore\" XIIIth no matter what. I also have the task of "
"choosing new young \"recruits\" to fill our ranks.")

Command2(INTL( 754, "THEODORE"),INTL( 1633, "XIII"))
INTL( 5470, "I despise him because he does not care about his people. Not as much as a "
"true king should. He does little other than sleep all day while people are "
"starving or attacked by vile creatures. Good men such as \"Derran\" \"Ironstrife\" "
"have to take the burden upon themselves of making difficult decisions.")

Command(INTL( 5471, "SWORD OF MIGHT"))
""
IF (CheckItem(__OBJ_SWORD_OF_MIGHT) > 1)
	Conversation
	FORMAT(INTL( 5472, "You are trying to fool me with some fake swords, %s?" 
    		"There can be only one Sword of Might!"),USER_NAME)		
ELSEIF (CheckItem(__OBJ_SWORD_OF_MIGHT) == 1)
 	GetItemHandle(__OBJ_SWORD_OF_MIGHT, Sword_Of_Might)
    IF (CheckUnitFlag(Sword_Of_Might, __ITEM_FLAG_SWORD_OF_MIGHT)  == (CheckFlag (__QUEST_SWORD_OF_MIGHT)))
		Conversation
		FORMAT(INTL( 5473, "You have retrieved my precious Sword of Might? No words of "
		"mine can express my gratitude. You show great promises, %s. "
		"If you haven't done so yet, perhaps you might want to enter "
		"our ranks as a \"recruit\"."), USER_NAME) 
		GiveFlag(__QUEST_ROYAL_KEY6,6)
		GiveItem(__OBJ_ROYAL_KEY_6)
		TakeItem(__OBJ_SWORD_OF_MIGHT)
		Conversation
		INTL( 5474, "{You} {receive} {the} {sixth} {Royal} {Key}.")
	ELSE
		TakeItem(__OBJ_SWORD_OF_MIGHT)
		Conversation
		FORMAT(INTL( 5475, "{As} {Mordrick} {touches} {the} {jeweled} {hilt} {of} {the} {Sword} "
		"{of} {Might} {you} {were} {carrying}, {it} {crumbles} {into} {dust!} "
		"This is no sword of mine! How could have you been fooled so easily, "
		"%s?"),USER_NAME) 
	ENDIF
ELSE
	Conversation
	INTL( 5476, "You have heard of the Sword of Might which is rightfully mine? In fact, only "
	"I can wield it. It is an odd sword indeed because it has a mind of its own. "
	"After a while, it always mysteriously disappears and I have to retrieve it in "
    "the depths of a \"cave\". I wonder why it always goes there. It only appears if I "
	"speak the magic words: \"Make\" \"Mine\" \"Thy\" \"Might\". Remember that carefully.")
ENDIF

Command(INTL( 881, "CAVE"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY6) >= 4)	// If PC knows to ask Mordrick about
   										// the sword and where it lies:
	Conversation																											  
	INTL( 5477, "There's an underground complex called the Caverns of Illusion. "
	"That is where sword often returns, for some mysterious reason.")
ELSE // The PC isn't far along in the quest:
	Conversation
	INTL( 5478, "There are many caverns and dungeons under our land. I'm not sure which one "
	"you're referring to.")
ENDIF

Command2(INTL( 4661, "DERRAN"),INTL( 4662, "IRONSTRIFE"))
INTL( 5479, "Derran Ironstrife is a great warrior and one of \"King\" \"Theodore\"'s pillars. "
"Without him, I am sure that the kingdom would already be overtaken by savages. ")

Command(INTL( 744, "ORC"))
INTL( 5480, "The orcs are a constant danger. They must be obliterated once and for all or "
"they will always attempt to cause use mischiefs.")

Command(INTL( 502, "TRAIN"))
INTL( 5481, "Do I look like a trainer to you? Go see Derran if you want some training.")

Command(INTL( 496, "TEACH"))
INTL( 5482, "Do I look like a teacher? Stop bothering me and see Derran if you want to be "
"taught new abilities.") 

Command(INTL( 5483, "RECRUIT"))
""
IF (CheckFlag(__FLAG_TITLE_MORDRICK) < 1) 
	Conversation
	INTL( 5484, "We are always recruiting well-trained soldiers into our ranks of elite warriors. "
	"I'll readily admit that the pay is rather slim but our soldiers are always well "
	"fed.  Do you wish to enroll yourself and pledge loyalty, even through death, to "
	"our Majesty?")
	SetYesNo(ENROLL)
ELSE
	Conversation
	INTL( 5485, "You have already enrolled yourself. Remember that you must \"report\" to me.") 
ENDIF

YES(ENROLL)
Conversation
INTL( 5486, "You understand that this won't be easy, eh? You'll have to prove yourself worthy "
"before I can accept you within our ranks. Remember to \"report\" to me whenever "
"you wish to receive an assignment.")
GiveFlag(__FLAG_TITLE_MORDRICK, 1)           
GiveFlag(__FLAG_COUNTER_SLAY_15, 0)                  // Reset the counter

NO(ENROLL)
Conversation
INTL( 5487, "I understand.")

YesNoELSE(ENROLL)
Conversation
INTL( 5488, "I will leave you time to think this out.")

Command(INTL( 601, "REPORT"))
""
IF (CheckFlag(__FLAG_TITLE_MORDRICK) == 1) 
	IF(CheckFlag(__QUEST_FLAG_MORDRICK_STATUS) == 0)
		Conversation
		INTL( 5489, "I need to know how good you can be in the heat of a battle. Therefore, you will have to "
		"slay at least 15 demon trees that plague the forest of Ravenwood. That shouldn't be "
		"too difficult for you.")
		GiveFlag(__QUEST_FLAG_MORDRICK_STATUS, 1)
	ELSEIF(CheckFlag(__QUEST_FLAG_MORDRICK_STATUS) == 1)
	// slay 15 demon trees
      IF(CheckFlag(__FLAG_COUNTER_SLAY_15) >= 15)
			Conversation
			INTL( 5490, "Congratulations! You've proven yourself to be a promising soldier. However, your testing "
			"is not over. Not yet. Your next assignment is of much more importance. Our scouts "
			"have reported strange activities in the orcish encampment. Surely they are planning "
			"to launch an attack against our fair castle. You must find their vicious leader, Ghundarg "
			"Rumblefoot, and find out what he is up to. Hurry up! They could already be on the move!")
			Conversation
          FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), (10000+(USER_LEVEL*250)))
			GiveXP(10000+(USER_LEVEL*250))
         RemFlag(__FLAG_COUNTER_SLAY_15)                // Remove the now useless Flag
			GiveFlag(__QUEST_FLAG_MORDRICK_STATUS, 2)
		ELSE			            
            Conversation
			FORMAT( INTL( 5491, "Your mission is not yet completed, recruit. You still haven't killed "
         "fifteen demon trees. Only %u more!"), 15 - CheckFlag(__FLAG_COUNTER_SLAY_15) )
		ENDIF
	// end
	ELSEIF(CheckFlag(__QUEST_FLAG_MORDRICK_STATUS) == 2)
	// slay Ghundarg & bring plans
		IF ((CheckFlag(__FLAG_KILLED_THE_ORC_LEADER) == 3) && (CheckItem(__OBJ_PLANS) >= 1))
			Conversation
			INTL( 5492, "You've bested Ghundarg Rumblefoot? Great! He had some sort of document on him? "
			"Hmmmm. This could be valuable information indeed as it might tell us what he is "
			"up to. However, it is written in orcish language. I cannot make  a single "
			"word out of this. Find somebody who can tell us what this gibberish means "
			"and come \"report\" to me with your findings.")
			Conversation
			FORMAT(INTL( 1844, "{You} {have} {been} {awarded} {%u} {experience} {points.}"), 30000+(USER_LEVEL*500))
			GiveXP(30000+USER_LEVEL*500)
			RemFlag(__FLAG_KILLED_THE_ORC_LEADER)				// Remove the now useless Flag 
			GiveFlag(__QUEST_FLAG_MORDRICK_STATUS, 3)
		ELSEIF (CheckFlag(__FLAG_KILLED_THE_ORC_LEADER) == 1)
			Conversation
			INTL( 5493, "You claim that you have bested Ghundarg Rumblefoot in fair combat yet have been too DUMB "
			"to find out what he is up to? Go back there at once and find out what he is planning!")
		ELSEIF (CheckItem(__OBJ_PLANS) >= 1)
			Conversation
			INTL( 5494, "You did not slay Ghundarg Rumblefoot yourself. Therefore, who can say "		
			"that the orcish plans you have found are valid ones? Surely not you. Do not lose "
			"time and get back to the orcish encampment at once.") 
			;int nNumPlans = CheckItem(__OBJ_PLANS); 
			FOR(0, nNumPlans )
				TakeItem(__OBJ_PLANS)
			ENDFOR
		ELSE
			Conversation
			INTL( 5495, "There is little time left, recruit. You must locate that filthy Ghundarg Rumblefoot "
			"and find out what he is up before it is too late.")
		ENDIF
	// end
	ELSEIF(CheckFlag(__QUEST_FLAG_MORDRICK_STATUS) == 3)
   // go to Morindin Arrowmist
      IF ((CheckFlag(__FLAG_MORINDIN_ORCISH) == 1) && (CheckItem(__OBJ_PLANS) >= 1))
			Conversation 
			INTL( 5496, "Great job, recruit! The news you bring is quite grim, my friend. "
			"However, I am quite confident in the might of our army. Knowing what are "
			"their tactics is a huge advantage to us. You've done well. Therefore, I accept "
			"you as an honorary soldier. Here, this brand new tower shield is yours.")
			;int nNumPlans = CheckItem(__OBJ_PLANS); 
			FOR(0, nNumPlans )
				TakeItem(__OBJ_PLANS)
			ENDFOR
			GiveItem(__OBJ_TOWER_SHIELD)
			GiveFlag(__FLAG_TITLE_MORDRICK, 2)
      ELSEIF (CheckFlag(__FLAG_MORINDIN_ORCISH) == 1)
			Conversation
			INTL( 5497, "You've lost the precious orcish document? Fortunately, I still have a copy. "
			"Here, bring this to Morindin and you are to report to me at once afterwards.")
			GiveItem(__OBJ_PLANS)
         RemFlag(__FLAG_MORINDIN_ORCISH)
		ELSEIF (CheckItem(__OBJ_PLANS) >= 1)
			Conversation
			INTL( 5498, "You have not found anybody who knows orcish language? Perhaps Morindin Arrowmist "
			"would know something about that...")
		ELSE
			Conversation
			INTL( 5499, "You've lost the precious orcish document? ARGH! Fortunately, I still have a copy. "
			"Here you go! Do not lose this one again. Scribes are not working for pennies.")
			GiveItem(__OBJ_PLANS)
		ENDIF
	// end
	ENDIF
ELSEIF (CheckFlag(__FLAG_TITLE_MORDRICK) == 2) 
	Conversation
	INTL( 5500, "I do not have anymore assignments for you right now, soldier. But do not despair, for you "
	"will get more opportunities to serve our Majesty.") 
ELSE
	Conversation
	INTL( 5501, "You do not have to report to me. You have even not enrolled yourself!")
ENDIF

Command3(INTL( 737, "LICH"),INTL( 738, "MAKRSH"),INTL( 739, "P'TANGH"))
INTL( 5502, "The Lich Makrsh P'Tangh is both strong in body and in magic. Weapons alone "
"will not overcome it that easily. Only a good mix of steel and magic will "
"be able to destroy him for good.") 

Command(INTL( 1794, "ROYAL KEY"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY6) >= 5) // If PC has been "cleared" by Celestina...
	Conversation
	INTL( 5503, "I see... ")
	IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) //...and is a Champion of Light...
		Conversation
		INTL( 5504, "You are a champion of Light, ")
		IF (USER_KARMA >= 0) // ...and is not unworthy even slightly...
			Conversation
			INTL( 5505, "you are of sufficient worth, ")
			IF (CheckItem(__OBJ_SWORD_OF_MIGHT) >= 1) // ...and has Sword of Might:
				Conversation
				INTL( 5506, "and you have my Sword of Might! Very well, you shall have your key!")
				GiveFlag(__QUEST_ROYAL_KEY6,6)
				GiveItem(__OBJ_ROYAL_KEY_6)
				TakeItem(__OBJ_SWORD_OF_MIGHT)
	//		GiveKarma(100)
				Conversation
				INTL( 5507, "{You} {receive} {the} {sixth} {Royal} {Key}. {You} {also} {feel} {your} {aura} "
				"{of} {goodness} {restored} {to} {what} {it} {was.}")
			ELSE //...but doesn't Have sword of Might:
				Conversation
				INTL( 5508, "but I would ask that you first bring me back my \"Sword\" \"of\" \"Might\".")
			ENDIF
		ELSE //...but is slightly unworthy:
			Conversation
			INTL( 5509, "but your worth troubles me. Do more good deeds, then ask me again.")
		ENDIF
	ELSE // ...but isn't a Champion of Light:
		Conversation
		INTL( 5510, "You must know, however, that I would only give this key to a Champion of "
		"Light. Come back when you have become one.")
	ENDIF
ELSE // PC hasn't been cleared by Celestina:
	Conversation
	INTL( 1864, "...")
ENDIF

Command(INTL( 1492, "DESERT"))
INTL( 5511, "What would be the need of going there? There's no water and nothing interesting "
"there. Furthermore, I heard stories of deadly scorpions roaming in that area.") 

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 698, " ASS "),INTL( 697, "ASSHOLE"))
INTL( 5512, "I could break all your bones just for saying that to me but I'll let it pass... "
"for now.") BREAK

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 5513, "Be on your way and stop bothering me. I have work to do.") BREAK

Default
INTL( 4675, "I don't have time for that nonsense.")

EndTalk
}
