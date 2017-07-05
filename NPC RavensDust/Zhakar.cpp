#pragma hdrstop
#include "Zhakar.H"

Zhakar::Zhakar()
{}

Zhakar::~Zhakar()
{}

extern NPCstructure::NPC ZhakarNPC;

void Zhakar::Create( void )
{
        npc = ( ZhakarNPC );
        SET_NPC_NAME( "[2993]Zhakar" );
        npc.InitialPos.X = 0;
        npc.InitialPos.Y = 0;
        npc.InitialPos.world = 0;
}
  
void Zhakar::OnInitialise( UNIT_FUNC_PROTOTYPE ){

	CastSpellSelf(__SPELL_MOB_AI_REGENERATION_SPELL);

	NPCstructure::OnInitialise( UNIT_FUNC_PARAM );
}



void Zhakar::OnAttacked( UNIT_FUNC_PROTOTYPE )
{ 

	SWITCH( rnd.roll(dice(1,10))) 
		CASE(1) 
			SHOUT(INTL( 10496, "You can hurt me no more. Another \"experiment\" conducted SUCCESSFULLY!")) 	
		ENDCASE
		CASE(2) 
			SHOUT(INTL( 10497, "Ha ha ha! I am \"invincible\"!!!")) 
		ENDCASE
		OTHERWISE
	ENDSWITCH
	
//	IF(NPC_HP<181)
//		SHOUT(INTL( 7686, "With my last dying breath, I shall kill you!"));		
//		CastSpellSelf(__SPELL_MOB_AI_SPELL_BLAZE_OF_GLORY);
//	ENDIF

/*	ELSEIF(NPC_HP<3006)

		switch(rnd(1, 10))
		{
			case 1: CastSpellSelf(__SPELL_MOB_AI_SPELL_SELF_HEALING_20_PERCENT); break;
			default: break;
		}
	ELSE
		switch(rnd(1,20))
		{
			case 1: CastSpellSelf(__SPELL_MOB_AI_SPELL_SELF_HEALING_10_PERCENT);
			CastSpellSelf(__SPELL_MOB_AI_REGENERATION_SPELL); break;
			default: break;
		}
*/

NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Zhakar::OnTalk( UNIT_FUNC_PROTOTYPE )
{
CONSTANT EGG = 1;
CONSTANT GET_MORE_KEY = 2;
CONSTANT THESWORD = 3;
CONSTANT THEMACE  = 4;
CONSTANT THESTAFF = 5;
CONSTANT THEPOUCH = 6;
CONSTANT RITUAL = 7;
CONSTANT TELEPORT = 8;
CONSTANT SPELLBOOK = 9;
CONSTANT TPORT = 10;

InitTalk

Begin
""                                                            

// This code is necessary for characters who did the good quest on Raven's Dust prior to 
// version 1.20 

IF ((CheckFlag(__QUEST_CUTHANA) == 4) && (CheckFlag(__FLAG_GOOD_QUEST_COMPLETED_ON_RD) == 0))
	GiveFlag(__QUEST_ISLAND_ACCESS, 1)	
	GiveFlag(__FLAG_GOOD_QUEST_COMPLETED_ON_RD, 1) 
	GiveFlag(__USER_CANNOT_GET_A_SILVER_FEATHER, 1) 
	;int nNumKeys = CheckItem(__OBJ_ROYAL_KEY_1);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_1 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_2);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_2 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_3);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_3 )  
	ENDFOR
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_4);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_4 )  
	ENDFOR
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_5);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_5 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_6);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_6 )  
	ENDFOR 

ENDIF				   
				
// If the user has island access == 2 but hasn't completed either the good or the evil quest, 
// the island access is decremented back to 1 and the user is given the good quest completed flag. 
																																																	 
IF((CheckFlag(__QUEST_ISLAND_ACCESS) == 2) && (CheckFlag(__FLAG_GOOD_QUEST_COMPLETED_ON_RD) == 0) && (CheckFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD) == 0)) 
	GiveFlag(__QUEST_ISLAND_ACCESS, 1)	
	GiveFlag(__FLAG_GOOD_QUEST_COMPLETED_ON_RD, 1) 
	GiveFlag(__USER_CANNOT_GET_A_SILVER_FEATHER, 1)
	;int nNumKeys = CheckItem(__OBJ_ROYAL_KEY_1);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_1 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_2);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_2 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_3);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_3 )  
	ENDFOR
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_4);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_4 )  
	ENDFOR
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_5);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_5 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_6);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_6 )  
	ENDFOR 
ENDIF

//	Ok. -sigh- This will support players that have completed the good quest, got the 
// curse removal service from Princess Delilah and restarted the quest. 
//
IF ( (CheckFlag(__BALORK_BRAND) == 0) && (CheckFlag(__BALORK_KILLED) == 1) && (CheckFlag(__QUEST_CUTHANA) >= 1)  && (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 1) && (CheckFlag(__FLAG_GOOD_QUEST_COMPLETED_ON_RD) == 0) && (CheckFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD) == 0))
	GiveFlag(__FLAG_GOOD_QUEST_COMPLETED_ON_RD, 1)
	GiveFlag(__USER_CANNOT_GET_A_SILVER_FEATHER, 1)
    ;int nNumKeys = CheckItem(__OBJ_ROYAL_KEY_1);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_1 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_2);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_2 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_3);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_3 )  
	ENDFOR
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_4);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_4 )  
	ENDFOR
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_5);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_5 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_6);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_6 )  
	ENDFOR 
ENDIF 

// This modification is here to support characters who did the evil quest on Raven's Dust prior 
// to version 1.20 

IF (CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 4) 
	GiveFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD, 1) 
ENDIF 

// Ok, this one removes all the tightly scrolls if the user no longer need 'em... 

IF (CheckFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD) == 1)
	IF (CheckItem(__OBJ_LETTER_FROM_DAMIEN_TO_XANTH) >= 1) 
		;int iNumLetters = CheckItem(__OBJ_LETTER_FROM_DAMIEN_TO_XANTH);
		FOR( 0, iNumLetters) 
			TakeItem(__OBJ_LETTER_FROM_DAMIEN_TO_XANTH) 
		ENDFOR
	ENDIF
ENDIF 

// This removes all the keys from players who have access to Stoneheim. :) 

IF((CheckFlag(__QUEST_ISLAND_ACCESS) == 2) && ((CheckFlag(__FLAG_GOOD_QUEST_COMPLETED_ON_RD) == 1) || (CheckFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD) == 1))) 
	;int nNumKeys = CheckItem(__OBJ_ROYAL_KEY_1);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_1 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_2);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_2 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_3);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_3 )  
	ENDFOR
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_4);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_4 )  
	ENDFOR
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_5);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_5 )  
	ENDFOR 
	;nNumKeys = CheckItem(__OBJ_ROYAL_KEY_6);
	FOR(0, nNumKeys) 
		TakeItem( __OBJ_ROYAL_KEY_6 )  
	ENDFOR 
ENDIF

// This modification is here to support evil characters before the fix for the negative flag 
// has been applied in the server. 

IF((CheckFlag(__QUEST_DAMIEN_SUBPLOT)>= 4) && (CheckFlag(__QUEST_FIXED_ALIGNMENT) == 0))
		GiveFlag(__QUEST_FIXED_ALIGNMENT, -1)
ENDIF

IF(CheckFlag(__FLAG_USER_IS_WAITING_FOR_ARCANE_SPELLBOOK) != 0)
	IF(CurrentRound < CheckFlag(__FLAG_ZHAKAR_IS_BUSY_MAKING_SPELLBOOK))
		IF(CurrentRound >= 18000)
			IF(rnd.roll(dice(1, 20)) <= CheckFlag(__FLAG_USER_IS_WAITING_FOR_ARCANE_SPELLBOOK))
				GiveItem(__OBJ_ARCANE_SPELLBOOK)
				GiveFlag(__FLAG_USER_HAS_ARCANE_SPELLBOOK, CheckFlag(__FLAG_USER_HAS_ARCANE_SPELLBOOK) + 1)
				RemFlag(__FLAG_USER_IS_WAITING_FOR_ARCANE_SPELLBOOK)
				RemFlag(__FLAG_ZHAKAR_IS_BUSY_MAKING_SPELLBOOK)
				Conversation
				INTL( 7924, "Here you are, as promised.")
				PRIVATE_SYSTEM_MESSAGE(INTL( 7925, "You receive an arcane spellbook."))
			ELSE
				Conversation
				INTL( 7926, "Uhh, ahem... it seems there was a problem with the procedure. We will have to \"start\" \"over\"...")
				RemFlag(__FLAG_USER_IS_WAITING_FOR_ARCANE_SPELLBOOK)
				RemFlag(__FLAG_ZHAKAR_IS_BUSY_MAKING_SPELLBOOK)
			ENDIF
		ELSE
			Conversation
			INTL( 7927, "It will take a few more moments, please be patient.")
			BREAK
		ENDIF
	ELSEIF(CurrentRound < CheckFlag(__FLAG_ZHAKAR_IS_BUSY_MAKING_SPELLBOOK) + 18000)
		Conversation
		INTL( 7927, "It will take a few more moments, please be patient.")
		BREAK
	ELSE
		IF(rnd.roll(dice(1, 20)) <= CheckFlag(__FLAG_USER_IS_WAITING_FOR_ARCANE_SPELLBOOK))
			GiveItem(__OBJ_ARCANE_SPELLBOOK)
			GiveFlag(__FLAG_USER_HAS_ARCANE_SPELLBOOK, CheckFlag(__FLAG_USER_HAS_ARCANE_SPELLBOOK) + 1)
			RemFlag(__FLAG_USER_IS_WAITING_FOR_ARCANE_SPELLBOOK)
			RemFlag(__FLAG_ZHAKAR_IS_BUSY_MAKING_SPELLBOOK)
			Conversation
			INTL( 7924, "Here you are, as promised.")
			PRIVATE_SYSTEM_MESSAGE(INTL( 7925, "You receive an arcane spellbook."))
		ELSE
			Conversation
			INTL( 7928, "Uhh, ahem... it seems there was a problem with the procedure. We will have to \"start\" \"over\"...")
			RemFlag(__FLAG_USER_IS_WAITING_FOR_ARCANE_SPELLBOOK)
			RemFlag(__FLAG_ZHAKAR_IS_BUSY_MAKING_SPELLBOOK)
		ENDIF
	ENDIF
ELSE
	IF ((CheckFlag(__QUEST_ROD_OF_MANA) == 1) && (CheckItem(__OBJ_ROD_OF_MANA) > 0))
	   Conversation
	   INTL( 5911, "WHAT!?! You have the Rod of Mana? You're saying that Aloysius Starbolt had it? "
	   "HA! He is but a mediocre wizard. I'll deal with him later. I cannot thank you "
	   "enough for retrieving my precious Rod of Mana for me.")
	   TakeItem(__OBJ_ROD_OF_MANA) 
	   RemFlag(__QUEST_ROD_OF_MANA)    
	   RemFlag(__FLAG_ALOYSIUS_GAVE_ROD)
	   GiveFlag(__FLAG_COUNTER_BEFORE_HATCH, (USER_LEVEL + (rnd.roll(dice(1,2)))))
	ELSEIF ((CheckFlag(__FLAG_ALOYSIUS_GAVE_ROD) == 1) && (CheckItem(__OBJ_ROD_OF_MANA) == 0))
	   Conversation
	   INTL( 5912, "You say that Aloysius had the Rod of Mana? Where it is? What? You've *lost* "
	   "it!?! You DUMB oaf!! Oh well... Easy come, easy go. You may come back later "
	   "to see the progress of the egg's growth until it finally hatches.")
	   RemFlag(__QUEST_ROD_OF_MANA)
	  	IF (CheckFlag(__FLAG_COUNTER_BEFORE_HATCH) == 0)    
			GiveFlag(__FLAG_COUNTER_BEFORE_HATCH, (USER_LEVEL + 1 + (rnd.roll(dice(1,3))))) 
		ENDIF
		RemFlag(__FLAG_ALOYSIUS_GAVE_ROD)
	ELSEIF ((((CheckFlag(__FLAG_COUNTER_BEFORE_ROM)+1) <= (USER_LEVEL)) && (CheckFlag(__FLAG_COUNTER_BEFORE_ROM) != 0)) || (CheckFlag(__QUEST_ROD_OF_MANA) == 1)) 
	   RemFlag(__FLAG_COUNTER_BEFORE_ROM)  
	   IF (CheckFlag(__QUEST_ROD_OF_MANA) == 0)  
			GiveFlag(__QUEST_ROD_OF_MANA, 1) 
		ENDIF
		Conversation
		INTL( 5913, "That blasted \"Deep\" \"One\"! Damned be the God who created them. He stole my Rod of Mana "
		"while I was tending to the precious egg. You *must* retrieve my Rod of Mana before "
		"it falls into the wrong hands -- any others than mine actually! The \"Deep\" \"One\" must "
		"have fled into its filthy cave!")
	ELSEIF ((CheckFlag(__FLAG_COUNTER_BEFORE_HATCH) <= USER_LEVEL) && (CheckFlag(__FLAG_COUNTER_BEFORE_HATCH) != 0))
	   Conversation
	   INTL( 5914, "ARGH! It is a... \"ZZARTGAX\"!! We'll have to fight lest we both die, my friend!")
	   RemFlag(__FLAG_COUNTER_BEFORE_HATCH)
	   RemFlag(__FLAG_ZHAKAR_HAS_THE_EGG)
	   GiveFlag(__QUEST_KRAANIAN_EGG_DONE, 1)
	   SUMMON( "Zzartgax", 63, 1777)
	   BREAK
	ELSE
	   Conversation
	   INTL( 5915, "What brings you into my \"Tower\" today?")
	ENDIF
ENDIF

Command(INTL( 10498, "INVINCIBLE")) 
INTL( 10499, "That is correct! Using arcane formulae and complex components such as the blood of a Seraph, "
"I've achieved invulnerability and immortality! It was quite an \"experiment\". Now I will be "
"able to take my time and gain even more power than before.")

Command(INTL( 10500, "EXPERIMENT")) 
INTL( 10501, "The experiment that resulted in my invulnerability has been a success. I'm not stupid, I tried "
"my formula on something else first. I created a flesh golem from dead body parts, revived it "
"using some powder from a Gem of Destiny, and performed my magic. It didn't work as expected at "
"first, but it allowed me to perfect the spell before I tried it on myself.")

Command(INTL( 10502, "FLESH GOLEM"))
INTL( 10503, "Oh, I set it loose since I didn't have any more use for it. You can find it wandering around. "
"I'm not worried for myself since I'm invulnerable, but you're obviously not, so watch your step.")

Command(INTL( 7561, "START OVER"))
INTL( 7562, "Yes well, er, by starting over I meant you will have to find more \"Sweepers\" and bring me more arcane scrolls. The ones you brought "
"me before have already been consumed and there is nothing I can do about it.")

Command(INTL( 3941, "DEEP ONE"))
INTL( 5916, "The Deep Ones are living in a cavern south-east of the \"Tower\".")

Command(INTL( 5917, "ZZARTGAX"))
""
IF(CheckFlag(__QUEST_KRAANIAN_EGG_DONE) == 1)
	Conversation
    INTL( 5918, "As you've witnessed, the experiment was a SUCCESS!! I couldn't have "
    "done it without your assistance. I am therefore indebted to you and "
    "shall reward you for your help. I give you this ethereal amulet as a "
	"token of my gratitude.")	 
	GiveItem(__OBJ_ETHEREAL_AMULET)  
	Conversation
    FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), 75000 )
	GiveXP(75000)
	GiveFlag(__QUEST_KRAANIAN_EGG_DONE, 2)
ELSEIF (CheckFlag(__QUEST_KRAANIAN_EGG_DONE) == 0)
	Conversation
	INTL( 5919, "Uh? What would you know about that?")	
ELSE
	Conversation
	INTL( 5920, "You have witnessed their strength, eh? Indeed, they are the fiercest "
	"of their race. You won't see much of them but I have heard that some "
	"of them have been sighted in Arakas.")
ENDIF

Command(INTL( 5921, "EGG"))
""
IF (CheckFlag(__QUEST_KRAANIAN_EGG_DONE) == 2)
   Conversation
   INTL( 5922, "Thank you again!")
ELSEIF(CheckFlag(__QUEST_KRAANIAN_EGG_DONE) == 1)
	Conversation
   INTL( 5923, "As you've witnessed, the experiment was a SUCCESS!! I couldn't have "
   "done it without your assistance. I am therefore indebted to you and "
   "shall reward you for your help. I give you this ethereal amulet as a "
	"token of my gratitude.")	 
	GiveItem(__OBJ_ETHEREAL_AMULET)  
	Conversation
    FORMAT(INTL( 4176, " {You} {have} {been} {awarded} {%u} {experience} {points.}"), 75000 )
	GiveXP(75000)
	GiveFlag(__QUEST_KRAANIAN_EGG_DONE, 2)
ELSE
   IF (CheckFlag(__FLAG_ZHAKAR_HAS_THE_EGG) == 1)
		Conversation
		INTL( 5924, "I am still waiting for the egg you brought me to hatch.")
	ELSE
      IF (CheckItem(__OBJ_KRAANIAN_EGG) == 0)
			Conversation
			INTL( 5925, "I yearn to lay my crippled hands on a kraanian egg and "
			"study its every features.")
		ELSE
			Conversation
	        INTL( 5926, "WHAT?!? You are telling me that you've been successful in finding an authentic "
            "kraanian egg? I MUST have it!! Do you agree to give me this precious egg? You "
			"will be rewarded greatly in due time.")
			SetYesNo(EGG)
		ENDIF
	ENDIF
ENDIF	

YES(EGG)
	IF(CheckItem(__OBJ_KRAANIAN_EGG) >= 1) 
		Conversation
		INTL( 5927, "It is but a small egg. I guess it will have to do.")
		GiveFlag( __FLAG_COUNTER_BEFORE_ROM, USER_LEVEL )	
		GiveFlag( __FLAG_ZHAKAR_HAS_THE_EGG, 1)
		;int nNumEggs = CheckItem(__OBJ_KRAANIAN_EGG); 
		FOR(0, nNumEggs)
			TakeItem( __OBJ_KRAANIAN_EGG) 
		ENDFOR
	ELSE
		Conversation
      INTL( 5928, "What sorcery is this?! The egg you were carrying has VANISHED?!!")
	ENDIF

NO(EGG)
	Conversation
   INTL( 5929, "No...NO?? How dare you?! I must have this egg! You *must* reconsider my offer!")

YesNoELSE(EGG)
	Conversation
	INTL( 5930, "Stop mumbling to yourself. Do you agree to give me this precious egg?")
	SetYesNo(EGG)

Command2(INTL( 2034, "HELLO"),INTL( 2035, " HI "))
INTL( 5931, "Have you come up here only to bother me? If you do not have anything "
"better to do, you should leave before I get angry.")

Command2(INTL( 5932, "BELLADONA"),INTL( 5933, "BERRIE"))
INTL( 5934, "If you want some belladona berries, you'll have to ask \"GreyLeaf\", the elder daemon tree. Be sure "
"to ask real nice lest you want to get squashed like a flea. Heh! Heh!")

CmdAND(INTL( 10191, "SKELETON"),INTL( 10192, "BONE")) 
INTL( 10193, "Hey, do you think I'm going to do everything for you? I'm sure that you are capable "
"of finding a skeleton bone by yourself.") 

CmdAND(INTL( 10194, "SILVER"),INTL( 10195, "FEATHER"))
""
IF ((CheckFlag(__USER_CANNOT_GET_A_SILVER_FEATHER) == 1) && (CheckItem(__OBJ_SILVER_FEATHER) == 0) && (CheckFlag(__QUEST_COMPLETED_RITUAL) == 0) && (CheckFlag(__QUEST_ZHAKAR_TIMER_RITUAL) == 0)) 
	Conversation
	INTL( 10504, "I think Princess Delilah has some silver feathers but she somehow forgot to give you one. "
	"Since I'm such in a good mood, I won't force you to walk back to Silversky. Here, I'll give you " 
	"a feather from my private collection. It's yours but.... Shhh... don't tell anyone I gave you one.")
	PRIVATE_SYSTEM_MESSAGE(INTL( 10505, "Zhakar gives you a silver feather.")) 
	GiveItem(__OBJ_SILVER_FEATHER) 
ELSE
	Conversation
	INTL( 10196, "I don't know where you can get those. They're very rare and most feather collectors refuse to part with them.")
ENDIF

Command(INTL( 3860, "GREYLEAF"))
INTL( 5935, "GreyLeaf is a much more powerful demon tree than those you will "
"see wandering around in Ravenwood.")

Command2(INTL( 4061, "MORINDIN"),INTL( 4062, "ARROWMIST"))
INTL( 5936, "You'll probably find him hunting somewhere in Ravenwood.")

CmdAND(INTL( 539, "GOBLIN"),INTL( 4128, "BLOOD"))
INTL( 5937, "Uh. Perhaps you could ask a goblin for a drop or two of its blood.")

CmdAND3(INTL( 4457, "FLASK"),INTL( 2590, "WATER"),INTL( 4458, "CRYSTAL"))
INTL( 5938, "That's your task to find that, not mine.")

Command(INTL( 5628, "ORACLE"))
INTL( 5939, "He was my mentor many years ago. He no longer resides on this island, but has instead "
"moved on to Stoneheim. If you go there some day, once the way is open again, you may "
"try and get an audience with him.")

Command(INTL( 7929, "ARCANE SPELLBOOK"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckFlag(__FLAG_USER_HAS_ARCANE_SPELLBOOK) >= 2)
		Conversation
		INTL( 7930, "I have already given you more than enough arcane spellbooks.")
	ELSE
		Conversation																																	  
		INTL( 7931, "You require an arcane spellbook? I see, what? You want me to give you two of them? Bah! I hope you realize that this will cost "
		"you. These arcane spellbooks are not so easily \"created\", as you probably guessed.")
	ENDIF
ELSE
	Conversation
	INTL( 660, "That is none of your business.")
ENDIF

Command(INTL( 7932, "CREATE"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 7933, "Very well then. To create one arcane spellbook, I will require at least 10 \"arcane\" \"scrolls\" and a minimum of 35000 gold. The more "
	"scrolls you have, the easier the process will be and the less chance of failing I have. "
	"Do you have at least 10 arcane scrolls and 35000 gold?")
	SetYesNo(SPELLBOOK)
ELSE
	Conversation
	INTL( 660, "That is none of your business.")
ENDIF

YES(SPELLBOOK)
	IF(CheckItem(__OBJ_ARCANE_SCROLL) >= 10)
		IF(Gold >= 35000)
			Conversation
			INTL( 7934, "Very well, I shall begin right away then. Come back later to see if I'm done.")
			IF(CheckItem(__OBJ_ARCANE_SCROLL) < 20)
				GiveFlag(__FLAG_USER_IS_WAITING_FOR_ARCANE_SPELLBOOK, CheckItem(__OBJ_ARCANE_SCROLL))
				;int nNumScrolls = CheckItem(__OBJ_ARCANE_SCROLL); 
				FOR(0, nNumScrolls)
			 		TakeItem(__OBJ_ARCANE_SCROLL)
				ENDFOR
				PRIVATE_SYSTEM_MESSAGE(INTL( 7935, "Zhakar takes all your arcane scrolls."))
			ELSEIF(CheckItem(__OBJ_ARCANE_SCROLL) == 20)
				GiveFlag(__FLAG_USER_IS_WAITING_FOR_ARCANE_SPELLBOOK, 20)
				FOR(0, 20)
					TakeItem(__OBJ_ARCANE_SCROLL)
				ENDFOR
				PRIVATE_SYSTEM_MESSAGE(INTL( 7935, "Zhakar takes all your arcane scrolls."))
			ELSE
				GiveFlag(__FLAG_USER_IS_WAITING_FOR_ARCANE_SPELLBOOK, 20)
				FOR(0, 20)
					TakeItem(__OBJ_ARCANE_SCROLL)
				ENDFOR
				PRIVATE_SYSTEM_MESSAGE(INTL( 7936, "Zhakar takes 20 of your scrolls."))
			ENDIF
			TakeGold(35000)
			PRIVATE_SYSTEM_MESSAGE(INTL( 7937, "Zhakar takes 35000 gold."))
			GiveFlag(__FLAG_ZHAKAR_IS_BUSY_MAKING_SPELLBOOK, CurrentRound)
			BREAK
		ELSE
			Conversation
			INTL( 7938, "You don't seem to have enough money. Come back when you have acquired at least 35000 gold.")
		ENDIF
	ELSE
		IF(Gold >= 35000)
			Conversation
			INTL( 7939, "You don't have enough arcane scrolls for me to even have a chance of succeeding the procedure. Come back when you "
			"have at least 10 of them.")
		ELSE
			Conversation
			INTL( 7940, "You don't seem to have enough money. On top of that, you don't even have the 10 arcane scrolls I require. Come back "
			"when you have at least 10 arcane scrolls and the 35000 gold. Remember, the more scrolls you bring me, the higher "
			"my chances of success are.")
		ENDIF
	ENDIF
NO(SPELLBOOK)
	Conversation
	INTL( 7941, "Then I can't help you. If you want me to \"create\" an arcane spellbook, you need to bring at least 10 \"arcane\" \"scrolls\" "
	"and 35000 gold.")
YesNoELSE(SPELLBOOK)
	Conversation
	INTL( 7942, "Do you have at least 10 arcane scrolls and 35000 gold or not?")
	SetYesNo(SPELLBOOK)

Command(INTL( 7943, "ARCANE SCROLL"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 7944, "The most common use I have for these scrolls is to create \"Sweepers\". They are little rodents that help me clean up the tower. "
	"I suppose you could find them if you want the scrolls, I can always create more later.")
ELSE
	Conversation
	INTL( 660, "That is none of your business.")
ENDIF

Command(INTL( 7945, "SWEEPER"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckFlag(__FLAG_SWEEPERS_KILLED_BY_USER) >= 1)
		IF(CheckGlobalFlag(__GLOBAL_FLAG_TOTAL_SWEEPERS_PRESENT) <= 5)
			Conversation
			INTL( 7946, "You can't find any more Sweepers? I'm sure they are around somewhere. You have but to look again and I am certain you will "
			"find more lurking around.")
			;int nNumSweeper = CheckGlobalFlag(__GLOBAL_FLAG_TOTAL_SWEEPERS_PRESENT);
			FOR(0, 20 - nNumSweeper)
				SWITCH(rnd.roll(dice(1, 20)))
					CASE(1)
			 			SUMMON("SWEEPER", 75, 1569)
					ENDCASE
					CASE(2)
						SUMMON("SWEEPER", 83, 1577)
					ENDCASE
					CASE(3)
						SUMMON("SWEEPER", 66, 1579)
					ENDCASE
					CASE(4)
						SUMMON("SWEEPER", 55, 1590)
					ENDCASE
					CASE(5)
						SUMMON("SWEEPER", 75, 1595)
					ENDCASE
					CASE(6)
						SUMMON("SWEEPER", 91, 1595)
					ENDCASE
					CASE(7)
						SUMMON("SWEEPER", 99, 1599)
					ENDCASE
					CASE(8)
						SUMMON("SWEEPER", 56, 1600)
					ENDCASE
					CASE(9)
						SUMMON("SWEEPER", 67, 1609)
					ENDCASE
					CASE(10)
						SUMMON("SWEEPER", 79, 1613)
					ENDCASE
					CASE(11)
						SUMMON("SWEEPER", 75, 1661)
					ENDCASE
					CASE(12)
						SUMMON("SWEEPER", 67, 1679)
					ENDCASE
					CASE(13)
						SUMMON("SWEEPER", 82, 1680)
					ENDCASE
					CASE(14)
						SUMMON("SWEEPER", 95, 1691)
					ENDCASE
					CASE(15)
						SUMMON("SWEEPER", 57, 1697)
					ENDCASE
					CASE(16)
						SUMMON("SWEEPER", 86, 1703)
					ENDCASE
					CASE(17)
						SUMMON("SWEEPER", 74, 1713)
					ENDCASE
					CASE(18)
						SUMMON("SWEEPER", 92, 1779)
					ENDCASE
					CASE(19)
						SUMMON("SWEEPER", 79, 1792)
					ENDCASE
					CASE(20)
						SUMMON("SWEEPER", 66, 1807)
					ENDCASE
				ENDSWITCH
			ENDFOR
		ELSE
			Conversation
			INTL( 7947, "There must be more lurking around here somewhere... look again.")
		ENDIF
	ELSE
		Conversation
		INTL( 7948, "You have but to strike them down to banish them and you will receive the scroll that was used to create them. Go now, seek them "
		"out throughout this tower and bring back the scrolls.")
		IF(CheckGlobalFlag(__GLOBAL_FLAG_TOTAL_SWEEPERS_PRESENT) <= 5)		
			SUMMON("SWEEPER", 75, 1569)
			SUMMON("SWEEPER", 83, 1577)
			SUMMON("SWEEPER", 66, 1579)
			SUMMON("SWEEPER", 55, 1590)
			SUMMON("SWEEPER", 75, 1595)
			SUMMON("SWEEPER", 91, 1595)
			SUMMON("SWEEPER", 99, 1599)
			SUMMON("SWEEPER", 56, 1600)
			SUMMON("SWEEPER", 67, 1609)
			SUMMON("SWEEPER", 79, 1613)
			SUMMON("SWEEPER", 75, 1661)
			SUMMON("SWEEPER", 67, 1679)
			SUMMON("SWEEPER", 82, 1680)
			SUMMON("SWEEPER", 95, 1691)
			SUMMON("SWEEPER", 57, 1697)
			SUMMON("SWEEPER", 86, 1703)
			SUMMON("SWEEPER", 74, 1713)
			SUMMON("SWEEPER", 92, 1779)
			SUMMON("SWEEPER", 79, 1792)
			SUMMON("SWEEPER", 66, 1807)
		ENDIF
	ENDIF
ELSE
	Conversation
	INTL( 660, "That is none of your business.")
ENDIF

Command(INTL( 6251, "STONEHEIM"))
INTL( 7949, "Unless you want to swim, you might need some \"mystical\" aid.")

Command(INTL( 7950, "MYSTICAL"))
INTL( 7951, "I know of a \"ritual\" of blood that would require a large amount of my strength. "
"Then, you will be able to step in the small pentacle and be translocated on "
"Stoneheim. Once you are there, you're on your own. I will do no more for you.")
IF ((CheckFlag(__FLAG_GOOD_QUEST_COMPLETED_ON_RD) == 0) && (CheckFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD) == 0))
	Conversation
	INTL( 10469, " Unfortunately, I sense that you are not ready to leave Raven's Dust just yet.") 
ENDIF 

Command(INTL( 1046, "TELEPORT"))
INTL( 7952, "Yes, that's right, I can do a teleportation \"ritual\".")

Command2(INTL( 4541, "PRINCESS"),INTL( 1005, "DELILAH")) 
INTL( 10470, "Princess Delilah is King Theodore's only daughter.")

Command(INTL( 509, "BALORK"))
INTL( 10471, "Balork is a low-level demon who terrorizes the inhabitants of Lighthaven.")

Command(INTL( 7953, "RITUAL"))
""
IF ((CheckFlag(__FLAG_GOOD_QUEST_COMPLETED_ON_RD) == 0) && (CheckFlag(__FLAG_EVIL_QUEST_COMPLETED_ON_RD) == 0))	
	//	Conversation
	//	"I'm afraid you are not ready to leave Raven's Dust just yet. I sense you bear the dreadful "
	//	"brand of Balork upon your soul. You wouldn't be welcomed in Stoneheim. You should seek Princess "
	//	"Delilah as she is the only one who can help you now."	
		Conversation
		INTL( 10472, "You are not ready to leave Raven's Dust just yet. I sense there are still great things you must do on "
		"here. I would not want to be the one to oppose the Fates and send you where you're not supposed to "
		"be. In due time, I shall help you reach Stoneheim, but not before.")
ELSEIF(CheckFlag(__QUEST_ISLAND_ACCESS) >= 2)
	;int nTeleportFee = 200 * USER_LEVEL;
	Conversation
	FORMAT(INTL( 7954, "Since you've already been to Stoneheim, it's easier to synchronize your life "
	"essence to return there. I can send you to Stonecrest without a ritual if you pay me "
	"%u gold pieces for that trip. Will you pay the sum?"), nTeleportFee)
	SetYesNo(TPORT)
ELSE
	IF (CheckFlag(__QUEST_COMPLETED_RITUAL) == 1)
	   Conversation
	   FORMAT(INTL( 7955, "%s? Do you want to step into the pentacle to be teleported "
	   "to Stoneheim?"), USER_NAME)
	   SetYesNo(TELEPORT)
	ELSEIF (CheckFlag(__QUEST_ZHAKAR_TIMER_RITUAL) != 0 )
		IF (CurrentRound < (CheckFlag(__QUEST_ZHAKAR_TIMER_RITUAL) - 72000))
			IF (CurrentRound > 72000) 
				GiveFlag(__QUEST_COMPLETED_RITUAL, 1)
				RemFlag(__QUEST_ZHAKAR_TIMER_RITUAL)
				Conversation
				FORMAT(INTL( 7956, "You have come back, %s! I have completed the ritual. By setting "
				"foot into the pentacle I've drawn, you shall be teleported directly to "
				"Stoneheim. Do you wish to step into the pentacle?"), USER_NAME)
				SetYesNo(TELEPORT)
			ELSE				  
				;int nTimeLeft = (72000 - CurrentRound) / 1200;
				Conversation
				FORMAT(INTL( 5028, "Sorry, I made a mess and had to start all over. Please come back in %u minutes."),nTimeLeft)
			ENDIF
		ELSE 
			IF ((CheckFlag(__QUEST_ZHAKAR_TIMER_RITUAL) < CurrentRound) && (CheckFlag(__QUEST_ZHAKAR_TIMER_RITUAL) != 0))
				GiveFlag(__QUEST_COMPLETED_RITUAL, 1)				
				RemFlag(__QUEST_ZHAKAR_TIMER_RITUAL)
				Conversation
				FORMAT(INTL( 7957, "You have come back, %s! I have completed the ritual. By setting "
				"foot into the pentacle I've drawn, you shall be teleported directly to "
				"Stoneheim. Do you wish to step into the pentacle?"), USER_NAME)
				SetYesNo(TELEPORT)
			ELSE
				;int nTimeLeft = ((CheckFlag(__QUEST_ZHAKAR_TIMER_RITUAL) - CurrentRound) / 1200);
				Conversation
				FORMAT(INTL( 7958, "I apologize but the ritual isn't completed yet. Please come back in %u minutes."),nTimeLeft)
			ENDIF
		ENDIF
	ELSE
		IF ( (CheckItem(__OBJ_FLASK_OF_GOBLIN_BLOOD) >= 1) && (CheckItem(__OBJ_BELLADONA_BERRIES) >= 1) && (CheckItem(__OBJ_SKELETON_BONE) >= 1) && (CheckItem(__OBJ_FLASK_OF_CRYSTAL_WATER) >= 1) && (CheckItem(__OBJ_SILVER_FEATHER) >= 1))
			IF(USER_LEVEL >= 50)
				Conversation
				INTL( 7959, "You have brought me all the needed components for the ritual of blood? You have done well, my friend. "
				"Now, if you want me to complete the difficult ritual of blood, you must pay me 5000 gold pieces for "
				"my troubles. Do you agree to pay such a price?")
				SetYesNo(RITUAL)
			ELSE
				PRIVATE_SYSTEM_MESSAGE(INTL( 11420, "You must be at least level 50 to gain access to Stoneheim."))
				Conversation
				INTL( 11421, "While I commend your efforts in gathering all the required ingredients for the ritual, I regret to "
				"tell you that it will all be for naught. I believe that at your current level of experience, you would "
				"not be able to survive the ritual. I would truly hate to have your blood on my hands. Therefore, I "
				"suggest you go back out into the world and come back once you have gathered more experience.")
			ENDIF
		ELSE
			IF(USER_LEVEL >= 50)
				Conversation
				INTL( 10473, "For the ritual of blood that will transport you to Stoneheim, I need some \"goblin\" \"blood\" "
				"to paint the mystical pentacle, a \"silver\" \"feather\" to draw it with, a \"flask\" \"of\" "
				"\"crystal\" \"water\" and a \"skeleton\" \"bone\" that I shall smash into powder. Oh, and I "
				"almost forgot, I also need some \"belladona\" \"berries\" to help me concentrate as this ritual "
				"will require a higher state of mind of me. Of course, my services aren't free... a small fee of 5000 gold "
				"for my troubles is also required.")
			ELSE
				PRIVATE_SYSTEM_MESSAGE(INTL( 11420, "You must be at least level 50 to gain access to Stoneheim."))
				Conversation
				INTL( 11422, "Although I am certain you are very eager to continue on your quest, I assure you that at your current "
				"level of experience you would be unable to survive the ritual. I suggest you go out into the world "
				"to gain more experience and come back when you are somewhat stronger.")
			ENDIF
		ENDIF	
	ENDIF
ENDIF

YES(TPORT)
	;int nTeleportFee = 200 * USER_LEVEL;
	IF(Gold >= nTeleportFee)
		TakeGold(nTeleportFee)
		PRIVATE_SYSTEM_MESSAGE( FORMAT(INTL( 10197, "You give %u gold to Zhakar."), nTeleportFee) ) 
		Conversation
		INTL( 7961, "Thank you. Shall you step into the pentagram?")		
		SetYesNo(TELEPORT)
	ELSE
		Conversation
		INTL( 7962, "I'm afraid you don't have the gold.")
		BREAK
	ENDIF

NO(TPORT)
	Conversation
	INTL( 5940, "How do you spell c-o-w-a-r-d?")

YesNoELSE(TPORT)
	Conversation
	INTL( 5941, "Uhhh? Was that a yes or a no?")
	SetYesNo(TPORT)

YES(TELEPORT)
	Conversation
	INTL( 7963, "Have a nice trip!")
	IF(CheckFlag(__QUEST_ISLAND_ACCESS) == 1)
		GiveFlag(__QUEST_ISLAND_ACCESS, 2)
	ENDIF
	RemFlag(__QUEST_COMPLETED_RITUAL)
	RemFlag(__QUEST_ZHAKAR_TIMER_RITUAL)
	
	PRIVATE_SYSTEM_MESSAGE(INTL( 9177, "You feel somewhat dizzy after being translocated somewhere on Stoneheim."))
	TELEPORT(207, 673, 0)

NO(TELEPORT)
	Conversation
	INTL( 5940, "How do you spell c-o-w-a-r-d?")

YesNoELSE(TELEPORT)
	Conversation
	INTL( 5941, "Uhhh? Was that a yes or a no?")
	SetYesNo(TELEPORT)

YES(RITUAL)
IF ( (CheckItem(__OBJ_FLASK_OF_GOBLIN_BLOOD) >= 1) && (CheckItem(__OBJ_BELLADONA_BERRIES) >= 1) && (CheckItem(__OBJ_SKELETON_BONE) >= 1) && (CheckItem(__OBJ_FLASK_OF_CRYSTAL_WATER) >= 1) && (CheckItem(__OBJ_SILVER_FEATHER) >= 1)) 
	IF(Gold >= 5000)
		TakeItem(__OBJ_FLASK_OF_GOBLIN_BLOOD)
		TakeItem(__OBJ_BELLADONA_BERRIES)
		TakeItem(__OBJ_FLASK_OF_CRYSTAL_WATER)
		TakeItem(__OBJ_SKELETON_BONE)
		;int nNumSilverFeather = CheckItem(__OBJ_SILVER_FEATHER); 
		FOR( 0, nNumSilverFeather ) 
			TakeItem(__OBJ_SILVER_FEATHER)
		ENDFOR 
		TakeGold(5000)
		PRIVATE_SYSTEM_MESSAGE(INTL( 10198, "You give 5000 gold along with all the required components to Zhakar.")) 		
		Conversation
		INTL( 5942, "Good. Now, leave me be. This ritual will require my utmost concentration.") 
		GiveFlag(__QUEST_ZHAKAR_TIMER_RITUAL, 1 HOURS TDELAY) 
	ELSE
		Conversation
		INTL( 5943, "You do not have the required 5000 gold pieces!")
	ENDIF
ELSE
	Conversation
	INTL( 7960, "You do not have all the components I require. Remember these words: I need some \"goblin\" "
	"\"blood\" to paint the mystical pentacle, a \"silver\" \"feather\" to draw it with, a \"flask\" \"of\" "
	"\"crystal\" \"water\" and a \"skeleton\" \"bone\" that I shall smash into powder. Oh, and I "
	"almost forgot, I also need some \"belladona\" \"berries\" to help me concentrate as this ritual "
	"will require a higher state of mind of me. Of course, my services aren't free... a small of 5000 gold "
	"for my troubles is also required.") 
ENDIF 

NO(RITUAL)
Conversation
INTL( 5748, "Your choice.")

YesNoELSE(RITUAL)
Conversation
INTL( 4166, "Uh? Whatever.")

Command(INTL( 3848, "ZHAKAR"))
INTL( 5945, "It seems that you have already heard of me, haven't you? Indeed, I am Zhakar "
"the great wizard and sole master of this damned \"tower\".")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 5946, "I am Zhakar, the great sorceror and sole master of this \"tower\".")

Command4(INTL( 3696, "WHAT DO YOU DO"),INTL( 4905, "WHAT ARE YOU"),INTL( 487, "OCCUPATION"),INTL( 489, "WORK"))
""
IF (USER_INT <= 35) 
   Conversation
   INTL( 5947, "I do not think that you would be able to understand what I am "
   "doing here.")
ELSE
   Conversation
   INTL( 5948, "I am studying the universe as it is. I have many ongoing \"studies\" "
   "that I work on currently. One of them, my favorite, is the study "
   "about \"Kraanians\".") 
ENDIF

Command2(INTL( 5949, "STUDIES"),INTL( 5444, "STUDY"))
INTL( 5950, "As I have stated before, I am very busy with my study of Kraanians, but I am not without any free time. Therefore "
"I have time to help you better your \"magic\" skills, if you have any that is, heh heh.")

Command2(INTL( 1096, "MAGIC"),INTL( 495, "LEARN"))
INTL( 7563, "Now then, let's see if we can improve those magic skills of yours.")
CreateSkillList
	AddTeachSkill (__SPELL_CHAIN_LIGHTNING, 15, 35700)
	AddTeachSkill (__SPELL_VORTEX_OF_AIR, 18, 60800)
	AddTeachSkill (__SPELL_NIMBLENESS, 19, 72688)
SendTeachSkillList

Command(INTL( 1794, "ROYAL KEY"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY3) >= 5) // If the PC has already received a key...
	Conversation
	INTL( 5984, "What, you want another one?")
	SetYesNo(GET_MORE_KEY)
ELSE // PC has never received a key:
	Conversation
	INTL( 5985, "I've got one and it's all mine.")
ENDIF

YES(GET_MORE_KEY)
	IF (Gold >= (10000 * CheckFlag(__QUEST_ROYAL_KEY3))) // PC asks for another key and has the money to get it:
      Conversation
		FORMAT(INTL( 5986, "Very well, here it is again, but it's just cost you %u gold pieces."), 10000 * CheckFlag(__QUEST_ROYAL_KEY3))
		TakeGold(10000 * CheckFlag(__QUEST_ROYAL_KEY3))
		GiveItem(__OBJ_ROYAL_KEY_3)
		GiveFlag(__QUEST_ROYAL_KEY3, CheckFlag(__QUEST_ROYAL_KEY3)+1)
	ELSE // PC wants another key but doesn't have the money:
      Conversation
		FORMAT(INTL( 5987, "Come back when you've got at least %u gold pieces, and we'll talk."), 10000 * CheckFlag(__QUEST_ROYAL_KEY3))
	ENDIF

NO(GET_MORE_KEY)
	Conversation
	INTL( 5988, "Better not. The more you ask, the more I ask.")

YesNoELSE(GET_MORE_KEY)
	Conversation
	INTL( 5989, "Heh heh heh... Makes perfect sense!")

Command2(INTL( 4002, "ELYSANA"),INTL( 4003, "BLACKROSE"))
""
SWITCH(CheckFlag(__QUEST_ROYAL_KEY3))
	CASE(2) // Has been sent by Elysana Blackrose
		Conversation
		INTL( 5990, "Ha! Ha ha! BwaahahahHAHAAHAHA!!! She told YOU that I'd give YOU a key if "
		"you mentioned HER name? Surely you JEST!!!")
		GiveFlag(__QUEST_ROYAL_KEY3,3)
	ENDCASE
	CASE(3) // Has been mocked once by Zhakar
		Conversation
		INTL( 5991, "WHAT?!? You *dare* mention her name again before me?!? This could cost you "
		"dearly, if you persist! *mumble* Let's see... Fire Storm... Where did I put "
		"that spell again... *mutter*")
		GiveFlag(__QUEST_ROYAL_KEY3,4)
	ENDCASE
	CASE(4) // Has been mocked twice by Zhakar
		Conversation
		INTL( 5992, "Well... I guess I could let you have a shot at it. Name three keys that won't "
		"open doors. {Type} {ANSWER} {then} {the} {three} {words} {of} {your} {answer.}")
	ENDCASE
	OTHERWISE
		Conversation
		INTL( 5993, "What about her? She dabbles in alchemy, but I'd hardly call her a sorceress.")
	ENDCASE
ENDSWITCH

CmdAND4(INTL( 5994, "ANSWER"),INTL( 5995, "MONKEY"),INTL( 5996, "DONKEY"),INTL( 5997, "TURKEY"))
""
IF (CheckFlag(__QUEST_ROYAL_KEY3) >= 4)
	Conversation
	INTL( 5998, "Oh, wonderful!! You found it! Very good, very good, there's a semblance of a brain "
	"between these two ears of yours. Well, a promise is a promise, I'll give you the "
	"key you asked for.")
	GiveItem(__OBJ_ROYAL_KEY_3)
	GiveFlag(__QUEST_ROYAL_KEY3, 5)
ELSE
	Conversation
	INTL( 5999, "Let's see... If that's the answer, the question must be... Um... Ah, I give up!")	
ENDIF

Command2(INTL( 3862, "BANE"),INTL( 3863, "BLACKBLOOD"))
INTL( 6000, "Bane? I don't know much about him except that his head probably "
"does not fit in the door frame!") 

Command(INTL( 6001, "TAUNTING HORROR"))
INTL( 6002, "They are useful for disposing of unwanted visitors and thieves.")

Command(INTL( 3844, "NIGHTBLADE"))
INTL( 6003, "Beware. They are skilled assassins and their offensive magic can "
"be quite devastating... Hmpft! Much less powerful than me, mind you.")

Command(INTL( 1686, "TOWER"))
INTL( 6004, "This is the Tower of Sorcery. It is both my home and my "
"tomb for I will never leave the library.")

Command(INTL( 3845, "BLACKGUARD"))
INTL( 6005, "They are swift assassins and cannot be trusted. However, they "
"sorely lack skill in the Art which is why they are not \"Nightblades\" yet.")

Command2(INTL( 1072, "KING"),INTL( 754, "THEODORE"))
INTL( 6006, "Pah! He is a pathetic fool. He would be less than nothing without "
"his personal advisors.")

CmdAND(INTL( 4160, "KRAANIAN"),INTL( 3955, "EYE"))
""
IF (CheckFlag(__QUEST_KRAANIAN_EYES) == 0)
   Conversation
   INTL( 6007, "I don't think that you really need kraanian eyes.")
ELSE
   Conversation
   INTL( 6008, "BAH! You need \"kraanian\" eyes, do you? You're on your own, my friend! "
   "Some annoying \"nightblades\" have breached through the \"tower\"'s defenses "
   "and stole about every magical components I had! \"Bane\" \"Blackblood\" "
   "probably has everything I owned by now...")
   IF (CheckFlag(__QUEST_KRAANIAN_EYES) == 1)
      GiveFlag(__QUEST_KRAANIAN_EYES, 2)
   ENDIF
ENDIF

Command(INTL( 4160, "KRAANIAN"))
INTL( 6009, "You've seen them in action on Arakas, haven't you? It is quite peculiar "
"to see the hatred they have toward giant wasps and death stingers. I would "
"be quite interested in obtaining a \"kraanian\" \"egg\" to study its features.")

Command(INTL( 3846, "ROGUE MAGE"))
INTL( 6010, "You've seen the rogue mages wandering in the accursed forest of \"Ravenwood\"? "
"They are working under the orders of \"Blackblood\" but they shouldn't "
"cause you too much troubles for they aren't very skilled in the Art yet.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 6011, "It has been quite a while since I had some. Now, begone!")
BREAK

Command4(INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"))
INTL( 6012, "It took you time to understand. Finally, I can continue on my studies "
"in peace.")
BREAK

Command(INTL( 3771, "?"))
""
SWITCH(rnd.roll(dice(1,6)))
	CASE(1)
		Conversation
		INTL( 6013, "Heh heh... If I had a gold piece for every stupid question I've been asked, "
		"I'd be a wealthy man!")
		IF (Gold > 1)
			TakeGold(1)
		ENDIF
	ENDCASE
	CASE(2)
		Conversation
		INTL( 6014, "Bah! Don't bother me with your silly questions, I'm busy with an important "
		"experiment.")
	ENDCASE
	CASE(3)
		Conversation
		INTL( 6015, "Aw, don't tell me you're still here?")
	ENDCASE
	CASE(4)
		Conversation
		INTL( 6016, "My my, we're full of questions today, aren't we?")
	ENDCASE
	CASE(5)
		Conversation
		INTL( 6017, "Let me consult my crystal ball... The answer is... tomorrow. Does that "
		"make sense to you? I certainly can't figure it out. Oh well... *shrug*")
	ENDCASE
	CASE(6)
		Conversation
		INTL( 6018, "I'm afraid I don't have the answer to that question.")
	ENDCASE
ENDSWITCH

Default
""
IF (rnd.roll( dice( 1, 2) ) == 1)
    Conversation
    INTL( 6019, "Tell it to someone who actually cares!")
ELSE
    Conversation
    INTL( 6020, "Perhaps the answer lies somewhere in one of my books.")     
ENDIF

EndTalk
}
//////////////////////////////////////////////////////////////////////////////////////////
void Zhakar::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL(__SPELL_CHAIN_LIGHTNING, 15, 35700)
			TEACH_SKILL(__SPELL_VORTEX_OF_AIR, 18, 60800)
			TEACH_SKILL(__SPELL_NIMBLENESS, 19, 72688)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE