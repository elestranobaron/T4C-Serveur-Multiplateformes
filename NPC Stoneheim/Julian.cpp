#pragma hdrstop
#include "Julian.h"

Julian::Julian()
{}

Julian::~Julian()
{}

extern NPCstructure::NPC JulianNPC;

void Julian::Create( ){
	npc = JulianNPC;
	SET_NPC_NAME( "[10862]Julian");
	npc.InitialPos.X = 210;		   
	npc.InitialPos.Y = 735;
	npc.InitialPos.world = 0;
}

void Julian::OnTalk( UNIT_FUNC_PROTOTYPE )

{

CONSTANT Nectar = 1;
CONSTANT MakeVenom = 2;
CONSTANT DidMordenthalSendYou = 3;
CONSTANT TakeRobes = 4;

InitTalk

Begin
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	FORMAT(INTL( 8885, "Hail %s! Your reputation precedes you!"), USER_NAME)
ELSE
	Conversation
	INTL( 4015, "Yes? What do you want?")
ENDIF

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 8886, "My name is Julian. Are you surprised I knew your name? Why, who has not heard of the one that slew the great Shadeen?")
ELSE
	Conversation
	INTL( 8887, "I don't see how your knowing my name will benefit me in any way.")
ENDIF

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 8888, "I live in a small house not far to the northeast. I am to spy on the townsfolk and report any important events to my \"master\".")
ELSE
	Conversation
	INTL( 8889, "Why should I tell you what I am doing here? I don't see that it's any concern of yours.")
ENDIF

CmdAND(INTL( 8890, "GLOOM"),INTL( 8891, "STAFF"))
INTL( 8892, "A must-have item for any black wizard.")

CmdAND(INTL( 7991, "ROBE"),INTL( 7992, "HELL"))
""
IF(CheckItem(__OBJ_ROBE_OF_HELL) < 3)
	Conversation
	INTL( 8893, "I know of these robes! They provide near-invulnerability against fire and darkness, "
	"but make the wearer very vulnerable against water and light. If you ever have some "
	"that you would part with, please let me know.")
ELSE
	Conversation
	INTL( 8894, "Would you want to exchange three such robes against a \"Gloom\" \"Staff\"?")
	SetYesNo(TakeRobes)
ENDIF

YES(TakeRobes)
	IF(CheckItem(__OBJ_ROBE_OF_HELL) < 3)
		Conversation
		INTL( 8895, "Well, come back when you *really* have them!")
		BREAK
	ELSE
		Conversation
		INTL( 8896, "Thank you. Here's your staff.")
		FOR(0,3) 
			TakeItem(__OBJ_ROBE_OF_HELL)
		ENDFOR
		GiveItem(__OBJ_GLOOM_STAFF)
		PRIVATE_SYSTEM_MESSAGE(INTL( 8897, "You have just received a Gloom Staff."))
		;int nExpReward = USER_LEVEL*2500;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
		GiveXP(nExpReward)
	ENDIF

NO(TakeRobes)
	Conversation
	INTL( 8898, "Well, then...")
	BREAK

YesNoELSE(TakeRobes)
	Conversation
	INTL( 8899, "Say again?")
	SetYesNo(TakeRobes)

Command(INTL( 5726, "MASTER"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 8900, "I cannot reveal his name to you... but I can tell you where to find him. He lives within a natural fortress of mountains "
	"to the north. Seek him out, and perhaps he will deem you worthy of the knowledge of his name.")
ELSE
	Conversation
	INTL( 8901, "I don't think this subject is of any importance to you.")
ENDIF

CmdAND3(INTL( 8902, "NEPHIL"), INTL( 8903, "SPIDER"), INTL( 8904, "VENOM"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	IF(CheckItem(__OBJ_SPIDER_VENOM) >= 3 && CheckItem(__OBJ_TARANTULA_FANG) >= 1 && CheckItem(__OBJ_ALCHEMY_KIT) >= 1)
		Conversation
		INTL( 8905, "Ahh, it appears that you have been successful in gathering all the things I have asked for, splendid! If you still want me "
		"to make some nephil spider venom, I will need all these things and 20000 gold for my troubles of course. "
		"Do you still wish for me to do this?")
		SetYesNo(MakeVenom)
	ELSE
		Conversation
		INTL( 8906, "Ahh, you are very informed to know that I have knowledge of this substance. I take it you wish to acquire some of this most "
		"deadly nectar yes?")
		SetYesNo(Nectar)
	ENDIF
ELSE
	Conversation
	INTL( 8901, "I don't think this subject is of any importance to you.")
ENDIF

YES(Nectar)
	Conversation
	INTL( 8907, "Wonderful! The only things I will require in order to concoct such a potent brew are 3 vials of \"spider\" \"venom\" and 1 "
	"\"tarantula\" \"fang\". I will also need to borrow an \"alchemy\" \"kit\" from you since I am rather far from my own. Get me "
	"all these things and I will be happy to give you what you want.")
NO(Nectar)
	Conversation
	INTL( 8908, "Oh, a pity then. I was rather bored and would have welcomed the diversion.")
YesNoELSE(Nectar)
	Conversation
	INTL( 8909, "Do you wish to acquire some nephil spider venom or not?")
	SetYesNo(Nectar)

YES(MakeVenom)
	IF(CheckItem(__OBJ_SPIDER_VENOM) >= 3)
		IF(CheckItem(__OBJ_TARANTULA_FANG) >= 1)
			IF(CheckItem(__OBJ_ALCHEMY_KIT) >= 1)
				IF(Gold >= 20000)
					TakeItem(__OBJ_SPIDER_VENOM)
					TakeItem(__OBJ_SPIDER_VENOM)
					TakeItem(__OBJ_SPIDER_VENOM)
					TakeItem(__OBJ_TARANTULA_FANG)
					GiveItem(__OBJ_BLACK_WIDOW_VENOM)
					TakeGold(20000)
					Conversation
					INTL( 8910, "Excellent, now may I borrow this please? ")
					PRIVATE_SYSTEM_MESSAGE(INTL( 8911, "You give your alchemy kit to Julian."))
					PRIVATE_SYSTEM_MESSAGE(INTL( 8912, "You give 3 vials of spider venom to Julian."))
					PRIVATE_SYSTEM_MESSAGE(INTL( 8913, "You give a tarantula fang to Julian."))
					PRIVATE_SYSTEM_MESSAGE(INTL( 8914, "You give 20000 gold to Julian."))
					Conversation
					INTL( 8915, "Here we go... put that in, add this, mix it all up, and voila! Trust me, it's actually much harder than it looks. ")
					PRIVATE_SYSTEM_MESSAGE(INTL( 8916, "Julian gives you back your alchemy kit."))
					PRIVATE_SYSTEM_MESSAGE(INTL( 8917, "Julian gives you a vial of nephil spider venom."))
					Conversation
					INTL( 8918, "With that done, I will resume my work unless you need more nephil spider venom. You will have to gather all the ingredients "
					"again for this, of course. Do you require more venom than what I have given you?")
					SetYesNo(MakeVenom)
				ELSE
					Conversation
					INTL( 8919, "I said 20000 gold, no less. Return once you have at least that much.")
				ENDIF
			ELSE
				Conversation
				INTL( 8920, "How do you expect me to make this venom you so desire without an alchemy kit? Return when you have acquired one for yourself.")
			ENDIF
		ELSE
			Conversation
			INTL( 8921, "You seem to be missing a crucial ingredient, or did you forget you needed a tarantula fang? Return when you have everything.")
		ENDIF
	ELSE
		IF(CheckItem(__OBJ_TARANTULA_FANG) >= 1)
			Conversation
			FORMAT(INTL( 8922, "Do not mock me, %s. If you do not have at least 3 vials of spider venom and 1 tarantula fang, then you are "
			"wasting my time. Oh and make sure you have an alchemy kit that I can borrow when you do come back."), USER_NAME)
		ELSE
			Conversation
			INTL( 8923, "You seem to be missing a very important component, or were you not listening when I said to bring 3 vials of spider venom? "
			"Do not return until you do.")
		ENDIF
	ENDIF
NO(MakeVenom)
	Conversation
	INTL( 8924, "Oh, what a pity. I was really looking forward to a change from this routine.")
YesNoELSE(MakeVenom)
	Conversation
	INTL( 8925, "Do you still wish for me to make some nephil spider venom or not?")
	SetYesNo(MakeVenom)

Command2(INTL( 8903, "SPIDER"), INTL( 8904, "VENOM"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 8926, "You can find some spider venom on the giant black widows and necrospiders far to the east of this town.")
ELSE
	Conversation
	INTL( 8901, "I don't think this subject is of any importance to you.")
ENDIF

Command2(INTL( 3954, "TARANTULA"), INTL( 8927, "FANG"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 8928, "The arachnofiends sometimes carry these. You can find them far to the east of here.")
ELSE
	Conversation
	INTL( 8901, "I don't think this subject is of any importance to you.")
ENDIF

Command2(INTL( 6514, "ALCHEMY"), INTL( 8929, "KIT"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 8930, "I believe there is a shaman in one of the skraug villages that sells these, but I cannot say precisely which.")
ELSE
	Conversation
	INTL( 8901, "I don't think this subject is of any importance to you.")
ENDIF
	
Command(INTL( 8931, "BLOOD OF OGRIMAR"))
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	IF(CheckFlag(__FLAG_USER_HAS_BLOOD_OF_OGRIMAR) == 1)
		Conversation
		INTL( 8932, "You have found the Blood of Ogrimar? Splendid! Well, just remember that I helped you get it, heh heh.")
	ELSE
		Conversation
		INTL( 8933, "Ahh, that is a most delicate subject indeed. You would do best to keep whatever is said here secret, if you value your life. "
		"I must admit that I am rather curious to see whether you are capable of acquiring this relic for yourself. I will point you "
		"in the right direction, but the rest you will have to do yourself. If you have not already been there, visit the temple of "
		"Ogrimar to the northeast. Starting your search there should prove to save you much time.")
	ENDIF
ELSE
	Conversation
	INTL( 8901, "I don't think this subject is of any importance to you.")
ENDIF

Command(INTL( 8934, "BONES OF OGRIMAR"))
""
IF( CheckFlag(__FLAG_QUEST_FOR_BONES ) == 1 )
	Conversation
	INTL( 8935, "Ahh, the Bones of Ogrimar, yes. Did my master send you to look for them?")
	SetYesNo(DidMordenthalSendYou)
ELSE
	Conversation
	INTL( 8936, "I'm afraid I don't know what you are talking about.")
ENDIF

YES(DidMordenthalSendYou)
	Conversation
	INTL( 8937, "Well in that case, I will give you all the information I have on the subject. The bones are supposedly being kept in a very deep "
	"underground \"cavern\" far to the northeast.")
NO(DidMordenthalSendYou)
	Conversation
	INTL( 8938, "I see, then there is not much I can do for you I'm afraid. You will have to seek help somewhere else.")
YesNoELSE(DidMordenthalSendYou)
	Conversation
	INTL( 8939, "Did my master send you or not?")
	SetYesNo(DidMordenthalSendYou)

Command(INTL( 2061, "CAVERN"))
""
IF(CheckFlag(__FLAG_QUEST_FOR_BONES) == 1)
	Conversation
	INTL( 8943, "There is a complex maze of caves under the northeast part of Stoneheim. Inside one of these caverns rest the Bones of Ogrimar. "
	"The \"entrance\" to this cave is but one amongst many.")
ELSEIF(CheckFlag(__FLAG_QUEST_FOR_BONES) > 1)
	Conversation
	INTL( 8944, "You have done well to find the cavern. I am not sure if I could've found it myself.")
ELSE
	Conversation
	INTL( 8945, "Cavern? What are you talking about?")
ENDIF

Command(INTL( 8946, "ENTRANCE"))
""
IF(CheckFlag(__FLAG_QUEST_FOR_BONES) == 1)
	Conversation
	INTL( 8947, "There was once a man called Venadar who was believed to be successful in finding the Bones of Ogrimar. "
	"This man, a giant among men, was a good friend of the one called Khimtesar. One day while walking outside the house of his "
	"friend after a meal, Venadar fell into an unseen hole that opened up to a huge cavern in the ground. Being very tall, he "
	"was able to climb back out of the hole and trace his steps back to the well behind Khimtesar's house. Some say he inscribed "
	"this information on the well itself. Afterwards, he returned to the hole in the ground and explored it for days, after which "
	"he found the bones. Very few know of this and even fewer know what happened to Venadar afterwards. Remember this story when "
	"you look for the entrance, and you will succeed.")
ELSEIF(CheckFlag(__FLAG_QUEST_FOR_BONES) > 1)
	Conversation
	INTL( 8944, "You have done well to find the cavern. I am not sure if I could've found it myself.")
ELSE
	Conversation
	INTL( 8936, "I'm afraid I don't know what you are talking about.")
ENDIF

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8948, "I'll have nothing to do with someone as ill-mannered as you.")
BREAK

Command5(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"),INTL( 521, "EXIT"))
""
IF(CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1)
	Conversation
	INTL( 8949, "Very well, until we meet again.")
ELSE
	Conversation
	INTL( 973, "Goodbye.")
ENDIF
BREAK

Default
""
IF(CheckFlag(__FLAG_FOLLOWER_OF_OGRIMAR) == 1)
	Conversation
	INTL( 8950, "I couldn't say, perhaps my master would know of such things.")
ELSE
	Conversation
	INTL( 8951, "I don't know what you're talking about and frankly I don't have time to think about it.")
ENDIF

EndTalk
}


