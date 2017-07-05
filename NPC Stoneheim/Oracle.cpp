#pragma hdrstop
#include "Oracle.h"

Oracle::Oracle()
{}

Oracle::~Oracle()
{}

extern NPCstructure::NPC OracleNPC;

void Oracle::Create( ){
   npc = OracleNPC;
   SET_NPC_NAME(   "[10903]The Oracle" );
	npc.InitialPos.X = 2724;
	npc.InitialPos.Y = 2192;
	npc.InitialPos.world = 2;
}

void Oracle::OnAttacked( UNIT_FUNC_PROTOTYPE )
{ 

	TFormat FORMAT;
	if( target != NULL )
	{
		IF(CheckFlag(__FLAG_PC_HAS_ATTACKED_ORACLE) == 0)
			GiveFlag(__FLAG_PC_HAS_ATTACKED_ORACLE, 1)
			CastSpellTarget(__SPELL_MOB_VAPORIZE_SPELL)
			SHOUT( INTL( 8786, "You will pay for this insult with your life.") );
		ENDIF
	}

NPCstructure::OnAttacked( UNIT_FUNC_PARAM );
}

void Oracle::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT REBIRTH = 1;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_USER_HAS_KILLED_MAKRSH_PTANGH) == 1)
	GiveFlag(__FLAG_USER_HAS_KILLED_MAKRSH_PTANGH, 2)
	Conversation
	INTL( 11378, "I have just felt a great tremor, one that I have not sensed in a long time. Makrsh P'Tangh is now dead "
	"and has been banished to the Nether Realm whence he came. Congratulations on this fantastic victory. We "
	"can only hope that his departure is permanent, but should it not be the case, we will call upon you to "
	"slay him again, 'till the day he returns no more.")
ELSEIF(CheckFlag(__FLAG_USER_HAS_KILLED_MAKRSH_PTANGH) == 3)
	GiveFlag(__FLAG_USER_HAS_KILLED_MAKRSH_PTANGH, 2)
	Conversation
	INTL( 11379, "It seems you have again rid us of the presence of Makrsh P'Tangh. I can only hope it will be permanent this time. "
	"Once again, I would like to thank you. Without your help, this world would be lost.")
ELSE
	GiveNPCFlag(__FLAG_ORACLE_INSULTED, 0)
	IF(CheckFlag(__FLAG_USER_HAS_DEFEATED_ASSISTANT) == 1)
		IF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= 3)
			Conversation
			INTL( 11380, "I must congratulate you on your victory against my assistant. Unfortunately, for some reason that I cannot explain, "
			"I cannot continue with your rebirth. In the mean time, perhaps you should \"prepare\" yourself for the last battle with "
			"Makrsh P'Tangh.")
		ELSE
			Conversation
			INTL( 8787, "I must congratulate you on your victory, even though I knew what the outcome would be all along. You have shown "
			"valor and determination in the face of battle. I believe you are ready to take the next step towards achieving "
			"\"purity\" \"of\" \"spirit\" \"and\" \"soul\".")
		ENDIF
	ELSEIF(CheckFlag(__FLAG_CONVERSATION_WITH_ORACLE) == 0)
		Conversation
		FORMAT(INTL( 8788, "Ahhh, at last we meet. Welcome, %s. As you no doubt have guessed, I am the Oracle."), USER_NAME)
		GiveFlag(__FLAG_CONVERSATION_WITH_ORACLE, 1) 
	ELSEIF(CheckFlag(__FLAG_CONVERSATION_WITH_ORACLE) == 1)
		Conversation
		FORMAT(INTL( 8789, "Welcome back %s. I trust you have fared well since last we met."), USER_NAME)  
	ENDIF
ENDIF

CmdAND3(INTL( 8790, "PURITY"), INTL( 8791, "SPIRIT"), INTL( 8792, "SOUL"))
""
IF(CheckFlag(__FLAG_USER_HAS_DEFEATED_ASSISTANT) == 1)
	Conversation
	INTL( 8793, "If one is pure in spirit and in soul, his true colors will be reflected by his physical self. To achieve "
	"such a level of purity, you must be \"reborn\".")
ELSE
	Conversation
	INTL( 8794, "I do not think we should be talking about this right now.")
ENDIF

CmdAND(INTL( 7390, "READY"), INTL( 8795, "REBORN"))
""
IF(CheckFlag(__FLAG_USER_HAS_DEFEATED_ASSISTANT) == 1)
//	IF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= 3)
	IF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= ACK_MAXREMORTS)		
		Conversation
		INTL( 11381, "For some reason that I cannot quite explain, I cannot continue with your rebirth. In the mean time, perhaps you should \"prepare\" "
		"yourself for the last battle with Makrsh P'Tangh.")		
	ELSE
		IF(USER_LEVEL >= (75 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5))
			//IF(CheckFlag(__FLAG_ORACLE_TOKEN) >= 1 || CheckFlag(__FLAG_NUMBER_OF_REMORTS) < 1)
				Conversation
				INTL( 8796, "Remember, after this there is no turning back. Are you absolutely certain that you wish to be reborn at this time?")
				SetYesNo(REBIRTH)
			/*ELSE
				PRIVATE_SYSTEM_MESSAGE( "Remorts are a paid feature." )
				Conversation
				INTL( 8794, "I do not think we should be talking about this right now.")
			ENDIF*/
		ELSE
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 11423, "You must be at least level %u to continue with the rebirth process."), 75 + CheckFlag(__FLAG_NUMBER_OF_REMORTS) * 5))
			Conversation
			INTL( 11424, "Unfortunately, I do not think you are strong enough to survive the rebirth process yet. Why don't you "
			"come back when you have gained more experience in the world?")
		ENDIF
	ENDIF
ELSE
	Conversation
	INTL( 8794, "I do not think we should be talking about this right now.")
ENDIF

YES(REBIRTH)
	Conversation
	INTL( 8797, "Then let it be so!")
	PRIVATE_SYSTEM_MESSAGE(INTL( 8798, "A brilliant flash of light engulfs you and you find yourself somewhere else."))
	PRIVATE_SYSTEM_MESSAGE(INTL( 8799, "You feel strangely different."))
	PRIVATE_SYSTEM_MESSAGE(INTL( 8800, "The Oracle tells you, 'We shall meet again, but until then, farewell...'"))
	IF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) == 0)
		IF(USER_GENDER == GENDER_MALE)
			CHATTER_SHOUT(FORMAT(INTL( 11349, "Congratulations to %s for attaining his first rebirth!"), USER_NAME))
		ELSE
			CHATTER_SHOUT(FORMAT(INTL( 11350, "Congratulations to %s for attaining her first rebirth!"), USER_NAME))
		ENDIF
	ELSEIF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) == 1)
		IF(USER_GENDER == GENDER_MALE)
			CHATTER_SHOUT(FORMAT(INTL( 11351, "Congratulations to %s for attaining his second rebirth!"), USER_NAME))
		ELSE
			CHATTER_SHOUT(FORMAT(INTL( 11352, "Congratulations to %s for attaining her second rebirth!"), USER_NAME))
		ENDIF
	ELSEIF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) == 2)
		IF(USER_GENDER == GENDER_MALE)
			CHATTER_SHOUT(FORMAT(INTL( 11353, "Congratulations to %s for attaining his third rebirth!"), USER_NAME))
		ELSE
			CHATTER_SHOUT(FORMAT(INTL( 11354, "Congratulations to %s for attaining her third rebirth!"), USER_NAME))
		ENDIF
	ELSEIF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) == 3)
		IF(USER_GENDER == GENDER_MALE)
			CHATTER_SHOUT(FORMAT(INTL( 11355, "Congratulations to %s for attaining his fourth rebirth!"), USER_NAME))
		ELSE
			CHATTER_SHOUT(FORMAT(INTL( 11356, "Congratulations to %s for attaining her fourth rebirth!"), USER_NAME))
		ENDIF
	ELSEIF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) == 4)
		IF(USER_GENDER == GENDER_MALE)
			CHATTER_SHOUT(FORMAT(INTL( 11357, "Congratulations to %s for attaining his fifth rebirth!"), USER_NAME))
		ELSE
			CHATTER_SHOUT(FORMAT(INTL( 11358, "Congratulations to %s for attaining her fifth rebirth!"), USER_NAME))
		ENDIF
	ELSEIF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) == 5)
		IF(USER_GENDER == GENDER_MALE)
			CHATTER_SHOUT(FORMAT(INTL( 11359, "Congratulations to %s for attaining his sixth rebirth!"), USER_NAME))
		ELSE
			CHATTER_SHOUT(FORMAT(INTL( 11360, "Congratulations to %s for attaining her sixth rebirth!"), USER_NAME))
		ENDIF
	ELSEIF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) == 6)
		IF(USER_GENDER == GENDER_MALE)
			CHATTER_SHOUT(FORMAT(INTL( 11361, "Congratulations to %s for attaining his seventh rebirth!"), USER_NAME))
		ELSE
			CHATTER_SHOUT(FORMAT(INTL( 11362, "Congratulations to %s for attaining her seventh rebirth!"), USER_NAME))
		ENDIF
	ELSEIF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) == 7)
		IF(USER_GENDER == GENDER_MALE)
			CHATTER_SHOUT(FORMAT(INTL( 11363, "Congratulations to %s for attaining his eighth rebirth!"), USER_NAME))
		ELSE
			CHATTER_SHOUT(FORMAT(INTL( 11364, "Congratulations to %s for attaining her eighth rebirth!"), USER_NAME))
		ENDIF
	ELSEIF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) == 8)
		IF(USER_GENDER == GENDER_MALE)
			CHATTER_SHOUT(FORMAT(INTL( 11365, "Congratulations to %s for attaining his ninth rebirth!"), USER_NAME))
		ELSE
			CHATTER_SHOUT(FORMAT(INTL( 11366, "Congratulations to %s for attaining her ninth rebirth!"), USER_NAME))
		ENDIF
	ELSEIF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= 9)
		IF(USER_GENDER == GENDER_MALE)
			CHATTER_SHOUT(FORMAT(INTL( 11367, "Congratulations to %s for attaining his %uth rebirth!"), USER_NAME, CheckFlag(__FLAG_NUMBER_OF_REMORTS)))
		ELSE
			CHATTER_SHOUT(FORMAT(INTL( 11368, "Congratulations to %s for attaining her %uth rebirth!"), USER_NAME, CheckFlag(__FLAG_NUMBER_OF_REMORTS)))
		ENDIF
	ENDIF 
	IF (CheckItem(__OBJ_TORCH) == 0) 
		GiveItem(__OBJ_TORCH)
	ENDIF 

	///////////////
	IF( CheckFlag( __FLAG_ORACLE_TOKEN ) >= 1 && CheckFlag( __FLAG_NUMBER_OF_REMORTS ) >= 1 )
		GiveFlag( __FLAG_ORACLE_TOKEN, CheckFlag(__FLAG_ORACLE_TOKEN) - 1 )
	ENDIF

	// This spell should dispel any teleportation spell the user has cast. 
	CastSpellTarget(__SPELL_MOB_REMORT_DISPEL)
	REMORT_TO( 1315, 920, 1 )	
	BREAK
NO(REBIRTH)
	Conversation
	INTL( 4106, "Very well then.")
YesNoELSE(REBIRTH)
	Conversation
	INTL( 8801, "Well? Do you wish to be reborn or not?")
	SetYesNo(REBIRTH)

Command2(INTL( 8795, "REBORN"), INTL( 8802, "REBIRTH"))
""
IF(CheckFlag(__FLAG_USER_HAS_DEFEATED_ASSISTANT) == 1)
	Conversation
	INTL( 8803, "Once you are reborn, you will be gifted with wings, a part of your heritage as a Seraph. You will also gain the "
	"status of a Seraph, gaining access to certain places where you could not go before. Be warned, there is a price "
	"to pay for such a prestige. Upon gaining the status of Seraph, you will be demoted to an inexperienced adventurer "
	"and will have to begin your life anew. You will, however, begin this life with greatly increased mental and "
	"physical capabilities. Well now, there is not much more I can say to prepare you. When you are \"ready\" \"to\" "
	"\"be\" \"reborn\", simply tell me so and we shall begin.")
ELSE
	Conversation
	INTL( 8794, "I do not think we should be talking about this right now.")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8804, "Since the \"beginning\" \"of\" \"time\", I have worn many guises. Those who know me now refer to me as the \"Oracle\".")

Command(INTL( 5628, "ORACLE"))
INTL( 8805, "I am one with the flow of time. I see all that was, is and will be.")

Command(INTL( 8806, "I KNOW KUNG"))
INTL( 8807, "Show me... This is a sparring program, similar to the programmed reality of the matrix. It has the same basic rules. Rules like "
"gravity. What you must remember is that these rules are no different than the rules of a computer system. Some of them "
"can be bent, others can be broken. Understand? Then hit me, if you can... BL did !")
FIGHT

CmdAND(INTL( 8808, "BEGINNING"), INTL( 8809, "TIME"))
INTL( 8810, "Since the moment of Creation, I have watched over this world. I have seen great civilizations rise and fall and entire continents "
"spring up out of great oceans, only to be swallowed up several millenia later.")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8811, "I am the Keeper of Time. I have many tasks to perform, not the least of which is the oversight of the \"balance\" "
"between Good and Evil.")

Command(INTL( 1764, "BALANCE"))
INTL( 8812, "There is \"one\" who deems himself outside of the flow of Time. His mere presence is a threat to the delicate scales of Good and "
"Evil.")

Command(INTL( 8813, " ONE"))
INTL( 8814, "I speak of \"Makrsh\" \"P'Tangh\" of course. His desire for \"death\" and \"destruction\" is beyond understanding.")

Command2(INTL( 738, "MAKRSH"), INTL( 8815, "TANG"))
INTL( 8816, "He must be dealt with, and soon, if this world is to continue its existence. There are few today with the \"potential\" to one day "
"be able to confront one powerful such as he. I believe you may be one with such \"potential\".")

Command2(INTL( 1609, "DEATH"), INTL( 8817, "DESTRUCTION"))
INTL( 8818, "The entire world will be consumed by Makrsh P'Tangh's need for destruction. He cares not what happens to any of his lieutenants and "
"followers. His desire is not to rule the world, but to destroy it as revenge for his own suffering.")

Command(INTL( 8819, "POTENTIAL"))
""
IF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= 1)
	Conversation
	INTL( 8820, "Yes, I do believe you truly have what is necessary to defeat Makrsh P'Tangh. All that remains is for you to \"prepare\" youself "
	"for the final conflict.")
ELSE
	Conversation
	INTL( 8821, "I say potential because I do not believe you would be ready to take on Makrsh P'Tangh right now. There are many \"preparations\" "
	"you must do before you are able to face him.")
ENDIF

Command(INTL( 8822, " PREP"))
""
IF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= 1)
	Conversation
	INTL( 11369, "There is very little you must do really. simply tell me when you wish to make the \"final\" \"step\" and I will "
	"send you on your way. I must remind you that if you feel you are not yet ready, you may continue with the \"test\" "
	"in order to be reborn again.")
ELSE
	Conversation
	INTL( 8824, "If you are to attain your true potential, you will have to become one with the seraph essence of your soul. I must first "
	"\"test\" you to see if you will survive the procedure.")
ENDIF

CmdAND(INTL( 11370, "FINAL"), INTL( 11371, "STEP"))
""
IF(CheckFlag(__FLAG_NUMBER_OF_REMORTS) >= 1)
	Conversation
	INTL( 11372, "Very well, the preparations are complete!")
	PRIVATE_SYSTEM_MESSAGE(INTL( 11373, "A bright light surrounds you and when you open your eyes again, you are somewhere else."))
	PRIVATE_SYSTEM_MESSAGE(INTL( 11374, "The oracle tells you: I wish you the best of luck."))
	TELEPORT(1073, 540, 0)
	BREAK
ELSE
	Conversation
	INTL( 8832, "I must ponder on this new thought...")
ENDIF

Command(INTL( 4138, "TEST"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) >= 1)
	Conversation
	INTL( 8825, "For your test, you will face Gabriel Archonis. You will fight him in a duel to the death inside a special arena. There are four "
	"doors surrounding the site, each of which will whisk you out of battle to a safe place should you so desire. To use one of these "
	"doors means that you forfeit the battle and will later have to start over. To reach the place of battle, you will require a \"key\".")
ELSEIF(CheckFlag(__QUEST_FIXED_ALIGNMENT) <= -1)
	Conversation
	INTL( 8826, "For your test, you will face Gaenen Elthorn. You will fight him in a duel to the death inside a special arena. There are four "
	"doors surrounding the site, each of which will whisk you out of battle to a safe place should you so desire. To use one of these "
	"doors means that you forfeit the battle and will later have to start over. To reach the place of battle, you will require a \"key\".")
ENDIF

Command(INTL( 8191, "KEY"))
""
IF (CheckItem(__OBJ_TRIAL_KEY) == 0) 
	Conversation
	INTL( 8827, "Here you are then... I trust you understand what must be done now. Be steadfast and you shall surely succeed. Remember this when "
	"you enter the arena. Now go and best of luck to you.")
	GiveItem(__OBJ_TRIAL_KEY)
	PRIVATE_SYSTEM_MESSAGE(INTL( 8828, "The Oracle gives you a key."))	
ELSE
	Conversation
	INTL( 11324, "You already have the trial key in your possession. I trust you understand what must be done now. Be steadfast and you shall surely succeed. "
	"Remember this when you enter the arena. Now go and best of luck to you.")
ENDIF

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
""
IF(CheckNPCFlag(__FLAG_ORACLE_INSULTED) == 0)
	Conversation
	FORMAT(INTL( 8829, "This kind of behavior will not be tolerated within these walls. You get that one for free, %s."), USER_NAME)
	GiveNPCFlag(__FLAG_ORACLE_INSULTED, 1)
ELSE 
	Conversation
	INTL( 8830, "I warned you!")
	FIGHT
ENDIF

Command4(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"))
INTL( 8831, "May you find the path that will lead you to your destiny.")
BREAK

Default
INTL( 8832, "I must ponder on this new thought...")

EndTalk
}
