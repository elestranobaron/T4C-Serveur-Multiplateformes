//////////////////////////////////////////////////////////////////////
// Xanth.cpp: implementation of the Etheanan class.
//////////////////////////////////////////////////////////////////////
#pragma hdrstop
#include "Xanth.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Xanth::Xanth()
{}

Xanth::~Xanth()
{}

extern NPCstructure::NPC Mage;

void Xanth::Create( ){
	npc = Mage;
	SET_NPC_NAME( "[2992]A blind man" );
	npc.InitialPos.X = 690; 
	npc.InitialPos.Y = 1610;
	npc.InitialPos.world = 2;
}

void Xanth::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT APPRENTICE = 1;
CONSTANT TUTELAGE = 2;
CONSTANT FOULPOTIONS = 3;
CONSTANT MAKEFOULPOTION = 4;
CONSTANT Ring = 5;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_ARAKNOR_APPRENTICE) == 1)
	Conversation
	INTL( 3781, "Who goes there? ...I do not know your steps, but I can sense a trace of the dark arts "
	"flowing within you... are you one of Araknor's apprentices?")
	SetYesNo(APPRENTICE)
ELSEIF(CheckFlag(__FLAG_ARAKNOR_APPRENTICE) == 2)
	Conversation
	FORMAT(INTL( 3782, "Ahh, %s, you have returned."), USER_NAME)
ELSEIF(CheckFlag(__FLAG_ARAKNOR_APPRENTICE) == 3)
	Conversation
	FORMAT(INTL( 3783, "Ahh, I feel a considerable amount of power emanating from within you. You are well on your "
	"way to reaching your full potential, %s!"), USER_NAME)
ELSE
	Conversation
	INTL( 3784, "Who goes there? ...I do not know your steps. You must be one of those wretches that live in that "
	"pitiful rat hole they call Silversky.")
ENDIF

YES(APPRENTICE)
	GiveFlag(__FLAG_ARAKNOR_APPRENTICE, 2)
	Conversation
	INTL( 3785, "Yes, I thought I could feel as much. Have you come here seeking my tutelage?")
	SetYesNo(TUTELAGE)
NO(APPRENTICE)
	Conversation
	INTL( 3786, "That is very strange... I have no time to waste with you then.")
	BREAK
YesNoELSE(APPRENTICE)
	Conversation
	INTL( 3787, "Are you one of Araknor's apprentices?")
	SetYesNo(APPRENTICE)

Command(INTL( 9111, "FOUL POTION"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckItem(__OBJ_ESSENCE_OF_BLOODLUST) >= 1 && CheckItem(__OBJ_NECROMANTIC_SCROLL) >= 2)
		Conversation
		INTL( 10159, "If you have gathered all the necessary elements, you can hand them over to me and I will combine them right away. Do "
		"you want me to make a foul potion now?")
		SetYesNo(MAKEFOULPOTION)
	ELSE
		Conversation
		INTL( 10160, "You must be in great need to come all the way here asking me for help. I will have you know I have not forgotten the debt you "
		"owe me, but now is not yet the time for me to collect it. Now then, back to the matter at hand. You require some foul potions, do "
		"you not?")
		SetYesNo(FOULPOTIONS)
	ENDIF
ELSE
	Conversation
	INTL( 10161, "I have nothing more to say to you.")
	BREAK
ENDIF

YES(FOULPOTIONS)
	Conversation
	INTL( 10162, "Very well. To make a foul potion, I will require 2 \"necromantic\" \"scrolls\", a \"bloodied\" \"rat\" \"pelt\" and the \"essence\" "
	"of a creature known as \"Bloodlust\". Fortunately for you, I have all the bloodied rat pelts I will ever need, so you need only "
	"gather the remaining two elements. Oh, there is also the matter of a certain fee of 25000 gold. I'm sure it is nothing for someone "
	"like you.")
NO(FOULPOTIONS)
	Conversation
	INTL( 10163, "Really? I must have misunderstood then. What is it you want?")
YesNoELSE(FOULPOTIONS)
	Conversation
	INTL( 10164, "Do you require some foul potions or not?")
	SetYesNo(FOULPOTIONS)

YES(MAKEFOULPOTION)
	IF(CheckItem(__OBJ_ESSENCE_OF_BLOODLUST) >= 1)
		IF(CheckItem(__OBJ_NECROMANTIC_SCROLL) >= 2)
			IF(Gold >= 25000)
				TakeItem(__OBJ_ESSENCE_OF_BLOODLUST)
				TakeItem(__OBJ_NECROMANTIC_SCROLL)
				TakeItem(__OBJ_NECROMANTIC_SCROLL)
				TakeGold(25000)
				GiveItem(__OBJ_FOUL_POTION)
				PRIVATE_SYSTEM_MESSAGE(INTL( 10165, "You give the essence of Bloodlust and 2 necromantic scrolls to Xanth."))
				PRIVATE_SYSTEM_MESSAGE(INTL( 10166, "You give 25000 gold to Xanth."))
				Conversation
				INTL( 10167, "Now then, this will only take a few seconds... ")
				PRIVATE_SYSTEM_MESSAGE(INTL( 10168, "Xanth works deftly with his hands and combines the materials to create a foul potion."))
				Conversation
				INTL( 10169, "and here you go. ")
				PRIVATE_SYSTEM_MESSAGE(INTL( 10170, "Xanth gives you a foul potion."))
				Conversation
				INTL( 10171, "Now then, did you want me to make you another potion?")
				SetYesNo(MAKEFOULPOTION)
			ELSE
				Conversation
				INTL( 10172, "Are you certain you have enough gold to pay the fee I ask? I might be blind, but I am not an idiot. Return when "
				"you have at least 25000 gold to pay for my services. You would think one debt is enough.")
			ENDIF
		ELSE
			Conversation
			INTL( 10173, "Are you certain you have everything that is needed? I told you I require 2 necromantic scrolls and the essence of Bloodlust "
			"combined with my bloodied rat pelts to make a foul potion. Return when you have gathered these things.")
		ENDIF
	ELSE
		Conversation
		INTL( 10174, "Are you certain you have everything that is needed? I told you I require 2 necromantic scrolls and the essence of Bloodlust "
		"combined with my bloodied rat pelts to make a foul potion. Return when you have gathered these things.")
	ENDIF
NO(MAKEFOULPOTION)
	Conversation
	INTL( 10175, "I see, then what is it that you want?")
YesNoELSE(MAKEFOULPOTION)
	Conversation
	INTL( 10176, "Do you want me to make a foul potion or not?")
	SetYesNo(MAKEFOULPOTION)

CmdAND(INTL( 10177, "NECROMANTIC"), INTL( 1159, "SCROLL"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 10178, "I usually some of these in my supplies, but unfortunately I don't have any right now. I could make some but I am rather busy. "
	"I know one who might be able to help you though, and you know him as well. Travel to Arakas to find Araknor and ask him if he "
	"has any.")
ELSE
	Conversation
	INTL( 10161, "I have nothing more to say to you.")
	BREAK
ENDIF

CmdAND3(INTL( 10179, "BLOODIED"), INTL( 5187, "RAT"), INTL( 10180, "PELT"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 10181, "You need not worry about finding these, I have plenty in storage.")
ELSE
	Conversation
	INTL( 10161, "I have nothing more to say to you.")
	BREAK
ENDIF

Command2(INTL( 10112, "ESSENCE"), INTL( 8754, "BLOODLUST"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 10182, "Bloodlust is a blood-sucking giant worm rumored to reside somewhere on the southern part of the island of Stoneheim. Few people "
	"have ever seen it, and even fewer have lived to tell the tale.")
ELSE
	Conversation
	INTL( 10161, "I have nothing more to say to you.")
	BREAK
ENDIF

Command(INTL( 8039, "RING"))
""
IF(CheckFlag(__FLAG_QUEST_FOR_BONES) == 6)
	Conversation
	INTL( 10183, "You want me to see if I can find anything useful about this ring? Very well... hmm, this is very strange. I believe I have "
	"been in contact with this ring before. If I am not mistaken, it might belong to someone I know. Would you like to know who "
	"that is?")
	SetYesNo(Ring)
ELSEIF(CheckFlag(__FLAG_QUEST_FOR_BONES) == 7)
	IF(CheckItem(__OBJ_ESSENCE_OF_BLOODLUST) >= 1 && CheckItem(__OBJ_BLOODSTONE_RING) >= 1)
		Conversation
		INTL( 10184, "Have you brought the objects I requested? Ahh splendid! I will take these off your hands and tell you what you desire. ")
		;int nNumEssenceOfBloodLust = CheckItem(__OBJ_ESSENCE_OF_BLOODLUST);
		FOR(0, nNumEssenceOfBloodLust) 
			TakeItem(__OBJ_ESSENCE_OF_BLOODLUST)
		ENDFOR
		;int nNumBloodstoneRing = CheckItem(__OBJ_BLOODSTONE_RING);
		FOR(0, nNumBloodstoneRing)
			TakeItem(__OBJ_BLOODSTONE_RING)
		ENDFOR
		PRIVATE_SYSTEM_MESSAGE(INTL( 10185, "You give Xanth all your bloodstone rings and your essence of Bloodlust."))
		GiveFlag(__FLAG_USER_KNOWS_MORDENTHAL_HAS_BONES, 1)
		Conversation
		INTL( 10186, "Now then, the person I distinctly remember wearing this ring is none other than my old mentor, Mordenthal.")
	ELSE
		Conversation
		INTL( 10187, "I will tell you who I think the ring belongs to if you bring me more of the essence of Bloodlust, as well as anything "
		"else you might find on the thing's corpse.")
	ENDIF
ELSE
	Conversation
	INTL( 10161, "I have nothing more to say to you.")
	BREAK
ENDIF

YES(Ring)
	Conversation
	INTL( 10188, "Very well. I have become most interested in this Bloodlust creature since you last brought me its essence. Bring me more "
	"of this essence and anything else you might find on this creature's corpse and I will gladly tell you what you need to know.")
	GiveFlag(__FLAG_QUEST_FOR_BONES, 7)
NO(Ring)
	Conversation
	INTL( 10189, "Very well, I will not argue with you.")
YesNoELSE(Ring)
	Conversation
	INTL( 10190, "Would you like to know who I think the ring belongs to?")
	SetYesNo(Ring)

Command(INTL( 3694, " NAME"))
INTL( 3788, "If you do not know my name, then you have no business here!")

Command(INTL( 489, "WORK"))
INTL( 3789, "That is none of your concerns.")

Command(INTL( 3744, "XANTH"))
""
IF(CheckItem(__OBJ_LETTER_FROM_DAMIEN_TO_XANTH) == 1)
	Conversation
	INTL( 3790, "So you have a letter for me, is that right? Give it to me then. {Xanth} {runs} {his} {fingers} {over} "
	"{the} {scroll}. I see, so you would have me enchant this blade of yours eh? I would have you know that "
	"this small service will not be without a \"price\".")	
ELSEIF(CheckFlag(__FLAG_ARAKNOR_APPRENTICE) >= 1)
	Conversation
	INTL( 3791, "Ahh, so you come here seeking my tutelage, is that it?")
	SetYesNo(TUTELAGE)
ELSE
	Conversation
	INTL( 3792, "I don't know how you came about knowing my identity, but if you value your life, you'll soon forget it!")
	BREAK
ENDIF


Command2(INTL( 495, "LEARN"), INTL( 496, "TEACH"))
""
IF(CheckFlag(__FLAG_ARAKNOR_APPRENTICE) >= 2)
	Conversation
	INTL( 7560, "Hmm, yes well, perhaps I can take some time to instruct you in the dark arts.")
	CreateSkillList
		AddTeachSkill (__SPELL_DRAIN_LIFE, 19, 22057)
		AddTeachSkill (__SPELL_PLAGUE, 24, 42537)
		AddTeachSkill (__SPELL_GREATER_DRAIN, 28, 63673)
	SendTeachSkillList
ELSE
	Conversation
	INTL( 3807, "I have more important things to do than to listen to your ramblings.")
ENDIF

YES(TUTELAGE)
	GiveFlag(__FLAG_ARAKNOR_APPRENTICE, 2)
	Conversation
	INTL( 7560, "Hmm, yes well, perhaps I can take some time to instruct you in the dark arts.")
	CreateSkillList
		AddTeachSkill (__SPELL_DRAIN_LIFE, 19, 22057)
		AddTeachSkill (__SPELL_PLAGUE, 24, 42537)
		AddTeachSkill (__SPELL_GREATER_DRAIN, 28, 63673)
	SendTeachSkillList
NO(TUTELAGE)
	IF(CheckItem(__OBJ_LETTER_FROM_DAMIEN_TO_XANTH) >= 1)
		IF (CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 3)
			Conversation
			INTL( 7224, "Then what is it you want?")
		ELSE
			Conversation
			INTL( 3801, "So you have a letter for me, is that right? Give it to me then. {Xanth} {runs} {his} {fingers} {over} "
			"{the} {scroll}. I see, so you would have me enchant this blade of yours eh? I would have you know that "
			"this small service will not be without a \"price\".")	
		ENDIF
	ELSE
		Conversation
		INTL( 3802, "Then you have no business here.")
	ENDIF
YesNoELSE(TUTELAGE)
	Conversation
	INTL( 3803, "Are you here seeking my tutelage?")
	SetYesNo(TUTELAGE)

Command(INTL( 3746, "PRICE"))
""
IF(CheckItem(__OBJ_LETTER_FROM_DAMIEN_TO_XANTH) >= 1)
	Conversation
	INTL( 3804, "Well, there is nothing that I have need for right now, but I will think of something. You will need my "
	"services again sometime in the future, and when you do, I will have devised a way for you to repay me. ")
	IF(CheckItem(__OBJ_BLADE_OF_RUIN) >= 1)
		;int nNumLetters = CheckItem(__OBJ_LETTER_FROM_DAMIEN_TO_XANTH); 
		FOR(0, nNumLetters)			
			TakeItem(__OBJ_LETTER_FROM_DAMIEN_TO_XANTH)
		ENDFOR
		TakeItem(__OBJ_BLADE_OF_RUIN)
		GiveItem(__OBJ_ELVENBANE)
		IF (CheckFlag(__QUEST_DAMIEN_SUBPLOT) == 2)
			GiveFlag(__QUEST_DAMIEN_SUBPLOT,3)
		ENDIF
		Conversation
		INTL( 3805, "With that said, give me the blade. {Xanth} {takes} {the} {Blade} {of} {Ruin}. Yes, I believe this will do. "
		"{Xanth} {performs} {the} {ritual} {that} {will} {enchant} {the} {blade} {with} {unholy} {powers.} I am done. "
		"Behold! I give you Elvenbane! With this blade, you should be able to defeat Shadeen without too much trouble. "
		"Oh and remember what I said earlier... the paths of our lives will cross again, at which time you will repay "
		"the debt you owe me.")
	ELSE
		Conversation
		INTL( 3806, "With that said, give me the blade. What? What do you mean you don't have it? You come here asking me to enchant "
		"a blade in order to kill Shadeen and yet you do not even have such a blade! Incompetent fool! This discussion is "
		"over!")		
	ENDIF
ELSE
	Conversation
	INTL( 3807, "I have more important things to do than to listen to your ramblings.")
ENDIF

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 1075, "Farewell.")
BREAK

Default
INTL( 3807, "I have more important things to do than to listen to your ramblings.")

EndTalk

}
//////////////////////////////////////////////////////////////////////////////////////////
void Xanth::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
         TEACH_SKILL(__SPELL_DRAIN_LIFE, 19, 22057)
			TEACH_SKILL(__SPELL_PLAGUE, 24, 42537)
         TEACH_SKILL(__SPELL_GREATER_DRAIN, 28, 63673)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE