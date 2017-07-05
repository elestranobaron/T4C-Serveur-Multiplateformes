#pragma hdrstop
#include "Khimtesar.h"

Khimtesar::Khimtesar()
{}

Khimtesar::~Khimtesar()
{}

extern NPCstructure::NPC KhimtesarNPC;

void Khimtesar::Create( ){
    npc = KhimtesarNPC;
    SET_NPC_NAME( "[10868]A healthy-looking old man" );
    npc.InitialPos.X = 1105;
    npc.InitialPos.Y = 265;
    npc.InitialPos.world = 0;
}

void Khimtesar::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT BRIGHTONE = 1;
CONSTANT EXPERIMENT = 2;
CONSTANT HEARMORE = 3;
CONSTANT SUNKENWOODSGATEWAY = 4;
CONSTANT LIGHTHAVENGATEWAY = 5;
CONSTANT WINDHOWLGATEWAY = 6;
CONSTANT DRUIDSPOINTGATEWAY = 7;
CONSTANT SILVERSKYGATEWAY = 8;
CONSTANT WIZARDSVALEGATEWAY = 9;
CONSTANT STONECRESTGATEWAY = 10;

InitTalk

Begin
INTL( 8976, "Yes? What can I do for you?")

Command(INTL( 5210, "NOTHING"))
INTL( 8977, "Well then why are you here? I have much to do, you know.")
	
Command2(INTL( 3694, " NAME"),INTL( 485, "WHO ARE YOU"))
""
SWITCH(rnd.roll(dice(1,3)))
	CASE(1)
		Conversation
		INTL( 8978, "I am known as Khimtesar, but you can call me old Kim.")
	ENDCASE
	CASE(2)
		Conversation
		INTL( 8979, "What was that name again? Oh yes, I remember now... it was Khimtesar!")
	ENDCASE
	CASE(3)
		Conversation
		INTL( 8980, "My name? Hmm, let me think... Ahh, it's been awhile since anyone has called me that, but the name's Khimtesar.")
	ENDCASE
ENDSWITCH

Command(INTL( 8981, "OLD KIM"))
INTL( 8982, "That's right! You're a bright one aren't you?")
SetYesNo(BRIGHTONE)

YES(BRIGHTONE)
	Conversation
	INTL( 8983, "That's what I thought too. Say, how would you like to help me experiment with my new spells?")
	SetYesNo(EXPERIMENT)
NO(BRIGHTONE)
	Conversation
	INTL( 8984, "What a pity, I could've used someone like you.")
YesNoELSE(BRIGHTONE)
	Conversation
	INTL( 2580, "Is that so?")

YES(EXPERIMENT)
	Conversation
	INTL( 8985, "Well, before you agree, I'll tell you a bit more of what kind of research I'm doing all the way out here. "
	"You see, I didn't select this location randomly. This whole forest is set on top of a natural maze of underground "
	"caverns. If you are not careful while walking outside, you can suddenly fall through the grass and find yourself "
	"trapped underground. For this reason, these woods are called the Sunken Woods. Now where was I? Oh yes, you see, very "
	"closeby is a special location, a nexus of mana if you will, where mana currents converge. I have been able to tap "
	"into this convergence and have created a new type of spell... which I have conveniently called gateways. Oh, I'm "
	"terribly sorry, I got caught up	in my excitement. You're probably already sorry you ever agreed to help me, aren't you? "
	"Would you like to hear more?")
	SetYesNo(HEARMORE)
NO(EXPERIMENT)
	Conversation
	INTL( 8986, "That's too bad. Oh well, I'll just get back to my research if you don't mind then. You can see yourself out when you're "
	"ready to leave.")
YesNoELSE(EXPERIMENT)
	Conversation
	INTL( 8987, "Well? Are you going to help me or not?")
	SetYesNo(EXPERIMENT)

YES(HEARMORE)
	Conversation
	INTL( 8988, "Good. As I was saying, I have been able to locate 7 different nexus and I have tapped into each of them. Coincidentally, "
	"at every nexus I have found, there was always a certain formation of stones surrounding the focal point of the convergence. "
	"I know not what these stones are there for, but one can speculate that they were erected as a ward of some kind. I will not go "
	"into the details now. What I require now is for someone to simple learn these \"spells\" and test them out.")
NO(HEARMORE)
	Conversation
	INTL( 8989, "Yes, as I was saying, I have been able to... did you say no? Hmm, I guess there is nothing to be done about it. If there is "
	"nothing else then, I must be returning to my research now.")
YesNoELSE(HEARMORE)
	Conversation
	INTL( 8990, "I'm sorry, I seem to have misunderstood. Did you say you wanted me to continue?")
	SetYesNo(HEARMORE)

Command(INTL( 8991, "VENADAR"))
INTL( 8992, "I have not heard that name in a long time...")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8993, "I am a scholar of the arcane art. I spend most of the time I have reading "
"large tomes of magic.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "),)
INTL( 8994, "I will not tolerate this kind of abusive language. I am taking half of your gold as punishment!")
TakeGold(Gold/2)

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
INTL( 8995, "At last, I can return to my studies.")
BREAK

Command2(INTL( 10475, "LEARN"), INTL( 7074, "SPELLS"))
INTL( 8996, "Ahh, so you come here seeking my help as a scholar of the magic arts, is that it? Very well then, I will teach "
"you what my research has taught me. If you did not already know, there are currently seven destinations for the gateway spells. "
"These are \"Lighthaven\" \"gateway\", \"Windhowl\" \"gateway\", \"Druid's\" \"Point\" \"gateway\", \"Silversky\" \"gateway\", \"Wizard's\" \"Vale\" \"gateway\", \"Stonecrest\" \"gateway\" and \"Sunken\" "
"\"Woods\" \"gateway\". As a small note, the \"Sunken\" \"Woods\" \"gateway\" spell will bring you near this place. Now then, which spell "
"would you like to learn?")

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// SUNKEN WOODS GATEWAY //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CmdAND3(INTL( 9013, "SUNKEN"), INTL( 9014, "WOODS"), INTL( 9015, "GATEWAY"))
INTL( 9016, "The Sunken Woods gateway spell opens a doorway that allows the caster to instantly travel to a pre-established location "
"inside the Sunken Woods forest, which happens to be right behind my house. To learn this spell, you must have "
"knowledge of the word of recall spell. Do you wish to learn the Sunken Woods gateway spell?")
SetYesNo(SUNKENWOODSGATEWAY)

YES(SUNKENWOODSGATEWAY)
	;const int nLEVEL = 70;
	const int nINT = 86;
	const int nWIS = 84;
	IF( UserSkill(__SPELL_SUNKEN_WOODS_GATEWAY) == 0 )
		IF( USER_LEVEL < nLEVEL)
			IF( USER_TRUE_INT < nINT )
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9017, "You need %u more levels, %u more intelligence and %u more wisdom to learn the Sunken Woods gateway spell."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9018, "You need %u more levels and %u more intelligence to learn the Sunken Woods gateway spell."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT )
				ENDIF
			ELSE
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9019, "You need %u more levels and %u more wisdom to learn the Sunken Woods gateway spell."), nLEVEL - USER_LEVEL, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9020, "You need %u more levels to learn the Sunken Woods gateway spell."), nLEVEL - USER_LEVEL )
				ENDIF
			ENDIF
		ELSE
			IF( USER_TRUE_INT < nINT )
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9021, "You need %u more intelligence and %u more wisdom to learn the Sunken Woods gateway spell."), nINT - USER_TRUE_INT, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9022, "You need %u more intelligence to learn the Sunken Woods gateway spell."), nINT - USER_TRUE_INT )
				ENDIF
			ELSE
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9023, "You need %u more wisdom to learn the Sunken Woods gateway spell."), nWIS - USER_TRUE_WIS )
				ELSE
					IF( UserSkill(__SPELL_WORD_OF_RECALL) == 0 )
						Conversation
						INTL( 9024, "The Sunken Woods gateway spell is beyond your control. First master the use of the word of recall "
						"spell, then I can teach it to you.")
					ELSE
						Conversation
						INTL( 712, "Very well.")
						CreateSkillList
							AddTeachSkill (__SPELL_SUNKEN_WOODS_GATEWAY, 5, 175700)
						SendTeachSkillList
					ENDIF
				ENDIF
			ENDIF
		ENDIF
	ELSE
		Conversation
		INTL( 9025, "You have already learned the Sunken Woods gateway spell.")
	ENDIF
NO(SUNKENWOODSGATEWAY)
	Conversation
	INTL( 1174, "That is too bad.")
YesNoELSE(SUNKENWOODSGATEWAY)
	Conversation
	INTL( 715, "Do you wish to learn it now?")
	SetYesNo(SUNKENWOODSGATEWAY)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// LIGHTHAVEN GATEWAY ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
CmdAND(INTL( 513, "LIGHTHAVEN"), INTL( 9015, "GATEWAY"))
INTL( 9026, "The Lighthaven gateway spell opens a doorway that allows the caster to instantly travel to a pre-established location "
"in the viscinity of the town of Lighthaven. To learn this spell, you must have knowledge of the word of recall spell. "
"Do you still wish to learn it?")
SetYesNo(LIGHTHAVENGATEWAY)

YES(LIGHTHAVENGATEWAY)
	;const int nLEVEL = 70;
	const int nINT = 86;
	const int nWIS = 84;
	IF( UserSkill(__SPELL_LIGHTHAVEN_GATEWAY) == 0 )
		IF( USER_LEVEL < nLEVEL)
			IF( USER_TRUE_INT < nINT )
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9027, "You need %u more levels, %u more intelligence and %u more wisdom to learn the Lighthaven gateway spell."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9028, "You need %u more levels and %u more intelligence to learn the Lighthaven gateway spell."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT )
				ENDIF
			ELSE
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9029, "You need %u more levels and %u more wisdom to learn the Lighthaven gateway spell."), nLEVEL - USER_LEVEL, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9030, "You need %u more levels to learn the Lighthaven gateway spell."), nLEVEL - USER_LEVEL )
				ENDIF
			ENDIF
		ELSE
			IF( USER_TRUE_INT < nINT )
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9031, "You need %u more intelligence and %u more wisdom to learn the Lighthaven gateway spell."), nINT - USER_TRUE_INT, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9032, "You need %u more intelligence to learn the Lighthaven gateway spell."), nINT - USER_TRUE_INT )
				ENDIF
			ELSE
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9033, "You need %u more wisdom to learn the Lighthaven gateway spell."), nWIS - USER_TRUE_WIS )
				ELSE
					IF( UserSkill(__SPELL_WORD_OF_RECALL) == 0 )
						Conversation
						INTL( 9034, "The Lighthaven gateway spell is beyond your control. First master the use of the word of recall "
						"spell, then I can teach it to you.")
					ELSE
						Conversation
						INTL( 712, "Very well.")
						CreateSkillList
							AddTeachSkill (__SPELL_LIGHTHAVEN_GATEWAY, 5, 175700)
						SendTeachSkillList
					ENDIF
				ENDIF
			ENDIF
		ENDIF
	ELSE
		Conversation
		INTL( 9035, "You have already learned the Lighthaven gateway spell.")
	ENDIF
NO(LIGHTHAVENGATEWAY)
	Conversation
	INTL( 1174, "That is too bad.")
YesNoELSE(LIGHTHAVENGATEWAY)
	Conversation
	INTL( 715, "Do you wish to learn it now?")
	SetYesNo(LIGHTHAVENGATEWAY)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// WINDHOWL GATEWAY ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
CmdAND(INTL( 514, "WINDHOWL"), INTL( 9015, "GATEWAY"))
INTL( 9036, "The Windhowl gateway spell opens a doorway that allows the caster to instantly travel to a pre-established location "
"in the viscinity of the town of Windhowl. To learn this spell, you must have knowledge of the word of recall spell. "
"Do you still wish to learn it?")
SetYesNo(WINDHOWLGATEWAY)

YES(WINDHOWLGATEWAY)
	;const int nLEVEL = 70;
	const int nINT = 86;
	const int nWIS = 84;
	IF( UserSkill(__SPELL_WINDHOWL_GATEWAY) == 0 )
		IF( USER_LEVEL < nLEVEL)
			IF( USER_TRUE_INT < nINT )
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9037, "You need %u more levels, %u more intelligence and %u more wisdom to learn the Windhowl gateway spell."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9038, "You need %u more levels and %u more intelligence to learn the Windhowl gateway spell."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT )
				ENDIF
			ELSE
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9039, "You need %u more levels and %u more wisdom to learn the Windhowl gateway spell."), nLEVEL - USER_LEVEL, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9040, "You need %u more levels to learn the Windhowl gateway spell."), nLEVEL - USER_LEVEL )
				ENDIF
			ENDIF
		ELSE
			IF( USER_TRUE_INT < nINT )
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9041, "You need %u more intelligence and %u more wisdom to learn the Windhowl gateway spell."), nINT - USER_TRUE_INT, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9042, "You need %u more intelligence to learn the Windhowl gateway spell."), nINT - USER_TRUE_INT )
				ENDIF
			ELSE
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9043, "You need %u more wisdom to learn the Windhowl gateway spell."), nWIS - USER_TRUE_WIS )
				ELSE
					IF( UserSkill(__SPELL_WORD_OF_RECALL) == 0 )
						Conversation
						INTL( 9044, "The Windhowl gateway spell is beyond your control. First master the use of the word of recall "
						"spell, then I can teach it to you.")
					ELSE
						Conversation
						INTL( 712, "Very well.")
						CreateSkillList
							AddTeachSkill (__SPELL_WINDHOWL_GATEWAY, 5, 175700)
						SendTeachSkillList
					ENDIF
				ENDIF
			ENDIF
		ENDIF
	ELSE
		Conversation
		INTL( 9045, "You have already learned the Windhowl gateway spell.")
	ENDIF
NO(WINDHOWLGATEWAY)
	Conversation
	INTL( 1174, "That is too bad.")
YesNoELSE(WINDHOWLGATEWAY)
	Conversation
	INTL( 715, "Do you wish to learn it now?")
	SetYesNo(WINDHOWLGATEWAY)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// SILVERSKY GATEWAY ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
CmdAND(INTL( 998, "SILVERSKY"), INTL( 9015, "GATEWAY"))
INTL( 9046, "The Silversky gateway spell opens a doorway that allows the caster to instantly travel to a pre-established location "
"in the viscinity of the town of Silversky. To learn this spell, you must have knowledge of the word of recall spell. "
"Do you still wish to learn it?")
SetYesNo(SILVERSKYGATEWAY)

YES(SILVERSKYGATEWAY)
	;const int nLEVEL = 70;
	const int nINT = 86;
	const int nWIS = 84;
	IF( UserSkill(__SPELL_SILVERSKY_GATEWAY) == 0 )
		IF( USER_LEVEL < nLEVEL)
			IF( USER_TRUE_INT < nINT )
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9047, "You need %u more levels, %u more intelligence and %u more wisdom to learn the Silversky gateway spell."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9048, "You need %u more levels and %u more intelligence to learn the Silversky gateway spell."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT )
				ENDIF
			ELSE
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9049, "You need %u more levels and %u more wisdom to learn the Silversky gateway spell."), nLEVEL - USER_LEVEL, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9050, "You need %u more levels to learn the Silversky gateway spell."), nLEVEL - USER_LEVEL )
				ENDIF
			ENDIF
		ELSE
			IF( USER_TRUE_INT < nINT )
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9051, "You need %u more intelligence and %u more wisdom to learn the Silversky gateway spell."), nINT - USER_TRUE_INT, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9052, "You need %u more intelligence to learn the Silversky gateway spell."), nINT - USER_TRUE_INT )
				ENDIF
			ELSE
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9053, "You need %u more wisdom to learn the Silversky gateway spell."), nWIS - USER_TRUE_WIS )
				ELSE
					IF( UserSkill(__SPELL_WORD_OF_RECALL) == 0 )
						Conversation
						INTL( 9054, "The Silversky gateway spell is beyond your control. First master the use of the word of recall "
						"spell, then I can teach it to you.")
					ELSE
						Conversation
						INTL( 712, "Very well.")
						CreateSkillList
							AddTeachSkill (__SPELL_SILVERSKY_GATEWAY, 5, 175700)
						SendTeachSkillList
					ENDIF
				ENDIF
			ENDIF
		ENDIF
	ELSE
		Conversation
		INTL( 9055, "You have already learned the Silversky gateway spell.")
	ENDIF
NO(SILVERSKYGATEWAY)
	Conversation
	INTL( 1174, "That is too bad.")
YesNoELSE(SILVERSKYGATEWAY)
	Conversation
	INTL( 715, "Do you wish to learn it now?")
	SetYesNo(SILVERSKYGATEWAY)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// STONECREST GATEWAY ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
CmdAND(INTL( 7700, "STONECREST"), INTL( 9015, "GATEWAY"))
INTL( 9056, "The Stonecrest gateway spell opens a doorway that allows the caster to instantly travel to a pre-established location "
"inside the town of Stonecrest. To learn this spell, you must have knowledge of the word of recall spell. "
"Do you still wish to learn it?")
SetYesNo(STONECRESTGATEWAY)

YES(STONECRESTGATEWAY)
	;const int nLEVEL = 70;
	const int nINT = 86;
	const int nWIS = 84;
	IF( UserSkill(__SPELL_STONECREST_GATEWAY) == 0 )
		IF( USER_LEVEL < nLEVEL)
			IF( USER_TRUE_INT < nINT )
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9057, "You need %u more levels, %u more intelligence and %u more wisdom to learn the Stonecrest gateway spell."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9058, "You need %u more levels and %u more intelligence to learn the Stonecrest gateway spell."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT )
				ENDIF
			ELSE
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9059, "You need %u more levels and %u more wisdom to learn the Stonecrest gateway spell."), nLEVEL - USER_LEVEL, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9060, "You need %u more levels to learn the Stonecrest gateway spell."), nLEVEL - USER_LEVEL )
				ENDIF
			ENDIF
		ELSE
			IF( USER_TRUE_INT < nINT )
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9061, "You need %u more intelligence and %u more wisdom to learn the Stonecrest gateway spell."), nINT - USER_TRUE_INT, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9062, "You need %u more intelligence to learn the Stonecrest gateway spell."), nINT - USER_TRUE_INT )
				ENDIF
			ELSE
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9063, "You need %u more wisdom to learn the Stonecrest gateway spell."), nWIS - USER_TRUE_WIS )
				ELSE
					IF( UserSkill(__SPELL_WORD_OF_RECALL) == 0 )
						Conversation
						INTL( 9064, "The Stonecrest gateway spell is beyond your control. First master the use of the word of recall "
						"spell, then I can teach it to you.")
					ELSE
						Conversation
						INTL( 712, "Very well.")
						CreateSkillList
							AddTeachSkill (__SPELL_STONECREST_GATEWAY, 5, 175700)
						SendTeachSkillList
					ENDIF
				ENDIF
			ENDIF
		ENDIF
	ELSE
		Conversation
		INTL( 9065, "You have already learned the Stonecrest gateway spell.")
	ENDIF
NO(STONECRESTGATEWAY)
	Conversation
	INTL( 1174, "That is too bad.")
YesNoELSE(STONECRESTGATEWAY)
	Conversation
	INTL( 715, "Do you wish to learn it now?")
	SetYesNo(STONECRESTGATEWAY)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// DRUID'S POINT GATEWAY //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
CmdAND3(INTL( 746, "DRUID"), INTL( 9066, "POINT"), INTL( 9015, "GATEWAY"))
INTL( 9067, "The Druid's Point gateway spell opens a doorway that allows the caster to instantly travel to a pre-established location "
"in the viscinity of Druid's Point, on Arakas. To learn this spell, you must have knowledge of the word of recall spell. "
"Do you still wish to learn it?")
SetYesNo(DRUIDSPOINTGATEWAY)

YES(DRUIDSPOINTGATEWAY)
	;const int nLEVEL = 70;
	const int nINT = 86;
	const int nWIS = 84;
	IF( UserSkill(__SPELL_DRUIDS_POINT_GATEWAY) == 0 )
		IF( USER_LEVEL < nLEVEL)
			IF( USER_TRUE_INT < nINT )
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9068, "You need %u more levels, %u more intelligence and %u more wisdom to learn the Druid's Point gateway spell."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9069, "You need %u more levels and %u more intelligence to learn the Druid's Point gateway spell."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT )
				ENDIF
			ELSE
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9070, "You need %u more levels and %u more wisdom to learn the Druid's Point gateway spell."), nLEVEL - USER_LEVEL, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9071, "You need %u more levels to learn the Druid's Point gateway spell."), nLEVEL - USER_LEVEL )
				ENDIF
			ENDIF
		ELSE
			IF( USER_TRUE_INT < nINT )
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9072, "You need %u more intelligence and %u more wisdom to learn the Druid's Point gateway spell."), nINT - USER_TRUE_INT, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9073, "You need %u more intelligence to learn the Druid's Point gateway spell."), nINT - USER_TRUE_INT )
				ENDIF
			ELSE
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9074, "You need %u more wisdom to learn the Druid's Point gateway spell."), nWIS - USER_TRUE_WIS )
				ELSE
					IF( UserSkill(__SPELL_WORD_OF_RECALL) == 0 )
						Conversation
						INTL( 9075, "The Druid's Point gateway spell is beyond your control. First master the use of the word of recall "
						"spell, then I can teach it to you.")
					ELSE
						Conversation
						INTL( 712, "Very well.")
						CreateSkillList
							AddTeachSkill (__SPELL_DRUIDS_POINT_GATEWAY, 5, 175700)
						SendTeachSkillList
					ENDIF
				ENDIF
			ENDIF
		ENDIF
	ELSE
		Conversation
		INTL( 9076, "You have already learned the Druid's Point gateway spell.")
	ENDIF
NO(DRUIDSPOINTGATEWAY)
	Conversation
	INTL( 1174, "That is too bad.")
YesNoELSE(DRUIDSPOINTGATEWAY)
	Conversation
	INTL( 715, "Do you wish to learn it now?")
	SetYesNo(DRUIDSPOINTGATEWAY)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// WIZARD'S VALE GATEWAY //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
CmdAND3(INTL( 6455, "WIZARD"), INTL( 9077, "VALE"), INTL( 9015, "GATEWAY"))
INTL( 9078, "The Wizard's Vale gateway spell opens a doorway that allows the caster to instantly travel to a pre-established location "
"in the viscinity of Wizard's Vale, on Raven's Dust. To learn this spell, you must have knowledge of the word of recall spell. "
"Do you still wish to learn it?")
SetYesNo(WIZARDSVALEGATEWAY)

YES(WIZARDSVALEGATEWAY)
	;const int nLEVEL = 70;
	const int nINT = 86;
	const int nWIS = 84;
	IF( UserSkill(__SPELL_WIZARDS_VALE_GATEWAY) == 0 )
		IF( USER_LEVEL < nLEVEL)
			IF( USER_TRUE_INT < nINT )
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9079, "You need %u more levels, %u more intelligence and %u more wisdom to learn the Wizard's Vale gateway spell."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9080, "You need %u more levels and %u more intelligence to learn the Wizard's Vale gateway spell."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT )
				ENDIF
			ELSE
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9081, "You need %u more levels and %u more wisdom to learn the Wizard's Vale gateway spell."), nLEVEL - USER_LEVEL, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9082, "You need %u more levels to learn the Wizard's Vale gateway spell."), nLEVEL - USER_LEVEL )
				ENDIF
			ENDIF
		ELSE
			IF( USER_TRUE_INT < nINT )
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9083, "You need %u more intelligence and %u more wisdom to learn the Wizard's Vale gateway spell."), nINT - USER_TRUE_INT, nWIS - USER_TRUE_WIS )
				ELSE
					Conversation
					FORMAT(INTL( 9084, "You need %u more intelligence to learn the Wizard's Vale gateway spell."), nINT - USER_TRUE_INT )
				ENDIF
			ELSE
				IF( USER_TRUE_WIS < nWIS )
					Conversation
					FORMAT(INTL( 9085, "You need %u more wisdom to learn the Wizard's Vale gateway spell."), nWIS - USER_TRUE_WIS )
				ELSE
					IF( UserSkill(__SPELL_WORD_OF_RECALL) == 0 )
						Conversation
						INTL( 9086, "The Wizard's Vale gateway spell is beyond your control. First master the use of the word of recall "
						"spell, then I can teach it to you.")
					ELSE
						Conversation
						INTL( 712, "Very well.")
						CreateSkillList
							AddTeachSkill (__SPELL_WIZARDS_VALE_GATEWAY, 5, 175700)
						SendTeachSkillList
					ENDIF
				ENDIF
			ENDIF
		ENDIF
	ELSE
		Conversation
		INTL( 9087, "You have already learned the Wizard's Vale gateway spell.")
	ENDIF
NO(WIZARDSVALEGATEWAY)
	Conversation
	INTL( 1174, "That is too bad.")
YesNoELSE(WIZARDSVALEGATEWAY)
	Conversation
	INTL( 715, "Do you wish to learn it now?")
	SetYesNo(WIZARDSVALEGATEWAY)

Default
""
IF (rnd.roll(dice(1,2)) == 1)
   Conversation
	INTL( 9088, "I honestly do not know.")
ELSE
   Conversation
   INTL( 5758, "I have no interest in that matter.")
ENDIF

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void Khimtesar::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Spell teacher
// 
//////////////////////////////////////////////////////////////////////////////////////////
{
NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL (__SPELL_SUNKEN_WOODS_GATEWAY, 5, 175700)
			TEACH_SKILL (__SPELL_LIGHTHAVEN_GATEWAY, 5, 175700)
			TEACH_SKILL (__SPELL_WINDHOWL_GATEWAY, 5, 175700)
			TEACH_SKILL (__SPELL_SILVERSKY_GATEWAY, 5, 175700)
			TEACH_SKILL (__SPELL_STONECREST_GATEWAY, 5, 175700)
			TEACH_SKILL (__SPELL_DRUIDS_POINT_GATEWAY, 5, 175700)
			TEACH_SKILL (__SPELL_WIZARDS_VALE_GATEWAY, 5, 175700)
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

CLOSE_NPC_DATA_EXCHANGE
}