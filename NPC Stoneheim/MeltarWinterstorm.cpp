#pragma hdrstop
#include "MeltarWinterstorm.h"

MeltarWinterstorm::MeltarWinterstorm()
{}

MeltarWinterstorm::~MeltarWinterstorm()
{}

extern NPCstructure::NPC MeltarWinterstormNPC;

void MeltarWinterstorm::Create( void )
{
    npc = MeltarWinterstormNPC;
    SET_NPC_NAME( "[10875]Meltar Winterstorm" );
    npc.InitialPos.X = 190;
    npc.InitialPos.Y = 1545;
    npc.InitialPos.world = 1;
}

void MeltarWinterstorm::OnTalk( UNIT_FUNC_PROTOTYPE )
{

CONSTANT HIDE = 1;
CONSTANT RENOWN = 2;
CONSTANT GEMS = 3;

InitTalk

Begin
""
IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) == 0)
	Conversation
	INTL( 9826, "Uh?! What do you want?")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 200)
	Conversation
	INTL( 9827, "You had better have a good reason for speaking to me. I will not suffer your presence much longer.")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 400)
	Conversation
	INTL( 9826, "Uh?! What do you want?")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 600)
	Conversation
	INTL( 9828, "Yes? What is your business here?")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 800)
	Conversation
	FORMAT(INTL( 9829, "Welcome %s. What can I do for you?"), USER_NAME)
ELSE
	Conversation
	FORMAT(INTL( 9830, "Ahh, %s! You honor us with your presence. How may I help you today?"), USER_NAME)
ENDIF

Command2(INTL( 9831, "MELTAR"), INTL( 9832, "WINTERSTORM"))
""
IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) == 0)
	Conversation
	INTL( 8876, "What now?")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 200)
	Conversation
	INTL( 9833, "You're trying my patience.")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 400)
	Conversation
	INTL( 8876, "What now?")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 600)
	Conversation
	INTL( 9834, "That's my name.")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 800)
	Conversation
	INTL( 9835, "Why, yes that's right, I am called Meltar Winterstorm.")
ELSE
	Conversation
	FORMAT(INTL( 9836, "Oh, it is an honor that you should know my name, %s."), USER_NAME)
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
""
IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) == 0)
	Conversation
	FORMAT(INTL( 9837, "I am Meltar Winterstorm. You do not have to tell me who you are, I already know your name, %s."), USER_NAME) 
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 200)
	Conversation
	INTL( 9838, "I will not give my name to a sniveling little brat like you!")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 400)
	Conversation
	FORMAT(INTL( 9837, "I am Meltar Winterstorm. You do not have to tell me who you are, I already know your name, %s."), USER_NAME) 
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 600)
	Conversation
	INTL( 9839, "I am called Meltar Winterstorm.")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 800)
	Conversation
	INTL( 9840, "My name? Of course, it's Meltar Winterstorm.")
ELSE
	Conversation
	INTL( 9841, "Well, my name is Meltar Winterstorm but you can just call me Meltar.")
ENDIF

Command3(INTL( 489, "WORK"),INTL( 488, "WHAT DO YOU"),INTL( 487, "OCCUPATION"))
""
IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) == 0)
	Conversation
	INTL( 9842, "Eh, you think I would tell you?")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 200)
	Conversation
	INTL( 9843, "I wouldn't give you the time of day, so what makes you think I would tell you that?")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 400)
	Conversation
	INTL( 9842, "Eh, you think I would tell you?")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 600)
	Conversation
	INTL( 9844, "I doubt my work is any concern of yours.")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 800)
	Conversation
	INTL( 9845, "I would rather not tell you what I do for a living... I'm sure you understand.")
ELSE
	Conversation
	INTL( 9846, "Heh heh, well let's just say I don't pay all my taxes and leave it at that, shall we?")
ENDIF

Command(INTL( 793, "RAVEN'S DUST"))
""
IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) == 0)
	Conversation
	INTL( 9847, "I don't care about anything that happens on that island.")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 200)
	Conversation
	INTL( 9848, "Bah! If that's where you come from then maybe you should just go back there!")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 400)
	Conversation
	INTL( 9847, "I don't care about anything that happens on that island.")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 600)
	Conversation
	INTL( 9849, "Whatever happens on that island is none of my concerns.")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 800)
	Conversation
	INTL( 9850, "Raven's Dust? I don't know much of the affairs of men on that island, so I cannot tell you anything.")
ELSE
	Conversation
	INTL( 9851, "Ahh yes, the island of Raven's Dust. I will not lie to you and say I know everything about that island, because I do not. "
	"I can't tell you anything about it, sorry friend.")
ENDIF

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
""
IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) == 0)
	Conversation
	INTL( 9852, "You think you're so tough, eh? We'll just see about that!")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 200)
	Conversation
	INTL( 9853, "Hah! You pathetic worm! I will crush you beneath the heel of my boot!")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 400)
	Conversation
	INTL( 9852, "You think you're so tough, eh? We'll just see about that!")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 600)
	Conversation
	INTL( 9854, "Come here and let me show you some manners!")
ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 800)
	Conversation
	INTL( 9855, "I will not tolerate insults from anyone, not even someone like you!")
ELSE
	Conversation
	INTL( 9856, "Do not think that because of your status with the thieves, I will not take offense from such "
	"foul language. Prepare to taste the steel of my blade!")
ENDIF
IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) > 20)
	GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) - 20)
ELSE
	GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1)
ENDIF
FIGHT

Command(INTL( 9678, "CROWN OF CORRUPTION"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckFlag(__FLAG_USER_HAS_CROWN_OF_CORRUPTION) == 1)
		Conversation
		INTL( 9857, "I have already given you the Crown of Corruption. What more do you want from me?")
	ELSE
		IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) == 0)
			Conversation
			INTL( 9858, "What the...? How is it possible that you know of the crown? We have only but acquired this fine piece and yet knowledge of "
			"it has already reached the ears of \"insignificants\" like you? What is this world coming to?")
		ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 200)
			Conversation
			INTL( 9859, "Don't insult me by asking me for that which you do not deserve.")
		ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 400)
			Conversation
			INTL( 9860, "I told you this before, you will not receive the crown from my hand until you have sufficiently increased your renown.")
		ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 600)
			Conversation
			INTL( 9861, "I can see that you are trying hard to increase your renown, but it is not yet enough, I'm afraid.")
		ELSE
			Conversation
			INTL( 9862, "Ahh, you have been a most profitable ally for us, and I thank you. As promised, here is the Crown of Corruption. "
			"I must tell you that it grieves me to lose a splendid item such as this one. I hope it will serve you well. Who knows, "
			"perhaps one day it might even mysteriously come back into our possession? heh heh.")
			PRIVATE_SYSTEM_MESSAGE(INTL( 9863, "You receive the Crown of Corruption."))
			GiveItem(__OBJ_CROWN_OF_CORRUPTION)
			GiveFlag(__FLAG_USER_HAS_CROWN_OF_CORRUPTION, 1)
		ENDIF
	ENDIF
ELSE
	Conversation
	INTL( 9864, "That's no concern of yours.")
ENDIF

Command(INTL( 9865, "INSIGNIFICANT"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckFlag(__FLAG_USER_HAS_CROWN_OF_CORRUPTION) == 1)
		Conversation
		INTL( 9866, "Yes that's right, I called you an insignificant. You probably think you're some sort of avatar or something of the like, but "
		"in reality you are nothing more than a mere puppet.")
	ELSE
		Conversation
		INTL( 9867, "Yes that's right, I called you an insignificant. You probably think you're some sort of avatar or something of the like, but "
		"in reality you are nothing more than a mere puppet. Anyway, about the crown... you can just forget about it, I doubt you would "
		"ever be smart or strong enough to \"deserve\" such a treasure.")
	ENDIF
ELSE
	Conversation
	INTL( 9864, "That's no concern of yours.")
ENDIF

Command(INTL( 9868, "DESERVE"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckFlag(__FLAG_USER_HAS_CROWN_OF_CORRUPTION) == 1)
		Conversation
		INTL( 9869, "Bah, I have already given you the crown, what more would you have me do?")
	ELSE
		Conversation
		INTL( 9870, "Hah, so you think you deserve the Crown of Corruption, is that it? Hah! HahahahaHAHAHAHA! What a laugh! I cannot believe my ears! "
		"Such arrogance, I don't know if I like you or if I want to smack you behind the head. Well, if you think yourself deserving of such "
		"a high honor as to possess the crown, who am I to question you then? I'll tell you who I am, I am the one who \"owns\" it, that's who!")
	ENDIF
ELSE
	Conversation
	INTL( 9864, "That's no concern of yours.")
ENDIF

Command(INTL( 9871, " OWN"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckFlag(__FLAG_USER_HAS_CROWN_OF_CORRUPTION) == 1)
		Conversation
		INTL( 9869, "Bah, I have already given you the crown, what more would you have me do?")
	ELSE
		Conversation
		INTL( 9872, "You will have to amass much \"renown\" before I will relinquish ownership of the crown to you.")
	ENDIF
ELSE
	Conversation
	INTL( 9864, "That's no concern of yours.")
ENDIF

Command(INTL( 9873, "INCREAS"))
INTL( 9874, "There are several ways to increase your standing with the thieves. Since we yearn for treasure of all sorts, one way of improving "
"your image would be to bring us valuable \"gems\" and \"precious\" \"stones\".")
IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) == 0)
	GiveFlag(__FLAG_FACTION_WITH_THIEVES, 250)
ENDIF

YES(RENOWN)
	IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) == 0)
		Conversation
		INTL( 9875, "Well, there is little to be said about you. You either do not wish to deal with the thieves or don't care altogether.")
	ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 200)
		Conversation
		INTL( 9876, "You insult me with your presence! You have probably slain more of my brothers than I can count! You will not receive any discounts "
		"from us, I can assure you.")
	ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 400)
		Conversation
		INTL( 9877, "Your presence is tolerable at best. I would advise you not to kill any of my brethren because it will not help you to gain our favor.")
	ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 600)
		Conversation
		INTL( 9878, "I can't say anything bad about you, nor can I say anything good, mind you. I will be watching your progress closely.")
	ELSEIF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) <= 800)
		Conversation
		INTL( 9879, "I must say you have surprised me. I did not expect my associates to take a liking to you, but it appears that they have. "
		"Keep this up and you might even be able to become one of us.")
	ELSE
		Conversation
		INTL( 9880, "Why are you even asking me that? You have the respect of every thief on this island, if not outside of it also. You will receive "
		"the best prices and rewards when it comes to trading with us.")
	ENDIF
NO(RENOWN)
	Conversation
	INTL( 9881, "Then what do you want?")
YesNoELSE(RENOWN)
	INTL( 9882, "Well? Have you come to find out how you stand with the thieves?")
	SetYesNo(RENOWN)

Command2(INTL( 9883, "GEMS"), INTL( 9884, "PRECIOUS STONES"))
""
IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) == 0)
	Conversation
	INTL( 9885, "If you want to secure our friendship, there is no better way than by gathering gems and precious stones and bringing them back to "
	"me or my colleagues. You will be rewarded differently for each type of gem depending on value, of course.")
ELSE
	Conversation
	INTL( 9886, "Have you come to give me some gems?")
	SetYesNo(GEMS)
ENDIF

Command(INTL( 9887, "RENOWN"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckFlag(__FLAG_USER_HAS_CROWN_OF_CORRUPTION) == 1)
		Conversation
		INTL( 9888, "You want to know what your standing amongst the thieves is?")
		SetYesNo(RENOWN)
	ELSE
		Conversation
		INTL( 9889, "Unless you start \"increasing\" your renown, you will never receive the crown, not by my hand at any rate.")
	ENDIF
ELSE
	Conversation
	INTL( 9888, "You want to know what your standing amongst the thieves is?")
	SetYesNo(RENOWN)
ENDIF

Command5(INTL( 518, "BYE"),INTL( 517, "FAREWELL"),INTL( 519, "LEAVE"),INTL( 521, "EXIT"),INTL( 520, "QUIT"))
INTL( 9890, "It's about time. Our little chat was somewhat boring.")
BREAK

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////// HIDE ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Command(INTL( 9391, "HIDE")) 
""
IF (CheckFlag(__FLAG_CHRYSEIDA_TOLD_ABOUT_MELTAR) == 0)
	Conversation
	INTL( 10223, "I have nothing to hide.")	
ELSEIF (CheckFlag(__FLAG_CHRYSEIDA_TOLD_ABOUT_MELTAR) == 1)
	Conversation
	INTL( 10224, "Who told you that? Hmm... never mind, you won't tell me anyway. I guess there's nothing to be done about it now. "
	"I will \"teach\" you how to hide, but if you ever breathe word of this to anyone else, I'll break your neck!")
	GiveFlag(__FLAG_CHRYSEIDA_TOLD_ABOUT_MELTAR, 2) 
ELSE // Flag Chryseida Told About Meltar == 2 
	Conversation
	INTL( 10225, "If you want to \"learn\" or \"train\" your ability to hide, just say so.")
ENDIF 

Command2(INTL( 495, "LEARN"), INTL( 496, "TEACH"))
""
IF (CheckFlag(__FLAG_CHRYSEIDA_TOLD_ABOUT_MELTAR) == 2) 
	Conversation	
	INTL( 9891, "So, you want to learn how to hide now?") 	
	SetYesNo(HIDE)
ELSE
	Conversation
	INTL( 10226, "Heh, what the hell would you want me to teach you?")
ENDIF 

YES(HIDE)
	;const int nLEVEL = 13;
	const int nAGI = 34;
	const int nINT = 20;
	IF( USER_LEVEL < nLEVEL )
		IF( USER_TRUE_AGI < nAGI )
			IF( USER_TRUE_INT < nINT )
				Conversation
				FORMAT( INTL( 9892, "You need %u more levels, %u more agility and %u more intelligence to learn hide."), nLEVEL - USER_LEVEL, nAGI - USER_TRUE_AGI, nINT - USER_TRUE_INT )
			ELSE
				Conversation
				FORMAT( INTL( 9893, "You need %u more levels and %u more agility to learn hide."), nLEVEL - USER_LEVEL, nAGI - USER_TRUE_AGI )
			ENDIF
		ELSE
			IF( USER_TRUE_INT < nINT )
				Conversation
				FORMAT( INTL( 9894, "You need %u more levels and %u more intelligence to learn hide."), nLEVEL - USER_LEVEL, nINT - USER_TRUE_INT )
			ELSE
				Conversation
				FORMAT( INTL( 9895, "You need %u more levels to learn hide."), nLEVEL - USER_LEVEL )
			ENDIF
		ENDIF
	ELSE
		IF( USER_TRUE_AGI < nAGI )
			IF( USER_TRUE_INT < nINT )
				Conversation
				FORMAT( INTL( 9896, "You need %u more agility and %u more intelligence to learn hide."), nAGI - USER_TRUE_AGI, nINT - USER_TRUE_INT )
			ELSE
				Conversation
				FORMAT( INTL( 9897, "You need %u more agility to learn hide."), nAGI - USER_TRUE_AGI )
			ENDIF
		ELSE
			IF( USER_TRUE_INT < nINT )
				Conversation
				FORMAT( INTL( 9898, "You need %u more intelligence to learn hide."), nINT - USER_TRUE_INT )
			ELSE
				Conversation
				INTL( 9899, "Alright, let's get this over with.")
				CreateSkillList
					AddTeachSkill( __SKILL_HIDE, 1, 1325 )
				SendTeachSkillList
			ENDIF
		ENDIF
	ENDIF

	//	ELSE
	//	Conversation
	//	"You already know how to hide! You're wasting my time!"
	//ENDIF

NO(HIDE)
	Conversation
	INTL( 9900, "Fine, just remember what I told you about your neck...")
YesNoELSE(HIDE)
	Conversation
	INTL( 9901, "Well, you want to learn it now or not?")
	SetYesNo(HIDE)

Command(INTL( 502, "TRAIN"))
""
IF (CheckFlag(__FLAG_CHRYSEIDA_TOLD_ABOUT_MELTAR) != 2) 
	Conversation
	INTL( 10227, "If you need training, I suggest you look elsewhere.")
ELSEIF( UserSkill(__SKILL_HIDE) == 0 )
	Conversation
	INTL( 9902, "Who do you think you're trying to fool? You haven't \"learned\" how to hide yet!")
ELSEIF( UserSkill(__SKILL_HIDE) < 100 )
	Conversation
	INTL( 9903, "Fine!")
	CreateSkillList
		AddTrainSkill( __SKILL_HIDE, 100, 75 )
	SendTrainSkillList
ELSE
	Conversation
	INTL( 9905, "Are you mocking me? You are already good enough at hide, almost as good as I am.")
ENDIF

YES(GEMS)

;int nNumRoughStones = (CheckItem(__OBJ_ROUGH_CARNELIAN)+CheckItem(__OBJ_ROUGH_AMETHYST)+CheckItem(__OBJ_ROUGH_AGATE)+CheckItem(__OBJ_ROUGH_MALACHITE) +CheckItem(__OBJ_ROUGH_RUBY)+CheckItem(__OBJ_ROUGH_SAPPHIRE)+CheckItem(__OBJ_ROUGH_DIAMOND)+CheckItem(__OBJ_ROUGH_EMERALD)+CheckItem(__OBJ_ROUGH_GARNET)+CheckItem(__OBJ_ROUGH_AQUAMARINE)+CheckItem(__OBJ_ROUGH_MOONSTONE)+CheckItem(__OBJ_ROUGH_LIMESTONE)); 
;int nNumFinelyCutStones = (CheckItem(__OBJ_FINELY_CUT_CARNELIAN)+CheckItem(__OBJ_FINELY_CUT_AMETHYST)+CheckItem(__OBJ_FINELY_CUT_AGATE)+CheckItem(__OBJ_FINELY_CUT_MALACHITE)+CheckItem(__OBJ_FINELY_CUT_RUBY)+CheckItem(__OBJ_FINELY_CUT_SAPPHIRE)+CheckItem(__OBJ_FINELY_CUT_DIAMOND)+CheckItem(__OBJ_FINELY_CUT_EMERALD)+CheckItem(__OBJ_FINELY_CUT_GARNET)+CheckItem(__OBJ_FINELY_CUT_AQUAMARINE)+CheckItem(__OBJ_FINELY_CUT_MOONSTONE)+CheckItem(__OBJ_FINELY_CUT_LIMESTONE)); 
;int nNumStonesGiven = 0;
IF ((nNumFinelyCutStones == 0) && (nNumRoughStones == 0)) 
	Conversation
	INTL( 10480, "You don't even have one stone to show me! You're just wasting my time!")
ELSE
	IF((nNumRoughStones + nNumFinelyCutStones) > 10)
		Conversation
		INTL( 10773, "So many gems, so little time. I will only take 10 for now.")
	ELSE
		Conversation
		INTL( 9906, "Splendid, let's see what you have brought me then.")
	ENDIF
	IF(CheckItem(__OBJ_ROUGH_CARNELIAN) >= 1)
		;int nNumRoughCarnelian = CheckItem(__OBJ_ROUGH_CARNELIAN);
		FOR(0, nNumRoughCarnelian)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_ROUGH_CARNELIAN)
				GiveXP(5000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9907, "You receive 5000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 1000)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 1)
				ENDIF
				IF(rnd.roll(dice(1, 5)) == 1)
					GiveItem(__OBJ_POTION_OF_LESSER_FIRE_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9908, "You receive a potion of lesser fire resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_ROUGH_AMETHYST) >= 1)
		;int nNumRoughAmethyst = CheckItem(__OBJ_ROUGH_AMETHYST);
		FOR(0, nNumRoughAmethyst)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_ROUGH_AMETHYST)
				GiveXP(5000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9907, "You receive 5000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 1000)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 1)
				ENDIF
				IF(rnd.roll(dice(1, 5)) == 1)
					GiveItem(__OBJ_POTION_OF_LESSER_WATER_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9909, "You receive a potion of lesser water resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_ROUGH_AGATE) >= 1)
		;int nNumRoughAgate = CheckItem(__OBJ_ROUGH_AGATE);
		FOR(0, nNumRoughAgate)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_ROUGH_AGATE)
				GiveXP(5000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9907, "You receive 5000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 1000)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 1)
				ENDIF
				IF(rnd.roll(dice(1, 5)) == 1)
					GiveItem(__OBJ_POTION_OF_LESSER_AIR_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9910, "You receive a potion of lesser air resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_ROUGH_MALACHITE) >= 1)
		;int nNumRoughMalachite = CheckItem(__OBJ_ROUGH_MALACHITE);
		FOR(0, nNumRoughMalachite)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_ROUGH_MALACHITE)
				GiveXP(5000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9907, "You receive 5000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 1000)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 1)
				ENDIF
				IF(rnd.roll(dice(1, 5)) == 1)
					GiveItem(__OBJ_POTION_OF_LESSER_EARTH_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9911, "You receive a potion of lesser earth resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_ROUGH_RUBY) >= 1)
		;int nNumRoughRuby = CheckItem(__OBJ_ROUGH_RUBY);
		FOR(0, nNumRoughRuby)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_ROUGH_RUBY)
				GiveXP(10000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9912, "You receive 10000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 998)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 3)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 7)) == 1)
					GiveItem(__OBJ_POTION_OF_PARTIAL_FIRE_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9913, "You receive a potion of partial fire resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_ROUGH_SAPPHIRE) >= 1)
		;int nNumRoughSapphire = CheckItem(__OBJ_ROUGH_SAPPHIRE);
		FOR(0, nNumRoughSapphire)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_ROUGH_SAPPHIRE)
				GiveXP(10000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9912, "You receive 10000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 998)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 3)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 7)) == 1)
					GiveItem(__OBJ_POTION_OF_PARTIAL_WATER_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9914, "You receive a potion of partial water resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_ROUGH_DIAMOND) >= 1)
		;int nNumRoughDiamond = CheckItem(__OBJ_ROUGH_DIAMOND);
		FOR(0, nNumRoughDiamond)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_ROUGH_DIAMOND)
				GiveXP(10000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9912, "You receive 10000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 998)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 3)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 7)) == 1)
					GiveItem(__OBJ_POTION_OF_PARTIAL_AIR_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9915, "You receive a potion of partial air resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_ROUGH_EMERALD) >= 1)
		;int nNumRoughEmerald = CheckItem(__OBJ_ROUGH_EMERALD);
		FOR(0, nNumRoughEmerald)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_ROUGH_EMERALD)
				GiveXP(10000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9912, "You receive 10000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 998)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 3)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 7)) == 1)
					GiveItem(__OBJ_POTION_OF_PARTIAL_EARTH_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9916, "You receive a potion of partial earth resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_ROUGH_GARNET) >= 1)
		;int nNumRoughGarnet = CheckItem(__OBJ_ROUGH_GARNET);
		FOR(0, nNumRoughGarnet)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_ROUGH_GARNET)
				GiveXP(15000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9917, "You receive 15000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 995)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 6)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 10)) == 1)
					GiveItem(__OBJ_POTION_OF_GREATER_FIRE_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9918, "You receive a potion of greater fire resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_ROUGH_AQUAMARINE) >= 1)
		;int nNumRoughAquamarine = CheckItem(__OBJ_ROUGH_AQUAMARINE);
		FOR(0, nNumRoughAquamarine)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_ROUGH_AQUAMARINE)
				GiveXP(15000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9917, "You receive 15000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 995)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 6)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 10)) == 1)
					GiveItem(__OBJ_POTION_OF_GREATER_WATER_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9919, "You receive a potion of greater water resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_ROUGH_MOONSTONE) >= 1)
		;int nNumRoughMoonstone = CheckItem(__OBJ_ROUGH_MOONSTONE);
		FOR(0, nNumRoughMoonstone)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_ROUGH_MOONSTONE)
				GiveXP(15000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9917, "You receive 15000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 995)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 6)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 10)) == 1)
					GiveItem(__OBJ_POTION_OF_GREATER_AIR_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9920, "You receive a potion of greater air resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_ROUGH_LIMESTONE) >= 1)
		;int nNumRoughLimestone = CheckItem(__OBJ_ROUGH_LIMESTONE);
		FOR(0, nNumRoughLimestone)			
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_ROUGH_LIMESTONE)
				GiveXP(15000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9917, "You receive 15000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 995)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 6)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 10)) == 1)
					GiveItem(__OBJ_POTION_OF_GREATER_EARTH_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9921, "You receive a potion of greater earth resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_FINELY_CUT_CARNELIAN) >= 1)
		;int nNumFinelyCutCarnelian = CheckItem(__OBJ_FINELY_CUT_CARNELIAN);
		FOR(0, nNumFinelyCutCarnelian)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_FINELY_CUT_CARNELIAN)
				GiveXP(20000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9922, "You receive 20000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 996)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 5)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 2)) == 1)
					GiveItem(__OBJ_POTION_OF_LESSER_FIRE_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9908, "You receive a potion of lesser fire resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_FINELY_CUT_AMETHYST) >= 1)
		;int nNumFinelyCutAmethyst = CheckItem(__OBJ_FINELY_CUT_AMETHYST);
		FOR(0, nNumFinelyCutAmethyst)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_FINELY_CUT_AMETHYST)
				GiveXP(20000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9922, "You receive 20000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 996)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 5)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 2)) == 1)
					GiveItem(__OBJ_POTION_OF_LESSER_WATER_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9909, "You receive a potion of lesser water resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_FINELY_CUT_AGATE) >= 1)
		;int nNumFinelyCutAgate = CheckItem(__OBJ_FINELY_CUT_AGATE);
		FOR(0, nNumFinelyCutAgate)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_FINELY_CUT_AGATE)
				GiveXP(20000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9922, "You receive 20000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 996)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 5)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 2)) == 1)
					GiveItem(__OBJ_POTION_OF_LESSER_AIR_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9910, "You receive a potion of lesser air resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_FINELY_CUT_MALACHITE) >= 1)
		;int nNumFinelyCutMalachite = CheckItem(__OBJ_FINELY_CUT_MALACHITE);
		FOR(0, nNumFinelyCutMalachite)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_FINELY_CUT_MALACHITE)
				GiveXP(20000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9922, "You receive 20000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 996)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 5)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 2)) == 1)
					GiveItem(__OBJ_POTION_OF_LESSER_EARTH_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9911, "You receive a potion of lesser earth resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_FINELY_CUT_RUBY) >= 1)
		;int nNumFinelyCutRuby = CheckItem(__OBJ_FINELY_CUT_RUBY);
		FOR(0, nNumFinelyCutRuby)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_FINELY_CUT_RUBY)
				GiveXP(25000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9923, "You receive 25000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 986)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 15)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 3)) == 1)
					GiveItem(__OBJ_POTION_OF_PARTIAL_FIRE_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9913, "You receive a potion of partial fire resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_FINELY_CUT_SAPPHIRE) >= 1)
		;int nNumFinelyCutSapphire = CheckItem(__OBJ_FINELY_CUT_SAPPHIRE);
		FOR(0, nNumFinelyCutSapphire)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_FINELY_CUT_SAPPHIRE)
				GiveXP(25000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9923, "You receive 25000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 986)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 15)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 3)) == 1)
					GiveItem(__OBJ_POTION_OF_PARTIAL_WATER_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9914, "You receive a potion of partial water resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_FINELY_CUT_DIAMOND) >= 1)
		;int nNumFinelyCutDiamond = CheckItem(__OBJ_FINELY_CUT_DIAMOND);
		FOR(0, nNumFinelyCutDiamond)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_FINELY_CUT_DIAMOND)
				GiveXP(25000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9923, "You receive 25000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 986)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 15)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 3)) == 1)
					GiveItem(__OBJ_POTION_OF_PARTIAL_AIR_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9915, "You receive a potion of partial air resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_FINELY_CUT_EMERALD) >= 1)
		;int nNumFinelyCutEmerald = CheckItem(__OBJ_FINELY_CUT_EMERALD);
		FOR(0, nNumFinelyCutEmerald)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_FINELY_CUT_EMERALD)
				GiveXP(25000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9923, "You receive 25000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 986)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 15)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 3)) == 1)
					GiveItem(__OBJ_POTION_OF_PARTIAL_EARTH_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9916, "You receive a potion of partial earth resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_FINELY_CUT_GARNET) >= 1)
		;int nNumFinelyCutGarnet = CheckItem(__OBJ_FINELY_CUT_GARNET);
		FOR(0, nNumFinelyCutGarnet)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_FINELY_CUT_GARNET)
				GiveXP(30000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9924, "You receive 30000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 971)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 30)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 4)) == 1)
					GiveItem(__OBJ_POTION_OF_GREATER_FIRE_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9918, "You receive a potion of greater fire resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_FINELY_CUT_AQUAMARINE) >= 1)
		;int nNumFinelyCutAquamarine = CheckItem(__OBJ_FINELY_CUT_AQUAMARINE);
		FOR(0, nNumFinelyCutAquamarine)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_FINELY_CUT_AQUAMARINE)
				GiveXP(30000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9924, "You receive 30000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 971)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 30)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 4)) == 1)
					GiveItem(__OBJ_POTION_OF_GREATER_WATER_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9919, "You receive a potion of greater water resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_FINELY_CUT_MOONSTONE) >= 1)
		;int nNumFinelyCutMoonstone = CheckItem(__OBJ_FINELY_CUT_MOONSTONE);
		FOR(0, nNumFinelyCutMoonstone)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_FINELY_CUT_MOONSTONE)
				GiveXP(30000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9924, "You receive 30000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 971)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 30)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 4)) == 1)
					GiveItem(__OBJ_POTION_OF_GREATER_AIR_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9920, "You receive a potion of greater air resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
	IF(CheckItem(__OBJ_FINELY_CUT_LIMESTONE) >= 1)
		;int nNumFinelyCutLimestone = CheckItem(__OBJ_FINELY_CUT_LIMESTONE);
		FOR(0, nNumFinelyCutLimestone)
			IF(nNumStonesGiven < 10)
				;nNumStonesGiven++;
				TakeItem(__OBJ_FINELY_CUT_LIMESTONE)
				GiveXP(30000)
				PRIVATE_SYSTEM_MESSAGE(INTL( 9924, "You receive 30000 experience points."))
				IF(CheckFlag(__FLAG_FACTION_WITH_THIEVES) < 971)
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, CheckFlag(__FLAG_FACTION_WITH_THIEVES) + 30)
				ELSE
					GiveFlag(__FLAG_FACTION_WITH_THIEVES, 1000)
				ENDIF
				IF(rnd.roll(dice(1, 4)) == 1)
					GiveItem(__OBJ_POTION_OF_GREATER_EARTH_RESISTANCE)
					PRIVATE_SYSTEM_MESSAGE(INTL( 9921, "You receive a potion of greater earth resistance."))
				ENDIF
			ENDIF
		ENDFOR
	ENDIF
ENDIF 

NO(GEMS)
	Conversation
	INTL( 9925, "Huh, that's not what I wanted to hear.")
YesNoELSE(GEMS)
	Conversation
	INTL( 9886, "Have you come to give me some gems?")
	SetYesNo(GEMS)

Default
""
IF (rnd.roll(dice(1,2)) == 1)
	Conversation
	INTL( 5396, "I honestly don't know.")
ELSE
	Conversation
	INTL( 5250, "I don't think that concerns me.")
ENDIF

EndTalk
}

//////////////////////////////////////////////////////////////////////////////////////////
void MeltarWinterstorm::OnNPCDataExchange( UNIT_FUNC_PROTOTYPE )
//////////////////////////////////////////////////////////////////////////////////////////
// Rolph data function, handles his shop
// 
//////////////////////////////////////////////////////////////////////////////////////////
{

NPC_DATA_EXCHANGE

	NPC_DATA_TEACH
		NPC_TEACH_SKILL_LIST
			TEACH_SKILL( __SKILL_HIDE, 1, 1325 )
		CLOSE_NPC_TEACH_SKILL_LIST
	CLOSE_NPC_DATA_TEACH

	NPC_DATA_TRAIN		 
		TRAIN_SKILL( __SKILL_HIDE, 100, 75 )
	CLOSE_NPC_DATA_TRAIN

CLOSE_NPC_DATA_EXCHANGE
}