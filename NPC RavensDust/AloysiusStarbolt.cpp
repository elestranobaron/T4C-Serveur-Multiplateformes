/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "AloysiusStarbolt.H"

AloysiusStarbolt::AloysiusStarbolt()
{}

AloysiusStarbolt::~AloysiusStarbolt()
{}

extern NPCstructure::NPC Mage;

void AloysiusStarbolt::Create( void )
{
      npc = ( Mage );
      SET_NPC_NAME( "[2913]Aloysius Starbolt" );  
      npc.InitialPos.X = 1370;//2949;//1342; 
      npc.InitialPos.Y = 2380;//212;//2380;
      npc.InitialPos.world = 0;//4;//0;
}

void AloysiusStarbolt::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{
CONSTANT DEAL = 1;
CONSTANT ROD = 2;
CONSTANT TARANTULA = 3; 

InitTalk

Begin
""
IF (CheckFlag( __QUEST_KILLED_ORC_MAGUS) == 1) //If user has killed the Orc Magus...
	IF (CheckFlag(__QUEST_REWARDED_FOR_MAGUS) > 0)	//...and has not been rewarded for it,
		IF (rnd.roll(dice(1,2)) == 1) //then Alosius either says thanks
			Conversation
			INTL( 3922, "You defeated that vile orcish arch mage again? I cannot thank you "
			"enough. I would do it myself but I have to stay at the Castle to protect "
			"our Majesty. I don't have anything to offer except this advice: "
			"'South of a middle tree in the middle of a sea shall you find "
			"the fabled lost dungeon.")
			RemFlag( __QUEST_KILLED_ORC_MAGUS) //and cancels the Orc Magus Quest...
		ELSE //...or  he gives the Ring of Despair and cancels the Orc Magus Quest.
			Conversation
			INTL( 3923, "You defeated the orcish arch mage by yourself again? Great! I do not have "
			"much to offer right now. I hope this ring of confidence will satisfy you.")
			RemFlag( __QUEST_KILLED_ORC_MAGUS)
			GiveItem(__OBJ_RING_OF_CONFIDENCE)
		ENDIF		
	ELSE //If the user has never been rewarded for killing the Orc Magus...
		Conversation
		INTL( 3924, "What? You're telling me that the cause of the magical disturbance "
		"was a puny orcish arch mage? Damn! I could have dealt with him "
		"myself if he hadn't been on his turf. Nonetheless, you deserve "
		"a reward. I give this platinum ring to you. Take good care "
		"of it because I do not have many of these. {You} {have} {been} "
		"{awarded} {25000} {experience} {points.}")
		GiveXP( 25000 ) //...he's getting plenty goodies and loses the Orc Magus Quest.
		GiveItem( __OBJ_PLATINUM_RING )
		RemFlag( __QUEST_KILLED_ORC_MAGUS)
		GiveFlag( __QUEST_REWARDED_FOR_MAGUS, 1)
	ENDIF
ELSEIF (CheckGlobalFlag( __GLOBAL_FLAG_ORC_QUEST) == 1) //If the user hasn't killed the Orc Mage
	Conversation //...and the quest can be activated...
	INTL( 3925, "Argh! I sense a disturbance in the magic flow and it's causing "
	"all my spells to fail miserably. This appears to be coming "
	"from the north. I wonder what it might be this time!")
ELSE // Otherwise everything is normal.
	Conversation
	INTL( 3926, "You appear to be lost or something. Perhaps I might be of "
	"assistance if you need to know something.") 
ENDIF	

Command(INTL( 3927, "PLATINUM RING"))
""
IF (CheckFlag(__QUEST_REWARDED_FOR_MAGUS) == 1) //If the user got the platinum ring...
	IF( CheckItem(__OBJ_PLATINUM_RING) == 0)    //...but no longer has it in his possession,
		Conversation
		INTL( 3928, "What? You've lost the precious platinum ring I gave you? "
		"Humpft! You should be careful, it is a precious magical "
		"item. Hmmmm, I think I could manage to sell another one "
		"to you for.. *ahem* 50,000 gold pieces. Is that a deal?") 
		SetYesNo( DEAL )	//...he can buy a new one
	ELSE
		Conversation //If the user still has the platinum ring...
		INTL( 3929, "I hope that the platinum ring I gave you is useful.")
	ENDIF
ELSEIF (CheckFlag(__QUEST_REWARDED_FOR_MAGUS == 2) ) //If the user had to purchase the ring,
	IF( CheckItem(__OBJ_PLATINUM_RING) == 0) //...and has once more lost it...
		Conversation //Aloysius gives him hell and refuses to sell it to him again.
		INTL( 3930, "Uh? Again? How can you be dumb enough to lose the ring "
		"twice? That's enough! I won't give or sell you another "
		"ring because you're dumb enough to lose it or sell it. "
		"You've had your chance before but that's it for now!")
	ELSE //If the user still has his second ring, Aloysius warns him not to lose it again.
		Conversation
		INTL( 3931, "Try not to lose the ring this time.")
	ENDIF
ELSE //If the user never got a ring, he gets an explanation.
	Conversation
	INTL( 3932, "The platinum ring is an enchanted steel ring that gives " 
	"something to its wearer.")
ENDIF	

YES(DEAL)
	IF (Gold < 50000 )
		Conversation
		INTL( 3933, "Pah! You will not fool me that easily. I might be old but "
		"I am not blind yet. I can see that you do not have that "
		"amount of gold pieces on you.") 
	ELSE
		Conversation
		INTL( 3934, "That's a deal, young one! This is the last time I give you "
		"a platinum ring however.")
		TakeGold(50000)
		GiveItem(__OBJ_PLATINUM_RING) 
		GiveFlag(__QUEST_REWARDED_FOR_MAGUS, 2)
	ENDIF

NO(DEAL)
Conversation
INTL( 3935, "Oh well. That's your choice.")

YesNoELSE(DEAL)
Conversation
INTL( 3936, "You can mumble to yourself alone. I've more important things to do.")

Command(INTL( 1159, "SCROLL"))
""
IF (CheckFlag(__FLAG_USER_KNOWS_ABOUT_ALOYSIUS) == 0)
	IF (CheckItem(__OBJ_NOTE_DEEPONE) > 0)
		Conversation
		INTL( 3937, "You have a note saying I bought a stolen item? AH! This note "
		"has been falsified. {The} {Deep} {One's} {note} {instantly} "
		"{crumbles} {into} {dust!}")
		TakeItem(__OBJ_NOTE_DEEPONE)
	ELSE
		Conversation
		INTL( 3938, "There are a lot of scrolls in this world, my friend.")
	ENDIF
ELSE // Deep One gave a value of '1' when he died. 
	IF (CheckFlag(__FLAG_USER_KNOWS_ABOUT_ALOYSIUS) == 2) 
		Conversation
		INTL( 3939, "Stop bothering me. I already gave you the Rod of Mana.")
		IF (CheckItem(__OBJ_NOTE_DEEPONE) > 0)
			Conversation	
			INTL( 7122, " You won't need these useless scrolls that the Deep One gave you anymore.")
			;int nNotes = CheckItem(__OBJ_NOTE_DEEPONE); 
			FOR (0, nNotes)
				TakeItem(__OBJ_NOTE_DEEPONE) 
			ENDFOR
		ENDIF
	ELSE // FLAG is worth 1 
		IF (CheckItem(__OBJ_NOTE_DEEPONE) > 0)
			Conversation
			INTL( 3940, "Ok. Ok. I admit it! I bought the Rod of Mana from the Deep One. So what? "
			"Oh. It was Zhakar's...? I see. But.. you see... I *BOUGHT* this item. "
			"I won't give it back to you unless you pay twice the price I paid... "
			"That will be 32,000 gold pieces. Does that seem fair to you?") 
			SetYesNo(ROD)
		ELSE
			Conversation
			INTL( 3938, "There are a lot of scrolls in this world, my friend.")			
		ENDIF	
	ENDIF
ENDIF

Command(INTL( 3941, "DEEP ONE"))
""
IF (CheckFlag(__FLAG_USER_KNOWS_ABOUT_ALOYSIUS) == 0)
	IF (CheckItem(__OBJ_NOTE_DEEPONE) > 0)
		Conversation
		INTL( 3942, "You have a note saying I bought a stolen item? AH! This note "
		"has been falsified. {The} {Deep} {One's} {note} {instantly} "
		"{crumbles} {into} {dust!}")
		TakeItem(__OBJ_NOTE_DEEPONE)
	ELSE
		Conversation
		INTL( 3943, "The Deep Ones are a race of humanoids dwelling in a cave near Zhakar's tower.")
	ENDIF
ELSE // Deep One gave a value of '1' when he died. 
	IF (CheckFlag(__FLAG_USER_KNOWS_ABOUT_ALOYSIUS) == 2) 
		Conversation
		INTL( 3939, "Stop bothering me. I already gave you the Rod of Mana.")
	ELSE // FLAG is worth 1 
		IF (CheckItem(__OBJ_NOTE_DEEPONE) > 0)
			Conversation
			INTL( 3944, "Ok. Ok. I admit it! I bought the Rod of Mana from the Deep One. So what? "
			"Oh. It was Zhakar's...? I see. But.. you see... I *BOUGHT* this item. "
			"I won't give it back to you unless you pay twice the price I paid... "
			"That will be 32,000 gold pieces. Does that seem fair to you?") 
			SetYesNo(ROD)
		ELSE
			Conversation
			INTL( 3943, "The Deep Ones are a race of humanoids dwelling in a cave near Zhakar's tower.")
		ENDIF	
	ENDIF
ENDIF

Command(INTL( 3945, "ROD OF MANA"))
""
IF (CheckFlag(__FLAG_USER_KNOWS_ABOUT_ALOYSIUS) == 0)
	IF (CheckItem(__OBJ_NOTE_DEEPONE) > 0)
		Conversation
		INTL( 3946, "You have a note saying I bought a stolen item? AH! This note "
		"has been falsified. {The} {Deep} {One's} {note} {instantly} "
		"{crumbles} {into} {dust!}")
		TakeItem(__OBJ_NOTE_DEEPONE)
	ELSE
		Conversation
		INTL( 3947, "What about it? You are wasting valuable time, you know.")
	ENDIF
ELSE // Deep One gave a value of '1' when he died. 
	IF (CheckFlag(__FLAG_USER_KNOWS_ABOUT_ALOYSIUS) == 2) 
		Conversation
		INTL( 3939, "Stop bothering me. I already gave you the Rod of Mana.")
	ELSE // FLAG is worth 1 
		IF (CheckItem(__OBJ_NOTE_DEEPONE) > 0)
			Conversation
			INTL( 3948, "Ok. Ok. I admit it! I bought the Rod of Mana from the Deep One. So what? "
			"Oh. It was Zhakar's...? I see. But.. you see... I *BOUGHT* this item. "
			"I won't give it back to you unless you pay twice the price I paid... "
			"That will be 32,000 gold pieces. Does that seem fair to you?") 
			SetYesNo(ROD)
		ELSE
			Conversation
			INTL( 3949, "You are saying that I paid a Deep One for Zhakar's Rod of Mana? Do you "
			"have a proof to back this up? No? Too bad!")
		ENDIF	
	ENDIF
ENDIF

YES(ROD)
	IF (Gold < 32000) 
		Conversation
		INTL( 2013, "You do not have enough gold pieces.")
	ELSE	
		Conversation
		INTL( 3950, "Ok. Here's the Rod of Mana. Happy now? Now, leave me alone.")
		IF (CheckItem(__OBJ_NOTE_DEEPONE) > 0)
		Conversation
		INTL( 3951, "{The} {Deep} {One's} {note} {instantly} {bursts} {in} {flames!}")
		ENDIF
		;int nNotes = CheckItem(__OBJ_NOTE_DEEPONE); 
      FOR( 0, nNotes )
			TakeItem(__OBJ_NOTE_DEEPONE) 
		ENDFOR
		TakeGold(32000)      
		GiveItem(__OBJ_ROD_OF_MANA)
		GiveFlag(__FLAG_ALOYSIUS_GAVE_ROD, 1) 
		GiveFlag(__FLAG_USER_KNOWS_ABOUT_ALOYSIUS,2)
	ENDIF
NO(ROD)
	Conversation
	INTL( 3952, "Well. Why did you bother me about it then?")
YesNoELSE(ROD)
	Conversation
	INTL( 3953, "I'm getting old and deaf. Was that a yes or a no?")
	SetYesNo(ROD) 


CmdAND(INTL( 3954, "TARANTULA"),INTL( 3955, "EYE"))
""
IF (CheckItem(__OBJ_TARANTULA_EYES) == 0)
	Conversation
	INTL( 3956, "I am always in need of some tarantula eyes for my spells. I'll pay up to 3000 gold pieces per "
	"pair of tarantula eyes!")	
ELSEIF (CheckItem(__OBJ_TARANTULA_EYES) >= 1) 
	Conversation
	FORMAT(INTL( 3957, "%s? You have a pair of tarantula eyes for me?! Great! I will pay you 3000 gold pieces "
	"for this pair of eyes. Do we have a deal?"), USER_NAME)
	SetYesNo(TARANTULA)
ENDIF

YES(TARANTULA)
IF (CheckItem(__OBJ_TARANTULA_EYES) == 0)
	Conversation
	INTL( 3959, "What kind of trick is this? You have no pair of tarantula eyes!")
	BREAK
ELSE
	TakeItem(__OBJ_TARANTULA_EYES) 
	GiveGold(3000)
	Conversation
	INTL( 7123, "Thanks, here is your reward!")	
ENDIF

NO(TARANTULA)
Conversation
INTL( 3962, "Darn it!")

YesNoELSE(TARANTULA)
Conversation
INTL( 3963, "Pardon me but was that a yes or a no?")
SetYesNo(TARANTULA)

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 3964, "I am Aloysius Starbolt, master wizard of this castle.") 

Command3(INTL( 489, "WORK"),INTL( 487, "OCCUPATION"),INTL( 488, "WHAT DO YOU"))
INTL( 3965, "Well, aside from being one of the king's many advisors, I am also a licensed spell-teacher. "
"As a magic user, I often also need some magical components. If you come across "
"some \"tarantula\" \"eyes\", I would gladly buy them from you.")

Command3(INTL( 700, "SPELL"),INTL( 496, "TEACH"),INTL( 495, "LEARN"))
INTL( 7545, "Ahh, finally, I am going to make some money... Oops, uh.. yes, ahem.. let's begin.")
CreateSkillList
	AddTeachSkill (__SPELL_DETECT_HIDDEN, 16, 47425)
	AddTeachSkill (__SPELL_FLAME_WAVE, 18, 60800)
	AddTeachSkill (__SPELL_RESIST_ICE, 20, 79028)
	AddTeachSkill (__SPELL_DETECT_INVISIBLE, 21, 92500)
SendTeachSkillList

Command2(INTL( 3862, "BANE"),INTL( 3863, "BLACKBLOOD"))
INTL( 3989, "Bane Blackblood is a self-centered butcher. He seeks to gain dominion over "
"the Kingdom of Goldmoon and therefore often attempts to end King "
"Theodore's life. In fact, he has created a group of assassins named "
"the \"Nightblades\".")

Command3(INTL( 1072, "KING"),INTL( 754, "THEODORE"),INTL( 3990, "MAJESTY"))
INTL( 3991, "King Theodore is not exactly a competent king but we could have gotten worse..."
"Or could we?")

Command2(INTL( 1492, "DESERT"),INTL( 3865, "VULTURE'S DEN"))
INTL( 3992, "I heard that there is a small oasis located right in the middle.")

Command2(INTL( 994, "KINGDOM"),INTL( 753, "GOLDMOON"))
INTL( 3993, "The Kingdom of Goldmoon is currently ruled by King Theodore XIII.")

Command(INTL( 3844, "NIGHTBLADE"))
INTL( 3994, "The Nightblades are a group of assassins working for \"Bane\".")

Command(INTL( 759, "SPELLBOOK"))
INTL( 3995, "The spellbook is the most precious thing in the life of a wizard.")

Command(INTL( 3854, "RAVENWOOD"))
INTL( 3996, "Ravenwood? Surely you do not want to go there by yourself. Instead, "
"you should travel south to where the \"druids\" are located. The Forest "
"Guardians up there will protect you.")

Command(INTL( 836, "FOREST GUARDIAN"))
INTL( 3997, "Since the Forest Guardians and the druids both share the same concern "
"about nature, it is just fitting that they should hang together.") 

Command(INTL( 746, "DRUID"))
INTL( 3998, "The druids strongly believe in the old ways and I advise you not to "
"harm nature in their presence lest you want to taste their "
"elemental fire blasts.") 

CmdAND3(INTL( 1429, "LIBRARY"),INTL( 3999, "LOST"),INTL( 1381, "KNOWLEDGE"))
INTL( 4000, "The Library of the Lost Knowledge is a mysterious place that has "
"been undisturbed for centuries. We often sought to find its location "
"but stories tell that the Library lies under a sea, south of a tree.")

Command2(INTL( 741, "4TH COMING"),INTL( 1882, "FOURTH COMING"))
INTL( 4001, "I have attempted to find clues on what the future holds but failed "
"miserably in understanding what the prophecies mean.")

Command2(INTL( 4002, "ELYSANA"),INTL( 4003, "BLACKROSE"))
INTL( 4004, "Elysana BlackRose has much more powers than she wants to show. That is "
"a shame that she did not want to ally with the council against our "
"two strongest enemies: \"Bane\" \"Blackblood\" and the \"orcs\".")

Command(INTL( 744, "ORC"))
INTL( 4005, "The orcs combine the sheer strength of their savage warriors, the black "
"magic of their filthy shamans and the might of their \"siege\" \"weapons\". "
"Therefore, they are a serious threat to our \"Kingdom\" and they must be " 
"stopped otherwise they will win.")

CmdAND(INTL( 4006, "SIEGE"),INTL( 914, "WEAPON"))
INTL( 4007, "They are slow to move but they CAN destroy the castle's walls.")

Command(INTL( 3848, "ZHAKAR"))
INTL( 4008, "Zhakar is a powerful wizard and I urge you not to underestimate his "
"abilities. Despite his mental illness, he is still very competent in "
"the arcane arts and is a valuable ally to our cause.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
""
IF (rnd.roll(dice(1, 3)) == 1 ) 
	Conversation
	INTL( 4009, "Well, well. You've learned some pretty words, haven't you? "
    "Have a nice trip, on me!")
	SWITCH(rnd.roll(dice(1, 6) ) )
		CASE(1)
			TELEPORT( 800, 1988, 0)
		ENDCASE	
		CASE(2)
			TELEPORT(742, 2154,0)
		ENDCASE	
		CASE(3)
			TELEPORT(877,2441,0)
		ENDCASE		
		CASE(4)
			TELEPORT(794,2677,0)
		ENDCASE
		CASE(5)
			TELEPORT(927,2884,0)
		ENDCASE
		CASE(6)
			TELEPORT(236,2408,1)	
		ENDCASE
	    ENDSWITCH
		BREAK
ELSE
	Conversation
	INTL( 4010, "That is not a wise thing to say to me considering the fact that I could "
	"obliterate you in a single thought.")
	BREAK
ENDIF

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
FORMAT(INTL( 4011, "Farewell %s!"),USER_NAME) 
BREAK

Default
""
IF (rnd.roll( dice( 1, 2 ) ) == 1)
    Conversation
    INTL( 4012, "Perhaps others would like to know about that.")
ELSE
    Conversation
    INTL( 4013, "Now that is something I did not know.")
ENDIF

EndTalk
}
//////////////////////////////////////////////////////////////////////////////////////////
void AloysiusStarbolt::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL(__SPELL_DETECT_HIDDEN, 16, 47425)
 			TEACH_SKILL(__SPELL_FLAME_WAVE, 18, 60800)
			TEACH_SKILL(__SPELL_RESIST_ICE, 20, 79028)
			TEACH_SKILL(__SPELL_DETECT_INVISIBLE, 21, 92500)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE