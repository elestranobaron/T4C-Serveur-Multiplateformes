
#pragma hdrstop
#include "MithannaSnowraven.h"

MithannaSnowraven::MithannaSnowraven()
{}

MithannaSnowraven::~MithannaSnowraven()
{}

extern NPCstructure::NPC MithannaSnowravenNPC;

void MithannaSnowraven::Create( ){
	npc = MithannaSnowravenNPC;
   SET_NPC_NAME( "[10877]Mithanna Snowraven" );
	npc.InitialPos.X = 120;
	npc.InitialPos.Y = 795;
	npc.InitialPos.world = 0;
}

void MithannaSnowraven::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT ERRAND = 1; 
CONSTANT HEART = 2; 

InitTalk		   
 

Begin
"" 
IF (TFCTime::IsSleepTime())
	Conversation
	INTL( 9580, "Please, it is getting late. Even a sorceress requires sleep.") BREAK
ELSE
	Conversation
	INTL( 9581, "I have been expecting you.")
ENDIF

Command2(INTL( 9582, "MITHANNA"),INTL( 9583, "SNOWRAVEN"))
INTL( 9584, "Just call me Mithanna.")
	
Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 9585, "I am Mithanna Snowraven, white sorceress of Stonecrest.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 9586, "Fear not, I am not a sorceress of evil. I study the art of spellcraft "
"and can perhaps \"help\" you if you need assistance.")

// __QUEST_FLAG_ARTHERK_HEART
// 0: User doesn't have it. 
// 1: User has it. 

Command(INTL( 7710, "LIGHTBRINGER"))
""
IF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 1)
	Conversation
	FORMAT(INTL( 9587, "I see that you are now a Lightbringer, %s. Let's hope that you're ready for what lies ahead."),USER_NAME) 
ELSEIF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1) 
	Conversation
	FORMAT(INTL( 9588, "I'm afraid it is too late to redeem yourself, %s."), USER_NAME) 
ELSE
	Conversation
	INTL( 9589, "A paladin may grant you such title if deemed worthy enough.")
ENDIF

Command(INTL( 5628, "ORACLE"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) >= 1)
	Conversation
	INTL( 9590, "You know of him? That's good. Yes, he's for real, he's very powerful and he's "
	"the next step toward your great destiny... to kill Makrsh P'Tangh.")
ELSE
	Conversation
	INTL( 9591, "I wouldn't tell you about him even if you asked for a hundred years.")
ENDIF

Command(INTL( 9592, "HEART OF ARTHERK"))
""
IF (CheckFlag(__QUEST_FLAG_ARTHERK_HEART) == 1) 
	Conversation
	INTL( 11527, "You already have this piece of the key. It would do you no good to have an additional one.")
ELSE 
	IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1) 
		Conversation
		INTL( 9594, "I am sorry but I cannot help you for you have chosen the path of darkness. Even "
		"the Heart of Artherk cannot help you redeem your corrupted soul.")
	ELSEIF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 0)
		Conversation
		INTL( 9595, "Only a \"Lightbringer\" can even think of touching the Heart of Artherk.")
	ELSE
		Conversation						   
		INTL( 9596, "The Heart of Artherk represents the courage and strength required to "
		"change the world for the better. In order to summon the Heart of Artherk "
		"into our presence, I would require two \"gems\" \"of\" \"courage\", four \"Tomes\" \"of\" "
		"\"Valor\" and three \"swords\" \"of\" \"majesty\".") 
		IF ((CheckItem(__OBJ_GEM_OF_COURAGE) >= 2) && (CheckItem(__OBJ_TOME_OF_VALOR) >= 4)  && (CheckItem(__OBJ_SWORD_OF_MAJESTY) >= 3))
			Conversation
			INTL( 9597, " I see that you have already gathered all the required components for us "
			"to summon the Heart of Artherk. Shall we proceed?")
			SetYesNo(HEART) 
		ENDIF 
	ENDIF 
ENDIF 

YES(HEART) 
	IF ((CheckItem(__OBJ_GEM_OF_COURAGE) >= 2) && (CheckItem(__OBJ_TOME_OF_VALOR) >= 4)  && (CheckItem(__OBJ_SWORD_OF_MAJESTY) >= 3))
		Conversation
		INTL( 9598, "Then, I shall initiate the summoning at once... Ah, the process has been completed. You are now the bearer of the Heart of Artherk! "
		"You must protect it with your very life.")	 	
		PRIVATE_SYSTEM_MESSAGE(INTL( 9599, "Mithanna gathers the components together and whispers words of magic.")) 
		PRIVATE_SYSTEM_MESSAGE(INTL( 9600, "A bluish flame instantly consumes them!")) 		
		PRIVATE_SYSTEM_MESSAGE(INTL( 9601, "You receive the Heart of Artherk!")) 
		;int nExpReward = 250000; 	
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
		GiveXP(nExpReward)
		FOR(0,2) 
			TakeItem(__OBJ_GEM_OF_COURAGE) 
		ENDFOR	
		FOR(0,4) 
			TakeItem(__OBJ_TOME_OF_VALOR) 
		ENDFOR
		FOR(0,3) 
			TakeItem(__OBJ_SWORD_OF_MAJESTY)
		ENDFOR
		GiveItem(__OBJ_HEART_OF_ARTHERK) 
		GiveFlag(__QUEST_FLAG_ARTHERK_HEART, 1) 
	ELSE
		Conversation
		INTL( 9602, "Hmmm. It seems that you did not have all the required components afterall. Gather "
		"what is needed and return here.")
	ENDIF 

NO(HEART)
	Conversation
	INTL( 7724, "Come back if you change your mind.")

YesNoELSE(HEART) 
	Conversation
	INTL( 9603, "Shall we summon the Heart of Artherk?")
	SetYesNo(HEART) 

CmdAND(INTL( 10774, "TOME"),INTL( 10775, "VALOR"))
INTL( 10776, "I do not recall the name of the mage who is skilled in writing this tome. The only thing I can "
"tell you is that he is usually busy working on one of his portals.") 

CmdAND(INTL( 4880, "SWORD"),INTL( 3990, "MAJESTY"))
INTL( 10777, "The sword of majesty must absolutely be forged by a very skilled blacksmith. I think only "
"a skillful centaur blacksmith can accomplish such a task, with the possible exception of \"Lance\" "
"\"Silversmith\".") 

CmdAND(INTL( 11320, "LANCE"),INTL( 10018, "SILVERSMITH")) 
INTL( 11321, "I think he lives somewhere on the island of Arakas.")
																										
CmdAND(INTL( 4639, "GEM"),INTL( 10778, "COURAGE")) 
INTL( 10779, "I think Omar Hald, the town's jeweller, might be up for this task.")
 
Command(INTL( 8092, "WHITE CROW"))
INTL( 9604, "Why, yes, that is also how some centaurs call me.")

/* NOTICE: DARAN'S QUEST HAS BEEN DISABLED ON October 31th 2000. 
CmdAND(INTL( 554, "HELP"),INTL( 8284, "DARAN"))
""
IF(CheckGlobalFlag(__QUEST_DARAN_CERTIFICATE) == CheckFlag(__QUEST_DARAN_CERTIFICATE)) // The quest is already in progress:
	SWITCH(CheckGlobalFlag(__QUEST_DARAN_ROMANCE))
		CASE(6)
			Conversation
			INTL( 9605, "I see... Well, it *is* possible to make a Scroll of Appearance Restoration, "
			"but I'll need a few \"ingredients\": ")
			Conversation
			INTL( 9606, "FIVE Flasks of Liquid Spider Silk, THREE Magic Mirrors and a DOZEN Scrolls "
			"of Enchantment. I know it's a lot, but you're asking for a rather difficult "
			"spell.")
			GiveGlobalFlag(__QUEST_DARAN_ROMANCE, 7)
		ENDCASE
		CASE(7)
			Conversation
			INTL( 9607, "The \"ingredients\" I need to make the Scroll of Appearance Restoration are: ")
			Conversation
			INTL( 9608, "FIVE Flasks of Liquid Spider Silk, THREE Magic Mirrors and a DOZEN Scrolls "
			"of Enchantment. I know it's a lot, but you're asking for a rather difficult "
			"spell.")
		ENDCASE
		CASE(8)
			Conversation
			INTL( 9609, "Oh! Did I mention that the scroll may cause amnesia? It happens, sometimes.")
		ENDCASE
		OTHERWISE
			Conversation
			INTL( 9610, "Perhaps you should come back at some other time, I'm not sure what you're talking about.")
	ENDSWITCH
ELSEIF(CheckFlag(__QUEST_DARAN_CERTIFICATE) != 0)
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
	PRIVATE_SYSTEM_MESSAGE(INTL( 8330, "A server crash or shutdown has occurred and you must restart this quest."))
ELSE
	Conversation
	INTL( 9611, "I believe someone else is handling this already.")
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
ENDIF

CmdAND3(INTL( 1159, "SCROLL"),INTL( 9252, "APPEARANCE"),INTL( 9612, "RESTORATION"))
""
IF(CheckGlobalFlag(__QUEST_DARAN_CERTIFICATE) == CheckFlag(__QUEST_DARAN_CERTIFICATE)) // The quest is already in progress:
	SWITCH(CheckGlobalFlag(__QUEST_DARAN_ROMANCE))
		CASE(6)
			Conversation
			INTL( 9613, "I see... Well, it *is* possible to make a Scroll of Appearance Restoration, "
			"but I'll need a few \"ingredients\": ")
			Conversation
			INTL( 9614, "FIVE Flasks of Liquid Spider Silk, THREE Magic Mirrors and a DOZEN Scrolls "
			"of Enchantment. I know it's a lot, but you're asking for a rather difficult "
			"spell.")
			GiveGlobalFlag(__QUEST_DARAN_ROMANCE, 7)
		ENDCASE
		CASE(7)
			Conversation
			INTL( 9615, "The \"ingredients\" I need to make the Scroll of Appearance Restoration are: ")
			Conversation
			INTL( 9616, "FIVE Flasks of Liquid Spider Silk, THREE Magic Mirrors and a DOZEN Scrolls "
			"of Enchantment. I know it's a lot, but you're asking for a rather difficult "
			"spell.")
		ENDCASE
		CASE(8)
			Conversation
			INTL( 9609, "Oh! Did I mention that the scroll may cause amnesia? It happens, sometimes.")
		ENDCASE
		OTHERWISE
			Conversation
			INTL( 9610, "Perhaps you should come back at some other time, I'm not sure what you're talking about.")
	ENDSWITCH
ELSEIF(CheckFlag(__QUEST_DARAN_CERTIFICATE) != 0)
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
	PRIVATE_SYSTEM_MESSAGE(INTL( 8330, "A server crash or shutdown has occurred and you must restart this quest."))
ELSE
	Conversation
	INTL( 9611, "I believe someone else is handling this already.")
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
ENDIF

CmdAND4(INTL( 4457, "FLASK"),INTL( 9617, "LIQUID"),INTL( 8903, "SPIDER"),INTL( 9618, "SILK"))
INTL( 9619, "This is rather hard to find. This is the liquid that spiders use to weave their webs, "
"but it tends to solidify when it's exposed to air, so it's very rare that you can get "
"some off their dead bodies.")

CmdAND(INTL( 1096, "MAGIC"),INTL( 9620, "MIRROR"))
INTL( 9621, "I hear Resha Marsack has some in a locked chest at her home. Maybe that's the secret "
"of her incredible good looks...")

CmdAND(INTL( 1159, "SCROLL"),INTL( 9622, "ENCHANTMENT"))
INTL( 9623, "They're hard to find, and literally no one here does them. You might have more luck if you "
"tried the Kingdom of Goldmoon.")

Command(INTL( 2076, "INGREDIENT"))
""
IF(CheckGlobalFlag(__QUEST_DARAN_CERTIFICATE) == CheckFlag(__QUEST_DARAN_CERTIFICATE)) // The quest is already in progress:
	SWITCH(CheckGlobalFlag(__QUEST_DARAN_ROMANCE))
		CASE(6)
			Conversation
			INTL( 9624, "Ingredients for *what*?")
		CASE(7)
			IF(CheckItem(__OBJ_FLASK_OF_LIQUID_SPIDER_SILK) >= 5 && CheckItem(__OBJ_MAGIC_MIRROR) >= 3 && CheckItem(__OBJ_SCROLL_OF_ENCHANTMENT) >= 12)
				Conversation
				INTL( 9625, "I'm impressed, you managed to find everything, and quickly too! Here's your "
				"scroll.")
				FOR(0,5) 
					TakeItem(__OBJ_FLASK_OF_LIQUID_SPIDER_SILK)
				ENDFOR
				FOR(0,3)
					TakeItem(__OBJ_MAGIC_MIRROR)
				ENDFOR
				FOR(0,12)
					TakeItem(__OBJ_SCROLL_OF_ENCHANTMENT)
				ENDFOR
				GiveItem(__OBJ_SCROLL_OF_APPEARANCE_RESTORATION)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9626, "Mithanna gives you the Scroll of Appearance Restoration."))
				GiveGlobalFlag(__QUEST_DARAN_ROMANCE, 8)
			ELSE
				Conversation
				INTL( 9627, "The \"ingredients\" I need to make the Scroll of Appearance Restoration are: ")
				Conversation
				INTL( 9628, "FIVE Flasks of Liquid Spider Silk, THREE Magic Mirrors and a DOZEN Scrolls "
				"of Enchantment. I know it's a lot, but you're asking for a rather difficult "
				"spell.")
			ENDIF
		ENDCASE
		CASE(8)
			Conversation
			INTL( 9629, "Take the scroll to Daran, now, I'm sure he's looking forward to using it. ")
			Conversation
			INTL( 9609, "Oh! Did I mention that the scroll may cause amnesia? It happens, sometimes.")
		ENDCASE
		OTHERWISE
			Conversation
			INTL( 9610, "Perhaps you should come back at some other time, I'm not sure what you're talking about.")
	ENDSWITCH
ELSEIF(CheckFlag(__QUEST_DARAN_CERTIFICATE) != 0)
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
	PRIVATE_SYSTEM_MESSAGE(INTL( 8330, "A server crash or shutdown has occurred and you must restart this quest."))
ELSE
	Conversation
	INTL( 8334, "Someone else's already on the job, thanks.")
	RemFlag(__QUEST_DARAN_CERTIFICATE) //Defensive code.
ENDIF
*/

CmdAND3(INTL( 8927, "FANG"),INTL( 9630, "TRUE"),INTL( 6869, "RESOLVE"))
""
IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) >= 4) 
	Conversation	
	INTL( 9631, "Fangs of True Resolve are made by Stonecrest's cleric, Nissus Haloseeker. Request his help and he will "
	"undoubtedly assist you.")
ELSEIF ((CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 2) || (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 3)) 
	Conversation
	INTL( 9632, "You have been sent on an errand to gather Fangs of True Resolve? Under normal circumstances, I would probably "
	"be able to aid you in your quest but I am very busy. I am currently trying to fine tune an extremely difficult "
	"arcane spell that I am studying. After consideration, perhaps we could make a little deal. If you could "
	"somehow gather a \"jade\" \"ring\" \"of\" \"sorcery\" and six pairs of \"tarantula\" \"eyes\", I would help you in return as a token "
	"of my gratitude.")
	GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 3)  
	IF ((CheckItem(__OBJ_JADE_RING_OF_SORCERY) >= 1) && (CheckItem(__OBJ_TARANTULA_EYES) >= 6))
		Conversation																	 
		INTL( 9633, " I sense that you already have the precious components I require. Do you think you could give them to me?")
		SetYesNo(ERRAND) 
	ENDIF
ELSE
	Conversation
	INTL( 9634, "I don't to see why you'd be interested in Fangs of True Resolve.")
ENDIF

YES(ERRAND) 
	IF ((CheckItem(__OBJ_JADE_RING_OF_SORCERY) >= 1) && (CheckItem(__OBJ_TARANTULA_EYES) >= 6))
		Conversation
		INTL( 9635, "Thank you! Thus, I shall keep my part of the deal and shall reveal to you the information you need to know. "
		"The Fangs of True Resolve are made by Stonecrest's cleric, Nissus Haloseeker. Request his help and he will "
		"undoubtedly assist you if you mention that you've been sent by me.")
		;int nExpReward = 75000; 	
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"),nExpReward)) 
		GiveXP(nExpReward)
		IF (CheckFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST) == 3)
			GiveFlag(__QUEST_FLAG_WILL_OF_ARTHERK_QUEST, 4) 
		ENDIF
		TakeItem(__OBJ_JADE_RING_OF_SORCERY) 
		FOR(0, 6) 
			TakeItem(__OBJ_TARANTULA_EYES)
		ENDFOR		
	ELSE
		Conversation
		INTL( 9636, "You are missing some components I require. I need a \"jade\" \"ring\" \"of\" \"sorcery\" to enhance the strength of my spells and "
		"six pairs of \"tarantula\" \"eyes\". Come back when you have everything.")
	ENDIF

NO(ERRAND)
	Conversation
	INTL( 9637, "Then, if you could be a dear and close the door on your way out, I'd appreciate.") BREAK 

YesNoELSE(ERRAND) 
	Conversation
	INTL( 9638, "I don't have much time. Come back when you make your mind.")

Command(INTL( 9639, "JADE RING OF SORCERY"))
INTL( 9640, "The jade ring of sorcery can enhance the strength of its wearer's spells.")
 
Command(INTL( 9641, "TARANTULA EYES"))
INTL( 9642, "I am sure that a seasoned adventurer such as yourself will have no problem in finding tarantula eyes.")

Command(INTL( 9643, "ARCANE ANALYSIS"))
INTL( 9644, "That is not something you should be concerned about. It has to do with legendary beings of ages past.")

Command(INTL( 554, "HELP"))
INTL( 9645, "I can help you by \"teaching\" you a spell or two")

Command2(INTL( 495, "LEARN"), INTL( 496, "TEACH"))
INTL( 9646, "These are the few spells that I can teach you. Use them wisely.")
CreateSkillList
	AddTeachSkill (__SPELL_ICE_STORM, 26, 152425)
	AddTeachSkill (__SPELL_BLIZZARD, 29, 195508)
SendTeachSkillList

Command(INTL( 9647, "ICE STORM"))
INTL( 9648, "The ice storm spell will freeze everything within the area of effect, inflicting great amounts of damage to all living "
"creatures affected. You are required to have the glacier spell before you can learn it.")

Command(INTL( 9649, "BLIZZARD"))
INTL( 9650, "The blizzard spell will freeze everything within the area of effect, inflicting tremendous amounts of damage to all living "
"creatures affected. You are required to have the ice storm spell before you can learn it.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 9651, "You should leave right away before I do something we'd both regret.")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 1075, "Farewell.")
BREAK

Default
""
IF (rnd.roll(dice(1,2)) == 1 ) 
	Conversation
	INTL( 5396, "I honestly don't know.")
ELSE
	Conversation
	INTL( 6431, "That is not my concern at the moment.")
ENDIF


EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void MithannaSnowraven::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_ICE_STORM, 26, 152425)
         TEACH_SKILL(__SPELL_BLIZZARD, 29, 195508)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE