//////////////////////////////////////////////////////////////////////
// LordSunrock.cpp: implementation of the LordSunrock class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "LordSunrock.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LordSunrock::LordSunrock()
{}

LordSunrock::~LordSunrock()
{}

extern NPCstructure::NPC Lord_SunRock;

//Nom: Lord Sunrock.
//Statistique: Lord Sunrock.
//Position: (1609, 1181)
//World: 0
//Description: Lord of Windhowl.
//Body: Lord.

//////////////////////////////////////////////////////////////////////////////////////////
void LordSunrock::Create( void )
//////////////////////////////////////////////////////////////////////////////////////////
// Creation of LordSunrock
//
{
	npc = Lord_SunRock;
	SET_NPC_NAME( "[3013]Lord Sunrock" );
	npc.InitialPos.X = 1609;
	npc.InitialPos.Y = 1181;
	npc.InitialPos.world = 0;    
}

//////////////////////////////////////////////////////////////////////////////////////////
void LordSunrock::OnTalk( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Talk module of LordSunrock
//
{
CONSTANT MERCHANT = 1;
CONSTANT DIAMOND = 2;

InitTalk

Begin
""            
IF (CheckFlag(__QUEST_USER_IS_A_TRAITOR) == 3)
	Conversation
	INTL( 7162, "Your actions prove that you've betrayed me. You are no longer welcome here.")
	BREAK
ELSEIF (CheckFlag(__QUEST_USER_IS_A_TRAITOR) == 1)
	Conversation
	INTL( 7169, "Well, where's my \"merchandise\"?")
ELSEIF (CheckFlag(__QUEST_BRIGAND_GOT_THE_REPORT) == 0)
	Conversation
	INTL( 2487, "I welcome you to \"WindHowl\", stranger!.")
ELSEIF (CheckFlag(__QUEST_BRIGAND_GOT_THE_REPORT) <= (USER_LEVEL-2) )
	Conversation
	INTL( 2488, "I do not understand all this! The merchandise transaction was perfectly "
	"planned and yet, the brigands somehow knew exactly the road my men took "
	"to get back from Lighthaven with the precious merchandise. ARGH! I'm "
	"beginning to think that you're \"connected\" with the incident...")
	RemFlag(__QUEST_BRIGAND_GOT_THE_REPORT) 
	GiveFlag(__QUEST_USER_IS_A_TRAITOR, 1)
ELSE
	Conversation
	INTL( 2489, "I welcome you to \"Windhowl\", stranger!.")
ENDIF

Command(INTL( 2490, "CONNECT"))
""
IF( CheckFlag( __QUEST_USER_IS_A_TRAITOR) != 0)
	Conversation
	INTL( 2491, "Whether or not you are guilty of treason, you will have to get my \"merchandise\" back "
	"at once!")
ELSE
	Conversation
	INTL( 2492, "I do not understand.")
ENDIF

Command(INTL( 2493, "MERCHANDISE"))
""
IF (CheckFlag(__QUEST_USER_IS_A_TRAITOR) == 1)
	Conversation
	INTL( 7170, "Well, where is my merchandise?")
ELSEIF( CheckFlag( __QUEST_USER_IS_A_TRAITOR) == 2 )
	IF( CheckItem(__OBJ_BOX_OF_JEWELS) >= 1 )
		Conversation
		INTL( 2494, "You were able to retrieve only this box of jewels from the brigands, "
		"but you say you defeated them? Great! It means you were not their accomplice "
		"after all. Take this chaos sword as a token of my gratitude.")
		GiveItem(__OBJ_CHAOS_SWORD)
		TakeItem(__OBJ_BOX_OF_JEWELS)
		;int nBox = CheckItem(__OBJ_BOX_OF_JEWELS); 
		FOR (0, nBox )
			TakeItem(__OBJ_BOX_OF_JEWELS)
		ENDFOR
		RemFlag (__QUEST_BRIGAND_GOT_THE_REPORT)
		RemFlag (__QUEST_USER_IS_A_TRAITOR)
	ELSE
		Conversation
		INTL( 2496, "I am still waiting for you to recover my merchandise from "
		"the brigands.")
	ENDIF
ELSE
	Conversation
	INTL( 2497, "Merchandise? What are you talking about? Do I look like a shopkeeper to you? "
	"I am the Lord of this town. ")
ENDIF

Command2(INTL( 1869, "TOWN"),INTL( 514, "WINDHOWL"))
INTL( 2502, "Windhowl is more like a city than a town. It has grown much in size "
"lately.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 2503, "I am Lord Sunrock. I rule over the city of Windhowl.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 2504, "I try to maintain order in the town. I have to make sure the \"guards\" "
"are doing their job well, and see the economy does not fall apart. "
"That is what is giving me the most trouble. There aren't any \"merchants\" "
"coming from Lighthaven except those under the protection of young adventurers "
"like yourself. \"Jarko\" the necromancer causes me many headaches, for his goblins "
"are everywhere in the forest.")

Command(INTL( 523, "ANNABELLE"))
INTL( 1158, "I do not know much about that woman.")

Command3(INTL( 509, "BALORK"),INTL( 510, "BRAND"),INTL( 511, "BALORK CURSE"))
INTL( 2670, "Balork's Brand? Huh?")

Command(INTL( 2505, "GUARD"))
INTL( 2506, "They're doing their work well enough, but there aren't enough of them to "
"make a strike at \"Righul's\" \"Mountain\".")

Command(INTL( 541, "JARKO"))
INTL( 2507, "Tell you what, you bring me Jarko's \"spellbook\" as a proof that you "
"defeated him and I'll reward you. Sounds nice, eh?!")

Command(INTL( 759, "SPELLBOOK"))
""
IF (CheckItem (__OBJ_JARKO_SPELLBOOK) > 0)
	TakeItem (__OBJ_JARKO_SPELLBOOK)
	Conversation
	INTL( 2508, "I thank you for bringing back Jarko's spellbook as a proof of your "
	"courageous act. I shall burn this atrocity at once, for it is probably "
	"cursed. For your good deed, I give you this small amount of gold and "
	"this magnificient golden ring!")
	GiveGold (800)
	GiveItem (__OBJ_GOLDEN_RING)
ELSE
	Conversation
	INTL( 2509, "Bring me back Jarko's spellbook and you shall be rewarded.")
ENDIF

Command(INTL( 1458, "RIGHUL"))
INTL( 2510, "If you're strong enough to survive hours in the cave north of Windhowl, "
"then you would be able to take a look at what is happening at the mountain.")

Command(INTL( 2511, "DIAMOND"))
INTL( 2512, "I tend to lose my diamonds around, I guess I'm plain careless, these days. "
"If you happen to find one, please return it to me at once! Hmmm... By the "
"way, did you find one of my diamonds, by any chance?")
SetYesNo( DIAMOND )

YES (DIAMOND) 
IF (CheckItem (__OBJ_DIAMOND) >= 1)
	TakeItem(__OBJ_DIAMOND) 
	GiveGold(400)
	Conversation
	INTL( 2513, "Thank you so much! You have earned a small reward. Here... I give "
	"you 400 gold pieces!")
ELSE
	Conversation
	INTL( 2514, "Liar! You do not have one of my precious diamonds!")
ENDIF

NO (DIAMOND)
Conversation
INTL( 2515, "*sigh*")

YesNoELSE (DIAMOND)
Conversation
INTL( 7291, "Well, have you found one of my diamonds?")
SetYesNo(DIAMOND) 

Command(INTL( 513, "LIGHTHAVEN"))
INTL( 2516, "Lighthaven is our sister town on the eastern part of this island.")

Command(INTL( 2345, "ROLPH"))
INTL( 2517, "The armorer of \"Lighthaven\" is supposed to send me a \"report\" soon.")

Command(INTL( 2518, "SIGFRIED"))
INTL( 2519, "Sigfried is a great weaponsmith who lives in \"Lighthaven\". I wonder if "
"he has sent a messenger for his \"report\" yet...")

Command2(INTL( 1257, "MERCHANT"),INTL( 601, "REPORT"))
""
IF (CheckItem(__OBJ_SIGFRIED_REPORT) >= 1 )
	GetItemHandle(__OBJ_SIGFRIED_REPORT, SigfriedReport)
	IF (CheckUnitFlag (SigfriedReport, __ITEM_QUEST_SIGFRIED_REPORT) == (CheckGlobalFlag (__GLOBAL_QUEST_SIGFRIED_REPORT)))
		TakeItem(__OBJ_SIGFRIED_REPORT)
		IF (CheckFlag(__QUEST_SIGFRIED_DONE) == 1)
			Conversation
			INTL( 2520, "I have previously given you a reward for bringing me the report I "
			"needed. I therefore do not think you need any more gold pieces. I "
			"see in your eyes the thirst for adventures, which is probably why "
			"you accepted to do this errand once more. I thank you very much.")
		ELSE
			GiveXP(6000)
			GiveFlag(__QUEST_SIGFRIED_DONE, 1)
			Conversation
			INTL( 2521, "Well, well! I appreciate what you did for our fair town. This "
			"important report will help us to sign treaties with Lighthaven. "
			"{You} {have} {been} {awarded} {6000} {experience} {points.}")
		ENDIF
	ELSE
		TakeItem(__OBJ_SIGFRIED_REPORT)
		Conversation
		INTL( 2522, "This report from Sigfried is outdated and thus useless to me! Sorry, "
		"but you will not be paid for such poor delivery. Next time, try to "
		"be in time, for a change!")
	ENDIF
ELSEIF (CheckItem(__OBJ_ROLPH_REPORT) >= 1 )
	GetItemHandle(__OBJ_ROLPH_REPORT, RolphReport)
	IF (CheckUnitFlag (RolphReport, __ITEM_QUEST_ROLPH_REPORT) == (CheckGlobalFlag (__GLOBAL_QUEST_ROLPH_REPORT)))
		TakeItem(__OBJ_ROLPH_REPORT)
		IF (CheckFlag(__QUEST_ROLPH_DONE) == 1)
			Conversation
			INTL( 2523, "You have brought me another report from Rolph? I thank you very much, "
			"your work is highly appreciated by both Windhowl and Lighthaven. I do not need to reward an "
			"experienced adventurer such as you for such a small task, do I?")
		ELSE
			GiveGold(750)
			GiveFlag(__QUEST_ROLPH_DONE, 1)
			Conversation
			INTL( 2524, "I reward you with 750 gold pieces for this report. I appreciate what you did "
			"for our fair town. This will help for signing treaties with Lighthaven.")
		ENDIF
	ELSE
		TakeItem(__OBJ_ROLPH_REPORT)
		Conversation
		INTL( 2525, "This report from Rolph is outdated and thus useless to me! Sorry "
		"but you will not be paid for such poor delivery. Next time, try to "
		"be in time, for a change!")
	ENDIF
ELSE
	Conversation
	INTL( 2526, "I doubt it concerns you.")
ENDIF

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 2527, "I'll return to my work now.") BREAK

Command(INTL( 2528, "FROM ASARR"))
""
IF ( CheckItem ( __OBJ_LETTER_TO_SUNROCK ) > 0 )
	;int nLetter = CheckItem(__OBJ_LETTER_TO_SUNROCK); 
	FOR ( 0, nLetter )
		TakeItem( __OBJ_LETTER_TO_SUNROCK ) 
	ENDFOR
	Conversation
	INTL( 2529, "Hm? What, a letter from Asarr? He wishes to surrender, perhaps? Let me see this. "
	"Mm. M-hm. Uh huh... Eh? What?!? Who does he *think* he is! That devil shall pay "
	"for these words! What insolence!"
	"You! Come here! Tell that ruffian he's not going to call me a blue-nosed babboon "
	"without suffering the consequences. Tell him he will feel the heat of my \"wrath\" "
	"and pay for his insufferable disrespect!")
	IF (CheckFlag(__TAUNTED_SUNROCK)==0 AND (USER_KARMA>(-100*(CheckFlag(__QUEST_ISLAND_ACCESS)+1))))
		GiveKarma(-10*(500+USER_KARMA)/500)
	ENDIF
	GiveFlag ( __TAUNTED_SUNROCK , 1 )
ELSE
	INTL( 2530, "Yes? What about Asarr?")
ENDIF

Command (INTL( 2531, "WRATH"))
""
IF ( CheckFlag ( __TAUNTED_SUNROCK ) > 0 )
	Conversation
	INTL( 2532, "Tell him. Tell him my anger will pursue him 'till the end of time!")
ELSE
	Conversation
	INTL( 2533, "Er... Yes, of course.")
ENDIF

Default
INTL( 2534, "I cannot say.")

EndTalk

}
