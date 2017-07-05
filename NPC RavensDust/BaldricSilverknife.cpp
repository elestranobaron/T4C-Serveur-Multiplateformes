/////////////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "BaldricSilverknife.H"

BaldricSilverknife::BaldricSilverknife()
{}

BaldricSilverknife::~BaldricSilverknife()
{}

extern NPCstructure::NPC Thief;

void BaldricSilverknife::Create( void )
{
      npc = ( Thief );
      SET_NPC_NAME( "[2916]Baldric Silverknife" );  
      npc.InitialPos.X = 1573; 
      npc.InitialPos.Y = 2551;
      npc.InitialPos.world = 0;
}

void BaldricSilverknife::OnTalk( UNIT_FUNC_PROTOTYPE )
/////////////////////////////////////////////////////////////////////////////

{
CONSTANT WORK = 1;
CONSTANT BUYSTUFF = 2;
CONSTANT DRUM = 3;

InitTalk

Begin
""
IF (CheckFlag(__BLACK_MARKET) == 2)
   Conversation
   INTL( 4065, "So, you're the new one in town? I doubt you are as skilled as they say but we shall see that in time "
   "my friend. Come back often to me as I may have \"assignments\" for you someday.") 
ELSEIF (USER_LEVEL >= 28) 
   Conversation
   INTL( 4066, "I have heard of you from my associates in the brigand camp of Arakas.")
ELSE
   Conversation
   INTL( 4067, "Who the hell are you? You're a nobody and I've got nothing to say to you.")
BREAK
ENDIF

Command2(INTL( 2034, "HELLO"), INTL( 2035, " HI "))
INTL( 4068, "Say what you have to say. I do not have time for useless chit-chat with you.")

Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 4069, "I'm known around here as Baldric Silverknife, the part-time \"musician\" "
"and notable thief. Heh! Heh!")

Command(INTL( 4070, "SILVERKNIFE"))
INTL( 4071, "You got that right.")

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
INTL( 4072, "Hmmm, I can tell you for a price. Are you willing to pay?")
SetYesNo(WORK)

YES(WORK)
   IF (CheckFlag(__BALDRIC_FEE_PAID) == 1)
		Conversation
		INTL( 4073, "Er. I already told you. I'm a thief and I steal from the rich as well "
		"as the poor for my own entertainment. Heh! Heh!") 		
	ELSE
	   IF (Gold >= 5000)
			TakeGold( 5000 ) 
			GiveFlag(__BALDRIC_FEE_PAID, 1)
			Conversation
			INTL( 4074, "Very well, you earned it I guess. You could say I'm a thief. I have had years of practice "
			"at \"robbing\" people, and it has brought me great prosperity. Heh, I just now took 5000 "
			"of your gold pieces, but that's just a precaution so that you don't turn me over to the guards.")
		ELSE
			Conversation
			INTL( 4075, "Hmmm, you don't seem to have enough money to pay my fee.")
		ENDIF
	ENDIF

NO(WORK)
	Conversation
	INTL( 4076, "Well, be on your way then!")

YesNoELSE(WORK)
	Conversation
	INTL( 4077, "Make up your mind, will you pay?")
   SetYesNo(WORK)

Command(INTL( 4078, "MUSICIAN"))
INTL( 4079, "Well, I am quite a talented artist. I excell at the flute and "
"the \"drum\" mostly. However, I can assure you that my voice is "
"quite excellent as well.")

Command(INTL( 4080, "DRUM"))
INTL( 4081, "Yes, I enjoy playing the drum. Uhh? You want my drum? For what "
"purpose? You don't know, eh? I betcha that old Thorbin is " 
"up to something. It doesn't bother me at all as he cannot "
"truly understand art as well as I do. And also, I don't mind "
"giving one of my drums as I have plenty of them in store. *smile* "
"Now, let's get down to business. If you want the drum, you'll have "
"to do a little \"something\" for me.")

Command(INTL( 4082, "SOMETHING"))	  
""
IF ((CheckItem(__OBJ_BLOOD_DAGGER) >= 1) && (CheckItem(__OBJ_GLEAMING_SHARD) >= 1))
	Conversation
	INTL( 4083, "Oh, geez! You've found a blood dagger and a gleaming shard? I am "
	"truly impressed by your well hidden talents. Do you want to "
    "give me the blood dagger and the gleaming shard?")
	 SetYesNo(DRUM)
ELSE
	Conversation
	INTL( 4084, " If you can find a gleaming shard and a \"blood\" \"dagger\", then the "
	"drum is yours.")
ENDIF

YES(DRUM)
IF ((CheckItem(__OBJ_BLOOD_DAGGER) >= 1) && (CheckItem(__OBJ_GLEAMING_SHARD) >= 1))
	TakeItem(__OBJ_BLOOD_DAGGER)
	TakeItem(__OBJ_GLEAMING_SHARD)
	GiveItem(__OBJ_BALDRIC_DRUM)
	Conversation
	INTL( 4085, "Here ya go.")
ELSE
	Conversation
	INTL( 4086, "You don't even have the Blood Dagger and the gleaming shard. You "
	"won't fool this thief, that's for sure!")
ENDIF

NO(DRUM)
Conversation
INTL( 4087, "Fine! No lil' drum for you!")

YesNoELSE(DRUM)
Conversation
INTL( 4088, "Hey, I need a clear answer. Is it a yes or a no?")
SetYesNo(DRUM)

Command2(INTL( 4089, "GLEAMING"),INTL( 4090, "SHARD"))
INTL( 4091, "Good luck finding one. I never said it would be easy to get this "
"drum out of me. Heh! Heh!")

Command(INTL( 4092, "PIG"))
""
IF (CheckFlag(__QUEST_KILL_THE_PIGS_COMPLETED) == 0)
   Conversation
   INTL( 4093, "Listen up, buddy! You'll laugh when I tell you the simple task you have "
	"to do for me. You simply have to kill 10 of Rondy's pigs.")	
	GiveFlag(__QUEST_KILL_THE_PIGS_COMPLETED, 1 )
    RemFlag(__FLAG_COUNTER_PIG_KILLED)
ELSEIF (CheckFlag(__QUEST_KILL_THE_PIGS_COMPLETED) == 2)
	Conversation
	INTL( 4094, "I never really liked pigs.")
ELSEIF ((CheckFlag(__QUEST_KILL_THE_PIGS_COMPLETED) == 1) && (CheckFlag(__FLAG_COUNTER_PIG_KILLED) >= 10))
   Conversation
   INTL( 4095, "You did what I asked? Great! That wasn't so hard, was it? Now, "
	"perhaps you're ready for a more serious \"assignment\", eh?")
   GiveFlag(__FLAG_RONDY_HATRED, USER_LEVEL)
   GiveFlag(__QUEST_KILL_THE_PIGS_COMPLETED, 2) 
   RemFlag(__FLAG_COUNTER_PIG_KILLED) 
ELSE
   Conversation
   FORMAT(INTL( 4096, "You've only killed %u pigs. I clearly said to you that you must kill at least 10 of those smelly pests."), CheckFlag( __FLAG_COUNTER_PIG_KILLED ))
ENDIF

Command2(INTL( 495, "LEARN"),INTL( 496, "TEACH"))
INTL( 712, "Very well.")
CreateSkillList
	AddTeachSkill( __SKILL_PEEK, 1, 500 )
	AddTeachSkill( __SKILL_ROB, 1, 5000 )
SendTeachSkillList

Command(INTL( 502, "TRAIN"))
INTL( 4106, "Very well then.") 
CreateSkillList
	AddTrainSkill( __SKILL_DODGE, 5000, 10 )
	AddTrainSkill( __SKILL_ARCHERY, 5000, 15 )
	AddTrainSkill( __SKILL_PEEK, 100, 25 )
	AddTrainSkill( __SKILL_ROB, 100, 250 )
SendTrainSkillList
  
Command(INTL( 1573, "ROBBING"))
INTL( 7546, "Well, that's not all I do, but let's face it, it's fun isn't it? heh. I suppose I could \"teach\" you how if you ask "
"me really nicely.")

Command(INTL( 4110, "ASSIGNMENT"))
""
IF(CheckFlag(__QUEST_KILL_THE_PIGS_COMPLETED) == 2)
	IF (CheckFlag(__QUEST_BALDRIC_SILVERKNIFE) == 0)
		Conversation
		INTL( 4111, "Hmmm. Perhaps I have something for you. Meet \"Doremas\" and ask him if his low-life "
		"friend \"Grimish\" has what I require.")
	ELSEIF (CheckFlag(__QUEST_BALDRIC_SILVERKNIFE) == 1)
		Conversation
		INTL( 4112, "I am still waiting.")
	ELSEIF(CheckFlag(__QUEST_BALDRIC_SILVERKNIFE) == 2) 
		Conversation
		INTL( 4113, "Thank you for your help.")
	ELSE
		Conversation
		INTL( 4113, "Thank you for your help.")
	ENDIF			
ELSE
	Conversation
	INTL( 4114, "Let's see what we have murder... stealing... spying... Ah! "
	"I have the perfect assignment for you! Are you up to "
	"some \"pig\" butchering? Heh! Heh!")
ENDIF

Command(INTL( 4115, "GRIMISH"))
INTL( 4116, "Grimish is a goblin and I hate goblins. That's why I leave a fool like \"Doremas\" "
"to deal with him.")

Command(INTL( 4117, "DOREMAS"))
INTL( 4118, "Doremas is but a fool. However, I find him useful at times. That's probably why I didn't "
"cut his throat open.. for the time being anyways.")

Command(INTL( 4119, "ALLIANCE IS RENEWED"))
""
IF (CheckFlag(__QUEST_BALDRIC_SILVERKNIFE) == 0) 
	Conversation
    INTL( 4120, "You're barely making sense. Have you been drinking at Thorbin's filthy tavern or what? "
    "If so, you'll have to sober up before talking to me again.") 
ELSEIF (CheckFlag(__QUEST_BALDRIC_SILVERKNIFE) == 1)
	Conversation
	INTL( 4121, "This is the password brought by Doremas's lame friend? Good. It means that the "
	"alliance with \"Blackblood\" is still intact. This is great news indeed that "
   "you've brought me. Perhaps you should consider working for Blackblood. "
   "He pays well... or he kills you. I guess it depends on his mood, uh? {You} "
   "{have} {been} {awarded} {70000} {experience} {points.} ")
   GiveXP(70000)
	GiveFlag(__QUEST_BALDRIC_SILVERKNIFE, 2)
ELSEIF (CheckFlag(__QUEST_BALDRIC_SILVERKNIFE) == 2)
	Conversation
	INTL( 4122, "Thank you again for your help.")
ELSE
	Conversation
	INTL( 4122, "Thank you again for your help.")
ENDIF

Command(INTL( 4123, " YES "))
INTL( 798, "Yeah, whatever.")

Command(INTL( 4124, "POISON")) 
INTL( 4125, "I'm a thief, not an assassin. The only person in town I would think who "
"has the poison lore knowledge would be Elysana Blackrose. Stay out of "
"troubles and remember... I've never seen you.")

Command2(INTL( 4002, "ELYSANA"),INTL( 4003, "BLACKROSE"))
INTL( 4126, "She is a witch.")

Command2(INTL( 3863, "BLACKBLOOD"),INTL( 3862, "BANE"))
INTL( 4127, "Shhh! If the town guards hear you say his name, you will find yourself spending the "
"remaining of your life in the \"prison\" of Silversky.")

Command2(INTL( 4128, "BLOOD"),INTL( 4129, "DAGGER"))
INTL( 4130, "I think Lord Bane has some but you'd be foolish to steal "
"one from him nor do I want to be associated with you if you do "
"such a thing.")

Command(INTL( 4131, "PRISON"))
INTL( 4132, "Sure ain't a nice place.")

Command(INTL( 4133, " ORDER ")) 
INTL( 4134, "If you insist, I will tell you what I know but you must keep your voice low "
"lest we want to get caught and executed by the royal guards for treason. "
"\"Blackblood\" is the leader of the \"Nightblades\".")

Command(INTL( 3844, "NIGHTBLADE"))
INTL( 4135, "The Nightblades are a \"group\" of assassins recruited and trained by "
"Blackblood himself. They combine the swift death of a dagger covered with "
"lethal poison and the various offensive spells, they are the best assassins "
"you will find around.")

Command(INTL( 4136, "GROUP"))
INTL( 4137, "To be able to enter into their organization, one must do the Test. Only "
"those who succeed are accepted. I never did the Test thus I cannot really say "
"what it is exactly. Only \"Blackblood\" knows. The \"Nightblades\" have sworn "
"on their life and soul that they will never give any information regarding the "
"Test to anyone.")

Command(INTL( 4138, "TEST"))
INTL( 4139, "How should I know? Ask a Nightblade.") 

Command2(INTL( 3865, "VULTURE'S DEN"),INTL( 1492, "DESERT"))
INTL( 4140, "\"Kalir\" and \"Jamar\" are often wandering in the desert. Quite frankly, I "
"do not have a clue how they do it or for what purpose.")

Command2(INTL( 4142, "KALIR"),INTL( 5255, "JAMAR"))
INTL( 4144, "Kalir and Jamir are both fools.")

Command(INTL( 3848, "ZHAKAR"))
INTL( 4141, "Zhakar is an insane old wizard who lives secluded in his tower.")
											
Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 2461, "Out of my face!")
IF (Gold >= 100)
   TakeGold( rnd.roll( dice( 2, 50 ) ) ) 
ENDIF
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 520, "QUIT"))
INTL( 4145, "Remember... no noise, no guards.")
BREAK

Default
""
IF (rnd.roll( dice( 1, 2 ) ) == 1)
   Conversation
   INTL( 4012, "Perhaps others would like to know about that.")
ELSE
   Conversation
   INTL( 4146, "I wouldn't talk about this here if I were you.")
ENDIF

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void BaldricSilverknife::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Rolph data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL( __SKILL_PEEK, 1, 500 )
         TEACH_SKILL( __SKILL_ROB, 1, 5000 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

	NPC_DATA_TRAIN
		TRAIN_SKILL( __SKILL_DODGE, 5000, 10 )
		TRAIN_SKILL( __SKILL_ARCHERY, 5000, 15 )
		TRAIN_SKILL( __SKILL_PEEK, 100, 25 )
		TRAIN_SKILL( __SKILL_ROB, 100, 250 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
}
