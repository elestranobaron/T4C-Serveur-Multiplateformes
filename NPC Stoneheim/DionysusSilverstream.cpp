#pragma hdrstop
#include "DionysusSilverstream.h"

DionysusSilverstream::DionysusSilverstream()
{}

DionysusSilverstream::~DionysusSilverstream()
{}

extern NPCstructure::NPC DionysusSilverstreamNPC;

void DionysusSilverstream::Create( ){
	npc = DionysusSilverstreamNPC;
   SET_NPC_NAME(   "[10848]Dionysus Silverstream" );
	npc.InitialPos.X = 1025; 
	npc.InitialPos.Y = 1000;
	npc.InitialPos.world = 0;
}

void DionysusSilverstream::OnTalk( UNIT_FUNC_PROTOTYPE )

{
CONSTANT HEALING = 1;
CONSTANT STAFFOFHOPE = 2;
CONSTANT RewardUser = 3;
CONSTANT AcceptHarp = 4;

InitTalk
									 
Begin
INTL( 8170, "Greetings, and may your day be bright and carefree, my friend.")

Command2(INTL( 483, "NAME"),INTL( 485, "WHO ARE YOU"))
INTL( 8171, "My name is Dionysus Silverstream. What is yours friend?")

Command3(INTL( 489, "WORK"),INTL( 3696, "WHAT DO YOU DO"),INTL( 487, "OCCUPATION"))
INTL( 8172, "I am here to help you rest your travel-weary bones.")

Command2(INTL( 1072, "KING"),INTL( 7998, "GRAVESOUL"))
INTL( 8173, "King Gravesoul is a proud and noble king. His heart is always sad and heavy, though, "
"but most don't notice that. I think he never recovered from the loss of his wife and son.")

Command2(INTL( 8001, "ZION"),INTL( 8002, "THUNDERHEART"))
INTL( 8174, "I can't say I like him much, but there are many who believe he should succeed King Gravesoul "
"after his passing. Let us pray this moment doesn't come to pass any time soon.")

Command2(INTL( 8005, "KYATHOS"),INTL( 8006, "SHATTERSKULL"))
INTL( 8175, "He and Gladdius protect us from monsters and enemies that might attack us when we sleep.")

Command2(INTL( 8009, "THOR"),INTL( 8010, "GLAREFIRE"))
INTL( 8176, "Don't mind his rough manners, he's a smith, not a socialite. If good weapons and equipment are "
"what you're looking for, then you should talk to him. If it's comfort and counsel, I'd be glad "
"to be of assistance.")

Command2(INTL( 8046, "MALACHAI"),INTL( 8047, "FATEBRINGER"))
INTL( 8177, "There is something very, very wrong and evil with him, but I don't know exactly what it is. Just be "
"careful around him, you never know.")

Command2(INTL( 8017, "GLADDIUS"),INTL( 8018, "WINDCHASER"))
INTL( 8178, "He and Kyathos protect us from monsters and enemies that might attack us when we sleep.")

Command2(INTL( 554, "HELP"),INTL( 896, "QUEST"))
INTL( 8179, "Should you feel like helping out, you could free the souls of my kin that are trapped in \"Skeletal\" \"Centaurs\". ")
IF (TFCTime::IsNight())
	Conversation
	INTL( 8180, "Oh, and if you've got some spare time, I'm sure I could use your help in recharging my "
	"\"Lute\" \"of\" \"Peace\".")
ENDIF

CmdAND(INTL( 9205, "LUTE"),INTL( 8182, "PEACE"))
""
IF (TFCTime::IsNight())
	IF(CheckFlag(__QUEST_DIONYSUS_RECHARGE_HARP) == 3 && CheckItem(__OBJ_LUTE_OF_PEACE) >= 1)
		Conversation
		INTL( 8183, "Oh, you brought it back already! Thank you so much! ")
		TakeItem(__OBJ_LUTE_OF_PEACE)
		RemFlag(__QUEST_DIONYSUS_RECHARGE_HARP)
		;int nExpReward = USER_LEVEL*750;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
		GiveXP(nExpReward)
		;int nGoldReward = USER_LEVEL*2000;
		PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 8184, "Dionysus gives you %u gold pieces."), nGoldReward) ) 
		GiveGoldNoEcho(nGoldReward)
		IF(rnd.roll(dice(1,3)) == 3)
			Conversation
			INTL( 8185, "Here's a little extra as a token of my gratitude.")
			GiveItem(__OBJ_ROBE_OF_HEAVEN)
			PRIVATE_SYSTEM_MESSAGE(INTL( 8186, "Dionysus gives you a Robe of Heaven."))
		ENDIF
	ELSE
		Conversation
		INTL( 8187, "It isn't something I talk about a lot, but yes, I own a Lute of Peace. It's music soothes "
		"the souls of centaurs and keeps them more peaceful. It needs to be \"recharged\", once "
		"in a while, so I can always use your help in doing this, if you've got time to spare.")
	ENDIF
ELSE
	Conversation
	INTL( 8188, "That's correct, I do own such an item, but I'd rather not talk about it now. Please "
	"come back when it's nighttime, I'll have more time to talk.")
ENDIF

Command(INTL( 8189, "GLAENSHEN"))
INTL( 8190, "I know she lives in the Nether Isles, but I don't know how to get there. I'm sure "
"someone as resourceful as you wouldn't have a problem finding her, though.")

CmdAND(INTL( 5010, "ETHER"),INTL( 8191, "KEY"))
""
IF(CheckFlag(__QUEST_DIONYSUS_RECHARGE_HARP) >= 1)
	Conversation
	INTL( 8192, "I guess you might want to ask Bastien Milandra. There's a rumor saying "
	"he's the son of Glaenshenmilandira herself, although that's a little hard to "
	"believe.")
ELSE
	Conversation
	INTL( 8193, "I'm not sure why you're asking me, but I know that some human thief has some.")
ENDIF

Command(INTL( 8194, "RECHARG"))
""
IF (TFCTime::IsNight())
	IF(CheckFlag(__QUEST_DIONYSUS_RECHARGE_HARP) >= 1)
		Conversation
		INTL( 8195, "You're already taking care of recharging my \"Lute\" \"of\" \"Peace\", right? "
		"Don't let me down, I'm counting on you.")
	ELSE
		Conversation
		INTL( 8196, "I could use some help in recharging my \"Lute\" \"of\" \"Peace\". Would you please take "
		"it to the Seraph Glaenshenmilandira?")
		SetYesNo(AcceptHarp)
	ENDIF
ELSE
	Conversation
	INTL( 8197, "I'm afraid it's better to ask me about this at night.")
ENDIF

YES(AcceptHarp)
	Conversation
	INTL( 8198, "Bravo! I expected nothing less from such a sterling person as you. Oh, if you don't "
	"know already, you'll need to get an \"Ethereal\" \"Key\" to get to the Seraph.")
	GiveFlag(__QUEST_DIONYSUS_RECHARGE_HARP, 1)
	PRIVATE_SYSTEM_MESSAGE(INTL( 8199, "Dionysus gives you a Lute of Peace."))
	GiveItem(__OBJ_LUTE_OF_PEACE)

NO(AcceptHarp)
	Conversation
	INTL( 8200, "Some other time, perhaps.")

YesNoELSE(AcceptHarp)
	Conversation
	INTL( 8201, "Please answer with a simple \"yes\" or \"no\".")
	SetYesNo(AcceptHarp)

CmdAND(INTL( 8202, "SKELETAL"),INTL( 8203, "CENTAURS"))
""
IF (CheckFlag(__FLAG_SKELETAL_CENTAURS_KILLED) < 12)
	Conversation
	FORMAT(INTL( 8204, "The only way to free the trapped souls within them is to shatter their skeletal body, I'm afraid. When you've freed "
	"a dozen or more of my kin, I will see to it that you are rewarded. So far, you have liberated %u Centaur(s) from their "
	"curse. Please keep up the good work."),CheckFlag(__FLAG_SKELETAL_CENTAURS_KILLED))
ELSE
	Conversation
	FORMAT(INTL( 8205, "I see that you have slain %u Skeletal Centaurs. Shall I reward you now?"),CheckFlag(__FLAG_SKELETAL_CENTAURS_KILLED))
	SetYesNo(RewardUser)
ENDIF

YES(RewardUser)
	Conversation
	INTL( 8206, "I gladly give you this!")
	RemFlag(__FLAG_SKELETAL_CENTAURS_KILLED)
	GiveItem(__OBJ_SCROLL_OF_HORSE_FRIENDSHIP)
	PRIVATE_SYSTEM_MESSAGE(INTL( 8207, "You receive a \"Scroll\" \"of\" \"Horse\" \"Friendship\"."))
	;int nExpReward = USER_LEVEL*1500;
	PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 7982, "You have been awarded %u experience points!"), nExpReward) ) 
	GiveXP(nExpReward)

NO(RewardUser)
	Conversation
	INTL( 8208, "There is nothing to be gained by refusing my reward. Please reconsider.")
	SetYesNo(RewardUser)

YesNoELSE(RewardUser)
	Conversation
	INTL( 8209, "I didn't quite get that. You said \"yes\", right?")
	SetYesNo(RewardUser)

CmdAND3(INTL( 1159, "SCROLL"),INTL( 10221, "HORSE"),INTL( 7973, "FRIENDSHIP"))
INTL( 8210, "With enough of these, you might befriend the \"World\" \"Wild\" \"Horse\". I'm told it's a special, magical "
"horse that can take you around the world! Oh! And be sure to *NOT* tell Malachai Fatebringer "
"that you have them. I'm told it upsets him greatly. You never know what he could do to you "
"just to get them.")

CmdAND3(INTL( 884, "WORLD"),INTL( 10208, "WILD"),INTL( 10221,  "HORSE"))
INTL( 10311, "This is a rather wonderful horse. If you own enough \"Scrolls\" \"of\" \"Horse\" \"Friendship\", "
"you may befriend this magical horse and use it to travel all over the world.")

Command(INTL( 5008, "CHAMPION OF LIGHT"))
INTL( 7709, "A Champion of Light is a person who has decided to follow the path of Light. ")

Command(INTL( 7710, "LIGHTBRINGER")) 
INTL( 8211, "To become a Lightbringer, you must be a \"Champion\" \"of\" \"Light\". If you are, then "
"all you have to do is to seek a paladin.")

Command(INTL( 8212, "STAFF OF HOPE"))
""
IF (CheckFlag(__QUEST_FIXED_ALIGNMENT) == -1) 
	Conversation
	INTL( 8213, "I sense malice deep within your soul. I am afraid that I cannot help you.")
ELSEIF (CheckFlag(__FLAG_LIGHTBRINGER_OF_ARTHERK) == 0)
	Conversation
	INTL( 8214, "I'm afraid I cannot help you. A staff of hope can only be made for a \"Lightbringer\".")
ELSE
	Conversation
	INTL( 8215, "I can create a staff of hope for you if you can supply me two stacks of \"demon\" \"tree\" \"wood\" and five \"symbols\" \"of\" \"hope\".")
	IF ((CheckItem(__OBJ_SYMBOL_OF_HOPE) >= 5) && (CheckItem(__OBJ_DEMON_TREE_WOOD) >= 2) )
		Conversation
		INTL( 8216, " Ah, I see that you already have all the necessary components. Shall I get to work and "
		"create a staff of hope for you?")
		SetYesNo(STAFFOFHOPE)
	ENDIF
ENDIF 

YES(STAFFOFHOPE)
	IF ((CheckItem(__OBJ_SYMBOL_OF_HOPE) < 5) || (CheckItem(__OBJ_DEMON_TREE_WOOD) < 2) )
		Conversation
		INTL( 8217, "I need two stacks of \"demon\" \"tree\" \"wood\" and five \"symbols\" \"of\" \"hope\". Please "
		"come back once you've gathered the required components. ")
	ELSE 
		Conversation
		INTL( 8218, "Here's the staff you asked for.")			
		GiveItem(__OBJ_STAFF_OF_HOPE) 
		FOR(0,2) 
			TakeItem(__OBJ_DEMON_TREE_WOOD)
		ENDFOR
		FOR(0,5) 
			TakeItem(__OBJ_SYMBOL_OF_HOPE)
		ENDFOR
		PRIVATE_SYSTEM_MESSAGE(INTL( 8219, "Dionysus gives you a staff of hope."))
	ENDIF

NO(STAFFOFHOPE) 
	Conversation
	INTL( 8220, "Come back if you ever change your mind.")

YesNoELSE(STAFFOFHOPE)
	Conversation
	INTL( 8221, "Do you want a staff of hope?")
	SetYesNo(STAFFOFHOPE)

CmdAND3(INTL( 6342, "DEMON"),INTL( 10209, "TREE"),INTL( 10210, "WOOD")) 
INTL( 10211, "I think you can find these corrupted creatures somewhere on Raven's Dust.") 

CmdAND(INTL( 10765, "SYMBOL"),INTL( 10272, "HOPE"))
INTL( 10768, "I think I've seen one of your kind selling these around. I think her name was Chryseida Yolangda.") 

Command(INTL( 569, "HEAL"))
""
IF (USER_MAXHP == USER_HP)
	Conversation
	INTL( 1147, "You do not need healing, you have no wounds.")
ELSE
	IF (USER_LEVEL < 5)
		Conversation
		INTL( 8222, "Since you are not strong enough to acquire gold pieces on your own, "
		"I shall heal your wounds. You are now healed, my friend.")
		CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
		PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 
		HealPlayer(USER_MAXHP)
	ELSE
		Conversation
      FORMAT(INTL( 1146, "Do you wish to be completely healed for %u gold pieces?"), ((USER_MAXHP-USER_HP) / 2))
      SetYesNo(HEALING)
	ENDIF
ENDIF

YES(HEALING)
	IF (USER_MAXHP == USER_HP)
		Conversation
		INTL( 1147, "You do not need healing, you have no wounds.")
	ELSE
		IF (Gold < ((USER_MAXHP-USER_HP)/2))
			IF (Gold > 0) 
				Conversation
				INTL( 8223, "You did not have enough gold pieces but I have healed a few of your wounds "
				"nonetheless for what you could spare.")
				CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
				HealPlayer(Gold*2) 
				PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 8224, "You give %u gold to Dionysus."), Gold) ) 
				PRIVATE_SYSTEM_MESSAGE(INTL( 8225, "Your wounds have been partially healed!")) 
				TakeGold(Gold)
			ELSE
				Conversation
				INTL( 8226, "You do not have enough gold pieces to be healed. You will have to find "
				"have to find the gold first.")
			ENDIF
		ELSE			
			Conversation
			INTL( 8227, "Thank you for this generous donation. Your wounds are now healed.  "
			"Please feel free to come back if you need more healing.")
			PRIVATE_SYSTEM_MESSAGE(FORMAT(INTL( 8224, "You give %u gold to Dionysus."), (USER_MAXHP-USER_HP) ) ) 
			PRIVATE_SYSTEM_MESSAGE(INTL( 7510, "Your wounds have been healed!")) 			
			TakeGold( ( (USER_MAXHP-USER_HP)) )
			CastSpellTarget(__SPELL_NPC_CANTRIP_SERIOUS_HEAL)
			HealPlayer(USER_MAXHP)			
		ENDIF
	ENDIF

NO(HEALING)
	Conversation
	INTL( 1239, "As you wish. Ask me again if you change your mind.")

YesNoELSE(HEALING)
	Conversation
	INTL( 2211, "So be it, my friend.")

Command4(INTL( 695, "FUCK"),INTL( 696, "SUCK"),INTL( 697, "ASSHOLE"),INTL( 698, " ASS "))
INTL( 8228, "You are a dishonor to your race. Flee now lest I summon the guards.")
BREAK

Command4(INTL( 519, "LEAVE"),INTL( 518, "BYE"),INTL( 520, "QUIT"),INTL( 517, "FAREWELL"))
INTL( 8229, "Farewell. May you not stray from the path of Light.") 
BREAK

Default
INTL( 8230, "Hmm, yes that's very interesting.")

EndTalk
}
